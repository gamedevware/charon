Vector 2/3/4
------------

The ``Vector 2/3/4`` is a sub-type of the :doc:`Text <../all/text>` data type used to store a group of 2, 3, or 4 decimal values. These values are space-separated and must be parsed from the string before use at runtime.

UI Behavior
-----------

This field is represented in the editor as a group of input fields, each allowing the user to enter one component of the vector (e.g., X, Y, Z).

Validation Behavior
-------------------

The editor ensures that a valid vector is entered and only stores properly formatted values. However, there is no runtime validation or built-in parsing logic, so the value must be manually parsed in game code.

Parsing
-------

**Unity (C#) example:**

.. code-block:: cs

  var hero = gameData.AllHeroes.Get("Knight"); // -> Hero
  var startingLocationString = hero.StartingLocation; // -> "120.1 56.3 30.0"
  var components = startingLocationString.Split(' ');
  var startingLocation = new Vector3(
      float.Parse(components[0]),
      float.Parse(components[1]),
      float.Parse(components[2])
  );

**Unreal Engine (C++) example:**

.. code-block:: cpp

  auto Hero = GameData->AllHeroes->Find(TEXT("Knight")); // -> UHero*
  FString StartingLocationString = Hero->StartingLocation; // -> "120.1 56.3 30.0"
  TArray<FString> Components;
  StartingLocationString.ParseIntoArray(Components, TEXT(" "));
  FVector StartingLocation = FVector(
      FCString::Atof(*Components[0]),
      FCString::Atof(*Components[1]),
      FCString::Atof(*Components[2])
  );

**TypeScript example:**

.. code-block:: ts

  let hero = gameData.heroesAll.find("Knight"); // -> Hero
  let startingLocationString = hero.StartingLocation; // -> "120.1 56.3 30.0"
  let parts = startingLocationString.split(" ").map(parseFloat);
  let startingLocation: [number, number, number] = [parts[0], parts[1], parts[2]];

**Haxe example:**

.. code-block:: haxe

  var heroById = gameData.heroesAll.get("Knight"); // -> Hero
  var startingLocationString = heroById.StartingLocation; // -> "120.1 56.3 30.0"
  var parts = startingLocationString.split(" ").map(Std.parseFloat);
  var startingLocation = { x: parts[0], y: parts[1], z: parts[2] };
