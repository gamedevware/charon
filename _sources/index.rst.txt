Overview
========

Charon is a powerful data-driven game development tool designed to streamline the creation and management of static game data within your game. 
It allows both developers and game designers to efficiently model and edit game entities such as characters, items, missions, quests, and more, directly within the Unity/Unreal Engine/Browser environment. 
Charon simplifies the process of data manipulation, offering a user-friendly interface and automatic source code generation, which significantly reduces development time and minimizes manual coding errors.
Charon also offers support for working with text in multiple languages, with easy loading and unloading of translated text. 

With Charon, game developers can focus on creating engaging gameplay experiences without worrying about the technical details of managing game data. It is available in three deployment variants, including a :doc:`standalone  <standalone/overview>` application, :doc:`web <web/overview>` application, :doc:`Unity <unity/overview>` plugin and :doc:`Unreal Engine </unreal_engine/overview>` plugin.  
  
**TLDR** Charon is an in-game database for your game, replacing spreadsheets or config files.  

Why Choose Charon?
------------------

Charon replaces traditional spreadsheets or config files with an in-game database, 
offering a structured and efficient way to manage game data. It allows developers to focus on creating engaging gameplay 
experiences without worrying about the technical details of data management.

Is It Free?
-----------

The offline version, :doc:`CLI <advanced/command_line>` and plugins are completely free and have no restrictions. 
They are distributed under a free license and allow you to distribute tools along with the game for modding games.  

The online version, which allows working in large teams on shared game data, requires a subscription.

What is Charon
--------------

It is a .NET 8 console application that can be used as a :doc:`command-line <advanced/command_line>` tool for performing CRUD operations with your game data, or as an HTTP Server to provide a UI for modeling and editing your game data. There are plugins for :doc:`Unity <unity/overview>` and :doc:`Unreal Engine </unreal_engine/overview>` that provide a more integrated experience while using Charon.  
As with any modern .NET application, it can be launched as is on Windows, macOS and Linux and via `dotnet` tool.


.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_screenshot.png
  :width: 600
  :alt: Charon UI

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/dashboard.png
  :width: 256
  :alt: Charon Dashboard
  
.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/document_collection.png
  :width: 256
  :alt: Charon Documents

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/document_form.png
  :width: 256
  :alt: Charon Document Form

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/documents_import.png
  :width: 256
  :alt: Charon Document Import 
  
Further reading
---------------

.. toctree::
   :caption: Unreal Engine Quick Start
   :titlesonly:
   :glob:

   /unreal_engine/overview
   /unreal_engine/*


.. toctree::
   :caption: Unity Quick Start
   :titlesonly:
   :glob:

   /unity/overview
   /unity/*

.. toctree::
   :caption: Standalone Quick Start
   :titlesonly:
   :glob:

   /standalone/overview
   /standalone/*

.. toctree::
   :caption: Web Quick Start
   :titlesonly:
   :glob:

   /web/overview
   /web/*

.. toctree::
   :caption: Working with Game Data
   :titlesonly:
   :glob:

   /gamedata/*

.. toctree::
   :caption: Advanced Features
   :titlesonly:
   :glob:

   /advanced/*
   /advanced/extensions/overview

.. toctree::
   :caption: Reference
   :titlesonly:

   /faq
   /glossary