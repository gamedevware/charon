Generating Source Code
===========================

The process of generating source code allows game data to be used inside a game. This process involves specifying the language (e.g. C#) and various generation parameters/optimizations. It can be done from both the project's dashboard user interface and the command-line interface (CLI).

Using Project's Dashboard UI
-----------------------------

To generate source code from the dashboard, follow these steps:

1. Go to the dashboard of the project where you want to generate source code.
2. Click on the *Generate Source Code* button.
3. Choose the language you want to generate the source code in.
4. Specify any generation parameters required.
5. Click on the *Finish* button to initiate the process.
6. Download archive file with generated source code.

Using Command-Line Interface (CLI)
-----------------------------------

To generate source code from the CLI, follow these steps:

1. Open the command-line interface.
2. Navigate to the game data's directory.
3. Use the ``GENERATE <SOURCECODE>`` command to generate the source code, specifying the target language and any generation parameters require.

Example
--------

.. code-block:: bash

  Charon.exe GENERATE CSHARPCODE --dataBase "c:\my app\gamedata.json" --namespace "MyGame.Parameters" --outputDirectory "c:\my app\scripts"

- Use the ``--outputDirectory`` parameter to specify the location where generated files will be saved.
- Use the ``--namespace`` and  ``--gameDataClassName`` parameters to adjust the signature of generated classes.
- Use the ``--splitFiles`` parameter to generate multiple files instead of one large one.

Once the process is complete, the generated source code will be available at ``--outputDirectory``.

See also
--------

- :doc:`Publishing Game Data <publication>`
- :doc:`Working with Source Code (C# 4.0) <working_with_csharp_code_4_0>`
- :doc:`Working with Source Code (C# 7.3) <working_with_csharp_code_7_3>`
- :doc:`Working with Source Code (TypeScript) <working_with_type_script_code>`
- :doc:`Working with Source Code (UE C++) <working_with_uecpp_code_>`
- :doc:`Command Line Interface (CLI) <../advanced/command_line>`
- :doc:`GENERATE CSHARPCODE Command <../advanced/commands/generate_csharp_code>`
- :doc:`GENERATE TYPESCRIPTCODE Command <../advanced/commands/generate_typescript_code>`
- :doc:`GENERATE UECPP Command <../advanced/commands/generate_uecpp_code>`
