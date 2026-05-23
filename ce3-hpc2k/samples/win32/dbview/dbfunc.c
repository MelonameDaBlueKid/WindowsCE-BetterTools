// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     dbfunc.c
//
//  PURPOSE:    Contains window procedures database related functions.
//
//  PLATFORMS:  WIN32_WCE
//
//  FUNCTIONS:
//      MainWndProc()       - Message handler for the main application window
//      Main_OnCommand()    - Processes WM_COMMAND messages
//      Main_OnDestroy()    - Handles the WM_DESTROY message
//      AboutDlgProc()      - Message handler for the application's about
//                            dialog.
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


//
//  FUNCTION:   NewDBDlgProc( HWND  hWnd,UINT  message, WPARAM  wParam, LPARAM  lParam )
//
//  PURPOSE:    Callback function for creating a new Database
//
//  PARAMETERS:
//
//  RETURN VALUE:
//      (LRESULT) Dependant on the specific notification.  See Below.
//
//  COMMENTS:
//

BOOL CALLBACK NewDBDlgProc( HWND  hWnd,UINT  message, WPARAM  wParam, LPARAM  lParam )
{
  WORD wNotifyCode, wID;
  HWND hwndCtl;

  wNotifyCode = HIWORD(wParam); // notification code
  wID = LOWORD(wParam);         // item, control, or accelerator identifier
  hwndCtl = (HWND) lParam;      // handle of control

  switch(message)
  {
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hWnd,IDC_DBNAME));
		return FALSE;
		break;


    case WM_COMMAND:
    {
		switch(wID)
		{
			case IDCANCEL:
					EndDialog(hWnd, IDCANCEL);
					break;
				case IDOK:
				{
					TCHAR szNewDBName[CEDB_MAXDBASENAMELEN];
					DWORD dwNewDBType = 929292; // hardcode for now

					if ( GetDlgItemText(hWnd,IDC_DBNAME, szNewDBName, (CEDB_MAXDBASENAMELEN-10) ))
					{
						CEOID CeOid;
						_tcscat(szNewDBName,TEXT("_TEST"));

						if ( !(CeOid =CeCreateDatabase(szNewDBName, dwNewDBType, 0, NULL)) )
						{
							TCHAR szBuf[50];
                            long lError;

                            lError = GetLastError();
   							wsprintf(szBuf, TEXT("ERROR: CeCreateDatabase failed with error: %ld\r\n"), lError);
   							OutputDebugString(szBuf);
                            switch(lError)
                            {
                                case ERROR_DISK_FULL:
                                    wsprintf(szBuf, TEXT("There is not enough disk space.\r\n"),szNewDBName);
                                    break;
                                case ERROR_DUP_NAME:
                                    wsprintf(szBuf, TEXT("Database '%s' already exists.\r\n"),szNewDBName);
                                    break;
                                default:
                                    break;
                            }
							MessageBox(hWnd, szBuf, TEXT("Error"), MB_OKCANCEL );

						}
						else
						{
							HANDLE          hNewDB;
							FILETIME        FileTime;
							SYSTEMTIME      SystemTime;
							LPVOID          lpStr;
							LPVOID          lpBlob;
							HWND            hwndTV;
							HWND            hParent;
							
							if( (hParent = GetParent(hWnd) ) )
								hwndTV = GetDlgItem(hParent, IDC_TREEVIEW);
							else
								hwndTV = GetDlgItem(hWnd, IDC_TREEVIEW);

							// Try to open DB
							hNewDB = CeOpenDatabase(&CeOid, NULL, 0, 0, NULL);
							if ( hNewDB == INVALID_HANDLE_VALUE)
							{
								TCHAR szError[50];
								wsprintf(szError, TEXT("ERROR: CeOpenDatabase failed after creating DB (%ld)"), GetLastError());
								OutputDebugString(szError);
								MessageBox(hwndTV, szError, TEXT("Error"), MB_OKCANCEL );
							}
							else
							{

								CEPROPVAL  NewRecProps[7];

								NewRecProps[0].propid = PROP_SHORT;
								NewRecProps[0].wLenData = 0;
								NewRecProps[0].wFlags = 0;
								NewRecProps[0].val.iVal = -1;

								NewRecProps[1].propid = PROP_USHORT;
								NewRecProps[1].wLenData = 0;
								NewRecProps[1].wFlags = 0;
								NewRecProps[1].val.uiVal = 1;

								NewRecProps[2].propid = PROP_LONG;
								NewRecProps[2].wLenData = 0;
								NewRecProps[2].wFlags = 0;
								NewRecProps[2].val.lVal = 0xffffffff;

								NewRecProps[3].propid = PROP_ULONG;
								NewRecProps[3].wLenData = 0;
								NewRecProps[3].wFlags = 0;
								NewRecProps[3].val.ulVal = 0x7FFFFFFF;

								SystemTime.wYear = 1999;
								SystemTime.wMonth = 12;
								SystemTime.wDayOfWeek = 6;
								SystemTime.wDay = 25;
								SystemTime.wHour = 12;
								SystemTime.wMinute = 12;
								SystemTime.wSecond = 12;
								SystemTime.wMilliseconds = 12;

								SystemTimeToFileTime(&SystemTime,&FileTime);
								NewRecProps[4].propid = PROP_FILETIME;
								NewRecProps[4].wLenData = 0;
								NewRecProps[4].wFlags = 0;
								NewRecProps[4].val.filetime = FileTime;
								
								lpStr = LocalAlloc(LMEM_FIXED, 50 * sizeof(TCHAR));
								if ( lpStr )
									_tcscpy(lpStr, TEXT("This is a string property"));

								NewRecProps[5].propid = PROP_LPWSTR;
								NewRecProps[5].wLenData = 0;
								NewRecProps[5].wFlags = 0;
								NewRecProps[5].val.lpwstr = lpStr;

								lpBlob = LocalAlloc(LMEM_FIXED, 50  * sizeof(TCHAR));
								if ( lpBlob )
									_tcscpy(lpBlob, TEXT("This is a blob property"));

								NewRecProps[6].propid = PROP_CEBLOB;
								NewRecProps[6].wLenData = 0;
								NewRecProps[6].wFlags = 0;
								NewRecProps[6].val.blob.dwCount = 50  * sizeof(TCHAR);
								NewRecProps[6].val.blob.lpb  = lpBlob;

                                //write record out with 7 property fields...
                                if( !CeWriteRecordProps(hNewDB, 0, 7, NewRecProps) )
								{
									TCHAR szError[50];
									wsprintf(szError, TEXT("ERROR: CeWriteRecordProps failed (%ld)"), GetLastError());
									OutputDebugString(szError);
									MessageBox(hwndTV, szError, TEXT("Error"), MB_OKCANCEL );
								}

								if( lpBlob )
									LocalFree(lpBlob);
								if( lpStr )
									LocalFree(lpStr);


								CloseHandle(hNewDB);
								if (!AddItemToTree(hwndTV, szNewDBName, NULL, TRUE, CeOid))
									OutputDebugString(TEXT("ERROR: Failed to add Database"));
							}


						}
					}
					else
						OutputDebugString(TEXT("ERROR: CeCreateDatabase Error. Error retreiving data.\r\n"));

					EndDialog(hWnd, IDOK);

					break;
				}
			default:
			return(FALSE);
		}
		break;
    }
    default:
      return(FALSE);
  }
  return (TRUE);
}


//
//  FUNCTION:   ShowDBInformation( TCHAR * pDBName)
//
//  PURPOSE:    Display database information in edit control
//
//  PARAMETERS:
//
//  RETURN VALUE:
//
//  COMMENTS:
//

void WINAPI ShowDBInformation( TCHAR * pDBName)
{
	TCHAR           szBuf[2000];
	TCHAR           szSort[100] = {0};
	CEOID          CeOID = 0;
    CEOIDINFO  CeObject;
	HANDLE          hOpenDB;
	int                     i;

	// no notification installed
	hOpenDB = CeOpenDatabase(&CeOID, pDBName, 0, 0, NULL);
	if ( hOpenDB == INVALID_HANDLE_VALUE)
	{
		wsprintf(szBuf, TEXT("ERROR: CeOpenDatabase failed to open database.(Error: %ld)\r\n"), GetLastError());
		OutputDebugString(szBuf);
		MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OKCANCEL );
	}
	else
	{
		if ( !CeOidGetInfo(CeOID, &CeObject) )
		{
			wsprintf(szBuf, TEXT("ERROR: CeOidGetInfo failed with error (%ld)\r\n"), GetLastError());
			OutputDebugString(szBuf);
			MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OKCANCEL );
		}
		else
		{
            switch(CeObject.wObjType)
            {
                case OBJTYPE_INVALID:
                    wsprintf(szBuf, TEXT("The object store contains no valid object that has this object identifier. \n"));
                    OutputDebugString(szBuf);
                    break;
                case OBJTYPE_FILE:
                    wsprintf(szBuf, TEXT("The object is a file. \n"));
                    OutputDebugString(szBuf);
                    break;
                case OBJTYPE_DIRECTORY:
                    wsprintf(szBuf, TEXT("The object is a directory. \n"));
                    OutputDebugString(szBuf);
                    break;
                case OBJTYPE_DATABASE:
                    wsprintf(szBuf, TEXT("The object is a database. \n"));
                    OutputDebugString(szBuf);
                    break;
                case OBJTYPE_RECORD:
                    wsprintf(szBuf, TEXT("The object is a record inside a database. \n"));
                    OutputDebugString(szBuf);
                    break;
                default:
                    wsprintf(szBuf, TEXT("Unrecognized wObjType\n"));
                    OutputDebugString(szBuf);
            }
			wsprintf(szBuf, TEXT("DB Flags: %#lx\r\nDB Name: %ls\r\nDB Type: %ld\r\n#Records: %d\r\n#Sort Orders: %d\r\nSorted On:"),
			CeObject.infDatabase.dwFlags,
			CeObject.infDatabase.szDbaseName,
			CeObject.infDatabase.dwDbaseType,
			CeObject.infDatabase.wNumRecords,
			CeObject.infDatabase.wNumSortOrder);
			for ( i = 0 ; i < CeObject.infDatabase.wNumSortOrder ; i++)
			{
				wsprintf(szSort, TEXT("\r\nRow: %ld\r\n"), CeObject.infDatabase.rgSortSpecs[i].propid);
						
				if ( CeObject.infDatabase.rgSortSpecs[i].dwFlags & CEDB_SORT_DESCENDING )
					_tcscat(szSort, TEXT("  DESCENDING \r\n"));

				if ( CeObject.infDatabase.rgSortSpecs[i].dwFlags & CEDB_SORT_CASEINSENSITIVE )
					_tcscat(szSort, TEXT("  CASEINSENSITIVE \r\n"));

				if ( CeObject.infDatabase.rgSortSpecs[i].dwFlags & CEDB_SORT_UNKNOWNFIRST )
					_tcscat(szSort, TEXT("  UNKNOWNFIRST \r\n"));

				if ( CeObject.infDatabase.rgSortSpecs[i].dwFlags & CEDB_SORT_GENERICORDER )
					_tcscat(szSort, TEXT("  GENERICORDER \r\n"));
				
				_tcscat(szBuf, szSort);

			}
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)szBuf);

		}
		CloseHandle(hOpenDB);
	}
}



//
//  FUNCTION:   ShowPropDesc(CEPROPID PropId, TCHAR * pDBName, LONG dwCurrectRecord )
//
//  PURPOSE:    Display database property information in edit control
//
//  PARAMETERS:
//
//  RETURN VALUE:
//
//  COMMENTS:
//
void WINAPI ShowPropDesc(CEPROPID PropId, DWORD dwOpenHandle, LONG dwCurrentRecord)
{
	TCHAR		szBuf[200];
	WORD		cPropID = 1;
	LPBYTE 		bData = NULL;
	DWORD		cbData = 0;
	SYSTEMTIME	SystemTime;
	CEOID      CeOID = 0;
	DWORD		dwIndex;

	if ( (HANDLE) dwOpenHandle == INVALID_HANDLE_VALUE)
	{
		wsprintf(szBuf, TEXT("ERROR: CeOpenDatabase failed to open database.(Error: %ld)\r\n"), GetLastError());
		OutputDebugString(szBuf);
		MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OKCANCEL );
	}
	else
	{
		if ( dwCurrentRecord == -1 )
		{
			if ( !CeSeekDatabase((HANDLE) dwOpenHandle, CEDB_SEEK_CURRENT, 0, &dwIndex) )
			{
				dwIndex = 0;
				wsprintf(szBuf, TEXT("ERROR: CeSeekDatabase failed to get record index.(Error: %ld)\r\n"), GetLastError());
				OutputDebugString(szBuf);
				MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OKCANCEL );
				SendMessage(hEdit,WM_SETTEXT, 0, (LPARAM) (LPTSTR) TEXT(""));
				return;
			}
		}
		else
			dwIndex = dwCurrentRecord;

		// check for eof by reading after a seek failure
		if( !CeReadRecordProps((HANDLE)dwOpenHandle, CEDB_ALLOWREALLOC, &cPropID,&PropId,&bData,&cbData) )
		{
			DWORD dwError;

			if ( (dwError=GetLastError()) != ERROR_NO_MORE_ITEMS )
			{
				wsprintf(szBuf, TEXT("ERROR: CeReadRecordProps failed to read database.(Error: %ld)\r\n"), dwError);
				OutputDebugString(szBuf);
				MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OKCANCEL );
				SendMessage(hEdit,WM_SETTEXT, 0, (LPARAM) (LPTSTR) TEXT(""));
			}
			else
				SendMessage(hEdit,WM_SETTEXT, 0, (LPARAM) (LPTSTR) TEXT("End-OF-File"));

			return;
		}
		
	}

	if( bData == NULL )
	{
		wsprintf(szBuf, TEXT("ERROR: CeReadRecordProps failed to read database.(Error: %ld)\r\n"), GetLastError());
		MessageBox(NULL, szBuf, TEXT("ERROR"), MB_OKCANCEL );
		OutputDebugString(szBuf);
		return;
	}


	switch(TypeFromPropID(PropId))
	{
		case CEVT_I2:
			wsprintf(szBuf, TEXT("Record: %ld\r\nProperty: Short\r\nDATA:\r\n%d"), dwIndex, bData?((PCEPROPVAL) bData)->val.iVal: 0) ;
			break;
		case CEVT_UI2:
			wsprintf(szBuf, TEXT("Record: %ld\r\nProperty: Unsigned Short\r\nDATA:\r\n%d"), dwIndex, bData?((PCEPROPVAL) bData)->val.uiVal: 0) ;
			break;
		case CEVT_I4:
			wsprintf(szBuf, TEXT("Record: %ld\r\nProperty: Long\r\nDATA:\r\n%d"), dwIndex, bData?((PCEPROPVAL) bData)->val.lVal: 0) ;
			break;
		case CEVT_UI4:
			wsprintf(szBuf, TEXT("Record: %ld\r\nProperty: Unsigned Long\r\nDATA:\r\n%d"), dwIndex, bData?((PCEPROPVAL) bData)->val.ulVal: 0) ;
			break;
		case CEVT_FILETIME:
			if ( bData != NULL )
			{
				FileTimeToSystemTime(&(((PCEPROPVAL) bData)->val.filetime), &SystemTime);

				wsprintf(szBuf, TEXT("Record: %ld\r\nProperty: File Time\r\nDATA:\r\nYear:%d\r\nMonth:%d\r\n"
					TEXT("Day:%d\r\nDay of Week:%d\r\nHour:%d\r\nMinute:%d\r\nSecond:%d\r\nMilliseconds:%d")),
					dwIndex, SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wDayOfWeek,
					SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond, SystemTime.wMilliseconds) ;
			}
			else
				wsprintf(szBuf,TEXT("Record: %ld\r\nProperty: File Time"), dwIndex);

			break;
		case CEVT_LPWSTR:
			wsprintf(szBuf, TEXT("Record: %ld\r\nProperty: String\r\nDATA:\r\n%-70s"), dwIndex,
				bData?((PCEPROPVAL) bData)->val.lpwstr: NULL) ;

			if ( bData && lstrlen(((PCEPROPVAL) bData)->val.lpwstr) > 70 )
				lstrcat(szBuf, TEXT("..."));

			break;
		case CEVT_BLOB:
		{
			DWORD dwMaxShow = 15;
			TCHAR szTempBuf[6];
			DWORD i;
			wsprintf(szBuf,TEXT("Record: %ld\r\nProperty: BLOB\r\nDATA:\r\n"), dwIndex);
			if( bData )
			{
				dwMaxShow = min(dwMaxShow, ((PCEPROPVAL) bData)->val.blob.dwCount);
				for (i = 0; i < dwMaxShow; i++)
				{
				  wsprintf (szTempBuf, TEXT("%#2x,"), (BYTE)((PCEPROPVAL) bData)->val.blob.lpb[i]);
				  lstrcat (szBuf, szTempBuf);
				}
				if (dwMaxShow < ((PCEPROPVAL) bData)->val.blob.dwCount )
					lstrcat (szBuf, TEXT("..."));
			}
			break;
		}
		default:
			wsprintf(szBuf, TEXT("Record: %ld\r\nUnknown record property"),dwIndex);
			break;
	}
	if ( bData )
		LocalFree(bData);

	SendMessage(hEdit,WM_SETTEXT, 0, (LPARAM)(LPCTSTR)szBuf);
}

void WINAPI AddRecToCurrentDB(HWND hwnd)
{
	HWND            hwndTV;
	HWND            hParent;
	HTREEITEM       hItem;
	TCHAR           szDBName[CEDB_MAXDBASENAMELEN];
	TV_ITEM         tvCurrent = {0};

	if( (hParent = GetParent(hwnd) ) )
		hwndTV = GetDlgItem(hParent, IDC_TREEVIEW);
	else
		hwndTV = GetDlgItem(hwnd, IDC_TREEVIEW);

	if( (hItem = TreeView_GetSelection( hwndTV )) )
	{
		tvCurrent.hItem = hItem;
		tvCurrent.mask |= (TVIF_TEXT|TVIF_PARAM);
		tvCurrent.pszText = szDBName;
		tvCurrent.cchTextMax =  CEDB_MAXDBASENAMELEN;
		

		if (!TreeView_GetItem(hwndTV, &tvCurrent))
			OutputDebugString(TEXT("ERROR: Database Deletion failed.\r\n"));
		else
		{

			if ( _tcsstr( szDBName, TEXT("_TEST") ) && (HANDLE) tvCurrent.lParam != INVALID_HANDLE_VALUE)
			{
				int				nRet;
				INSERTSTRUCT	NewRecord;

				if ( (nRet=DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_NEWRECORD), hwnd,
						(WNDPROC)AddRecDlgProc,(LPARAM)&NewRecord)) != -1)
				{
					if( nRet == IDOK)
					{
						CEPROPVAL  NewRecProps[7];
						SYSTEMTIME	SystemTime;
						FILETIME	FileTime;

						NewRecProps[0].propid = PROP_SHORT;
						NewRecProps[0].wLenData = 0;
						NewRecProps[0].wFlags = 0;
						NewRecProps[0].val.iVal = NewRecord.shNumber;

						NewRecProps[1].propid = PROP_USHORT;
						NewRecProps[1].wLenData = 0;
						NewRecProps[1].wFlags = 0;
						NewRecProps[1].val.uiVal = NewRecord.ushNumber;

						NewRecProps[2].propid = PROP_LONG;
						NewRecProps[2].wLenData = 0;
						NewRecProps[2].wFlags = 0;
						NewRecProps[2].val.lVal = NewRecord.lNumber;

						NewRecProps[3].propid = PROP_ULONG;
						NewRecProps[3].wLenData = 0;
						NewRecProps[3].wFlags = 0;
						NewRecProps[3].val.ulVal = NewRecord.ulNumber;

						GetSystemTime(&SystemTime );

						SystemTimeToFileTime(&SystemTime,&FileTime);
						NewRecProps[4].propid = PROP_FILETIME;
						NewRecProps[4].wLenData = 0;
						NewRecProps[4].wFlags = 0;
						NewRecProps[4].val.filetime = FileTime;
						
						NewRecProps[5].propid = PROP_LPWSTR;
						NewRecProps[5].wLenData = 0;
						NewRecProps[5].wFlags = 0;
						NewRecProps[5].val.lpwstr = NewRecord.pString;

						NewRecProps[6].propid = PROP_CEBLOB;
						NewRecProps[6].wLenData = 0;
						NewRecProps[6].wFlags = 0;
						NewRecProps[6].val.blob.dwCount = NewRecord.cbBlob;
						NewRecProps[6].val.blob.lpb  = NewRecord.pBlob;

						if( !CeWriteRecordProps((HANDLE) tvCurrent.lParam, 0, 7, NewRecProps) )
						{
							TCHAR	szError[50];
							wsprintf(szError, TEXT("ERROR: CeWriteRecordProps failed (%ld)"), GetLastError());
							MessageBox(hwnd, szError, TEXT("ERROR"), MB_OKCANCEL );
							OutputDebugString(szError);
						}

						if( NewRecord.pBlob)
							LocalFree(NewRecord.pBlob);

						if( NewRecord.pString)
							LocalFree(NewRecord.pString);


					}
				}
			}
            else
            {
                TCHAR   szError[50];
                wsprintf(szError, TEXT("Can not modify this database."));
                MessageBox(hwnd, szError, TEXT("DBView"), MB_OKCANCEL);
            }
		}

	}
	else                                                             // database property
		OutputDebugString(TEXT("Deleting currently selected DB.\r\n"));

}


//
//  FUNCTION:   DeleteCurrentDB(HWND hwnd)
//
//  PURPOSE:    Delete the currently selected Database
//
//  PARAMETERS:
//
//  RETURN VALUE:
//
//  COMMENTS:
//
void WINAPI DeleteCurrentDB(HWND hwnd)
{
	HWND            hwndTV;
	HWND            hParent;
	HTREEITEM       hItem;
	TCHAR           szDBName[CEDB_MAXDBASENAMELEN];
	TCHAR           szBuf[200];
	TV_ITEM         tvCurrent = {0};

	if( (hParent = GetParent(hwnd) ) )
		hwndTV = GetDlgItem(hParent, IDC_TREEVIEW);
	else
		hwndTV = GetDlgItem(hwnd, IDC_TREEVIEW);

	if( (hItem = TreeView_GetSelection( hwndTV )) )
	{
		//memset(&tvCurrent, 0, sizeof(TV_ITEM));
		tvCurrent.hItem = hItem;
		tvCurrent.mask |= (TVIF_TEXT|TVIF_PARAM);
		tvCurrent.pszText = szDBName;
		tvCurrent.cchTextMax =  CEDB_MAXDBASENAMELEN;
		

		if (!TreeView_GetItem(hwndTV, &tvCurrent))
			OutputDebugString(TEXT("ERROR: Database Deletion failed.\r\n"));
		else
		{

			if ( _tcsstr( szDBName, TEXT("_TEST") ) )
			{
				HANDLE          hNewDB;
				CEOID          CeOid = (CEOID)NULL;

				wsprintf(szBuf, TEXT("Delete Database: %s"), szDBName);
				if ( MessageBox(hwnd, szBuf, TEXT("Delete Database"), MB_YESNO) == IDYES )
				{
					// Try to open DB and get ID required for deletion
					hNewDB = CeOpenDatabase(&CeOid, szDBName, 0, 0, NULL);
					if ( hNewDB == INVALID_HANDLE_VALUE)
					{
						TCHAR szError[50];
						wsprintf(szError, TEXT("ERROR: CeOpenDatabase failed after creating DB (%ld)"), GetLastError());
						MessageBox(hwnd, szError, TEXT("ERROR"), MB_OKCANCEL );
						OutputDebugString(szError);

					}
					else
					{
						// close 2 DB before deleting
						// 1) used to get ID
						// 2) used current record stuff
						if ( CloseHandle(hNewDB) && CloseHandle((HANDLE) tvCurrent.lParam))
						{
							if ( !CeDeleteDatabase(CeOid) )
							{
								wsprintf(szBuf, TEXT("ERROR: CeDeleteDatabase failed with error: %ld\r\n"), GetLastError());
								MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OKCANCEL );
								OutputDebugString(szBuf);
							}
							else
								TreeView_DeleteItem(hwndTV, hItem);
						}
						else
						{
							wsprintf(szBuf, TEXT("ERROR: CloseHandle failed with error: %ld\r\n"), GetLastError());
							MessageBox(hwnd, szBuf, TEXT("ERROR"), MB_OKCANCEL );
							OutputDebugString(szBuf);
						}
					}
				}
			}
			else
				MessageBox(hwndTV, TEXT("Selected Database not created by test program."), TEXT("Invalid Database"), MB_OKCANCEL );
		}

	}
	else                                                             // database property
		OutputDebugString(TEXT("Deleting currently selected DB.\r\n"));
}

