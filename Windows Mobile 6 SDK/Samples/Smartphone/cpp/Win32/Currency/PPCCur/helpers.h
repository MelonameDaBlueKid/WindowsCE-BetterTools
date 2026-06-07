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

#pragma once


extern HINSTANCE g_hInstRes;
extern HINSTANCE g_hInst;

#define PROP_TAG(ulPropType,ulPropID)  ((((ULONG)(ulPropID))<<16)|((ULONG)(ulPropType)))

#define  ARRAYSIZE(a) (sizeof(a)/ sizeof(a[0]))


HRESULT ActivatePreviousInstance(const TCHAR* pszClass, const TCHAR* pszTitle, BOOL* pfActivated);
DWORD FormatMessageHelp(TCHAR* pszOut, UINT cchOut, const TCHAR* pszFormat, ...);
int FormattedMessageBox(HWND hwnd, UINT uType, HINSTANCE hInst, UINT idsCaption, UINT idsFormat, ...);
void DisplayError(HWND hWndOwner, HINSTANCE hInst, UINT idsCaption, UINT idsFormat, HRESULT hr);
void GetSystemTimeAsFileTime(FILETIME* pSystemAsFileTime);
HRESULT GetFileTimeForDate(int iYear, int iMonth, int iDay, FILETIME* pft);


