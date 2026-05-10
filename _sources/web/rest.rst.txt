REST API
========

The web edition of Charon exposes a REST API at ``https://charon.live/api/v1``.
It covers the full feature set of the application — data CRUD, import/export,
branch management, code generation, validation, and more.

An interactive API explorer (Swagger UI) is available at
`https://charon.live/api/index.html <https://charon.live/api/index.html>`_.

.. contents:: On this page
   :local:
   :depth: 2

----

Authentication
--------------

All endpoints require a bearer token in the ``Authorization`` header.
Two credential types are accepted:

**API Key (recommended for CI/CD and scripts)**
   Obtain an API key from **User Profile → API Keys → Generate API Key**.
   Use it directly as the bearer value:

   .. code-block:: http

      Authorization: Bearer <api-key>

See :doc:`cli_access_to_web_project` for step-by-step instructions on
generating one.

----

Request and Response Formats
-----------------------------

All endpoints default to ``application/json``. Use the ``Accept`` and
``Content-Type`` headers to switch between supported formats.

+------------------------------------------------------+-----------------------------+
| Format                                               | Media type                  |
+======================================================+=============================+
| JSON (default)                                       | ``application/json``        |
+------------------------------------------------------+-----------------------------+
| MessagePack (binary, compact)                        | ``application/x-msgpack``   |
+------------------------------------------------------+-----------------------------+
| BSON                                                 | ``application/bson``        |
+------------------------------------------------------+-----------------------------+
| Excel                                                | ``application/vnd.          |
|                                                      | openxmlformats-officedocument|
|                                                      | .spreadsheetml.sheet``      |
+------------------------------------------------------+-----------------------------+
| XLIFF (translation)                                  | ``application/xliff+xml``   |
+------------------------------------------------------+-----------------------------+

Most data endpoints also support these formats for both request bodies and
responses. Prefer MessagePack for large payloads in performance-sensitive
pipelines.

----

Finding Your IDs
----------------

Most data endpoints require ``projectId`` and/or ``dataSourceId``.

``projectId``
   Visible in the browser URL when you open a project:
   ``https://charon.live/view/project/<projectId>/``.

``dataSourceId``
   Each branch has its own data source ID. Retrieve it via
   ``GET /project/{projectId}/``:

   .. code-block:: bash

      curl -s "https://charon.live/api/v1/project/{projectId}/" \
        -H "Authorization: Bearer $CHARON_API_KEY" | jq '.result.branches[]'

   The response includes each branch name and its ``id``, which is the
   ``dataSourceId`` used in all ``/datasource/`` endpoints.

----

Response Envelope
-----------------

Every response — success or failure — shares the same top-level JSON structure:

.. code-block:: json

   {
     "result": { ... },
     "errors": []
   }

One of fields are always present in the response body:

- ``result`` — contains the operation's output on success. The shape varies by
  endpoint (a single document, a list, a backup payload, etc.). On failure the
  field is absent.
- ``errors`` — an array of error objects. Absent on success; contains
  one or more entries on failure.

The intended semantics are a discriminated union — either ``result`` carries
meaningful data **or** ``errors`` is non-empty.

**Success example** — ``GET /datasource/{id}/collection/Item/``

.. code-block:: json

   {
     "result": {
       "document": { "Id": "Sword", "Name": "Iron Sword", "Damage": 20 },
       "meta": { "schemaId": "592fc86c983a36266c0912a0", "path": "/Item/Sword" }
     }
   }

**No-content success** — some write operations (create branch, commit
transaction, etc.) return HTTP ``204`` with no body.

The simplest way to detect success in code is to check the HTTP status code
first. A ``2xx`` status means the operation succeeded; anything else means at
least one entry will be present in ``errors``.

----

Error Responses
---------------

Every failed response uses the same JSON envelope regardless of the HTTP status
code:

.. code-block:: json

   {
     "errors": [
       {
         "code": "resourceNotFound",
         "message": "Document with id 'Sword' not found in collection 'Item'."
       }
     ]
   }

Fields:

- ``result`` — is absent on error.
- ``errors`` — array of one or more error objects. Each object has:

  - ``code`` *(string)* — machine-readable error code from the ``ErrorCode`` enum (see below).
  - ``message`` *(string)* — human-readable description of the problem.
  - Additional fields may be present for specific error types (e.g. ``parameterName``, ``path``).

HTTP status codes and their typical error codes:

+-------+----------------------------+----------------------------------------------+
| HTTP  | Typical ``code`` value     | When it occurs                               |
+=======+============================+==============================================+
| 400   | ``invalidRequestBody``     | Malformed JSON body                          |
|       +----------------------------+----------------------------------------------+
|       | ``invalidParameterValue``  | Query/route parameter has wrong type or value|
|       +----------------------------+----------------------------------------------+
|       | ``missingParameterValue``  | Required parameter absent                    |
|       +----------------------------+----------------------------------------------+
|       | ``invalidImportData``      | Imported document fails schema validation    |
+-------+----------------------------+----------------------------------------------+
| 401   | ``authenticationFailed``   | Missing or invalid ``Authorization`` header  |
+-------+----------------------------+----------------------------------------------+
| 403   | ``authorizationFailed``    | Authenticated but lacks required permission  |
|       +----------------------------+----------------------------------------------+
|       | ``resourceReadOnly``       | Target resource is read-only                 |
+-------+----------------------------+----------------------------------------------+
| 404   | ``resourceNotFound``       | Project, branch, or document does not exist  |
+-------+----------------------------+----------------------------------------------+
| 409   | ``duplicateTransaction``   | Transaction ID already in use                |
|       +----------------------------+----------------------------------------------+
|       | ``abortedTransaction``     | Transaction was rolled back by the server    |
|       +----------------------------+----------------------------------------------+
|       | ``completedTransaction``   | Transaction already committed or rolled back |
|       +----------------------------+----------------------------------------------+
|       | ``duplicateUniqueValue``   | Document violates a unique-value constraint  |
+-------+----------------------------+----------------------------------------------+
| 429   | ``tooManyRequests``        | Rate limit exceeded                          |
+-------+----------------------------+----------------------------------------------+
| 503   | ``serviceUnavailable``     | Server temporarily unavailable               |
+-------+----------------------------+----------------------------------------------+
| 5xx   | ``genericError``           | Unexpected server-side error                 |
+-------+----------------------------+----------------------------------------------+

Error code reference
~~~~~~~~~~~~~~~~~~~~

The full set of ``code`` values, grouped by category:

**General**

+------------------------------+----------------------------------------------+
| Code                         | Meaning                                      |
+==============================+==============================================+
| ``genericError``             | Unexpected server error.                     |
+------------------------------+----------------------------------------------+
| ``resourceNotFound``         | Requested resource does not exist.           |
+------------------------------+----------------------------------------------+
| ``serviceUnavailable``       | Server is temporarily unavailable.           |
+------------------------------+----------------------------------------------+
| ``tooManyRequests``          | Too many concurrent requests from this       |
|                              | client.                                      |
+------------------------------+----------------------------------------------+
| ``operationNotSupported``    | Operation is not supported by this resource. |
+------------------------------+----------------------------------------------+
| ``authenticationFailed``     | Credentials are missing or invalid.          |
+------------------------------+----------------------------------------------+
| ``authorizationFailed``      | Permission denied for this operation.        |
+------------------------------+----------------------------------------------+
| ``resourceReadOnly``         | Target resource is read-only.                |
+------------------------------+----------------------------------------------+

**Request validation**

+---------------------------------------+----------------------------------------------+
| Code                                  | Meaning                                      |
+=======================================+==============================================+
| ``invalidRequestBody``                | Request body could not be parsed.            |
+---------------------------------------+----------------------------------------------+
| ``invalidParameterValue``             | Parameter has an unacceptable value.         |
+---------------------------------------+----------------------------------------------+
| ``missingParameterValue``             | Required parameter is absent.                |
+---------------------------------------+----------------------------------------------+
| ``invalidParameterPattern``           | String parameter does not match the required |
|                                       | pattern.                                     |
+---------------------------------------+----------------------------------------------+
| ``parameterBelowMinValue``            | Numeric parameter is below the minimum       |
| ``parameterBelowMinValueInclusive``   | (exclusive / inclusive).                     |
+---------------------------------------+----------------------------------------------+
| ``parameterAboveMaxValue``            | Numeric parameter exceeds the maximum        |
| ``parameterAboveMaxValueInclusive``   | (exclusive / inclusive).                     |
+---------------------------------------+----------------------------------------------+
| ``parameterBelowMinLength``           | String parameter is shorter than minimum     |
|                                       | length.                                      |
+---------------------------------------+----------------------------------------------+
| ``parameterAboveMaxLength``           | String parameter exceeds maximum length.     |
+---------------------------------------+----------------------------------------------+
| ``parameterBelowMinSize``             | Collection parameter has fewer items than    |
|                                       | the minimum.                                 |
+---------------------------------------+----------------------------------------------+
| ``parameterAboveMaxSize``             | Collection parameter exceeds maximum item    |
|                                       | count.                                       |
+---------------------------------------+----------------------------------------------+
| ``duplicateParameterItems``           | Collection parameter contains duplicate      |
|                                       | values.                                      |
+---------------------------------------+----------------------------------------------+
| ``invalidImportData``                 | Import payload does not match the expected   |
|                                       | schema.                                      |
+---------------------------------------+----------------------------------------------+

**JSON Patch**

+-------------------------------+----------------------------------------------+
| Code                          | Meaning                                      |
+===============================+==============================================+
| ``invalidJsonPatchParameter`` | Patch document is malformed.                 |
+-------------------------------+----------------------------------------------+
| ``jsonPatchTestFailed``       | A ``test`` operation in the patch failed.    |
+-------------------------------+----------------------------------------------+
| ``forbiddenJsonPatchOperation``| Patch attempts a prohibited operation.      |
+-------------------------------+----------------------------------------------+

**Data source / transaction**

+------------------------------+----------------------------------------------+
| Code                         | Meaning                                      |
+==============================+==============================================+
| ``referencedSchemaDeleted``  | Operation references a schema that has been  |
|                              | deleted.                                     |
+------------------------------+----------------------------------------------+
| ``protectedDocument``        | Document is protected and cannot be modified |
|                              | or deleted.                                  |
+------------------------------+----------------------------------------------+
| ``nonRootDocument``          | Operation requires a root document but an    |
|                              | embedded document was supplied.              |
+------------------------------+----------------------------------------------+
| ``abortedTransaction``       | Transaction was aborted by the server (e.g.  |
|                              | timeout or conflict).                        |
+------------------------------+----------------------------------------------+
| ``completedTransaction``     | Transaction has already been committed or    |
|                              | rolled back.                                 |
+------------------------------+----------------------------------------------+
| ``duplicateTransaction``     | A transaction with this ID already exists.   |
+------------------------------+----------------------------------------------+
| ``missingTransaction``       | The referenced transaction ID does not exist.|
+------------------------------+----------------------------------------------+
| ``failedMetadataLoad``       | Schema/metadata could not be loaded.         |
+------------------------------+----------------------------------------------+

**Document value validation**

These codes appear inside import or create/update responses when individual
field values fail validation. They are also returned by the ``POST /validity/``
endpoint.

+--------------------------------------+----------------------------------------------+
| Code                                 | Meaning                                      |
+======================================+==============================================+
| ``invalidTimeFormat``                | Value does not match the time format.        |
+--------------------------------------+----------------------------------------------+
| ``invalidDateFormat``                | Value does not match the date format.        |
+--------------------------------------+----------------------------------------------+
| ``invalidLocalizedTextFormat``       | Localized text value is malformed.           |
+--------------------------------------+----------------------------------------------+
| ``invalidTextFormat``                | Text value is malformed.                     |
+--------------------------------------+----------------------------------------------+
| ``invalidLogicalFormat``             | Boolean value is malformed.                  |
+--------------------------------------+----------------------------------------------+
| ``invalidNumberFormat``              | Decimal number value is malformed.           |
+--------------------------------------+----------------------------------------------+
| ``invalidIntegerFormat``             | Integer value is malformed.                  |
+--------------------------------------+----------------------------------------------+
| ``invalidPickListFormat``            | Pick list value does not match any defined   |
|                                      | option.                                      |
+--------------------------------------+----------------------------------------------+
| ``invalidMultiPickListFormat``       | Multi-pick list value is malformed.          |
+--------------------------------------+----------------------------------------------+
| ``invalidDocumentFormat``            | Embedded document value is malformed.        |
+--------------------------------------+----------------------------------------------+
| ``invalidDocumentCollectionFormat``  | Embedded document collection is malformed.   |
+--------------------------------------+----------------------------------------------+
| ``invalidReferenceFormat``           | Reference value is malformed.                |
+--------------------------------------+----------------------------------------------+
| ``invalidReferenceCollectionFormat`` | Reference collection is malformed.           |
+--------------------------------------+----------------------------------------------+
| ``invalidFormulaFormat``             | Formula expression is malformed.             |
+--------------------------------------+----------------------------------------------+
| ``nullValue``                        | Required field is null.                      |
+--------------------------------------+----------------------------------------------+
| ``emptyValue``                       | Required field is empty.                     |
+--------------------------------------+----------------------------------------------+
| ``overflowedValue``                  | Numeric value exceeds the type's range.      |
+--------------------------------------+----------------------------------------------+
| ``exceededValueLength``              | String value exceeds maximum length.         |
+--------------------------------------+----------------------------------------------+
| ``exceededCollectionSize``           | Collection exceeds maximum item count.       |
+--------------------------------------+----------------------------------------------+
| ``brokenReference``                  | Reference points to a non-existent document. |
+--------------------------------------+----------------------------------------------+
| ``missingTranslation``               | Localized text is missing a required         |
|                                      | translation.                                 |
+--------------------------------------+----------------------------------------------+
| ``duplicateUniqueValue``             | Value violates a unique constraint.          |
+--------------------------------------+----------------------------------------------+
| ``invalidIdFormat``                  | Document ``Id`` value is malformed.          |
+--------------------------------------+----------------------------------------------+
| ``invalidGeneratedIdFormat``         | Auto-generated ID does not match the schema's|
|                                      | ID generator format.                         |
+--------------------------------------+----------------------------------------------+
| ``documentsInRootCollection``        | Embedded documents were supplied as root     |
|                                      | documents.                                   |
+--------------------------------------+----------------------------------------------+
| ``missingSettingsDocument``          | A required settings document is absent.      |
+--------------------------------------+----------------------------------------------+
| ``duplicateSettingsDocument``        | More than one settings document exists.      |
+--------------------------------------+----------------------------------------------+
| ``emptyUnion``                       | Tagged union has no selected option.         |
+--------------------------------------+----------------------------------------------+
| ``conflictingUnionOptions``          | Tagged union has more than one selected      |
|                                      | option.                                      |
+--------------------------------------+----------------------------------------------+

**Schema / metadata validation**

These codes appear when a schema definition itself is invalid (e.g. during
schema create or update operations).

+---------------------------------------+----------------------------------------------+
| Code                                  | Meaning                                      |
+=======================================+==============================================+
| ``invalidNameFormat``                 | Schema or property name is not a valid C     |
|                                       | identifier.                                  |
+---------------------------------------+----------------------------------------------+
| ``reservedName``                      | Name conflicts with a reserved keyword.      |
+---------------------------------------+----------------------------------------------+
| ``invalidSize``                       | Size value is out of the allowed range.      |
+---------------------------------------+----------------------------------------------+
| ``invalidLanguage``                   | Language code is not a valid BCP-47 tag.     |
+---------------------------------------+----------------------------------------------+
| ``recursiveReferenceType``            | Schema has a circular reference that is not  |
|                                       | allowed.                                     |
+---------------------------------------+----------------------------------------------+
| ``invalidIdDataType``                 | The ``Id`` property uses a data type that is |
|                                       | not allowed for identifiers.                 |
+---------------------------------------+----------------------------------------------+
| ``invalidDataTypeChange``             | Changing a property's data type in a way that|
|                                       | would corrupt existing data.                 |
+---------------------------------------+----------------------------------------------+
| ``invalidIdGeneratorChange``          | Changing the ID generator in an incompatible |
|                                       | way.                                         |
+---------------------------------------+----------------------------------------------+
| ``invalidRequirementForDataType``     | Requirement level is incompatible with the   |
|                                       | property's data type.                        |
+---------------------------------------+----------------------------------------------+
| ``nonOptionalTaggedUnionProperty``    | A tagged-union property must be optional.    |
+---------------------------------------+----------------------------------------------+

**Schema specification validation**

+-------------------------------+----------------------------------------------+
| Code                          | Meaning                                      |
+===============================+==============================================+
| ``invalidIconFormat``         | Icon specification is malformed.             |
+-------------------------------+----------------------------------------------+
| ``invalidDisplayTextTemplate``| Display text template expression is invalid. |
+-------------------------------+----------------------------------------------+
| ``invalidPickName``           | Pick list option name is invalid.            |
+-------------------------------+----------------------------------------------+
| ``duplicatePickName``         | Pick list has duplicate option names.        |
+-------------------------------+----------------------------------------------+
| ``invalidPickValue``          | Pick list option value is invalid.           |
+-------------------------------+----------------------------------------------+
| ``invalidParameterName``      | Formula parameter name is invalid.           |
+-------------------------------+----------------------------------------------+
| ``duplicateParameterName``    | Formula has duplicate parameter names.       |
+-------------------------------+----------------------------------------------+
| ``invalidTypeName``           | Type name in specification is invalid.       |
+-------------------------------+----------------------------------------------+
| ``invalidTypeReference``      | Type reference cannot be resolved.           |
+-------------------------------+----------------------------------------------+
| ``invalidPrecision``          | Decimal precision value is out of range.     |
+-------------------------------+----------------------------------------------+
| ``invalidRowCount``           | Row count specification is out of range.     |
+-------------------------------+----------------------------------------------+

----

See also
--------

- :doc:`cli_access_to_web_project`
- :doc:`workspaces_and_projects`
- :doc:`permission_and_roles`
- :doc:`../advanced/backup_restore`
- :doc:`../advanced/import_export`
- :doc:`../advanced/cicd`
- :doc:`../advanced/patch_diff`