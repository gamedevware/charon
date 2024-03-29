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


See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE TYPESCRIPTCODE Command <../advanced/commands/generate_typescript_code>`