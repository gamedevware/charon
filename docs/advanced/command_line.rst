Command Line Interface (CLI)
============================

Most of Charon functionality could be accessed via CLI commands. The application uses
`GNU-style long options <https://en.wikipedia.org/wiki/Command-line_interface#Command-line_option>`_
(``--parameterName <value>``). You should be familiar with the terminal on your OS to fully tap the potential of the CLI.

.. _CommandLine_Requirements:

Requirements
------------

Charon is distributed as a `.NET tool <https://learn.microsoft.com/en-us/dotnet/core/tools/global-tools>`_, so the
`.NET SDK <https://dotnet.microsoft.com/en-us/download>`_ is the only prerequisite.

- **.NET SDK 10 or later** — recommended. Enables ``dnx``, which runs Charon without installing anything.
- **.NET SDK 8 or 9** — supported through :ref:`bootstrap scripts <CommandLine_Bootstrap>` or a
  :ref:`classic tool install <CommandLine_DotnetTool>`. ``dnx`` is not available on these versions.

Check which version you have:

.. code-block:: bash

  dotnet --version
  #> 10.0.100

If the command is not found, the SDK is not installed or not on ``PATH``.

.. _CommandLine_Installation:

Installation
------------

.. _CommandLine_Dnx:

Option 1: dnx (recommended, .NET SDK 10+)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.NET SDK 10 introduced `dnx <https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-dnx>`_, a runner for .NET tools
similar to ``npx``. It downloads and executes the tool on demand without registering it in the global or local tool
manifest. Nothing to install, nothing to add to ``PATH``:

.. code-block:: bash

  # run any charon command
  dnx dotnet-charon -- DATA EXPORT --help

  # use this form when dnx is not registered in PATH
  dotnet dnx dotnet-charon -- DATA EXPORT --help

Everything after ``--`` is passed to Charon. The tool is cached by NuGet after the first run, so subsequent
invocations start immediately.

Pin a version for reproducible builds:

.. code-block:: bash

  dnx dotnet-charon@2026.3.4 -- VERSION

This is the notation used throughout the rest of the documentation. If you installed Charon in another way, see
:ref:`Choosing how to invoke Charon <CommandLine_Invocation>` for the equivalent command.

.. _CommandLine_DotnetTool:

Option 2: dotnet tool (.NET SDK 8+)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Installs Charon into the global tool store or into a local tool manifest next to your project.

.. code-block:: bash

  # install charon globally
  dotnet tool install --global dotnet-charon

  # install charon in current working directory
  dotnet tool install dotnet-charon --local --create-manifest-if-needed

  # pin a specific version (recommended for CI)
  dotnet tool install --global dotnet-charon --version 2026.3.4

If the repository already contains a ``.config/dotnet-tools.json`` manifest, you do not install anything — just
restore it:

.. code-block:: bash

  dotnet tool restore

To update an installed tool:

.. code-block:: bash

  # update global tool
  dotnet tool update --global dotnet-charon

  # update local tool
  dotnet tool update dotnet-charon --local

To remove it:

.. code-block:: bash

  dotnet tool uninstall --global dotnet-charon
  dotnet tool uninstall dotnet-charon --local

.. _CommandLine_Path:

Adding the global tool to PATH
""""""""""""""""""""""""""""""

A **global** tool is launched by the bare ``charon`` command, but only if the .NET tools directory is on ``PATH``.
On Windows this normally happens automatically; on macOS and Linux you have to do it yourself.

.. tab-set::

   .. tab-item:: Windows

      The installer adds ``%USERPROFILE%\.dotnet\tools`` to ``PATH``. Open a **new** terminal window after
      installing so it picks up the change. To add it manually:

      .. code-block:: bat

        setx PATH "%PATH%;%USERPROFILE%\.dotnet\tools"

   .. tab-item:: macOS

      .. code-block:: bash

        echo 'export PATH="$PATH:$HOME/.dotnet/tools"' >> ~/.zshrc
        source ~/.zshrc

   .. tab-item:: Linux

      .. code-block:: bash

        echo 'export PATH="$PATH:$HOME/.dotnet/tools"' >> ~/.bashrc
        source ~/.bashrc

A **local** tool is never placed on ``PATH``. It is always invoked through ``dotnet`` from the directory containing
the manifest — see :ref:`Choosing how to invoke Charon <CommandLine_Invocation>`.

.. _CommandLine_Bootstrap:

Option 3: Bootstrap scripts (.NET SDK 8+)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Use this when ``dnx`` is unavailable (.NET SDK 8 or 9) and you would rather not manage the tool manifest yourself.
The scripts create a local tool manifest, install or update Charon in it, and then run it.

  - `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_
  - `RunCharon.sh (Linux, macOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download>`_ tool to be included in the system ``PATH``.

.. tab-set::

   .. tab-item:: Windows

      .. code-block:: bat

        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat

        REM everything after the script name is your command
        .\RunCharon.bat DATA EXPORT --help

   .. tab-item:: Linux, macOS

      .. code-block:: bash

        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.sh

        chmod +x ./RunCharon.sh

        # everything after the script name is your command
        ./RunCharon.sh DATA EXPORT --help

.. _CommandLine_Verify:

Verifying the installation
--------------------------

Run the ``VERSION`` command. It prints the tool version and exits with code ``0``:

.. tab-set::

   .. tab-item:: dnx

      .. code-block:: bash

        dnx dotnet-charon -- VERSION

   .. tab-item:: Global tool

      .. code-block:: bash

        charon VERSION
        dotnet tool list --global

   .. tab-item:: Local tool

      .. code-block:: bash

        dotnet charon VERSION
        dotnet tool list --local

   .. tab-item:: Bootstrap script

      .. code-block:: bash

        # Windows
        .\RunCharon.bat VERSION

        # Linux, macOS
        ./RunCharon.sh VERSION

If ``charon`` is reported as an unknown command after a global install, the .NET tools directory is missing from
``PATH`` — see :ref:`Adding the global tool to PATH <CommandLine_Path>`.

.. _CommandLine_Invocation:

Choosing how to invoke Charon
-----------------------------

Every example in this documentation is written as ``dnx dotnet-charon -- <VERB>``. If you installed Charon in
another way, substitute the leading part of the command:

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Installation
     - Command prefix
   * - :ref:`dnx <CommandLine_Dnx>` (.NET SDK 10+)
     - ``dnx dotnet-charon --``
   * - :ref:`Global tool <CommandLine_DotnetTool>`
     - ``charon``
   * - :ref:`Local tool <CommandLine_DotnetTool>`
     - ``dotnet charon``
   * - :ref:`Bootstrap script <CommandLine_Bootstrap>`
     - ``.\RunCharon.bat`` or ``./RunCharon.sh``

For example, these four commands are equivalent:

.. code-block:: bash

  dnx dotnet-charon -- DATA VALIDATE --dataBase ./gamedata.json
  charon DATA VALIDATE --dataBase ./gamedata.json
  dotnet charon DATA VALIDATE --dataBase ./gamedata.json
  ./RunCharon.sh DATA VALIDATE --dataBase ./gamedata.json

Command Syntax
--------------

Commands have the following syntax:

.. code-block:: bash

  dnx dotnet-charon -- VERB [SUB-VERB] --parameterName <parameter-value>

  # parameters can have more than one value.
  # Use space to separate values
  dnx dotnet-charon -- DATA EXPORT --schemas Item Armor "Project Settings" Quest

  # if your value contains a space, put it inside the quotation marks.
  dnx dotnet-charon -- DATA EXPORT --dataBase "c:\my application\gamedata.json"

  # some parameters don't require a value (e.g. flag).
  dnx dotnet-charon -- VERSION --verbose

Available verbs are ``INIT``, ``DATA``, ``GENERATE``, ``SERVER``, ``MCP`` and ``VERSION``. Verbs are case-insensitive;
they are written in upper case in this documentation to stand out from parameters.

.. _CommandLine_Shells:

Running on Windows, macOS and Linux
-----------------------------------

Charon behaves identically on all platforms, but the *shell* around it does not. Examples in this documentation use
Bash syntax. Keep the following in mind.

**Splitting a long command across lines.** The trailing ``\`` used in the examples is a Bash/Zsh continuation
character. It is not understood by Windows shells:

.. tab-set::

   .. tab-item:: Bash / Zsh (macOS, Linux)

      .. code-block:: bash

        dnx dotnet-charon -- DATA EXPORT \
          --dataBase ./gamedata.json \
          --output ./characters.json

   .. tab-item:: PowerShell

      .. code-block:: powershell

        dnx dotnet-charon -- DATA EXPORT `
          --dataBase ./gamedata.json `
          --output ./characters.json

   .. tab-item:: Command Prompt

      .. code-block:: bat

        dnx dotnet-charon -- DATA EXPORT ^
          --dataBase .\gamedata.json ^
          --output .\characters.json

When in doubt, put the whole command on a single line — that works in every shell.

**Wildcards.** Parameters like ``--schemas`` accept ``*`` wildcards. Bash and Zsh expand ``*`` against file names
before Charon ever sees it, so always quote such values:

.. code-block:: bash

  # correct
  dnx dotnet-charon -- DATA EXPORT --schemas "Item*"

  # wrong on macOS/Linux — the shell replaces Item* with matching file names
  dnx dotnet-charon -- DATA EXPORT --schemas Item*

**Environment variables.** Setting :doc:`CHARON_API_KEY <commands/universal_parameters>` differs per shell:

.. tab-set::

   .. tab-item:: Bash / Zsh

      .. code-block:: bash

        export CHARON_API_KEY=87758CC0D7C745D0948F2A8AFE61BC81

   .. tab-item:: PowerShell

      .. code-block:: powershell

        $env:CHARON_API_KEY = "87758CC0D7C745D0948F2A8AFE61BC81"

   .. tab-item:: Command Prompt

      .. code-block:: bat

        set CHARON_API_KEY=87758CC0D7C745D0948F2A8AFE61BC81

Absolute and relative paths
---------------------------

When running commands, it's crucial to be aware of whether you are using `absolute or relative paths <https://en.wikipedia.org/wiki/Working_directory>`_ to files.

Understanding Paths
^^^^^^^^^^^^^^^^^^^

1. **Absolute Path**:
   An absolute path defines a file or directory's location in relation to the root directory. In Linux and macOS, it starts from the root ``/``, while in Windows, it begins with a drive letter (like ``C:\``).

   - Example for Linux/macOS: ``/usr/local/share/mygame``
   - Example for Windows: ``C:\Program Files\MyGame``

2. **Relative Path**:
   A relative path references a file or directory in relation to the current working directory, without starting with a root slash or drive letter.

   - Example: If currently in ``/home/user/Documents``, a file in ``/home/user/Documents/Projects`` would have the relative path ``Projects/FileName``.

Usage in Terminals
^^^^^^^^^^^^^^^^^^

- **Windows (Command Prompt and PowerShell)**:
  Paths use backslashes (``\``). Absolute paths start with a drive letter (like ``C:\Users\Name``), while relative
  paths use the file name or paths like ``subfolder\file.txt``. Forward slashes are also accepted, so
  ``./gamedata.json`` works too.

- **macOS/Linux Terminal**:
  Paths are denoted with forward slashes (``/``). Absolute paths begin from the root (``/``), and relative paths use ``./`` for the current directory or ``../`` to go up one level.

Getting Help Text
-----------------

To display the list of available commands add ``--help`` or ``/?``.

.. code-block:: bash

  dnx dotnet-charon -- --help

  #> Verbs:
  #>   INIT        Initialize a new, empty game data file at the specified path.
  #>   MCP         Start an MCP (Model Context Protocol) server for AI assistant integration via stdio.
  #>               Usage: claude mcp add --transport stdio charon -- charon MCP
  #>   SERVER      Commands for starting and managing the embedded HTTP server.
  #>   DATA        Commands for reading, writing, importing, and exporting game data.
  #>   GENERATE    Commands for generating typed source code from game data schemas.
  #>   VERSION     Print current product version.

The same flag works for any verb and sub-verb:

.. code-block:: bash

  dnx dotnet-charon -- DATA --help

  dnx dotnet-charon -- DATA EXPORT --help

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

See also
--------

- :doc:`CI/CD Integration <cicd>`
- :doc:`URL-based Input/Output <commands/remote_input_output>`
- :doc:`Universal Parameters <commands/universal_parameters>`
- :doc:`Game Data Structure <game_data_structure>`
- `dnx documentation <https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-dnx>`_
- `dotnet tool documentation <https://learn.microsoft.com/en-us/dotnet/core/tools/global-tools>`_
