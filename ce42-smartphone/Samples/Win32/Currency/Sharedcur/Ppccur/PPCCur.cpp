///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "resource.h"
#include "CurDlg.h"
#include "..\helpers.h"

// Global Variables:
HINSTANCE g_hInst;    // The current instance
HINSTANCE g_hInstRes; // instance of the resource dll.
static SHACTIVATEINFO g_sai;
static const TCHAR* g_szAppWndClass = TEXT("CurrencyApp");

HWND g_hDlgActive = NULL;

/**************************************************************************************

 **************************************************************************************/
LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    LRESULT lResult = TRUE;

    switch(msg)
    {
        case WM_CREATE:
            memset(&g_sai, 0, sizeof (g_sai));
            g_sai.cbSize = sizeof (g_sai);

            lResult = 0;
            break;

        case WM_DESTROY:
            if(g_hDlgActive)
                {
                DestroyWindow(g_hDlgActive);
                }
            PostQuitMessage(0);
            break;
        
        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hwnd, wParam, lParam, &g_sai, 0);
            break;

        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hwnd, wParam, lParam, &g_sai);
            break;

        default:
            lResult = DefWindowProc(hwnd, msg, wParam, lParam);
            break;
    }

    return(lResult);
}


/*****************************************************************************

  ***************************************************************************/

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow
    )
{
    MSG msg;
    HWND hwnd = NULL;
    BOOL fActivated;
    WNDCLASS wc;
    HWND hwndMain;
    TCHAR szAppTitle[20];

	g_hInst = hInstance;
    g_hInstRes = hInstance;

    if(0 == LoadString(g_hInstRes, IDS_APP_TITLE, szAppTitle, ARRAYSIZE(szAppTitle)))
    {
        return(0);
    }

    if(FAILED(ActivatePreviousInstance(g_szAppWndClass, szAppTitle, &fActivated)) ||
            fActivated)
    {
        return(0);
    }

    // Register our main window's class.
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.hInstance = g_hInst;
    wc.lpszClassName = g_szAppWndClass;
    if(!RegisterClass(&wc))
    {
        return(0);
    }

    // Create the main window.    
    hwndMain = CreateWindow(g_szAppWndClass, szAppTitle,
            WS_CLIPCHILDREN, // Setting this to 0 gives a default style we don't want.  Use a benign style bit instead.
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, g_hInst, NULL );
    if(!hwndMain)
    {
        return(0);
    }

    ShowWindow(hwndMain, nCmdShow);

    if(FAILED(StartupCurrencyConverterDialog(hwndMain)))
    {
        return(0);
    }

    while(GetMessage(&msg, NULL, 0, 0)) 
    {
        if((NULL == g_hDlgActive) || (!IsDialogMessage(g_hDlgActive, &msg)))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
  
    return msg.wParam;
}


