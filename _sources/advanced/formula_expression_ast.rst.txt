Formula Expression AST
======================

Formula values are stored as a JSON-encoded Abstract Syntax Tree (AST). Each node in the tree represents an expression and is identified by the ``expressionType`` field, which acts as a discriminator for the node type. An interpreter recursively evaluates the tree starting from the root node.

Reference implementations exist for C#, TypeScript, and C++.

.. tab-set::

    .. tab-item:: Diagram

        .. graphviz::

            digraph ExpressionAST {
                rankdir=TB;
                graph [fontname="Helvetica", fontsize=11, bgcolor="#f8f9fa", pad=0.4, nodesep=0.3, ranksep=0.5, splines=polyline];
                node  [fontname="Helvetica", fontsize=10, shape=box, style="filled,rounded", height=0.3, width=1.6, fixedsize=false];
                edge  [fontname="Helvetica", fontsize=8, arrowsize=0.6];
            
                // Root union
                FormulaExpressionObj [fillcolor="#4a90d9", fontcolor="white", color="#2c6fad", penwidth=2];
            
                // Expression nodes
                node [fillcolor="#c8e6c9", color="#388e3c"];
                UnaryExpressionObj
                BinaryExpressionObj
                ConditionExpressionObj
                ConstantExpressionObj
                ConvertExpressionObj
                DefaultExpressionObj
                IndexExpressionObj
                InvokeExpressionObj
                LambdaExpressionObj
                MemberExpressionObj
                NewArrayBoundExpressionObj
                NewArrayInitExpressionObj
                ListInitExpressionObj
                MemberInitExpressionObj
                NewExpressionObj
                TypeIsExpressionObj
                TypeOfExpressionObj
            
                // Collection / ref types
                node [fillcolor="#ffe082", color="#f57f17"];
                TypeReferenceObj
                ArgumentCollectionObj
                TypeArgumentCollectionObj
                ElementInitCollectionObj
                MemberBindingCollectionObj
            
                // Binding types
                node [fillcolor="#ce93d8", color="#6a1b9a"];
                ElementInitBindingObj
                MemberMemberBindingObj
                MemberListBindingObj
                MemberAssignmentBindingObj
            
                // ── Union membership (dashed blue) ──
                edge [style=dashed, arrowhead=onormal, color="#4a90d9"];
                FormulaExpressionObj -> {
                    UnaryExpressionObj BinaryExpressionObj ConditionExpressionObj
                    ConstantExpressionObj ConvertExpressionObj DefaultExpressionObj
                    IndexExpressionObj InvokeExpressionObj LambdaExpressionObj
                    MemberExpressionObj NewArrayBoundExpressionObj NewArrayInitExpressionObj
                    ListInitExpressionObj MemberInitExpressionObj NewExpressionObj
                    TypeIsExpressionObj TypeOfExpressionObj
                }
            
                // ── Composition (solid dark) ──
                edge [style=solid, arrowhead=vee, color="#333333"];
            
                // → ArgumentCollectionObj
                IndexExpressionObj         -> ArgumentCollectionObj
                InvokeExpressionObj        -> ArgumentCollectionObj
                LambdaExpressionObj        -> ArgumentCollectionObj
                NewArrayBoundExpressionObj -> ArgumentCollectionObj
                NewArrayInitExpressionObj  -> ArgumentCollectionObj
                NewExpressionObj           -> ArgumentCollectionObj
                ElementInitBindingObj      -> ArgumentCollectionObj
            
                // → TypeArgumentCollectionObj
                MemberExpressionObj -> TypeArgumentCollectionObj
                TypeReferenceObj    -> TypeArgumentCollectionObj
            
                // → FormulaExpressionObj (back-refs, gray)
                edge [color="#999999", style=dashed, arrowhead=vee];
                ArgumentCollectionObj      -> FormulaExpressionObj
                MemberAssignmentBindingObj -> FormulaExpressionObj
            
                // → TypeReferenceObj (back-refs)
                TypeArgumentCollectionObj -> TypeReferenceObj
                TypeReferenceObj          -> TypeReferenceObj [label="self"]
            
                // Compound nodes
                edge [style=solid, color="#333333", arrowhead=vee];
                ListInitExpressionObj   -> NewExpressionObj
                ListInitExpressionObj   -> ElementInitCollectionObj
                MemberInitExpressionObj -> NewExpressionObj
                MemberInitExpressionObj -> MemberBindingCollectionObj
            
                // Collections → binding types
                edge [style=dashed, color="#999999", arrowhead=vee];
                ElementInitCollectionObj   -> ElementInitBindingObj
                MemberBindingCollectionObj -> MemberMemberBindingObj
                MemberBindingCollectionObj -> MemberListBindingObj
                MemberBindingCollectionObj -> MemberAssignmentBindingObj
            
                // Binding recursive refs
                edge [style=solid, color="#333333", arrowhead=vee];
                MemberMemberBindingObj -> MemberBindingCollectionObj
                MemberListBindingObj   -> ElementInitCollectionObj
            }

    .. tab-item:: TypeScript Interfaces

        .. code-block:: typescript

            export type FormulaExpressionObj = UnaryExpressionObj | BinaryExpressionObj | ConditionExpressionObj | ConstantExpressionObj |
                ConvertExpressionObj | DefaultExpressionObj | IndexExpressionObj | InvokeExpressionObj | LambdaExpressionObj | MemberExpressionObj |
                NewArrayBoundExpressionObj | NewArrayInitExpressionObj | ListInitExpressionObj | MemberInitExpressionObj | NewExpressionObj |
                TypeIsExpressionObj | TypeOfExpressionObj;
            
            export interface UnaryExpressionObj {
                'expressionType': 'UncheckedScope' | 'CheckedScope' | 'Group' | 'UnaryPlus' | 'Negate' | 'NegateChecked' | 'Not' | 'Complement';
                'expression': FormulaExpressionObj;
            }
            
            export interface BinaryExpressionObj {
                'expressionType': 'Divide' | 'MultiplyChecked' | 'Multiply' | 'Power' | 'Modulo' | 'AddChecked' | 'Add' | 'SubtractChecked' | 'Subtract' | 'LeftShift' | 'RightShift' | 'GreaterThan' | 'GreaterThanOrEqual' | 'LessThan' | 'LessThanOrEqual' | 'Equal' | 'NotEqual' | 'And' | 'Or' | 'ExclusiveOr' | 'AndAlso' | 'OrElse' | 'Coalesce';
                'left': FormulaExpressionObj;
                'right': FormulaExpressionObj;
            };
            
            export interface ConditionExpressionObj {
                'expressionType': 'Condition';
                'test': FormulaExpressionObj;
                'ifTrue': FormulaExpressionObj;
                'ifFalse': FormulaExpressionObj;
            }
            
            export interface ConstantExpressionObj {
                'expressionType': 'Constant';
                'type': TypeReferenceObj | string;
                'value': any;
            };
            
            export interface ConvertExpressionObj {
                'expressionType': 'TypeAs' | 'Convert' | 'ConvertChecked';
                'type': TypeReferenceObj | string;
                'expression': FormulaExpressionObj;
            }
            
            export interface DefaultExpressionObj {
                'expressionType': 'Default';
                'type': TypeReferenceObj | string;
            }
            
            export interface IndexExpressionObj {
                'expressionType': 'Index';
                'expression': FormulaExpressionObj;
                'arguments': ArgumentCollectionObj;
                'useNullPropagation': boolean;
            }
            
            
            export interface InvokeExpressionObj {
                'expressionType': 'Invoke';
                'expression': FormulaExpressionObj;
                'arguments': ArgumentCollectionObj;
            }
            
            export interface LambdaExpressionObj {
                'expressionType': 'Lambda';
                'arguments': ArgumentCollectionObj;
                'expression': FormulaExpressionObj;
            }
            
            export interface MemberExpressionObj {
                'expressionType': 'MemberResolve';
                'name': string;
                'arguments'?: TypeArgumentCollectionObj;
                'expression'?: FormulaExpressionObj | null;
                'useNullPropagation': boolean;
            };
            
            export interface NewArrayBoundExpressionObj {
                'expressionType': 'NewArrayBounds';
                'type': TypeReferenceObj | string;
                'arguments': ArgumentCollectionObj;
            };
            
            export interface NewArrayInitExpressionObj {
                'expressionType': 'NewArrayInit';
                'type': TypeReferenceObj | string;
                'initializers': ArgumentCollectionObj;
            };
            
            export interface ListInitExpressionObj {
                'expressionType': 'ListInit';
                'new': NewExpressionObj;
                'initializers': ElementInitCollectionObj;
            };
            
            export interface MemberInitExpressionObj {
                'expressionType': 'MemberInit';
                'new': NewExpressionObj;
                'bindings': MemberBindingCollectionObj;
            };
            
            export interface NewExpressionObj {
                'expressionType': 'New';
                'type': TypeReferenceObj | string;
                'arguments': ArgumentCollectionObj;
            }
            
            export interface TypeIsExpressionObj {
                'expressionType': 'TypeIs';
                'type': TypeReferenceObj | string;
                'expression': FormulaExpressionObj;
            }
            
            export interface TypeOfExpressionObj {
                'expressionType': 'TypeOf';
                'type': TypeReferenceObj | string;
            }
            
            export interface TypeReferenceObj {
                'name': string;
                'expressionType'?: 'MemberResolve';
                'expression'?: TypeReferenceObj | string;
                'arguments'?: TypeArgumentCollectionObj;
            }
            
            export interface ElementInitBindingObj {
                'expressionType': 'ElementInitBinding';
                'initializers': ArgumentCollectionObj;
            }
            
            export interface MemberMemberBindingObj {
                'expressionType': 'MemberBinding';
                'name': string;
                'bindings': MemberBindingCollectionObj;
            }
            
            export interface MemberListBindingObj {
                'expressionType': 'ListBinding';
                'name': string;
                'initializers': ElementInitCollectionObj;
            }
            
            export interface MemberAssignmentBindingObj {
                'expressionType': 'AssignmentBinding';
                'name': string;
                'expression': FormulaExpressionObj;
            }
            
            export interface TypeArgumentCollectionObj {
                [name: string]: TypeReferenceObj | string;
            }
            
            export interface ArgumentCollectionObj {
                [name: string]: FormulaExpressionObj | null;
            }
            
            export interface ElementInitCollectionObj {
                [name: string]: ElementInitBindingObj;
            }
            
            export interface MemberBindingCollectionObj {
                [name: string]: MemberMemberBindingObj | MemberListBindingObj | MemberAssignmentBindingObj;
            }

Structure
---------

Every AST node is a JSON object with at least one field:

- ``expressionType`` — a string that identifies the node type and determines which other fields are present.

Nodes that refer to types use either a plain string (e.g. ``"System.Int32"``) or a :ref:`type-reference` object for generic or nested types.

Argument collections (``ArgumentCollectionObj``) are JSON objects where each key is either a zero-based positional index (``"0"``, ``"1"``, ...) or a named parameter, and each value is a child expression node (or ``null`` for omitted optional arguments).

.. _type-reference:

TypeReference
-------------

A type reference describes a type, including generic types. It is used wherever a type is needed (e.g. ``Constant``, ``Convert``, ``New``).

Fields
~~~~~~

- ``name`` *(string)* — The simple or fully-qualified type name.
- ``expressionType`` *(string, optional)* — When set to ``"MemberResolve"``, the type is resolved relative to ``expression``.
- ``expression`` *(TypeReference or string, optional)* — The containing namespace or type from which ``name`` is resolved.
- ``arguments`` *(object, optional)* — A map of generic type arguments, where keys are type parameter names and values are TypeReference objects or strings.

Example: ``List<int>``

.. code-block:: json

   {
     "name": "List",
     "expression": { "expressionType": "MemberResolve", "name": "System.Collections.Generic" },
     "expressionType": "MemberResolve",
     "arguments": {
       "T": "System.Int32"
     }
   }

----

Expression Types
----------------

Constant
~~~~~~~~

Represents a literal value of a known type.

Fields
^^^^^^

- ``expressionType``: ``"Constant"``
- ``type`` — The type of the value (TypeReference or string).
- ``value`` — The literal value. The JSON type matches the declared type (number, string, boolean, null, etc.).

Example: the integer literal ``42``

.. code-block:: json

   {
     "expressionType": "Constant",
     "type": "System.Int32",
     "value": 42
   }

Example: the string literal ``"hello"``

.. code-block:: json

   {
     "expressionType": "Constant",
     "type": "System.String",
     "value": "hello"
   }

----

MemberResolve
~~~~~~~~~~~~~

Resolves a named member (variable, property, field, method, or type) optionally relative to another expression. This is also used to reference formula parameters by name.

Fields
^^^^^^

- ``expressionType``: ``"MemberResolve"``
- ``name`` *(string)* — The member name to resolve.
- ``expression`` *(FormulaExpression or null, optional)* — The target object. When ``null`` or absent, the name is resolved in the current scope (e.g. a formula parameter or a known type).
- ``arguments`` *(object, optional)* — Generic type arguments for the member, keyed by type parameter name.
- ``useNullPropagation`` *(boolean)* — When ``true``, the access uses null-safe semantics (equivalent to ``?.`` in C#). If ``expression`` evaluates to null, the result is null instead of throwing.

Example: accessing ``target.HP``

.. code-block:: json

   {
     "expressionType": "MemberResolve",
     "name": "HP",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "target",
       "expression": null,
       "useNullPropagation": false
     },
     "useNullPropagation": false
   }

Example: null-safe access ``target?.HP``

.. code-block:: json

   {
     "expressionType": "MemberResolve",
     "name": "HP",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "target",
       "expression": null,
       "useNullPropagation": false
     },
     "useNullPropagation": true
   }

----

Unary
~~~~~

Applies a unary operator to a single operand.

Fields
^^^^^^

- ``expressionType`` — One of:

  - ``"UnaryPlus"`` — identity (``+x``)
  - ``"Negate"`` — arithmetic negation (``-x``)
  - ``"NegateChecked"`` — arithmetic negation with overflow checking
  - ``"Not"`` — logical NOT (``!x``)
  - ``"Complement"`` — bitwise complement (``~x``)
  - ``"Group"`` — grouping parentheses, no operation change (``(x)``)
  - ``"UncheckedScope"`` — disables overflow checking for the inner expression (``unchecked(x)``)
  - ``"CheckedScope"`` — enables overflow checking for the inner expression (``checked(x)``)

- ``expression`` *(FormulaExpression)* — The operand.

Example: ``-x``

.. code-block:: json

   {
     "expressionType": "Negate",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "x",
       "expression": null,
       "useNullPropagation": false
     }
   }

----

Binary
~~~~~~

Applies a binary operator to two operands.

Fields
^^^^^^

- ``expressionType`` — One of:

  - Arithmetic: ``"Add"``, ``"AddChecked"``, ``"Subtract"``, ``"SubtractChecked"``, ``"Multiply"``, ``"MultiplyChecked"``, ``"Divide"``, ``"Modulo"``, ``"Power"``
  - Bitwise / Shift: ``"And"``, ``"Or"``, ``"ExclusiveOr"``, ``"LeftShift"``, ``"RightShift"``
  - Comparison: ``"Equal"``, ``"NotEqual"``, ``"LessThan"``, ``"LessThanOrEqual"``, ``"GreaterThan"``, ``"GreaterThanOrEqual"``
  - Logical short-circuit: ``"AndAlso"`` (``&&``), ``"OrElse"`` (``||``)
  - Null coalescing: ``"Coalesce"`` (``??``)

  Variants with ``Checked`` suffix perform overflow-checked arithmetic.

- ``left`` *(FormulaExpression)* — The left operand.
- ``right`` *(FormulaExpression)* — The right operand.

Example: ``weaponPower * targetResistance``

.. code-block:: json

   {
     "expressionType": "Multiply",
     "left": {
       "expressionType": "MemberResolve",
       "name": "weaponPower",
       "expression": null,
       "useNullPropagation": false
     },
     "right": {
       "expressionType": "MemberResolve",
       "name": "targetResistance",
       "expression": null,
       "useNullPropagation": false
     }
   }

----

Condition
~~~~~~~~~

A conditional (ternary) expression: ``test ? ifTrue : ifFalse``.

Fields
^^^^^^

- ``expressionType``: ``"Condition"``
- ``test`` *(FormulaExpression)* — The boolean condition.
- ``ifTrue`` *(FormulaExpression)* — Evaluated when ``test`` is true.
- ``ifFalse`` *(FormulaExpression)* — Evaluated when ``test`` is false.

Example: ``x > 0 ? x : -x``

.. code-block:: json

   {
     "expressionType": "Condition",
     "test": {
       "expressionType": "GreaterThan",
       "left": { "expressionType": "MemberResolve", "name": "x", "expression": null, "useNullPropagation": false },
       "right": { "expressionType": "Constant", "type": "System.Int32", "value": 0 }
     },
     "ifTrue": {
       "expressionType": "MemberResolve",
       "name": "x",
       "expression": null,
       "useNullPropagation": false
     },
     "ifFalse": {
       "expressionType": "Negate",
       "expression": { "expressionType": "MemberResolve", "name": "x", "expression": null, "useNullPropagation": false }
     }
   }

----

Convert / TypeAs
~~~~~~~~~~~~~~~~

Converts or casts an expression to a different type.

Fields
^^^^^^

- ``expressionType`` — One of:

  - ``"Convert"`` — explicit cast; throws on failure.
  - ``"ConvertChecked"`` — explicit cast with overflow checking.
  - ``"TypeAs"`` — safe cast; returns null if the object is not of the target type (equivalent to ``as`` in C#).

- ``type`` — The target type (TypeReference or string).
- ``expression`` *(FormulaExpression)* — The expression to convert.

Example: ``(float)damage``

.. code-block:: json

   {
     "expressionType": "Convert",
     "type": "System.Single",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "damage",
       "expression": null,
       "useNullPropagation": false
     }
   }

----

Default
~~~~~~~

Produces the default value for a type (e.g. ``0`` for numeric types, ``null`` for reference types).

Fields
^^^^^^

- ``expressionType``: ``"Default"``
- ``type`` — The type whose default value to produce (TypeReference or string).

Example: ``default(Int32)``

.. code-block:: json

   {
     "expressionType": "Default",
     "type": "Int32"
   }

----

TypeIs
~~~~~~

Tests whether an expression is of a given type (equivalent to ``is`` in C#). Evaluates to a boolean.

Fields
^^^^^^

- ``expressionType``: ``"TypeIs"``
- ``type`` — The type to test against (TypeReference or string).
- ``expression`` *(FormulaExpression)* — The expression whose type is tested.

Example: ``obj is Enemy``

.. code-block:: json

   {
     "expressionType": "TypeIs",
     "type": "Enemy",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "obj",
       "expression": null,
       "useNullPropagation": false
     }
   }

----

TypeOf
~~~~~~

Returns the runtime type descriptor for the given type (equivalent to ``typeof(T)`` in C#).

Fields
^^^^^^

- ``expressionType``: ``"TypeOf"``
- ``type`` — The type to retrieve (TypeReference or string).

Example: ``typeof(String)``

.. code-block:: json

   {
     "expressionType": "TypeOf",
     "type": "String"
   }

----

Index
~~~~~

Accesses an element of an indexable object (array, list, dictionary, or any type with an indexer).

Fields
^^^^^^

- ``expressionType``: ``"Index"``
- ``expression`` *(FormulaExpression)* — The collection or indexable object.
- ``arguments`` *(ArgumentCollectionObj)* — The index arguments, keyed by positional index (``"0"``, ``"1"``, ...).
- ``useNullPropagation`` *(boolean)* — When ``true``, the access is null-safe (``?[...]``). Returns null if ``expression`` is null.

Example: ``items[0]``

.. code-block:: json

   {
     "expressionType": "Index",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "items",
       "expression": null,
       "useNullPropagation": false
     },
     "arguments": {
       "0": { "expressionType": "Constant", "type": "Int32", "value": 0 }
     },
     "useNullPropagation": false
   }

----

Invoke
~~~~~~

Calls a method or invokes a delegate/function. The method itself is resolved as a ``MemberResolve`` node in the ``expression`` field.

Fields
^^^^^^

- ``expressionType``: ``"Invoke"``
- ``expression`` *(FormulaExpression)* — The callable to invoke (typically a ``MemberResolve`` node).
- ``arguments`` *(ArgumentCollectionObj)* — Arguments passed to the call, keyed by positional index (``"0"``, ``"1"``, ...) or parameter name.

Example: ``target.DoDamage(100)``

.. code-block:: json

   {
     "expressionType": "Invoke",
     "expression": {
       "expressionType": "MemberResolve",
       "name": "DoDamage",
       "expression": {
         "expressionType": "MemberResolve",
         "name": "target",
         "expression": null,
         "useNullPropagation": false
       },
       "useNullPropagation": false
     },
     "arguments": {
       "0": { "expressionType": "Constant", "type": "Int32", "value": 100 }
     }
   }

----

Lambda
~~~~~~

Defines an anonymous function (lambda). The ``arguments`` field declares the parameters; ``expression`` is the body.

Fields
^^^^^^

- ``expressionType``: ``"Lambda"``
- ``arguments`` *(ArgumentCollectionObj)* — Parameter declarations. Keys are parameter names; values are ``null`` (parameter type is inferred from context) or a ``MemberResolve`` expression denoting the declared type.
- ``expression`` *(FormulaExpression)* — The lambda body.

Example: ``x => x * 2``

.. code-block:: json

   {
     "expressionType": "Lambda",
     "arguments": {
       "x": null
     },
     "expression": {
       "expressionType": "Multiply",
       "left": { "expressionType": "MemberResolve", "name": "x", "expression": null, "useNullPropagation": false },
       "right": { "expressionType": "Constant", "type": "System.Int32", "value": 2 }
     }
   }

----

New
~~~

Instantiates a new object of a given type by calling a constructor.

Fields
^^^^^^

- ``expressionType``: ``"New"``
- ``type`` — The type to instantiate (TypeReference or string).
- ``arguments`` *(ArgumentCollectionObj)* — Constructor arguments, keyed by positional index (``"0"``, ``"1"``, ...) or parameter name.

Example: ``new Vector2(1.0, 0.5)``

.. code-block:: json

   {
     "expressionType": "New",
     "type": "Vector2",
     "arguments": {
       "0": { "expressionType": "Constant", "type": "System.Single", "value": 1.0 },
       "1": { "expressionType": "Constant", "type": "System.Single", "value": 0.5 }
     }
   }

----

NewArrayBounds
~~~~~~~~~~~~~~

Creates a new array with specified dimension sizes but without initializers.

Fields
^^^^^^

- ``expressionType``: ``"NewArrayBounds"``
- ``type`` — The element type of the array (TypeReference or string).
- ``arguments`` *(ArgumentCollectionObj)* — Dimension size expressions, keyed by dimension index (``"0"`` for one-dimensional arrays).

Example: ``new int[10]``

.. code-block:: json

   {
     "expressionType": "NewArrayBounds",
     "type": "System.Int32",
     "arguments": {
       "0": { "expressionType": "Constant", "type": "System.Int32", "value": 10 }
     }
   }

----

NewArrayInit
~~~~~~~~~~~~

Creates a new single-dimensional array and initializes it with a list of values.

Fields
^^^^^^

- ``expressionType``: ``"NewArrayInit"``
- ``type`` — The element type of the array (TypeReference or string).
- ``initializers`` *(ArgumentCollectionObj)* — Element expressions, keyed by positional index (``"0"``, ``"1"``, ...).

Example: ``new int[] { 1, 2, 3 }``

.. code-block:: json

   {
     "expressionType": "NewArrayInit",
     "type": "System.Int32",
     "initializers": {
       "0": { "expressionType": "Constant", "type": "System.Int32", "value": 1 },
       "1": { "expressionType": "Constant", "type": "System.Int32", "value": 2 },
       "2": { "expressionType": "Constant", "type": "System.Int32", "value": 3 }
     }
   }

----

MemberInit
~~~~~~~~~~

Creates a new object and initializes its members. Combines a ``New`` node with a set of member bindings.

Fields
^^^^^^

- ``expressionType``: ``"MemberInit"``
- ``new`` *(NewExpression)* — The object construction node.
- ``bindings`` *(MemberBindingCollectionObj)* — A map of member bindings, keyed by member name. Each value is one of:

  - ``AssignmentBinding`` — assigns an expression to a member.
  - ``MemberBinding`` — recursively initializes members of a nested object.
  - ``ListBinding`` — adds elements to a collection member.

Example: ``new Vector2 { X = 1.0, Y = 0.5 }``

.. code-block:: json

   {
     "expressionType": "MemberInit",
     "new": {
       "expressionType": "New",
       "type": "Vector2",
       "arguments": {}
     },
     "bindings": {
       "X": {
         "expressionType": "AssignmentBinding",
         "name": "X",
         "expression": { "expressionType": "Constant", "type": "System.Single", "value": 1.0 }
       },
       "Y": {
         "expressionType": "AssignmentBinding",
         "name": "Y",
         "expression": { "expressionType": "Constant", "type": "System.Single", "value": 0.5 }
       }
     }
   }

----

ListInit
~~~~~~~~

Creates a new collection object and populates it using an initializer list. Each element is added by calling the collection's ``Add`` method (or equivalent).

Fields
^^^^^^

- ``expressionType``: ``"ListInit"``
- ``new`` *(NewExpression)* — The collection construction node.
- ``initializers`` *(ElementInitCollectionObj)* — A map of element initializers, keyed by positional index. Each value is an ``ElementInitBinding`` object with:

  - ``expressionType``: ``"ElementInitBinding"``
  - ``initializers`` *(ArgumentCollectionObj)* — Arguments passed to the Add method for this element.

Example: ``new List<int> { 1, 2, 3 }``

.. code-block:: json

   {
     "expressionType": "ListInit",
     "new": {
       "expressionType": "New",
       "type": {
         "name": "List",
         "expression": "System.Collections.Generic",
         "expressionType": "MemberResolve",
         "arguments": { "T": "System.Int32" }
       },
       "arguments": {}
     },
     "initializers": {
       "0": {
         "expressionType": "ElementInitBinding",
         "initializers": {
           "0": { "expressionType": "Constant", "type": "System.Int32", "value": 1 }
         }
       },
       "1": {
         "expressionType": "ElementInitBinding",
         "initializers": {
           "0": { "expressionType": "Constant", "type": "System.Int32", "value": 2 }
         }
       },
       "2": {
         "expressionType": "ElementInitBinding",
         "initializers": {
           "0": { "expressionType": "Constant", "type": "System.Int32", "value": 3 }
         }
       }
     }
   }

----

Member Bindings
---------------

Member bindings are used inside ``MemberInit`` nodes to specify how object members are initialized.

AssignmentBinding
~~~~~~~~~~~~~~~~~

Assigns a value to a named member.

- ``expressionType``: ``"AssignmentBinding"``
- ``name`` *(string)* — Member name.
- ``expression`` *(FormulaExpression)* — The value to assign.

MemberBinding
~~~~~~~~~~~~~

Recursively initializes the members of a nested object member without reassigning the member itself.

- ``expressionType``: ``"MemberBinding"``
- ``name`` *(string)* — Member name of the nested object.
- ``bindings`` *(MemberBindingCollectionObj)* — Nested bindings applied to the member's sub-members.

ListBinding
~~~~~~~~~~~

Adds elements to a collection member using element initializers.

- ``expressionType``: ``"ListBinding"``
- ``name`` *(string)* — Member name of the collection.
- ``initializers`` *(ElementInitCollectionObj)* — Elements to add, keyed by positional index.

----

Implementing an Interpreter
----------------------------

An interpreter for this AST typically consists of a recursive ``evaluate(node, context)`` function that dispatches on ``expressionType``. The ``context`` holds the current scope: parameter values, known types, and available members.

Suggested steps:

1. **Dispatch** — read ``expressionType`` from the node and select the appropriate handler.
2. **Recurse** — evaluate child nodes before computing the current node's result (bottom-up evaluation).
3. **Scope** — maintain a variable scope for formula parameters; ``MemberResolve`` with a null ``expression`` looks up names in this scope first, then in known types.
4. **Type resolution** — map type names (strings or TypeReference objects) to concrete types in your runtime. Built-in types follow .NET naming conventions (e.g. ``System.Int32``, ``System.String``).
5. **Null propagation** — for ``MemberResolve`` and ``Index`` nodes with ``useNullPropagation: true``, short-circuit and return null when the target expression is null.
6. **Overflow checking** — ``Checked`` variants of arithmetic operators should raise an error on integer overflow; ``UncheckedScope`` / ``CheckedScope`` change the checking mode for a sub-tree.

See also
--------

- :doc:`Game Data Structure <game_data_structure>`
- :doc:`Data Types <../gamedata/datatypes/list>`
- `Abstract Syntax Tree (Wikipedia) <https://en.wikipedia.org/wiki/Abstract_syntax_tree>`_
- `Expression tree pattern <https://en.wikipedia.org/wiki/Expression_(computer_science)>`_
