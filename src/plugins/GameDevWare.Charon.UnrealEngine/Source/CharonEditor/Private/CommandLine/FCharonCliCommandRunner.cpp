#pragma once

#include "GameData/CommandLine/FCharonCliCommandRunner.h"

DEFINE_LOG_CATEGORY(LogFCharonCliCommandRunner);

FCharonCliCommandRunner::FCharonCliCommandRunner(FString InParameters)
// we will modify URL and Params in this constructor, so there's no need to pass anything up to base
	: FMonitoredProcess("", "", true, true), FileCleanupList(), EnvironmentVariables()
{
	WorkingDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	const FString CharonIntermediateDirectory = FCharonCliCommandRunner::GetOrCreateCharonIntermediateDirectory();

#if PLATFORM_WINDOWS
	RunScriptPath = CharonIntermediateDirectory / TEXT("RunCharon.bat");
	URL = TEXT("cmd.exe");
	Params = FString::Printf(TEXT("/c \"\"%s\" %s\""), *RunScriptPath, *InParameters);
#elif PLATFORM_MAC || PLATFORM_LINUX
	RunScriptPath = CharonIntermediateDirectory / TEXT("RunCharon.sh");
	URL = TEXT("/usr/bin/env");
	Params = FString::Printf(TEXT(" -- \"%s\" %s"), *RunScriptPath, *InParameters);
#endif
}

FCharonCliCommandRunner::~FCharonCliCommandRunner()
{
	IFileManager& FileManager = IFileManager::Get();
	for (FString FileName : FileCleanupList)
	{
		const bool bDeleted = FileManager.Delete(*FileName, /* require exists */ false, /* even read only */ true,
		                                         /* quiet */ true);
		if (!bDeleted)
		{
			UE_LOG(LogFCharonCliCommandRunner, Log,
			       TEXT("Failed to delete temporary filename '%s' for command '%s'."), *FileName, *Params);
		}
	}
}

bool FCharonCliCommandRunner::Launch()
{
	for (auto KeyValue : EnvironmentVariables)
	{
		FPlatformMisc::SetEnvironmentVar(*KeyValue.Key, *KeyValue.Value);
	}

	UE_LOG(LogFCharonCliCommandRunner, Log, TEXT("Launching CLI process with '%s %s'."), *URL, *Params);

	return FMonitoredProcess::Launch();
}

void FCharonCliCommandRunner::SetApiKey(const FString& InApiKey)
{
	if (InApiKey.IsEmpty())
	{
		return;
	}
	this->EnvironmentVariables.Add(TEXT("CHARON_API_KEY"), InApiKey);
}

void FCharonCliCommandRunner::AttachTemporaryFile(const FString& InFilePath)
{
	if (InFilePath.IsEmpty())
	{
		return;
	}
	FileCleanupList.Add(InFilePath);
}

FString FCharonCliCommandRunner::GetOrCreateCharonIntermediateDirectory()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString PluginScriptsDirectory = FPaths::ConvertRelativePathToFull(
		FPaths::ProjectDir() / TEXT("Plugins/Charon/Resources/Scripts"));
	const FString CharonIntermediateDirectory = FPaths::ConvertRelativePathToFull(
		FPaths::ProjectIntermediateDir() / "Charon");
	if (!PlatformFile.DirectoryExists(*CharonIntermediateDirectory))
	{
		if (!PlatformFile.CreateDirectory(*CharonIntermediateDirectory))
		{
			UE_LOG(LogFCharonCliCommandRunner, Warning,
			       TEXT("Create directory '%s' in Project's intermediate directory."), *CharonIntermediateDirectory);
			return CharonIntermediateDirectory;
		}
		bScriptsCopied = false;
	}

	if (!bScriptsCopied)
	{
		bScriptsCopied = true;
		TArray<FString> FoundFiles;
		PlatformFile.FindFiles(FoundFiles, *PluginScriptsDirectory, nullptr);
		for (const FString SourceFilePath : FoundFiles)
		{
			const FString TargetFileName = CharonIntermediateDirectory / FPaths::GetCleanFilename(SourceFilePath);
			/*if (PlatformFile.FileExists(*TargetFileName))
			{
				continue;
			}*/
			if (!PlatformFile.CopyFile(*TargetFileName, *SourceFilePath))
			{
				UE_LOG(LogFCharonCliCommandRunner, Warning,
				       TEXT("Failed to copy file '%s' to Project's intermediate directory."), *SourceFilePath);
			}
		}
	}

	return CharonIntermediateDirectory;
}
