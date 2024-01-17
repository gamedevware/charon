#include "TCharonCliCommand.h"

#include "JsonObjectConverter.h"
#include "Async/Async.h"
#include "GameData/Formatters/FJsonGameDataReader.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY(LogTCharonCliCommand);

template <typename InResultType>
TCharonCliCommand<InResultType>::TCharonCliCommand(const TSharedRef<FMonitoredProcess>& Process)
	:Process(Process), DispatchThread(ENamedThreads::AnyThread)
{
	CommandSucceed.AddLambda([this](InResultType _) { this->TaskSucceed.Broadcast(); });
	CommandFailed.AddLambda([this](int32 _, FString __) { this->TaskFailed.Broadcast(); });
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::Run(ENamedThreads::Type EventDispatchThread)
{
	const auto WeakThisPtr = this->AsWeak();
	Process->OnCompleted().BindLambda([WeakThisPtr](int32 ExitCode)
	{
		const auto ThisPtr = WeakThisPtr.Pin();
		if (!ThisPtr.IsValid()) { return; }
		if (ThisPtr->DispatchThread != ENamedThreads::AnyThread)
		{
			AsyncTask(ThisPtr->DispatchThread, [WeakThisPtr, ExitCode]
			{
				const auto ThisPtr = WeakThisPtr.Pin();
				if (!ThisPtr.IsValid()) { return; }
				ThisPtr->OnProcessCompleted(ExitCode);				
			});
		}
		else
		{
			ThisPtr->OnProcessCompleted(ExitCode);
		}
	});
	
	Process->OnCanceled().BindLambda([WeakThisPtr]
	{
		const auto ThisPtr = WeakThisPtr.Pin();
		if (!ThisPtr.IsValid()) { return; }
		if (ThisPtr->DispatchThread != ENamedThreads::AnyThread)
		{
			AsyncTask(ThisPtr->DispatchThread, [WeakThisPtr]
			{
				const auto ThisPtr = WeakThisPtr.Pin();
				if (!ThisPtr.IsValid()) { return; }
				ThisPtr->OnProcessCancelled();				
			});
		}
		else
		{
			ThisPtr->OnProcessCancelled();
		}
	});
	
	Process->OnOutput().BindLambda([WeakThisPtr](const FString& OutputChunk)
	{
		const auto ThisPtr = WeakThisPtr.Pin();
		if (!ThisPtr.IsValid()) { return; }
		ThisPtr->OnProcessOutput(OutputChunk);
	});

	this->DispatchThread = EventDispatchThread;
	
	const bool bRunSuccess = Process->Launch();
	if(!bRunSuccess)
	{
		auto _ = Process->OnCanceled().ExecuteIfBound();
	}
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::OnProcessCompleted(int32 ExitCode) const
{
	UE_LOG(LogTCharonCliCommand, Log, TEXT("Command process has been finished with %d exit code."), ExitCode);
	
	InResultType Result;
	if (!TryReadResult(Output, ExitCode, Result))
	{
		this->CommandFailed.Broadcast(ExitCode, Output);
		return;
	}
	CommandSucceed.Broadcast(Result);
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::OnProcessCancelled() const
{
	UE_LOG(LogTCharonCliCommand, Log, TEXT("Command process has been stopped or cancelled by other means."));

	this->CommandFailed.Broadcast(INT32_MIN, TEXT("Process launch failed or has been cancelled."));
}

template <typename InResultType>
void TCharonCliCommand<InResultType>::OnProcessOutput(const FString& OutputChunk)
{
	this->Output += OutputChunk;
}

template <typename InResultType>
bool TCharonCliCommand<InResultType>::TryReadResult(const FString& Output, int32 ExitCode, TSharedPtr<FJsonObject>& OutResult)
{
	if (ExitCode != 0)
	{
		return false;
	}
	
	const TUniquePtr<FBufferReader> OutputReader = MakeUnique<FBufferReader>((void*)*Output, Output.Len() * sizeof(TCHAR), false);
	check(OutputReader.IsValid());
	TSharedPtr<FJsonValue> OutValue;
	const auto JsonReader = TJsonReaderFactory<UTF8CHAR>::Create(OutputReader.Get());
	
	if (!FJsonSerializer::Deserialize(JsonReader, OutValue))
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Failed to read command's output as JSON. Output is not a valid JSON. Output: "));
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("%s"), *Output);
		return false;
	}
	
	TSharedPtr<FJsonObject>* OutObject;
	if (OutValue->TryGetObject(OutObject) && OutObject != nullptr && OutObject->IsValid())
	{
		UE_LOG(LogTCharonCliCommand, Warning, TEXT("Failed to read command's output as JSON. Result value is not a JSON object."));

		OutResult = OutObject->ToSharedRef();
		return true;
	}
	return false;
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
void TCharonCliCommand<InResultType>::Stop() const
{
	Process->Stop();
}
