Export Data
===========

Exports documents into a file.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe DATA EXPORT --dataBase "c:\my app\gamedata.json" --entities Character --output "c:\my app\characters.json" --outputFormat json
  
  # Linux or OSX
  mono Charon.exe DATA EXPORT --dataBase "~/gamedata.json" --entities Character --output "~/characters.json" --outputFormat json
  
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
     
--entities
   A list of types of documents (entities) to export. By default all entities *EXCEPT* metadata are exported.

   - Use space to separate multiple entities.
   - You can use wildcards (*) at the beginning and end of names.
   - You can use identifiers in {} instead of names.
   - You can exclude certain names by using an exclamation mark (!) at the beginning of their names.

   .. code-block:: bash
   
     # entity name
     --entities Character
     --entities Character Item
     
     # all (default)
     --entities * 
     
     # masks
     --entities Char*
     --entities *Modifier
     --entities *Mod*
     
     # entity id
     --entities {18d4bf318f3c49688087dbed}
     
     # negation
     --entities Char* !Character
     --entities !*Item*
     
--attributes
   A list of attributes or attribute types to export. By default all attributes are exported.
   
   - Id attribute always included
   - Use space to separate multiple entities.
   - You can use wildcards (*) at the beginning and end of names.
   - You can use identifiers in {} instead of names.
   - You can exclude certain names by using an exclamation mark (!) at the beginning of their names.
   - You can use data type in [] instead of names.
   
--languages
   List of languages to keep in exported data. Language's `english name <https://docs.microsoft.com/en-us/dotnet/api/system.globalization.cultureinfo.englishname?view=netframework-4.8>`_ is used or `language tag (BCP 47) <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_. 
   
   Use `DATA I18N LANGUAGES <data_i18n_languages.rst>`_ to get list of used languages.
   
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
      Export all related data without any modification.
      This mode always export valid graph of documents without broken references.
      
   publication
      Same as *default*, but all non-essential data will be stripped. 
      The result of the export can be safely loaded within the game with the `generated code <generate_csharp_code.rst>`_.
   
   extraction
      Export only selected entities without any related data. 
      This mode may export a broken graph of documents, so it is recommended to use the ``safeupdate`` import mode.
   
   localization
       Same as *extraction* but only ``LocalizedText`` attributes are exported.
    
--output
   Path to a exported data file. If the file exists, it will be overwritten. The directory must already exist. 
   Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
   `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
   `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <universal_parameters.rst>`_.
  
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
     
     # remote location with authentification (FTP)
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
     
     # XML
     --outputFormat xml
     
     # XLSX Spreadsheet
     --outputFormat xlsx
     
--outputFormattingOptions
   Additional options for specified format.
   
------------------
 Output Data Schema
------------------

The expored data follow this schema:

   .. code-block:: js
     
     {
       "Collections": {
         "<EntityName>": [
           {
             // <Document>
           },
           // ...
         ]
       }
     }
