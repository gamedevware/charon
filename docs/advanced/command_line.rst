CLI - Command Line Interface
============================

Most of Charon functionality could be accessed via CLI commands. The application itself uses the `getops <https://en.wikipedia.org/wiki/Getopts>`_ syntax.
You should be familiar with terminal on your OS to fully tap potential of CLI.

Installation
============

Manual Download
_______________

The ``Charon.exe`` package can be `downloaded from Nuget <https://www.nuget.org/packages/GameDevWare.Charon>`_ and extracted as a `ZIP <https://www.7-zip.org/>`_ archive, containing the application located in the ``tools/`` directory.

Nuget Client
____________

Or use `Nuget client <https://learn.microsoft.com/en-us/nuget/install-nuget-client-tools>`_ to download and unpack package:

.. code-block:: bash

  nuget install GameDevWare.Charon -ExcludeVersion -PackageSaveMode nupkg -PreRelease -OutputDirectory ./

Cake Script (dotnet tool)
_________________________

Alternatively, you can follow the guide for :doc:`standalone launch <../standalone/installation_and_updates>`. To pass commands to the ``update_and_launch.cake`` script, use the ``--`` parameter and continue with the command and it's parameters.

.. code-block:: bash
  
  dotnet tool restore
  dotnet cake "./update_and_launch.cake" -- DATA EXPORT --help
                                          ^
                            your command goes after this

Command Syntax
======

Commands have the following syntax:

.. code-block:: bash

  Charon.exe COMMAND --parameterName <parameter-value>
   
  # parameters can have more than one value. 
  # Use space to separate values
  Charon.exe EXPORT --schemas Item Armor "Project Settings" Quest

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

Getting Help Text
=================

To display list of available commands add `--help` or `/?`.

.. code-block:: bash
  
  Charon.exe --help
  
  #> Usage: Charon.exe <action> [--<param> || (--<param> <paramValue> ...) ...]
  #>
  #> Verbs:
  #>  SERVE       Start a HTTP Server at specified 'port'.
  #>  DATA        Data manipulation actions.
  #>  GENERATE    Code generation actions.
  #>  VERSION     Print version.
  
  Charon.exe DATA EXPORT --help
  
  #> Usage:
  #>   DATA EXPORT --dataBase <URI> [--schemas [<TEXT>]] [--properties [<TEXT>]] [--languages [<TEXT>]] [--output <TEXT>
  #>               ] [--outputFormat <TEXT>] [--outputFormattingOptions [<TEXT>]] [--mode <EXPORTMODE>] [--credentials [<
  #>               TEXT>]]
  
List of Commands
================

- :doc:`SERVER START <commands/serve>`
- :doc:`VERSION <commands/version>`
- :doc:`DATA EXPORT <commands/data_export>`
- :doc:`DATA IMPORT <commands/data_import>`
- :doc:`DATA BACKUP <commands/data_backup>`
- :doc:`DATA RESTORE <commands/data_restore>`
- :doc:`DATA VALIDATE <commands/data_validate>`
- :doc:`DATA CREATE <commands/data_create>`
- :doc:`DATA UPDATE <commands/data_update>`
- :doc:`DATA DELETE <commands/data_delete>`
- :doc:`DATA FIND <commands/data_find>`
- :doc:`DATA LIST <commands/data_list>`
- :doc:`DATA CREATEPATCH <commands/data_create_patch>`
- :doc:`DATA APPLYPATCH <commands/data_apply_patch>`
- :doc:`DATA I18N EXPORT <commands/data_i18n_export>`
- :doc:`DATA I18N IMPORT <commands/data_i18n_import>`
- :doc:`DATA I18N LANGUAGES <commands/data_i18n_languages>`
- :doc:`GENERATE TEMPLATES <commands/generate_templates>`
- :doc:`GENERATE CSHARPCODE <commands/generate_csharp_code>`
- :doc:`GENERATE TEXT <commands/generate_text>`
