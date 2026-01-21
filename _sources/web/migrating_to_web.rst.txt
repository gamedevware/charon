Migrating to Web Application
============================

To migrate to the web application, you only need to backup your game data in your current editor and restore it in the web application.  

In short: project settings include a backup and restore feature. You make a backup in one place, and you can restore it in another. This is how you can transfer game data to another project.  

Backup Data Step by Step
-------------------------

1. Open your game data in the editor (Standalone, Unity ...)
2. In the bottom left corner, click on the gear icon "Settings"
3. In the left menu, select "Backup"  
4. On the backup management page, click the "Backup" button  
5. Choose "File" as the destination to save the backup and click "Next"  
6. On the "Format" step, select "JSON" and click "Backup"  
7. On the "Summary" step, click the link with a file name like ``backup_2023_11_10_11_27.json`` and save it to your computer.  

Restoring Backup in the Web Application
--------------------------------------

1. On the Home screen, click on "Create Project"  
2. Specify the project name, tags, and script language  
3. Click the "Create" button  
4. In the left menu, select "Backup"  
5. On the backup management page, click the "Restore" button  
6. Choose "File" as the source of the restore and click "Next"  
7. Select the input file, the one you have after the backup, such as ``backup_2023_11_10_11_27.json``, and click "Restore"  
8. Done  

Any data that was in this project at the time before the restore will be lost.  

See also
--------

- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Publication of Game Data <../gamedata/publication>`
- :doc:`Generating Source Code <../gamedata/generating_source_code>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`