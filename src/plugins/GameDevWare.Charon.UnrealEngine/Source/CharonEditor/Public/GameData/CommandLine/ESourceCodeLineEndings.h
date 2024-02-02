#pragma once

#include "ESourceCodeLineEndings.generated.h"

UENUM()
/**
 * @enum ESourceCodeLineEndings
 * @brief Defines the style of line endings for the generated C++ source code in FCharonCli::GenerateUnrealEngineSourceCode().
 */
enum class ESourceCodeLineEndings
{
	/**
	 * @brief Uses Windows-style line endings (CRLF) in the generated source code.
	 */
	Windows = 0,

	/**
	 * @brief Uses Unix-style line endings (LF) in the generated source code.
	 */
	Unix = 1,
};