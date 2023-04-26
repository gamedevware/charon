Overview
==========

The ``Reference`` data type allows the creation of non-embedding relationships between documents. A reference is essentially a pointer to another document, using that document's ``Id`` as a key. This allows for easier linking between related documents, without having to embed one document inside another.

When using a ``Reference``, the referenced documents are not stored within the parent document, but rather as references to their respective locations. This can be useful when dealing with large, complex data sets where it's more efficient to reference data than to embed it. Additionally, this data type can help enforce data integrity by ensuring that references to other documents are valid.

For example, in a game, a Chest with loot might have a reference to a specific inventory item document, rather than having the entire item embedded inside the chest document. This makes it easier to manage the loot separately of items and maintain the relationship between the chest, loot and and the item.

C# Type
   ``Reference{T}`` or ``T`` where ``T`` is Schema
Uniqueness
   May NOT be checked for uniqueness.
   
Example
=======

.. code-block:: js
  
  { "Id": "Sword" }
  "Sword" // just raw Id is also accepted
  
