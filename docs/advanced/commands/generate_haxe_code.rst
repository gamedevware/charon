Generate Haxe Source Code
========================

Generates Haxe source code for game data into output directory.

This command does not delete previously generated files, and it is the responsibility of the user to ensure that any previous files are removed before running the command again.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dotnet charon GENERATE HAXE --dataBase "c:\my app\gamedata.json" --packageName "" --outputDirectory "c:\my app\scripts"

  # remote game data
  dotnet charon GENERATE HAXE --dataBase "https://charon.live/view/data/My_Game/develop/" --packageName "" --outputDirectory "./scripts" --credentials "<API-Key>"
  
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

--outputDirectory
   Specifies the path where the source code should be written. It can be either an absolute or relative path to a directory. The specified directory must already be present.

   .. code-block:: bash
   
     # Windows
     --outputDirectory "c:\my app\scripts"
     
     # Linux or OSX
     --outputDirectory "~/my app/scripts"
     
     # Relative path
     --outputDirectory "./my app/scripts"

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
     
--packageName
   Package name for all generated classes.
   
   .. code-block:: bash

     # empty package (default)
     --packageName ""
   
     # named
     --packageName GameParameters
     

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
   Set this flag to lay out generated classes into separate files. If not set, then one giant file with the name of ``--gameDataClassName``.hx will be generated.

--optimizations
   List of enabled optimization in generated code.
   
   .. code-block:: bash
   
     # Eagerly resolves and validates all references in loaded documents.
     # When enabled, this optimization ensures that all references in documents are resolved and validated
     # during loading. This comes with a performance cost but guarantees the validity of references.
     --optimizations eagerReferenceResolution
     
     # Opts for raw references without generating helper methods for referenced documents.
     # With this optimization, the generated code will not include helper methods for accessing
     # referenced documents, keeping only accessors that work with raw references.
     --optimizations rawReferences
     
     # Avoids generating helper methods for localized strings, keeping only raw accessors.
     # This optimization eliminates helper methods for accessing localized text, instead providing
     # accessors that deal directly with lists of localized texts.
     --optimizations rawLocalizedStrings
     
     # Disables string pooling during game data loading.
     # Turning off string pooling can yield a minor performance improvement at the cost of increased
     # memory usage, as it avoids reusing short strings.
     --optimizations disableStringPooling
     
     # Disables generation of code for loading game data from JSON formatted files.
     # This optimization omits code related to JSON serialization, useful when JSON formatted
     # game data is not used.
     --optimizations disableJsonSerialization
     
     # Disables generation of code for loading game data from Message Pack formatted files.
     # Similar to DisableJsonSerialization, this option removes code related to loading data
     # from Message Pack formatted files.
     --optimizations disableMessagePackSerialization
     
     # Disables generation of code related to applying patches during game data loading.
     # This removes a significant portion of code that is mainly used for modding support,
     # where patches are applied to game data at runtime.
     --optimizations disablePatching
     
     # Disables generation of enums with known document IDs.
     # This removes a significant portion of code that contains listings of IDs for
     # documents known at the moment of code generation, which improves compilation time.
     --optimizations disableDocumentIdEnums

--clearOutputDirectory
   Clear the output directory from generated files. Generated files are identified by the presence of the '<auto-generated>' tag inside.

This command supports :doc:`universal parameters <universal_parameters>`.

