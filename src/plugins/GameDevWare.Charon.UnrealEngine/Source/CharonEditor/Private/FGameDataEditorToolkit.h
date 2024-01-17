#pragma once

#include "CoreMinimal.h"
#include "SWebBrowser.h"
#include "FGameDataEditorProcessRunner.h"
#include "TCharonCliCommand.h"
#include "GameData/UGameDataBase.h"
#include "Toolkits/AssetEditorToolkit.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFGameDataEditorToolkit, Log, All);

class FGameDataEditorToolkit : public FAssetEditorToolkit
{
private:
	UGameDataBase* GameData = nullptr;
	TSharedPtr<SWebBrowser> Browser;
	TSharedPtr<TCharonCliCommand<>> CurrentRunningCommand;
	TSharedPtr<FGameDataEditorProcessRunner> EditorProcess;

	void LaunchCharonProcess();
	void BindCommands();
	void ExtendToolbar();
	void ExtendMenu();

protected:
	void GenerateSourceCode_Execute();
	bool CanConnect();
	bool CanGenerateSourceCode() const;
	void Connect_Execute();
	void Disconnect_Execute();
	bool CanDisconnect();
	
	void BroadcastCommandRunning(const TSharedRef<IGameDataEditorTask>& Command, FName IconName,
	                             FText CommandPendingText, FText CommandSucceedText, FText CommandFailedText,
	                             bool bCanCancel);

public:
	void InitEditor(const TArray<UObject*>& InObjects);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	// FAssetEditorToolkit
	virtual FText GetToolkitName() const override { return FText::FromString(GameData->GetClass()->GetName()); }
	virtual FName GetToolkitFName() const override { return "GameDataEditor"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Game Data Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "Game Data "; }
	virtual FString GetDocumentationLink() const override { return "https://gamedevware.github.io/charon/"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
};
