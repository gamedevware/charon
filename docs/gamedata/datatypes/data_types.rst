Overview
==========
Selecting the proper data type is important in order to ensure that data is correctly and efficiently stored and used in the game. Each data type has its own specific purpose and characteristics, which should be considered when choosing the appropriate type for a given property.

For example, if a property needs to store a text value, the `Text <text.rst>`_ data type would be appropriate. If the text needs to be translated into multiple languages, the `LocalizedText <localized_text.rst>`_ data type would be the best choice.

Similarly, if a property needs to store a numeric value, the `Number  <number.rst>`_ or `Integer <integer.rst>`_ data types would be appropriate depending on the type of number being stored.

The `PickList <pick_list.rst>`_ and `MultiPickList <multi_pick_list.rst>`_ data types are useful for properties that have a limited set of values, such as a list of game items or character classes.

The `Document <document.rst>`_ and `DocumentCollection <document_collection.rst>`_ data types are useful for storing complex data that may contain multiple fields or properties.

Ultimately, selecting the proper data type ensures that game data is properly structured, and helps to prevent errors and inconsistencies in the game.

Data Types
==========

+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| Data Type                                         | Description                                                     | Example                                          |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Text <text.rst>`_                                | A single line of text.                                          | "Hello, world!"                                  |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `LocalizedText <localized_text.rst>`_             | A single line of localized text.                                | {"en-US": "Hello", "fr-FR": "Bonjour"}           |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Logical <logical.rst>`_                          | A true/false value.                                             | True                                             |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Time <time.rst>`_                                | A time span.                                                    | "1.00:00:00"                                     |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Date <date.rst>`_                                | A specific date.                                                | "2017-12-27T00:00:00.000Z"                       |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Number  <number.rst>`_                           | A decimal number.                                               | 3.14                                             |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Integer <integer.rst>`_                          | A whole number.                                                 | 42                                               |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `PickList <pick_list.rst>`_                       | A list of pre-defined values.                                   | "Red"                                            |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `MultiPickList <multi_pick_list.rst>`_            | A list of pre-defined values that can have multiple selections. | "Apple, Banana, Cherry"                          |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Document <document.rst>`_                        | An embedded document.                                           | { "Id": "Sword", "Name": "Rusty Sword" }         |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `DocumentCollection <document_collection.rst>`_   | A collection of embedded documents.                             | [{ "Id": "Sword", "Name": "Rusty Sword" }]       |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Reference <reference.rst>`_                      | A reference to another document.                                | { "Id": "Sword"}                                 |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `ReferenceCollection <reference_collection.rst>`_ | A collection of references to other documents.                  | [{ "Id": "Sword" }]                              |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| `Formula <formula.rst>`_                          | A C# expression used to calculate something                     | "target.HP < 100"                                |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
