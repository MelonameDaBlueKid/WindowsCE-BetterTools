Code Sample Name: 

Feature Area: 

Description: 
    The MUIHello sample is a MUI version of a hello world sample.  

    This sample contains the following projects:
	
    app: This directory builds muihello.exe.  

    resfile: This directory builds a resource-only DLL called muihello.exe.0409.mui.  
    This is where the OS will pull the resources used by muihello.exe if the device 
    language is set to US English 

    german_resfile: This directory builds a resource-only DLL 
    called muihello.exe.0407.mui.  This is where the OS will pull the resources 
    used by muihello.exe if the device language is set to German.  Note that the 
    strings are not actually in German, but are the English strings followed by "(Ger)"

Usage: 
    To build this sample, build all three projects in the workspace and run 
    muihello.exe.  Because muihello.exe loads resources from the .mui files, you'll 
    need to be sure that those files have been built and copied to the target 
    platform before muihello.exe will properly run.  By switching languages, note 
    how the OS automatically loads strings from the appropriate .mui file. 

    If you wish to switch the emulator (to use one that has a different language), 
    make sure that you change it on each of the projects.

Relevant APIs/Associated Help Topics: MUI

Assumptions: none

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 
