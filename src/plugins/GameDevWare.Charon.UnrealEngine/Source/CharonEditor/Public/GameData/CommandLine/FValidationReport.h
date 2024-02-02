#pragma once
#include "FDocumentValidationRecord.h"

#include "FValidationReport.generated.h"

USTRUCT()
/**
 * @struct FValidationReport
 * @brief Represents the result of the validation process performed by FCharonCli::Validate().
 *
 * This struct contains the details of the validation result, including a list of issues found in documents
 * and hashes that represent the state of the game data and metadata after validation.
 */
struct CHARONEDITOR_API FValidationReport
{
	GENERATED_BODY();

	/**
	 * @brief List of issues found in the documents during validation.
	 *
	 * Each record in this array represents a specific issue or concern identified in an individual
	 * document as a result of the validation process.
	 */
	UPROPERTY(VisibleAnywhere, Category="Game Data")
	TArray<FDocumentValidationRecord> Records;

	/**
	 * @brief Hash of the metadata after validation.
	 *
	 * This string represents a hash of the metadata post-validation, which can be used to verify
	 * the integrity or track changes in the metadata.
	 */
	UPROPERTY(VisibleAnywhere, Category="Game Data")
	FString MetadataHash;
    
	/**
	 * @brief Hash of the game data after validation.
	 *
	 * Similar to MetadataHash, this string represents a hash of the game data after the validation
	 * process. It provides a means to verify integrity or track revisions in the game data.
	 */
	UPROPERTY(VisibleAnywhere, Category="Game Data")
	FString RevisionHash;
};