Overview
========
Currently, using a `cakescript <https://cakebuild.net/>`_ is the most convenient method to obtain the latest version of ``Charon.exe``.
Alternatively `Nuget Package <https://www.nuget.org/packages/GameDevWare.Charon>`_ could be used. Read :doc:`CLI <../advanced/command_line>` overview for details.

Step By Step
=============

1. Download scripts from `/scripts <../../scripts/>`_ into a local folder ``/charon``.
2. Navigate to local folder ``cd /charon``.
3. Run ``update_and_launch.bat`` or ``update_and_launch.sh`` depending on your OS.
4. Wait for the script to automatically download and upgrade ``Charon.exe``, and launch it for you.

.NET Tool
===========
Alternatively, you could execute ``update_and_launch.cake`` with ``dotnet``.

First, install the Cake tool:

.. code-block:: bash

    # Make sure to have a tool manifest available in your repository or create one using the following command
    dotnet new tool-manifest
  
    # Install Cake  (you can replace 3.0.0 with a different version of Cake you want to use)
    dotnet tool install Cake.Tool --version 3.0.0

Finally, execute the Cake script:

.. code-block:: bash

    # launch update_and_launch.cake with normal log verbosity
    dotnet cake "./update_and_launch.cake" -v normal

See also
========

- :doc:`Requirements <requirements>`
- :doc:`Creating and Editing Game Data <creating_and_editing_game_data>`
