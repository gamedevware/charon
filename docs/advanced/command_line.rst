Most of Charon functionality could be accessed via CLI commands. The application itself uses the `getops <https://en.wikipedia.org/wiki/Getopts>`_ syntax.
You should be familiar with terminal on your OS to fully tap potential of CLI.

Syntax
======

Commands have the following syntax:

.. code-block:: bash

  Charon.exe COMMAND --parameterName <parameter-value>
   
  # parameters can have more than one value. 
  # Use space to separate values
  Charon.exe EXPORT --entities Item Armor "Project Settings" Quest

  # if your value contains a space, put it inside the quotation marks.
  # Escape characters and other rules depend on the OS you are running.
  Charon.exe SERVE --dataBase "c:\my application\my path.txt"
  
  # some parameters don't require a value (e.g. flag).
  Charon.exe VERSION --verbose
  
OSX and Linux
=============
To run ``Charon.exe`` on non-Windows systems, you need to have the ``mono`` runtime installed, which can be 
either a global one from ``$PATH`` or a local installation.

.. code-block:: bash

  # for globally installed mono
  mono Charon.exe VERSION

  # for non-brew installed mono on OSX
  /Library/Frameworks/Mono.framework/Commands/mono Charon.exe VERSION
  
  # for some linux installations
  /usr/bin/mono Charon.exe VERSION

Help
====

To display list of available commands type `--help` or `/?`.

.. code-block:: bash
  
  Charon.exe --help
  
  > Usage: Charon.exe <action> [--<param> || (--<param> <paramValue> ...) ...]
  >
  > Verbs:
  >  SERVE       Start a HTTP Server at specified 'port'.
  >  DATA        Data manipulation actions.
  >  GENERATE    Code generation actions.
  >  VERSION     Print version.
  
  # to display syntax and description for command just add --help as parameter
  Charon.exe DATA EXPORT --help
  
  > Usage:
  >   DATA EXPORT --dataBase <URI> [--entities [<TEXT>]] [--attributes [<TEXT>]] [--languages [<TEXT>]] [--output <TEXT>
  >               ] [--outputFormat <TEXT>] [--outputFormattingOptions [<TEXT>]] [--mode <EXPORTMODE>] [--credentials [<
  >               TEXT>]]
  
Commands
========

- `SERVE <commands/serve.rst>`_
- `VERSION <commands/version.rst>`_
- `DATA EXPORT <commands/data_export.rst>`_
- `DATA IMPORT <commands/data_import.rst>`_
- `DATA BACKUP <commands/data_backup.rst>`_
- `DATA RESTORE <commands/data_restore.rst>`_
- `DATA VALIDATE <commands/data_validate.rst>`_
- `DATA CREATE <commands/data_create.rst>`_
- `DATA UPDATE <commands/data_update.rst>`_
- `DATA DELETE <commands/data_delete.rst>`_
- `DATA FIND <commands/data_find.rst>`_
- `DATA CREATEPATCH <commands/data_create_patch.rst>`_
- `DATA APPLYPATCH <commands/data_apply_patch.rst>`_
- `DATA VERSION <commands/data_version.rst>`_
- `DATA I18N EXPORT <commands/data_i18n_export.rst>`_
- `DATA I18N IMPORT <commands/data_i18n_import.rst>`_
- `DATA I18N LANGUAGES <commands/data_i18n_languages.rst>`_
- `GENERATE TEMPLATES <commands/generate_templates.rst>`_
- `GENERATE CSHARPCODE <commands/generate_csharp_code.rst>`_
- `GENERATE TEXT <commands/generate_text.rst>`_
