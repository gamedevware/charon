Troubleshooting Common Issues
=============================

This page collects the most frequently reported problems and their solutions. Each section starts
with the symptom or the exact error message, followed by the cause and the fix.

If your problem is not listed here, check the :doc:`log files <logs>` for errors and
see `Nothing Helped?`_ below for support channels.

.. contents:: On this page
   :local:
   :depth: 1

----

Editor Fails to Launch or Gets Stuck Loading
--------------------------------------------

**Symptom:** The editor window (or browser tab) never finishes loading, or the launch fails with
a timeout error. Sometimes a retry succeeds.

Common causes and fixes, in order of likelihood:

1. **Large game data file exceeds the launch timeout.** The plugin waits a limited time
   (30 seconds by default) for the editor process to load the game data. For large files,
   increase the *Idle Close Timeout* in the Unity project settings:
   **Edit → Project Settings → Charon**.

2. **VPN or proxy software interferes with local connections.** The editor is a local web
   application served on ``localhost``. Some VPN clients and system-wide proxies intercept or
   block this traffic. Temporarily disable them and retry.

3. **A stale editor process is holding the port.** Restart the Unity/Unreal editor. If that does
   not help, restart the computer to clear orphaned processes.

4. **Unreal Engine plugin: the randomly chosen port is unavailable.** The editor picks a random
   local port on each launch, and sometimes that port is already taken or blocked by OS
   permissions. Simply close and reopen the Charon window - a new port is picked on the next
   launch. Check the *Output Log* console for error messages if the problem persists.

If the problem persists, collect the :doc:`log files <logs>` and repeat the launch with
verbose logging enabled.

----

Web UI Shows "Http failure response for api/v1/context/: 0 Unknown Error"
--------------------------------------------------------------------------

**Symptom:** The editor page opens but fails with the error above, while the same project may
work in another git branch or after a reboot.

This indicates that the browser could not reach the local editor process at all. Try in order:

1. Hard-refresh the page and clear the cache: :kbd:`Ctrl+F5` or :kbd:`Ctrl+Shift+R`.
2. Disable browser extensions (ad blockers and privacy tools are frequent offenders).
3. Disable VPN/proxy software.
4. Restart the Unity/Unreal editor, then the computer.

If the error reoccurs, save the :doc:`log files <logs>` from the failing session and send them to
support - this class of problem is hard to reproduce and logs are essential.

----

Blank Page or Extension Fails to Load
--------------------------------------

**Symptom:** The editor opens as a blank page, or an installed extension (custom document editor,
property editor) does not appear as an option in the UI.

1. Hard-refresh and clear the browser cache: :kbd:`Ctrl+F5` or :kbd:`Ctrl+Shift+R`.
2. Open the browser developer console (:kbd:`F12`) and check for errors. A crashed or blocking
   browser extension is often visible at the top of the console output.
3. Try a private/incognito window or another browser to rule out browser extensions.
4. For Charon extensions: open **Project Settings → Extensions** and verify the package
   downloaded successfully (hover over the status icon, click *Recheck* if needed).
5. Verify your browser is supported: **Chrome** released 2021 or later, **Firefox** released
   2023 or later. Other Chromium-based browsers (Edge, Opera, Brave...) should be a recent
   version.

----

Game Data File Is Corrupted After Version Control Operations
-------------------------------------------------------------

**Symptom:** After a merge, rebase, or branch switch, Charon reports that the game data file is
corrupted or is not valid JSON.

The file most likely contains unresolved merge conflict markers (``<<<<<<<``, ``=======``,
``>>>>>>>``). Charon detects **Git**, **Mercurial**, and **SVN** working copies and reloads the
game data on checkouts, but it does not detect merge conflicts inside the file - a file with
conflict markers is simply no longer valid JSON.

**Fix:**

- For **JSON** game data: resolve the conflict with your usual text merge tools, the same way as
  for source code.
- For **binary** formats (MessagePack): merging is not possible. Choose the correct side of the
  conflict entirely (``ours`` or ``theirs``) and re-apply the other side's changes in the editor.

.. note::

   JSON is the default storage format precisely because it can be diffed and merged in version
   control. Keep binary formats for publication output rather than for the editable source file.

----

Validation Errors on System Schemas (Schema, ProjectSettings, SchemaProperty)
------------------------------------------------------------------------------

**Symptom:** Every schema and property in the project shows validation errors such as an invalid
identifier, including freshly created schemas.

Charon stores the metadata that describes metadata (the ``Schema``, ``ProjectSettings``, and
``SchemaProperty`` system schemas) in the same file as your data. Hand-editing the game data
file can accidentally damage them, which breaks validation for everything defined on top.

.. warning::

   Never modify these system documents when editing the game data file manually:

   - ``Schema`` - id ``18d4bf318f3c49688087dbed``
   - ``ProjectSettings`` - id ``55a4f32faca22e191098f3d9``
   - ``SchemaProperty`` - id ``d40d8eb1a23248b69b252eea``

**Fix:** Create a new, empty game data file (e.g. via your engine plugin or ``charon INIT``),
open both files in a text editor, and copy the three system schema documents from the fresh file
into your damaged one, replacing the broken versions. Make a backup first.

----

".NET SDK is not installed" During Setup
-----------------------------------------

**Symptom:** The engine plugin fails to set up the game data editor and complains about a missing
.NET installation.

Charon is a .NET tool and requires the **.NET 8 SDK or later**. Download it from
`dotnet.microsoft.com <https://dotnet.microsoft.com/download>`_ and verify:

.. code-block:: bash

   dotnet --list-sdks

After installing the SDK, restart the Unity/Unreal editor. If the plugin still does not detect
it, restart the computer so the updated ``PATH`` is picked up.

----

Exported XLSX File Contains an "Errors" Sheet
----------------------------------------------

**Symptom:** A ``DATA EXPORT`` or localization export produces a spreadsheet that looks empty
except for a sheet named *Errors*.

The export failed and the error details were written into that sheet instead of the console.
Open the *Errors* sheet and read the message - it typically points to the exact document,
property, and reason.

----

Game Data Is Read-Only in the Web Editor
-----------------------------------------

**Symptom:** The online editor shows the project as read-only and design changes are rejected,
with a message about exceeded limits.

Your workspace has crossed one of its subscription limits. Go to
**Workspace Settings → Subscriptions** and check which limit is exceeded - *Projects*, *Members*,
or *Size*. Remove the excess or upgrade the plan; the read-only message disappears once the
workspace is back within limits.

----

Unreal Engine Compile Errors After an Engine Upgrade
-----------------------------------------------------

**Symptom:** After upgrading Unreal Engine, previously generated C++ code or the Charon plugin
fails to compile.

New Unreal Engine releases regularly change engine APIs, so support for a new UE version ships in
a Charon plugin update. The safe upgrade routine is:

1. **Wait** until the new UE version is officially supported (see the release #announcements channel on Discord or https://www.gamedevware.com/whats-new).
2. **Regenerate** the C++ source code while still on your current engine version - generated
   code is backward compatible.
3. **Upgrade** the engine and the Charon plugin together, then rebuild.

----

Import Regenerates IDs of Nested Documents
-------------------------------------------

**Symptom:** After importing data (e.g. a localization round-trip), embedded documents receive
new identifiers, which shows up as large diffs in version control.

The default import mode replaces embedded collections, recreating their documents. To update
existing documents in place:

- Pass ``--mode safeUpdate`` to :doc:`DATA IMPORT <commands/data_import>` - it prevents creation
  and deletion of nested documents.
- Or use :doc:`DATA I18N IMPORT <commands/data_i18n_import>` for localization round-trips - it is
  a specialized import that only touches translated text.

----

Nothing Helped?
---------------

If none of the above solves your problem, reach out directly:

- **Discord** - join the `Charon Discord server <https://discord.gg/2quB5vXryd>`_ and ask in
  the ``#issues`` channel. This is usually the fastest way to get help.
- **GitHub** - file a work item at
  `github.com/gamedevware/charon/issues <https://github.com/gamedevware/charon/issues>`_.
- **Email** - write to `support@gamedevware.com <mailto:support@gamedevware.com>`_.

Whichever channel you choose, attach the :doc:`log files <logs>` and mention your Charon
version, engine (Unity/Unreal/standalone/web), and operating system - it saves a round-trip.

----

See also
--------

- :doc:`Working with Logs <logs>`
- :doc:`Reset UI Preferences <reset_preferences>`
- :doc:`Merge Logic <merge_logic>`
- :doc:`Command Line Reference <command_line>`
