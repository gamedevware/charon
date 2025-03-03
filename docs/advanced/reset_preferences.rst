Resetting UI Preferences
========================

If for some reason editor behaves erratically (grids aren't displayed correctly or aren't displayed at all), you can restore default UI settings.

Unity plugin 
   Select in menu ``Tools → Charon → Troubleshooting → Reset Preferences``.
CLI and Standalone 
   Launch with ``--resetPreferences.`` parameter.
Web
  Use the ``Preferences`` profile tab ``<User Icon> → Profile → Preferences``.

CLI Example:

.. code-block:: bash

  dotnet charon SERVER START ./gamedata.json --launchDefaultBrowser --resetPreferences

