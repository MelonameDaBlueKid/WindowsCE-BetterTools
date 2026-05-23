// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     memory.c
//
//  PURPOSE:    Contains window procedures for memory determination.
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



//
//  FUNCTION:   MemoryDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam )
//
//  PURPOSE:    Callback function for Memory Dialog
//
//  PARAMETERS:
//
//  RETURN VALUE:
//      (LRESULT) Dependant on the specific notification.  See Below.
//
//  COMMENTS:
//
BOOL CALLBACK MemoryDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam )
{
  WORD wNotifyCode, wID;
  HWND hwndCtl;
  TCHAR szBuf[50];
  DWORD rc;
  wNotifyCode = HIWORD(wParam); // notification code
  wID = LOWORD(wParam);         // item, control, or accelerator identifier
  hwndCtl = (HWND) lParam;      // handle of control

  switch(message)
  {
    case WM_COMMAND:
    {
	switch(wID)
	{
			case IDOK:
			case IDCANCEL:
				EndDialog(hDlg, TRUE);
				break;
	    default:
		return(FALSE);
	}
		break;
    }
    case WM_INITDIALOG:
		{
			STORE_INFORMATION si;

			if ( GetStoreInformation(&si) )
			{
				wsprintf(szBuf, TEXT("%ld"), si.dwStoreSize);
				SetDlgItemText(hDlg,IDC_AVAIL, szBuf);
				wsprintf(szBuf, TEXT("%ld"), si.dwFreeSize);
				SetDlgItemText(hDlg,IDC_FREE, szBuf);

			}
			else
			{
				if ( ERROR_NOT_SUPPORTED != (rc=GetLastError()) )
				{
					wsprintf(szBuf, TEXT("Error: GetStoreInformation failed (Error %ld)\r\n"), rc);
					MessageBox(hDlg, szBuf, TEXT("ERROR"), MB_OK);
					OutputDebugString(szBuf);
				}
				else
					OutputDebugString(TEXT("Warning: GetStoreInformation is not supported on platform.\r\n"));

			}

		break;
		}
    default:
      return(FALSE);
  }
  return (TRUE);
}

