Feature Area: CEInvoke

Description: 
    This sample illustrates the use of the CEInvoke API in different ways. 
    This sample is not supported for emulation.

    There are two solutions for this sample:
  
    Server:    
    This is the device side code. The project builds a DLL called CeInvoke.Dll. 

    This DLL contains methods which will be invoked (via RAPI) by the the client
    desktop program.

    Note: CeInvoke.dll must exist in the windows folder on the device or at 
          the root of the device folder hierarchy. That is \ceinvoke.dll or
          \windows\ceinvoke.dll

    Client:   
    This is the desktop side code. 

    1. Open the project file/solution file using Visual Studio 2005.
    2. Point to "Platform", and select the platform you want to run this 
       application on (Pocket PC, Smartphone)

    3. Go to "Build" -> "ReBuild All" to compile the executable file, CeInvoke.exe.

Relevant APIs: 
    CEInvoke

Usage:
    Load the project from Visual Studio 2005, and build both solutions 
    normally. The server project will build ceinvoke.dll while the client 
    project will build ceinvoke.exe. Make sure ceinvoke.dll exists in the windows 
    directory on the device.

    Note: This server application must run as Trusted, which means it must be 
    signed with a security certificate that is in the privileged certificate store on the 
    device.

  
    If you have not installed the SDKSamplePrivDeveloper certificate, you 
    will need to do that so that your dll is signed correctly.  

	To install the certificate from the windows desktop:
	1. Click Start
	2. Click Run
	3. Type in the path the SDKSamplePrivDeveloper.pfx.  
        (This file will be where you installed the Smartphone or Pocket PC SDK under 
        the Tools directory)
	4. Click OK
        (The Certificate Import Wizard should appear)
	5. Click Next
        (The path to the certificate should be filled in for the File name)
	6. Click Next
	7. Click Next 
	(you do not need a password)
	8. Click Next 
	(you want the default options here: Automatically select the  certificate 
	store based on the type of certificate)
	9. Click Finish
    
    See "Windows Mobile Security and Software Development" in the SDK 
    documentation for more details on how to install the SDK certificates onto the device, 
    and how to use the privileged SDK certificate to sign this application.

    Build the desktop side. It is a Windows app without any UI. The 
    project builds an exe called CeInvoke.exe. The results are displayed in 
    a simple Message Box. You can run the exe from the command line with one 
    of the following or any other parameters:

    Command Line Param  Tests              Expected Result
    ------------------  -----              ---------------
    No param            Simple Block       Will return an error code
    StoreInfo           Simple Block       Will return the store info on the device
    S1                  Simple Stream      Will return some text specifying Stream Mode 1
    S2                  Multiple Stream    Will return a list of all databases on the device.


    You can also run the exe from within Visual Studio 
    (by altering the Project > Settings > Debug tab > General category > 
    Program Arguments).

Assumptions: 
	As of Windows Mobile Version 5.0, the Remote Access Security Policy on Smartphone and Pocket PC 
	is restricted by default. The RAPI policy on these devices is considered "Restricted," which 
	prevents you from using CeRapiInvoke to invoke device-side DLLs - unless you take extra steps to 
	satisfy the requirements of the Remote Access Security Policy. For more information on RAPI 
	security and steps to satisfy the requirements of the Remote Access Security Policy, see 
	CERapiInvoke in the Windows Mobile 6 SDK documentation.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK
    Windows Mobile 6 Standard SDK
    Activesync 4.5.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **

