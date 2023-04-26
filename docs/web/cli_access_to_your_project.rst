Overview
========

Charon provides a REST API and CLI for accessing and modifying game data. To access the API, you need to generate an API Key in the *API Keys* section of your *User Profile*.

With the API Key, you can easily integrate Charon into your existing game development workflow. For example, the API Key can be used to export game data from the web into a local GIT repository.

Step By Step
=============

To generate an API Key:

1. Navigate to the *API Keys* section and click on the *Generate API Key...* button.
2. Copy the generated *API Key*.
3. Use the *API Key* in the `Authenticate` header to access the REST API or in the `--credentials` parameter of the CLI.

See also
========

- `Command Line Interface (CLI) <../advanced/command_line.rst>`_
- `DATA EXPORT Command <../advanced/commands/data_export.rst>`_
- `DATA IMPORT Command <../advanced/commands/data_import.rst>`_
- `GENERATE CSHARPCODE Command <../advanced/commands/generate_csharp_code.rst>`_