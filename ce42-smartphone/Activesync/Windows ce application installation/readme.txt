
Application Installation Sample App
===================================

This sample is unsupported by Microsoft, and is supplied 'as is'.

Purpose:
-------
This sample Application Installation app provides a CEAppMgr INI file 
(see Sample.INI) to register the device
application's CE CAB files with the ActiveSync Application Manager.

The sample does not provide instructions to build the cab files.



File List:
---------
register.bat  - batch file to invoke CEAppMgr to register the sample app's
                    CAB files

SAMPLE.INI    - sample CEAppMgr INI file that will register the created CE
                    CAB files with the ActiveSync Application Manager,
                    used to download the application to the device

sample.ico    - sample icon used in the CEAppMgr UI to represent the device app

cabs\*.*      - CAB files to register with CEAppMgr

code\blkjack\*.*  - the code used to create the sample "Blkjack.exe"
code\cesetup\*.*  - the code used to create the sample "CESetup.dll"
code\selfreg\*.*  - the code used to create the sample "SelfReg.dll"
code\autorun\*.*  - sample source code to demonstrate how to install CE CAB
                        files from a Compact Flash (CF) Card to Pocket PCs.

platform\*.*      - source directory layout for the common and platform-
                        specific files


Instructions:
------------

- Ensure that ActiveSync is installed

- Copy this Application Installation sample directory to the local drive
- Locate the CEAppMgr.exe file from the ActiveSync install path
- Modify the "register.bat" file with the path of the CEAppMgr.exe file


- Run "register.bat" to register the app with CEAppMgr
- Verify that CEAppMgr acknowledges the application registration

- Connect a CE device 
- Download the created application to the CE device

- When uninstalling the app on a Windows CE device, if the Remove Programs app appears
    hung, this may be caused by the un-parented messageboxes created by the
    CESetup.dll and SelfReg.dll.  Go back to the Today screen to dismiss the
    messagebox, and then back to the Remove Programs app.

Note: The provided cab files are not supported on the Smartphone platform