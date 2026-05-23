// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:		enumdb
//
//  PURPOSE:    Contains functions that perform the database enumerations
//
//  PLATFORMS: 	Windows CE
//
//  FUNCTIONS:
//
//  COMMENTS:
//
//

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "globals.h"



//
//  FUNCTION:   EnumDbaseProps(HWND hwndTV, HTREEITEM htiParent, DWORD dwOpenHandle); //TCHAR * pDBName)
//
//  PURPOSE:    Enumerates database properties.
//
//  PARAMETERS:
//      hwndTV          - TreeView to add the contents to
//      htiParent       - TreeView item to add the contents as children of
//		pDBName			- Database name to enumerate
//  RETURN VALUE:
//
//  COMMENTS:
//

void WINAPI EnumDbaseProps(HWND hwndTV, HTREEITEM htiParent, DWORD dwOpenHandle)
{
    TCHAR		szBuf[100];
	CEOID		CeRecObj;
	CEOID		CeOID = 0;
    DWORD		cbRecProps = 0;
	LPBYTE		lpRecProps = NULL;
	WORD		wNumRecProps = 0;
	WORD		i;
	TV_ITEM     tvParent;

	PCEPROPVAL pCePropVal;

	if ( (HANDLE) dwOpenHandle == INVALID_HANDLE_VALUE)

		MessageBox(NULL, TEXT("CeOpenDatabase failed after creating DB"), TEXT("Error"), MB_OK);
	else
	{
		// read all properties
		if ( (CeRecObj = CeReadRecordProps((HANDLE) dwOpenHandle, CEDB_ALLOWREALLOC,
					&wNumRecProps, NULL, &lpRecProps, &cbRecProps)) )
		{
			if ( lpRecProps )
			{
				if ( wNumRecProps )
				{
					pCePropVal = (PCEPROPVAL)lpRecProps;

					// add each property to treeview
					for ( i= 0 ; i < wNumRecProps; i++)
					{
						wsprintf(szBuf, TEXT("%#lx"), pCePropVal[i].propid);//HIWORD(pCePropVal[i].propid));
						if (!AddItemToTree(hwndTV, szBuf, htiParent, FALSE, pCePropVal[i].propid) )
							OutputDebugString(TEXT("ERROR: AddItemToTree item failed.\r\n"));
							
					}
					tvParent.hItem = htiParent;
					tvParent.mask = TVIF_CHILDREN;
					tvParent.cChildren = 1;

					if (!TreeView_SetItem(hwndTV, &tvParent))
						OutputDebugString(TEXT("ERROR: Modifying parent item for child items.\r\n"));

				}
				LocalFree(lpRecProps);
			}

			
	   }
	   else
	   {
		   DWORD dwRtn;

		   if ( ERROR_NO_MORE_ITEMS != (dwRtn=GetLastError()) )
		   {
			   wsprintf(szBuf, TEXT("CeReadrecordProps failed with error: %ld"), dwRtn);
			   MessageBox(NULL, szBuf, TEXT("Error"), MB_OK );
		   }
		   else
		   {
			   // remove child attribut from parent
				TV_ITEM         tvi;

				tvi.hItem = htiParent;
				tvi.mask = TVIF_CHILDREN;
				tvi.cChildren = 0;

				if( !TreeView_SetItem(hwndTV, &tvi) )
					OutputDebugString(TEXT("ERROR: setting item for no children.\r\n"));
		   }
	   }
	}
}


//
//  FUNCTION:   EnumDbase(HWND hwndTV, HTREEITEM htiParent)
//
//  PURPOSE:    Enumerates system databases
//
//  PARAMETERS:
//      hwndTV          - TreeView to add the contents to
//      htiParent       - TreeView item to add the contents as children of
//  RETURN VALUE:
//
//  COMMENTS:
//

void WINAPI EnumDbase(HWND hwndTV, HTREEITEM htiParent)
{
    HANDLE hEnumObject;
    TCHAR  szBuf[100];
    CEOID ObjectID;
    CEOIDINFO CeObject;
    DWORD      rc;

	// enumerate all dbs
    if( (hEnumObject = CeFindFirstDatabase(0)) != INVALID_HANDLE_VALUE)
    {
        while( (ObjectID = CeFindNextDatabase(hEnumObject)) != 0)
		{
			// get db information
			if ( !CeOidGetInfo(ObjectID, &CeObject) )
			{
				wsprintf(szBuf, TEXT("CeOidGetInfo failed with error (%ld)"), GetLastError());
				MessageBox(NULL, szBuf, TEXT("Error"), MB_OK);
				break;
			}
			else
			{
				// add database name to treeview
				if (!AddItemToTree(hwndTV, CeObject.infDatabase.szDbaseName, htiParent, TRUE, ObjectID))
					OutputDebugString(TEXT("ERROR: Failed to add Database\r\n"));
			}

		}
        if ( (rc=GetLastError()) != ERROR_NO_MORE_ITEMS )
        {
            wsprintf(szBuf, TEXT("CeFindFirstDatabase failed with error (%ld)"), rc);
            MessageBox(NULL, szBuf, TEXT("Error"), MB_OK);
        }

    }
    else
    {
        wsprintf(szBuf, TEXT("CeFindFirstDatabase failed with error (%ld)"), GetLastError());
        MessageBox(NULL, szBuf, TEXT("Error"), MB_OK);
    }
}
