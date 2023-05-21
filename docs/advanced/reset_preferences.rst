Resetting UI Preferences
========================

If for some reason editor behaves erratically (grids aren't displayed correctly or aren't displayed at all), you can restore default UI settings.

- In Unity plugin select ``Tools → Charon → Troubleshooting → Reset Preferences``.
- For CLI and standalone launch just add ``--resetPreferences.`` parameter.

Example:

.. code-block:: bash

  Charon.exe SERVE ./gamedata.json --port 8080 --launchDefaultBrowser --resetPreferences
