#pragma once

#include "FDocumentValidationError.generated.h"

USTRUCT()
/**
 * @struct FDocumentValidationError
 * @brief Represents a specific error found in a document during the validation process.
 */
struct CHARONEDITOR_API FDocumentValidationError
{
	GENERATED_BODY();

	/**
	 * @brief Path to the property where the error occurred.
	 *
	 * The format of this path is a JSON Pointer as defined in RFC 6901 (https://datatracker.ietf.org/doc/html/rfc6901).
	 * It provides a precise location within the document where the validation error was identified. 
	 */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Path;

	/**
	 * @brief A message describing the nature of the error.
	 *
	 * This string provides a human-readable description of the validation error, offering insight into
	 * what aspect of the document did not meet the validation criteria.
	 */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Message;

	/**
	 * @brief A unique code identifying the type of error.
	 *
	 * This code serves as an identifier for the specific type of validation error encountered, which can
	 * be used for categorizing, reporting, or further processing of the error.
	 */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Code;
};