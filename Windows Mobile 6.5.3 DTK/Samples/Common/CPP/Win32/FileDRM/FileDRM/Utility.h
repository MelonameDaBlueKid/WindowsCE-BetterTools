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

HRESULT			BuildFullName	(LPTSTR pszFullName, size_t cchFullName, const LPCTSTR pszDirectory, const LPCTSTR pszFile);
HWND			CreateListView	(HINSTANCE hInst, HWND hWndParent, HWND hWndMenuBar);
BOOL			FillListView	(HINSTANCE hInst, HWND hWndList, const LPCTSTR pszPath);
unsigned int	MenuBarHeight	(HWND hWndMenu);
BOOL			IsJPEGFile		(const LPCTSTR pszFile);
