Code Sample Name: PIEHelper

Feature Area: Internet Explorer Mobile

Description:
    This sample demonstrates creating a Browser Helper Object (BHO), 
    which IE Mobile will load each time it starts up.

    In particular, it shows how a BHO can
    - get the IWebBrowser2 interface pointer of its associated Internet Explorer object
    - catch WebBrowser events

Usage:

    Load the project in Visual Studio 2005 and pick the target platform and SDK.

    You need to set Internet Explorer Mobile to be the remote executable:

       1. Open the PieHelper Project Properties. 
       2. Go to Configuration Properties > Debugging. 
       3. Make sure the Smart Device Native Debugger is set as the debugger 
          to launch and set the Remote Executable to \windows\iexplore.exe

    Now you can build and deploy normally. Doing so should copy the sample 
    to the device, register it, and automatically launch Internet Explorer Mobile.

    When IE mobile launches, the BHO gets loaded and creates a window where it 
    displays the WebBrowser events that it catches. Initially, this window may 
    get hidden by IE Mobile's main window. So, navigate around with IE Mobile as 
    you normally would, and whenever you want to see the BHO-created window, 
    minimize IE Mobile.

Relevant APIs/Associated Help Topics:
    Internet Explorer Mobile: IWebBrowser2
    Internet Explorer Mobile: DWebBrowserEvents2
    ATL
    COM

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK,
    Windows Mobile 5.0 Smartphone SDK,

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 

