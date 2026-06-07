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
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__86D2675F_D579_411C_93B1_D2C7592AD80B__INCLUDED_)
#define AFX_STDAFX_H__86D2675F_D579_411C_93B1_D2C7592AD80B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (_WIN32_WCE <= 211)
#error This project can not be built for H/PC Pro 2.11 or earlier platforms.
#endif

#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include "DeviceResolutionAware.h"
#define SCALEX DRA::SCALEX
#define SCALEY DRA::SCALEY

// Local Header Files

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__86D2675F_D579_411C_93B1_D2C7592AD80B__INCLUDED_)
