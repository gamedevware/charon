#pragma once

#include "ECharonLogLevel.generated.h"

UENUM()
/**
 * @enum ECharonLogLevel
 * @brief Represents the logging level during the execution of FCharonCli operations.
 *
 * This enumeration defines the different levels of logging that can be set for the operations
 * performed by FCharonCli. It allows control over the amount and detail of log information
 * produced during these operations.
 */
enum class ECharonLogLevel
{
	/**
	 * @brief Indicates no logging, except for fatal errors.
	 *
	 * When set to None, the logging system will only output messages that are classified as fatal errors,
	 * which are typically those that cause the operation to terminate unexpectedly.
	 */
	None,

	/**
	 * @brief Indicates normal logging level with informational messages.
	 *
	 * In this mode, the logging system outputs regular information messages. This is typically used for
	 * standard operational logging where routine information is logged.
	 */
	Normal,

	/**
	 * @brief Indicates verbose logging with detailed messages.
	 *
	 * When set to Verbose, the logging system produces a detailed log output, including debug messages.
	 * This level is typically used for troubleshooting and debugging purposes, as it provides in-depth
	 * details about the operation's progress and state.
	 */
	Verbose,
};