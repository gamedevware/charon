Logical
=======

The ``Logical`` data type is used to represent boolean values, i.e., values that can be either true or false. It is commonly used in game development to represent various settings, options, or conditions.

For example, a game designer may use a ``Logical`` data type to represent whether a particular game feature is enabled or disabled. The ``Logical`` data type can be used in combination with control flow statements, such as conditional statements or loops, to determine the behavior of the game.

The :doc:`MultiPickList <multi_pick_list>` data type can also be used to represent boolean values, but it allows the selection of multiple options instead of just two. This can be useful for representing more complex options or flags that require multiple selections. However, if the options are limited to just two, it is recommended to use the Logical data type for clarity and simplicity.

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
   May be checked for uniqueness.

Example
-------
.. code-block:: js

  true
  false