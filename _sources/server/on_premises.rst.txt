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
- **Network isolation** — studios working on unannounced titles with air-gapped environments.
- **Cost at scale** — large teams where a self-hosted MongoDB instance is more economical than
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

   charon DATA BACKUP \
       --dataBase "https://charon.example.com/view/data/MyGame/main/" \
       --output myGame_main.zip \
       --credentials "$CHARON_API_KEY"

   unzip myGame_main.zip -d myGame/
   charon SERVER START myGame/gamedata.json --launchDefaultBrowser

This portability is a deliberate design decision — teams are never locked in to the hosted
service.

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
