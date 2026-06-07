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
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__0A5879C1_D79D_4548_813E_41F92B9846DD__INCLUDED_)
#define AFX_STDAFX_H__0A5879C1_D79D_4548_813E_41F92B9846DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (_WIN32_WCE <= 211)
#error This project can not be built for H/PC Pro 2.11 or earlier platforms.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define EDB
// Windows Header Files:
#include <windows.h>
#include <aygshell.h>

// Local Header Files

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__0A5879C1_D79D_4548_813E_41F92B9846DD__INCLUDED_)
