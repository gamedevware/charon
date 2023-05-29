REST API
========

REST API is experimental feature and should not be used in production environment.


Testing REST API
---------------------
You can utilize the `Swagger UI <https://charon.live/api/index.html>`_ to perform test requests. In the *Swagger UI*, click on the *Authorize* button and paste your :doc:`API Key <cli_access_to_web_project>` for authentication.

Working with REST API
---------------------
To make requests, you will need an :doc:`API Key <cli_access_to_web_project>` obtained from your profile page. Add the `Authorization: <https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Authorization>`_ ``Basic <api-key>`` header to all of your HTTP requests. Also is recommeded to provide correct `User-Agent <https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/User-Agent>`_ header.

.. openapi:: ../openapi.yml
   :group:
   :exclude:
      /app/*
      /billing/notification/