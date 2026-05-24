CLI Access to charon.live
=========================

The web version of Charon provides a :doc:`REST API <rest>` and :doc:`CLI <../advanced/command_line>` for accessing and
modifying game data remotely. To authenticate CLI commands against a web project, users need to generate an ``API Key``
in the *API Keys* section of their *User Profile*.

With an API Key, Charon integrates into any existing workflow - exporting data into a local repository,
importing designer edits back to the server, generating source code, or running validation in CI.

.. contents:: On this page
   :local:
   :depth: 2

----

Installing the CLI
------------------

Install ``dotnet-charon`` as a global .NET tool (requires .NET 8 or later):

.. code-block:: bash

   dotnet tool install -g dotnet-charon

After installation the ``charon`` command is available on your ``PATH``.
Alternatively, use ``dnx`` (.NET SDK 10+) to run without installing:

.. code-block:: bash

   dnx dotnet-charon -- DATA EXPORT --help

See :doc:`Command Line Interface (CLI) <../advanced/command_line>` for full installation options.

----

Finding Your Project URL
------------------------

Every web project has a stable URL that can be passed to the ``--dataBase`` parameter. You can find it in your
browser's address bar while viewing any page inside the project on charon.live - it has the form:

.. code-block:: text

   https://charon.live/view/data/<Project>/
   https://charon.live/view/data/<Project>/<Branch>/

For example:

.. code-block:: text

   https://charon.live/view/data/My_Game/
   https://charon.live/view/data/My_Game/develop/

Use the branch-specific URL when you want to target a particular branch (e.g. ``main``, ``develop``).

----

Generating an API Key
---------------------

1. Navigate to the *API Keys* section in your *User Profile → API Keys* and click **Create API Key...**.
2. Copy the generated ``API Key`` - it is shown only once.
3. Store the key securely (e.g. in a password manager or CI secret store).

Use the API Key in:

- The ``--credentials`` parameter of any CLI command.
- The ``CHARON_API_KEY`` environment variable (the CLI reads it automatically).
- The ``Authenticate`` HTTP header when calling the REST API directly.

----

Authentication
--------------

Pass the API Key either as an explicit parameter or as an environment variable:

.. code-block:: bash

   # Explicit parameter
   charon DATA EXPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --output "./gamedata.json" \
     --outputFormat json \
     --credentials "<API-Key>"

.. code-block:: bash

   # Environment variable - picked up automatically by all commands
   export CHARON_API_KEY="<API-Key>"
   charon DATA EXPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --output "./gamedata.json" \
     --outputFormat json

The environment variable takes precedence when both are supplied. In CI pipelines, store the key as a
secret and inject it via ``CHARON_API_KEY`` rather than hard-coding it in pipeline files.

----

Common Operations
-----------------

Export Data
^^^^^^^^^^^

Export all documents (or a subset by schema) from a web project into a local file:

.. code-block:: bash

   # Export all schemas
   charon DATA EXPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --output "./gamedata.json" \
     --outputFormat json \
     --credentials "<API-Key>"

   # Export a specific schema
   charon DATA EXPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --schemas Character \
     --output "./characters.json" \
     --outputFormat json \
     --credentials "<API-Key>"

   # Export publication-ready data (strips non-essential fields)
   charon DATA EXPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --mode publication \
     --output "./StreamingAssets/gamedata.json" \
     --outputFormat json \
     --credentials "<API-Key>"

Import Data
^^^^^^^^^^^

Push local edits back to the web project:

.. code-block:: bash

   # Update existing documents (safe - no creates or deletes)
   charon DATA IMPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --schemas Character \
     --input "./characters.json" \
     --inputFormat json \
     --mode safeUpdate \
     --credentials "<API-Key>"

   # Create and update documents
   charon DATA IMPORT \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --input "./gamedata.json" \
     --inputFormat json \
     --mode createAndUpdate \
     --credentials "<API-Key>"

Generate Source Code
^^^^^^^^^^^^^^^^^^^^

Generate C# classes directly from the web project without downloading the data first:

.. code-block:: bash

   charon GENERATE CSHARPCODE \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --namespace "MyGame.Parameters" \
     --outputDirectory "./Assets/Scripts/Generated" \
     --clearOutputDirectory \
     --credentials "<API-Key>"

Validate Data
^^^^^^^^^^^^^

Check data integrity - useful before a release or as a CI gate:

.. code-block:: bash

   # Print a validation report to stdout
   charon DATA VALIDATE \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --validationOptions checkRequirements checkReferences checkFormat \
     --credentials "<API-Key>"

   # Exit with code 1 if any errors are found (CI-friendly)
   charon DATA VALIDATE \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --validationOptions checkRequirements checkReferences checkFormat \
     --output err \
     --credentials "<API-Key>"

Backup
^^^^^^

Create a local backup archive of a web project:

.. code-block:: bash

   charon DATA BACKUP \
     --dataBase "https://charon.live/view/data/My_Game/develop/" \
     --output "./backup_my_game.zip" \
     --credentials "<API-Key>"

----

See also
--------

- :doc:`Command Line Interface (CLI) <../advanced/command_line>`
- :doc:`Migrating to Web <migrating_to_web>`
- :doc:`REST API <rest>`
- :doc:`CI/CD Integration <../advanced/cicd>`
- :doc:`DATA EXPORT Command <../advanced/commands/data_export>`
- :doc:`DATA IMPORT Command <../advanced/commands/data_import>`
- :doc:`DATA VALIDATE Command <../advanced/commands/data_validate>`
- :doc:`DATA BACKUP Command <../advanced/commands/data_backup>`
- :doc:`GENERATE CSHARPCODE Command <../advanced/commands/generate_csharp_code>`
- :doc:`URL-based Input/Output <../advanced/commands/remote_input_output>`
