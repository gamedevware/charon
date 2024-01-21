#pragma once
#include "EditorFramework/AssetImportData.h"

#include "UGameDataImportData.generated.h"

UCLASS(EditInlineNew)
class CHARON_API UGameDataImportData : public UAssetImportData
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	FString ServerAddress;
	UPROPERTY(BlueprintReadOnly)
	FString ProjectId;
	UPROPERTY(BlueprintReadOnly)
	FString BranchId;
	UPROPERTY(BlueprintReadOnly)
	FString ProjectName;
	UPROPERTY(BlueprintReadOnly)
	FString BranchName;

	bool IsConnected() const { return !ServerAddress.IsEmpty() && !ProjectId.IsEmpty() && !BranchId.IsEmpty(); }

	UFUNCTION(BlueprintCallable)
	void Disconnect()
	{
		ServerAddress.Empty();
		ProjectId.Empty();
		ProjectName.Empty();
		BranchId.Empty();
		BranchName.Empty();
	}
#endif
};