All Data Types
==============
Selecting the proper data type is important in order to ensure that data is correctly and efficiently stored and used in the game. Each data type has its own specific purpose and characteristics, which should be considered when choosing the appropriate type for a given property.

For example, if a property needs to store a text value, the :doc:`Text <text>` data type would be appropriate. If the text needs to be translated into multiple languages, the :doc:`LocalizedText <localized_text>` data type would be the best choice.

Similarly, if a property needs to store a numeric value, the :doc:`Number  <number>` or :doc:`Integer <integer>` data types would be appropriate depending on the type of number being stored.

The :doc:`PickList <pick_list>` and :doc:`MultiPickList <multi_pick_list>` data types are useful for properties that have a limited set of values, such as a list of game items or character classes.

The :doc:`Document <document>` and :doc:`DocumentCollection <document_collection>` data types are useful for storing complex data that may contain multiple fields or properties.

Ultimately, selecting the proper data type ensures that game data is properly structured, and helps to prevent errors and inconsistencies in the game.

Table with example
------------------

+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| Data Type                                         | Description                                                     | Example                                          |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Text <text>`                                | A single line of text.                                          | "Hello, world!"                                  |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`LocalizedText <localized_text>`             | A single line of localized text.                                | {"en-US": "Hello", "fr-FR": "Bonjour"}           |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Logical <logical>`                          | A true/false value.                                             | True                                             |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Time <time>`                                | A time span.                                                    | "1.00:00:00"                                     |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Date <date>`                                | A specific date.                                                | "2017-12-27T00:00:00.000Z"                       |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Number  <number>`                           | A decimal number.                                               | 3.14                                             |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Integer <integer>`                          | A whole number.                                                 | 42                                               |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`PickList <pick_list>`                       | A list of pre-defined values.                                   | "Red"                                            |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`MultiPickList <multi_pick_list>`            | A list of pre-defined values that can have multiple selections. | "Apple, Banana, Cherry"                          |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Document <document>`                        | An embedded document.                                           | { "Id": "Sword", "Name": "Rusty Sword" }         |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`DocumentCollection <document_collection>`   | A collection of embedded documents.                             | [{ "Id": "Sword", "Name": "Rusty Sword" }]       |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Reference <reference>`                      | A reference to another document.                                | { "Id": "Sword"}                                 |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`ReferenceCollection <reference_collection>` | A collection of references to other documents.                  | [{ "Id": "Sword" }]                              |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Formula <formula>`                          | A C# expression used to calculate something                     | "target.HP < 100"                                |
+---------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
