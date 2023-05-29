Reference Collection
====================

The ``ReferenceCollection`` data type is used to create non-embedded relationships between documents. It allows for referencing multiple documents of the same type from within another document. 

When using a ``ReferenceCollection``, the referenced documents are not stored within the parent document, but rather as references to their respective locations. This can be useful when dealing with large, complex data sets where it's more efficient to reference data than to embed it. Additionally, this data type can help enforce data integrity by ensuring that references to other documents are valid.

For example, a game might have a collection of quests, each of which references a collection of objectives. The objectives might be stored in a separate collection for purpose rof e-use, and can be referenced by the quest document using the ``ReferenceCollection`` data type.

C# Type
   ``ReadOnlyList{T}`` or ``ReadOnlyList{Reference{T}}`` where ``T`` is Schema
Uniqueness
   May NOT be checked for uniqueness.
Size
   May be limited in number of items. 0 - no limit.
   
Example
-------

.. code-block:: js
  
  [{ "Id": "Sword" }, { "Id": "Gold" }]
  ["Sword", "Gold"] // just raw Ids are also accepted
  
