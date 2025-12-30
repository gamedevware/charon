===========================
Internationalization (i18n)
===========================

Charon supports localization by enabling text data to be stored in multiple languages using the :doc:`Localized Text <../gamedata/datatypes/all/localized_text>` data type. This allows game data to be exported for translation, modified externally, and imported back after localization.

Supported export formats include `XLSX <https://en.wikipedia.org/wiki/Office_Open_XML>`_, `XLIFF <https://en.wikipedia.org/wiki/XLIFF>`_ (XML Localization Interchange File Format) and `JSON <https://www.json.org/json-en.html>`_. These formats are suitable for translation workflows involving external tools or localization teams.

Overview
========

Localization workflows in Charon rely on identifying fields of type :doc:`Localized Text <../gamedata/datatypes/all/localized_text>` and processing them through either spreadsheet or industry-standard interchange formats. Translated data can then be re-integrated using import commands.

Common use cases include:

- Managing multi-language game content.
- Sending text data to third-party localization vendors.
- Automating translation pipelines with CLI tools.

Supported Languages
===================

Translation languages are defined in the **Project Settings**. To view the configured languages via the CLI, run:

.. code-block:: bash

   charon DATA I18N LANGUAGES --dataBase gamedata.json

Exporting Translatable Text
===========================

Charon provides two primary formats for exporting localizable content: XLSX and XLIFF. Exporting can be done via the graphical interface or command-line interface.

XLSX Export (Spreadsheet)
-------------------------

The following example exports all translatable text to an Excel spreadsheet:

.. code-block:: bash

   charon DATA EXPORT --dataBase "gamedata.json" --properties [LocalizedText] --output "text_all_languages.xlsx" --outputFormat xlsx

Key parameters:

- ``--properties [LocalizedText]``: Filters exported data to include only `LocalizedText` fields.
- ``--languages``: (Optional) Specifies which languages to include in the export.

.. note::
   The exported spreadsheet may contain additional metadata columns that are required for correct import.

XLIFF Export (Industry Standard)
--------------------------------

To export translation data in XLIFF format:

.. code-block:: bash

   charon DATA I18N EXPORT --dataBase "gamedata.json" --sourceLanguage en --targetLanguage fr --output "en_fr_texts.xliff" --outputFormat xliff

Key parameters:

- ``--sourceLanguage``: Language of the original text.
- ``--targetLanguage``: Language to which the content will be translated.
- ``--outputFormat``: Format of the exported file. Supported values include `xliff`, `xliff1`, and `xliff2`.

Importing Translated Data
==========================

After translation, the modified data can be imported back into the project. Both XLSX and XLIFF formats are supported.

XLSX Import
-----------

To import translated spreadsheet data:

.. code-block:: bash

   charon DATA IMPORT --dataBase "gamedata.json" --input "text_all_languages.xlsx" --inputFormat xlsx --mode safeUpdate

Key parameters:

- ``--inputFormat xlsx``: Indicates the input file format.
- ``--mode safeUpdate``: Ensures only existing fields are updated, without creating or deleting data.

XLIFF Import
------------

To import translated XLIFF content:

.. code-block:: bash

   charon DATA I18N IMPORT --dataBase "gamedata.json" --input "en_fr_texts.xliff"

Best Practices
==============

- Use **XLSX** when working with translators familiar with spreadsheet tools.
- Use **XLIFF** for integration with professional translation software or localization platforms.
- Validate the translated data with a **dry run** before importing changes into production data.

Unsupported Formats
===================

While Charon may accept other serialization formats (e.g., BSON, MsgPack), compatibility for internationalization workflows is only guaranteed for XLSX, XLIFF and JSON.

Additional Resources
====================

- :doc:`DATA EXPORT <commands/data_export>`
- :doc:`DATA IMPORT <commands/data_import>`
- :doc:`DATA I18N EXPORT <commands/data_i18n_export>`
- :doc:`DATA I18N IMPORT <commands/data_i18n_import>`
- :doc:`DATA I18N LANGUAGES <commands/data_i18n_languages>`
