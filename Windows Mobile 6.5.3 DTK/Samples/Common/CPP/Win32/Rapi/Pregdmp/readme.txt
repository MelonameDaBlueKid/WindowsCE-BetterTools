Code Sample Name: Pregdmp

Feature Area: ActiveSync

Description: 

    This application runs on a desktop host computer, and is used to retrieve a 
    Windows Mobile-based device's list of registry settings.
    
Usage: 
    You must compile this application with Visual Studio 2005 or newer.
    
    1. Open the project file in Visual Studio.
   
    2. Navigate to "Tools" -> "Options", and expand "Projects and Solutions", 
    and click "VC++ Directories".
    
    3. In "Show directories for:" select "Include files".
    
    4. Add the path to the mobile device include directory. If you accepted 
    the defaults when installing Windows Mobile SDK, then the new directory 
    will be "C:\Program Files\Windows Mobile 6 SDK\Activesync\inc" 
    
    5. In "Show directories for:" select "Library files".
    
    6. Add the path to the mobile device library directory. If you accepted 
    the defaults when installing Windows Mobile SDK, then the new directory 
    will be "C:\Program Files\Windows Mobile 6 SDK\Activesync\Lib".
        
    7. Navigate to "Build", and click "ReBuild All" to compile the executable 
    file.

     To get a list of the registry settings, , use the following command line:
    "Pregdmp".
    
Relevant APIs/Associated Help Topics:     
    CeRapiInit
    CeRegEnumKeyEx
    CeRegOpenKeyEx
    CeRegEnumValue
    CeRegCloseKey
    CeRapiUninit

Assumptions: none.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **


