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
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once


#ifdef _X86_
    #pragma comment(linker, "/nodefaultlib:libc.lib")
    #pragma comment(linker, "/nodefaultlib:libcd.lib")
    #pragma comment(linker, "/nodefaultlib:oldnames.lib")
#endif

// NOTE - this is value is not strongly correlated to the Windows CE OS version being targeted
#define WINVER _WIN32_WCE

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS    // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define SHELL_AYGSHELL
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>        // MFC support for Internet Explorer 4 Common Controls
#endif



#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#include "DeviceResolutionAware.h"
#endif

#include <aygshell.h>
#pragma comment(lib, "aygshell.lib") 

// TODO: temporary code, until the CE compilers correctly implement the /MT[d], /MD[d] switches, and MFCCE fixes some #pragma issues
#ifdef _DLL // /MD
    #if defined(_DEBUG)
        #pragma comment(lib, "msvcrtd.lib")
    #else
        #pragma comment(lib, "msvcrt.lib")
    #endif
#else // /MT
    #if defined(_DEBUG)
        #pragma comment(lib, "libcmtd.lib")
    #else
        #pragma comment(lib, "libcmt.lib")
    #endif
#endif

#if (_WIN32_WCE < 0x500) && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
    #pragma comment(lib, "ccrtrtti.lib")
    #ifdef _X86_    
        #if defined(_DEBUG)
            #pragma comment(lib, "libcmtx86d.lib")
        #else
            #pragma comment(lib, "libcmtx86.lib")
        #endif
    #endif
#endif
