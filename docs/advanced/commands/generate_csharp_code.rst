Start in standalone mode
========================

Generates C# source code for game data into output directory.

This command does not delete previously generated files, and it is the responsibility of the user to ensure that any previous files are removed before running the command again.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe Charon.exe GENERATE CSHARPCODE --dataBase "c:\my app\gamedata.json" --namespace "MyGame.Parameters" --outputDirectory "c:\my app\scripts"
  
  # Linux or OSX
  mono Charon.exe Charon.exe GENERATE CSHARPCODE --dataBase "~/gamedata.json" --namespace "MyGame.Parameters" --outputDirectory "~/my app/scripts"
  
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
     
--outputDirectory
   Specifies the path where the source code should be written. It can be either an absolute or relative path to a directory. The specified directory must already be present.

   .. code-block:: bash
   
     # Windows
     --outputDirectory "c:\my app\scripts"
     
     # Linux or OSX
     --outputDirectory "~/my app/templates"
     
     # Relative path
     --outputDirectory "./my app/templates"
 
--documentClassName
   Name for base class for all documents.

   .. code-block:: bash
   
     # name (default)
     --documentClassName Document
     
     # in case of name collision
     --documentClassName GameDataDocument
     
--gameDataClassName
   Name for class containing whole in-memory game data.

   .. code-block:: bash
   
     # name (default)
     --gameDataClassName GameData
     
     # in case of name collision
     --gameDataClassName MyGameData
     
--namespace
   Namespace for all generated classes.
   
   .. code-block:: bash
   
     # name (default)
     --namespace GameParameters
    
--indentation
   Indentation style for generated code.
   
   .. code-block:: bash
   
     # Tabs (default)
     --indentation Tabs
     
     # Two spaces
     --indentation TwoSpaces
     
     # Four spaces
     --indentation FourSpaces
     
--lineEndings
   Line ending symbols for generated code.
   
   .. code-block:: bash
   
     # Windows \\r\\n (default)
     --lineEndings Windows
     
     # Unix style \\n
     --lineEndings Unix
     
--splitFiles
   Set this flag to lay out generated classes into separate files. If not set, then one giant file with the name of ``--gameDataClassName``.cs will be generated.

--optimizations
   List of enabled optimization in generated code.
   
   .. code-block:: bash
   
     # Follow all references during loading to ensure no broken references exist. 
     # This will result in longer loading times.
     --optimizations eagerReferenceResolution
     
     # Expose raw Reference and ReferenceCollection properties instead of hiding them behind their values.
     --optimizations rawReferences
     
     # Expose raw LocalizedText properties instead of hiding them as ``string``.
     --optimizations rawLocalizedStrings
     
     # Disable the string de-duplication algorithm during loading. 
     # This will result in shorter loading times, but with the downside of increased memory usage.
     --optimizations disableStringOptimization
     
     # Exclude JSON-related code to reduce generated code size 
     --optimizations disableJsonSerialization
     
     # Exclude Message Pack-related code to reduce generated code size
     --optimizations disableMessagePackSerialization
     
     # Exclude code responsible to patch loading to reduce generated code size
     --optimizations disablePatching
     
