Apply Patch
===========

Applies patch created with :doc:`DATA CREATEPATCH <commands/data_create_patch>` command to a game data.

- :doc:`Installation <../command_line:installation>`
- :doc:`Commands Reference <../command_line>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA APPLYPATCH --dataBase "c:\my app\gamedata.json" --input "c:\my app\gamedata_patch.json" --inputFormat json
  
  # remote game data
  Charon.exe DATA APPLYPATCH --dataBase "https://charon.live/view/data/My_Game/develop/" --input "./gamedata_patch.json" --inputFormat json --credentials "<API-Key>"
  
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

--input
   Path to a file with patch to apply. Alternatively, you can use `Standart Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or `URL <remote_input_output>`.

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
     
     # remote location with authentication (FTP)
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
 
This command supports :doc:`universal parameters <universal_parameters>`.
