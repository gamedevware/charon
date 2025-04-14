Integer Rectangle
-----------------

The ``Integer Rectangle`` (``RectangleInt``) is a sub-type of the :doc:`Text <../all/text>` data type used to store four integer values representing a rectangle. The components represent ``X``, ``Y``, ``Width``, and ``Height``, in that order. Values are separated by spaces and must be parsed from the string before use at runtime.

UI Behavior
-----------

This field is represented in the editor as a group of input fields labeled ``X``, ``Y``, ``Width``, and ``Height``. Each component accepts only whole numbers (integers).

Validation Behavior
-------------------

The editor ensures that a valid integer rectangle is entered and only stores properly formatted values. However, there is no runtime validation or built-in parsing logic, so values must be parsed manually in game code.

Parsing
-------

**Unity (C#) example:**

.. code-block:: cs

  var uiElement = gameData.AllUIElements.Get("HealthBar"); // -> UIElement
  var boundsString = uiElement.Bounds; // -> "50 100 200 25"
  var components = boundsString.Split(' ');
  var bounds = new RectInt(
      int.Parse(components[0]), // X
      int.Parse(components[1]), // Y
      int.Parse(components[2]), // Width
      int.Parse(components[3])  // Height
  );

**Unreal Engine (C++) example:**

.. code-block:: cpp

  auto UIElement = GameData->AllUIElements->Find(TEXT("HealthBar")); // -> UUIElement*
  FString BoundsString = UIElement->Bounds; // -> "50 100 200 25"
  TArray<FString> Components;
  BoundsString.ParseIntoArray(Components, TEXT(" "));
  FIntRect Bounds(
      FCString::Atoi(*Components[0]), // X
      FCString::Atoi(*Components[1]), // Y
      FCString::Atoi(*Components[2]), // Width
      FCString::Atoi(*Components[3])  // Height
  );

**TypeScript example:**

.. code-block:: ts

  let uiElement = gameData.uiElementsAll.find("HealthBar"); // -> UIElement
  let boundsString = uiElement.Bounds; // -> "50 100 200 25"
  let parts = boundsString.split(" ").map(x => parseInt(x, 10));
  let bounds = { x: parts[0], y: parts[1], width: parts[2], height: parts[3] };

**Haxe example:**

.. code-block:: haxe

  var uiElement = gameData.uiElementsAll.get("HealthBar"); // -> UIElement
  var boundsString = uiElement.Bounds; // -> "50 100 200 25"
  var parts = boundsString.split(" ").map(Std.parseInt);
  var bounds = { x: parts[0], y: parts[1], width: parts[2], height: parts[3] };
