Migration from Legacy Version (Before 2025.1.*)
===============================================

.. warning::
    **Before proceeding with the migration, ensure your project is under a source control system (e.g., Git) or that a full backup of your project has been created.**  
    Migration involves modifying and deleting files, and having a backup or version control ensures you can recover in case of unexpected issues.

Install the package with the new version of the plugin via the `Unity Asset Store <https://assetstore.unity.com/packages/tools/visual-scripting/game-data-editor-charon-95117>`_ or using `OpenUPM <https://openupm.com/packages/com.gamedevware.charon/?subPage=readme>`_ (recommended). After installing plugin package you have two options:

Automated Migration
-------------------

A window will appear offering to perform the migration automatically.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/unity_migrate_window.png
  :width: 498
  :alt: Unity Editor Migrate Plugin

1. Click the **Migrate** button and wait for the process to complete.
2. Once the migration is finished, close the window if everything is successful.
3. If an error occurs, check the **Console** window for details and consider using the *Manual Migration* approach.

Manual Migration
-------------------

To migrate manually, you will need to remove the old plugin, convert, and configure the game data files:

1. Navigate to the ``Assets/Editor/GameDevWare.Charon`` folder and delete it.
2. Temporarily move all **.gdjs** and **.gdmp** files from ``Assets/StreamingAssets/`` to ``Assets/``.
3. Select each **.gdjs** or **.gdmp** file and click the **Reimport** button in the **Inspector** window.
4. Replace the old **.asset** file with the newly generated one. If the file did not exist previously, place it anywhere within the boundaries of the **.asmdef** file.
5. Replace the old source code files (**.cs**) with the newly generated ones.

.. warning::
    Preserve the original **.meta** files for **.cs** and **.asset** assets to maintain Unity resource associations and links.

See also
--------

- :doc:`Unity Plugin Overview <overview>`