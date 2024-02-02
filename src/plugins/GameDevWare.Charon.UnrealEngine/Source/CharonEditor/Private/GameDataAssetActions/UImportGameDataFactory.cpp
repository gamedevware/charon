#pragma once

#include "GameDataAssetActions/UImportGameDataFactory.h"
#include "UObject/Class.h"
#include "Misc/FeedbackContext.h"
#include "JsonObjectConverter.h"
#include "GameData/UGameDataBase.h"
#include "Serialization/MemoryReader.h"
#include "ClassViewerModule.h"
#include "FAssetClassParentFilter.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Misc/DateTime.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogUImportGameDataFactory);

bool UImportGameDataFactory::PickClass()
{
	// nullptr the GameDataClass so we can check for selection
	GameDataClass = nullptr;

	// Load the classviewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::DisplayName;


	TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilters.Add(Filter.ToSharedRef());

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UGameDataBase::StaticClass());

	const FText TitleText = FText::FromString(TEXT("Game Data Class"));
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UGameDataBase::StaticClass());

	if (bPressedOk)
	{
		GameDataClass = ChosenClass;
	}

	return bPressedOk;
}

UImportGameDataFactory::UImportGameDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UGameDataBase::StaticClass();

	Formats.Add(TEXT("gdjs;JSON Game Data"));
	Formats.Add(TEXT("gdmp;MessagePack Game Data"));

	bCreateNew = false;
	bEditorImport = true;
}

bool UImportGameDataFactory::DoesSupportClass(UClass* Class)
{
	return UGameDataBase::StaticClass() == Class || Class->IsChildOf(UGameDataBase::StaticClass());
}

bool UImportGameDataFactory::ConfigureProperties()
{
	return true;
}

void UImportGameDataFactory::CleanUp()
{
	Super::CleanUp();

	AutomatedImportSettings = nullptr;
	GameDataClass = nullptr;
}

UObject* UImportGameDataFactory::FactoryCreateFile
(
	UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	const FString& Filename,
	const TCHAR* Params,
	FFeedbackContext* Warn,
	bool& bOutOperationCanceled
)
{
	const auto GameData = Cast<UGameDataBase>(Super::FactoryCreateFile(InClass, InParent, InName, Flags, Filename, Params, Warn, bOutOperationCanceled));
	if (GameData != nullptr)
	{
		GameData->AssetImportData->UpdateFilenameOnly(Filename);
	}
	return GameData;
}

UObject* UImportGameDataFactory::FactoryCreateBinary
(
	UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UObject* Context,
	const TCHAR* InType,
	const uint8*& Buffer,
	const uint8* BufferEnd,
	FFeedbackContext* Warn
)
{
	UImportSubsystem* ImportSubsystem = GEditor->GetEditorSubsystem<UImportSubsystem>();
	EGameDataFormat Format;

	const double StartTime = FPlatformTime::Seconds();
	UE_LOG(LogUImportGameDataFactory, Log, TEXT("Importing game data with name '%s' from file type '%s'."), *InName.ToString(), InType);

	const FString FileName = InName.ToString();
	const FString Extension = FPaths::GetExtension(FileName);
	if (FCString::Stricmp(InType, TEXT("GDJS")) == 0 || FCString::Stricmp(InType, TEXT("JSON")) == 0)
	{
		Format = EGameDataFormat::Json;
	}
	else if (FCString::Stricmp(InType, TEXT("GDMP")) == 0 || FCString::Stricmp(InType, TEXT("MSGPACK")) == 0 ||
		FCString::Stricmp(InType, TEXT("MSGPCK")) == 0)
	{
		Format = EGameDataFormat::MessagePack;
	}
	else
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Import failed due to an unknown extension '%s' of the game data file. Expected extensions are '.gdjs, .json, .gdmp, .msgpack, .msgpck'."), *FileName);
		return nullptr;
	}

	if (GameDataClass == nullptr && !PickClass())
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Import failed because class picking was cancelled by the user."));
		return nullptr;
	}

	ImportSubsystem->BroadcastAssetPreImport(this, InClass, InParent, InName, InType);

	UGameDataBase* GameData;
	UObject* ExistingGameData = StaticFindObject(nullptr, InParent, *InName.ToString(), true);
	if (ExistingGameData != nullptr && (GameDataClass != nullptr || ExistingGameData->GetClass() == GameDataClass))
	{
		GameData = Cast<UGameDataBase>(ExistingGameData);
	}
	else if (GameDataClass != nullptr)
	{
		GameData = NewObject<UGameDataBase>(InParent, GameDataClass, InName, Flags | RF_Transactional);
	}
	else
	{
		// if we have no data asset class, use the passed-in class instead
		check(InClass->IsChildOf(UGameDataBase::StaticClass()));
		GameData = NewObject<UGameDataBase>(InParent, InClass, InName, Flags);
	}

	FBufferReader Stream((void*)Buffer, BufferEnd - Buffer, false);
	if (!GameData->TryLoad(&Stream, Format))
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Failed to import the game data file '%s'. Detailed information is provided in the Output Log."), *FileName);
		return nullptr;
	}

	UE_LOG(LogUImportGameDataFactory, Log, TEXT("Successfully imported the game data file '%s' with the extension '%s' in %f seconds."), *InName.ToString(), InType, FPlatformTime::Seconds() - StartTime);

	ImportSubsystem->BroadcastAssetPostImport(this, GameData);

	return GameData;
}

bool UImportGameDataFactory::FactoryCanImport(const FString& Filename)

{
	FString Extension = FPaths::GetExtension(Filename);

	return (Formats.ContainsByPredicate(
		[&Extension](const FString& Format)
		{
			return Format.StartsWith(Extension);
		}));
}

IImportSettingsParser* UImportGameDataFactory::GetImportSettingsParser()
{
	return this;
}

void UImportGameDataFactory::ParseFromJson(TSharedRef<FJsonObject> ImportSettingsJson)
{
	// Store these settings to be applied to the texture later
	AutomatedImportSettings = ImportSettingsJson;

	// Try to apply any import time options now
	FJsonObjectConverter::JsonObjectToUStruct(ImportSettingsJson, GetClass(), this, 0, CPF_InstancedReference);
}
