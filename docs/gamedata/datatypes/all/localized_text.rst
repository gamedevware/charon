Localized Text
==============

The ``LocalizedText`` data type is used to store text that needs to be displayed in multiple languages. Unlike the :doc:`Text <text>` data type, the LocalizedText data type allows the storage of the same text in multiple languages. It supports the whole range of UTF symbols, just like the :doc:`Text <text>` data type. The ``LocalizedText`` data type is essential for games that require localization support, and it makes it easy for game developers to manage text that needs to be displayed in multiple languages.

Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | LocalizedText or System.String                                  |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | LocalizedText or string                                         |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | FLocalizedText or FText                                         |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | LocalizedText or String                                         |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   May NOT be checked for uniqueness.
Size
   May be limited in number of characters. 0 - no limit.
   
Example
-------

.. code-block:: js
  
  {"en-US": "Hello", "fr-FR": "Bonjour"}
