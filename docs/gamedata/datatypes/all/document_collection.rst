Document Collection
===================

The DocumentCollection data type is used to store an array of sub-documents, which are used to represent complex structures.
It is important to note that the lifetime of sub-documents is tied to the lifetime of the parent document, meaning that any changes (e.g. deletion) to the parent document will affect all of its sub-documents.

Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | ReadOnlyCollection{T}                                           |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | ReadOnlyArray{T}                                                |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | TArray{T}                                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | ReadOnlyArray{T}                                                |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   Document Collection Text cannot be marked as unique.
Size
   May be limited in number of items. 0 - no limit.

Example
-------

One example use case for ``DocumentCollection`` is storing a list of items in a game, such as a chest and its contents. Each item in the chest could be represented by a sub-document containing information such as :doc:`reference <reference>` to an item and its :doc:`quantity <integer>`.

.. code-block:: js

  {
      "Name": "Silver Chest",
      "Loot": [
          {
              "Item": { "Id": "Sword" },
              "Quantity": 1
          },
          {
              "Item": { "Id": "Silver" },
              "Quantity": 100
          }
      ]
  }
