Overview
==========

The ``Integer`` data type is a whole number data type that is limited to 64 bits. It is used to represent integers without a fractional component. It can be used in cases where you need to store a large range of positive or negative whole numbers, such as in-game currency or player levels.

Unlike the :doc:`Number  <number>` data type, integers do not have any precision caveats since they do not store decimal values. Therefore, they are suitable for calculations that require exact values.

C# Type
   ``System.SByte``, ``System.Int16``, ``System.Int32``, ``System.Int64``
Uniqueness
   May be checked for uniqueness.
Size
   32 or 64bit

Example
=======
.. code-block:: js

  0
  -1
  100