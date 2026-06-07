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
#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 260

// Global Variables:
HINSTANCE g_hInst;			// The current instance
HWND g_hWnd;
HWND g_hwndCB = NULL;			// The command bar handle
TCHAR tszTitle[MAX_LOADSTRING];			// The title bar text
TCHAR tszWindowClass[MAX_LOADSTRING];		// The window class name
DWORD g_dwSHInitFlags = 0;
BOOL g_fButtonHide = TRUE;
DWORD g_dwCreateMenuType = 0;

// Foward declarations of functions included in this code module:
ATOM MyRegisterClass(
    HINSTANCE hInstance,
    LPTSTR tszWindowClass
    );
BOOL InitInstance	(
    HINSTANCE, int
    );
LRESULT CALLBACK WndProc(
    HWND,
    UINT,
    WPARAM, 
    LPARAM
    );
BOOL CALLBACK About(
    HWND,
    UINT,
    WPARAM,
    LPARAM
    );
BOOL CALLBACK SHInitDialogTestProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam,
    LPARAM lParam
    );
BOOL CALLBACK SHCreateMenuTestProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam,
    LPARAM lParam
    );
BOOL CALLBACK SHEnableSoftkeyTestProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam,
    LPARAM lParam
    );
    
//Demo's SHDoneButton
BOOL DoSHDoneButton(
    HWND hwndRequester
    );

//Demo's SHSetNavBarText
BOOL DoSHSetNavBarText(
    HWND hwndRequester, 
    UINT idMenu
    );

//Demo's SHFullScreen
BOOL DoSHFullScreen(
    HWND hwndRequester,
    DWORD dwState
    );

//Demo's SHInitDialog
BOOL DoSHInitDialogSetFlags(
    UINT wmID
    );
BOOL DoSHInitDialog(
    HWND hDlg, 
    DWORD dwFlags
    );

//Demo's SHGetAutoRunPath
BOOL DoSHGetAutoRunPath(
    HWND hwnd
    );

int WINAPI WinMain(	
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow
    )
{
  MSG Msg;
 
  LoadString(hInstance, IDC_SHAPI, tszWindowClass, MAX_LOADSTRING);
  LoadString(hInstance, IDS_APP_TITLE, tszTitle, MAX_LOADSTRING);
  
  // Check if this app. is running
  if (FindWindow(tszWindowClass, tszTitle))
  {
      SetForegroundWindow(FindWindow(tszWindowClass, tszTitle));
      return FALSE;
  }
  
  // Perform application initialization:
  if (FALSE == InitInstance (hInstance, nCmdShow)) 
  {
    return FALSE;
  }
  
  // Main Msg loop:
  while (GetMessage(&Msg, NULL, 0, 0)) 
  {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
  }
  
  return Msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
ATOM MyRegisterClass(
    HINSTANCE hInstance, 
    LPTSTR tszWindowClass
    )
{
    WNDCLASS	wc;
    
    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc	= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHAPI));
    wc.hCursor		= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName	= 0;
    wc.lpszClassName	= tszWindowClass;
    
    return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
BOOL InitInstance(
    HINSTANCE hInstance, 
    int nCmdShow)
{
    RECT rc;
    
    g_hInst = hInstance;		// Store instance handle in our global variable
    // Initialize global strings
    MyRegisterClass(hInstance, tszWindowClass);
    
    g_hWnd = CreateWindow(tszWindowClass, tszTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    
    GetWindowRect(g_hWnd, &rc);
    rc.bottom -= MENU_HEIGHT; 
    if (g_hwndCB)MoveWindow(g_hWnd, rc.left, rc.top, rc.right, rc.bottom - rc.top, TRUE); 
    
    if (NULL == g_hWnd)
    {	
        return FALSE;
    }
    
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);
    
    return TRUE;
}

//
LRESULT CALLBACK WndProc(
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    )
{
    HDC hdc;
    static int cx, cy;
    PAINTSTRUCT ps;
    TCHAR tszBuff[MAX_LOADSTRING];
    RECT rc;
    
    SHMENUBARINFO mbi;
    
    switch (Msg) 
    {
    case WM_COMMAND:
        // Parse the menu selections:
        switch (LOWORD(wParam))
        {
        case ID_SHAPI_SHINITDIALOG:
            DialogBox(g_hInst, (LPCTSTR)IDD_TESTDIALOG, hWnd, (DLGPROC)SHInitDialogTestProc);
            break;
            
        case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON:
        case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG:
        case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN:
        case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN:
        case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR:
            DoSHInitDialogSetFlags(LOWORD(wParam));
            break;
            
        case ID_SHAPI_SHFULLSCREENWINDOW:
            DoSHFullScreen(hWnd, SHFS_HIDETASKBAR);
            DoSHFullScreen(hWnd, SHFS_HIDESIPBUTTON);
            ShowWindow(g_hwndCB, SW_HIDE);
            rc.left = 0; 
            rc.top = 0;
            rc.right = cx;
            rc.bottom = cy;
            MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
            break;
            
        case ID_SHAPI_SHFULLSCREEN_SHFSSHOWTASKBAR:
            DoSHFullScreen(hWnd, SHFS_SHOWTASKBAR);
            rc.left = 0; 
            rc.top = MENU_HEIGHT;
            rc.right = cx;
            rc.bottom = cy - (2*MENU_HEIGHT);
            MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
            break;
            
        case ID_SHAPI_SHFULLSCREEN_SHFSHIDETASKBAR:
            DoSHFullScreen(hWnd, SHFS_HIDETASKBAR);
            rc.left = 0; 
            rc.top = 0;
            rc.right = cx;
            rc.bottom = cy - MENU_HEIGHT;
            MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
            break;
            
        case ID_SHAPI_SHFULLSCREEN_SHFSSHOWSIPBUTTON:
            DoSHFullScreen(hWnd, SHFS_SHOWSIPBUTTON);
            break;
            
        case ID_SHAPI_SHFULLSCREEN_SHFSHIDESIPBUTTON:
            DoSHFullScreen(hWnd, SHFS_HIDESIPBUTTON);
            break;
            
        case ID_SHAPI_SHFULLSCREEN_SHFSSHOWSTARTICON:
            DoSHFullScreen(hWnd, SHFS_SHOWSTARTICON);
            break;
            
        case ID_SHAPI_SHFULLSCREEN_SHFSHIDESTARTICON:
            DoSHFullScreen(hWnd, SHFS_HIDESTARTICON);
            break;
            
        case ID_SHAPI_SHSETNAVBARTEXT_HERETODAY:
        case ID_SHAPI_SHSETNAVBARTEXT_GONETOMORROW:
            DoSHSetNavBarText(hWnd, LOWORD(wParam));
            break;
            
        case ID_SHAPI_SHDONEBUTTON:
            DoSHDoneButton(hWnd);
            break;
            
        case ID_SHAPI_SHGETAUTORUNPATH:
            DoSHGetAutoRunPath(hWnd);
            break;

        case ID_SHCREATEMENUBAR_RCDATA:
        case ID_SHCREATEMENUBAR_HMENU:
        case ID_SHCREATEMENUBAR_EMPTYBAR:
        case ID_SHCREATEMENUBAR_NOSIPBUTTON:
        case ID_SHCREATEMENUBAR_HIDDENMENUBAR:
            g_dwCreateMenuType = LOWORD(wParam);
            DialogBox(g_hInst, (LPCTSTR)IDD_TESTDIALOG, hWnd, (DLGPROC)SHCreateMenuTestProc);
            break;

        case ID_SHELLAPI_SHENABLESOFTKEY:
            DialogBox(g_hInst, (LPCTSTR)IDD_TESTDIALOG, hWnd, (DLGPROC)SHEnableSoftkeyTestProc);
            break;
           
        case IDM_ABOUT:
            DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            break;
            
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDOK:
            MessageBox(hWnd, _T("Done button hit!"), _T("Alert!"), MB_OK);
            break;
        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }
        break;
        
    case WM_LBUTTONDOWN:
        SHFullScreen(hWnd, SHFS_SHOWTASKBAR );
        ShowWindow(g_hwndCB, SW_SHOW);
        rc.left = 0; 
        rc.top = MENU_HEIGHT;
        rc.right = cx;
        rc.bottom = cy - (2*MENU_HEIGHT);
        MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
        break;
        
    case WM_CREATE:
        {
            //set up menu bar structure
            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hWnd;
            mbi.nToolBarId = IDM_MAIN_MENU;
            mbi.hInstRes   = g_hInst;
            //mbi.nBmpId     = 0; //set in memset
            //mbi.cBmpImages = 0; //set in memset
            
            if (FALSE == SHCreateMenuBar(&mbi))
            {
                MessageBox(hWnd, _T("SHCreateMenuBar Failed"), _T("Error"), MB_OK);
            }
            //retain the hwnd to the toolbar to destroy it if necessary
            g_hwndCB = mbi.hwndMB;
            //get screen size
            HDC hdc = GetDC(hWnd);
            cx = GetDeviceCaps(hdc, HORZRES);
            cy = GetDeviceCaps(hdc, VERTRES);
            ReleaseDC(hWnd, hdc);
        }
        break;
        
    case WM_PAINT:
        {
            RECT rt;
            hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rt);
            LoadString(g_hInst, IDS_SHAPI_TEXT, tszBuff, MAX_LOADSTRING);
            DrawText(hdc, tszBuff, _tcslen(tszBuff), &rt, 
                DT_SINGLELINE | DT_VCENTER | DT_CENTER);
            SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
            Rectangle(hdc, rt.left, rt.top, rt.left + 50, rt.top+ 50);
            Ellipse(hdc, rt.right-50, rt.top, rt.right, rt.top+ 50);
            Rectangle(hdc, rt.right-50, rt.bottom-50, rt.right, rt.bottom);
            Ellipse(hdc, rt.left, rt.bottom-50, rt.left + 50, rt.bottom);
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            EndPaint(hWnd, &ps);
        }
        break;
        
    case WM_DESTROY:
        DestroyWindow(g_hwndCB);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
 }
 return 0;
}

// Mesage handler for the About box.
BOOL CALLBACK About(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        //On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
        // with an OK button in the upper corner. 
        SHINITDLGINFO shidi;
        // Create a Done button and size it.
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        //initialzes the dialog based on the dwFlags parameter
        SHInitDialog(&shidi);
        return TRUE;
        
    case WM_COMMAND:
        if ((IDOK == LOWORD(wParam)) || (IDCANCEL == LOWORD(wParam)))
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}



//DoSHDoneButton
// demonstrates how to put an OK button on the task bar
BOOL DoSHDoneButton(
    HWND hwndRequester
    )
{
    
    //BOOL SHDoneButton(HWND hwndRequester, DWORD dwState);
    //
    // Valid states
    //#define SHDB_SHOW                   0x0001
    //#define SHDB_HIDE                   0x0002
    
    if (TRUE == g_fButtonHide)
    {
        g_fButtonHide = FALSE;
        HMENU hShowButton = SHMenuBar_GetMenu(g_hwndCB, IDM_MAIN_SHAPI);
        CheckMenuItem(hShowButton, ID_SHAPI_SHDONEBUTTON, MF_CHECKED | MF_BYCOMMAND);
        return SHDoneButton(hwndRequester, SHDB_SHOW);
    } 
    else 
    {
        g_fButtonHide = TRUE;
        HMENU hShowButton = SHMenuBar_GetMenu(g_hwndCB, IDM_MAIN_SHAPI);
        CheckMenuItem(hShowButton, ID_SHAPI_SHDONEBUTTON, MF_UNCHECKED | MF_BYCOMMAND);
        return SHDoneButton(hwndRequester, SHDB_HIDE);
    }
    
}

//DoSHDoneButton
// demonstrates how to set text on the navigation bar
BOOL DoSHSetNavBarText(
    HWND hwndRequester, 
    UINT idMenu
    )
{
    TCHAR tszText[MAX_LOADSTRING];
    MENUITEMINFO mii;
    
    HMENU hSHMenu = SHMenuBar_GetMenu(g_hwndCB, IDM_MAIN_SHAPI);
    
    memset((char *)&mii, 0, sizeof(mii));
    mii.cbSize = sizeof(mii); 
    mii.fMask  = MIIM_TYPE;
    mii.dwTypeData = &tszText[0];
    mii.cch = MAX_LOADSTRING;
    mii.fType =  MFT_STRING; 
    GetMenuItemInfo(hSHMenu, idMenu, FALSE, &mii);
    
    return SHSetNavBarText(hwndRequester, tszText);
}

//DoSHFullScreen
// demonstrates how to show app fullscreen
BOOL DoSHFullScreen(
    HWND hwndRequester, 
    DWORD dwState
    )
{
    // Valid states
    //#define SHFS_SHOWTASKBAR            0x0001
    //#define SHFS_HIDETASKBAR            0x0002
    //#define SHFS_SHOWSIPBUTTON          0x0004
    //#define SHFS_HIDESIPBUTTON          0x0008
    //#define SHFS_SHOWSTARTICON          0x0010
    //#define SHFS_HIDESTARTICON          0x0020
    
    return SHFullScreen(hwndRequester, dwState);
}

////////////////////////////////////////////////////////////////////////////////////
// Demostration of SHInitDialog
//
// Mesage handler for the SHInitDialogTestProc box.
BOOL CALLBACK SHInitDialogTestProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        DoSHInitDialog(hDlg, g_dwSHInitFlags); 
        return TRUE;
        
    case WM_COMMAND:
        if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}

//DoSHInitDialog
// demonstrates how to use SHInitDialog with various flags
BOOL DoSHInitDialog(
    HWND hDlg,
    DWORD dwFlags)
{
    SHINITDLGINFO shidi;
    //
    // Valid mask values
    //#define SHIDIM_FLAGS                0x0001
    
    shidi.hDlg = hDlg;
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = dwFlags;
    
    return SHInitDialog(&shidi);
}


BOOL DoSHInitDialogSetFlags(
    UINT wmID
    )
{
    
    HMENU hMenu = SHMenuBar_GetMenu(g_hwndCB, IDM_MAIN_SHAPI);
    // Valid flags
    //#define SHIDIF_DONEBUTTON           0x0001
    //#define SHIDIF_SIZEDLG              0x0002
    //#define SHIDIF_SIZEDLGFULLSCREEN    0x0004
    //#define SHIDIF_SIPDOWN              0x0008
    //#define SHIDIF_FULLSCREENNOMENUBAR  0x0010 
    
    //add or remove flag and un/checkmenuitem
    switch (wmID)
    {
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON:
        if (g_dwSHInitFlags & SHIDIF_DONEBUTTON)
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON , MF_UNCHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags &= ~SHIDIF_DONEBUTTON; //remove flag 
        }
        else 
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON , MF_CHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags |= SHIDIF_DONEBUTTON;  //add flag
        }
        break;
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG:
        if (g_dwSHInitFlags & SHIDIF_SIZEDLG)
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG , MF_UNCHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags &= ~SHIDIF_SIZEDLG; //remove flag 
        }
        else 
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG , MF_CHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags |= SHIDIF_SIZEDLG;  //add flag
        }
        break;
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN:
        if (g_dwSHInitFlags & SHIDIF_SIZEDLGFULLSCREEN)
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN , MF_UNCHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags &= ~SHIDIF_SIZEDLGFULLSCREEN; //remove flag 
        } 
        else
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN , MF_CHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags |= SHIDIF_SIZEDLGFULLSCREEN;  //add flag
        }
        break;
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN:
        if (g_dwSHInitFlags & SHIDIF_SIPDOWN)
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN , MF_UNCHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags &= ~SHIDIF_SIPDOWN; //remove flag 
        }
        else
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN , MF_CHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags |= SHIDIF_SIPDOWN;  //add flag
        }
        break;
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR:
        if (g_dwSHInitFlags & SHIDIF_FULLSCREENNOMENUBAR)
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR , MF_UNCHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags &= ~SHIDIF_FULLSCREENNOMENUBAR; //remove flag 
        } 
        else 
        {
            CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR , MF_CHECKED | MF_BYCOMMAND);
            g_dwSHInitFlags |= SHIDIF_FULLSCREENNOMENUBAR;  //add flag
        }
        break;
    }
    return TRUE;
}

BOOL DoSHGetAutoRunPath(
    HWND hwnd
    )
{
    
    TCHAR tszBuff[MAX_PATH];
    
    memset(&tszBuff, 0, sizeof(tszBuff));
    
    SHGetAutoRunPath(&tszBuff[0]);
    if (tszBuff[0] != '\0')
    {
        MessageBox(hwnd, tszBuff, L"AutoRun", MB_OK);
    }
    else
    {
        MessageBox(hwnd, L"AutoRunPath not set.", L"AutoRun", MB_OK);
    }
   
    return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////
// Demostration of SHCreateMenuBar
//
// Mesage handler for the SHCreateMenuTestProc box.
//
// Note: IDR_CMB_CMDBAR will be overwritten if .RC file is changed in VC.
//       So the resource is here for reference.
// 
// IDR_CMB_CMDBAR RCDATA 
// BEGIN
//     IDM_CMB_SK2MENU, // menu
//     2,               // Count of buttons
//     I_IMAGENONE, IDM_SK1,  TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, IDS_SK1, 0, NOMENU,
//     I_IMAGENONE, IDM_MENU, TBSTATE_ENABLED, TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE, IDS_MENU, 0, 0
// END

BOOL CALLBACK SHCreateMenuTestProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam)
{
    static HWND hwndMB = NULL;

    switch (Msg)
    {
        case WM_INITDIALOG:
        {
            DWORD dwSHInitFlags = SHIDIF_DONEBUTTON|SHIDIF_SIZEDLGFULLSCREEN|SHIDIF_SIPDOWN;
            SHMENUBARINFO mbi;

            if (ID_SHCREATEMENUBAR_HIDDENMENUBAR == g_dwCreateMenuType)
            {
                dwSHInitFlags &= ~SHIDIF_SIZEDLGFULLSCREEN;
            }
            
            DoSHInitDialog(hDlg, dwSHInitFlags);

            //set up menu bar structure
            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hDlg;
            mbi.hInstRes   = g_hInst;

            switch(g_dwCreateMenuType)
            {
                case ID_SHCREATEMENUBAR_RCDATA:
                    mbi.nToolBarId = IDR_CMB_CMDBAR;
                    break;
                    
                case ID_SHCREATEMENUBAR_HMENU:
                    mbi.dwFlags = SHCMBF_HMENU;
                    mbi.nToolBarId = IDM_CMB_MENU;
                    break;

                case ID_SHCREATEMENUBAR_EMPTYBAR:
                    mbi.dwFlags = SHCMBF_EMPTYBAR;
                    break;

                case ID_SHCREATEMENUBAR_NOSIPBUTTON:
                    mbi.dwFlags = SHCMBF_EMPTYBAR|SHCMBF_HIDESIPBUTTON;
                    break;

                case ID_SHCREATEMENUBAR_HIDDENMENUBAR:
                    mbi.dwFlags = SHCMBF_HMENU;
                    break;

                default:
                    break;
            }

            if (FALSE == SHCreateMenuBar(&mbi))
            {
                MessageBox(hDlg, _T("SHCreateMenuBar Failed"), _T("Error"), MB_OK);
            }
            //retain the hwnd to the toolbar to destroy it if necessary
            hwndMB = mbi.hwndMB;

            return TRUE;
        }    
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                case IDCANCEL:
                    DestroyWindow(hwndMB);
                    EndDialog(hDlg, LOWORD(wParam));
                    return TRUE;
                case IDM_SK1:
                    MessageBox(hDlg, _T("SK1 is pressed"), _T("Message"), MB_OK);
                    break;
                case IDM_MENUITEM_1:
                    MessageBox(hDlg, _T("Menu item 1 is selected"), _T("Message"), MB_OK);
                    break;
                case IDM_MENUITEM_2:
                    MessageBox(hDlg, _T("Menu item 2 is selected"), _T("Message"), MB_OK);
                    break;
            }
            break;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////
// Demostration of SHEnableSoftkey
//
// Mesage handler for the SHEnableSoftkeyTestProc box.
//
// Note: IDR_ENABLESK_CMDBAR will be overwritten if .RC file is changed in VC.
//       So the resource is here for reference.
// 
// IDR_ENABLESK_CMDBAR RCDATA 
// BEGIN
//     0,   // menu
//     2,   // Count of buttons
//     I_IMAGENONE, IDM_SK1, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, IDS_SK1, 0, NOMENU,
//     I_IMAGENONE, IDM_SK2, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, IDS_DISABLESK1, 0, NOMENU
// END

BOOL CALLBACK SHEnableSoftkeyTestProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam)
{
    static HWND hwndMB = NULL;
    static BOOL fEnableSK1 = TRUE;

    switch (Msg)
    {
        case WM_INITDIALOG:
        {
            SHMENUBARINFO mbi;

            DoSHInitDialog(hDlg, SHIDIF_DONEBUTTON|SHIDIF_SIZEDLGFULLSCREEN);

            //set up menu bar structure
            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hDlg;
            mbi.nToolBarId = IDR_ENABLESK_CMDBAR;
            mbi.hInstRes   = g_hInst;

            if (FALSE == SHCreateMenuBar(&mbi))
            {
                MessageBox(hDlg, _T("SHCreateMenuBar Failed"), _T("Error"), MB_OK);
            }
            //retain the hwnd to the toolbar to destroy it if necessary
            hwndMB = mbi.hwndMB;

            return TRUE;
        }    
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                case IDCANCEL:
                    DestroyWindow(hwndMB);
                    EndDialog(hDlg, LOWORD(wParam));
                    return TRUE;

                case IDM_SK1:
                    MessageBox(hDlg, _T("Softkey I is pressed"), _T("Message"), MB_OK);
                    break;

                case IDM_SK2:
                {
                    // Set SK2 text
                    TBBUTTONINFO tbbi;
                    memset(&tbbi, 0, sizeof(tbbi));
                    tbbi.cbSize = sizeof(tbbi);
                    tbbi.dwMask = TBIF_TEXT;
                    tbbi.pszText = (LPTSTR)LoadString(g_hInst, fEnableSK1 ? IDS_ENABLESK1 : IDS_DISABLESK1, NULL, 0);

                    if (tbbi.pszText)
                    {
                        SendMessage(hwndMB, TB_SETBUTTONINFO, IDM_SK2, (LPARAM)&tbbi);
                    }

                    // Enable/Disable SK1
                    SHEnableSoftkey(hwndMB, 0, TRUE, fEnableSK1 ? FALSE : TRUE);

                    // Set cached state
                    fEnableSK1 ^= TRUE;
                    break;
                }
            }
            break;
    }
    return FALSE;
}


