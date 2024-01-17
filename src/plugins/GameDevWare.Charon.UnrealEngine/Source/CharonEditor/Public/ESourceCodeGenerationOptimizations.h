#pragma once

#include "ESourceCodeGenerationOptimizations.generated.h"

UENUM()
enum class ESourceCodeGenerationOptimizations
{
	EagerReferenceResolution = 0,
	RawReferences = 1,
	RawLocalizedStrings = 2,
	DisableStringPooling = 3,
	DisableJsonSerialization = 4,
	DisableMessagePackSerialization = 5,
	DisablePatching = 6,
	DisableFormulaCompilation = 7,
};
