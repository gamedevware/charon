Overview
========

Any empty file could be used as starting point for standalone application launch.

.. code-block:: bash

    # create new empty game data file
    # available formats are .json, gdjs, .msgpack, .msgpck, .gdmp
    echo > gamedata.json
    
    # open newly created file
    charon.exe SERVE ./gamedata.json --port 8080 --launchDefaultBrowser

See also
========

- `Requirements <requirements.rst>`_
- `Installation <installation_and_updates.rst>`_
- `Working with Game Data <../gamedata/basics.rst>`_
