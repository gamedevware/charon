Data-Driven Game Design with Charon
=====================================

Every game team hits the wall eventually.

It starts small — a spreadsheet for item stats, another for enemy data, a few config files for quests.
Then the game grows. Tabs multiply. Formulas break silently. A programmer renames a constant and three
designer files now reference something that doesn't exist. A localization request arrives and no one knows
where all the strings actually live.

**This is the spreadsheet ceiling** — and most teams don't realize they've hit it until something breaks in production.

Charon exists to push that ceiling out of your way.

----

What is Data-Driven Game Design?
---------------------------------

Data-driven game design means your game's content lives in *structured, validated data* — not in source code,
not in spreadsheets, not in a programmer's head. Designers define what a quest looks like. Programmers consume
it through generated, type-safe code. The pipeline enforces that they stay in sync.

When it works:

- A designer changes a boss's phase thresholds without filing a ticket
- Deleting a deprecated item immediately surfaces every quest that still references it
- Adding a language is a data task, not a code task
- Game balance is version-controlled, diff-able, and rollback-able

**Charon is the tool that makes this practical.** It gives your team a shared language between design and engineering —
a structured database, a visual editor, and a code generator that keeps both sides moving independently.

**TLDR:** Charon is an in-game database for your game. It replaces spreadsheets and config files with a validated,
schema-driven data layer that generates ready-to-use code for your engine.

----

Who Is This For?
-----------------

**Game Designers**
  You get a real editor — schemas you define, forms that match your data, and validation that catches mistakes
  before the next build does. No more pasting values into cells and hoping the formula still works.

**Programmers**
  You get generated, type-safe classes for your data. Instead of parsing raw JSON and casting strings,
  you write ``gameData.Heroes.Find("Arbalest").Stats.Hp`` with full IDE autocomplete. The loading, validation,
  and localization plumbing is already handled.

**Technical Leads**
  You get a pipeline. Charon has a CLI, a REST API, and CI/CD hooks. Validate data on every commit.
  Diff game data between versions. Patch live data without a full rebuild. Distribute the editor with
  your game for community modding.

----

Deployment Options
-------------------

Charon adapts to your workflow, not the other way around:

- :doc:`Unity Plugin <unity/overview>` — edit game data directly inside the Unity editor
- :doc:`Unreal Engine Plugin <unreal_engine/overview>` — native integration with the Unreal content pipeline
- :doc:`Standalone App <standalone/overview>` — run the editor locally for any engine (C#, TypeScript, Haxe)
- :doc:`Web / Cloud Edition <web/overview>` — collaborative editing for distributed teams

----

Is It Free?
------------

The offline CLI, standalone app, and engine plugins are **completely free** with no usage restrictions.
They are open-licensed and can be bundled with your shipped game — so your players can build mods
using the same tools you used to build the game.

The online collaborative edition, which enables shared editing across large teams with cloud hosting,
requires a subscription.

----

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 600
  :alt: Charon UI

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/dashboard.png
  :width: 256
  :alt: Charon Dashboard

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/document_collection.png
  :width: 256
  :alt: Charon Document List

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/document_form.png
  :width: 256
  :alt: Charon Document Form

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/documents_import.png
  :width: 256
  :alt: Charon Import

----

Further Reading
---------------

.. toctree::
   :caption: Unreal Engine Quick Start
   :titlesonly:
   :glob:

   /unreal_engine/overview
   /unreal_engine/*

.. toctree::
   :caption: Unity Quick Start
   :titlesonly:
   :glob:

   /unity/overview
   /unity/*

.. toctree::
   :caption: Standalone Quick Start
   :titlesonly:
   :glob:

   /standalone/overview
   /standalone/*

.. toctree::
   :caption: Web / Cloud Edition
   :titlesonly:
   :glob:

   /web/overview
   /web/*

.. toctree::
   :caption: Server Edition
   :titlesonly:

   /server/overview

.. toctree::
   :caption: Data Modeling
   :titlesonly:

   /gamedata/basics
   /gamedata/creating_schema
   /gamedata/filling_documents
   /gamedata/inheritance
   /gamedata/schemas/schema
   /gamedata/schemas/schema_types
   /gamedata/schemas/display_text_template
   /gamedata/schemas/specification
   /gamedata/properties/property
   /gamedata/properties/id_property
   /gamedata/properties/shared_property
   /gamedata/datatypes/list

.. toctree::
   :caption: Source Code Generation
   :titlesonly:

   /gamedata/generating_source_code
   /gamedata/working_with_csharp_code_7_3
   /gamedata/working_with_csharp_code_4_0
   /gamedata/working_with_type_script_code
   /gamedata/working_with_uecpp_code
   /gamedata/working_with_haxe_code

.. toctree::
   :caption: Data Workflows
   :titlesonly:

   /gamedata/publication
   /advanced/import_export
   /advanced/merge_logic
   /advanced/internationalization
   /advanced/validation
   /advanced/backup_restore
   /advanced/patch_diff
   /advanced/cicd

.. toctree::
   :caption: Integration & Automation
   :titlesonly:

   /advanced/command_line
   /advanced/game_data_structure
   /advanced/formula_expression_ast
   /web/rest

.. toctree::
   :caption: Extending Charon
   :titlesonly:

   /advanced/extensions/overview
   /advanced/extensions/implementing_property_editor
   /advanced/extensions/creating_react_extension
   /advanced/extensions/creating_angular_extension

.. toctree::
   :caption: Configuration & Troubleshooting
   :titlesonly:

   /advanced/logs
   /advanced/reset_preferences

.. toctree::
   :caption: CLI Command Reference
   :titlesonly:
   :glob:

   /advanced/commands/*

.. toctree::
   :caption: Reference
   :titlesonly:

   /faq
   /glossary