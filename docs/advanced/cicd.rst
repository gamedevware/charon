CI/CD Integration
=================

Charon's CLI supports full automation of game data workflows - validation, export, translation,
code generation, and backup - making it straightforward to integrate into any continuous
integration or deployment pipeline.

.. contents:: On this page
   :local:
   :depth: 2

----

Installation in CI
------------------

Charon requires the **.NET SDK 10 or later** on the runner. With SDK 10 there is no install step at
all - ``dnx`` fetches and runs the tool on demand, and NuGet caches it for the rest of the job.

.. tab-set::

   .. tab-item:: GitHub Actions

      .. code-block:: yaml

         - name: Setup .NET
           uses: actions/setup-dotnet@v5
           with:
             dotnet-version: '10.x'

         - name: Check Charon
           run: dnx dotnet-charon -- VERSION

   .. tab-item:: GitLab CI

      .. code-block:: yaml

         before_script:
           - apt-get install -y dotnet-sdk-10.0
           - dnx dotnet-charon -- VERSION

   .. tab-item:: Shell script (any runner)

      .. code-block:: bash

         dnx dotnet-charon -- VERSION

If your runner is pinned to .NET SDK 8 or 9, ``dnx`` is unavailable. Install the tool globally instead
and call it as ``charon``:

.. code-block:: bash

   dotnet tool install -g dotnet-charon
   export PATH="$PATH:$HOME/.dotnet/tools"
   charon VERSION

----

Version Pinning and Compatibility
----------------------------------

``dnx dotnet-charon`` without a version always fetches the latest release. For reproducible
builds, pin the tool version.

**On-demand with a pinned version (recommended, .NET SDK 10+).** Nothing to install or commit:

.. code-block:: bash

   dnx dotnet-charon@2026.3.4 -- DATA VALIDATE --dataBase gamedata.json ...

**Local tools manifest.** Create a manifest once and commit ``.config/dotnet-tools.json`` to the
repository:

.. code-block:: bash

   dotnet new tool-manifest
   dotnet tool install dotnet-charon --version 2026.3.4

CI then restores the exact pinned version and invokes the tool through ``dotnet``:

.. code-block:: bash

   dotnet tool restore
   dotnet charon DATA VALIDATE --dataBase gamedata.json ...

**Global install with a pinned version:**

.. code-block:: bash

   dotnet tool install -g dotnet-charon --version 2026.3.4
   charon DATA VALIDATE --dataBase gamedata.json ...

Tool version vs. format version
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Two versions matter for compatibility:

- **Tool version** (e.g. ``2026.3.4``) - the actual release version of ``dotnet-charon``.
  It changes with every release: bug fixes, new features, UI updates.
- **Format version** - the version of the game data file format. It changes only when the
  system schemas are updated or system fields are added or changed, which is rare. Tool
  releases overwhelmingly ship with an unchanged format version.

Game data files are **auto-migrated to the newest format version on save**. Read-only
operations - ``DATA VALIDATE``, ``DATA EXPORT``, ``GENERATE ...`` - never mutate the file, so
running a newer tool against an older-format file in CI is safe and leaves the file untouched.

If you want to deliberately migrate a file to the current format version, apply any change and
save - for example, update the *Copyright* field in *Project Settings* from the editor UI.
The save rewrites the file in the newest format.

----

Authentication
--------------

Provide the API key for remote data sources via the ``CHARON_API_KEY`` environment variable.
Store it as a CI secret; never hard-code it in pipeline files.

.. code-block:: yaml

   # GitHub Actions - secrets.CHARON_API_KEY defined in repository settings
   env:
     CHARON_API_KEY: ${{ secrets.CHARON_API_KEY }}

.. code-block:: bash

   # Shell - set before running any charon command
   export CHARON_API_KEY="your-api-key-here"
   dnx dotnet-charon -- DATA EXPORT --dataBase "https://charon.live/view/data/MyGame/main/" ...

Alternatively, pass credentials explicitly with ``--credentials``. The environment variable
takes precedence when both are supplied.

----

Exit Codes
----------

Charon exits with ``0`` on success. It exits with ``1`` or any positive code in these cases:

- A fatal error occurred (bad parameters, file not found, network failure).
- ``DATA VALIDATE`` produced errors **and** ``--output`` was set to ``err``.

All other cases - including a validation report that contains errors written to a file -
exit with ``0``. Design your pipeline steps accordingly.

----

Common Pipeline Recipes
-----------------------

Validate on every pull request
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: yaml

   # .github/workflows/validate.yml
   name: Validate game data

   on: [pull_request]

   jobs:
     validate:
       runs-on: ubuntu-latest
       steps:
         - uses: actions/checkout@v4

         - uses: actions/setup-dotnet@v5
           with: { dotnet-version: '10.x' }


         - name: Validate integrity
           run: |
             dnx dotnet-charon -- DATA VALIDATE \
               --dataBase gamedata.json \
               --validationOptions checkRequirements checkReferences checkFormat \
               --output err
           # Exits 1 and fails the workflow if errors are found

Export and publish on tag
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: yaml

   # .github/workflows/publish.yml
   name: Publish game data

   on:
     push:
       tags: ['v*']

   jobs:
     publish:
       runs-on: ubuntu-latest
       env:
         CHARON_API_KEY: ${{ secrets.CHARON_API_KEY }}

       steps:
         - uses: actions/checkout@v4
         - uses: actions/setup-dotnet@v5
           with: { dotnet-version: '10.x' }

         - name: Backup before publish
           run: |
             dnx dotnet-charon -- DATA BACKUP \
               --dataBase "https://charon.live/view/data/MyGame/main/" \
               --output backup_${{ github.ref_name }}.zip

         - name: Validate
           run: |
             dnx dotnet-charon -- DATA VALIDATE \
               --dataBase "https://charon.live/view/data/MyGame/main/" \
               --validationOptions checkRequirements checkReferences \
               --output err

         - name: Export published data (JSON)
           run: |
             dnx dotnet-charon -- DATA EXPORT \
               --dataBase "https://charon.live/view/data/MyGame/main/" \
               --mode publication \
               --output StreamingAssets/gamedata.json \
               --outputFormat json

         - name: Generate C# source code
           run: |
             dnx dotnet-charon -- GENERATE CSHARPCODE \
               --dataBase "https://charon.live/view/data/MyGame/main/" \
               --namespace MyGame.Parameters \
               --outputDirectory Assets/Scripts/Generated \
               --clearOutputDirectory

         - name: Commit generated files
           run: |
             git config user.name "CI Bot"
             git config user.email "ci@example.com"
             git add Assets/Scripts/Generated StreamingAssets/gamedata.json
             git commit -m "chore: regenerate game data for ${{ github.ref_name }}"
             git push

Apply a patch on merge
^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   # In a merge script or CI job
   dnx dotnet-charon -- DATA APPLYPATCH \
       --dataBase gamedata.json \
       --input feature_changes.patch.json \
       --validationOptions repair checkRequirements checkReferences

   dnx dotnet-charon -- DATA VALIDATE \
       --dataBase gamedata.json \
       --validationOptions checkRequirements checkReferences checkFormat \
       --output err   # Fail CI if post-merge data is invalid

Export translation files for a localization vendor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   for lang in de fr ja ko; do
     dnx dotnet-charon -- DATA I18N EXPORT \
       --dataBase gamedata.json \
       --sourceLanguage en \
       --targetLanguage "$lang" \
       --output "translations/en_${lang}.xliff" \
       --outputFormat xliff
   done

Import translated files from a vendor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

   for file in translations/en_*.xliff; do
     dnx dotnet-charon -- DATA I18N IMPORT \
       --dataBase gamedata.json \
       --input "$file" \
       --dryRun   # Preview first

     dnx dotnet-charon -- DATA I18N IMPORT \
       --dataBase gamedata.json \
       --input "$file"
   done

----

Recommended Pipeline Structure
-------------------------------

.. code-block::

   [PR open]
     └─ DATA VALIDATE (checkRequirements + checkReferences + checkFormat → err)

   [Merge to main]
     └─ DATA BACKUP
     └─ DATA VALIDATE (as above)
     └─ GENERATE <LANG>CODE --clearOutputDirectory
     └─ commit generated files

   [Release tag]
     └─ DATA BACKUP (tagged archive)
     └─ DATA EXPORT --mode publication
     └─ upload to CDN / game build

See also
--------

- :doc:`Command Line Interface <command_line>`
- :doc:`Validation <validation>`
- :doc:`Backup and Restore <backup_restore>`
- :doc:`Patch and Diff Workflow <patch_diff>`
- :doc:`Internationalization <internationalization>`
- :doc:`Universal Parameters <commands/universal_parameters>`
- :doc:`URL-based I/O <commands/remote_input_output>`