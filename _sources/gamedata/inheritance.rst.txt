Implementing Inheritance
========================

Inheritance is a familiar tool for programmers when working with shared behavior or data. Unfortunately, it is not natively supported in Charon. However, you can achieve similar functionality using alternative approaches.


For example, imagine you have three different document types: ``Armor``, ``Weapon``, and ``Shield``. You want to include all these items in a ``Shop`` list of sellable goods. In traditional inheritance, you could create a base type to unify these documents and refer to it. 

.. figure:: ./inheritance_start.png

Without inheritance, here are three possible approaches:

1. Composition
---------------

Extract the shared data from all sellable item types into a separate document type called ``Item``. Each sellable document (e.g., ``Armor``, ``Weapon``, ``Shield``) should include an embedded ``Item`` document containing store-relevant information. In the ``Shop`` list of sellable goods, you can store references to ``Item`` documents.

.. figure:: ./inheritance_composition.png

2. Merging
----------

Alternatively, combine the three document types (``Armor``, ``Weapon``, and ``Shield``) into a single document type called ``Item``. This document will contain fields for all three original types, along with an additional ``Type`` field to specify the item's category. The ``Shop`` list can then store references to these unified ``Item`` documents.

.. figure:: ./inheritance_merging.png

3. Aggregation
--------------

As a less elegant alternative, introduce a ``ShopItem`` type with fields referencing all possible document types (``Armor``, ``Weapon``, and ``Shield``). In each ``ShopItem`` document, only one of these fields will be filled, depending on the item's type. The ``Shop`` list can then reference ``ShopItem`` documents.

.. figure:: ./inheritance_aggregation.png

4. Tagged Union (Recommended)
-----------------------------

A more powerful and storage-efficient alternative to Aggregation is to use a Tagged Union Schema (also known as a Discriminated Union, Sum Type, or ``$oneOf``). Tagged Unions allow documents of different shapes to coexist within the same collection or be embedded inside other documents, making them a natural fit when multiple heterogeneous document types must be handled together.

Union Schemas have several important distinctions from Aggregation:

- They provide first-class support in the editor UI, making them more convenient to create and maintain than other inheritance alternatives.
- Unassigned properties within a Tagged Union document are not stored and therefore take no space.

When used in this scenario, a ``ShopItem`` can be modeled as a Tagged Union that defines ``Armor``, ``Weapon``, and ``Shield`` as its possible variants.

.. figure:: ./inheritance_tagged_union.png

Conclusion
----------

Each of these methods has its trade-offs in terms of simplicity, flexibility, and performance. Choosing the right approach depends on your application's requirements and the expected complexity of your data model.

See also
--------

- :doc:`Creating Document Type (Schema) <creating_schema>`
- :doc:`Filling Documents <filling_documents>`
- :doc:`Publishing Game Data <publication>`
- :doc:`Generating Source Code <generating_source_code>`