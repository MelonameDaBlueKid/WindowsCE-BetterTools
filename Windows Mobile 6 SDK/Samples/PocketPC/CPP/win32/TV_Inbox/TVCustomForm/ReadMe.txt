Code Sample Name: TV_Inbox

Feature Area: Custom forms, SMS interception

Description:
Implements a new message class appropriate for SMS notifications from your DVR. Message
class is assigned to SMS messages with a "{TV}" prefix via an SMS interception rule.

Usage:
Build the project and register the DLL.

Restart the messaging application.

Receive an SMS message that begins with the prefix string "{TV}".
Note the unique message class behavior in Inbox's listview and form.

Relevant APIs/Associated Help Topics: IFormProviderEx, IMailRuleClient.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 

