Code Sample Name: AXSample

Feature Area: Internet Explorer Mobile

Description:
This sample demonstrates creating an ActiveX control and how to access that 
control in a web page.

Usage:
To build the sample -
Load the project in Visual Studio 2005, pick the target platform and SDK, 
and build normally.

To run/debug the sample -

The AxSample.htm file needs to be loaded by Internet Explorer Mobile. 

To set Internet Explorer Mobile to load axsample.htm upon deployment:

    1. Open to the AxSample project properties.
    2. Navigate to Configuration Options>Debugging
    3. Set the Debugger to Launch to:
        Smart Device Native Debugger
    4. Set the Remote Executable to:
        \windows\iexplore.exe
    5. Set the Command Arguments to:
        \Program Files\AxSample\AXSample.htm

Now you can deploy the solution as usual. Doing so should copy the sample to the 
device and register it. Then, Internet Explorer Mobile should automatically launch and 
navigate to axsample.htm

At this point you can try clicking various buttons, circles, etc that have 
been displayed.

Notes -
To run this sample on Smartphone, be sure to sign axsample.dll with the 
SDKSamplePrivDeveloper certificate. To install the certificate from the windows 
desktop:
	1. Click Start
	2. Click Run
	3. Type in the path to SDKSamplePrivDeveloper.pfx.  (This file will be 
	   where you installed the Smartphone SDK under the Tools directory)
	4. Click OK
	   (The Certificate Import Wizard should appear)
	5. Click Next
	   (The path to the certificate should be filled in for the File name)
	6. Click Next
	7. Click Next (you do not need a password)
	8. Click Next (you want the default options here: Automatically select 
	   the certificate store based on the type of certificate)
	9. Click Finish

Relevant APIs/Associated Help Topics:
ActiveX controls
ATL
COM

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK
    Windows Mobile 5.0 Smartphone SDK

Source file listing and summary:
    axsample.cpp    - implements functions exported via the .def file
    axsample.def    - dll export definitions
    axsample.idl    - midl script file
    axsample.rc     - resource script
    axsamplectl.cpp - implements the ActiveX entry points including OnDraw
    stdafx.cpp      - defines precompiled type information
    axsamplectl.h   - defines COM interfaces to ActiveX control
    resource.h      - resource script header file
    stdafx.h        - precompiled header

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 

