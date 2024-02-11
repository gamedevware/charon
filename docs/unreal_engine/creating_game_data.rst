How to Create Game Data File
==============================

To create a new game data file within the Unreal Engine Editor, open the **Content Drawer**, right-click in the desired folder, and select in the **Create Advanced Assets** section **Miscellaneous → Game Data** menu option. 
Name your game data file and proceed according to the instructions in the dialog window that appears.  

Step By Step
------------

1. **Open Content Drawer:** Open the *Content Drawer* window in the Unreal Engine Editor.
2. **Select Folder:** Right-click in the desired folder where you want to create the game data file.
3. **Create Game Data:** Navigate to **Create Advanced Assets → Miscellaneous → Game Data** from the context menu.
4. **Name the File:** In the *Content Drawer* window that appears, enter a name for your game data file.
5. **Check for Errors:** Ensure there are no error messages in the dialog window that opens, then press *Next*.
6. **Wait for Module Generation:** Allow time for the new module to be generated, watching the wizard in the dialog proceed to the next step automatically.
7. **Review Summary:** Check the summary and verify there are no suspicious errors in the *Output Log* window.
8. **Recompile C++ Code:** Use your IDE of choice to recompile the C++ code.
9. **Import Game Data:** Reopen the *Content Drawer* window and click the **Import** button.
10. **Select .gdjs File:** Locate and select the *.gdjs* game data file you named in step 4, then click *Ok*.
11. **Choose Game Data Class:** Select the *Game Data* class, which should match the game data file name. If it's not listed, return to step 7.
12. **Save .uasset File:** Save the newly created *.uasset* file after completing the import process.

Throubleshooting
----------------
Game data creation or code generation/compilation may encounter issues under certain circumstances:  

**Insufficient File System Rights or File Creation Errors**
- **Problem**: Lack of sufficient rights to the OS file system, or errors during file creation (e.g., file name too long, antivirus block).
- **Solution**: Check the *Output Log* window for errors or the most recent log file in ``<project-dir>\Intermediate\Charon\logs`` and attempt to resolve them.

**Class Name Collision Within Project**
- **Solution 1** (Game Data Class Name Collision): Delete the newly created **.gdjs** game data file and the generated module. Then, start over with a new name and clean your ``.Target.cs`` files from the generated module name.
- **Solution 2** (Schema Class Name Collision): Open the game data in another editor (Online, Standalone), rename the schema, and try again.

**No Game Data Class in Import Window**
- **Problem**: The generated game data module is not being compiled.
- **Solution**: Ensure it's added to your ``<project-name>.Target.cs`` and ``<project-name>Editor.Target.cs`` files as an extra module. 
If missing, include the expression ``ExtraModuleNames.Add("<module-name>");`` in both target files.  
  
Additionally, verify that your **.uproject** file includes the generated module definition. If it's absent, add the following module definition to the **Modules** list:

.. code-block:: json

    {
        "Name": "<module-name>",
        "Type": "Runtime",
        "LoadingPhase": "Default"
    }

See also
--------

- :doc:`Basic Navigation and User Interface Overview <../gamedata/basics>`
- :doc:`Creating Document Type (Schema) <../gamedata/creating_schema>`
- :doc:`Filling Documents <../gamedata/filling_documents>`
- :doc:`Frequently Asked Questions (FAQ) <../faq>`
- :doc:`Glossary <../glossary>`
