Installation and Updates
========================

There is two bootstrap scripts which download and run latest version of Charon on your PC:  

  - RunCharon.bat for Windows  
  - RunCharon.sh for Linux or MacOS  

Both scripts require the `dotnet <https://dotnet.microsoft.com/en-us/download/dotnet>`_ tool to be available in ``PATH`` 
and `mono <https://www.mono-project.com/download/stable/>`_ installed for Linux and MacOS.  


Step By Step
------------


1. Download one of the scripts into a local folder ``/charon``.  
    a) `RunCharon.bat (Windows) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.bat>`_  
    b) `RunCharon.sh (Linux, MacOS) <https://github.com/gamedevware/charon/blob/main/scripts/bootstrap/RunCharon.sh>`_  
2. Navigate to the local folder ``cd /charon``. 
3. Run ``RunCharon.bat`` or ``RunCharon.sh`` depending on your OS.  
4. Wait for the script to automatically download and upgrade ``Charon.exe``, and display help text.  
5. Create an empty file named ``./gamedata.json``  
6. Run ``Charon.exe`` in standalone mode  

.. code-block:: bash

  # Windows
  ./RunCharon.bat SERVER START --database ./gamedata.json --launchDefaultBrowser --log out
  
  # Linux, MacOS
  chmod +x ./RunCharon.sh
  ./RunCharon.sh SERVER START --database ./gamedata.json --launchDefaultBrowser --log out

After finishing your work, you could just terminate the process.  

See also
--------

- :doc:`Requirements <requirements>`
- :doc:`Creating and Editing Game Data <creating_and_editing_game_data>`
