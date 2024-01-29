#pragma once

#include "EValidationOption.generated.h"

UENUM()
enum class EValidationOption
{
	Repair = 0,
	CheckTranslation = 1,
	DeduplicateIds = 2,
	RepairRequiredWithDefaultValue = 3,
	EraseInvalidValue = 4,
	CheckRequirements = 5,
	CheckFormat = 6,
	CheckUniqueness = 7,
	CheckReferences = 8,
	CheckSpecification = 9,
	CheckConstraints = 10,
};