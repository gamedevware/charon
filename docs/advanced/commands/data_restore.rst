Restore from Backup
===================

Restores game data from a file created by :doc:`DATA BACKUP <data_backup>` command.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
   charon DATA RESTORE --dataBase "c:\my app\gamedata.json" --input "c:\my app\backup.msgpkg" --inputFormat msgpack

  # remote game data
   charon DATA RESTORE --dataBase "https://charon.live/view/data/My_Game/develop/" --input "./backup.msgpkg" --inputFormat msgpack --credentials "<API-Key>"
  
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
   Path to a backup file. Alternatively, you can use `Standart Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or :doc:`URL <remote_input_output>`.

   .. code-block:: bash

     # standart input (default)
     --input in
     --input con

     # absolute path (windows)
     --input "c:\my app\backup.json"
     
     # absolute path (unix)
     --input "/user/data/backup.json"
     
     # relative path (universal)
     --input "./backup.json"
     
     # remote location (HTTP)
     --input "http://example.com/backup.json"
     
     # remote location with authentication (FTP)
     --input "ftp://user:password@example.com/backup.json"
     
--inputFormat
   Format of imported data.
   
   .. code-block:: bash
   
     # Auto-detect by extension (default)
     --inputFormat auto
   
     # JSON
     --inputFormat json

     # Message Pack
     --inputFormat msgpack

--inputFormattingOptions
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.
