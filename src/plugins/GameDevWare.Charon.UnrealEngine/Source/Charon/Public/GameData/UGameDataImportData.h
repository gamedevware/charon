#pragma once
#include "EditorFramework/AssetImportData.h"

#include "UGameDataImportData.generated.h"

UCLASS(EditInlineNew)
class CHARON_API UGameDataImportData : public UAssetImportData
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	/*
	 * Address of game data server to which this asset is connected. 
	 */
	UPROPERTY()
	FString ServerAddress;
	/*
	 * Id of project to which this asset is connected. 
	 */
	UPROPERTY(BlueprintReadOnly)
	FString ProjectId;
	/*
	 * Id of branch on project to which this asset is connected. 
	 */
	UPROPERTY(BlueprintReadOnly)
	FString BranchId;
	/*
	 * Name of project to which this asset is connected. Used for UI. 
	 */
	UPROPERTY(BlueprintReadOnly)
	FString ProjectName;
	/*
	 * Name of branch on project to which this asset is connected. Used for UI.
	 */
	UPROPERTY(BlueprintReadOnly)
	FString BranchName;
	
	/*
	 * Is this game data asset is connected to remote project. 
	 */
	bool IsConnected() const { return !ServerAddress.IsEmpty() && !ProjectId.IsEmpty() && !BranchId.IsEmpty(); }

	/*
	 * Disconnect this data from remote project.
	 */
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