#pragma once
	 
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FGameDataAssetTypeActions : public FAssetTypeActions_Base
{
public:
	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override;
	
	virtual bool CanLocalize() const override { return false; }
	virtual bool IsImportedAsset() const override { return true; }
};
