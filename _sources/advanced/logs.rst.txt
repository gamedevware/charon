Working with Logs
==============

Charon creates a log files with various messages that may be useful for troubleshooting and debugging.

Unity Plugin
   Log files are saved to ``<project-directory>/Library/Charon/logs/``.

Unreal Engine Plugin
   Log files are saved to ``<project-directory>/Intermediate/Charon/logs/``.

CLI and Standalone
   Log files are saved to:
    - Windows: ``C:/ProgramData/Charon/logs/``.
    - MacOS: ``/Users/<username>/.config/Charon/logs``
    - Linux: ``/home/<username>/.config/Charon/logs``

Note: Make sure to replace ``<project-directory>`` and ``<charon-directory>`` with the actual directories on your system.

Logging Levels
--------------

Normally only the most important events are logged.  
If you have trouble identifying an issue, you might want to change log
to *verbose*. This way more information is included in logs.

Unity Plugin
   In menu select ``Tools → Charon → Troubleshooting → Verbose Logs``.

CLI and Standalone
   Launch with ``--verbose`` parameter.

Then repeat the action that causes the bug (or the one you want analyzed anyway) and check log file again.

CLI Example:

.. code-block:: bash

   charon SERVER START ./gamedata.json --launchDefaultBrowser --verbose

