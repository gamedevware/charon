Change Requests
===============

A **change request** proposes moving changes into a branch. Instead of overwriting a branch the way a
push does (see :doc:`Workspaces, Projects, and Branches <workspaces_and_projects>`), you review the proposed changes
one by one, accept or reject each of them, and the accepted ones land in the target branch as a single validated commit.

.. contents:: On this page
   :local:
   :depth: 2

----

What a Change Request Is
------------------------

Every change request has a **target branch** - the branch that receives the changes - a title, a description, and a
state: *open*, *merged*, or *closed*. Each branch request also gets a project-local number such as ``#12`` for display.
Two kinds exist:

.. list-table::
   :header-rows: 1
   :widths: 15 55 30

   * - Kind
     - Where the changes come from
     - Typical author
   * - ``branch``
     - Another branch of the same project. The request is live: it follows the source branch, so new commits
       there show up in the review without recreating anything.
     - A designer finishing work on a feature branch.
   * - ``proposal``
     - The result of an import, run against the target branch head without applying it.
     - A user who wants to check an import before it lands in the branch.

Both kinds are reviewed and completed the same way. The source branch is never modified by a change request.

A branch change request cannot be opened when the source branch has nothing the target lacks, nor from a branch into
itself. Only one open branch request can exist for a given pair of branches.

Proposals are short-lived
^^^^^^^^^^^^^^^^^^^^^^^^^

A proposal is kept in the server's memory only. It has no number (it reads ``0``), it is not listed with the other
requests, and it leaves no record behind once it is gone. It is addressed by its id, so it can be shared as a link with
anyone who can view the target branch.

A proposal is discarded **one hour after it was last opened**. Reading it, or any step of its review, starts the hour
again. A merged or closed proposal stays readable for the same hour. A server restart discards every proposal.

Changes are compared against the **merge base** - the latest revision both branches share. A change counts as
*incoming* when only the source changed it, as a *conflict* when both sides changed it differently, and as
*converged* when both sides ended up with the same result. Converged changes need no decision. Changes made only
on the target are not listed. Comparisons are exact: ``null`` and an empty text are different values.

----

Reviewing in Three Stages
-------------------------

The server keeps no review state. The review is a sequence of three stages, and the decisions you make are held by
the client until you complete the request.

1. **Schema.** Changes to document types (schemas), their properties, shared properties and the project settings are
   compared first, and each is decided as a whole. A schema change reshapes the data of every document of that schema, so schema is settled
   before data is compared. Each schema item is one of:

   - *incoming* - changed on the source only. Decide ``accept`` or ``reject``.
   - *conflict* - changed differently on both sides, or two different items added under one name. Decide
     ``takeSource`` or ``takeTarget``.
   - *converged* - identical on both sides. No decision.
   - *deleted* - a schema, property or shared property deleted on either side. **Deletions always win**: the item is deleted in the
     result whatever the other side did to it, because a deletion removes dependent data and references that cannot
     be brought back along with it. A deleted item is listed together with the number of documents and dependent
     properties that go with it, but takes no decision. To keep the item, stop the deletion at its source or close
     the change request.

   A property linked to a shared property takes its data type, size, reference, specification, requirement, uniqueness
   and default value from the shared property, so those follow the decision on the shared property item. The
   property's own item decides its name, display name, description and link. A link to a deleted shared property is
   removed.

2. **Data.** Once schema decisions are known, the documents of the three states are reshaped to the resulting
   schema and compared document by document. Each document is *incoming*, *conflict* or *converged*, with the same
   decisions as above. Changing a schema decision requires a new data analysis.

3. **Review.** Both lists are shown with their decisions, and a validation dry run reports what completion would
   break, without changing anything.

If either branch moves while you review, the request reports the new revisions, and decisions made against older
ones should be looked at again.

----

Completing
----------

Completion is a single call that carries the reviewed revisions of both branches and a decision for **every**
incoming and conflicting schema item and document. A missing decision is refused, and so is a decision that is
not allowed for its row.

- The accepted changes are applied to the target as **one merge commit** that carries schema and data together, so
  the target never sits in a half-merged state. Open transactions on the target are not aborted.
- The commit is validated like any bulk edit. When validation fails, the request stays open and nothing is
  written; fix the cause or change a decision and complete again.
- If you **reject everything**, no commit is made and the request is closed as rejected.
- If either branch **moved** since the revisions you reviewed, completion is refused and a new review is required.
- Rejecting an incoming document of a branch request is permanent in the usual version-control sense: after a merge
  the merge base moves past it, so a later request from the same branch does not offer it again.

The result reports the state, the merge revision, and how many changes were accepted and rejected.
A merged branch request records the source branch as a second parent in the target's history, which can be
filtered with ``kind:merge``.

Other ways a request ends
^^^^^^^^^^^^^^^^^^^^^^^^^

- **Close** closes an open request as rejected. A closed branch request can be reopened while both branches
  still exist; a closed proposal cannot, and its imported changes are discarded.
- Deleting the source or the target branch closes the request.
- Restoring the project from a restore point closes all of its requests.
- Deleting the project deletes its requests.
- If the source head is already contained in the target - for example because the branches were merged another
  way - the request is marked merged on its next read.

----

Permissions
-----------

- Anyone who can view the project can list and read change requests.
- **Edit** access to the target branch is enough to create, update, complete, close and reopen a request.
- Accepting a **schema** change additionally needs **design** access to the target branch. Completion is refused
  when the resulting schema differs from the target's current one and the caller lacks it.

See :doc:`Roles and Permissions <permission_and_roles>` for what each role grants.

----

Limits
------

- Change requests work only in **journaled projects**, that is, with :doc:`change history <change_history>` enabled on the branch. Otherwise
  the request is refused and the branch capabilities report ``journaling: false``.
- A branch request needs a revision both branches share. It cannot be opened when history deletion detached
  one of them.
- Change requests between branches are part of the **Studio** and **Enterprise** subscriptions. Studio allows
  50 open branch requests per project; Enterprise has no limit. On other subscriptions new branch requests cannot
  be opened and closed ones cannot be reopened. Proposals need no subscription, and requests that are already
  open can still be completed or closed.
- The server administrator can turn change requests off with ``ChangeRequests:IsEnabled`` set to ``false``.
  Every change request operation, proposals included, then answers *not supported*.
- A project can hold a limited number of open proposals at once (50 by default). A proposal writes no history.
- Merged and closed requests are removed after a retention period (180 days by default, configured by the
  server administrator).

----

REST API
--------

All operations are under ``/project/{projectId}/change-request/`` (OpenAPI tag ``ChangeRequest``) and are
addressed by ``changeRequestId``, the identifier returned by the create and list calls. Only
``getChangeRequest`` additionally accepts the display number (``12``) of a branch request, so a link such as
``/change-request/12`` can be resolved with one call. Failures use the usual :doc:`error body <rest>` with an error code.

A proposal is opened by ``importAsChangeRequest``: ``PUT /datasource/{dataSourceId}/change-request/`` takes the same
parameters and body as the ``import`` operation, minus ``dryRun``, and returns the import ``report`` with the new
``changeRequest``. ``changeRequest`` is null when the import failed or changed nothing. Every operation below then
works on it by its id.

.. list-table::
   :header-rows: 1
   :widths: 8 32 60

   * - Method
     - Path
     - Operation
   * - GET
     - ``/``
     - ``listChangeRequests`` - query ``filters``, ``query``, ``skip``, ``take``. Newest first. ``filters`` takes
       ``property operator value`` triplets, as the history search does, over ``state``, ``authorId``,
       ``branchName`` (source or target), ``createdAt`` and ``updatedAt``; ``query`` matches the title, the
       description or the number. Proposals are never listed.
   * - POST
     - ``/``
     - ``createChangeRequest`` - opens a branch request; body ``CreateChangeRequest``: ``title``, ``description``,
       ``targetBranchName``, ``sourceBranchName``.
   * - GET
     - ``/{changeRequestId}/``
     - ``getChangeRequest`` - the record plus its live status (revisions and mergeability) while open.
   * - PATCH
     - ``/{changeRequestId}/``
     - ``updateChangeRequest`` - ``title`` and ``description``.
   * - GET
     - ``/{changeRequestId}/schema-changes/``
     - ``getChangeRequestSchemaChanges`` - stage 1 items for the current revisions, each with its base, source and
       target bodies.
   * - POST
     - ``/{changeRequestId}/analysis/``
     - ``analyzeChangeRequest`` - body: ``expectedSourceRevisionHash``, ``expectedTargetRevisionHash``,
       ``schemaDecisions``. Returns ``analysisId`` with ``incoming``, ``conflicts`` and ``converged`` counts.
   * - GET
     - ``/{changeRequestId}/changes/``
     - ``getChangeRequestChanges`` - query ``analysisId``, ``filter`` (``all``, ``incoming``, ``conflict``,
       ``converged``), ``schemaId``, ``skip``, ``take``. A page of document rows.
   * - POST
     - ``/{changeRequestId}/validate/``
     - ``validateChangeRequest`` - body ``CompleteChangeRequest``. Dry run: returns ``isValid`` and a ``report``,
       changes nothing.
   * - POST
     - ``/{changeRequestId}/complete/``
     - ``completeChangeRequest`` - body ``CompleteChangeRequest``: both ``expected...RevisionHash`` values,
       ``schemaDecisions`` (``itemId``, ``decision``) and ``dataDecisions`` (``schemaId``, ``documentId``,
       ``decision``). Returns ``state``, ``mergeRevisionHash``, ``acceptedCount``, ``rejectedCount``.
   * - POST
     - ``/{changeRequestId}/close/``
     - ``closeChangeRequest``
   * - POST
     - ``/{changeRequestId}/reopen/``
     - ``reopenChangeRequest`` - branch requests only.

A decision is ``accept`` or ``reject`` for an *incoming* row and ``takeSource`` or ``takeTarget`` for a *conflict*
row. A typical client reads the schema changes, posts the schema decisions to ``analysis``, pages through
``changes`` with the returned ``analysisId``, calls ``validate``, and finally calls ``complete`` with all decisions.
An ``analysisId`` is kept for a few minutes; when it has expired, post the analysis again.

Every change to a request, and every new commit on the source or target branch of an open request, raises a
``ChangeRequestChangedNotification`` carrying only identifiers: the request id and number, both branch ids, and the
head the event moved. Clients read the request again to see what changed.

----

In the Web Application
----------------------

- **Change Requests** in the side navigation lists the requests of the project, open ones by default. The **Filter**
  menu narrows the list by state (including *archived*, which means merged or closed), author, branch and time.
- **Create Change Request...** is offered on that page, on **Project Settings - Branches** (for the whole project and
  for each branch), and in the **Actions** menu of the change history. The dialog asks for the source and target
  branches, a title and a description. With **Complete if no conflicts**, the request is completed at once accepting
  every change; a request with conflicts, schema deletions or validation errors stays open for review instead.
- A request page has a **Summary** tab and, while the request is open, a review tab. The review tab is labeled
  *Conflicts* while conflicts exist and *Changes* otherwise, and shows each change side by side with its decision.
  Decisions are kept in the browser session until the request is completed.
- When a branch moves during a review, the page says so and offers to review again.
- In the **Import Data** wizard, **Review the changes before applying them** opens the import as a proposal instead
  of applying it, and takes you to its page. A proposal that has expired shows a notice to import the file again.

See also
--------

- :doc:`Workspaces, Projects, and Branches <workspaces_and_projects>`
- :doc:`Roles and Permissions <permission_and_roles>`
- :doc:`REST API <rest>`
- :doc:`Patch and Diff <../advanced/patch_diff>`
