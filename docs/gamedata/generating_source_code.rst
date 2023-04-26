Overview
========

The "Generate Source Code" process generates source code for game data, allowing it to be used inside a game. This process involves specifying the language (e.g. C#) and various generation parameters. It can be done from both the project's dashboard user interface and the command-line interface (CLI).

-----------------------------
Using Project's Dashboard UI
-----------------------------


To generate source code from the dashboard, follow these steps:

    Go to the dashboard of the project where you want to generate source code.
    Click on the "Generate Source Code" button.
    Choose the language you want to generate the source code in.
    Specify any generation parameters required.
    Click on the "Generate" button to start the process.

-----------------------------------
Using Command-Line Interface (CLI)
-----------------------------------

To generate source code from the CLI, follow these steps:

1. Open the command-line interface.
2. Navigate to the game data's directory.
3. Use the ``GENERATE CSHARPCODE`` command to generate the source code, specifying the target language and any generation parameters require.

Example
--------

.. code-block:: bash

  Charon.exe GENERATE CSHARPCODE --dataBase "c:\my app\gamedata.json" --namespace "MyGame.Parameters" --outputDirectory "c:\my app\scripts"

- Use the ``--outputDirectory`` parameter to specify the location where generated files will be saved.
- Use the ``--namespace`` and  ``--gameDataClassName`` parameters to adjust the signature of generated classes.
- Use the ``--splitFiles`` parameter to generate multiple files instead of one large one.

Once the process is complete, the generated source code will be available at ``--outputDirectory``.

See also
========

- `Command Line Interface (CLI) <../advanced/command_line.rst>`_
- `GENERATE CSHARPCODE Command <../advanced/commands/generate_csharp_code.rst>`_