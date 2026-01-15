Unreal Engine Plugin Overview
=============================

For Unreal Engine developers, managing complex game data shouldn't mean fighting with restricted DataTables or bloated Blueprints. The `Charon Unreal Plugin <https://www.unrealengine.com/marketplace/en-US/product/charon-game-data-editor>`_ provides a robust, professional-grade database workflow designed to handle the scale and performance requirements of modern UE projects.

----------

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 800
  :alt: Charon editor UI

----------

1. What is it?
--------------

The **Charon Unreal Plugin** is a high-performance data management ecosystem integrated directly into the Unreal Editor. It replaces traditional, flat DataTables with a **relational game database** that supports complex nesting, cross-references, and multi-language text—all accessible via a native-feeling UI and backed by an automated C++ code generator.

2. Which problem does it solve?
-------------------------------

While Unreal Engine is powerful, its default data tools often fall short in complex productions. Charon solves these specific pain points:

* **DataTable Limitations:** Unlike standard DataTables, Charon handles deep hierarchies and complex relationships (like branching quest lines or intricate skill trees) without becoming a visual mess.
* **Boilerplate Fatigue:** It automatically generates the **C++ and Blueprint** code required to access your data, eliminating the need to manually write struct definitions or parsing logic.
* **Data Fragility:** With built-in validation checks, it catches errors (like broken links or out-of-range values) before they cause a crash in your build.
* **Content "Locked" in the Engine:** It allows for easy import/export for spreadsheets and localization, making it easier to collaborate with external writers or translation agencies.

3. For whom?
------------

* **Technical Directors & Programmers:** Who need type-safe, performant C++ access to game data and a reliable pipeline for CI/CD and modding support.
* **Game & Narrative Designers:** Who require a structured environment to build massive game worlds, item economies, and dialogue systems without needing to know C++.
* **Live-Ops Teams:** Who need the ability to dynamically load data updates or perform A/B testing without submitting a new build to storefronts.

----------

Key Features
------------

+------------------------------+----------------------------------------------------------------------------+
| Feature                      | Benefit to Your Workflow                                                   |
+==============================+============================================================================+
| **C++/Blueprint Generation** | Access your data instantly with full IDE auto-complete and Blueprint nodes.|
+------------------------------+----------------------------------------------------------------------------+
| **Relational Modeling**      | Interconnect tables (Items, Quests, NPCs) with ease within a single UI.    |
+------------------------------+----------------------------------------------------------------------------+
| **Hot Updates**              | Support for dynamic loading of game data for live-tuning and hotfixes.     |
+------------------------------+----------------------------------------------------------------------------+
| **Modding Support**          | Give your community the same professional tools to create game mods.       |
+------------------------------+----------------------------------------------------------------------------+
| **Localization**             | Seamlessly export and import translation keys for global releases.         |
+------------------------------+----------------------------------------------------------------------------+

Getting Started
===============

To begin using `this <https://www.unrealengine.com/marketplace/en-US/product/charon-game-data-editor>`_ plugin, the initial step involves installing the plugin from the Unreal Engine Marketplace. 
Once installed, you'll need to `enable the plugin <https://docs.unrealengine.com/5.2/en-US/working-with-plugins-in-unreal-engine/>`_ for your project through the project settings. 
Following this, a rebuild of your project's C++ code is necessary. The final step in the setup process is the creation of your first game data file.

Prerequisites
-------------

The Unreal Engine plugin is written in C++ but relies on ``dotnet charon``, a .NET Core application which runs on .NET 8.

.. tab-set::

   .. tab-item:: Windows

      1. Download and install `SDK NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``%PROGRAMDATA%/Charon``.

   .. tab-item:: MacOS

      1. Download and install `SDK NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/Users/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

.. tab-item:: Linux

      1. Download and install `NET SDK 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/home/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

**Checking Available .NET SDK Versions**

.. code-block:: bash

    # check for dotnet already installed
    dotnet --list-sdks

.. code-block:: bash

    # output for dotnet --list-sdks
    7.0.120 [C:\Program Files\dotnet\sdk]
    8.0.206 [C:\Program Files\dotnet\sdk]
    8.0.414 [C:\Program Files\dotnet\sdk]  # <- this one is fine
    9.0.300 [C:\Program Files\dotnet\sdk]  # <- this one too

Installation from Marketplace
-----------------------------

1. Add to cart Charon plugin `[Epic Launcher] <com.epicgames.launcher://ue/marketplace/product/b4231a79707e491ba96b9842d971e6f4>`_ / `[Fab.com Asset Page] <https://www.unrealengine.com/marketplace/en-US/product/charon-game-data-editor>`_ in the Unreal Engine Marketplace.
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

To reference assets within the game, you can use a special :doc:`Asset <../gamedata/datatypes/sub/asset>` composite type. Create a property via ``Composite Types`` -> ``Asset Path`` menu options.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/schema_designer_select_editor.png
  :width: 800
  :alt: Schema Designer with Custom Editor

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


