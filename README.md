
Charon - Game Data Editor
=========================
![NuGet Version](https://img.shields.io/nuget/v/GameDevWare.Charon)

<img width="894" alt="dashboard" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/cover_github.png"/>  

[Documentation](https://gamedevware.github.io/charon/) • [Discord](https://discord.gg/2quB5vXryd) • [Website](https://www.gamedevware.com/) • [Changelog](https://www.gamedevware.com/changelog) • [Issues](https://github.com/gamedevware/charon/issues)  
  
Plugins 
-------
  
[<img width="100" alt="unity" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_logo.svg"/>](https://gamedevware.github.io/charon/unity/overview.html)
[<img width="100" alt="unreal engine" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unreal_engine_logo.svg"/>](https://gamedevware.github.io/charon/unreal_engine/overview.html)  

[Unity](https://gamedevware.github.io/charon/unity/overview.html) [Unreal Engine](https://gamedevware.github.io/charon/unreal_engine/overview.html)  

Standalone
----------

[How to start with custom game engine](https://gamedevware.github.io/charon/standalone/overview.html) → [C#](https://gamedevware.github.io/charon/gamedata/working_with_csharp_code_7_3.html) • [TypeScript](https://gamedevware.github.io/charon/gamedata/working_with_type_script_code.html)  

Summary
=======

Charon is a powerful game development tool that streamlines the game development process. 
It provides a structured approach to designing and modeling game data, with automatic source code generation that reduces the load on programmers and eliminates human errors. 
Charon also offers support for working with text in multiple languages, with easy loading and unloading of translated text. 

With Charon, game developers can focus on creating engaging gameplay experiences without worrying about the technical details of managing game data. 
It is available in three deployment variants, including a [standalone/offline](https://gamedevware.github.io/charon/standalone/overview.html) application, [web](https://gamedevware.github.io/charon/web/overview.html) application, [Unity](https://gamedevware.github.io/charon/unity/overview.html) and [Unreal Engine](https://gamedevware.github.io/charon/unreal_engine/overview.html) plugins.  

What is Charon
==============
It is a .NET 4.6 console application that can be used as a command-line tool for performing CRUD operations with your game data, or as an HTTP Server to provide a UI for modeling and editing your game data. There are plugins for Unity and Unreal Engine that provide a more integrated experience while using Charon.  
As with any .NET application, it can be launched as is on Windows and via Mono on macOS and Linux.

How it works
============
You create an empty `gamedata.json` file when launching the Charon.exe application, which acts as an HTTP server. You edit your game data in the UI, then generate source code for your game engine. With this source code, you load `gamedata.json` into your game and use it in a safe and structured manner.

<img width="894" alt="scheme" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/how_it_works.png"/>  

If you use plugins for Unity or Unreal Engine, it is a little bit easier than shown in the diagram.

Editor's UI
===========

<img width="894" alt="screenshot" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png"/>  

C# Code Example
===============
```cs
using System.IO;

using var fileStream = File.OpenRead("gamedata.json"); // or .gdjs
var gameData = new GameData(fileStream, new Formatters.GameDataLoadOptions { Format = Formatters.Format.Json });

var heroes = gameData.Heroes.AsList // -> IReadOnlyList<Hero>
// or
var heroById = gameData.AllHeroes.Find("Arbalest"); // -> Hero | null
```

C++ Code Example
================
```cpp
#include "UGameData.h"

TSoftObjectPtr<UGameData> GameDataPtr = TEXT("/Game/Content/GameData");
auto GameData = GameDataPtr.LoadSynchronous(); // -> UGameData*

auto Heroes = GameData->Heroes; // -> TMap<FString,UHero*>
auto HeroById = GameData->Heroes.Find(TEXT("Arbalest")); // -> UHero**
```

TypeScript Code Example
=======================
```ts
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

let heroes = gameData.heroes; // -> readonly Hero[]
let hero = gameData.heroesAll.find("Arbalest"); // -> Hero | undefined
```

License
=======
* Generated Code - MIT  
* Plugins: 
  * Unreal Engine - MIT  
  * Unity - Unity Asset Store License  
* Charon - CC BY-ND - can freely use and can redistribute, as long as it is passed along unchanged and in whole.
