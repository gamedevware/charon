Update Project Settings
=======================

.. versionadded:: vNext

Updates a single property of the project settings document (project name, copyright, languages, and other
project-level configuration) in game data.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # bump the game data version (windows)
  dnx dotnet-charon -- DATA UPDATEPROJECTSETTINGS \
    --dataBase "c:\my app\gamedata.json" \
    --property Version \
    --value "1.2.0.0"

  # the same property addressed by JSON Pointer
  dnx dotnet-charon -- DATA UPDATEPROJECTSETTINGS \
    --dataBase "c:\my app\gamedata.json" \
    --property /Version \
    --value "1.2.0.0"

  # rename the project
  dnx dotnet-charon -- DATA UPDATEPROJECTSETTINGS \
    --dataBase "c:\my app\gamedata.json" \
    --property Name \
    --value "My Project"

  # remote game data
  dnx dotnet-charon -- DATA UPDATEPROJECTSETTINGS \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --property Copyright \
    --value "My Company (c) 2025" \
    --credentials "<API-Key>"

There is always exactly one project settings document per game data source, so unlike
:doc:`DATA UPDATE <data_update>` this command takes no ``--schema``/``--id`` parameters - its identity is
fixed internally.

--------------------------
 Available Properties
--------------------------

One property is updated per command run. All project settings properties hold text values.

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - Property
     - Description
   * - ``Id``
     - Unique identifier of the project settings document (BSON ObjectId). Read-only - the command refuses
       to change it.
   * - ``Name``
     - Name of the project.
   * - ``PrimaryLanguage``
     - Primary language for localizable text (language ID in BCP-47 format, e.g. ``en-US``).
   * - ``Languages``
     - Alternative languages for localizable text (semicolon-delimited list of BCP-47 language IDs, e.g.
       ``en-GB;fr-FR``). Prefer :doc:`DATA I18N ADD LANGUAGE <data_i18n_add_language>` when adding a
       language, because it keeps the primary language out of the list and preserves existing entries.
   * - ``Copyright``
     - Copyright information for the project.
   * - ``Version``
     - Version of the current file as four dot-separated numbers (``Major.Minor.Build.Revision``).
   * - ``Extensions``
     - Installed extension packages as a semicolon-delimited list of ``name=version`` pairs.

See the :ref:`Project Settings <GameDataStructure_ProjectSettings>` section for the full field reference.
Any other property present in the document can be addressed the same way, by name or by
`JSON Pointer <https://datatracker.ietf.org/doc/html/rfc6901>`_.

---------------
 Parameters
---------------

--dataBase
   Absolute or relative path to game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash

     # local file
     --dataBase "c:\my app\gamedata.json"

     # remote server
     --dataBase "https://charon.live/view/data/My_Game/develop/"

--property
   Project settings property to update. Use a property name for top level values, or a
   `JSON Pointer <https://datatracker.ietf.org/doc/html/rfc6901>`_ starting with ``/`` to address nested
   values.

   .. code-block:: bash

     # top level property by name
     --property PrimaryLanguage

     # the same property as a JSON Pointer
     --property /PrimaryLanguage

     # nested value
     --property /Extensions/0

--value
   New value of the property. It is stored as text unless *--valueIsJson* is specified.

   .. code-block:: bash

     --value "en-GB;fr-FR"

--valueIsJson
   Treats *--value* as a JSON document and parses it, which allows storing numbers, booleans, arrays, and
   objects instead of text.

   .. code-block:: bash

     --property Version --valueIsJson --value "\"1.2.0.0\""

     --property Extensions --valueIsJson --value "null"

--credentials
   The API key used to access remote server in case of *--dataBase* being URL.

--output
   Path to the file receiving the updated document. If the file exists, it will be overwritten. The directory
   must already exist. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_,
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_,
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.

   .. code-block:: bash

     # standard output (default)
     --output out
     --output con

     # standard error
     --output err

     # null device
     --output null

     # absolute path (windows)
     --output "c:\my app\settings.json"

     # absolute path (unix)
     --output /user/data/settings.json

     # relative path (universal)
     --output "./settings.json"

     # remote location (HTTP)
     --output "http://example.com/settings.json"

     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/settings.json"

--outputFormat
   Specifies the format of the output data.

   .. code-block:: bash

     # JSON (default)
     --outputFormat json

     # BSON
     --outputFormat bson

     # Message Pack
     --outputFormat msgpack

--outputFormattingOptions
   Additional options for formatting the output.

This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Output
------------------

Outputs the updated project settings document.

.. code-block:: json

  {
    "Id": "55a4f32faca22e191098f3d9",
    "Name": "My Project",
    "PrimaryLanguage": "en-US",
    "Languages": "en-GB;fr-FR",
    "Copyright": "My Company (c) 2025",
    "Version": "1.2.0.0"
  }

See also
--------

- :doc:`DATA PROJECTSETTINGS <data_project_settings>`
- :doc:`DATA I18N ADD LANGUAGE <data_i18n_add_language>`
- :doc:`DATA UPDATE <data_update>`
- :doc:`Game Data Structure <../game_data_structure>`
