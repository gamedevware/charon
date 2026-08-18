Find Game Data Files
====================

Scans a folder for game data files and returns discovered paths with their collection statistics.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # scan a folder tree, JSON output (default)
  charon DATA FINDFILES \
    --folder "c:\my app\game-content"

  # scan a folder tree, one path per line for shell piping
  charon DATA FINDFILES \
    --folder "c:\my app\game-content" \
    --resultFormat list \
    --output out | xargs -I{} charon DATA EXAMINE --dataBase "{}"

Use this command to bootstrap work in an unfamiliar directory tree - "what game data lives here?" - before
picking a file to pass to :doc:`DATA EXAMINE <data_examine>`, :doc:`DATA LIST <data_list>`, or
:doc:`DATA SEARCH <data_search>`. Only files with recognized formatter extensions (``.json``, ``.bson``,
``.msgpack``, ``.xlsx``, ...) are considered, and each candidate is probed - reading only its first 4 KB
for the ``Collections`` marker - before a full load, so the scan stays fast even on large directory trees
full of unrelated files.

---------------
 Parameters
---------------

--folder
   Path to the folder to scan.

   .. code-block:: bash

     # local folder
     --folder "c:\my app\game-content"
     --folder /home/user/game-content

--recursive
   When ``true`` (default), scans all sub-folders recursively.

   .. code-block:: bash

     # scan sub-folders too (default)
     --recursive true

     # scan only the top-level folder
     --recursive false

--outputFormat
   Output shape.

   .. code-block:: bash

     # JSON array of `{path, collections}` objects, matching the MCP `data_find_files` tool (default)
     --resultFormat json

     # one file path per line, for shell piping (e.g. `xargs`, `for` loops)
     --resultFormat list

--output
   Specifies where to write the output data.

   .. code-block:: bash

     # standart output (default)
     --output out
     --output con

     # standart error
     --output err

     # null device
     --output null

     # absolute path (windows)
     --output "c:\my app\found-files.json"

     # absolute path (unix)
     --output /user/data/found-files.json

     # relative path (universal)
     --output "./found-files.json"

     # remote location (HTTP)
     --output "http://example.com/found-files.json"

     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/found-files.json"

--credentials
   Supplies authentication credentials for accessing discovered files if they're located on a remote server.
   Credentials can also be provided via the ``CHARON_API_KEY`` environment variable.

This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Output
------------------

``--resultFormat json`` (default) writes an array of ``{path, collections}`` objects, where ``collections``
maps each schema name found in that file to its document count:

.. code-block:: json

  [
    {
      "path": "C:/my app/game-content/characters.json",
      "collections":
      {
        "Character": 128,
        "Item": 340
      }
    },
    {
      "path": "C:/my app/game-content/quests.xlsx",
      "collections":
      {
        "Quest": 56
      }
    }
  ]

``--resultFormat list`` writes one absolute file path per line, with no other formatting - suitable for
piping into ``xargs`` or a shell ``for`` loop:

.. code-block:: text

  C:/my app/game-content/characters.json
  C:/my app/game-content/quests.xlsx

See also
--------

- :doc:`DATA EXAMINE <data_examine>`
- :doc:`DATA LIST <data_list>`
- :doc:`DATA SEARCH <data_search>`
