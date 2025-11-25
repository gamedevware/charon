# Source Code Notice

This repository contains documentation related to Charon.  
The `/src` directory is intentionally empty.

## Why is there no editor source code here?

The source code for the Charon editor itself is **not publicly available**.  
This folder exists to explain source code availability, the core application is distributed as a binary product.

If you are looking for the engine plugin sources, they are available publicly:

- **Unity, Unreal, and Extension–related repositories:**  
  https://github.com/gamedevware?tab=repositories

Charon is fully extensible through custom field editors and document editors.  
You can build your own UI components, node-based tools, inspectors, or integrations using the documented extension APIs, even without access to the editor’s internal source code.

## What about long-term availability?

In the unlikely event that Charon is ever discontinued or no longer maintained, a formal continuity plan is in place:

- The full server source code and private Docker images will be published under the MIT license by a designated successor.
- All offline tools (CLI, plugins, generated code, exporters) rely on public NuGet packages and will continue to function.
- Teams using the online service will retain complete, locally stored copies of their projects, which remain fully compatible with the standalone application.

This ensures that development workflows can continue without disruption and that the system can be self-hosted or forked by the community if ever required.