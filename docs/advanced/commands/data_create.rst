Create Document
===============

| Creates a new document. For a bulk creations use :doc:`DATA IMPORT <data_import>` command with ``--mode create``.
| Only the first document from the ``--input`` will be processed.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dotnet tool charon DATA CREATE --dataBase "c:\my app\gamedata.json" --schema Item --input "c:\my app\item.json" --inputFormat json 

  # remote game data
  dotnet tool charon DATA CREATE --dataBase "https://charon.live/view/data/My_Game/develop/" --schema Item --input "./item.json" --inputFormat json --credentials "<API-Key>" 
  
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

--schema
   Name or identifier of the type (schema) of the new document.
     
   .. code-block:: bash

     # name
     --schema Item
     
     # id
     --schema 55a4f32faca22e191098f3d9
     
--input
   Path to a file with document. Alternatively, you can use `Standart Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or :doc:`URL <remote_input_output>`.

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
     
     # remote location with authentication (FTP)
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
     
     # XML (removed in 2025.1.1) 
     --inputFormat xml

--inputFormattingOptions
   Additional options for specified format.
   
--output
   Path to a created document file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.
  
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
     
     # remote location with authentication (FTP)
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
     
     # XML (removed in 2025.1.1) 
     --outputFormat xml
     
--outputFormattingOptions
   Additional options for specified format.
 
This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Input Data Schema
------------------

The data you input should follow this schema (recommended):

   .. code-block:: js
     
     {
       "Collections": {
         "<Schema-Name>": [
           {
             // <Document>
           }
         ]
       }
     }
     
This schema is also accepted:

   .. code-block:: js
     
     {
       "<Schema-Name>": [
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
