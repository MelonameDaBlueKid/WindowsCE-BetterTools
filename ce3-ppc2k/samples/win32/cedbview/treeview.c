// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:  treeview.c
//
//  PURPOSE:    Contains functions that maintain the treeview control
//
//  PLATFORMS:  Windows CE
//
//  FUNCTIONS:
//
//  COMMENTS:
//
//

#include <windows.h>
#if !defined(_WIN_CE_EMULATION)
	#include <memory.h>
#endif
#include <commctrl.h>
#include "resource.h"
#include "globals.h"




//
//  FUNCTION:   InitDBViewImageLists(HWND)
//
//  PURPOSE:    Here we load the bitmaps and create image lists for the item
//              images and the state images.
//
//  PARAMETERS:
//      hwndTV  - Handle of the treeview that these image lists are being added
//                to.
//
//  RETURN VALUE:
//      (BOOL) Returns TRUE if the image lists are added successfully, FALSE
//             otherwise.
//
//  COMMENTS:
//

BOOL WINAPI InitDBViewImageLists(HWND hwndTV)
{
	HBITMAP    hbmp;                        // handle of the bitmaps to add

	// Create the image list for the item pictures
	if ((himl = ImageList_Create(CX_BITMAP, CY_BITMAP, ILC_MASK, NUM_BITMAPS, 0))
			  == NULL)
		return FALSE;

	// Add the bitmaps to the list
	hbmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_IMAGE));

	if (-1 == ImageList_AddMasked(himl, hbmp, RGB(0, 255, 0)))
	{
		ErrorHandler();
		return FALSE;
	}

    // Clean up the GDI objects
	DeleteObject(hbmp);

	// Fail if not all the images were added
	if (ImageList_GetImageCount(himl) < NUM_BITMAPS)
		return FALSE;

	// Associate the image list with the treeview control
	TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL);
	
	return TRUE;
}


//
//  FUNCTION:   InitDBViewItems(HWND)
//
//  PURPOSE:    Here is where items are initially added to the tree.
//
//  PARAMETERS:
//      hwndTV  - Handle of the treeview to add images to.
//
//  RETURN VALUE:
//      (BOOL) Returns TRUE if the items were added successfully, FALSE
//             otherwise.
//
//  COMMENTS:
//
//

BOOL WINAPI InitDBViewItems(HWND hwndTV)
{
	EnumDbase(hwndTV, NULL);

	return TRUE;
}


//
//  FUNCTION:   AddItemToTree(HWND, LPSTR, int, int, DWORD)
//
//  PURPOSE:    Here is where the item is actually inserted into the tree.  The
//              position on the tree is also determined.
//
//  PARAMETERS:
//      hwndTV     - handle of the treeview to add the item to
//      lpszItem   - string to add to the tree
//      htiParent  - handle of the tree item that will be this item's parent
//      fDirectory - TRUE if this item is a directory
//
//  RETURN VALUE:
//      (HTREEITEM) Returns the handle of the item once it's been added to the
//                  tree. Otherwise it returns NULL.
//
//  COMMENTS:
//

HTREEITEM WINAPI AddItemToTree(HWND hwndTV, LPTSTR lpszItem, HTREEITEM htiParent,
						BOOL fDirectory, DWORD dwRProp_DBId)
{
	TV_ITEM          tvi = {0};
	TV_INSERTSTRUCT  tvins = {0};
	HTREEITEM        hti;
	HANDLE			 hNewDB = INVALID_HANDLE_VALUE;
	CEOID			 PropId = (CEOID) dwRProp_DBId;

	// Filter out the "." and ".." directories.
	if (!lstrcmpi(lpszItem, TEXT(".")) || !lstrcmpi(lpszItem, TEXT("..")))
		return (HTREEITEM)TRUE;

    // Start by initializing the structures
	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

	// If it's a directory, add a child count so the expand button shows
	// Open database or save Property ID
	if (fDirectory)
	{
		tvi.mask |= TVIF_CHILDREN;
		tvi.cChildren = 1;

		hNewDB = CeOpenDatabase( &PropId, NULL, 0, 0, NULL);
		if ( (HANDLE) hNewDB == INVALID_HANDLE_VALUE)
		{
			TCHAR szError[50];
			wsprintf(szError, TEXT("ERROR: CeOpenDatabase failed after creating DB (%ld)"), GetLastError());
			OutputDebugString(szError);
			MessageBox(hwndTV, szError, TEXT("Error"), MB_OK);
			return NULL;
		}
		
		tvi.lParam = (LPARAM) hNewDB;
	}
	else
	{
		tvi.lParam = dwRProp_DBId;
	}


	// Set the text of the item
	tvi.pszText = lpszItem;
	tvi.cchTextMax = lstrlen(lpszItem);


	// Give the item the appropriate image
	tvi.iSelectedImage = tvi.iImage = fDirectory ? IMAGE_CLOSED : IMAGE_DOCUMENT;

	tvins.item = tvi;
	tvins.hInsertAfter = TVI_SORT;

	// Set the parent item based on the specified level
	if (!htiParent)
		tvins.hParent = TVI_ROOT;
	else
		tvins.hParent = htiParent;

	// Add the item to the tree view control
	hti = TreeView_InsertItem(hwndTV, &tvins);
	
	// BUGBUG fix current refresh problem on top line of control...
	InvalidateRect(hwndTV, NULL,TRUE);


    // Return the handle to the item
	return hti;
}


