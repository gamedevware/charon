Formula
=======

The **Formula** data type allows storing and evaluating C# expressions within game data. It enables developers to define logic that performs calculations based on dynamic inputs and parameters not known until runtime. A formula can be any valid C# expression that returns a value of a supported data type.

Formulas are especially useful in scenarios involving complex calculations, such as determining weapon damage based on factors like target resistance and attack type. By encapsulating such logic in formulas, developers can fine-tune gameplay mechanics without modifying or recompiling the source code.

At runtime, formulas are evaluated using arguments passed to them. These arguments can reference other data properties or objects, providing a high level of flexibility in defining game rules and balancing.

For example, a damage formula might look like this:

.. code-block:: js
  
  (weaponPower * (1.0 - targetResistance)) * attackMultiplier

This expression multiplies weapon power by a factor based on the target’s resistance and then scales the result by an attack multiplier. The final result is the computed damage.


Source Code Type
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Language                                              | Type                                                            |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C#                                                    | ``class``                                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | TypeScript                                            | ``class``                                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | C++ (Unreal Engine)                                   | ``UCLASS``                                                      |
   +-------------------------------------------------------+-----------------------------------------------------------------+
   | Haxe                                                  | ``class``                                                       |
   +-------------------------------------------------------+-----------------------------------------------------------------+
Uniqueness
   Formulas cannot be marked as unique.
Specification 
   Formulas support the following specification parameters:
   - ``param.<name>`` — Defines a formula parameter and its type.  
     Example: ``param.id=System.Int32``
   - ``resultType`` — Specifies the return type of the formula.  
     Example: ``resultType=System.String``
   - ``knownType`` — Declares types known to the formula. Only static members of known types can be accessed.  
     Example: ``knownType=System.FMath``
   - ``typeName`` — Custom type name for the generated class. If omitted, a name is derived from the containing schema and property.  
     Example: ``typeName=MyDamageCalculatingFormula``

Example
-------

.. code-block:: js
  
  "target.HP < 100"
  "x != 0"
  "target.DoDamage(100)"
  "(weapon.Damage / target.DamageResistance) / 2"