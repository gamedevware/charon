Creating and Editing Game Data
==============================

Any empty file could be used as starting point for standalone application launch.

.. code-block:: bash

    # create new empty game data file
    # available formats are .json, gdjs, .msgpack, .msgpck, .gdmp
    echo > gamedata.json
    
    # open newly created file

    # Windows
    ./RunCharon.sh SERVER START --dataBase ./gamedata.json --launchDefaultBrowser --log out
    
    # Linux, MacOS
    ./RunCharon.sh SERVER START --database ./gamedata.json --launchDefaultBrowser --log out

See also
--------

- :doc:`Requirements <requirements>`
- :doc:`Installation <installation_and_updates>`
- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Creating Document Type (Schema) <../gamedata/creating_schema>`
- :doc:`Filling Documents <../gamedata/filling_documents>`
- :doc:`Publication of Game Data <../gamedata/publication>`
- :doc:`Generating Source Code <../gamedata/generating_source_code>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`
