Creating a Custom Editor with Angular
====================================

Charon is a flexible data modeling web application that supports user-defined custom editors for fields and documents. By leveraging **Web Components**, Charon allows developers to seamlessly integrate reusable UI components that can be packaged and distributed via NPM.

This guide walks you through the process of preparing and packaging a Charon-compatible extension. It assumes proficiency with Angular and modern frontend tooling.

Introduction to Web Components
------------------------------

Web Components are a set of standardized browser APIs that allow developers to create reusable and encapsulated HTML elements. Core technologies include:

- **Custom Elements**: Define new HTML tags using JavaScript.
- **Shadow DOM**: Encapsulate markup and styles.
- **HTML Templates**: Define reusable markup structures.

Web Components are framework-agnostic, making them ideal for embedding in applications like Charon.

Charon loads user-defined Web Components dynamically at runtime. Each component is registered via a known selector and associated with supported data types and usage contexts (e.g., form property, grid column).

Step-by-Step: Building a Color Picker Editor
--------------------------------------------

This guide uses a custom color picker field editor as an example. You can `download and try <https://github.com/gamedevware/charon-extensions/tree/main/src/charon-color-picker>`_ the example code referenced in this article.

1. Install the Latest Angular CLI
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: bash

    npm uninstall -g @angular/cli
    npm install -g @angular/cli@latest

2. Create a New Angular Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: bash

    ng new charon-color-picker --standalone false --ssr false --style sass

.. note::

    Ensure SSR is disabled and SCSS is used for styling.

3. Install Required Dependencies
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Install Angular Elements for Web Component support, the Web Components polyfill (for broader compatibility), and the Charon extension types package.

.. code-block:: bash

    npm install @angular/elements --save
    npm install @webcomponents/custom-elements --save
    npm install charon-extension --save

4. Write and Export Your Web Component
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Follow the official Angular guide to export your component as a custom element:

- `Angular Elements Guide <https://angular.dev/guide/elements>`_
- `color.picker.component.ts <https://github.com/gamedevware/charon-extensions/blob/main/src/charon-color-picker/src/app/color.picker/color.picker.component.ts>`_

Key points when writing your component:

- Implement the ``CharonPropertyEditorElement`` interface in your Angular component to accept input properties from the main application.
- Ensure you correctly subscribe and unsubscribe when ``valueControl`` or ``documentControl`` input values change, to avoid memory leaks.
- Export your component with a unique tag name (e.g., ``ext-color-picker-editor``) that is **not the same** as the Angular component's selector.

5. Modify ``angular.json`` for Packaging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Update the ``angular.json`` file:

- Set the build output path:

  .. code-block:: json

      "outputPath": "dist"

- Disable output hashing:

  .. code-block:: json

      "outputHashing": "none"

- Change the project type to ``library``:

  .. code-block:: json

      "projectType": "library"

- Optionally disable production optimizations during development:

  .. code-block:: json

      "configurations": {
        "production": {
          "optimizations": false
        }
      }

6. Update ``package.json`` for Packaging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ensure your ``package.json`` includes the following:

- A non-default version number (e.g., ``1.0.0``).
- A ``main`` field pointing to your generated JS bundle (e.g., ``main.js``).
- A ``build`` script for bundling and packaging:

  .. code-block:: json

      "scripts": {
        "build": "ng build && copy package.json dist\\browser\\package.json && cd dist\\browser && npm pack"
      }

- Include your stylesheet(s) in the ``files`` array:

  .. code-block:: json

      "files": ["styles.css"]

- Declare the Charon extension metadata using the ``config.customEditors`` section:

  .. code-block:: json

      "config": {
        "customEditors": [
          {
            "id": "ext-color-picker",
            "selector": "ext-color-picker-editor",
            "name": "Color Picker",
            "type": ["Property", "Grid"],
            "dataTypes": ["Text", "Integer"]
          }
        ]
      }

- Add the Charon extension schema reference:

  .. code-block:: json

      "$schema": "https://raw.githubusercontent.com/gamedevware/charon-extensions/refs/heads/main/package.json.schema.json"

- Remove the ``"private": true`` flag before publishing.
- Fill in other metadata: ``author``, ``description``, ``license``, etc.

7. Enable Standalone/Zoneless Mode (Performance)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ensure your component runs independently of Angular’s `zone.js`. This improves performance and prevents interference between extensions. Refer to Angular documentation for zoneless application setup.

Debugging & Local Testing
-------------------------

Test Locally in Charon
~~~~~~~~~~~~~~~~~~~~~~

Place the generated ``.tgz`` file in:

.. tab-set::

   .. tab-item:: Windows

      .. code-block::

        %PROGRAMDATA%\Charon\extensions\
        C:\ProgramData\Charon\extensions\

   .. tab-item:: MacOS

      .. code-block::

        /Users/<username>/.config/Charon/extensions/

   .. tab-item:: Linux

      .. code-block::

        /home/<username>/.config/Charon/extensions/

   .. tab-item:: Unity

      .. code-block::

        <project-directory>/Library/Charon/extensions/

   .. tab-item:: Unreal Engine

      .. code-block::

        <project-directory>/Intermediate/Charon/extensions/

This allows Charon to detect and load the extension during development, bypassing the NPM publication process.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/project_settings_extensions.png
  :width: 800
  :alt: Project Settings Extensions

Disable Optimizations for Browser Debugging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

During debugging, set:

.. code-block:: json

    "optimizations": false

in the ``production`` build configuration to simplify source maps and runtime behavior.

Versioning
~~~~~~~~~~

Always increment the ``version`` field in ``package.json`` between builds to ensure Charon detects updates.

Publishing
----------

Once your component is built, tested, and versioned, you can publish it to NPM and reference it in Charon's ``Project Settings → Extensions`` tab.  
Your custom editor will then be available in the schema designer for relevant property types.

.. image:: https://raw.githubusercontent.com/gamedevware/charon/main/docs/assets/schema_designer_select_extension_editor.png
  :width: 800
  :alt: Schema Designer with Custom Editor
