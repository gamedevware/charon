Requirements
========

Unity plugin uses `Charon.exe`, which is a .NET application built for .NET Framework 4.7.2 and tested for compatibility with Mono 5.18.0.

Step By Step
------------

Windows
^^^^^^^

1. Download and install `NET Framework 4.7.2+ <https://dotnet.microsoft.com/en-us/download/dotnet-framework/net472>`_.
2. Make sure you have write access to ``%APPDATA%/Charon``.

OSX
^^^

1. Download and install `Mono runtime 5.18.0+ <http://www.mono-project.com/download/#download-mac>`_.
2. Make sure you have write access to ``~/Library/Application Support/Charon``.

Linux
^^^^^

1. Download and install `Mono runtime 5.18.0+ <https://www.mono-project.com/download/stable/#download-lin>`_.
2. Make sure you have write access to ``~/.config``.
3. Make sure ``mono`` is available to the current user.

.. code-block:: bash

    # check for mono already installed
    mono --version

Checking Available Runtime Version
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To examine your current .NET Framework runtime or Mono runtime version, you need to select 
**Tools** → **Charon** → **Troubleshooting** → **Check Runtime Version...** in the Unity menu.

See also
--------

- :doc:`Plugin Installation <plugin_installation>`
- :doc:`Creating and Editing Game Data <creating_and_editing_game_data>`
