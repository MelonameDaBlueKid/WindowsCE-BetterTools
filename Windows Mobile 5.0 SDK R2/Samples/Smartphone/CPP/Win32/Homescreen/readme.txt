Code Sample Name: Homescreen

Feature Area: Smartphone Shell Homescreens

Description: 
	This sample implements a home-screen plugin and custom home-screen layout for 
	the Smartphone. The layout consists of a few standard plugins, and a new 
	plugin which displays information about available memory. The layout is 
	specified in an XML file which is found in the Common directory.  The 
	included memory status plugin (memplug.cpp) is implemented as a COM object 
	which supports IHomePlugin, in addition to the standard factory and class 
	object interfaces.

	- The Plugin Manager does one-time initialization of the plugin via it�s 
	IHomePlugin::Initialize method, using the custom configuration info specified 
	in the layout XML. Config info is saved to an intermediate file (via 
	IPersistStream::Save) and the plugin is released (see Notes below)

	- home.exe loads the IHomePlugin object and loads the custom config info from 
	the intermediate file via the plugin�s IPersistStream interface.

	- The user returns to home screen

	- The new layout is drawn and plugin responds to a number of system and UI 
	messages.

	- The user can select the plugin (a status bar indicating percentage of 
	remaining system memory) and a dialog appears with more detailed information

Usage: 
	Build the project, copy the cab to the device and run the cab. 

	To Run the sample:
	From the Settings menu, select "Home Screen". From the drop-down box at the 
	top of the screen, select "Memplug". Select "Done" to return to the Settings 
	screen. From there, return to the Home screen. You will see a new home screen 
	with the memory usage status bar. The text above it is specified in the 
	layout XML and may be changed by modifying the XML and restarting the device.


	Developing (and particularly debugging) Homescreen plugins can be tricky 
	because of the complex way in which they are loaded and configured. To keep 
	CPU-heavy XML parsing to a minimum on resource-limited devices, such parsing 
	occurs only when the plugin is initially loaded by the plugin manager. This 
	keeps home.exe (which loads the plugin on boot-up) from having to parse 
        XML, which would dramatically increase boot time. To debug 
	a plugin at runtime, you must attach the debugger to the home.exe process.  
        Here are the details:

	How to Interactively Debug a Home Screen Plugin at Runtime:

	This can be a bit tricky because the plugin is already loaded when you want 
	to debug. You must attach to the home.exe process:

	Make sure you have a debug version of the plugin installed and working on an 
	attached device or emulator

	Load the project in Visual Studio 2005 and select Tools->Attach to Process.  
	Choose Smart Device in the list of transports.  Then select or browse for the device 
	that you are working with. A Process list will appear.  Attach to the 
	home.exe process

	At this point you�re almost finished. If you switch to the Debug tab in the 
	Output window you should see debugging messages. All that�s left to do now is 
	open the source file you wish to debug and set a break point somewhere, such 
	as OnEvent. 

	Trigger that event and the breakpoint will be hit and you�ll be able to debug 
	normally. 



Note: If you have not installed the SDKSamplePrivDeveloper certificate, you 
will need to do that so that your dll and cab projects are signed correctly.  

	To install the certificate from the windows desktop:
	1. Click Start
	2. Click Run
	3. Type in the path to SDKSamplePrivDeveloper.pfx.  (This file will be where 
	   you installed the Smartphone SDK under the Tools directory)
	4. Click OK
	   (The Certificate Import Wizard should appear)
	5. Click Next
	   (The path to the certificate should be filled in for the File name)
	6. Click Next
	7. Click Next (you do not need a password)
	8. Click Next (you want the default options here: Automatically select the 
	   certificate store based on the type of certificate)
	9. Click Finish

Relevant APIs/Associated Help Topics: 
	Building a Home-Screen plugin
	IHomePlugin
	IPersistStream
	IHomePluginEnvironment

Assumptions: 
	Unprivileged Test Certs are installed on desktop machine to 
	properly sign the cab and dll

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 
