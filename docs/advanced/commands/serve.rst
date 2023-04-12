Start in Standalone Mode
========================

Starts Charon in standalone mode for specified game data. Path to game data could be local file system's file or remote server address.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe SERVE --dataBase "c:\my app\gamedata.json" --port 8080 --launchDefaultBrowser
  
  # Linux or OSX
  mono Charon.exe SERVE --dataBase "~/gamedata.json" --port 8080 --launchDefaultBrowser
  
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

--port
   Number of an `IP port <https://en.wikipedia.org/wiki/Port_(computer_networking)>`_ (1-65535) to be used to listen for browser based UI.

   .. code-block:: bash
     --port 8080
  
--launchDefaultBrowser
   Set this flag to open system-default browser on successful start.

--resetPreferences
   Set this flag to reset UI preferences on successful start.
 
