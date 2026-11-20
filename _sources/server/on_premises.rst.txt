On-Premises Deployment
=======================

The Charon server edition can be self-hosted on your own infrastructure. This gives teams
complete control over data residency, network access, and configuration, while providing the
same collaboration features as the hosted ``charon.live`` service.

.. contents:: On this page
   :local:
   :depth: 2

----

When to Self-Host
-----------------

Consider on-premises deployment when:

- **Data residency requirements** prohibit storing game data on third-party cloud services.
- **NDA or IP restrictions** require all data to stay within a private network.
- **Network isolation** - studios working on unannounced titles with air-gapped environments.
- **Cost at scale** - large teams where a self-hosted MongoDB instance is more economical than
  the hosted subscription.

----

Prerequisites
-------------

- A Linux, Windows, or macOS server with .NET 8 runtime installed.
- A running **MongoDB** instance (v6.0 or later recommended), accessible from the server.
- Optional: an SMTP server or email relay for transactional emails (registration, 2FA, etc.).
- Optional: a reverse proxy (nginx, Caddy, or similar) to provide HTTPS termination.

----

Data Compatibility
------------------

Files created by the server edition are **fully compatible** with the standalone CLI and
engine plugins. A branch can be downloaded at any time with ``DATA BACKUP`` and opened
locally:

.. code-block:: bash

   dnx dotnet-charon -- DATA BACKUP \
       --dataBase "https://charon.example.com/view/data/MyGame/main/" \
       --output myGame_main.zip \
       --credentials "$CHARON_API_KEY"

   unzip myGame_main.zip -d myGame/
   dnx dotnet-charon -- SERVER START myGame/gamedata.json --launchDefaultBrowser

This portability is a deliberate design decision - teams are never locked in to the hosted
service.

----

Safety Snapshots
----------------

.. versionadded:: vNext

Apart from the backups a workspace configures for itself, the server keeps a short-lived local copy of
every project so an operator can undo a destructive action. These copies are not shown to users and do
not count against a workspace's backup storage.

A snapshot holds the game data of every branch of one project. It is taken:

- before a project is restored from a backup;
- before a project or a branch is deleted;
- before a branch is rolled back to an earlier revision;
- on a schedule, for each project in use that changed since its last snapshot.

Snapshots are written to ``<Location>/<project id>/<UTC time>-<reason>-<suffix>.tar.zst``. They are
configured in the ``ArchiveStorage:SafetySnapshots`` section of ``appsettings.json``:

.. list-table::
   :header-rows: 1
   :widths: 25 25 50

   * - Setting
     - Default
     - Meaning
   * - ``IsEnabled``
     - ``true``
     - Turns safety snapshots on or off.
   * - ``Location``
     - ``./data/safety-snapshots``
     - Directory the snapshots are kept in.
   * - ``RetentionDays``
     - ``7``
     - A snapshot older than this is deleted.
   * - ``MaxTotalSize``
     - ``5368709120`` (5 GB)
     - Size limit, in bytes, for all snapshots on the server. Past it the oldest are deleted first.
   * - ``Schedule``
     - ``0 * * * *``
     - Cron schedule of the periodic snapshot.

A snapshot that cannot be written is logged as a warning and never blocks the action it precedes.

To recover a project, pick the snapshot taken before the damage and send the file as the raw body of
``POST /project/{projectId}/archives/upload-restore/``, as a workspace administrator. A snapshot restores
only over the project it was taken from, so the data of a deleted project has to be imported branch by
branch into a new one instead. The file is a Zstandard-compressed TAR of BSON documents, one
``snapshots/<branch id>/gamedata.bson`` per branch.

----

Backup Payload Cache
--------------------

.. versionadded:: vNext

Only the newest backup of a project is stored whole. When a new one is written, the one before it is
rewritten as a binary delta against it, which costs roughly what changed between the two. Restoring,
verifying or downloading an older backup rebuilds it from the newest one through the deltas between them,
on the spool volume.

To write that delta the server needs the previous backup, so it keeps the newest backup of each project
on local disk instead of downloading it again. The cache is configured in the
``ArchiveStorage:PayloadCache`` section of ``appsettings.json``:

.. list-table::
   :header-rows: 1
   :widths: 25 25 50

   * - Setting
     - Default
     - Meaning
   * - ``IsEnabled``
     - ``true``
     - Turns the cache on or off. With it off, every backup run downloads the previous backup.
   * - ``Location``
     - ``./data/archive-payload-cache``
     - Directory the cached backups are kept in, one subdirectory per project.
   * - ``RetentionDays``
     - ``3``
     - A cached backup older than this is deleted, so projects nobody edits stop using disk.
   * - ``MaxTotalSize``
     - ``5368709120`` (5 GB)
     - Size limit, in bytes, for all cached backups on the server. Past it the oldest are deleted first.

A backup whose uncompressed size passes 200 MB is logged as a warning, and past 300 MB as an error: the
delta encoder holds an index of the newest backup in memory, about one to two and a half times its size.

----

Contingency Plan
----------------

In the unlikely event that the Charon project is discontinued or key contributors become
unavailable, the full server source code and private Docker images will be published under
the **MIT license** by a designated successor. This guarantees that self-hosted deployments
can continue to be maintained by the community indefinitely.

The CLI and engine plugins rely on published NuGet packages, which are already public and
will remain unaffected regardless of the server's status.

----

Getting Help
------------

For licensing, installation, and support:

- Email: ``support@gamedevware.com``
- GitHub issues: `<https://github.com/gamedevware/charon/issues>`_

See also
--------

- :doc:`overview`
- :doc:`../web/workspaces_and_projects`
- :doc:`../web/permission_and_roles`
