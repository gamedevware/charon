Working with Source Code (UE C++)
=================================

Accessing game data during runtime is possible by utilizing the generated source code.

This section provides examples using default class names, but it is possible to customize class names during the source code generation process. Additionally, this customization allows to avoid naming collisions with existing code.

Loading Game Data
-----------------

The following C++ code creates ``UGameData`` class and loads your game data into memory.

.. code-block:: cpp
  
  IFileManager& FileManager = IFileManager::Get();

  const FString GameDataFilePath = TEXT("./RpgGameData.gdjs");  // or .json
  const TUniquePtr<FArchive> GameDataStream = TUniquePtr<FArchive>(FileManager.CreateFileReader(*GameDataFilePath, EFileRead::FILEREAD_None));
	
  UGameData* GameData = NewObject<UGameData>();

  FGameDataLoadOptions Options;
  Options.Format = EGameDataFormat::Json;
  // Options.Patches.Add(PatchStream1);
  // Options.Patches.Add(PatchStream2);
  // ...
	
  if (!GameData->TryLoad(GameDataStream.Get(), Options))
  {
    // Handle failure
  }

The file ``RpgGameData.gdjs`` could be :doc:`published <publication>` game data or original database file (.gdjs or .gdmp).  
  
Accessing Documents
-------------------

You can access your documents as a list:

.. code-block:: cpp

  auto AllHeroes = GameData->AllHeroes // -> TMap<string, UHero>
  auto Heroes = GameData->Heroes // -> TMap<string, UHero>

``Settings`` schemas are accessed by name:

.. code-block:: cpp

  auto StartingHeroes = GameData->StartingSet.Heroes; // -> TMap<string, UHero>
  
Formulas
--------

Formulas are currently not supported.

See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE UECPP Command <../advanced/commands/generate_uecpp_code>`
