Overview
==========

The ``Text`` data type is used to store simple text values in game data. Unlike the `LocalizedText <localized_text.rst>`_ data type, ``Text`` does not have support for multiple translations of the same text. Instead, it allows for the storage of any UTF symbol in a single language. This data type is useful for fields that do not require localization, such as character names, item descriptions, or game lore.

C# Type
   ``System.String``
Uniqueness
   May be checked for uniqueness (case sensitive for uniqueness purposes).
Size
   May be limited in number of characters. 0 - no limit.

Example
=======
.. code-block:: js

  "Hello world!"