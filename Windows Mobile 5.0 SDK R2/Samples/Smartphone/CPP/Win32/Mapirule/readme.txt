Code Sample Name: MapiRule

Feature Area: Messaging

Description: 
    This sample demonstrates how to implement a MAPI Rule Client, a COM object 
    which can handle / filter incoming MAPI messages. Of particular relevance is 
    the implementation of IMailRuleClient and its ProcessMessage method. This 
    method is called by the MAPI subsystem when a message matching the Rule 
    Client�s transport (SMS, ActiveSync, POP3) arrives. From within 
    ProcessMessage, you can reroute messages, delete messages, parse messages 
    and send custom data to other apps, or anything else you may need to do. 
    Currently, only SMS is supported as a transport for Rule Clients. 
    IMailRuleClient::Initialize must also be implemented to set message store 
    access privileges.
    
    A Rule Client is a COM object (generally housed in a DLL) which implements 
    the IMailRuleClient interface. In order to work properly, it must be 
    registered in two places: 
    
    1.) Standard COM registration - HKEY_CLASSES_ROOT\CLSID\<clsid>
    
    2.) MAPI Inbox - HKEY_LOCAL_MACHINE\Software\Microsoft\Inbox\Svc\SMS\Rules\<clsid>

    where <clsid> represents the COM object�s class ID GUID
    
    This sample Rule Client uses MAPI message property methods to look for the 
    string "zzz" in incoming SMS messages. If found, it will display the message 
    and sender address in a custom message box instead of the usual incoming SMS 
    dialog. It will also delete the message from the message store, preventing it 
    from showing up in the Inbox. Messages which do not contain "zzz" will be 
    processed normally.
    
Usage: 
    Load the project from Visual Studio 2005, and build normally.

    After installing the Rule Client sample, you can run it by sending yourself 
    a test SMS message. Send an SMS message to the device (use 425-001-0001)
    with the sample Rule Client installed containing the string "zzz" anywhere 
    in the message. Instead of the standard popup dialog that appears, you will 
    see a standard message box with the address as the caption and the message 
    itself as the body. You may have to close the Inbox to see this message box, 
    as it can appear underneath.  Note that the message does not appear in the 
    Inbox at all. This is because it was handled and discarded by the Rule Client.
    
    Send the device another SMS message without "zzz". This will be handled 
    normally, with the standard incoming SMS popup dialog showing the message, 
    and the message appearing in the Inbox.

    To disable the sample Rule Client, remove both registry keys and reboot the 
    device.

Relevant APIs/Associated Help Topics:     
    Creating a Rule Client 
	IMailRuleClient
	IMailRuleClient::ProcessMessage
	IMailRuleClient::Initialize
	IMsgStore
	IMsgStore::OpenEntry
	IMessage
	IMessage::GetProps
	MAPI Message properties

Assumptions: The device is capable of sending and receiving SMS messages. 

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

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK or
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **

