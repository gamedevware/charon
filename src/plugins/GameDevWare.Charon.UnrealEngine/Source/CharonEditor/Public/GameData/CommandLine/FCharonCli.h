#pragma once

#include "ECharonLogLevel.h"
#include "EExportMode.h"
#include "EImportMode.h"
#include "ESourceCodeGenerationOptimizations.h"
#include "ESourceCodeIndentation.h"
#include "ESourceCodeLineEndings.h"
#include "EValidationOption.h"
#include "FValidationReport.h"
#include "TCharonCliCommand.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFCharonCli, Log, All);

class CHARONEDITOR_API FCharonCli final
{
public:
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> CreateDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const TSharedRef<FJsonObject>& Document,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> UpdateDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const TSharedRef<FJsonObject>& Document,
		const FString& Id = FString(),
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> DeleteDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const TSharedRef<FJsonObject>& Document,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> DeleteDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const FString& Id,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FindDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const FString& Id,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> Import(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		const TSharedRef<FJsonObject>& DocumentsBySchemaNameOrId,
		EImportMode ImportMode,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> ImportFromFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		EImportMode ImportMode,
		const FString& DocumentsBySchemaNameOrIdFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> Export(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		const TArray<FString>& Properties,
		const TArray<FString>& Languages,
		EExportMode ExportMode,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> ExportToFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		const TArray<FString>& Properties,
		const TArray<FString>& Languages,
		EExportMode ExportMode,
		const FString& ExportedDocumentsFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);
	
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> CreatePatch(
		const FString& GameDataUrl1,
		const FString& GameDataUrl2,
		const FString& ApiKey,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);
	
	static TSharedRef<TCharonCliCommand<>> ApplyPatch(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TSharedRef<FJsonObject>& GameDataPatch,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);
	
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> Backup(
		const FString& GameDataUrl,
		const FString& ApiKey,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> BackupToFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& GameDataFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);
	
	static TSharedRef<TCharonCliCommand<>> Restore(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TSharedRef<FJsonObject>& GameData,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> RestoreFromFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& GameDataFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);
	
	static TSharedRef<TCharonCliCommand<FValidationReport>> Validate(
		const FString& GameDataUrl,
		const FString& ApiKey,
		TArray<EValidationOption> ValidationOptions,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> GenerateUnrealEngineSourceCode(
		const FString& GameDataUrl,
		const FString& ApiKey,
		FString OutputDirectory,
		FString DocumentClassName = "UDocument",
		FString GameDataClassName = "UGameData",
		FString DefineConstants = FString(),
		TArray<ESourceCodeGenerationOptimizations> SourceCodeGenerationOptimizations = TArray<ESourceCodeGenerationOptimizations>(),
		ESourceCodeIndentation SourceCodeIndentation = ESourceCodeIndentation::Tabs,
#if WIN32
		ESourceCodeLineEndings SourceCodeLineEndings = ESourceCodeLineEndings::Windows,
#else
		ESourceCodeLineEndings SourceCodeLineEndings = ESourceCodeLineEndings::Unix,
#endif
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	static TSharedRef<TCharonCliCommand<>> DumpTemplates(
		FString OutputDirectory
	);

	static TSharedRef<TCharonCliCommand<FString>> GetVersion();
	
	static TSharedRef<TCharonCliCommand<FString>> GetGameDataVersion(
		const FString& GameDataUrl,
		const FString& ApiKey,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

private:
	static FString GetLogOptions(ECharonLogLevel LogsVerbosity);
	static FString WriteJsonToTempFile(const TSharedRef<FJsonObject>& JsonObject);
	static FString PrepareTempOutputFile(const FString& Extension = TEXT(".tmp"));
};
