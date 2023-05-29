REST API
========

REST API is experimental feature and should not be used in production environment.


Working with REST API
---------------------
To make requests, you will need an *API Key* obtained from your profile page. Add the ``Authorize: Basic <api-key> header to all of your HTTP requests.
You can utilize `the Swagger UI <https://charon.live/api/index.html>`_ to perform test requests. In the ``Swagger UI``, click on the *Authorize* button and paste your *API Key* for authentication.

.. openapi:: ../openapi.yml
   :group:
   :exclude:
      /app/*
      /billing/notification/