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

#include "stdafx.h"
#include "FileDRM.h"
#include "Utility.h"

typedef struct
{
	UINT	mask;		// LVCF_* bitmask
	int		fmt;		// LVCFMT_*value
	int		size;		// Column size in percent
	UINT	idsName;	// Index into string table (column header)
} COLUMNDEF;

static const COLUMNDEF gs_Columns[] = 
{	{LVCF_FMT | LVCF_WIDTH | LVCF_TEXT, LVCFMT_LEFT, 60, IDS_COLUMN1},
	{LVCF_FMT | LVCF_TEXT,              LVCFMT_LEFT,  0, IDS_COLUMN2}
};
static const size_t gs_cColumns = ARRAYSIZE (gs_Columns);

static HRESULT CreateColumns (const HINSTANCE			hInstRes,
							  const HWND				hWndList, 
							  const COLUMNDEF * const	Columns, 
							  const size_t				cColumns)
{
	HRESULT		hr = S_OK;
	LV_COLUMN	lvC;
	DWORD		cxRemainingWidth;
	RECT		rcClient;

	if (GetClientRect(hWndList, &rcClient))
	{
		const DWORD cxTotalWidth = cxRemainingWidth = rcClient.right - rcClient.left;
	
		for (size_t i = 0; i < cColumns; ++i)
		{
			assert (cxRemainingWidth != 0);
			lvC.mask = Columns[i].mask;

			if (lvC.mask & LVCF_FMT)
			{
				lvC.fmt  = Columns[i].fmt;
			}

			if (lvC.mask & LVCF_WIDTH)
			{
				lvC.cx = ((cxTotalWidth * Columns[i].size) + 50 ) / 100;
				assert (lvC.cx > 0);
				if (lvC.cx > cxRemainingWidth)
				{
					lvC.cx = cxRemainingWidth;
				}
				cxRemainingWidth -= lvC.cx;
			}

			if (Columns[i].idsName)
			{
				TCHAR szBuffer [MAX_LOADSTRING];
				lvC.pszText = szBuffer;
				if (0 == LoadString (hInstRes, Columns[i].idsName, szBuffer, ARRAYSIZE (szBuffer)))
				{
					const DWORD dwLastError = GetLastError ();
					hr = HRESULT_FROM_WIN32 (dwLastError);
					break;
				}
			}

			if (-1 == ListView_InsertColumn (hWndList, i, &lvC))
			{
				hr = E_FAIL;
				break;
			}
		}
	}
	else
	{
		const DWORD dwLastError = GetLastError ();
		hr = HRESULT_FROM_WIN32 (dwLastError);
	}

	return hr;
}

HRESULT BuildFullName (LPTSTR pszFullName, 
					   size_t cchFullName, 
					   const LPCTSTR pszDirectory, 
					   const LPCTSTR pszFile)
{
	HRESULT hr = S_OK;

	hr = StringCchCopy (pszFullName, cchFullName, pszDirectory);
	if (SUCCEEDED (hr))
	{
		size_t cchDirectory;

		hr = StringCchLength (pszDirectory, STRSAFE_MAX_CCH, &cchDirectory);
		if (SUCCEEDED (hr))
		{
			if (*(pszDirectory + cchDirectory - 1) != _T('\\'))
			{
				hr = StringCchCat (pszFullName, cchFullName, _T("\\"));
			}

			if (SUCCEEDED (hr))
			{
				hr = StringCchCat (pszFullName, cchFullName, pszFile);
			}
		}
	}
	return hr;
}

HWND CreateLVWindow (HINSTANCE hInst, HWND hWndParent, HWND hWndMenuBar)
{
	HWND hWndList = NULL;  		// handle to list view window
	RECT rcClient;         		// rectangle for setting size of window
	int cyMenuBar;
	
	// Get the size and position of the parent window.
	if (GetClientRect(hWndParent, &rcClient))
	{
		cyMenuBar = MenuBarHeight (hWndMenuBar);
	}

	// Create the list view window
	hWndList = CreateWindow(WC_LISTVIEW, NULL,
								WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL,
								rcClient.left, rcClient.top, 
								(rcClient.right - rcClient.left), 
								(rcClient.bottom - rcClient.top) - cyMenuBar,
								hWndParent, (HMENU)ID_LISTVIEW, hInst, NULL);
	return hWndList;	
}

HWND CreateListView (HINSTANCE hInst, HWND hWndParent, HWND hWndMenuBar)
{
	HWND hWndList;
	DWORD dwLVStyle;

	hWndList = CreateLVWindow (hInst, hWndParent, hWndMenuBar);
	if (hWndList)
	{
		dwLVStyle = ListView_GetExtendedListViewStyle( hWndList);
		dwLVStyle |= (LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);
		ListView_SetExtendedListViewStyle (hWndList, dwLVStyle); 

		if (SUCCEEDED (CreateColumns (hInst, hWndList, gs_Columns, gs_cColumns)))
		{
			// Set last column to auto-size
			if (!ListView_SetColumnWidth (hWndList, 1, LVSCW_AUTOSIZE_USEHEADER))
			{
				hWndList = NULL;
			}
		}
		else
		{
			hWndList = NULL;
		}
	}
	
	return hWndList;
}


static HRESULT FinishLVUpdate (const HWND hWndList)
{
	HRESULT hr = S_OK;
	SendMessage (hWndList, WM_SETREDRAW, TRUE, 0);
	return hr;
}


static HRESULT StartLVUpdate (const HWND hWndList)
{
	HRESULT hr = S_OK;
	
	SendMessage (hWndList, WM_SETREDRAW, FALSE, 0);
	if (!ListView_DeleteAllItems (hWndList))
	{
		const DWORD dwLastError = GetLastError ();
		hr = HRESULT_FROM_WIN32 (dwLastError);

		FinishLVUpdate (hWndList);
	}

	return hr;
}


BOOL FillListView (HINSTANCE hInst, HWND hWndList, LPCTSTR const pszPath)
{
	HRESULT			hr = S_OK;
	LVITEM			lv = { 0 };
	int				iNextItem = 0;
	HANDLE			hFind;
	WIN32_FIND_DATA wfdFileInfo;
	TCHAR			szFindString[MAX_PATH];
	TCHAR			szTypeDir[MAX_LOADSTRING];
	TCHAR			szTypeDRM[MAX_LOADSTRING];

	if (   0 != LoadString (hInst, IDS_LV_DIR, szTypeDir, ARRAYSIZE(szTypeDir))
		&& 0 != LoadString (hInst, IDS_LV_DRM, szTypeDRM, ARRAYSIZE(szTypeDRM)))
	{
		hr = BuildFullName (szFindString, ARRAYSIZE (szFindString), pszPath, _T("*"));
		if (SUCCEEDED (hr))
		{
			hr = StartLVUpdate (hWndList);
			if (SUCCEEDED (hr))
			{
				hFind = FindFirstFile (szFindString, &wfdFileInfo);
				if (hFind != INVALID_HANDLE_VALUE)
				{
					do
					{
						lv.mask = LVIF_TEXT | LVIF_PARAM;
						lv.iItem = iNextItem;
						lv.pszText = wfdFileInfo.cFileName;
						lv.lParam = wfdFileInfo.dwFileAttributes;

						ListView_InsertItem (hWndList, &lv);

						if (wfdFileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
						{
							ListView_SetItemText (hWndList, iNextItem, 1, szTypeDir);
						}
						else
						{
							BOOL fIsDRM;
							if (SUCCEEDED (IsDRMProtected (g_szCurrentDirectory, wfdFileInfo.cFileName, &fIsDRM)))
							{
								if (fIsDRM)
								{
									ListView_SetItemText (hWndList, iNextItem, 1, szTypeDRM);
								}
							}
						}
					}
					while (FindNextFile (hFind, &wfdFileInfo));

					FindClose (hFind);
				}
			}

			if (ListView_GetItemCount (hWndList) > 0)
			{
				ListView_SetItemState (hWndList, 0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			}
	
			FinishLVUpdate (hWndList);
		}
	}
	return SUCCEEDED (hr);
}

unsigned int MenuBarHeight (HWND hWndMenu)
{
	unsigned int cyRetValue = 0;
#ifdef WIN32_PLATFORM_PSPC
	RECT rcMenu;

    if (hWndMenu)
    {
        GetWindowRect(hWndMenu, &rcMenu);
        cyRetValue = rcMenu.bottom-rcMenu.top;
    }
#endif
	return cyRetValue;
}


BOOL IsJPEGFile (const LPCTSTR pszFile)
{
	LPCTSTR pszWork = pszFile;
	BOOL	fResult	= FALSE;
	LPCTSTR pszDot	= NULL;

    while (*pszWork)
    {
        switch (*pszWork)
		{
	        case _T('.'):
		        pszDot = pszWork;   // remember the last dot
				break;

			case TEXT('\\'):		// Ignore "." and ".." directories
			case TEXT(' '):         // extensions can't have spaces
				pszDot = NULL;       
				break;
        }
		++pszWork;
    }

	if (pszDot)
	{
		const LCID lcidCompare = MAKELCID (MAKELANGID (LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
		const int iCompare = CompareString (lcidCompare, NORM_IGNORECASE, 
												pszDot + 1, -1, 
												_T("jpg"), -1);

		if (iCompare == CSTR_EQUAL)
		{
			fResult = TRUE;
		}
	}
	return fResult;
}