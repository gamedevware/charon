UI Extension Version
====================

.. versionadded:: vNext

Print the latest installed version of a UI extension package. With ``--online``, the latest version published to the NPM registry is checked too, which shows whether an update is available.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  dnx dotnet-charon -- EXTENSION VERSION --name charon-conversation-editor --online

  #> {
  #>   "name": "charon-conversation-editor",
  #>   "installedVersion": "0.0.42",
  #>   "onlineVersion": "0.0.43"
  #> }

---------------
 Parameters
---------------

--name
   Name of the package, as written in its ``package.json``.

--online
   Also check the NPM registry for the latest published version.

--output
   Path to the output file. If the file exists, it will be overwritten. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_,  `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`. Defaults to ``out``.

--outputFormat
   Format of the output. Defaults to ``json``.

--outputFormattingOptions
   Additional options for specified format.

A version is ``null`` when the package is not installed, or not found online. The command exits with code ``1`` when neither is found.

This command supports :doc:`universal parameters <universal_parameters>`.

See also
--------

- :doc:`Extensions Overview <../extensions/overview>`
- :doc:`EXTENSION INSTALL <extension_install>`
- :doc:`EXTENSION LIST <extension_list>`
- :doc:`EXTENSION UNINSTALL <extension_uninstall>`
