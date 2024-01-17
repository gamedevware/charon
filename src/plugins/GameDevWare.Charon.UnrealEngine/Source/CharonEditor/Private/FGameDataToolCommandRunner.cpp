#include "FGameDataToolCommandRunner.h"

DEFINE_LOG_CATEGORY(LogFGameDataToolCommandRunner);

FGameDataToolCommandRunner::FGameDataToolCommandRunner(FString InParameters)
// we will modify URL and Params in this constructor, so there's no need to pass anything up to base
	: FMonitoredProcess("", "", true, true), FileCleanupList(), EnvironmentVariables()
{
	this->WorkingDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	const FString CharonIntermediateDirectory = FGameDataToolCommandRunner::GetOrCreateCharonIntermediateDirectory();

#if PLATFORM_WINDOWS
	this->RunScriptPath = CharonIntermediateDirectory / TEXT("RunCharon.bat");
	this->URL = TEXT("cmd.exe");
	this->Params = FString::Printf(TEXT("/c \"\"%s\" %s\""), *RunScriptPath, *InParameters);
#elif PLATFORM_MAC || PLATFORM_LINUX
	RunScriptPath = CharonIntermediateDirectory / TEXT("RunCharon.sh");
	this->URL = TEXT("/usr/bin/env");
	this->Params = FString::Printf(TEXT(" -- \"%s\" %s"), *RunScriptPath, *InParameters);
#endif
}

FGameDataToolCommandRunner::~FGameDataToolCommandRunner()
{
	IFileManager& FileManager = IFileManager::Get();
	for (FString FileName : FileCleanupList)
	{
		const bool bDeleted = FileManager.Delete(*FileName, /* require exists */ false, /* even read only */ true,
		                                         /* quiet */ true);
		if (!bDeleted)
		{
			UE_LOG(LogFGameDataToolCommandRunner, Log,
			       TEXT("Failed to delete temporary filename '%s' for command '%s'."), *FileName, *Params);
		}
	}
}

bool FGameDataToolCommandRunner::Launch()
{
	for (auto KeyValue : EnvironmentVariables)
	{
		FPlatformMisc::SetEnvironmentVar(*KeyValue.Key, *KeyValue.Value);
	}

	UE_LOG(LogFGameDataToolCommandRunner, Log, TEXT("Launching CLI process with '%s %s'."), *URL, *Params);

	return FMonitoredProcess::Launch();
}

void FGameDataToolCommandRunner::SetApiKey(const FString& InApiKey)
{
	if (InApiKey.IsEmpty())
	{
		return;
	}
	this->EnvironmentVariables.Add(TEXT("CHARON_API_KEY"), InApiKey);
}

void FGameDataToolCommandRunner::AttachTemporaryFile(const FString& InFilePath)
{
	if (InFilePath.IsEmpty())
	{
		return;
	}
	FileCleanupList.Add(InFilePath);
}

FString FGameDataToolCommandRunner::GetOrCreateCharonIntermediateDirectory()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString PluginContentDirectory = FPaths::ConvertRelativePathToFull(
		FPaths::ProjectDir() / TEXT("Plugins/Charon/Source/CharonEditor/Content"));
	const FString EditorIntermediateFolder = FPaths::ConvertRelativePathToFull(
		FPaths::ProjectIntermediateDir() / "Charon");
	if (!PlatformFile.DirectoryExists(*EditorIntermediateFolder))
	{
		if (!PlatformFile.CreateDirectory(*EditorIntermediateFolder))
		{
			UE_LOG(LogFGameDataToolCommandRunner, Warning,
			       TEXT("Create directory '%s' in Project's intermediate directory."), *EditorIntermediateFolder);
			return EditorIntermediateFolder;
		}
		bContentCopied = false;
	}

	if (!bContentCopied)
	{
		bContentCopied = true;
		TArray<FString> FoundFiles;
		PlatformFile.FindFiles(FoundFiles, *PluginContentDirectory, nullptr);
		for (FString SourceFilePath : FoundFiles)
		{
			FString TargetFileName = EditorIntermediateFolder / FPaths::GetCleanFilename(SourceFilePath);
			/*if (PlatformFile.FileExists(*TargetFileName))
			{
				continue;
			}*/
			if (!PlatformFile.CopyFile(*TargetFileName, *SourceFilePath))
			{
				UE_LOG(LogFGameDataToolCommandRunner, Warning,
				       TEXT("Failed to copy file '%s' to Project's intermediate directory."), *SourceFilePath);
			}
		}
	}

	return EditorIntermediateFolder;
}
