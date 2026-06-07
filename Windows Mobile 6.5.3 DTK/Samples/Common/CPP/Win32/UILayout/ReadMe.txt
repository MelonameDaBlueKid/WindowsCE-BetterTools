Code Sample Name: UILayout

Feature Area: Screen Size and Orientation Awareness

Description: 
	This sample application demonstrates a technique to achieve screen size
	and orientation independence in your applications. Since Windows Mobile
	devices come in a variety of shapes and sizes, it is a good practice to
	stretch and shrink your dialog box controls depending on screen size, 
	which can even change at runtime. Doing so will help you maintain a 
	single binary that runs well on all Windows Mobile devices regardless 
	of platform, DPI, resolution, orientation etc.
	
	Using a class called ScreenLib, it is very easy to resize and 
	stretch your controls to maximize usage of the available screen space. 
	Please see ScreenLib.h for the available functions. These functions are 
	typically used in the WM_SIZE event that a control's parent window receives. 
	
	The sample shows you several common scenarios where you might use ScreenLib. 

 
Usage: 
    Load the solution into Visual Studio 2005, and build and deploy normally.
    
    When running the sample, try switching the screen to various orientations.

    On the Pocket PC emulator, you can press the "Calendar" button to quickly
    switch between landscape and portrait modes. Also try running the sample
    on various Smartphone emulator images such as landscape and QVGA.
    
    In each case, you will notice that the dialog controls resize themselves 
    to fit all the available space regardless of the screen size or orientation.
    
    Note: This sample has no functionality other than illustrating UI layout.

Relevant APIs/Associated Help Topics:     
	ScreenLib does not use any special APIs. Common Win32 APIs such as 
	GetWindowRect, SetWindowPos, MoveWindow etc are used to do the plumbing.
	
Assumptions: 
	ScreenLib can be used in MFC or Win32 native applications.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 SDK (Professional or Standard)
    ActiveSync 4.0 or Windows Mobile Device Center (Vista)

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **