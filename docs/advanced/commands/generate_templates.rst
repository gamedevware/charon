Export Code Generation Templates
========================

Exports `T4 <https://learn.microsoft.com/en-us/visualstudio/modeling/code-generation-and-t4-text-templates>`_ code generation templates to a specified directory. 
These templates can be used with Visual Studio, Rider, Visual Studio Code with plugin, ``dotnet`` `tool <https://www.nuget.org/packages/dotnet-t4>`_ or other tools to generate source code.

- :ref:`CLI Installation <CommandLine_Installation>`
- :ref:`Commands Reference <CommandLine_Commands>`
- :doc:`Universal Parameters <universal_parameters>`
- :doc:`URL-based Input/Output <remote_input_output>`

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  dotnet charon GENERATE TEMPLATES --outputDirectory "c:\templates"
  

---------------
 Parameters
---------------

--outputDirectory
   Specifies the path where the templates should be written. It can be either an absolute or relative path to a directory. The specified directory must already be present.

   .. code-block:: bash
   
     # Windows
     --outputDirectory "c:\templates"
     
     # Linux or OSX
     --outputDirectory "~/templates"
     
     # Relative path
     --outputDirectory "./templates"
