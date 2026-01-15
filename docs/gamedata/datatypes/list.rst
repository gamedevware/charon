Data Types
==========

.. toctree::
   :caption: All Data Types
   :titlesonly:
   :glob:
   :hidden:

   all/*
   sub/*

Choosing the appropriate data type is essential for ensuring that game data is accurately structured, efficiently stored, and correctly interpreted by both the editor and runtime systems. Each data type serves a specific purpose and is designed to represent particular kinds of values or relationships.

For instance, use the :doc:`Text <text>` data type for simple string values, or the :doc:`LocalizedText <localized_text>` type when the same text must support multiple languages. For numeric data, :doc:`Number <number>` is suited for decimal values, while :doc:`Integer <integer>` should be used for whole numbers.

When a property should be selected from a defined set of options, :doc:`PickList <pick_list>` and :doc:`MultiPickList <multi_pick_list>` are recommended for single or multiple selections, respectively. For more complex structures, use :doc:`Document <document>` to define an embedded object, or :doc:`DocumentCollection <document_collection>` to represent a list of such objects.

By selecting data types according to their intended purpose, developers can ensure better validation, clearer data organization, and more predictable behavior across tools and runtime systems.


Data Types
----------

+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| Data Type                                             | Description                                                     | Example                                          |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Text <all/text>`                                | A line of text.                                                 | "Hello, world!"                                  |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`LocalizedText <all/localized_text>`             | A localized text for multiple languages.                        | {"en-US": "Hello", "fr-FR": "Bonjour"}           |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Logical <all/logical>`                          | A true/false value.                                             | true                                             |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Time <all/time>`                                | A time duration (days, hours, etc.).                            | "1.00:00:00"                                     |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Date <all/date>`                                | A calendar date and time.                                       | "2017-12-27T00:00:00.000Z"                       |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Number <all/number>`                            | A decimal number.                                               | 3.14                                             |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Integer <all/integer>`                          | A whole number.                                                 | 42                                               |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`PickList <all/pick_list>`                       | A single value from a predefined list.                          | "Red"                                            |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`MultiPickList <all/multi_pick_list>`            | Multiple values from a predefined list.                         | "Apple, Banana, Cherry"                          |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Document <all/document>`                        | An embedded structured object.                                  | { "Id": "Sword", "Name": "Rusty Sword" }         |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`DocumentCollection <all/document_collection>`   | A list of embedded structured objects.                          | [{ "Id": "Sword", "Name": "Rusty Sword" }]       |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Reference <all/reference>`                      | A pointer to another document by ID.                            | { "Id": "Sword" }                                |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`ReferenceCollection <all/reference_collection>` | A list of pointers to other documents.                          | [{ "Id": "Sword" }]                              |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+
| :doc:`Formula <all/formula>`                          | A C# expression evaluated at runtime.                           | "target.HP < 100"                                |
+-------------------------------------------------------+-----------------------------------------------------------------+--------------------------------------------------+

Composite Types
=========

+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| Composite Type                                        | Base Type | Description                                                     |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| :doc:`Asset Path <sub/asset>`                         | Text      | A relative path to a single game asset.                         |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| :doc:`Vector 2/3/4 <sub/vector>`                      | Text      | A group of 2, 3, or 4 decimal values (e.g., position or scale). |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| :doc:`Integer Vector 2/3/4 <sub/vector_int>`          | Text      | A group of 2, 3, or 4 whole numbers.                            |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| :doc:`Rectangle <sub/rectangle>`                      | Text      | A rectangle with floating-point position and size.              |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| :doc:`Integer Rectangle <sub/rectangle_int>`          | Text      | A rectangle with integer position and size.                     |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+
| :doc:`Tags <sub/tags>`                                | Text      | A reusable set of tags shared across documents.                 |
+-------------------------------------------------------+-----------+-----------------------------------------------------------------+

Use Cases and Guidance
----------------------

- Use **Text** and **LocalizedText** for titles, descriptions, and UI content.
- Choose **Integer** or **Number** for quantities, rates, and stats.
- Use **Document** or **Reference** to include structured data or link to another entity.
- Use **PickList** or **MultiPickList** when the value should be selected from a known set.
- Use **Asset Path** or **Asset Path Collection** when referencing assets like textures, sounds, or prefabs by path.
- Use **Formula** to define runtime-calculated values, like damage formulas or dynamic prices.
- Use **Tags** when multiple documents share common descriptors (e.g., "fire", "enemy", "magic").
