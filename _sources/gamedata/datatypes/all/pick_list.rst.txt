Pick List
=========

The ``PickList`` data type defines a property that can take one value from a predefined set of options. It is best suited for fields where only a single choice is valid at any given time. This ensures consistency and restricts inputs to known, valid values.  
This type is commonly used for categorical selections such as character class, item rarity, or region. By standardizing the input, PickList helps reduce errors and supports better validation and filtering within game systems.  
In user interfaces, a ``PickList`` is typically presented as a dropdown menu, allowing users to choose only one option from the list.  

Storage on Disk
   On disk, ``PickList`` values are stored as integer. This value correspond directly to one of the predefined options.  

Example
   In a character creator, the player might choose "Mage" as their class from a list of available options like Warrior, Mage, or Rogue.

Source Code Type
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | Language                                              | Type                                                                     |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | C#                                                    | ``enum``                                                                 |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | TypeScript                                            | ``enum``                                                                 |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | ``UENUM``                                                                |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
   | Haxe                                                  | ``abstract``                                                             |
   +-------------------------------------------------------+--------------------------------------------------------------------------+
Uniqueness
   Pick Lists can be marked as unique.
Size
   32 or 64bit
Specification 
   Pick Lists support the following specification parameters:
   
   - ``typeName`` — Custom type name for the generated class. If omitted, a name is derived from the containing schema and property.  
   
     Example: ``typeName=MyEnum``

Example
-------
.. code-block:: js

  1 // on-disk stored as integers
  "Apple" // string values also valid