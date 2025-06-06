Id Property
===========

Each schema includes an ``Id`` property that defines the unique identifier for a document.  
This property is always named ``Id`` and must satisfy the following constraints:

- Must be unique.
- Required and must be non-empty (for ``Text`` data type).
- Must use a data type with a stable text representation and comparison support, such as:

  - Time
  - Date
  - Number
  - Integer
  - Text
  - MultiPickList
  - PickList

Generated Id
-------------

Schemas can specify that the ``Id`` property should be automatically generated.  
Based on the selected ``Id Generator`` type, an appropriate ``Id`` property will be added to the schema.

Supported Id Generators:

- ObjectId
- Guid
- Sequence
- GlobalSequence

Generated ObjectId
^^^^^^^^^^^^^^^^^^

A BSON ObjectId is a 96-bit unique identifier derived from the machine name, process ID, and timestamp.  
It is always increasing and well-suited for sorting documents by creation time.

Id property details:

- **Data Type:** Text  
- **Size:** 24 characters  
- **Requirement:** Not Empty  
- **Example:** "049bc0604c363a980b000088"

Generated Guid
^^^^^^^^^^^^^^

A GUID (Globally Unique Identifier) is a 128-bit identifier typically represented as a 32-character hexadecimal string.  
It ensures global uniqueness across systems.

Id property details:

- **Data Type:** Text  
- **Size:** 32 characters  
- **Requirement:** Not Empty  
- **Example:** "6fe4202b1b9c4565b439980138524112"

Generated Sequence
^^^^^^^^^^^^^^^^^^

A sequential numeric identifier unique to each document within a specific schema.  
Documents from different schemas may share the same numeric ``Id``.  
For globally unique numeric IDs, use ``GlobalSequence``.

Id property details:

- **Data Type:** Integer  
- **Size:** 32-bit  
- **Requirement:** Not Null  
- **Example:** 1

Generated Global Sequence
^^^^^^^^^^^^^^^^^^^^^^^^^^

A globally unique numeric identifier across all schemas and documents in the project.

Id property details:

- **Data Type:** Integer  
- **Size:** 32-bit  
- **Requirement:** Not Null  
- **Example:** 69

Non-Generated Id
----------------

Schemas may also use a manually defined ``Id`` property by selecting the ``None`` option for the ``Id Generator``.  
You can define the ``Id`` property using any supported data type listed above.

All Id constraints will be automatically validated when saving the schema.  
You can change a schema's ``Id Generator`` to ``None`` at any time, but you cannot switch back to a generator once this change is made.

Id Placeholder
--------------

If you want to assign a temporary value to the ID of a document being created—for example, for internal reference—you can use a placeholder string such as ``_ID_XXX_ANY_UNIQUE_TEXT_HERE_XXX``.  
This placeholder will be automatically replaced with the actual generated ID during saving or importing.

Before save:

.. code-block:: json

  {
    "Id": "_ID_ITEM_123",
    "Name": "My New Item",
    "ItemReference": {
      "Id": "_ID_ITEM_123",  // self-reference
      "DisplayName": "My New Item"
    }
  }

After save:

.. code-block:: json

  {
    "Id": 42,
    "Name": "My New Item",
    "ItemReference": {
      "Id": 42,
      "DisplayName": "My New Item"
    }
  }

  
See also
--------

- :doc:`Schema <../schemas/schema>`
- :doc:`Property <property>`
- :doc:`Shared Property <shared_property>`
- :doc:`All Data Types <../datatypes/list>`
- :doc:`Creating Document Type (Schema) <../creating_schema>`
