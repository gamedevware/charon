Generate Text from Templates
============================

| Generates text from T4 templates into output directory.
| Note that this command is experimental and may not be reliable.
| It is recommended to use an IDE or open-source alternatives for generating text with T4 templates.
| See `GENERATE TEMPLATES <generate_templates.rst>`_ for details.

- `Installation <../command_line.rst#installation>`_
- `Commands Reference <../command_line.rst>`_

---------------
 Command
---------------

.. code-block:: bash

  # Windows
  Charon.exe GENERATE TEXT --templatePath "c:\my app\template.tt" --namespaces System System.Collection.Generic --outputPath "c:\my app\template.txt"

---------------
 Parameters
---------------

--templatePath
   Path to T4 template.

   .. code-block:: bash
   
     # local file
     --templatePath "c:\my app\template.tt"
     
--outputPath
   Specifies the path where the generated text should be written. It can be either an absolute or relative path to a file. The file's directory must already be present.

   .. code-block:: bash
   
     # Windows
     --outputPath "c:\my app\scripts\text.txt"
     
     # Linux or OSX
     --outputPath "~/my app/templates/text.txt"
     
     # Relative path
     --outputPath "./my app/templates/text.txt"
 
--references
   List of referenced assemblies used in template. Full path to assemblies should be specified.

   .. code-block:: bash
   
     # path
     --references "C:\Windows\Microsoft.NET\Framework64\v4.0.30319\System.Collections.Concurrent.dll"
     
--namespaces
   List of namespaces used in template.

   .. code-block:: bash
   
     # list of namespaces
     --namespaces System System.Collections System.Collections.Concurrent

--includes
   List of other T4 templates to include.
   
   .. code-block:: bash
   
     # relative path
     --includes "./include.t4"
     
     # Windows
     --includes "c:\my app\include.t4"
     
     # Linux or OSX
     --includes "~/my app/include.t4" "/var/lib/include.t4"
     
--referencePaths
   List of locations to search for referenced assemblies.
   
   .. code-block:: bash
   
     # relative path
     --includes "./libs/"
     
     # Windows
     --includes "C:\Windows\Microsoft.NET\Framework64\v4.0.30319\"
     
     # Linux or OSX
     --includes "/Library/Frameworks/Mono.framework/Commands/bin" "/user/lib/mono"
     
--createGenerator
   Set this flag to get generator's code instead on generation result.