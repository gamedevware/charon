#pragma once

#include "GameData/UNewGameDataFactory.h"

#include "UObject/Class.h"
#include "Misc/FeedbackContext.h"
#include "GameData/UGameDataBase.h"
#include "Serialization/MemoryReader.h"
#include "Misc/DateTime.h"
#include "HAL/FileManager.h"
#include "GameDataEditor/SCreateGameDataDialog.h"

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
}