Asset Path
==========

The ``Asset Path`` is a sub-type of the :doc:`Text <../all/text>` data type and is used to store a path to a game asset within game data. 

Paths are typically relative to the project root and can be used to load assets directly at runtime.

Specification 
-------------

Asset Path Collection supports the following specification parameters:

- ``assetType`` — Filters the types of assets to select.  
  For Unity and Unreal Engine, this refers to class names.  
  For standalone builds, it refers to file extensions.  
  Example: ``assetType=Texture`` or ``assetType=Texture2D``

UI Behavior
-----------

This field is represented in the editor by a multi-select searchable input.  
Users can type to search for assets and add multiple items to the collection using auto-complete.

The search input supports the ``t:<TypeName>`` filter pattern to limit search results by asset type.

Examples:

- Unity: ``swing t:AudioClip``
- Unreal Engine: ``swing t:SoundWave``
- Standalone: ``swing t:wav``

Validation Behavior
-------------------

The Charon editor does not validate asset paths during game data loading (i.e., at runtime).  
You are responsible for ensuring the existence of assets at the provided paths.  
To improve reliability, consider writing a custom editor extension that validates all asset references before packaging the game.

Asset Localization
------------------

Localizable asset paths are not currently supported.  
If this is a required feature, you are encouraged to suggest it in Charon’s `Discord <https://discord.gg/2quB5vXryd>`_ channel.

Path Origin
-----------

The meaning of "relative path" for asset references depends on how the game data editor is launched:

- **Unity Editor**:  
  Paths are relative to the Unity project root directory, typically the directory containing the ``Assets`` folder.  
  Asset paths will usually start with ``Assets/``.  
  Example: ``Assets/Textures/MyTexture.png``

- **Unreal Engine Editor**:  
  Paths are relative to the Unreal project root directory, usually containing the ``Content`` folder.  
  Asset paths often start with ``/Game/`` because it is Unreal Engine package path, not physical path.  
  Example: ``/Game/Textures/MyTexture``

- **Standalone Execution** (via CLI):  
  Paths are relative to the game data file path by default.  
  This behavior can be customized using either:
  
  - The ``--gameAssetsPath`` CLI argument:  
    ``dotnet tool charon ./gamedata.gdjs --gameAssetsPath "C:/Projects/MyGame/"``
  
  - The ``STANDALONE__GAMEASSETSPATH`` environment variable.

Example
-------

.. code-block:: js

  "Assets/Textures/MyTexture.png"     // Unity
  "/Game/Textures/MyTexture"          // Unreal Engine
  "Textures/MyTexture.png"            // Standalone
