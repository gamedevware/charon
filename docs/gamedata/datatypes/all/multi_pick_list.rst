Multi-Pick List
===============

The ``MultiPickList`` data type is used when you want to allow the selection of multiple values from a predefined list of options. It is similar to the :doc:`PickList <pick_list>` data type, but it allows for multiple selections.

``MultiPickList`` is particularly useful when you want to replace several :doc:`Logical <logical>` properties that have a related meaning with a single property. For example, instead of having three separate properties to indicate if a item can be broken, disassembled, or sold, you can use a MultiPickList with the options "CanBeBreaken," "CanBeDisassembled," and "CanBeSold."

Source Code Type
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | Language                                              | Type                                                                     |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | C#                                                    | ``[Flags] enum``                                                         |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | TypeScript                                            | ``enum``                                                                 |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | ``UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`` |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | Haxe                                                  | ``abstract``                                                             |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
Uniqueness
   May be checked for uniqueness.
Size
   32 or 64bit

Example
-------
.. code-block:: js

  1 // internaly stored as integers
  "Apple" // string values also valid