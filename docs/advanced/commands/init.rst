Initialize Game Data
====================

Initializes an empty or missing file with initial data. Path to game data should be local file system's file.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`

---------------
 Command
---------------

.. code-block:: bash

  # full path (windows)
  dotnet charon INIT "c:\my app\gamedata.gdjs"
  
  # full path (linux)
  dotnet charon INIT "/var/mygame/gamedata.json"
  
  # relative path
  dotnet charon INIT mygame/gamedata.json
  
---------------
 Parameters
---------------

--fileName
   Absolute or relative path to game data file. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --fileName "c:\my app\gamedata.json"
