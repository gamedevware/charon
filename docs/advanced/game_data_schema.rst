------------------
 Game Data Schema
------------------

The game data follow this pattern, but additional properties are allowed at top level ``/``:

   .. code-block:: js
     
     {
       "ToolsVersion": "2023.1.2.0", // example version
         
       "Collections": 
       {
         "Entity":
         [
           {
             "Id": "18d4bf318f3c49688087dbed", // example id
             "Name": "<Name>"
             
             // rest of entity
           }
         ],
         
         "ProjectSettings":
         [
           {
             "Id": "049bc0604c363a980b000088", // expected id from starter template
             "Name": "New Project",
             "PrimaryLanguage": "en-US",
             "Languages": null,
             "Version": "1.0.0.0",
             "Copyright": ""
           }
         ],
         
         "<Entity-Name>": 
         [
           {
             "Id": "<Id>"
             
             // rest of document
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
