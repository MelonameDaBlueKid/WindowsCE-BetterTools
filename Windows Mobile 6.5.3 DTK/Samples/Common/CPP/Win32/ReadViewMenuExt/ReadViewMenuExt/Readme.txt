Code Sample Name: Reply Using Outlook-Email.

Feature Area: Messaging.


Description: 
Replies to an email message using a default email account. This 
is enabled for mail messages in all non-default email accounts.


Usage: 
In the read view of a message, the menu will contain the additional 
option "Reply Using Outlook E-mail".  Actioning on this item, will launch a new 
compose form for a reply that would be sent from the Outlook E-mail account.


Relevant APIs/Associated Help Topics:
Menu Extensibility, IContextMenu, IObjectWithSite, MailComposeMessage

Note:
If you would like to debug the dll, please go to 
Project Properties > Configuration Properties > Debugging
and set the Remote Executable to \Windows\tmail.exe

Assumptions: 

To deploy the solution on a smartphone emulator, you must sign and provision 
the dll. To do this:
(1) Go to your project properties. In the Authenticode signing tab, select 
Certificate, then Manage Certificates, and then Import. 
(2) Navigate to \SmartDevices\SDK\SDKTools\TestCertificates (in your Visual 
Studio folder) and in the filter box type *.pfx. 
(3) Select the Privileged .pfx and run through the wizard (no password required). 
Once the certificate is imported, select it and also say "Privileged Store" 
in the "Provision to Device" dialog. 

Once the dll is deployed, to see what the menu extensions do, you should have a 
POP/IMAP mail account set up and with some downloaded mail.


Requirements: 
Microsoft Visual Studio 2005, Windows Mobile 6 SDK


** For more information about this code sample, please see the Windows Mobile 
SDK help system. **


