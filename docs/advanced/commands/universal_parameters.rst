Universal parameters
====================

All commands accept universal parameters and environment variables.

--verbose
   Set this flag to get additional diagnostic information in logs.

--log <path>
   Add additional file logging to the existing logging configuration from ``appsettings.json``.

   .. code-block:: bash
   
     --log "./logs/charon.log"
   
--log
   Add additional terminal (`standard output <https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)>`_) logging to the existing logging configuration from ``appsettings.json``.
   
   .. code-block:: bash
   
     --log out
     # or
     --log con

--pause
   Wait for user prompt before the application exits.
   
Environment variables
=====================
 
In addition to the standard configuration redefinition `mechanism <https://learn.microsoft.com/en-us/aspnet/core/fundamentals/configuration/?view=aspnetcore-7.0#non-prefixed-environment-variables>`_ 
using environment variables, the following environment variables are also supported.

CHARON_API_KEY
   The `API key <../../online/cli_access_to_your_project.rst>`_ which is used to access the remote server. This environment variable is usually used in 
   conjunction with ``--dataBase``, which points to a remote server.
   
   .. code-block:: bash
   
     # Windows
     set CHARON_API_KEY=87758CC0D7C745D0948F2A8AFE61BC81
     
     # OSX or Linux
     export CHARON_API_KEY=87758CC0D7C745D0948F2A8AFE61BC81
