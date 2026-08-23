Search Documents
================

Searches for documents across all schemas using a text query with wildcard matching.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows), default table output
  charon DATA SEARCH \
    --dataBase "c:\my app\gamedata.json" \
    --query Dragon

  # remote game data, full documents as JSON
  charon DATA SEARCH \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --query Dragon \
    --outputFormat json \
    --credentials "<API-Key>"

Unlike :doc:`DATA LIST <data_list>`, which requires a ``--schema`` and matches one field at a time via
``--filters``, ``DATA SEARCH`` matches the query text against *every field of every document*, across
schemas, using a ``contains`` (LIKE) operator. Use it to find where a value shows up when you don't know
which schema or field it lives in; use ``DATA LIST`` once you do.

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

--query
   Text to search for across all document fields. Matches using 'contains' (LIKE) operator against every
   field.

   .. code-block:: bash

     # matches any document with 'Dragon' in any field value
     --query Dragon

--caseSensitive
   Whether the search should be case-sensitive. Default is ``false`` (case-insensitive).

   .. code-block:: bash

     --caseSensitive true
     --caseSensitive false

--schemas
   Defines which schemas to search. Accepts a list of schema names. If omitted, all schemas are searched.

   .. code-block:: bash

     # single schema
     --schemas Item

     # multiple schemas
     --schemas Item Character

     # masks
     --schemas *Item*

     # negation
     --schemas !DeprecatedSchema

--skip
   Number of matches to skip from the start of the result set. Use for pagination.

   .. code-block:: bash

     # skip first ten matches
     --skip 10

--take
   Number of matches to return after skipping. Use for limiting result size in combination with ``--skip``.

   .. code-block:: bash

     # limit to first 100 matches after --skip
     --take 100

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
     --output "c:\my app\results.json"

     # absolute path (unix)
     --output /user/data/results.json

     # relative path (universal)
     --output "./results.json"

     # remote location (HTTP)
     --output "http://example.com/results.json"

     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/results.json"

--outputFormat
   Format for serializing the output. Only used when ``--outputFormat json``; ignored for ``table``.

   .. code-block:: bash

     # flat `Schema|Document Id|Path|Value` rows, script/grep-friendly (default)
     --outputFormat table

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

``--outputFormat table`` (default) writes one line per match, pipe-delimited, with a header row - convenient
for ``grep``/``cut``/``awk``:

.. code-block:: text

  Schema|Document Id|Path|Value
  Character|Knight|/Description|A knight who slays dragons for gold.
  Item|DragonScale|/Name|Dragon Scale
  Quest|SlayTheDragon|/Name|Slay the Dragon

The ``Path`` column is empty for root documents and holds the embedding property's JSON Pointer path
(e.g. ``/Item``) for documents embedded inside another document.

``--outputFormat json`` writes the matched documents in full, grouped back into their schema collections, in
the same shape as :doc:`DATA EXPORT <data_export>`'s ``ExportResult``:

.. code-block:: json

  {
    "Collections":
    {
      "Character":
      [
        {
          "Id": "Knight"

          /* rest of properties of document */
        }
      ],
      "Item":
      [
        {
          "Id": "DragonScale"

          /* rest of properties of document */
        }
      ]
    }
  }

See also
--------

- :doc:`DATA LIST <data_list>`
- :doc:`DATA LISTSCHEMAS <data_list_schemas>`
- :doc:`DATA FIND <data_find>`
- :doc:`DATA FINDFILES <data_find_files>`
- :doc:`DATA EXPORT <data_export>`
