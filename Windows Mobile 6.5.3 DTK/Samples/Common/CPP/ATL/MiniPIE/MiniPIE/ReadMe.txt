Code Sample Name: MiniPIE

Feature Area: Internet Explorer Mobile

Description: Shows you how to reuse the IE Mobile web browser in your application:
- shows how to host the Microsoft.PIEDocView (PIEWebBrowser) control
- show how to use the control's IWebBrowser2 interface
- shows how to respond to browser events, using the DWebBrowserEvents2 outgoing dispinterface
This sample uses ATL. It's designed for both Pocket PC and Smartphone.

Usage: From Visual Studio, use F5 to build and deploy. After the application launches, you can
- navigate using the "Open URL..." menu item, or using the address bar (if deploying to Pocket PC)
- use the Exit softkey to quit
- use the Back, Forward, Refresh, Home and Stop menu items as you would in IE Mobile

Relevant APIs/Associated Help Topics: IWebBrowser2 and DWebBrowserEvents2.

Requirements: Visual Studio 2005, Windows Mobile 6 SDK.

** For more information about this code sample, please see the Windows Mobile SDK help system. **

Summary of what you will find in each of the files that make up this project:

MainWindow.h, MainWindow.cpp
    Defines main window for this application.

GetURLDialog.h, GetURLDialog.cpp
    Defines a dialog that allows a user to enter an URL.
    This is not really needed to host the PIEWebBrowser control. However, it's 
    implemented here in order to allow the user to navigate on Smartphone, 
    where the AddressBar property is not implemented.

MiniPIE.cpp
    Implementation of WinMain.

MiniPIE.rc
    Resources used by this application.

resource.h
    Header file that defines resource IDs. Used by MiniPIE.rc.

Macros.h
    Utility macros used for error-checking, etc.

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named MiniPIE.pch and a precompiled types file named StdAfx.obj.

MiniPIE.vcproj
    Main project file for VC++ projects generated using Application Wizards.

