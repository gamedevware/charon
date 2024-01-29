#pragma once
#include "Misc/MonitoredProcess.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFCharonCliCommandRunner, Log, All);

class CHARONEDITOR_API FCharonCliCommandRunner final : public TSharedFromThis<FCharonCliCommandRunner>, public FMonitoredProcess
{
private:
	inline static bool bScriptsCopied = false;
	
	TArray<FString> FileCleanupList;
	FString RunScriptPath;
public:
	TMap<FString, FString> EnvironmentVariables;

	explicit FCharonCliCommandRunner(FString InParameters);
	virtual ~FCharonCliCommandRunner() override;
	
	virtual bool Launch() override;
	
	void SetApiKey(const FString& InApiKey);
	void AttachTemporaryFile(const FString& InFilePath);

	static FString GetOrCreateCharonIntermediateDirectory();
};
