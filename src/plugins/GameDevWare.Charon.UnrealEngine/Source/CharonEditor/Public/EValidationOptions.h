#pragma once

enum class CHARONEDITOR_API EValidationOptions
{
	None = 0x0,
	Repair = 0x1 << 0,
	CheckTranslation = 0x1 << 1,
	DeduplicateIds = 0x1 << 2,
	RepairRequiredWithDefaultValue = 0x1 << 3,
	EraseInvalidValue = 0x1 << 4,
	CheckRequirements = 0x1 << 5,
	CheckFormat = 0x1 << 6,
	CheckUniqueness = 0x1 << 7,
	CheckReferences = 0x1 << 8,
	CheckSpecification = 0x1 << 9,
	CheckConstraints = 0x1 << 10,
		
	AllIntegrityChecks = CheckRequirements | CheckFormat | CheckUniqueness | CheckReferences | CheckSpecification | CheckConstraints,
	Default = Repair | DeduplicateIds | RepairRequiredWithDefaultValue | EraseInvalidValue | CheckRequirements | CheckFormat | CheckUniqueness | CheckReferences | CheckConstraints,
	DefaultForCreate = Repair | RepairRequiredWithDefaultValue | AllIntegrityChecks,
	DefaultForUpdate = DefaultForCreate,
	DefaultForBulkChange = Repair | DeduplicateIds | RepairRequiredWithDefaultValue,
	DefaultForInternalChange = Repair | DeduplicateIds | RepairRequiredWithDefaultValue,
	DefaultForBackgroundValidation = AllIntegrityChecks | CheckTranslation
};