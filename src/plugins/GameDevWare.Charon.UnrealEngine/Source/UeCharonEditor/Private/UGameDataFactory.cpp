

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

FString MakeProjectAbsolutePath(FString ProjectRelativePath)
{
	if (!FPaths::IsRelative(ProjectRelativePath))
	{
		return ProjectRelativePath;
	}
	
	FString ProjectDir = FPaths::ProjectDir();
	FString AbsolutePath = FPaths::Combine(ProjectDir, ProjectRelativePath);
	return AbsolutePath;
}
FString MakeProjectRelativePath(const FString& AbsolutePath)
{
	if (FPaths::IsRelative(AbsolutePath))
	{
		return AbsolutePath;
	}
	
	const FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString RelativePath = AbsolutePath;
	FPaths::MakePathRelativeTo(RelativePath, *ProjectDir);
	return RelativePath;
}

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
	return Class == UGameDataBase::StaticClass();
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
		GameData->ImportSettings.OriginalAssetPath = MakeProjectRelativePath(Filename);
		GameData->ImportSettings.OriginalAssetHash = LexToString(FMD5Hash::HashFile(*Filename));

	}
	return GameData;
}
UObject* UGameDataFactory::FactoryCreateBinary
(
	UClass*				Class,
	UObject*			InParent,
	FName				Name,
	EObjectFlags		Flags,
	UObject*			Context,
	const TCHAR*		FileType,
	const uint8*&		Buffer,
	const uint8*		BufferEnd,
	FFeedbackContext*	Warn
)
{
	EGameDataFormat Format;
	
	const double StartTime = FPlatformTime::Seconds();
	UE_LOG(LogUGameDataFactory, Log, TEXT("Importing game data by name '%s' from file type '%s'."), *Name.ToString(), FileType);
	
	const FString FileName = Name.ToString();
	const FString Extension = FPaths::GetExtension(FileName);
	if (FCString::Stricmp(FileType, TEXT("GDJS")) == 0)
	{
		Format = EGameDataFormat::Json;
	}
	else if (FCString::Stricmp(FileType, TEXT("GDMP")) == 0)
	{
		Format = EGameDataFormat::MessagePack;
	}
	else
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Invalid Game Data asset extension '%s'. Expected are '.gdjs, .gdmp'."), *FileName);
		return nullptr;
	}

	UGameDataBase* GameData;
	if (GameDataClass != nullptr)
	{
		GameData = NewObject<UGameDataBase>(InParent, GameDataClass, Name, Flags | RF_Transactional);
	}
	else
	{
		// if we have no data asset class, use the passed-in class instead
		check(Class->IsChildOf(UGameDataBase::StaticClass()));
		GameData = NewObject<UGameDataBase>(InParent, Class, Name, Flags);

	}

	FBufferReader Stream((void*)Buffer, BufferEnd-Buffer, false);
	if (!GameData->TryLoad(&Stream, Format))
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Failed to import Game Data from file '%s'. Read logs for details."), *FileName);
		return nullptr;
	}

	UE_LOG(LogUGameDataFactory, Log, TEXT("Successfully imported game data with name '%s' from file type '%s' in %f seconds."), *Name.ToString(), FileType, FPlatformTime::Seconds() - StartTime);
	
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

bool UGameDataFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	const auto GameData = Cast<UGameDataBase>(Obj);
	if(GameData == nullptr || GameData->ImportSettings.OriginalAssetPath.IsEmpty())
	{
		return false;
	}
	OutFilenames.Add(MakeProjectAbsolutePath(GameData->ImportSettings.OriginalAssetPath));
	return true;
}

void UGameDataFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	if (NewReimportPaths.Num() == 0)
	{
		return;
	}
	
	const auto GameData = Cast<UGameDataBase>(Obj);
	if(GameData == nullptr)
	{
		return;
	}
	GameData->ImportSettings.OriginalAssetPath = MakeProjectRelativePath(NewReimportPaths[0]);
}

EReimportResult::Type UGameDataFactory::Reimport(UObject* Obj)
{
	const auto GameData = Cast<UGameDataBase>(Obj);
	if(GameData == nullptr || GameData->ImportSettings.OriginalAssetPath.IsEmpty())
	{
		return EReimportResult::Failed;
	}
	const auto GameDataFilePath = MakeProjectAbsolutePath(GameData->ImportSettings.OriginalAssetPath);
	EGameDataFormat Format;
	
	const double StartTime = FPlatformTime::Seconds();
	UE_LOG(LogUGameDataFactory, Log, TEXT("Re-importing game data from file '%s'."), *GameDataFilePath);
	
	const FString Extension = FPaths::GetExtension(GameDataFilePath);
	if (FCString::Stricmp(*Extension, TEXT("GDJS")) == 0)
	{
		Format = EGameDataFormat::Json;
	}
	else if (FCString::Stricmp(*Extension, TEXT("GDMP")) == 0)
	{
		Format = EGameDataFormat::MessagePack;
	}
	else
	{
		UE_LOG(LogUGameDataFactory, Error, TEXT("Invalid Game Data asset extension '%s'. Expected are '.gdjs, .gdmp'."), *GameDataFilePath);
		return EReimportResult::Failed;
	}

	const auto Stream = IFileManager::Get().CreateFileReader(*GameDataFilePath, 0);
	if(Stream == nullptr)
	{
		UE_LOG(LogUGameDataFactory, Error, TEXT("Failed open file '%s' for import."), *GameDataFilePath);
		return EReimportResult::Failed;
	}
	if (!GameData->TryLoad(Stream, Format))
	{
		UE_LOG(LogUGameDataFactory, Error, TEXT("Failed to import Game Data from file '%s'. Read logs for details."), *GameDataFilePath);
		return EReimportResult::Failed;
	}

	UE_LOG(LogUGameDataFactory, Log, TEXT("Successfully imported game data from file '%s' in %f seconds."), *GameDataFilePath, FPlatformTime::Seconds() - StartTime);
	return EReimportResult::Succeeded;
}