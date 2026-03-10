Document Merge Logic
====================

When ``DATA IMPORT`` or ``DATA APPLYPATCH`` merges incoming (modified) data with the
existing (original) data, it follows a set of deterministic rules per property type.
Understanding these rules is essential for predicting the outcome of partial updates,
patch application, and ``SafeUpdate`` operations.

.. contents:: On this page
   :local:
   :depth: 2

----

Core Principle
--------------

Every merge operation takes two document trees — **original** (left) and **modified**
(right) — and produces a **merged** result. The fundamental rule is:

- If **modified** provides a value for a property → the merged result uses the modified value.
- If **modified** does not provide a value for a property → the merged result keeps the original value.
- Both absent → the property is omitted from the result.

The rule applies recursively: properties that are themselves documents are merged
property-by-property using the same rules, and collections are merged item-by-item
using the document's ``Id`` as the key.

.. note::
   "Modified does not provide a value" means the property key is absent from the incoming
   document. A property present in modified with an explicit ``null`` value is treated as
   an intentional deletion, not a missing value.

----

Import Mode
-----------

The merge behaviour is governed by the **import mode** passed to the operation. Two modes
affect merge in particular:

``createAndUpdate`` (default)
   Modified values always win. Items absent from the modified collection are treated as
   deleted. This is the mode used by ``DATA APPLYPATCH``.

``safeUpdate``
   A restricted mode that prevents deletions. Items absent from the modified collection
   are left unchanged. The ``Id`` field of a document is never overwritten regardless of
   what modified supplies.

Other modes (``create``, ``update``, ``replace``, ``delete``) control *which* documents
are eligible for merge, but once a document is selected, the merge rules below apply.

----

Property-Level Merge Rules
---------------------------

Scalar Properties
^^^^^^^^^^^^^^^^^

Applies to: ``Text``, ``Time``, ``Date``, ``Logical``, ``Reference``, ``Formula``,
``Number``, ``Integer``, ``PickList``, ``MultiPickList``.

If modified supplies a value, it overwrites the original unconditionally.
If modified does not supply a value, the original is kept.

**Special case — ``Id`` in SafeUpdate mode:**
The ``Id`` property is never overwritten when the import mode is ``safeUpdate``.
Even if modified provides an ``Id`` value, the original ``Id`` is preserved.
This prevents accidental re-identification of documents when patching subsets of fields.

LocalizedText Properties
^^^^^^^^^^^^^^^^^^^^^^^^^

``LocalizedText`` values are merged **per language** rather than replaced wholesale:

1. For each language configured in Project Settings:

   - If modified contains a value for that language → use the modified value.
   - If modified does not contain that language key → keep the original value for
     that language.

2. If modified cannot be interpreted as a ``LocalizedText`` at all → the result is
   ``null``.

3. If original cannot be interpreted as a ``LocalizedText`` (e.g. property was empty
   before) → the modified value is used as-is with no per-language merging.

**Translation notes** are merged separately:

- The **comment** field: modified wins if it has a comment; otherwise the original comment
  is kept.
- **Stale translation flags**: the union (OR) of both sets — a language that was stale in
  either original or modified remains stale. Stale flags are then automatically cleared for
  any language whose value was explicitly supplied by modified.

Inline Document Properties
^^^^^^^^^^^^^^^^^^^^^^^^^^

A property of type ``Document`` (an embedded sub-document) is merged recursively using
the same rules applied to top-level documents.

The four cases:

+----------------------+----------------------+------------------------------------------+
| Original             | Modified             | Result                                   |
+======================+======================+==========================================+
| absent / null        | document             | Merge(empty, modified) — see caveat      |
+----------------------+----------------------+------------------------------------------+
| document             | absent / null        | ``null`` (deleted), *or* original in     |
|                      |                      | ``safeUpdate``                           |
+----------------------+----------------------+------------------------------------------+
| document             | document             | Recursive merge, property by property    |
+----------------------+----------------------+------------------------------------------+
| absent / null        | absent / null        | Property omitted from result             |
+----------------------+----------------------+------------------------------------------+

Document Collections
^^^^^^^^^^^^^^^^^^^^

``DocumentCollection`` and ``ReferenceCollection`` properties are merged **by document
Id**. The set of Ids to iterate depends on the mode:

- **createAndUpdate** — iterates the **modified** Ids. Documents present in original but
  absent from modified are treated as deleted and dropped from the result.
- **safeUpdate** — iterates the **original** Ids. Documents present in original but absent
  from modified are left unchanged. Items in modified not in original are ignored.

Per-item resolution:

+------------------------+------------------------+---------------------------------------------+
| Original item          | Modified item          | Result                                      |
+========================+========================+=============================================+
| exists                 | absent (id not listed) | Kept unchanged                              |
+------------------------+------------------------+---------------------------------------------+
| absent                 | exists                 | Created (added to result)                   |
+------------------------+------------------------+---------------------------------------------+
| exists                 | ``null`` / not a doc   | Deleted (dropped), kept in ``safeUpdate``   |
+------------------------+------------------------+---------------------------------------------+
| exists                 | exists                 | ``DocumentCollection``: recursive merge     |
|                        |                        | ``ReferenceCollection``: modified wins      |
+------------------------+------------------------+---------------------------------------------+

For ``ReferenceCollection`` items (which store a reference object, not full data), when
both sides exist the modified reference object replaces the original without recursion —
there are no meaningful sub-properties to merge.

Null optional collections
"""""""""""""""""""""""""

If modified explicitly supplies ``null`` for an optional (non-required) collection property,
the result is ``null`` regardless of what original contained. In ``safeUpdate`` mode, an
empty modified collection means "no changes", not "clear the collection".

----

The Partial-Document Resurrection Caveat
-----------------------------------------

A subtle but important edge case arises when:

1. A document was **deleted** from the original (original is ``null`` or absent).
2. A patch was created that **adds or modifies** that document (modified contains a
   partial document — only the properties that changed).
3. ``DATA APPLYPATCH`` (``createAndUpdate`` mode) applies the patch.

In this case the merge calls ``Merge(empty, partialModified, schema)``.
Since ``empty`` provides no values, every property takes its value from ``partialModified``
where present — and is simply **omitted** where modified does not supply it.

The resulting document exists in the data, but **only contains the properties included in
the patch**. Required properties that were absent in the original document — and were not
listed in the patch — will be missing from the result.

**Example:**

Original ``Item/IronSword`` was deleted. A patch contains:

.. code-block:: json

   {
     "Collections": {
       "Item": {
         "IronSword": { "Id": "IronSword", "Damage": 20 }
       }
     }
   }

If the ``Item`` schema has a required ``Name`` field, the merged document will be:

.. code-block:: json

   { "Id": "IronSword", "Damage": 20 }

``Name`` is absent. Subsequent validation (``checkRequirements``) will report this as an
error.

**How to avoid it:**

- When generating a patch for a *new* document, include **all required fields** in the
  patch, not only the diff.
- When applying a patch that resurrects deleted documents, pass stricter
  ``--validationOptions`` to catch missing required fields immediately:

  .. code-block:: bash

     charon DATA APPLYPATCH \
         --dataBase target.json \
         --input changes.patch.json \
         --validationOptions repair checkRequirements checkReferences

- If the resurrection is intentional but the document is expected to be incomplete,
  use ``--validationOptions None`` and fix the document via a follow-up import.

----

Merge in Context
----------------

The merge logic is invoked by:

- **``DATA IMPORT``** — for every document that matches both the import input and the
  target data (matched by ``Id``). The mode is set by ``--mode``.
- **``DATA APPLYPATCH``** — always runs in ``createAndUpdate`` mode. The patch format
  uses ``null`` entries to express deletions, which interact directly with the merge rules
  described above.
- **``DATA UPDATE`` (single document)** — runs in ``createAndUpdate`` mode on a single
  document.

----

See also
--------

- :doc:`Patch and Diff Workflow <patch_diff>`
- :doc:`Importing and Exporting Data <import_export>`
- :doc:`Validation <validation>`
- :doc:`DATA IMPORT Command <commands/data_import>`
- :doc:`DATA APPLYPATCH Command <commands/data_apply_patch>`