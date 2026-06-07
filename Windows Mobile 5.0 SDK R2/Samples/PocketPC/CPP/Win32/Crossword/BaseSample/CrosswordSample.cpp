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
// CrosswordSample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CrosswordSample.h"

const int MAX_LOADSTRING = 100;

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: WinMain
//
// PURPOSE: Entry point of our application.
//
int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPTSTR    lpCmdLine,
                    int       nCmdShow)
{
    MSG msg;
    HACCEL hAccelTable;

    if (!InitInstance (hInstance, nCmdShow)) 
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CROSSWORDSAMPLE);

    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: MyRegisterClass
//
// PURPOSE: Registers the window class for the main window.
//
// ON ENTRY:
//      HINSTANCE hInstance: the application instance.
//      LPTSTR    szWindowClass: the window class name to register.
//
// ON EXIT:
//      The window class is registered and the return value 
//      from RegisterClass is returned.
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS    wc;

    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC) WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CROSSWORDSAMPLE));
    wc.hCursor          = 0;
    wc.hbrBackground    = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName     = 0;
    wc.lpszClassName    = szWindowClass;

    return RegisterClass(&wc);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: CreateRpCommandBar
//
// PURPOSE: Creates the command bar at the bottom of the window.
//
// ON ENTRY:
//      HWND hwnd: the window which will recieve the command bar.
//      g_hInst: the application instance.
//
// ON EXIT:
//      The HWND of the command bar.
//
HWND CreateRpCommandBar(HWND hwnd)
{
    SHMENUBARINFO mbi;

    memset(&mbi, 0, sizeof(SHMENUBARINFO));
    mbi.cbSize     = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hwnd;
    mbi.nToolBarId = IDM_MENU;
    mbi.hInstRes   = g_hInst;
    mbi.nBmpId     = 0;
    mbi.cBmpImages = 0;

    if (!SHCreateMenuBar(&mbi)) 
        return NULL;

    CommandBar_AddBitmap (mbi.hwndMB, g_hInst, IDR_TOOLBAR1, 4, 16, 15);

    return mbi.hwndMB;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: InitInstance
//
// PURPOSE: Saves instance handle to g_hInst and creates the main window.
//
// ON ENTRY:
//      HINSTANCE hInstance: the application instance.
//      int nCmdShow: the hide/show parameter from WinMain.
//
// ON EXIT: 
//      g_hInst is initialized.
//      Returns TRUE if all initialization completed successfully.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND    hWnd = NULL;
    TCHAR   szTitle[MAX_LOADSTRING];
    TCHAR   szWindowClass[MAX_LOADSTRING];

    g_hInst = hInstance;
    LoadString(hInstance, IDC_CROSSWORDSAMPLE, szWindowClass, MAX_LOADSTRING);
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    //
    // If the app is already running, find it and bring it to the foreground.
    // (the "| 0x01" is used to bring any owned windows to the foreground). 
    //
    hWnd = FindWindow(szWindowClass, szTitle);  
    if (hWnd) 
    {
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    } 

    //
    // Create the main window.
    //
    MyRegisterClass(hInstance, szWindowClass);
    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {   
        return FALSE;
    }

    //
    // Initialize the crossword data structures.
    //
    CreateCrossword();

    //
    // Create all child windows.
    //
    CreateWindow(_T("Edit"), NULL, 
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 
        8, 4, 170, 20, 
        hWnd, (HMENU)IDC_MAIN_EDIT_BOX, g_hInst, 0);
    CreateWindow(_T("Button"), _T(""), 
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        183, 4, 50, 20, 
        hWnd, (HMENU)IDC_MAIN_ENTER_BUTTON, g_hInst, 0);

    //
    // This magic control automatically brings up the SIP when focus
    //    is transferred to an editable control.
    //
    SHInitExtraControls();
    CreateWindow(WC_SIPPREF, NULL,
        WS_CHILD,
        0,0,0,0,
        hWnd, NULL, g_hInst, 0);

    //
    // Create the default font.
    //
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight = -12;
    _tcscpy(lf.lfFaceName, _T("Courier New"));
    lf.lfWeight = FW_NORMAL;
    g_hFont = CreateFontIndirect(&lf);

    //
    // Load the images for the ENTER button.
    //
    g_hImageList = ImageList_LoadImage(
        g_hInst,
        MAKEINTRESOURCE(IDB_ENTERBTN),
        46,
        0,
        CLR_NONE,
        IMAGE_BITMAP,
        0);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: CreateCrossword
//
// PURPOSE: Creates the crossword bitmaps and does all initial drawing.
//
// ON EXIT: g_hMemDC, g_hMemBitmap, g_selectedClue, g_crossword 
//      are initialized.
//
void CreateCrossword()
{
    HDC hScreenDC = GetWindowDC(NULL);
    g_hMemDC = CreateCompatibleDC(hScreenDC);
    g_hMemBitmap = CreateCompatibleBitmap(hScreenDC, 240, 320);
    ReleaseDC(NULL, hScreenDC);
    SelectObject(g_hMemDC, g_hMemBitmap);

    int iHint = 0;

    //
    // Fill in each g_hints structure from left to right (for ACROSS hints).
    //
    for (int y = 0; y < CROSSWORD_Y - 1; y++)
    {
        int cLetters = 0;
        for (int x = 0; x < CROSSWORD_X; x++)
        {
            if (g_crosswordSolution[y][x] == '*')
            {
                SelectObject(g_hMemDC, GetStockObject(BLACK_BRUSH));
                if (cLetters > 1)
                {
                    g_hints[iHint].x = x - cLetters;
                    g_hints[iHint].y = y;
                    g_hints[iHint].cLetters = cLetters;
                    g_hints[iHint].fDown = false;
                    iHint++;
                }
                cLetters = 0;
            }
            else 
            {
                SelectObject(g_hMemDC, GetStockObject(WHITE_BRUSH));
                cLetters++;
            }

            //
            // Also draw the offscreen crossword bitmap during this pass.
            //
            RECT r;
            r.left   = 16 * x;
            r.top    = 16 * y;
            r.right  = r.left + 17;
            r.bottom = r.top + 17;
            Rectangle(g_hMemDC, r.left, r.top, r.right, r.bottom);
            g_crossword[y][x] = ' ';
        }
    }

    //
    // Fill in each g_hints structure from top to bottom (for DOWN hints).
    //
    for (int x = 0; x < CROSSWORD_X - 1; x++)
    {
        int cLetters = 0;
        for (int y = 0; y < CROSSWORD_Y; y++)
        {
            if (g_crosswordSolution[y][x] == '*')
            {
                if (cLetters > 1)
                {
                    g_hints[iHint].x = x;
                    g_hints[iHint].y = y - cLetters;
                    g_hints[iHint].cLetters = cLetters;
                    g_hints[iHint].fDown = true;
                    iHint++;
                }
                cLetters = 0;
            }
            else 
            {
                cLetters++;
            }
        }
    }
    g_selectedHint = -1;
}


//////////////////////////////////////////////////////////////////////////////
// FUNCTION: DrawHint
//
// PURPOSE: Draws the row or column specified by the given hint onto the 
//      crossword offscreen buffer (g_hMemDC).
//
// ON ENTRY:
//      HWND hWnd: the main window app (we need this to invalidate the window
//          after we are done, so that it will send WM_PAINT).
//      INT nHint: the hint whose row or column we wish to draw.
//      COLORREF rgbColor: the background color of the squares we draw.
//
void DrawHint (HWND hWnd, INT nHint, COLORREF rgbColor)
{
    if (nHint == -1) return;
    HBRUSH hBrush = CreateSolidBrush(rgbColor);
    for (int i = 0; i < g_hints[nHint].cLetters; i++)
    {
        RECT r;
        int x = g_hints[nHint].x + (g_hints[nHint].fDown ? 0 : i);
        int y = g_hints[nHint].y + (g_hints[nHint].fDown ? i : 0);
        r.left = x * 16 + 1;
        r.top  = y * 16 + 1;
        r.right  = r.left + 15;
        r.bottom = r.top + 15;
        SetBkMode(g_hMemDC, TRANSPARENT);
        FillRect(g_hMemDC, &r, hBrush);
        DrawText(g_hMemDC, &g_crossword[y][x], 1, &r, DT_CENTER | DT_VCENTER);
        
        //
        // Invalidate the rectangle on the screen.
        //
        r.left += 8; 
        r.right += 8;
        r.top += 26;
        r.bottom += 26;
        InvalidateRect(hWnd, &r, false);
    }
    DeleteObject(hBrush);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: PropSheetCallback.
//
// PURPOSE: Callback for the Tools / Options property sheet used by
//      OnCommandToolsOptions.  This is necessary so that dialog tabs get 
//      drawn in the flat PocketPC style.
//
int PropSheetCallback(HWND hwndDlg, UINT message, LPARAM lParam)
{
    if (message == PSCB_GETVERSION) 
    {
        return COMCTL32_VERSION;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: OnCommandToolsOptions
//
// PURPOSE: Creates the dialog window for Tools / Options.
//
// ON ENTRY:
//      HWND hWnd: the main window app.
//
void OnCommandToolsOptions(HWND hWnd)
{
    PROPSHEETPAGE psp[2];
    psp[0].dwSize = sizeof(psp[0]);
    psp[0].dwFlags = PSP_DEFAULT;
    psp[0].hInstance = g_hInst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_TOOLS_OPTIONS_1);
    psp[0].pfnDlgProc = (DLGPROC)&ToolsOptionsDialog1;

    psp[1].dwSize = sizeof(psp[1]);
    psp[1].dwFlags = PSP_DEFAULT;
    psp[1].hInstance = g_hInst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_TOOLS_OPTIONS_2);
    psp[1].pfnDlgProc = (DLGPROC)&ToolsOptionsDialog2;

    //
    // See http://msdn.microsoft.com/library/default.asp?url=/library/en-us/win_ce/htm/pwc_propertysheets.asp
    // for more information about PSH_MAXIMIZE and handling PSCB_GETVERSION in the
    // PropertySheet callback. 
    //
    PROPSHEETHEADER psh;
    psh.dwSize = sizeof(psh);
    psh.dwFlags = PSH_DEFAULT | PSH_PROPSHEETPAGE | PSH_MAXIMIZE | PSH_NOAPPLYNOW | PSH_USECALLBACK;
    psh.hwndParent = hWnd;
    psh.hInstance = g_hInst;
    psh.pszCaption = _T("Tools / Options");
    psh.nPages = 2;
    psh.nStartPage = 0;
    psh.ppsp = &psp[0];
    psh.pfnCallback = PropSheetCallback;
    PropertySheet(&psh);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: OnClickEnterButton
//
// PURPOSE: Called when the enter button is clicked.  Copies the text in the
//      g_hwndEditBox to the crossword offscreen buffer (using DrawHint).  
//
// ON ENTRY:
//      HWND hWnd: the main window app.
//      g_selectedHint: the destination row or column the text will 
//          be copied to.
//
// ON EXIT:
//      The edit box is cleared.
//
void OnClickEnterButton(HWND hWnd)
{
    WCHAR szBuffer[80];
    SendDlgItemMessage(hWnd, IDC_MAIN_EDIT_BOX, WM_GETTEXT, sizeof(szBuffer)/sizeof(WCHAR), (LPARAM)szBuffer);
    SendDlgItemMessage(hWnd, IDC_MAIN_EDIT_BOX, WM_SETTEXT, 0, (LPARAM)_T(""));

    if (g_selectedHint == -1) return;

    for (int i = 0; i < g_hints[g_selectedHint].cLetters; i++)
    {
        if (szBuffer[i] == '\0')
        {
            break;
        }
        int x = g_hints[g_selectedHint].x + (g_hints[g_selectedHint].fDown ? 0 : i);
        int y = g_hints[g_selectedHint].y + (g_hints[g_selectedHint].fDown ? i : 0);
        g_crossword[y][x] = towupper(szBuffer[i]);
    }

    DrawHint(hWnd, g_selectedHint, RGB(128,0,0));
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: OnLButtonDown
//
// PURPOSE: Called when the stylus is tapped on the screen.  Selects a row or
//      column based on the location of the tap.
//
// ON ENTRY:
//      HWND hWnd: the window which was tapped.
//      INT x: the x location of the screen tap in pixels.
//      INT y: the y location of the screen tap in pixels.
//
// ON EXIT:
//      g_selectedHint equals the location of the screen tap. 
//
void OnLButtonDown(HWND hWnd, INT x, INT y)
{
    x = (x - 8) / 16;
    y = (y - 26) / 16;

    if (x < 0 || y < 0 || x >= CROSSWORD_X - 1 || y >= CROSSWORD_Y - 1)
    {
        return;
    }

    //
    // Erase the old hint.
    //
    DrawHint(hWnd, g_selectedHint, RGB(255,255,255));
    
    //
    // Search for the hint that we clicked.
    //
    int oldSelectedHint = g_selectedHint;
    g_selectedHint = -1;
    for (int i = 0; i < sizeof(g_hints) / sizeof(CROSSWORD_HINT); i++)
    {
        if (i == oldSelectedHint) continue;
        if ((!g_hints[i].fDown && y == g_hints[i].y &&
            x >= g_hints[i].x && x < g_hints[i].x + g_hints[i].cLetters) ||
            (g_hints[i].fDown && x == g_hints[i].x &&
            y >= g_hints[i].y && y < g_hints[i].y + g_hints[i].cLetters))
        {
            g_selectedHint = i;
            break;
        }
    }

    //
    // Draw in this new hint.
    //
    DrawHint(hWnd, g_selectedHint, RGB(128, 0, 0));

    if (g_selectedHint != -1)
    {
        SendDlgItemMessage(hWnd, IDC_MAIN_EDIT_BOX, EM_LIMITTEXT, g_hints[g_selectedHint].cLetters, 0);
    }

    //
    // Invalidate the hint area so we redraw.
    //
    RECT r = { 0, 189, 240, 320 };
    InvalidateRect(hWnd, &r, FALSE);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: OnPaint
//
// PURPOSE: Paints the main application window.
//
// ON ENTRY:
//      HWND hWnd: the window to paint.
//
void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd, &ps);

    //
    // Draw background.
    //
    HBITMAP hBMP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND_1));
    HDC hMemDC = CreateCompatibleDC(NULL);
    HBITMAP hOldBMP = (HBITMAP)SelectObject(hMemDC, hBMP);
    BitBlt(hDC, 0, 0, 240, 320, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBMP);
    DeleteObject(hBMP);
    DeleteDC(hMemDC);

    //
    // Draw crossword.
    //
    TransparentImage(hDC, 8, 26, 14 * 16 + 1, 10 * 16 + 1, 
        g_hMemDC, 0, 0, 14 * 16 + 1, 10 * 16 + 1, RGB(255, 255, 255));
            
    POINT line[] = { {0, 188}, {240, 188} };
    Polyline(hDC, line, 2);
    
    //
    // Erase the hint area using a pattern brush.
    //
    RECT r = { 25, 200, 230, 245 };
    HBITMAP hPattern = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_PATTERN));
    HBRUSH hNewBrush = CreatePatternBrush(hPattern);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
    Rectangle(hDC, r.left, r.top, r.right, r.bottom);
    SelectObject(hDC, hOldBrush);
    DeleteObject(hNewBrush);
    DeleteObject(hPattern);

    if (g_selectedHint != -1)
    {
        //
        // Print the hint out at bottom.
        //
        r.left  += 4;
        r.right -= 4;
        SetBkMode(hDC, TRANSPARENT);
        HFONT hOldFont = (HFONT)SelectObject(hDC, g_hFont);
        DrawText(hDC, g_hints[g_selectedHint].szHint, -1, &r, DT_TOP | DT_LEFT | DT_WORDBREAK);
        SelectObject(hDC, hOldFont);

        //
        // Display an arrow next to the hint.
        //
        POINT rgArrow[] = { {0,3}, {6,3}, {6,0}, {12, 5}, {6, 10}, {6, 7}, {0, 7} };
        for (int i = 0; i < 7; i++)
        { 
            //
            // A vertical arrow is a horizontal arrow with X and Y flipped.
            //
            if (g_hints[g_selectedHint].fDown)
            {
                int t = rgArrow[i].x;
                rgArrow[i].x = rgArrow[i].y;
                rgArrow[i].y = t;
            }
            rgArrow[i].x += 5; 
            rgArrow[i].y += 200; 
        }
        Polygon(hDC, rgArrow, 7);
    }
    
    EndPaint(hWnd, &ps);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: WndProc()
//
// PURPOSE:  Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) 
    {
        case WM_CREATE:
            g_hwndCB = CreateRpCommandBar(hWnd);
            memset (&g_sai, 0, sizeof (g_sai));
            g_sai.cbSize = sizeof (g_sai);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDC_MAIN_ENTER_BUTTON:
                OnClickEnterButton(hWnd);
                break;
            
            case ID_TOOLS_OPTIONS:
                OnCommandToolsOptions(hWnd);
                break;
            
            case ID_TOOLS_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_TOOLS_ABOUT), hWnd, &ToolsAboutDialog);
                break;
            }
            break;

        case WM_DRAWITEM:
            {
                //
                // Draws the Enter button.
                //
                LPDRAWITEMSTRUCT lpDis = (LPDRAWITEMSTRUCT)lParam;
                DrawEdge(lpDis->hDC, &lpDis->rcItem, 
                    (lpDis->itemState & ODS_SELECTED) ? EDGE_SUNKEN : EDGE_RAISED, 
                    BF_RECT);
                ImageList_Draw(g_hImageList,
                    (lpDis->itemState & ODS_SELECTED) ? 0 : 1,
                    lpDis->hDC, 2, 2, ILD_NORMAL);
            }
            break;

        case WM_PAINT:
            OnPaint(hWnd);
            break;
            
        case WM_LBUTTONDOWN:
            OnLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_DESTROY:
            CommandBar_Destroy(g_hwndCB);
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            SHHandleWMActivate(hWnd, wParam, lParam, &g_sai, FALSE);
            break;

        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &g_sai);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

