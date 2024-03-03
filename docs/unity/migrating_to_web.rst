Migrating to Web Application
============================

To migrate to the web application, you can do it through a `backup <../web/migrating_to_web>` or through the "Connection" mechanism.  

In short: you need to create an empty project in the web application, click **Connect** in Unity's Inspector window, and specify that you want to upload data to the web application.  

Migration with Connection
-------------------------

Be sure to back up your local data before making any connections.

1. In the Web Application: on the Home screen, click on **Create Project**  
2. Specify the project name, tags, and script language  
3. Click the **Create** button   
4. In the Unity Editor: select your game data file in the **Project** window  
5. In the **Inspector** window, click **Connect**  
6. In the dialog that opens, click on the **Profile → API Keys** link  
7. In the Web Application: a page of your profile on the *API Keys* management page should have opened in your browser  
8. Click **Create API Key...** button  
9. Fill in the name and expiration time, then click the **Create** button  
10. Click the **Copy** button in the list of keys next to the newly created key labeled "New!"  
11. In the Unity Editor: paste the *API Key* into the corresponding field in the window  
12. Check the *Upload local data...* checkbox, it is only available when the selected *Project* is empty and does not contain any data.  
13. Click the **Upload** button"
14. Done  

See also
--------
- :doc:`Basics <basics>`
- `Web-based Application <https://gamedevware.com?ref=documentation>`_