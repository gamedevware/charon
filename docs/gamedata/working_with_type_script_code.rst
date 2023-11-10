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
    format: Formatters.GameDataFormat.Json
  });
  
The content of ``gameDataFilePath`` could be `published <publication>` game data or original database file.  
  
Accessing Documents
-------------------

You can access your documents as a list:

.. code-block:: js

  var characters = gameData.charactersAll; // all characters from all documents -> readonly Character[]
  var characters = gameData.charactersRoot; // characters only from root collection -> readonly Character[]

Or you can access specific documents by their ``Id`` or ``Unique`` properties:

.. code-block:: js

  var character = gameData.charactersAll.find(characterId); // -> Character | undefined
  var character = gameData.charactersAll.withOtherKey('Name').find(characterName); // -> Character | undefined

``Settings`` schemas are accessed by name:

.. code-block:: js

  var resetTime = gameData.lootSettings.resetTime; // -> TimeSpan
  
Formulas
--------

Formulas inherit the ``Function`` type and can be invoked as-is or with ``invoke`` method:

.. code-block:: js

  var reward = gameData.lootSettings.rewardFormula()  // -> number
  // or
  var reward = gameData.lootSettings.rewardFormula.invoke()  // -> number

Formula's parameters are passed as arguments of ``invoke`` method.

See also
--------

- :doc:`Generating Source Code <generating_source_code>`