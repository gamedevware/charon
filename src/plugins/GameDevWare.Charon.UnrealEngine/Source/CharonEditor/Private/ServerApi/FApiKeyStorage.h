#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogFApiKeyStorage, Log, All);

class FApiKeyStorage
{
public:
	static bool IsKeyExists(const FString& ServerAddress, const FString& ProjectId);
	static bool LoadApiKey(const FString& ServerAddress, const FString& ProjectId, FString& OutApiKey);
	static void SaveApiKey(const FString& ServerAddress, const FString& ProjectId, const FString& ApiKey);

private:
	static FString GetOrCreateKeyDirectory();
	static FString GetKeyFileName(const FString& ServerAddress, const FString& ProjectId);
};
