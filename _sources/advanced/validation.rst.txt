Validation
==========

Charon validates game data at several points in the editing lifecycle: on every document save,
on import, and on demand via ``DATA VALIDATE``. Understanding the flag system lets you control
which checks run, how the system auto-repairs common problems, and how to tune validation for
bulk workflows such as CI pipelines or large data migrations.

.. contents:: On this page
   :local:
   :depth: 2

----

When Validation Runs
--------------------

+-------------------------------------------+---------------------------------------------+
| Trigger                                   | Default preset                              |
+===========================================+=============================================+
| Document save (UI / API CREATE or UPDATE) | ``DefaultForCreate`` / ``DefaultForUpdate`` |
+-------------------------------------------+---------------------------------------------+
| ``DATA IMPORT``                           | ``DefaultForBulkChange``                    |
+-------------------------------------------+---------------------------------------------+
| ``DATA I18N IMPORT``                      | ``DefaultForBulkChange``                    |
+-------------------------------------------+---------------------------------------------+
| ``DATA VALIDATE`` (on demand)             | ``AllIntegrityChecks``                      |
+-------------------------------------------+---------------------------------------------+
| Server background check (web edition)     | ``DefaultForBackgroundValidation``          |
+-------------------------------------------+---------------------------------------------+

All defaults can be overridden with ``--validationOptions`` on the relevant command.

----

Validation Flags
----------------

Flags are combined to form a validation profile. Pass multiple flags as space-separated values:

.. code-block:: bash

   charon DATA VALIDATE --dataBase gamedata.json \
       --validationOptions checkRequirements checkReferences checkFormat

Integrity check flags
^^^^^^^^^^^^^^^^^^^^^

These flags **report errors** without modifying data.

``checkRequirements``
   Every property marked **Not Null** or **Not Empty** must have a value.

``checkFormat``
   Values must match the declared data type format — e.g. ``Date`` must be ISO 8601,
   ``Number`` must not be a string, ``PickList`` value must be in the defined list.

``checkUniqueness``
   Properties marked **Unique** or **Unique In Collection** must have no duplicates.

``checkReferences``
   Every :doc:`Reference <../gamedata/datatypes/all/reference>` and
   :doc:`ReferenceCollection <../gamedata/datatypes/all/reference_collection>` must point to a
   document that exists.

``checkSpecification``
   Values must satisfy constraints declared in the :doc:`Specification <../gamedata/schemas/specification>`
   field of the schema or property (used by extension editors and code-generation plugins).

``checkConstraints``
   Structural invariants: valid pick-list values, formula syntax, collection size limits
   defined via ``Size`` on the property.

``checkTranslation``
   Every :doc:`LocalizedText <../gamedata/datatypes/all/localized_text>` field must have a
   translation for each language declared in Project Settings. Detects untranslated strings
   before shipping.

Repair flags
^^^^^^^^^^^^

Repair flags **automatically fix** certain problem classes before integrity checks run.
They modify the data in-place (or within the import transaction).

``repair``
   Master switch — must be present alongside individual repair flags.

``deduplicateIds``
   If multiple documents in the same collection share the same ``Id``, each duplicate gets
   a new auto-generated Id.

``repairRequiredWithDefaultValue``
   A missing required field is filled with the property's **Default Value** if one is defined.

``eraseInvalidValues``
   A field whose value cannot be parsed as the declared data type is set to ``null``.

``resolveConflictingUnions``
   A :doc:`Union <../gamedata/schemas/schema_types>` document having a multiple variants is reset to the first available variant, documents having empty variants are nulled.

----

Validation Report Format
------------------------

Both ``DATA VALIDATE`` and ``DATA IMPORT`` can emit a structured validation report:

.. code-block:: json

   {
     "records": [
       {
         "id": "<document-id>",
         "schemaId": "<schema-id>",
         "schemaName": "<schema-name>",
         "errors": [
           {
             "path": "<json-pointer to field>",
             "message": "<human-readable description>",
             "code": "<machine-readable error code>"
           }
         ]
       }
     ]
   }

Documents with no errors are omitted. An empty ``records`` array means the data is valid.

----

Exit Code Behaviour
-------------------

The exit code is ``1`` **only when** the report contains errors **and** ``--output`` is set
to ``err`` (standard error). In all other cases the exit code is ``0``, even if the report
file contains errors.

This design makes it easy to use validation in CI:

.. code-block:: bash

   # Fail the pipeline if there are any integrity errors
   charon DATA VALIDATE --dataBase gamedata.json \
       --validationOptions checkRequirements checkReferences checkFormat \
       --output err
   # Exit code 1  →  CI step fails

   # Write report to a file without failing the step
   charon DATA VALIDATE --dataBase gamedata.json \
       --output validation_report.json --outputFormat json
   # Exit code 0  →  CI step passes; inspect the file separately

----

Common Recipes
--------------

Skip all checks (import prototype data)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   charon DATA IMPORT --dataBase gamedata.json --input prototype.json \
       --validationOptions none

Auto-repair + full check on import
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   charon DATA IMPORT --dataBase gamedata.json --input data.json \
       --validationOptions repair deduplicateIds repairRequiredWithDefaultValue \
                          checkRequirements checkReferences checkFormat

Fix union conflicts after schema refactor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   charon DATA IMPORT --dataBase gamedata.json --input data.json \
       --validationOptions repair resolveConflictingUnions

Check for untranslated strings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   charon DATA VALIDATE --dataBase gamedata.json \
       --validationOptions checkTranslation --output out --outputFormat json

----

Dry Run vs Validate
-------------------

- ``DATA VALIDATE`` checks the **current state** of the database.
- ``DATA IMPORT --dryRun`` simulates the full import pipeline inside a transaction, then
  rolls back. Use this to preview the post-import state and catch referential errors before
  committing.

See also
--------

- :doc:`Importing and Exporting Data <import_export>`
- :doc:`DATA VALIDATE Command <commands/data_validate>`
- :doc:`DATA IMPORT Command <commands/data_import>`
- :doc:`Schema Types <../gamedata/schemas/schema_types>`
- :doc:`Property <../gamedata/properties/property>`