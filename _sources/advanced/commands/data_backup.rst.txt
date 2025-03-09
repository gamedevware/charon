Create Backup
=============

| Backs up game data to a specified file. Saved data could be later used with :doc:`DATA RESTORE <data_restore>` command.
| Also this command can be used to convert game data into different format.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dotnet charon DATA BACKUP --dataBase "c:\my app\gamedata.json" --output "c:\my app\backup.msgpkg" --outputFormat msgpack
  
  # remote game data
  dotnet charon DATA BACKUP --dataBase "https://charon.live/view/data/My_Game/develop/" --output "./backup.msgpkg" --outputFormat msgpack --credentials "<API-Key>"
  
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

--output
   Path to a backup file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.
  
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
     
     # remote location with authentication (FTP)
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
 
This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Output
------------------

The back up data follows the general :doc:`game data structure <../game_data_structure>`.