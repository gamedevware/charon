#pragma once

#include "GameData/CommandLine/FCharonCli.h"

#include "GameData/CommandLine/FGameDataToolCommandRunner.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY(LogFCharonCli);

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::CreateDocument(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const FString& SchemaNameOrId,
	const TSharedRef<FJsonObject>& Document)
{
	const FString TempInputFile = WriteJsonToTempFile(Document);
		const FString Params = FString::Format(TEXT("DATA CREATE \"{0}\" --input \"{1}\" --inputFormat json --schema \"{2}\" --output out --outputFormat json"), {
		GameDataUrl,
		TempInputFile,
		SchemaNameOrId
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	CommandRunner->AttachTemporaryFile(TempInputFile);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::UpdateDocument(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const FString& SchemaNameOrId,
	const TSharedRef<FJsonObject>& Document, 
	const FString& Id)
{
	const FString TempInputFile = WriteJsonToTempFile(Document);
	const FString Params = FString::Format(TEXT("DATA UPDATE \"{0}\" --input \"{1}\" --inputFormat json --schema \"{2}\" --id \"{3}\" --output out --outputFormat json"), {
		GameDataUrl,
		TempInputFile,
		SchemaNameOrId,
		Id
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	CommandRunner->AttachTemporaryFile(TempInputFile);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::DeleteDocument(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const FString& SchemaNameOrId,
	const TSharedRef<FJsonObject>& Document)
{
	const FString TempInputFile = WriteJsonToTempFile(Document);
	const FString Params = FString::Format(TEXT("DATA DELETE \"{0}\" --input \"{1}\" --inputFormat json --schema \"{2}\" --output out --outputFormat json"), {
		GameDataUrl,
		TempInputFile,
		SchemaNameOrId
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	CommandRunner->AttachTemporaryFile(TempInputFile);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::DeleteDocument(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const FString& SchemaNameOrId,
	const FString& Id)
{
	const FString Params = FString::Format(TEXT("DATA DELETE \"{0}\" --schema \"{1}\" --id \"{2}\" --output out --outputFormat json"), {
		GameDataUrl,
		SchemaNameOrId,
		Id
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::FindDocument(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const FString& SchemaNameOrId,
	const FString& Id)
{
	const FString Params = FString::Format(TEXT("DATA FIND \"{0}\" --schema \"{1}\" --id \"{2}\" --output out --outputFormat json"), {
		GameDataUrl,
		SchemaNameOrId,
		Id
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::Import(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const TArray<FString>& SchemaNamesOrIds,
	const TSharedRef<FJsonObject>& DocumentsBySchemaNameOrId,
	EImportMode ImportMode)
{
	FString ImportModeName;
	switch (ImportMode)
	{
	default:
	case EImportMode::CreateAndUpdate:
		ImportModeName = TEXT("CreateAndUpdate");
		break;
	case EImportMode::Create:
		ImportModeName = TEXT("Create");
		break;
	case EImportMode::Update:
		ImportModeName = TEXT("Update");
		break;
	case EImportMode::SafeUpdate:
		ImportModeName = TEXT("SafeUpdate");
		break;
	case EImportMode::Replace:
		ImportModeName = TEXT("Replace");
		break;
	case EImportMode::Delete:
		ImportModeName = TEXT("Delete");
		break;
	}
	const FString TempInputFile = WriteJsonToTempFile(DocumentsBySchemaNameOrId);
	const FString Params = FString::Format(TEXT("DATA IMPORT \"{0}\" --input \"{1}\" --inputFormat json --schemas {2} --mode {3}"), {
		GameDataUrl,
		TempInputFile,
		SchemaNamesOrIds.IsEmpty() ? "*" : FString::Join(SchemaNamesOrIds, TEXT(" ")),
		ImportModeName
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	CommandRunner->AttachTemporaryFile(TempInputFile);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::ImportFromFile(const FString& GameDataUrl, const FString& ApiKey,
	const TArray<FString>& SchemaNamesOrIds, EImportMode ImportMode, const FString& DocumentsBySchemaNameOrIdFilePath,
	const FString& Format)
{
	FString ImportModeName;
	switch (ImportMode)
	{
	default:
	case EImportMode::CreateAndUpdate:
		ImportModeName = TEXT("CreateAndUpdate");
		break;
	case EImportMode::Create:
		ImportModeName = TEXT("Create");
		break;
	case EImportMode::Update:
		ImportModeName = TEXT("Update");
		break;
	case EImportMode::SafeUpdate:
		ImportModeName = TEXT("SafeUpdate");
		break;
	case EImportMode::Replace:
		ImportModeName = TEXT("Replace");
		break;
	case EImportMode::Delete:
		ImportModeName = TEXT("Delete");
		break;
	}
	const FString Params = FString::Format(TEXT("DATA IMPORT \"{0}\" --input \"{1}\" --inputFormat {4} --schemas {2} --mode {3}"), {
		GameDataUrl,
		DocumentsBySchemaNameOrIdFilePath,
		SchemaNamesOrIds.IsEmpty() ? "*" : FString::Join(SchemaNamesOrIds, TEXT(" ")),
		ImportModeName,
		Format
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::Export(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const TArray<FString>& SchemaNamesOrIds,
	const TArray<FString>& Properties,
	const TArray<FString>& Languages,
	EExportMode ExportMode)
{
	FString ExportModeName;
	switch (ExportMode)
	{
	default:
	case EExportMode::Default:
		ExportModeName = TEXT("Default");
		break;
	case EExportMode::Publication:
		ExportModeName = TEXT("Publication");
		break;
	case EExportMode::Localization:
		ExportModeName = TEXT("Localization");
		break;
	case EExportMode::Extraction:
		ExportModeName = TEXT("Extraction");
		break;
	}
	
	const FString Params = FString::Format(TEXT("DATA EXPORT \"{0}\" --output out --outputFormat json --schemas {1} --properties {2} --languages {3} --mode {4}"), {
		GameDataUrl,
		SchemaNamesOrIds.IsEmpty() ? "*" : FString::Join(SchemaNamesOrIds, TEXT(" ")),
		Properties.IsEmpty() ? "*" : FString::Join(Properties, TEXT(" ")),
		Languages.IsEmpty() ? "*" : FString::Join(Languages, TEXT(" ")),
		ExportModeName
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::ExportToFile(const FString& GameDataUrl, const FString& ApiKey,
	const TArray<FString>& SchemaNamesOrIds, const TArray<FString>& Properties, const TArray<FString>& Languages,
	EExportMode ExportMode, const FString& ExportedDocumentsFilePath, const FString& Format)
{
	FString ExportModeName;
	switch (ExportMode)
	{
	default:
	case EExportMode::Default:
		ExportModeName = TEXT("Default");
		break;
	case EExportMode::Publication:
		ExportModeName = TEXT("Publication");
		break;
	case EExportMode::Localization:
		ExportModeName = TEXT("Localization");
		break;
	case EExportMode::Extraction:
		ExportModeName = TEXT("Extraction");
		break;
	}
	
	const FString Params = FString::Format(TEXT("DATA EXPORT \"{0}\" --output \"{5}\" --outputFormat {6} --schemas {1} --properties {2} --languages {3} --mode {4}"), {
		GameDataUrl,
		SchemaNamesOrIds.IsEmpty() ? "*" : FString::Join(SchemaNamesOrIds, TEXT(" ")),
		Properties.IsEmpty() ? "*" : FString::Join(Properties, TEXT(" ")),
		Languages.IsEmpty() ? "*" : FString::Join(Languages, TEXT(" ")),
		ExportModeName,
		ExportedDocumentsFilePath,
		Format
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::CreatePatch(
	const FString& GameDataUrl1,
	const FString& GameDataUrl2,
	const FString& ApiKey
)
{
	const FString Params = FString::Format(TEXT("DATA CREATEPATCH \"{0}\" \"{1}\" --output out --outputFormat json"), {
		GameDataUrl1,
		GameDataUrl2
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::ApplyPatch(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const TSharedRef<FJsonObject>& GameDataPatch)
{
	const FString TempInputFile = WriteJsonToTempFile(GameDataPatch);
	const FString Params = FString::Format(TEXT("DATA APPLYPATCH \"{0}\" --input \"{1}\" --inputFormat json"), {
		GameDataUrl,
		TempInputFile
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	CommandRunner->AttachTemporaryFile(TempInputFile);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<TSharedPtr<FJsonObject>>> FCharonCli::Backup(
	const FString& GameDataUrl,
	const FString& ApiKey)
{
	const FString Params = FString::Format(TEXT("DATA BACKUP \"{0}\" --output out --outputFormat json"), {
		GameDataUrl
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<TSharedPtr<FJsonObject>>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::BackupToFile(const FString& GameDataUrl, const FString& ApiKey,
	const FString& GameDataFilePath, const FString& Format)
{
	const FString Params = FString::Format(TEXT("DATA BACKUP \"{0}\" --output \"{1}\" --outputFormat {2}"), {
		GameDataUrl,
		GameDataFilePath,
		Format
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::Restore(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const TSharedRef<FJsonObject>& GameData)
{
	const FString TempInputFile = WriteJsonToTempFile(GameData);
	const FString Params = FString::Format(TEXT("DATA RESTORE \"{0}\" --input \"{1}\" --inputFormat json"), {
		GameDataUrl,
		TempInputFile
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	CommandRunner->AttachTemporaryFile(TempInputFile);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::RestoreFromFile(
	const FString& GameDataUrl,
	const FString& ApiKey,
	const FString& GameDataFilePath,
		const FString& Format)
{
	const FString Params = FString::Format(TEXT("DATA RESTORE \"{0}\" --input \"{1}\" --inputFormat {2}"), {
		GameDataUrl,
		GameDataFilePath,
		Format
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<FValidationReport>> FCharonCli::Validate(
	const FString& GameDataUrl,
	const FString& ApiKey,
	TArray<EValidationOptions> ValidationOptions)
{
	TArray<FString> ValidationOptionNames;
	for (const auto Option : ValidationOptions)
	{
		switch (Option)
		{
			default:
			case EValidationOptions::None: break;
			case EValidationOptions::Repair: ValidationOptionNames.Add(TEXT("Repair")); break;
			case EValidationOptions::CheckTranslation: ValidationOptionNames.Add(TEXT("CheckTranslation")); break;
			case EValidationOptions::DeduplicateIds: ValidationOptionNames.Add(TEXT("DeduplicateIds")); break;
			case EValidationOptions::RepairRequiredWithDefaultValue: ValidationOptionNames.Add(TEXT("RepairRequiredWithDefaultValue")); break;
			case EValidationOptions::EraseInvalidValue: ValidationOptionNames.Add(TEXT("EraseInvalidValue")); break;
			case EValidationOptions::CheckRequirements: ValidationOptionNames.Add(TEXT("CheckRequirements")); break;
			case EValidationOptions::CheckFormat: ValidationOptionNames.Add(TEXT("CheckFormat")); break;
			case EValidationOptions::CheckUniqueness: ValidationOptionNames.Add(TEXT("CheckUniqueness")); break;
			case EValidationOptions::CheckReferences: ValidationOptionNames.Add(TEXT("CheckReferences")); break;
			case EValidationOptions::CheckSpecification: ValidationOptionNames.Add(TEXT("CheckSpecification")); break;
			case EValidationOptions::CheckConstraints: ValidationOptionNames.Add(TEXT("CheckConstraints")); break;
		}
	}
	
	const FString Params = FString::Format(TEXT("DATA VALIDATE \"{0}\" --validationOptions {1} --output out --outputFormat json"), {
		GameDataUrl,
		ValidationOptionNames.IsEmpty() ? "None" : FString::Join(ValidationOptionNames, TEXT(" ")),
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<FValidationReport>>(CommandRunner);
}


TSharedRef<TCharonCliCommand<>> FCharonCli::GenerateUnrealEngineSourceCode(
	const FString& GameDataUrl,
	const FString& ApiKey,
	FString OutputDirectory,
	FString DocumentClassName,
	FString GameDataClassName,
	FString DefineConstants,
	TArray<ESourceCodeGenerationOptimizations> SourceCodeGenerationOptimizations,
	ESourceCodeIndentation SourceCodeIndentation,
	ESourceCodeLineEndings SourceCodeLineEndings)
{
	FString SourceCodeIndentationName;
	switch (SourceCodeIndentation)
	{
		default:
		case ESourceCodeIndentation::Tabs: SourceCodeIndentationName = TEXT("Tabs"); break;
		case ESourceCodeIndentation::TwoSpaces: SourceCodeIndentationName = TEXT("TwoSpaces"); break;
		case ESourceCodeIndentation::FourSpaces: SourceCodeIndentationName = TEXT("FourSpaces"); break;
	}

	FString SourceCodeLineEndingsName;
	switch (SourceCodeLineEndings)
	{
		default:
		case ESourceCodeLineEndings::Windows: SourceCodeLineEndingsName = TEXT("Windows"); break;
		case ESourceCodeLineEndings::Unix: SourceCodeLineEndingsName = TEXT("Unix"); break;
	}

	TArray<FString> SourceCodeGenerationOptimizationNames;
	for (const auto Optimization : SourceCodeGenerationOptimizations)
	{
		switch (Optimization)
		{
			default: break;
			case ESourceCodeGenerationOptimizations::EagerReferenceResolution: SourceCodeGenerationOptimizationNames.Add(TEXT("EagerReferenceResolution")); break;
			case ESourceCodeGenerationOptimizations::RawReferences:	SourceCodeGenerationOptimizationNames.Add(TEXT("RawReferences")); break;
			case ESourceCodeGenerationOptimizations::RawLocalizedStrings: SourceCodeGenerationOptimizationNames.Add(TEXT("RawLocalizedStrings")); break;
			case ESourceCodeGenerationOptimizations::DisableStringPooling: SourceCodeGenerationOptimizationNames.Add(TEXT("DisableStringPooling")); break;
			case ESourceCodeGenerationOptimizations::DisableJsonSerialization: SourceCodeGenerationOptimizationNames.Add(TEXT("DisableJsonSerialization")); break;
			case ESourceCodeGenerationOptimizations::DisableMessagePackSerialization: SourceCodeGenerationOptimizationNames.Add(TEXT("DisableMessagePackSerialization")); break;
			case ESourceCodeGenerationOptimizations::DisablePatching: SourceCodeGenerationOptimizationNames.Add(TEXT("DisablePatching")); break;
			case ESourceCodeGenerationOptimizations::DisableFormulaCompilation: SourceCodeGenerationOptimizationNames.Add(TEXT("DisableFormulaCompilation")); break;
		}
	}
	
	const FString Params = FString::Format(TEXT("GENERATE UECPPCODE \"{0}\" --outputDirectory \"{1}\" --documentClassName \"{2}\" --gameDataClassName \"{3}\" --defineConstants \"{4}\" --indentation \"{5}\" --lineEndings \"{6}\" --splitFiles --optimizations {7}"), {
		GameDataUrl,
		OutputDirectory,
		DocumentClassName,
		GameDataClassName,
		DefineConstants,
		SourceCodeIndentationName,
		SourceCodeLineEndingsName,
		SourceCodeGenerationOptimizationNames.IsEmpty() ? "" : FString::Join(SourceCodeGenerationOptimizationNames, TEXT(" ")),
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<>> FCharonCli::DumpTemplates(FString OutputDirectory)
{
	const FString Params = FString::Format(TEXT("GENERATE TEMPLATES --outputDirectory \"{0}\""), {
		OutputDirectory
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	return MakeShared<TCharonCliCommand<>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<FString>> FCharonCli::GetVersion()
{
	const FString Params = TEXT("VERSION");
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	return MakeShared<TCharonCliCommand<FString>>(CommandRunner);
}

TSharedRef<TCharonCliCommand<FString>> FCharonCli::GetGameDataVersion(const FString& GameDataUrl, const FString& ApiKey)
{
	const FString Params = FString::Format(TEXT("DATA VERSION \"{0}\""), {
		GameDataUrl
	});
	
	const TSharedRef<FGameDataToolCommandRunner> CommandRunner = MakeShared<FGameDataToolCommandRunner>(Params);
	CommandRunner->SetApiKey(ApiKey);
	return MakeShared<TCharonCliCommand<FString>>(CommandRunner);
}

FString FCharonCli::WriteJsonToTempFile(const TSharedRef<FJsonObject>& JsonObject)
{
	IFileManager& FileManager = IFileManager::Get();
	const FString TempFilePath = FPaths::CreateTempFilename(FPlatformProcess::UserTempDir(), TEXT(""), TEXT(".json"));
	FArchive* TempFileStream = FileManager.CreateFileWriter(*TempFilePath, EFileWrite::FILEWRITE_None);
	const auto JsonWriter = TJsonWriterFactory<UTF8CHAR>::Create(TempFileStream);
	FJsonSerializer::Serialize(JsonObject, JsonWriter, true);

	return TempFilePath;
}
