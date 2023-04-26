Overview
==========

The ``Time`` data type in game data is equivalent to the ``TimeSpan`` data type in C#. It is used to store a duration or a time interval, such as the time it takes to complete a task or the length of a cutscene in a game. The ``Time`` data type is represented as a string in the format ``HH:mm:ss``, where HH is the number of hours, mm is the number of minutes, and ss is the number of seconds.

For example, if a task takes 2 hours and 30 minutes to complete, the ``Time`` data type value would be ``02:30:00``.

C# Type
   ``System.TimeSpan``
Uniqueness
   May NOT be checked for uniqueness.

Example
=======
.. code-block:: js

  // format: [DD.]HH:mm:ss

  "02:30:00" // 2 hours and 30 minutes
  "1.00:00:00" // 1 day
  60 // 60 seconds 
  120 // two minutes
  
  "-00:30:00" // could be negative
