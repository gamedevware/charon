#pragma once

#include "GameData/UGameDataBase.h"
#include "Styling/SlateStyle.h"
#include "GameData/ICharonTask.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCharonGameDataAction, UGameDataBase* /* GameDataAsset */, TArray<TSharedRef<ICharonTask>>& /* Tasks */);

/**
 * @class ICharonEditorModule
 * @brief Interface for the Charon Editor module, which provides extension points for the plugin.
 *
 * This interface exposes methods for accessing and extending various aspects of the Charon Editor, 
 * including UI elements like menus and toolbars, and hooks into the game data source code generation 
 * and synchronization processes.
 */
class CHARONEDITOR_API ICharonEditorModule : public IModuleInterface
{
public:
	/**
	 * Gets the style set for the module, which includes used icons.
	 *
	 * @return A shared pointer to the FSlateStyleSet of the module.
	 */
	virtual TSharedPtr<FSlateStyleSet> GetStyleSet() { return nullptr; }

	/**
	 * Provides a point of registration for extensions to the game data editor's menu.
	 *
	 * @return A shared pointer to an FExtensibilityManager for the game data editor menu.
	 */
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorMenuExtensibilityManager() = 0;
	/**
	 * Provides a point of registration for extensions to the toolbar of the game data editor's window.
	 *
	 * @return A shared pointer to an FExtensibilityManager for the game data editor toolbar.
	 */
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorToolBarExtensibilityManager() = 0;

	/**
	 * Access point for extensions of the source code generation process for game data, 
	 * allowing for pre-generation custom tasks.
	 *
	 * @return A reference to the FOnCharonGameDataAction event for pre-source code generation tasks.
	 */
	virtual FOnCharonGameDataAction& OnGameDataPreSourceCodeGeneration() = 0;
	/**
	 * Access point for extensions of the source code generation process for game data, 
	 * allowing for post-generation custom tasks.
	 *
	 * @return A reference to the FOnCharonGameDataAction event for post-source code generation tasks.
	 */
	virtual FOnCharonGameDataAction& OnGameDataPostSourceCodeGeneration() = 0;

	/**
	 * Access point for extensions of the Reimport process for game data, allowing for pre-synchronization custom tasks.
	 *
	 * @return A reference to the FOnCharonGameDataAction event for pre-synchronization tasks.
	 */
	virtual FOnCharonGameDataAction& OnGameDataPreSynchronization() = 0;
	/**
	 * Access point for extensions of the Reimport process for game data, allowing for post-synchronization custom tasks.
	 *
	 * @return A reference to the FOnCharonGameDataAction event for post-synchronization tasks.
	 */
	virtual FOnCharonGameDataAction& OnGameDataPostSynchronization() = 0;

	/**
	 * Retrieves the current instance of ICharonEditorModule from the FModuleManager.
	 *
	 * @return A reference to the current instance of ICharonEditorModule.
	 */
	static ICharonEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ICharonEditorModule>("CharonEditor");
	}
};
