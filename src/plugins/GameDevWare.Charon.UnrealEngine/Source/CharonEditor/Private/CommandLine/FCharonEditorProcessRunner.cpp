#pragma once

#include "GameData/CommandLine/FCharonEditorProcessRunner.h"

#include "GameData/CommandLine/EGameDataEditorLaunchStatus.h"
#include "GameData/CommandLine/FCharonCliCommandRunner.h"
#include "HttpModule.h"
#include "Async/Async.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Misc/FileHelper.h"

DEFINE_LOG_CATEGORY(LogFCharonEditorProcessRunner);

constexpr float CheckTimerPeriod = 2.0; // 2 seconds

FCharonEditorProcessRunner::FCharonEditorProcessRunner(const FString& InDataBaseUrl, const uint16 InPort, const FTimespan InLaunchTimeout)
{
	this->LaunchTimeout = InLaunchTimeout;
	this->StartUrl = FString::Format(TEXT("http://localhost:{0}/"), { InPort });
	
	const uint32 EditorPid = FPlatformProcess::GetCurrentProcessId();
	const FString ProjectDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	const FString RunParameters = FString::Format(TEXT("SERVER START --dataBase \"{0}\" --port \"{1}\" --watchPid {2} --log con"), { InDataBaseUrl, InPort, EditorPid });
	const FString CharonIntermediateDirectory = FCharonCliCommandRunner::GetOrCreateCharonIntermediateDirectory();
	
#if PLATFORM_WINDOWS
	this->RunScriptPath = CharonIntermediateDirectory / TEXT("RunCharon.bat");
	FString URL = TEXT("cmd.exe");
	FString Params = FString::Printf(TEXT("/c \"\"%s\" %s\""), *RunScriptPath, *RunParameters);
#elif PLATFORM_MAC || PLATFORM_LINUX
	RunScriptPath = CharonIntermediateDirectory / TEXT("RunCharon.sh");
	FString URL = TEXT("/usr/bin/env");
	FString Params = FString::Printf(TEXT(" -- \"%s\" %s"), *RunScriptPath, *RunParameters);
#endif
	this->ExecutableName = FPaths::GetCleanFilename(RunScriptPath);
	bool bInHidden = true;
	bool bInCreatePipes = true;
	this->Process = MakeShared<FMonitoredProcess>(URL, Params, ProjectDirectory, bInHidden, bInCreatePipes);

	UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Preparing to launching '%s' executable with '%s' parameters at '%s' working directory."), *ExecutableName, *RunParameters, *ProjectDirectory);
}

FCharonEditorProcessRunner::~FCharonEditorProcessRunner()
{
	GEditor->GetTimerManager()->ClearTimer(this->LaunchCheckTimer);
	this->LaunchCheckRequest = nullptr;
}

bool FCharonEditorProcessRunner::Launch()
{
	if (this->LaunchCheckTimer.IsValid())
	{
		UE_LOG(LogFCharonEditorProcessRunner, Warning, TEXT("Unable to FGameDataEditorProcessRunner::Launch() again because it is already been launched."));
		return false;
	}

	if (!FPaths::FileExists(this->RunScriptPath))
	{
		UE_LOG(LogFCharonEditorProcessRunner, Warning, TEXT("Missing launch script file at '%s'."), *this->RunScriptPath);
		this->RaiseLaunched(EGameDataEditorLaunchStatus::MissingRunScript);
		return false;
	}
	
	auto WeakThisPtr = this->AsWeak();
	this->Process->OnOutput().BindLambda([WeakThisPtr](FString Output)
	{
		auto SharedOutputRef = MakeShared<FString>(Output);
		AsyncTask(ENamedThreads::GameThread, [WeakThisPtr, SharedOutputRef]()
		{
			if (!WeakThisPtr.IsValid()) return;
			if (SharedOutputRef->Contains(TEXT("Error]")))
			{
				UE_LOG(LogFCharonEditorProcessRunner, Error, TEXT("%s"), *SharedOutputRef.Get());
			}
			else if(SharedOutputRef->Contains(TEXT("Warning]")))
			{
				UE_LOG(LogFCharonEditorProcessRunner, Warning, TEXT("%s"), *SharedOutputRef.Get());
			}
			else
			{
				UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("%s"), *SharedOutputRef.Get());
			}
		});
	});
	
	this->Process->OnCanceled().BindLambda([WeakThisPtr]
	{
		AsyncTask(ENamedThreads::GameThread, [WeakThisPtr]
		{
			const auto ThisPtr = WeakThisPtr.Pin();
			if (!ThisPtr.IsValid()) return;
			UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Script at '%s' has been interrupted."), *ThisPtr->ExecutableName);
		});
	});
	
	this->Process->OnCompleted().BindLambda([WeakThisPtr](int32 ExitCode)
	{
		AsyncTask(ENamedThreads::GameThread, [WeakThisPtr, ExitCode]
		{
			const auto ThisPtr = WeakThisPtr.Pin();
			if (!ThisPtr.IsValid()) return;
			UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Executable at '%s' has exited with code %d."), *ThisPtr->ExecutableName, ExitCode);
		});
	});
	
	this->LaunchTimeoutTime = FDateTime::Now() + this->LaunchTimeout; 
	
	const bool bLaunched = this->Process->Launch();
	if (!bLaunched)
	{
		UE_LOG(LogFCharonEditorProcessRunner, Warning, TEXT("Failed to launch script file at '%s'."), *this->RunScriptPath);
		this->RaiseLaunched(EGameDataEditorLaunchStatus::Failed);
		return false;
	}

	UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Successfully launched script '%s'. Starting polling HTTP Server for response."), *this->RunScriptPath);
	
	FTimerDelegate OnCheckTimerDelegate;
	OnCheckTimerDelegate.BindSP(this, &FCharonEditorProcessRunner::OnCheckTimer);
	GEditor->GetTimerManager()->SetTimer(this->LaunchCheckTimer, OnCheckTimerDelegate, CheckTimerPeriod, true);
	
	return true;
}

void FCharonEditorProcessRunner::OnCheckTimer()
{
	if (this->LaunchTimeoutTime < FDateTime::Now())
	{
		UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Polling HTTP server process for response at [GET] '%s' has timed out."), *StartUrl);
		this->RaiseLaunched(EGameDataEditorLaunchStatus::Timeout);
		return;
	}
	
	if (!this->Process->Update())
	{
		UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("HTTP server process has exited with code %d during polling."), this->Process->GetReturnCode());
		this->RaiseLaunched(EGameDataEditorLaunchStatus::Failed);
		return;
	}
		
	if (LaunchCheckRequest != nullptr)
	{
		switch (this->LaunchCheckRequest->GetStatus())
		{
			case EHttpRequestStatus::Type::Succeeded:
				if (const auto ResponsePtr = this->LaunchCheckRequest->GetResponse(); ResponsePtr != nullptr)
				{
					UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Polling HTTP server process for response at [GET] '%s' has succeed. Status code: '%d'."), *StartUrl, ResponsePtr->GetResponseCode());
				}
				this->RaiseLaunched(EGameDataEditorLaunchStatus::Succeed);
				return;
			case EHttpRequestStatus::Type::Failed_ConnectionError:
			case EHttpRequestStatus::Type::Failed:
				UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Polling HTTP server process for response at [GET] '%s' has failed."), *StartUrl);
				this->LaunchCheckRequest = nullptr;
				break;
			case EHttpRequestStatus::Type::NotStarted:
			case EHttpRequestStatus::Type::Processing:
			default:
				break;
		}
	}

	if (LaunchCheckRequest == nullptr)
	{
		FHttpModule& httpModule = FHttpModule::Get();
		this->LaunchCheckRequest = httpModule.CreateRequest();
		this->LaunchCheckRequest->SetVerb(TEXT("GET"));
		this->LaunchCheckRequest->SetURL(this->StartUrl);
		this->LaunchCheckRequest->SetTimeout(CheckTimerPeriod);
		this->LaunchCheckRequest->ProcessRequest();
		
		UE_LOG(LogFCharonEditorProcessRunner, Log, TEXT("Polling HTTP server process for response at [GET] '%s'."), *StartUrl);
	}
}

void FCharonEditorProcessRunner::RaiseLaunched(const EGameDataEditorLaunchStatus Status)
{
	GEditor->GetTimerManager()->ClearTimer(this->LaunchCheckTimer);
	this->LaunchCheckRequest = nullptr;
	
	auto _ = this->Launched.ExecuteIfBound(Status);
}

void FCharonEditorProcessRunner::Stop()
{
	this->Process->Stop();
	this->RaiseLaunched(EGameDataEditorLaunchStatus::Cancelled);
}
