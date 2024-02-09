Requirements
============

Charon is a .NET Framework 4.7.2 and/or Mono 5.18.0 application. It currently uses ``.NET Core`` tools for bootstrap scripts.

Step By Step
------------

Windows
^^^^^^^

1. Download and install `.NET Framework 4.7.2+ <https://dotnet.microsoft.com/en-us/download/dotnet-framework/net472>`_.
2. Download and install `.NET Core 5+ <https://dotnet.microsoft.com/en-us/download/dotnet>`_.
3. Make sure you have write access to ``%APPDATA%/Charon``.

OSX
^^^

1. Download and install `Mono runtime 5.18.0+ <http://www.mono-project.com/download/#download-mac>`_.
2. Download and install `.NET Core 5+ <https://dotnet.microsoft.com/en-us/download/dotnet>`_.
3. Make sure you have write access to ``~/Library/Application Support/Charon``.
4. Make sure ``mono`` is available from ``$PATH``.

Linux
^^^^^

1. Download and install `Mono runtime 5.18.0+ <https://www.mono-project.com/download/stable/#download-lin>`_.
2. Download and install `.NET Core 5+ <https://dotnet.microsoft.com/en-us/download/dotnet>`_.
3. Make sure you have write access to ``~/.config``.
4. Make sure ``mono`` is available from ``$PATH``.

.. code-block:: bash

  # check for mono is already installed
  mono --version
  
  # check for .NET Core is already installed
  dotnet --version

See also
--------

- :doc:`Installation and Updates <installation_and_updates>`
- :doc:`Creating and Editing Game Data <creating_and_editing_game_data>`
