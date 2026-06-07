Code Sample Name: Multicab

Feature Area: Application Deployment

Description: 
    Sample Program that shows how to create a program to unpack all 
    the cabs in a container cab ('uber-cab').

Usage: 
     1. Build MCSetup.dll and MultiCab.exe using VS 2005.
     2. Create a container cab ('uber-cab') to unpack all the cabs 
        needed in your application.
     3. Add the following to your uber-cab:
        a. Multiple cab files
        b. The following registry settings:
           - HKCU\Software\ChainedCabSample\MultiCab with an "InstallCabName" entry
             pointing to the subkey that enumerates the cabs installed.  
               - This registry key will be deleted by this program
               - This subkey must have the same name as the uber-cab

           - HKCU\Software\ChainedCabSample\UberCabNameHere (this is not the actual 
             name) with the fully qualified paths of the cabs to be unpacked.
               - This registry key will be deleted by this program.
               - the names of the values under this key must 1, 2, 3, etc. as the
                 code assumes this.
    
    For a more detailed explanation of the sample, and how to use it see the
    "MultiCab Whitepaper.doc" file.

Relevant APIs/Associated Help Topics: 
    Setup DLL
    WCELoad

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **

