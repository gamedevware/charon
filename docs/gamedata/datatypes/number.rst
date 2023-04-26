Overview
==========

The ``Number`` data type is used to represent decimal numbers. It conforms to the `IEEE 754 <https://en.wikipedia.org/wiki/IEEE_754>`_ floating-point standard and can represent both positive and negative numbers, as well as zero. However, due to the limitations of the floating-point representation, precision may be lost when performing certain arithmetic operations. Therefore, it is recommended to use the `Integer <integer.rst>`_ data type for financial calculations and other scenarios that require high precision.

Some use cases for the ``Number`` data type include representing quantities, such as the count of an items or the amount of gold reward in the chest, or representing percentages, such as the chance of an event occurring. It can also be used to represent measurements, such as the height of a character or the length of a weapon.

When working with ``Numbers`` in game data, it is important to ensure that the precision is appropriate for the use case. Additionally, it may be necessary to round numbers to a certain number of decimal places to avoid displaying unnecessarily precise values to players.

C# Type
   ``System.Single`` or ``System.Double``
Uniqueness
   May be checked for uniqueness.
Size
   May be set between 1-8 bytes. Maximum size is 8.

Example
=======
.. code-block:: js

  3.14
  0.21
  -3.14
