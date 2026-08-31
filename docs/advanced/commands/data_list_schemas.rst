List Schemas
============

.. versionadded:: vNext

Lists schema definitions (document types) configured in game data.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dnx dotnet-charon -- DATA LISTSCHEMAS \
    --dataBase "c:\my app\gamedata.json"

  # remote game data
  dnx dotnet-charon -- DATA LISTSCHEMAS \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --credentials "<API-Key>"

This command lists the built-in ``Schema`` collection itself - the schema *documents* (definitions: name,
display name, properties, id generator, and so on), not the documents of a particular schema. It is the same
listing capability as :doc:`DATA LIST <data_list>`, just scoped internally to ``Schema`` instead of an
arbitrary ``--schema`` you provide. For full metadata (including computed/derived information used when
generating source code), use the ``data_get_metadata`` MCP tool or the metadata endpoint of a running server
instead.

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

--filters
   Schema filter expressions. Use the format ``<PropertyName> <Operation> <Value>``, e.g., ``Name == "Item"``.
   Multiple filters are ANDed together. For deeper paths use JSON Pointer format. Example:
   ``['/Item/Level', '>=', '10']``.

   .. code-block:: bash

     # patterns
     --filters <Field> <Operator> <Value> [<Field> <Operator> <Value>...]

     # single expression
     --filters Name == "Item"
     --filters DisplayName like "Item*"

     # multiple expressions
     --filters Type == 0 Name like "*Item*"

--sorters
   Sorting rules for the result set. Use the format ``<PropertyName> <ASC|DESC>``, e.g., ``Name ASC``. You can
   specify multiple sorters to sort by multiple fields. For deeper paths use JSON Pointer format. Example:
   ``['/Item/Name', 'ASC']``.

   .. code-block:: bash

     # patterns
     --sorters <Field> ASC|DESC [<Field> ASC|DESC ...]

     # ascending
     --sorters Name ASC

     # descending
     --sorters Name DESC

--select
   Projection of specific fields to include in the output. Use the format ``<PropertyName>``, e.g., ``Name``
   or ``Id``. Useful for reducing output size.

   .. code-block:: bash

     # only names and ids
     --select Id Name

--skip
   Number of schema definitions to skip from the start of the result set. Use for pagination.

   .. code-block:: bash

     # skip first ten schemas after applying --filters and --sorters
     --skip 10

--take
   Number of schema definitions to return after skipping. Use for limiting result size in combination with
   ``--skip``.

   .. code-block:: bash

     # limit to first 100 schemas after --skip
     --take 100

--output
   Path to a found document file. If the file exists, it will be overwritten. The directory must already exist.
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_,
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
     --output "c:\my app\schemas.json"

     # absolute path (unix)
     --output /user/data/schemas.json

     # relative path (universal)
     --output "./schemas.json"

     # remote location (HTTP)
     --output "http://example.com/schemas.json"

     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/schemas.json"

--outputFormat
   Format of exported data.

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
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Output
------------------

The result follows the general :doc:`game data structure <../game_data_structure>`, with schema documents
under the ``Schema`` collection key. See the :ref:`Schema <GameDataStructure_Schema>` section for the full
field reference.

.. code-block:: json

  {
    "Collections":
    {
      "Schema":
      [
        {
          "Id": "592fc86c983a36266c0912a0",
          "Name": "Item",
          "DisplayName": "Items",
          "Type": 0,
          "Description": "An item.",
          "IdGenerator": 1,
          "Specification": "icon=fugue16%2Fabacus&group=Metagame",
          "Properties": [
            // schema property
          ]
        },
        {
          "Id": "592fc86c983a36266c0912b1",
          "Name": "Character"

          /* rest of properties of schema document */
        },
        // ...
      ]
    }
  }

See also
--------

- :doc:`DATA LIST <data_list>`
- :doc:`DATA SEARCH <data_search>`
- :doc:`DATA FINDFILES <data_find_files>`
- :doc:`Game Data Structure <../game_data_structure>`
