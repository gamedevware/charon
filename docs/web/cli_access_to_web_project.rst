CLI Access to Web Project
========

Charon provides a :doc:`REST API <rest>` and :doc:`CLI <../advanced/command_line>` for accessing and modifying game data. To access the API, users need to generate an ``API Key`` in the *API Keys* section of their *User Profile*.

With the API Key, Charon can easily be integrated into existing game development workflows. For example, the API Key can be used to export game data from the web into a local GIT repository

Step By Step
------------

To generate an API Key:

1. Navigate to the *API Keys* section and click on the *Generate API Key...* button.
2. Copy the generated ``API Key``.
3. Use the ``API Key`` in `the `Authenticate`` header to access the REST API or in the ``--credentials`` parameter of the CLI.

See also
--------

- :doc:`Command Line Interface (CLI) <../advanced/command_line>`
- :doc:`REST API <rest>`
- :doc:`DATA EXPORT Command <../advanced/commands/data_export>`
- :doc:`DATA IMPORT Command <../advanced/commands/data_import>`
- :doc:`GENERATE CSHARPCODE Command <../advanced/commands/generate_csharp_code>`