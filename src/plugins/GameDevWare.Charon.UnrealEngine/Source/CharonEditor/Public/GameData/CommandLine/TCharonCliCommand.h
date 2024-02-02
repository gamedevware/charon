#pragma once

#include "FValidationReport.h"
#include "CommandLine/FImportReport.h"
#include "../ICharonTask.h"
#include "Misc/MonitoredProcess.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTCharonCliCommand, Log, All);

/**
 * @class TCharonCliCommand
 * @brief Represents a prepared command from FCharonCli, with customizable result type.
 *
 * This class encapsulates a command that can be executed via FCharonCli. It is templated to allow
 * specifying the type of result the command should produce. By default, it uses an int32 to represent
 * the process exit code if no specific result type is provided.
 *
 * @tparam InResultType The type of the result produced by the command. Defaults to int32.
 */
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
	ENamedThreads::Type EventThread;
	std::atomic<ERunStatus> RunStatus;

	FSimpleMulticastDelegate TaskStart;
	FSimpleMulticastDelegate TaskSucceed;
	FSimpleMulticastDelegate TaskFailed;
	FOnCommandSucceed CommandSucceed;
	FOnCommandFailed CommandFailed;

public:
	/**
	 * Event that fires when the task is started.
	 *
	 * @return A reference to the FSimpleMulticastDelegate that can be used to bind event handlers for task start.
	 */
	virtual FSimpleMulticastDelegate& OnStart() override { return TaskStart; }
	/**
	 * Event that fires when the task succeeds.
	 *
	 * @return A reference to the FSimpleMulticastDelegate that can be used to bind event handlers for task success.
	 */
	virtual FSimpleMulticastDelegate& OnSucceed() override { return TaskSucceed; }
	/**
	 * Event that fires when the task fails.
	 *
	 * @return A reference to the FSimpleMulticastDelegate that can be used to bind event handlers for task failure.
	 */
	virtual FSimpleMulticastDelegate& OnFailed() override { return TaskFailed; }
	/**
	 * Event that fires when the command succeeds.
	 *
	 * @return FOnCommandSucceed event, providing the result of the command of type InResultType.
	 */
	FOnCommandSucceed& OnCommandSucceed() { return CommandSucceed; }
	/**
	 * Event that fires when the command fails.
	 *
	 * @return FOnCommandFailed event, providing the exit code and process's output.
	 */
	FOnCommandFailed& OnCommandFailed() { return CommandFailed; }
	/**
	 * Retrieves the display name of the task, primarily used for logging purposes.
     *
     * @return The display name of the task as FText.
     */
	virtual const FText& GetDisplayName() override { return DisplayName; }

	/**
	 * Constructs a TCharonCliCommand object.
	 *
	 * @param Process A shared reference to FMonitoredProcess, typically an instance of FCharonCliCommandRunner.
	 * @param DisplayName The display name of the command for logging purposes.
	 * @param OutputFilePath Optional file path where Charon.exe process will output results to be read into InResultType.
	 */
	TCharonCliCommand(const TSharedRef<FMonitoredProcess>& Process, const FText& DisplayName, const FString& OutputFilePath = FString());

	/**
	 * Starts the command execution.
	 * If it returns false, then no events will be fired due to initial misconfiguration of the command, or if the command is already running or finished.
	 * This method should be called only once.
	 * @param EventDispatchThread The thread on which the events should be dispatched. Defaults to ENamedThreads::AnyThread.
	 * @return true if the task was started successfully, false otherwise.
	 */
	virtual bool Start(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) override;
	/**
	 * Stops the command execution by aborting (SIGTERM) process. 
	 */
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
