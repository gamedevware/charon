#pragma once

#include "ESourceCodeGenerationOptimizations.generated.h"

UENUM()
/**
 * @enum ESourceCodeGenerationOptimizations
 * @brief Specifies optimization options in the generated C++ source code by FCharonCli::GenerateUnrealEngineSourceCode().
 *
 * This enumeration lists various optimization flags that can be used to control the generated
 * C++ source code for game data loading. These options allow for fine-tuning the balance between
 * performance, memory usage, and the complexity of the generated code.
 */
enum class ESourceCodeGenerationOptimizations
{
    /**
     * @brief Eagerly resolves and validates all references in loaded documents.
     *
     * When enabled, this optimization ensures that all references in documents are resolved and validated
     * during loading. This comes with a performance cost but guarantees the validity of references.
     */
    EagerReferenceResolution = 0,

    /**
     * @brief Opts for raw references without generating helper methods for referenced documents.
     *
     * With this optimization, the generated code will not include helper methods for accessing
     * referenced documents, keeping only accessors that work with raw references.
     */
    RawReferences = 1,

    /**
     * @brief Avoids generating helper methods for localized strings, keeping only raw accessors.
     *
     * This optimization eliminates helper methods for accessing localized text, instead providing
     * accessors that deal directly with lists of localized texts.
     */
    RawLocalizedStrings = 2,

    /**
     * @brief Disables string pooling during game data loading.
     *
     * Turning off string pooling can yield a minor performance improvement at the cost of increased
     * memory usage, as it avoids reusing short strings.
     */
    DisableStringPooling = 3,

    /**
     * @brief Disables generation of code for loading game data from JSON formatted files.
     *
     * This optimization omits code related to JSON serialization, useful when JSON formatted
     * game data is not used.
     */
    DisableJsonSerialization = 4,

    /**
     * @brief Disables generation of code for loading game data from Message Pack formatted files.
     *
     * Similar to DisableJsonSerialization, this option removes code related to loading data
     * from Message Pack formatted files.
     */
    DisableMessagePackSerialization = 5,

    /**
     * @brief Disables generation of code related to applying patches during game data loading.
     *
     * This removes a significant portion of code that is mainly used for modding support,
     * where patches are applied to game data at runtime.
     */
    DisablePatching = 6,

    /**
     * @brief Disables ahead-of-time compilation of formulas, opting to interpret them instead.
     *
     * This optimization changes how formulas are handled, moving away from compiling them
     * from text into machine or JIT code, to interpreting them at runtime.
     */
    DisableFormulaCompilation = 7,
};
