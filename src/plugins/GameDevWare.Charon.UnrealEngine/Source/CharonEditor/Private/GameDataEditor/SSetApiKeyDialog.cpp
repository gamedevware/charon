#pragma once

#include "SSetApiKeyDialog.h"

#include "Widgets/Input/SHyperlink.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Application/SlateApplication.h"
#include "SWarningOrErrorBox.h"
#include "ServerApi/FProject.h"

DEFINE_LOG_CATEGORY(LogSSetApiKeyDialog);

void SSetApiKeyDialog::Construct(const FArguments& InArgs)
{
	OnFinished = InArgs._OnFinished;
	ServerAddress = InArgs._ServerAddress;
	ProjectId = InArgs._ProjectId;
	ProjectName = InArgs._ProjectName;
	ServerApiClient = MakeShared<FServerApiClient>(ServerAddress);
	
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
					SAssignNew(MainWizard, SWizard)
					.ShowPageList(false)
					.CanFinish(this, &SSetApiKeyDialog::CanFinish)
					.FinishButtonText(INVTEXT("Save"))
					.OnCanceled(this, &SSetApiKeyDialog::CancelClicked)
					.OnFinished(this, &SSetApiKeyDialog::FinishClicked)
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
								.OnTextChanged(this, &SSetApiKeyDialog::OnApiKeyChanged)
						]
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)

							+SHorizontalBox::Slot()
							.HAlign(HAlign_Left)
							[
								SNew(SHyperlink)
								.OnNavigate(this, &SSetApiKeyDialog::GoToProfileApiKey)
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
							.Visibility(this, &SSetApiKeyDialog::GetApiKeyErrorLabelVisibility)
							.Message(this, &SSetApiKeyDialog::GetApiKeyErrorLabelText)
						]
					]
				]
			]
		]);
}

void SSetApiKeyDialog::ShowModal()
{
	FSlateApplication::Get().AddModalWindow(StaticCastSharedRef<SWindow>(this->AsShared()), FGlobalTabmanager::Get()->GetRootWindow());
}

void SSetApiKeyDialog::Show()
{
	const TSharedRef<SWindow> Window = FSlateApplication::Get().AddWindow(StaticCastSharedRef<SWindow>(this->AsShared()), true);
}

EVisibility SSetApiKeyDialog::GetApiKeyErrorLabelVisibility() const
{
	return ApiKeyError.IsEmpty() ? EVisibility::Hidden : EVisibility::Visible;
}


bool SSetApiKeyDialog::CanFinish() const
{
	return !ApiKey.IsEmpty() && IsApiKeyMatchingProjectId;
}


FText SSetApiKeyDialog::GetApiKeyErrorLabelText() const
{
	return ApiKeyError;
}


void SSetApiKeyDialog::OnApiKeyChanged(const FText& NewApiKey)
{
	ApiKeyError = FText::GetEmpty();
	ApiKey = NewApiKey.ToString();;
	
	if (NewApiKey.IsEmpty())
	{
		return;
	}
	
	ServerApiClient->UseApiKey(ApiKey);
	ServerApiClient->GetMyProjects(OnGetMyProjectsResponse::CreateSP(this, &SSetApiKeyDialog::OnMyProjectResponse));
}

void SSetApiKeyDialog::OnMyProjectResponse(FProjectsResponse ProjectsResponse)
{
	if (!ProjectsResponse.Errors.IsEmpty())
	{
		ApiKeyError = INVTEXT("Invalid API Key.");
		return;
	}

	for (auto Project : ProjectsResponse.Result)
	{
		if (Project.Id == ProjectId)
		{
			IsApiKeyMatchingProjectId = true;
			ApiKeyError = FText::GetEmpty();
			return;
		}
	}

	ApiKeyError = FText::Format(INVTEXT("API Key doesn't allow to access '{0}' (id: {1}) project."), FText::FromString(ProjectName), FText::FromString(ProjectId));
	IsApiKeyMatchingProjectId = false;
}

void SSetApiKeyDialog::GoToProfileApiKey() const
{
	const auto ProfileUrl = ServerApiClient->GetApiKeysUrl();

	FString Error;
	FPlatformProcess::LaunchURL(*ProfileUrl, nullptr, &Error);
	if (!Error.IsEmpty())
	{
		UE_LOG(LogSSetApiKeyDialog, Error, TEXT("Failed to open the URL '%s' in the OS browser due to an error. %s"), *ProfileUrl, *Error);
	}
}

void SSetApiKeyDialog::CloseWindow()
{
	const auto ContainingWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	if ( ContainingWindow.IsValid() )
	{
		ContainingWindow->RequestDestroyWindow();
	}
}

void SSetApiKeyDialog::CancelClicked()
{
	CloseWindow();
}

void SSetApiKeyDialog::FinishClicked()
{
	auto _= this->OnFinished.ExecuteIfBound(ApiKey);
	CloseWindow();
}