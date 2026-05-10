Working with Source Code (UE C++)
=================================

.. note::
   **Tier 1 Support:** The UE C++ code generator provides complete Tier 1 support. This includes full formula execution (interpreter), patching during load, and language idiomatic features.

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

Formulas are supported when the plugin has the ``CHARON_FEATURE_FORMULAS_V2=1`` compilation
constant enabled (available since plugin version 2025.2.x).

Each formula property in your schema generates a dedicated ``UObject`` subclass — for example
a property named ``LevelUpConditionsCheck`` with return type ``System.Boolean`` and one parameter
``stats`` of type ``UObject`` produces:

.. code-block:: cpp

  // Formula Signature: (UObject stats) -> System.Boolean
  UCLASS(BlueprintType)
  class ULevelUpConditionsCheckFormula : public UObject
  {
      GENERATED_BODY()
  public:
      UFUNCTION(BlueprintCallable)
      bool Invoke(UObject* Stats) const;
  };

The generated ``Invoke`` method is ``BlueprintCallable``, so it is usable both from C++ and
from Blueprint graphs without any additional work.

Calling a Formula
^^^^^^^^^^^^^^^^^

Formula properties are stored as ``UPROPERTY`` pointers on the owning document. Call
``Invoke`` with the required arguments to evaluate the expression:

.. code-block:: cpp

  UHeroStats* Stats; // context for level condition checks
  UHero* Hero = GameData->AllHeroes.FindRef(TEXT("hero_01"));
  if (Hero && Hero->LevelUpConditionsCheck)
  {
      // for example formula is: Stats.Experience >= this.Levels[Stats.Level].ExperienceToLevelUp
      // where `this` is a reference to the `UHero` document.
      bool bCheckResult = Hero->LevelUpConditionsCheck->Invoke(Stats /* UObject* Stats */);
  }

If the formula's expression tree is missing, or if evaluation fails at runtime, ``Invoke``
logs an error to the formula's dedicated log category and returns the default value for the
return type (e.g. ``false`` for ``bool``, ``0`` for numeric types).

Formula Scope
^^^^^^^^^^^^^

Every formula expression has two implicit identifiers available without a qualifier:

- ``this`` — the document instance that declares the formula property. For a formula property
  defined on the ``Hero`` schema, ``this`` refers to the ``UHero`` object being
  evaluated.
- ``GameData`` — the root ``UGameData`` instance, giving access to all other documents and
  settings.

Consider a ``Hero`` schema with a numeric property ``BaseDamage`` and a formula property
``DamageFormula`` with signature ``(int32 Multiplier) -> int32``. The formula expression
can reference ``this.BaseDamage`` directly:

.. code-block:: none

  this.BaseDamage * Multiplier

When ``Hero->DamageFormula->Invoke(/* Multiplier */ 5)`` is called on a ``Hero`` whose ``BaseDamage`` is ``10``, the expression
evaluates ``10 * 5`` and returns ``50``.

Formula Syntax
^^^^^^^^^^^^^^

Formula expressions use **C# 3.5 syntax** with several extensions:

- ``?.`` — null-conditional member access (``this.Target?.Health``)
- ``?[`` — null-conditional index access (``list?[0]``)
- ``??`` — null-coalescing operator (``value ?? 0``)
- ``**`` — exponentiation operator (``base ** exponent``)

The following C# features are **not supported**:

- Lambda expressions (``x => expr``) — see below.
- Generic type arguments (``SomeMethod<T>()``) — type arguments cannot be specified
  explicitly.

Member and method dispatch is **dynamic**: property and method names are resolved at
evaluation time against the actual ``UObject`` (or ``UStruct``) instance passed as an
argument. Any ``UObject`` that has an ``Invoke(...)``
``UFUNCTION`` is treated as a callable. This means type mismatches surface at runtime
rather than at compile time.

Supported value types are the standard Blueprint primitives (``bool``, ``int32``, ``int64``,
``float``, ``double``, ``FString``, ``FText``, ``FTimespan``, ``FDateTime``) plus any
``UObject*`` and ``UStruct`` registered with Unreal Engine's reflection system.

Lambda Expressions
^^^^^^^^^^^^^^^^^^

Lambda expressions (``x => expr``, ``(x, y) => expr``) are parsed but are **not
implemented** — calling ``Invoke`` on a formula that contains a lambda returns the default
value and logs an ``UnsupportedExpression`` error.

Generated Code Contract
-----------------------

Document properties are declared as public ``UPROPERTY`` fields and collections as
``TArray<T*>`` / ``TMap<FString, T*>``. These are intentionally mutable for two reasons:

- **Blueprint compatibility** — Blueprint nodes read and write ``UPROPERTY`` fields
  directly; getter-only accessors are not reachable from Blueprints.
- **UObject lifecycle** — UE's garbage collector tracks references through ``UPROPERTY``
  metadata, which requires fields to be declared in the standard way.

Treat the loaded data as **logically read-only** even though the language does not
enforce it. Do not assign to, replace, or clear any field or collection on a document
obtained from a loaded ``UGameData`` instance — mutating loaded data produces undefined
behaviour and is not persisted to the source file.

.. note::
   To add derived or cached per-document state, subclass the relevant document class or
   keep a separate runtime data structure. Do not write to the generated fields after
   ``TryLoad`` returns.

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
