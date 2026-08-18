Project Settings
================

Retrieves the project settings document (languages, primary language, and other project-level configuration)
from game data.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  charon DATA PROJECTSETTINGS \
    --dataBase "c:\my app\gamedata.json"

  # remote game data
  charon DATA PROJECTSETTINGS \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --credentials "<API-Key>"

There is always exactly one project settings document per game data source, so unlike
:doc:`DATA FIND <data_find>` this command takes no ``--schema``/``--id`` parameters - its identity is fixed
internally.

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

--credentials
   The API key used to access remote server in case of *--dataBase* being URL.

--output
   Path to the retrieved document file. If the file exists, it will be overwritten. The directory must
   already exist. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_,
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_,
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.

   .. code-block:: bash

     # standart output (default)
     --output out
     --output con

     # standart error
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

Outputs the project settings document. See the
:ref:`Project Settings <GameDataStructure_ProjectSettings>` section for the full field reference.

.. code-block:: json

  {
    "Id": "55a4f32faca22e191098f3d9",
    "Name": "My Project",
    "PrimaryLanguage": "en-US",
    "Languages": "en-GB;fr-FR",
    "Copyright": "My Company (c) 2025",
    "Version": "1.0.0.0"
  }

See also
--------

- :doc:`DATA I18N LANGUAGES <data_i18n_languages>`
- :doc:`DATA FIND <data_find>`
- :doc:`Game Data Structure <../game_data_structure>`
