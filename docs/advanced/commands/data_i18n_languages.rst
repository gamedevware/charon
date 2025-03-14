List Translation Languages
=========================

Get a list of supported translation languages. Primary language always shows up first in the list.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dotnet charon DATA I18N LANGUAGES --dataBase "c:\my app\gamedata.json" --output out --outputFormat table

  # remote game data
  dotnet charon DATA I18N LANGUAGES --dataBase "https://charon.live/view/data/My_Game/develop/" --output out --outputFormat table --credentials "<API-Key>"

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

--output
   Path to language list file. If the file exists, it will be overwritten. The directory must already exist. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_,  `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.

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
     
     # remote location with authentication (FTP)
     --output "ftp://user:password@example.com/input.json"
     
--outputFormat
   Format of exported data.
   
   .. code-block:: bash
    
     # JSON (default)
     --outputFormat json
     
     #> [
     #>   "en-US",
     #>   "es-ES",
     #> ]
     
     
     # Space separated list
     --outputFormat list
     
     #> en-US es-ES
     
     # New line (OS specific) separated list
     --outputFormat table
     
     #> en-US
	 #> es-ES
     
	 
--outputFormattingOptions
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.


