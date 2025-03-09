Working with Source Code (Haxe)
=================================

Accessing game data during runtime is possible by utilizing the generated source code.

This section provides examples using default class names, but it is possible to customize class names during the source code generation process. Additionally, this customization allows to avoid naming collisions with existing code.

Loading Game Data
-----------------

The following Haxe code creates ``GameData`` class and loads your game data into memory.

.. code-block:: haxe
  
  import GameData;
  import Formatters;
  import haxe.io.Path;
  import sys.io.File;
  
  var input = File.read("RpgGameData.gdjs"); // or .json
  var options = new GameDataLoadOptions();
  options.format = GameDataFormat.Json;
  options.leaveInputsOpen = false;
  // options.patches <-- put patches here
  var gameData = new GameData(input, options);

The file ``RpgGameData.gdjs`` could be :doc:`published <publication>` game data or original database file (.gdjs or .gdmp).  
  
Accessing Documents
-------------------

You can access your documents as a list:

.. code-block:: haxe

  var allHeroes = gameData.heroesAll.list // -> ReadOnlyArray<Hero>
  var heroes = gameData.heroes.list // -> ReadOnlyArray<Hero>

Or you can access specific documents by their ``id`` or *Unique* properties:

.. code-block:: haxe
  using GameData; // load byName() and other extension methods
  
  var heroById = gameData.heroesAll.get(heroId); // -> Hero
  var heroByName = gameData.heroesAll.byName().get(heroName); // -> Hero

``Settings`` schemas are accessed by name:

.. code-block:: haxe

  var startingHeroes = gameData.startingSet.heroes; // -> ReadOnlyArray<Hero>
  
Formulas
--------

Formulas are currently not supported.


See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE HAXE Command <../advanced/commands/generate_haxe_code>`