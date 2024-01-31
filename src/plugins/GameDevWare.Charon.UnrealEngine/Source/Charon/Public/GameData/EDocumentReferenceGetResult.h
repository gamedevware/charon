
#pragma once

/*
 * List of possible branches of GetXXXDocument function
 */
UENUM(BlueprintType)
enum class EDocumentReferenceGetResult : uint8
{
	NotFound,
	Found
};
