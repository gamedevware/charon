Reference Collection
====================

The ``ReferenceCollection`` data type is used to create non-embedded, one-to-many relationships between documents. It allows a document to reference multiple documents of the same type without embedding them directly.

When using a ``ReferenceCollection``, the referenced documents are stored as references to their original locations, rather than being embedded in the parent document. This approach is particularly useful when dealing with large or complex datasets where referencing is more efficient and scalable than embedding. It also helps maintain data integrity by ensuring that all references point to valid documents.

For example, in a game, each **Quest** may reference a collection of **Objectives**. These objectives can be defined separately for reuse across multiple quests. The ``ReferenceCollection`` data type enables the quest document to maintain a list of references to objective documents.

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
   Reference Collection cannot be marked as unique.
Size
   May be limited in number of items. 0 - no limit.
Specification 
   References support the following specification parameter:
   
   - ``displayTextTemplate`` — Defines a template string for how the referenced value is displayed in the UI.  
   
     Example:  
     ``displayTextTemplate=Item%3A+%7BName%7D%2C+Count%3A+%7BCount%7D``  
     (renders as: `Item: {Name}, Count: {Count}`)  
   
   - ``localOnly`` — Limits the selection to documents defined within the current document. References from other documents will be excluded from the drop-down list.  
   
     Example:  
     ``localOnly=true``  
   
   - ``pathFilter`` — Filters available documents based on their path (RFC 6901 JSON Pointer). Use ``*`` to include all paths, or an empty string ``""`` to include only root-level documents.  
   
     Example:  
     ``pathFilter=%2FItem`` (documents under `/Item`)  
     ``pathFilter=*`` (all documents)  
     ``pathFilter=`` (only root documents)  

Example
-------

.. code-block:: js
  
  [{ "Id": "Sword" }, { "Id": "Gold" }]
  ["Sword", "Gold"] // just raw Ids are also accepted
  
