Code Sample Name: myBackLight

Feature Area: Shell

Description: 
   This project demonstrates how to create a simple control panel applet for a
   Windows Mobile-based Pocket PC device.

   Note: This sample does not actually control the backlight, it simply
   illustrates how a control panel applet is implemented.

Relevant APIs: 
   CPlApplet

Usage:
   Load and deploy the project in Visual Studio 2005. The resulting file,
   myBackLight.cpl, will be deployed to the \Windows directory. To view the CPL
   in Start:Settings, you may need to reset the device.

   Control panel applets can be started programmatically.  The format of the 
   command is:

   '\Windows\ctlpnl.exe cpl_filename.cpl,applet_name,applet_index,tab_index'

   You can configure Visual Studio 2005 to debug this sample automatically on
   the device after you build it by following these steps:

   1. Select Properties from the Project menu.
   2. Select Debugging from the Configuration Properties tree.
   3. For Remote Executable, specify "\Windows\ctlpnl.exe".
   4. For Command Arguments, specify "myBackLight.cpl".
   5. Select OK to save your changes. Press F5 to begin debugging.

Assumptions: 
   None.
    
Requirements: 
   Visual Studio 2005, 
   Windows Mobile 6 Professional SDK

** For more information about this code sample, please see the
   Windows Mobile SDK help system. **

