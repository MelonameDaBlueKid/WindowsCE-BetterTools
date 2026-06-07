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
// menu.cpp : Defines the entry point for the application.
//

/***************************************************************************
*                                                                         *
*  PROGRAM     : Menu.cpp                                                   *
*                                                                         *
*  PURPOSE     : To give a demonstration of the use of popup menus, user  *
*                defined menus and menu functions.                        *
*                                                                         *
*  FUNCTIONS   : WinMain()           - Calls the initialization function  *
*                                      and enters the Msg loop.       *
*                                                                         *
*                MenuInit()          - Registers the app. window class.   *
*                                                                         *
*                About()             - Dialog function for the About..    *
*                                      dialog.                            *
*                                                                         *
*                HandleCreate()      - Creates a new menu and appends it  *
*                                      to the main menu                   *
*                                                                         *
*                HandlePaint()       - Handles repainting the app's client*
*                                      area                               *
*                                                                         *
*                HandleChangeColors()- Changes the state of the "colors"  *
*                                      menu item.                         *
*                                                                         *
*                HandleDrawItem()    - Redraws the menu items in the      *
*                                      "colors" menu                      *
*                                                                         *
*                HandlePopupMenu()   - handles display of the "floating"  *
*                                      popup.                             *
*                                                                         *
*                MenuWndProc()       - Window function for the app.       *
*                                                                         *
*                                                                         *
***************************************************************************/
#include "stdafx.h"
#include "menu.h"


// Globals
HINSTANCE g_hInst;
HWND g_hWndCB;
HMENU g_hMenuBig;

UINT wce_GetMenuState(
    HMENU hMenu, 
    UINT uId, 
    UINT uFlags
    )
{
    MENUITEMINFO mii;

    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STATE;

    if (uFlags & MF_BYPOSITION) {
        GetMenuItemInfo(hMenu, uId, TRUE, &mii);
    }
    else
    {
        GetMenuItemInfo(hMenu, uId, FALSE, &mii);
    }

    return mii.fState;
}

int wce_GetMenuItemCount(
    HMENU hMenu
    )
{
    const int MAX_NUM_ITEMS = 256;
    int  iPos, iCount;
    
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    
    iCount = 0;
    for (iPos = 0; iPos < MAX_NUM_ITEMS; iPos++)
    {
        if (FALSE == GetMenuItemInfo(hMenu, (UINT)iPos, TRUE, &mii)) 
        {
            break;
        }
        iCount++;
    }
    
    return iCount;
}

UINT wce_GetMenuItemID(
    HMENU hMenu, 
    int nPos
    )    
{	
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(mii));
    mii.cbSize = sizeof(mii); 
    mii.fMask = MIIM_ID; 
    GetMenuItemInfo(hMenu, nPos, TRUE, &mii);
    
    return mii.wID; 
}


BOOL wce_ModifyMenu(
    HMENU hMenu,      // handle of menu 
    UINT uPosition,  // menu item to modify 
    UINT uFlags,     // menu item flags 
    UINT uIDNewItem, // menu item identifier or handle of drop-down menu or submenu 
    LPCTSTR lpNewItem // menu item content 
    )
{
    // Handle MF_BYCOMMAND case
    if (MF_BYPOSITION != (uFlags & MF_BYPOSITION))
    {	
        int nMax = wce_GetMenuItemCount(hMenu);
        int nCount = 0;
        while (uPosition != wce_GetMenuItemID(hMenu, nCount) && (nCount < nMax))
        {
            nCount++;
        }
        uPosition = nCount;
        uFlags |= MF_BYPOSITION;
    }
    
    if (FALSE == DeleteMenu(hMenu, uPosition, uFlags))
    {
        return FALSE;
    }
    
    return InsertMenu(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

/****************************************************************************
*                                                                          *
*  FUNCTION   : WinMain(HANDLE, HANDLE, LPSTR, int)                        *
*                                                                          *
*  PURPOSE    : Creates the main app. window, calls an initialization      *
*               function and enters the Msg loop.                      *
*                                                                          *
****************************************************************************/
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
    )
{
    
    HWND hWnd;
    MSG msg;
    
    UNREFERENCED_PARAMETER( lpCmdLine );
    
    /* Register main window class if this is the first instance of the app. */
    if (!hPrevInstance)
    {
        if (!MenuInit(hInstance))
        {
            return 0;
        }
    }
        
    g_hInst = hInstance;
    
    /* Create the app. window */
    hWnd = CreateWindow (L"Menu App", L"Menu Example", WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        (HWND)NULL, NULL, hInstance, (LPSTR)NULL);
    
    //When the main window is created using CW_USEDEFAULT the height of the menubar (if one
    // is created is not taken into account). So we resize the window after creating it
    // if a menubar is present
    {
        RECT rc;
        GetWindowRect(hWnd, &rc);
        rc.bottom -= MENU_HEIGHT;
        if (g_hWndCB)
        {
            MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);

        }
    }
    
    if (NULL == hWnd)
    {
        return 0;
    }
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return(msg.wParam);
}


/****************************************************************************
*                                                                          *
*  FUNCTION   : MenuInit (hInstance)                                       *
*                                                                          *
*  PURPOSE    : Registers the main window class.                           *
*                                                                          *
*  RETURNS    : TRUE   -  if RegisterClass() went off ok                   *
*               FALSE  -  otherwise.                                       *
*                                                                          *
****************************************************************************/
BOOL MenuInit(
    HINSTANCE hInstance
    )
{
    WNDCLASS wc;
    BOOL     bSuccess;
    
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) MenuWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName	= 0;
    wc.lpszClassName = (LPTSTR) L"Menu App";
    
    bSuccess = RegisterClass (&wc);
    return bSuccess;
}


/****************************************************************************
*                                                                          *
*  FUNCTION   : About (hDlg, Msg, wParam, lParam)                      *
*                                                                          *
*  PURPOSE    : Dialog function for the About menu... dialog.              *
*                                                                          *
****************************************************************************/
BOOL APIENTRY About(
    HWND hDlg,
    UINT Msg,
    UINT wParam,
    LONG lParam
    )
{
    switch (Msg)
    {
    case WM_INITDIALOG:
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
        
    case WM_COMMAND:
        // LOWORD added for portability
        if (IDOK == LOWORD(wParam))
        {
            EndDialog(hDlg,0);
            return(TRUE);
        }
        break;
    }
    return(FALSE);
    UNREFERENCED_PARAMETER(lParam);
}



/****************************************************************************
*                                                                          *
*  FUNCTION   : HandleCreate ( hwnd )                                      *
*                                                                          *
*  PURPOSE    : Creates a new (empty) menu and appends to it the "State"   *
*               menu items. It sets up the user-defined checkmarks for the *
*               menu. It then inserts this menu into the main menu bar.    *
*                                                                          *
****************************************************************************/
VOID APIENTRY HandleCreate(
    HWND hwnd
    )
{
#if _WIN32_WCE > 211 //Pocket PC devices
    //Create a MenuBar for WCE devices
    SHMENUBARINFO mbi;
    memset(&mbi, 0, sizeof(SHMENUBARINFO));
    mbi.cbSize = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hwnd;
    mbi.nToolBarId = IDM_MAIN_MENU;
    mbi.hInstRes = g_hInst;
    mbi.nBmpId = 0;
    mbi.cBmpImages = 0;	
    
    if (FALSE == SHCreateMenuBar(&mbi))
    {
        MessageBox(hwnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
    }
    g_hWndCB = mbi.hwndMB;
    
#else
    g_hWndCB = CommandBar_Create(g_hInst, hwnd, 1);			
    CommandBar_InsertMenubar(g_hWndCB, g_hInst, IDM_MAIN_MENU, 0);
    CommandBar_AddAdornments(g_hWndCB, 0, 0);
    
#endif
    
    return;
}

/****************************************************************************
*                                                                          *
*  FUNCTION   : HandlePaint ( hwnd )                                       *
*                                                                          *
*  PURPOSE    : Handles the repainting of the main app's client area.      *
*                                                                          *
****************************************************************************/
VOID APIENTRY HandlePaint(
    HWND hwnd
    )
{
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rc;
    TCHAR       tszOut[] = TEXT("Tap in the window for a popup menu");
    
    hdc = BeginPaint(hwnd, (LPPAINTSTRUCT)&ps);
    
    /* Center the text in the client area */
    GetClientRect (hwnd, (LPRECT)&rc);
    DrawText (hdc,
        tszOut,
        _tcslen(tszOut),
        (LPRECT)&rc,
        DT_VCENTER | DT_CENTER | DT_SINGLELINE);
    EndPaint(hwnd, (LPPAINTSTRUCT)&ps);
}


/****************************************************************************
*                                                                          *
*  FUNCTION   : HandleChangeColors (hwnd)                                  *
*                                                                          *
*  PURPOSE    : Toggles the state of the Owner Draw item in the Colors     *
*               menu. If it is on, the "Black", "Blue", "Red", and "Green" *
*               individual menu text items are modified so that they will  *
*               contain bands of color. Otherwise, the colors are replaced *
*               by the text.                                               *
*                                                                          *
****************************************************************************/
VOID APIENTRY HandleChangeColors(
    HWND hwnd
    )
{
    HMENU hMenu = NULL;
    BOOL  fOwnerDraw = FALSE;
    
    /* Get a handle to the Colors menu. This is at position 1. */
#if _WIN32_WCE > 211 //Pocket PC devices
    hMenu = (HMENU)SHMenuBar_GetMenu(g_hWndCB, IDM_MAIN_MENUITEM2);
#else
    hMenu =  GetSubMenu(CommandBar_GetMenu(g_hWndCB, 0), IDCOLORS_POS);
#endif
    
    /* Get the current state of the item */
    UINT nState = wce_GetMenuState(hMenu, IDM_COLOROWNERDR, MF_BYCOMMAND);
    
    fOwnerDraw = wce_GetMenuState(hMenu,
        IDM_COLOROWNERDR, MF_BYCOMMAND) & MF_CHECKED;
    
    /* Toggle the state of the item. */
    CheckMenuItem(hMenu,
        IDM_COLOROWNERDR,
        MF_BYCOMMAND | (fOwnerDraw ? MFS_UNCHECKED : MFS_CHECKED));
    
    if (FALSE == fOwnerDraw){
    /* Change the items to owner-draw items. Pass the RGB value for the
     * color as the application-supplied data. This makes it easier for
     * us to draw the items.
     */
        wce_ModifyMenu(hMenu,
            IDM_BLACK,
            MF_OWNERDRAW | MF_BYCOMMAND,
            IDM_BLACK,
            (LPTSTR)RGB (0,0,0));
        
        wce_ModifyMenu(hMenu,
            IDM_BLUE,
            MF_OWNERDRAW | MF_BYCOMMAND,
            IDM_BLUE,
            (LPTSTR)RGB (0,0,255));
        
        wce_ModifyMenu(hMenu,
            IDM_RED,
            MF_OWNERDRAW | MF_BYCOMMAND,
            IDM_RED,
            (LPTSTR)RGB (255,0,0));
        
        wce_ModifyMenu(hMenu,
            IDM_GREEN,
            MF_OWNERDRAW | MF_BYCOMMAND,
            IDM_GREEN,
            (LPTSTR)RGB (0,255,0));
    }
    else 
    {
        /* Change the items to normal text items. */
        wce_ModifyMenu(hMenu, IDM_BLACK, MF_BYCOMMAND, IDM_BLACK, L"Black");
        
        wce_ModifyMenu(hMenu, IDM_BLUE, MF_BYCOMMAND, IDM_BLUE, L"Blue");
        
        wce_ModifyMenu(hMenu, IDM_RED, MF_BYCOMMAND, IDM_RED, L"Red");
        
        wce_ModifyMenu(hMenu, IDM_GREEN, MF_BYCOMMAND, IDM_GREEN, L"Green");
    }
}


/****************************************************************************
*                                                                          *
*  FUNCTION   : HandleDrawItem ( hwnd, lpdis)                              *
*                                                                          *
*  PURPOSE    : Called in response to a WM_DRAWITEM Msg, i.e. when the *
*               colors menu is being modified to an owner-draw menu				 *
*                                                                          *
****************************************************************************/
VOID APIENTRY HandleDrawItem(
    HWND hwnd,
    LPDRAWITEMSTRUCT lpdis
    )
                             
{
    HBRUSH  hbr;
    RECT    rc;
    LONG    checkMarkSize = 0;
    
    if (ODA_DRAWENTIRE == lpdis->itemAction)
    {
        /* Paint the color item in the color requested. */
        hbr = CreateSolidBrush(lpdis->itemData);
        CopyRect((LPRECT)&rc, (LPRECT)&lpdis->rcItem);
        InflateRect((LPRECT)&rc, -10-LOWORD(checkMarkSize), -10);
        FillRect(lpdis->hDC, (LPRECT)&rc, hbr);
        DeleteObject (hbr);
        
    }
    UNREFERENCED_PARAMETER(hwnd);
}

/****************************************************************************
*                                                                          *
*  FUNCTION   : HandlePopupMenu (hwnd, point)                              *
*                                                                          *
*  PURPOSE    : Handles the display of the "floating" popup that appears   *                                                           *
*               on a mouse click in the app's client area.                 *
*                                                                          *
****************************************************************************/
VOID APIENTRY HandlePopupMenu (
    HWND hwnd,
    POINT point
    )
                               
{
    HMENU hMenu;
    HMENU hMenuTrackPopup;
    
    /* Get the menu for the popup from the resource file. */
    hMenu = LoadMenu (g_hInst, MAKEINTRESOURCE(IDM_POPUPMENU));
    if (NULL != hMenu)
    {
        /* Get the first menu in it which we will use for the call to
         * TrackPopup(). This could also have been created on the fly using
         * CreatePopupMenu and then we could have used InsertMenu() or
         * AppendMenu.
         */
        hMenuTrackPopup = GetSubMenu(hMenu, 0);
    
        /* Convert the mouse point to screen coordinates since that is what
         * TrackPopup expects.
         */
        ClientToScreen(hwnd, (LPPOINT)&point);
    
        /* Draw and track the "floating" popup */
        TrackPopupMenu(hMenuTrackPopup, 0, point.x, point.y, 0, hwnd, NULL);
    
        /* Destroy the menu since were are done with it. */
        DestroyMenu(hMenu);
    }
    return; //for completeness
}

/****************************************************************************
*                                                                          *
*  FUNCTION   : MenuWndProc (hWnd, Msg, wParam, lParam)                *
*                                                                          *
*  PURPOSE    : Window function for the main app. window. Processes all the*
*               menu selections and oter messages.                         *
*                                                                          *
****************************************************************************/
LONG APIENTRY MenuWndProc (
    HWND hWnd,
    UINT Msg,
    UINT wParam,
    LONG lParam)
                           
{
    HMENU hMenu;
    RECT rc;
    POINT pt;

    
    switch (Msg)
    {
        
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_EXIT:
            DestroyWindow (hWnd);
            break;
            
        case IDM_ABOUT:
            // Bring up the About.. dialog box 
            DialogBox (g_hInst, L"AboutBox", hWnd, About);
            
            break;
            
        case IDM_COLOROWNERDR:
            /* Change colors in color menu depending on state of this
             * menu item. 
             */
            HandleChangeColors (hWnd);
            break;
            
        case IDM_STATE1:
        case IDM_STATE2:
        case IDM_STATE3:
        case IDM_STATE4:
            // Get a handle to the states menu...
            
#if _WIN32_WCE > 211 //Pocket PC devices
            hMenu = (HMENU)SHMenuBar_GetMenu (g_hWndCB, IDM_MAIN_MENUITEM1);
#else
            hMenu =  GetSubMenu (CommandBar_GetMenu(g_hWndCB, 0), IDSTATES_POS);
#endif
            
            /* Uncheck all the items. */
            CheckMenuItem (hMenu, IDM_STATE1,
                MF_BYCOMMAND | MF_UNCHECKED);
            CheckMenuItem (hMenu, IDM_STATE2,
                MF_BYCOMMAND | MF_UNCHECKED);
            CheckMenuItem (hMenu, IDM_STATE3,
                MF_BYCOMMAND | MF_UNCHECKED);
            CheckMenuItem (hMenu, IDM_STATE4,
                MF_BYCOMMAND | MF_UNCHECKED);
            
            // ...and just check the selected one
            CheckMenuItem (hMenu, (WORD)wParam,
                MF_BYCOMMAND | MF_CHECKED);
            break;
            
        case IDM_BLACK:
        case IDM_RED:
        case IDM_BLUE:
        case IDM_GREEN:
            // Get a handle to the Colors menu.
#if _WIN32_WCE > 211 //Pocket PC devices
            hMenu = (HMENU)SHMenuBar_GetMenu (g_hWndCB, IDM_MAIN_MENUITEM2);
#else
            hMenu =  GetSubMenu (CommandBar_GetMenu(g_hWndCB, 0), IDCOLORS_POS);
#endif
            
            // Uncheck all the items.
            CheckMenuItem (hMenu, IDM_BLACK,
                MF_BYCOMMAND | MF_UNCHECKED);
            CheckMenuItem (hMenu, IDM_RED,
                MF_BYCOMMAND | MF_UNCHECKED);
            CheckMenuItem (hMenu, IDM_BLUE,
                MF_BYCOMMAND | MF_UNCHECKED);
            CheckMenuItem (hMenu, IDM_GREEN,
                MF_BYCOMMAND | MF_UNCHECKED);
            
            // ...and just check the selected one.
            CheckMenuItem (hMenu, (WORD)wParam,
                MF_BYCOMMAND | MF_CHECKED);
            break;
            
        case IDM_FONT:
            /* Messages sent to us from TrackPopupMenu when
             * items are selected from the "floating" popups
             */
            MessageBox (hWnd, L"A font was selected", L"Popup Menu Alert", 
                MB_APPLMODAL|MB_OK);
            break;
            
        case IDM_SIZE:
            MessageBox (hWnd, L"A size was selected", L"Popup Menu Alert",
                MB_APPLMODAL|MB_OK);
            break;
            
        case IDM_STYLE:
            MessageBox (hWnd, L"A style was selected", L"Popup Menu Alert",
                MB_APPLMODAL|MB_OK);
            break;
        }
        break;
        
    case WM_SIZE:
        if (lParam)
        {
            /* If window is being sized to a non zero value...
             * invalidate it's client area.
             */
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
        
    case WM_PAINT:
        HandlePaint(hWnd);
        break;
        
    case WM_MEASUREITEM:
        /* Use the same width for all items. We could examine the item id
         * and use different widths/heights for each item. 
         */
        ((LPMEASUREITEMSTRUCT)lParam)->itemWidth  = MEASUREITEMWIDTH;
        ((LPMEASUREITEMSTRUCT)lParam)->itemHeight = MEASUREITEMHEIGHT;
        return TRUE;
        
    case WM_DRAWITEM:
        // Redraw the "colors" menu in normal/ownerdrawmode
        HandleDrawItem (hWnd,(LPDRAWITEMSTRUCT)lParam);
        return TRUE;
        break;
        
    case WM_CREATE:
        // Create the menu 
        HandleCreate(hWnd);
        break;
        
    case WM_DESTROY:
        //Destroy MenuBar       
        DestroyWindow(g_hWndCB);
        
        PostQuitMessage (0);
        break;
        
    case WM_LBUTTONDOWN:
        // Draw the "floating" popup in the app's client area
        GetClientRect(hWnd, (LPRECT)&rc);
        
        // Temporary porting macro
        LONG2POINT(lParam, pt);
        if (PtInRect((LPRECT)&rc, pt))
        {
            HandlePopupMenu(hWnd, pt);
        }
        break;
        
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
    return(0);
}
