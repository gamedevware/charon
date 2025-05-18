==========================
Importing and Exporting Data
==========================

Charon supports exporting and importing game data to facilitate workflows such as version control, bulk editing, translation, and integration with external tools or pipelines. This document outlines the general principles of working with exported data, the process of modifying it, and best practices for importing it back into the system.

Overview
========

Data may be exported from Charon in various formats, edited externally, and re-imported into a project. Data can also be created outside of Charon, provided it conforms to the expected structure. For detailed structural information, refer to :doc:`Game Data Structure <game_data_structure>`.

Common use cases include:

- Performing batch modifications using tools such as `yq`, spreadsheets, or custom scripts.
- Managing localization and translation workflows.
- Synchronizing game data with external DBs, Tools, Game Engines etc...
- Integrating game data with CI/CD pipelines.

Exporting Data
==============

Data can be exported using either the graphical user interface (GUI) or the command-line interface (CLI). For a full CLI reference, refer to :doc:`Export via CLI <commands/data_export>`.

Exported data is available in formats such as JSON, BSON, MsgPack, and XLSX. JSON is recommended for most use cases due to its compatibility with standard tooling.

**Example (CLI):**

.. code-block:: bash

   dotnet charon DATA EXPORT --dataBase gamedata.json --schemas Item --output items.json --outputFormat json

**Example output (JSON):**

.. code-block:: json

   {
     "Collections": {
       "Item": [
         { "Id": "Sword", "Name": "Iron Sword", "Damage": 3 }
       ]
     }
   }

Modifying Exported Data
=======================

After export, data can be edited manually or via automated tools. Below is an example using `yq` to update a value:

.. code-block:: bash

   yq -i '.Collections.Item[0].Damage = 5' items.json

In addition to editing, tools may be used to convert between formats (e.g., JSON to YAML) or to apply structural changes such as renaming fields.

Creating Data from Scratch
==========================

Data files can be authored externally and later imported into Charon, provided they conform to the required format. The structure must include a `Collections` object containing arrays of documents for each schema:

.. code-block:: json

   {
     "Collections": {
       "Item": [
         { "Id": "BronzeSword", "Name": "Bronze Sword", "Damage": 4 }
       ]
     }
   }

See :doc:`Game Data Structure <game_data_structure>` for full format specifications.

Importing Data
==============

Data can be imported through both the GUI and CLI. Several import modes are available to support different workflows.

**Example (CLI):**

.. code-block:: bash

   dotnet charon DATA IMPORT --dataBase gamedata.json --schemas Item --input items.json --mode safeUpdate

For full CLI options, refer to :doc:`Import via CLI <commands/data_import>`.

Special Considerations
======================

Document Identification (Id Field)
----------------------------------

- If an `Id` is not specified, it will be automatically generated.
- If the document is referenced elsewhere in the data, an `Id` must be provided.
- Temporary identifiers of the form `_ID_<UNIQUE>` can be used during import; these will be consistently resolved across all documents.

Partial Updates
---------------

When using update modes, documents do not need to include all fields. Partial structures containing only modified or relevant fields are accepted.

.. code-block:: json

   [
     { "Id": "IronSword", "Damage": 10 }
   ]

Dry Run
-------

It is recommended to use dry run functionality to preview changes before committing them:

- **GUI**: Enable the ``Perform a dry run and don’t persist changes`` option.
- **CLI**: Use the ``--dryRun`` flag:

.. code-block:: bash

   dotnet charon DATA IMPORT --dataBase gamedata.json --schemas Item --input items.json --mode update --dryRun

Validation Options
------------------

Validation may be disabled to import incomplete or prototype data:

- **GUI**: Enable the ``Ignore consistency errors in imported data`` option.
- **CLI**: Use the ``--validationOptions None`` flag.

.. code-block:: bash

   dotnet charon DATA IMPORT --dataBase gamedata.json --schemas Item --input items.json --mode createAndUpdate --validationOptions None

.. note::
   When importing schema definitions, validation is always enforced and must pass successfully.

Import Modes
============

Charon supports multiple import modes depending on the desired outcome:

+------------------+----------------------------------------------------------+
| Mode             | Description                                              |
+==================+==========================================================+
| `createAndUpdate`| Default mode. Creates new documents and updates existing.|
+------------------+----------------------------------------------------------+
| `create`         | Creates new documents only. Existing ones are untouched. |
+------------------+----------------------------------------------------------+
| `update`         | Updates existing documents only. No new documents added. |
+------------------+----------------------------------------------------------+
| `safeUpdate`     | Updates only top-level fields. Fields are not added or   |
|                  | removed.                                                 |
+------------------+----------------------------------------------------------+
| `replace`        | Replaces the entire collection with imported documents.  |
+------------------+----------------------------------------------------------+
| `delete`         | Deletes documents listed in the input file.              |
+------------------+----------------------------------------------------------+

All import modes support both full and partial document structures depending on the use case.

See also
========

- :doc:`Internationalization (i18n) <internationalization>`
- :doc:`Game Data Structure <game_data_structure>`
- :doc:`Export via CLI <commands/data_export>`
- :doc:`Import via CLI <commands/data_import>`
