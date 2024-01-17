#include "FGameDataEditorToolkit.h"

#include "FCharonCli.h"
#include "FGameDataEditorCommands.h"
#include "ICharonEditorModule.h"
#include "SourceCodeNavigation.h"
#include "SWebBrowser.h"
#include "UGameDataFactory.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Math/UnrealMathUtility.h"
#include "Widgets/Notifications/SNotificationList.h"

DEFINE_LOG_CATEGORY(LogFGameDataEditorToolkit);

const FString LoadingHtml = TEXT(
	"<style>.loadingspinner {pointer-events: none;width: 2.5em;height: 2.5em;border: 0.4em solid transparent;border-color: #eee;border-top-color: #3E67EC;border-radius: 50%;animation: loadingspin 1s linear infinite;}@keyframes loadingspin {100% {transform: rotate(360deg) }}body {height: 100vh;margin: 0;padding: 0;display: flex;justify-content: center;align-items: center;}</style><div class=\"loadingspinner\"></div>");
const FString CancelledHtml = TEXT("<h1>Process Start Cancelled</h1><p>Review Unreal Engine logs for details.</p>");
const FString FailedHtml = TEXT("<h1>Process Start Failed</h1><p>Review Unreal Engine logs for details.</p>");

void FGameDataEditorToolkit::InitEditor(const TArray<UObject*>& InObjects)
{
	GameData = Cast<UGameDataBase>(InObjects[0]);

	BindCommands();

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("GameDataEditorLayout")->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.6f)
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->AddTab("GameDataBrowserTab", ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab("GameDataDetailsTab", ETabState::OpenedTab)
			)
		)
	);

	InitAssetEditor(EToolkitMode::Standalone, {}, "GameDataEditor", Layout, true, true, InObjects);

	ExtendToolbar();
	ExtendMenu();

	RegenerateMenusAndToolbars();

	LaunchCharonProcess();
}

void FGameDataEditorToolkit::BindCommands()
{
	const TSharedRef<FUICommandList>& UICommandList = GetToolkitCommands();

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().BrowserBack,
		FExecuteAction::CreateLambda([this] { if (Browser != nullptr) Browser->GoBack(); }),
		FCanExecuteAction::CreateLambda([this] { return Browser != nullptr && Browser->CanGoBack(); }));

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().BrowserForward,
		FExecuteAction::CreateLambda([this] { if (Browser != nullptr) Browser->GoForward(); }),
		FCanExecuteAction::CreateLambda([this] { return Browser != nullptr && Browser->CanGoForward(); }));

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().BrowserReload,
		FExecuteAction::CreateLambda([this] { if (Browser != nullptr) Browser->Reload(); }),
		FCanExecuteAction::CreateLambda([this] { return Browser != nullptr; }));

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().Reimport,
		FExecuteAction::CreateSP(this, &FGameDataEditorToolkit::Reimport_Execute),
		FCanExecuteAction::CreateSP(this, &FGameDataEditorToolkit::CanReimport));

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().GenerateSourceCode,
		FExecuteAction::CreateSP(this, &FGameDataEditorToolkit::GenerateSourceCode_Execute),
		FCanExecuteAction::CreateSP(this, &FGameDataEditorToolkit::CanGenerateSourceCode));

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().Connect,
		FExecuteAction::CreateSP(this, &FGameDataEditorToolkit::Connect_Execute),
		FCanExecuteAction::CreateSP(this, &FGameDataEditorToolkit::CanConnect));

	UICommandList->MapAction(
		FGameDataEditorCommands::Get().Disconnect,
		FExecuteAction::CreateSP(this, &FGameDataEditorToolkit::Disconnect_Execute),
		FCanExecuteAction::CreateSP(this, &FGameDataEditorToolkit::CanDisconnect));
}

void FGameDataEditorToolkit::ExtendToolbar()
{
	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.BeginSection("Browser");
			{
				ToolbarBuilder.AddToolBarButton(FGameDataEditorCommands::Get().BrowserBack,
				                                NAME_None, FText(), TAttribute<FText>(),
				                                FSlateIcon(FAppStyle::GetAppStyleSetName(),
				                                           "GraphBreadcrumb.BrowseBack")
				);
				ToolbarBuilder.AddToolBarButton(FGameDataEditorCommands::Get().BrowserForward,
				                                NAME_None, FText(), TAttribute<FText>(),
				                                FSlateIcon(FAppStyle::GetAppStyleSetName(),
				                                           "GraphBreadcrumb.BrowseForward")
				);
				ToolbarBuilder.AddToolBarButton(
					FGameDataEditorCommands::Get().BrowserReload,
					NAME_None, FText(), TAttribute<FText>(),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Refresh")
				);
				ToolbarBuilder.AddSeparator();

				ToolbarBuilder.AddToolBarButton(FGameDataEditorCommands::Get().Reimport,
				                                NAME_None, FText(), TAttribute<FText>(),
				                                FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Import"));

				ToolbarBuilder.AddToolBarButton(FGameDataEditorCommands::Get().GenerateSourceCode,
				                                NAME_None, FText(), TAttribute<FText>(),
				                                FSlateIcon(FAppStyle::GetAppStyleSetName(),
				                                           "MainFrame.AddCodeToProject"));
			}
			ToolbarBuilder.EndSection();
		}
	};

	const TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar)
	);

	AddToolbarExtender(ToolbarExtender);

	ICharonEditorModule* CharonEditorModule = &FModuleManager::LoadModuleChecked<ICharonEditorModule>(
		"CharonEditor");
	AddToolbarExtender(CharonEditorModule->GetGameDataEditorToolBarExtensibilityManager()->GetAllExtenders());
}

void FGameDataEditorToolkit::ExtendMenu()
{
	ICharonEditorModule* CharonEditorModule = &FModuleManager::LoadModuleChecked<ICharonEditorModule>(
		"CharonEditor");
	AddMenuExtender(CharonEditorModule->GetGameDataEditorMenuExtensibilityManager()->GetAllExtenders());
}

void FGameDataEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Game Data Editor"));

	InTabManager->RegisterTabSpawner("GameDataBrowserTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	            {
		            return SNew(SDockTab)
		            [
			            SAssignNew(Browser, SWebBrowser)
						.ShowErrorMessage(false)
						.ShowControls(false)
						.SupportsTransparency(false)
						.BackgroundColor(FColor::White)
						.InitialURL(TEXT("about:blank"))
		            ];
	            }))
	            .SetDisplayName(INVTEXT("Game Data"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObjects(TArray<UObject*>{GameData});
	InTabManager->RegisterTabSpawner("GameDataDetailsTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	            {
		            return SNew(SDockTab)
		            [
			            DetailsView
		            ];
	            }))
	            .SetDisplayName(INVTEXT("Details"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FGameDataEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner("GameDataBrowserTab");
	InTabManager->UnregisterTabSpawner("GameDataDetailsTab");
}

void FGameDataEditorToolkit::LaunchCharonProcess()
{
	FString GameDataFilePath = GameData->AssetImportData != nullptr
		                           ? GameData->AssetImportData->GetFirstFilename()
		                           : TEXT("");
	if (GameDataFilePath.IsEmpty() || !FPaths::FileExists(GameDataFilePath))
	{
		if (GameDataFilePath.IsEmpty())
		{
			UE_LOG(LogFGameDataEditorToolkit, Error, TEXT("There is source file is set for asset '%s'."),
			       *GameData->GetPathName());
		}
		else
		{
			UE_LOG(LogFGameDataEditorToolkit, Error, TEXT("Unable to find source file '%s' for asset '%s'."),
			       *GameDataFilePath, *GameData->GetPathName());
		}
		Browser->LoadString(FailedHtml, TEXT("about:blank"));
		return;
	}

	const int32 Port = FMath::RandRange(10001, 65500);
	EditorProcess = MakeShared<FGameDataEditorProcessRunner>(GameDataFilePath, Port, FTimespan::FromSeconds(30));
	EditorProcess->OnLaunched().BindLambda([this](EGameDataEditorLaunchStatus Status)
	{
		switch (Status)
		{
		case EGameDataEditorLaunchStatus::Succeed: Browser->LoadURL(EditorProcess->StartUrl);
			break;
		case EGameDataEditorLaunchStatus::Cancelled: Browser->LoadString(CancelledHtml, EditorProcess->StartUrl);
			break;
		case EGameDataEditorLaunchStatus::MissingExecutable:
		case EGameDataEditorLaunchStatus::MissingRuntime:
		case EGameDataEditorLaunchStatus::Timeout:
		case EGameDataEditorLaunchStatus::Failed: Browser->LoadString(FailedHtml, EditorProcess->StartUrl);
			break;
		}
	});

	Browser->LoadString(LoadingHtml, EditorProcess->StartUrl);
	EditorProcess->Launch();
}

bool FGameDataEditorToolkit::CanGenerateSourceCode() const
{
	return this->CanReimport(); // if it has source file, then we can generate source code from it
}

void FGameDataEditorToolkit::GenerateSourceCode_Execute()
{
	if (!CanReimport(GameData))
	{
		UE_LOG(LogFGameDataEditorToolkit, Warning,
		       TEXT(
			       "Unable to generate C++ Source code for game data file '%s' because it doesn't contains path to a source file."
		       ), *GameData->GetName());
		return;
	}
	FString GameDataClassPath;
	if (!FSourceCodeNavigation::FindClassHeaderPath(GameData->GetClass(), GameDataClassPath))
	{
		UE_LOG(LogFGameDataEditorToolkit, Warning,
		       TEXT(
			       "Unable to generate C++ Source code for game data file '%s' because 'FSourceCodeNavigation' can't find source code location."
		       ), *GameData->GetName());
		return;
	}

	const FString SourceCodePath = FPaths::ConvertRelativePathToFull(GameDataClassPath / "../../");
	const FString GameDataPath = GameData->AssetImportData->GetFirstFilename();
	const FString ApiKey;
	const FString GameDataClassName = GameData->GetClass()->GetPrefixCPP() + GameData->GetClass()->GetName();
	const FString DefineConstants;
	const auto Command = FCharonCli::GenerateUnrealEngineSourceCode(GameDataPath, ApiKey, SourceCodePath, "UDocument",
	                                                                GameDataClassName, DefineConstants);

	BroadcastCommandRunning(
		Command,
		TEXT("MainFrame.AddCodeToProject"),
		INVTEXT("Generating C++ source code..."),
		INVTEXT("C++ source code has been generated."),
		INVTEXT("C++ source code generation failed."),
		/* can cancel */ true
	);

	Command->Run(/* event dispatch thread */ ENamedThreads::GameThread);

	CurrentRunningCommand = Command; // prevent destruction of this command
}

bool FGameDataEditorToolkit::CanConnect()
{
	return !CanDisconnect();
}

void FGameDataEditorToolkit::Connect_Execute()
{
}

bool FGameDataEditorToolkit::CanDisconnect()
{
	return false;
}

void FGameDataEditorToolkit::Disconnect_Execute()
{
}

void FGameDataEditorToolkit::BroadcastCommandRunning(
	const TSharedRef<IGameDataEditorTask>& Command,
	FName IconName,
	FText CommandPendingText,
	FText CommandSucceedText,
	FText CommandFailedText,
	bool bCanCancel)
{
	FNotificationInfo Info(CommandPendingText);
	Info.Image = FSlateIcon(FAppStyle::GetAppStyleSetName(), IconName).GetIcon();
	if (bCanCancel)
	{
		FSimpleDelegate CancelCommandAction;
		const auto WeakCommand = TWeakPtr<IGameDataEditorTask>(Command);
		CancelCommandAction.BindLambda([WeakCommand]
		{
			const auto CommandPtr = WeakCommand.Pin();
			if (CommandPtr.IsValid()) CommandPtr->Stop();
		});
		Info.ButtonDetails.Add(FNotificationButtonInfo(
				INVTEXT("Cancel"),
				INVTEXT(""),
				CancelCommandAction)
		);
	}
	Info.bFireAndForget = false;
	Info.bUseLargeFont = false;
	Info.bUseThrobber = false;
	Info.bUseSuccessFailIcons = false;

	const auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);
	if (!NotificationItem.IsValid()) { return; }

	NotificationItem->SetCompletionState(SNotificationItem::CS_Pending);
	Command->OnSucceed().AddLambda([NotificationItem, CommandSucceedText]
	{
		NotificationItem->Pulse(FLinearColor::Green);
		NotificationItem->SetText(CommandSucceedText);
		NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
		NotificationItem->Fadeout();
	});
	Command->OnFailed().AddLambda([NotificationItem, CommandFailedText]
	{
		NotificationItem->Pulse(FLinearColor::Red);
		NotificationItem->SetText(CommandFailedText);
		NotificationItem->SetCompletionState(SNotificationItem::CS_Fail);
		NotificationItem->Fadeout();
	});
}
