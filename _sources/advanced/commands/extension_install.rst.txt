Install UI Extension
====================

.. versionadded:: vNext

Install a UI extension NPM package (``.tgz`` or ``.tar``, as produced by ``npm pack``) into the local extension directory. The package name and version are read from its ``package.json``, and the file is saved as ``<name>-<version>.tgz``. A package with the same name and version is replaced; other versions of the same package are kept, so a project can still pin an older one.

A running Charon server picks up the new package without a restart.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local file (windows)
  dnx dotnet-charon -- EXTENSION INSTALL --input "c:\my extension\my-extension-1.0.0.tgz"

  # remote file
  dnx dotnet-charon -- EXTENSION INSTALL --input "https://example.com/my-extension-1.0.0.tgz"

  # standard input
  dnx dotnet-charon -- EXTENSION INSTALL --input in < my-extension-1.0.0.tgz

---------------
 Parameters
---------------

--input
   Required. Path to the package file. Alternatively, you can read from `Standard Input <https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)>`_ or a :doc:`URL <remote_input_output>`.

   .. code-block:: bash

     # standard input
     --input in
     --input con

     # absolute path (windows)
     --input "c:\my extension\my-extension-1.0.0.tgz"

     # absolute path (unix)
     --input /user/extensions/my-extension-1.0.0.tgz

     # relative path (universal)
     --input "./my-extension-1.0.0.tgz"

     # remote location (HTTP)
     --input "http://example.com/my-extension-1.0.0.tgz"

     # remote location with authentication (FTP)
     --input "ftp://user:password@example.com/my-extension-1.0.0.tgz"

The command exits with code ``1`` when the input is not an NPM package.

This command supports :doc:`universal parameters <universal_parameters>`.

See also
--------

- :doc:`Extensions Overview <../extensions/overview>`
- :doc:`EXTENSION LIST <extension_list>`
- :doc:`EXTENSION UNINSTALL <extension_uninstall>`
- :doc:`EXTENSION VERSION <extension_version>`
- :doc:`EXTENSION UPLOAD <extension_upload>`
