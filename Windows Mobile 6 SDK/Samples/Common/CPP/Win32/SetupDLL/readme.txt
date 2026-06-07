Code Sample Name: SetupDLL

Feature Area: Platform - Device Management

Description: 
    SetupDLL is a user-interactive sample of a setup.dll, which can be included 
    in CAB files to perform complex operations.  In its default form, it is 
    designed to work as the setup dll for the CfgClient SDK sample, should the 
    CfgClient be encapsulated in a cab file. During installation and 
    uninstallation of a cab, the dll is invoked, and it prompts the user for 
    confirmation to perform the installation or uninstallation.  In addition, 
    the dll invokes the cfgclient push client with the "/register" parameter so 
    that the client can register itself with the push router during 
    installation.  During uninstallation, CfgClient is invoked with the 
    "/unregister" parameter so that the client can unregister itself with the 
    push router.


Usage: 
    Load the project from Visual Studio 2005, and build normally.

    In order to see this sample in action, you must package it with an 
    application in a .CAB installation archive file. Please see the SDK 
    documentation for how to do this, as well as the CabWiz.exe tool and the 
    CreateCab sample.


Relevant APIs/Associated Help Topics:     
    Application Installation
    Custom Setup DLLs
    CAB file packaging
    SETUP_API
    CreateProcess

Assumptions: none.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **
