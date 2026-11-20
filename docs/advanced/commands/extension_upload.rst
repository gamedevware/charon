Upload UI Extension
===================

Upload a UI extension NPM package (``.tgz`` or ``.tar``, as produced by ``npm pack``) to the private extension storage of the workspace that owns a project on a Charon server. The package name and version are read from its ``package.json``. A stored package with the same name is replaced.

Unlike :doc:`EXTENSION INSTALL <extension_install>`, which writes to the local extension directory, an uploaded package is available to every project and user of the workspace. Uploading requires permission to administer the project.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # local file (windows)
  dnx dotnet-charon -- EXTENSION UPLOAD --project "https://charon.live/view/data/My_Game/develop/" --input "c:\my extension\my-extension-1.0.0.tgz" --credentials "<API-Key>"

  # standard input, API key from environment variable
  export CHARON_API_KEY=<API-Key>
  dnx dotnet-charon -- EXTENSION UPLOAD --project "https://charon.live/view/data/My_Game/develop/" --input in < my-extension-1.0.0.tgz

---------------
 Parameters
---------------

--project
   URL of a project branch on the server. The package is stored for the whole workspace; the branch only locates the project.

   .. code-block:: bash

     --project "https://charon.live/view/data/My_Game/develop/"

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

--credentials
   The API key used to access the server. It can also be provided via the ``CHARON_API_KEY`` environment variable.

The command fails when the input is not an NPM package, or when the workspace's extension package limit is reached.

This command supports :doc:`universal parameters <universal_parameters>`.

See also
--------

- :doc:`Extensions Overview <../extensions/overview>`
- :doc:`EXTENSION INSTALL <extension_install>`
- :doc:`EXTENSION LIST <extension_list>`
- :doc:`EXTENSION UNINSTALL <extension_uninstall>`
- :doc:`EXTENSION VERSION <extension_version>`
