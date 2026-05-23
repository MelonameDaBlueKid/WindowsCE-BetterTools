/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"


//------------------------------------------------------
// Globals
//------------------------------------------------------
#define ITEM_COUNT   500000

HINSTANCE   g_hInst;
TCHAR szAppName[] = TEXT("VirtListView Application");
TCHAR szTitle[]   = TEXT("VirtListView");
static HWND hwndListView;

HWND			g_hwndCB = NULL;       // Handle to a commandband

//------------------------------------------------------
// Forwards
//------------------------------------------------------
HWND CreateListView(HINSTANCE , HWND );
BOOL InitListView(HWND );
LRESULT ListViewNotify(HWND, LPARAM);
void SwitchView(HWND, DWORD, UINT);
BOOL InsertListViewItems(HWND);
void ResizeListView(HWND , HWND );


//Boilerplate
BOOL InitApplication(HINSTANCE );
BOOL InitInstance(HINSTANCE ,int );
LRESULT CALLBACK MainWndProc( HWND ,UINT ,WPARAM ,LPARAM );

//------------------------------------------------------
// WinMain
//------------------------------------------------------
int WINAPI  WinMain(  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
  MSG  msg;
  
  g_hInst = hInstance;
  
  if(!hPrevInstance)
    if(!InitApplication(hInstance))
      return FALSE;
    //required to use the common controls
    InitCommonControls();
    if (!InitInstance(hInstance, nCmdShow))
      return FALSE;
    while(GetMessage( &msg, NULL, 0x00, 0x00))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    
    return msg.wParam;
}


//------------------------------------------------------
// InitApplication
//------------------------------------------------------
BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wcex;
  ATOM        aReturn;
  
  wcex.style           = 0;
  wcex.lpfnWndProc     = (WNDPROC)MainWndProc;
  wcex.cbClsExtra      = 0;
  wcex.cbWndExtra      = 0;
  wcex.hInstance       = hInstance;
  wcex.hCursor         = 0;
  wcex.hbrBackground   = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName    = 0;
  wcex.lpszClassName   = szAppName;
  wcex.hIcon           = 0;
  aReturn = RegisterClass(&wcex);
  return aReturn;
}

//------------------------------------------------------
// InitInstance
//------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance,int nCmdShow){
  HWND     hWnd;
  g_hInst = hInstance;
  hWnd = CreateWindowEx(  0,szAppName,szTitle,WS_VISIBLE,
    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
    NULL,NULL,hInstance,NULL);
  //When the main window is created using CW_USEDEFAULT the height of the menubar (if one
  // is created is not taken into account). So we resize the window after creating it
  // if a menubar is present
  {
    RECT rc;
    GetWindowRect(hWnd, &rc);
    rc.bottom -= MENU_HEIGHT;
    if (g_hwndCB)
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
  }
  ResizeListView(hwndListView, GetParent(hwndListView));
  
  if (!hWnd)
    return FALSE;
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return TRUE;
}

//------------------------------------------------------
// MainWndProc
//------------------------------------------------------
LRESULT CALLBACK MainWndProc( HWND hWnd,UINT uMessage,WPARAM wParam,LPARAM lParam){
  
  switch (uMessage)
  {
  case WM_CREATE:
    //Create a MenuBar
    SHMENUBARINFO mbi;
    memset(&mbi, 0, sizeof(SHMENUBARINFO));
    mbi.cbSize     = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hWnd;
    mbi.nToolBarId = IDM_MAIN_MENU;
    mbi.hInstRes   = g_hInst;
    mbi.nBmpId     = 0;
    mbi.cBmpImages = 0;	
    
    SHCreateMenuBar(&mbi);
    if (!SHCreateMenuBar(&mbi))
      MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
    g_hwndCB = mbi.hwndMB;
    
    // create the ListView control
    hwndListView = CreateListView(g_hInst, hWnd);
    //initialize the ListView control
    InitListView(hwndListView);
    break;
    
  case WM_NOTIFY:
    return ListViewNotify(hWnd, lParam);
    
  case WM_SIZE:
    ResizeListView(hwndListView, hWnd);
    break;
    
  case WM_COMMAND:
    switch (GET_WM_COMMAND_ID(wParam, lParam))
    {
    case IDM_LARGE_ICONS:
      SwitchView(hwndListView, LVS_ICON, IDM_LARGE_ICONS);
      break;
      
    case IDM_SMALL_ICONS:
      SwitchView(hwndListView, LVS_SMALLICON, IDM_SMALL_ICONS);
      break;
      
    case IDM_LIST:
      SwitchView(hwndListView, LVS_LIST, IDM_LIST);
      break;
      
    case IDM_REPORT:
      SwitchView(hwndListView, LVS_REPORT, IDM_REPORT);
      break;
      
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
      
    }
    break;
    
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
      
    default:
      break;
  }
  return DefWindowProc(hWnd, uMessage, wParam, lParam);
}


//------------------------------------------------------
// AboutDlgProc(HWND, WORD, WORD, LONG)
//------------------------------------------------------
BOOL CALLBACK  AboutDlgProc( HWND hDlg, UINT message, WPARAM wParam, LONG lParam){
  if (message == WM_COMMAND){
    EndDialog(hDlg, TRUE);
    return(TRUE);
  }
  if (message == WM_INITDIALOG)
    return(TRUE);
  else
    return(FALSE);
  UNREFERENCED_PARAMETER(wParam);
  UNREFERENCED_PARAMETER(lParam);
}


// Important code below:
//------------------------------------------------------
// CreateListView
//------------------------------------------------------
HWND CreateListView(HINSTANCE hInstance, HWND hwndParent){
  DWORD       dwStyle;
  HWND        hwndListView;
  HIMAGELIST  himlSmall;
  HIMAGELIST  himlLarge;
  BOOL        bSuccess = TRUE;
  
  dwStyle =   WS_TABSTOP | 
    WS_CHILD | 
    WS_VISIBLE |
    LVS_AUTOARRANGE |
    LVS_REPORT | 
    LVS_OWNERDATA;
  
  //Create the LISTVIEW here
  //Use the following params if you want to create the listview in position
  // ResizeListView would then not be necessary 
  // RECT  rc;
  // GetClientRect(hwndParent, &rc);
  // in the createwindow use: rc.left, rc.top + g_nCBrHeight, rc.right-rc.left, rc.bottom- (rc.top + g_nCBrHeight)
  
  hwndListView = CreateWindow( 
    WC_LISTVIEW,               // class name - defined in commctrl.h
    TEXT(""),                        // dummy text
    dwStyle,                   // style
    0,                         // x position
    0,                         // y position
    0,                         // width
    0,                         // height
    hwndParent,                // parent
    (HMENU)ID_LISTVIEW,        // ID
    g_hInst,                   // instance
    NULL);                     // no extra data
  
  if(!hwndListView)
    return NULL;
  
  ResizeListView(hwndListView, hwndParent);
  
  //create an the image list for the ListView
  himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
  himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);
  
  if (himlSmall && himlLarge)
  {
    HICON hIcon;
    
    //set up the small image list
    hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    ImageList_AddIcon(himlSmall, hIcon);
    
    //set up the large image list
    hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON)); 
    ImageList_AddIcon(himlLarge, hIcon);
    
    ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
    ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
  }
  
  return hwndListView;
}

//------------------------------------------------------
// ResizeListView
//------------------------------------------------------
void ResizeListView(HWND hwndListView, HWND hwndParent)
{
  RECT  rc;
  GetClientRect(hwndParent, &rc);
  MoveWindow( hwndListView, rc.left, 
    rc.top, rc.right, rc.bottom - MENU_HEIGHT, TRUE);
}

//------------------------------------------------------
// InitListView
//------------------------------------------------------
BOOL InitListView(HWND hwndListView)
{
  LV_COLUMN   lvColumn;
  int         i;
  TCHAR       szString[5][20] = {TEXT("Main Column"), 
    TEXT("Column 1"),
    TEXT("Column 2"), 
    TEXT("Column 3"), 
    TEXT("Column 4")};
  
  //empty the list
  ListView_DeleteAllItems(hwndListView);
  
  //initialize the columns
  lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
  lvColumn.fmt = LVCFMT_LEFT;
  lvColumn.cx = 120;
  for(i = 0; i < 5; i++)
  {
    lvColumn.pszText = szString[i];
    ListView_InsertColumn(hwndListView, i, &lvColumn);
  }
  
  InsertListViewItems(hwndListView);
  
  return TRUE;
}

//------------------------------------------------------
// InsertListViewItems
//------------------------------------------------------
BOOL InsertListViewItems(HWND hwndListView)
{
  //empty the list
  ListView_DeleteAllItems(hwndListView);
  
  //set the number of items in the list
  ListView_SetItemCount(hwndListView, ITEM_COUNT);
  
  return TRUE;
}

//------------------------------------------------------
// ListViewNotify (WM_NOTIFY handler for the ListView control)
// This is used for a virtual listviewer
//------------------------------------------------------
LRESULT ListViewNotify(HWND hWnd, LPARAM lParam)
{
  LPNMHDR  lpnmh = (LPNMHDR) lParam;
  HWND     hwndListView = GetDlgItem(hWnd, ID_LISTVIEW);
  
  switch(lpnmh->code)
  {
  case LVN_GETDISPINFO:
    {
      LV_DISPINFO *lpdi = (LV_DISPINFO *)lParam;
      TCHAR szString[MAX_PATH];
      
      if(lpdi->item.iSubItem)
      {
        if(lpdi->item.mask & LVIF_TEXT)
        {
          wsprintf(szString, TEXT("Item %d - Column %d"), lpdi->item.iItem + 1, lpdi->item.iSubItem);
          lstrcpy(lpdi->item.pszText, szString);
        }
      }
      else
      {
        if(lpdi->item.mask & LVIF_TEXT)
        {
          wsprintf(szString, TEXT("Item %d"), lpdi->item.iItem + 1);
          lstrcpy(lpdi->item.pszText, szString);
        }
        
        if(lpdi->item.mask & LVIF_IMAGE)
        {
          lpdi->item.iImage = 0;
        }
      }
    }
    return 0;
    
  case LVN_ODFINDITEM:
    {
      LPNMLVFINDITEM lpFindItem = (LPNMLVFINDITEM)lParam;
      // Used if you are trying to find an item in the list view
    }
    return 0;
  }
  
  return 0;
}

//------------------------------------------------------
// SwitchView (Changes from report/icon/etc.. views
//------------------------------------------------------
void SwitchView(HWND hwndListView, DWORD dwView, UINT idMenuPos){
  DWORD dwStyle = GetWindowLong(hwndListView, GWL_STYLE);
  SetWindowLong(hwndListView, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
  
  //
  HMENU hMenu = SHMenuBar_GetMenu(g_hwndCB, IDM_MAIN_MENUITEM2);
  CheckMenuRadioItem(hMenu, IDM_LARGE_ICONS, IDM_REPORT, idMenuPos, MF_BYCOMMAND);
  
  ResizeListView(hwndListView, GetParent(hwndListView));
}
