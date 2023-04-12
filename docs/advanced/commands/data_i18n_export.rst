Export Translated Data
=========================

Export text that can be translated into a file.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe DATA I18N EXPORT --dataBase "c:\my app\gamedata.json" --entities Character --sourceLanguage en-US --targetLanguage fr --output "c:\my app\character_loc.xliff" --outputFormat xliff
  
  # Linux or OSX
  mono Charon.exe DATA I18N EXPORT --dataBase "~\gamedata.json" --entities Item --sourceLanguage en-US --targetLanguage fr --output "~\character_loc.xslx"
  
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

--sourceLanguage
   Source (original) language for translation. Value is `language tag (BCP 47) <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_. 
   
   Use `DATA I18N LANGUAGES <data_i18n_languages.rst>`_ to get list of used languages.
   
   .. code-block:: bash
     
     # it is used as <source> in XLIFF
     --sourceLanguage en-US
     
--targetLanguage 
   Target language for translation. Value is `language tag (BCP 47) <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_. 
   
   .. code-block:: bash
   
     # it is used as <target> in XLIFF
     --targetLanguage es-ES
     
--output
   Path to a file to which data will be exported. If the file exists, it will be overwritten. The directory must already exist. 
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
     --output "c:\my app\input.json"
     
     # absolute path (unix)
     --output /user/data/input.json
     
     # relative path (universal)
     --output "./input.json"
     
     # remote location (HTTP)
     --output "http://example.com/input.json"
     
     # remote location with authentification (FTP)
     --output "ftp://user:password@example.com/input.json"
     
--outputFormat
   Format of exported data.
   
   .. code-block:: bash
    
     # XLIFF v2 (default)
     --outputFormat xliff
     --outputFormat xliff2
     
     # XLIFF v1
     --outputFormat xliff1
     
     # XSLX Spreadsheet
     --outputFormat xslx
     

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
