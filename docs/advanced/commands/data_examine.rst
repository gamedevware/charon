Examine Game Data
=================

Returns quick statistics about game data: document counts per schema, metadata hash, and revision hash.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  charon DATA EXAMINE \
    --dataBase "c:\my app\gamedata.json"

  # remote game data
  charon DATA EXAMINE \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --credentials "<API-Key>"

Use this command to verify that a file is valid game data and get a cheap content overview - document counts
per schema, a metadata hash, and a revision hash - before running a heavier command such as
:doc:`DATA LIST <data_list>`, :doc:`DATA SEARCH <data_search>`, or :doc:`DATA VALIDATE <data_validate>`. It
does not load or validate document contents, so it stays fast even on large files.

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
   Path to the statistics output file. If the file exists, it will be overwritten. The directory must already
   exist. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_,
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
     --output "c:\my app\stats.json"

     # absolute path (unix)
     --output /user/data/stats.json

     # relative path (universal)
     --output "./stats.json"

     # remote location (HTTP)
     --output "http://example.com/stats.json"

     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/stats.json"

--outputFormat
   Format for serializing the output.

   .. code-block:: bash

     # JSON (default)
     --outputFormat json

     # BSON
     --outputFormat bson

     # Message Pack
     --outputFormat msgpack

     # XLSX Spreadsheet
     --outputFormat xlsx

--outputFormattingOptions
   Additional formatting options for the chosen output format.

This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Output
------------------

.. code-block:: json

  {
    "metadataHash": "3f1c2a9e7b0d4c5e8a1f6d2b",
    "revisionHash": "678f998993a22d1f54b7fa80",
    "toolsVersion": "2025.1.1.0",
    "changeNumber": 42,
    "collections":
    [
      {
        "schemaName": "Character",
        "schemaId": "592fc86c983a36266c0912b1",
        "documentCount": 128,
        "rootDocumentCount": 128,
        "validationErrorCount": {}
      },
      {
        "schemaName": "Item",
        "schemaId": "592fc86c983a36266c0912a0",
        "documentCount": 340,
        "rootDocumentCount": 210,
        "validationErrorCount": {}
      }
      // ...
    ]
  }

``documentCount`` includes documents embedded inside other documents; ``rootDocumentCount`` counts only
top-level documents in the collection. ``validationErrorCount`` maps validation error codes to their
occurrence count and is empty when no errors were found during the examine pass.

See also
--------

- :doc:`DATA FINDFILES <data_find_files>`
- :doc:`DATA VALIDATE <data_validate>`
- :doc:`DATA LIST <data_list>`
