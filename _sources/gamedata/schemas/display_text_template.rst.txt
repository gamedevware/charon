Display Text Template
=====================

When a document needs to be shown or referenced in the UI, a text representation is required. By default, Charon will use one of the following properties, in order of precedence: ``DisplayName``, ``Name``, ``Title``, or ``Id``. This fallback behavior can often result in uninformative or unclear document labels.

For example, consider the following document:

.. code-block:: json

  {
    "Id": 1,
    "Description": "Bring 40 wolf skins",
    "Type": "RepeatableQuest",
    "Tasks": [ /* ... */ ]
  }

By default, this document would be displayed in UI lists simply as ``"1"``. This can be improved by defining a custom **Display Name Template** for the :doc:`Schema <schema>`.

For instance, the template:

``Quest #{Id}: {Type} - {Description}``

would render the document's label as:

``Quest #1: RepeatableQuest - Bring 40 wolf skins``

Template Syntax
---------------

The display name template is a string that may include *replaceable expressions* enclosed in curly braces (``{}``). These expressions support a subset of C-style syntax and can reference any top-level or nested property of the document.

Property Access
^^^^^^^^^^^^^^^

- Top-level properties can be accessed directly by name.
- Nested properties in embedded documents can be accessed using dot notation, e.g., ``Item.Name``.

Supported Data Types
^^^^^^^^^^^^^^^^^^^^

+------------------------+------------------------+
| Type                   | Example                |
+========================+========================+
| String                 | ``"a string"``         |
+------------------------+------------------------+
| Number                 | ``1`` or ``3.14``      |
+------------------------+------------------------+
| Boolean                | ``true`` or ``true``   |
+------------------------+------------------------+
| null                   | ``null``               |
+------------------------+------------------------+


Unary Operators
^^^^^^^^^^^^^^^

+------------------------+------------------------+
| Operator               | Example                |
+========================+========================+
| Logical NOT            | ``!CanWalk``           |
+------------------------+------------------------+
| Bitwise Complement     | ``~ResistanceTypes``   |
+------------------------+------------------------+
| Negation               | ``-Damage``            |
+------------------------+------------------------+

Binary Operators
^^^^^^^^^^^^^^^^

The following binary expressions are supported:

+-----------------------------+----------------------------------------------+
| Operator                    | Example                                      |
+=============================+==============================================+
| Subtract                    | ``TotalPrice - BasePrice``                   |
+-----------------------------+----------------------------------------------+
| Add                         | ``BaseDamage + BonusDamage``                 |
+-----------------------------+----------------------------------------------+
| Concatenate                 | ``"Quest #" + Id``                           |
+-----------------------------+----------------------------------------------+
| Division                    | ``CriticalChance / CurseDebuff``             |
+-----------------------------+----------------------------------------------+
| Multiplication              | ``DropRate * 100.0``                         |
+-----------------------------+----------------------------------------------+
| Power                       | ``Damage ** CriticalChance``                 |
+-----------------------------+----------------------------------------------+
| Modulo                      | ``Slots % SlotPerPage``                      |
+-----------------------------+----------------------------------------------+
| Bitwise AND                 | ``DamageFlags & AdditionalDamageFlags``      |
+-----------------------------+----------------------------------------------+
| Bitwise OR                  | ``DamageTypes | ResistanceTypes``            |
+-----------------------------+----------------------------------------------+
| Bitwise XOR                 | ``ResistanceTypes ^ HealingTypes``           |
+-----------------------------+----------------------------------------------+
| Bitwise Left Shift          | ``Flags << 1``                               |
+-----------------------------+----------------------------------------------+
| Bitwise Right Shift         | ``Flags >> 1``                               |
+-----------------------------+----------------------------------------------+
| Logical AND (short-circuit) | ``CanWalk && CanRun``                        |
+-----------------------------+----------------------------------------------+
| Logical OR (short-circuit)  | ``HasHead || CanBeHeadshoted``               |
+-----------------------------+----------------------------------------------+
| Greater Than                | ``Count > MaxCount``                         |
+-----------------------------+----------------------------------------------+
| Greater Than or Equal       | ``Count >= MaxCount``                        |
+-----------------------------+----------------------------------------------+
| Less Than                   | ``HP < MaxHP``                               |
+-----------------------------+----------------------------------------------+
| Less Than or Equal          | ``HP <= MaxHP``                              |
+-----------------------------+----------------------------------------------+
| Equal To                    | ``Type == "RepeatableQuest"``                |
+-----------------------------+----------------------------------------------+
| Not Equal To                | ``Description != null``                      |
+-----------------------------+----------------------------------------------+
| Coalesce                    | ``Nickname ?? Name``                         |
+-----------------------------+----------------------------------------------+


Ternary Operator
^^^^^^^^^^^^^^^^

Ternary expressions are supported using the standard syntax:

.. code-block:: text

  {Damage >= 0 ? "Total Damage" : "Total Heal"}: {Damage}

This will result in either "Total Damage: X" or "Total Heal: X", depending on the value of ``Damage``.

Operator Precedence
^^^^^^^^^^^^^^^^^^^^^

You can control expression evaluation order using parentheses. For example:

.. code-block:: text

  Max Damage: {BaseDamage * (BaseCriticalChance + BonusCriticalChance)}

Boolean Coercion
^^^^^^^^^^^^^^^^

Many types can be implicitly coerced to a Boolean value:

- **Numeric values** are considered ``true`` if they are not equal to 0.
- **Documents**, **References**, and **Formulas** are considered ``true`` if they are not null.
- **Collections** (Document or Reference), **Text**, and **Localized Text** are ``true`` if they are not empty.

Other types must be explicitly compared to a value to be evaluated as Boolean. These coercion rules apply to ternary expressions and unary logical negation (`!`).

.. code-block:: text

  Has Items: {Items ? "Yes" : "No"}

Format Specifiers
^^^^^^^^^^^^^^^^^

Template expressions can include format specifiers, similar to C#'s formatting syntax. Add a colon and format string at the end of the substitution expression:

.. code-block:: text

  Resist Chance: {ResistChance * 100.0 :F2}

This limits the precision to two decimal places.

**Supported format specifiers:**

- ``F``: Fixed-point (decimal precision), e.g., ``F2`` for two decimal places.
- ``X`` / ``x``: Uppercase / lowercase hexadecimal (integers only), e.g., ``X16`` for hexadecimal string padded with zeroes to length of 16 characters.
- ``B``: Binary representation (integers only), e.g., ``B32`` for binary string padded with zeroes to length of 32 characters.

Collection Accessors
^^^^^^^^^^^^^^^^^^^^

Collections can be accessed by index using square brackets. If the index is out of bounds, the result is ``null``.

.. code-block:: text

  First Item: {Items[0]}

The number of items in a collection can be accessed using the ``.Count`` property:

.. code-block:: text

  Item Count: {Items.Count}

To create a joined string from all items in a collection, use the ``Join(separator: string)`` method:

.. code-block:: text

  Items: {Items.Join(" and ")}

This would produce output like:

``Items: Sword and Shield and Armor``

String Manipulation Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^

String expressions support several methods:

- ``Trim()`` — Removes leading and trailing whitespace.
- ``Substring(start: int, count: int)`` — Extracts a substring from a given position.
- ``ToString()`` — Converts any non-null value to its string representation.

String concatenation is done using the ``+`` operator:

.. code-block:: text

  Damage: {Damage + " [" + DamageType + "]"}

Result:

``Damage: 100 [Fire]``


See also
--------

- :doc:`Schema <schema>`
- :doc:`Property <../properties/property>`
- :doc:`Id Property <../properties/id_property>`
- :doc:`Shared Property <../properties/shared_property>`
- :doc:`All Data Types <../datatypes/list>`
- :doc:`Creating Document Type (Schema) <../creating_schema>`