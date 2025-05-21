Reference
=========

The ``Reference`` data type enables the creation of non-embedded relationships between documents. A reference acts as a pointer to another document by using that document's ``Id`` as a key. This approach facilitates linking between related documents without the need to duplicate or embed data.

When using a ``Reference``, the target documents are not stored within the parent document but are instead referenced externally. This is particularly beneficial when working with large or complex data sets, where referencing is more efficient and maintains separation of concerns. It also promotes data integrity by ensuring that only valid document references are maintained.

For example, in a game scenario, a **Chest** with a loot table might hold a reference to an **Item** document, rather than embedding the entire **Item** directly within the **Chest**. This separation allows independent management of the loot logic and item definitions while preserving their relationships.

Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | DocumentReference{T} or T                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | DocumentReference{T} or T                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | FGameDataDocumentReference                                      |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | DocumentReference{T} or T                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   Reference cannot be marked as unique.
Specification 
   References support the following specification parameter:
   
   - ``displayTextTemplate`` — Defines a template string for how the referenced value is displayed in the UI.  
   
     Example:  
     ``displayTextTemplate=Item%3A+%7BName%7D%2C+Count%3A+%7BCount%7D``  
     (renders as: `Item: {Name}, Count: {Count}`)

Example
-------

.. code-block:: js
  
  { "Id": "Sword" }
  "Sword" // just raw Id is also accepted
  
