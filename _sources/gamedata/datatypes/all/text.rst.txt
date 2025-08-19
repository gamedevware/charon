Text
====

The ``Text`` data type is used to store simple text values in game data. Unlike the :doc:`LocalizedText <localized_text>` data type, ``Text`` does not have support for multiple translations of the same text. Instead, it allows for the storage of any UTF symbol in a single language. This data type is useful for fields that do not require localization, such as character names, item descriptions, or game lore.

Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | System.String                                                   |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | string                                                          |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | FString                                                         |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | String                                                          |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   Text can be marked as unique (case sensitive for uniqueness purposes).
Size
   May be limited in number of characters. 0 - no limit.

Example
-------

.. code-block:: js

  "Hello world!"
  
Sub-Types
---------
 - :doc:`Asset Path <../sub/asset>`
 - :doc:`Asset Path Collection <../sub/asset_collection>`
 - :doc:`Vector 2/3/4 <../sub/vector>`
 - :doc:`Integer Vector 2/3/4<../sub/vector_int>`
 - :doc:`Rectangle<../sub/rectangle>`
 - :doc:`Integer Rectangle<../sub/rectangle_int>`
 - :doc:`Tags<../sub/tags>`