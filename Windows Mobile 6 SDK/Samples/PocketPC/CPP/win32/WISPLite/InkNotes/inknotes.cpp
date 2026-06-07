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
// **************************************************************************
// InkNotes.cpp
// 
// Program to edit and view ink files which can be synced with OneNote.
//
// Copyright Microsoft Corporation, All Rights Reserved
//
// **************************************************************************

#include "Windows.h"
#include "InkNotes.h"
#include "commctrl.h"
#include "aygshell.h"
#include "resource.h"
#include "InkCtrls.h"
#include "PersistentNote.h"
#include "UIHelper.h"

//
// Cached values of GetDeviceCaps(LOGPIXELSX/Y) for the screen DC.
//
int g_HIDPI_LogPixelsX;
int g_HIDPI_LogPixelsY;

#define MAX_LOADSTRING 100




///////////////////////////////////////////////////////////
// Modes
#define INKING_MODE             1
#define HIGHLIGHTER_MODE        2
#define ERASER_MODE             3
#define SELECTION_MODE          4


///////////////////////////////////////////////////////////
// Colors
#define BLUECOLOR               0x00ff0000
#define REDCOLOR                0x000000ff
#define GREENCOLOR              0x0000ff00
#define YELLOWCOLOR             0x0000ffff
#define BLACKCOLOR              0x00000000


///////////////////////////////////////////////////////////
// Pen width
#define PENWIDTHFINE            1.0f
#define PENWIDTHMEDIUM          53.0f
#define PENWIDTHTHICK           100.0f
#define PENWIDTHMARKER          200.0f


///////////////////////////////////////////////////////////
#define INKCTRLSDLL             TEXT("inkctrls.dll")
#define STR_MAILAPP             TEXT("tmail.exe")
#define STR_ATTACH              TEXT("-attach \"%s\"")
#define TOOLBAR_ITEM_COUNT      9

//////////////////////////////////////////////////////////
// Global variables
HINSTANCE   g_hInstance;
HWND        g_hWndToolBar;
HWND        g_hWndIC;
HWND        g_hWndMenuBar;
HANDLE      g_hInkControlDll;

////////////////////////////////////////////////////////
// Canvas related state
PENSTYLE    g_psNormalPen;
PENSTYLE    g_psHighlighterPen;
LONG        g_lZoomLevel = 100;

//
//
// Modes
#define     INKING_MODE         1
#define     HIGHLIGHTER_MODE    2
#define     ERASER_MODE         3
#define     SELECTION_MODE      4

//
// Colors
//
#define     BLACKCOLOR          0x00000000
#define     BLUECOLOR           0x00ff0000
#define     GREENCOLOR          0x0000ff00
#define     REDCOLOR            0x000000ff
#define     YELLOWCOLOR         0x0000ffff


////////////////////////////////////////////////////////
// File related state and defines

#define     BLANK_UNEDITED      1
#define     BLANK_EDITED        2
#define     OPEN_UNEDITED       3
#define     OPEN_EDITED         4

BOOL                g_bFileOpened           = FALSE;
WCHAR               g_wszFileName[MAX_PATH] = {0};
long                g_lAppState             = BLANK_UNEDITED;
CPersistentNote     g_PNote;


////////////////////////////////////////////////////////
// Helper functions for emailing ink data
HRESULT   SendByEmail( LPTSTR lpFile );
void      UpdateZoomButtons();
BOOL      InitInstance(HINSTANCE hInstance, int nCmdShow);



//////////////////////////////////////////////////////////
// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

// Handlers for window messages
LRESULT OnCreate(HWND, WPARAM, LPARAM);
LRESULT OnCommand(HWND, WPARAM, LPARAM);
LRESULT OnNotify(HWND, WPARAM, LPARAM);
LRESULT OnSettingChange(HWND, WPARAM, LPARAM);

// File Menu handlers
LRESULT OnFileOpen(HWND, WPARAM, LPARAM);
LRESULT OnFileSave(HWND, WPARAM, LPARAM);
LRESULT OnFileSend(HWND, WPARAM, LPARAM);
LRESULT OnFileNew(HWND, WPARAM, LPARAM);
LRESULT OnFileClose(HWND, WPARAM, LPARAM);
LRESULT OnFileExit(HWND, WPARAM, LPARAM);

// Edit Menu handlers
LRESULT OnEditCut(HWND, WPARAM, LPARAM);
LRESULT OnEditCopy(HWND, WPARAM, LPARAM);
LRESULT OnEditPaste(HWND, WPARAM, LPARAM);

// Toolbar and menu handlers

// Input modes
LRESULT OnSwitchToInkingMode(HWND, WPARAM, LPARAM);
LRESULT OnSwitchToHighlighterMode(HWND, WPARAM, LPARAM);
LRESULT OnSwitchToEraserMode(HWND, WPARAM, LPARAM);
LRESULT OnSwitchToSelectionMode(HWND, WPARAM, LPARAM);

// Normal pen width
LRESULT OnNormalPenWidthFine(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenWidthMedium(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenWidthThick(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenWidthMarker(HWND, WPARAM, LPARAM);

// Normal pen color
LRESULT OnNormalPenColorBlue(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenColorGreen(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenColorRed(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenColorYellow(HWND, WPARAM, LPARAM);
LRESULT OnNormalPenColorBlack(HWND, WPARAM, LPARAM);

// Highlighter pen color
LRESULT OnHighlighterPenColorYellow(HWND, WPARAM, LPARAM);
LRESULT OnHighlighterPenColorGreen(HWND, WPARAM, LPARAM);

// Zoom and Undo
LRESULT OnZoomIn(HWND, WPARAM, LPARAM);
LRESULT OnZoomOut(HWND, WPARAM, LPARAM);
LRESULT OnUndo(HWND, WPARAM, LPARAM);
LRESULT OnRedo(HWND, WPARAM, LPARAM);



HRESULT GetBitmapFromInkData(VARIANT *pvarData, HBITMAP *phBitMapOut);

///////////////////////////////////////////////////////////
// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    if( FAILED( CoInitializeEx( NULL, 0 ) ) )
    {
        MessageBox( NULL, L"Application Initialization failed.", L"Ink Notes", MB_OK );
        return( 0 );
    }


    if( !InitInstance(hInstance, nCmdShow) )
    {
        return 0;
    }


    //
    // Application message loop
    //
    while( 0 < GetMessage( &msg, NULL, 0, 0 ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }


    CoUninitialize();

    return( 0 );
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = 0;
    wc.lpszClassName = szWindowClass;

    return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE:  Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    TCHAR szTitle[MAX_LOADSTRING];		// title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];	// main window class name
    INITCOMMONCONTROLSEX icex;

    g_hInstance = hInstance; // Store instance handle in our global variable


    //
    // Load the inkcontrols library
    //
    g_hInkControlDll = ::LoadLibrary(INKCTRLSDLL);
    if(! g_hInkControlDll)
    {
        return FALSE;
    }

    icex.dwSize = sizeof( INITCOMMONCONTROLSEX );
    icex.dwICC = ICC_COOL_CLASSES;
    InitCommonControlsEx( &icex );

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the device specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    HIDPI_InitScaling();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_INKNOTES, szWindowClass, MAX_LOADSTRING);

    //If it is already running, then focus on the window, and exit
    hWnd = FindWindow(szWindowClass, szTitle);	
    if (hWnd) 
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        exit(0);
    } 

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
        MessageBox( NULL, L"Error occured in initializing application", NULL, 0 );
        return FALSE;
    }

    hWnd = CreateWindow(szWindowClass, 
                        szTitle, 
                        WS_VISIBLE,
                        CW_USEDEFAULT, 
                        CW_USEDEFAULT, 
                        CW_USEDEFAULT, 
                        CW_USEDEFAULT, 
                        NULL, 
                        NULL, 
                        hInstance, 
                        NULL);

    if (!hWnd)
    {
        MessageBox( NULL, L"Error occured in initializing application", NULL, 0 );
        return FALSE;
    }


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc
//
//  PURPOSE:  The window messages handler for our application's window class
//
//  COMMENTS: 
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = 0;
    switch(wMsg)
    {
    case WM_CREATE:
        lr = OnCreate(hWnd, wParam, lParam);
        break;

    case WM_COMMAND:
        lr = OnCommand(hWnd, wParam, lParam);
        break;

    case WM_NOTIFY:
        lr = OnNotify(hWnd, wParam, lParam);
        break;

    case WM_SETTINGCHANGE:
        lr = OnSettingChange(hWnd, wParam, lParam);
        break;
    
    default:
        lr = DefWindowProc(hWnd, wMsg, wParam, lParam);
    }
    return lr;
}



//
//  FUNCTION: CreateToolBar
//
//  PURPOSE:  Create the application toolbar
//
//  COMMENTS: 
//
BOOL CreateToolBar(HWND hWnd)
{
    TBBUTTON tbButton[TOOLBAR_ITEM_COUNT] = 
    {   
        {0, IDT_INKINGMODE,      (BYTE)(TBSTATE_ENABLED | TBSTATE_CHECKED), (BYTE)(WS_TABSTOP | TBSTYLE_CHECKGROUP | TBSTYLE_DROPDOWN), 0, 0},
        {1, IDT_HIGHLIGHTERMODE, (BYTE)TBSTATE_ENABLED,                     (BYTE)(WS_TABSTOP | TBSTYLE_CHECKGROUP | TBSTYLE_DROPDOWN), 0, 0},
        {2, IDT_ERASERMODE,      (BYTE)TBSTATE_ENABLED,                     (BYTE)(WS_TABSTOP | TBSTYLE_CHECKGROUP),                    0, 0},
        {3, IDT_SELECTIONMODE,   (BYTE)TBSTATE_ENABLED,                     (BYTE)(WS_TABSTOP | TBSTYLE_CHECKGROUP),                    0, 0},
        {0, 0,                   0,                                         (BYTE)TBSTYLE_SEP,                                          0, 0 },
        {4, IDT_ZOOMIN,          (BYTE)TBSTATE_ENABLED,                     (BYTE)WS_TABSTOP,                                           0, 0},
        {5, IDT_ZOOMOUT,         (BYTE)TBSTATE_ENABLED,                     (BYTE)WS_TABSTOP,                                           0, 0},
        {6, IDT_UNDO,            0,                                         (BYTE)WS_TABSTOP,                                           0, 0},
        {7, IDT_REDO,            0,                                         (BYTE)WS_TABSTOP,                                           0, 0}
    };
        
    //
    // Create a tool bar
    //
    int idBitmapToolBar = g_HIDPI_LogPixelsX == 96 ? IDB_TOOLBAR96 : IDB_TOOLBAR192;

    g_hWndToolBar = CreateToolbarEx( hWnd, 
                                    WS_CHILD | WS_CLIPCHILDREN | WS_BORDER | WS_VISIBLE | WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_BOTTOM, 
                                    (UINT)ID_TOOLBAR, 
                                    TOOLBAR_ITEM_COUNT, 
                                    g_hInstance, 
                                    idBitmapToolBar, 
                                    tbButton, 
                                    TOOLBAR_ITEM_COUNT, 
                                    SCALEX(16), 
                                    SCALEY(16), 
                                    SCALEX(16), 
                                    SCALEY(16), 
                                    sizeof(TBBUTTON));

    return (IsWindow(g_hWndToolBar));
}


//
//  FUNCTION: InitializeCanvas
//
//  PURPOSE:  Initialize the pen styles of the canvas
//
//  COMMENTS: This function also enables auto-scrolling of the canvas
//
void InitializeCanvas()
{
    // Initialize the normal pen style
    g_psNormalPen.cbSize = sizeof(g_psNormalPen);
    g_psNormalPen.crColor = BLUECOLOR;
    g_psNormalPen.dPenWidth = PENWIDTHMEDIUM;
    g_psNormalPen.ptPenType = IC_PENTYPE_NORMAL;
    SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen);
    
    // Initialize the highlighter pen style
    g_psHighlighterPen.cbSize = sizeof(g_psHighlighterPen);
    g_psHighlighterPen.crColor = YELLOWCOLOR;
    g_psHighlighterPen.dPenWidth = PENWIDTHMARKER;
    g_psHighlighterPen.ptPenType = IC_PENTYPE_HIGHLIGHTER;

    // Set the zoom level
    g_lZoomLevel = 100;

    SendMessage(g_hWndIC, ICM_SETAUTOSCROLL, (WPARAM)VARIANT_TRUE, 0 );
}


//
//  FUNCTION: OnCreate
//
//  PURPOSE:  Hanlder for the WM_CREATE message
//
//  COMMENTS: Create a toolbar and the canvas window for inking
//
LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

    SHMENUBARINFO   smbi;
    SIPINFO         si;

    memset( &smbi, 0, sizeof( SHMENUBARINFO ) );
    smbi.cbSize = sizeof( SHMENUBARINFO );
    smbi.hwndParent = hWnd;
    smbi.nToolBarId = IDM_MAINMENU;
    smbi.hInstRes = g_hInstance;
  
    if( !SHCreateMenuBar( &smbi ) )
    {
        return -1;
    }
    else
    {
        g_hWndMenuBar = smbi.hwndMB;
    }

    // 
    memset( &si, 0, sizeof( SIPINFO ) );
    si.cbSize = sizeof( SIPINFO );
    SHSipInfo( SPI_GETSIPINFO, 0, (PVOID)&si, FALSE );
    int iDx = si.rcVisibleDesktop.right - si.rcVisibleDesktop.left;
    int iDy = si.rcVisibleDesktop.bottom - si.rcVisibleDesktop.top;

    RECT rcMB;
    GetWindowRect( g_hWndMenuBar, &rcMB );
    iDy -= ( rcMB.bottom - rcMB.top );

    SetWindowPos( hWnd, NULL, 0, 0, iDx, iDy, SWP_NOMOVE | SWP_NOZORDER );
   
    // Creat the toolbar
    if( !CreateToolBar(hWnd) )
    {
        return -1;
    }

    ShowWindow( smbi.hwndMB, SW_SHOW );


    RECT rcTB;
    GetWindowRect( g_hWndToolBar, &rcTB );

    // Create the canvas window
    g_hWndIC = CreateWindow(WC_INKCANVAS, 
                            NULL, 
                            WS_VISIBLE | WS_CHILD | WS_HSCROLL | WS_VSCROLL, 
                            0, 
                            0, 
                            iDx, 
                            iDy - rcTB.bottom + rcTB.top + SCALEY(1), 
                            hWnd, 
                            NULL, 
                            g_hInstance, 
                            NULL);

    ASSERT(IsWindow(g_hWndIC));
    if(! IsWindow(g_hWndIC))
    {
        return -1;
        
    }
    SetFocus(g_hWndIC);

    // Initialize the canvas
    InitializeCanvas();

    // Subscribe to the strokes added/deleted notifications
    LONG lNotificationMask = ICMASK_DEFAULT | ICMASK_STROKEADDED | ICMASK_STROKEDELETED;
    ::SendMessage(g_hWndIC, ICM_SETNOTIFICATIONMASK, lNotificationMask, 0);

    return( 0 );
}




//
//  FUNCTION: OnCommand
//
//  PURPOSE:  Hanlder for the WM_COMMAND message
//
//  COMMENTS: Dispatch the appropriate handlers depending on the command received
//
LRESULT OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = 0;
    UINT uiCommand = (UINT) LOWORD(wParam);
    WPARAM wCode = (WPARAM) HIWORD(wParam);

    switch(uiCommand)
    {
        //
        // File menu message handlers
        //

    case IDM_OPEN:
        lr = OnFileOpen(hWnd, wCode, lParam);
        break;
    case IDM_SAVE:
        lr = OnFileSave(hWnd, wCode, lParam);
        break;

    case IDM_EMAIL:
        lr = OnFileSend(hWnd, wCode, lParam);
        break;
    
    case IDM_NEW: 
        lr = OnFileNew(hWnd, wCode, lParam);
        break;
    
    case IDM_EXIT: 
       lr = OnFileExit(hWnd, wCode, lParam);
        break;

        //
        // Edit menu message handlers
        //
    
    case IDM_CUT:
        lr = OnEditCut(hWnd, wCode, lParam);
        break;

    case IDM_COPY:
        lr = OnEditCopy(hWnd, wCode, lParam);
        break;

    case IDM_PASTE:
        lr = OnEditPaste(hWnd, wCode, lParam);
        break;

        //
        // Toolbar button message handlers
        //

    case IDT_INKINGMODE:
        lr = OnSwitchToInkingMode(hWnd, wCode, lParam);
        break;

    case IDT_HIGHLIGHTERMODE:
        lr = OnSwitchToHighlighterMode(hWnd, wCode, lParam);
        break;

    case IDT_ERASERMODE:
        lr = OnSwitchToEraserMode(hWnd, wCode, lParam);
        break;

    case IDT_SELECTIONMODE:
        lr = OnSwitchToSelectionMode(hWnd, wCode, lParam);
        break;

    case IDT_ZOOMIN:
        lr = OnZoomIn(hWnd, wCode, lParam);
        break;

    case IDT_ZOOMOUT:
        lr = OnZoomOut(hWnd, wCode, lParam);
        break;
    
    case IDT_UNDO: 
        lr = OnUndo(hWnd, wCode, lParam);
        break;

    case IDT_REDO: 
        lr = OnRedo(hWnd, wCode, lParam);
        break;

        //
        // Pen settings for normal pen
        //
    case IDM_PWFINE:
        lr = OnNormalPenWidthFine(hWnd, wCode, lParam);
        break;

    case IDM_PWMEDIUM:
        lr = OnNormalPenWidthMedium(hWnd, wCode, lParam);
        break;

    case IDM_PWTHICK:
        lr = OnNormalPenWidthThick(hWnd, wCode, lParam);
        break;

    case IDM_PWMARKER:
        lr = OnNormalPenWidthMarker(hWnd, wCode, lParam);
        break;
        
    case IDM_PCPBLUE:
        lr = OnNormalPenColorBlue(hWnd, wCode, lParam);
        break;

    case IDM_PCPGREEN:
        lr = OnNormalPenColorGreen(hWnd, wCode, lParam);
        break;

    case IDM_PCPRED:
        lr = OnNormalPenColorRed(hWnd, wCode, lParam);
        break;

    case IDM_PCPYELLOW:
        lr = OnNormalPenColorYellow(hWnd, wCode, lParam);
        break;

    case IDM_PCPBLACK:
        lr = OnNormalPenColorBlack(hWnd, wCode, lParam);
        break;

        //
        // Pen settings for highlighter pen
        //
    case IDM_PCHYELLOW:
        lr = OnHighlighterPenColorYellow(hWnd, wCode, lParam);
        break;

    case IDM_PCHGREEN:
        lr = OnHighlighterPenColorGreen(hWnd, wCode, lParam);
        break;

    default:
        break;

    }
    return lr;
}


//
//  FUNCTION: OnSettingChange
//
//  PURPOSE:  Handler for the WM_SETTINGCHANGE message
//
//  COMMENTS: Update the size and position of this window and that of the canavs
//
LRESULT OnSettingChange(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (SETTINGCHANGE_RESET == wParam) 
    {
        // An orientation change occurred. This is where we
        // perform processing that you cannot perform in WM_SIZE, 
        // such as resizing full-screen child windows, calling 
        // MoveWindow on the top-level window, and so on.

        SIPINFO si;

        memset( &si, 0, sizeof( SIPINFO ) );
        si.cbSize = sizeof( SIPINFO );
        SHSipInfo( SPI_GETSIPINFO, 0, (PVOID)&si, FALSE );
        int iDx = si.rcVisibleDesktop.right - si.rcVisibleDesktop.left;
        int iDy = si.rcVisibleDesktop.bottom - si.rcVisibleDesktop.top;


        // Get the menubar size
        RECT rcMB;
        HWND hWndMenuBar = ::SHFindMenuBar(hWnd);
        GetWindowRect( hWndMenuBar, &rcMB );
        iDy -= ( rcMB.bottom - rcMB.top );
        
        //// Move the toolbar. The arguments supplied do not matter
        ::MoveWindow( g_hWndToolBar, 0, 0, 0, 0, TRUE);

        // Get the toolbar size
        RECT rcTB;
        GetWindowRect( g_hWndToolBar, &rcTB );

        // Move the window appropriately
        ::MoveWindow( g_hWndIC, 0, 0, iDx, iDy - rcTB.bottom + rcTB.top + SCALEY(1), TRUE);

    }

    return( 0 );
}


//
//  FUNCTION: UpdateUndoButton
//
//  PURPOSE:  Enable/disable the undo button
//
//  COMMENTS: Query the canvas if undo can be performed and update the button accordingly
//
void UpdateUndoButton()
{
    BOOL bEnable = ( 0 != SendMessage( g_hWndIC, ICM_CANUNDO, 0, 0 ));
    SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_UNDO, MAKELONG(bEnable, 0 ));
}


//
//  FUNCTION: UpdateRedoButton
//
//  PURPOSE:  Enable/disable the redo button
//
//  COMMENTS: Query the canvas if Redo can be performed and update the button accordingly
//
void UpdateRedoButton()
{
    BOOL bEnable = ( 0 != SendMessage( g_hWndIC, ICM_CANREDO, 0, 0 ));
    SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_REDO, MAKELONG(bEnable, 0 ));
}


//
//  FUNCTION: OnNotify
//
//  PURPOSE:  Handler for the WM_NOTIFY message. 
//
//  COMMENTS: Create menu for manipulating ink width/color and update undo/redo buttons
//
LRESULT OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR     pNotifyHeader;
    LPNMTOOLBAR pNotifyToolbar;
    RECT        rect;
    TPMPARAMS   tpm;
    HMENU       hMenu;

    pNotifyHeader = (LPNMHDR) lParam;

    if( ICNM_STROKEADDED == pNotifyHeader->code || ICNM_STROKEDELETED == pNotifyHeader->code )
    {
        if( OPEN_UNEDITED == g_lAppState )
        {
            g_lAppState = OPEN_EDITED;
        }
        else if( BLANK_UNEDITED == g_lAppState )
        {
            g_lAppState = BLANK_EDITED;
        }

        UpdateUndoButton();
        UpdateRedoButton();
        return 0;
    }

    if( TBN_DROPDOWN == pNotifyHeader->code )
    {
        pNotifyToolbar = (LPNMTOOLBAR) lParam;

        if( IDT_INKINGMODE == pNotifyToolbar->iItem )
        {
            SendMessage( pNotifyHeader->hwndFrom, TB_GETRECT, pNotifyToolbar->iItem, (LPARAM) &rect );

            MapWindowPoints( pNotifyHeader->hwndFrom, HWND_DESKTOP, (LPPOINT) &rect, 2 );

            tpm.cbSize = sizeof( tpm );

            CopyRect( &tpm.rcExclude, &rect );

            hMenu = GetSubMenu( LoadMenu( g_hInstance, TEXT("NORMALPEN_POPUP") ), 0 );

            TrackPopupMenuEx( hMenu, TPM_LEFTALIGN | TPM_VERTICAL, rect.left, rect.bottom, hWnd, &tpm );
        }
        else if( IDT_HIGHLIGHTERMODE == pNotifyToolbar->iItem )
        {
            SendMessage( pNotifyHeader->hwndFrom, TB_GETRECT, pNotifyToolbar->iItem, (LPARAM) &rect );

            MapWindowPoints( pNotifyHeader->hwndFrom, HWND_DESKTOP, (LPPOINT) &rect, 2 );

            tpm.cbSize = sizeof( tpm );

            CopyRect( &tpm.rcExclude, &rect );

            hMenu = GetSubMenu( LoadMenu( g_hInstance, TEXT("HIGHLIGHTERPEN_POPUP") ), 0 );

            TrackPopupMenuEx( hMenu, TPM_LEFTALIGN | TPM_VERTICAL, rect.left, rect.bottom, hWnd, &tpm );
        }
    }

    return( 0 );
}



//
//  FUNCTION: OnFileOpen
//
//  PURPOSE:  Opens a note file
//
//  COMMENTS: 
//
LRESULT OnFileOpen(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HRESULT             hr = S_OK;
    OPENFILENAME        of;
    WCHAR               szFileName[255] = {0};
    VARIANT             variant;
    LPCTSTR             pszOpenFilter = L"Ink notes files (*.ink)\0*.ink\0\0";

    memset( &of, 0, sizeof( of ) );
    of.lStructSize = sizeof( of );
    of.hwndOwner = hWnd;
    of.lpstrFile = szFileName;
    of.nMaxFile = 255;
    of.lpstrFilter = pszOpenFilter;
    of.Flags = 0;
    
    if( OPEN_EDITED == g_lAppState || BLANK_EDITED == g_lAppState )
    {
        // Confirm if the user wants to save changes.
    }

    if( IDOK == GetOpenFileName( &of ) )
    {
        
        hr = StringCchCopy( g_wszFileName, MAX_PATH, szFileName);
        if(FAILED(hr))
        {
            goto Error;
        }
        
        // Clear the previous data
        g_PNote.Clear();

        // Load the supplied file name
        hr = g_PNote.LoadFromFile( g_wszFileName );
        if(FAILED(hr))
        {
            goto Error;
        }

        ::VariantInit(&variant);
        V_VT(&variant) = VT_BSTR;
        g_PNote.get_InkData(&variant.bstrVal);
   
        // Load the ink data into the canvas
        LRESULT lr = SendMessage(g_hWndIC, ICM_LOADINKDATA, (WPARAM)0, (LPARAM)&variant);
        
        SysFreeString(variant.bstrVal);
        ::VariantClear(&variant);

        if(0 == lr)
        {               

            hr = (HRESULT)::GetLastError();
            goto Error;
        }
        else
        {
            hr = S_OK;
        }        

        //
        // If the file is succesfully loaded, reset the global state
        //
        if( SUCCEEDED(hr))
        {
            g_bFileOpened = true;
            g_lAppState = OPEN_UNEDITED;
            g_lZoomLevel = 100;
            UpdateZoomButtons();
            UpdateUndoButton();
            UpdateRedoButton();
        }
    }
Error:
    if(FAILED(hr))
    {
        MessageBox(NULL, L"Error in loading file", L"Critical Error", MB_OK);
    }
    return 0;    
}

//
//  FUNCTION: GetFileTitleBSTR
//
//  PURPOSE:  Returns the title of a file as a BSTR
//
//  COMMENTS: The title of the file is merely it's name sans the file path
//            and the extension name
//
void GetFileTitleBSTR(LPCTSTR szFileName, BSTR* pbstrTitle)
{
    // Remove the path component and the extension component from szFileName
    
    // Get the index of the last '/' and the index of the last '.'
    size_t dwLen = 0;
    ::StringCchLengthW( szFileName, MAX_PATH, &dwLen );
    LONG lSlash = 0;
    LONG lPeriod = 0;
    BOOL bPeriodNotFound = TRUE;
    for(int i = dwLen -1; i>=0; i--)
    {

        if( bPeriodNotFound && szFileName[i] == '.')
        {
            lPeriod = i;
            bPeriodNotFound = FALSE;
        }
        if( szFileName[i] == '\\' )
        {
            // We should have found a valid period
            ASSERT( FALSE == bPeriodNotFound );
            lSlash = i;
            break;
        }
    }
    WCHAR sztitle[MAX_PATH]={0};
    for(int i = lSlash + 1, ti = 0; i<lPeriod; i++, ti++)
    {
        sztitle[ti] = szFileName[i];
    }
    ASSERT(NULL != pbstrTitle);
    *pbstrTitle = ::SysAllocString(sztitle);
    
    return;
}

//
//  FUNCTION: GetInkData
//
//  PURPOSE:  Returns the base64 encoded ink data 
//
//  COMMENTS: This function is used while saving a file
//
HRESULT GetInkData(BSTR *pbstrInkData)
{
    HRESULT hr = S_OK;
    LRESULT lr = 0;
    ASSERT(NULL != pbstrInkData);
    VARIANT Data;
    
    // Get the base64 encoded ink data
    VariantInit( &Data );
    lr = SendMessage(g_hWndIC, ICM_GETINKDATA, (WPARAM)IC_INKENCODING_BASE64, (LPARAM)&Data);

    if( 0 == lr )
    {
        hr = (HRESULT)::GetLastError();
    }
    else
    {
        *pbstrInkData = Data.bstrVal;
        ::VariantClear( &Data );
    }

    return hr;
}

//
//  FUNCTION: OnFileSave
//
//  PURPOSE:  Saves the ink to a file
//
//  COMMENTS: 
//
LRESULT OnFileSave(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HRESULT             hr = S_OK;
    OPENFILENAME        of;
    TCHAR               szFileName[MAX_PATH] = {0};
    const LPTSTR        pszOpenFilter = L"Ink Notes files (*.ink)\0*.ink\0\0";
    BOOL                bOpenedFile = FALSE;

    szFileName[0] = '\0';
    memset( &of, 0, sizeof( of ) );
    of.lStructSize = sizeof( of );
    of.hwndOwner = hWnd;
    of.lpstrFile = szFileName;
    of.nMaxFile = 255;
    of.lpstrFilter = pszOpenFilter;
    of.Flags = 0;

    // If the notes page isn't edited, we needn't save at all
    if( OPEN_UNEDITED == g_lAppState || BLANK_UNEDITED == g_lAppState )
    {
        return 1;
    }


    if( BLANK_EDITED == g_lAppState)
    {
        // We haven't opened a fileName
        bOpenedFile = GetSaveFileName( &of );
        if( bOpenedFile )
        {
            StringCchCopy(g_wszFileName, MAX_PATH, szFileName);
        }
    }
    else
    {
        ASSERT( OPEN_EDITED == g_lAppState );
        StringCchCopy(szFileName, MAX_PATH, g_wszFileName);
        bOpenedFile = TRUE;
    }

    
    if( bOpenedFile )
    {
        
        //
        // Associate the ink with the note
        //
        BSTR bstrInkData = NULL;
        hr = GetInkData( &bstrInkData );
        if(FAILED(hr))
        {
            goto Error;
        }

        hr = g_PNote.put_InkData(bstrInkData);
        if(FAILED(hr))
        {
            goto Error;
        }
        ::SysFreeString(bstrInkData);

        //
        // Set the title of the note
        //
        BSTR bstrTitle = NULL;
        GetFileTitleBSTR( szFileName, &bstrTitle);
        hr = g_PNote.put_Title( bstrTitle);
        ::SysFreeString(bstrTitle);

        //
        // Set the guid of the page
        //
        GUID pageGUID = {0};
        CoCreateGuid( &pageGUID );
        WCHAR* szPageGUID = NULL;
        StringFromCLSID( pageGUID, &szPageGUID );
        BSTR bstrPageGuid = ::SysAllocString(szPageGUID);
        g_PNote.put_PageGuid(bstrPageGuid);
        ::CoTaskMemFree(szPageGUID);
        ::SysFreeString(bstrPageGuid);

        //
        // Set the guid of the object
        //
        GUID objGUID = {0};
        CoCreateGuid(&objGUID);
        WCHAR* szGuid = NULL;
        StringFromCLSID(objGUID, &szGuid);
        BSTR bstrGuid = ::SysAllocString(szGuid);
        g_PNote.put_ObjectGuid(bstrGuid);
        ::CoTaskMemFree(szGuid);
        ::SysFreeString(bstrGuid);

        // Finally save the note to the supplied filename
        hr = g_PNote.SaveToFile( szFileName );
        if(FAILED(hr))
        {
            MessageBox(NULL, L"Error in saving file", 0, MB_OK);
        }
        else
        {
            g_lAppState = OPEN_UNEDITED;
            g_bFileOpened = TRUE;
        }
        
    }
    else
    {

        // Get open file name failed or was cancelled

        DWORD dwLastError = GetLastError();

        if( dwLastError != 0 )
        {
            MessageBox( NULL, L"Error in saving file", 0, MB_OK );
        }
        SetFocus(g_hWndIC);

    }

Error:

    return 0;
}


//
//  FUNCTION: OnFileNew
//
//  PURPOSE:  Create a new canvas on which we can ink
//
//  COMMENTS: 
//
LRESULT OnFileNew(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = 0;
    lr = SendMessage(g_hWndIC, ICM_CLEARCANVAS, 0, 0);
    g_bFileOpened = FALSE;
    g_lZoomLevel = 100;
    
    if(BLANK_EDITED == g_lAppState || OPEN_EDITED == g_lAppState)
    {
        // We may want to ask the user to save notes here.
    }

    // Change the global canvas state
    g_lAppState = BLANK_UNEDITED;

    UpdateZoomButtons();
    UpdateUndoButton();
    UpdateRedoButton();

    g_PNote.Clear();

    return lr;
}

//
//  FUNCTION: SendByEmail
//
//  PURPOSE:  Start outlook to send an email with a file attachment.
//
//  COMMENTS: 
//
HRESULT SendByEmail( LPTSTR lpFile )
{
    HRESULT hr = S_OK;
    TCHAR szCmdLine[MAX_PATH];

    
    SHELLEXECUTEINFO sei = {0};
    sei.cbSize = sizeof(sei);
    sei.lpFile =  STR_MAILAPP;
    sei.nShow = SW_SHOWNORMAL;
    if( lpFile )
    {
        StringCchPrintf(szCmdLine, MAX_PATH, STR_ATTACH, lpFile);
    }
    sei.lpParameters = szCmdLine;
    
    if(!ShellExecuteEx(&sei))
    {
        hr = S_FALSE;
    }
    return hr;
}



//
//  FUNCTION: OnFileSend
//
//  PURPOSE:  Sends the current ink object as a GIF file attachment
//
//  COMMENTS: Obtain the ink data in a GIF file and email it
//
LRESULT OnFileSend(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    VARIANT     Data;
    LRESULT     lr = 0;
    HRESULT     hr = S_OK;
    DWORD       dwWrittenSize;
    WCHAR       szTempPath[MAX_PATH];
    WCHAR       szTempFile[MAX_PATH];
    HANDLE      hFileTemp = NULL;
    SAFEARRAY*  pSA = NULL;

    VariantInit( &Data );

    lr = SendMessage(g_hWndIC, ICM_GETINKDATA, (WPARAM)IC_INKENCODING_GIF, (LPARAM)&Data);


    ::GetTempPath( MAX_PATH, szTempPath );
    ::GetTempFileName( szTempPath, L"inknote", 0, szTempFile );


    hFileTemp = CreateFile( szTempFile,
                            GENERIC_WRITE, 
                            0, 
                            NULL, 
                            CREATE_ALWAYS, 
                            FILE_ATTRIBUTE_NORMAL, 
                            NULL );    

    ASSERT(NULL != hFileTemp);

    // Get the safe array from the variant data
    pSA = V_ARRAY(&Data);

    unsigned char *pBytes = NULL;
    hr = ::SafeArrayAccessData(pSA, (void HUGEP **)&pBytes);
    if(FAILED(hr))
    {
        ::SafeArrayDestroy(pSA);
        MessageBox( 0, L"Unable to send file", 0, 0 );
        SetFocus(g_hWndIC);
        goto End;
    }

    //
    // Write to file
    //
    WriteFile( hFileTemp, pBytes, pSA->rgsabound->cElements, &dwWrittenSize, NULL );

    hr = ::SafeArrayUnaccessData(pSA);
    if(FAILED(hr))
    {
        ::SafeArrayDestroy(pSA);
        MessageBox( 0, L"Unable to send file", 0, 0 );
        SetFocus(g_hWndIC);
        goto End;
    }

    //
    // Close the open file, e-mail it and delete it.
    //
    CloseHandle(hFileTemp);
    SendByEmail(szTempFile);
    DeleteFile(szTempFile);

End:
    return 0;
}

//
//  FUNCTION: OnFileExit
//
//  PURPOSE:  Exits the current application
//
//  COMMENTS: 
//
LRESULT OnFileExit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage( 0 );
    return( 0 );
}


//
//  FUNCTION: OnEditCut
//
//  PURPOSE:  Cut the selected strokes
//
//  COMMENTS: 
//
LRESULT OnEditCut(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return SendMessage(g_hWndIC, WM_CUT, 0, 0);
}

//
//  FUNCTION: OnEditCopy
//
//  PURPOSE:  Copy the selected strokes
//
//  COMMENTS: 
//
LRESULT OnEditCopy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return SendMessage(g_hWndIC, WM_COPY, 0, 0);
}


//
//  FUNCTION: OnEditPaste
//
//  PURPOSE:  Paste the selected strokes
//
//  COMMENTS: 
//
LRESULT OnEditPaste(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return SendMessage(g_hWndIC, WM_PASTE, 0, 0);
}


//
//  FUNCTION: OnSwitchToInkingMode
//
//  PURPOSE:  Change the input mode to inking mode
//
//  COMMENTS: 
//
LRESULT OnSwitchToInkingMode(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.ptPenType = IC_PENTYPE_NORMAL;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen);
    return( 0 );
}

//
//  FUNCTION: OnSwitchToHighlighterMode
//
//  PURPOSE:  Change the input mode to highlighter pen mode
//
//  COMMENTS: 
//
LRESULT OnSwitchToHighlighterMode(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psHighlighterPen);
    return( 0 );
}

//
//  FUNCTION: OnSwitchToEraserMode
//
//  PURPOSE:  Switch to eraser mode
//
//  COMMENTS: 
//
LRESULT OnSwitchToEraserMode(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_DELETE, 0); 
    return( 0 );
}

//
//  FUNCTION: OnSwitchToSelectionMode
//
//  PURPOSE:  Change the current mode to selection
//
//  COMMENTS: 
//
LRESULT OnSwitchToSelectionMode(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_SELECT, 0); 
    return( 0 );
}



//
//  FUNCTION: UpdateZoomButtons
//
//  PURPOSE:  Update the zoom buttons depending on the current global zoom level
//
//  COMMENTS: 
//
void UpdateZoomButtons()
{
    //
    // Disable the zoom in button if we're at max zooming level else enable it
    //
    if( g_lZoomLevel >= 500 )
    {
        SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_ZOOMIN, MAKELONG( FALSE, 0 ));
    }
    else
    {
        SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_ZOOMIN, MAKELONG( TRUE, 0 ));
    }

    //
    // Disable the zoom in button if we're at min zooming level else enable it
    //
    if( g_lZoomLevel <= 20 )
    {
        SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_ZOOMOUT, MAKELONG( FALSE, 0 ));
    }
    else
    {
        SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_ZOOMOUT, MAKELONG( TRUE, 0 ));
    }

    return;
}

//
//  FUNCTION: OnZoomIn
//
//  PURPOSE:  Zoom in if it's possible and update the zoom buttons
//
//  COMMENTS: 
//
LRESULT OnZoomIn(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int newZoom = 0;
    newZoom = g_lZoomLevel + (g_lZoomLevel < 100 ? 20 : 100 );
    
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETZOOM, (WPARAM) newZoom, 0);
    if( lr )
    {
        g_lZoomLevel = newZoom;
        UpdateZoomButtons();
    }
    return 0;
}


//
//  FUNCTION: OnZoomOut
//
//  PURPOSE:  Zoom out if it's possible and update the zoom buttons
//
//  COMMENTS: 
//
LRESULT OnZoomOut(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int newZoom = 0;

    newZoom = g_lZoomLevel - (g_lZoomLevel <= 100 ? 20 : 100 );
    
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETZOOM, (WPARAM) newZoom, 0);
    if( lr )
    {
        g_lZoomLevel = newZoom;
        UpdateZoomButtons();
    }
    return 0;
}

//
//  FUNCTION: OnUndo
//
//  PURPOSE:  Undo the last action and update the buttons
//
//  COMMENTS: 
//
LRESULT OnUndo(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = 0;
    lr = SendMessage( g_hWndIC, WM_UNDO, 0, 0);
    UpdateUndoButton();
    UpdateRedoButton();
    return lr;
}

//
//  FUNCTION: OnRedo
//
//  PURPOSE:  Redo the last action and update the buttons
//
//  COMMENTS:
//
LRESULT OnRedo(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT lr = 0;
    lr = SendMessage( g_hWndIC, ICM_REDO, 0, 0);
    UpdateUndoButton();
    UpdateRedoButton();
    return lr;
}




//
//  FUNCTION: EnableButton
//
//  PURPOSE:  Enable the supplied button and disable the otherone
//
//  COMMENTS: 
void EnableButton(long lBtn)
{
    BOOL bInkButton = IDT_INKINGMODE == lBtn;
    BOOL bHighlighterButton = IDT_HIGHLIGHTERMODE == lBtn;

    SendMessage( g_hWndToolBar, TB_CHECKBUTTON, (WPARAM)IDT_INKINGMODE, MAKELONG(bInkButton, 0 ));
    SendMessage( g_hWndToolBar, TB_CHECKBUTTON, (WPARAM)IDT_HIGHLIGHTERMODE, MAKELONG(bHighlighterButton, 0 ));

    // Uncheck the selection and the eraser buttom
    SendMessage( g_hWndToolBar, TB_CHECKBUTTON, (WPARAM)IDT_ERASERMODE, MAKELONG(FALSE, 0 ));
    SendMessage( g_hWndToolBar, TB_CHECKBUTTON, (WPARAM)IDT_SELECTIONMODE, MAKELONG(FALSE, 0 ));
}


//
//  FUNCTION: OnNormalPenWidhtFine
//
//  PURPOSE:  Enable the supplied button and disable the otherone
//
//  COMMENTS: 
//
LRESULT OnNormalPenWidthFine(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.dPenWidth = PENWIDTHFINE;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0 );
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnNormalPenWidthMedium
//
//  PURPOSE:  Sets the normal pen width to meduim
//
//  COMMENTS:
//
LRESULT OnNormalPenWidthMedium(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.dPenWidth = PENWIDTHMEDIUM;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnNormalPenWidthThick
//
//  PURPOSE:  Sets the normal pen width to thick
//
//  COMMENTS: 
//
LRESULT OnNormalPenWidthThick(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.dPenWidth = PENWIDTHTHICK;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnNormalPenWidthMarker
//
//  PURPOSE:  Sets the normal pen width to marker
//
//  COMMENTS: 
//
LRESULT OnNormalPenWidthMarker(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.dPenWidth = PENWIDTHMARKER;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}


//
//  FUNCTION: OnNormalPenColorBlue
//
//  PURPOSE:  Sets the normal pen color to blue
//
//  COMMENTS: 
//
LRESULT OnNormalPenColorBlue(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.crColor = BLUECOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnNormalPenColorGreen
//
//  PURPOSE:  Sets the normal pen color to green
//
//  COMMENTS: 
//
LRESULT OnNormalPenColorGreen(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.crColor = GREENCOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnNormalPenColorRed
//
//  PURPOSE:  Sets the normal pen color to red
//
//  COMMENTS: 
//
LRESULT OnNormalPenColorRed(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.crColor = REDCOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnNormalPenColorYellow
//
//  PURPOSE:  Sets the normal pen color to yellow
//
//  COMMENTS: 
//
LRESULT OnNormalPenColorYellow(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.crColor = YELLOWCOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}

//
//  FUNCTION: OnHighlighterPenColorBlack
//
//  PURPOSE:  Sets the highlighter pen color to black
//
//  COMMENTS: 
//
LRESULT OnNormalPenColorBlack(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psNormalPen.crColor = BLACKCOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psNormalPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_INKINGMODE);
    return( 0 );
}


//
//  FUNCTION: OnHighlighterPenColorYellow
//
//  PURPOSE:  Sets the highlighter pen color to yellow
//
//  COMMENTS: 
//
LRESULT OnHighlighterPenColorYellow(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psHighlighterPen.crColor = YELLOWCOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psHighlighterPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_HIGHLIGHTERMODE);
    return( 0 );
}

//
//  FUNCTION: OnHighlighterPenColorGreen
//
//  PURPOSE:  Sets the highlighter pen color to green
//
//  COMMENTS: 
//
LRESULT OnHighlighterPenColorGreen(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_psHighlighterPen.crColor = GREENCOLOR;
    LRESULT lr = SendMessage(g_hWndIC, ICM_SETMODE, (WPARAM) IC_EDITINGMODE_INK, 0);
    lr = SendMessage(g_hWndIC, ICM_SETPENSTYLE, 0, (LPARAM)&g_psHighlighterPen); 
    // Now update the state of the toolbar buttons
    EnableButton(IDT_HIGHLIGHTERMODE);
    return( 0 );
}
