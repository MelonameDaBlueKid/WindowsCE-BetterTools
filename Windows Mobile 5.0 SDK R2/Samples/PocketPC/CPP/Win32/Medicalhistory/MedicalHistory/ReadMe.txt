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
    Medical History

Feature Area: 
    Menu extensions and named properties.

Description: 
    This sample adds a menu extension to the contacts summary card which allows
    you add medical information about health insurance provider, blood group, 
    blood pressure, and allergies to a contact via use of named properties.

Usage: 
    Deploy the solution and enter the summary card for a contact.  Select the 
    "Menu" softkey and then choose "Medical History".

        NOTE: To deploy/debug the project you will need to setup poutlook.exe as the remote 
              application for the debugger to connect to. 

              Project Properties->Configuration Properties->Debugging
              Choose "Smart Device Native Debugger" for the debugger.
              set "Remote Executable" to "\Windows\poutlook.exe"
              and "Command Arguments" to "contacts"



Relevant APIs/Associated Help Topics: 
    POOM custom properties (GetIDsFromNames)
    IPOutlookApp2 interface (Logon, GetIdsFromNames, GetItemFromOidEx)
    IItem interface (GetProps, SetProps, Save)
    Menu Extensibility
    IContextMenu interface
    IObjectWithSite interface

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK,
    ActiveSync 4.0.
    

** For more information about this code sample, please see the Windows Mobile SDK help system. **
