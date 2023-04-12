Import Data
===========

Imports documents from file to a game data.

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA IMPORT --dataBase "c:\my app\gamedata.json" --entities Character --input "c:\my app\characters.json" --inputFormat json --mode safeUpdate
  
  # remote game data
  Charon.exe DATA IMPORT --dataBase "https://charon.live/view/data/My_Game/develop/" --entities Character --input "./characters.json" --inputFormat json --mode safeUpdate --credentials "<API-Key>"
  
---------------
 Parameters
---------------

--dataBase
   Absolute or relative oath to game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --dataBase "c:\my app\gamedata.json"
     
     # remote server
     --dataBase "https://charon.live/view/data/My_Game/develop/"
     
--entities
   A list of types of documents (entities) to import. By default all entities *EXCEPT* metadata are imported.
       
   - Use space to separate multiple entities.
   - You can use wildcards (*) at the beginning and end of names.
   - You can use identifiers in {} instead of names.
   - You can exclude certain names by using an exclamation mark (!) at the beginning of their names.

   .. code-block:: bash
   
     # entity name
     --entities Character
     --entities Character Item
     
     # all (default)
     --entities * 
     
     # masks
     --entities Char*
     --entities *Modifier
     --entities *Mod*
     
     # entity id
     --entities {18d4bf318f3c49688087dbed}
     
     # negation
     --entities Char* !Character
     --entities !*Item*
     
--mode
   Import mode controls merge behavior during import.
   
   .. code-block:: bash
   
     # (default)
     --mode createAndUpdate
   
     --mode create
     --mode update
     --mode safeUpdate
     --mode replace
     --mode delete
   
   createAndUpdate
      creates new documents and updates existing ones 
   create
      only creates new documents, existing documents are kept unchanged
   update
      only updates existing documents, no new ones are created
   safeUpdate
      same as *update* but without creating, moving and erasing embedded documents
   replace
      replaces the entire collection with the imported documents
   delete
      deletes documents found in the imported data  
    
--input
   Path to a data file. Alternatively, you can use `Standart Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or `URL <remote_input_output.rst>`_.

   .. code-block:: bash

     # standart input (default)
     --input in
     --input con

     # absolute path (windows)
     --input "c:\my app\characters.json"
     
     # absolute path (unix)
     --input "/user/data/characters.json"
     
     # relative path (universal)
     --input "./characters.json"
     
     # remote location (HTTP)
     --input "http://example.com/characters.json"
     
     # remote location with authentification (FTP)
     --input "ftp://user:password@example.com/characters.json"
     
--inputFormat
   Format of imported data.
   
   .. code-block:: bash
   
     # Auto-detect by extension (default)
     --inputFormat auto
   
     # JSON
     --inputFormat json
     
     # BSON
     --inputFormat bson
     
     # Message Pack
     --inputFormat msgpack
     
     # XML
     --inputFormat xml
     
     # XLSX Spreadsheet
     --inputFormat xlsx

--inputFormattingOptions
   Additional options for specified format.
   
--dryRun
   Allows you to run the command without actually making any changes to the game data, providing a preview of what would happen.

This command supports `universal parameters <universal_parameters.rst>`_.

------------------
 Input Data Schema
------------------

The data you input should follow this schema (recommended):

   .. code-block:: js
     
     {
       "Collections": {
         "<EntityName>": [
           {
             // <Document>
           }
         ]
       }
     }
     
This schema is also accepted:

   .. code-block:: js
     
     {
       "<EntityName>": [
         {
           // <Document>
         }
       ]
     }
     
A list of documents is accepted if only one name in ``--entities`` is specified:

   .. code-block:: js
   
     [
       {
         // <Document>
       }
     ]
     
And single document is accepted too if only one name in ``--entities`` is specified:

   .. code-block:: js
   
     {
       // <Document>
     }
