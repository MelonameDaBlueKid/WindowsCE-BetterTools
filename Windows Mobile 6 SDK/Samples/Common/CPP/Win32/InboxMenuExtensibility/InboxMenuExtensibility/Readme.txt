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
    Inbox List View Menu Extensions

Feature Area: 
    Inbox

Description: 
    This sample will add items to the menus which are seen while in the message list view within the Inbox (tmail.exe)
    Note: This is not an application: it's a dll that will be loaded by inbox to extend the specified menus. In order
          to be loaded by inbox it populates the appropriate registry settings via DllRegisterServer, which is called
          when solution is deployed to a device.

Functionality 
	CONTEXT MENU ITEM - Add Sender to Contacts 
	1) WILL BE ENABLED you are in an incoming mail folder (NOT Outbox, Sent 
		Items nor Drafts) AND you have context menued on a SINGLE message
		which is the same as 
	2) WILL NOT BE ENABLED any time you context menu in Outbox, Sent Items or 
		Drafts
	3) WILL NOT BE ENABLED any time you context menu in an incoming mail folder 
		AND you have context menued on MORE THAN 1 message


	* Add Sender to Contacts will create a new contact and put the DISPLAY NAME
		from the email in the FileAs field and the EMAIL ADDRESS in the Email 
		field.  In the case of no DISPLAY NAME only the email will be populated.
		There is NO PARSING of the display nor email address.
	
	
	SK MENU ITEMS - Mark All as Read / Delete all (these items are allways 
		enabled/disabled together
	1) WILL BE ENABLED when you are in a folder with at least 1 message
		which is the same as 
	2) WILL NOT BE ENABLED when you are in a folder with 0 messages

	
	* Mark All items as Read - simply does this... 

	* Delete All - in any folder other than Deleted items - will move all items
		to the Deleted Items folder.  In the Deleted Items folder it will prompt
		and permanently delete.

        NOTE: To deploy/debug the project you will need to setup tmail.exe as the remote 
               application for the debugger to connect to. 
                Project Properties->Configuration Properties->Debugging->Remote Executable
               and specify \Windows\tmail.exe.



Usage: 
    See description


Relevant APIs/Associated Help Topics: 
    Menu Extensibility
    IContextMenu interface
    IObjectWithSite interface
    IMAPIFolder::DeleteMessages
    IMAPIFolder::CopyMessages

Assumptions: 
    In order to show off what this sample can do, you should have some read and unread mail in your Inbox.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.
    

** For more information about this code sample, please see the Windows Mobile SDK help system. **
