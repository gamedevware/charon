Implementing ``CharonPropertyEditorElement``
--------------------------------------------

Each custom property editor must implement the ``CharonPropertyEditorElement`` interface from the `charon-extensions <https://www.npmjs.com/package/charon-extensions>`_ package:

.. code-block:: typescript

  export declare interface CharonPropertyEditorElement {
    valueControl: ValueControl;
  }

When the editor is rendered, Charon sets ``valueControl`` to allow your component to:

- Subscribe to input value changes.
- Update the current value.
- Access schema metadata.
- Add custom validation.
- Respond to focus events.

Understanding ``ValueControl``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ``ValueControl`` interface loosely mirrors Angular’s `AbstractControl <https://angular.dev/api/forms/AbstractControl>`_. Here's a simplified definition:

.. code-block:: typescript

  export declare interface ValueControl<TValue = any> {
    readonly schemaProperty: SchemaProperty;

    readonly valueChanges: ObservableLike<TValue>;
    readonly value: TValue;

    setValue(value: TValue, options?: ControlEventEmitOptions): void;

    registerDoFocus(fn: (options?: FocusOptions) => void, targetName?: string): TeardownLogic;

    readonly errors: Object | null;

    addValidators(validators: ValueValidatorFn | ValueValidatorFn[]): void;
    removeValidators(validators: ValueValidatorFn | ValueValidatorFn[]): void;
    hasValidator(validator: ValueValidatorFn): boolean;
  }

Reacting to Value Changes
^^^^^^^^^^^^^^^^^^^^^^^^^

When your editor receives the ``valueControl``, subscribe to ``valueChanges``:

.. code-block:: tsx

  useEffect(() => {
    const subscription = valueControl.valueChanges.subscribe(value => {
      setLocalValue(value); // Update local state
    });

    return () => subscription.unsubscribe(); // Cleanup on unmount
  }, [valueControl]);

When the user edits the field, call:

.. code-block:: tsx

  valueControl.setValue(newValue); // it will trigger `valueControl.valueChanges` even if values are same (!)

The format and type of the value are described in ``valueControl.schemaProperty``.

Handling Focus Events
^^^^^^^^^^^^^^^^^^^^^

Charon can request that your editor focuses the first interactive element. Use ``registerDoFocus``:

.. code-block:: tsx

  useEffect(() => {
    const teardown = valueControl.registerDoFocus(() => {
      inputRef.current?.focus();
    });

    return () => teardown(); // Unregister on unmount or control change
  }, [valueControl]);

Providing Custom Validators
^^^^^^^^^^^^^^^^^^^^^^^^^^^

To enable custom validation:

1. Register validators when ``valueControl`` is assigned.
2. Clean them up when your component is destroyed or ``valueControl`` changes.

Example:

.. code-block:: tsx

  useEffect(() => {
    const validateValue = (control: ValueControl): Object | null => {
      if (isValidColor(control.value)) {
        return null;
      }
      return {
        ERROR_CUSTOM: 'Invalid value for color in #XXXXXX format.'
      };
    };

    valueControl.addValidators(validateValue);
    return () => valueControl.removeValidators(validateValue);
  }, [valueControl]);
