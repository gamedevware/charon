Find Document
===============

Seaches for a document.

- `Installation <../command_line.rst#installation>`_
- `Commands Reference <../command_line.rst>`_
- `Universal Parameters <universal_parameters.rst>`_
- `URL-based Input/Output <remote_input_output.rst>`_

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA FIND --dataBase "c:\my app\gamedata.json" --schema Character --id John
  
  # remote game data
  Charon.exe DATA FIND --dataBase "https://charon.live/view/data/My_Game/develop/" --schema Character --id John --credentials "<API-Key>"
  
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
     
--schema
   Name or identifier of the type (schema) of document.
     
   .. code-block:: bash

     # name
     --schema Item
     
     # id
     --schema 55a4f32faca22e191098f3d9
     
--id
   Identifier of document. 

   .. code-block:: bash

     # text
     --id Sword
     
     # number
     --id 101

--output
   Path to a found document file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <remote_input_output.rst>`_.
  
   .. code-block:: bash

     # standart output (default)
     --output out
     --output con

     # standart error
     --output err
     
     # null device
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
