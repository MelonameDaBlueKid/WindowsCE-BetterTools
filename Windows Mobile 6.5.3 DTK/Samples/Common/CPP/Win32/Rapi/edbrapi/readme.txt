Code Sample Name: EDBRapi

Feature Area: RAPI

Description: 
    This sample demonstrates how to use RAPI to access EDB databases. It also provides a 
    reusable libary for accessing EDB databases remotely on the Windows Mobile device.

    This application mounts an EDB database volume, creates an EDB database and populates it 
    with the names, size and time of the files or directories in the root directory of the 
    device.
    
    The database is then closed and re-opened sorted by file or directory names. The content of 
    the database in the created volume is printed. Finally, the database will be deleted and 
    the volume will be unmounted.

    The solution contains the following projects:

        Client:
        This Win32 project is the startup project. It uses the functions defined in 
        clientlib.lib to access EDB databases on the Windows mobile devices remotely.

        Clientlib:
        This project produces a desktop library that contains 36 EDB RAPI functions that
        communicate with the device. The output is clientlib.lib. If you wish to link to this
        library, make sure to include Clientlib.h .

        EdbRapiServer:
        This project produces EdbRapiServer.dll. 
        This device DLL is invoked by the EDB RAPI functions in Clientlib to access the EDB 
        database on the device and return results or data to the desktop application.

        SetupDLL:
        This setup DLL calls DMProcessConfigXML to allow EdbRapiServer.dll to receive
        CeRapiInvoke calls.

        ServerSetup:
        This project produces ServerSetup.CAB. 
        It will copy EdbRapiServer.dll to the \Windows folder.

Note:
    After calling our EDB RAPI functions, you can get the last error by calling GetLastError() 
    instead of CeGetLastError().

Usage: 
    You must compile this application with Visual Studio 2005.
    
    1. Open the project file in Visual Studio.
   
    2. Navigate to "Tools" -> "Options", and expand "Projects and Solutions", 
    and click "VC++ Directories".
    
    3. In "Show directories for:" select "Include files".
    
    4. For Win32 and mobile device platform, add the ActiveSync include path to 
    the include directories.
        
    If you accepted the defaults when installing Windows Mobile SDK, then the 
    new directory will be will be something like "C:\Program Files\Windows Mobile 6 SDK\Activesync\Inc"
    
    5. In "Show directories for:" select "Library files".
    
    6. For Win32 and mobile device platform, add the ActiveSync library path to 
    the library directories. 
    If you accepted the defaults when installing Windows Mobile SDK, then the new directory 
    will be something like "C:\Program Files\Windows Mobile 6 SDK\Activesync\Lib".
        
    7. Right click properties for the "EDBRapi" Solution, and Select Configuration Properties.
    Set the platform for Client and Clientlib as WIN32 and the platform for EDBRapiServer 
    as the mobile platform you choose, either Windows Mobile 6 Professional or Standard.      
    
    8. Navigate to "Build", and click "ReBuild Solution" to compile the executable file.
    
    9. Go to the main output directory of ServerSetup, and copy ServerSetup.CAB to the device, 
    and run it. (You may use Remote File Viewer to copy the file to a location you can access 
    on the device or emulator).

    Running the CAB will copy the signed version of EdbRapiServer.dll to the \windows folder on the device.

    The Setup DLL included in the ServerSetup CAB needs to run with privileged rights. If you will 
    run this CAB on a windows mobile device, make sure to sign the CAB with a certificate on the 
    privileged certificate store. 
    
    10. Make sure your device/emulator is connected to ActiveSync before running the application.


Relevant APIs/Associated Help Topics:
    EDB
    RAPI


Assumptions:

   If you have not installed the SDKSamplePrivDeveloper certificate, you will
   need to do that so that your dll and cab projects are signed correctly.

    To install the certificate from the windows desktop:
    1. Click Start
    2. Click Run
    3. Type in the path to SDKSamplePrivDeveloper.pfx.  (This file will be where 
       you installed the Pocket PC or Smartphone SDK under the Tools directory)
    4. Click OK
       (The Certificate Import Wizard should appear)
    5. Click Next
       (The path to the certificate should be filled in for the File name)
    6. Click Next
    7. Click Next (you do not need a password)
    8. Click Next (you want the default options here: Automatically select the 
       certificate store based on the type of certificate)
    9. Click Finish

Requirements:
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.

