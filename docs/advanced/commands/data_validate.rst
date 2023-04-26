Validate Game Data
===============

Checks the game data for validity and produces a report.

The exit code will be ``1`` if the report contains errors and the ``--output`` is set to ``err``. Otherwise, the exit code will be ``0``.

- `Installation <../command_line.rst#installation>`_
- `Commands Reference <../command_line.rst>`_
- `Universal Parameters <universal_parameters.rst>`_
- `URL-based Input/Output <remote_input_output.rst>`_

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA DELETE --dataBase "c:\my app\gamedata.json" --schema Item --id "Sword"
  
  # remote game data
  Charon.exe DATA DELETE --dataBase "https://charon.live/view/data/My_Game/develop/" --schema Item --id "Sword" --credentials "<API-Key>"
  
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
   The API key used to access remote server in case of `--dataBase` being URL.

--validationOptions
   List of validation checks and repairs to perform.
     
   .. code-block:: bash

     # repairs
     --validationOptions repair     
     --validationOptions deduplicateIds
     --validationOptions repairRequiredWithDefaultValue
     --validationOptions eraseInvalidValue
     
     # checks (default)
     --validationOptions checkTranslation
     --validationOptions checkRequirements
     --validationOptions checkFormat
     --validationOptions checkUniqueness
     --validationOptions checkReferences
     --validationOptions checkSpecification
     --validationOptions checkConstraints

--output
   Path to a validation report file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <remote_input_output.rst>`_.
  
   .. code-block:: bash

     # standart output
     --output out
     --output con

     # standart error
     --output err
     
     # null device (default)
     --output null
     
     # absolute path (windows)
     --output "c:\my app\document.json"
     
     # absolute path (unix)
     --output /user/data/document.json
     
     # relative path (universal)
     --output "./document.json"
     
     # remote location (HTTP)
     --output "http://example.com/document.json"
     
     # remote location with authentification (FTP)
     --output "ftp://user:password@example.com/document.json"
     
--outputFormat
   Format of exported data.
   
   .. code-block:: bash
    
     # JSON (default)
     --outputFormat json
     
     # BSON
     --outputFormat bson
     
     # Message Pack
     --outputFormat msgpack
     
     # XML
     --outputFormat xml
     
--outputFormattingOptions
   Additional options for specified format.

This command supports `universal parameters <universal_parameters.rst>`_.

------------------
 Output Data Schema
------------------

The report follow this pattern:

   .. code-block:: js
   
     {
       records: 
       [
         {
           id: "<document-id>",
           schemaId: "<schema-id>",
           schemaName: "<schema-name>",
           errors: // could be null if no errors
           [
             {
               path: "<path-in-document>",
               message: "<error-message>",
               code: "<error-code>"
             },
             // ...
           ]
         },
         // ...
       ]
     }
     
or `JSON schema <https://json-schema.org/>`_:

   .. code-block:: json
   
     {
       "type": "object",
       "x-name": "ValidationReport",
       "additionalProperties": false,
       "properties": {
         "records": {
           "type": "array",
           "items": {
             "type": "object",
             "x-name": "ValidationRecord",
             "additionalProperties": false,
             "properties": {
               "id": { },
               "schemaName": {
                 "type": "string"
               },
               "schemaId": {
                 "type": "string"
               },
               "errors": {
                 "type": "array",
                 "items": {
                   "type": "object",
                   "x-name": "ValidationError",
                   "additionalProperties": true,
                   "readOnly": true,
                   "properties": {
                     "path": {
                       "type": "string"
                     },
                     "message": {
                       "type": "string"
                     },
                     "code": {
                       "type": "string"
                     }
                   }
                 }
               }
             }
           }
         },
         "metadataHashCode": {
           "type": "integer",
           "format": "int32"
         }
       }
     }
