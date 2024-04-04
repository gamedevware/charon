Game Data Structure
===================

The game data follow this structure, but additional properties are allowed at top level ``/``:

   .. code-block:: js
     
     {
       "ToolsVersion": "2023.1.2.0", // version of Charon which created this game data file
         
       "Collections": 
       {
         "Schema":
         [
           {
             "Id": "18d4bf318f3c49688087dbed",
             "Name": "<Name>"
             
             /* rest of properties of schema */
           }
         ],
         
         "ProjectSettings":
         [
           {
             "Id": "049bc0604c363a980b000088",
             "Name": "New Project",
             "PrimaryLanguage": "en-US",
             "Languages": null,
             "Version": "1.0.0.0",
             "Copyright": ""
           }
         ],
         
         "<Schema-Name>": 
         [
           {
             "Id": "<Id>" // Id is always present
             
             /* rest of properties of document */
           },
           // ...
         ]
       }
     }
     
or `JSON schema <https://json-schema.org/>`_:
     
   .. code-block:: js
     
     {
       "type": "object",
       "x-name": "GameData",
       "additionalProperties": true,
       "properties": {
         "ToolsVersion": {
           "type": "string"
         },
         "Collections": {
           "type": "object",
           "x-name": "GameDataCollections",
           "additionalProperties": {
             "type": "array",
             "items": {}
           }
         }
       }
     }
