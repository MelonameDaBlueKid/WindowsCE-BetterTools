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
// dynamenu.cpp : Defines the entry point for the application.
// 

#include "stdafx.h"
#include "dynamenu.h"
#include <commctrl.h>


//The position of the color option popmenu on the toplevel menu
#define ID_COLOR_OPTION_MENUITEM 1
#define ID_RADIO_OPTION_MENUITEM 2

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND          hwndMain;
HWND				hwndCB;			// The command bar handle
TCHAR      	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	      szWindowClass[MAX_LOADSTRING];		// The window class name

// This is the number of possible text colors.  It should match the
// number of checkboxes which appear in the color options dialog.
const int NUM_TEXTCOLOR = 4;

// This is the maximum length of a color name.
const int MAX_COLORLEN = 20;

// This structure defines the relationship between a color name,
// menu ID, and COLORREF value.  By defining this array, we don't
// depend on the menu IDs being in any particular order, or being
// sequential.
struct DynaMenuDef {
  UINT 	m_nString;					// color name (in string table)
  UINT     m_nID;                      // menu ID
  COLORREF m_crf;                      // color value
};

// This array defines the possible text colors.  There is a one-to-one
// correspondence with m_abAllowColor. m_iColor is an index into both arrays.
DynaMenuDef m_aColorDef[NUM_TEXTCOLOR] =
{
  { IDS_BLACK,    ID_COLOR1, RGB(0, 0, 0) },
  { IDS_LTGRAY,   ID_COLOR2, RGB(192, 192, 192) },
  { IDS_DKGRAY,   ID_COLOR3, RGB(128, 128, 128) },
  { IDS_WHITE,    ID_COLOR4, RGB(255, 255, 255) },
};

int  m_iColor;                      // current text color
BOOL m_abAllowColor[NUM_TEXTCOLOR]; // flags whether colors may be used
int  m_iDrawText = ID_MENUITEM3_RADIO1;                   // id of menu string to draw


// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChangeColorDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void RefreshColorMenu(HWND hwndMenuBar);
void DoSelectColor(int iColor, HWND hwndMenuBar);
void DoSelectRadioMenuItem(int idMenuItem, HWND hwndMenuBar);


int WINAPI WinMain(	HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine,int       nCmdShow)
{
  MSG msg;
  HWND hwndThis = NULL;
  
  LoadString(hInstance, IDC_DYNAMENU, szWindowClass, MAX_LOADSTRING);
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  
  // Check if this app. is running
  if (FindWindow(szWindowClass, szTitle)){
    SetForegroundWindow(FindWindow(szWindowClass, szTitle));
    return FALSE;
  }
  
  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow)) 
  {
    return FALSE;
  }
  
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
  WNDCLASS	wc;
  
  wc.style			= CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc		= (WNDPROC) WndProc;
  wc.cbClsExtra		= 0;
  wc.cbWndExtra		= 0;
  wc.hInstance		= hInstance;
  wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DYNAMENU));
  wc.hCursor			= 0;
  wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName		= 0;
  wc.lpszClassName	= szWindowClass;
  
  return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND	hWnd;
  
  hInst = hInstance;		// Store instance handle in our global variable
  // Initialize global strings
  MyRegisterClass(hInstance, szWindowClass);
  
  hwndMain = hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  
  if (!hWnd){	
    return FALSE;
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
#if _WIN32_WCE < 212//non-Pocket PC devices
  if (hwndCB)
    CommandBar_Show(hwndCB, TRUE);
#endif
  
  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  TCHAR szDrawText[MAX_LOADSTRING];
  
#if _WIN32_WCE > 211 //Pocket PC devices
  SHMENUBARINFO mbi;
#endif
  
  switch (message) 
  {
		case WM_COMMAND:
      wmId    = LOWORD(wParam); 
      wmEvent = HIWORD(wParam); 
      // Parse the menu selections:
      switch (wmId)
      {
      case ID_COLOR1:
      case ID_COLOR2:
      case ID_COLOR3:
      case ID_COLOR4:
        DoSelectColor(wmId - ID_COLOR1, hwndCB);
        break;
        
      case ID_MENUITEM3_RADIO1:
      case ID_MENUITEM3_RADIO2:
      case ID_MENUITEM3_RADIO3:
        DoSelectRadioMenuItem(wmId, hwndCB);
        break;
        
      case ID_COLOR_OPTIONS:
        DialogBox(hInst, (LPCTSTR)IDD_CHANGECOLOR, hWnd, (DLGPROC)ChangeColorDlg);
        RefreshColorMenu(hwndCB);
  //refresh screen
  InvalidateRect(hwndMain, NULL, TRUE);
  UpdateWindow(NULL);
        break;
        
      case IDM_ABOUT:
        DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
        break;
        
      case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
        
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
      case WM_CREATE:
        {
#if _WIN32_WCE > 211 //Pocket PC devices
          
          memset(&mbi, 0, sizeof(SHMENUBARINFO));
          mbi.cbSize     = sizeof(SHMENUBARINFO);
          mbi.hwndParent = hWnd;
          mbi.nToolBarId = IDM_MAIN_MENU;
          mbi.hInstRes   = hInst;
          mbi.nBmpId     = 0;
          mbi.cBmpImages = 0;	
          
          SHCreateMenuBar(&mbi);
          //retain the hwnd to the toolbar to destroy it if necessary
          //note: the height of the toolbar is 26
          //#define MENU_HEIGHT 26
          hwndCB = mbi.hwndMB;
          
#elif _WIN32_WCE < 212//non-Pocket PC devices
          
          hwndCB = CommandBar_Create(hInst, hWnd, 1);			
          CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);
          CommandBar_AddAdornments(hwndCB, 0, 0);
          
#endif
          // Initialize data.  Start out by allowing all possible
          // text colors and default to using the first one.
          m_iColor = 0;
          for (int i = 0; i < NUM_TEXTCOLOR; i++)
            m_abAllowColor[i] = TRUE;
          RefreshColorMenu(hwndCB);
          DoSelectColor(0, hwndCB);
          DoSelectRadioMenuItem(m_iDrawText, hwndCB);
          
        }      
        break;
      case WM_PAINT:
        {
          RECT rt;
          hdc = BeginPaint(hWnd, &ps);
          // set color to use for text
          int iColor   = m_iColor;
          
          SetTextColor(hdc, m_aColorDef[iColor].m_crf);
          SetBkMode(hdc,TRANSPARENT);
          
          GetClientRect(hWnd, &rt);
          
          {	
            HMENU hRadioItemMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM3);
            MENUITEMINFO mii;
            memset((char *)&mii, 0, sizeof(mii));
            mii.cbSize = sizeof(mii); 
            mii.fMask  = MIIM_TYPE;
            mii.dwTypeData = &szDrawText[0];
            mii.cch = MAX_LOADSTRING;
            mii.fType =  MFT_STRING; 
            GetMenuItemInfo(hRadioItemMenu, m_iDrawText, FALSE, &mii);
          }
          
          DrawText(hdc, szDrawText, _tcslen(szDrawText), &rt, 
            DT_SINGLELINE | DT_VCENTER | DT_CENTER);
          EndPaint(hWnd, &ps);
        }
        break;
        
      case WM_DESTROY:
        
#if _WIN32_WCE > 211 //Pocket PC devices
        //BUGBUG Is this necessary?
        DestroyWindow(hwndCB);
#elif _WIN32_WCE < 212//non-Pocket PC devices
        CommandBar_Destroy(hwndCB);
#endif
        
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Mesage handler for the About box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  //RECT rt, rt1;
  //int DlgWidth, DlgHeight;	// dialog width and height in pixel units
  //int NewPosX, NewPosY;
  
  switch (message)
  {
		case WM_INITDIALOG:
#if _WIN32_WCE > 211 //Pocket PC devices
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
      
#elif _WIN32_WCE < 212//non-Pocket PC devices
      RECT rt, rt1;
      int DlgWidth, DlgHeight;	// dialog width and height in pixel units
      int NewPosX, NewPosY;
      // trying to center the About dialog
      if (GetWindowRect(hDlg, &rt1)) {
        GetClientRect(GetParent(hDlg), &rt);
        DlgWidth	= rt1.right - rt1.left;
        DlgHeight	= rt1.bottom - rt1.top ;
        NewPosX		= (rt.right - rt.left - DlgWidth)/2;
        NewPosY		= (rt.bottom - rt.top - DlgHeight)/2;
        
        // if the About box is larger than the physical screen 
        if (NewPosX < 0) NewPosX = 0;
        if (NewPosY < 0) NewPosY = 0;
        SetWindowPos(hDlg, 0, NewPosX, NewPosY,
          0, 0, SWP_NOZORDER | SWP_NOSIZE);
      }
#endif


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

// Mesage handler for the ChangeColorDlg box.
LRESULT CALLBACK ChangeColorDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  //RECT rt, rt1;
  //int DlgWidth, DlgHeight;	// dialog width and height in pixel units
  //int NewPosX, NewPosY;
  int wmId, wmEvent;
  
  switch (message)
  {
		case WM_INITDIALOG:
      {
        // set the text of each color checkbox
        for (int i = 0; i < NUM_TEXTCOLOR; i++)
        {
          HWND hwCtl = GetDlgItem(hDlg, i + IDC_COLOR1);
          TCHAR strColor[MAX_LOADSTRING];
          LoadString(hInst, IDS_BLACK + i, strColor, MAX_LOADSTRING);
          SetWindowText(hwCtl, strColor);
        }
        //Set check value
        for (int i = 0; i < NUM_TEXTCOLOR; i++)
          if (m_abAllowColor[i]) Button_SetCheck(GetDlgItem(hDlg,IDC_COLOR1 + i), TRUE);
          
#if _WIN32_WCE > 211 //Pocket PC devices
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
      
#elif _WIN32_WCE < 212//non-Pocket PC devices
      RECT rt, rt1;
      int DlgWidth, DlgHeight;	// dialog width and height in pixel units
      int NewPosX, NewPosY;
      // trying to center the About dialog
      if (GetWindowRect(hDlg, &rt1)) {
        GetClientRect(GetParent(hDlg), &rt);
        DlgWidth	= rt1.right - rt1.left;
        DlgHeight	= rt1.bottom - rt1.top ;
        NewPosX		= (rt.right - rt.left - DlgWidth)/2;
        NewPosY		= (rt.bottom - rt.top - DlgHeight)/2;
        
        // if the About box is larger than the physical screen 
        if (NewPosX < 0) NewPosX = 0;
        if (NewPosY < 0) NewPosY = 0;
        SetWindowPos(hDlg, 0, NewPosX, NewPosY,
          0, 0, SWP_NOZORDER | SWP_NOSIZE);
      }
#endif
      }
      return TRUE;
      
    case WM_COMMAND:
      wmId    = LOWORD(wParam); 
      wmEvent = HIWORD(wParam); 
      // Parse the menu selections:
      switch (wmId){
      case IDOK:
        {
          //Set new check value
          for (int i = 0; i < NUM_TEXTCOLOR; i++)
            m_abAllowColor[i] = Button_GetCheck(GetDlgItem(hDlg,IDC_COLOR1 + i));
          EndDialog(hDlg, LOWORD(wParam));
        }
        return TRUE;
      case IDCANCEL:
        //Don't set new check value
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;
        break;
      }
  }
  return FALSE;
}


UINT wce_GetMenuItemID(HMENU hMenu, int nPos)
{	
  MENUITEMINFO mii;
  memset((char *)&mii, 0, sizeof(mii));
  mii.cbSize = sizeof(mii); 
  mii.fMask  = MIIM_ID; 
  GetMenuItemInfo(hMenu, nPos, TRUE, &mii);
  
  return mii.wID; 
}

////////////////////////////
void RefreshColorMenu(HWND hwndMenuBar)
{
  HMENU hColorMenu = SHGetSubMenu(hwndMenuBar, IDM_MAIN_MENUITEM2);
  
  // Delete existing color options
  for (int i = 0; i < NUM_TEXTCOLOR; i++)
    DeleteMenu(hColorMenu, m_aColorDef[i].m_nID, MF_BYCOMMAND);
  
  // Delete the separator
  if (wce_GetMenuItemID(hColorMenu, 0) == 0)	// SEPERATOR
    DeleteMenu(hColorMenu, 0, MF_BYPOSITION);
  
  int nColors = 0;
  // Insert chosen color options
  for (int i = 0; i < NUM_TEXTCOLOR; i++)
  {
    if (m_abAllowColor[i] == TRUE)
    {
      TCHAR strColor[MAX_LOADSTRING];
      LoadString(hInst, m_aColorDef[i].m_nString, strColor, MAX_LOADSTRING);
      InsertMenu(hColorMenu, ID_COLOR_OPTIONS, MF_STRING,
        m_aColorDef[i].m_nID, strColor);
      nColors++;
    }
  }
  
  // Add separator if there are any color options
  if (nColors > 0)
    InsertMenu(hColorMenu, ID_COLOR_OPTIONS, MF_SEPARATOR,
    0, _T(""));
  
  //check current menu item
  CheckMenuItem(hColorMenu, m_iColor + ID_COLOR1 , MF_CHECKED | MF_BYCOMMAND); 
  
  //refresh screen
  InvalidateRect(hwndMain, NULL, TRUE);
  UpdateWindow(NULL);
}


void DoSelectColor(int iColor, HWND hwndMenuBar)
{
  HMENU hColorMenu = SHGetSubMenu(hwndMenuBar, IDM_MAIN_MENUITEM2);
  
  //uncheck current menu item
  CheckMenuItem(hColorMenu, m_iColor + ID_COLOR1 , MF_UNCHECKED | MF_BYCOMMAND); 
  
  //check new menu item
  DWORD dwRet = CheckMenuItem(hColorMenu, iColor  + ID_COLOR1, MF_CHECKED | MF_BYCOMMAND);
  
  //cache new menu position
  m_iColor = iColor;
  
  //refresh screen
  InvalidateRect(hwndMain, NULL, TRUE);
  UpdateWindow(NULL);
}

void DoSelectRadioMenuItem(int idMenuItem, HWND hwndMenuBar)
{
  HMENU hRadioItemMenu = SHGetSubMenu(hwndMenuBar, IDM_MAIN_MENUITEM3);
  
  //check new menu item
  DWORD dwRet = CheckMenuRadioItem(hRadioItemMenu, ID_MENUITEM3_RADIO1, ID_MENUITEM3_RADIO3, idMenuItem , MF_BYCOMMAND);
  
  //cache new menu position
  m_iDrawText = idMenuItem;
  
  //refresh screen
  InvalidateRect(hwndMain, NULL, TRUE);
  UpdateWindow(NULL);
}


