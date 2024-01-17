#pragma once

class CHARONEDITOR_API ICharonEditorModule : public IModuleInterface
{
public:
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorMenuExtensibilityManager() { return nullptr; }
	virtual TSharedPtr<FExtensibilityManager> GetGameDataEditorToolBarExtensibilityManager() { return nullptr; }
};
