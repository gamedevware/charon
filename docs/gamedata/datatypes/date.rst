Overview
==========

The ``Date`` data type is used to store dates in `ISO 8601 <https://en.wikipedia.org/wiki/ISO_8601>`_ format, which includes the year, month, day, and time with `UTC <https://en.wikipedia.org/wiki/Coordinated_Universal_Time>`_ time zone. This data type is particularly useful for storing information about events that occur on specific dates or for tracking the age of entities. Since dates are stored with `UTC <https://en.wikipedia.org/wiki/Coordinated_Universal_Time>`_ time zone, the data can be consistently interpreted across different time zones.


C# Type
   ``System.DateTime``
Uniqueness
   May NOT be checked for uniqueness.
Format
   ``yyyy-MM-ddTHH:mm:ss.fffZ``

Example
=======
.. code-block:: js

  "2017-12-27T00:00:00.000Z"
  "1970-01-01T00:00:00.000Z" // it is better not to store dates before this mark for compatibility reasons
