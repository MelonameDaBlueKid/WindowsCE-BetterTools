//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

Code Sample Name: 
    TransportDemo

Feature Area: 
    CEMAPI/Messaging Custom email transport

Description: 
This sample illustrates how to create a custom Inbox transport for a Windows Mobile 5.0 Pocket PC.

This sample transport does not actually sync email using any protocol. It merely demonstrates how to construct an Inbox transport through which a developer could implement their needed protocol.


Usage: 

To install the transport:
1) Build the solution.

2) Copy the installation cab to the My Documents folder on the Windows Mobile Emulator.  You will need the Remote File Vieiwer tool to accomplish this.

3) On the emulator: Click Start->Programs->File Explorer->My Documents->TransportDemoSetup.cab.  Wait for the cab to finish installation.

3) Start the Messaging app. (Start->Messaging)

4) Create a new account: 
a) Menu->Tools->New Account.
b) (E-mail setup 1/5) Enter an email address which will use your custom transport. Click the Next softkey.
c) (E-mail setup 2/5) Click the Next softkey.
d) (E-mail setup 3/5) Enter the username, password etc for the email account which uses the custom transport. Click the Next softkey.
e) (E-mail setup 4/5) Select the Custom Transport from the "Account Type" drop down. (This is transport this sample implements).
f) Complete the remainder of the E-mail setup as per the custom transport email account settings.

To manually install the transport (optional of you don't use cab-install method mentioned above):
1) Copy the transport DLL to the \Windows directory of the device or emulator.

2) Set these registry keys (using the Remote Registry Editor tool).  
   *** NOTE:  It is critical that the KEY NAME matches the key's value "Name" ***
[HKEY_LOCAL_MACHINE\Software\Microsoft\Inbox\Svc\TransportDemo]         <<< The key name "TransportDemo" must match 
"Name"="TransportDemo"                                                  <<< the value for "Name" here.
"DLL"="TransportDemo.dll"
"Port"=dword:00000000

3) Restart Inbox

4) Follow step #4 from the steps above.



Requirements: 
    Visual Studio 2005, Windows Mobile 2005 SDK,  ActiveSync 4.0.
    


** For more information about this code sample, please see the Windows Mobile SDK help system. **

