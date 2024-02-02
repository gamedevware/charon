#pragma once

/**
 * @enum EGameDataEditorLaunchStatus
 * @brief Represents the status of launching the Charon.exe executable in interactive mode for data editing purposes.
 *
 * This enumeration defines the various statuses that can occur when attempting to launch
 * the Charon.exe executable through the FCharonEditorProcessRunner. It provides detailed
 * information about the success or failure of the launch process.
 */
enum class EGameDataEditorLaunchStatus
{
	/**
	 * @brief Indicates that the process failed to start.
	 *
	 * This status means that the Charon.exe process could not be started. Further details
	 * about the failure can be found in the logs located in the project's /Intermediate/Charon/logs folder.
	 */
	Failed,

	/**
	 * @brief Indicates that the startup script is missing in the plugin's resources.
	 *
	 * This status is returned when the required startup script for the Charon.exe process
	 * is not found, suggesting possible corruption or incomplete installation of the plugin data.
	 */
	MissingRunScript,

	/**
	 * @brief Indicates a timeout during the start process.
	 *
	 * This status is returned when the Charon.exe process fails to start within the expected time frame.
	 * Additional details can be found in the logs in the project's /Intermediate/Charon/logs folder.
	 */
	Timeout,

	/**
	 * @brief Indicates that the launch was cancelled.
	 *
	 * This status is used when the launch process is actively cancelled by calling FCharonEditorProcessRunner::Stop().
	 * It signifies an intentional termination of the process launch.
	 */
	Cancelled,

	/**
	 * @brief Indicates that the process has been successfully launched.
	 *
	 * This status is returned when the Charon.exe process is successfully started and is ready for interaction.
	 */
	Succeed,
};
