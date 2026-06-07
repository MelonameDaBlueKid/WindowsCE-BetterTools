//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
/*++


Module Name: windows.h

Purpose: Master include file for Windows applications.

--*/

#ifndef __WINDOWS__
#define __WINDOWS__

#include <windef.h>
#include <types.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <winreg.h>
#include <shellapi.h>
#if !defined(WINCEMACRO) && !defined(WIN32_NO_OLE)
#include <ole2.h>
#endif

#include <imm.h>

#include <tchar.h>
#include <excpt.h>

// On CE force the functions to be linked instead of inline and
// turn off auto deprecate
#ifdef UNDER_CE
#define STRSAFE_LIB
#define STRSAFE_NO_DEPRECATE
#endif
#include <strsafe.h>

#endif /* __WINDOWS__ */

