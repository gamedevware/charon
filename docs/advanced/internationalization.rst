Internationalization (i18n)
===========================

Charon supports storing text data in multiple languages by using the special ``LocalizedText`` data type.

A list of possible translation languages is defined in the ``Project Settings``.


Translation
-----------

There are two ways to pass translatable text to a third party (e.g., for localization or editing):

- You can export all translatable data as an `XLSX <https://en.wikipedia.org/wiki/Office_Open_XML>`_ spreadsheet.
- You can use the special localization format, `XLIFF <https://en.wikipedia.org/wiki/XLIFF>`_ (XML Localization Interchange File Format).

Using UI
^^^^^^^^

The ``Internationalization Settings`` link is available under the *Tasks* tab in the project's dashboard, which leads to the ``Export`` and ``Import`` buttons for translation data in the *Project Settings*.

Using CLI
^^^^^^^^^

Exporting to XLSX spreadsheet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To export translatable text data as *XLSX*, run the :doc:`DATA EXPORT <commands/data_export>` command with the following parameters:

.. code-block:: bash

  Charon.exe DATA EXPORT --dataBase "c:\my app\gamedata.json" --properties [LocalizedText] --output "c:\my app\text_all_languages.xlsx" --outputFormat xlsx
  
- Use ``--properties [LocalizedText]`` parameter to indicate that only the properties containing ``LocalizedText`` should be exported.
- Use ``--languages`` parameter to limit the number of exported languages.

Extra columns may be present in the export files, which are required for the correct import of the translated data.

Importing from XLSX spreadsheet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Once your data is processed (e.g., translated), you can import it using the :doc:`DATA IMPORT <commands/data_import>` command with the ``safeUpdate`` mode:

.. code-block:: bash

  Charon.exe DATA IMPORT --dataBase "c:\my app\gamedata.json" --input "c:\my app\text_all_languages.xlsx" --inputFormat xlsx --mode safeUpdate
  
Exporting to XLIFF
------------------

To export translatable text data as *XLIFF*, run the :doc:`DATA I18N EXPORT <commands/data_i18n_export>` command with the following parameters:

.. code-block:: bash

  Charon.exe DATA I18N EXPORT --dataBase "c:\my app\gamedata.json" --sourceLanguage en --targetLanguage fr --output "c:\my app\en_fr_texts.xliff" --outputFormat xliff

- Use the ``--outputFormat`` parameter to indicate the exact format of the exported data, which can be either *xliff*, *xiff1*, or *xliff2*.
- Use ``--sourceLanguage`` to indicate the language text is being translated from as the *source*, and ``--targetLanguage`` to indicate the *target* language that the text is being translated to.
- To get a list of configured translation languages for the game data, run the :doc:`DATA I18N LANGUAGES <commands/data_i18n_languages>` command.

Importing from XLIFF
^^^^^^^^^^^^^^^^^^^^

Once the data has been processed, you can import it using the :doc:`DATA I18N IMPORT <commands/data_i18n_import>` command.

.. code-block:: bash

  Charon.exe DATA I18N IMPORT --dataBase "c:\my app\gamedata.json" --input "c:\my app\en_fr_texts.xliff"
  
Other formats
^^^^^^^^^^^^^

While the export and import commands may accept other formats, it cannot be guaranteed that they will be supported.
  
