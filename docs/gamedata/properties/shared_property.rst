Shared Property
===============

A **Shared Property** is a :doc:`Schema <../schemas/schema>` property that syncs data type-related configuration with other properties of the same name across different schemas. When a shared property is modified in one schema, all other synced properties with the same shared name are updated accordingly.

Shared properties can be unlinked (or "decoupled") at any time, converting them into independent, schema-specific properties.

Replicated Parameters
=====================

Shared properties replicate a defined subset of configuration parameters between themselves:

- Data Type
- Default Value
- Uniqueness
- Requirement
- Reference Type (for `Document`, `DocumentCollection`, `Reference`, and `ReferenceCollection` types)
- Size
- Specifications for `PickList`, `MultiPickList`, and `Formula` data types

These parameters ensure consistency across schemas that use the same shared property.

Impact on Generated Source Code
===============================

In cases where a property results in a distinct type in the generated source code—such as a `PickList` producing an ``enum``—the **name of the shared property** is used to derive the generated type name.

For example:

- A shared `PickList` property named ``Damage Type`` would generate:
  - `DamageType` enum in C#
  - `EDamageType` enum in Unreal Engine C++

To customize this behavior, the `Generated Type Name` field of the property can be set manually to override the default naming convention.

See also
========

- :doc:`Schema <../schemas/schema>`
- :doc:`Property <property>`
- :doc:`Id Property <id_property>`
- :doc:`Shared Property <shared_property>`
- :doc:`All Data Types <../datatypes/list>`
- :doc:`Creating Document Type (Schema) <../creating_schema>`