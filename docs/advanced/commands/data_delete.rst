Delete Document
===============

Deletes a document. For a bulk deletion use `DATA IMPORT <data_import.rst>`_ command with ``--mode delete``.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe DATA DELETE --dataBase "c:\my app\gamedata.json" --entity Item --id "Sword"
  
  # Linux or OSX
  mono Charon.exe DATA DELETE --dataBase "c:\my app\gamedata.json" --entity Item --id "Sword"
  
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
   Name or identifier of the type (entity) of deleting document.
     
   .. code-block:: bash

     # name
     --entity Item
     
     # id
     --entity 55a4f32faca22e191098f3d9
     
--id
   Identifier of deleting document. 

   .. code-block:: bash

     # text
     --id Sword
     
     # number
     --id 101

--output
   Path to a deleted document file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <universal_parameters.rst>`_.
  
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
   Format of deleted data.
   
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
