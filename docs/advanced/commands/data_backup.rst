Create Backup
=============

Backs up game data to a specified file. Can be used to convert game data into different format.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe DATA BACKUP --dataBase "c:\my app\gamedata.json" --output "c:\my app\backup.msgpkg" --outputFormat msgpack
  
  # Linux or OSX
  mono Charon.exe DATA BACKUP --dataBase "~/gamedata.json" --output "~/backup.msgpkg" --outputFormat msgpack
  
  # With remote game data
  Charon.exe DATA BACKUP --dataBase "https://charon.live/view/data/My_Game/develop/" --output "./backup.msgpkg" --outputFormat msgpack --credentials 87758CC0D7C745D0948F2A8AFE61BC81
  
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
     
--output
   Path to a file to which data will be exported. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <universal_parameters.rst>`_.
  
   .. code-block:: bash

     # standart output (default)
     --output out
     --output con

     # standart error
     --output err
     
     # null device
     --output null
     
     # absolute path (windows)
     --output "c:\my app\backup.json"
     
     # absolute path (unix)
     --output "/user/data/backup.json"
     
     # relative path (universal)
     --output "./backup.json"
     
     # remote location (HTTP)
     --output "http://example.com/backup.json"
     
     # remote location with authentification (FTP)
     --output "ftp://user:password@example.com/backup.json"
     
--outputFormat
   Format of backed up data.
   
   .. code-block:: bash
    
     # JSON (default)
     --outputFormat json
     
     # Message Pack
     --outputFormat msgpack

--outputFormattingOptions
   Additional options for specified format.

------------------
 Output Data Schema
------------------

The backed up data follow `game data <../game_data_schema.rst>`_  schema.
