Start in Standalone Mode
========================

Starts Charon in standalone mode for specified game data. Path to game data could be local file system's file or remote server address.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  charon SERVER START --dataBase "c:\my app\gamedata.json" --port 8080 --launchDefaultBrowser
  
  # shortcut version
  charon "c:\my app\gamedata.json"
  
---------------
 Parameters
---------------

--dataBase
   Absolute or relative path to game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --dataBase "c:\my app\gamedata.json"

--port
   Number of an `IP port <https://en.wikipedia.org/wiki/Port_(computer_networking)>`_ (1-65535) to be used to listen for browser based UI.

   .. code-block:: bash
   
     --port 8080
  
--launchDefaultBrowser
   Set this flag to open system-default browser on successful start.

--denySchemaEditing 
   Disable the ability to change the data structure (metadata) for editable game data.

--resetPreferences
   Set this flag to reset UI preferences on successful start.
 
This command supports :doc:`universal parameters <universal_parameters>`.
