

#include "UGameDataFactory.h"
#include "UObject/Class.h"
#include "JsonObjectConverter.h"
#include "GameData/UGameDataBase.h"
#include "Serialization/MemoryReader.h"
#include "JsonObjectConverter.h"
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"
#include "FAssetClassParentFilter.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Misc/DateTime.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogUGameDataFactory);

UGameDataFactory::UGameDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UGameDataBase::StaticClass();

	Formats.Add( TEXT( "gdjs;JSON Game Data" ) );
	Formats.Add( TEXT( "gdmp;MessagePack Game Data" ) );
	bCreateNew = false;
	bEditorImport = true;
}

bool UGameDataFactory::DoesSupportClass(UClass* Class)
{
	return UGameDataBase::StaticClass() == Class || Class->IsChildOf(UGameDataBase::StaticClass());
}

bool UGameDataFactory::ConfigureProperties()
{
	// nullptr the GameDataClass so we can check for selection
	GameDataClass = nullptr;

	// Load the classviewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilters.Add(Filter.ToSharedRef());

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UGameDataBase::StaticClass());

	const FText TitleText = FText::FromString(TEXT("Pick Class For Game Data Instance"));
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UGameDataBase::StaticClass());

	if ( bPressedOk )
	{
		GameDataClass = ChosenClass;
	}

	return bPressedOk;
}

void UGameDataFactory::CleanUp()
{
	Super::CleanUp();

	AutomatedImportSettings = nullptr;
	GameDataClass = nullptr;
}

UObject* UGameDataFactory::FactoryCreateFile
(
	UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	const FString& Filename,
	const TCHAR* Parms,
	FFeedbackContext* Warn,
	bool& bOutOperationCanceled
)
{
	auto GameData = Cast<UGameDataBase>(Super::FactoryCreateFile(InClass, InParent, InName, Flags, Filename, Parms, Warn, bOutOperationCanceled));
	if(GameData != nullptr)
	{
		GameData->AssetImportData->UpdateFilenameOnly(Filename);
	}
	return GameData;
}
UObject* UGameDataFactory::FactoryCreateBinary
(
	UClass*				InClass,
	UObject*			InParent,
	FName				InName,
	EObjectFlags		Flags,
	UObject*			Context,
	const TCHAR*		InType,
	const uint8*&		Buffer,
	const uint8*		BufferEnd,
	FFeedbackContext*	Warn
)
{
	UImportSubsystem* ImportSubsystem = GEditor->GetEditorSubsystem<UImportSubsystem>();
	EGameDataFormat Format;
	
	const double StartTime = FPlatformTime::Seconds();
	UE_LOG(LogUGameDataFactory, Log, TEXT("Importing game data by name '%s' from file type '%s'."), *InName.ToString(), InType);
	
	const FString FileName = InName.ToString();
	const FString Extension = FPaths::GetExtension(FileName);
	if (FCString::Stricmp(InType, TEXT("GDJS")) == 0)
	{
		Format = EGameDataFormat::Json;
	}
	else if (FCString::Stricmp(InType, TEXT("GDMP")) == 0)
	{
		Format = EGameDataFormat::MessagePack;
	}
	else
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Invalid Game Data asset extension '%s'. Expected are '.gdjs, .gdmp'."), *FileName);
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

	FBufferReader Stream((void*)Buffer, BufferEnd-Buffer, false);
	if (!GameData->TryLoad(&Stream, Format))
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Failed to import Game Data from file '%s'. Read logs for details."), *FileName);
		return nullptr;
	}

	UE_LOG(LogUGameDataFactory, Log, TEXT("Successfully imported game data with name '%s' from file type '%s' in %f seconds."), *InName.ToString(), InType, FPlatformTime::Seconds() - StartTime);

	ImportSubsystem->BroadcastAssetPostImport(this, GameData);
	
	return GameData;
}

bool UGameDataFactory::FactoryCanImport(const FString& Filename)

{
	FString Extension = FPaths::GetExtension(Filename);

	return (Formats.ContainsByPredicate(
		[&Extension](const FString& Format)
		{
			return Format.StartsWith(Extension);
		}));
}

IImportSettingsParser* UGameDataFactory::GetImportSettingsParser()
{
	return this;
}

void UGameDataFactory::ParseFromJson(TSharedRef<FJsonObject> ImportSettingsJson)
{
	// Store these settings to be applied to the texture later
	AutomatedImportSettings = ImportSettingsJson;

	// Try to apply any import time options now
	FJsonObjectConverter::JsonObjectToUStruct(ImportSettingsJson, GetClass(), this, 0, CPF_InstancedReference);
}