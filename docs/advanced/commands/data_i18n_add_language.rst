Add Translation Languages
=========================

Add translation languages to specified game data.

- :ref:`CLI Installation <CommandLine_Installation>`
- :doc:`Universal Parameters <universal_parameters>`
- :ref:`Commands Reference <CommandLine_Commands>`

---------------
 Command
---------------

.. code-block:: bash

  # local game data (windows)
  dnx dotnet-charon -- DATA I18N ADDLANGUAGE \
    --dataBase "c:\my app\gamedata.json" \
    --languages "es-ES" "en-GB"

  # remote game data
  dnx dotnet-charon -- DATA I18N ADDLANGUAGE \
    --dataBase "https://charon.live/view/data/My_Game/develop/" \
    --languages "es-ES" "en-GB" \
    --credentials "<API-Key>"

  
---------------
 Parameters
---------------

--dataBase
   Absolute or relative path to game data. Use quotation marks if your path contains spaces.

   .. code-block:: bash
   
     # local file
     --dataBase "c:\my app\gamedata.json"
     
     # remote server
     --dataBase "https://charon.live/view/data/My_Game/develop/"

--languages
   The list of languages to add. Values are `language tags (BCP 47) separated by space. <https://msdn.microsoft.com/en-US/library/system.globalization.cultureinfo.name(v=vs.110).aspx>`_.

--credentials
   The API key used to access remote server in case of *--dataBase* being URL.

--output
   Path to the file receiving the updated language list. If the file exists, it will be overwritten. The directory must already exist. Alternatively, you can output to `Standard Error <https://en.wikipedia.org/wiki/Standard_streams#Standard_error_(stderr)>`_, `Standard Output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_,  `/dev/null <https://en.wikipedia.org/wiki/Null_device>`_, or a :doc:`URL <remote_input_output>`.

   .. code-block:: bash

     # standard output (default)
     --output out
     --output con

     # standard error
     --output err

     # null device
     --output null

     # relative path (universal)
     --output "./languages.json"

--outputFormat
   Format of the returned language list.

   .. code-block:: bash

     # JSON (default)
     --outputFormat json

     # space separated list
     --outputFormat list

     # new line (OS specific) separated list
     --outputFormat table

--outputFormattingOptions
   Additional options for specified format.

This command supports :doc:`universal parameters <universal_parameters>`.

See also
--------

- :doc:`Internationalization <../internationalization>`
- :doc:`DATA I18N LANGUAGES <data_i18n_languages>`
- :doc:`DATA I18N EXPORT <data_i18n_export>`
- :doc:`DATA I18N IMPORT <data_i18n_import>`
- `BCP 47 language tags <https://en.wikipedia.org/wiki/IETF_language_tag>`_