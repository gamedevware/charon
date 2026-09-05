Generate JSON Schema
====================

Generates a `JSON Schema <https://json-schema.org/>`_ (Draft-07) document describing the structure of your game data.

Unlike the source code generation commands, this one produces a single document instead of a directory of files, and it has no language, class name or optimization options.

The generated schema describes the game data file as a whole: the root object with its ``Collections`` map, and one ``definitions`` entry per schema in your project. Use it to:

- **Validate** exported game data in CI or in an asset pipeline with any JSON Schema validator (ajv, jsonschema, Json.Schema.Net).
- **Generate models** in languages Charon has no SDK for, with tools like quicktype, json-schema-to-typescript, NSwag or OpenAPI Generator. Such tools consume the ``#/definitions/*`` entries.
- **Get editor support** while editing game data by hand, by pointing a ``$schema`` key or an IDE schema mapping at the generated file.
- **Share the data format** with another team or tool without shipping the data itself.
- **Review data model changes** by regenerating the schema and diffing it.

The schema does not replace :doc:`validation <../validation>`: formulas, reference resolution and uniqueness rules can't be expressed in JSON Schema.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dnx dotnet-charon -- GENERATE JSONSCHEMA \
    --dataBase "c:\my app\gamedata.json" \
    --output "c:\my app\gamedata.schema.json"

  # remote game data
  dnx dotnet-charon -- GENERATE JSONSCHEMA \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --output "./gamedata.schema.json" \
    --credentials "<API-Key>"

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
   Destination of the generated schema. It can be a file path, ``out`` for standard output (default), ``err`` for standard error, or ``null`` to discard the result. An existing file is overwritten.

   .. code-block:: bash

     # file
     --output "./gamedata.schema.json"

     # standard output (default)
     --output out

--title
   Title of the root schema. By default, it is the name of the game data file.

   .. code-block:: bash

     --title "My Game Data"

This command supports :doc:`universal parameters <universal_parameters>`.

------------------------
 Validating game data
------------------------

Any JSON Schema validator accepts the generated document. For example, with `ajv-cli <https://github.com/ajv-validator/ajv-cli>`_:

.. code-block:: bash

  dnx dotnet-charon -- GENERATE JSONSCHEMA \
    --dataBase ./gamedata.json \
    --output ./gamedata.schema.json

  npx ajv-cli validate --spec=draft7 --strict=false \
    -s ./gamedata.schema.json \
    -d ./gamedata.json

``--strict=false`` is needed because the schema annotates numbers with ``int32``, ``float`` and similar formats, which ajv doesn't know by default.

See also
--------

- :doc:`Generating Source Code <../../gamedata/generating_source_code>`
- :doc:`GENERATE CSHARPCODE <generate_csharp_code>`
- :doc:`GENERATE TYPESCRIPTCODE <generate_typescript_code>`
- :doc:`DATA VALIDATE <data_validate>`
- :doc:`Publication <../../gamedata/publication>`
