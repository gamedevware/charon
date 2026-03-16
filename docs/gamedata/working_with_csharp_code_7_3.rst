Working with Source Code (C# 7.3)
=================================

Accessing game data during runtime is possible by utilizing the generated source code.

This section provides examples using default class names, but it is possible to customize class names during the source code generation process. Additionally, this customization allows to avoid naming collisions with existing code.

Loading Game Data
-----------------

The following C# code creates ``GameData`` class and loads your game data into memory.

.. code-block:: csharp
  
  using System.IO;
  
  var fileStream = File.OpenRead("RpgGameData.gdjs"); // or .json
  var gameData = new GameData(fileStream, new Formatters.GameDataLoadOptions { 
    Format = Formatters.Format.Json,
    // Patches = new [] { patchStream1, patchStream2, ... }
  });
  fileStream.Dispose();

The file ``RpgGameData.gdjs`` could be :doc:`published <publication>` game data or original database file (.gdjs or .gdmp).  
  
Accessing Documents
-------------------

You can access your documents as a list:

.. code-block:: csharp

  var allHeroes = gameData.AllHeroes.AsList // -> IReadOnlyList<Hero>
  var heroes = gameData.Heroes.AsList // -> IReadOnlyList<Hero>

Or you can access specific documents by their ``Id`` or *Unique* properties:

.. code-block:: csharp

  var heroById = gameData.AllHeroes.Get(heroId); // -> Hero
  var heroByName = gameData.AllHeroes.ByName().Get(heroName); // -> Hero

``Settings`` schemas are accessed by name:

.. code-block:: csharp

  var startingHeroes = gameData.StartingSet.Heroes; // -> IReadOnlyList<Hero>
  
Formulas
--------

Each formula property in your schema generates a dedicated ``partial class`` — for example
a property named ``LevelUpConditionsCheck`` with return type ``bool`` and one parameter
``stats`` of type ``HeroStats`` produces:

.. code-block:: csharp

  // Formula Signature: (HeroStats stats) -> bool
  public partial class LevelUpConditionsCheckFormula
  {
      public bool Invoke(HeroStats stats);
  }

Calling a Formula
^^^^^^^^^^^^^^^^^

Formula properties are stored as read-only properties on the owning document. Call
``Invoke`` with the required arguments to evaluate the expression:

.. code-block:: csharp

  var hero = gameData.AllHeroes.Get("hero_01");
  if (hero?.LevelUpConditionsCheck != null)
  {
      // formula: stats.Experience >= this.Levels[stats.Level].ExperienceToLevelUp
      // where `this` is a reference to the Hero document
      bool result = hero.LevelUpConditionsCheck.Invoke(heroStats);
  }

If evaluation or compilation fails, ``Invoke`` throws ``FormulaException`` with
a message describing the failure and the formula expression that caused it.

Formula Scope
^^^^^^^^^^^^^

Every formula expression has two implicit identifiers available without a qualifier:

- ``this`` — the document instance that declares the formula property. For a formula property
  defined on the ``Hero`` schema, ``this`` refers to the ``Hero`` object being evaluated.
- ``GameData`` — the root ``GameData`` instance, giving access to all other documents and
  settings.

Consider a ``Hero`` schema with a numeric property ``BaseDamage`` and a formula property
``DamageFormula`` with signature ``(int multiplier) -> int``. The formula expression can
reference ``this.BaseDamage`` directly:

.. code-block:: none

  this.BaseDamage * multiplier

When ``hero.DamageFormula.Invoke(/* multiplier */ 5)`` is called on a ``Hero`` whose
``BaseDamage`` is ``10``, the expression evaluates ``10 * 5`` and returns ``50``.

Formula Syntax
^^^^^^^^^^^^^^

Formula expressions use **C# 3.5 syntax** with several extensions:

- ``?.`` — null-conditional member access (``this.Target?.Health``)
- ``?[`` — null-conditional index access (``list?[0]``)
- ``??`` — null-coalescing operator (``value ?? 0``)
- ``**`` — exponentiation operator (``base ** exponent``)

Unlike the UE C++ generator, **lambda expressions and explicit generic type arguments are
fully supported**:

.. code-block:: none

  items.Where(x => x.Active).Sum(x => x.Value)

Member and method dispatch is **dynamic**: property and method names are resolved at
evaluation time against the actual object instance. This means type mismatches surface at
runtime (as an ``FormulaException``) rather than at compile time.

Supported value types are the standard .NET primitives (``bool``, ``int``, ``long``,
``float``, ``double``, ``string``, ``DateTime``, ``TimeSpan``) plus any type explicitly
registered in the formula's known-types list via the ``Specification`` field of the schema
property.

Generated Code Contract
-----------------------

The generated C# API is **read-only by design**:

- Document classes expose only public *getters* — there are no public property setters.
- Collections are typed as ``IReadOnlyList<T>`` or ``IReadOnlyDictionary<TKey, TValue>``.
- After the ``GameData`` constructor returns, all documents and collections are **frozen**. Attempting to modify internal state via reflection or unsafe casts will corrupt the object graph.
- Some properties — notably resolved cross-document references and formula results — are computed lazily on first access and cached internally. This is an implementation detail; the observable value never changes after load.

The intended usage pattern is: **load once, read many times, never write**.

.. note::
   Do not assign to, replace, or clear any collection or document property obtained from
   ``GameData`` or its documents. To add computed or derived data, extend the generated
   classes with :ref:`partial classes <partial-classes>` instead.

Extension of Generated Code
-------------------------

.. _partial-classes:

Partial Classes and Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^
When generating source code for game data, the resulting C# classes are declared as `partial <https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/partial-classes-and-methods>`_. This means that the classes can be extended by the programmer to add custom functionality.

For example, let's say that you have generated a ``GameData`` class for your game data. This class contains properties and methods for accessing and manipulating the data. However, you want to add some custom functionality to this class, such as a method for getting specific documents by criteria.

To do this, you can create a new C# file and declare a partial class with the same name as the generated ``GameData`` class. You can then define your custom method in this class, and it will be merged with the generated class at compile time.

Here is an example of how this could look:

.. code-block:: csharp

  // should be in same namespace as generated GameData class
  public partial class GameData {
  
      public IEnumerable<Hero> GetReligiousHeroes() {
          return this.AllHeroes.AsList.Where(hero => hero.Religious);
      }
  
  }

In this example, the ``GameData`` class is declared as partial, and two partial classes are defined with the same name: one generated by the source code generation process and one containing custom code added by the programmer.

By using partial classes in this way, you can extend the functionality of the generated classes without modifying the generated code directly. This allows you to keep your custom code separate from the generated code, making it easier to maintain and update your game data classes over time.

There is also extension point on ``GameData`` class:

.. code-block:: csharp

  partial void OnInitialize(); // Called after loading and prepping all data.

Customizing Attributes
^^^^^^^^^^^^^^^^^^^^^^

You can append additional `C# Attributes <https://learn.microsoft.com/en-us/dotnet/csharp/advanced-topics/reflection-and-attributes/>`_ to the generated classes and their properties by modifying the ``Specification`` field of the related schema or property.

Attributes are specified using the ``csAttribute`` key in the ``Specification`` string, which uses the ``application/x-www-form-urlencoded`` format.

To help construct the correct value, you can use a spreadsheet formula (e.g., in Excel or Google Sheets):

.. code-block:: none

  # Place your attribute in cell A1
  =TEXTJOIN("&", 1, IF(ISBLANK(A1), "", "&csAttribute=" & ENCODEURL(A1)))

Alternatively, use JavaScript to generate the encoded string:

.. code-block:: javascript

  const params = new URLSearchParams(); 
  params.append("csAttribute", "Obsolete(\"Value is obsolete, do not use\")"); 
  console.log(params.toString());
  // → csAttribute=Obsolete%28%22Value%20is%20obsolete%2C%20do%20not%20use%22%29

After obtaining the encoded string, append it to the existing ``Specification`` value.

Example:

.. code-block:: none

  # Original Specification value:
  icon=material&group=Metadata

  # New attribute to add:
  csAttribute=Obsolete%28%22Value%20is%20obsolete%2C%20do%20not%20use%22%29

  # Final Specification value:
  icon=material&group=Metadata&csAttribute=Obsolete%28%22Value%20is%20obsolete%2C%20do%20not%20use%22%29

You can add multiple attributes by including multiple ``csAttribute`` keys:

.. code-block:: none

  csAttribute=Serializable&csAttribute=DebuggerDisplay%28%22Id%3D%7BId%7D%22%29

These attributes will be emitted directly into the generated C# code, attached to the appropriate class or property.

See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE CSHARPCODE Command <../advanced/commands/generate_csharp_code>`