List UI Extensions
==================

List UI extension packages installed in the local extension directory, one entry per installed version. With ``--online``, packages published to the NPM registry with the ``charon`` and ``extensions`` keywords are listed too, at their latest version.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # installed packages
  dnx dotnet-charon -- EXTENSION LIST

  # installed and published packages with "editor" in the name
  dnx dotnet-charon -- EXTENSION LIST --query editor --online

---------------
 Parameters
---------------

--query
   Case-insensitive part of the package name to filter by.

--online
   Also search the NPM registry.

--output
   Path to the output file. If the file exists, it will be overwritten. The directory must already exist. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_,  `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.

   .. code-block:: bash

     # standard output (default)
     --output out

     # standard error
     --output err

     # null device
     --output null

     # relative path (universal)
     --output "./extensions.json"

--outputFormat
   Format of the output.

   .. code-block:: bash

     # JSON (default)
     --outputFormat json

     #> [
     #>   {
     #>     "name": "charon-conversation-editor",
     #>     "version": "0.0.43",
     #>     "isInstalled": false,
     #>     "location": "https://registry.npmjs.org/charon-conversation-editor"
     #>   },
     #>   {
     #>     "name": "charon-conversation-editor",
     #>     "version": "0.0.42",
     #>     "isInstalled": true,
     #>     "location": "C:\\ProgramData\\Charon\\extensions\\charon-conversation-editor-0.0.42.tgz"
     #>   }
     #> ]

--outputFormattingOptions
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.

See also
--------

- :doc:`Extensions Overview <../extensions/overview>`
- :doc:`EXTENSION INSTALL <extension_install>`
- :doc:`EXTENSION UNINSTALL <extension_uninstall>`
- :doc:`EXTENSION VERSION <extension_version>`
