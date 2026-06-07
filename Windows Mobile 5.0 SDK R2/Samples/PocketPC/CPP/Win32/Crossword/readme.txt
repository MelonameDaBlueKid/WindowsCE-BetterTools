Code Sample Name: Crossword

Feature Area: DPI and Landscape awareness

Description: 
    This set of solutions demonstrates how to convert a basic application into 
    a high DPI aware application and into a landscape/portrait aware application.

    It consists of three solutions:
    BaseSample:
        The basic application. It is a crossword game.
    HiDpiAware:
        The HI DPI aware version of BaseSample.
    LandscapeAware:
        The landscape/portrait aware version of BaseSample.
    
    
Relevant APIs: 
    ChangeDisplaySettingsEx,
    WM_SETTINGCHANGE,
    WM_SIZE,
    GetDeviceCaps,
    GetSystemMetrics,
    SHGetUIMetric 
    
Usage:
   Load the project from Visual Studio 2005, and build and deploy normally.

Assumptions: 
    None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK,
    ActiveSync 4.0.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
