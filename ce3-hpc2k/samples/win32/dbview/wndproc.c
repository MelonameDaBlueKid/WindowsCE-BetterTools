// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     wndproc.c
//
//  PURPOSE:    Contains window procedures for the main application windows.
//
//  PLATFORMS:  Windows CE
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
#include "WINDBASE.H"

//----------------------------------------------------------------------------
// Local prototypes




static TBBUTTON tbVIEWButton[] = {
	{DB_NEXT_REC, DB_NEXT_REC, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
	{DB_PREV_REC, DB_PREV_REC, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 1},
	{DB_ADD_REC,  DB_ADD_REC,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 2}
};


LRESULT OnSetFocus(HWND hwndLostFocus, HWND dummy)
{
    SetFocus(g_hwndTreeView);
    return 0;
}

//----------------------------------------------------------------------------

//
//  FUNCTION:   MainWndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:    Processes messages for the main application window.
//
//  PARAMETERS:
//      hwnd        - handle the the window receiving the message
//      uMsg        - identifier of the message
//      wParam      - additional info associated with the message
//      lParam      - additional info associated with the message
//
//  RETURN VALUE:
//      (LRESULT) Returns 0 by default if the message is handled by this
//                procedure.
//
//  COMMENTS:
//
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam,
			     LPARAM lParam)
{
    switch(uMsg)
    {
	HANDLE_MSG(hwnd, WM_COMMAND,            Main_OnCommand);
	HANDLE_MSG(hwnd, WM_DESTROY,            Main_OnDestroy);
	HANDLE_MSG(hwnd, WM_CREATE,             Main_OnCreate );
	HANDLE_MSG(hwnd, WM_NOTIFY,             Main_OnNotify );
    HANDLE_MSG(hwnd, WM_SETFOCUS,           OnSetFocus);  // set focus to treeview
	default:                // Pass message on for default proccessing
	    return DefWindowProc( hwnd, uMsg, wParam, lParam );
    }

    // If we performed non-default processing on the message, return FALSE
    return FALSE;
}


//
//  FUNCTION:   Main_OnCommand(HWND, int, HWND, UINT)
//
//  PURPOSE:    Handles the WM_COMMAND messages for the Win32Generic window
//              class
//
//  PARAMETERS:
//      hwnd        - handle of the window receiving the message
//      id          - identifier of the command
//      hwndCtl     - handle of the control sending the message)
//      codeNotify  - specifies the notification code if the message is from
//                    a control
//
//  RETURN VALUE:
//      none
//
//  COMMENTS:
//      codeNotify is 1 if from an accelerator, 0 if from a menu.
//      If the message is not from a control hwndCtl is NULL.
//

LRESULT WINAPI Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
		case IDM_FILE_EXIT:
			// The user wants to exit, so send our window a close message
			SendMessage(hwnd, WM_CLOSE, 0, 0L);
			break;

		case IDM_HELP_ABOUT:
			// Display the "About" dialog
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, AboutDlgProc);
			break;

		case ID_OBJECTSTORE_STORAGESPACE:
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_PEGMEMORY), hwnd, (WNDPROC)MemoryDlgProc);
			break;
		case IDM_CREATEDB:
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_NEWDBNAME), hwnd, (WNDPROC)NewDBDlgProc);
			break;
		case IDM_DELETEDB:
			DeleteCurrentDB(hwnd);
			break;

		case DB_NEXT_REC:
			SeekNextRecord(hwnd, 1);
			break;

		case DB_PREV_REC:
			SeekNextRecord(hwnd, (DWORD) -1);
			break;

		case DB_ADD_REC:
			AddRecToCurrentDB(hwnd);
			break;

		case IDM_INDEXDB:
			ModifyIndex(hwnd);
			break;
		case IDM_USEINDEXES:
			OpenIndex(hwnd);
			break;

		default:
			return 1L;

    }

	return 0L;
}


//
//  FUNCTION:   Main_OnDestroy(HWND)
//
//  PURPOSE:    Handle any clean up and post the quit message to exit the
//              message loop.
//
//  PARAMETERS:
//      hwnd    - handle of the window receiving this message
//
//  RETURN VALUE:
//      none
//

void WINAPI Main_OnDestroy(HWND hwnd)
{
    // Indicate that the message loop should exit since the main window
    // is being destroyed.
	CommandBar_Destroy(hwndCB);
	if ( himl )
		ImageList_Destroy(himl);

    PostQuitMessage(0);
}


//
//  FUNCTION:   Main_OnCreate(HWND, LPCREATESTRUCT)
//
//  PURPOSE:    Create the treeview control and initialize the data
//
//  PARAMETERS:
//      hwnd                    - handle of the window receiving this message
//              lpCreateStruct  - points to a CREATESTRUCT containing information
//                                                about the window creation
//
//  RETURN VALUE:
//      returns TRUE if the window should be created, FALSE otherwise
//
//  COMMENTS:
//

BOOL WINAPI Main_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	HWND hwndTV;
	RECT rcClient;
    int  nCommandHeight;
	BOOL bButton;

	// Start by initializing the common control libraries
	InitCommonControls();

	// Get the client area rect to put the treeview in
	GetClientRect(hwnd, &rcClient);

	hwndCB = CommandBar_Create(g_hInstance, hwnd, 1);
	CommandBar_AddBitmap(hwndCB, g_hInstance, IDB_BUTTONS, 3, 16, 16);

	
	bButton = CommandBar_AddButtons(hwndCB, 3, tbVIEWButton);

	CommandBar_InsertMenubar(hwndCB, g_hInstance, IDM_MAIN, 0);


	CommandBar_AddAdornments(hwndCB, 0, 0);

    nCommandHeight = CommandBar_Height(hwndCB);
	// We need to create the treeview control
	hwndTV = CreateWindowEx(0, WC_TREEVIEW, TEXT("DB View Control"),
							WS_VISIBLE | WS_CHILD | TVS_HASLINES |
							TVS_LINESATROOT | TVS_HASBUTTONS | WS_BORDER, 0, nCommandHeight,
							rcClient.right/2, rcClient.bottom-nCommandHeight, hwnd,
							(HMENU) IDC_TREEVIEW, g_hInstance, NULL);

	hEdit = CreateWindow(TEXT("EDIT"), TEXT("Property Information"),
							WS_VISIBLE | WS_CHILD | ES_MULTILINE |  ES_READONLY | WS_VSCROLL | WS_BORDER ,
							rcClient.right/2, nCommandHeight,
							rcClient.right/2, rcClient.bottom-nCommandHeight, hwnd,
							(HMENU) IDC_EDITCONTROL, g_hInstance, NULL);

	// Make sure the treeview was actually created
	if (!hwndTV)
	{
		ErrorHandler();
		return FALSE;
	}


	// Initialize the image list, and add items to the control.
	// InitTreeViewImageLists() and InitTreeViewItems() are defined in treeview.c.
	if (!InitDBViewImageLists(hwndTV) || !InitDBViewItems(hwndTV))
	{
		DestroyWindow(hwndTV);
		return FALSE;
	}

	// Everything is set up correctly, now set the global handle to the treeview
	// and finish window creation.
	g_hwndTreeView = hwndTV;

	return TRUE;
}


//
//  FUNCTION:   AboutDlgProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:    Processes messages for the About dialog box
//
//  PARAMETERS:
//      hwnd    - window handle of the dialog box
//      uMsg    - identifier of the message being handled
//      wParam  - additional info associated with the message
//      lParam  - additional info associated with the message
//
//  RETURN VALUE:
//      Except in response to the WM_INITDIALOG message, the dialog box
//      procedure should return nonzero if it processes the message, and zero
//      if it does not.
//
//  COMMENTS:
//

LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam,
			      LPARAM lParam)
{
    switch(uMsg)
    {
	case WM_INITDIALOG:
	    // Should return nonzero to set focus to the first control in the
	    // dialog, or zero if this routine sets the focus manually.
	    return (TRUE);

	case WM_COMMAND:
	    switch (LOWORD(wParam))
	    {
			case IDOK:
				EndDialog(hwnd, 0);
				break;
			case IDCANCEL:
				EndDialog(hwnd, 0);
				break;
	    }
	    return (TRUE);
    }
    return (FALSE);
}



BOOL CALLBACK AddRecDlgProc( HWND  hWnd,UINT  message, WPARAM  wParam, LPARAM  lParam )
{
  WORD wNotifyCode, wID;
  HWND hwndCtl;
  static INSERTSTRUCT * pInsert;
  wNotifyCode = HIWORD(wParam); // notification code
  wID = LOWORD(wParam);         // item, control, or accelerator identifier
  hwndCtl = (HWND) lParam;      // handle of control

  switch(message)
  {
	case WM_INITDIALOG:
	    // Should return nonzero to set focus to the first control in the
	    // dialog, or zero if this routine sets the focus manually.
		pInsert = (INSERTSTRUCT *) lParam;
	    return (TRUE);

	  case WM_COMMAND:
	  {
			switch(wID)
			{
				case IDCANCEL:
						EndDialog(hWnd, IDCANCEL);
						break;
				case IDC_SAVE:
				{
					BOOL bTranslS, bTranslUS;
					DWORD  cbLong, cbULong, cbString, cbBlob;
					TCHAR * pszLong, *pszULong, * pString;
					BYTE  * pBlob;
					UINT	unChars;
                    BOOL bStatus = TRUE;

                    // Initialize Properties structure
					pInsert->shNumber = 0;
                    pInsert->ushNumber = 0;
                    pInsert->lNumber = 0;
                    pInsert->ulNumber = 0;
                    pInsert->pString = NULL;
					pInsert->pBlob = NULL;
					pInsert->cbBlob = 0;

					
					// Short
                    pInsert->shNumber = (short) GetDlgItemInt(hWnd,IDC_SHORT,&bTranslS,TRUE );	

                    // Unsigned Short
					pInsert->ushNumber = GetDlgItemInt(hWnd,IDC_USHORT,&bTranslUS,FALSE );	

                    // Long
                    cbLong = SendDlgItemMessage(hWnd, IDC_LONG, WM_GETTEXTLENGTH, 0, 0);
					pszLong = LocalAlloc( LPTR , max(cbLong, (cbLong * sizeof(TCHAR) + sizeof(TCHAR))));
					if ( pszLong && bStatus)
					{
						if ( unChars = GetDlgItemText(hWnd,IDC_LONG,pszLong, cbLong) )
							pInsert->lNumber = _ttol(pszLong);
                        LocalFree(pszLong);
					}
                    else
                    {
						TCHAR szError[50];
						wsprintf(szError, TEXT("ERROR: could not allocate memory for field 'Long'."), GetLastError());
						OutputDebugString(szError);
						MessageBox(hWnd, szError, TEXT("Error"), MB_OK);                                            
                        bStatus = FALSE;
                    }

                    // Unsigned Long
                    cbULong = SendDlgItemMessage(hWnd, IDC_ULONG, WM_GETTEXTLENGTH, 0, 0);
					pszULong = LocalAlloc( LPTR , max(cbULong, (cbLong * sizeof(TCHAR) + sizeof(TCHAR))));
					if ( pszULong)
					{
						if ( unChars = GetDlgItemText(hWnd,IDC_ULONG,pszULong,cbULong) )
							pInsert->ulNumber = (unsigned long) _ttol(pszULong);
                        LocalFree(pszULong);
					}

					// String
                    cbString = SendDlgItemMessage(hWnd, IDC_STRING, WM_GETTEXTLENGTH, 0, 0);
					pString = (TCHAR *) LocalAlloc( LPTR , (cbString * sizeof(TCHAR) + sizeof(TCHAR)));
					if ( pString)
					{
						if ( unChars = GetDlgItemText(hWnd,IDC_STRING, pString, (INT) cbString))
							pInsert->pString = pString;
					    LocalFree(pString);
                    }

                    // Blob
                    cbBlob = SendDlgItemMessage(hWnd, IDC_BLOB, WM_GETTEXTLENGTH, 0, 0);
					pBlob = (BYTE *) LocalAlloc( LPTR , (cbBlob * sizeof(TCHAR) + sizeof(TCHAR)));
					if ( pBlob)
					{
						if ( unChars = GetDlgItemText(hWnd,IDC_BLOB,(TCHAR *)pBlob, cbBlob) )
						{
							pInsert->pBlob = pBlob;
							pInsert->cbBlob = cbBlob * sizeof(TCHAR);
						}
                        LocalFree(pBlob);
					}
					
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
//  FUNCTION:   Main_OnNotify(HWND, int, LPNMHDR)
//
//  PURPOSE:    Handles any notifications the treeview control spits out.
//
//  PARAMETERS:
//      hwnd    - handle of the window receiving the notification
//      idCtl   - identifies the control sending the notification
//      pnmh    - points to a NMHDR struct with more inforamation regarding the
//                notification
//
//  RETURN VALUE:
//      (LRESULT) Dependant on the specific notification.  See Below.
//
//  COMMENTS:
//

LRESULT WINAPI Main_OnNotify(HWND hwnd, int idCtl, LPNMHDR pnmh)
{
	HTREEITEM hti, htiNext;

	switch (pnmh->code)
	{
		// A directory node has been collapsed.  Now we can remove the child items
		// from the node.

		case TVN_SELCHANGED:
		{

			HTREEITEM hti;
			TV_ITEM	  ParentItem;
			TCHAR szEntryName[CEDB_MAXDBASENAMELEN];
			LPNM_TREEVIEW pnmtv = (LPNM_TREEVIEW) pnmh;

			if ( bRemovingProps )
				break;

			OutputDebugString(TEXT("Item selected\r\n"));


			// Check to see if this is a database or property
			// if item has no parent then database
			if ( !(hti=TreeView_GetParent(pnmh->hwndFrom, pnmtv->itemNew.hItem )) )
			{
				
				OutputDebugString(TEXT("Display Database Information\r\n"));

				// Get the text parent
				pnmtv->itemNew.mask |= TVIF_TEXT;
				pnmtv->itemNew.pszText = szEntryName;
				pnmtv->itemNew.cchTextMax =  CEDB_MAXDBASENAMELEN;

				if (!TreeView_GetItem(pnmtv->hdr.hwndFrom, &pnmtv->itemNew))
					return (FALSE);
				else
				{
					// Show DB Properties
					ShowDBInformation(szEntryName);

				}

			}
			else                                                             // database property
			{
				DWORD dwOpenHandle = (DWORD) INVALID_HANDLE_VALUE;
				ParentItem.hItem = hti;
				ParentItem.mask = TVIF_PARAM;

				if ( TreeView_GetItem(pnmh->hwndFrom, &ParentItem) )
					dwOpenHandle = ParentItem.lParam;

				OutputDebugString(TEXT("Display Database Property Information\r\n"));

				// Get the text child property
				pnmtv->itemNew.mask |= (TVIF_TEXT | TVIF_PARAM);
				pnmtv->itemNew.pszText = szEntryName;
				pnmtv->itemNew.cchTextMax = CEDB_MAXDBASENAMELEN;

				if (!TreeView_GetItem(pnmtv->hdr.hwndFrom, &pnmtv->itemNew))
					return (FALSE);
				else
				{
				   ShowPropDesc(pnmtv->itemNew.lParam, dwOpenHandle, -1);

				}


			}
			break;
		}



		case TVN_ITEMEXPANDED:
		{
			LPNM_TREEVIEW pnmtv = (LPNM_TREEVIEW) pnmh;

			if (pnmtv->action == TVE_COLLAPSE)
			{
				OutputDebugString(TEXT("Item collapsed\r\n"));

				// Now actually remove the child items within this directory
				hti = TreeView_GetChild(pnmh->hwndFrom, pnmtv->itemNew.hItem);
				while (hti)
				{
					htiNext = TreeView_GetNextSibling(pnmh->hwndFrom, hti);
					TreeView_DeleteItem(pnmh->hwndFrom, hti);
					hti = htiNext;
				}
			}

			return (FALSE);
		}
			
	// A node is expanding or collapsing.  We need to update the folder
	// images to reflect either a closed or open folder depending on it's
	// new state.
		case TVN_ITEMEXPANDING:
		{
			// cast the NMHDR into a treeview notify structure
			LPNM_TREEVIEW pnmtv = (LPNM_TREEVIEW) pnmh;

			if (pnmtv->action == TVE_COLLAPSE)
			{
				OutputDebugString(TEXT("Item collapsing\r\n"));

				// Retrieve the image from the current item
				pnmtv->itemNew.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
				TreeView_GetItem(pnmh->hwndFrom, &(pnmtv->itemNew));

				// Set the item's image to the closed folder
				pnmtv->itemNew.iImage = IMAGE_CLOSED;
				pnmtv->itemNew.iSelectedImage = IMAGE_CLOSED;
		
				TreeView_SetItem(pnmh->hwndFrom, &(pnmtv->itemNew));
			}
			else
			{
				TCHAR szDBName[CEDB_MAXDBASENAMELEN];
				OutputDebugString(TEXT("Item expanding\r\n"));

				// Retrieve the image from the current item
				pnmtv->itemNew.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
				TreeView_GetItem(pnmh->hwndFrom, &(pnmtv->itemNew));

				// Set the item's image to the closed folder
				pnmtv->itemNew.iImage = IMAGE_OPEN;
				pnmtv->itemNew.iSelectedImage = IMAGE_OPEN;
				TreeView_SetItem(pnmh->hwndFrom, &(pnmtv->itemNew));

				// Get the text for the first item
				pnmtv->itemNew.mask |= (TVIF_TEXT|TVIF_PARAM);
				pnmtv->itemNew.pszText = szDBName;
				pnmtv->itemNew.cchTextMax =  CEDB_MAXDBASENAMELEN;
				if (!TreeView_GetItem(pnmtv->hdr.hwndFrom, &pnmtv->itemNew))
					return (FALSE);
				else
					EnumDbaseProps(pnmtv->hdr.hwndFrom, (HTREEITEM)pnmtv->itemNew.hItem, pnmtv->itemNew.lParam);

			}

			return (FALSE); // return value is ignored
		}

	// The mouse has been clicked within the control.  We need to determine
	// if the click is over the state image and if so toggle the check box.
		case NM_CLICK:
		{
			UINT                    state;
			DWORD                   dwPos;
			TV_HITTESTINFO			tvhti;
			HTREEITEM               htiItemClicked;
			POINT                   point;
			HWND                    hwndTV = GetDlgItem(hwnd, IDC_TREEVIEW);
			TV_ITEM					tvi;
	
            // Find out where the cursor was
			dwPos = GetMessagePos();
			point.x = LOWORD(dwPos);
			point.y = HIWORD(dwPos);

			ScreenToClient(hwndTV, &point);

			tvhti.pt = point;
			htiItemClicked = TreeView_HitTest(hwndTV, &tvhti);

			// Now get the state information from the item and toggle it
			if (tvhti.flags & TVHT_ONITEMSTATEICON)
			{
				// Fill out the TV_ITEM struct to get the state image mask and
				// get the item from the control
				tvi.hItem = htiItemClicked;
				tvi.mask = TVIF_STATE;
				tvi.stateMask = TVIS_STATEIMAGEMASK;
				TreeView_GetItem(hwndTV, &tvi);

				// Now toggle the state
				state = tvi.state;
				tvi.state = (state & INDEXTOSTATEIMAGEMASK(TVIS_GCNOCHECK)) ?
						INDEXTOSTATEIMAGEMASK(TVIS_GCCHECK) :
							INDEXTOSTATEIMAGEMASK(TVIS_GCNOCHECK);

				// And finally set the new state of the item back into the
				// control
				TreeView_SetItem(hwndTV, &tvi);
			}

	    return (0L);    // Return value is ignored
		}
	}
	return (0L);
}
