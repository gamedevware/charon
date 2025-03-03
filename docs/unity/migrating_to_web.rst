Migrating to Web Application
============================

To migrate to the https://charon.live, you can do it through a `backup <../web/migrating_to_web>` or through the "Connection" mechanism.  

In short: you need to create an empty project in at https://charon.live, in Unity Editor in Inspector window click **Connect**, and specify that you want to upload data to the https://charon.live.  

Migration with Connection
-------------------------

Be sure to back up your local data before making any connections.

1. At https://charon.live: on the Home screen, click on **Create Project**.  
2. Specify the project name, tags, and script language.  
3. Click the **Create** button.  
4. In the Unity Editor: select your game data **.asset** file in the **Project** window.  
5. In the **Inspector** window, expand **<Not Connected>** foldout, click **Connect** button.  
6. In the dialog that opens, click on the **Profile → API Keys** link.  
7. At https://charon.live: a page of your profile on the *API Keys* management page should have opened in your browser.  
8. Click **Create API Key...** button.  
9. Fill in the name and expiration time, then click the **Create** button.  
10. Click the **Copy** button in the list of keys next to the newly created key labeled "New!".  
11. In the Unity Editor: paste the *API Key* into the corresponding field in the **Connect Game Data** window.  
12. Check the *Upload local data...* checkbox, it is only available when the selected *Project* is empty and does not contain any data.  
13. Click the **Upload** button".
14. Close **Connect Game Data** window  

See also
--------

- :doc:`Basics <basics>`
- `Charon Website <https://gamedevware.com>`_