// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     seek.c
//
//  PURPOSE:    Contains window procedures for seeking.
//
//  PLATFORMS:  Windows CE
//
//  FUNCTIONS:
//
//  COMMENTS:
//
//

#include <windows.h>
#include <windowsx.h>
#if !defined(_WIN_CE_EMULATION)
	#include <memory.h>
#endif
#include <commctrl.h>
#include <tchar.h>
#include "resource.h"
#include "globals.h"


void WINAPI SeekNextRecord(HWND hwnd, DWORD dwSkip)
{

	HTREEITEM		hParent;
	HTREEITEM       hCurrentItem;
	TCHAR           szBuf[200];
	TCHAR			szProp[20] = {0};
	TCHAR			szCurrentProp[20] = {0};
	TV_ITEM         tvTable = {0};
	TV_ITEM         tvProperty = {0};
	CEOID			CeOid = 0;
	DWORD			dwIndex;
	WORD			cPropID = 0;
	LPBYTE 			bData = NULL;
	DWORD			cbData = 0;
	LPARAM			lCurrentProp;

	if( (hCurrentItem = TreeView_GetSelection( g_hwndTreeView )) )
	{

		if ( (hParent=TreeView_GetParent(g_hwndTreeView, hCurrentItem)) )
		{
			tvTable.hItem = hParent;
			tvTable.mask = TVIF_PARAM;
			if (!TreeView_GetItem(g_hwndTreeView, &tvTable))
				OutputDebugString(TEXT("ERROR: Database Deletion failed.\r\n"));
			else
			{
				if ( (HANDLE) tvTable.lParam == INVALID_HANDLE_VALUE)
					OutputDebugString(TEXT("ERROR: SeekNextRecord failed with invalid handle\r\n"));
				else
				{
					HTREEITEM hProp;
					
					if ( !CeSeekDatabase((HANDLE) tvTable.lParam, CEDB_SEEK_CURRENT, dwSkip, &dwIndex) )
					{
						wsprintf(szBuf, TEXT("CeSeekDatabase reports error: %ld\r\n"),GetLastError());
						OutputDebugString(szBuf);

						// check for end of file
						if( !CeReadRecordProps((HANDLE) tvTable.lParam, 0, &cPropID,NULL,&bData,&cbData) )
						{
							DWORD dwError;

							if ( (dwError=GetLastError()) != ERROR_NO_MORE_ITEMS && dwError != ERROR_INSUFFICIENT_BUFFER)
							{
								wsprintf(szBuf, TEXT("CeSeekDatabase reports error: %ld\r\n"),GetLastError());
								MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OK);
								OutputDebugString(szBuf);
								SendMessage(hwndEdit,WM_SETTEXT, 0, (LPARAM) (LPTSTR) TEXT("Error"));
							}
							else
							{
								if ( (LONG) dwSkip < 0 ) /// moving backward so set back to start
								{
									OutputDebugString(TEXT("End-OF-File encounterd. Resetting to start of database\r\n"));
									if ( !CeSeekDatabase((HANDLE) tvTable.lParam, CEDB_SEEK_BEGINNING, 0, &dwIndex) )
									{
										wsprintf(szBuf, TEXT("CeSeekDatabase to start reports error: %ld\r\n"),GetLastError());
										MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OK);
										OutputDebugString(szBuf);
									}
								}
								else
								{
									OutputDebugString(TEXT("End-OF-File encounterd. Resetting to end of database\r\n"));
									if ( !CeSeekDatabase((HANDLE) tvTable.lParam, CEDB_SEEK_END, 0, &dwIndex) )
									{
										wsprintf(szBuf, TEXT("CeSeekDatabase to end reports error: %ld\r\n"),GetLastError());
										MessageBox( hwnd, szBuf, TEXT("ERROR"), MB_OK);
										OutputDebugString(szBuf);
									}

								}
							}
						}
						else  /// this should not happen
							SendMessage(hwndEdit,WM_SETTEXT, 0, (LPARAM) (LPTSTR) TEXT("Error"));

					}
					else
					{
						
						/// get curret property information
						tvProperty.hItem = hCurrentItem;
						tvProperty.mask = TVIF_PARAM|TVIF_TEXT;
						tvProperty.pszText = szCurrentProp;
						tvProperty.cchTextMax = 20;


						if (!TreeView_GetItem(g_hwndTreeView, &tvProperty))
						{
							OutputDebugString(TEXT("ERROR: Retreiving database property from TreeView.\r\n"));
							lCurrentProp = -1;
						}
						else
							lCurrentProp = tvProperty.lParam;

						bRemovingProps = TRUE;
						// remove all current properties from the database item
						hProp = TreeView_GetChild(g_hwndTreeView, tvTable.hItem);
						while ( hProp )
						{
							TreeView_DeleteItem(g_hwndTreeView, hProp);
							hProp = TreeView_GetChild(g_hwndTreeView, tvTable.hItem);
						}

						// set parent to have not children
						tvTable.hItem = hParent;
						tvTable.mask = TVIF_CHILDREN;
						tvTable.cChildren = 0;

						if (!TreeView_SetItem(g_hwndTreeView, &tvTable))
							OutputDebugString(TEXT("ERROR: Modifying TreeView control.\r\n"));


						// read to find out what the new properties for this record are
						EnumDbaseProps(g_hwndTreeView, tvTable.hItem, tvTable.lParam);
						bRemovingProps = FALSE;						

						
						// try to find old selected property else select first child

						// get first new property
						hProp = TreeView_GetChild(g_hwndTreeView, tvTable.hItem);

						if ( hProp )
						{
							tvProperty.hItem = hProp;
							tvProperty.mask = TVIF_TEXT;
							tvProperty.pszText = szProp;
							tvProperty.cchTextMax = 20;

							if (!TreeView_GetItem(g_hwndTreeView, &tvProperty))
								OutputDebugString(TEXT("ERROR: Retreiving database property from TreeView.\r\n"));
						}

						/// look item selected before new property list was created
						while ( hProp )
						{
							// is this property equal to the one we had previously selected
							if ( lstrcmp(szProp, szCurrentProp ) == 0 )
							{
								ShowPropDesc((CEPROPID)tvProperty.lParam, (DWORD) tvTable.lParam, dwIndex);
								TreeView_Select(g_hwndTreeView, hProp, TVGN_CARET);
								break;
							}

							hProp = TreeView_GetNextSibling(g_hwndTreeView, hProp);
							if ( hProp )
							{
								tvProperty.hItem = hProp;
								tvProperty.mask = TVIF_PARAM|TVIF_TEXT;
								tvProperty.pszText = szProp;
								tvProperty.cchTextMax = 20;
								if (!TreeView_GetItem(g_hwndTreeView, &tvProperty))
								{
									OutputDebugString(TEXT("ERROR: Retreiving database property from TreeView.\r\n"));
									break;
								}

							}
						}

						if ( hProp == NULL && lCurrentProp != -1 )
						{
							// get the first child and show its properties
							hProp = TreeView_GetChild(g_hwndTreeView, tvTable.hItem);
							if ( hProp )
							{
								tvProperty.hItem = hProp;
								tvProperty.mask = TVIF_PARAM;

								if (!TreeView_GetItem(g_hwndTreeView, &tvProperty))
									OutputDebugString(TEXT("ERROR: Retreiving database property from TreeView.\r\n"));
								else
								{
									ShowPropDesc((CEPROPID)tvProperty.lParam, (DWORD) tvTable.lParam, dwIndex);
									TreeView_Select(g_hwndTreeView, hProp, TVGN_CARET);
								}
							}
							else
								OutputDebugString(TEXT("ERROR: Retreiving database property from TreeView.\r\n"));
						}
					
					}
				}
			}

		}
		else
			MessageBox(hwnd, TEXT("Select database property prior to seeking."), TEXT("Record Seek"), MB_OK|MB_ICONINFORMATION);
	}
	else                                                             // database property
		OutputDebugString(TEXT("No db selected for seeking.\r\n"));
}
