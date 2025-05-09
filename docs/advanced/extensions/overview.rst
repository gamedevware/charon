UI Extensions
=============

Charon supports a powerful plugin model through **extensions**, which allow developers to create custom field and document editors that integrate with the application. These extensions are built using **Web Components** and packaged as **NPM modules** for easy distribution and reuse.

What Is a Charon Extension?
---------------------------

A **Charon extension** is an external package that provides one or more custom UI components (editors) used inside the document form.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/editor_custom_editor.png
  :width: 800
  :alt: Form with custom editor


Each extension is:

- A **Web Component** implementing a specific interface.
- Packaged as a standard **NPM module**.
- Discoverable by Charon at runtime (via local ``.tgz`` or a public NPM registry).
- Described with metadata in ``package.json`` under the ``config.customEditors`` section.

What Is a Web Component?
------------------------

A **Web Component** is a browser-native way to define reusable UI elements that are:

- **Encapsulated**: HTML, CSS, and JS are scoped to the component.
- **Self-contained**: No dependencies on the application’s framework.
- **Reusable**: Can be shared across projects regardless of frontend tech (React, Angular, Vue, etc.).

This isolation is essential for Charon, which must load unknown user-defined components without conflict or side effects.

What Is an NPM Package?
-----------------------

An **NPM package** is a collection of files published to the `npm registry <https://www.npmjs.com/>`_ or used locally. It contains:

- JavaScript bundles
- Stylesheets (optional)
- Metadata (``package.json``)
- Documentation or type definitions

In Charon, an extension is published as an NPM package (or ``.tgz`` archive) and loaded dynamically at runtime.

Typical NPM Package Structure
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A Charon extension NPM package usually contains:

.. code-block::

  dist/
  ├── index.js               # Compiled JS bundle that registers the component
  ├── assets/
  │   └── index.css          # Optional styles
  ├── package.json           # Includes Charon metadata and schema reference
  └── *.tgz                  # (optional) Published archive

Example ``package.json`` metadata:

.. code-block:: json

  "config": {
    "customEditors": [
      {
        "id": "ext-logical-toggle",
        "selector": "ext-logical-toggle-editor",
        "name": "Logical Toggle",
        "type": ["Property", "Grid"],
        "dataTypes": ["Logical"]
      }
    ]
  }

Gettings Started
----------------

- :doc:`Creating a Custom Editor with React <creating_react_extension>`
- :doc:`Creating a Custom Editor with Angular <creating_angular_extension>`
- :doc:`Implementing Custom Property Editor Interface <implementing_property_editor>`

Publication and Consumption
---------------------------

After you implement the extension interface and build the UI logic to display and edit the value, you need to create a production build of your package and publish it either locally or to the NPM registry.

To publish locally:

.. code-block:: bash

   npm pack

This creates a ``.tgz`` archive in your ``dist`` directory that can be manually placed in Charon’s extension folder for testing.

To `publish <https://docs.npmjs.com/creating-and-publishing-unscoped-public-packages>`_ publicly:

.. code-block:: bash

   npm publish

Make sure your ``package.json`` contains all required metadata and the ``"private": true`` flag is removed.

Once published, the extension package can be added through the ``Project Settings → Extensions`` tab in Charon. Enter the NPM package name and, optionally, specify a version. If the version is omitted, the latest published version will be used.

The list of enabled extensions is saved inside your Charon data file, making it automatically available to all users working on that file.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/project_settings_extensions.png
  :width: 800
  :alt: Project Settings Extensions

.. note::

   Locally installed extensions (via ``.tgz`` files) are intended only for development and debugging. They are available **only on your machine** and will not be shared with other users.

See Also
--------

- :doc:`Creating a Custom Editor with React <creating_react_extension>`
- :doc:`Creating a Custom Editor with Angular <creating_angular_extension>`
- `Example Projects (GitHub) <https://github.com/gamedevware/charon-extensions/>`_

