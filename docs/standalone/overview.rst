Standalone Application Overview
===============================

The standalone version of the game development `tool <https://www.nuget.org/packages/GameDevWare.Charon>`_ is a desktop application that can be installed on 
a computer, and it allows the user to design and model game data, as well as generate source code for it. 
The standalone version is typically used by individual game developers or small development teams who want to work offline.

Requirements
============

Charon is a .NET Framework 4.7.2 and/or Mono 5.18.0 application. It currently uses ``.NET Core`` tools for bootstrap scripts.

.. tabs::

   .. tab:: Windows

      1. Download and install `.NET Framework 4.7.2+ <https://dotnet.microsoft.com/en-us/download/dotnet-framework/net472>`_.
      2. Download and install `.NET Core 5+ <https://dotnet.microsoft.com/en-us/download/dotnet>`_.
      3. Make sure you have write access to ``%APPDATA%/Charon``.

   .. tab:: MacOS

      1. Download and install `Mono runtime 5.18.0+ <http://www.mono-project.com/download/#download-mac>`_.
      2. Download and install `.NET Core 5+ <https://dotnet.microsoft.com/en-us/download/dotnet>`_.
      3. Make sure you have write access to ``~/Library/Application Support/Charon``.
      4. Make sure ``mono`` is available from ``$PATH``.

   .. tab:: Linux

      1. Download and install `Mono runtime 5.18.0+ <https://www.mono-project.com/download/stable/#download-lin>`_.
      2. Download and install `.NET Core 5+ <https://dotnet.microsoft.com/en-us/download/dotnet>`_.
      3. Make sure you have write access to ``~/.config``.
      4. Make sure ``mono`` is available from ``$PATH``.

.. code-block:: bash

  # check for mono is already installed
  mono --version
  
  # check for .NET Core is already installed
  dotnet --version

Installation and Updates
========================

There is two bootstrap scripts which download and run latest version of Charon on your PC:  

  - ``RunCharon.bat`` for Windows  
  - ``RunCharon.sh`` for Linux or MacOS  

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download/dotnet>`_ tool to be available in ``PATH`` 
and `mono <https://www.mono-project.com/download/stable/>`_ installed for Linux and MacOS.  

  1. Download one of the scripts into a local folder ``charon``.  
      a) `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_  
      b) `RunCharon.sh (Linux, MacOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_  
  2. Navigate to the local folder ``cd charon``. 
  3. Run ``RunCharon.bat`` or ``RunCharon.sh`` depending on your OS.  
  4. Wait for the script to automatically download and upgrade ``Charon.exe``, and display help text.  
  5. Create an empty file named ``gamedata.json``  
  6. Run ``Charon.exe`` in standalone mode  

Or use following bootstrap script:  

.. tabs::

   .. tab:: Windows

      .. code-block:: bash
  
        rem ##### Load and run bootstrap script #####

        @echo off
        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.bat
        echo. 2>  gamedata.json
        
        rem ##### Start editor #####

        RunCharon.bat SERVER START --database ./gamedata.json --launchDefaultBrowser --log out

   .. tab:: Linux, MacOS

      .. code-block:: bash

        ##### Load and run bootstrap script #####

        mkdir Charon
        cd Charon
        curl -O https://raw.githubusercontent.com/gamedevware/charon/main/scripts/bootstrap/RunCharon.sh
        touch gamedata.json
        chmod +x RunCharon.sh
        
        ##### Start editor #####

        ./RunCharon.sh SERVER START --database ./gamedata.json --launchDefaultBrowser --log out

Creating and Editing Game Data
==============================

Any empty **gamedata.json** file could be used as starting point for standalone application launch. 
The editor will automatically fill the empty file with the initial data.  

.. tabs::

   .. tab:: Windows

      .. code-block:: bash
  
        ./RunCharon.bat SERVER START --database ./gamedata.json --launchDefaultBrowser --log out

   .. tab:: Linux, MacOS

      .. code-block:: bash

        ./RunCharon.sh SERVER START --database ./gamedata.json --launchDefaultBrowser --log out

After finishing your work, you could just terminate the process.  

See also
--------

- `Nuget Package <https://www.nuget.org/packages/GameDevWare.Charon>`_
- `Bootstrap Scripts <https://github.com/gamedevware/charon/tree/main/scripts/bootstrap/>`_
- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Creating Document Type (Schema) <../gamedata/creating_schema>`
- :doc:`Filling Documents <../gamedata/filling_documents>`
- :doc:`Publication of Game Data <../gamedata/publication>`
- :doc:`Generating Source Code <../gamedata/generating_source_code>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`
