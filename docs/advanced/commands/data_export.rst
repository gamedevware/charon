Export Data
===========

Exports documents into a file.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dotnet charon DATA EXPORT --dataBase "c:\my app\gamedata.json" --schemas Character --output "c:\my app\characters.json" --outputFormat json
  
  # remote game data
  dotnet charon DATA EXPORT --dataBase "https://charon.live/view/data/My_Game/develop/" --schemas Character --output "./characters.json" --outputFormat json --credentials "<API-Key>"
  
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

--schemas
   A list of types of documents (schemas) to export. By default all schemas *EXCEPT* metadata are exported.

   - Use space to separate multiple schemas.
   - You can use wildcards (*) at the beginning and end of names.
   - You can use identifiers in {} instead of names.
   - You can exclude certain names by using an exclamation mark (!) at the beginning of their names.

   .. code-block:: bash
   
     # schema name
     --schemas Character
     --schemas Character Item
     
     # all (default)
     --schemas * 
     
     # masks
     --schemas Char*
     --schemas *Modifier
     --schemas *Mod*
     
     # schema id
     --schemas {18d4bf318f3c49688087dbed}
     
     # negation
     --schemas Char* !Character
     --schemas !*Item*
     
--properties
   A list of properties or property types to export. By default all properties are exported.
   
   - *Id* property always included
   - Use space to separate multiple properties.
   - You can use wildcards (*) at the beginning and end of names.
   - You can use identifiers in {} instead of names.
   - You can exclude certain names by using an exclamation mark (!) at the beginning of their names.
   - You can use data type in [] instead of names.
   
--languages
   List of languages to keep in exported data. Language's `english name <https://docs.microsoft.com/en-us/dotnet/api/system.globalization.cultureinfo.englishname?view=netframework-4.8>`_ is used or `language tag (BCP 47) <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_. 
   
   Use :doc:`DATA I18N LANGUAGES <data_i18n_languages>` to get list of used languages.
   
   - Use space to separate multiple languages
   - You can use wildcards (*) at the beginning and end of names.
   - You can use LCID or `CultureInfo.Name <https://docs.microsoft.com/en-us/dotnet/api/system.globalization.cultureinfo.name?view=netframework-4.8>`_ in {} instead of the name.
   - You can exclude certain names by using an exclamation mark (!) at the beginning of their names.
   
   .. code-block:: bash
     
     # language tag (BCP 47)
     --languages {en-US}
     
     # language name
     --languages "Spanish (Spain)"
     
     # language name mask
     --languages Spanish*
     
     # language LCID
     --languages {3082}
     
     # negation and masks
     --languages !Spanish*
     --languages Spanish* !{es-Es}

--mode
   Export mode controls stripping and inclusion rules for exported data.

   .. code-block:: bash
      
     # (default)   
     --mode normal  
     
     --mode publication
     --mode extraction
     --mode localization

   normal
      Export all specified documents defined in `--schemas`. 
      This mode ensures that the exported graph of documents remains valid by including any necessary additional documents to avoid any broken references.

   publication
      Same as `--mode normal`, but all non-essential data will be stripped. 
      The result of the export can be safely loaded within the game with the :doc:`generated code <../../gamedata/generating_source_code>`.
   
   extraction
      Export only the specified `--schemas` without exporting any referenced documents. 
      In this mode, the exported graph of documents may contain broken references. 
      It is recommended to use the import `--mode safeupdate` when importing this data back.

   localization
       Same as `--mode extraction` but only ``LocalizedText`` properties are exported.
    
--output
   Path to a exported data file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.
  
   .. code-block:: bash

     # standart output (default)
     --output out
     --output con

     # standart error
     --output err
     
     # null device
     --output null
     
     # absolute path (windows)
     --output "c:\my app\document.json"
     
     # absolute path (unix)
     --output /user/data/document.json
     
     # relative path (universal)
     --output "./document.json"
     
     # remote location (HTTP)
     --output "http://example.com/document.json"
     
     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/document.json"
     
--outputFormat
   Format of exported data.
   
   .. code-block:: bash
    
     # JSON (default)
     --outputFormat json
     
     # BSON
     --outputFormat bson
     
     # Message Pack
     --outputFormat msgpack
     
     # XML (removed in 2025.1.1) 
     --outputFormat xml
     
     # XLSX Spreadsheet
     --outputFormat xlsx
     
--outputFormattingOptions
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.

------------------
 Output
------------------

The exported data follows the general :doc:`game data structure <../game_data_structure>`, but omits `ToolsVersion`, `RevisionHash`, and `ChangeNumber` when the export mode is **not** set to publication.

.. code-block:: json
  
  {
    "Collections": 
    {
      "Character": 
      [
        {
          "Id": "Knight"
          
          /* rest of properties of document */
        },
        {
          "Id": "Templar"
          
          /* rest of properties of document */
        },
        // ...
      ]
    }
  }

------------------
 Modifying Exported Data with `yq`
------------------

The exported data can be accessed or modified using the `yq` tool, a lightweight and portable command-line YAML, JSON, and XML processor. `yq` uses `jq`-like syntax and supports common operations for manipulating structured data.

To use `yq` with exported JSON data:

1. **Install `yq`**:
   Follow the installation instructions from the official `yq` documentation: https://mikefarah.gitbook.io/yq/.

2. **Query Data**:
   Use `yq` to query specific fields or values from the exported JSON file.

   .. code-block:: bash

     # Query a specific field
     yq '.Collections.Character[0].name' characters.json

3. **Modify Data**:
   Use `yq` to update or add fields in the exported JSON file.

   .. code-block:: bash
     # Export data
     dotnet charon DATA EXPORT --dataBase gamedata.json --schemas Character --output characters.json

     # Update a field
     yq -i '.Collections.Character[0].name = "New Name"' characters.json

     # Add a new field
     yq -i '.Collections.Character[0].level = 10' characters.json

     # Import data back
     dotnet charon DATA IMPORT --dataBase gamedata.json --schemas Character --input characters.json --mode safeUpdate

4. **Convert Formats**:
   `yq` can also convert between JSON, YAML, and other supported formats.

   .. code-block:: bash

     # Convert JSON to YAML
     yq -o=yaml characters.json > characters.yaml

For more advanced usage, refer to the `yq` documentation: https://mikefarah.gitbook.io/yq/.
