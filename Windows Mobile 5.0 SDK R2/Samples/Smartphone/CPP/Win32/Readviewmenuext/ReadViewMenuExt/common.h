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

#define USES_IID_IMessage
#define USES_IID_IMAPIProp
#define USES_IID_IMAPIFolder
#define USES_IID_IMAPIContainer
#define USES_IID_IMAPIAdviseSink
//#include <mapiguid.h>

///////////////////////////////////////////////////////////////////////////////
//CEMAPI GUIDS - ITI_FolderItemRef, ITI_MessageItemRef, ITI_StoreItemRef, 
//               ITI_MessageFormExItemRef, etc... 
//CEMAPI Error Codes, and constatnts, etc.. 
#include <CEMAPI.h>         


// NOTE:
// If you are creating new menu extensions based on this code
// you absolutely must create your own CLSIDs!  
// Visual Studio's Guidgen.exe is an excellent tool for this

// {DB4EE6A9-CD73-43e3-B8BC-312D154E9A9A}
DEFINE_GUID(CLSID_READVIEW_SK_MENUEXT, 0xdb4ee6a9, 0xcd73, 0x43e3, 0xb8, 0xbc, 0x31, 0x2d, 0x15, 0x4e, 0x9a, 0x9a);
#define CLSIDTEXT_READVIEW_SK_MENUEXT TEXT("DB4EE6A9-CD73-43e3-B8BC-312D154E9A9A")

// A string representing this DLL.  If you change the name of the DLL - change 
//  this string 
#define IMAGENAME TEXT("ReadViewMenuExt.dll")


///////////////////////////////////////////////////////////////////////////////
// local project
#include "Macros.h"
#include "ReadViewMenuExt.h"
#include "ClassFactory.h"


