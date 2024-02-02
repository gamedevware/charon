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

/**
 * @class FCharonCli
 * @brief Provides a convenient interface for running Charon.exe command line operations.
 *
 * This class encapsulates functionality for creating, updating, deleting, importing, exporting and finding documents
 * within a specified GameData URL, either file-based or server-based. It simplifies interactions
 * with the Charon command line tool, offering methods that return tasks representing the operations.
 * For more detailed documentation of each method, refer to the Charon command line documentation at
 * https://gamedevware.github.io/charon/advanced/command_line.html
 */
class CHARONEDITOR_API FCharonCli final
{
public:
	/**
	 * Creates a document in the specified GameData URL.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNameOrId The schema name or ID of the document.
	 * @param Document The document to create as a shared reference to an FJsonObject.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the create operation. 
	 *         The command, upon completion, provides the created document.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> CreateDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const TSharedRef<FJsonObject>& Document,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * Updates a document in the specified GameData URL.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNameOrId The schema name or ID of the document.
	 * @param Document The document to update as a shared reference to an FJsonObject.
	 * @param Id Optional ID of the document to update if not present in the Document object.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the update operation. 
	 *         The command, upon completion, provides the updated document.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> UpdateDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const TSharedRef<FJsonObject>& Document,
		const FString& Id = FString(),
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

    /**
     * Deletes a document in the specified GameData URL.
     *
     * @param GameDataUrl The URL of the GameData file or server.
     * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
     * @param SchemaNameOrId The schema name or ID of the document.
     * @param Document The document to delete, only the ID is used for deletion.
     * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
     * @return A shared reference to a TCharonCliCommand representing the delete operation. 
     *         The command, upon completion, provides the deleted document.
     */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> DeleteDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const TSharedRef<FJsonObject>& Document,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * Deletes a document in the specified GameData URL by ID.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNameOrId The schema name or ID of the document.
	 * @param Id The ID of the document to delete.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the delete operation. 
	 *         The command, upon completion, provides the deleted document.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> DeleteDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const FString& Id,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * Finds a document in the specified GameData URL by ID.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNameOrId The schema name or ID of the document.
	 * @param Id The ID of the document to find.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the find operation. 
	 *         The command, upon completion, provides the found document.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FindDocument(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& SchemaNameOrId,
		const FString& Id,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Import documents grouped by schema into a specified GameDataUrl file or server.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNamesOrIds Names or IDs of schemas to import from DocumentsBySchemaNameOrId. Can be empty or '*' to import all documents.
	 * @param DocumentsBySchemaNameOrId The documents to be imported, grouped by schema name or ID.
	 * @param ImportMode The mode of import operation, see EImportMode for details.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the import operation.
	 */
	static TSharedRef<TCharonCliCommand<>> Import(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		const TSharedRef<FJsonObject>& DocumentsBySchemaNameOrId,
		EImportMode ImportMode,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Import documents from a file into a specified GameDataUrl file or server.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNamesOrIds Names or IDs of schemas to import. Can be empty or '*' to import all documents.
	 * @param ImportMode The mode of import operation, see EImportMode for details.
	 * @param DocumentsBySchemaNameOrIdFilePath File path to the documents to import.
	 * @param Format The format of the imported documents ('json', 'bson', 'msgpack', 'xml', 'xlsx', 'auto').
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the import operation.
	 */
	static TSharedRef<TCharonCliCommand<>> ImportFromFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		EImportMode ImportMode,
		const FString& DocumentsBySchemaNameOrIdFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Export documents from a GameDataUrl file or server.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNamesOrIds Names or IDs of schemas to export. Can be empty or '*' to export all documents.
	 * @param Properties Names, IDs, types of properties in schemas to include in the export. Can be empty or '*' to export all properties.
	 * @param Languages Language tags (BCP 47) to include in the export of localized text. Can be empty or '*' to export all languages.
	 * @param ExportMode The mode of export operation, see EExportMode for details.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand<TSharedPtr<FJsonObject>> representing the export operation. The command, upon completion, provides the exported documents.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> Export(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TArray<FString>& SchemaNamesOrIds,
		const TArray<FString>& Properties,
		const TArray<FString>& Languages,
		EExportMode ExportMode,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Export documents from a GameDataUrl file or server to a file.
	 *
	 * @param GameDataUrl The URL of the GameData file or server.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param SchemaNamesOrIds Names or IDs of schemas to export. Can be empty or '*' to export all documents.
	 * @param Properties Names, IDs, types of properties in schemas to include in the export. Can be empty or '*' to export all properties.
	 * @param Languages Language tags (BCP 47) to include in the export of localized text. Can be empty or '*' to export all languages.
	 * @param ExportMode The mode of export operation, see EExportMode for details.
	 * @param ExportedDocumentsFilePath File path where the exported documents will be saved.
	 * @param Format The format in which to save the exported data ('json', 'bson', 'msgpack', 'xml', 'xlsx').
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand<TSharedPtr<FJsonObject>> representing the export operation. The command, upon completion, provides the exported documents.
	 */
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

	/**
	 * @brief Compares all documents in two GameData URLs and creates a patch representing the difference.
	 *
	 * @param GameDataUrl1 The first GameData URL for comparison.
	 * @param GameDataUrl2 The second GameData URL for comparison.
	 * @param ApiKey Authentication credentials if the GameData URLs are servers, otherwise empty.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand<TSharedPtr<FJsonObject>> representing the create patch operation. The command, upon completion, provides the patch data.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> CreatePatch(
		const FString& GameDataUrl1,
		const FString& GameDataUrl2,
		const FString& ApiKey,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Applies a patch created by CreatePatch to a specified GameData URL.
	 *
	 * @param GameDataUrl The GameData URL to apply the patch to.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param GameDataPatch The patch document created by CreatePatch.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the apply patch operation.
	 */
	static TSharedRef<TCharonCliCommand<>> ApplyPatch(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TSharedRef<FJsonObject>& GameDataPatch,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Backups game data with all documents and their metadata.
	 *
	 * @param GameDataUrl The GameData URL to backup.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand<TSharedPtr<FJsonObject>> representing the backup operation. The command, upon completion, provides the backup data.
	 */
	static TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> Backup(
		const FString& GameDataUrl,
		const FString& ApiKey,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Backups game data to a file with all documents and their metadata.
	 *
	 * @param GameDataUrl The GameData URL to backup.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param GameDataFilePath File path where the backup will be saved.
	 * @param Format The format for saving data ('json', 'msgpack').
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the backup to file operation. The command, upon completion, provides the backup data.
	 */
	static TSharedRef<TCharonCliCommand<>> BackupToFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& GameDataFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Restores game data with all documents and their metadata.
	 *
	 * @param GameDataUrl The GameData URL to restore.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param GameData Previously backed up data.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the restore operation.
	 */
	static TSharedRef<TCharonCliCommand<>> Restore(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const TSharedRef<FJsonObject>& GameData,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Restores game data from a file with all documents and their metadata.
	 *
	 * @param GameDataUrl The GameData URL to restore.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param GameDataFilePath File path with previously backed up data.
	 * @param Format The format for the backed up data ('json', 'msgpack', 'auto').
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the restore from file operation.
	 */
	static TSharedRef<TCharonCliCommand<>> RestoreFromFile(
		const FString& GameDataUrl,
		const FString& ApiKey,
		const FString& GameDataFilePath,
		const FString& Format = "json",
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Checks all documents in the specified GameData URL and returns a report with any issues.
	 *
	 * @param GameDataUrl The GameData URL to validate.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param ValidationOptions A list of checks to perform during validation, see EValidationOption for details.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the validation operation. The command, upon completion, provides the report of issues.
	 */
	static TSharedRef<TCharonCliCommand<FValidationReport>> Validate(
		const FString& GameDataUrl,
		const FString& ApiKey,
		TArray<EValidationOption> ValidationOptions,
		ECharonLogLevel LogsVerbosity = ECharonLogLevel::Normal
	);

	/**
	 * @brief Generates C++ source code for loading game data from a GameDataUrl into a game's runtime.
	 *
	 * @param GameDataUrl The GameData URL from which to generate source code.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param OutputDirectory Directory to place generated files, preferably empty.
	 * @param DocumentClassName Name for the base class for all documents.
	 * @param GameDataClassName Name for the main class from which all documents are accessible.
	 * @param DefineConstants Additional defines for all generated files.
	 * @param SourceCodeGenerationOptimizations List of enabled optimizations in the generated code, see ESourceCodeGenerationOptimizations for details.
	 * @param SourceCodeIndentation Indentation style for the generated code.
	 * @param SourceCodeLineEndings Line endings for the generated code.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand representing the source code generation operation.
	 */
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

	/**
	 * @brief Dumps T4 code generation templates used to generate source code into a specified directory.
	 *
	 * @param OutputDirectory The directory where the templates will be dumped.
	 * @return A shared reference to a TCharonCliCommand representing the template dumping operation.
	 */
	static TSharedRef<TCharonCliCommand<>> DumpTemplates(
		FString OutputDirectory
	);

	/**
	 * @brief Gets the version number of the Charon.exe executable.
	 *
	 * @return A shared reference to a TCharonCliCommand containing the version number as a string.
	 */
	static TSharedRef<TCharonCliCommand<FString>> GetVersion();

	/**
	 * @brief Gets the version of the Charon.exe executable used to create the specified GameData URL.
	 *
	 * @param GameDataUrl The GameData URL to check.
	 * @param ApiKey Authentication credentials if GameDataUrl is a server, otherwise empty.
	 * @param LogsVerbosity The verbosity level of logs. Defaults to ECharonLogLevel::Normal.
	 * @return A shared reference to a TCharonCliCommand containing the version number as a string.
	 */
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
