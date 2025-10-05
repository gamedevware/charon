 
Logical
=======

The ``Logical`` data type is used to represent boolean values — values that can be either ``true`` or ``false``. It is suitable for modeling simple binary states, conditions, or flags commonly used throughout game data.

Use Cases
---------

The ``Logical`` type is ideal for:

- Representing **simple state**:  
  Examples include `IsActive`, `IsPublished`, `IsLatest`, `IsReligious`, or `IsOptional`.

- Indicating **ownership or structural conditions**:  
  Examples include `HasPartner`, `HasSecondPhase`.

- Controlling **behavioral expectations**:  
  Examples include `ShouldFinishTutorial`, `ShouldGoFirst`.

- Defining **capabilities or permissions**:  
  Examples include `CanBlock`, `CanRun`, `CanBeSold`.

This makes the ``Logical`` type a versatile and lightweight choice for many decision-driven properties in schema design.

Comparison with MultiPickList
-----------------------------

While the :doc:`MultiPickList <multi_pick_list>` data type can represent combinations of multiple states, the ``Logical`` type is recommended when the property has exactly two possible values.  
Using ``Logical`` ensures simplicity, clarity, and optimal editor behavior for binary flags.

Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | System.Boolean                                                  |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | boolean                                                         |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | bool                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | Bool                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   Logical can be marked as unique.

Example
-------
.. code-block:: js

  true
  false
  True
  False
  1
  0
  "Yes"
  "No"
  