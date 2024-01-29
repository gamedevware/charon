#pragma once

#include "FGameDataReimportHandler.h"
#include "GameData/UGameDataBase.h"

DEFINE_LOG_CATEGORY(LogFGameDataReimportHandler);

int32 FGameDataReimportHandler::GetPriority() const
{
	return 1;
}

bool FGameDataReimportHandler::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
#if WITH_EDITORONLY_DATA
	const UGameDataBase* GameData = Cast<UGameDataBase>(Obj);

	if (GameData != nullptr && GameData->AssetImportData != nullptr)
	{
		GameData->AssetImportData->ExtractFilenames(OutFilenames);
		return true;
	}
#endif	// WITH_EDITORONLY_DATA

	return false;
}

void FGameDataReimportHandler::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
#if WITH_EDITORONLY_DATA
	const UGameDataBase* GameData = Cast<UGameDataBase>(Obj);

	if (GameData && GameData->AssetImportData && ensure(NewReimportPaths.Num() == 1))
	{
		GameData->AssetImportData->UpdateFilenameOnly(NewReimportPaths[0]);
	}
#endif	// WITH_EDITORONLY_DATA
}

EReimportResult::Type FGameDataReimportHandler::Reimport(UObject* Obj)
{
#if WITH_EDITORONLY_DATA
	const auto GameData = Cast<UGameDataBase>(Obj);
	FString Filename;

	if (GameData != nullptr && GameData->AssetImportData != nullptr)
	{
		Filename = GameData->AssetImportData->GetFirstFilename();
	}
	if (Filename.IsEmpty())
	{
		return EReimportResult::Failed;
	}

	const auto GameDataFilePath = Filename;
	EGameDataFormat Format;

	const double StartTime = FPlatformTime::Seconds();
	UE_LOG(LogFGameDataReimportHandler, Log, TEXT("Re-importing game data from file '%s'."), *GameDataFilePath);

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
		UE_LOG(LogFGameDataReimportHandler, Error, TEXT("Invalid Game Data asset extension '%s'. Expected are '.gdjs, .gdmp'."), *GameDataFilePath);
		return EReimportResult::Failed;
	}

	const TUniquePtr<FArchive> Stream(IFileManager::Get().CreateFileReader(*GameDataFilePath, 0));
	if (Stream == nullptr)
	{
		UE_LOG(LogFGameDataReimportHandler, Error, TEXT("Failed open file '%s' for import."), *GameDataFilePath);
		return EReimportResult::Failed;
	}
	if (!GameData->TryLoad(Stream.Get(), Format))
	{
		UE_LOG(LogFGameDataReimportHandler, Error, TEXT("Failed to import Game Data from file '%s'. Read logs for details."), *GameDataFilePath);
		return EReimportResult::Failed;
	}

	UE_LOG(LogFGameDataReimportHandler, Log, TEXT("Successfully imported game data from file '%s' in %f seconds."), *GameDataFilePath, FPlatformTime::Seconds() - StartTime);

	return EReimportResult::Succeeded;
#else
	return EReimportResult::Failed;
#endif
}
