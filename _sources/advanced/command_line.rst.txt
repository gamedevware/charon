Command Line Interface (CLI)
============================

Most of Charon functionality could be accessed via CLI commands. The application itself uses the `getops <https://en.wikipedia.org/wiki/Getopts>`_ syntax.
You should be familiar with terminal on your OS to fully tap potential of CLI.

.. _CommandLine_Installation:

Installation
------------

Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.

Option 1: dotnet tool (recommended)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The easiest way to install is to use the infrastructure provided by the `dotnet tool <https://learn.microsoft.com/en-us/dotnet/core/tools/global-tools>`_.

.. code-block:: bash

  # install charon globally
  dotnet tool install -g dotnet-charon
  
  # install charon in current working directory
  dotnet tool install dotnet-charon --local --create-manifest-if-needed 

To update current tool use following commands:

.. code-block:: bash
  
  # update global tool
  dotnet tool update --global dotnet-charon
  
  # update local tool
  dotnet tool update dotnet-charon --local

Option 2: Bootstrap scripts
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Alternatively, you can use one of two bootstrap scripts:  

  - `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_
  - `RunCharon.sh (Linux, MacOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download>`_ tool to be included in the system PATH. 
The scripts handle the installation of the Charon tool and ensure it stays up to date.

.. tabs::

   .. tab:: Windows

      .. code-block:: bash
  
        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
        
        .\RunCharon.bat DATA EXPORT --help
        #               ^
        #      your command goes here

   .. tab:: Linux, MacOS

      .. code-block:: bash

        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
        
        chmod +x ./RunCharon.sh
        
        ./RunCharon.sh DATA EXPORT --help
        #               ^
        #      your command goes here

Command Syntax
--------------

Commands have the following syntax:

.. code-block:: bash

  dotnet charon COMMAND --parameterName <parameter-value>
   
  # parameters can have more than one value. 
  # Use space to separate values
  dotnet charon EXPORT --schemas Item Armor "Project Settings" Quest

  # if your value contains a space, put it inside the quotation marks.
  # Escape characters and other rules depend on the OS you are running.
  dotnet charon "c:\my application\my path.txt"
  
  # some parameters don't require a value (e.g. flag).
  dotnet charon VERSION --verbose

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
  
  dotnet charon --help
  
  #> Usage: dotnet charon <action> [--<param> || (--<param> <paramValue> ...) ...]
  #>
  #> Verbs:
  #>  DATA        Data manipulation actions.
  #>  GENERATE    Code generation actions.
  #>  VERSION     Print version.
  
  dotnet charon DATA EXPORT --help
  
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
