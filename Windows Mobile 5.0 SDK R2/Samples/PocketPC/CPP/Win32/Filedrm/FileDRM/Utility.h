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

HRESULT			BuildFullName	(LPTSTR pszFullName, size_t cchFullName, const LPCTSTR pszDirectory, const LPCTSTR pszFile);
HWND			CreateListView	(HINSTANCE hInst, HWND hWndParent, HWND hWndMenuBar);
BOOL			FillListView	(HINSTANCE hInst, HWND hWndList, const LPCTSTR pszPath);
unsigned int	MenuBarHeight	(HWND hWndMenu);
BOOL			IsJPEGFile		(const LPCTSTR pszFile);
