Delete Document
===============

Deletes a document. For a bulk deletion use :doc:`DATA IMPORT <data_import>` command with ``--mode delete``.

- :doc:`Installation <../command_line#installation>`
- :doc:`Commands Reference <../command_line>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

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
   The API key used to access remote server in case of *--dataBase* being URL.

--schema
   Name or identifier of the type (schema) of deleting document.
     
   .. code-block:: bash

     # name
     --schema Item
     
     # id
     --schema 55a4f32faca22e191098f3d9
     
--id
   Identifier of deleting document. 

   .. code-block:: bash

     # text
     --id Sword
     
     # number
     --id 101

--output
   The path to a file where the *deleted document* should be placed. If the file exists, it will be overwritten. The directory must already exist. 
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
     --output "c:\my app\deleted_item.json"
     
     # absolute path (unix)
     --output /user/data/deleted_item.json
     
     # relative path (universal)
     --output "./deleted_item.json"
     
     # remote location (HTTP)
     --output "http://example.com/deleted_item.json"
     
     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/deleted_item.json"
     
--outputFormat
   Format for deleted document.
   
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
 
This command supports :doc:`universal parameters <universal_parameters>`.
