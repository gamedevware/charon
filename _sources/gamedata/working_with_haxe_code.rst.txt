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

Extension of Generated Code
-------------------------

Customizing Metadata
^^^^^^^^^^^^^^^^^^^^

You can append additional `metadata <https://haxe.org/manual/lf-metadata.html>`_ to the generated classes and their properties by modifying the ``Specification`` field of the related schema or property.

metadata annotations are specified using the ``haxeAttribute`` key in the ``Specification`` string, which uses the ``application/x-www-form-urlencoded`` format.

To help construct the correct value, you can use a spreadsheet formula (e.g., in Excel or Google Sheets):

.. code-block:: none

  # Place your attribute in cell A1
  =TEXTJOIN("&", 1, IF(ISBLANK(A1), "", "&haxeAttribute=" & ENCODEURL(A1)))

Alternatively, use JavaScript to generate the encoded string:

.. code-block:: javascript

  const params = new URLSearchParams(); 
  params.append("haxeAttribute", ":deprecated"); 
  console.log(params.toString());
  // → haxeAttribute=%3Adeprecated

After obtaining the encoded string, append it to the existing ``Specification`` value.

Example:

.. code-block:: none

  # Original Specification value:
  icon=material&group=Metadata

  # New attribute to add:
  haxeAttribute=%3Adeprecated

  # Final Specification value:
  icon=material&group=Metadata&haxeAttribute=%3Adeprecated

You can add multiple metadata annotations by including multiple ``haxeAttribute`` keys:

.. code-block:: none

  haxeAttribute=broken&haxeAttribute=range%281%2C+2%29

These metadata annotations will be emitted directly into the generated Haxe code, attached to the appropriate class or property.

See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE HAXE Command <../advanced/commands/generate_haxe_code>`