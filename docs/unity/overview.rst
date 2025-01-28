Unity Plugin Overview
=====================

Charon is a versatile `plugin <https://assetstore.unity.com/packages/tools/visual-scripting/game-data-editor-charon-95117>`_ tailored for Unity, designed to facilitate data-driven game design 
by allowing both developers and game designers to efficiently manage static game data, like 
units, items, missions, quests, and other. Charon elevates the experience by offering an editing UI directly in your web browser, 
enabling the modeling of diverse data structures suited to any game genre. 
It provides a user-friendly interface that requires no special skills for game designers, simplifying the process of data manipulation. 
For programmers, Charon streamlines development workflows by generating code to load game data seamlessly into the game.

Key Features
------------

- **Data Modeling**: Define game entities like characters, items, missions, quests, and dialogs to meet the specific needs of your game. Interconnect and fill these tables within one UI.
- **Error Control**: Implements validation checks to verify the accuracy of input data, reducing the likelihood of errors that could impact gameplay or development.
- **Code Generation**: Automates the creation of boilerplate code needed to work with your game data, significantly speeding up development time and reducing manual coding errors.
- **Spreadsheet Export/Import**: Offers seamless integration with spreadsheet software, enabling you to effortlessly populate, edit, and manage your game data in a familiar environment.
- **Localization Export/Import**: Simplifies the process of preparing game data for translation, making it straightforward to adapt your game for global audiences.
- **Modding Support**: Empowers your gaming community by providing them with the tools to create and share mods, enhancing the longevity and depth of your game.
- **Dynamic Load**: Facilitates the dynamic loading of game data, enabling features like A/B testing or the ability to push hot updates directly to your players.

Getting Started
===============

Prerequisites
------------

Unity plugin uses `dotnet tool charon`, which is a .NET Core application built for .NET 8.

.. tabs::

   .. tab:: Windows

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``%APPDATA%/Charon``.

   .. tab:: MacOS

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``~/Library/Application Support/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

   .. tab:: Linux

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``~/.config``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

**Checking Available .NET Versions**

.. code-block:: bash

    # check for mono already installed
    dotnet --list-sdks

.. code-block:: bash
    # output for dotnet --list-sdks
    5.0.303 [C:\Program Files\dotnet\sdk]
    5.0.408 [C:\Program Files\dotnet\sdk]
    6.0.428 [C:\Program Files\dotnet\sdk]
    7.0.120 [C:\Program Files\dotnet\sdk]
    8.0.206 [C:\Program Files\dotnet\sdk]
    8.0.405 [C:\Program Files\dotnet\sdk]

**Checking installed .NET version**

To examine your current .NET runtime version, you need to select 
**Tools** → **Charon** → **Troubleshooting** → **Check Runtime Version...** in the Unity menu after plugin being installed.

Installation from Unity Asset Store
-----------------------------------

1. Install the required software for your operating system.
2. Make sure your Unity version is 2020.1+.
3. Open the `Charon plugin <https://assetstore.unity.com/packages/tools/visual-scripting/game-data-editor-charon-95117>`_ in Unity Asset Store .
4. Click **Add To My Assets**.
5. Open Unity Package Manager by going to **Window → PackageManager**.
6. Wait for the package manager to populate the list.
7. Select **My Assets** from the dropdown on the top left corner.
8. Select **Charon** from the list and click download. If it’s already downloaded, you will see an import option.

Installation from GitHub
------------------------

1. Install the required software for your operating system.
2. Clone or download the `plugin source code <https://github.com/gamedevware/charon-unity3d>`_ from the GitHub repository.
3. Create a ``<project-dir>/Assets/Editor/GameDevWare.Charon`` directory.
4. Copy the plugin files from ``src/example/GameDevWare.Charon.Unity.2021/Assets/Editor/GameDevWare.Charon`` into this directory.
5. Restart Unity if needed.

Core Concepts
=============

Data-Driven Design Principles
-----------------------------

Data-driven design emphasizes the control of gameplay through data, rather than source code/blueprints, with game mechanics and processes determined by structured data files.  
For instance, rather than embedding damage calculations directly in the game's source code, these are defined by data specifying weapon effects and the rules for their application.  
Or for example, mission progression is not hardcoded; it's outlined in editable text files, making these aspects of game design highly flexible.  
This approach not only facilitates quick adjustments during development but also simplifies adding modding support post-release.  

  - `Modify Everything! Data-Driven Dynamic Gameplay Effects on 'For Honor' (Video) <https://www.gdcvault.com/play/1024050/Modify-Everything-Data-Driven-Dynamic>`_
  - `Data-driven Design in Unreal (Article) <https://benui.ca/unreal/data-driven-design/>`_


Understanding the Plugin's Architecture
---------------------------------------

**Plugin Assets**  

All game data information is stored in a JSON file within your project. The generated source code is utilized to load this data into the game. 
Additionally, you have the option to create a ``ScriptableObject`` asset with game data and integrate it into the game.
 Whenever there's a modification in the data structure within a JSON file, it's necessary to regenerate the C# source code and recreate the *.asset* file if it's being utilized.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/plugin_assets.png
  :width: 800
  :alt: Charon assets scheme in Unity

**Plugin Libraries**  

The plugin comprises the ``Assets/Editor/GameDevWare.Charon/GameDevWare.Charon.Unity.dll`` library, alongside the ``GameDevWare.Charon.Unity.Settings.json`` configuration file and the current settings stored in the ``/Library/Charon`` folder.  
  
The library contains the code required for seamless integration into the Unity editor environment and is not essential for running the game. The generated source code for game data is self-contained and does not rely on any external dependencies.  

Working with the Plugin
=======================

Creating Game Data
------------------

To create a new game data file within the Unity Editor, open the **Project** window, right-click in the desired folder, and select in the **Create → Game Data → Game Data (JSON)** menu option. 
Name your game data file and select it to review settings in **Inspector** window.  

1. Open the **Project** window and navigate to the desired folder.
2. Right-click the **Project** window and select **Create → Game Data → Game Data (JSON)**.
3. Double-click on the created file to start editing.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_create_gamedata.png
  :width: 800
  :alt: Unity Editor Create Game Data

Editing Game Data
------------------

To edit a game data file in the Unity Editor, open the **Project** window, find the corresponding *.gdjs* or *.gdmp* file, and double-click it. 
This action opens a new web browser window featuring a user interface for editing the game data. Remember to reimport and, if necessary, regenerate the source 
code after completing your edits.  

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_edit_gamedata.png
  :width: 800
  :alt: Charon UI in Unity Editor

Advanced Features
=======================

Localization and Multi-Language Support
---------------------------------------

Charon facilitates multi-language text support through the ``Localizable Text`` data type. When creating a *Schema*, properties can be defined with various data types, including ``Localizable Text``.
Initially, all localizable text defaults to ``EN-us`` (US English). Additional languages can be added via **Project Settings → Internationalization → Translation Languages** in the Charon UI.  
  
:doc:`Exporting/importing localizable data.<../advanced/internationalization>`  


Referencing Unity Assets
------------------------

By default, game data files and the Charon editor are unaware of the surrounding content/assets. 
To reference assets such as sounds, textures, models, or animations. For example you can create a 'UnitySoundAsset' schema with three 
properties: *Id* (required), *Path*, and *Name*. Prepare a listing of your assets (see Unity ``AssetDatabase`` class documentation) in following format:

.. code-block:: json
  
  {
      "UnitySoundAsset": [{
              "Id": "_Content_Sounds_MySound",
              "Path": "/Content/Sounds/MySound",
              "Name": "MySound"
          }
          /* other assets */
      ],
      /* other document collections to import */
  }

Then, import this list into your game data file using the ``CharonCli.ImportAsync`` method with ``ImportMode.Replace`` import mode. It's crucial that the *Id* field of imported 
records remains stable and unchanged across imports for the same assets.

After you've imported the asset list into the game data file, you can reference them from your documents by adding a ``Document Reference`` property with **Reference Type → Unity Sound Asset** to the schema.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_asset_reference.png
  :width: 800
  :alt: Charon assets scheme in Unity

Feedback
--------

We welcome and encourage feedback, particularly bug reports and suggestions, to help improve our tool. If you have any questions or would like to share your thoughts, 
please join our `Discord community <https://discord.gg/2quB5vXryd>`_ or reach out to us via email at `support@gamedevware.com <mailto:support@gamedevware.com>`_.  
  

See also
^^^^^^^^

- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Creating Document Type (Schema) <../gamedata/creating_schema>`
- :doc:`Filling Documents <../gamedata/filling_documents>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`