Unity Plugin Overview
=====================

If you are building a data-heavy game in Unity, managing that data through Inspector overrides or massive ScriptableObjects can quickly become unmanageable. The `Charon Unity Plugin <https://assetstore.unity.com/packages/tools/visual-scripting/game-data-editor-charon-95117>`_ provides a professional-grade database workflow directly within your Unity project.

----------

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 800
  :alt: Charon editor UI
  
----------

1. What is it?
--------------

The **Charon Unity Plugin** is an integrated extension for the Unity Editor that bridges the gap between game design and implementation. It combines a **structured data editor** (accessible via an embedded or external browser) with a **native code generator**.

Instead of manual data entry, it provides a centralized "Game Database" inside your project that behaves like a professional CMS but lives within your local assets.

2. Which problem does it solve?
-------------------------------

Unity's built-in tools are often insufficient for complex game data. Charon solves the most common "data-driven" headaches:

* **ScriptableObject Sprawl:** No more navigating hundreds of individual ``.asset`` files. All your items, NPCs, and quests are managed in one organized, searchable database.
* **Lack of Type Safety:** Charon automatically generates the C# classes needed to load your data. This means you get **full IntelliSense support**—no more searching for strings or worrying about typos in your code.
* **The "Designer-to-Developer" Gap:** It provides a user-friendly, non-technical UI for designers to balance numbers and write dialogue, while generating the clean, performant code that programmers expect.
* **Localization Bottlenecks:** It includes built-in support for multi-language text, allowing you to swap languages or export translation keys without leaving the editor.

3. For whom?
------------

* **Unity Developers:** Who want to stop writing boilerplate data-loading code and start using type-safe, optimized data structures.
* **Game & Narrative Designers:** Who need a powerful, visual environment to model complex systems (like skill trees or quest branches) without touching a line of code.
* **Production Teams:** Working on RPGs, CCGs, Strategy games, or any project where thousands of balanced data points are the core of the experience.

----------

Key Features
------------

+----------------------+---------------------------------------------------------------------------------+
| Feature              | Description                                                                     |
+======================+=================================================================================+
| **In-Editor Server** | Launch the data editor directly from the Unity menu bar.                        |
+----------------------+---------------------------------------------------------------------------------+
| **Auto-Generation**  | C# code is updated automatically whenever you change your data schema.          |
+----------------------+---------------------------------------------------------------------------------+
| **Asset Integration**| Link your game data directly to Unity Assets (like Prefabs, Sprites, etc.).     |
+----------------------+---------------------------------------------------------------------------------+
| **Memory Efficient** | Optimized loading routines designed specifically for mobile/console performance.|
+----------------------+---------------------------------------------------------------------------------+

Getting Started
===============

Prerequisites
------------

Unity plugin uses ``dotnet charon`` tool, which is a .NET Core application built for .NET 8.

.. tab-set::

   .. tab-item:: Windows

      1. Download and install `NET SDK 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``%PROGRAMDATA%/Charon``.

   .. tab-item:: MacOS

      1. Download and install `NET SDK 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/Users/<username>/.config/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

   .. tab-item:: Linux

      1. Download and install `NET SDK 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/usr/share/Charon``.
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

Microsoft.WindowsDesktop.App 9.0.0 [C:\Program Files\dotnet\shared\Microsoft.WindowsDesktop.App]

Installation from OpenUPM (recommended)
---------------------------------------

.. youtube:: xJLR5lkDYb8
   :width: 640
   :height: 480

1. Install the required software for your operating system.
2. Ensure your Unity version is 2021.3 or later.
3. Open the `OpenUPM <https://openupm.com/packages/com.gamedevware.charon/>`_ page for the plugin.
4. Click the **Manual Installation** button in the upper right corner and follow the instructions.


Installation from Unity Asset Store
-----------------------------------

.. youtube:: MoklxNzt_aY
   :width: 640
   :height: 480

1. Install the required software for your operating system.
2. Ensure your Unity version is 2021.3 or later.
3. Open the `Charon plugin <https://assetstore.unity.com/packages/tools/visual-scripting/game-data-editor-charon-95117>`_ in the Unity Asset Store.
4. Click **Add To My Assets**.
5. Open the Unity Package Manager by navigating to **Window → Package Manager**.
6. Wait for the package manager to populate the list.
7. Select **My Assets** from the dropdown in the top left corner.
8. Select **Charon** from the list and click **Download**. If it’s already downloaded, you will see an **Import** option.


Installation from GitHub
------------------------

1. Install the required software for your operating system.
2. Clone or download the `plugin source code <https://github.com/gamedevware/charon-unity3d>`_ from the GitHub repository.
3. Create a ``<project-dir>/Packages/com.gamedevware.charon`` directory.
4. Copy the plugin files from ``src/GameDevWare.Charon.Unity/Packages/com.gamedevware.charon`` into this directory.
5. Restart Unity if necessary.


Core Concepts
=============

Data-Driven Design Principles
-----------------------------

Data-driven design emphasizes controlling gameplay through data rather than source code or blueprints. Game mechanics and processes are determined by structured data files.  
For example, instead of embedding damage calculations directly in the game's source code, these are defined by data specifying weapon effects and the rules for their application.  
Similarly, mission progression is not hardcoded; it is outlined in editable text files, making these aspects of game design highly flexible.  
This approach not only facilitates quick adjustments during development but also simplifies adding modding support post-release.  

  - `Modify Everything! Data-Driven Dynamic Gameplay Effects in 'For Honor' (Video) <https://www.gdcvault.com/play/1024050/Modify-Everything-Data-Driven-Dynamic>`_
  - `Data-driven Design in Unreal (Article) <https://benui.ca/unreal/data-driven-design/>`_


Understanding the Plugin's Architecture
---------------------------------------

**Plugin Assets**  

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_plugin_assets.png
  :width: 800
  :alt: Charon assets scheme in Unity

All game data information is stored in a JSON file within your project. The generated source code is used to load this data into the game. 
Additionally, a ``ScriptableObject`` asset will be created, which can be used to access game data from your scenes.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_plugin_asset_inspector.png
  :width: 519
  :alt: Charon asset Inspector view

Whenever there is a modification in the data structure within a JSON file, it is necessary to regenerate the C# source code and reimport the *.asset* file. To do this, select the *.asset* file and press the **Synchronize** button.


Working with the Plugin
=======================

.. youtube:: EZ0oEEVuEug
   :width: 640
   :height: 480

Creating Game Data
------------------

To create a new game data file within the Unity Editor, open the **Project** window, right-click in the desired folder, and select the **Create → Game Data** menu option. 

1. Open the **Project** window and navigate to the desired folder.
2. Right-click in the **Project** window and select **Create → Game Data**.
3. Name your game data file and click the **Create** button.
4. Wait for the source code and assets to be created in the specified folder and for the editor to recompile the scripts.
5. Double-click the created *.asset* or *.gdjs* file to start editing.


Editing Game Data
------------------

To edit a game data file in the Unity Editor, open the **Project** window, find the corresponding *.gdjs*, *.gdmp*, or *.asset* file, and double-click it. 
This action opens a new web browser window featuring a user interface for editing the game data. Remember to **Synchronize** assets from the Inspector window after completing your edits.  

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


Referencing Game Data in Scenes
-------------------------------

The Charon plugin introduces a specific type for referencing documents within scenes, named ``GameDataDocumentReference``. This type is part of the Charon package. To create such a reference, add a field with the ``GameDataDocumentReference`` type to your component class. 

.. code-block:: csharp
  
  public class HeroComponent : MonoBehaviour
  {
    public GameDataDocumentReference heroReference;
  }

You can then configure it in the Inspector. Here is an example of a **Game Data Document Reference** used to point to a *Hero* document:

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_document_reference.png
  :width: 516
  :alt: Charon document reference example screenshot

To get an instance of a document in your game code, call the ``GameDataDocumentReference.GetReferencedDocument<Hero>()`` method.

.. code-block:: csharp
  
  private void OnEnable()
  {
    var hero = this.heroReference.GetReferencedDocument<Hero>();
    Debug.Log(hero.Name);
  }

Referencing Unity Assets
------------------------

To reference assets within the game, you can use a special :doc:`Asset <../gamedata/datatypes/sub/asset>` composite type. Create a property via ``Composite Types`` -> ``Asset Path`` menu options.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/schema_designer_select_editor.png
  :width: 800
  :alt: Schema Designer with Custom Editor


Work & Build Automation
-----------------------

To facilitate automation of work or builds, a programmatic interface for working with game data is provided. You can read more about it on the :doc:`CharonCli <charon_cli>` class documentation page.


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