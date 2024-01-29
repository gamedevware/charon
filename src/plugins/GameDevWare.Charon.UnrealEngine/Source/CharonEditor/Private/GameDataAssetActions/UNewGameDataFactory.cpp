#pragma once

#include "GameData/UNewGameDataFactory.h"

#include "EditorAssetLibrary.h"
#include "FGameDataReimportHandler.h"
#include "GameProjectGenerationModule.h"
#include "IHotReload.h"
#include "ProjectDescriptor.h"
#include "Dialogs/SOutputLogDialog.h"
#include "UObject/Class.h"
#include "Misc/FeedbackContext.h"
#include "GameData/UGameDataBase.h"
#include "GameData/CommandLine/FCharonCli.h"
#include "Serialization/MemoryReader.h"
#include "Misc/DateTime.h"
#include "HAL/FileManager.h"
#include "Interfaces/IProjectManager.h"
#include "Misc/FileHelper.h"
#include "GameData/UGameDataBase.h"
#include "ProjectDescriptor.h"
#include "GameDataEditor/SCreateGameDataDialog.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY(LogUNewGameDataFactory);

UNewGameDataFactory::UNewGameDataFactory(const FObjectInitializer& ObjectInitializer)
{
	SupportedClass = UGameDataBase::StaticClass();

	bCreateNew = true;
}

bool UNewGameDataFactory::DoesSupportClass(UClass* Class)
{
	return UGameDataBase::StaticClass() == Class || Class->IsChildOf(UGameDataBase::StaticClass());
}


bool UNewGameDataFactory::ConfigureProperties()
{
	return true;
}

void UNewGameDataFactory::CleanUp()
{
	Super::CleanUp();

	CreateNewGameDataClassTask = nullptr;
}

UObject* UNewGameDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                               EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UGameDataBase::StaticClass()));

	if (InParent == nullptr)
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Unable to create a game data file. The parent package is not set in the FactoryCreateNew() parameters."));
		return nullptr;
	}

	FString PackageFilePath;
	FPackageName::TryConvertLongPackageNameToFilename(InParent->GetPackage()->GetName(), PackageFilePath);

	if (PackageFilePath.IsEmpty())
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Unable to create a game data file. Failed to determine asset path in file system."));
		return nullptr;
	}

	const auto CreateGameDataDialog = SNew(SCreateGameDataDialog)
		.AssetPath(PackageFilePath);
	CreateGameDataDialog->Show();

	return nullptr;

	const FString FileName = FPaths::GetCleanFilename(PackageFilePath);
	if (FModuleManager::Get().GetModule(FName(FileName)) != nullptr)
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Invalid name '%s' for a game data file. A module with the same name already exists. Choose another name."), *FileName);
		return nullptr;
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString GameDataFilePath = PackageFilePath + TEXT(".gdjs");
	const FString ModuleDirectory = FPaths::ProjectDir() / TEXT("Source") / FileName;
	if (PlatformFile.DirectoryExists(*ModuleDirectory))
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Invalid name '%s' for a game data file. A module directory with the same name '%s' already exists. Use the 'Import to' option if the game data code is already generated."), *GameDataFilePath, *ModuleDirectory);
		return nullptr;
	}

	const FString EmptyGameData;
	if (!PlatformFile.FileExists(*GameDataFilePath) && !FFileHelper::SaveStringToFile(EmptyGameData, *GameDataFilePath))
	{
		Warn->Logf(ELogVerbosity::Error, TEXT("Failed to create the game data file '%s' due to a file system-related error. Make sure you have permission to write to the specified directory."), *GameDataFilePath);
		return nullptr;
	}

	const TObjectPtr<UObject> GameData = NewObject<UObject>(InParent, UObject::StaticClass(), InName, Flags);

	if (PlatformFile.FileSize(*GameDataFilePath) == 0)
	{
		const FString EmptyApiKey;
		const TSharedRef<FJsonObject> ProjectSettingsDocument = MakeShared<FJsonObject>();
		ProjectSettingsDocument->SetStringField(TEXT("Name"), FileName);
		CreateNewGameDataClassTask = FCharonCli::UpdateDocument(
			GameDataFilePath,
			EmptyApiKey,
			TEXT("ProjectSettings"),
			ProjectSettingsDocument,
			TEXT("049bc0604c363a980b000088")
		);
		CreateNewGameDataClassTask.Get()->OnSucceed().AddUObject(this, &UNewGameDataFactory::OnGameDataFileUpdated,
		                                                         PackageFilePath, ModuleDirectory, GameData);
		CreateNewGameDataClassTask.Get()->OnFailed().AddLambda([]()
		{
			UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to update game data file. Check the Output Log and 'Intermediate\\Charon\\logs' for errors."));
		});
		CreateNewGameDataClassTask->Run(ENamedThreads::GameThread);
	}
	else
	{
		OnGameDataFileUpdated(PackageFilePath, ModuleDirectory, GameData);
	}

	UE_LOG(LogUNewGameDataFactory, Log,
	       TEXT("The game data file has been created at '%s', and the source code is generated into the '%s' directory. For a detailed guide, refer to the plugin's documentation."), *GameDataFilePath, *ModuleDirectory);

	return GameData;
}

void UNewGameDataFactory::OnGameDataFileUpdated(const FString PackageFilePath, const FString ModuleDirectory,
                                                const TObjectPtr<UObject> GameData)
{
	const FName ModuleName = FName(FPaths::GetCleanFilename(PackageFilePath));
	const FString GameDataFilePath = PackageFilePath + TEXT(".gdjs");
	const FString GameDataClassName = TEXT("U") + ModuleName.ToString();
	const FString EmptyApiKey;

	CreateNewGameDataClassTask = FCharonCli::GenerateUnrealEngineSourceCode(
		GameDataFilePath,
		EmptyApiKey,
		ModuleDirectory,
		TEXT("UDocument"),
		GameDataClassName
	);
	CreateNewGameDataClassTask.Get()->OnSucceed().AddUObject(this, &UNewGameDataFactory::OnSourceCodeGenerated,
	                                                         PackageFilePath, ModuleDirectory, GameData);
	CreateNewGameDataClassTask.Get()->OnFailed().AddLambda([]()
	{
		UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to generate the C++ code. Check the Output Log and 'Intermediate\\Charon\\logs' for errors."));
	});
	CreateNewGameDataClassTask->Run(ENamedThreads::GameThread);
}

void UNewGameDataFactory::OnSourceCodeGenerated(
	const FString PackageFilePath,
	const FString ModuleDirectory,
	const TObjectPtr<UObject> GameData)
{
	const FName ModuleName = FName(FPaths::GetCleanFilename(PackageFilePath));
	const FString GameDataFilePath = PackageFilePath + TEXT(".gdjs");
	const FString GameDataClassName = TEXT("U") + ModuleName.ToString();

	AddModuleToProjectFile(ModuleName);
	UpdateCodeProjectFiles();

	UE_LOG(LogUNewGameDataFactory, Log, TEXT("Starting the C++ code compilation, after which the new '%s' module will be included in your project."), *ModuleName.ToString());

	IHotReloadModule& HotReloadModule = IHotReloadModule::Get();
	const bool bRecompileSucceeded = HotReloadModule.RecompileModule(ModuleName, *GLog,
	                                                                 ERecompileModuleFlags::ReloadAfterRecompile);
	if (!bRecompileSucceeded)
	{
		UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to recompile the C++ code due error. Check Output Log, fix errors and try 'Import to' option on '%s' file."), *GameDataFilePath);
		RemoveAsset(GameData);
		return;
	}

	const IModuleInterface* GameDataModule = FModuleManager::Get().GetModule(ModuleName);
	if (GameDataModule == nullptr)
	{
		UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to load '%s' module. Check Output Log, fix errors and try 'Import to' option on '%s' file."), *ModuleName.ToString(), *GameDataFilePath);

		RemoveAsset(GameData);
		return;
	}

	const FString GameDataClassPackagePath = ModuleDirectory / TEXT("Public") / GameDataClassName + TEXT(".h");
	const auto GameDataClassPackage = LoadPackage(nullptr, *GameDataClassPackagePath, LOAD_None);
	const auto GameDataClass = FindObject<UClass>(GameDataClassPackage, *GameDataClassName, /*exact class*/ false);
	if (GameDataClass == nullptr)
	{
		UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to locate the new game data class '%s' using the FindObject() method. Please check the Output Log, fix any errors, and try using the 'Import to' option on the '%s' file."), *GameDataClassName, *GameDataFilePath);
		RemoveAsset(GameData);
		return;
	}

	const auto GameDataPackage = GameData.Get()->GetPackage();
	const TObjectPtr<UGameDataBase> NewGameData = NewObject<UGameDataBase>(
		GameDataPackage, GameDataClass, GameData->GetFName(), GameData->GetFlags());
	GameData->MarkAsGarbage();
	auto _ = GameDataPackage->MarkPackageDirty();

	UE_LOG(LogUNewGameDataFactory, Log, TEXT("Starting the import of game data file '%s' into the newly created asset '%s'."), *GameDataFilePath, *GameDataPackage->GetName());

	auto ReimportHandler = FGameDataReimportHandler();
	if (ReimportHandler.Reimport(NewGameData) != EReimportResult::Succeeded)
	{
		UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to import of game data file '%s' into the newly created asset '%s'. Please check the Output Log, fix any errors, and try using the 'Import to' option on the '%s' file."), *GameDataFilePath, *GameDataPackage->GetName(), *GameDataFilePath);
		RemoveAsset(GameData);
		return;
	}

	UE_LOG(LogUNewGameDataFactory, Log, TEXT("Successfully completed creation of game data asset '%s'."),
	       *GameDataPackage->GetName());
}

void UNewGameDataFactory::RemoveAsset(const TObjectPtr<UObject> AssetObject)
{
	if (AssetObject == nullptr)
	{
		return;
	}

	FString PackageFilePath;
	FPackageName::TryConvertLongPackageNameToFilename(AssetObject->GetPackage()->GetName(), PackageFilePath);
	PackageFilePath.Append(TEXT(".uasset"));
	FPaths::MakePathRelativeTo(PackageFilePath, *FPaths::ProjectDir());

	const bool bAssetExists = UEditorAssetLibrary::DoesAssetExist(PackageFilePath);
	if (bAssetExists)
	{
		const bool bDeleteOK = UEditorAssetLibrary::DeleteAsset(PackageFilePath);
		ensure(bDeleteOK);
	}
}

void UNewGameDataFactory::AddModuleToProjectFile(const FName ModuleName)
{
	IProjectManager& ProjectManager = IProjectManager::Get();
	auto CurrentProject = FProjectDescriptor(*ProjectManager.Get().GetCurrentProject());

	if (!CurrentProject.HasModule(ModuleName))
	{
		UE_LOG(LogUNewGameDataFactory, Log, TEXT("Inserting module '%s' into the current .uproject file."), *ModuleName.ToString());

		CurrentProject.Modules.Add(FModuleDescriptor(ModuleName, EHostType::Runtime, ELoadingPhase::Default));
	}

	FText FailReason;
	if (!CurrentProject.Save(FPaths::GetProjectFilePath(), FailReason))
	{
		UE_LOG(LogUNewGameDataFactory, Error, TEXT("Failed to add the module '%s' to the .uproject file due to an error - %s. Please check the Output Log, fix any errors, and try adding module and compiling code manually."), *ModuleName.ToString(), *FailReason.ToString());
		SOutputLogDialog::Open(INVTEXT("Add Module"), INVTEXT("Failed to add module"), FailReason, FText::GetEmpty());
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString TargetFileDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Source"));

	TArray<FString> FoundTargetFiles;
	PlatformFile.FindFiles(FoundTargetFiles, *TargetFileDirectory, TEXT(".cs"));
	for (FString TargetFilePath : FoundTargetFiles)
	{
		if (!TargetFilePath.EndsWith(".Target.cs"))
		{
			continue;
		}

		TArray<FString> FileLines;
		if (!FFileHelper::LoadFileToStringArray(FileLines, *TargetFilePath))
		{
			UE_LOG(LogUNewGameDataFactory, Warning, TEXT("Failed to add the module '%s' to the '%s'. Please check the Output Log, fix any errors, and try adding module and compiling code manually."), *ModuleName.ToString(), *TargetFilePath);
			continue;
		}

		UE_LOG(LogUNewGameDataFactory, Log, TEXT("Inserting module '%s' into the '%s' file."), *ModuleName.ToString(), *TargetFilePath);

		const FString QuotedModuleName = FString::Format(TEXT("\"{0}\""), {ModuleName.ToString()});
		if (!FileLines.ContainsByPredicate([QuotedModuleName](const FString& Content)
		{
			return Content.Contains(QuotedModuleName);
		}))
		{
			FString SearchPattern = TEXT("ExtraModuleNames.");
			const int32 InsertPosition = FileLines.IndexOfByPredicate([SearchPattern](const FString& Content)
			{
				return Content.Contains(SearchPattern);
			});
			if (InsertPosition != INDEX_NONE)
			{
				FString InsertString = FileLines[InsertPosition];
				const int32 CutPosition = InsertString.Find(SearchPattern) + SearchPattern.Len();
				InsertString.MidInline(0, CutPosition);
				InsertString.Appendf(TEXT("Add(%s);"), *QuotedModuleName);
				FileLines.Insert(InsertString, InsertPosition);
			}
		}

		if (!FFileHelper::SaveStringArrayToFile(FileLines, *TargetFilePath))
		{
			UE_LOG(LogUNewGameDataFactory, Warning, TEXT("Failed to add the module '%s' to the '%s'. Please check the Output Log, fix any errors, and try adding module and compiling code manually."), *ModuleName.ToString(), *TargetFilePath);
			continue;
		}
	}
}

void UNewGameDataFactory::UpdateCodeProjectFiles()
{
	FText FailReason, FailLog;
	if (!FGameProjectGenerationModule::Get().UpdateCodeProject(FailReason, FailLog))
	{
		SOutputLogDialog::Open(INVTEXT("Refresh Project"), FailReason, FailLog, FText::GetEmpty());
	}
}
