Unreal Engine Plugin Overview
=============================

Charon is a versatile plugin tailored for Unreal Engine, designed to facilitate data-driven game design 
by allowing both developers and game designers to efficiently manage static game data, like 
units, items, missions, quests, and other. Unlike Unreal Engine's DataTables, Charon elevates the 
experience by offering an integrated editing UI directly within Unreal Engine, 
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

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 800
  :alt: Charon editor UI

Getting Started
===============

To begin using `this <https://www.unrealengine.com/marketplace/en-US/product/charon-game-data-editor>`_ plugin, the initial step involves installing the plugin from the Unreal Engine Marketplace. 
Once installed, you'll need to `enable the plugin <https://docs.unrealengine.com/5.2/en-US/working-with-plugins-in-unreal-engine/>`_ for your project through the project settings. 
Following this, a rebuild of your project's C++ code is necessary. The final step in the setup process is the creation of your first game data file.

Prerequisites
-------------

The Unreal Engine plugin is written in C++ but relies on ``dotnet charon``, a .NET Core application which runs on .NET 8.

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

    # check for dotnet already installed
    dotnet --list-sdks

.. code-block:: bash
    # output for dotnet --list-sdks
    5.0.303 [C:\Program Files\dotnet\sdk]
    5.0.408 [C:\Program Files\dotnet\sdk]
    6.0.428 [C:\Program Files\dotnet\sdk]
    7.0.120 [C:\Program Files\dotnet\sdk]
    8.0.206 [C:\Program Files\dotnet\sdk]
    8.0.405 [C:\Program Files\dotnet\sdk]

Installation from Marketplace
-----------------------------

1. Add to cart Charon plugin `[Epic Launcher] <com.epicgames.launcher://ue/marketplace/product/b4231a79707e491ba96b9842d971e6f4>`_ / `[Web] <https://www.unrealengine.com/marketplace/en-US/product/charon-game-data-editor>`_ in the Unreal Engine Marketplace.
2. Follow the `instruction <https://docs.unrealengine.com/5.2/en-US/working-with-plugins-in-unreal-engine/>`_ on installing plugin into your project:
  a. Click **Install to Engine** and select the engine version.
  b. Open your project and go to **Edit → Plugins...** window.
  c. Type **Charon** in the **Search** bar.
  d. Check the checkbox near the plugin's name to enable it.
3. Rebuild project C++ code.

Building from Source Code
-------------------------

1. Clone or download the `plugin source code <https://github.com/gamedevware/charon-unreal-engine/tree/main>`_ from the GitHub repository.
2. Create a ``<project-dir>/Plugins/Charon`` directory.
3. Copy the plugin files into this directory. Ensure **Charon.uplugin** is located at the path ``<project-dir>/Plugins/Charon/Charon.uplugin`` after copying.
4. Remove the ``"EngineVersion"`` attribute if your engine doesn't match the plugin's engine version.
5. Rebuild the project's C++ code.
6. Enable the plugin in **Edit → Plugins...** if needed.


Core Concepts
=============

Data-Driven Design Principles
-----------------------------

Data-driven design emphasizes the control of gameplay through data, rather than source code/blueprints, with game mechanics and processes determined by structured data files.  
For instance, rather than embedding damage calculations directly in the game's source code, these are defined by data specifying weapon effects and the rules for their application.  
Or for example, mission progression is not hardcoded; it's outlined in editable text files, making these aspects of game design highly flexible.  
This approach not only facilitates quick adjustments during development but also simplifies adding modding support post-release.  

  - `Data Driven Gameplay Elements (UE Documentation) <https://docs.unrealengine.com/5.3/en-US/data-driven-gameplay-elements-in-unreal-engine/>`_  
  - `Modify Everything! Data-Driven Dynamic Gameplay Effects on 'For Honor' (Video) <https://www.gdcvault.com/play/1024050/Modify-Everything-Data-Driven-Dynamic>`_
  - `Data-driven Design in Unreal (Article) <https://benui.ca/unreal/data-driven-design/>`_


Understanding the Plugin's Architecture
---------------------------------------

**Plugin Assets**  
  
Working with data in this plugin is akin to how the built-in *DataTable* functions. There is a data source file, a module containing the code required to load the data, 
and an asset that will be utilized in the game. Whenever you edit a data source file, you need to re-import this data into the asset. 
Should the data structure in the source file change, then the C++ code must be regenerated.  

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/ue_plugin_assets.png
  :width: 800
  :alt: Charon assets scheme in Unreal Engine

For scenarios requiring dynamic loading of game data, this can be accomplished through the ``TryLoad`` method on the game data class, which accepts the source JSON file.  
  
**Plugin Modules**  
  
The Charon plugin is structured into two modules: 
  - ``CharonEditor`` module acts as an Unreal Engine Editor extension. Extension points for the module are declared in the ``ICharonEditorModule`` class, and automation of game data processing is facilitated through the ``FCharonCli`` class.  
  - ``Charon`` module, houses the core logic and shared code crucial for handling game data files.  
  
Working with the Plugin
=======================

Creating Game Data
------------------

To create a new game data file within the Unreal Engine Editor, open the **Content Drawer**, right-click in the desired folder, and select in the **Create Advanced Assets** section **Miscellaneous → Game Data** menu option. 
Name your game data file and proceed according to the instructions in the dialog window that appears.  
  
:doc:`Detailed guide on how to create game data. <creating_game_data>`

Editing Game Data
------------------

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/ue_editor_screenshot.png
  :width: 800
  :alt: Charon UI in Unreal Engine editor

To edit a game data file in the Unreal Engine Editor, navigate to the **Content Drawer**, find the corresponding .uasset file, and double-click it. 
This action opens a new window featuring a user interface for editing the game data. Remember to reimport and, if necessary, regenerate the source 
code after completing your edits.  

Refencing Game Data in Blueprints
--------------------------------

Similar to the DataTable's ``FDataTableRowHandle``, the Charon plugin introduces a specific type for referencing documents within Blueprints, 
named ``FGameDataDocumentReference``. This type is housed within the Charon module. Here is example of **Game Data Document Reference** used to resolve *Hero* document:

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/ue_document_reference.png
  :width: 800
  :alt: Charon document reference example screenshot

Advanced Features
=======================

Localization and Multi-Language Support
---------------------------------------

Charon facilitates multi-language text support through the ``Localizable Text`` data type. When creating a *Schema*, properties can be defined with various data types, including ``Localizable Text``.
Initially, all localizable text defaults to ``EN-us`` (US English). Additional languages can be added via **Project Settings → Internationalization → Translation Languages** in the Charon UI.  
  
:doc:`Exporting/importing localizable data.<../advanced/internationalization>`  

Referencing Unreal Engine Assets
--------------------------------

By default, game data files and the Charon editor are unaware of the surrounding content/assets. 
To reference assets such as sounds, textures, models, or animations. For example you can create a 'UeSoundAsset' schema with three 
properties: *Id* (required), *Path*, and *Name*. Prepare a ``FJsonObject`` listing of your assets (see Unreal Engine ``AssetRegistry`` module documentation) in following format:

.. code-block:: json
  
  {
      "UeSoundAsset": [{
              "Id": "_Content_Sounds_MySound",
              "Path": "/Content/Sounds/MySound",
              "Name": "MySound"
          }
          /* other assets */
      ],
      /* other document collections to import */
  }

Then, import this list into your game data file using the ``FCharonCli::Import`` method with ``EImportMode::Replace`` import mode. It's crucial that the *Id* field of imported 
records remains stable and unchanged across imports for the same assets.

To streamline the process of importing asset paths, consider leveraging the ``ICharonEditorModule::OnGameDataPreSynchronization`` event. 
This allows for automatic execution of the import routine each time the **Import** button is clicked in the UI.

After you've imported the asset list into the game data file, you can reference them from your documents by adding a ``Document Reference`` property with **Reference Type → UeSoundAsset** to the schema.

Feedback
--------

We welcome and encourage feedback, particularly bug reports and suggestions, to help improve our tool. If you have any questions or would like to share your thoughts, 
please join our `Discord community <https://discord.gg/2quB5vXryd>`_ or reach out to us via email at `support@gamedevware.com <mailto:support@gamedevware.com>`_.  
  

See also
--------

- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Creating Document Type (Schema) <../gamedata/creating_schema>`
- :doc:`Filling Documents <../gamedata/filling_documents>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`


