#pragma once

#include "GameData/UGameDataBase.h"
#include "Styling/SlateStyle.h"
#include "GameData/ICharonTask.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCharonGameDataAction, UGameDataBase* /* GameDataAsset */, TArray<TSharedRef<ICharonTask>>&  /* Tasks */);

class CHARONEDITOR_API ICharonEditorModule : public IModuleInterface
{
public:
	virtual TSharedPtr<FSlateStyleSet> GetStyleSet() { return nullptr; }

	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorMenuExtensibilityManager() = 0;
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorToolBarExtensibilityManager() = 0;

	virtual FOnCharonGameDataAction& OnGameDataPreSourceCodeGeneration() = 0;
	virtual FOnCharonGameDataAction& OnGameDataPostSourceCodeGeneration() = 0;

	virtual FOnCharonGameDataAction& OnGameDataPreSynchronization() = 0;
	virtual FOnCharonGameDataAction& OnGameDataPostSynchronization() = 0;
	
	static ICharonEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ICharonEditorModule>("CharonEditor");
	}
};
