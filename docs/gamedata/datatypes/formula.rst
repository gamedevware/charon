Overview
==========

Formula data type is a way to store and use C# expressions inside game data. It allows game developers to perform calculations based on certain inputs and parameters that are not known until runtime. A formula can be any valid C# expression that returns a value of any supported data type.

Formulas are typically used in situations where there are complex calculations involved, such as determining the damage a weapon does based on various factors like the target's resistance and the type of attack being used. By storing these calculations as formulas, game developers can easily modify and tweak them without having to recompile the entire game code.

During runtime, formulas can be evaluated using the values of any other properties or data types that are passed to formula as arguments. This allows for a great deal of flexibility in designing game mechanics and balancing gameplay.

For example, a formula for calculating the damage a weapon does to a target could be stored as follows:

.. code-block:: js
  
  (weaponPower * (1.0 - targetResistance)) * attackMultiplier
  
This formula takes the weapon power, subtracts the target's resistance, and then multiplies the result by an attack multiplier. 
The resulting value is the final amount of damage the weapon does to the target.

C# Type
   ``class``
Uniqueness
   May NOT be checked for uniqueness.
   
Example
=======

.. code-block:: js
  
  "target.HP < 100"
  "x != 0"
  "target.DoDamage(100)"
  "(weapon.Damage / target.DamageResistance) / 2"