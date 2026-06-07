Code Sample Name: PimExProvider

Feature Area: PIM Source Provider Extensibility 

Description: 
    The following application registers a source provider for the 
    Contacts and Calendar applications.  The source provider implements 
    3 features. 
    (1) Paints the contacts picture in the contacts app listview. 
    (2) Creates a custom summary card for the contact. 
    (3) Changes the background color of an appointment in the Agenda View.  
    All of these only apply to items which are associated with the source 
    provider (thru the source Id property).

Usage: 
    Follow the steps below to register and use this sample.
    (1) Create a few contacts with pictures and a few appointments. 
    (2) Kill the poutlook.exe process.  (Use the Remote Process Viewer Tool 
        that installs with Visual Studio to do this).
    (3) Call regsvrce pimexprovider.dll.  This is done by default when you 
        deploy the project.
    (4) Relaunch the contacts and/or calendar application to see the 
        customizations.

    Note: 
    The sample updates the source id for all existing contacts and calendar 
    items in the store. These updates are reverted when the dll is un-registered.

Assumptions: 
    None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK
    ActiveSync 4.0.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
