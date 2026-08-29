Standalone & CLI Overview
=========================

For developers who require maximum control over their environment, Charon offers a flexible standalone distribution. This version is built for those who prefer working outside of a specific game engine or need to automate their data workflows.

----------

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 800
  :alt: Charon editor UI
  
----------

1. What is it?
--------------

The standalone version is a **cross-platform .NET CLI application**. It operates as a dual-purpose tool:

* **Headless CLI:** A powerful command-line interface for data manipulation and code generation.
* **Local HTTP Server:** By launching a local server, it provides a high-performance **browser-based UI** for visual data modeling and editing without requiring an internet connection.

2. Which problem does it solve?
-------------------------------

While the engine plugins are great for standard development, the Standalone/CLI version addresses specialized technical requirements:

* **Custom Pipeline Integration:** Easily integrate game data validation and code generation into custom build scripts or tools.
* **CI/CD Automation:** Run data integrity checks and generate source code automatically on build servers (GitHub Actions, Jenkins, etc.).
* **Modding Toolsets:** Distribute a lightweight, engine-agnostic tool to your players, enabling them to create and edit game content safely.
* **Engine-Agnostic Workflows:** Work on game data for custom engines or projects that don't use Unity or Unreal.

3. For whom?
------------

This version is tailored for **advanced users and technical leads** who are comfortable with the terminal. It is ideal for:

* **Tools Engineers** building custom development pipelines.
* **Technical Designers** who need a standalone environment for content creation.
* **Build Engineers** automating game data processing in the cloud.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 800
  :alt: Charon editor UI

Prerequisites
=============

Standalone application uses the `dotnet-charon <https://www.nuget.org/packages/dotnet-charon>`_ tool,
which is distributed as a .NET tool. The `.NET SDK 10 or later <https://dotnet.microsoft.com/en-us/download>`_
is recommended - it provides ``dnx``, which runs Charon without installing anything. The .NET SDK 8 and 9
are also supported, but require an explicit install (see :ref:`Installation <CommandLine_Installation>`).

.. tab-set::

   .. tab-item:: Windows

      1. Download and install the `.NET SDK 10+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``%PROGRAMDATA%/Charon``.

   .. tab-item:: MacOS

      1. Download and install the `.NET SDK 10+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/Users/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

   .. tab-item:: Linux

      1. Download and install the `.NET SDK 10+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/home/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

**Checking Available .NET Versions**

.. code-block:: bash

    # check which SDKs are installed
    dotnet --list-sdks

.. code-block:: bash

    # output for dotnet --list-sdks
    8.0.404 [C:\Program Files\dotnet\sdk]   # supported, no dnx
    10.0.100 [C:\Program Files\dotnet\sdk]  # <- this one is what you want

Installation and Updates
========================

Either run the tool on demand with ``dnx``, install it once as a global tool, or use a bootstrap
script that checks dependencies, then downloads and runs the tool for you.

dnx (recommended, .NET SDK 10+)
-------------------------------

Nothing to install - ``dnx`` downloads and runs the tool on demand:

.. code-block:: bash

  # make empty game data file
  dnx dotnet-charon -- INIT ./gamedata.json

  # run editor
  dnx dotnet-charon -- ./gamedata.json

The tool is cached by NuGet after the first run, so subsequent invocations start quickly.

dotnet tool (.NET SDK 8+)
-------------------------

On .NET SDK 8 or 9 ``dnx`` is unavailable. Install the tool globally instead, which also lets you
type ``charon`` directly:

.. code-block:: bash

  # install charon globally (run it once)
  dotnet tool install -g dotnet-charon

  # update global tool
  dotnet tool update -g dotnet-charon

  # make empty game data file
  charon INIT ./gamedata.json

  # run editor
  charon ./gamedata.json

On macOS and Linux the ``charon`` command only works once ``$HOME/.dotnet/tools`` is on your
``PATH`` - see :ref:`Adding the global tool to PATH <CommandLine_Path>`.

.. youtube:: TOBmJEkNb2U
   :width: 640
   :height: 480

Bootstrap Script
----------------

Two bootstrap scripts which download and run the latest version of Charon on your PC:

  - ``RunCharon.bat`` for Windows
  - ``RunCharon.sh`` for Linux or MacOS

.. warning::
    Bootstrap scripts require the **.NET SDK** to run, not only the bare .NET Runtime.

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download/dotnet>`_ tool to be available in ``PATH``.

  1. Download the script for your OS into a local folder ``Charon``:

      a) `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_
      b) `RunCharon.sh (Linux, MacOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_

  2. Navigate into that folder with ``cd Charon``.
  3. Run the script with no arguments. It downloads and upgrades the ``dotnet-charon`` tool, then displays the help text.
  4. Create an empty game data file: ``.\RunCharon.bat INIT gamedata.json`` (Windows) or ``./RunCharon.sh INIT gamedata.json``.
  5. Run in standalone mode: ``.\RunCharon.bat gamedata.json`` (Windows) or ``./RunCharon.sh gamedata.json``.

Or copy the whole sequence:

.. tab-set::

   .. tab-item:: Windows

      .. code-block:: bat

        REM ##### Load and run bootstrap script #####

        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
        .\RunCharon.bat INIT .\gamedata.json

        REM ##### Start editor #####

        .\RunCharon.bat .\gamedata.json --log out

   .. tab-item:: Linux, MacOS

      .. code-block:: bash

        ##### Load and run bootstrap script #####

        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.sh
        chmod +x RunCharon.sh
        ./RunCharon.sh INIT ./gamedata.json

        ##### Start editor #####

        ./RunCharon.sh ./gamedata.json --log out

Creating and Editing Game Data
==============================

Any empty **gamedata.json** file could be used as starting point for standalone application launch. 
The editor will automatically fill the empty file with the initial data.  

.. tab-set::

   .. tab-item:: Windows

      .. code-block:: bash

        # dnx dotnet-charon -- INIT .\gamedata.json 
        # or
        # copy /y NUL .\gamedata.json >NUL
        
        charon .\gamedata.json --log out

   .. tab-item:: Linux, MacOS

      .. code-block:: bash

        # dnx dotnet-charon -- INIT ./gamedata.json 
        # or
        # touch ./gamedata.json 
        
        charon ./gamedata.json --log out

After finishing your work, you could just terminate the process with ``CTRL+C`` keyboard shortcut or close terminal window.  

See also
--------

- `Nuget Package <https://www.nuget.org/packages/dotnet-charon>`_
- `Bootstrap Scripts <https://github.com/gamedevware/charon/tree/main/scripts/bootstrap/>`_
- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Creating Document Type (Schema) <../gamedata/creating_schema>`
- :doc:`Filling Documents <../gamedata/filling_documents>`
- :doc:`Publication of Game Data <../gamedata/publication>`
- :doc:`Generating Source Code <../gamedata/generating_source_code>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`
