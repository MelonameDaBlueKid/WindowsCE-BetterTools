Code Sample Name: Prun

Feature Area: ActiveSync

Description: 
    This application runs on a desktop host computer, and is used to execute 
    an executable file on a Windows Mobile-based device.
   
Usage: 
    You must compile this application with Visual Studio 2005 or newer.
    
    1. Open the project file in Visual Studio.
   
    2. Navigate to "Tools" -> "Options", and expand "Projects and Solutions", 
    and click "VC++ Directories".
    
    3. In "Show directories for:" select "Include files".
    
    4. Add the path to the mobile device include directory. If you accepted 
    the defaults when installing Windows Mobile SDK, then the new directory 
    will be either 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\Activesync\Inc" 
    for Pocket PC, or 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\Activesync\Inc" 
    for Smartphone.
    
    5. In "Show directories for:" select "Library files".
    
    6. Add the path to the mobile device library directory. If you accepted 
    the defaults when installing Windows Mobile SDK, then the new directory 
    will be either 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\Activesync\Lib" 
    for Pocket PC, or 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\Activesync\Lib" 
    for Smartphone.
        
    7. Navigate to "Build", and click "ReBuild All" to compile the executable 
    file.
    
    To run cmd.exe on the device, use the following command line:
    "Prun \windows\cmd.exe".
    
Relevant APIs/Associated Help Topics:     
    CeRapiInit
    CeCreateProcess
    CeCloseHandle
    CeRapiUninit

Assumptions: none.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK or
    Windows Mobile 5.0 Smartphone SDK
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **

