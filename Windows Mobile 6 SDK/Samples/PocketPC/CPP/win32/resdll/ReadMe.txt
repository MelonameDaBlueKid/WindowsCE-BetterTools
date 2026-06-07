Code Sample Name: ResDLL

Feature Area: Shell


Description: 

    As you are developing applications for new high-resolution Pocket PCs with 
    192 DPI resolution displays, you may wonder where the 
    new high-resolution bitmaps and resources should go. The simplest solution 
    is to include them in the same EXE alongside the old, low-resolution 
    resources. However, this approach wastes storage space. Device screens only 
    have one resolution, which never changes for that device. Therefore, if the 
    application is deployed to a 96 DPI device, it doesn't need 192 DPI 
    resources - and vice versa.

    A better solution is to separate your application's resources into separate, 
    resolution-specific DLLs. With this approach, the device can choose the 
    appropriate resources to use during installation, and discard the resources 
    it doesn't need. The ResDLL sample demonstrates how to do this.

    The solution contains the following projects:


    - SetupDPI - 

    SetupDPI.DLL is a setup DLL that is used in the installation CAB 
    file. It is run after your application's install process has completed. 

    SetupDPI.DLL takes a list of files as input. It finds this list in the 
    registry. For each file, if the filename ends in a number, and that number 
    is the same as the display resolution, then SetupDPI.DLL renames the file, 
    removing the number. Otherwise, it deletes the file. For example, if the 
    display resolution is 192DPI, SetupDPI.DLL will delete RES_096.DLL and 
    rename RES_192.DLL to RES.DLL.

    The list of files is found under [HKLM\Software\Microsoft\SetupDPI]. Each 
    key name is a path to a file; the value and type of the key is ignored. 
    These registry keys will be populated by the CAB file and will be deleted 
    by SetupDPI.DLL after setup is complete.

    - RES_096 -

    Res_096.dll contains the 96 DPI resources.

    - RES_192 -

    Res_192.dll contains the 192 DPI resources.

    - ResDLL - 

    This project will produce the executable. It will call Res.DLL 
    (which will be a renamed version of RES_096.DLL or RES_192.DLL.)

    - GetRealDPI -

    GetRealDPI is an executable that returns the real DPI of the device. This 
    executable is called from SetupDPI.DLL. It is required because 
    wceload.exe (the executable that runs the cab installer) could fake the DPI 
    value returned in order to pixel double older apps in hi-dpi systems.
    
    - Setup_DPI -
 
    Setup_DPI is a Smart Device CAB project. When built, the CAB will end up
    in the release directory of this project.


Usage: 
    Load the project from Visual Studio 2005, and build normally.
    
    Build the CAB project and copy the CAB file to the device and
    install the CAB normally. This will install ResDLL.exe under
    \Program Files\ResDll


Relevant APIs/Associated Help Topics:
    Resolution Awareness.

Assumptions: A 96 DPI or 192 DPI device or emulator is used.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **

