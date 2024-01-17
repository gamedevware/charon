#pragma once

#include "EImportReportDocumentChangeStatus.h"
#include "FDocumentValidationError.h"
#include "FImportReportDocumentChange.generated.h"

USTRUCT()
struct CHARONEDITOR_API FImportReportDocumentChange
{
	GENERATED_BODY();
	
	/** Id of the changed document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString Id;

	/** New id of the newly created document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString NewId;

	/** Schema name of changed document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString SchemaName;
	
	/** Schema name of changed document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString SchemaId;

	/** Status of change for document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	EImportReportDocumentChangeStatus Status = EImportReportDocumentChangeStatus::Skipped;

	/** Reason or informational comment for a change status. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString Comment;

	/** List of errors happened during attempt to apply change. Could be empty even if EImportReportDocumentChangeStatus::Error */
	UPROPERTY(VisibleAnywhere, Category="Change")
	TArray<FDocumentValidationError> Errors;
};

