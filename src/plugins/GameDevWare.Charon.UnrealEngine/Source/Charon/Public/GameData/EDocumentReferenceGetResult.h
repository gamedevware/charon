
#pragma once

UENUM(BlueprintType)
/*
 * List of possible branches of GetXXXDocument function
 */
enum class EDocumentReferenceGetResult : uint8
{
	/*
	 * Document is not found OR document type is not that requested.
	 */
	NotFound,
	/*
	 * Document is found.
	 */
	Found
};
