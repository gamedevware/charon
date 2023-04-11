To launch in standalone mode, `Charon.exe` requires .NET Framework 4.7.2 and/or Mono 5.18.0.

.. rubric:: Windows

1. Download and install `NET Framework 4.7.2+ <https://dotnet.microsoft.com/en-us/download/dotnet-framework/net472>`_.
2. Make sure you have write access to ``%APPDATA%/Charon``.

.. rubric:: OSX

1. Download and install `Mono runtime 5.18.0+ <http://www.mono-project.com/download/#download-mac>`_.
2. Make sure you have write access to ``~/Library/Application Support/Charon``.
3. Make sure ``mono`` is available from ``$PATH``.

.. rubric:: Linux

1. Download and install `Mono runtime 5.18.0+ <https://www.mono-project.com/download/stable/#download-lin>`_.
2. Make sure you have write access to ``~/.config``.
3. Make sure ``mono`` is available from ``$PATH``.

.. code-block:: bash

    # check for mono already installed
    mono --version
