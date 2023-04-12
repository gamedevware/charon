Create Document
===============

| Creates a new document. For a bulk creations use `DATA IMPORT <data_import.rst>`_ command with ``--mode create``.
| Only the first document from the ``--input`` will be processed.

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA CREATE --dataBase "c:\my app\gamedata.json" --entity Item --input "c:\my app\item.json" --inputFormat json 

  # remote game data
  Charon.exe DATA CREATE --dataBase "https://charon.live/view/data/My_Game/develop/" --entity Item --input "./item.json" --inputFormat json --credentials "<API-Key>" 
  
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
     
--entity
   Name or identifier of the type (entity) of the new document.
     
   .. code-block:: bash

     # name
     --entity Item
     
     # id
     --entity 55a4f32faca22e191098f3d9
     
--input
   Path to a file with document. Alternatively, you can use `Standart Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or `URL <remote_input_output.rst>`_.

   .. code-block:: bash

     # standart input (default)
     --input in
     --input con

     # absolute path (windows)
     --input "c:\my app\item.json"
     
     # absolute path (unix)
     --input "/user/data/item.json"
     
     # relative path (universal)
     --input "./item.json"
     
     # remote location (HTTP)
     --input "http://example.com/item.json"
     
     # remote location with authentification (FTP)
     --input "ftp://user:password@example.com/item.json"
     
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

--inputFormattingOptions
   Additional options for specified format.
   
--output
   Path to a created document file. If the file exists, it will be overwritten. The directory must already exist. 
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
     --output "c:\my app\created_item.json"
     
     # absolute path (unix)
     --output /user/data/created_item.json
     
     # relative path (universal)
     --output "./created_item.json"
     
     # remote location (HTTP)
     --output "http://example.com/created_item.json"
     
     # remote location with authentification (FTP)
     --output "ftp://user:password@example.com/created_item.json"
     
--outputFormat
   Format of created data.
   
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
     
A list of documents is accepted:

   .. code-block:: js
   
     [
       {
         // <Document>
       }
     ]
     
And single document too:

   .. code-block:: js
   
     {
       // <Document>
     }
