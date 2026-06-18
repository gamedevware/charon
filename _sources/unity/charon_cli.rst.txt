CharonCli Overview
==================

The `CharonCli <https://github.com/gamedevware/charon-unity3d/blob/master/src/GameDevWare.Charon.Unity/Packages/com.gamedevware.charon/Editor/Cli/CharonCli.cs>`_ class provides a convenient interface for running ``dotnet charon`` command-line operations. It simplifies interactions with the Charon tool, enabling developers to manage game data, automate workflows, and integrate with Unity projects. Below is an overview of its methods grouped by purpose.

Game Data Management
--------------------

- **InitGameDataAsync**: Initializes a GameData file.
- **CreateDocumentAsync**: Creates a document in the specified GameData URL.
- **UpdateDocumentAsync**: Updates a document in the specified GameData URL.
- **DeleteDocumentAsync**: Deletes a document in the specified GameData URL (by document or ID).
- **FindDocumentAsync**: Finds a document in the specified GameData URL by ID.
- **ListDocumentsAsync**: Lists documents in the specified GameData URL with optional filters and sorting.

Import and Export
-----------------

- **ImportAsync**: Imports documents grouped by schema into a specified GameData URL.
- **ImportFromFileAsync**: Imports documents from a file into a specified GameData URL.
- **ExportAsync**: Exports documents from a GameData URL.
- **ExportToFileAsync**: Exports documents from a GameData URL to a file.

Localization (I18N)
-------------------

- **I18NImportAsync**: Imports translated documents grouped by schema into a specified GameData URL.
- **I18NImportFromFileAsync**: Imports translated documents from a file into a specified GameData URL.
- **I18NExportAsync**: Exports documents for localization from a GameData URL.
- **I18NExportToFileAsync**: Exports documents for localization from a GameData URL to a file.
- **I18NAddLanguageAsync**: Adds translation languages to a GameData URL.

Patching and Backup
-------------------

- **CreatePatchAsync**: Compares documents in two GameData URLs and creates a patch representing the difference.
- **CreatePatchToFileAsync**: Compares documents in two GameData URLs and saves the patch to a file.
- **ApplyPatchAsync**: Applies a patch to a specified GameData URL.
- **ApplyPatchFromFileAsync**: Applies a patch from a file to a specified GameData URL.
- **BackupAsync**: Backs up game data with all documents and metadata.
- **BackupToFileAsync**: Backs up game data to a file with all documents and metadata.
- **RestoreAsync**: Restores game data from a backup.
- **RestoreFromFileAsync**: Restores game data from a backup file.

Validation and Code Generation
------------------------------

- **ValidateAsync**: Validates all documents in a GameData URL and returns a report with issues.
- **GenerateCSharpCodeAsync**: Generates C# source code for loading game data into a game's runtime.
- **DumpTemplatesAsync**: Dumps T4 code generation templates into a specified directory.

Tool Utilities
--------------

- **GetVersionAsync**: Gets the version number of the Charon tool executable.
- **GetGameDataToolVersionAsync**: Gets the version of the Charon tool used to create a GameData URL.
- **RunCharonAsync**: Runs a specified command with the Charon tool.
- **RunT4Async**: Processes T4 templates using the ``dotnet-t4`` command-line tool.

See also
--------

- :doc:`Unity Plugin Overview <overview>`
- `CharonCli class <https://github.com/gamedevware/charon-unity3d/blob/master/src/GameDevWare.Charon.Unity/Packages/com.gamedevware.charon/Editor/Cli/CharonCli.cs>`_
- `Examples of CharonCli class <https://github.com/gamedevware/charon-unity3d/blob/master/src/GameDevWare.Charon.Unity/Assets/Editor/CharonExamples/CharonCliExamples.cs>`_
