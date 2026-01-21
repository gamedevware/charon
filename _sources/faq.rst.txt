Frequently Asked Questions (FAQ)
================================

What kind of game data can be modeled in Charon?
------------------------------------------------

Charon is designed for modeling static game data. Typical use cases include Quests, Dialogs, Levels, Loot Tables, Items, Monsters, Abilities, Units, Research Trees, Weapons, Spells, Goods, Buildings, and similar structured data used to drive gameplay logic and content.

What data types are supported in Charon?
----------------------------------------

Charon provides a broad set of data types to suit a variety of needs. These include primitive types such as text, localized text, booleans, time, dates, numbers, enums (pick lists), and flags. More advanced structures are also supported, including embedded documents, collections, references to other documents, and computed formulas.

Is schema inheritance supported?
--------------------------------
Yes, schema inheritance is supported in Charon, although it is implemented using a composition-based approach rather than traditional inheritance. Existing schemas can be extended by including them as ``Document`` properties within other schemas.  
:doc:`Read more about inheritance. <gamedata/inheritance>`

Is Charon free to use?
----------------------
The offline version, including the command-line interface (CLI) and associated plugins, is free to use and distributed under a permissive license. It imposes no restrictions and may be bundled with games to support modding workflows.

The `online <https://www.gamedevware.com/>`_ version, which enables collaborative editing of shared game data in teams, is available under a subscription model.

Are there limitations in the Unity/Unreal plugins or CLI version?
------------------------------------------------------------------
No, there are no imposed limitations on the CLI version or the Unity and Unreal Engine plugins. This includes file size, number of documents, or schema complexity.

Does Charon support localization?
---------------------------------

Yes, Charon supports multi-language content through the :doc:`localized text <gamedata/datatypes/all/localized_text>` type. Localizable text can be exported for translation and imported back once translated. In-game, language switching is supported globally with a single function call, ensuring a consistent localization experience.

How does Charon integrate with Unity or Unreal Engine?
------------------------------------------------------

Charon provides dedicated plugins for both Unity and Unreal Engine. These plugins integrate natively into each engine’s workflow and expose game data as strongly typed assets. Full source code is included, along with example projects demonstrating how to extend and use the plugins within game code.

Can I define relationships between documents (e.g., parent-child or references)?
--------------------------------------------------------------------------------

Yes. Charon supports embedding documents within each other to model hierarchical structures (e.g., trees). It also allows referencing other documents through reference fields or reference collections. These references can be automatically validated for consistency, avoiding the common pitfalls of spreadsheet-based data modeling.

Can I generate custom editors or tools with Charon?
---------------------------------------------------

Yes. Charon is extensible through :doc:`custom field and document editors <advanced/extensions/overview>`. It can also be embedded in other applications using an embedded browser such as CEF. For example, the Unreal Engine plugin demonstrates how to run the Charon UI inside an in-editor browser, allowing you to build a seamless experience around your tools.

Does Charon support formulas or computed fields?
------------------------------------------------

Yes. Charon includes support for C#-like :doc:`formulas <gamedata/datatypes/all/formula>` as a first-class data type. These formulas can be evaluated at runtime with user-defined parameters, allowing you to move balance logic and other calculations out of compiled code and into editable data structures.

Can Charon be integrated into CI/CD pipelines or custom toolchains?
--------------------------------------------------------------------

Yes. Charon includes a :doc:`command-line interface (CLI) <advanced/command_line>` that supports full CRUD operations and data import/export. The CLI can work with local game data stored in JSON or MessagePack formats, as well as connect to the online service. You can script uploads, downloads, merges, and validation steps as part of your CI/CD workflow.

What export formats does Charon support?
----------------------------------------

Charon supports multiple export and import formats for game data, including JSON, MessagePack, BSON, and XLSX (spreadsheets). For localization, the XLIFF format is also supported. Runtime and asset storage formats are limited to JSON and MessagePack.

Can I control user access and editing permissions?
--------------------------------------------------

Yes. In collaborative environments using the online version of Charon, a role-based access model is available. Roles include Administrator, Schema Designer, Editor, and Viewer, each with a defined set of permissions. For more information, see :doc:`Roles and Permissions <web/permission_and_roles>`.

Is the editor's source code available?
--------------------------------------
The source code for the editor itself is not publicly available. However, the plugin source code is available on GitHub:  
`Charon GitHub Repositories <https://github.com/gamedevware?tab=repositories>`_

Charon can be :doc:`extended <advanced/extensions/overview>` with custom field editors or even full document editors, such as node-based interfaces.  

For teams requiring a fully private, self-contained collaborative workspace, an **on-premises installation** of the online service is available. It provides the same features as the hosted version — real-time collaboration, access control, multiple projects, AI features, Machine Translation, and team workflows — while keeping all data and infrastructure under your control.  
If you are interested in an on-premises deployment, please contact us support@gamedevware.com for licensing and installation options.

What happens if the project is discontinued or no longer maintained?
--------------------------------------------------------------------

In the unlikely event that Charon is no longer maintained or all original contributors become unavailable, a contingency plan is in place. The online service domain would eventually become inaccessible; however, the full source code of the server, as well as private Docker images, will be published under the MIT license by a designated successor. This ensures that the system can be self-hosted or forked by the community.

The CLI and engine plugins rely on published NuGet packages, which are already public and will remain unaffected. Users working in offline mode will experience no disruption. For users of the online version, all project data is periodically cloned and stored locally. These local copies remain fully compatible with the standalone application, allowing teams to continue working without interruption.


