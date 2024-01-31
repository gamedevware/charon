// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameDataAssetActions/FGameDataAssetTypeActions.h"
#include "GameDataAssetActions/FGameDataReimportHandler.h"
#include "ICharonEditorModule.h"
#include "Modules/ModuleManager.h"

/*
 * Charon-related UE editor extensions. 
 */
class CHARONEDITOR_API FCharonEditorModule final : public ICharonEditorModule
{
private:
	TSharedPtr<FExtensibilityManager> EditorMenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> EditorToolBarExtensibilityManager;
	TSharedPtr<FGameDataAssetTypeActions> GameDataAssetTypeActions;
	FOnCharonGameDataAction PreSourceCodeGeneration;
	FOnCharonGameDataAction PostSourceCodeGeneration;
	FOnCharonGameDataAction PreSynchronization;
	FOnCharonGameDataAction PostSynchronization;
	TSharedPtr<FSlateStyleSet> StyleSet;
	FGameDataReimportHandler GameDataReimportHandler;
	
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorMenuExtensibilityManager() override { return EditorMenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorToolBarExtensibilityManager() override { return EditorToolBarExtensibilityManager; }

	virtual FOnCharonGameDataAction& OnGameDataPreSourceCodeGeneration() override { return PreSourceCodeGeneration; }
	virtual FOnCharonGameDataAction& OnGameDataPostSourceCodeGeneration() override { return PostSourceCodeGeneration; }

	virtual FOnCharonGameDataAction& OnGameDataPreSynchronization() override { return PreSynchronization; }
	virtual FOnCharonGameDataAction& OnGameDataPostSynchronization() override { return PostSynchronization; }
	
	virtual TSharedPtr<FSlateStyleSet> GetStyleSet() override { return StyleSet; }
};
