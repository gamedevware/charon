#pragma once

#include "CoreMinimal.h"
#include "FConnectGameDataParameters.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "ServerApi/FServerApiClient.h"
#include "Widgets/Workflow/SWizard.h"

struct FProject;
struct FBranch;

DECLARE_LOG_CATEGORY_EXTERN(LogSConnectGameDataDialog, Log, All);

DECLARE_DELEGATE_OneParam(SConnectGameDataDialogFinished, FConnectGameDataParameters)

class SConnectGameDataDialog : public SWindow
{
public:
	enum InitialGameDataSyncDirection
	{
		None = 0,
		Upload = 1,
		Download = -1,
	};
	
	SLATE_BEGIN_ARGS(SConnectGameDataDialog) {}
		/** Provides title for SCustomDialog. */
		SLATE_ARGUMENT(FText, Title)
		SLATE_ARGUMENT(FString, LocalGameDataFile)
		SLATE_EVENT(SConnectGameDataDialogFinished, OnFinished)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void ShowModal();
	void Show();
private:
	TSharedPtr<SWizard> MainWizard;
	TSharedPtr<SComboBox<TSharedRef<FProject>>> ProjectBox;
	TSharedPtr<SComboBox<TSharedRef<FBranch>>> BranchBox;
	TSharedPtr<FServerApiClient> ServerApiClient;
	SConnectGameDataDialogFinished OnFinished;
	
	FString LocalGameDataFile;
	int32 LocalGameDataFileSize = 0;
	FText ApiKeyError;
	FText DataEraseMessage;
	FString ApiKey;
	FString ServerAddress;
	TArray<TSharedRef<FProject>> Projects;
	TArray<TSharedRef<FBranch>> Branches;
	int32 SelectedProjectIndex = -1;
	int32 SelectedBranchIndex = -1;
	InitialGameDataSyncDirection SyncDirection = None;

	EVisibility GetApiKeyErrorLabelVisibility() const;
	EVisibility GetDataEraseLabelVisibility() const;
	bool CanShowProjectsAndBranches() const;
	bool CanShowProjectUploadDownload() const;
	bool CanFinish() const;
	FText GetApiKeyErrorLabelText() const;
	FText GetDataEraseLabelText() const;
	FText GetCurrentSelectedProjectName() const;
	FText GetCurrentSelectedBranchName() const;
	FSlateColor GetUploadDownloadSelectionColor(InitialGameDataSyncDirection Direction) const;
	FText GetFormattedDataSourceSize(InitialGameDataSyncDirection InitialGameDataSyncDirection) const;

	void OnApiKeyChanged(const FText& Text);
	void OnMyProjectResponse(FProjectsResponse ProjectsResponse);
	void OnBranchSelectionChanged(TSharedPtr<FBranch> Branch, ESelectInfo::Type Arg);
	void OnProjectSelectionChanged(TSharedPtr<FProject> Project, ESelectInfo::Type Arg);
	FReply GetUploadDownloadDirectionSelected(InitialGameDataSyncDirection Direction);

	void GoToProfileApiKey() const;
	void CloseWindow();
	void CancelClicked();
	void FinishClicked();
};
