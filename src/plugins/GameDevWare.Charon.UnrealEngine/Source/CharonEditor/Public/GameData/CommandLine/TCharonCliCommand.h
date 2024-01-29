#pragma once

#include "FImportReport.h"
#include "FValidationReport.h"
#include "../ICharonTask.h"
#include "Misc/MonitoredProcess.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTCharonCliCommand, Log, All);

template<typename InResultType = int32>
class CHARONEDITOR_API TCharonCliCommand final : public TSharedFromThis<TCharonCliCommand<InResultType>>, public ICharonTask
{
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommandSucceed, InResultType)
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommandFailed, int32, FString)
private:
	enum struct ERunStatus
	{
		ReadyToRun,
		Running,
		Stopped,
		Succeed,
		Failed,
	};

	FText DisplayName;
	TSharedRef<FMonitoredProcess> Process;
	FString OutputFilePath;
	ENamedThreads::Type DispatchThread;
	std::atomic<ERunStatus> RunStatus;

	FSimpleMulticastDelegate TaskStart;
	FSimpleMulticastDelegate TaskSucceed;
	FSimpleMulticastDelegate TaskFailed;
	FOnCommandSucceed CommandSucceed;
	FOnCommandFailed CommandFailed;

public:
	virtual FSimpleMulticastDelegate& OnStart() override { return TaskStart; }
	virtual FSimpleMulticastDelegate& OnSucceed() override { return TaskSucceed; }
	virtual FSimpleMulticastDelegate& OnFailed() override { return TaskFailed; }
	FOnCommandSucceed& OnCommandSucceed() { return CommandSucceed; }
	FOnCommandFailed& OnCommandFailed() { return CommandFailed; }
	virtual const FText& GetDisplayName() override { return DisplayName; }
	
	TCharonCliCommand(const TSharedRef<FMonitoredProcess>& Process, const FText& DisplayName, const FString& OutputFilePath = FString());
	
	virtual bool Run(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) override;
	virtual void Stop() override;

private:
	void OnProcessCompleted(int32 ExitCode);
	void OnProcessCancelled();
	void OnProcessOutput(FString Output);

	static bool TryReadResult(const FString& Output, int32 ExitCode, TSharedPtr<FJsonObject>& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, int32& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, FString& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, FValidationReport& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, FImportReport& OutResult);
};
