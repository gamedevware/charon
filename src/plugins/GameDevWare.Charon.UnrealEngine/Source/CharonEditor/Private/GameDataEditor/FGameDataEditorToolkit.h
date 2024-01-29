#pragma once

#include "CoreMinimal.h"
#include "FConnectGameDataParameters.h"
#include "SWebBrowser.h"
#include "GameData/CommandLine/FCharonEditorProcessRunner.h"
#include "SConnectGameDataDialog.h"
#include "GameData/CommandLine/TCharonCliCommand.h"
#include "..\..\Public\GameData\ICharonTask.h"
#include "GameData/UGameDataBase.h"
#include "Toolkits/AssetEditorToolkit.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFGameDataEditorToolkit, Log, All);

class FGameDataEditorToolkit : public FAssetEditorToolkit
{
private:
	UGameDataBase* GameData = nullptr;
	TSharedPtr<SWebBrowser> Browser;
	TSharedPtr<ICharonTask> CurrentRunningCommand;
	TSharedPtr<FCharonEditorProcessRunner> EditorProcess;
	TSharedPtr<SWindow> PendingDialog;

	void LaunchCharonProcess();
	void OpenCharonWebsite() const;
	void BindCommands();
	void ExtendToolbar();
	void ExtendMenu();

protected:
	void GenerateSourceCode_Execute();
	bool CanConnect() const;
	bool CanGenerateSourceCode() const;
	void Connect_Execute();
	void Sync_Execute();
	void Disconnect_Execute() const;
	bool CanDisconnect() const;
	void SetApiKey_Execute();
	bool CanSetApiKey() const;
	void OnSetApiKeyFinished(FString String) const;
	void OnConnectFinished(FConnectGameDataParameters Parameters);
	void OnGameDataDownloadSucceed(FString String, FString String1);

	static void BroadcastCommandRunning(const TSharedRef<ICharonTask>& Command, FName IconName,
	                                    FText CommandPendingText, FText CommandSucceedText, FText CommandFailedText,
	                                    bool bCanCancel);

	static void BroadcastMissingApiKey(FText ProjectName);

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