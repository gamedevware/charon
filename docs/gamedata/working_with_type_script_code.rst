Working with Source Code (Type Script)
=============================

Accessing game data during runtime is possible by utilizing the generated source code.

This section provides examples using default class names, but it is possible to customize class names during the source code generation process. Additionally, this customization allows to avoid naming collisions with existing code.

Loading Game Data
-----------------

The following Type Script code creates ``GameData`` class and loads your game data into memory.

.. code-block:: js

  import { GameData } from './game.data';
  import { Formatters } from './formatters';

  // Node.js
  import { readFileSync } from 'fs';
  const gameDataStream = readFileSync(gameDataFilePath);
  
  // Blob or File
  const gameDataStream = gameDataFileBlob.arrayBuffer();
  
  // XMLHttpRequest (XHR)
  // gameDataRequest.responseType -> "arraybuffer"
  const gameDataStream = gameDataRequest.response;
  
  const gameData = new GameData(gameDataStream, {
    format: Formatters.GameDataFormat.Json,
    // patches: [patchStream1, patchStream2, ...]
  });
  
The content of ``gameDataStream`` could be :doc:`published <publication>` game data or original database file (.gdjs or .gdmp).  
  
Accessing Documents
-------------------

You can access your documents as a list:

.. code-block:: js

  let heroes = gameData.heroesAll; // all heroes from all documents -> readonly Hero[]
  let heroes = gameData.heroes; // heroes only from root collection -> readonly Hero[]

Or you can access specific documents by their ``Id`` or *Unique* properties:

.. code-block:: js

  let hero = gameData.heroesAll.find(heroId); // -> Hero | undefined
  let hero = gameData.heroesAll.withOtherKey('Name').find(heroName); // -> Hero | undefined

``Settings`` schemas are accessed by name:

.. code-block:: js

  let resetTime = gameData.lootSettings.resetTime; // -> TimeSpan
  
Formulas
--------

Formulas inherit the ``Function`` type and can be invoked as-is or with ``invoke`` method:

.. code-block:: js

  var reward = gameData.lootSettings.rewardFormula()  // -> number
  // or
  var reward = gameData.lootSettings.rewardFormula.invoke()  // -> number

Formula's parameters are passed as arguments of ``invoke`` method.  

Any non-game data related types are imported from ```formula.known.types.ts``, which should be created by the developer and have all required types exported.
Here is an example of a ``formula.known.types.ts`` file:

.. code-block:: js
  
  import { MyFormulaContext } from '../my.formula.context';

  // example of MyFormulaContext type.
  export MyFormulaContext;

  // example of Assets.Scripts.CheckContext.  
  export namespace Assets.Scripts {
    export class CheckContext {
      myField: string;
    }
  }


Extension of Generated Code
-------------------------

Customizing Decorators
^^^^^^^^^^^^^^^^^^^^^^

You can append additional `TypeScript Decorators <https://www.typescriptlang.org/docs/handbook/decorators.html>`_ to the generated classes and their properties by modifying the ``Specification`` field of the related schema or property.

Decorators are specified using the ``tsAttribute`` key in the ``Specification`` string, which uses the ``application/x-www-form-urlencoded`` format.

To help construct the correct value, you can use a spreadsheet formula (e.g., in Excel or Google Sheets):

.. code-block:: none

  # Place your attribute in cell A1
  =TEXTJOIN("&", 1, IF(ISBLANK(A1), "", "&tsAttribute=" & ENCODEURL(A1)))

Alternatively, use JavaScript to generate the encoded string:

.. code-block:: javascript

  const params = new URLSearchParams(); 
  params.append("tsAttribute", "deprecated(\"Value is deprecated\")");
  console.log(params.toString());
  // → tsAttribute=deprecated%28%22Value+is+deprecated%22%29

After obtaining the encoded string, append it to the existing ``Specification`` value.

Example:

.. code-block:: none

  # Original Specification value:
  icon=material&group=Metadata

  # New attribute to add:
  tsAttribute=deprecated%28%22Value+is+deprecated%22%29

  # Final Specification value:
  icon=material&group=Metadata&tsAttribute=deprecated%28%22Value+is+deprecated%22%29

You can add multiple attributes by including multiple ``tsAttribute`` keys:

.. code-block:: none

  tsAttribute=@Input&tsAttribute=range%281%2C+2%29

These attributes will be emitted directly into the generated TypeScript code, attached to the appropriate class or property.


See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE TYPESCRIPTCODE Command <../advanced/commands/generate_typescript_code>`