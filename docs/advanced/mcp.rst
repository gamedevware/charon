MCP Server (AI Assistant Integration)
======================================

Charon ships a built-in `Model Context Protocol (MCP) <https://modelcontextprotocol.io/>`_ server that
lets AI assistants — Claude, Cursor, GitHub Copilot, Windsurf, Cline, Zed, and others — read and write game data directly.
The server communicates over **stdio** using the standard JSON-RPC MCP transport, so no network port
is opened and no extra infrastructure is required.

With the MCP server running, an AI assistant can:

- Discover and inspect schemas
- Query, create, update, and delete game data documents
- Import and export data in multiple formats
- Generate typed source code (C#, TypeScript, Unreal C++, Haxe)
- Manage localization (XLIFF / JSON round-trips)
- Compare and patch game data between two sources

.. contents:: On this page
   :local:
   :depth: 2

----

Prerequisites
-------------

Install .NET 8 or later and the ``dotnet-charon`` tool:

.. code-block:: bash

   dotnet tool install -g dotnet-charon

Verify the installation:

.. code-block:: bash

   charon VERSION

.. note::

   On **.NET SDK 10+** you can skip the install step and invoke the tool on demand
   with ``dnx dotnet-charon -- MCP``. The examples below assume ``charon`` is on
   ``PATH``; if you prefer ``dnx``, replace the ``command`` / ``args`` pair in each
   client config with ``"command": "dnx"`` and ``"args": ["dotnet-charon", "--", "MCP"]``.

----

Starting the MCP Server
-----------------------

Run the ``MCP`` verb with no additional arguments:

.. code-block:: bash

   charon MCP

The process stays running and communicates over **stdin / stdout**.
Do not write anything else to stdout while the server is active — the transport is
the raw MCP JSON-RPC stream and any extra output will corrupt the protocol.

All diagnostic logging should be going to a log file (see `Logging`_ below),
so it never interferes with the transport.

----

Logging
-------

Because stdout is reserved for the MCP transport, use the ``--log`` option to write
diagnostics to a file:

.. code-block:: bash

   charon MCP --log /tmp/charon-mcp.log

Pass ``--verbose`` to include debug-level messages:

.. code-block:: bash

   charon MCP --log /tmp/charon-mcp.log --verbose

Specifying ``--log con`` or ``--log out`` in MCP mode is silently ignored to protect
the transport.

----

Configuring AI Clients
-----------------------

Claude Desktop
^^^^^^^^^^^^^^

Add the following entry to your ``claude_desktop_config.json``
(usually at ``~/Library/Application Support/Claude/claude_desktop_config.json`` on macOS
or ``%APPDATA%\Claude\claude_desktop_config.json`` on Windows):

.. code-block:: json

   {
     "mcpServers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"]
       }
     }
   }

Restart Claude Desktop after editing the file.

Claude Code (CLI)
^^^^^^^^^^^^^^^^^

.. code-block:: bash

   claude mcp add --transport stdio charon -- charon MCP

Cursor
^^^^^^

Open **Settings → MCP → Add MCP Server** and fill in:

- **Command**: ``charon``
- **Arguments**: ``MCP``

VS Code (GitHub Copilot)
^^^^^^^^^^^^^^^^^^^^^^^^

Add to your workspace ``.vscode/mcp.json``:

.. code-block:: json

   {
     "servers": {
       "charon": {
         "type": "stdio",
         "command": "charon",
         "args": ["MCP"]
       }
     }
   }

Windsurf
^^^^^^^^

Add to ``~/.codeium/windsurf/mcp_config.json``
(or open **Windsurf Settings → Cascade → Model Context Protocol**):

.. code-block:: json

   {
     "mcpServers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"]
       }
     }
   }

JetBrains IDEs (Rider, IntelliJ IDEA, WebStorm, etc.)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Open **Settings → Tools → AI Assistant → Model Context Protocol (MCP)**, click **Add**,
and paste the following configuration:

.. code-block:: json

   {
     "mcpServers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"]
       }
     }
   }

.. note::
   MCP client support requires JetBrains AI Assistant plugin and IDE version 2025.1 or later.

Cline (VS Code Extension)
^^^^^^^^^^^^^^^^^^^^^^^^^^

Open the **MCP Servers** panel in Cline, click **Configure**, then **Configure MCP Servers**,
and add the following to ``cline_mcp_settings.json``:

.. code-block:: json

   {
     "mcpServers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"]
       }
     }
   }

Zed
^^^

Add to your Zed settings file (open with **Zed → Settings → Open Settings** or :kbd:`Cmd+,`):

.. code-block:: json

   {
     "context_servers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"]
       }
     }
   }

----

Authentication for Remote Sources
----------------------------------

When a tool's ``dataBase`` parameter points to a remote Charon service URL
(e.g. ``https://charon.live/view/data/MyGame/main``), set the ``CHARON_API_KEY``
environment variable before starting the server:

.. code-block:: bash

   export CHARON_API_KEY=your_api_key_here
   charon MCP

In client configuration files you can pass the variable directly.
Most clients (Claude Desktop, Windsurf, Cursor, Cline, JetBrains) use the same ``env`` block:

.. code-block:: json

   {
     "mcpServers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"],
         "env": {
           "CHARON_API_KEY": "your_api_key_here"
         }
       }
     }
   }

For **VS Code (GitHub Copilot)**, add the ``env`` field inside the server entry in ``.vscode/mcp.json``:

.. code-block:: json

   {
     "servers": {
       "charon": {
         "type": "stdio",
         "command": "charon",
         "args": ["MCP"],
         "env": {
           "CHARON_API_KEY": "your_api_key_here"
         }
       }
     }
   }

For **Zed**, add the ``env`` field inside your ``context_servers`` entry:

.. code-block:: json

   {
     "context_servers": {
       "charon": {
         "command": "charon",
         "args": ["MCP"],
         "env": {
           "CHARON_API_KEY": "your_api_key_here"
         }
       }
     }
   }

Local file sources do not require an API key.

----

Available Tools
---------------

Use the following command to inspect the MCP server:

.. code-block:: sh

    npx @modelcontextprotocol/inspector charon MCP

----

Limitations and Remote-Only Use Case
--------------------------------------

The built-in MCP server works with **local files** and with **remote Charon service URLs** that
are reachable from the machine running the ``charon`` process. The game data file is loaded
locally by the CLI tool.

If you need a **fully-remote** MCP setup where Charon itself runs as a cloud service and the
CLI is not installed on the AI client's machine, the MCP server cannot be used directly.
As a fallback, ``charon.live`` exposes its full API through an OpenAPI 3 specification:

.. code-block:: text

   https://charon.live/api/v1/open.api.server.yml

AI clients that support OpenAPI-based tool use (such as those using function-calling from
an OpenAPI schema) can configure that URL as an API tool source. Authentication is done
with a bearer token equal to your ``CHARON_API_KEY`` value.

.. seealso::

   - :doc:`/web/rest` — REST API reference for the ``charon.live`` service
   - :doc:`command_line` — full CLI reference, including all ``DATA`` and ``GENERATE`` verbs
   - :doc:`cicd` — using Charon in automated pipelines