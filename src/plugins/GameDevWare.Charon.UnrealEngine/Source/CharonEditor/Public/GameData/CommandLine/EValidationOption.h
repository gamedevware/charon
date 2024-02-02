#pragma once

#include "EValidationOption.generated.h"

UENUM()
/**
 * @enum EValidationOption
 * @brief Specifies the types of validation checks performed during the FCharonCli::Validate() operation.
 *
 * This enumeration lists various checks and operations that can be performed as part of the validation
 * of documents.
 */
enum class EValidationOption
{
    /**
     * @brief Performs repairs on documents if possible.
     *
     * When selected, this option allows the validation process to make modifications to the documents
     * in order to fix identified issues. Without this option, no changes will be made to the documents.
     */
    Repair = 0,

    /**
     * @brief Checks if translations for all required languages are provided.
     *
     * This option verifies that each document contains translations in all the languages that are
     * specified in Project's Settings.
     */
    CheckTranslation = 1,

    /**
     * @brief Attempts to fix duplicate IDs in documents, works only with the Repair option.
     *
     * This check identifies and resolves instances where multiple documents have the same ID.
     * It requires the Repair option to be enabled in order to make changes.
     */
    DeduplicateIds = 2,

    /**
     * @brief Repairs missing values with default ones, works only with the Repair option.
     *
     * When enabled, this check finds missing values in documents and fills them with default values,
     * if available. This option is dependent on the Repair option being active.
     */
    RepairRequiredWithDefaultValue = 3,

    /**
     * @brief Erases invalid values, with the option to replace with defaults, works only with Repair.
     *
     * This check removes any values that are deemed invalid. If the RepairRequiredWithDefaultValue
     * option is also specified, these invalid values are replaced with defaults.
     */
    EraseInvalidValue = 4,

    /**
     * @brief Checks if required values are present in documents.
     *
     * This validation step ensures that all mandatory values or fields in the documents are provided.
     */
    CheckRequirements = 5,

    /**
     * @brief Verifies that values match the proper data type and format.
     *
     * This check ensures that each value in the documents adheres to the expected data type and format,
     * maintaining data integrity and consistency.
     */
    CheckFormat = 6,

    /**
     * @brief Ensures that values marked as unique are indeed unique within the documents.
     *
     * This option checks for the uniqueness of values that are supposed to be unique, such as IDs
     * or custom 'Unique' properties.
     */
    CheckUniqueness = 7,

    /**
     * @brief Validates the correctness of references to other documents.
     *
     * This check ensures that all references to other documents are valid and correctly specified.
     */
    CheckReferences = 8,

    /**
     * @brief Checks the correctness of complex data types in metadata.
     *
     * This validation step is concerned with verifying that complex data types (Pick List, Multi-Pick List, Formula ...) are set up.
     */
    CheckSpecification = 9,

    /**
     * @brief Verifies various constraints like text length, collection size, and number ranges.
     *
     * This check ensures that all specified constraints, such as the length of text fields,
     * sizes of collections, and ranges of numbers, are adhered to in the documents.
     */
    CheckConstraints = 10,
};