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


// ****************************************************************************
// FILE: memwatcher.cpp
// ABTRACT: Main implementation file for the today item
// ****************************************************************************
//

#include "stdafx.h"


#define INVALID_HEIGHT            0xFFFFFFFF

// flags bits for options - we use negative logic to make the default (0)
// show both
#define FLAGS_HIDE_STORAGE    0x1
#define FLAGS_HIDE_PROGRAM    0x2


//global variables    
HICON               g_hIcon;
UINT                g_plugInHeight;
HINSTANCE           g_hInst;
HWND                g_hWnd;
BOOL                g_bFirstDisplay         = TRUE;
HWND                g_hStorageProgressBar;
HWND                g_hProgramProgressBar;
UINT                g_StorageMemUsed;
UINT                g_ProgramMemUsed;
BOOL                g_fShowStorage          = TRUE;
BOOL                g_fShowProgram          = TRUE;


// forward function declarations
static INT InitializeClasses();

/*************************************************************************/
/* Entry point for the dll                                                 */
/*************************************************************************/
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:            
        
        // The DLL is being loaded for the first time by a given process.
        // Perform per-process initialization here.  If the initialization
        // is successful, return TRUE; if unsuccessful, return FALSE.
        g_hInst = (HINSTANCE)hModule;
        
        //load the icon
        g_hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISPLAYICON), IMAGE_ICON, DRA::SCALEX(16), DRA::SCALEY(16) ,LR_DEFAULTCOLOR);
        
        //initilize the application class, and set the global window handle
        UnregisterClass((LPCTSTR)LoadString(g_hInst, IDS_TODAY_STORAGE_APPNAME,0,0), g_hInst);
        InitializeClasses();
        g_hWnd = 0;
        
        break;
        
    case DLL_PROCESS_DETACH:
        // The DLL is being unloaded by a given process.  Do any
        // per-process clean up here, such as undoing what was done in
        // DLL_PROCESS_ATTACH.    The return value is ignored.
        
        DestroyIcon(g_hIcon);
        
        UnregisterClass((LPCTSTR)LoadString(g_hInst, IDS_TODAY_STORAGE_APPNAME,0,0), g_hInst);
        g_hInst = NULL;
        break;           
    }
    
    return TRUE;
}

/*************************************************************************/
/* Handle any messages that may be needed for the plugin                 */
/* Handled messages:                                                     */
/*        WM_TODAYCUSTOM_QUERYREFRESHCACHE                                 */
/*        WM_CREATE                                                         */
/*        WM_LBUTTONUP                                                     */
/*        WM_PAINT                                                         */
/*        WM_DESTROY                                                         */
/*************************************************************************/
LRESULT CALLBACK WndProc (HWND hwnd, UINT uimessage, WPARAM wParam, LPARAM lParam) 
{
    switch (uimessage)
    {          
        //check to see if a refresh is required
    case WM_TODAYCUSTOM_QUERYREFRESHCACHE: 
        {
            TODAYLISTITEM *ptliItem;
            MEMORYSTATUS MemStatus;
            STORE_INFORMATION StoreInfo;
            INT iItemHeight;
            
            UINT iCurrentStore;
            DOUBLE dCurrentStore;
            BOOL    bReturn = FALSE;
            
            // get the pointer to the item from the Today screen
            ptliItem = (TODAYLISTITEM*)wParam;

            if ((NULL == ptliItem) || (WaitForSingleObject(SHELL_API_READY_EVENT, 0) == WAIT_TIMEOUT))
            {
                return FALSE;
            }
            
            g_fShowStorage = !(ptliItem->grfFlags & FLAGS_HIDE_STORAGE);
            g_fShowProgram = !(ptliItem->grfFlags & FLAGS_HIDE_PROGRAM);

            // adjust the height of the today item based on showing one or two bars
            if (g_fShowProgram && g_fShowStorage)
            {
                iItemHeight = DRA::SCALEY(40);
            }
            else
            {
                iItemHeight = DRA::SCALEY(20);
            }
            
            // determine % memory space and see if it has changed
            GlobalMemoryStatus(&MemStatus);
            if(g_ProgramMemUsed != MemStatus.dwMemoryLoad)
            {
                g_ProgramMemUsed = MemStatus.dwMemoryLoad;
                bReturn = TRUE;
            }
            
            // determine % storage space and see if it has changed
            GetStoreInformation(&StoreInfo);
            dCurrentStore = ((((DOUBLE)StoreInfo.dwStoreSize - (DOUBLE)StoreInfo.dwFreeSize) / (DOUBLE)StoreInfo.dwStoreSize) * 100);
            iCurrentStore = (INT)dCurrentStore;
            
            if(g_StorageMemUsed != iCurrentStore)
            {
                g_StorageMemUsed = iCurrentStore;
                bReturn = TRUE;
            }
            
            if (0 == ptliItem->cyp)
            {
                ptliItem->cyp = iItemHeight;
                bReturn = TRUE;
            }
            
            return bReturn;
            
            
        }        
        
    case WM_CREATE:         
        break;
        
    case WM_LBUTTONUP: 
        MessageBox(NULL, TEXT("Detected Screen Tap!"), TEXT("StorageCheck Today Item:"), MB_OK);
        break;          
        
    case WM_PAINT: 
        PAINTSTRUCT     ps;
        RECT            rcWindBounds; 
        RECT            rcMyBounds;
        HDC             hDC;
        HFONT            hFontOld;
        TCHAR            szTextBuffer[10];
        COLORREF        crText;

        GetWindowRect( hwnd, &rcWindBounds); 
        
        hDC = BeginPaint(hwnd, &ps);
        
        // create a custom rectangle relative to the client area
        rcMyBounds.left = 0;
        rcMyBounds.top = DRA::SCALEY(2);
        rcMyBounds.right = rcWindBounds.right - rcWindBounds.left;
        rcMyBounds.bottom = rcWindBounds.bottom - rcWindBounds.top;          
        
        // draw the icon on the screen
        SetBkMode(hDC, TRANSPARENT);
        DrawIcon(hDC, 2, 0, g_hIcon);
        
        BOOL bIsFarEast;
        LOGFONT lf;
        HFONT hSysFont;
        HFONT hFont;

        //determine if this is a Far East platform
        switch (PRIMARYLANGID(LANGIDFROMLCID(GetSystemDefaultLCID())))
        {
        case LANG_CHINESE:
        case LANG_KOREAN:
        case LANG_JAPANESE:
            bIsFarEast = TRUE;
            break;
            
        default:
            bIsFarEast = FALSE;
            break;
        }

        hSysFont = (HFONT) GetStockObject(SYSTEM_FONT);
        GetObject(hSysFont, sizeof(LOGFONT), &lf);
        // If it is far east, use a normal font at 9 points,
        //  otherwise use a bold font as 8 points
        if (bIsFarEast)
        {
            lf.lfWeight = FW_NORMAL;
            // Calculate the font size, making sure to round the result to the nearest integer
            lf.lfHeight = (long) -((9.0 * (double)GetDeviceCaps(hDC, LOGPIXELSY) / 72.0)+.5);
        }
        else
        {
            lf.lfWeight = FW_BOLD;
            // Calculate the font size, making sure to round the result to the nearest integer
            lf.lfHeight = (long) -((8.0 * (double)GetDeviceCaps(hDC, LOGPIXELSY) / 72.0)+.5);
        }

        // create the font
        hFont = CreateFontIndirect(&lf);
    
        // Select the system font into the device context
        hFontOld = (HFONT) SelectObject(hDC, hFont);

        // determine the theme's current text color
        //  this color will change when the user picks a new theme,
        //  so get it each time the display needs to be painted
        crText = SendMessage(GetParent(hwnd), TODAYM_GETCOLOR, (WPARAM) TODAYCOLOR_TEXT, NULL);

        // set that color
        SetTextColor(hDC, crText);

        // determine if there is one or two bars to paint
        if(g_fShowProgram && g_fShowStorage)
        {
            // update and paint storage status bar
            SendMessage(g_hStorageProgressBar, PBM_SETPOS, g_StorageMemUsed, NULL);
            SetWindowPos(g_hStorageProgressBar, g_hWnd, DRA::SCALEX(85), DRA::SCALEY(4), DRA::SCALEX(120), DRA::SCALEY(10), SWP_SHOWWINDOW);
            
            // update and paint program status bar
            SendMessage(g_hProgramProgressBar, PBM_SETPOS, g_ProgramMemUsed, NULL);
            SetWindowPos(g_hProgramProgressBar, g_hWnd, DRA::SCALEX(85), DRA::SCALEY(24), DRA::SCALEX(120), DRA::SCALEY(10), SWP_SHOWWINDOW);

            // draw the storage item text
            rcMyBounds.left = rcMyBounds.left + DRA::SCALEX(28);
            DrawText(hDC, TEXT("Storage:"), -1, &rcMyBounds, DT_LEFT);
            
            // draw the program item text
            rcMyBounds.top += DRA::SCALEX(20);
            DrawText(hDC, TEXT("Program:"), -1, &rcMyBounds, DT_LEFT);
            
            // draw the program item % text
            rcMyBounds.left = DRA::SCALEX(210);
            wsprintf(szTextBuffer, TEXT("%i%%"), g_ProgramMemUsed);
            DrawText(hDC, szTextBuffer, -1, &rcMyBounds, DT_LEFT);
            
            // draw the storage item % text
            rcMyBounds.top = DRA::SCALEY(2);
            wsprintf(szTextBuffer, TEXT("%i%%"), g_StorageMemUsed);
            DrawText(hDC, szTextBuffer, -1, &rcMyBounds, DT_LEFT);
            
        }
        else
        {
            // if only show program memory is checked
            if(g_fShowProgram)
            {
                // update and paint program status bar
                SendMessage(g_hProgramProgressBar, PBM_SETPOS, g_ProgramMemUsed, NULL);
                SetWindowPos(g_hProgramProgressBar, g_hWnd, DRA::SCALEX(85), DRA::SCALEY(4), DRA::SCALEX(120), DRA::SCALEY(10), SWP_SHOWWINDOW);
                
                // draw the program item text
                rcMyBounds.left = rcMyBounds.left + DRA::SCALEX(28);
                DrawText(hDC, TEXT("Program:"), -1, &rcMyBounds, DT_LEFT);
                
                // draw the program item % text
                rcMyBounds.left = DRA::SCALEX(210);
                wsprintf(szTextBuffer, TEXT("%i%%"), g_ProgramMemUsed);
                DrawText(hDC, szTextBuffer, -1, &rcMyBounds, DT_LEFT);
            }
            // if only show storage memory is checked
            else
            {
                // update and paint storage status bar
                SendMessage(g_hStorageProgressBar, PBM_SETPOS, g_StorageMemUsed, NULL);
                SetWindowPos(g_hStorageProgressBar, g_hWnd, DRA::SCALEX(85), DRA::SCALEX(4), DRA::SCALEX(120), DRA::SCALEX(10), SWP_SHOWWINDOW);
                
                // draw the storage item text
                rcMyBounds.left = rcMyBounds.left + DRA::SCALEX(28);
                DrawText(hDC, TEXT("Storage:"), -1, &rcMyBounds, DT_LEFT);
                
                // draw the storage item % text
                rcMyBounds.left = DRA::SCALEX(210);
                wsprintf(szTextBuffer, TEXT("%i%%"), g_StorageMemUsed);
                DrawText(hDC, szTextBuffer, -1, &rcMyBounds, DT_LEFT);
            }
        }
        
        // Select the previous font back into the device context
        SelectObject(hDC, hFontOld);

        DeleteObject(hFont);

        EndPaint(hwnd, &ps);
        return 0;
        
    case WM_DESTROY :          
        return 0 ;
        
    // this fills in the background with the today screen image
    case WM_ERASEBKGND:
        TODAYDRAWWATERMARKINFO dwi;
        dwi.hdc = (HDC)wParam;
        GetClientRect(hwnd, &dwi.rc);
        
        dwi.hwnd = hwnd;
        SendMessage(GetParent(hwnd), TODAYM_DRAWWATERMARK, 0,(LPARAM)&dwi);
        return TRUE;
    }

    return DefWindowProc (hwnd, uimessage, wParam, lParam) ;
}


/*************************************************************************/
/* Create and register our window class for the today item                 */
/*************************************************************************/
INT InitializeClasses()
{
    WNDCLASS         wc; 
    memset(&wc, 0, sizeof(wc));
    
    wc.style         = 0;                   
    wc.lpfnWndProc     = (WNDPROC) WndProc;
    wc.hInstance     = g_hInst;
    wc.hIcon         = 0;
    wc.hCursor         = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = (LPCTSTR)LoadString(g_hInst, IDS_TODAY_STORAGE_APPNAME,0,0);
    
    //register our window
    if(!RegisterClass(&wc))
    { 
        return 0 ;
    }
    return 1;
}

/*************************************************************************/
/* Initialize the DLL by creating a new window                             */
/*************************************************************************/
HWND InitializeCustomItem(TODAYLISTITEM *ptli, HWND hwndParent) 
{
    LPCTSTR appName = (LPCTSTR)LoadString(g_hInst,IDS_TODAY_STORAGE_APPNAME,0,0);
    
    //create a new window
    g_hWnd = CreateWindow(appName,appName,WS_VISIBLE | WS_CHILD,
        CW_USEDEFAULT,CW_USEDEFAULT,240,0,hwndParent, NULL, g_hInst, NULL) ;
    
    // create the storage space progress bar
    g_hStorageProgressBar = CreateWindow(PROGRESS_CLASS, TEXT("Storage Progress Bar"), 
        WS_CHILD | PBS_SMOOTH, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        ,g_hWnd, NULL, g_hInst, NULL);
    
    // adjust the step to be in 1% increments
    SendMessage(g_hStorageProgressBar,PBM_SETSTEP,1,NULL); 
    
    // create the program memory progress bar
    g_hProgramProgressBar = CreateWindow(PROGRESS_CLASS, TEXT("Program Progress Bar"), 
        WS_CHILD | PBS_SMOOTH, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        ,g_hWnd, NULL, g_hInst, NULL);
    
    
    // adjust the step to be in 1% increments
    SendMessage(g_hProgramProgressBar,PBM_SETSTEP,1,NULL); 
    
    
    // attach our winproc to the newly created window
    SetWindowLong(g_hWnd, GWL_WNDPROC, (LONG) WndProc);
    
    //display the window
    ShowWindow (g_hWnd, SW_SHOWNORMAL);
    UpdateWindow (g_hWnd) ;  
    
    return g_hWnd;
}

/*************************************************************************/
/* Message Handler for the options dialog                                 */
/*************************************************************************/
LRESULT WINAPI CustomItemOptionsDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TODAYLISTITEM *s_ptliItem = NULL;

    switch (message)
    {
    case WM_INITDIALOG:
        {
            SHINITDLGINFO shidi;
            BOOL fShowStorage, fShowProgram;

            // Create a Done button and size it.  
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;
            SHInitDialog(&shidi);

            // get a pointer to the item structure that Settings passes us
            s_ptliItem = (TODAYLISTITEM*)lParam;

            // the flags are used to store the user choice of what to show
            // (beyond that, further settings could be stored in the registry)

            if (NULL != s_ptliItem)
            {
                // get the selection stored in grfFlags
                fShowStorage = !(s_ptliItem->grfFlags & FLAGS_HIDE_STORAGE);
                fShowProgram = !(s_ptliItem->grfFlags & FLAGS_HIDE_PROGRAM);
            }
            else
            {
                // something went wrong, check both
                fShowStorage = fShowProgram = TRUE;
            }

            if (fShowStorage && fShowProgram)
            {
                CheckRadioButton(hDlg, IDC_PROGRAM, IDC_STORAGE, IDC_BOTH);
            }
            else if (fShowStorage)
            {
                CheckRadioButton(hDlg, IDC_PROGRAM, IDC_STORAGE, IDC_STORAGE);
            }
            else
            {
                CheckRadioButton(hDlg, IDC_PROGRAM, IDC_STORAGE, IDC_PROGRAM);
            }
        }
        return TRUE; 
        
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) 
        {
            HWND hCurrentRadioButton;
            BOOL fShowStorage, fShowProgram;

            // check to see if both is checked
            hCurrentRadioButton = GetDlgItem(hDlg, IDC_BOTH);
            if(BST_CHECKED == SendMessage(hCurrentRadioButton, BM_GETCHECK, NULL, NULL))
            {
                fShowStorage = TRUE;
                fShowProgram = TRUE;
            }
            
            // check to see if only program is checked
            hCurrentRadioButton = GetDlgItem(hDlg, IDC_PROGRAM);
            if(BST_CHECKED == SendMessage(hCurrentRadioButton, BM_GETCHECK, NULL, NULL))
            {
                fShowStorage = FALSE;
                fShowProgram = TRUE;
            }
            
            // check to see if only storage is checked
            hCurrentRadioButton = GetDlgItem(hDlg, IDC_STORAGE);
            if(BST_CHECKED == SendMessage(hCurrentRadioButton, BM_GETCHECK, NULL, NULL))
            {
                fShowStorage = TRUE;
                fShowProgram = FALSE;
            }
            
            s_ptliItem->grfFlags = (fShowStorage ? 0 : FLAGS_HIDE_STORAGE) |
                (fShowProgram ? 0 : FLAGS_HIDE_PROGRAM);
            
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;

    case WM_DESTROY:
        // reset this - the Settings instance is closing
        s_ptliItem = NULL;
        break;

    }

    return FALSE;
}
