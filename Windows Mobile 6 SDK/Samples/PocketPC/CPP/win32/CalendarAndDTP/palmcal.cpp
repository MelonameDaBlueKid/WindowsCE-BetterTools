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

/*-------------------------------------------------------------------*\
Module: PalmCal.cpp
\*-------------------------------------------------------------------*/
#include "stdafx.h"
#include "resource.h"

//------------------------------------------------------
// Globals
//------------------------------------------------------

HINSTANCE g_hInst = NULL;  // Local copy of hInstance, used in Commandbar_Create & Commandbar_InsertMenubar
HWND      g_hwndMain = NULL;    // Handle to Main window returned from CreateWindow
HWND            g_hwndCB =NULL;       // Handle to a commandband
HMENU           g_hMenu =NULL;       // Handle to a commandbar0 menu

HWND            g_hwnd_SCR1 = NULL;
HWND            g_hwnd_SCR2 = NULL;
HWND            g_hwnd_SCR3 = NULL;

HWND            g_hwndCurrentDisplay = NULL;

HWND            g_hCommandCombo = NULL;
UINT            g_nCBrHeight = 0;

int             g_iCurrentMenuItem = 0;
RECT            g_hwndMainRect;

#if defined (_DEBUG)
TCHAR   szDebug[500];
LRESULT iDebugRET;
#endif

TCHAR szAppName[] = TEXT("Calendar Sample Application");
TCHAR szTitle[]   = TEXT("Calendar Sample");

//------------------------------------------------------
// Forward Declares
//------------------------------------------------------

BOOL CALLBACK  AboutDlgProc(HWND, WORD, WORD, LONG);

//---Screen proc's
LRESULT CALLBACK  Dialog1DlgProc(HWND , UINT , WPARAM , LPARAM );
LRESULT CALLBACK  Dialog2DlgProc(HWND , UINT , WPARAM , LPARAM );
LRESULT CALLBACK  Dialog3DlgProc(HWND , UINT , WPARAM , LPARAM );

//------------------------------------------------------
// Local Functions
//------------------------------------------------------
int SetCurrentMenu(UINT uiChecked)
{
    //Get the hMenu of the View submenu of the MenuBar
    HMENU hViewMenu = SHMenuBar_GetMenu(g_hwndCB, IDM_MAIN_MENUITEM1);
    if (NULL == hViewMenu)
    {
        MessageBox(g_hwndMain, L"SHMenuBar_GetMenu Failed", L"Error", MB_OK);
    }
    
    //check new menu item
    if (FALSE == CheckMenuRadioItem(hViewMenu, IDM_VIEW_SCREEN1, IDM_VIEW_SCREEN3, uiChecked , MF_BYCOMMAND))
    {
        MessageBox(g_hwndMain, L"CheckMenuRadioItem Failed", L"Error", MB_OK);
    }
    
    g_iCurrentMenuItem = uiChecked;
    return (uiChecked);
}

void InitScreens(HWND hwnd)
{
    g_hwnd_SCR1 = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SCR1), hwnd, (DLGPROC)Dialog1DlgProc);    
    g_hwnd_SCR2 = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SCR2), hwnd, (DLGPROC)Dialog2DlgProc);    
    g_hwnd_SCR3 = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SCR3), hwnd, (DLGPROC)Dialog3DlgProc);  
}

HWND Refresh(HWND hwnd)
{
    UpdateWindow(hwnd);
    return hwnd;
}

HWND ShowNewWindow(HWND oldHwnd, HWND newHwnd)
{
    RECT rc;
    ShowWindow(oldHwnd, SW_HIDE);
    GetClientRect(g_hwndMain, &rc);
    rc.bottom -= MENU_HEIGHT;
    MoveWindow(newHwnd, rc.left, rc.top, rc.right, rc.bottom, TRUE);
    ShowWindow(newHwnd, SW_SHOW);
    UpdateWindow(newHwnd);
    return newHwnd;
}


//------------------------------------------------------
//   MainWndProc
//------------------------------------------------------

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    LRESULT lResult = TRUE;
    TCHAR szbuffer[_MAX_PATH] = TEXT(" ");
    
    switch(msg)
    {
        
    case WM_CREATE:
        {
            //Required in order to use the calendar and DTP controls
            INITCOMMONCONTROLSEX icex;
            icex.dwSize = sizeof(icex);
            icex.dwICC = ICC_DATE_CLASSES;
            InitCommonControlsEx(&icex);
            
            
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
            else
            {
                g_hwndCB = mbi.hwndMB;
            }
            
            InitScreens( hwnd );
            
            if ( g_hwnd_SCR1 )
            {
                ShowWindow(g_hwnd_SCR1, SW_SHOW);
                UpdateWindow(g_hwnd_SCR1);
                g_hwndCurrentDisplay = ShowNewWindow(g_hwndCurrentDisplay, g_hwnd_SCR1);
                g_iCurrentMenuItem=SetCurrentMenu(IDM_VIEW_SCREEN1);
            }
        }
        break;
        
        
    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wp,lp))
        { 
            
        case IDM_VIEW_SCREEN1 :    
            g_hwndCurrentDisplay = ShowNewWindow(g_hwndCurrentDisplay, g_hwnd_SCR1);
            g_iCurrentMenuItem = SetCurrentMenu(IDM_VIEW_SCREEN1);
            break;
            
        case IDM_VIEW_SCREEN2 :    
            g_hwndCurrentDisplay = ShowNewWindow(g_hwndCurrentDisplay, g_hwnd_SCR2);
            g_iCurrentMenuItem = SetCurrentMenu(IDM_VIEW_SCREEN2);
            break;
            
        case IDM_VIEW_SCREEN3 :
            g_hwndCurrentDisplay = ShowNewWindow(g_hwndCurrentDisplay, g_hwnd_SCR3);
            g_iCurrentMenuItem = SetCurrentMenu(IDM_VIEW_SCREEN3);
            break;
            
        case IDM_FILE_EXIT:
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            
        case IDM_HELP_ABOUT:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG), hwnd, (DLGPROC)AboutDlgProc);
            break;
            
            
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
        }
        break; //WM_COMMAND
        
        case WM_CLOSE:
            DestroyWindow(g_hwndCB);
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
    g_hwndMain = CreateWindow(szAppName,
        szTitle,              
        WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL, 
        NULL, 
        hInstance, 
        NULL );
    
    if ( !g_hwndMain )      
    {
        return FALSE;
    }
    // After CreateWindow
    //When the main window is created using CW_USEDEFAULT the height of the menubar (if one
    // is created is not taken into account). So we resize the window after creating it
    // if a menubar is present
    {
        RECT rc;
        GetWindowRect(g_hwndMain, &rc);
        rc.bottom -= MENU_HEIGHT;
        if (g_hwndCB)
            MoveWindow(g_hwndMain, rc.left, rc.top, rc.right, rc.bottom, FALSE);
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
    
    InitCommonControls();
    
    wc.style = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//NULL;
    wc.hInstance = hInstance;
    wc.hCursor = NULL;                                              // No cursor if target is not NT
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
// AboutDlgProc(HWND, WORD, WORD, LONG)
//------------------------------------------------------
BOOL CALLBACK  AboutDlgProc( HWND hDlg, WORD message, WORD wParam, LONG lParam)

{
    if (message == WM_COMMAND)
    {
        EndDialog(hDlg, TRUE);
        return(TRUE);
    }
    if (message == WM_INITDIALOG){
      //On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
      // with an OK button in the upper corner. You should get/set any program settings
      // during each modal dialog creation and destruction
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      //initialzes the dialog based on the dwFlags parameter
      SHInitDialog(&shidi);
      
        return(TRUE);
    }
    else
        return(FALSE);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);
}


//------------------------------------------------------
// Dialog1DlgProc(HWND, WORD, WORD, LONG)
//------------------------------------------------------

LRESULT CALLBACK Dialog1DlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{  
    LRESULT lResult = TRUE;
    
    switch(msg)
    {
    case WM_INITDIALOG:
        {
            //Custom DateTimeFormatting example
            //DateTime_SetFormat( GetDlgItem(hwnd,IDC_CONTROL_DTS_LONGDATEFORMAT ), TEXT("MMMdd','yyy hh':'m':'s tt"));
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
// Dialog2DlgProc(HWND, WORD, WORD, LONG)
//------------------------------------------------------
LRESULT CALLBACK Dialog2DlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)

{  
    LRESULT lResult = TRUE;
    
    switch(msg)
    {
    case WM_INITDIALOG:
        {
            //Custom DateTimeFormatting example
            //DateTime_SetFormat( GetDlgItem(hwnd,IDC_CONTROL_DTS_LONGDATEFORMAT ), TEXT("MMMdd','yyy hh':'m':'s tt"));
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
// Dialog3DlgProc(HWND, WORD, WORD, LONG)
//------------------------------------------------------
LRESULT CALLBACK Dialog3DlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)

{  
    LRESULT lResult = TRUE;
    
    switch(msg)
    {
        
    case WM_INITDIALOG:
        {
            //Custom DateTimeFormatting example
            DateTime_SetFormat( GetDlgItem(hwnd,IDC_CONTROL_DTS_LONGDATEFORMAT1 ), TEXT("MMMdd','yyy hh':'m':'s tt"));
            DateTime_SetFormat( GetDlgItem(hwnd,IDC_CONTROL_DTS_LONGDATEFORMAT2 ), TEXT("yyy hh':'mm':'ss tt MMMdd"));
            DateTime_SetFormat( GetDlgItem(hwnd,IDC_CONTROL_DTS_LONGDATEFORMAT3 ), TEXT("dd MMMM','yyy hh':'m tt"));
            DateTime_SetFormat( GetDlgItem(hwnd,IDC_CONTROL_DTS_LONGDATEFORMAT4 ), TEXT("'Today is: 'hh':'m':'s ddddMMMdd', 'yyy"));
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
