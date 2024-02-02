#pragma once

#include "FDocumentValidationError.h"

#include "FDocumentValidationRecord.generated.h"

USTRUCT()
/**
 * @struct FDocumentValidationRecord
 * @brief Represents an individual record of a validated document in FValidationReport, particularly those with identified issues.
 *
 * This struct provides details about a specific document that was validated, including its identity and any validation errors that were found.
 */
struct CHARONEDITOR_API FDocumentValidationRecord
{
	GENERATED_BODY();

	/**
	 * @brief The ID of the document.
	 */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Id;

	/**
	 * @brief The name of the schema for the document.
	 */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString SchemaName;
    
	/**
	 * @brief The ID of the schema for the document.
	 */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString SchemaId;

	/**
	 * @brief List of errors found in the document during validation.
	 */
	UPROPERTY(VisibleAnywhere, Category="Change")
	TArray<FDocumentValidationError> Errors;
};