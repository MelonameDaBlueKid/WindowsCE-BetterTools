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

#include "stdafx.h"
#include "BattStat.h"
#include <windows.h>
#include <commctrl.h>
#include <regext.h>
#include <snapi.h>

#define MAX_LOADSTRING      100
#define STATUS_STRING_LEN   500

#define WM_OFFSET                 10000
#define WM_CHANGE_BATTSTRENGTH    (WM_OFFSET + 1)
#define WM_CHANGE_BATTSTATE       (WM_OFFSET + 2)
#define WM_CHANGE_BACKUPSTRENGTH  (WM_OFFSET + 3)
#define WM_CHANGE_BACKUPSTATE     (WM_OFFSET + 4)


#define IDC_BATTSTRENGTH    (WM_OFFSET + 200)
#define IDC_BATTSTATE       (WM_OFFSET + 201)
#define IDC_BACKUPSTRENGTH  (WM_OFFSET + 202)
#define IDC_BACKUPSTATE     (WM_OFFSET + 203)
#define IDC_CMDLINE         (WM_OFFSET + 204)

// Global Variables:
HINSTANCE g_hInst;      // Current instance

HWND g_hWndMenuBar;     // Menu bar handle
HWND g_hCurWndDialog;   // Primary Window Dialog

HWND g_hBattStrength;   // Status text windows
HWND g_hBattState;
HWND g_hBackupStrength;
HWND g_hBackupState;
HWND g_hCmdLine;

// RegistryNotifyApp names
const WCHAR c_wszAppBattStrengthName[]     = L"BattStat.BattStrength";
const WCHAR c_wszAppBattStateName[]        = L"BattStat.BattState";
const WCHAR c_wszAppBackupStrengthName[]   = L"BattStat.BackupStrength";
const WCHAR c_wszAppBackupStateName[]      = L"BattStat.BackupState";


#define NOTIFY_CNT 4
HREGNOTIFY  g_hNotify[NOTIFY_CNT];  // Handles to notifications



// Forward declarations of functions included in this code module:
ATOM    MyRegisterClass(HINSTANCE, LPTSTR);
BOOL    InitInstance(HINSTANCE, int);
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK  About(HWND, UINT, WPARAM, LPARAM);
HRESULT RegisterWindows();
HRESULT RegisterApps();
HRESULT UnregisterWindows();
HRESULT UnregisterApps();
void    BattStateCallback(HREGNOTIFY hNotify, DWORD dwUserData, const PBYTE pData, const UINT cbData);

//
//  FUNCTION: int WINAPI WinMain(HINSTANCE hInstance,
//                   HINSTANCE hPrevInstance,
//                   LPTSTR    lpCmdLine,
//                   int       nCmdShow)
//
//  PURPOSE: Main loop.
//
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
  MSG msg;

  // Perform application initialization.
  if (!InitInstance(hInstance, nCmdShow)) 
  {
    return FALSE;
  }

  HACCEL hAccelTable;
  hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BATTSTAT));

  // Main message loop.
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int) msg.wParam;
}

//
//  FUNCTION: ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
  WNDCLASS wc;

  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BATTSTAT));
  wc.hCursor       = 0;
  wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName  = 0;
  wc.lpszClassName = szWindowClass;

  return RegisterClass(&wc);
}


 
//
//  FUNCTION: void GetBattStateStr(DWORD dwBattState, LPTSTR  pszBattStateStr)
//
//  PURPOSE: Form the battery state string from the given battery state flag.
//
void GetBattStateStr(DWORD dwBattState, LPTSTR  pszBattStateStr)
{
  if (dwBattState == 0)
  {
    StringCchCat(pszBattStateStr, STATUS_STRING_LEN, L"Normal");
  }
  else
  {
    // Check each bit; specific battery drivers may set different combinations of bits.
    if (dwBattState & 1)
    {
      StringCchCat(pszBattStateStr, STATUS_STRING_LEN, L"Not Present ");
    }

    if (dwBattState & 2)
    {
      StringCchCat(pszBattStateStr, STATUS_STRING_LEN, L"Charging ");
    }

    if (dwBattState & 4)
    {
      StringCchCat(pszBattStateStr, STATUS_STRING_LEN, L"Low ");
    }

    if (dwBattState & 8)
    {
      StringCchCat(pszBattStateStr, STATUS_STRING_LEN, L"Critical");
    }
  }
}



//
//  FUNCTION: void UpdateBattState(HKEY hKey, LPCWSTR wszSubKey, LPCWSTR wszName, 
//                                 DWORD dwBitMask, int nControlID)
//
//  PURPOSE:  Update the given battery state.
//
void UpdateBattState(HKEY hKey, LPCWSTR wszSubKey, LPCWSTR wszName, DWORD dwBitMask, int nControlID)
{
  HRESULT hr;
  DWORD dwRegValue;
  DWORD dwBattState;
  TCHAR szBattStateStr[STATUS_STRING_LEN];
  
  StringCchCopy(szBattStateStr, STATUS_STRING_LEN, L"");

  // Read the new value.
  hr = RegistryGetDWORD(hKey, wszSubKey, wszName, &dwRegValue);

  if (hr == S_OK)
  {
    // Only look at specified bits.
    dwBattState = dwRegValue  & dwBitMask;
    GetBattStateStr(dwBattState, szBattStateStr);
  }

  // Update the status text.
  SetDlgItemText(g_hCurWndDialog, nControlID, szBattStateStr);
}


 
//
//  FUNCTION: void UpdateBattStrength(HKEY hKey, LPCWSTR wszSubKey, LPCWSTR wszName, 
//                                    DWORD dwBitMask, int nControlID)
//
//  PURPOSE: Update the given battery strength level.
//
void UpdateBattStrength(HKEY hKey, LPCWSTR wszSubKey, LPCWSTR wszName, DWORD dwBitMask, int nControlID)
{
  HRESULT hr;
  DWORD dwRegValue;
  ULONG dwBattStrength;
  TCHAR szBattStrengthStr[STATUS_STRING_LEN];
  
  StringCchCopy(szBattStrengthStr, STATUS_STRING_LEN, L"");

  // Read the new value from the registry.
  hr = RegistryGetDWORD(hKey, wszSubKey, wszName, &dwRegValue);

  if (hr == S_OK)
  {
    // Get the value of the highword and shift the bits over to read the actual value.
    dwBattStrength = (dwRegValue  & dwBitMask) >> 16;

    // Check the value to get the appropriate string.
    if (dwBattStrength == 0)
    {
      StringCchCopy(szBattStrengthStr, STATUS_STRING_LEN, L"Very Low");
    }
    else if (dwBattStrength == 21)
    {
      StringCchCopy(szBattStrengthStr, STATUS_STRING_LEN, L"Low");
    }
    else if (dwBattStrength == 41)
    {
      StringCchCopy(szBattStrengthStr, STATUS_STRING_LEN, L"Medium");
    }
    else if (dwBattStrength == 61)
    {
      StringCchCopy(szBattStrengthStr, STATUS_STRING_LEN, L"High");
    }
    else if (dwBattStrength == 81)
    {
      StringCchCopy(szBattStrengthStr, STATUS_STRING_LEN, L"Very High");
    }

  }

  // Update the status text.
  SetDlgItemText(g_hCurWndDialog, nControlID, szBattStrengthStr);
}


//
//  FUNCTION: void UpdateAll()
//
//  PURPOSE: Update all the battery values.
//
void UpdateAll()
{
  UpdateBattStrength(SN_POWERBATTERYSTRENGTH_ROOT, SN_POWERBATTERYSTRENGTH_PATH, SN_POWERBATTERYSTRENGTH_VALUE, SN_POWERBATTERYSTRENGTH_BITMASK, IDC_BATTSTRENGTH);
  UpdateBattState(SN_POWERBATTERYSTATE_ROOT, SN_POWERBATTERYSTATE_PATH, SN_POWERBATTERYSTATE_VALUE, SN_POWERBATTERYSTATE_BITMASK, IDC_BATTSTATE);
  UpdateBattStrength(SN_POWERBATTERYBACKUPSTRENGTH_ROOT, SN_POWERBATTERYBACKUPSTRENGTH_PATH, SN_POWERBATTERYBACKUPSTRENGTH_VALUE, SN_POWERBATTERYBACKUPSTRENGTH_BITMASK, IDC_BACKUPSTRENGTH);
  UpdateBattState(SN_POWERBATTERYBACKUPSTATE_ROOT, SN_POWERBATTERYBACKUPSTATE_PATH, SN_POWERBATTERYBACKUPSTATE_VALUE, SN_POWERBATTERYBACKUPSTATE_BITMASK, IDC_BACKUPSTATE);
  SetDlgItemText(g_hCurWndDialog, IDC_CMDLINE, GetCommandLine());
}




//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window.
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  TCHAR szTitle[MAX_LOADSTRING];        // Title bar text
  TCHAR szWindowClass[MAX_LOADSTRING];  // Main window class name

  // Store instance handle in our global variable.
  g_hInst = hInstance;                  

  // SHInitExtraControls should be called once during your application's initialization to initialize any
  // of the Pocket PC special controls such as CAPEDIT and SIPPREF.
  SHInitExtraControls();

  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
  LoadString(hInstance, IDC_BATTSTAT, szWindowClass, MAX_LOADSTRING);

  //If it is already running, then focus on the window, and exit.
  hWnd = FindWindow(szWindowClass, szTitle);  

  if (hWnd) 
  {
    // Set focus to foremost child window.
    // The "| 0x00000001" is used to bring any owned windows to the foreground and
    // activate them.
    SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));

    return 0;
  } 

  if (!MyRegisterClass(hInstance, szWindowClass))
  {
    return FALSE;
  }

  hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  if (!hWnd)
  {
      return FALSE;
  }

  g_hCurWndDialog = hWnd;

  // When the main window is created using CW_USEDEFAULT the height of the menubar (if one
  // is created is not taken into account). So we resize the window after creating it
  // if a menubar is present
  if (g_hWndMenuBar)
  {
    RECT rc;
    RECT rcMenuBar;

    GetWindowRect(hWnd, &rc);
    GetWindowRect(g_hWndMenuBar, &rcMenuBar);
    rc.bottom -= (rcMenuBar.bottom - rcMenuBar.top);

    MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  // Create the status text windows - the labels and the current value.
  CreateWindow(TEXT("STATIC"), 
         TEXT("Battery Strength : "), 
         WS_VISIBLE,
         10, 20, 110, 14, 
         hWnd, NULL, hInstance, NULL);

  g_hBattStrength = CreateWindow(TEXT("STATIC"), 
         TEXT(""), 
         WS_VISIBLE,
         10, 35, 200, 14, 
         hWnd, (HMENU)IDC_BATTSTRENGTH, hInstance, NULL);

  CreateWindow(TEXT("STATIC"), 
         TEXT("Battery State : "), 
         WS_VISIBLE,
         10, 60, 110, 14, 
         hWnd, NULL, hInstance, NULL);

  g_hBattState = CreateWindow(TEXT("STATIC"), 
         TEXT(""), 
         WS_VISIBLE,
         10, 75, 200, 14, 
         hWnd, (HMENU)IDC_BATTSTATE, hInstance, NULL);

  CreateWindow(TEXT("STATIC"), 
         TEXT("Backup Strength : "), 
         WS_VISIBLE,
         10, 100, 110, 14, 
         hWnd, NULL, hInstance, NULL);

  g_hBackupStrength = CreateWindow(TEXT("STATIC"), 
         TEXT(""), 
         WS_VISIBLE,
         10, 115, 200, 14, 
         hWnd, (HMENU)IDC_BACKUPSTRENGTH, hInstance, NULL);

  CreateWindow(TEXT("STATIC"), 
         TEXT("Backup State : "), 
         WS_VISIBLE,
         10, 140, 110, 14, 
         hWnd, NULL, hInstance, NULL);

  g_hBackupState = CreateWindow(TEXT("STATIC"), 
         TEXT(""), 
         WS_VISIBLE,
         10, 155, 200, 14, 
         hWnd, (HMENU)IDC_BACKUPSTATE, hInstance, NULL);

  CreateWindow(TEXT("STATIC"), 
         TEXT("Command Line : "), 
         WS_VISIBLE,
         10, 200, 110, 14, 
         hWnd, NULL, hInstance, NULL);

  g_hCmdLine = CreateWindow(TEXT("STATIC"), 
         TEXT(""), 
         WS_VISIBLE,
         10, 215, 200, 14, 
         hWnd, (HMENU)IDC_CMDLINE, hInstance, NULL);

  // Register our window notifications.
  RegisterWindows();

  // Initialize the display of the battery values.
  UpdateAll();

  return TRUE;
}



//
//  FUNCTION: LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT  - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  static SHACTIVATEINFO s_sai;

  switch (message) 
  {
    case WM_COMMAND:
      wmId    = LOWORD(wParam); 
      wmEvent = HIWORD(wParam); 

      // Parse the menu selections.
      switch (wmId)
      {
        case IDM_HELP_ABOUT:
          DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, About);

          break;

        case IDM_OK:
          // Unregister our window notifications and exit.
          UnregisterWindows();
          SendMessage (hWnd, WM_CLOSE, 0, 0);        

          break;

        case ID_MENU_UPDATE:
          // Manually update all battery status values.
          UpdateAll();

          break;

        case ID_MENU_PERSIST:
          // Register the app notifications.
          RegisterApps();

          break;

        case ID_MENU_REMOVEPERSIST:
          // Unregister the app notifications.
          UnregisterApps();

          break;

        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
      }

      break;

    case WM_CREATE:
      SHMENUBARINFO mbi;

      memset(&mbi, 0, sizeof(SHMENUBARINFO));
      mbi.cbSize     = sizeof(SHMENUBARINFO);
      mbi.hwndParent = hWnd;
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

      // Initialize the shell activate info structure.
      memset(&s_sai, 0, sizeof (s_sai));
      s_sai.cbSize = sizeof (s_sai);

      break;

    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      
      EndPaint(hWnd, &ps);

      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_ACTIVATE:
      // Notify shell of our activate message.
      SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);

      break;

    case WM_SETTINGCHANGE:
      SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);

      break;

    case WM_CHANGE_BATTSTRENGTH:
      // Main battery strength value changed.
      UpdateBattStrength(SN_POWERBATTERYSTRENGTH_ROOT, SN_POWERBATTERYSTRENGTH_PATH, SN_POWERBATTERYSTRENGTH_VALUE, SN_POWERBATTERYSTRENGTH_BITMASK, IDC_BATTSTRENGTH);

      break;

    case WM_CHANGE_BATTSTATE:
      // Main battery state value changed.
      UpdateBattState(SN_POWERBATTERYSTATE_ROOT, SN_POWERBATTERYSTATE_PATH, SN_POWERBATTERYSTATE_VALUE, SN_POWERBATTERYSTATE_BITMASK, IDC_BATTSTATE);

      break;

    case WM_CHANGE_BACKUPSTRENGTH:
      // Backup battery strength value changed.
      UpdateBattStrength(SN_POWERBATTERYBACKUPSTRENGTH_ROOT, SN_POWERBATTERYBACKUPSTRENGTH_PATH, SN_POWERBATTERYBACKUPSTRENGTH_VALUE, SN_POWERBATTERYBACKUPSTRENGTH_BITMASK, IDC_BACKUPSTRENGTH);

      break;

    case WM_CHANGE_BACKUPSTATE:
      // Backup battery state value changed.
      UpdateBattState(SN_POWERBATTERYBACKUPSTATE_ROOT, SN_POWERBATTERYBACKUPSTATE_PATH, SN_POWERBATTERYBACKUPSTATE_VALUE, SN_POWERBATTERYBACKUPSTATE_BITMASK, IDC_BACKUPSTATE);

      break;

    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;

}


//
//  FUNCTION: INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//
//  PURPOSE: Message handler for about box.
//
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


//
//  FUNCTION: HRESULT RegisterWindows()
//
//  PURPOSE: Register the window notifications.
//
HRESULT RegisterWindows()
{
  HRESULT hr;
  NOTIFICATIONCONDITION nc;

  // Make sure we aren't already registered.
  UnregisterWindows();

  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYSTRENGTH_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register battery strength notification.
  hr = RegistryNotifyWindow(
                SN_POWERBATTERYSTRENGTH_ROOT,
                SN_POWERBATTERYSTRENGTH_PATH,
                SN_POWERBATTERYSTRENGTH_VALUE,
                g_hCurWndDialog, 
                WM_CHANGE_BATTSTRENGTH,       // This notification uses a custom window message.
                0,
                &nc,
                &g_hNotify[0]
                );

  if (FAILED(hr))
  {
      goto Error;
  }

  // Notify us of any change in the value and set the bitmask of the value to check.
  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYSTATE_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register battery state notification.
  hr = RegistryNotifyCallback(
                SN_POWERBATTERYSTATE_ROOT,
                SN_POWERBATTERYSTATE_PATH,
                SN_POWERBATTERYSTATE_VALUE,
                BattStateCallback,          // This notification uses a callback.
                0,       
                &nc,
                &g_hNotify[1]
                );

  if (FAILED(hr))
  {
    goto Error;
  }

  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYBACKUPSTRENGTH_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register backup battery strength notification.
  hr = RegistryNotifyWindow(
                SN_POWERBATTERYBACKUPSTRENGTH_ROOT,
                SN_POWERBATTERYBACKUPSTRENGTH_PATH,
                SN_POWERBATTERYBACKUPSTRENGTH_VALUE,
                g_hCurWndDialog, 
                WM_CHANGE_BACKUPSTRENGTH,
                0,
                &nc,
                &g_hNotify[2]
                );

  if (FAILED(hr))
  {
    goto Error;
  }

  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYBACKUPSTATE_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register backup battery state notification.
  hr = RegistryNotifyWindow(
                SN_POWERBATTERYBACKUPSTATE_ROOT,
                SN_POWERBATTERYBACKUPSTATE_PATH,
                SN_POWERBATTERYBACKUPSTATE_VALUE,
                g_hCurWndDialog, 
                WM_CHANGE_BACKUPSTATE,
                0,
                &nc,
                &g_hNotify[3]
                );

  if (FAILED(hr))
  {
    goto Error;
  }


Error:
    return hr;
}



//
//  FUNCTION: HRESULT RegisterApps()
//
//  PURPOSE: Register the application notifications.
//
HRESULT RegisterApps()
{
  HRESULT hr;
  NOTIFICATIONCONDITION nc;
  TCHAR szExePath[MAX_PATH];
  TCHAR szThisPath[MAX_PATH];

  // Make sure we aren't already registered.
  UnregisterApps();

  // Get the path to this application.
  GetModuleFileName(NULL, szThisPath, MAX_PATH);

  // Need to put a quote before and after the path, in case the path contains spaces.
  StringCchCopy(szExePath, MAX_PATH, L"\"");
  StringCchCat(szExePath, MAX_PATH, szThisPath);
  StringCchCat(szExePath, MAX_PATH, L"\"");

  // Notify us of any change in the value and set the bitmask of the value to check.
  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYSTRENGTH_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register battery strength notification.
  hr = RegistryNotifyApp(
                SN_POWERBATTERYSTRENGTH_ROOT,
                SN_POWERBATTERYSTRENGTH_PATH,
                SN_POWERBATTERYSTRENGTH_VALUE,
                c_wszAppBattStrengthName,
                szExePath,                      // Path to our app so that BattStat will be launched if it is not already running.
                NULL,
                NULL,
                WM_CHANGE_BATTSTRENGTH,
                RNAF_NONAMEONCMDLINE,         // Don't pass along anything on the command line.
                &nc
                );

  if (FAILED(hr))
  {
    goto Error;
  }

  
  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYSTATE_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register battery state notification.
  hr = RegistryNotifyApp(
                SN_POWERBATTERYSTATE_ROOT,
                SN_POWERBATTERYSTATE_PATH,
                SN_POWERBATTERYSTATE_VALUE,
                c_wszAppBattStateName,
                szExePath,
                NULL,
                NULL,
                WM_CHANGE_BATTSTATE,
                0,                      // Command line will contain   "/notify <notification name>".
                &nc
                );

  if (FAILED(hr))
  {
    goto Error;
  }

  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYBACKUPSTRENGTH_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register backup battery strength notification.
  hr = RegistryNotifyApp(
                SN_POWERBATTERYBACKUPSTRENGTH_ROOT,
                SN_POWERBATTERYBACKUPSTRENGTH_PATH,
                SN_POWERBATTERYBACKUPSTRENGTH_VALUE,
                c_wszAppBackupStrengthName,
                szExePath,
                NULL,
                NULL,
                WM_CHANGE_BACKUPSTRENGTH,
                RNAF_NONAMEONCMDLINE,           // Don't pass along anything on the command line.
                &nc
                );

  if (FAILED(hr))
  {
    goto Error;
  }

  nc.ctComparisonType = REG_CT_ANYCHANGE;
  nc.dwMask           = SN_POWERBATTERYBACKUPSTATE_BITMASK;
  nc.TargetValue.dw   = 0;

  // Register backup battery state notification.
  hr = RegistryNotifyApp(
                SN_POWERBATTERYBACKUPSTATE_ROOT,
                SN_POWERBATTERYBACKUPSTATE_PATH,
                SN_POWERBATTERYBACKUPSTATE_VALUE,
                c_wszAppBackupStateName,
                szExePath,
                NULL,
                NULL,
                WM_CHANGE_BACKUPSTATE,
                0,                        // Command line will contain   "/notify <notification name>".
                &nc
                );

  if (FAILED(hr))
  {
    goto Error;
  }

Error:

  return hr;
}


//
//  FUNCTION: HRESULT UnregisterWindows()
//
//  PURPOSE: Unregister all window notifications.
//
HRESULT UnregisterWindows()
{
  long lNotifyIndx;

  // For each notification handle:
  for (lNotifyIndx=0; lNotifyIndx < NOTIFY_CNT; lNotifyIndx++)
  {
    if (g_hNotify[lNotifyIndx] != NULL)
    {
      // Close off the notification.
      RegistryCloseNotification(g_hNotify[lNotifyIndx]);
    }

    g_hNotify[lNotifyIndx] = 0;
  }

  return S_OK;
}

//
//  FUNCTION: HRESULT UnregisterApps()
//
//  PURPOSE: Unregister all application notifications.
//
HRESULT UnregisterApps()
{

  RegistryStopNotification(c_wszAppBattStrengthName);
  RegistryStopNotification(c_wszAppBattStateName);
  RegistryStopNotification(c_wszAppBackupStrengthName);
  RegistryStopNotification(c_wszAppBackupStateName);

  return S_OK;
}


//
//  FUNCTION: void BattStateCallback(HREGNOTIFY hNotify, DWORD dwUserData, 
//                                   const PBYTE pData, const UINT cbData)
//
//  PURPOSE: Callback function that is called when battery state changes.
//
void BattStateCallback(HREGNOTIFY hNotify, DWORD dwUserData, const PBYTE pData, const UINT cbData)
{
  DWORD dwBattState = 0;
  PDWORD pdwData;
  TCHAR szBattStateStr[STATUS_STRING_LEN];
    
  StringCchCopy(szBattStateStr, STATUS_STRING_LEN, L"");

  // Get the new value.
  pdwData = (DWORD *)pData;
  dwBattState = *pdwData;

  // Apply our bitmap mask and form the battery state as a string.
  dwBattState = dwBattState & SN_POWERBATTERYSTATE_BITMASK;
  GetBattStateStr(dwBattState, szBattStateStr);

  // Update the status text.
  SetDlgItemText(g_hCurWndDialog, IDC_BATTSTATE, szBattStateStr);

}
