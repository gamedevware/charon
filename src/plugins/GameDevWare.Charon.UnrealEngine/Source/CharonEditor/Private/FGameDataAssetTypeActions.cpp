#include "FGameDataAssetTypeActions.h"

#include "FGameDataEditorToolkit.h"
#include "GameData/UGameDataBase.h"

UClass* FGameDataAssetTypeActions::GetSupportedClass() const
{
	return UGameDataBase::StaticClass();
}

FText FGameDataAssetTypeActions::GetName() const
{
	return INVTEXT("Game Data");
}

FColor FGameDataAssetTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

uint32 FGameDataAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FGameDataAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	MakeShared<FGameDataEditorToolkit>()->InitEditor(InObjects);
}

void FGameDataAssetTypeActions::GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets,
	TArray<FString>& OutSourceFilePaths) const
{
	for (auto& Asset : TypeAssets)
	{
		const auto GameData = CastChecked<UGameDataBase>(Asset);
		GameData->AssetImportData->ExtractFilenames(OutSourceFilePaths);
	}
}
