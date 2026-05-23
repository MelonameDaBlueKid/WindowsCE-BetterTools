/*-------------------------------------------------------------------*\

(c) Copyright Microsoft Corp. 1997 All Rights Reserved

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module: Htmlview.cpp


Abstract: The Htmlview sample allows the user to browse and open HTML (.htp)
help files. This sample code demonstrates the notifications and
structures defined by Htmlctrl.h.
\*-------------------------------------------------------------------*/

#include <windows.h>
#include <windowsx.h>


#include <commctrl.h>
#include <commdlg.h>

extern "C" {
#include <htmlctrl.h>
}


#include <tchar.h>

#include "resource.h"

HINSTANCE hInst = NULL;  // Local copy of hInstance, used in Commandbar_Create & Commandbar_InsertMenubar
HWND hwndMain = NULL;    // Handle to Main window returned from CreateWindow
HWND hwndCB =NULL;       // Handle to a commandbar
HWND hwndHtml = NULL;    // Handle to Main window returned from CreateWindow

HWND    hCommandCombo;

#define  COMBOID   100
#define  HTMLID    200

#define WM_ADDIMAGE     WM_USER + 100                // send the inline image to the HTML control
#define WM_PLAYSOUND    WM_USER + 200                // send the inline image to the HTML control


#if defined (DEBUG)
    TCHAR   szDebug[500];
#endif

HANDLE  hHeap = NULL;

TCHAR szAppName[20] = TEXT("HTMLVIEW Sample");

TCHAR szTitle[20] =  TEXT("HTMLVIEW Sample");

TCHAR szHtmlChild[20] = TEXT("HTMLChild");

LPTSTR      pCurrentDirectory = NULL;

TCHAR * WINAPI    OpenBrowseFile(HWND hOwner);
void WINAPI LoadBrowseFile(LPTSTR pszBrowsFile);

/**************************************************************************************

   MainWndProc

  *************************************************************************************/


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    LRESULT	lResult = TRUE;

	switch(msg)
	{

	case WM_CREATE:
		{
            int     nHeight;
			int		nWidth;
			HDC     hdc;
            RECT    rect;

			hdc = GetDC(hwnd);
			nWidth = (int)(GetDeviceCaps(hdc, HORZRES) * 0.85);
			ReleaseDC(hwnd, hdc);

            GetClientRect(hwnd, &rect);
		    hwndCB = CommandBar_Create(hInst, hwnd, 1);

		    CommandBar_InsertMenubar(hwndCB, hInst, IDR_MAINMENU, 0);

            nHeight = CommandBar_Height(hwndCB);
            hCommandCombo = CommandBar_InsertComboBox(	hwndCB, hInst, nWidth,
				CBS_DROPDOWNLIST | WS_VSCROLL,COMBOID,1 );

		    CommandBar_AddAdornments(hwndCB, 0, 0);    // Add exit button

		    hwndHtml = CreateWindow(DISPLAYCLASS,NULL,WS_CHILD | WS_VISIBLE | WS_BORDER,
			        0, nHeight, rect.right-rect.left, rect.bottom- (rect.top+nHeight), hwnd,
			        (HMENU)HTMLID, hInst,NULL);

            if ( hwndHtml )
            {
	            ShowWindow(hwndHtml, SW_SHOW);
                UpdateWindow(hwndHtml);
            }

        break;
		}		
	case WM_NOTIFY:
    {
		if (wp == HTMLID)
        {

            NM_HTMLVIEW * pnmHTML = (NM_HTMLVIEW *) lp;
            LPNMHDR pnmh = (LPNMHDR) &(pnmHTML->hdr);

            switch(pnmh->code)
            {
				// User tapped on a link or submitted a form
                case NM_HOTSPOT:
                {
                    LPSTR   lpFileName;
                    LPTSTR  lpFileBuf;
                    #if defined (DEBUG)
                        wsprintf(szDebug, TEXT("NM_HOTSPOT:: Target: %S\nData: %S\r\n"),
                            (pnmHTML->szTarget?pnmHTML->szTarget:"NULL"),
                            (pnmHTML->szData?pnmHTML->szData:"NULL"));
                        OutputDebugString(szDebug);
                    #endif

                    if ( pnmHTML->szTarget )
                    {
						//jump
                        lpFileName = pnmHTML->szTarget;
						{
						LPSTR	lpTemp = strchr(lpFileName, ':'); // skip 'file' keyword
						if ( lpTemp ) lpFileName = lpTemp + 1; // skip
						}

                        lpFileBuf = (LPTSTR) HeapAlloc(hHeap, HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,
                                    (strlen(lpFileName) + lstrlen(pCurrentDirectory) + 1) * sizeof(TCHAR));
                        if ( lpFileBuf )
                        {
                            wsprintf(lpFileBuf, TEXT("%s%S"), pCurrentDirectory, lpFileName);
                            LoadBrowseFile(lpFileBuf);
                            HeapFree(hHeap, HEAP_NO_SERIALIZE, lpFileBuf);
                        }
                    }
                    break;
                }
				// Notify the application to load the image
                case NM_INLINE_IMAGE:
                {
                    LPSTR         lpImageFile;

                    #if defined (DEBUG)
                        wsprintf(szDebug, TEXT("NM_INLINE_IMAGE:: Target: %S\nCookie: %ld\r\n"),
                            (pnmHTML->szTarget?pnmHTML->szTarget:"NULL"), pnmHTML->dwCookie);
                        OutputDebugString(szDebug);
                    #endif

                    lpImageFile = (LPSTR)HeapAlloc(hHeap, HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,
                                                strlen(pnmHTML->szTarget) + 1);

                    if ( lpImageFile )
                    {
                        strcpy(lpImageFile, pnmHTML->szTarget);
                        PostMessage(hwnd, WM_ADDIMAGE, pnmHTML->dwCookie , (LPARAM) lpImageFile);
                    }
                    else
                        SendMessage(hwndHtml, DTM_IMAGEFAIL, 0, (LPARAM) pnmHTML->dwCookie);

                    break;
                }
				// notify the application to load the sound
                case NM_INLINE_SOUND:
                {
                    LPSTR         lpImageFile;

                    #if defined (DEBUG)
                        wsprintf(szDebug, TEXT("NM_INLINE_IMAGE:: Target: %S\nCookie: %ld\r\n"),
                            (pnmHTML->szTarget?pnmHTML->szTarget:"NULL"), pnmHTML->dwCookie);
                        OutputDebugString(szDebug);
                    #endif

                    lpImageFile = (LPSTR)HeapAlloc(hHeap, HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY, strlen(pnmHTML->szTarget) + 1);

                    if ( lpImageFile )
                    {
                        strcpy(lpImageFile, pnmHTML->szTarget);
                        PostMessage(hwnd, WM_PLAYSOUND, pnmHTML->dwCookie , (LPARAM) lpImageFile);

                    }

                    break;
                }
				// Contains the HTTP-EQUIV and CONTENT parameters of the META tag
                case NM_META:
                    #if defined (DEBUG)
                        wsprintf(szDebug, TEXT("NM_META:: Target: %S\nData: %S\r\n"),
                            (pnmHTML->szTarget?pnmHTML->szTarget:"NULL"),
                            (pnmHTML->szData?pnmHTML->szData:"NULL"));
                        OutputDebugString(szDebug);
                    #endif
                    break;
                // Contains the title of the HTML document
                case NM_TITLE:
                    #if defined (DEBUG)
                        wsprintf(szDebug, TEXT("NM_TITLE:: Target: %S\r\n"), (pnmHTML->szTarget?pnmHTML->szTarget:"NULL"));
                        OutputDebugString(szDebug);
                    #endif
                    break;

            }

        }
        break;
    }
    case WM_PLAYSOUND:
    {
        LPTSTR  lpTarget;
        DWORD   dwCount;

        LPSTR  lpImageFile = (LPSTR) lp;

        if ( lp )
        {
            lpTarget = (LPTSTR)HeapAlloc(hHeap, HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY, (strlen(lpImageFile) + lstrlen(pCurrentDirectory) + 1) * sizeof(TCHAR));

            if ( lpTarget )
            {
				{
				LPSTR	lpTemp = strchr(lpImageFile, ':'); // skip 'file' keyword
				if ( lpTemp ) lpImageFile = lpTemp + 1; // skip
				}
                wsprintf(lpTarget, TEXT("%s%S"), pCurrentDirectory, lpImageFile);

                for ( dwCount = 0 ; dwCount < wp; dwCount++)
                    sndPlaySound(lpTarget, SND_FILENAME|SND_ASYNC);

                HeapFree(hHeap, HEAP_NO_SERIALIZE, lpTarget);
            }

            HeapFree(hHeap, HEAP_NO_SERIALIZE, (LPVOID)lp);
        }
        break;

    }
    case WM_ADDIMAGE:
    {
        HBITMAP             hBitMap;
        LPTSTR              lpTarget;
        TCHAR               szError[100];
        BITMAP              BitMapInfo;
        INLINEIMAGEINFO     WebImage;
        LPSTR               lpImageFile = (LPSTR) lp;

        if ( lp )
        {
            lpTarget = (LPTSTR)HeapAlloc(hHeap, HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY, (strlen(lpImageFile) + lstrlen(pCurrentDirectory) + 1) * sizeof(TCHAR));

            if ( lpTarget )
            {
				{
				LPSTR	lpTemp = strchr(lpImageFile, ':'); // skip 'file' keyword
				if ( lpTemp ) lpImageFile = lpTemp + 1; // skip
				}
                wsprintf(lpTarget, TEXT("%s%S"), pCurrentDirectory, lpImageFile);
                hBitMap = SHLoadDIBitmap(lpTarget);
                if ( hBitMap )
                {
                    GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);
                    WebImage.dwCookie = wp;  // pass back to DTM_SETIMAGE
                    WebImage.bOwnBitmap = TRUE; // control to destroy object;
	                WebImage.iOrigHeight = BitMapInfo.bmHeight;
	                WebImage.iOrigWidth = BitMapInfo.bmWidth;
	                WebImage.hbm = hBitMap;

                    SendMessage(hwndHtml, DTM_SETIMAGE, 0, (LPARAM) &WebImage);
                }
                else
                {
                    wsprintf(szError, TEXT("Failed to load Image %s, error %ld"), lpTarget, GetLastError());
                    MessageBox(hwnd, szError, TEXT("Load Image"), MB_OK|MB_SETFOREGROUND);
                    SendMessage(hwndHtml, DTM_IMAGEFAIL, 0, (LPARAM) wp);
                }

                HeapFree(hHeap, HEAP_NO_SERIALIZE, lpTarget);
            }
            else
                SendMessage(hwndHtml, DTM_IMAGEFAIL, 0, (LPARAM) wp);

            HeapFree(hHeap, HEAP_NO_SERIALIZE, (LPVOID) lp);
        }

    }
    break;

	case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp))
			{
				
				case IDM_FILE_EXIT:
					SendMessage(hwnd, WM_CLOSE, 0, 0);
					break;

                case IDM_FILE_BROWSE:
                {
                    LPTSTR pszBrowsFile;
                    pszBrowsFile = OpenBrowseFile(hwnd);
                    if( pszBrowsFile )
                    {
                        LoadBrowseFile(pszBrowsFile);
                        HeapFree(hHeap, HEAP_NO_SERIALIZE , pszBrowsFile);
                    }
                    break;
                }
                case COMBOID:
                {
                    if( HIWORD(wp) == CBN_SELENDOK)
                    {
                        LRESULT  lIndex;

                        lIndex = SendMessage(hCommandCombo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                        if ( lIndex != CB_ERR )
                        {
                            LRESULT lLength;

                            lLength = SendMessage(hCommandCombo, CB_GETLBTEXTLEN, lIndex, (LPARAM) 0);
                            if ( lLength != CB_ERR && lLength)
                            {
                                LPTSTR  lpFileName;

                                lpFileName = (LPTSTR)HeapAlloc(hHeap, HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY, (lLength + 1 ) * sizeof(TCHAR));
                                if ( lpFileName )
                                {
                                    if ( CB_ERR != SendMessage(hCommandCombo, CB_GETLBTEXT, lIndex, (LPARAM) (LPCSTR)lpFileName ) )
                                        LoadBrowseFile(lpFileName);

                                    HeapFree(hHeap, HEAP_NO_SERIALIZE , lpFileName);

                                }
                            }

                        }

                    }
                    break;
                }

				default:
					return DefWindowProc(hwnd, msg, wp, lp);
			}
			break;
	
	case WM_CLOSE:
		CommandBar_Destroy(hwndCB);
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
        HeapDestroy(hHeap);
        //Clear control of current file
        SetWindowText(hwndHtml, TEXT(""));              // erase the text that is currently in the control
		PostQuitMessage(0);
		break;

	default:
		lResult = DefWindowProc(hwnd, msg, wp, lp);
		break;
	}
	return (lResult);
}


/******************************************************************************************************

  InitInstance

*********************************************************************************************************/

BOOL InitInstance (HINSTANCE hInstance, int CmdShow )
{

	hInst = hInstance;

	hwndMain = CreateWindow(szAppName,						// If target is not NT, create a default size
                			szTitle,                        // window
						    WS_VISIBLE,
							0,0,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL );

	if ( !hwndMain )
		
	{
		return FALSE;
	}

	ShowWindow(hwndMain, CmdShow );

	UpdateWindow(hwndMain);

    hHeap = HeapCreate(HEAP_NO_SERIALIZE, 1024, 0);
    if ( !hHeap )
        return FALSE;

	return TRUE;
}

/****************************************************************************************************

   InitApplication

  **************************************************************************************************/

BOOL InitApplication ( HINSTANCE hInstance )
{
	WNDCLASS wc;
	BOOL f;

	wc.style = 0;//CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = NULL;                                              // No cursor if target is not NT
	wc.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	
	f = (RegisterClass(&wc));

    InitHTMLControl(hInstance);
    InitCommonControls();

    return f;
}


/*************************************************************************************************

  WinMain

  ***********************************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                     LPWSTR     lpCmdLine,                           // If target not NT lpCmdLine is of type
                     int        CmdShow)

{
	MSG msg;

	if ( !hPrevInstance )
	{
		if ( !InitApplication ( hInstance ) )

		{ return (FALSE); }

	}

	if ( !InitInstance( hInstance, CmdShow )  )
		return (FALSE);

    while ( GetMessage( &msg, NULL, 0,0 ) )
	{
		TranslateMessage (&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

TCHAR * WINAPI   OpenBrowseFile(HWND hOwner)
{

    BOOL            bSuccess = FALSE;
    TCHAR           szFileName[MAX_PATH] = {0}, szPathName[MAX_PATH] = TEXT("\\windows"), szExtName[100] = {0};
    OPENFILENAME    of;
    TCHAR           szOpen[50] = TEXT("Open");
    LPTSTR          pFileName, pTemp;

    const LPTSTR pszOpenFilter      = TEXT("Browser Files(*.htm;*.htc;*.htp)\0*.htm;*.htc;*.htp\0All Documents (*.*)\0*.*\0\0");

    memset((LPVOID)&of, 0, sizeof(OPENFILENAME));
    of.lStructSize	    = sizeof(OPENFILENAME);
    of.hwndOwner	    = hOwner;
    of.lpstrFile	    = szFileName;
    of.lpstrInitialDir  = NULL;
    of.nMaxFile		    = sizeof(szFileName)/sizeof(TCHAR);

    of.lpstrDefExt  = szExtName;
    of.Flags = OFN_HIDEREADONLY |  // Do not display the Read-Only check box.
               OFN_LONGNAMES;      // Display long filenames if possible.

    of.lpfnHook = NULL;
    of.Flags        |= OFN_FILEMUSTEXIST;
    of.lpstrTitle   = szOpen;
    of.lpstrFilter	= pszOpenFilter;
    bSuccess = GetOpenFileName(&of);

    if( bSuccess )
    {
        if ( pTemp = _tcsrchr(szFileName, TEXT('\\')) )
		{
			pCurrentDirectory = (LPTSTR)HeapAlloc(
									hHeap,
									HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,
									(lstrlen(szFileName) +1) * sizeof(TCHAR)
									);
			if ( pCurrentDirectory )
				_tcsncpy(pCurrentDirectory, szFileName, (pTemp - szFileName)+1);
		}

        pFileName = (LPTSTR) HeapAlloc(
									hHeap,
									HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,
									(lstrlen(szFileName) +1) * sizeof(TCHAR)
									);

        if ( pFileName )
        {
            _tcscpy(pFileName, szFileName);
        }
        else
        {
            if ( pFileName )
            {
                HeapFree(hHeap, HEAP_NO_SERIALIZE, pFileName);
                pFileName = NULL;
            }
            if ( pCurrentDirectory)
            {
                HeapFree(hHeap, HEAP_NO_SERIALIZE, pCurrentDirectory);
                pCurrentDirectory = NULL;
            }
            return FALSE;
        }

        return pFileName;
    }
    else
        return NULL;

}

void WINAPI LoadBrowseFile(LPTSTR pszBrowsFile)
{
    HANDLE hFile;
    BYTE    szBuffer[1025] = {0};
    DWORD   dwNumberOfBytesRead;

    // massage file name.. we are not supporting html "anchors" or "query strings"
    TCHAR * pChar = NULL;
    pChar = wcspbrk( pszBrowsFile, TEXT("#?"));
    if(pChar !=NULL)
    {
        *pChar = '\0';  // truncate the filename to get rid of the part we don't want
    }

    hFile = CreateFile(	pszBrowsFile, GENERIC_READ ,FILE_SHARE_READ,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL );
    if ( hFile )
    {
        //Clear control of current file
        SetWindowText(hwndHtml, TEXT(""));              // erase the text that is currently in the control
        while ( ReadFile( hFile,szBuffer,1024,&dwNumberOfBytesRead,NULL) )
        {
            if ( dwNumberOfBytesRead )
                SendMessage(hwndHtml, DTM_ADDTEXT, FALSE, (LPARAM)szBuffer);
            else
                break;
            memset(szBuffer, 0, 1025);
        }
        if ( GetLastError() != ERROR_SUCCESS)
        {
            ;///real error
        }
        SendMessage(hwndHtml, DTM_ENDOFSOURCE, 0, (LPARAM)NULL);
        CloseHandle(hFile);

        if ( CB_ERR == SendMessage(hCommandCombo, CB_SELECTSTRING, (WPARAM)-1, (LPARAM) (LPCTSTR) pszBrowsFile) )
        {
            SendMessage(hCommandCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) pszBrowsFile);
            SendMessage(hCommandCombo, CB_SELECTSTRING, (WPARAM)-1, (LPARAM) (LPCTSTR) pszBrowsFile);
        }
    }
    else
    {
        TCHAR szError[256];

        wsprintf(szError, TEXT("Failed to load file %s, error %ld"), pszBrowsFile, GetLastError());
        MessageBox(hwndHtml, szError, TEXT("Load File"), MB_OK|MB_SETFOREGROUND);    
    }


}
