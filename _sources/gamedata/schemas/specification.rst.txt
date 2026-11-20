Specification
=============

The ``Specification`` field is a flexible extension point available on both :doc:`Schema <schema>` and :doc:`Property <../properties/property>` documents. It enables developers to attach additional metadata in a standardized format that can be used for custom logic in UI field editors, source code generation, or other tooling integrations.

Overview
--------

The ``Specification`` field stores a string formatted using the `application/x-www-form-urlencoded <https://url.spec.whatwg.org/#application-x-www-form-urlencoded-percent-encode-set>`_ standard (commonly referred to as `URLSearchParams <https://developer.mozilla.org/en-US/docs/Web/API/URLSearchParams>`_ format). It contains key-value pairs separated by ampersands (`&`), where each key and value are URL-encoded.

For example:

.. code-block::

    icon=table&group=Combat

Use Cases
---------

The `Specification` field is commonly used for:

- **Schema metadata**:  
  Define an icon, group behavior, or UI preferences:
  
  .. code-block::

     icon=table&category=Gameplay&hideInMenu=true

- **Property editor extensions**:  
  Pass configuration values to custom editors:
  
  .. code-block::

     colorFormat=RGB&alpha=true

- **Source code generation**:  
  Customize how types or methods are generated:
  
  .. code-block::

     typeName=MyEnum&csAttribute=Obsolete

Encoding Guide
--------------

All keys and values must be properly URL-encoded to ensure compatibility with parsing libraries and avoid format-breaking characters.

Encoding in JavaScript
^^^^^^^^^^^^^^^^^^^^^^

In any browser console or Node.js REPL:

  .. code-block:: js

    const params = new URLSearchParams({
      icon: "sword",
      group: "Items and Stuff",
      noThumbnail: true
    });
    console.log(params.toString());
    // Output: icon=sword&group=Items%20and%20Stuff&noThumbnail=true


Encoding in Excel
^^^^^^^^^^^^^^^^^^^^^

To encode values manually using Excel formulas:

- Build a key-value pair:

  .. code-block::

    =ENCODEURL("noThumbnail") & "=" & ENCODEURL("true")


- Combine multiple:

  .. code-block::

    =ENCODEURL("icon") & "=" & ENCODEURL("sword") & "&" & ENCODEURL("group") & "=" & ENCODEURL("Items and Stuff")


Best Practices
--------------

- **Use lowercase or camelCase for keys** to ensure consistency.
- **Avoid spaces or special characters** in keys; values should always be encoded.

See also
--------

- :doc:`Display Text Template <display_text_template>`
- :doc:`Property <../properties/property>`
- :doc:`Schema <schema>`
- :doc:`All Data Types <../datatypes/list>`
- :doc:`Creating Document Type (Schema) <../creating_schema>`

