Uninstall UI Extension
======================

.. versionadded:: vNext

Remove versions of a UI extension package from the local extension directory. Without ``--version``, every installed version of the package is removed.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`

---------------
 Command
---------------

.. code-block:: bash

  # all versions
  dnx dotnet-charon -- EXTENSION UNINSTALL --name charon-conversation-editor

  # versions older than 1.0.0
  dnx dotnet-charon -- EXTENSION UNINSTALL --name charon-conversation-editor --version "<1.0.0"

---------------
 Parameters
---------------

--name
   Name of the package to remove, as written in its ``package.json``.

--version
   Version or version range to remove. Defaults to ``*``, all versions.

   .. code-block:: bash

     # exact version
     --version 1.2.0

     # same major version
     --version "^1.0.0"

     # same minor version
     --version "~1.2.0"

     # older than
     --version "<2.0.0"

The command exits with code ``1`` when no installed version matches.

This command supports :doc:`universal parameters <universal_parameters>`.

See also
--------

- :doc:`Extensions Overview <../extensions/overview>`
- :doc:`EXTENSION INSTALL <extension_install>`
- :doc:`EXTENSION LIST <extension_list>`
- :doc:`EXTENSION VERSION <extension_version>`
