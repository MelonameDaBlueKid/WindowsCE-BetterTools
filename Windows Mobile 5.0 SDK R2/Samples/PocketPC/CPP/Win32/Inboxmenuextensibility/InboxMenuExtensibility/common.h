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


// TODO: REMOVE THIS AFTER WHIDBEY FIXES THIS BUG
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

#pragma once

///////////////////////////////////////////////////////////////////////////////
// Windows Core
#include <windows.h>
#include <objbase.h>
#include <Ocidl.h>


///////////////////////////////////////////////////////////////////////////////
// Windows Mobile
#include <shlguid.h>
#include <shlobj.h>
#include <COGUID.H>
#include <aygshell.h>
#include <winuserm.h>

///////////////////////////////////////////////////////////////////////////////
// Menu Extension definitions - ItemRefArray, ItemRef, CFNAME_ITEMREFARRAY
#include <appext.h>         


///////////////////////////////////////////////////////////////////////////////
// The following defines are used by some of the .H files refered to by CEMAPI.H
// to determine which items are included and which are not
#define USES_IID_IMessage
#define USES_IID_IMAPIProp
#define USES_IID_IMAPIFolder
#define USES_IID_IMAPIContainer
#define USES_IID_IMAPIAdviseSink

///////////////////////////////////////////////////////////////////////////////
//CEMAPI GUIDS - ITI_FolderItemRef, ITI_MessageItemRef, ITI_StoreItemRef, 
//               ITI_MessageFormExItemRef, etc... 
//CEMAPI Error Codes, and constatnts, etc.. 
#include <CEMAPI.h>         


// NOTE:
// If you are creating new menu extensions based on this code
// you absolutely must create your own CLSIDs!  
// Visual Studio's Guidgen.exe (accesible via "Tools->Create Guid") is an excellent tool for this

// {47018836-A919-42f7-84AF-89257BA458BA}
DEFINE_GUID(CLSID_INBOX_SK_MENUEXT, 0x47018836, 0xa919, 0x42f7, 0x84, 0xaf, 0x89, 0x25, 0x7b, 0xa4, 0x58, 0xba);
#define CLSIDTEXT_INBOX_SK_MENUEXT TEXT("47018836-A919-42f7-84AF-89257BA458BA")

// {6F3A2AA2-D88D-4e3d-85C1-D5B403EAD4EF}
DEFINE_GUID(CLSID_INBOX_CONTEXT_MENUEXT, 0x6f3a2aa2, 0xd88d, 0x4e3d, 0x85, 0xc1, 0xd5, 0xb4, 0x3, 0xea, 0xd4, 0xef);
#define CLSIDTEXT_INBOX_CONTEXT_MENUEXT TEXT("6F3A2AA2-D88D-4e3d-85C1-D5B403EAD4EF")

// NOTE:  guids for IID_IObjectWithSite and IID_IDataObject come from uuid.lib

// A string representing this DLL.  
// If you change the name of the DLL - change this string 
#define IMAGENAME TEXT("InboxMenuExtensibility.dll")


// Used to help us determine if we are a Context or Softkey Menu Ext
typedef enum {
    Context,
    Softkey,
} ExtensionType;


///////////////////////////////////////////////////////////////////////////////
// local project header files
#include "Macros.h"
#include "InboxMenuExt.h"
#include "ClassFactory.h"


