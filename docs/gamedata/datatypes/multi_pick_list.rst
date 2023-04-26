Overview
==========

The ``MultiPickList`` data type is used when you want to allow the selection of multiple values from a predefined list of options. It is similar to the `PickList <pick_list.rst>`_ data type, but it allows for multiple selections.

``MultiPickList`` is particularly useful when you want to replace several `Logical <logical.rst>`_ properties that have a related meaning with a single property. For example, instead of having three separate properties to indicate if a item can be broken, disassembled, or sold, you can use a MultiPickList with the options "CanBeBreaken," "CanBeDisassembled," and "CanBeSold."

C# Type
  ``enum`` based on System.SByte, System.Int16, System.Int32, System.Int64
Uniqueness
   May be checked for uniqueness.
Size
   May be set between 1-8 bytes. Maximum size is 8.

Example
=======
.. code-block:: js

  1 // internaly stored as integers
  "Apple" // string values also valid