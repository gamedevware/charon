Integer
=======

The ``Integer`` data type is a whole number data type that is limited to 64 bits. It is used to represent integers without a fractional component. It can be used in cases where you need to store a large range of positive or negative whole numbers, such as in-game currency or player levels.

Unlike the :doc:`Number  <number>` data type, integers do not have any precision caveats since they do not store decimal values. Therefore, they are suitable for calculations that require exact values.

Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | System.Int32 or System.Int64                                    |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | number or bigint                                                |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | int32 or int64                                                  |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | Int or Int64                                                    |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   Integers can be marked as unique.
Size
   32 or 64bit

Example
-------
.. code-block:: js

  0
  -1
  100