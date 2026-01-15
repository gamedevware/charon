Creating a Custom Editor with React
===================================

Charon is a flexible data modeling web application that supports user-defined custom editors for fields and documents. By leveraging **Web Components**, Charon allows developers to seamlessly integrate reusable UI components that can be packaged and distributed via NPM.

This guide walks you through the process of preparing and packaging a Charon-compatible extension. It assumes proficiency with React and modern frontend tooling.

Introduction to Web Components
------------------------------

Web Components are a set of standardized browser APIs that allow developers to create reusable and encapsulated HTML elements. Core technologies include:

- **Custom Elements**: Define new HTML tags using JavaScript.
- **Shadow DOM**: Encapsulate markup and styles.
- **HTML Templates**: Define reusable markup structures.

Web Components are framework-agnostic, making them ideal for embedding in applications like Charon.

Charon loads user-defined Web Components dynamically at runtime. Each component is registered via a known selector and associated with supported data types and usage contexts (e.g., form property, grid column).

Step-by-Step: Building a Logical Toggle Editor
----------------------------------------------

This guide uses a custom logical toggle field editor as an example. You can `download and try <https://github.com/gamedevware/charon-extensions/tree/main/src/charon-logical-toggle>`_ the example code referenced in this article.

1. Create a New React Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: bash

    npm create vite
    > Project name: charon-logical-toggle
    > Select a framework: React
    > Select a variant: TypeScript
    
    cd charon-logical-toggle
    npm install

2. Install Required Dependencies
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Install SASS, RxJS (recommended), the Web Components polyfill (for broader compatibility), and the Charon extension types package.

.. code-block:: bash

    npm install sass --save
    npm install rxjs --save
    npm install @webcomponents/custom-elements --save
    npm install charon-extension --save

3. Write and Export Your Web Component
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Follow a recommended guide for wrapping React components as Web Components:

- `Create a Web Component from a React Component <https://techblog.skeepers.io/create-a-web-component-from-a-react-component-bbe7c5f85ee6>`_
- `LogicalToggleElement.tsx (Web Component) <https://github.com/gamedevware/charon-extensions/blob/main/src/charon-logical-toggle/src/LogicalToggleElement.tsx>`_
- `LogicalToggle.tsx (React Component) <https://github.com/gamedevware/charon-extensions/blob/main/src/charon-logical-toggle/src/LogicalToggle.tsx>`_

Key points when writing your component:

- Implement the ``CharonPropertyEditorElement`` interface in your Web Component to accept input properties from the main application.
- Ensure you correctly subscribe and unsubscribe when ``valueControl`` or ``documentControl`` input values change to avoid memory leaks.
- Export your Web Component using a unique tag name (e.g., ``ext-logical-toggle-editor``).
- Your ``main.js`` script should only register the Web Component—it should not render anything directly.

4. Modify ``vite.config.ts`` for Packaging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Update the ``vite.config.ts`` file to control file naming and minimize output hashing:

.. code-block:: ts

    import { defineConfig } from 'vite'
    import react from '@vitejs/plugin-react'
    
    export default defineConfig({
      plugins: [react()],
      build: {
        rollupOptions: {
          output: {
            assetFileNames: 'assets/[name].[ext]',
            chunkFileNames: '[name].js',
            entryFileNames: '[name].js'
          }
        },
        minify: false // Disable minification during development
      }
    })

5. Update ``package.json`` for Packaging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ensure your ``package.json`` includes the following:

- A non-default version number (e.g., ``1.0.0``).
- A ``main`` field pointing to your generated JS bundle (e.g., ``index.js``).
- A ``build`` script for bundling and packaging:

  .. code-block:: json

      "scripts": {
        "build": "tsc -b && vite build && copy package.json dist\\package.json && cd dist && npm pack"
      }

- Include your stylesheet(s) in the ``files`` array:

  .. code-block:: json

      "files": ["assets/index.css"]

- Declare the Charon extension metadata using the ``config.customEditors`` section:

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

- Add the Charon extension schema reference:

  .. code-block:: json

      "$schema": "https://raw.githubusercontent.com/gamedevware/charon-extensions/refs/heads/main/package.json.schema.json"

- Remove the ``"private": true`` flag before publishing.
- Fill in metadata fields like ``author``, ``description``, and ``license``.

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

During debugging, set the following in ``vite.config.ts``:

.. code-block:: ts

    build: {
      minify: false
    }

This improves source map quality and simplifies runtime behavior.

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
