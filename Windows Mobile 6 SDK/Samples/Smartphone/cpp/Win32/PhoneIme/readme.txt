Code Sample Name: PhoneIme

Feature Area: Shell

Description: PhoneIme is a sample that shows how to create your own Input Method
for Smartphone. It implements multitap and numeral entry.

    Source file listing and summary are:

	custom.bmp- bitmap used as the image list for the numeral entry modes

	engine.cpp- Conversion Engine that implements MultiTap

	ime.cpp- Front end to the IME.  Calls the converter for the mode that is active.
	
	misc.cpp- CreateFullScreenWindow helper function
	
	mtapconv.cpp- CMTapConverter class implemention. Conversion engine wrapper.

	mtapime.cpp- Multitap IME wrapper for the input converter

	phoneime.cpp- IME wrapper for the input converter.  DLL entry points.

        phoneime.rc– contains the resources for the IME.

	prshld.cpp- IME wrapper for input converter. CPressHOldDetectorClass implementation

	symmenu.cpp- The symbols menu

	utils.cpp- Composition string utilities functions


Usage: Build the application and cab projects.  Install the cab on the device.

Note: If you have not installed the SDKSamplePrivDeveloper certificate, you will
need to do that so that your dll and cab projects are signed correctly.  

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

Relevant APIs: SHImeSetCustomInputIcons, SHImeSetModeIcon, SHImeOnKeyPress, SHImeGetClearMessage

Assumptions: None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.


** For more information about this code sample, please see the Windows Mobile SDK help system. **
