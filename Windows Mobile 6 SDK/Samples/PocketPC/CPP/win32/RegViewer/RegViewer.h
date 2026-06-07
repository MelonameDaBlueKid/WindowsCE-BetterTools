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

#if !defined(AFX_PSPCMONKEY_H__25A6EDD6_67CC_11D3_93E4_525400E907B2__INCLUDED_)
#define AFX_PSPCMONKEY_H__25A6EDD6_67CC_11D3_93E4_525400E907B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#define IDE_NAME                    101
#define IDE_TITLEINDEX              102
#define IDE_ACL                     104
#define IDE_LASTWRT                 105
#define IDE_VALUE1                  106
#define IDE_VALUE2                  107
#define IDE_VALUE3                  108
#define IDE_CLASS                   109
#define IDB_NEXT                    111
#define IDB_BACK                    112
#define IDL_LISTBOX                 110
#define IDL_LISTBOX2                103
#define IDE_CVALUES                 113
#define IDB_PRINT                   114
#define IDR_FULL                    115
#define IDE_TEXTOUT                 116
#define IDR_TRIMMED                 117

#define MAX_VALUE_NAME              1024
#define MAX_DATA_LEN                1024

#define LINE_LEN                    80

#define BRANCH                      1
#define CHILD                       2
#define OTHER                       3

#define BOOT_INI                    TEXT("c:\\boot.ini")
#define REGISTRY_TXT                TEXT("registry.txt")

// MAX_PATH is defined as 260 in windef.h

#define WM_GETFIRSTKEY              WM_APP

int  APIENTRY ViewerDlgProc (HWND, UINT, WPARAM, LPARAM  );

VOID EnumerateLevel (HWND hDlg, LPTSTR NameLBSelect,
                     LPTSTR RegPath, size_t RegPathSize, HKEY *hKeyRoot);

VOID QueryKey (HWND, HKEY);
VOID DisplayKeyData (HWND hDlg, TCHAR *RegPath, HKEY hKeyRoot);


#endif // !defined(AFX_PSPCMONKEY_H__25A6EDD6_67CC_11D3_93E4_525400E907B2__INCLUDED_)
