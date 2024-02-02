#pragma once

#include "EImportMode.generated.h"

UENUM()
/**
 * @enum EImportMode
 * @brief Defines how documents should be applied during the FCharonCli::Import() operation.
 *
 * This enumeration details various modes of import, each dictating how new or existing documents
 * should be handled during the import process. The mode chosen affects how documents are created,
 * updated, replaced, or deleted.
 */
enum class EImportMode
{
	/**
	 * @brief Same as CreateAndUpdate.
	 */
	Default = 0,
	/**
	 * @brief Default mode where existing documents are updated and new ones are created.
	 *
	 * In this mode, the import operation updates documents that already exist and creates new ones
	 * for those that don't. It's a comprehensive import strategy for adding and updating data.
	 */
	CreateAndUpdate = 0,
	
	/**
	 * @brief Imports only new documents, keeping existing ones intact.
	 *
	 * In Create mode, the import process adds new documents without altering any existing ones.
	 * This mode is useful when the intent is to expand the collection without modifying current data.
	 */
	Create,

	/**
	 * @brief Updates only existing documents, omitting new ones.
	 *
	 * Update mode focuses on modifying existing documents. Any document in the import set that
	 * doesn't already exist in the target collection is ignored.
	 */
	Update,

	/**
	 * @brief Safely updates existing documents while preserving their internal structure.
	 *
	 * SafeUpdate is particularly useful for importing translated text or other specific updates
	 * without altering the overall structure or other data within the documents.
	 */
	SafeUpdate,

	/**
	 * @brief Replaces all existing documents with the imported ones.
	 *
	 * In Replace mode, the import operation discards the current collection and replaces it entirely
	 * with the imported documents. This mode is suitable for complete overhauls of the collection.
	 */
	Replace,

	/**
	 * @brief Deletes documents that match the imported ones, keeping non-matching documents intact.
	 *
	 * Delete mode is used to remove specific documents from the collection. Only the documents that
	 * correspond to those in the import set are deleted; others are left unchanged.
	 */
	Delete
};