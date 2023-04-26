Overview
==========

The ``Document`` data type in game data schema is used to represent complex structures. A document can contain multiple properties of different data types, including other documents or document collections, allowing for hierarchical data modeling.
It is important to note that the lifetime of sub-documents is tied to the lifetime of the parent document, meaning that any changes (e.g. deletion) to the parent document will affect all of its sub-documents.

C# Type
   ``class``
Uniqueness
   May NOT be checked for uniqueness.
   
Example
=======

For example, in a **Dialog**, each node can be a ``Document`` with dialog `text  <localized_text.rst>`_, response options, and `actions  <formula.rst>`_ that occur after a response is chosen. Each response option can be a sub-document that is another **Dialog** node.

.. code-block:: js
  {
      "Text": "Welcome to the game. What's your name?",
      "Options": [
          {
              "Text": "My name is John.",
              "Options": [
                  {
                      "Text": "Hello John! What brings you here?",
                      "Options": [
                          {
                              "Text": "I'm looking for adventure.",
                              "Action": "dialog.GiveQuestAndEnd()"
                          },
                          {
                              "Text": "I'm on a mission.",
                              "Options": [/* ... */]
                          }
                      ]
                  }
              ]
          },
          {
              "Text": "I prefer not to say.",
              "Action": "dialog.End()"
          }
      ]
  }
 