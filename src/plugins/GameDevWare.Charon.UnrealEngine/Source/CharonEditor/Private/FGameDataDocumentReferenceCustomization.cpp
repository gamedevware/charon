
#include "FGameDataDocumentReferenceCustomization.h"
#include "AssetRegistry/AssetData.h"
#include "Containers/Map.h"
#include "Delegates/Delegate.h"
#include "DetailWidgetRow.h"
#include "Editor.h"
#include "GameData/FGameDataDocumentReference.h"
#include "Engine/DataTable.h"
#include "Fonts/SlateFontInfo.h"
#include "Framework/Commands/UIAction.h"
#include "HAL/Platform.h"
#include "HAL/PlatformCrt.h"
#include "IDetailChildrenBuilder.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Text.h"
#include "Misc/Attribute.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyEditorModule.h"
#include "PropertyHandle.h"
#include "GameData/UGameDataBase.h"
#include "Templates/Casts.h"
#include "UObject/Class.h"
#include "UObject/Object.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Text/STextBlock.h"

DEFINE_LOG_CATEGORY(LogFGameDataDocumentReferenceCustomization);

TSharedRef<IPropertyTypeCustomization> FGameDataDocumentReferenceCustomization::MakeInstance()
{
	// Create the instance and returned a SharedRef
	return MakeShareable(new FGameDataDocumentReferenceCustomization());
}

void FGameDataDocumentReferenceCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FGameDataDocumentReferenceCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	GameDataPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataDocumentReference, GameData));
	SchemaPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataDocumentReference, SchemaIdOrName));
	IdPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataDocumentReference, Id));

	const FText PropertyName = PropertyHandle->GetPropertyDisplayName();
	const bool ReadOnly = PropertyHandle->IsEditConst() || !PropertyHandle->IsEditable();
	const bool IsValidHandles = GameDataPropertyHandle.IsValid() && GameDataPropertyHandle->IsValidHandle() &&
		SchemaPropertyHandle.IsValid() && SchemaPropertyHandle->IsValidHandle() &&
		IdPropertyHandle.IsValid() && IdPropertyHandle->IsValidHandle();

	if (ReadOnly && IsValidHandles)
	{
		FString SchemaName = OnGetCurrentSchemaNameString();
		FString DocumentId = OnGetCurrentDocumentIdString();
		
		ChildBuilder.AddCustomRow(PropertyName)
				.NameContent()
				[
					SNew(STextBlock)
					.Text(PropertyName)
					.Font(CustomizationUtils.GetRegularFont())
				]
				.ValueContent()
				.MaxDesiredWidth(0.0f) // don't constrain the combo button width
				[
					SNew(STextBlock)
						.Text(FText::FromString(TEXT("[") + SchemaName + TEXT("] ") + DocumentId))
						.Font(CustomizationUtils.GetRegularFont())
				];
	}
	else if (IsValidHandles)
	{
		/** Construct a asset picker widget with a custom filter */
		ChildBuilder.AddCustomRow(FText::FromString(TEXT("Game Data")))
			.NameContent()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Game Data")))
				.Font(CustomizationUtils.GetRegularFont())
			]
			.ValueContent()
			.MaxDesiredWidth(0.0f) // don't constrain the combo button width
			[
				SNew(SObjectPropertyEntryBox)
				.PropertyHandle(GameDataPropertyHandle)
				.AllowedClass(UGameDataBase::StaticClass())
			];

		FPropertyComboBoxArgs SchemaComboBox(SchemaPropertyHandle, 
					FOnGetPropertyComboBoxStrings::CreateSP(this, &FGameDataDocumentReferenceCustomization::OnGetSchemaNames), 
					FOnGetPropertyComboBoxValue::CreateSP(this, &FGameDataDocumentReferenceCustomization::OnGetCurrentSchemaNameString));
		SchemaComboBox.ShowSearchForItemCount = 1;
		
		ChildBuilder.AddCustomRow(FText::FromString(TEXT("Schema")))
			.NameContent()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Schema")))
				.Font(CustomizationUtils.GetRegularFont())
			]
			.ValueContent()
			.MaxDesiredWidth(0.0f) // don't constrain the combo button width
			[
				PropertyCustomizationHelpers::MakePropertyComboBox(SchemaComboBox)
			];
		
		FPropertyComboBoxArgs IdComboBox(IdPropertyHandle, 
			FOnGetPropertyComboBoxStrings::CreateSP(this, &FGameDataDocumentReferenceCustomization::OnGetDocumentIds), 
			FOnGetPropertyComboBoxValue::CreateSP(this, &FGameDataDocumentReferenceCustomization::OnGetCurrentDocumentIdString));
		IdComboBox.ShowSearchForItemCount = 1;
		
		ChildBuilder.AddCustomRow(FText::FromString(TEXT("Document Id")))
			.NameContent()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Document Id")))
				.Font(CustomizationUtils.GetRegularFont())
			]
			.ValueContent()
			.MaxDesiredWidth(0.0f) // don't constrain the combo button width
			[
				PropertyCustomizationHelpers::MakePropertyComboBox(IdComboBox)
			];
		
	}
	else if (GameDataPropertyHandle.IsValid() || SchemaPropertyHandle.IsValid() || IdPropertyHandle.IsValid())
	{
		UE_LOG(LogFGameDataDocumentReferenceCustomization, Error, TEXT("Unable to find some of of child handles for 'FGameDataDocumentReference'."));
	}
}

UGameDataBase* FGameDataDocumentReferenceCustomization::GetGameData() const
{
	UObject* GameDataObj = nullptr;
	const FPropertyAccess::Result GameDataResult = GameDataPropertyHandle->IsValidHandle() && GameDataPropertyHandle.IsValid() ?
	GameDataPropertyHandle->GetValue(GameDataObj) : FPropertyAccess::Fail;
	if (GameDataResult == FPropertyAccess::Success && GameDataObj != nullptr)
	{
		const auto GameData = Cast<UGameDataBase>(GameDataObj);
		return GameData;
	}
	return nullptr;
}

void FGameDataDocumentReferenceCustomization::OnGetDocumentIds(
	TArray<TSharedPtr<FString>>& OutStrings,
	TArray<TSharedPtr<SToolTip>>& OutToolTips,
	TArray<bool>& OutRestrictedItems) const
{
	const auto GameData = GetGameData();
	const auto IgnoredDocumentId = OnGetCurrentDocumentIdString();
	const auto SchemaNameOrId = OnGetCurrentSchemaNameString();
	
	TArray<FString> AllIds;
	if (GameData != nullptr)
	{
		GameData->GetDocumentIds(SchemaNameOrId, AllIds);
		AllIds.Remove(IgnoredDocumentId);
		
		// Sort the names alphabetically.
		AllIds.Sort();
	}

	for (const FString& DocumentId : AllIds)
	{
		OutStrings.Add(MakeShared<FString>(DocumentId));
		OutRestrictedItems.Add(false);
	}
}

FString FGameDataDocumentReferenceCustomization::OnGetCurrentDocumentIdString() const
{
	if (!IdPropertyHandle.IsValid() || !IdPropertyHandle->IsValidHandle())
	{
		return FString();
	}

	FString DocumentId;
	const FPropertyAccess::Result IdResult = IdPropertyHandle->GetValue(DocumentId);
	if (IdResult == FPropertyAccess::Success)
	{
		if (DocumentId.IsEmpty())
		{
			return TEXT("None");
		}
		return DocumentId;
	}
	else if (IdResult == FPropertyAccess::Fail)
	{
		return TEXT("None");
	}
	else
	{
		return TEXT("Multiple (Invalid)");
	}
}

void FGameDataDocumentReferenceCustomization::OnGetSchemaNames(
	TArray<TSharedPtr<FString>>& OutStrings,
	TArray<TSharedPtr<SToolTip>>& OutToolTips,
	TArray<bool>& OutRestrictedItems) const
{
	const auto GameData = GetGameData();
	auto IgnoredSchemaId = OnGetCurrentSchemaNameString();

	TArray<FString> AllSchemaNames;
	if (GameData != nullptr)
	{
		GameData->GetDocumentSchemaNames(AllSchemaNames);

		// Sort the names alphabetically.
		AllSchemaNames.Sort();
	}

	for (const FString& SchemaName : AllSchemaNames)
	{
		OutStrings.Add(MakeShared<FString>(SchemaName));
		OutRestrictedItems.Add(false);
	}
}

FString FGameDataDocumentReferenceCustomization::OnGetCurrentSchemaNameString() const
{
	if (!SchemaPropertyHandle.IsValid() || !SchemaPropertyHandle->IsValidHandle())
	{
		return FString();
	}

	const auto GameData = GetGameData();
	FString SchemaNameOrId;
	const FPropertyAccess::Result IdResult = SchemaPropertyHandle->GetValue(SchemaNameOrId);
	if (IdResult == FPropertyAccess::Success)
	{
		if (SchemaNameOrId.IsEmpty())
		{
			return TEXT("None");
		}

		if (GameData != nullptr)
		{
			const auto DocumentClass = GameData->FindDocumentSchemaClass(SchemaNameOrId);
			if(DocumentClass)
			{
				return DocumentClass->GetName();
			}
			return SchemaNameOrId;
		}
		else
		{
			return SchemaNameOrId;
		}
	}
	else if (IdResult == FPropertyAccess::Fail)
	{
		return TEXT("None");
	}
	else
	{
		return TEXT("Multiple (Invalid)");
	}
}
