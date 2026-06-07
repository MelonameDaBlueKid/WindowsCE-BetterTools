Code Sample Name:  DDEx2

Feature Area: Direct Draw

Description: 
    DDEx2 demonstrates the tasks required to initialize and run a DirectDraw 
    application.

    This program shows how to initialize DirectDraw and create a DirectDraw 
    surface. It creates a back surface and uses page flipping to alternately 
    display the contents of the front and back surfaces. Other techniques 
    demonstrated include color fills and using GDI functions on a DirectDraw 
    surface.

    The DDEx2 sample is an extension of DDEx1 that adds a bitmap. Routines in 
    DDutil.cpp load a bitmap file and copy it to a DirectDraw surface. 

Relevant APIs: 
    DirectDraw

Usage:
    Load the project from Visual Studio 2005, and build and deploy normally.
    DDEx2 requires no user input. Press the ACTION button to quit the 
    program.

Assumptions: 
    The device supports hardware flipping support.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK,
    ActiveSync 4.0.

    This sample requires hardware flipping support.  If the display
    driver doesn't support page flipping the sample will exit during
    initialization.


** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
