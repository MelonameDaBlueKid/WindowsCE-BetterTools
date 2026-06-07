//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.


#pragma once


#include <windows.h>
#include "Macros.h"

#define APPNAME L"MenuExtHelper"

#define NULLVAL _T("")

#define REGKEY_MENUEXT_ROOT _T("Software\\Microsoft\\Shell\\Extensions\\ContextMenus\\")

#define REGKEY_MENUEXT_CONTACTS_SUMMARYCARD_PPC     REGKEY_MENUEXT_ROOT _T("Contacts\\Summary_Tools\\{") CLSIDTEXT_TESTEXT _T("}")

HRESULT CreateMenuExtensionCLSIDRegKey(LPTSTR ptszCLSID, LPTSTR ptszMenuExtDllName);
HRESULT CreateMenuExtensionRegKey(LPTSTR pszKey);