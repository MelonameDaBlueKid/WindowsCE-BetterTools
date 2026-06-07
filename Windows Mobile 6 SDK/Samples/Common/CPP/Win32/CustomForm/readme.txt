Code Sample Name: CustomForm

Feature Area: Pocket Office - Messaging

Description: 
    This sample demonstrates how to implement a Rule Client to capture and 
    process SMS/EMS, process multipart EMS, and implement a custom read form 
    to display the EMS in the Inbox application. 


Usage: 

    Building the Sample
        Build CustomForm.sln.  Copy CustomFormSetup.cab to the device, and install it.
        
		A reboot is required if the router has previously received any SMS.

     Running the Sample
        Once the Rule Client and Custom Form are installed, you should be able to receive EMS messages on the 
        device.  They will be processed by the Rule Client and available for viewing in the SMS account in Inbox.
        The only supported EMS IEIs are pictures.  The normal SMS user data (text) is also processed.

    Notes
        Supported IEIs - Referenced from 3GPP TS 23.040, V4.3.0

        0x10 = Large Picture (32x32)
        0x11 = Small Picture (16x16)
        0x12 = Variable Picture
 

    Additional IEIs will be ignored by the Rule Client.


Relevant APIs:    
	IMailRuleClient 
	IFormProviderEx

Assumptions: 
	The device supports SMS.

Requirements: 
	Visual Studio 2005 
	Windows Mobile 6 Professional SDK or
	Windows Mobile 6 Standard SDK
	Activesync 4.5

** For more information about this code sample, please see the Windows Mobile SDK help system. **
