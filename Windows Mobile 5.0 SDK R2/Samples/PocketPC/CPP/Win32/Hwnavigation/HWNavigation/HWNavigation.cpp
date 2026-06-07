// HWNavigation.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HWNavigation.h"
#include <windows.h>
#include <commctrl.h>

// Global Constants
#define MAX_LOADSTRING 100
TCHAR c_szHWNavCtlFocusProp[] = TEXT("HWNAVCTL_FOCUS");
TCHAR c_szHWNavCtlPosProp[] = TEXT("HWNAVCTL_POSITION");

// Global Variables:
HINSTANCE            g_hInst;            // current instance
HWND                g_hWndMenuBar;        // menu bar handle

// Forward declarations of functions included in this code module:
ATOM            RegisterCustomClass(HINSTANCE hInstance);
BOOL            InitInstance(HINSTANCE, int, HWND*);
BOOL APIENTRY CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK        HWNavWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK        About(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    MSG msg;
    HWND hDlg;

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow, &hDlg)) 
    {
        return FALSE;
    }

    HACCEL hAccelTable;
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HWNAVIGATION));

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        // For Hardware Navigation to work at all, the message pump must call
        // IsDialogMessage. This can either be done explicitly, as shown below,
        // or implicitly, when one of the DialogBox* APIs are used.
        if (!hDlg || !IsDialogMessage(hDlg, &msg))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return (int) msg.wParam;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND *phDlg)
{
    HWND hDlg;
    TCHAR szTitle[MAX_LOADSTRING];        // title bar text
    TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Dialog");    // main window class name
    INITCOMMONCONTROLSEX icce;

    if (phDlg)
    {
        *phDlg = NULL;
    }

    g_hInst = hInstance; // Store instance handle in our global variable

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Pocket PC special controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 

    //If it is already running, then focus on the window, and exit
    hDlg = FindWindow(szWindowClass, szTitle);    
    if (hDlg) 
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hDlg | 0x00000001));
        return 0;
    }

    // Register Listview class
    icce.dwSize = sizeof(icce);
    icce.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icce);

    // Register custom control class
    RegisterCustomClass(hInstance);

    hDlg = CreateDialogParam( hInstance, MAKEINTRESOURCE( IDD_MAIN ), NULL, DlgProc, 0 );
    if (!hDlg)
    {
        return FALSE;
    }

    ShowWindow( hDlg , SW_SHOW );

    if (phDlg)
    {
        *phDlg = hDlg;
    }

    ShowWindow(hDlg, nCmdShow);
    UpdateWindow(hDlg);


    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: RegisterCustomClass
//
// PURPOSE: Registers the window class for the custom control window.
//
// ON ENTRY:
//      HINSTANCE hInstance: the application instance.
//
// ON EXIT:
//      The window class is registered and the return value 
//      from RegisterClass is returned.
//
ATOM RegisterCustomClass(HINSTANCE hInstance)
{
    WNDCLASS    wc;

    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC) HWNavWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = 0;
    wc.hbrBackground    = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName     = 0;
    wc.lpszClassName    = TEXT("HWNavControl");

    return RegisterClass(&wc);
}

//
//  FUNCTION: DlgProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main dialog.
//
//  WM_COMMAND    - process the application menu
//  WM_INITDIALOG - Populate listview and create menu bar
//  WM_DESTROY    - post a quit message and return
//
//
BOOL APIENTRY CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    BOOL bRet = FALSE;

    static HIMAGELIST s_himlBell = NULL;
    static SHACTIVATEINFO s_sai;

    
    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_HELP_ABOUT:
                    DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hDlg, About);
                    break;
                case IDM_CLOSE:
                    PostMessage(hDlg, WM_CLOSE,0,0);
                    bRet = TRUE;
                    break;
                default:
                    return DefWindowProc(hDlg, message, wParam, lParam);
            }
            break;

        case WM_INITDIALOG:
            {
                SHMENUBARINFO mbi;
                SHINITDLGINFO sidi;
                LVITEM lvi;

                HWND hwndLV = GetDlgItem(hDlg, IDC_LIST1);

                // Add items to listview
                lvi.mask = LVIF_TEXT;
                lvi.iSubItem = 0;
                lvi.cchTextMax = MAX_PATH;

                lvi.iItem = 0;
                lvi.pszText = TEXT("first item");
                ListView_InsertItem(hwndLV, &lvi);

                lvi.iItem = 1;
                lvi.pszText = TEXT("second item");
                ListView_InsertItem(hwndLV, &lvi);

                lvi.iItem = 2;
                lvi.pszText = TEXT("third item");
                ListView_InsertItem(hwndLV, &lvi);

                lvi.iItem = 3;
                lvi.pszText = TEXT("fourth item");
                ListView_InsertItem(hwndLV, &lvi);

                SendMessage(hwndLV, CCM_SETVERSION, COMCTL32_VERSION, 0L);

                // First listview item should be selected and focused initially
                ListView_SetItemState(hwndLV, 0, LVIS_SELECTED | LVIS_FOCUSED,
                                                 LVIS_SELECTED | LVIS_FOCUSED);

                // We want to have selection and focus be disjoint in listview,
                // so that selection changes caused by hardware navigation need
                // to be explicit. That is, movement causes focus change only and
                // return, action or spacebar keypresses cause selection change.
                ListView_SetExtendedListViewStyle(hwndLV, LVS_EX_DISJOINTFOCUS);

                // Add menu bar
                memset(&mbi, 0, sizeof(SHMENUBARINFO));
                mbi.cbSize     = sizeof(SHMENUBARINFO);
                mbi.hwndParent = hDlg;
                mbi.nToolBarId = IDR_MENU;
                mbi.hInstRes   = g_hInst;

                if (!SHCreateMenuBar(&mbi)) 
                {
                    g_hWndMenuBar = NULL;
                }
                else
                {
                    g_hWndMenuBar = mbi.hwndMB;
                }

                // Initialize the shell activate info structure
                memset(&s_sai, 0, sizeof (s_sai));
                s_sai.cbSize = sizeof (s_sai);

                // Size dialog full-screen
                sidi.dwMask = SHIDIM_FLAGS;
                sidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
                sidi.hDlg = hDlg;
                SHInitDialog(&sidi);
                bRet = TRUE;
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hDlg, &ps);
            
            EndPaint(hDlg, &ps);
            bRet = TRUE;
            break;

        case WM_CLOSE:
            DestroyWindow(hDlg);
            break;

        case WM_DESTROY:
            CommandBar_Destroy(g_hWndMenuBar);
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hDlg, wParam, lParam, &s_sai, FALSE);
            bRet = TRUE;
            break;

        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hDlg, wParam, lParam, &s_sai);
            bRet = TRUE;
            break;
    }
    return FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                // Create a Done button and size it.  
                SHINITDLGINFO shidi;
                shidi.dwMask = SHIDIM_FLAGS;
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
                shidi.hDlg = hDlg;
                SHInitDialog(&shidi);
            }
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, message);
            return TRUE;

#ifdef _DEVICE_RESOLUTION_AWARE
        case WM_SIZE:
            {
        DRA::RelayoutDialog(
            g_hInst, 
            hDlg, 
            DRA::GetDisplayMode() != DRA::Portrait ? MAKEINTRESOURCE(IDD_ABOUTBOX_WIDE) : MAKEINTRESOURCE(IDD_ABOUTBOX));
            }
            break;
#endif
    }
    return (INT_PTR)FALSE;
}

// The HWNavControl class is intended to showcase some hardware navigation concepts
// and is not very flexible. It only supports exactly 2 items, laid out horizontally.
// It responds to keyboard interaction but not to mouse/stylus events. A full-featured
// custom control would also respond to mouse/stylus.
// In addition, the control items have a predetermined size and separation.
#define HWNC_NUMITEMS    2
#define HWNC_ITEMWIDTH  (DRA::SCALEX(40))
#define HWNC_ITEMHEIGHT (DRA::SCALEY(40))
#define HWNC_ITEMSEP    (DRA::SCALEX(2))

// Message handler for windows of "HWNavControl" class
LRESULT CALLBACK HWNavWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    int iCurItem;
    LRESULT lRet = 0;

    static HIMAGELIST s_himlBell = NULL;

    switch (message)
    {
    case WM_CREATE:
        rcClient.left = 0;
        rcClient.top = 0;
        rcClient.right = 2*HWNC_ITEMWIDTH + HWNC_ITEMSEP;
        rcClient.bottom = HWNC_ITEMHEIGHT;

        // Keep track of focus state, FALSE on creation
        SetProp(hWnd, c_szHWNavCtlFocusProp, (HANDLE)FALSE);

        // Keep track of current item, 0 on creation
        SetProp(hWnd, c_szHWNavCtlPosProp, (HANDLE)0);
        break;

    case WM_SETFOCUS:
        // Keep track of focus state
        SetProp(hWnd, c_szHWNavCtlFocusProp, (HANDLE)TRUE);
        InvalidateRect(hWnd, NULL, TRUE);
    break;

    case WM_KILLFOCUS:
        // Keep track of focus state 
        SetProp(hWnd, c_szHWNavCtlFocusProp, (HANDLE)FALSE);
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_GETDLGCODE:
        {
            // We want to process arrow messages unless we detect
            // that arrow key would take focus out of control.
            // In that case, let system take care of message.
            LONG code = DLGC_WANTARROWS;

            if (lParam)
            {
                MSG *pMsg = (MSG*)lParam;
                if (WM_KEYDOWN == pMsg->message)
                {
                    iCurItem = (int)GetProp(hWnd, c_szHWNavCtlPosProp);

                    switch (pMsg->wParam)
                    {
                    case VK_UP:
                    case VK_DOWN:
                        // Vertical motion always takes focus away from control,
                        // so we let system take care of these keypresses.
                        code &= ~DLGC_WANTARROWS;
                        break;

                    case VK_LEFT:
                        // Horizontal motion to the left takes focus away from
                        // control if focus is currently on first item, so we
                        // let system take care of these keypresses. 
                        if (iCurItem <= 0)
                        {
                            code &= ~DLGC_WANTARROWS;
                        }
                        break;

                    case VK_RIGHT:
                        // Horizontal motion to the right takes focus away from
                        // control if focus is currently on last item, so we
                        // let system take care of these keypresses.
                        if (iCurItem >= HWNC_NUMITEMS - 1)
                        {
                            code &= ~DLGC_WANTARROWS;
                        }
                        break;

                    case VK_RETURN:
                        // We always want control to process return key
                        code |= DLGC_WANTMESSAGE;
                        break;
                    }
                }
            }

            lRet = code;
        }
        break;

    case WM_KEYDOWN:
        {
            iCurItem = (int)GetProp(hWnd, c_szHWNavCtlPosProp);

            switch (wParam)
            {
            case VK_LEFT:
                // Change currently focused item down towards first one
                iCurItem = max(0, iCurItem - 1);
                SetProp(hWnd, c_szHWNavCtlPosProp, (HANDLE)iCurItem);
                break;
            
            case VK_RIGHT:
                // Change currently focused item up towards last one
                iCurItem = min(HWNC_NUMITEMS - 1, iCurItem + 1);
                SetProp(hWnd, c_szHWNavCtlPosProp, (HANDLE)iCurItem);
                break;

            case VK_RETURN:
                {
                    // Perform action with currently focused item
                    TCHAR szMsg[200];
                    _stprintf(szMsg, TEXT("Item %i has focus"),iCurItem);
                    MessageBox(hWnd, szMsg, TEXT("Custom Control Focus"), MB_OK);
                    break;
                }
            }
            
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

    case WM_PAINT:
        {
            int i;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            GetClientRect(hWnd, &rcClient);
            FillRect(hdc, &rcClient, GetSysColorBrush(COLOR_WINDOW));

            iCurItem = (int)GetProp(hWnd, c_szHWNavCtlPosProp);

            if ((BOOL)GetProp(hWnd, c_szHWNavCtlFocusProp))
            {
                // If control has focus, draw themed focus rect around
                // focused item.
                RECT rcFocus = rcClient;

                rcFocus.left = iCurItem*HWNC_ITEMWIDTH + 
                    max(0, iCurItem-1)*HWNC_ITEMSEP;
                rcFocus.right = rcFocus.left + HWNC_ITEMWIDTH;
                DrawFocusRectColor(hdc, &rcFocus, DFRC_FOCUSCOLOR);
            }

            if (!s_himlBell)
            {
                s_himlBell = DRA::ImageList_LoadImage(g_hInst, 
                                MAKEINTRESOURCE(IDB_IMAGES), 
                                HWNC_ITEMWIDTH, 
                                0, 
                                RGB(255,255,255), 
                                IMAGE_BITMAP, 
                                0);
            }


            for (i = 0; i < HWNC_NUMITEMS; i++)
            {
                // Draw the image corresponding to each item
                ImageList_Draw(s_himlBell, i, hdc,
                            i*HWNC_ITEMWIDTH + max(0, i-1)*HWNC_ITEMSEP,
                            rcClient.top,
                            ILD_NORMAL);
            }

            EndPaint(hWnd, &ps);
            break;
        }
    }

    return lRet;
}