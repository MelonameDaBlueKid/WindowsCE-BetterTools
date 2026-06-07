Code Sample Name: FileClient

Feature Area: Messaging

Description: 
	FileClient is a push client that receives a push message and saves the 
	message�s body into a file and then calls ShellExecuteEx on that file. The 
	value of the X-MS-FileName header (in the message�s headers section) 
	specifies the saved file�s name. Application parameters can be set by 
	filling in the X-MyCompany-Params header field.  The directory into which 
	the file is saved is the value of CSIDL_WINDOWS.  Since the message is 
	traveling over SMS, the max SMS size determines the max size that an app 
	can be in order to be pushed down to the device.  Most SMSC�s limit pushed 
	file size to 64KB. The application id of this push client is "fileclient", 
	and so push messages intended for this client should have "fileclient" 
	as the X-Wap-Application-Id header.

	Source file listing and summary:
	
	fileclient.cpp - contains functions for saving a file, getting user 
	permissions, checking if file type is allowed for download and processing a 
	push message.
		
	main.cpp - contains the application entry point.
	
	string.cpp - defines all constant string values.
	
	utils.cpp - contains functions for extracting data from SMS header and 
	copying strings.
	
	fileclient.h - contains function prototypes and forward declaration for 
	constant strings.
	
	precomp.h - defines precompiled header.
	
	resource.h - header file for resource script.
 
    fileclient.rc - resource script.

Usage: 
    Load the project from Visual Studio 2005, and build normally.

    Run the sample on the device once with "/register" as the command line  
    argument.  After registering the sample receiving any SMS message with 
    X-Wap-Application-Id set to "fileclient" will result in the 
    application running. 

    Notes
    The SetupDLL sample shipped with the SDK can be used to create a .CAB file 
    for deploying this application as well.  

Relevant APIs/Associated Help Topics: 
    Push router messages
    Registering as a push router client
    Saving data to storage    
    ShellExecuteEx

Assumptions: None. 

Requirements: 
	Visual Studio 2005, Windows Mobile 5.0 SDK, ActiveSync 4.0.
	Network coverage is also required to receive push messages.


** For more information about this code sample, please see the Windows Mobile SDK help system. **

