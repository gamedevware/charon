Multi-Pick List
===============

The ``MultiPickList`` data type allows a property to represent multiple values selected from a predefined list of options. It is designed for cases where multiple attributes, traits, or capabilities can be applied to a single entity simultaneously.  
Unlike :doc:`PickList <pick_list>`, which limits the property to a single choice, ``MultiPickList`` enables the combination of several boolean-like flags into a single compact representation.  
In the UI, MultiPickList is typically presented as a dropdown menu, allowing users to select or deselect multiple options independently.  

Storage on Disk
   On disk, the ``MultiPickList`` is stored as an integer bitmask. Each option is assigned a specific bit position. When multiple options are selected, their bits are combined using bitwise OR operations. The number of options is limited by the bit width of the storage format—commonly 32 or 64 options for a 32-bit or 64-bit integer, respectively.  

Example
   An item in an RPG might be marked as equippable, sellable, and destructible using a single MultiPickList field instead of three separate boolean flags.

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
   Multi-Pick Lists can be marked as unique.
Size
   32 or 64bit
Specification 
   Multi-Pick Lists support the following specification parameters:
   
   - ``typeName`` — Custom type name for the generated class. If omitted, a name is derived from the containing schema and property.  
   
     Example: ``typeName=MyEnum``

Example
-------
.. code-block:: js

  1 // internaly stored as integers
  "Apple" // string values also valid