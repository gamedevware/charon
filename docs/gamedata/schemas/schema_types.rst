Schema Types
============

Every :doc:`Schema <schema>` has a **Type** field that controls how its documents are created, stored, and navigated within the data model. Choosing the right type is fundamental to a well-structured data model.

.. contents:: On this page
   :local:
   :depth: 2

----

Normal
------

**Normal** is the default type. Documents of a Normal schema can be:

- Created as standalone root-level entries, visible in the left navigation menu.
- Embedded inside other documents as :doc:`Document <../datatypes/all/document>` or
  :doc:`DocumentCollection <../datatypes/all/document_collection>` property values.
- Referenced from other documents via :doc:`Reference <../datatypes/all/reference>` or
  :doc:`ReferenceCollection <../datatypes/all/reference_collection>` properties.

Use **Normal** for any entity that has an independent identity and may need to be listed,
searched, and referenced across the project — items, characters, quests, abilities, etc.

.. code-block:: json

   { "Id": "Sword", "Name": "Iron Sword", "Damage": 15 }

----

Component
---------

**Component** schemas model sub-objects that are *always embedded* inside another document
and never exist as standalone root-level entries.

- Do **not** appear in the left navigation menu.
- Can only be used as a value for a ``Document`` or ``DocumentCollection`` property.
- Useful for reusable sub-structures with no independent identity.

Typical examples: a ``Stat`` block inside a ``Character``, a ``DropEntry`` inside a ``LootTable``,
a ``BonusEffect`` inside a ``Weapon``.

.. code-block:: json

   {
     "Id": "Hero_Arbalest",
     "BaseStats": { "HP": 100, "Speed": 4, "Damage": 12 }
   }

----

Settings
--------

**Settings** is a singleton type. Exactly **one** document of this schema may exist in the
root-level collection. It cannot be embedded inside other documents.

- Created automatically on first access and cannot be deleted.
- Appears in the navigation menu as a direct link (no list page).
- Suited for project-wide configuration: ``GameSettings``, ``BalanceConfig``, ``GlobalRules``.

.. code-block:: json

   { "Id": "settings", "DifficultyMultiplier": 1.5, "MaxPlayersPerRoom": 4 }

----

Union (Tagged Union)
--------------------

A **Union** schema — also known as a Discriminated Union, Sum Type, or ``$oneOf`` — lets a
single collection slot or property hold documents of **different shapes** in a type-safe way.

A Union schema does not define properties itself. Instead it declares a set of **variant
schemas** (any Normal or Component schema).

Why Union instead of the other inheritance patterns
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

See :doc:`Implementing Inheritance <../inheritance>` for a full comparison, but in short:

+----------------+-------------------------------+---------------------------+-----------------------+
| Pattern        | Storage cost                  | UI                        | Schema refactoring    |
+================+===============================+===========================+=======================+
| Composition    | Extra ``Item`` schema level   | Standard form             | Move fields to Item   |
+----------------+-------------------------------+---------------------------+-----------------------+
| Merging        | All fields on every doc       | All fields always visible | Edit one big schema   |
+----------------+-------------------------------+---------------------------+-----------------------+
| Aggregation    | Nullable ref per variant      | Multiple nullable refs    | Add a new ref field   |
+----------------+-------------------------------+---------------------------+-----------------------+
| **Union**      | Only active variant's fields  | Type picker, sparse form  | Add a new variant     |
+----------------+-------------------------------+---------------------------+-----------------------+

Key properties of Union:

- **Sparse storage** — unset variant fields are not written to disk; only the active variant's
  properties are stored.
- **First-class UI** — when editing a Union field the editor shows a type-selector dropdown
  and only renders the form for the chosen variant.

Defining a Union schema
^^^^^^^^^^^^^^^^^^^^^^^^

1. Create the variant schemas (Normal or Component) with their own properties.
2. Create a new schema, set **Type** to **Union**, and list the variant schemas in **Variants**.
3. Use the Union schema as the ``ReferenceType`` of a ``Reference``, ``ReferenceCollection``,
   ``Document``, or ``DocumentCollection`` property on another schema.

Storage format
^^^^^^^^^^^^^^

Unlike many serialisation libraries that use a ``"$type"`` or ``"@class"`` string field
to tag the variant, Charon uses **property-key presence** as the discriminator.
Each union slot is serialised as a **single-key wrapper object** whose key is the
variant schema name and whose value is the document body:

.. code-block:: json

   { "Weapon": { "Id": "Sword01", "Damage": 15, "WeaponType": "Melee" } }
   { "Armor":  { "Id": "Plate01", "Defense": 8                        } }
   { "Shield": { "Id": "Shield01","BlockChance": 0.25                 }, /* Weapon: null, "Armor": null, are ommited */ }

The variant is identified by whichever key is present in the wrapper — ``"Weapon"``,
``"Armor"``, ``"Shield"``, etc. There is no ``"$type"`` string anywhere in the stored data; the schema name *is* the discriminator.

A full collection of union documents therefore looks like:

.. code-block:: json

   {
     "Collections": {
       "ShopItem": [
         { "Weapon": { "Id": "Sword01", "Damage": 15, "WeaponType": "Melee" } },
         { "Armor":  { "Id": "Plate01", "Defense": 8                        } },
         { "Shield": { "Id": "Shield01","BlockChance": 0.25                 } }
       ]
     }
   }

Generated source code
^^^^^^^^^^^^^^^^^^^^^

Union schemas generate a container type in the target language. Each variant is a
nullable field inside that container; exactly one field is non-null at runtime.

Malformed Union values
^^^^^^^^^^^^^^^^^^^^^^

A Union value is **well-formed** when the wrapper object contains exactly two keys:
``Id`` and exactly one variant key. Two malformed states can occur — usually as a result
of a bulk import, a hand-crafted JSON payload, or a patch applied to a Union field without
accounting for the wrapper format.

**Empty union** — the ``Id`` is present but no variant key is set:

.. code-block:: json

   { "Id": "item_01" }

**Conflicting union** — two or more variant keys are set simultaneously:

.. code-block:: json

   { "Id": "item_01", "Weapon": { "Damage": 15 }, "Potion": { "HP": 5 } }

Both states are detected by the ``checkConstraints`` validation option (enabled by default)
and reported as separate error codes in the validation report:

- Empty union → ``emptyUnion`` error
- Conflicting union → ``conflictingUnionOptions`` error, listing the conflicting variant names

Repairing malformed unions
~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``resolveConflictingUnions`` repair option fixes both cases automatically. It can be
used with :doc:`DATA VALIDATE <../../advanced/commands/data_validate>` or
:doc:`DATA IMPORT <../../advanced/commands/data_import>`:

.. code-block:: bash

   # repair in-place
   charon DATA VALIDATE --dataBase "gamedata.json" \
       --validationOptions repair resolveConflictingUnions

   # repair while importing
   charon DATA IMPORT --dataBase "gamedata.json" --input "./patch.json" \
       --validationOptions repair resolveConflictingUnions

Repair behaviour:

+---------------------+----------------------------------------------------------+
| Malformed state     | What the repair does                                     |
+=====================+==========================================================+
| Empty union         | Erases the union value entirely (sets it to ``null``).   |
+---------------------+----------------------------------------------------------+
| Conflicting union   | Keeps the **last** variant in schema-property order;     |
|                     | all other variant values are discarded.                  |
+---------------------+----------------------------------------------------------+

.. note::
   The "last variant in schema-property order" is determined by the order of variant
   schemas as listed in the Union schema definition, not by the order of keys in the
   stored JSON. If the outcome of the automatic repair is not acceptable, correct the
   source data manually before importing.

.. note::
   The ``Union`` type is the recommended approach when you need heterogeneous collections
   and want first-class editor support. Prefer it over Aggregation for new designs.

See also
--------

- :doc:`Schema <schema>`
- :doc:`Implementing Inheritance <../inheritance>`
- :doc:`Specification <specification>`
- :doc:`Document <../datatypes/all/document>`
- :doc:`Reference <../datatypes/all/reference>`