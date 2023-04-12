Apply Patch
===========

Apply patch created by `DATA CREATEPATCH <commands/data_create_patch.rst>`_ to a game data.

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA APPLYPATCH --dataBase "c:\my app\gamedata.json" --input "c:\my app\gamedata_patch.json" --inputFormat json
  
  # remote game data
  Charon.exe DATA APPLYPATCH --dataBase "https://charon.live/view/data/My_Game/develop/" --input "./gamedata_patch.json" --inputFormat json --credentials <API-Key>
  
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
     
--input
   Path to a file with patch to apply. Alternatively, you can use `Standart Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or `URL <remote_input_output.rst>`_.

   .. code-block:: bash

     # standart input (default)
     --input in
     --input con

     # absolute path (windows)
     --input "c:\my app\gamedata_patch.json"
     
     # absolute path (unix)
     --input "/user/data/gamedata_patch.json"
     
     # relative path (universal)
     --input "./gamedata_patch.json"
     
     # remote location (HTTP)
     --input "http://example.com/gamedata_patch.json"
     
     # remote location with authentification (FTP)
     --input "ftp://user:password@example.com/gamedata_patch.json"
     
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
 
This command supports `universal parameters <universal_parameters.rst>`_.