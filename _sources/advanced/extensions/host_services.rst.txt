Host Services
=============

Extension code does not talk to Charon's server or its UI directly. It is handed a set of **services** by the
host, and reaches everything through them - reading and writing game data, opening dialogs and Charon's own
wizards, showing notifications, navigating, and persisting UI state between sessions.

Which object carries them depends on what the extension is:

.. list-table::
   :header-rows: 1
   :widths: 32 68

   * - Extension kind
     - Where the services are
   * - :doc:`Custom action <custom_actions>`
     - ``context.services`` on the action context
   * - :doc:`Custom page <custom_pages>`
     - ``context.services`` on the page context
   * - :doc:`Schema editor <implementing_schema_editor>`
     - ``documentControl.services``
   * - :doc:`Property editor <implementing_property_editor>`
     - ``getRootDocumentControl(valueControl).services``

The two sets overlap but are not identical: an action or a page gets the project-level services, a document gets
the document-level ones. Both are declared ``Partial`` - **the host populates only what makes sense in the
context, so check every field before use.**

.. code-block:: typescript

  const dialog = context.services.ui?.dialog;
  if (!dialog) {
      return;
  }

.. contents:: On this page
   :local:
   :depth: 2

----

What Each Context Carries
-------------------------

.. list-table::
   :header-rows: 1
   :widths: 30 35 35

   * - Service
     - Action / page context
     - Document control
   * - ``gameData``
     - yes
     - yes
   * - ``ui.dialog`` / ``ui.snackBar``
     - yes
     - yes
   * - ``ui.state``
     - scoped to the package
     - scoped to the document or its schema
   * - ``navigation``
     - yes
     - \-
   * - ``userService`` / ``projectService`` / ``workspaceService``
     - yes
     - \-
   * - ``undoRedo``
     - \-
     - yes
   * - ``validationProvider``
     - \-
     - yes
   * - ``translationLanguage``
     - \-
     - yes
   * - ``serverApiClient``
     - yes
     - yes

``serverApiClient`` is the raw HTTP client behind everything else. It is deliberately untyped and its surface is
not stable - use it only for something the typed services do not cover, and expect it to change.

.. note::
   ``services.uiState`` still exists next to ``services.ui.state`` and is the very same object, kept for
   packages written before ``ui`` was introduced. New code should use ``ui.state``.

----

Game Data
---------

``GameDataService`` is the project's data, as the server sees it - not the document currently open in a form.
Everything returns an observable.

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Method
     - Purpose
   * - ``getMetadata()``
     - The project's schemas and settings.
   * - ``list(schema, parameters?)``
     - Documents of a schema, with ``skip``, ``take``, ``query``, ``select``, ``filters``, ``sorters``, and
       ``path`` for sub-documents. Returns the documents, their metadata, and the total before paging.
   * - ``find(schema, property, value)``
     - One document by a unique property value.
   * - ``query(requests)``
     - Several such lookups in one round trip.
   * - ``bulkChange(schema, documents, importMode, validationOptions?, dryRun?)``
     - Create, update, or delete many documents of one schema.
   * - ``import(collections, importMode?, schemas?, languages?, validationOptions?, dryRun?)``
     - The same across several schemas at once, taking a whole game data document.
   * - ``export(exportMode?, schemas?, properties?, languages?)``
     - Read data out in one of the export modes.
   * - ``validate(validationOptions)``
     - Run :doc:`validation <../validation>` and get the errors per document.

``importMode`` is the same choice the :doc:`import wizard <../import_export>` offers -
``createAndUpdate``, ``create``, ``update``, ``safeUpdate``, ``replace``, ``delete``. ``exportMode`` likewise:
``normal``, ``publication``, ``localization``, ``extraction``.

.. tip::
   ``dryRun: true`` on ``bulkChange`` and ``import`` validates the whole change and reports what would happen
   without writing anything. Every result carries per-document ``errors``, so an extension can show the user
   what it is about to do before it does it.

Results carry a ``metadataHash`` and a ``revisionHash`` - the state of the schemas and of the data at the time of
the call. Comparing them across two calls is how an extension notices that someone else changed the project
underneath it.

----

Dialogs and Wizards
-------------------

``ui.dialog`` opens modals in the host's own chrome.

Progress
^^^^^^^^

``showProgress(options)`` returns a handle for a long operation - ``update(percent, message?, color?)``,
``setFaulted()``, and ``close(delayMs?)``. With ``cancellable: true`` the dialog can be dismissed and
``closedHandler(cancelled)`` fires. See :doc:`Custom Actions <custom_actions>` for the full pattern.

Your Own Dialog
^^^^^^^^^^^^^^^

``showCustom(selector, data?, options?)`` hosts a custom element your package registered, inside a Charon dialog:

.. code-block:: typescript

  const dialogRef = dialog.showCustom<MyResult>('ext-my-dialog', { itemId }, {
      title: 'Pick an item',
      width: '600px',
      disableClose: false,
  });
  const result = await firstValueFrom(dialogRef.afterClosed());

The element receives ``data`` and closes itself through ``dialogRef.close(result)``; ``afterClosed()`` emits
that result, or ``undefined`` when the dialog was dismissed.

``showCodeSnippet({ sourceCode })`` is a ready-made read-only viewer with copy-to-clipboard, for showing a
generated command line or a fragment of JSON.

Charon's Wizards
^^^^^^^^^^^^^^^^

An extension can open the editor's own wizards rather than reimplementing them. Each returns a promise that
resolves ``true`` when the wizard completed and ``false`` when it was cancelled:

.. list-table::
   :header-rows: 1
   :widths: 45 55

   * - Method
     - Opens
   * - ``showImportWizard(options?)``
     - :doc:`Import <../import_export>`, optionally pre-loaded with a file or text and a schema
   * - ``showExportWizard(options?)``
     - :doc:`Export <../import_export>`, optionally with a schema and format preselected
   * - ``showImportLocalizationWizard(options?)`` / ``showExportLocalizationWizard(options?)``
     - The :doc:`translation <../internationalization>` round trip
   * - ``showPublicationWizard(options?)``
     - :doc:`Publication <../../gamedata/publication>`
   * - ``showSourceCodeGenerationWizard(options?)``
     - :doc:`Source code generation <../../gamedata/generating_source_code>`
   * - ``showBackupWizard(options?)`` / ``showRestoreWizard(options?)``
     - :doc:`Backup and restore <../backup_restore>`

All of them take ``loadPreferences`` and ``savePreferences``, both defaulting to true - the wizard opens filled
in the way the user last left it, and remembers what they do this time. Pass ``false`` when the extension is
driving the wizard with its own values and should not disturb the user's saved choices.

----

Notifications
-------------

``ui.snackBar`` is the host's transient notification strip, in matched sets of three - ``loadStarted`` /
``loadSucceed`` / ``loadFailed(error)``, and the same for ``save``, ``reload``, and ``delete``. Using them keeps
an extension's feedback indistinguishable from the editor's own, including how errors are rendered.

----

Navigation
----------

``navigation`` moves around the editor without building URLs. Every method navigates immediately.

.. list-table::
   :header-rows: 1
   :widths: 45 55

   * - Method
     - Goes to
   * - ``dashboard()``
     - The project dashboard.
   * - ``settings(section?)``
     - Project settings - ``general``, ``backup``, ``publication``, ``source-code``, ``internationalization``,
       ``branches``, ``members``, ``extensions``, ``features``.
   * - ``documentCollection(schemaName)``
     - A :doc:`collection page <../../gamedata/filling_documents>`.
   * - ``documentForm(schemaName, id)``
     - A single :doc:`document form <../../gamedata/document_form>`.
   * - ``customPage(packageName, pageId, restOfRoute?, params?)``
     - A :doc:`custom page <custom_pages>` of any installed extension.
   * - ``errorPage(error?, retryRoute?)``
     - The generic error page.
   * - ``back()``
     - The previous entry in browser history.

----

Persisted UI State
------------------

``ui.state`` stores small pieces of state - a zoom level, a collapsed panel, a chosen layout - and gives them
back the next time the extension runs. On an action or page context it is scoped to the extension package; on a
document control it takes a scope first, ``'document'`` or ``'schema'``.

.. code-block:: typescript

  state.save('projectPersonal', { zoom, collapsed });
  const restored = state.load('projectPersonal');

The layer decides where the value lives and how far it travels. On load, the requested layer is checked first
and lower-priority layers after it, so a personal value shadows a shared one:

.. list-table::
   :header-rows: 1
   :widths: 28 72

   * - Layer
     - Stored in
   * - ``browserSession``
     - Session storage - gone when the tab closes.
   * - ``browserPersonal``
     - Local storage, this user.
   * - ``browserShared``
     - Local storage, everyone using this browser.
   * - ``projectPersonal``
     - The server, this user, this project.
   * - ``projectTeam``
     - The server, everyone in the project.
   * - ``workspacePersonal``
     - The server, this user, across the workspace.
   * - ``workspaceTeam``
     - The server, everyone in the workspace.
   * - ``default``
     - Fallback, lowest priority.

Use a ``browser*`` layer for view state nobody else cares about, and a ``*Team`` layer for something the whole
project should share - a canvas layout that everyone should see the same way, for instance. ``save`` with
``null`` clears the value.

----

Current User, Project, and Workspace
------------------------------------

``userService.currentUser$``, ``projectService.currentProject$``, ``projectService.currentBranch$``, and
``workspaceService.currentWorkspace$`` are observables of who and where. The project carries its
:doc:`branches <../../web/workspaces_and_projects>`, and the branch says whether it is the primary one - enough
for an extension to warn before writing to production data, or to label what it produces.

----

See also
--------

- :doc:`UI Extensions <overview>`
- :doc:`Custom Actions <custom_actions>`
- :doc:`Custom Pages <custom_pages>`
- :doc:`Implementing a Schema Editor <implementing_schema_editor>`
- :doc:`Implementing a Property Editor <implementing_property_editor>`
- :doc:`Importing and Exporting Data <../import_export>`
- :doc:`Validation <../validation>`
