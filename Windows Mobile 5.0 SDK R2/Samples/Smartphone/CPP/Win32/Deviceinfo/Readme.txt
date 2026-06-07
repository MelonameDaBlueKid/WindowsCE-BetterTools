Code Sample Name: DeviceInfo

Feature Area: RAPI

Description: 
	DeviceInfo is a Win32 Desktop component that demontrates the use of 
	IRAPI interfaces to get information about the Windows Mobile device
	connected through ActiveSync and the corresponding communication
	medium used.  Once the information is collected, it is printed
	on the console window

Usage: 
    You must compile this application with Visual Studio 2005 or newer.
    
    1. Open the project file in Visual Studio.
   
    2. Navigate to "Tools" -> "Options", and expand "Projects and Solutions", 
    and click "VC++ Directories".
    
    3. In "Show directories for:" select "Include files".
    
    4. Add the path to the mobile device include directory. If you accepted 
    the defaults when installing Windows Mobile SDK, then the new directory 
    will be either 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\PocketPC\Activesync\Inc" 
    for Pocket PC, or 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\Smartphone\Activesync\Inc" 
    for Smartphone.
    
    5. In "Show directories for:" select "Library files".
    
    6. Add the path to the mobile device library directory. If you accepted 
    the defaults when installing Windows Mobile SDK, then the new directory 
    will be either 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\PocketPC\Activesync\Lib" 
    for Pocket PC, or 
    "C:\Program Files\Windows Mobile 5.0 SDK R2\Samples\Smartphone\Activesync\Lib" 
    for Smartphone.
        
    7. Navigate to "Build", and click "ReBuild All" to compile the executable 
    file.
	From a command line, run DeviceInfo.exe while a device is connected

Relevant APIs/Associated Help Topics: 
	iRAPIDesktop, EnumDevices, IRAPIDevice, IRAPIDevice::GetConnectionInfo, IRAPIDevice::GetDeviceInfo

Assumptions: 
	This project file assumes that Visual Studio default Headers and Libraries search path
	have been updated properly as described on the usage section above

Requirements: 
   Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK,
    ActiveSync 4.0.
