Filling Documents
=================

Once the game data structure has been defined, there are several methods available for creating and populating game entities. One option is to import game data from other sources, such as tables or JSON files. Another option is to generate data using external tools and import it into the editor. Finally, data can be added gradually as development progresses using the game data editor.

Importing JSON files
--------------------
JSON files can be imported via the user interface by following these steps:

1. Navigate to the document collection page.
2. Click on ``Actions → Import...``.
3. Select the JSON file and follow the steps in the import wizard.

:doc:`See structure requirements. <../advanced/commands/data_import>`

Exporting to Spreadsheet and Importing Back
-------------------------------------------
To export game data to a spreadsheet for editing and then import it back, follow these steps:

1. Navigate to the document collection page.
2. Click on ``Actions → Export To → Spreadsheet (.xlsx)`` to export the data to a spreadsheet file.
3. Open the downloaded file and make the necessary edits.
4. Import the modified data back into the system:
    a. Drag and drop the edited file onto the document collection page.
    b. Alternatively, click on ``Actions → Import...`` and follow the steps in the import wizard to select and import the modified file.

Adding New Document
-------------------
To create a new document using the user interface, follow these steps:

1. Navigate to the document collection page.
2. Click on the ``Create`` button.
3. Fill in the required fields in the form provided.
4. Click ``Save`` to save the new document.

See also
--------

- :doc:`Publishing Game Data <publication>`
- :doc:`Generating Source Code <generating_source_code>`