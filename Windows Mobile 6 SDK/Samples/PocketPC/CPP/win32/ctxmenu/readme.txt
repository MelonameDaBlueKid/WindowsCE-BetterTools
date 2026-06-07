Code Sample Name: CTXMenu

Feature Area: Shell

Description: 

    This sample shows how to implement a context menu extension handler, and

    specifically one that extends the context menu in File Explorer when
    tapping and holding on a file.

    Context menu extensions are only loaded when a single file is selected;
    if multiple files are selected and the user invokes the context menu, no
    File Explorer will not load any extension handlers.

    This is a standard implementation of the IContextMenu interface.  The
    filename is retrieved from File Explorer via the IDataObject interface.

Usage: 
    1.  Run guidgen.exe to generate a new GUID
    2.  Put this GUID in guids.h, replacing the one that's already there
    3.  Compile and deploy the sample
    4.  ctxmenu.dll will be built, deployed to \windows, and registered
    5.  Start/Programs/File Explorer and tap and hold on any .bmp file to 
        bring up the context menu.  You should see an additional menu item.


Relevant APIs: IContextMenu

Assumptions: None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
