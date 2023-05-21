List Documents
==============

Seaches for a documents.

- :doc:`Installation <../command_line:installation>`
- :doc:`Commands Reference <../command_line>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  Charon.exe DATA LIST --dataBase "c:\my app\gamedata.json" --schema Character
  
  # remote game data
  Charon.exe DATA LIST --dataBase "https://charon.live/view/data/My_Game/develop/" --schema Character --credentials "<API-Key>"
  
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

--schema
   Name or identifier of the type (schema) of document.
     
   .. code-block:: bash

     # name
     --schema Item
     
     # id
     --schema 55a4f32faca22e191098f3d9
     
--filters
   Document filter expressions.

   .. code-block:: bash

     # patterns
     --filters <Field> <Operator> <Value> [<Field> <Operator> <Value>...]

     # single expression
     --filters Id > 10
     --filters Name like "Zombie"
    
     # multiple expressions
     --filters Id > 10 Name like "Zombie"

     # greater than
     --filters Id > 0
     --filters Id greaterThan 0

     
     # greater than or equal
     --filters Id >= 0
     --filters Id greaterThanOrEqual 0

     
     # less than
     --filters Id < 0
     --filters Id lessThan 0

     # less than or equal
     --filters Id <= 0
     --filters Id LessThanOrEqual 0
     
     # equal
     --filters Id = 0
     --filters Id == 0
     --filters Id equal 0
     
     # not equal
     --filters Id <> 0
     --filters Id != 0
     --filters Id notEqual 0
     
     # like - is used to search for specific patterns in a field, allowing for partial matches.
     --filters Name like "Zombie" 

--sorters
   Document sort expressions.

   .. code-block:: bash

     # patterns
     --sorters <Field> ASC|DESC [<Field> ASC|DESC ...]
     
     # ascending
     --sorters Name ASC
     
     # descending
     --sorters Name DESC

--path
   Embeddance path filter. Could be used to get only embedded documents.

   .. code-block:: bash

     # any path
     --path *

     # root documents (default)
     --path ""

     # in 'Item' property
     --path /Item

--skip
   Number of found documents to skip.

   .. code-block:: bash

     # skip first ten documents after applying --filter and --sort
     --skip 10

--take
   Max amount to documents return.

   .. code-block:: bash

     # limit to first 100 documents after --skip
     --take 100

--output
   Path to a found document file. If the file exists, it will be overwritten. The directory must already exist. 
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
     
     # XML
     --outputFormat xml

--outputFormattingOptions
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.
