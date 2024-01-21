#pragma once

#include "SConnectGameDataDialog.h"

#include "MathUtil.h"
#include "Widgets/Input/SHyperlink.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Layout/SGridPanel.h"
#include "SWarningOrErrorBox.h"
#include "ServerApi/FBranch.h"
#include "ServerApi/FProject.h"

DEFINE_LOG_CATEGORY(LogSConnectGameDataDialog);

void SConnectGameDataDialog::Construct(const FArguments& InArgs)
{
	OnFinished = InArgs._OnFinished;
	LocalGameDataFile = InArgs._LocalGameDataFile;
	ServerAddress = FServerApiClient::DEFAULT_SERVER_ADDRESS;
	ServerApiClient = MakeShared<FServerApiClient>(ServerAddress);
	
	if (FPaths::FileExists(LocalGameDataFile))
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		LocalGameDataFileSize = PlatformFile.FileSize(*LocalGameDataFile);
	}
	
	SWindow::Construct(SWindow::FArguments()
		.Title(InArgs._Title)
		.SizingRule(ESizingRule::Autosized)
		.Content()
		[
			SNew(SBorder)
			.Padding(18)
			.BorderImage( FAppStyle::GetBrush("Docking.Tab.ContentAreaBrush") )
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				[
					SAssignNew( MainWizard, SWizard)
					.ShowPageList(false)
					.CanFinish(this, &SConnectGameDataDialog::CanFinish)
					.FinishButtonText(INVTEXT("Connect"))
					.OnCanceled(this, &SConnectGameDataDialog::CancelClicked)
					.OnFinished(this, &SConnectGameDataDialog::FinishClicked)
					.InitialPageIndex(0)

					// Enter API Key
					+SWizard::Page()
					[
						SNew(SVerticalBox)

						// Title
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0)
						[
							SNew(STextBlock)
							.Font(FAppStyle::Get().GetFontStyle("HeadingExtraSmall"))
							.Text( INVTEXT("Enter API Key" ) )
							.TransformPolicy(ETextTransformPolicy::ToUpper)
						]

						+ SVerticalBox::Slot()
						.Padding(0, 10, 0, 10)
						.AutoHeight()
						[
							SNew(SEditableTextBox)
								.HintText(INVTEXT("ZS0wnNyOCAABudl05bU-lZMr..."))
								.OnTextChanged(this, &SConnectGameDataDialog::OnApiKeyChanged)
						]
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)

							+SHorizontalBox::Slot()
							.HAlign(HAlign_Left)
							[
								SNew(SHyperlink)
								.OnNavigate(this, &SConnectGameDataDialog::GoToProfileApiKey)
								.Text(INVTEXT("To generate a new key, go to \"User -> Profile -> API Keys\"."))
							]
						]

						// API KEY Error label
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 5)
						[
							SNew(SWarningOrErrorBox)
							.MessageStyle(EMessageStyle::Error)
							.Visibility(this, &SConnectGameDataDialog::GetApiKeyErrorLabelVisibility)
							.Message(this, &SConnectGameDataDialog::GetApiKeyErrorLabelText)
						]
					]

					// Select Project and Branch
					+SWizard::Page()
					.CanShow(this, &SConnectGameDataDialog::CanShowProjectsAndBranches)
					[
						SNew(SVerticalBox)

						// Title
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0)
						[
							SNew(STextBlock)
							.Font(FAppStyle::Get().GetFontStyle("HeadingExtraSmall"))
							.Text( INVTEXT("Choose Project" ) )
							.TransformPolicy(ETextTransformPolicy::ToUpper)
						]

						+ SVerticalBox::Slot()
						.Padding(0, 10, 0, 10)
						.AutoHeight()
						[
							SNew(SGridPanel)
							.FillColumn(1, 1.0f)
							
							+ SGridPanel::Slot(0, 0)
							.VAlign(VAlign_Center)
							.Padding(0, 0, 12, 0)
							[
								SNew(STextBlock).Text(INVTEXT("Project"))
							]

							+SGridPanel::Slot(1,0)
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Left)
							.Padding(2.0f)
							[
								SAssignNew(ProjectBox, SComboBox<TSharedRef<FProject>>)
									.OptionsSource(&Projects)
									.Content()
									[
										SNew(STextBlock).Text(this, &SConnectGameDataDialog::GetCurrentSelectedProjectName)
									]
									.OnSelectionChanged(this, &SConnectGameDataDialog::OnProjectSelectionChanged)
									.OnGenerateWidget_Lambda([](TSharedRef<FProject> Project) {
										return SNew(STextBlock).Text(FText::FromString(Project->Name));
									})
							]

							+ SGridPanel::Slot(0, 1)
							.VAlign(VAlign_Center)
							.Padding(0, 0, 12, 0)
							[
								SNew(STextBlock).Text(INVTEXT("Branch"))
							]

							+SGridPanel::Slot(1,1)
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Left)
							.Padding(2.0f)
							[
								SAssignNew(BranchBox, SComboBox<TSharedRef<FBranch>>)
								.OptionsSource(&Branches)
								.Content()
								[
									SNew(STextBlock).Text(this, &SConnectGameDataDialog::GetCurrentSelectedBranchName)
								]
								.OnSelectionChanged(this, &SConnectGameDataDialog::OnBranchSelectionChanged)
								.OnGenerateWidget_Lambda([](TSharedRef<FBranch> Branch) {
									return SNew(STextBlock).Text(FText::FromString(Branch->Name));
								})
							]
						]
					]

					// Select Upload / Download
					+SWizard::Page()
					.CanShow(this, &SConnectGameDataDialog::CanShowProjectUploadDownload)
					[
						SNew(SVerticalBox)

						// Title
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0)
						[
							SNew(STextBlock)
							.Font(FAppStyle::Get().GetFontStyle("HeadingExtraSmall"))
							.Text( INVTEXT("Initial Sync Direction" ) )
							.TransformPolicy(ETextTransformPolicy::ToUpper)
						]
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Center)
						[
							SNew(SHorizontalBox)

							+ SHorizontalBox::Slot()
							.Padding(10.0f)
							[
								SNew(SBorder)
								.Padding(5)
								.BorderBackgroundColor(this, &SConnectGameDataDialog::GetUploadDownloadSelectionColor, Upload)
								[
									SNew(SButton)
									.Text(INVTEXT("Upload"))
									.ButtonStyle( FAppStyle::Get(), "ToggleButton" )
									.ForegroundColor( FSlateColor::UseForeground() )
									.OnClicked(this, &SConnectGameDataDialog::GetUploadDownloadDirectionSelected, Upload)
									.ContentPadding( FMargin( 1 ) )
									[
										SNew( SVerticalBox )
										
										+SVerticalBox::Slot()
										.Padding(3.0f)
										.HAlign(HAlign_Center)
										.AutoHeight()
										[
											SNew(SImage)
											.DesiredSizeOverride(FVector2D(40, 40))
											.Image(FSlateIcon(FAppStyle::GetAppStyleSetName(), "BlueprintMerge.AcceptSource").GetIcon())
										]

										+SVerticalBox::Slot()
										.AutoHeight()
										.HAlign(HAlign_Center)
										.Padding( 0.0f, 3.0f, 0.0f, 3.0f )
										[
											SNew(STextBlock)
											.Text(INVTEXT("Upload"))
										]
			
										+SVerticalBox::Slot()
										.AutoHeight()
										.HAlign(HAlign_Center)
										.Padding( 0.0f, 3.0f, 0.0f, 3.0f )
										[
											SNew(STextBlock)
											.Text(this, &SConnectGameDataDialog::GetFormattedDataSourceSize, Upload)
										]
									]
								]
							]

							+ SHorizontalBox::Slot()
							.Padding(10.0f)
							[
								SNew(SBorder)
								.Padding(5)
								.BorderBackgroundColor(this, &SConnectGameDataDialog::GetUploadDownloadSelectionColor, Download)
								[
									SNew(SButton)
									.Text(INVTEXT("Download"))
									.ButtonStyle( FAppStyle::Get(), "ToggleButton" )
									.ForegroundColor( FSlateColor::UseForeground() )
									.OnClicked(this, &SConnectGameDataDialog::GetUploadDownloadDirectionSelected, Download)
									.ContentPadding( FMargin( 1 ) )
									[
										SNew( SVerticalBox )
										
										+SVerticalBox::Slot()
										.Padding(3.0f)
										.HAlign(HAlign_Center)
										.AutoHeight()
										[
											SNew(SImage)
											.DesiredSizeOverride(FVector2D(40, 40))
											.Image(FSlateIcon(FAppStyle::GetAppStyleSetName(), "BlueprintMerge.AcceptTarget").GetIcon())
										]

										+SVerticalBox::Slot()
										.AutoHeight()
										.HAlign(HAlign_Center)
										.Padding( 0.0f, 3.0f, 0.0f, 3.0f )
										[
											SNew(STextBlock)
											.Text(INVTEXT("Download"))
										]
										
										+SVerticalBox::Slot()
										.AutoHeight()
										.HAlign(HAlign_Center)
										.Padding( 0.0f, 3.0f, 0.0f, 3.0f )
										[
											SNew(STextBlock)
											.Text(this, &SConnectGameDataDialog::GetFormattedDataSourceSize, Download)
										]
									]
								]
							]
						]

						// Data Warning label
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 5)
						[
							SNew(SWarningOrErrorBox)
							.MessageStyle(EMessageStyle::Warning)
							.Visibility(this, &SConnectGameDataDialog::GetDataEraseLabelVisibility)
							.Message(this, &SConnectGameDataDialog::GetDataEraseLabelText)
						]
						
					]
				]
			]
		]);
}

void SConnectGameDataDialog::ShowModal()
{
	FSlateApplication::Get().AddModalWindow(StaticCastSharedRef<SWindow>(this->AsShared()), FGlobalTabmanager::Get()->GetRootWindow());
}

void SConnectGameDataDialog::Show()
{
	const TSharedRef<SWindow> Window = FSlateApplication::Get().AddWindow(StaticCastSharedRef<SWindow>(this->AsShared()), true);
}

EVisibility SConnectGameDataDialog::GetApiKeyErrorLabelVisibility() const
{
	return ApiKeyError.IsEmpty() ? EVisibility::Hidden : EVisibility::Visible;
}

EVisibility SConnectGameDataDialog::GetDataEraseLabelVisibility() const
{
	return DataEraseMessage.IsEmpty() ? EVisibility::Hidden : EVisibility::Visible;
}

bool SConnectGameDataDialog::CanShowProjectsAndBranches() const
{
	return ApiKeyError.IsEmpty() && !Projects.IsEmpty();
}

bool SConnectGameDataDialog::CanShowProjectUploadDownload() const
{
	return SelectedProjectIndex >= 0 && SelectedBranchIndex >= 0;
}

bool SConnectGameDataDialog::CanFinish() const
{
	return !ApiKey.IsEmpty() && SelectedProjectIndex >= 0 && SelectedBranchIndex >= 0 && SyncDirection != None;
}

FText SConnectGameDataDialog::GetApiKeyErrorLabelText() const
{
	return ApiKeyError;
}

FText SConnectGameDataDialog::GetDataEraseLabelText() const
{
	return DataEraseMessage;
}

FText SConnectGameDataDialog::GetCurrentSelectedProjectName() const
{
	if (SelectedProjectIndex >= 0 && SelectedProjectIndex < Projects.Num())
	{
		return FText::FromString(Projects[SelectedProjectIndex]->Name);
	}
	return FText::GetEmpty();
}

FText SConnectGameDataDialog::GetCurrentSelectedBranchName() const
{
	if (SelectedBranchIndex >= 0 && SelectedBranchIndex < Branches.Num())
	{
		return FText::FromString(Branches[SelectedBranchIndex]->Name);
	}
	return FText::GetEmpty();
}

FSlateColor SConnectGameDataDialog::GetUploadDownloadSelectionColor(InitialGameDataSyncDirection Direction) const
{
	return SyncDirection == Direction ? FLinearColor::Green : FLinearColor::Transparent;
}

FText SConnectGameDataDialog::GetFormattedDataSourceSize(InitialGameDataSyncDirection Direction) const
{
	if (Direction == Upload && !LocalGameDataFile.IsEmpty())
	{
		const auto LocalGameDataFileSizeString = FString::Printf(TEXT("%.2f"), FMathf::Ceil(LocalGameDataFileSize / 1024.0f / 1024.0f * 100.0f) / 100.0f);
		return FText::Format(INVTEXT("{0} [{1} MiB]"), FText::FromString(FPaths::GetCleanFilename(LocalGameDataFile)), FText::FromString(LocalGameDataFileSizeString) );
	}
	else if (Direction == Download && SelectedProjectIndex >= 0 && SelectedBranchIndex >= 0)
	{
		const auto Project = Projects[SelectedProjectIndex];
		const auto Branch = Branches[SelectedBranchIndex];
		const auto BranchSizeString = FString::Printf(TEXT("%.2f"), FMathf::Ceil(Branch->DataSize / 1024.0f / 1024.0f * 100.0f) / 100.0f);
		
		return FText::Format(INVTEXT("{0} ({1}) [{2} MiB]"), FText::FromString(Project->Name), FText::FromString(Branch->Name), FText::FromString(BranchSizeString));	
	}
	else
	{
		return FText::GetEmpty();
	}
}

void SConnectGameDataDialog::OnApiKeyChanged(const FText& NewApiKey)
{
	ApiKeyError = FText::GetEmpty();
	ApiKey = NewApiKey.ToString();;
	
	if (NewApiKey.IsEmpty())
	{
		return;
	}
	
	ServerApiClient->UseApiKey(ApiKey);
	ServerApiClient->GetMyProjects(OnGetMyProjectsResponse::CreateSP(this, &SConnectGameDataDialog::OnMyProjectResponse));
}

void SConnectGameDataDialog::OnMyProjectResponse(FProjectsResponse ProjectsResponse)
{
	if (!ProjectsResponse.Errors.IsEmpty())
	{
		ApiKeyError = INVTEXT("Invalid API Key.");
		return;
	}

	ApiKeyError = FText::GetEmpty();
	Projects.Empty();
	for (auto Project : ProjectsResponse.Result)
	{
		Projects.Add(MakeShared<FProject>(Project));
	}
	Branches.Empty();
	SelectedProjectIndex = -1;
	SelectedBranchIndex = -1;
	if (!Projects.IsEmpty())
	{
		SelectedProjectIndex = 0;
		for (auto Branch : Projects[0]->Branches)
		{
			Branches.Add(MakeShared<FBranch>(Branch));
		}
		ProjectBox->SetSelectedItem(Projects[0]);
	}
	if (!Branches.IsEmpty())
	{
		SelectedBranchIndex = 0;
		BranchBox->SetSelectedItem(Branches[0]);
	}
}

void SConnectGameDataDialog::OnBranchSelectionChanged(TSharedPtr<FBranch> Branch, ESelectInfo::Type Arg)
{
	SelectedBranchIndex = Branches.IndexOfByKey(Branch);
}

void SConnectGameDataDialog::OnProjectSelectionChanged(TSharedPtr<FProject> Project, ESelectInfo::Type Arg)
{
	SelectedProjectIndex = Projects.IndexOfByKey(Project);
}

FReply SConnectGameDataDialog::GetUploadDownloadDirectionSelected(InitialGameDataSyncDirection Direction)
{
	SyncDirection = Direction;
	if (Direction == Download && !LocalGameDataFile.IsEmpty())
	{
		const auto LocalGameDataFileSizeString = FString::Printf(TEXT("%.2f"), FMathf::Ceil(LocalGameDataFileSize / 1024.0f / 1024.0f * 100.0f) / 100.0f);
		DataEraseMessage = FText::Format(INVTEXT("Any existing data in local file '{0}' will be deleted."), FText::FromString(FPaths::GetCleanFilename(LocalGameDataFile)), FText::FromString(LocalGameDataFileSizeString) );
	}
	else if (Direction == Upload && SelectedProjectIndex >= 0 && SelectedBranchIndex >= 0)
	{
		const auto Project = Projects[SelectedProjectIndex];
		const auto Branch = Branches[SelectedBranchIndex];
		const auto BranchSizeString = FString::Printf(TEXT("%.2f"), FMathf::Ceil(Branch->DataSize / 1024.0f / 1024.0f * 100.0f) / 100.0f);
		
		DataEraseMessage = FText::Format(INVTEXT("All existing data in branch '{1}' [{2} MiB] of project '{0}' will be deleted."), FText::FromString(Project->Name), FText::FromString(Branch->Name), FText::FromString(BranchSizeString));	
	}
	
	return FReply::Handled();
}

void SConnectGameDataDialog::GoToProfileApiKey() const
{
	const auto ProfileUrl = ServerApiClient->GetApiKeysUrl();

	FString Error;
	FPlatformProcess::LaunchURL(*ProfileUrl, nullptr, &Error);
	if (!Error.IsEmpty())
	{
		UE_LOG(LogSConnectGameDataDialog, Error, TEXT("Failed to open the URL '%s' in the OS browser due to an error. %s"), *ProfileUrl, *Error);
	}
}

void SConnectGameDataDialog::CloseWindow()
{
	const auto ContainingWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
    if ( ContainingWindow.IsValid() )
    {
    	ContainingWindow->RequestDestroyWindow();
    }
}

void SConnectGameDataDialog::CancelClicked()
{
	CloseWindow();
}

void SConnectGameDataDialog::FinishClicked()
{
	const auto Project = Projects[SelectedProjectIndex];
	const auto Branch = Branches[SelectedBranchIndex];
	const auto FinishParameters = FConnectGameDataParameters
	{
		Project,
		Branch,
		ApiKey,
		ServerAddress,
		SyncDirection
	};
	auto _= this->OnFinished.ExecuteIfBound(FinishParameters);
	
	CloseWindow();
}
