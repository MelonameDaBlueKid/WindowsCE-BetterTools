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

#include "Imaging.h"

class CImageView
{
public:
	CImageView();
	~CImageView();

	HRESULT OpenImageFile	(HWND hWnd, const LPCTSTR pszFullName);
	HRESULT Draw			(HWND hWnd, HDC hdc, RECT *rc);

private:
	HRESULT ReadImageFile ();
	HRESULT CreateIImage  ();

private:
	HANDLE	m_hFile;				// Handle to the file containing the image being viewed
	BYTE   *m_pbBuffer;				// in-memory buffer holding image data
	DWORD	m_cbBuffer;				// Size of buffer
	DWORD	m_dwPreviousTickCount;	// System tick count last time image updated
	DWORD	m_dwElapsedViewTime;	// Time image had been displayed without rights verification
	IImage *m_pImage;				// Pointer to the IImaging class that does all the display work
	TCHAR	m_szFileName[MAX_PATH];	// Full path to file being displayed
	bool	m_fRightsCommitted;		// TRUE if rights have been committed
};
