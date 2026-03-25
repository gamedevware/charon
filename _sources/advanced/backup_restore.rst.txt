Backup and Restore
==================

Charon can create a full snapshot of a game data file and restore it later. Backups capture
the complete state of the database — all documents, schemas, project settings, and metadata —
in a single portable file.

.. contents:: On this page
   :local:
   :depth: 2

----

Creating a Backup
-----------------

.. code-block:: bash

   # Local file
   charon DATA BACKUP --dataBase gamedata.json --output backup.msgpack

   # Remote project
   charon DATA BACKUP \
       --dataBase "https://charon.live/view/data/MyGame/develop/" \
       --output backup.msgpack \
       --credentials "$CHARON_API_KEY"

The output is a file containing the complete game data in JSON format.

What is included
^^^^^^^^^^^^^^^^

- All document collections (user data, schema definitions, project settings).
- ``ToolsVersion``, ``RevisionHash``, and ``ChangeNumber`` file-level fields.

What is **not** included
^^^^^^^^^^^^^^^^^^^^^^^^

- User accounts, API keys, and access control settings (server edition — managed separately).
- Binary resource files (images, audio) attached to documents via Asset Path properties.

----

Restoring from a Backup
------------------------

.. code-block:: bash

   # Local file
   charon DATA RESTORE --dataBase gamedata.json --input backup.msgpack

   # Remote project
   charon DATA RESTORE \
       --dataBase "https://charon.live/view/data/MyGame/develop/" \
       --input backup.msgpack \
       --credentials "$CHARON_API_KEY"

.. warning::
   ``DATA RESTORE`` **replaces all content** in the target database. The operation is not
   incremental — the entire existing state is overwritten. Confirm you are targeting the
   correct database before running.

----

Backup vs Export
----------------

Choose the right tool for the job:

+---------------------------+-------------------------------------+--------------------------------------------+
|                           | ``DATA BACKUP``                     | ``DATA EXPORT``                            |
+===========================+=====================================+============================================+
| **Purpose**               | Full snapshot for disaster recovery | Filtered slice for runtime or tooling      |
+---------------------------+-------------------------------------+--------------------------------------------+
| **Format**                | JSON / MEssagePack                  | JSON / BSON / MessagePack / XLSX           |
+---------------------------+-------------------------------------+--------------------------------------------+
| **Includes schemas**      | Always                              | Optional (``--schemas Schema``)            |
+---------------------------+-------------------------------------+--------------------------------------------+
| **Strips unused data**    | No                                  | Yes — ``--mode publication`` strips unused |
|                           |                                     | docs and languages                         |
+---------------------------+-------------------------------------+--------------------------------------------+
| **Restorable**            | Yes, via ``DATA RESTORE``           | Partially — via ``DATA IMPORT``            |
+---------------------------+-------------------------------------+--------------------------------------------+

Use **Backup** when you need a full, restorable point-in-time snapshot.
Use **Export** when preparing data for the game runtime or for external tools.

----

Scheduled Automated Backups
-----------------------------

.. tab-set::

   .. tab-item:: Linux / macOS (cron)

      .. code-block:: bash

         # Daily at 02:00
         0 2 * * * charon DATA BACKUP \
             --dataBase /var/game/gamedata.json \
             --output /backups/gamedata_$(date +\%Y\%m\%d).msgpack

   .. tab-item:: GitHub Actions

      .. code-block:: yaml

         - name: Backup game data
           run: |
             charon DATA BACKUP \
               --dataBase "${{ secrets.CHARON_DB_URL }}" \
               --output backups/gamedata_${{ github.run_id }}.msgpack \
               --credentials "${{ secrets.CHARON_API_KEY }}"

         - name: Upload artifact
           uses: actions/upload-artifact@v4
           with:
             name: gamedata-backup
             path: backups/

----

Pre-Publish Safety Snapshot
-----------------------------

Take a backup immediately before publishing so that a known-good restore point exists:

.. code-block:: bash

   # 1. Snapshot
   charon DATA BACKUP --dataBase gamedata.json --output pre_publish_backup.msgpack

   # 2. Validate
   charon DATA VALIDATE --dataBase gamedata.json \
       --validationOptions checkRequirements checkReferences --output err

   # 3. Publish
   charon DATA EXPORT --dataBase gamedata.json \
       --mode publication --output StreamingAssets/gamedata.json --outputFormat json

See also
--------

- :doc:`DATA BACKUP Command <commands/data_backup>`
- :doc:`DATA RESTORE Command <commands/data_restore>`
- :doc:`Importing and Exporting Data <import_export>`
- :doc:`Publishing Game Data <../gamedata/publication>`
- :doc:`CI/CD Integration <cicd>`
- :doc:`Patch and Diff Workflow <patch_diff>`