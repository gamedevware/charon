Integer Vector 2/3/4
====================

The ``Integer Vector 2/3/4`` is a sub-type of the :doc:`Text <../all/text>` data type used to store a group of 2, 3, or 4 integer (whole number) values. Values are separated by spaces and must be parsed from the string before use at runtime.

UI Behavior
-----------

This field is represented in the editor as a group of input fields, allowing the user to enter each component of the vector (e.g., X, Y, Z) as whole numbers.

Validation Behavior
-------------------

The editor ensures that a valid integer vector is entered and only stores properly formatted values. However, there is no runtime validation or built-in parsing logic, so the value must be manually parsed in game code.

Example
-------

.. code-block:: js

  "10 20 5"

Parsing
-------

**Unity (C#) example:**

.. code-block:: cs

  var hero = gameData.AllHeroes.Get("Knight"); // -> Hero
  var gridPositionString = hero.StartingLocation; // -> "10 20 5"
  var components = gridPositionString.Split(' ');
  var startingLocation = new Vector3Int(
      int.Parse(components[0]),
      int.Parse(components[1]),
      int.Parse(components[2])
  );

**Unreal Engine (C++) example:**

.. code-block:: cpp

  auto Hero = GameData->AllHeroes->Find(TEXT("Knight")); // -> UHero*
  FString GridPositionString = Hero->StartingLocation; // -> "10 20 5"
  TArray<FString> Components;
  GridPositionString.ParseIntoArray(Components, TEXT(" "));
  FIntVector StartingLocation = FIntVector(
      FCString::Atoi(*Components[0]),
      FCString::Atoi(*Components[1]),
      FCString::Atoi(*Components[2])
  );

**TypeScript example:**

.. code-block:: ts

  let hero = gameData.heroesAll.find("Knight"); // -> Hero
  let gridPositionString = hero.StartingLocation; // -> "10 20 5"
  let parts = gridPositionString.split(" ").map(x => parseInt(x, 10));
  let startingLocation: [number, number, number] = [parts[0], parts[1], parts[2]];

**Haxe example:**

.. code-block:: haxe

  var heroById = gameData.heroesAll.get("Knight"); // -> Hero
  var gridPositionString = heroById.StartingLocation; // -> "10 20 5"
  var parts = gridPositionString.split(" ").map(Std.parseInt);
  var startingLocation = { x: parts[0], y: parts[1], z: parts[2] };
