Workspaces, Projects, and Branches
====================================

Charon organises collaborative game data in a three-level hierarchy.
Understanding this model is the foundation for managing teams, permissions,
and parallel design workflows.

.. contents:: On this page
   :local:
   :depth: 2

----

Hierarchy
---------

.. code-block::

   Workspace
   └── Project
       ├── Branch  (e.g. main)
       ├── Branch  (e.g. develop)
       └── Branch  (e.g. feature-loot-rework)

Workspace
^^^^^^^^^

A **Workspace** is the top-level organisational container for your studio or team.

- A workspace holds one or more projects.
- A workspace has one **Owner** and can have multiple **Administrators**.
- Deleting a workspace permanently removes all projects and branches inside it.

Project
^^^^^^^

A **Project** is a named container for a single game's data.

- Every project has at least one branch (``main`` by default).
- Projects can be shared by inviting team members; each invitation carries a
  specific :doc:`role <permission_and_roles>`.
- Projects can be cloned locally at any time — the resulting file is fully compatible
  with the standalone CLI.

Branch
^^^^^^

A **Branch** is a named, independently editable snapshot of game data inside a project.

- Branches are addressed in CLI calls via their URL:
  ``https://charon.live/view/data/<project>/<branch>/``
- Branches enable parallel development: designers work on feature branches, then merge
  changes back to ``main`` using Charon's :doc:`patch/diff <../advanced/patch_diff>` tooling.

----

Creating a Project
------------------

1. Sign in to `charon.live <https://charon.live>`_.
2. Open your workspace from the top navigation.
3. Click **New Project** and choose a name.
4. The project is created with a single ``main`` branch.

Inviting Collaborators
----------------------

1. Open the project.
2. Navigate to **Project Settings → Members**.
3. Enter the invitee's email and choose a role.
4. The invitee receives an email with a link to accept the invitation.

Available roles: Viewer, Editor, Designer, Administrator.
See :doc:`permission_and_roles` for the full permission matrix.

----

Working with Branches via CLI
------------------------------

All CLI ``DATA`` and ``GENERATE`` commands accept a branch URL as ``--dataBase``:

.. code-block:: bash

   # Export from the develop branch
   charon DATA EXPORT \
       --dataBase "https://charon.live/view/data/MyGame/develop/" \
       --output items.json --outputFormat json \
       --credentials "$CHARON_API_KEY"

   # Import into a feature branch
   charon DATA IMPORT \
       --dataBase "https://charon.live/view/data/MyGame/feature-loot/" \
       --input new_items.json --inputFormat json \
       --mode createAndUpdate \
       --credentials "$CHARON_API_KEY"

   # Generate code from main
   charon GENERATE CSHARPCODE \
       --dataBase "https://charon.live/view/data/MyGame/main/" \
       --namespace MyGame.Parameters \
       --outputDirectory ./Generated \
       --credentials "$CHARON_API_KEY"

----

Branch-based Release Pipeline
------------------------------

The recommended workflow is a linear promotion pipeline. Work flows in one
direction — from ``dev`` toward ``stable`` — by **pushing** (copying) the entire
branch into the next stage. A push replaces the destination branch completely;
it is not a merge.

.. code-block::

   dev ──── push ────→ staging ──── push ────→ stable ──── publish ──→ game
   (design)            (QA)                    (release)

How a push works
^^^^^^^^^^^^^^^^

A push copies the complete content of one branch into another, replacing the
destination entirely. There is no partial merge — every document in the
destination is overwritten.

Three ways to trigger a push are available:

**Web UI**
   Go to **Project Settings → Branches**, open the ``...`` menu next to the
   source branch, and choose **Push Branch…**. Select the target branch from
   the dropdown and confirm.

**REST API**
   Send a ``PUT`` request to the branch endpoint with the destination branch
   name in the request body:

   .. code-block:: bash

      curl -X PUT \
        "https://charon.live/api/project/{projectId}/branch/dev/" \
        -H "Authorization: Bearer $CHARON_API_KEY" \
        -H "Content-Type: application/json" \
        -d '{ "destinationBranchName": "staging" }'

   The operation is synchronous; a ``200`` response means the push completed
   successfully.

**CLI (BACKUP + RESTORE)**
   Use this approach when the push is part of a larger CLI script, or when
   you need to inspect the snapshot before promoting it:

   .. code-block:: bash

      # Step 1 – snapshot the source branch
      charon DATA BACKUP \
          --dataBase "https://charon.live/view/data/MyGame/dev/" \
          --output dev_snapshot.json \
          --credentials "$CHARON_API_KEY"

      # Step 2 – overwrite the destination branch with the snapshot
      charon DATA RESTORE \
          --dataBase "https://charon.live/view/data/MyGame/staging/" \
          --input dev_snapshot.json \
          --credentials "$CHARON_API_KEY"

Repeat the same steps to promote from ``staging`` to ``stable``.

.. warning::
   All three methods **replace all content** in the target branch. Double-check
   that you are targeting the correct branch before triggering a push.

Typical branch setup
^^^^^^^^^^^^^^^^^^^^

+----------------+------------------------------------------+---------------------------+
| Branch         | Purpose                                  | Who writes to it          |
+================+==========================================+===========================+
| ``dev``        | Active design and iteration              | Designers, game designers |
+----------------+------------------------------------------+---------------------------+
| ``staging``    | Integration and QA testing               | CI pipeline (push from    |
|                |                                          | ``dev``)                  |
+----------------+------------------------------------------+---------------------------+
| ``stable``     | Release-ready data; source for publish   | CI pipeline (push from    |
|                |                                          | ``staging``)              |
+----------------+------------------------------------------+---------------------------+

CI/CD pipeline example
^^^^^^^^^^^^^^^^^^^^^^

The REST API push is the simplest option for CI pipelines — a single HTTP
call with no intermediate files. The example below uses GitHub Actions, but
the same pattern works with any CI system.

.. code-block:: yaml

   # .github/workflows/promote.yml
   name: Promote dev → staging

   on:
     workflow_dispatch:   # triggered manually or on a schedule

   jobs:
     promote:
       runs-on: ubuntu-latest
       steps:
         - name: Push dev branch into staging
           run: |
             curl -X PUT \
               "https://charon.live/api/project/${{ secrets.CHARON_PROJECT_ID }}/branch/dev/" \
               -H "Authorization: Bearer ${{ secrets.CHARON_API_KEY }}" \
               -H "Content-Type: application/json" \
               -d '{ "destinationBranchName": "staging" }'

See :doc:`../advanced/cicd` for a full CI/CD walkthrough including validation
and publish steps.

----

Advanced: Patch-based Feature Merging
--------------------------------------

For teams that need to integrate isolated feature branches selectively — without
promoting the entire ``dev`` branch — Charon provides a patch/diff workflow.
A *patch* is a JSON file that captures only the differences between two branches.
It can be reviewed, stored in version control, and applied to any compatible
target.

.. code-block:: bash

   # Compute what changed between dev and a feature branch
   charon DATA CREATEPATCH \
       --dataBase1 "https://charon.live/view/data/MyGame/dev/" \
       --dataBase2 "https://charon.live/view/data/MyGame/feature-loot/" \
       --output loot.patch.json --credentials "$CHARON_API_KEY"

   # Apply only those changes to the target branch
   charon DATA APPLYPATCH \
       --dataBase "https://charon.live/view/data/MyGame/dev/" \
       --input loot.patch.json --credentials "$CHARON_API_KEY"

This approach requires a custom build pipeline and additional scripting to handle
conflict resolution. It is best suited for large teams with long-lived feature
branches or for shipping incremental live-service updates.

See :doc:`../advanced/patch_diff` for the full reference.

----

Cloning a Branch Locally
--------------------------

Any branch can be downloaded as a standalone file using ``DATA BACKUP``:

.. code-block:: bash

   charon DATA BACKUP \
       --dataBase "https://charon.live/view/data/MyGame/main/" \
       --output myGame_main.json \
       --credentials "$CHARON_API_KEY"

The resulting file can be opened with the standalone CLI:

.. code-block:: bash

   charon myGame_main.json

The standalone tool and the server share the same file format — full round-trip
compatibility is guaranteed.

See also
--------

- :doc:`overview`
- :doc:`permission_and_roles`
- :doc:`cli_access_to_web_project`
- :doc:`rest`
- :doc:`../advanced/backup_restore`
- :doc:`../advanced/cicd`
- :doc:`../advanced/patch_diff`