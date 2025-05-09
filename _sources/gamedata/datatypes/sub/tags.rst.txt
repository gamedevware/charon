Tags
====

The ``Tag`` data type is a sub-type of the :doc:`Text <../all/text>` data type and is used to store a reusable set of tag values (e.g., "fire", "enemy", "magic") that can be shared across multiple documents.  

The ``Tag Collection`` is a collection variant of this type and it is used to store multiple tags. Each tag is separated by the `` `` (space) character.  

UI Behavior
-----------

In the editor, this field is represented as a list of chips/pills/tokens with support for free-form input and autocompletion of existing tags.  
Note that autocompletion relies on scanning all documents of the same type to extract available tags, so performance considerations should be made when using this data type at scale.

Validation Behavior
-------------------

The Charon editor does not validate tags during game data loading (i.e., at runtime). Ensure that your game logic handles any missing or unexpected tags appropriately.

Relation to Multi-Pick List
---------------------------

Tags are similar to the :doc:`Multi-Pick List <../all/multi_pick_list>` data type but offer more flexibility by allowing free-form input.  
C-style named tags can be easily converted to a Multi-Pick List by changing the property type.  
Likewise, Multi-Pick List values can be converted back to Tags if strict value control is no longer needed.

Example
-------

.. code-block:: js

  "fire"
  "poison magical non-resistable"