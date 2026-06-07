Code Sample Name: AppointmentOverSms

Feature Area: Managed Programming

Description: 
    This sample uses custom controls to pick an appointment and a contact and 
    then sends a meeting request to the contact over SMS. The sample also 
    intercepts meeting requests and prompts the user respectively.

    The custom controls used by this sample are ListViews that access the 
    contacts and appointments on the device using Microsoft.WindowsMobile.PocketOutlook. 
    These ListViews have good performance since they access only those items 
    that need to be displayed and draw their own content.
          
Usage:
    To correctly test this sample you should use two devices with SMS 
    capabilities. If you do not have two devices with SMS capabilities you may 
    send a message to yourself.
    
    Load and deploy the project in Visual Studio 2005.

Relevant APIs/Associated Help Topics: 
    Microsoft.WindowsMobile.PocketOutlook
    Microsoft.WindowsMobile.PocketOutlook.MessageInterception
    Managed custom controls.

Assumptions:
    The device can send and receive SMS messages.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK,
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **
