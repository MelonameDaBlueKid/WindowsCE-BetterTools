Code Sample Name: HWNavigation

Feature Area: Shell

Description: 
    This sample illustrates how focus moves around a dialog when the user
    performs various hardware navigation actions. Specifically, it shows
    how custom controls should interact with the system to track and display
    the focus rect, and also how focus in listviews can be separated from
    selection when so desired.

 
Relevant APIs: 
    WM_GETDLGCODE
    DrawFocusRectColor
    LVS_EX_DISJOINTFOCUS
   
Usage:
    Load the project from Visual Studio 2005, and build normally.
    This sample will build as an application called HWNavigation.exe. Deploy
    the application on your device and run it. Use arrow keys to move between
    the dialog controls and action/return key to perform some action. Every
    action available to the user should be accessible in this way.

Assumptions: 
    None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
