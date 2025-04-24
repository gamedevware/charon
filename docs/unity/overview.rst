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

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 800
  :alt: Charon editor UI

Getting Started
===============

Prerequisites
------------

Unity plugin uses ``dotnet charon`` tool, which is a .NET Core application built for .NET 8.

.. tabs::

   .. tab:: Windows

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``%PROGRAMDATA%/Charon``.

   .. tab:: MacOS

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``~/Library/Application Support/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

   .. tab:: Linux

      1. Download and install `NET 8+ <https://dotnet.microsoft.com/en-us/download>`_.
      2. Make sure you have write access to ``/usr/share/Charon``.
      3. Make sure ``dotnet`` is available from ``$PATH``.

**Checking Available .NET Versions**

In terminal window run ``dotnet --list-runtimes`` command:

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

Microsoft.WindowsDesktop.App 9.0.0 [C:\Program Files\dotnet\shared\Microsoft.WindowsDesktop.App]

Installation from OpenUPM (recommended)
---------------------------------------

1. Install the required software for your operating system.
2. Ensure your Unity version is 2021.3 or later.
3. Open the `OpenUPM <https://openupm.com/packages/com.gamedevware.charon/>`_ page for the plugin.
4. Click the **Manual Installation** button in the upper right corner and follow the instructions.


Installation from Unity Asset Store
-----------------------------------

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

To reference assets within the game, you can use a special :doc:`sub-data <../gamedata/datatypes/sub/asset>` type. Create a property with the ``Text`` type, enable the `Advanced Options`, and select the `Asset Path` editor for this property.

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