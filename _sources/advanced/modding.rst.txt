Modding Support
===============

The free version of Charon can be distributed together with your shipped game, letting players
edit game data with the same editor your team used to build it. Combined with patch files,
this enables a full modding pipeline: players edit a copy of the game data, changes are captured
as a small patch, and the game loads the base data with any number of patches applied on top.

.. contents:: On this page
   :local:
   :depth: 2

----

Overview
--------

A typical modding setup consists of three parts:

1. **The base game data file** (e.g. ``gamedata.json``), shipped with the game or provided in a
   separate mod kit.
2. **The Charon editor**, launched locally by the player (or by your game) against a copy of that
   file, with schema editing disabled.
3. **Patch files** describing the mod's changes relative to the base data, loaded by the game at
   startup through the generated ``Load()`` code.

----

Shipping the Editor with Your Game
-----------------------------------

Charon is a .NET tool, so the player's machine needs .NET installed. What exactly is required depends
on which of the two options below you pick. Verify what is present with:

.. code-block:: bash

   dotnet --list-sdks
   dotnet --list-runtimes

If .NET is missing, direct the player to the
`.NET download page <https://dotnet.microsoft.com/download>`_. Some distribution platforms
(e.g. Steam) can install the .NET Runtime automatically as a game dependency.

There are two ways to run the editor:

**On-demand via the .NET SDK (simplest, requires the .NET SDK 10 or later):**

.. code-block:: bash

   dnx dotnet-charon -- SERVER START --dataBase "./gamedata.json" --denySchemaEditing --launchDefaultBrowser

**A bundled copy of a specific version (full control, only the .NET 8 Runtime required):**

Download the ``dotnet-charon`` package from
`nuget.org <https://www.nuget.org/packages/dotnet-charon/>`_ (a ``.nupkg`` file is a ZIP archive)
and ship the contents of ``tools/net8.0/any/`` with your game, then launch it via the runtime:

.. code-block:: bash

   dotnet "<game folder>/Charon/Charon.dll" SERVER START \
     --dataBase "./mods/gamedata_copy.json" \
     --port 8080 \
     --denySchemaEditing \
     --launchDefaultBrowser

The ``--denySchemaEditing`` flag is important for modding scenarios: it locks the data
*structure* (schemas), so mods can change values and documents but cannot break the shape of
the data your compiled game expects. See :doc:`SERVER START <commands/serve>` for all flags.

----

Capturing Mod Changes as a Patch
---------------------------------

Instead of shipping a whole modified game data file, a mod can be a small **patch file** -
the difference between the base data and the modified copy. Creating patches is currently
a CLI-only operation - there is no UI action for it:

.. code-block:: bash

   dnx dotnet-charon -- DATA CREATEPATCH \
     --dataBase1 "./gamedata.json" \
     --dataBase2 "./mods/gamedata_copy.json" \
     --output "./mods/my_mod.gdpatch" \
     --outputFormat json

Patch files are small, composable, and independent of each other as long as they touch
different documents. See :doc:`Patch and Diff Workflow <patch_diff>` for the format details
and conflict behavior.

----

Loading Mods at Runtime
------------------------

The generated source code loads patches alongside the base game data - pass patch streams in
the load options. Patches are applied in the order given, and each patch is merged into the
data following the default :doc:`merge rules <merge_logic>`. Patching during load is supported
by all Tier 1 code generators:
**C# 4.0**, **C# 7.3**, **TypeScript**, and **Unreal Engine C++** (see
:doc:`Generating Source Code <../gamedata/generating_source_code>`).

C# example:

.. code-block:: csharp

   var gameData = new GameData(gameDataStream, new Formatters.GameDataLoadOptions {
       Format = Formatters.Format.Json,
       Patches = new[] { modPatchStream1, modPatchStream2 }
   });

A simple mod-loading convention: scan a ``mods/`` folder for patch files at startup and pass
them all to ``Load()`` in a deterministic order (e.g. alphabetical, or driven by a mod manifest).

----

How Patches Are Merged at Load Time
------------------------------------

Runtime patching follows the same deterministic principles as the editor-side
:doc:`document merge logic <merge_logic>`. The core rules, in short:

- If the patch **provides a value** for a property → the result uses the patch value.
- If the patch **does not provide a value** (the property key is absent) → the original
  value is kept.
- A property present with an explicit ``null`` is an **intentional deletion**, not a
  missing value.
- The rules apply recursively: embedded documents are merged property-by-property, and
  collections are merged item-by-item using the document's ``Id`` as the key.

On top of that, for whole documents inside a patch, the **presence of the** ``Id`` **field**
decides how the entry is applied - the ``Id`` *value* is irrelevant:

**No** ``Id`` **field** - a *partial update*. The entry's fields are merged into the existing
document. A partial update cannot resurrect a deleted document - if the document was removed
by an earlier patch, it stays deleted:

.. code-block:: text

   original     patch 1    patch 2     patch 3     result
   { Id: 1 }  →  null   →  { ... }  →  { ... }  =  null

**Has an** ``Id`` **field** - a *full replacement*. The document is replaced entirely.
A replacement can also resurrect a previously deleted document:

.. code-block:: text

   original     patch 1    patch 2       patch 3       result
   { Id: 1 }  →  null   →  { Id: 2 }  →  { Id: 3 }  =  { Id: 3 }

See :doc:`Document Merge Logic <merge_logic>` for the full property-level rules
(``LocalizedText`` per-language merging, collection modes, and validation caveats when a
patch recreates a document with missing required fields).

----

See also
--------

- :doc:`SERVER START Command <commands/serve>`
- :doc:`DATA CREATEPATCH Command <commands/data_create_patch>`
- :doc:`Patch and Diff Workflow <patch_diff>`
- :doc:`Merge Logic <merge_logic>`
- :doc:`Generating Source Code <../gamedata/generating_source_code>`
- :doc:`Publishing Game Data <../gamedata/publication>`
