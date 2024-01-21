#pragma once

#include "FApiKeyStorage.h"
#include "Misc/FileHelper.h"

DEFINE_LOG_CATEGORY(LogFApiKeyStorage);

bool FApiKeyStorage::IsKeyExists(const FString& ServerAddress, const FString& ProjectId)
{
	const auto KeyFilePath = GetOrCreateKeyDirectory() / GetKeyFileName(ServerAddress, ProjectId);
	return FPaths::FileExists(KeyFilePath);	
}

bool FApiKeyStorage::LoadApiKey(const FString& ServerAddress, const FString& ProjectId, FString& OutApiKey)
{
	const auto KeyFilePath = GetOrCreateKeyDirectory() / GetKeyFileName(ServerAddress, ProjectId);
	 return FFileHelper::LoadFileToString(OutApiKey, *KeyFilePath);
}

void FApiKeyStorage::SaveApiKey(const FString& ServerAddress, const FString& ProjectId, const FString& ApiKey)
{
	const auto KeyFilePath = GetOrCreateKeyDirectory() / GetKeyFileName(ServerAddress, ProjectId);
	const bool bSaved = FFileHelper::SaveStringToFile(ApiKey, *KeyFilePath, FFileHelper::EEncodingOptions::ForceUTF8);
	if(!bSaved)
	{
		UE_LOG(LogFApiKeyStorage, Error, TEXT("Failed to save API Key to file '%s'."), *KeyFilePath);
	}
}

FString FApiKeyStorage::GetOrCreateKeyDirectory()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString KeysDirectory = FPaths::ConvertRelativePathToFull(
		FPaths::ProjectIntermediateDir() / "Charon" / "keys");

	if (PlatformFile.DirectoryExists(*KeysDirectory))
	{
		PlatformFile.CreateDirectoryTree(*KeysDirectory);
	}
	return KeysDirectory;
}

FString FApiKeyStorage::GetKeyFileName(const FString& ServerAddress, const FString& ProjectId)
{
	return FPaths::MakeValidFileName(ServerAddress) + "_" +
		FPaths::MakeValidFileName(ProjectId) + ".key"; 
}
