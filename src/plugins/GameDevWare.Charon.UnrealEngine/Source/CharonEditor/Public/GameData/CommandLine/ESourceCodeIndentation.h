#pragma once

#include "ESourceCodeIndentation.generated.h"

UENUM()
/**
 * @enum ESourceCodeIndentation
 * @brief Defines indentation styles for the generated C++ source code in FCharonCli::GenerateUnrealEngineSourceCode().
 */
enum class ESourceCodeIndentation
{
	/**
	 * @brief Uses tabs for indentation in the generated source code.
	 */
	Tabs = 0,

	/**
	 * @brief Uses two spaces for indentation in the generated source code.
	 */
	TwoSpaces = 1,

	/**
	 * @brief Uses four spaces for indentation in the generated source code.
	 */
	FourSpaces = 2,
};