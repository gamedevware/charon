#pragma once

#include "FGameDataAssetTypeActions.h"

#include "GameData/ICharonEditorModule.h"
#include "GameDataEditor/FGameDataEditorToolkit.h"
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

const FSlateBrush* FGameDataAssetTypeActions::GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const
{
	const auto StyleSet = ICharonEditorModule::Get().GetStyleSet();
	const auto PluginIcon = FSlateIcon(StyleSet->GetStyleSetName(), "Icon128");
	return PluginIcon.GetIcon();
}
