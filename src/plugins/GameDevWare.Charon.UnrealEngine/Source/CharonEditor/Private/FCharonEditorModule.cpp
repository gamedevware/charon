// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameData/FCharonEditorModule.h"

#include "GameDataAssetActions/FGameDataAssetTypeActions.h"
#include "GameData/FGameDataDocumentReference.h"
#include "DocumentReferenceExtensions/FGameDataDocumentReferenceCustomization.h"
#include "GameDataEditor/FGameDataEditorCommands.h"
#include "PropertyEditorModule.h"
#include "GameDataAssetActions/FGameDataReimportHandler.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FCharonEditorModule"

void FCharonEditorModule::StartupModule()
{
	GameDataEditorMenuExtensibilityManager = MakeShared<FExtensibilityManager>();
	GameDataEditorToolBarExtensibilityManager = MakeShared<FExtensibilityManager>();
	
	// Register game data asset editor commands
	FGameDataEditorCommands::Register();
	
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FGameDataDocumentReference::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGameDataDocumentReferenceCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();

	// register re-import handler
	GameDataReimportHandler = FGameDataReimportHandler();
	FReimportManager::Instance()->RegisterHandler(GameDataReimportHandler);
	
	const FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
	GameDataAssetTypeActions = MakeShared<FGameDataAssetTypeActions>();
	AssetToolsModule.Get().RegisterAssetTypeActions(GameDataAssetTypeActions.ToSharedRef());
}

void FCharonEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(FGameDataDocumentReference::StaticStruct()->GetFName());
		PropertyModule.NotifyCustomizationModuleChanged();
	}

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		const FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
		AssetToolsModule.Get().UnregisterAssetTypeActions(GameDataAssetTypeActions.ToSharedRef());
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCharonEditorModule, CharonEditor)