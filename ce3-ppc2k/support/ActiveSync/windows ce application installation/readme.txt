
Application Installation Sample App
===================================

This sample is unsupported by Microsoft, and is supplied 'as is'.

Purpose:
-------
This sample Application Installation app provides code to create a set of
Windows CE CAB files to package a device application (see Sample.INF).

A CEAppMgr INI file is also included (see Sample.INI) to register the device
application's CE CAB files with the Windows CE Services Application Manager,
used by the end-user to download the device application.


File List:
---------
buildcab.bat  - batch file to invoke CabWiz to create the sample CAB files
register.bat  - batch file to invoke CEAppMgr to register the sample app's
                    CAB files

SAMPLE.INF    - sample CabWiz INF file that will create multiple CE CAB files
                    to support multiple CE device types (H/PC, H/PC Pro,
                    Palm-size PC, Pocket PC) and processor types
                    (SH3, MIPS, ARM, CEF)

SAMPLE.INI    - sample CEAppMgr INI file that will register the created CE
                    CAB files with the Windows CE Services Application Manager,
                    used to download the application to the device

sample.ico    - sample icon used in the CEAppMgr UI to represent the device app

cabs\*.*      - the resultant CE CAB files. Note that your created CAB files
                    will be slightly different because of the source binaries
                    timestamp

code\blkjack\*.*  - the code used to create the sample "Blkjack.exe"
code\cesetup\*.*  - the code used to create the sample "CESetup.dll"
code\selfreg\*.*  - the code used to create the sample "SelfReg.dll"
code\autorun\*.*  - sample source code to demonstrate how to install CE CAB
                        files from a Compact Flash (CF) Card to Pocket PCs.

cpu\ce_2.0\*.*    - source directory layout for the CE 2.0 processor-specific
                        files (for H/PC), referenced by the CabWiz INF file
cpu\ce_2.1\*.*    - source directory layout for the CE 2.1 processor-specific
                        files (for H/PC Pro and Palm-size PC), referenced by
                        the CabWiz INF file
cpu\ce_3.0\*.*    - source directory layout for the CE 3.0 CEF (common
                        executable format) files (for Pocket PC), referenced
                        by the CabWiz INF file
platform\*.*      - source directory layout for the common and platform-
                        specific files, referenced by the CabWiz INF file


Instructions:
------------
NOTE - CabWiz.exe will only work on Windows NT and Windows 98

- Ensure that the Windows CE SDK is installed (you will need the
    "Application Installation" SDK component)
- Ensure that Windows CE Services is installed

- Copy this Application Installation sample directory to the local drive
- Make sure all the files in the sample directory are not read-only;
    otherwise, the files packaged in the created CAB files will be read-only
- Locate the CabWiz.exe file (and its support files) from the Windows CE SDK
- Modify the "buildcab.bat" file with the path of the CabWiz.exe file
- Locate the CEAppMgr.exe file from the Windows CE Services install path
- Modify the "register.bat" file with the path of the CEAppMgr.exe file

- Run "buildcab.bat" to create the CAB files
- Verify that the CAB files were created (see the created "err.log" if the CAB
    files were not created)
- Optionally delete the created DAT files

- Run "register.bat" to register the app with CEAppMgr
- Verify that CEAppMgr acknowledges the application registration

- Connect a CE device (H/PC, H/PC Pro, Palm-size PC or Pocket PC)
- Download the created application to the CE device

- When uninstalling the app on a Pocket PC, if the Remove Programs app appears
    hung, this may be caused by the un-parented messageboxes created by the
    CESetup.dll and SelfReg.dll.  Go back to the Today screen to dismiss the
    messagebox, and then back to the Remove Programs app.
