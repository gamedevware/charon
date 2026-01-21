URL input/output parameters
===========================

Some command accept `URL <https://en.wikipedia.org/wiki/Uniform_Resource_Identifier>`_ as input/output parameter.

Supported URL Schemes
---------------------

+---------+----------------------------+-----------------------------------------------------+
| Scheme  | Input parameter            | Output parameter                                    |
+=========+============================+=====================================================+
| HTTP[S] | A GET request will be sent | A POST request with body containing output will be  |
|         |                            | sent                                                |
+---------+----------------------------+-----------------------------------------------------+
| FTP(S)  | A RETR command will be sent| A STOR command with output content will be sent     |
+---------+----------------------------+-----------------------------------------------------+
| FILE    | File will be read          | File will be written                                |
+---------+----------------------------+-----------------------------------------------------+

Authentication
--------------
Authentication data could be passed in *user* part of `URL <https://en.wikipedia.org/wiki/Uniform_Resource_Identifier>`_. 
More advanced authentication schemes are not supported.

Examples
--------

.. code-block:: bash
  
  # publish data to FTP
  charon DATA EXPORT 
    --dataBase "https://charon.live/view/data/My_Game/develop/dashboard"     
    --output "ftp://user:password@example.com/public/gamedata.json"
    --mode publication 
    --outputFormat json
    --credentials "<API-Key>" 
    
  # import localization from remote HTTP server 
  charon DATA I18N IMPORT
    --dataBase "file:///c:/my app/gamedata.json" 
    --input "https://example.com/translated/gamedata.xliff"
    --inputFormat xliff

  # print languages for game data in local file
  charon DATA I18N LANGUAGES --dataBase "file:///c:/my app/gamedata.json" 
  
  # print languages for game data in local file relative to current working directory
  charon DATA I18N LANGUAGES --dataBase "file:///./gamedata.json" 
  
  # print languages for game data at remote server using API Key
  export CHARON_API_KEY=87758CC0D7C745D0948F2A8AFE61BC81
  charon DATA I18N LANGUAGES --dataBase "https://charon.live/view/data/My_Game/develop/dashboard"  
  
    
