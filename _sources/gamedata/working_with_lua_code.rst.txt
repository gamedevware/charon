Working with Source Code (Lua)
=============================

.. note::
   **Tier 3 Support:** The Lua code generator provides Tier 3 support. This includes basic game data class, schema types, enums, and JSON/Message Pack reading (via external table deserialization).

Accessing game data during runtime is possible by utilizing the generated source code.

This section provides examples using default class names, but it is possible to customize class names during the source code generation process. Additionally, this customization allows to avoid naming collisions with existing code.

Loading Game Data
-----------------

The following Lua code creates ``GameData`` class and loads your game data into memory.

.. code-block:: lua
  
  local cjson = require("cjson")
  local GameData = require('game_data') -- if splitFiles = true, otherwise `require('game_data').gameData`

  -- Read file content (e.g., from 'gamedata.json')
  local file = io.open("gamedata.json", "r")
  local json_string = file:read("*a")
  file:close()

  local decodedTable = cjson.decode(json_string)
  local gameData = GameData.new(decodedTable) -- data should be deserialized into table before passed into GameData
  
The file ``gamedata.json`` could be :doc:`published <publication>` game data or original database file (.gdjs or .gdmp).  
  
Accessing Documents
-------------------

You can access your documents as a map/table by ID:

.. code-block:: lua

  local heroes = gameData:getHeroes() -- heroes only from root collection by id -> table<any, Hero>

Or you can access specific documents by their ``Id`` or *Unique* properties:

.. code-block:: lua

  local hero = heroes[heroId] -- -> Hero | nil

``Settings`` schemas are accessed via their getter:

.. code-block:: lua

  local lootSettings = gameData:getLootSettings() -- -> LootSetting | nil
  local resetTime = lootSettings.resetTime -- -> number
  
Formulas
--------

Formulas are currently not supported.

See also
--------

- :doc:`Generating Source Code <generating_source_code>`
- :doc:`GENERATE LUA Command <../advanced/commands/generate_lua_code>`
