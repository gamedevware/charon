Create Patch
===========

Outputs the differences between two game datas as a file that can be used later to `DATA APPLYPATCH <data_apply_patch.rst>`_ to another game data.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe DATA CREATEPATCH --dataBase "c:\my app\gamedata.json" --input "c:\my app\gamedata_patch.json" --inputFormat json
  
  # Linux or OSX
  mono Charon.exe DATA CREATEPATCH --dataBase "~/gamedata.json" --input "~/gamedata_patch.json" --inputFormat json
  
---------------
 Parameters
---------------

--dataBase1
   Absolute or relative oath to a first game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --dataBase1 "c:\my app\gamedata.json"
     
     # remote server
     --dataBase1 "https://charon.live/view/data/My_Game/develop/"
     
--dataBase2
   Absolute or relative oath to a second game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --dataBase2 "c:\my app\gamedata.json"
     
     # remote server
     --dataBase2 "https://charon.live/view/data/My_Game/develop/"
     
--output
   Path to a file to which patch will be saved. If the file exists, it will be overwritten. The directory must already exist. 
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
     --output "c:\my app\gamedata_patch.json"
     
     # absolute path (unix)
     --output /user/data/gamedata_patch.json
     
     # relative path (universal)
     --output "./gamedata_patch.json"
     
     # remote location (HTTP)
     --output "http://example.com/gamedata_patch.json"
     
     # remote location with authentification (FTP)
     --output "ftp://user:password@example.com/gamedata_patch.json"
     
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

--credentials
   This parameter sets the API key used to access *BOTH* remote servers. 
   If this is not suitable, consider `downloading <https://github.com/gamedevware/charon/blob/main/docs/advanced/commands/data_backup.rst>`_ the data locally and running this command on local files instead.
