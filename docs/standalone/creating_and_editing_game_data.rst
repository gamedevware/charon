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
- `Basic Navigation and User Interface Overview <../gamedata/basics.rst>`_
- `Creating Document Type (Schema) <../gamedata/creating_schema.rst>`_
- `Creating Document <../gamedata/creating_document.rst>`_
- `Publication of Game Data <../gamedata/publication.rst>`_
- `Generating Source Code (C#) <../gamedata/generating_source_code.rst>`_
- `Working with Source Code (C#) <../gamedata/working_with_source_code.rst>`_
- `Frequently Asked Questions (FAQ) <../gamedata/faq.rst>`_
- `Glossary <../gamedata/glossary.rst>`_
- `Examples <../gamedata/example.rst>`_
