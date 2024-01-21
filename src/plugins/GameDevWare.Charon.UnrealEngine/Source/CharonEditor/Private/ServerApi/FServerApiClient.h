#pragma once

#include "FProjectsResponse.h"
#include "Interfaces/IHttpRequest.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFServerApiClient, Log, All);

DECLARE_DELEGATE_OneParam(OnGetMyProjectsResponse, FProjectsResponse)

class FServerApiClient
{
	FString BaseAddress;
	TMap<FString, FString> RequestHeaders;
	TArray<TSharedRef<IHttpRequest>> PendingRequests;
	
public:
	inline static FString DEFAULT_SERVER_ADDRESS = "https://charon.live";
	
	FServerApiClient(const FString& BaseAddress);

	FString GetApiKeysUrl() const;
	FString GetGameDataUrl(FString ProjectId, FString BranchId) const;
	
	void UseApiKey(const FString& ApiKey);

	bool GetMyProjects(OnGetMyProjectsResponse OnResponse);
private:
	template<typename ObjectType>
	static bool TryReadJson(const FString& JsonText, ObjectType& OutObject);
};
