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

--dataBase <path>
   Absolute or relative oath to game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --dataBase "c:\my app\gamedata.json"
     
     # remote server
     --dataBase "https://charon.live/view/data/My_Game/develop/dashboard"
     
--entities <entityNameOrId1 entityNameOrId2 ...>
   A list of types of documents (entities) to scan for texts. By default all entities are scanned.

   .. code-block:: bash
   
     # entity name
     --entities Character Item
     
     # masks
     --entities *
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
   
     --sourceLanguage en-US
     
--targetLanguage 
   Target language for translation. Value is `language tag (BCP 47) <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_. 
   
   .. code-block:: bash
   
     --targetLanguage es-ES
     
--output
    Path to a file to which data will be exported. If the file exists, it will be overwritten. The directory must already exist. 
    Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
    `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
    `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <universal_parameters.rst>`_.
     
   .. code-block:: bash

     # standart output
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
     
--outputFormat <format>
   Format of exported data. Default value is ``xliff2``.
   
   .. code-block:: bash
    
     # XLIFF v2
     --outputFormat xliff
     --outputFormat xliff2
     
     # XLIFF v1
     --outputFormat xliff1
     
     # XSLX Spreadsheet
     --outputFormat xslx
     

--outputFormattingOptions <options>
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
