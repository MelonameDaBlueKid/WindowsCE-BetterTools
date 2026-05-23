// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     index.c
//
//  PURPOSE:    Contains window procedures for index manipulation.
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

void WINAPI OpenIndex(HWND hwnd)
{
	HTREEITEM       hItem;
	TCHAR           szDBName[CEDB_MAXDBASENAMELEN];
	TCHAR           szBuf[200];
	TV_ITEM         tvCurrent = {0};

	if( (hItem = TreeView_GetSelection( g_hwndTreeView )) )
	{

	// Check to see if this is a database or property
	// if item has no parent then database
		tvCurrent.hItem = hItem;
		if ( !(hItem=TreeView_GetParent(g_hwndTreeView, tvCurrent.hItem) ))
		{
			tvCurrent.mask |= (TVIF_TEXT|TVIF_PARAM);
			tvCurrent.pszText = szDBName;
			tvCurrent.cchTextMax =  CEDB_MAXDBASENAMELEN;
		
			if (!TreeView_GetItem(g_hwndTreeView, &tvCurrent))
				OutputDebugString(TEXT("ERROR: Database Deletion failed.\r\n"));
			else
			{

				int				nRet;
				MODSORT			SortOrders;
				memset(&SortOrders, 0, sizeof(MODSORT));

				SortOrders.pszDBName = szDBName;
				if ( (nRet=DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_SELECTINDEX),
						hwnd, (WNDPROC)UseIndexDlgProc, (LPARAM) &SortOrders)) != -1)
				{
					if( nRet == IDOK)
					{
						HANDLE	hOpenDB;
						CEOID	CeOID = 0;
						
						if ( SortOrders.PropsIndexed )
						{			
							// close current session
							CloseHandle((HANDLE)tvCurrent.lParam);
							// reopen with new index
							hOpenDB = CeOpenDatabase(&CeOID, szDBName, SortOrders.SortOrderOut[0].propid, 0, NULL);
							if ( hOpenDB == INVALID_HANDLE_VALUE)
							{
								wsprintf(szBuf, TEXT("ERROR: CeOpenDatabase failed to open database.(Error: %ld)\r\n"), GetLastError());
								MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OK);
								OutputDebugString(szBuf);
							}
							else
							{
								tvCurrent.mask = TVIF_PARAM;
								tvCurrent.lParam = (LPARAM)hOpenDB;
								if (!TreeView_SetItem(g_hwndTreeView, &tvCurrent))			
									OutputDebugString(TEXT("ERROR: Reopen with index failed.\r\n"));
							}
						}
					}
				}
			}
		}
		else
		{
			wsprintf(szBuf, TEXT("Select the database property to open a database index.\r\n"));
			MessageBox(hwnd, szBuf, TEXT("Error"), MB_OK);
		}


	}
	else
		OutputDebugString(TEXT("Opening index failed.\r\n"));

}


void WINAPI ModifyIndex(HWND hwnd)
{
	HTREEITEM       hItem;
	TCHAR           szDBName[CEDB_MAXDBASENAMELEN];
	TCHAR           szBuf[200];
	TV_ITEM         tvCurrent = {0};

	if( (hItem = TreeView_GetSelection( g_hwndTreeView)) )
	{
		
		tvCurrent.hItem = hItem;
		tvCurrent.mask |= (TVIF_TEXT|TVIF_PARAM);
		tvCurrent.pszText = szDBName;
		tvCurrent.cchTextMax =  CEDB_MAXDBASENAMELEN;
		

		if (!TreeView_GetItem(g_hwndTreeView, &tvCurrent))
			OutputDebugString(TEXT("ERROR: Database Index modification failed.\r\n"));
		else
		{

			if ( _tcsstr( szDBName, TEXT("_TEST") ) && (HANDLE) tvCurrent.lParam != INVALID_HANDLE_VALUE)
			{
				int				nRet;
				MODSORT			SortOrders;
				
				memset(&SortOrders, 0, sizeof(MODSORT));

				SortOrders.pszDBName = szDBName;
				if ( (nRet=DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_MODINDEX),
						hwnd, (WNDPROC)ModIndexDlgProc, (LPARAM) &SortOrders)) != -1)
				{
					if( nRet == IDOK)
					{
						HANDLE	hOpenDB;
						CEOID	CeOID = 0;
						CEDBASEINFO  DBInfo;

						DBInfo.dwFlags = CEDB_VALIDSORTSPEC;
						DBInfo.wNumSortOrder = SortOrders.PropsIndexed;

						hOpenDB = CeOpenDatabase(&CeOID, SortOrders.pszDBName, 0, 0, NULL);
						if ( hOpenDB == INVALID_HANDLE_VALUE)
						{
							wsprintf(szBuf, TEXT("ERROR: CeOpenDatabase failed to open database.(Error: %ld)\r\n"), GetLastError());
							MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OK);
							OutputDebugString(szBuf);
						}
						else
						{
							memcpy(&(DBInfo.rgSortSpecs), &(SortOrders.SortOrderOut), sizeof(SORTORDERSPEC)*DBInfo.wNumSortOrder);
							if ( !CeSetDatabaseInfo(CeOID, &DBInfo) )
							{
								long lLastError;
                                wsprintf(szBuf, TEXT("ERROR: CeSetDatabaseInfo failed to modify indexes.(Error: %ld)\r\n"), lLastError=GetLastError());
								MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OK);
								OutputDebugString(szBuf);
                                switch(lLastError)
                                {
                                    case ERROR_INVALID_PARAMETER:
                                        OutputDebugString(TEXT("Invalid Parameter\n"));
                                        break;
                                    case ERROR_DISK_FULL:
                                        OutputDebugString(TEXT("The object store is full and any size changes required could not be accomodated. \n"));
                                        break;
                                    case ERROR_SHARING_VIOLATION:
                                        break;
                                        OutputDebugString(TEXT("CeSetDatabaseInfo tried to remove a sort order that is being used by a currently open database. \n"));
                                    default:
                                        OutputDebugString(TEXT("Unknown Failure\n"));
                                }
							}
							CloseHandle(hOpenDB);
						}
					}
				}
			}
			else
			{
				wsprintf(szBuf, TEXT("Select the database property to modify database indexes.\r\n"));
				MessageBox(hwnd, szBuf, TEXT("Error"), MB_OK);
			}
		}

	}
	else                                                             // database property
		OutputDebugString(TEXT("Deleting currently selected DB.\r\n"));

}



BOOL CALLBACK UseIndexDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam )
{

	static MODSORT	*	pModIndex;
	int					i;
	TCHAR				szProperty[50];
	LONG				lResult;

    switch(message)
    {
	case WM_INITDIALOG:
		pModIndex = (MODSORT *) lParam;
		if ( pModIndex )
		{
			GetIndexesProps(pModIndex);
			if ( pModIndex->PropsIndexed )
			{
				for ( i = 0 ; i < pModIndex->PropsIndexed; i++)
				{
					wsprintf(szProperty, TEXT("%#lX "), pModIndex->SortOrderIn[i].propid);
					if ( pModIndex->SortOrderIn[i].dwFlags & CEDB_SORT_DESCENDING)
						lstrcat(szProperty, TEXT("DESC "));

					if ( pModIndex->SortOrderIn[i].dwFlags & CEDB_SORT_CASEINSENSITIVE )
						lstrcat(szProperty, TEXT("CASE "));
					
					if ( pModIndex->SortOrderIn[i].dwFlags & CEDB_SORT_UNKNOWNFIRST )
						lstrcat(szProperty, TEXT("UNKNOWN "));

					if( (lResult=SendDlgItemMessage(hDlg,IDC_INDEXES,LB_ADDSTRING,0,(LPARAM) (LPCTSTR) szProperty)) != LB_ERR)
						SendDlgItemMessage(hDlg,IDC_INDEXES,LB_SETITEMDATA ,(WPARAM) lResult,(LPARAM) pModIndex->SortOrderIn[i].propid);
				}

				return (TRUE);
			}
			else
			{
				MessageBox(hDlg, TEXT("No indexes available for use."), TEXT("Indexes"), MB_OK|MB_ICONINFORMATION);
				EndDialog(hDlg, IDCANCEL);
			}
			
		}

	case WM_COMMAND:
	    switch (LOWORD(wParam))
	    {
			case IDOK:

				// get the number of listbox entries
				if ((lResult=SendDlgItemMessage(hDlg, IDC_CURRENT, LB_GETCURSEL, (WPARAM)0 , (LPARAM)0)) != LB_ERR )
				{
					pModIndex->SortOrderOut[0].propid = (CEPROPID) SendDlgItemMessage(hDlg,IDC_CURRENT,LB_GETITEMDATA ,(WPARAM) lResult,(LPARAM) 0);						
					pModIndex->PropsIndexed = 1;
				}
				else
					pModIndex->PropsIndexed = 0;

				if ( pModIndex && pModIndex->RemainingProps)
					LocalFree(pModIndex->RemainingProps);

				EndDialog(hDlg, IDOK);
				break;
			case IDCANCEL:
				if ( pModIndex && pModIndex->RemainingProps)
					LocalFree(pModIndex->RemainingProps);

				EndDialog(hDlg, IDCANCEL);
				break;

	    }
	    return (TRUE);
    }
    return (FALSE);
}



BOOL CALLBACK ModIndexDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam )
{

	static MODSORT	*	pModIndex;
	int					i;
	TCHAR				szProperty[50];
	DWORD			*	pProp;
	LONG				lResult, l;

    switch(message)
    {
	case WM_INITDIALOG:
		pModIndex = (MODSORT *) lParam;
		if ( pModIndex )
		{
			GetIndexesProps(pModIndex);
			pProp = (DWORD *) pModIndex->RemainingProps;
			for ( i = 0 ; i < pModIndex->RemainProps; i++)
			{
				switch(TypeFromPropID(pProp[i]))
				{
					case CEVT_I2:
						wsprintf(szProperty, TEXT("%#X: (Short)"), pProp[i]);
						break;
					case CEVT_UI2:
						wsprintf(szProperty, TEXT("%#X: (UShort)"), pProp[i]);
						break;
					case CEVT_I4:
						wsprintf(szProperty, TEXT("%#X: (Long)"), pProp[i]);
						break;
					case CEVT_UI4:
						wsprintf(szProperty, TEXT("%#X: (ULong)"), pProp[i]);
						break;
					case CEVT_FILETIME:
						wsprintf(szProperty, TEXT("%#X: (FileTime)"), pProp[i]);
						break;
					case CEVT_LPWSTR:
						wsprintf(szProperty, TEXT("%#X: (String)"), pProp[i]);
						break;
					case CEVT_BLOB:
						wsprintf(szProperty, TEXT("%#X: (Blob)"), pProp[i]);
						break;
					default:
						wsprintf(szProperty, TEXT("%#X: (Unknown)"), pProp[i]);
						break;
				}	
				if( (lResult=SendDlgItemMessage(hDlg,IDC_AVAILABLE,LB_ADDSTRING,0,(LPARAM) (LPCTSTR) szProperty)) != LB_ERR)
					SendDlgItemMessage(hDlg,IDC_AVAILABLE,LB_SETITEMDATA ,(WPARAM) lResult,(LPARAM) pProp[i]);

			
			}

			for ( i = 0 ; i < pModIndex->PropsIndexed; i++)
			{
				wsprintf(szProperty, TEXT("%#lX "), pModIndex->SortOrderIn[i].propid);
				if ( pModIndex->SortOrderIn[i].dwFlags & CEDB_SORT_DESCENDING)
					lstrcat(szProperty, TEXT("DESC "));

				if ( pModIndex->SortOrderIn[i].dwFlags & CEDB_SORT_CASEINSENSITIVE )
					lstrcat(szProperty, TEXT("CASE "));
				
				if ( pModIndex->SortOrderIn[i].dwFlags & CEDB_SORT_UNKNOWNFIRST )
					lstrcat(szProperty, TEXT("UNKNOWN "));

				if( (lResult=SendDlgItemMessage(hDlg,IDC_CURRENT,LB_ADDSTRING,0,(LPARAM) (LPCTSTR) szProperty)) != LB_ERR)
					SendDlgItemMessage(hDlg,IDC_CURRENT,LB_SETITEMDATA ,(WPARAM) lResult,(LPARAM) pModIndex->SortOrderIn[i].propid);
			}
		}
		
	    return (TRUE);

	case WM_COMMAND:
	    switch (LOWORD(wParam))
	    {
			case IDOK:

				// get the number of listbox entries
				if ((lResult=SendDlgItemMessage(hDlg, IDC_CURRENT, LB_GETCOUNT, (WPARAM)0 , (LPARAM)0)) != LB_ERR )
				{
					pModIndex->PropsIndexed = (WORD) lResult;
					for ( l = 0 ; l < lResult; l++ )
					{
						pModIndex->SortOrderOut[l].propid = (CEPROPID) SendDlgItemMessage(hDlg,IDC_CURRENT,LB_GETITEMDATA ,(WPARAM) l,(LPARAM) 0);						
						pModIndex->SortOrderOut[l].dwFlags = 0;
					}
				}

				if ( pModIndex && pModIndex->RemainingProps)
					LocalFree(pModIndex->RemainingProps);

				EndDialog(hDlg, IDOK);
				break;
			case IDCANCEL:
				if ( pModIndex && pModIndex->RemainingProps)
					LocalFree(pModIndex->RemainingProps);

				EndDialog(hDlg, IDCANCEL);
				break;

			case IDC_ADDINDEX:
			{
				if ((lResult=SendDlgItemMessage(hDlg, IDC_CURRENT, LB_GETCOUNT, (WPARAM)0 , (LPARAM)0)) != LB_ERR )
				{
					if ( lResult < 4 )
					{
						if ((lResult=SendDlgItemMessage(hDlg, IDC_AVAILABLE, LB_GETCURSEL, (WPARAM)0 , (LPARAM)0)) != LB_ERR )
						{
							if ( LB_ERR != SendDlgItemMessage( hDlg, IDC_AVAILABLE, LB_GETTEXT,
								(WPARAM) lResult, (LPARAM) (LPCTSTR) szProperty) )
							{
								LRESULT	lItemData;
                                long lPropType;

								lItemData = SendDlgItemMessage(hDlg,IDC_AVAILABLE,LB_GETITEMDATA ,(WPARAM) lResult,(LPARAM) 0);
								lPropType = TypeFromPropID(lItemData);
                                if(lPropType == CEVT_BLOB)
                                {
                                    MessageBox(hDlg, TEXT("Binary Fields can not be indexed."),TEXT("Invalid index type"),MB_OK|MB_ICONINFORMATION);
                                }
                                else
                                {
                                    SendDlgItemMessage( hDlg, IDC_AVAILABLE, LB_DELETESTRING, (WPARAM) lResult, (LPARAM) 0);
								
								    lResult = SendDlgItemMessage( hDlg, IDC_CURRENT, LB_ADDSTRING,(WPARAM) 0, (LPARAM) (LPCTSTR) szProperty);
								    SendDlgItemMessage(hDlg,IDC_CURRENT,LB_SETITEMDATA ,(WPARAM) lResult,(LPARAM) lItemData);						
								    EnableWindow(GetDlgItem(hDlg,IDC_ADDINDEX),	FALSE);
                                }
							}
						
						}
					}
					else
						MessageBox(hDlg, TEXT("A Windows CE database only supports 4 indexes!"), TEXT("Index Limit"), MB_OK|MB_ICONINFORMATION);
				}
				break;
			}
			case IDC_REMINDEX:
			{
				if ((lResult=SendDlgItemMessage(hDlg, IDC_CURRENT, LB_GETCURSEL, (WPARAM)0 , (LPARAM)0)) != LB_ERR )
				{
					if ( LB_ERR != SendDlgItemMessage( hDlg, IDC_CURRENT, LB_GETTEXT,
						(WPARAM) lResult, (LPARAM) (LPCTSTR) szProperty) )
					{
						LRESULT	lItemData;

						lItemData = SendDlgItemMessage(hDlg,IDC_CURRENT,LB_GETITEMDATA ,(WPARAM) lResult,(LPARAM) 0);
						SendDlgItemMessage( hDlg, IDC_CURRENT, LB_DELETESTRING, (WPARAM) lResult, (LPARAM) 0);
						lResult = SendDlgItemMessage( hDlg, IDC_AVAILABLE, LB_ADDSTRING,(WPARAM) 0, (LPARAM) (LPCTSTR) szProperty);
						SendDlgItemMessage(hDlg,IDC_AVAILABLE,LB_SETITEMDATA ,(WPARAM) lResult,(LPARAM) lItemData);
						EnableWindow(GetDlgItem(hDlg,IDC_REMINDEX),	FALSE);

					}
				
				}
				break;
			}

			case IDC_AVAILABLE:
				switch ( HIWORD(wParam) )
				{
					case LBN_SELCHANGE:
					{
						EnableWindow(GetDlgItem(hDlg,IDC_ADDINDEX),	TRUE);
						break;
					}
				}
				break;
				



			case IDC_CURRENT:
				switch ( HIWORD(wParam) )
				{
					case LBN_SELCHANGE:
					{
						EnableWindow(GetDlgItem(hDlg,IDC_REMINDEX),	TRUE);
						break;
					}

				}

				break;
	    }
	    return (TRUE);
    }
    return (FALSE);
}


void WINAPI GetIndexesProps( MODSORT * pModIndex)
{
	TCHAR           szBuf[200];
	TCHAR           szSort[100] = {0};
	CEOID          CeOID = 0;
    CEOIDINFO		CeObject;
	HANDLE          hOpenDB;
	int             i, j;
	WORD			cPropID;
	LPBYTE 			bData = NULL;
	DWORD			cbData;
	DWORD	*		pdwNextProp = NULL;
	PCEPROPVAL		pPropIds;

	hOpenDB = CeOpenDatabase(&CeOID, pModIndex->pszDBName, 0, 0, NULL);
	if ( hOpenDB == INVALID_HANDLE_VALUE)
	{
		wsprintf(szBuf, TEXT("ERROR: CeOpenDatabase failed to open database.(Error: %ld)\r\n"), GetLastError());
		MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OK);
		OutputDebugString(szBuf);
	}
	else
	{
		if ( !CeOidGetInfo(CeOID, &CeObject) )
		{
			wsprintf(szBuf, TEXT("ERROR: CeOidGetInfo failed with error (%ld)\r\n"), GetLastError());
			MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OK);
			OutputDebugString(szBuf);
		}
		else
		{
			if ( CeObject.infDatabase.dwFlags &  CEDB_VALIDSORTSPEC ) // is valid sort struct
			{
				pModIndex->PropsIndexed = CeObject.infDatabase.wNumSortOrder;
				for ( i = 0 ; i < CeObject.infDatabase.wNumSortOrder ; i++)
				{
					if( !(CeObject.infDatabase.rgSortSpecs[i].dwFlags & CEDB_SORT_GENERICORDER ) )
						memcpy(&pModIndex->SortOrderIn[i], &CeObject.infDatabase.rgSortSpecs[i], sizeof(SORTORDERSPEC));
					else
						--pModIndex->PropsIndexed;

				}
			}
		}
		pModIndex->MaxProps = 0;
		pModIndex->RemainProps = 0;

		// get a list of properties
		if( !CeReadRecordProps(hOpenDB, CEDB_ALLOWREALLOC, &cPropID,NULL,&bData,&cbData) )
		{
			DWORD dwError;

			if ( (dwError = GetLastError()) != ERROR_NO_MORE_ITEMS)
			{
				wsprintf(szBuf, TEXT("ERROR: CeReadRecordProps failed to read database.(Error: %ld)\r\n"), dwError);
				MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OK);
				OutputDebugString(szBuf);
			}
		}
		else
		{
			pModIndex->MaxProps = cPropID;

			pModIndex->RemainProps = 0;

			if ( cPropID )
				pModIndex->RemainingProps = (BYTE * )LocalAlloc(LPTR, sizeof(CEPROPID)* cPropID);

			if ( pModIndex->RemainingProps )
			{
				pdwNextProp = (DWORD *) pModIndex->RemainingProps;
				pPropIds = (PCEPROPVAL) bData;
				for ( i = 0 ; i < cPropID; i++ )
				{
					for ( j = 0 ; j < pModIndex->PropsIndexed ; j++)
					{
						if ( pModIndex->SortOrderIn[j].propid == (DWORD)pPropIds[i].propid )
							break;
					}
					if ( j == pModIndex->PropsIndexed )
					{
						pdwNextProp[pModIndex->RemainProps] = (DWORD)pPropIds[i].propid;
						++(pModIndex->RemainProps);
					}

				}

			}
			LocalFree(bData);
		}
		CloseHandle(hOpenDB);
	}
}
