Change History
==============

On a server with change history enabled, every commit to a branch is recorded as a **change**: who made it, when, which
documents it touched, and the patch that reproduces it. The history lets you see what happened to the game data,
compare any two revisions, restore a single document, roll the branch back, or start a new branch from a past revision.

.. contents:: On this page
   :local:
   :depth: 2

----

Revisions and Changes
---------------------

Each change produces a new **revision** of the branch, identified by a revision hash. The latest revision is the
branch **head**. Changes come in several kinds:

.. list-table::
   :header-rows: 1
   :widths: 15 85

   * - Kind
     - Recorded when
   * - ``Edit``
     - Documents are created, updated or deleted, including schema changes and imports.
   * - ``Restore``
     - The branch is restored from a backup file, which replaces its game data in one change.
   * - ``Rollback``
     - The branch is rolled back to an earlier revision. The record carries the reason given for it.
   * - ``Merge``
     - A :doc:`change request <change_requests>` is completed. A merge from another branch also records the source
       revision it took the changes from.
   * - ``Gap``
     - The server could not record what happened between two revisions, for example after the data was changed
       outside the server. The gap marks where the history is incomplete.

Branches share history. A branch created from another one starts at the source's head and keeps the source's earlier
changes on its own timeline, so its history begins with the source's (see
:doc:`Workspaces, Projects, and Branches <workspaces_and_projects>`).

----

Browsing the History
--------------------

Open **Change History** from the branch's actions menu in the side navigation. The page lists the branch's changes,
newest first, with their kind, author, time and the collections they touched. More changes load as you scroll.

To see the history of one collection, use **History** in that collection's document list. The collection page lists
every change that touched a document of the collection, one row per document. Pick a document there to narrow it to
that document alone. A collection deleted since still has its history.

Searching
^^^^^^^^^

The search field matches the text each change wrote or removed, the ids of the documents it touched, the names of
their collections, the reason a change was detached, and the start of a revision hash. Words match loosely, so a small
typo still finds the change. The **Filter** menu adds conditions such as the
author, the change kind, a time range (*Today*, *Since...*, *Before...*), the collection or the document.

A search over a long history runs in steps. When it has not reached the oldest change yet, the page says how far back
it searched and offers **Search older** to continue.

Filters are written as ``property operator value`` triplets separated by spaces, the same way the REST API takes them:

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - Property
     - Value
   * - ``revisionHash``
     - A full revision hash, or its first characters.
   * - ``committedAt``
     - A date and time, compared with ``>``, ``>=``, ``<``, ``<=``.
   * - ``authorId``
     - The author's user id.
   * - ``changeKind``
     - ``Edit``, ``Restore``, ``Rollback``, ``Merge`` or ``Gap``.
   * - ``schemaId``
     - A collection's schema id. Matches changes that touched one of its documents.
   * - ``documentId``
     - A document id.
   * - ``detached``
     - ``true`` or ``false``. See *Detached changes* below.

Operators are ``=``, ``!=``, ``>``, ``>=``, ``<``, ``<=``, ``contains`` and ``in``. For example,
``changeKind = Merge committedAt >= 2026-11-01`` lists the merges since the first of November.

Viewing a change
^^^^^^^^^^^^^^^^

Open a change to see every document it changed, before and after, side by side. Unchanged parts of each document are
folded. Use the arrows to step to the previous or next change, and the search field to find a document in a large
change. **Compare** on the history page does the same for any two revisions: select two or more changes and it compares
the oldest with the newest of them.

**Download Patch** saves the change as a patch file, which can be applied to other game data with an import.

----

Undoing Changes
---------------

Restoring one document
^^^^^^^^^^^^^^^^^^^^^^

On a document's history, **Restore As Before...** and **Restore As After...** bring that document back to its version
before or after the selected change. A document that did not exist at that revision is deleted, and a deleted one is
created again. The restore is saved as a new change; other documents and the rest of the history stay as they are. The
restored document must still pass validation against the current schema.

Rolling back a branch
^^^^^^^^^^^^^^^^^^^^^

**Rollback to Here...** returns the whole branch to its state right after the selected change. A reason is required and
is kept in the history.

- Every later change leaves the timeline and becomes *detached*. Detached changes stay readable for a while and are
  then deleted for good.
- The rollback is recorded as a ``Rollback`` change, so the history shows what happened and why.
- With **Abort pending transactions**, edits in progress on the branch are aborted so they cannot hold the rollback up.
  Otherwise the rollback waits for them to finish.

Detached changes
^^^^^^^^^^^^^^^^

A rollback, or a push onto a branch, takes changes off the branch's timeline. These changes are *detached*: hidden by
default, shown with **Show detached**, and still readable until the retention period ends (30 days by default,
configured by the server administrator with ``DataSources:History:DetachedRetention``). After that they are deleted.
To keep a detached state for longer, create a branch or a backup from it before it expires.

Starting a branch from a past revision
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Branch from Here...** creates a new branch whose data is the state right after the selected change. The current
branch is not modified. It is not offered for detached changes. This is the way to recover something from the past without rolling back everyone's work.

----

Truncating the History
----------------------

History takes storage, which counts towards the workspace quota. **Truncate to Here...** deletes the selected change and
every change before it from the branch's history:

- The next newer revision becomes the oldest one in the history.
- Deleted revisions can no longer be viewed, compared or rolled back to, and detached changes made before that revision
  are deleted as well.
- The game data itself does not change.

Truncation is refused at the branch head, for history the branch inherited from its source branch, and for history
another branch still builds on.

Truncation and rollback cannot be undone. Both dialogs offer to back up the project first; the operation then starts
only once the backup completes. When no backup destination is set up, the dialogs link to the backup settings instead.

----

Limits
------

- Change history is a server feature. The administrator turns it off with ``DataSources:History:IsEnabled`` set to
  ``false``; the history menu items, change requests and history links are then hidden.
- A branch that keeps its game data in an external MongoDB database records no change history.

----

REST API
--------

All operations are under ``/datasource/{dataSourceId}/history/`` (OpenAPI tag ``DataSourceHistory``). Revisions are addressed by
their revision hash. Failures use the usual :doc:`error body <rest>` with an error code.

.. list-table::
   :header-rows: 1
   :widths: 8 32 60

   * - Method
     - Path
     - Operation
   * - GET
     - ``/``
     - ``getHistory`` - streams the branch timeline, newest first. Query ``fromRevision``, ``limit``,
       ``includeDetached``, ``filters``, ``query`` and ``parts``. A ``query`` that is a bare revision hash with no
       filters returns that revision directly.
   * - GET
     - ``/documents/``
     - ``getDocumentHistory`` - streams the changes of one collection (``schemaId``) or one document
       (``documentId``), resuming at ``fromRevision`` and ``fromDocumentIndex``.
   * - GET
     - ``/{revisionHash}/``
     - ``getChange`` - one change with its forward patch.
   * - DELETE
     - ``/{revisionHash}/``
     - ``deleteHistory`` - truncates: deletes the revision and all history before it.
   * - GET
     - ``/{revisionHash}/diff/``
     - ``getChangeDiff`` - the patch between this revision and the one given in ``vs``.
   * - GET
     - ``/{revisionHash}/changeset/``
     - ``getChangeSet`` - the documents the revision changed, before and after, paged with ``skip`` and ``take``.
       ``vs`` picks another revision as the *before* state.
   * - POST
     - ``/{revisionHash}/rollback/``
     - ``rollback`` - body ``reason`` and ``rejectAllTransactions``.

The data source capabilities report ``journaling: true`` for a branch that records history.
