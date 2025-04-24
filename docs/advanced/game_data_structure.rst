Game Data Structure
===================

.. graphviz::

   digraph gamedata {
      "Game Data" -> "Collections";
      "Game Data" -> "ToolsVersion";
      "Game Data" -> "RevisionHash";
      "Game Data" -> "ChangeNumber";
	  "Collections" -> "Project Settings";
	  "Collections" -> "Schema";
	  "Schema" -> "Properties";
	  "Properties" -> "Schema Property";
	  "Collections" -> "<Schema-Name>";
   }

.. _GameDataStructure_GameData:
=========
Game Data
=========

.. tabs::

   .. tab:: Fields

      - ``ToolsVersion`` (string): Version of the application used to create this file.  
      - ``RevisionHash`` (string): Current changeset hash value.  
      - ``ChangeNumber`` (number): Current changeset ordinal number.  
      - ``Collections`` (object): List of document collections identified by schema name.  
	  
          - ``ProjectSettings`` (array): Project-related settings for the current file.  
		  
              - See :ref:`Project Settings <GameDataStructure_ProjectSettings>` section below.  
			  
          - ``Schema`` (array): Project-related schemas for the current file.  
		  
              - See :ref:`Schema <GameDataStructure_Schema>` section below.  
			  
          - ``<Schema-Name>`` (array): Other document collections listed in alphabetical order.  

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
                /* see project settings section below */
              }
            ],
            "Schema":
            [
              {
                /* see schema section below */
              }
            ],
            "SchemaProperty": [ /* always empty */ ],

            "<Schema-Name>": 
            [
              {
                "Id": "<Id>" // All documents have Id
                
                /* rest of properties of document */
              },
              // ...
            ]
          }
        }

.. _GameDataStructure_ProjectSettings:
================
Project Settings
================

.. tabs::

   .. tab:: Fields

      - ``Id`` (string): Unique identifier for the project settings (BSON ObjectId).  
      - ``Name`` (string): Name of the project.  
      - ``PrimaryLanguage`` (string): Primary language for localizable text in the project (language ID in BCP-47 format).  
      - ``Languages`` (string): Alternative languages for localizable text in the project (semicolon-delimited list of language IDs in BCP-47 format).  
      - ``Copyright`` (string): Copyright information for the project.  
      - ``Version`` (string): Version of the current file, represented as four numbers separated by dots (Major.Minor.Build.Revision).  

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

.. _GameDataStructure_Schema:
======
Schema
======

.. tabs::

   .. tab:: Fields

      - ``Id`` (string): Unique identifier for the schema (BSON ObjectId).  
      - ``Name`` (string): Name of the schema (valid C identifier).  
      - ``DisplayName`` (string): Display name of the schema for UI purposes.  
      - ``Description`` (string): Schema description used in generated documentation.  
      - ``Specification`` (string): Extension data for the schema in `application/x-www-form-urlencoded` format (RFC-1867).  
      - ``IdGenerator`` (number): ID generation method for documents created by this schema:  
	  
          - `0` : None - ID must be provided manually by the user.  
          - `1` : ObjectId - Generates a new BSON ObjectId.  
          - `2` : Guid - Generates a new UUID.  
          - `3` : Sequence - Uses an incrementing number unique to each schema.  
          - `4` : GlobalSequence - Uses an incrementing number shared across all schemas.  
		  
      - ``Type`` (number): Schema type:  
	  
          - `0` : Normal - Documents can be created in `Collections` or embedded in another document.  
          - `1` : Component - Documents are always embedded in another document and never appear in ``Collections``.  
          - `2` : Settings - Only one document of this schema can exist in ``Collections``.  
		  
      - ``Properties`` (array): List of schema properties. Always includes the ``Id`` property.  
	  
          - See :ref:`Schema Property <GameDataStructure_SchemaProperty>` section below.  

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

.. _GameDataStructure_SchemaProperty:
===============
Schema Property
===============

.. tabs::

   .. tab:: Structure

      - ``Id`` (string): Unique identifier for the property (BSON ObjectId).  
      - ``Name`` (string): Name of the property (valid C identifier).  
      - ``DisplayName`` (string): Display name for UI and documentation purposes.  
      - ``Description`` (string): Property description used in generated documentation.  
      - ``DataType`` (number): Data type of values stored in documents:  
	  
          - `0`: Text - Line of text.  
          - `1`: LocalizedText - Lines of localized text.  
          - `5`: Logical - Boolean value.  
          - `8`: Time - Time span.  
          - `9`: Date - Specific date.  
          - `12` : Number - Decimal number.  
          - `13` : Integer - Whole number.  
          - `18` : PickList - Predefined value list.  
          - `19` : MultiPickList - Multiple selections from predefined values.  
          - `22` : Document - Embedded document.  
          - `23` : DocumentCollection - Collection of embedded documents.  
          - `28` : Reference - Reference to another document.  
          - `29` : ReferenceCollection - References to multiple documents.  
          - `35` : Formula - C#-like expression for calculations.  
		  
      - ``DefaultValue`` (vary|null): Default value for the property used when a new document is created.  
      - ``Uniqueness`` (number): Uniqueness requirement for the property:  
	  
          - `0` : None - Value does not need to be unique.  
          - `1` : Unique - Value must be unique across all documents of this type.  
          - `2` : UniqueInCollection - Value must be unique within the containing collection.  
		  
      - ``Requirement`` (number): Value requirement for the property:  
	  
          - `0` : None - Value is optional and can be null.  
		  - `1` : <UNUSED> - Remapped to 2 (NotNull) during saving.  
          - `2` : NotNull - Value is required but can be an empty string/collection.  
          - `3` : NotEmpty - Value is required and cannot be empty.  
		  
      - ``ReferenceType`` (object|null): Referenced schema for certain data types (`Document`, `DocumentCollection`, `Reference`, `ReferenceCollection`):  
	  
          - ``Id`` (string): Identifier of the referenced schema.  
          - ``DisplayName`` (string): Optional display name of the referenced schema.  
		  
      - ``Size`` (number): Maximum or exact size of the data type. For variable-length types (e.g., text, collections), this defines the size; for others, it is zero.  
      - ``Specification`` (string): Extension data for the property in `application/x-www-form-urlencoded` format (RFC-1867).  

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