#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "ServerApi/FServerApiClient.h"
#include "Widgets/Workflow/SWizard.h"

struct FProject;
struct FBranch;

DECLARE_LOG_CATEGORY_EXTERN(LogSSetApiKeyDialog, Log, All);

DECLARE_DELEGATE_OneParam(SSetApiKeyDialogFinished, FString)

class SSetApiKeyDialog : public SWindow
{
public:
	enum InitialGameDataSyncDirection
	{
		None = 0,
		Upload = 1,
		Download = -1,
	};
	
	SLATE_BEGIN_ARGS(SSetApiKeyDialog) {}
		SLATE_ARGUMENT(FText, Title)
		SLATE_ARGUMENT(FString, ProjectName)
		SLATE_ARGUMENT(FString, ProjectId)
		SLATE_ARGUMENT(FString, ServerAddress)
		SLATE_EVENT(SSetApiKeyDialogFinished, OnFinished)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void ShowModal();
	void Show();
private:
	TSharedPtr<SWizard> MainWizard;
	TSharedPtr<FServerApiClient> ServerApiClient;
	SSetApiKeyDialogFinished OnFinished;
	
	FText ApiKeyError;
	FString ApiKey;
	FString ServerAddress;
	FString ProjectId;
	FString ProjectName;
	bool IsApiKeyMatchingProjectId = false;

	EVisibility GetApiKeyErrorLabelVisibility() const;
	bool CanFinish() const;
	FText GetApiKeyErrorLabelText() const;

	void OnApiKeyChanged(const FText& Text);
	
	void OnMyProjectResponse(FProjectsResponse ProjectsResponse);
	
	void GoToProfileApiKey() const;
	void CloseWindow();
	void CancelClicked();
	void FinishClicked();
};
