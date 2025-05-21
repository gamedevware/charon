Pick List
=========

``PickList`` is a data type used to define a list of pre-defined options for a property. It allows the user to select only one option from the given list. The options can be defined as a string, and the list can contain any number of options.

``PickList`` data type is commonly used to define properties such as gender, language, or country, where there are a limited number of options to choose from. It provides a convenient way to standardize the data, and also helps to prevent errors or inconsistencies in the data.

For example, in a game where the player can choose a character class, the ``PickList`` data type can be used to define the available options, such as "Warrior," "Mage," or "Rogue." This ensures that the player can only choose from the available options and helps to prevent invalid inputs.

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

  1 // internaly stored as integers
  "Apple" // string values also valid