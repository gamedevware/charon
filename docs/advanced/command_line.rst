Most of Charon functionality could be accessed via CLI commands. The application itself uses the `getops <https://en.wikipedia.org/wiki/Getopts>`_ syntax.
You should be familiar with terminal on your OS to fully tap potential of CLI.

Syntax
======

Commands have the following syntax:

.. code-block:: bash

  Charon.exe COMMAND --parameterName <parameter-value>
   
  # parameters can have more than one value. 
  # Use space to separate values
  Charon.exe EXPORT --entities Item Armor "Project Settings" Quest

  # if your value contains a space, put it inside the quotation marks.
  # Escape characters and other rules depend on the OS you are running.
  Charon.exe SERVE --dataBase "c:\my application\my path.txt"
  
  # some parameters don't require a value (e.g. flag).
  Charon.exe VERSION --verbose
  
OSX and Linux
=============
To run ``Charon.exe`` on non-Windows systems, you need to have the ``mono`` runtime installed, which can be 
either a global one from ``$PATH`` or a local installation.

.. code-block:: bash

  # for globally installed mono
  mono Charon.exe VERSION

  # for non-brew installed mono on OSX
  /Library/Frameworks/Mono.framework/Commands/mono Charon.exe VERSION
  
  # for some linux installations
  /usr/bin/mono Charon.exe VERSION

Help
====

To display list of available commands type `--help` or `/?`.

.. code-block:: bash
  
  Charon.exe --help
  
  > Usage: Charon.exe <action> [--<param> || (--<param> <paramValue> ...) ...]
  >
  > Verbs:
  >  SERVE       Start a HTTP Server at specified 'port'.
  >  DATA        Data manipulation actions.
  >  GENERATE    Code generation actions.
  >  VERSION     Print version.
  
  # to display syntax and description for command just add --help as parameter
  Charon.exe DATA EXPORT --help
  
  > Usage:
  >   DATA EXPORT --dataBase <URI> [--entities [<TEXT>]] [--attributes [<TEXT>]] [--languages [<TEXT>]] [--output <TEXT>
  >               ] [--outputFormat <TEXT>] [--outputFormattingOptions [<TEXT>]] [--mode <EXPORTMODE>] [--credentials [<
  >               TEXT>]]
  
URL input/output parameters
===========================

Some command accept `URL <https://en.wikipedia.org/wiki/Uniform_Resource_Identifier>`_ as input/output parameter.

Table below show supported URL schemes:

+---------+----------------------------+-----------------------------------------------------+
| Scheme  | Input parameter            | Output parameter                                    |
+=========+============================+=====================================================+
| HTTP[S] | A GET request will be sent | A POST request with body containing output will be  |
|         |                            | sent                                                |
+---------+----------------------------+-----------------------------------------------------+
| FTP(S)  | A RETR command will be sent| A STOR command with output content will be sent     |
+---------+----------------------------+-----------------------------------------------------+
| FILE    | File will be read          | File will be written                                |
+---------+----------------------------+-----------------------------------------------------+

Any authentication data could be passed in *user* part of `URL <https://en.wikipedia.org/wiki/Uniform_Resource_Identifier>`_. 
More advanced authentication schemes are not supported.

Commands
========
