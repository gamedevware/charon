Schema Editing
==============

.. versionadded:: vNext

Reads and changes schemas (document types) and their properties, one small command per change: rename a
property, add a field, change a type, edit pick list options.

These commands are built for **agents and scripts**. People editing schemas by hand should use the
:doc:`schema editor in the UI </gamedata/creating_schema>`.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`MCP Server </advanced/mcp>` - the same operations as ``schema_*`` tools

---------------
 Commands
---------------

All commands take ``--dataBase`` (file path or remote URL) and ``--credentials`` (for remote sources).
Every write takes ``--dryRun``, which validates and prints the same summary without writing.

.. list-table::
   :header-rows: 1
   :widths: 30 45 25

   * - Command
     - Parameters
     - MCP tool
   * - ``DATA SCHEMA GET``
     - ``--schema``, ``--details``
     - ``schema_get``
   * - ``DATA SCHEMA CREATE``
     - ``--name``, ``--schemaType``, ``--idGenerator``, ``--displayName``, ``--description``, ``--group``, ``--icon``
     - ``schema_create``
   * - ``DATA SCHEMA RENAME``
     - ``--schema``, ``--newName``
     - ``schema_rename``
   * - ``DATA SCHEMA UPDATE``
     - ``--schema``, ``--displayName``, ``--description``, ``--schemaType``, ``--idGenerator``, ``--group``, ``--icon``
     - ``schema_update``
   * - ``DATA SCHEMA RELATIONS``
     - ``--schema``, ``--direction Incoming|Outgoing|Both``, ``--kind Reference|Document``, ``--recursive``,
       ``--depth``, ``--format List|Table|Tree``, ``--details``, ``--counts``
     - ``schema_relations``
   * - ``DATA SCHEMA DELETE``
     - ``--schema``, ``--allowDataLoss``, ``--cascade Deny|Cascade``
     - ``schema_delete``
   * - ``DATA SCHEMA PROPERTY GET``
     - ``--schema``, ``--property``, ``--details``
     - ``schema_property_get``
   * - ``DATA SCHEMA PROPERTY ADD``
     - ``--schema``, ``--name``, ``--type``, ``--requirement``, ``--uniqueness``, ``--default``, ``--after``,
       ``--displayName``, ``--description``
     - ``schema_property_add``
   * - ``DATA SCHEMA PROPERTY RENAME``
     - ``--schema``, ``--property``, ``--newName``
     - ``schema_property_rename``
   * - ``DATA SCHEMA PROPERTY UPDATE``
     - ``--schema``, ``--property``, ``--requirement``, ``--uniqueness``, ``--default``, ``--after``,
       ``--displayName``, ``--description``
     - ``schema_property_update``
   * - ``DATA SCHEMA PROPERTY UPDATESPECIFICATION``
     - ``--schema``, ``--property``, ``--specification``, ``--preservePickList``, ``--preserveFormula``
     - ``schema_property_update_specification``
   * - ``DATA SCHEMA PROPERTY UPDATEPICKLIST``
     - ``--schema``, ``--property``, ``--changes``, ``--allowDataLoss``
     - ``schema_property_update_picklist``
   * - ``DATA SCHEMA PROPERTY CHANGETYPE``
     - ``--schema``, ``--property``, ``--type``, ``--default``, ``--allowDataLoss``
     - ``schema_property_change_type``
   * - ``DATA SCHEMA PROPERTY REMOVE``
     - ``--schema``, ``--property``, ``--allowDataLoss``
     - ``schema_property_remove``

Option values and defaults:

- ``--schemaType`` (``CREATE``, ``UPDATE``): ``Normal`` (default), ``Component`` (always embedded in other documents),
  ``Settings`` (one document only) or ``Union``.
- ``--idGenerator`` (``CREATE``, ``UPDATE``): how the ``Id`` of new documents is produced. ``None`` (default, you
  supply every Id), ``ObjectId``, ``Guid``, ``Sequence`` (per schema) or ``GlobalSequence`` (across the project).
- ``--cascade`` (``DELETE``): what happens to properties of *other* schemas that reference or embed the deleted
  schema, including shared properties. ``Deny`` (default) refuses the delete and lists them; ``Cascade`` removes
  them along with the schema.
- ``--allowDataLoss``: needed only when the edited schema has documents (embedded ones included). On an empty
  schema every command runs without it.
- ``--requirement``: ``None`` (default), ``NotNull`` or ``NotEmpty``. ``--uniqueness``: ``None`` (default),
  ``Unique`` or ``UniqueInCollection``.

Rules shared by all commands:

- ``--schema`` and ``--property`` take exact names or Ids. ``GET``, ``ADD``, ``UPDATE``, ``CHANGETYPE`` and
  ``REMOVE`` accept a space-separated list (``--schema Quest QuestStep``) or ``'*'`` alone for all. Other commands
  take exactly one. On writes ``'*'`` skips the ``Id`` property; on ``GET`` it lists it too. Schema ``'*'`` never
  selects the system schemas (``Schema``, ``SchemaProperty``, ``ProjectSettings``).
- There are no patterns: ``Quest*`` is an unknown name, and ``!`` exclusions are not supported. Every listed name
  must exist, otherwise nothing is written and the error names the missing ones.
- Quote ``'*'``: a bare ``*`` is expanded to file names by the shell before Charon sees it.
- The ``Id`` property cannot be renamed, removed or moved.
- Unknown options fail these commands (``--dry-run`` instead of ``--dryRun`` is an error, not a silent real
  write). Other ``DATA`` commands keep ignoring unknown options.
- Write output is a short summary: targets, changes, affected document count and warnings. Errors go to stderr
  with exit code ``2``.

---------------
 Type Grammar
---------------

``--type`` takes one quoted string ``<DataType> [size] [schema] [options]``. ``GET`` prints types in the same
form, so a printed type passed back to ``CHANGETYPE`` changes nothing.

.. list-table::
   :header-rows: 1

   * - Form
     - Meaning
   * - ``Text``, ``Text 100``, ``LocalizedText 500``
     - optional maximum length
   * - ``Logical``, ``Date``, ``Time``
     - no arguments
   * - ``Integer 4``, ``Number 8``
     - size in bytes, 1-8; omitted size is 4
   * - ``Reference Item``, ``ReferenceCollection Item``
     - referenced schema name, required
   * - ``Document Quest``, ``DocumentCollection Reward``
     - embedded schema name, required
   * - ``ReferenceCollection 10 Item``, ``DocumentCollection 10 Reward``
     - optional maximum item count before the schema name
   * - ``PickList Common=0 Rare=1 Epic=2``
     - options; omitted values are assigned 0, 1, 2...
   * - ``MultiPickList Fire=1 Ice=2 Poison=4``
     - options; omitted values are assigned as powers of two

The type fully determines size and reference target: ``Integer 8`` changed to ``Text`` becomes an unlimited
``Text``, not ``Text 8``. ``Formula`` is not supported by the grammar.

-----------------------
 Pick List Changes
-----------------------

``UPDATEPICKLIST`` edits options partially. Put all changes in one quoted ``--changes`` value; unquoted, the
shell would split them.

.. list-table::
   :header-rows: 1

   * - Token
     - Meaning
   * - ``+Name=value``
     - add an option
   * - ``+Name``
     - add with the next free value (next free power of two for ``MultiPickList``)
   * - ``-Name``
     - remove by name
   * - ``-Name=value``
     - remove and assert the current value; fails when it differs (stale view guard)

Removals apply before additions. A removal and an addition with the same value is a **rename**
(``-HP=2 +HealthPoints=2``); documents store values, so nothing else changes. The same name with a new value is a
**renumber** (``-A=1 +A=3``). Stored values are never migrated: after a renumber or removal they no longer match an
option, so both need ``--allowDataLoss`` while the schema has documents.

-----------------------
 Data Loss Guard
-----------------------

``CHANGETYPE`` with documents (embedded ones included) rejects changes to or from ``Document``,
``DocumentCollection``, ``Reference``, ``ReferenceCollection``, ``Formula``, and from ``LocalizedText``.
These are allowed while the schema has no documents.

Lossy changes need ``--allowDataLoss`` while documents exist: text to number, logical, date, time or pick list;
``Number`` to ``Integer``; number to logical, date or time and back; any type to a pick list; a smaller size or text limit, or a limit added to unlimited
text; a new reference target; options dropped by a full option list replacement. The decision uses the change and
the document count only. Values that do not convert stay as they are and leave documents invalid until edited.
A changed type drops ``pick.*`` entries the new type does not use and formula entries (``param.*``,
``resultType``, ``knownType``). For a shared property, documents of every schema using it count.

To check that a schema is empty, run :doc:`DATA LIST <data_list>` with ``--path '*' --take 0``.

-----------------------
 Relations
-----------------------

``RELATIONS`` answers two questions: where documents of a schema can be found, and which properties point at it.
Each line is one property link:

- ``Incoming`` (default) - other schemas reference (``Reference``, ``ReferenceCollection``) or embed (``Document``,
  ``DocumentCollection``) the schema. ``Owner`` is the schema whose documents hold the link.
- ``Outgoing`` - what the schema references or embeds.
- ``--recursive`` follows embedding chains: incoming ones up to the schemas that embed the owner, outgoing ones down
  into embedded schemas. ``--depth`` caps the path length and implies ``--recursive``. An embedding that returns to
  a schema already on the path is marked ``Cycle`` and not followed further.

``Path`` is the logical path, a JSON Pointer of property names from the owner's root document without collection
indexes, e.g. ``/Item/ActivationEffects``. It is the value :doc:`DATA LIST <data_list>` takes in ``--path``. A
``Component`` owner has no collection of its own; follow ``--recursive`` to the owners that do.

``--counts`` adds ``Documents`` to the header (root documents) and to each incoming ``Document`` line whose owner
has its own collection: the documents stored at that path inside that owner. It runs one query per line.

-----------------------
 Read Format
-----------------------

One line per schema and property, labels equal to the write parameter names, defaults omitted. Property attributes
print in the order ``Property``, ``Type``, ``Requirement``, ``Uniqueness``, ``Auto-Generated``, ``Default``,
``Shared``, then with ``--details`` ``DisplayName`` and ``Description``.

Free text is JSON-quoted and single-line. Without ``--details`` a ``Default`` longer than 80 characters is cut and
ends in ``…``; such a value is truncated and must not be passed back.

---------------
 Examples
---------------

The examples run against a copy of the RPG sample project.

**GET** - schema with its properties:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA GET --dataBase rpg.json --schema Quest

  #> Schema: Quest, IdGenerator: ObjectId, Group: Story
  #>   - Property: Id, Type: Text 24, Requirement: NotNull, Uniqueness: Unique, Auto-Generated
  #>   - Property: Title, Type: LocalizedText 200, Requirement: NotEmpty
  #>   - Property: Difficulty, Type: PickList Easy=0 Normal=1 Hard=2, Default: "Normal"
  #>   - Property: Giver, Type: Reference Hero

**CREATE**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA CREATE --dataBase rpg.json --name Quest --idGenerator ObjectId --group Story

  #> Target: Quest
  #> Change: created schema Quest

**RENAME** (dry run):

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA RENAME --dataBase rpg.json --schema Disease --newName Illness --dryRun

  #> Dry run: nothing was written.
  #> Target: Disease
  #> Change: renamed schema Disease to Illness
  #> Documents: 6 (incl. embedded)

**UPDATE**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA UPDATE --dataBase rpg.json --schema Quest --displayName "Quests" --icon scroll

  #> Target: Quest
  #> Change: updated schema Quest: DisplayName, Icon scroll

**DELETE** - an empty schema needs no extra options:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA DELETE --dataBase rpg.json --schema Quest

  #> Target: Quest
  #> Change: deleted schema Quest
  #> Documents: 0 (incl. embedded)

A schema with documents needs ``--allowDataLoss``; its documents are deleted with it:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA DELETE --dataBase rpg.json --schema Quirk

  #> Schema `Quirk` has 8 documents (incl. embedded). Pass allowDataLoss to delete them with the schema.

  dnx dotnet-charon -- DATA SCHEMA DELETE --dataBase rpg.json --schema Quirk --allowDataLoss

  #> Target: Quirk
  #> Change: deleted schema Quirk
  #> Documents: 8 (incl. embedded)

A schema other schemas reference is refused until ``--cascade Cascade`` allows removing those properties:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA DELETE --dataBase rpg.json --schema Item --allowDataLoss

  #> Schema `Item` is referenced by property CurioCleansingOption.Item, property ItemWithCount.Item,
  #> property Provision.Item, property Trinket.Item. Set cascade to Cascade to remove these properties too.

  dnx dotnet-charon -- DATA SCHEMA DELETE --dataBase rpg.json --schema Item --allowDataLoss --cascade Cascade

  #> Target: Item
  #> Change: deleted schema Item
  #> Change: removed property CurioCleansingOption.Item
  #> Change: removed property ItemWithCount.Item
  #> Change: removed property Provision.Item
  #> Change: removed property Trinket.Item
  #> Documents: 39 (incl. embedded)

**PROPERTY GET**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY GET --dataBase rpg.json --schema Monster --property Name Type

  #> Property: Name, Type: LocalizedText 120, Requirement: NotNull
  #> Property: Type, Type: PickList Human=1 Beast=2 Unholy=3 Eldritch=4 Corpse=5 Carpentry=6 Crockery=7 Ironwork=8 Thatchery=9 Cosmic=10, Requirement: NotNull, Default: "1"

**PROPERTY ADD**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY ADD --dataBase rpg.json --schema Quest \
    --name Difficulty --type "PickList Easy Normal Hard" --default Normal

  #> Target: Quest.Difficulty
  #> Change: added property Quest.Difficulty (PickList Easy=0 Normal=1 Hard=2)

**PROPERTY RENAME**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY RENAME --dataBase rpg.json --schema Quest --property Giver --newName QuestGiver

  #> Target: Quest.Giver
  #> Change: renamed property Quest.Giver to QuestGiver
  #> Documents: 0 (incl. embedded)

The rename keeps the property Id, so stored values move with it. It warns when the old name still appears in the
schema's display text template or a formula specification; those are not rewritten.

**PROPERTY UPDATE**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY UPDATE --dataBase rpg.json --schema Quest --property Difficulty \
    --requirement NotNull --after Id

  #> Target: Quest.Difficulty
  #> Change: updated property Quest.Difficulty: Requirement NotNull, moved after Id

**PROPERTY UPDATESPECIFICATION** - the only raw ``key=value`` surface; ``--preservePickList`` and
``--preserveFormula`` keep the entries the type system owns:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY UPDATESPECIFICATION --dataBase rpg.json --schema Quest \
    --property Difficulty --specification "editor=radio" --preservePickList

  #> Target: Quest.Difficulty
  #> Change: set specification of Quest.Difficulty

**PROPERTY UPDATEPICKLIST**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY UPDATEPICKLIST --dataBase rpg.json --schema Quest \
    --property Difficulty --changes "-Hard=2 +Heroic=2 +Legendary"

  #> Target: Quest.Difficulty
  #> Change: renamed option Hard to Heroic (value 2)
  #> Change: added option Legendary (value 3)
  #> Documents: 0 (incl. embedded)

**PROPERTY CHANGETYPE** - a lossy change with documents needs ``--allowDataLoss``:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY CHANGETYPE --dataBase rpg.json --schema Hero \
    --property ProvisionsCount --type "Integer 2" --dryRun

  #> `Hero.ProvisionsCount` has 3 documents (incl. embedded) and the change may lose data: `Integer 4` → `Integer 2`
  #> shrinks the size from 4 to 2 bytes. Pass allowDataLoss to proceed; values that do not convert stay as they are
  #> and leave documents invalid until edited.

  dnx dotnet-charon -- DATA SCHEMA PROPERTY CHANGETYPE --dataBase rpg.json --schema Hero \
    --property ProvisionsCount --type "Integer 2" --allowDataLoss --dryRun

  #> Dry run: nothing was written.
  #> Target: Hero.ProvisionsCount
  #> Change: changed type of Hero.ProvisionsCount from `Integer 4` to `Integer 2`
  #> Documents: 3 (incl. embedded)
  #> Warning: Hero.ProvisionsCount: `Integer 4` → `Integer 2` shrinks the size from 4 to 2 bytes

**PROPERTY REMOVE**:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA PROPERTY REMOVE --dataBase rpg.json --schema Quest --property QuestGiver

  #> Target: Quest.QuestGiver
  #> Change: removed property Quest.QuestGiver
  #> Documents: 0 (incl. embedded)

**RELATIONS** - where ``ParameterValue`` documents live:

.. code-block:: bash

  dnx dotnet-charon -- DATA SCHEMA RELATIONS --dataBase rpg.json --schema ParameterValue --recursive --format Tree

  #> Schema: ParameterValue, SchemaType: Component, IdGenerator: Sequence, Icon: fugue16/edit-list
  #>   Incoming (referenced or embedded by):
  #>     └ CurioCleansingOption (Component) /Effects — DocumentCollection ParameterValue
  #>       └ Curio /CleansingOptions/Effects — DocumentCollection 8000 CurioCleansingOption
  #>     └ Item /ActivationEffects — DocumentCollection ParameterValue
  #>       └ Trinket /Item/ActivationEffects — Document Item
  #>     └ Monster /Parameters — DocumentCollection 8000 ParameterValue

  dnx dotnet-charon -- DATA LIST --dataBase rpg.json --schema ParameterValue --path /Parameters

---------------
 See also
---------------

- :doc:`DATA LIST SCHEMAS <data_list_schemas>` - the raw ``Schema`` collection documents
- :doc:`MCP Server </advanced/mcp>`
