
Charon - Game Data Editor
=========================

<img width="894" alt="dashboard" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/cover_github.png"/>  

[Documentation](https://gamedevware.github.io/charon/) [[PDF]](https://gamedevware.github.io/charon/pdf/documentation.pdf)   • [Discord](https://discord.gg/2quB5vXryd) • [Website](https://www.gamedevware.com/) • [Changelog](https://www.gamedevware.com/changelog) • [Issues](https://github.com/gamedevware/charon/issues)  
  
Plugins 
-------
  
[<img width="100" alt="unity" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_logo.svg"/>](https://gamedevware.github.io/charon/unity/overview.html)
[<img width="100" alt="unreal engine" src="https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unreal_engine_logo.svg"/>](https://gamedevware.github.io/charon/unreal_engine/overview.html)  

[[Unity Asset Store]](https://gamedevware.github.io/charon/unity/overview.html) [[Unity OpenUPM]](https://openupm.com/packages/com.gamedevware.charon/) [[Unreal Engine Marketplace]](https://gamedevware.github.io/charon/unreal_engine/overview.html)  

Standalone
----------

[How to start with custom game engine](https://gamedevware.github.io/charon/standalone/overview.html) → [C#](https://gamedevware.github.io/charon/gamedata/working_with_csharp_code_7_3.html) • [TypeScript](https://gamedevware.github.io/charon/gamedata/working_with_type_script_code.html) • [Haxe](https://gamedevware.github.io/charon/gamedata/working_with_haxe_code.html)  

Introduction
============

### 1. What is it?

**Charon** is a comprehensive data management ecosystem designed to handle static game data (such as item databases, character stats, and quest trees). It functions as both a **visual editor** and a **code generator**, bridging the gap between raw data and game engine implementation.

Charon is highly flexible and can be used across various environments:

* **Engine Plugins:** Native support for **[Unity](https://gamedevware.github.io/charon/unity/overview.html)** and **[Unreal Engine](https://gamedevware.github.io/charon/unreal_engine/overview.html)**.
* **[Web](https://gamedevware.github.io/charon/web/overview.html) & Standalone:** Accessible via browser or as a [standalone/CLI](https://gamedevware.github.io/charon/standalone/overview.html) application for custom pipelines.

### 2. Which problem does it solve?

Managing game data manually is often a fragile process involving messy spreadsheets and repetitive boilerplate code. Charon solves several key pain points:

* **Manual Coding Errors:** Automatically generates source code based on your data models, ensuring type safety and reducing "plumbing" work.
* **Workflow Fragmentation:** Provides a user-friendly interface for editing data directly within the engine or browser, so you don't have to constantly switch between tools.
* **Localization Complexity:** Simplifies multi-language support by managing translated text and allowing for easy loading/unloading of localized content.
* **Data Integrity:** Streamlines the modeling of complex entities like missions and character stats, ensuring the data structure remains consistent.

### 3. For whom?

Charon is built for collaborative game development teams:

* **Game Designers:** Can focus on balancing gameplay and writing content using a structured, intuitive interface without needing to touch raw code.
* **Developers:** Benefit from clean, automatically generated code and a robust pipeline that handles data serialization and localization out of the box.

## Why Charon over Spreadsheets?

Traditional spreadsheets become "brittle" as a game grows. Charon replaces flat files with a structured game database that handles the complexity for you:

* **Data Integrity:** Unlike spreadsheets, Charon enforces relationships between data (e.g., ensuring a "Quest" doesn't reference an "Item" that was deleted).
* **Scalability:** It hides the technical "noise" of raw JSON/XML, allowing you to manage thousands of entries without losing track of the big picture.
* **Type Safety:** By generating source code directly from your data, you eliminate the risk of typos or "magic strings" breaking your build.

---

## Pricing & Licensing

Charon is designed to be accessible for solo developers while providing enterprise features for large studios.

| Version | Features | Cost |
| --- | --- | --- |
| **Community** | Offline CLI, Unity/Unreal Plugins, Standalone App. | **Free** (Open License) |
| **Professional** | Collaborative Online Editor, Team Management, Cloud Hosting. | **Subscription** |

> **Note on Modding:** The free version can be distributed alongside your game, allowing your community to build mods using the same professional tools you used to create the game.

---

## Technical Architecture

Charon is built on **.NET 8** for maximum performance and cross-platform compatibility. It is a versatile tool that adapts to your environment:

* **Cross-Platform:** Runs natively on **Windows, macOS, and Linux**.
* **Headless or UI:** Can be used as a simple **Command-Line Tool (CLI)** for automated CRUD operations or as an **HTTP Server** that provides a rich web-based UI.
* **Deep Integration:** Native plugins for [Unity](https://gamedevware.github.io/charon/unity/overview.html) and [Unreal Engine](https://gamedevware.github.io/charon/unreal_engine/overview.html) provide a seamless experience directly within your game editor.

---

## Getting Started

### 1. Installation

To use the standalone version, ensure you have the [dotnet runtime](https://dotnet.microsoft.com/en-us/download) installed, then run:

```bash
dotnet tool install dotnet-charon --global  
```

### 2. The Workflow

Charon follows a logical 4-step cycle to get data from your head into your game engine.

1. **Initialize:** Create your data file using `charon INIT gamedata.json`.
2. **Edit:** Launch the editor by running `charon gamedata.json`. This opens a local web server and UI.
3. **Generate:** Use the built-in generator to create type-safe source code (C#, C++, etc.) for your specific engine.
4. **Integrate:** Import the generated code and the `gamedata.json` into your project. You can now access your data with full IntelliSense support.

---

## Browser-Based UI

The editor provides a clean, modern interface for managing even the most complex data structures.

| Dashboard | Document Collection |
| --- | --- |
| <img width="400" alt="dashboard" src="docs/assets/dashboard.png"/> | <img width="400" alt="document collection" src="docs/assets/document_collection.png"/> |

| Data Entry Form | Import Tools |
| --- | --- |
| <img width="400" alt="document form" src="docs/assets/document_form.png"/> | <img width="400" alt="import" src="docs/assets/documents_import.png"/> |


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

Haxe Code Example
=================
```haxe
import GameData;
import Formatters;
import haxe.io.Path;
sys.io.File;

var input = File.read("RpgGameData.gdjs"); // or .json
var options = new GameDataLoadOptions();
options.format = GameDataFormat.Json;
var gameData = new GameData(input, options);

var allHeroes = gameData.heroesAll.list // -> ReadOnlyArray<Hero>
var heroById = gameData.heroesAll.get("Arbalest"); // -> Hero
```

License
=======
* Generated Code - MIT  
* Plugins: 
  * Unreal Engine - MIT  
  * Unity - Unity Asset Store License  
* Charon - CC BY-ND - can freely use and can redistribute, as long as it is passed along unchanged and in whole.
