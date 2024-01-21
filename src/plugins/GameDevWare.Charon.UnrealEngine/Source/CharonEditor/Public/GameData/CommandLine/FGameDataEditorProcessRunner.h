#pragma once

#include "EGameDataEditorLaunchStatus.h"
#include "Misc/MonitoredProcess.h"
#include "Interfaces/IHttpRequest.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFGameDataEditorProcessRunner, Log, All);

DECLARE_DELEGATE_OneParam(FGameDataEditorProcessRunnerLaunchResult, EGameDataEditorLaunchStatus)

class CHARONEDITOR_API FGameDataEditorProcessRunner : public TSharedFromThis<FGameDataEditorProcessRunner>
{
private:
	TSharedPtr<FMonitoredProcess> Process;
	TSharedPtr<IHttpRequest> LaunchCheckRequest;
	FString RunScriptPath;
	FString ExecutableName;
	
	FGameDataEditorProcessRunnerLaunchResult Launched;
	FTimespan LaunchTimeout;
	FDateTime LaunchTimeoutTime;
	FTimerHandle LaunchCheckTimer;

	void OnCheckTimer();
	void RaiseLaunched(EGameDataEditorLaunchStatus Status);
public:
	FString StartUrl;

	FGameDataEditorProcessRunner(const FString& InDataBaseUrl, const uint16 InPort, const FTimespan InLaunchTimeout);
	~FGameDataEditorProcessRunner();
	
	/**
	 * Launches the Charon.exe process with 'SERVER START' command and specified parameters.
	 */
	bool Launch();
	/**
	 * Stops the process. This is called if a process is requested to terminate early.
	 */
	void Stop();

	/**
	 * Returns a delegate that is executed when the process has been canceled.
	 *
	 * @return The delegate.
	 */
	FGameDataEditorProcessRunnerLaunchResult& OnLaunched() { return Launched; }
};
