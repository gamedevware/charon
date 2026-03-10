Server Edition
==============

The **Charon Server Edition** is the team collaboration layer built on top of the standalone
editor. It gives studios a shared, version-controlled game data repository that every
designer, developer, and QA engineer accesses through a browser — no local installation
required.

It is available as a hosted cloud service at `charon.live <https://charon.live>`_ or
self-hosted on your own infrastructure for studios with data-residency or security
requirements.

.. contents:: On this page
   :local:
   :depth: 2

----

Why Teams Need It
-----------------

The standalone editor is designed for a single user working locally. As soon as a second
designer touches the same data file, the team is managing conflicts in spreadsheets or
shared drives. The server edition eliminates that problem:

- **Single source of truth** — all designers edit the same live data; no more "who has
  the latest version?" questions.
- **Branch-based workflows** — feature branches let designers work in isolation and merge
  changes only when ready, the same way engineers use Git.
- **Full audit trail** — every data change is attributed to a user with a timestamp,
  satisfying compliance and post-mortem requirements.
- **Works with existing pipelines** — the CLI and REST API are the same as the standalone
  edition, so CI/CD scripts, engine plugins, and code generation workflows require no
  changes.

----

Feature Comparison
------------------

+-------------------------------------------+------------+--------+
| Feature                                   | Standalone | Server |
+===========================================+============+========+
| Game data editing UI                      | ✓          | ✓      |
+-------------------------------------------+------------+--------+
| CLI access (all DATA / GENERATE commands) | ✓          | ✓      |
+-------------------------------------------+------------+--------+
| Local file storage                        | ✓          | ✓      |
+-------------------------------------------+------------+--------+
| Multi-user real-time collaboration        |            | ✓      |
+-------------------------------------------+------------+--------+
| Workspaces, Projects, Branches            |            | ✓      |
+-------------------------------------------+------------+--------+
| Role-based access control                 |            | ✓      |
+-------------------------------------------+------------+--------+
| Enterprise SSO (OAuth2, SAML, AD)         |            | ✓      |
+-------------------------------------------+------------+--------+
| API key management                        |            | ✓      |
+-------------------------------------------+------------+--------+
| Audit logs (auth events, command traces)  |            | ✓      |
+-------------------------------------------+------------+--------+
| On-premises / private cloud deployment    |            | ✓      |
+-------------------------------------------+------------+--------+

----

Collaboration Model
-------------------

Game data is organised in a three-level hierarchy:
**Workspace → Project → Branch**.

Designers work on named branches (e.g. ``feature/new-enemies``) and merge changes to a
shared ``main`` branch using Charon's patch/diff tooling — a workflow familiar to any
engineer who uses Git, adapted for non-technical designers who never touch the terminal.

See :doc:`../web/workspaces_and_projects` for the full collaboration guide.

----

Authentication and Enterprise Integration
------------------------------------------

The server edition supports multiple identity models to fit into your studio's existing
infrastructure:

- **Email + password** with optional **TOTP two-factor authentication** — suitable for
  small teams or studios without a central directory.
- **OAuth2** — delegate authentication to any standards-compliant identity provider,
  including Google Workspace, GitHub, or an in-house IdP.
- **SAML 2.0 / Active Directory** — for enterprise studios that require single sign-on
  through their corporate directory. Users log in with their existing company credentials;
  no separate Charon account needed.
- **API keys** — generated per user for CLI and REST API access in automated pipelines.

Contact ``support@gamedevware.com`` to discuss SSO integration options for your studio.

----

Access Control
--------------

Fine-grained roles control what each team member can do within a project:
**Viewer, Editor, Designer, Administrator**.

See :doc:`../web/permission_and_roles` for the full role and permission matrix.

----

Deployment Options
------------------

Cloud (charon.live)
   The fastest way to get started. No infrastructure to manage. Game data is stored on
   `charon.live <https://charon.live>`_ servers. Suitable for teams without strict
   data-residency requirements.

On-premises / Private Cloud
   Deploy the server on your own infrastructure — on-premises servers, private cloud VPC,
   or an air-gapped environment. You retain full control over where game data is stored and
   who can reach the service. See :doc:`on_premises` for deployment guidance.

.. note::
   Files created by the server edition are fully compatible with the standalone CLI and
   engine plugins. Any branch can be downloaded at any time and opened locally — teams are
   never locked in to the hosted service.

----

See also
--------

- :doc:`../web/overview`
- :doc:`../web/workspaces_and_projects`
- :doc:`../web/permission_and_roles`
- :doc:`../web/rest`