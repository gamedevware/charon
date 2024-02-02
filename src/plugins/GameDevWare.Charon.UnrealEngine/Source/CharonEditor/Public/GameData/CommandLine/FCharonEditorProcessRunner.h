#pragma once

#include "EGameDataEditorLaunchStatus.h"
#include "Misc/MonitoredProcess.h"
#include "Interfaces/IHttpRequest.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFCharonEditorProcessRunner, Log, All);

DECLARE_DELEGATE_OneParam(FGameDataEditorProcessRunnerLaunchResult, EGameDataEditorLaunchStatus)
/**
 * @class FCharonEditorProcessRunner
 * @brief Provides a convenient interface for executing Charon.exe in interactive mode.
 *
 * This class is designed to facilitate the launching of Charon.exe for interactive editing
 * of game data. It configures and starts an instance of Charon.exe, making the editing UI
 * available at a specified URL.
 */
class CHARONEDITOR_API FCharonEditorProcessRunner final : public TSharedFromThis<FCharonEditorProcessRunner>
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
	/**
	 * The URL at which the interactive UI will be available after launch.
	 *
	 * This string represents the address where users can access the Charon.exe interactive editing
	 * interface via a web browser. The URL is constructed using the provided data base URL and port.
	 */
	FString StartUrl;

	/**
	  * Constructs an FCharonEditorProcessRunner to launch Charon.exe in interactive edit mode.
	  *
	  * @param InDataBaseUrl The base URL of the game data to be edited.
	  * @param InPort The TCP port on which the UI server will be started.
	  * @param InLaunchTimeout The amount of time to wait for Charon.exe to launch before timing out.
	  */
	FCharonEditorProcessRunner(const FString& InDataBaseUrl, const uint16 InPort, const FTimespan InLaunchTimeout);
	/**
	 * Destructor for FCharonEditorProcessRunner.
	 */
	~FCharonEditorProcessRunner();
	
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
