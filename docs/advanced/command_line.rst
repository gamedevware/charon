Command Line Interface (CLI)
============================

Most of Charon functionality could be accessed via CLI commands. The application itself uses the `getops <https://en.wikipedia.org/wiki/Getopts>`_ syntax.
You should be familiar with terminal on your OS to fully tap potential of CLI.

.. _CommandLine_Installation:

Installation
------------

Manual Download
^^^^^^^^^^^^^^^

The ``Charon.exe`` package can be `downloaded from Nuget <https://www.nuget.org/packages/GameDevWare.Charon>`_ and extracted as a `ZIP <https://www.7-zip.org/>`_ archive, containing the application located in the ``tools/`` directory.

Nuget Client
^^^^^^^^^^^^

Or use `Nuget client <https://learn.microsoft.com/en-us/nuget/install-nuget-client-tools>`_ to download and unpack package:

.. code-block:: bash

  nuget install GameDevWare.Charon -ExcludeVersion -PackageSaveMode nupkg -PreRelease -OutputDirectory ./

Bootstrap scripts (recommended)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Alternatively, you can use one of two bootstrap scripts:  

  - `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_
  - `RunCharon.sh (Linux, MacOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download/dotnet>`_ tool to be available in ``PATH`` and `mono <https://www.mono-project.com/download/stable/>`_ installed for Linux and MacOS.

.. code-block:: bash

  # Windows
  
  mkdir Charon
  cd Charon
  curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
  
  call RunCharon.bat DATA EXPORT --help
  #                  ^
  #         your command goes here
  
  # Linux, MacOS

  mkdir Charon
  cd Charon
  curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
  
  chmod +x RunCharon.sh
  
  ./RunCharon.sh DATA EXPORT --help
  #              ^
  #      your command goes here
  

Command Syntax
--------------

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
  
Linux and MacOS
-------------

To run ``Charon.exe`` on non-Windows systems, you need to have the ``mono`` runtime installed, which can be 
either a global one from ``$PATH`` or a local installation.

.. code-block:: bash

  # for globally installed mono
  mono Charon.exe VERSION

  # for non-brew installed mono on MacOS
  /Library/Frameworks/Mono.framework/Commands/mono Charon.exe VERSION
  
  # for some linux installations
  /usr/bin/mono Charon.exe VERSION
  
  # or use bootstrap script
  ./RunCharon.sh VERSION

Absolute and relative paths
---------------------------
When running commands, it's crucial to be aware of whether you are using `absolute or relative paths <https://en.wikipedia.org/wiki/Working_directory>`_ to files.  

Understanding Paths
~~~~~~~~~~~~~~~~~~~

1. **Absolute Path**:
   An absolute path defines a file or directory's location in relation to the root directory. In Linux and macOS, it starts from the root ``/``, while in Windows, it begins with a drive letter (like ``C:\\``).  

   - Example for Linux/macOS: ``/usr/local/bin``
   - Example for Windows: ``C:\\Program Files\\mono``

2. **Relative Path**:
   A relative path references a file or directory in relation to the current working directory, without starting with a root slash or drive letter.  

   - Example: If currently in ``/home/user/Documents``, a file in ``/home/user/Documents/Projects`` would have the relative path ``Projects/FileName``.  

Usage in Terminals
~~~~~~~~~~~~~~~~~~

- **Windows Command Prompt**:
  Paths use backslashes (``\\``). Absolute paths start with a drive letter (like ``C:\\Users\\Name``), while relative paths use the file name or paths like ``subfolder\\file.txt``.  

- **macOS/Linux Terminal**:
  Paths are denoted with forward slashes (``/``). Absolute paths begin from the root (``/``), and relative paths use ``./`` for the current directory or ``../`` to go up one level.  

Getting Help Text
-----------------

To display list of available commands add `--help` or `/?`.

.. code-block:: bash
  
  Charon.exe --help
  
  #> Usage: Charon.exe <action> [--<param> || (--<param> <paramValue> ...) ...]
  #>
  #> Verbs:
  #>  DATA        Data manipulation actions.
  #>  GENERATE    Code generation actions.
  #>  VERSION     Print version.
  
  Charon.exe DATA EXPORT --help
  
  #> Usage:
  #>   DATA EXPORT --dataBase <URI> [--schemas [<TEXT>]] [--properties [<TEXT>]] [--languages [<TEXT>]] [--output <TEXT>
  #>               ] [--outputFormat <TEXT>] [--outputFormattingOptions [<TEXT>]] [--mode <EXPORTMODE>] [--credentials [<
  #>               TEXT>]]
  
.. _CommandLine_Commands:

.. toctree::
   :caption: List of Commands
   :titlesonly:
   :glob:

   commands/*
