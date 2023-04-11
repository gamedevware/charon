Any empty file could be used as starting point for standalone application launch.

For example:

.. code-block:: bash

    # create new empty game data file
    # available formats are .json, gdjs, .msgpack, .msgpck, .gdmp
    echo > gamedata.json
    
    # open newly created file
    charon.exe SERVE ./gamedata.json --port 8080 --launchDefaultBrowser
