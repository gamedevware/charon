#pragma once

#include "FImportReport.h"
#include "FValidationReport.h"
#include "../IGameDataEditorTask.h"
#include "Misc/MonitoredProcess.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTCharonCliCommand, Log, All);

template<typename InResultType = int32>
class CHARONEDITOR_API TCharonCliCommand : public TSharedFromThis<TCharonCliCommand<InResultType>>, public IGameDataEditorTask
{
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommandSucceed, InResultType)
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommandFailed, int32, FString)
private:
	TSharedRef<FMonitoredProcess> Process;
	FString OutputFilePath;
	ENamedThreads::Type DispatchThread;
	FSimpleMulticastDelegate TaskSucceed;
	FSimpleMulticastDelegate TaskFailed;
	FOnCommandSucceed CommandSucceed;
	FOnCommandFailed CommandFailed;
	
	void OnProcessCompleted(int32 ExitCode) const;
	void OnProcessCancelled() const;
	void OnProcessOutput(FString OutputChunk);

	static bool TryReadResult(const FString& Output, int32 ExitCode, TSharedPtr<FJsonObject>& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, int32& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, FString& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, FValidationReport& OutResult);
	static bool TryReadResult(const FString& Output, int32 ExitCode, FImportReport& OutResult);

public:
	virtual FSimpleMulticastDelegate& OnSucceed() override { return TaskSucceed; }
	virtual FSimpleMulticastDelegate& OnFailed() override { return TaskFailed; }
	FOnCommandSucceed& OnCommandSucceed() { return CommandSucceed; }
	FOnCommandFailed& OnCommandFailed() { return CommandFailed; }
	
	TCharonCliCommand(const TSharedRef<FMonitoredProcess>& Process, const FString& OutputFilePath = FString());
	
	virtual void Run(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) override;
	virtual void Stop() const override;
};
