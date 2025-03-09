Add Translation Languages
=========================

Add translation languages to specified game data.

- :ref:`CLI Installation <CommandLine_Installation>`
- :doc:`Universal Parameters <universal_parameters>`
- :ref:`Commands Reference <CommandLine_Commands>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dotnet charon DATA I18N ADDLANGUAGE --dataBase "c:\my app\gamedata.json" --languages "es-ES" "en-GB"
  
  # remote game data
  dotnet charon DATA I18N ADDLANGUAGE --dataBase "https://charon.live/view/data/My_Game/develop/" --languages "es-ES" "en-GB" --credentials "<API-Key>"

  
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

--languages
   The list of languages to add. Values are `language tags (BCP 47) separated by space. <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_. 
   
This command supports :doc:`universal parameters <universal_parameters>`.