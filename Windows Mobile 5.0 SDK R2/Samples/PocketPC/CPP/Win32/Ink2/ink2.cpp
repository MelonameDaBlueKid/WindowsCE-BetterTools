//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
/*-------------------------------------------------------------------*\
Module: ink2.cpp

    
        Abstract: The ink2 sample 
        
            The code to note is prefaced by the comment tag: //RICHINK: 
            Step 1. Load the DLL
            Step 2. Create the ink window
            Step 3. Write the Callback functions
            Step 4. Stream the data 
            
\*-------------------------------------------------------------------*/

#include "ink2.h"
//------------------------------------------------------
// Globals
//------------------------------------------------------

HINSTANCE g_hInst = NULL;  // Local copy of hInstance, used in Commandbar_Create & Commandbar_InsertMenubar
HWND      g_hwndMain = NULL;    // Handle to Main window returned from CreateWindow
HMENU           g_hMenu =NULL;       // Handle to a commandbar0 menu
HWND            g_hwndChild = NULL;    // Handle to Main window returned from CreateWindow

HWND            g_hCommandCombo = NULL;
UINT            g_nCBrHeight = 0;
int             g_nMenuHeight;

#if defined (_DEBUG)
TCHAR   szDebug[500];
LRESULT iDebugRET;
#endif

TCHAR szAppName[] = TEXT("ink2 Application");
TCHAR szTitle[]   = TEXT("ink2");

HBITMAP hbmTransUpUp,hbmTransUpDown;
HBITMAP hbmTransDownUp,hbmTransDownDown;
//------------------------------------------------------
// Forward Declares
//------------------------------------------------------

BOOL CALLBACK  BasicDlgProc(HWND, WORD, WORD, LONG);

void TranslateUP(HWND);
void TranslateDOWN(HWND);
static DWORD CALLBACK EditStreamReadCallback(DWORD , LPBYTE , LONG , LONG *);
static DWORD CALLBACK EditStreamWriteCallback(DWORD , LPBYTE , LONG , LONG *);

//------------------------------------------------------
// Local Functions
//------------------------------------------------------

//------------------------------------------------------
//   MainWndProc
//------------------------------------------------------
void ResizeMainWindow(HWND hwnd)
{
    RECT rect;

    //Get all workspace the client can use
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, FALSE);

    SIPINFO si = {0};
    si.cbSize = sizeof(si);
    SHSipInfo(SPI_GETSIPINFO, 0, &si, 0);

    //Change rect to be left/top/width/height
    rect.right = rect.right - rect.left;
    rect.bottom = rect.bottom - rect.top - g_nMenuHeight;

    if (SIPF_ON == (si.fdwFlags & SIPF_ON))
    {
        //SIP is shown, make space for it on bottom of screen
        rect.bottom = rect.bottom - (si.rcSipRect.bottom - si.rcSipRect.top);
    }

    //Move main window
    MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, FALSE);


    //Moving a child window, X & Y relative to parent window
    MoveWindow(g_hwndChild, 0, 0, rect.right, rect.bottom, FALSE);
    //Update after moving - CE MoveWindow assumes bRepaint of MoveWindow is always false
    UpdateWindow(g_hwndChild);
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    LRESULT lResult = TRUE;
    TCHAR szbuffer[_MAX_PATH] = TEXT(" ");
    
    switch(msg)
    {
        
    case WM_CREATE:
        {
            
            //Create a MenuBar
            SHMENUBARINFO mbi;
            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hwnd;
            mbi.nToolBarId = IDM_MAIN_MENU;
            mbi.hInstRes   = g_hInst;
            mbi.nBmpId     = 0;
            mbi.cBmpImages = 0; 
            
            if (FALSE == SHCreateMenuBar(&mbi))
            {
                MessageBox(hwnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
            }

            RECT rect;
            //Set menu height
            GetWindowRect(mbi.hwndMB, &rect);
            g_nMenuHeight = rect.bottom - rect.top;

            g_hwndChild =CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_PALMDIALOG), hwnd, (DLGPROC)BasicDlgProc); 
            
            if (NULL != g_hwndChild)
            {
                ResizeMainWindow(hwnd);
            }
        }
        break;
        
    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wp,lp))
        { 
            
        case IDM_FILE_RESET:
            //Clear data from richtext and force a repaint
            SendMessage(GetDlgItem(g_hwndChild, ID_RICHINKCTL), EM_CLEARALL,(WPARAM) (BOOL) TRUE, 0);
            
            //Clear the edit control window
            SetWindowText(GetDlgItem(g_hwndChild, ID_EDITCTL), _T(""));
            
            break;
            
        case IDM_FILE_EXIT:
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
            
        }
        break; //WM_COMMAND
    case WM_SETTINGCHANGE:
        if ((SETTINGCHANGE_RESET == wp) ||
            (SPI_SETSIPINFO == wp))
        {
            //Orientation change
            ResizeMainWindow(hwnd);
        }
        break;
        
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break; //WM_CLOSE
        
    case WM_DESTROY:
        PostQuitMessage(0);
        break; //WM_DESTROY
        
    default:
        lResult = DefWindowProc(hwnd, msg, wp, lp);
        break;
    }
    return (lResult);
}

//------------------------------------------------------
//  InitInstance
//------------------------------------------------------


BOOL InitInstance (HINSTANCE hInstance, int CmdShow )
{
    g_hInst = hInstance;
    ////////// Setting default main window size
    // This technique allows for you to create the main
    // window to allow for the postion of a menubar and/or
    // the SIP button at the bottom of the screen
    
    g_hwndMain = CreateWindow(szAppName, szTitle, WS_VISIBLE ,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    
    
    if ( !g_hwndMain )      
    {
        return FALSE;
    }
    
    ShowWindow(g_hwndMain, CmdShow );
    UpdateWindow(g_hwndMain);
    
    return TRUE;
}

//------------------------------------------------------
//   InitApplication
//------------------------------------------------------


BOOL InitApplication ( HINSTANCE hInstance )
{
    WNDCLASS wc;
    BOOL f;
    
    //Call InitCommonControls to load the common control dynamics-link library (DLL). 
  InitCommonControls();
    //Call InitCommonControls to load the common control dynamics-link library (DLL). 
    InitCommonControls();
    //RICHINK: Step 1. load the RichInk DLL:
    // Use this technique for older platforms if necessary
    //HINSTANCE hLib;
    //hLib = LoadLibrary( TEXT("richink.dll" ) );
    //if (!hLib)
    //  return ERROR;
    InitRichInkDLL();
    //RICHINK:
    
    wc.style = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hInstance = hInstance;
    wc.hCursor = NULL;                                              
    wc.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;
    
    f = (RegisterClass(&wc));
    
    return f;
}

//------------------------------------------------------
//  WinMain
//------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int CmdShow)
{
    MSG msg;
    HWND hThisWnd = NULL;
    //Check to see if app is running then pop to foreground
    hThisWnd = FindWindow(szAppName, szTitle);  
    if (hThisWnd) 
    {
        SetForegroundWindow (hThisWnd);    
        return 0;
    }
    if ( !hPrevInstance )
    {
        if ( !InitApplication ( hInstance ) )
        { 
            return (FALSE); 
        }
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

//------------------------------------------------------
// BasicDlgProc(HWND, WORD, WORD, LONG)
//------------------------------------------------------
BOOL CALLBACK BasicDlgProc(HWND hwnd, WORD msg, WORD wp, LONG lp)
{  
    LRESULT lResult = TRUE;
    //For owner draw button
    HDC hdcMem; 
    LPDRAWITEMSTRUCT lpdis;
    HBITMAP hbmOld;
    
    switch(msg)
    {
    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wp,lp))
        {
        case  IDC_BUT_TRANSUP:
            TranslateUP(hwnd);
            break;
            
        case  IDC_BUT_TRANSDOWN:
            TranslateDOWN(hwnd);
            break;
        }
        break;
        
        case WM_DRAWITEM: 
            lpdis = (LPDRAWITEMSTRUCT) lp;
            hdcMem = CreateCompatibleDC((HDC)lpdis->hDC);
            if ((lpdis->itemState & ODS_SELECTED) && wp == IDC_BUT_TRANSUP)
                hbmOld = SelectBitmap(hdcMem, hbmTransUpDown);             
            else if (!(lpdis->itemState & ODS_SELECTED) && wp == IDC_BUT_TRANSUP)
                hbmOld = SelectBitmap(hdcMem, hbmTransUpUp);
            if ((lpdis->itemState & ODS_SELECTED) && wp == IDC_BUT_TRANSDOWN)
                hbmOld = SelectBitmap(hdcMem, hbmTransDownDown);             
            else if (!(lpdis->itemState & ODS_SELECTED) && wp == IDC_BUT_TRANSDOWN)
                hbmOld = SelectBitmap(hdcMem, hbmTransDownUp);
            if (hbmOld == NULL)
                break;     // destructors will clean up
            lResult = StretchBlt(
                lpdis->hDC,         // destination DC 
                lpdis->rcItem.left, // x upper left 
                lpdis->rcItem.top,  // y upper left  
                lpdis->rcItem.right - lpdis->rcItem.left, 
                lpdis->rcItem.bottom - lpdis->rcItem.top, 
                hdcMem,    // source device context 
                0, 0,      // x and y upper left 
                20,        // source bitmap width 
                20,        // source bitmap height 
                SRCCOPY);  // raster operation
            DeleteDC(hdcMem); 
            break;          
            
        case WM_INITDIALOG:
            {
                //Set initial RTF mode:
                Button_SetCheck(GetDlgItem(hwnd,IDC_RADIO_RTF) , BST_CHECKED); //A macro from windowsx.h
                //Load up owner draw button bitmaps
                hbmTransUpUp = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BITMAP_TRANSUPUP)); 
                hbmTransUpDown = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BITMAP_TRANSUPDOWN)); 
                hbmTransDownUp = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BITMAP_TRANSDOWNUP)); 
                hbmTransDownDown = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BITMAP_TRANSDOWNDOWN)); 
            }
            break;
            
        case WM_CLOSE:
            DeleteObject(hbmTransUpUp); 
            DeleteObject(hbmTransUpDown);
            DeleteObject(hbmTransDownUp);
            DeleteObject(hbmTransDownDown);
            break;
        case WM_MOVE:
            //move all child controls
            {
                RECT rect;
                HWND hWndControl;
                int nBottom;
                int nWidth;
                int nTop;

                GetWindowRect(hwnd, &rect);

                //Move the labels
                nTop = LAYOUT_BUFFER;
                hWndControl = GetDlgItem(hwnd, IDC_LABEL_RICHINK);
                MoveWindow(hWndControl, LAYOUT_BUFFER, nTop, 
                    ((rect.right - rect.left - 2 * LAYOUT_BUFFER)/2), EDIT_HEIGHT, FALSE);
                hWndControl = GetDlgItem(hwnd, IDC_LABEL_EDIT);
                MoveWindow(hWndControl, ((rect.right - rect.left)/2) + LAYOUT_BUFFER, nTop,
                    ((rect.right - rect.left - 2 * LAYOUT_BUFFER)/2), EDIT_HEIGHT, FALSE);

                //Move the Radio buttons
                nBottom = rect.bottom - rect.top - (2 * LAYOUT_BUFFER) - RADIO_BUTTOM_SIZE;
                nWidth = ((rect.right - rect.left - 4 * LAYOUT_BUFFER)/3);

                hWndControl = GetDlgItem(hwnd, IDC_RADIO_RTF);
                MoveWindow(hWndControl, LAYOUT_BUFFER, nBottom, 
                    nWidth, RADIO_BUTTOM_SIZE, FALSE);
                hWndControl = GetDlgItem(hwnd, IDC_RADIO_TXT);
                MoveWindow(hWndControl, (2 * LAYOUT_BUFFER) + nWidth, nBottom, 
                    nWidth, RADIO_BUTTOM_SIZE, FALSE);
                hWndControl = GetDlgItem(hwnd, IDC_RADIO_UNI);
                MoveWindow(hWndControl, (3 * LAYOUT_BUFFER) + (2 * nWidth), nBottom, 
                    nWidth, RADIO_BUTTOM_SIZE, FALSE);

                //Move the translation buttoms
                nBottom = nBottom - LAYOUT_BUFFER - BUTTON_SIZE;

                hWndControl = GetDlgItem(hwnd, IDC_BUT_TRANSUP);
                MoveWindow(hWndControl, ((rect.right - rect.left)/4) - (BUTTON_SIZE/2),
                    nBottom, BUTTON_SIZE, BUTTON_SIZE, FALSE);
                hWndControl = GetDlgItem(hwnd, IDC_BUT_TRANSDOWN);
                MoveWindow(hWndControl, (3*((rect.right - rect.left)/4)) - (BUTTON_SIZE/2),
                    nBottom, BUTTON_SIZE, BUTTON_SIZE, FALSE);

                //Move the RichInk and Edit controls
                nBottom = nBottom - LAYOUT_BUFFER;
                nTop = nTop + LAYOUT_BUFFER + EDIT_HEIGHT;

                hWndControl = GetDlgItem(hwnd, ID_RICHINKCTL);
                MoveWindow(hWndControl, LAYOUT_BUFFER, nTop, 
                    ((rect.right - rect.left - 3 * LAYOUT_BUFFER)/2),
                    nBottom - nTop, FALSE);
                hWndControl = GetDlgItem(hwnd, ID_EDITCTL);
                MoveWindow(hWndControl, ((rect.right - rect.left)/2) + LAYOUT_BUFFER,
                    nTop, ((rect.right - rect.left - 3 * LAYOUT_BUFFER)/2),
                    nBottom - nTop, FALSE);

            }
            break;
            
        default:
            //return DefWindowProc(hwnd, msg, wp, lp);
            return(FALSE);
            break;
    }
    
  UNREFERENCED_PARAMETER(wp);
  UNREFERENCED_PARAMETER(lp);
    return (lResult);
}

//------------------------------------------------------
// RICHINK: Step 4. Translation functions
//------------------------------------------------------
//------------------------------------------------------
// RICHINK: TranslateUP
//------------------------------------------------------
void TranslateUP(HWND hwnd)
{
    EDITSTREAM  myEditStream;
    COOKIE      myCookie;
    LPBYTE      pb = NULL;
    long            cb = 0, cbSz = 0;
    DWORD   lResult = 0;
    LPSTR   sz = _T('\0');
    LPWSTR  szW = _T('\0');
    
    HWND hwndRickInk, hwndEdit;
    DWORD dwSF, dwTextLen;
    
    hwndRickInk = GetDlgItem(hwnd,ID_RICHINKCTL); 
    hwndEdit = GetDlgItem(hwnd,ID_EDITCTL);
    
    dwTextLen = Edit_GetTextLength(hwndEdit);  
    
    //if nothing to translate then show that and return
    if (dwTextLen == 0) {
        MessageBox(hwnd, _T("Nothing in the edit control"), _T("Error"), MB_OK);\
        return;
        }

    szW = (LPWSTR)LocalAlloc(LPTR, (dwTextLen + 1) * sizeof(TCHAR)); //Add 1 for the NULL 
    sz = (LPSTR)LocalAlloc(LPTR, dwTextLen + 1); //Add 1 for the NULL 
    Edit_GetText(hwndEdit, szW, dwTextLen + 1); //Add 1 for the NULL

    //
    // Stream formats:
    //
    //#define SF_TEXT         0x0001
    //#define SF_RTF          0x0002

    //#define SF_UNICODE      0x0010                          // Unicode data of some kind
    //#define SF_UTEXT        (SF_TEXT | SF_UNICODE)            // Unicode text file

    //#define SFF_PWI         0x0800      
    //#define SF_PWI          ( SF_RTF | SFF_PWI | 0x010000 ) // Pocket Word Ink (PWI) format
    
    //Translate from 'type'
    //SF_RTF
    if (Button_GetCheck(GetDlgItem(hwnd,IDC_RADIO_RTF))) {
        dwSF = SF_RTF;
        wcstombs(sz, szW,dwTextLen);
        pb = (LPBYTE)sz;
        cb = strlen(sz) + 1;
        }
    //SF_TEXT
    if (Button_GetCheck(GetDlgItem(hwnd,IDC_RADIO_TXT))) {
        dwSF = SF_TEXT;
        wcstombs(sz, szW,dwTextLen);
        pb = (LPBYTE)sz;
        cb = strlen(sz) + 1;
        }
    //SF_UTEXT
    if (Button_GetCheck(GetDlgItem(hwnd,IDC_RADIO_UNI))) {
        dwSF = SF_UTEXT;
        pb = (LPBYTE)szW;
        cb = lstrlen(szW) * sizeof(TCHAR);
        }
    

    // Stream in the Ink Data from a memory block.
    memset(&myCookie, 0, sizeof(myCookie));
    myCookie.dwError            = 0;
    myCookie.pbStart            = (LPBYTE)pb;       // Pointer to memory block
    myCookie.pbCur              = myCookie.pbStart;
    myCookie.bCount                     = cb;           // Size of ink data
    
    memset(&myEditStream, 0, sizeof(myEditStream));
    myEditStream.dwCookie     = (DWORD)&myCookie;
    myEditStream.dwError      = 0;
    myEditStream.pfnCallback  = EditStreamReadCallback;

    
    //---------------------------------------------------------
// IMPORTANT COMPATIBILITY NOTE:
//
//  Previous versions of the richink.dll required the EM_STREAMIN
//  and EM_STREAMOUT messages to pass a pointer to the parameter 
//  which specifies the format type rather than passing the format
//  type directly.  Here is an example:
//
//  DWORD   wpSF = SF_PWI;
//
//  SendMessage (hwndInk, EM_STREAMIN, (WPARAM)&wpSF, (LPARAM)&es);
//
//  So it would look like this for early versions of richink:
//
//  lResult = SendMessage (hwndRickInk, EM_STREAMIN, (WPARAM)&dwSFPWI, (LPARAM)&myEditStream);
//---------------------------------------------------------

    lResult = SendMessage (hwndRickInk, EM_STREAMIN, (WPARAM)dwSF, (LPARAM)&myEditStream);
    
    if (szW) LocalFree((HLOCAL)szW);
    if (sz) LocalFree((HLOCAL)sz);
    return;
}
//------------------------------------------------------
// RICHINK: TranslateDOWN
//------------------------------------------------------
void TranslateDOWN(HWND hwnd)
{
    EDITSTREAM  myEditStream;
    COOKIE      myCookie;
    LPBYTE      pb = NULL;
    long            cb = 0, cbSz = 0;
    DWORD   lResult = 0;
    LPWSTR  sz = _T('\0');
    LPWSTR  szW = _T('\0');
    
    HWND hwndRickInk = NULL;
    DWORD dwTransType;
    
    hwndRickInk = GetDlgItem(hwnd,ID_RICHINKCTL); 
    
    //Translate to 'type'
    //SF_RTF
    if (Button_GetCheck(GetDlgItem(hwnd,IDC_RADIO_RTF))) 
        dwTransType = SF_RTF;
    //SF_TEXT
    if (Button_GetCheck(GetDlgItem(hwnd,IDC_RADIO_TXT))) 
        dwTransType = SF_TEXT;
    //SF_UTEXT
    if (Button_GetCheck(GetDlgItem(hwnd,IDC_RADIO_UNI))) 
        dwTransType = SF_UTEXT;
    
    // Clear structs.
    memset(&myCookie, 0, sizeof(myCookie));
    memset(&myEditStream, 0, sizeof(myEditStream));
    
    // Stream out to get the size of the output text.
    // This basically allows us to determine how much space to allocate
    // for the real stream out
    
    myCookie.dwError            = 0;
    myCookie.pbStart            = 0;
    myCookie.pbCur              = 0;
    myCookie.bCount                     = 0;
    myEditStream.dwCookie     = (DWORD)&myCookie;
    myEditStream.dwError      = 0;
    myEditStream.pfnCallback  = EditStreamWriteCallback;

//---------------------------------------------------------
// IMPORTANT COMPATIBILITY NOTE:
//
//  Previous versions of the richink.dll required the EM_STREAMIN
//  and EM_STREAMOUT messages to pass a pointer to the parameter 
//  which specifies the format type rather than passing the format
//  type directly.  Here is an example:
//
//  DWORD   wpSF = SF_PWI;
//
//  SendMessage (hwndInk, EM_STREAMOUT, (WPARAM)&wpSF, (LPARAM)&es);
//
//  So it would look like this for early versions of richink:
//
//  lResult = SendMessage (hwndRickInk, EM_STREAMOUT, (WPARAM)&dwTransType, (LPARAM)&myEditStream);
//---------------------------------------------------------

    lResult = SendMessage (hwndRickInk, EM_STREAMOUT, (WPARAM)dwTransType, (LPARAM)&myEditStream);
    
    //Clear the edit control window
    SetWindowText(GetDlgItem(g_hwndChild, ID_EDITCTL), _T(""));

    // Allocate memory and stream out the output text to it.  
    sz = (LPTSTR)LocalAlloc(LPTR, (cbSz = myCookie.pbCur - myCookie.pbStart) + 32);
    // Check for alloc err.
    if (!sz) return;
    
    myCookie.dwError                    = 0;
    myCookie.pbStart                    = (LPBYTE)sz;
    myCookie.pbCur                      = myCookie.pbStart;
    myCookie.bCount                     = cbSz;
    myEditStream.dwCookie     = (DWORD)&myCookie;
    myEditStream.dwError      = 0;
    myEditStream.pfnCallback  = EditStreamWriteCallback;
    lResult = SendMessage (hwndRickInk, EM_STREAMOUT, (WPARAM)dwTransType, (LPARAM)&myEditStream);
    
    // Set the text to the edit control
    if ((dwTransType == SF_RTF) || (dwTransType == SF_TEXT) )
    {
        szW = (LPWSTR)LocalAlloc(LPTR, (strlen((LPSTR)sz) + 32) * sizeof(TCHAR) );
        // Check for alloc err.
        if (szW) 
        {
            mbstowcs(szW, (LPSTR)sz, strlen((LPSTR)sz) + 32);
            SetWindowText(GetDlgItem(hwnd, ID_EDITCTL), szW);
        }
    } 
    else if (dwTransType == SF_UTEXT)
    {
        Edit_SetText(GetDlgItem(hwnd, ID_EDITCTL), (LPTSTR)sz);
    }
    
    // free the memory
    if (szW)
        LocalFree((HLOCAL)szW);
    if (sz)
        LocalFree((HLOCAL)sz);
    
    return;
}
//------------------------------------------------------
// RICHINK: Step 3. CallBack functions
//------------------------------------------------------
//------------------------------------------------------
// RICHINK: EditStreamReadCallback
//------------------------------------------------------
// This has the form 
//DWORD CALLBACK EditStreamCallback(  DWORD dwCookie, // application-defined value
//  LPBYTE pbBuff,  // pointer to a buffer
//  LONG cb,        // number of bytes to read or write
//  LONG *pcb       // pointer to number of bytes transferred);

static DWORD CALLBACK EditStreamReadCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    PCOOKIE pCookie = (PCOOKIE)dwCookie;
    LONG    bytesLeft;
    LONG    bytesRead;
    
    // Calc the bytes read.
    bytesRead = pCookie->pbCur - pCookie->pbStart;
    
    // Calc bytes left to read.
    if (bytesRead < pCookie->bCount)
    {
        // Calc the bytes left to read.
        bytesLeft = pCookie->bCount - bytesRead;
    }
    else
    {
        bytesLeft = 0;
    }
    
    // Don't read past the end of buffer.
    if (cb > bytesLeft) cb = bytesLeft;
    
    // Set bytes read.
    *pcb = cb;
    
    // Copy any bytes.
    if (cb)
    {
        memcpy(pbBuff, pCookie->pbCur, cb);
        pCookie->pbCur += cb;
    }
    
    // Return no error.
    return 0;
} // EditStreamReadCallback()

//------------------------------------------------------
// RICHINK: EditStreamWriteCallback
//------------------------------------------------------
// This has the form 
//DWORD CALLBACK EditStreamCallback(  DWORD dwCookie, // application-defined value
//  LPBYTE pbBuff,  // pointer to a buffer
//  LONG cb,        // number of bytes to read or write
//  LONG *pcb       // pointer to number of bytes transferred);

static DWORD CALLBACK EditStreamWriteCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    PCOOKIE pCookie = (PCOOKIE)dwCookie;
        
    // Do not overwrite the end of the buffer. If there is no output 
    // buffer, then we're only here to determine the space required for the stream out.
    
    if (pCookie->pbStart && (pCookie->pbCur + cb > pCookie->pbStart + pCookie->bCount))
    {
        // Writing all this data would overflow the buffer.
        // So only write what will fit.
        cb = pCookie->pbStart + pCookie->bCount - pCookie->pbCur;
    }

    
    *pcb = cb;

    if (pCookie->pbStart)
        memcpy(pCookie->pbCur, pbBuff, cb);

    pCookie->pbCur += cb;
    
    return 0;
} // EditStreamWriteCallback()

