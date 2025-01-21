Game Data Structure
===================

The game data follow this structure, but additional properties are allowed at top level ``/``:

.. tabs::

   .. tab:: Structure

      - **ToolsVersion** (string): Version of the application used to create this file.
      - **RevisionHash** (string): Current changeset hash value.
      - **ChangeNumber** (number): Current changeset ordinal number.
      - **Collections** (object): List of document collections identified by schema name.
        - **ProjectSettings** (array): Project-related settings for the current file.
            - See **Project Settings** section below.
        - **Schema** (array): Project-related schemas for the current file.
          - See **Schema** section below.
        - **<Your-Schema-Name>** (array): Other document collections listed in alphabetical order.

   .. tab:: Example

      .. code-block:: js
        
        {
          "ToolsVersion": "2023.1.2.0",
          "RevisionHash": "678f998993a22d1f54b7fa80",
          "ChangeNumber": 1,
          "Collections": 
          {
            "ProjectSettings":
            [
              {
                "Id": "049bc0604c363a980b000088", 
                "Name": "My Project", 
                "PrimaryLanguage": "en-US", 
                "Languages": "en-GB;fr-FR", 
                "Copyright": "My Company (с) 2025", 
                "Version": "1.0.0.0" 
              }
            ],
            "Schema":
            [
              {
                "Id": "18d4bf318f3c49688087dbed",
                "Name": "<Name>"
                
                /* rest of properties of schema */
              }
            ],
            "<Schema-Name>": 
            [
              {
                "Id": "<Id>" // Id is always present
                
                /* rest of properties of document */
              },
              // ...
            ]
          }
        }

================
Project Settings
================

.. tabs::

   .. tab:: Structure

        - **Id** (string): Unique identifier for the project settings (BSON ObjectId).
        - **Name** (string): Name of the project.
        - **PrimaryLanguage** (string): Primary language for localizable text in the project (language ID in BCP-47 format).
        - **Languages** (string): Alternative languages for localizable text in the project (semicolon-delimited list of language IDs in BCP-47 format).
        - **Copyright** (string): Copyright information for the project.
        - **Version** (string): Version of the current file, represented as four numbers separated by dots (Major.Minor.Build.Revision).

   .. tab:: Example

      .. code-block:: js
        
        {
          "Id": "049bc0604c363a980b000088", 
          "Name": "My Project", 
          "PrimaryLanguage": "en-US", 
          "Languages": "en-GB;fr-FR", 
          "Copyright": "My Company (с) 2025", 
          "Version": "1.0.0.0" 
        } 


======
Schema
======

.. tabs::

   .. tab:: Structure

        - **Id** (string): Unique identifier for the schema (BSON ObjectId).
        - **Name** (string): Name of the schema (valid C identifier).
        - **DisplayName** (string): Display name of the schema for UI purposes.
        - **Description** (string): Schema description used in generated documentation.
        - **Specification** (string): Extension data for the schema in `application/x-www-form-urlencoded` format (RFC-1867).
        - **IdGenerator** (number): ID generation method for documents created by this schema:
          - `0` (number): None - ID must be provided manually by the user.
          - `1` (number): ObjectId - Generates a new BSON ObjectId.
          - `2` (number): Guid - Generates a new UUID.
          - `3` (number): Sequence - Uses an incrementing number unique to each schema.
          - `4` (number): GlobalSequence - Uses an incrementing number shared across all schemas.
        - **Type** (number): Schema type:
          - `0` (number): Normal - Documents can be created in `Collections` or embedded in another document.
          - `1` (number): Component - Documents are always embedded in another document and never appear in `Collections`.
          - `2` (number): Settings - Only one document of this schema can exist in `Collections`.
        - **Properties** (array): List of schema properties. Always includes the `Id` property.
          - See **Schema Property** section below.

   .. tab:: Example

      .. code-block:: js
        
        {
          "Id": "592fc86c983a36266c0912a0", 
          "Name": "Item", 
          "DisplayName": "Items", 
          "Type": 0, 
          "Description": "An item.", 
          "IdGenerator": 1, 
          "Specification": "icon=fugue16%2Fabacus&group=Metagame", 
          "Properties": [ 
            // property
          ]
        }

===============
Schema Property
===============

.. tabs::

   .. tab:: Structure

        - **Id** (string): Unique identifier for the property (BSON ObjectId).
        - **Name** (string): Name of the property (valid C identifier).
        - **DisplayName** (string): Display name for UI and documentation purposes.
        - **Description** (string): Property description used in generated documentation.
        - **DataType** (number): Data type of values stored in documents:
          - `0` (number): Text - Line of text.
          - `1` (number): LocalizedText - Lines of localized text.
          - `5` (number): Logical - Boolean value.
          - `8` (number): Time - Time span.
          - `9` (number): Date - Specific date.
          - `12` (number): Number - Decimal number.
          - `13` (number): Integer - Whole number.
          - `18` (number): PickList - Predefined value list.
          - `19` (number): MultiPickList - Multiple selections from predefined values.
          - `22` (number): Document - Embedded document.
          - `23` (number): DocumentCollection - Collection of embedded documents.
          - `28` (number): Reference - Reference to another document.
          - `29` (number): ReferenceCollection - References to multiple documents.
          - `35` (number): Formula - C#-like expression for calculations.
        - **DefaultValue** (vary|null): Default value for the property used when a new document is created.
        - **Uniqueness** (number): Uniqueness requirement for the property:
          - `0` (number): None - Value does not need to be unique.
          - `1` (number): Unique - Value must be unique across all documents of this type.
          - `2` (number): UniqueInCollection - Value must be unique within the containing collection.
        - **Requirement** (number): Value requirement for the property:
          - `0` (number): None - Value is optional and can be null.
          - `2` (number): NotNull - Value is required but can be an empty string/collection.
          - `3` (number): NotEmpty - Value is required and cannot be empty.
        - **ReferenceType** (object|null): Referenced schema for certain data types (`Document`, `DocumentCollection`, `Reference`, `ReferenceCollection`):
          - **Id** (string): Identifier of the referenced schema.
          - **DisplayName** (string): Optional display name of the referenced schema.
        - **Size** (number): Maximum or exact size of the data type. For variable-length types (e.g., text, collections), this defines the size; for others, it is zero.
        - **Specification** (string): Extension data for the property in `application/x-www-form-urlencoded` format (RFC-1867).

   .. tab:: Example

      .. code-block:: js
        
        {
          "Id": "592fc9f8983a36266c0912aa", 
          "Name": "TextField", 
          "DisplayName": "Text Field", 
          "Description": "", 
          "DataType": 0, 
          "DefaultValue": null, 
          "Uniqueness": 0, 
          "Requirement": 0, 
          "ReferenceType": null, 
          "Size": 0, 
          "Specification": null 
        }