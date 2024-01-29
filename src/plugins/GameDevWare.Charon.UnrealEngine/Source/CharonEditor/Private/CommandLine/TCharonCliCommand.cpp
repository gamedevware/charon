#pragma once

#include "GameData/CommandLine/TCharonCliCommand.h"

#include "JsonObjectConverter.h"
#include "Async/Async.h"
#include "GameData/Formatters/FJsonGameDataReader.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY(LogTCharonCliCommand);

template <typename InResultType>
TCharonCliCommand<InResultType>::TCharonCliCommand(
	const TSharedRef<FMonitoredProcess>& Process,
	const FText& DisplayName,
	const FString& OutputFilePath)
	: DisplayName(DisplayName), Process(Process), DispatchThread(ENamedThreads::AnyThread), RunStatus(ERunStatus::ReadyToRun)
{
	CommandSucceed.AddLambda([this](InResultType _) { TaskSucceed.Broadcast(); });
	CommandFailed.AddLambda([this](int32 _, FString __) { TaskFailed.Broadcast(); });
	this->OutputFilePath = OutputFilePath;
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::Run(ENamedThreads::Type EventDispatchThread)
{
	ERunStatus ExpectedReadyToRun = ERunStatus::ReadyToRun;
	if (!RunStatus.compare_exchange_strong(ExpectedReadyToRun, ERunStatus::Running))
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Unable to run command because it is already running or finished."));
		return false;
	}

	const auto WeakThisPtr = this->AsWeak();
	DispatchThread = EventDispatchThread;
	BroadcastEvent(WeakThisPtr, TaskStart, DispatchThread);
	
	if (DispatchThread != ENamedThreads::AnyThread)
	{
		Process->OnCompleted().BindSP(this, &TCharonCliCommand::OnProcessCompleted);
		Process->OnCanceled().BindSP(this, &TCharonCliCommand::OnProcessCancelled);
	}
	else
	{
		Process->OnCompleted().BindLambda([WeakThisPtr, EventDispatchThread](int32 ExitCode)
		{
			AsyncTask(EventDispatchThread, [WeakThisPtr, ExitCode]
			{
				if (const auto ThisPtr = WeakThisPtr.Pin())
				{
					ThisPtr->OnProcessCompleted(ExitCode);
				}
			});
		});
		Process->OnCanceled().BindLambda([WeakThisPtr, EventDispatchThread]
		{
			AsyncTask(EventDispatchThread, [WeakThisPtr]
			{
				if (const auto ThisPtr = WeakThisPtr.Pin())
				{
					ThisPtr->OnProcessCancelled();
				}
			});
		});
	}
	Process->OnOutput().BindSP(this, &TCharonCliCommand::OnProcessOutput);
	
	const bool bRunSuccess = Process->Launch();
	if(!bRunSuccess)
	{
		auto _ = Process->OnCanceled().ExecuteIfBound();
	}
	return bRunSuccess;
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::OnProcessCompleted(int32 ExitCode)
{
	ERunStatus ExpectedRunning = RunStatus.load();
	if (ExpectedRunning != ERunStatus::Running)
	{
		return; // already finished
	}
	
	UE_LOG(LogTCharonCliCommand, Log, TEXT("Command's '%s' process has been finished with exit code %d."), *DisplayName.ToString(), ExitCode);

	FString Output;
	if (!OutputFilePath.IsEmpty() && FPaths::FileExists(OutputFilePath))
	{
		FFileHelper::LoadFileToString(Output, *OutputFilePath);
	}
	
	InResultType Result;
	if (!TryReadResult(Output, ExitCode, Result))
	{
		if (!RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Failed))
		{
			return; // already finished
		}
		
		CommandFailed.Broadcast(ExitCode, Output);
	}
	else
	{
		if (!RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Succeed))
		{
			return; // already finished
		}
		
		CommandSucceed.Broadcast(Result);
	}
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::OnProcessCancelled()
{
	ERunStatus ExpectedRunning = ERunStatus::Running;
	if (!RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Stopped))
	{
		return; // already finished
	}
	
	UE_LOG(LogTCharonCliCommand, Log, TEXT("Command's '%s' process has been stopped or canceled by other means."), *DisplayName.ToString());

	CommandFailed.Broadcast(INT32_MIN, TEXT("Process launch failed or has been cancelled."));
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::OnProcessOutput(FString Output)
{
	auto SharedOutputRef = MakeShared<FString>(Output);
	const auto WeakThisPtr = this->AsWeak();
	AsyncTask(ENamedThreads::GameThread, [WeakThisPtr, SharedOutputRef]()
	{
		if (!WeakThisPtr.IsValid()) return;
		UE_LOG(LogTCharonCliCommand, Log, TEXT("%s"), *SharedOutputRef.Get());
	});
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::TryReadResult(const FString& Output, int32 ExitCode, TSharedPtr<FJsonObject>& OutResult)
{
	if (ExitCode != 0)
	{
		return false;
	}
	
	const auto JsonReader = TJsonReaderFactory<>::Create(Output);
	TSharedPtr<FJsonValue> OutValue;
	
	if (!FJsonSerializer::Deserialize(JsonReader, OutValue) || !OutValue.IsValid())
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Failed to read command's output as JSON. Output is not a valid JSON. Output: "));
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("%s"), *Output);
		return false;
	}
	
	TSharedPtr<FJsonObject>* OutObject;
	if (!OutValue->TryGetObject(OutObject) || !OutObject->IsValid())
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Failed to read command's output as JSON. Result value is not a JSON object."));
		return false;
	}

	check(OutObject);
	OutResult = OutObject->ToSharedRef();
	return true;
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::TryReadResult(const FString& Output, int32 ExitCode, int32& OutResult)
{
	if (ExitCode != 0)
	{
		return false;
	}
	
	OutResult = ExitCode;
	return true;
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::TryReadResult(const FString& Output, int32 ExitCode, FString& OutResult)
{
	if (ExitCode != 0)
	{
		return false;
	}

	OutResult = Output;
	return true;
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::TryReadResult(const FString& Output, int32 ExitCode, FValidationReport& OutResult)
{
	TSharedPtr<FJsonObject> Object;
	if (!TryReadResult(Output, ExitCode, Object))
	{
		return false;
	}
	check(Object.IsValid());
	
	FText FailReason;
	if(!FJsonObjectConverter::JsonObjectToUStruct<FValidationReport>(Object.ToSharedRef(), &OutResult, 0, 0, false, &FailReason))
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Failed to read command's output as JSON. Result value is not valid 'FValidationReport' object. Reason: %s."), *FailReason.ToString());
		return false;
	}

	return true;
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::TryReadResult(const FString& Output, int32 ExitCode, FImportReport& OutResult)
{
	TSharedRef<FJsonObject> Object;
	if (!TryReadResult(Output, ExitCode, Object))
	{
		return false;
	}

	FText FailReason;
	if(!FJsonObjectConverter::JsonObjectToUStruct<FImportReport>(Object, &OutResult, 0, 0, false, &FailReason))
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Failed to read command's output as JSON. Result value is not valid 'FImportReport' object. Reason: %s."), *FailReason.ToString());
		return false;
	}
	return true;
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::Stop()
{
	Process->Stop();
}
