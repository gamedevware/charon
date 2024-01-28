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
class CHARONEDITOR_API FCharonEditorModule : public ICharonEditorModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorMenuExtensibilityManager() override { return GameDataEditorMenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorToolBarExtensibilityManager() override { return GameDataEditorToolBarExtensibilityManager; }
	
private:
	TSharedPtr<FExtensibilityManager> GameDataEditorMenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> GameDataEditorToolBarExtensibilityManager;
	TSharedPtr<FGameDataAssetTypeActions> GameDataAssetTypeActions;
	FGameDataReimportHandler GameDataReimportHandler;
};
