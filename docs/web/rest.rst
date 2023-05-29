REST API
========

REST API is experimental feature and should not be used in production environment.


Working with REST API
---------------------
To make requests, you will need an :doc:`API Key <cli_access_to_web_project>` obtained from your profile page. Add the ``Authorize: Basic <api-key>`` header to all of your HTTP requests.
You can utilize the `Swagger UI <https://charon.live/api/index.html>`_ to perform test requests. In the *Swagger UI*, click on the *Authorize* button and paste your :doc:`API Key <cli_access_to_web_project>` for authentication.

.. openapi:: ../openapi.yml
   :group:
   :exclude:
      /app/*
      /billing/notification/