Create Backup
=============

| Backs up game data to a specified file. Saved data could be later used with `DATA RESTORE <data_restore.rst>`_ command.
| Also this command can be used to convert game data into different format.

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA BACKUP --dataBase "c:\my app\gamedata.json" --output "c:\my app\backup.msgpkg" --outputFormat msgpack
  
  # remote game data
  Charon.exe DATA BACKUP --dataBase "https://charon.live/view/data/My_Game/develop/" --output "./backup.msgpkg" --outputFormat msgpack --credentials "<API-Key>"
  
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
     
--output
   Path to a backup file. If the file exists, it will be overwritten. The directory must already exist. 
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
 
This command supports `universal parameters <universal_parameters.rst>`_.

------------------
 Output Data Schema
------------------

The backed-up data follows the schema of game data <../game_data_schema.rst>_.
