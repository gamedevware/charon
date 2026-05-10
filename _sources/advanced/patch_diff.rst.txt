Patch and Diff Workflow
=======================

Charon can compute the **difference** between two game data files and represent it as a reusable
patch. That patch can later be applied to any compatible target file. This enables branching
workflows, incremental DLC updates, audit trails, and automated data merging in CI/CD pipelines.

.. contents:: On this page
   :local:
   :depth: 2

----

Overview
--------

Two commands form the workflow:

``DATA CREATEPATCH``
   Compares two game data sources and produces a *patch file* describing every addition,
   modification, and deletion between them.

``DATA APPLYPATCH``
   Applies a patch file to a target game data file.

.. code-block::

   dataBase1 (before)  ─┐
                         ├─ CREATEPATCH ─→ patch.json
   dataBase2 (after)   ─┘

   target.json  ──┬── APPLYPATCH ──→ patched target.json
   patch.json   ──┘

Common use cases:

- **Feature branch merge** — keep a stable baseline; apply a feature branch as a patch.
- **DLC / live updates** — ship incremental changes without distributing the full file.
- **Code-review diff** — generate a human-readable changelog of data edits for review.
- **Automated reconciliation** — merge concurrent edits from multiple environments in CI.

----

Creating a Patch
----------------

.. code-block:: bash

   charon DATA CREATEPATCH \
       --dataBase1 gamedata_before.json \
       --dataBase2 gamedata_after.json \
       --output    changes.patch.json \
       --outputFormat json

- ``--dataBase1`` is the **baseline** (before).
- ``--dataBase2`` is the **modified** version (after).
- Both can be local files or remote server URLs. A single ``--credentials`` value is used
  for both when they are remote.

.. tip::
   When both sources are remote and the dataset is large, download them first with
   ``DATA BACKUP`` and run ``CREATEPATCH`` on the local copies to avoid network round-trips.

Patch file format
^^^^^^^^^^^^^^^^^

The patch file follows the standard game data JSON format.:

.. code-block:: json

   {
     "Collections": {
       "Item": {
         "IronSword": { Id: "IronSword", "Name": "Iron Sword", "Damage": 20 }, // addition
         "OldSword": { "Damage": 18 }, // modification
         "RustySword": null // deletion
       }
     }
   }

----

Applying a Patch
----------------

.. code-block:: bash

   charon DATA APPLYPATCH \
       --dataBase target.json \
       --input    changes.patch.json \
       --inputFormat json

Validation on apply
^^^^^^^^^^^^^^^^^^^^

``DATA APPLYPATCH`` validates the target after applying the patch using the
``DefaultForBulkChange`` preset (repairs only, no strict integrity checks). To tighten this:

.. code-block:: bash

   charon DATA APPLYPATCH \
       --dataBase target.json \
       --input changes.patch.json \
       --validationOptions repair checkRequirements checkReferences

Dry run
^^^^^^^^

Preview what the patch would do without committing any changes:

.. code-block:: bash

   charon DATA APPLYPATCH \
       --dataBase target.json \
       --input changes.patch.json \
       --dryRun

----

End-to-End Example: Feature Branch Merge
-----------------------------------------

.. code-block:: bash

   # 1. Backup the stable main branch
   charon DATA BACKUP \
       --dataBase "https://charon.live/view/data/MyGame/main/" \
       --output main.zip --credentials "$CHARON_KEY"

   # 2. Backup the feature branch
   charon DATA BACKUP \
       --dataBase "https://charon.live/view/data/MyGame/feature-loot/" \
       --output feature.zip --credentials "$CHARON_KEY"

   # 3. Extract
   unzip main.zip -d main/ && unzip feature.zip -d feature/

   # 4. Compute the diff
   charon DATA CREATEPATCH \
       --dataBase1 main/gamedata.json \
       --dataBase2 feature/gamedata.json \
       --output loot_changes.patch.json

   # 5. (Optional) review the patch in a text editor or commit it to version control

   # 6. Apply to a staging branch
   charon DATA APPLYPATCH \
       --dataBase staging/gamedata.json \
       --input loot_changes.patch.json \
       --validationOptions repair checkRequirements checkReferences

----

Storing Patches in Version Control
------------------------------------

Patch files are plain JSON (or BSON / MessagePack). They can be:

- Committed alongside game source code to track data changes per feature branch.
- Applied conditionally during a build — e.g., apply a hotfix patch only in production builds.
- Accumulated as a migration log: ``v1.0→v1.1.patch.json``, ``v1.1→v1.2.patch.json``, and so on.

See also
--------

- :doc:`Document Merge Logic <merge_logic>`
- :doc:`DATA CREATEPATCH Command <commands/data_create_patch>`
- :doc:`DATA APPLYPATCH Command <commands/data_apply_patch>`
- :doc:`Backup and Restore <backup_restore>`
- :doc:`CI/CD Integration <cicd>`
- :doc:`Importing and Exporting Data <import_export>`