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

#pragma once
#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 
#ifdef SMARTPHONE2003_UI_MODEL
#include "resourcesp.h"
#endif

extern TCHAR		g_szCurrentDirectory[MAX_PATH];	// Current directory in the list view

#define MAX_LOADSTRING 100

#define ID_LISTVIEW			1000
#define WM_DISPLAYIMAGE		WM_USER + 1000

HRESULT	IsDRMProtected (const LPCTSTR pszDirectory, const LPCTSTR pszFile, BOOL *fIsDRM);
