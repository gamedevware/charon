#pragma once
#include "Misc/MonitoredProcess.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFGameDataToolCommandRunner, Log, All);

class CHARONEDITOR_API FGameDataToolCommandRunner : public TSharedFromThis<FGameDataToolCommandRunner>, public FMonitoredProcess
{
private:
	inline static bool bContentCopied = false;
	
	TArray<FString> FileCleanupList;
	FString RunScriptPath;
public:
	TMap<FString, FString> EnvironmentVariables;
	
	FGameDataToolCommandRunner(FString InParameters);
	virtual ~FGameDataToolCommandRunner() override;
	
	virtual bool Launch() override;
	
	void SetApiKey(const FString& InApiKey);
	void AttachTemporaryFile(const FString& InFilePath);

	static FString GetOrCreateCharonIntermediateDirectory();
};
