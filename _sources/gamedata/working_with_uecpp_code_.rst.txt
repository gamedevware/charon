Working with Source Code (UE C++)
=================================

.. warning::
    The source code for Unreal Engine requires a `plugin <https://www.fab.com/listings/8cdfd7af-e1e9-4c97-b28d-d4b196767824>`_ to be installed to function. If you get compilation errors, make sure the plugin is `installed and enabled <../unreal_engine/overview>`_.

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

Extension of Generated Code
-------------------------

Customizing Metadata
^^^^^^^^^^^^^^^^^^^^^^

You can append additional or replace existing `macro <https://dev.epicgames.com/documentation/en-us/unreal-engine/objects-in-unreal-engine>`_ to the generated classes and their properties by modifying the ``Specification`` field of the related schema or property.

Metadata annotations are specified using the ``uecppAttribute`` key in the ``Specification`` string, which uses the ``application/x-www-form-urlencoded`` format.

To help construct the correct value, you can use a spreadsheet formula (e.g., in Excel or Google Sheets):

.. code-block:: none

  # Place your attribute in cell A1
  =TEXTJOIN("&", 1, IF(ISBLANK(A1), "", "&uecppAttribute=" & ENCODEURL(A1)))

Alternatively, use JavaScript to generate the encoded string:

.. code-block:: javascript

  const params = new URLSearchParams(); 
  params.append("uecppAttribute", "UPROPERTY(EditAnywhere, Meta = (Bitmask))"); 
  console.log(params.toString());
  // → uecppAttribute=UPROPERTY%28EditAnywhere%2C+Meta+%3D+%28Bitmask%29%29

After obtaining the encoded string, append it to the existing ``Specification`` value.

Example:

.. code-block:: none

  # Original Specification value:
  icon=material&group=Metadata

  # New attribute to add:
  uecppAttribute=UCLASS%28BlueprintType%29

  # Final Specification value:
  icon=material&group=Metadata&uecppAttribute=UCLASS%28BlueprintType%29

These metadata annotations will be emitted directly into the generated C++ code, attached to the appropriate class or property.


See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE UECPP Command <../advanced/commands/generate_uecpp_code>`
