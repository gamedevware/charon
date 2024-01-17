#pragma once
#include "FDocumentValidationRecord.h"

#include "FValidationReport.generated.h"

USTRUCT()
struct CHARONEDITOR_API FValidationReport
{
	GENERATED_BODY();
	
	UPROPERTY(VisibleAnywhere, Category="Game Data")
	TArray<FDocumentValidationRecord> Records;

	/** Hash of metadata after import operation. */
	UPROPERTY(VisibleAnywhere, Category="Game Data")
	FString MetadataHash;
	
	/** Hash of game data after import operation. */
	UPROPERTY(VisibleAnywhere, Category="Game Data")
	FString RevisionHash;
};