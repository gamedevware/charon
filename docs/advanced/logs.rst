Working with Logs
==============

Game editor creates a special file (log file) with various messages that may be useful for debugging.

Log files are saved to:

.. code-block:: bash

    # Unity
    <project-directory>/Library/Charon/Logs/

    # Standalone
    <charon-directory>/logs/

Note: Make sure to replace ``<project-directory>`` and ``<charon-directory>`` with the actual directories on your system.

Logging Levels
--------------

Normally only the most important events are logged.  
If you have trouble identifying an issue, you might want to change log
to *verbose*. This way more information is included in logs.

- In Unity plugin select ``Tools → Charon → Troubleshooting → Verbose Logs``.
- For CLI and standalone launch just add ``--verbose`` parameter.

Then repeat the action that causes the bug (or the one you want analyzed
anyway) and check log file again.

Example:

.. code-block:: bash

  Charon.exe SERVE ./gamedata.json --port 8080 --launchDefaultBrowser --verbose
