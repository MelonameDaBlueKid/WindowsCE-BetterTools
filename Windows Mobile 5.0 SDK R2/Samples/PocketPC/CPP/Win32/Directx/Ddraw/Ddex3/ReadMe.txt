Code Sample Name:  DDEx3

Feature Area: Direct Draw

Description: 
    DDEx3 demonstrates the use of off-screen surfaces.

    This program shows how to initialize DirectDraw and create a DirectDraw 
    surface. It creates a back surface and uses page flipping to alternately 
    display the contents of the front and back surfaces. Other techniques 
    demonstrated include color fills and using GDI functions on a DirectDraw 
    surface.

    The DDEx3 sample is an extension of DDEx2. In addition to the front and back 
    surfaces, the program creates two off-screen surfaces and loads bitmaps 
    into them. It calls the IDirectDrawSurface4::BltFast method to copy the 
    contents of an off-screen surface to the back surface, alternating the 
    source surface on each frame. After it blits the bitmap to the back surface, 
    DDEx3 flips the front and back surfaces. 
    
Relevant APIs: 
    DirectDraw

Usage:
    Load the project from Visual Studio 2005, and build and deploy normally.
    DDEx3 requires no user input. Press the ACTION button to quit the 
    program.

Assumptions: 
    The device supports hardware flipping support.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK
    ActiveSync 4.0.

    This sample requires hardware flipping support.  If the display
    driver doesn't support page flipping the sample will exit during
    initialization.

    Requires at least 1.2 MB of video RAM.    

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
