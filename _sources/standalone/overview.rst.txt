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

The standalone version is a **cross-platform .NET 8 CLI application**. It operates as a dual-purpose tool:

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
============

Standalone application uses `dotnet-charon <https://www.nuget.org/packages/dotnet-charon>` tool, which is a .NET Core application built for .NET 8.

.. tab-set::

   .. tab-item:: Windows

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``%PROGRAMDATA%/Charon``.

   .. tab-item:: MacOS

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/Users/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

   .. tab-item:: Linux

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/home/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

**Checking Available .NET Versions**

.. code-block:: bash

    # check for dotnet already installed
    dotnet --list-runtimes

.. code-block:: bash

    # output for dotnet --list-runtimes
    Microsoft.AspNetCore.App 6.0.36 [C:\Program Files\dotnet\shared\Microsoft.AspNetCore.App]
    Microsoft.AspNetCore.App 7.0.20 [C:\Program Files\dotnet\shared\Microsoft.AspNetCore.App]
    Microsoft.AspNetCore.App 8.0.6 [C:\Program Files\dotnet\shared\Microsoft.AspNetCore.App]
    Microsoft.AspNetCore.App 9.0.0 [C:\Program Files\dotnet\shared\Microsoft.AspNetCore.App]
    Microsoft.NETCore.App 6.0.36 [C:\Program Files\dotnet\shared\Microsoft.NETCore.App]
    Microsoft.NETCore.App 7.0.20 [C:\Program Files\dotnet\shared\Microsoft.NETCore.App]
    Microsoft.NETCore.App 8.0.6 [C:\Program Files\dotnet\shared\Microsoft.NETCore.App] # <- this one is fine
    Microsoft.NETCore.App 9.0.0 [C:\Program Files\dotnet\shared\Microsoft.NETCore.App] # <- this one too

Installation and Updates
========================

You can use just two commands to install the command line tool, or use a bootstrap script that will check dependencies and installed software, and then download and run the tool for you.

dotnet tool (recommended)
-----------

.. code-block:: bash

  # install charon globally (run it once)
  dotnet tool install -g dotnet-charon
  
  # update global tool
  dotnet tool update -g dotnet-charon
  
  # make empty game data file
   charon INIT ./gamedata.json

  # run editor
   charon ./gamedata.json

Bootstrap Script
----------------

Two bootstrap scripts which download and run latest version of Charon on your PC:  

  - ``RunCharon.bat`` for Windows  
  - ``RunCharon.sh`` for Linux or MacOS  

.. warning::
    Bootstrap scripts require **.NET SDK️** to run, not only bare .NET Runtime.

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download/dotnet>`_ tool to be available in ``PATH``.

  1. Download one of the scripts into a local folder ``charon``.  
      a) `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_  
      b) `RunCharon.sh (Linux, MacOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_  
  2. Navigate to the local folder ``cd charon``. 
  3. Run ``RunCharon.bat`` or ``RunCharon.sh`` depending on your OS.  
  4. Wait for the script to automatically download and upgrade ``dotnet-charon tool``, and display help text.  
  5. Create an empty file named ``RunCharon.bat INIT gamedata.json``  
  6. Run in standalone mode: ``RunCharon.bat gamedata.json``  

Or use following bootstrap script:  

.. tab-set::

   .. tab-item:: Windows

      .. code-block:: bash
  
        rem ##### Load and run bootstrap script #####

        @echo off
        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
        ./RunCharon.bat INIT ./gamedata.json
        
        rem ##### Start editor #####

        ./RunCharon.bat ./gamedata.json --log out

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

        # charon INIT .\gamedata.json 
        # or
        # copy /y NUL .\gamedata.json >NUL
        
        charon .\gamedata.json --log out

   .. tab-item:: Linux, MacOS

      .. code-block:: bash

        # charon INIT ./gamedata.json 
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
