List Translation Languages
=========================

Get a list of supported translation languages. Primary language always shows up first in the list.

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe DATA I18N LANGUAGES --dataBase "c:\my app\gamedata.json" --output out --outputFormat json
  
  # Linux or OSX
  mono Charon.exe DATA I18N LANGUAGES --dataBase "~\gamedata.json" --output out --outputFormat list
  
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
     
--output
    Path to a file to which data will be exported. If the file exists, it will be overwritten. The directory must already exist. 
    Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, 
    `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_, 
    `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a `URL <universal_parameters.rst>`_. Default value is ``out``.
     
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
   Format of exported data. Default value is ``json ``.
   
   .. code-block:: bash
    
     # JSON
     --outputFormat json
     
     # Space separated list
     --outputFormat list
     
     # New line (OS specific) separated list
     --outputFormat table

--outputFormattingOptions <options>
   Additional options for specified format.
     
