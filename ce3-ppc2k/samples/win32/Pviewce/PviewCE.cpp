// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   PViewCE.cpp
//
//  PURPOSE:   Implement the windows procedure for the main application
//    windows.  Also implement the basic message and command dispatchers.
//
//  FUNCTIONS:
//    WndProc            - Processes messages for the main window.
//    MsgCommand         - Handle WM_COMMAND messages for the main window.
//    MsgCreate          - Handles the WM_CREATE message.
//    MsgPaint           - Redraws divider bar
//    MsgSize            - Resizes app and all child controls
//    MsgLButtonDown     - Starts redrawing divider bar
//    MsgLButtonUp       - Ends redrawing divider bar
//    MsgMouseMove       - Helps redraw divider bar
//    MsgNotify          - Handles notification messages from child controls
//    MsgActivateApp     - Refreshes the process list when app is activated
//    MsgDisplayChange   - Resizes application if display dimensions change
//    MsgDestroy         - Handles the WM_DESTROY message by calling
//                         PostQuitMessage().
//    CmdRefreshDisplay  - Refreshes the process list
//    CmdShowThreads     - Shows the Thread list window
//    CmdShowModules     - Shows the Module list window
//    CmdRefreshDisplay  - Refreshes the process list
//    CmdKillProcess     - Handles the menu/toolbar item that allows the
//                         user to kill a process
//    CmdExit            - Handles the file exit command by calling destory
//                         window on the main window.
//
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include <commctrl.h>
#include "globals.h"            // prototypes specific to this application
#include "resource.h"
#include "listview.h"
#include "procthrd.h"

#if _WIN32_WCE > 211//non-Rapier devices
#include <aygshell.h>
#endif

//Menu Bar Height
#define MENU_HEIGHT 26


//-------------------------------------------------------------------------
// Manifest constants

#define DIVIDER_HEIGHT  7  // height of the resizing divider (height - 1)
#define TOP_HEIGHT      27 // height at the top to reserve for controls
#define BOTTOM_HEIGHT   0  // height at the bottom to reserve for controls


//-------------------------------------------------------------------------
// Useful application-global variables defined here!
HWND g_hwndMain    = NULL;
HWND g_hwndProcess = NULL;
HWND g_hwndThread  = NULL;
HWND g_hwndModule  = NULL;
HWND hwndCB = NULL;

eActiveList fActiveWindow; //enum of the active lower window

//-------------------------------------------------------------------------
// Useful static global variables defined here!
static RECT g_rcClient;             // Save the client area so the controls
//   can remain proportionally sized
static RECT g_rcDivider;            // Position of the divider between
//   the controls
static LONG g_lPrevPos;             // Previous mouse position for resizing
static LONG g_lToolbarHeight;       // Height of the toolbar
static double g_dDividerProportion;   // Proportion of the screen that the
//   is at divider
static HCURSOR g_hcurResize;        // Resizing cursor handle


// Main window message table definition.
MSD rgmsd[] =
{
	
  {WM_COMMAND,        MsgCommand},
  {WM_PAINT,          MsgPaint},
  {WM_SIZE,           MsgSize},
  {WM_LBUTTONDOWN,    MsgLButtonDown},
  {WM_LBUTTONUP,      MsgLButtonUp},
  {WM_MOUSEMOVE,      MsgMouseMove},
  {WM_NOTIFY,         MsgNotify},
  {WM_ACTIVATE,    MsgActivateApp},
  //{WM_DISPLAYCHANGE,  MsgDisplayChange},
  {WM_CREATE,         MsgCreate},
  {WM_DESTROY,        MsgDestroy}
};

MSDI msdiMain =
{
  sizeof(rgmsd) / sizeof(MSD),
    rgmsd,
    edwpWindow
};


// Main window command table definition.
CMD rgcmd[] =
{
  {ID_FILE_EXIT,       CmdExit},
  {ID_PROCESS_REFRESH, CmdRefreshDisplay},
  {ID_PROCESS_KILL,    CmdKillProcess},
  {ID_HELP_ABOUT,      CmdAbout},
  {ID_VIEW_THREADS,      CmdShowThreads},
  {ID_VIEW_MODULES,      CmdShowModules}
};

CMDI cmdiMain =
{
  sizeof(rgcmd) / sizeof(CMD),
    rgcmd,
    edwpWindow
};


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//    The return value depends on the message number.  If the message
//    is implemented in the message dispatch table, the return value is
//    the value returned by the message handling function.  Otherwise,
//    the return value is the value returned by the default window procedure.
//
//  COMMENTS:
//    Call the DispMessage() function with the main window's message dispatch
//    information (msdiMain) and the message specific information.
//

LRESULT CALLBACK WndProc(HWND   hwnd,
                         UINT   uMessage,
                         WPARAM wparam,
                         LPARAM lparam)
{
  return DispMessage(&msdiMain, hwnd, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Handle the WM_COMMAND messages for the main window.
//
//  PARAMETERS:
//    hwnd                                - window handle
//    uMessage                            - WM_COMMAND (Unused)
//    GET_WM_COMMAND_ID(wparam, lparam)   - Command identifier
//    GET_WM_COMMAND_HWND(wparam, lparam) - Control handle
//
//  RETURN VALUE:
//    The return value depends on the message number.  If the message
//    is implemented in the message dispatch table, the return value is
//    the value returned by the message handling function.  Otherwise,
//    the return value is the value returned by the default window procedure.
//
//  COMMENTS:
//    Call the DispCommand() function with the main window's command dispatch
//    information (cmdiMain) and the command specific information.
//


LRESULT MsgCommand(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  return DispCommand(&cmdiMain, hwnd, wparam, lparam);
}


//
//  FUNCTION: MsgCreate(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Performs initialization needed at window creation time
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - WM_CREATE      (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Returns 0 if all initialization was successful, or -1 if any part
//    of the initialization failed.
//
//  COMMENTS:
//    Returning 0 allows the window to continue being created while -1
//    forces the creation to fail.
//


LRESULT MsgCreate(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  RECT  rcToolbar   = {0};
  
  // Save the main window handle for accelerators
  g_hwndMain = hwnd;
	//MessageBox(NULL, L"WM_CREATE", NULL, MB_OK);

 #if _WIN32_WCE > 211 //Rapier devices
       SHMENUBARINFO mbi;
        
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hwnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = hInst;
        mbi.nBmpId     = IDB_TOOLBAR;
        mbi.cBmpImages = 2;	
        
        SHCreateMenuBar(&mbi);
        hwndCB = mbi.hwndMB;
        
#elif _WIN32_WCE < 212//non-Rapier devices
        
        hwndCB = CommandBar_Create(hInst, hwnd, 1);			
        CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);
        
        CommandBar_AddBitmap(hwndCB, hInst, IDB_TOOLBAR, 2, 0, 0); 
        
        TBBUTTON tb1 = { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, -1};
        TBBUTTON tb2 = { 1, ID_PROCESS_REFRESH, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, 0, 0, 0, -1};
        TBBUTTON tb3 = { 0, ID_PROCESS_KILL, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, 0, 0, 0, -1 };
        
        CommandBar_InsertButton(hwndCB, 1, &tb1);
        CommandBar_InsertButton(hwndCB, 2, &tb2);
        CommandBar_InsertButton(hwndCB, 3, &tb3);
        
        CommandBar_AddAdornments(hwndCB, 0, 0);
#endif

  // Create the listview controls for the process list and thread list.
  // If the windows were not created, show the error and exit the program.
  g_hwndProcess = CreateListView(hwnd,
    WS_CHILD|LVS_REPORT|LVS_SINGLESEL|
    LVS_SHOWSELALWAYS|WS_TABSTOP,
    acdProcess,
    CPROCESSCOLUMNS,
    IDC_PROCESS);
  if (!g_hwndProcess)
    return (-1);
  
  g_hwndThread = CreateListView(hwnd,
    WS_CHILD|LVS_REPORT|LVS_SINGLESEL|WS_TABSTOP,
    acdThread,
    CTHREADCOLUMNS,
    IDC_THREAD);
  if (!g_hwndThread)
    return (-1);
  
  g_hwndModule = CreateListView(hwnd,
    WS_CHILD|LVS_REPORT|LVS_SINGLESEL|WS_TABSTOP,
    acdModule,
    CMODULECOLUMNS,
    IDC_MODULE);
  if (!g_hwndModule)
    return (-1);

  // Subclass the thread list view so that we can set the focus back to
  // the process list view if the user should select anything in the
  // thread list view.
  g_lpfnThreadListView = (FARPROC)SetWindowLong(g_hwndThread,
    GWL_WNDPROC,
    (LONG)LV_Thread_Subclass);
  
  // Subclass the module list view so that we can set the focus back to
  // the process list view if the user should select anything in the
  // thread list view.
  g_lpfnModuleListView = (FARPROC)SetWindowLong(g_hwndModule,
    GWL_WNDPROC,
    (LONG)LV_Module_Subclass);
  
  // The listview controls were created correctly, so show them
  ShowWindow(g_hwndProcess, SW_SHOW);
  ShowWindow(g_hwndThread, SW_SHOW);
  ShowWindow(g_hwndModule, SW_HIDE);

#if _WIN32_WCE > 211 //Rapier devices
  HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);      
#elif _WIN32_WCE < 212//non-Rapier devices
  HMENU hm = CommandBar_GetMenu(hwndCB, 0);      
#endif
  CheckMenuRadioItem(hm, ID_VIEW_THREADS, ID_VIEW_MODULES, ID_VIEW_THREADS, MF_BYCOMMAND);
  fActiveWindow = ThreadWindow;

  // Set the initial size of the client area and divider position
  GetClientRect(hwnd, &g_rcClient);
  
  // make room at the top and bottom for any controls
  
#if _WIN32_WCE < 212//non-Rapier devices
  g_rcClient.top += CommandBar_Height(hwndCB);
  g_rcClient.bottom -= (BOTTOM_HEIGHT + g_rcClient.top);
#endif
  
  // The initial divider proportion is 50%
  g_dDividerProportion = 0.50;
  
  // The initial divider position is mid way down the client area
  g_rcDivider.top = (LONG) ((g_rcClient.bottom - g_rcClient.top)
    * g_dDividerProportion) + g_rcClient.top;
  g_rcDivider.bottom = g_rcDivider.top + DIVIDER_HEIGHT;
  g_rcDivider.left = 0;
  g_rcDivider.right = g_rcClient.right;
  
  
  // Update the information in the process list
  RefreshProcessList(g_hwndProcess);
  
  return 0;
}


//
//  FUNCTION: MsgPaint(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Repaints the divider bar between the process and thread lists.
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - WM_PAINT       (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgPaint(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  PAINTSTRUCT ps;
  HDC      hdc;
  
  hdc = BeginPaint(hwnd, &ps);
  
  DrawEdge(hdc, &g_rcDivider, EDGE_RAISED, BF_TOP | BF_BOTTOM | BF_MIDDLE);
  
  EndPaint(hwnd, &ps);
  
  return 0;
}


//
//  FUNCTION: MsgSize(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Resizes all controls proportionally within the main window
//            when the main window is resized.
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - WM_SIZE
//    wparam    - Resizing type
//    lparam    - New Width & Height of the window
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgSize(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  int cx = LOWORD(lparam);
  int cy = HIWORD(lparam);
  
  
  // store the client area size for the next time we have to do this
  g_rcClient.right = cx;
  g_rcClient.bottom = cy - BOTTOM_HEIGHT - g_rcClient.top;
  
  // set the new divider position to a proportional position
  g_rcDivider.top = (LONG) ((g_rcClient.bottom + g_rcClient.top)
    * g_dDividerProportion);
  g_rcDivider.bottom = g_rcDivider.top + DIVIDER_HEIGHT;
  g_rcDivider.right = cx;
  
  // Update the positions of the controls
  MoveWindow(g_hwndProcess, 0, g_rcClient.top, cx,
    (g_rcDivider.top - g_rcClient.top), TRUE);
  MoveWindow(g_hwndThread, 0, g_rcDivider.bottom + 1, cx,
    (g_rcClient.bottom - g_rcDivider.bottom + g_rcClient.top),
    TRUE);
  MoveWindow(g_hwndModule, 0, g_rcDivider.bottom + 1, cx,
    (g_rcClient.bottom - g_rcDivider.bottom + g_rcClient.top),
    TRUE);
 
  return 0;
}


//
//  FUNCTION: MsgLButtonDown(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Start moving the divider bar within the main window's
//            client area.
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - WM_LBUTTONDOWN (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - X, Y coordinates where mouse event occurred
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//    Works in conjunction with MsgLButtonUp and MsgMouseMove
//


LRESULT MsgLButtonDown(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  POINT pt;
  
  pt.x = LOWORD(lparam);
  pt.y = HIWORD(lparam);
  
  // Check to see if the mouse is in the divider
  if (PtInRect(&g_rcDivider, pt))
  {
    SetCapture(hwnd);       // keep track of the mouse until the
    // ..button is released;
    DrawResizeLine(hwnd, pt.y);   // draw the resizing rectangle
    g_lPrevPos = pt.y;         // save the position so the resize
    // ..rectangle can be moved
  }
  
  return 0;
}


//
//  FUNCTION: MsgLButtonUp(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Stop moving divider bar and resize process and thread
//            list views
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - WM_LBUTTONUP   (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - X, Y coordinates where mouse event occurred
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgLButtonUp(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  WORD y = HIWORD(lparam);
  
  if (GetCapture() != NULL)
  {
    // clean up from resize operation, release the capture and
    // remove the resizing line from the window
    ReleaseCapture();
    DrawResizeLine(hwnd, g_lPrevPos);
    
    // update the divider position
    g_rcDivider.top = y;
    g_rcDivider.bottom = g_rcDivider.top + DIVIDER_HEIGHT;
    
    // move the listivew controls
    MoveWindow(g_hwndProcess, 0, g_rcClient.top, g_rcClient.right,
      g_rcDivider.top - g_rcClient.top, TRUE);
    MoveWindow(g_hwndThread, 0, g_rcDivider.bottom + 1, g_rcClient.right,
      (g_rcClient.bottom - g_rcDivider.bottom + g_rcClient.top), TRUE);
    
    MoveWindow(g_hwndModule, 0, g_rcDivider.bottom + 1, g_rcClient.right,
      (g_rcClient.bottom - g_rcDivider.bottom + g_rcClient.top), TRUE);

    // find out where the divider was in proportion to the window size
    g_dDividerProportion = (double)(g_rcDivider.top) /
      (double)(g_rcClient.bottom + g_rcClient.top);
    
    // update the window
    InvalidateRect(hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
  }
  return 0;
}


//
//  FUNCTION: MsgMouseMove(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Move divider bar in client area.
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - WM_MOUSEMOVE   (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     X, Y coordinates where mouse event occurred
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgMouseMove(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  WORD x = LOWORD(lparam);
  WORD y = HIWORD(lparam);
  
  
  if (GetCapture() != NULL)
  {
    DrawResizeLine(hwnd, g_lPrevPos);   // remove the previous line
    DrawResizeLine(hwnd, y);         // draw the new resizing line in
    // .. the current position
    g_lPrevPos = y;                  // save this position for next
  }                             // .. time
  
  return 0;
}


//
//  FUNCTION: MsgNotify(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Handles notification messages from controls
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - WM_NOTIFY      (Unused)
//    wparam    - Child control ID
//    lparam    - Child control-specific information
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgNotify(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  int    idFrom  = (int)wparam;
  NMHDR *pnmhdr  = (NMHDR *)lparam;
  
  switch (pnmhdr->code)
  {
  case NM_CLICK:
    return ListView_OnClick(idFrom, (NM_LISTVIEW *) pnmhdr);
    
  case LVN_GETDISPINFO:
    return ListView_OnGetDispInfo(idFrom, (LV_DISPINFO *) pnmhdr);
    
  case LVN_DELETEITEM:
    return ListView_OnDeleteItem(idFrom, (NM_LISTVIEW *) pnmhdr);
    
  case LVN_COLUMNCLICK:
    return ListView_OnColumnClick(idFrom, (NM_LISTVIEW *) pnmhdr);
  }
  
  return 0;
}


//
//  FUNCTION: MsgActivateApp(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  To refresh the process list when application is made active.
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - WM_ACTIVATEAPP (Unused)
//    wparam    - Whether app is being activated or deactivated
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgActivateApp(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  BOOL bActivating = (BOOL)wparam;
  if (bActivating)
  {
    if (IsWindowVisible(g_hwndThread)) ListView_DeleteAllItems(g_hwndThread);
    if (IsWindowVisible(g_hwndModule)) ListView_DeleteAllItems(g_hwndModule);
    if (IsWindowVisible(g_hwndProcess)) RefreshProcessList(g_hwndProcess);
  }
  return 0;

}

//
//  FUNCTION: MsgDisplayChange(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Resizes the application if the display's dimensions change.
//
//  PARAMETERS:
//
//    hwnd      - Window handle    (Unused)
//    uMessage  - WM_DISPLAYCHANGE (Unused)
//    wparam    - Extra data       (Unused)
//    lparam    - Extra data       (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgDisplayChange(HWND hwnd,
                         UINT uMessage,
                         WPARAM wparam,
                         LPARAM lparam)
{
  static WORD cxOld, cyOld;  // Used to store old screen resolution
  // when wparam == FALSE
  WORD cxNew, cyNew;
  RECT rcWindow;
  RECT rcNewWindow;
  float cxChange, cyChange;
  
  if (wparam == FALSE)
  {
    // save the old screen resoulution
    cxOld = LOWORD(lparam);
    cyOld = HIWORD(lparam);
  }
  else
  {
    // move the window to a proportionally new size
    cxNew = LOWORD(lparam);
    cyNew = HIWORD(lparam);
    
    GetWindowRect(hwnd, &rcWindow);
    
    // Compute horizontal and vertical proportions for display
    // resolution changes
    cxChange = (float)cxNew / cxOld;
    cyChange = (float)cyNew / cyOld;
    
    // Apply proportions to the top left and bottom right corners
    // of the window.
    rcNewWindow.left   = (LONG)(rcWindow.left   * cxChange);
    rcNewWindow.right  = (LONG)(rcWindow.right  * cxChange);
    rcNewWindow.top    = (LONG)(rcWindow.top    * cyChange);
    rcNewWindow.bottom = (LONG)(rcWindow.bottom * cyChange);
    
    MoveWindow(hwnd, rcNewWindow.left, rcNewWindow.top,
      (rcNewWindow.right - rcNewWindow.left),
      (rcNewWindow.bottom - rcNewWindow.top), TRUE);
  }
  return 0;
}


//
//  FUNCTION: MsgDestroy(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Calls PostQuitMessage().
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - WM_DESTROY     (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//


LRESULT MsgDestroy(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  
#if _WIN32_WCE > 211 //Rapier devices
        DestroyWindow(hwndCB);
#elif _WIN32_WCE < 212//non-Rapier devices
        CommandBar_Destroy(hwndCB);
#endif

  PostQuitMessage(0);
  return 0;
}


//
//  FUNCTION: CmdRefreshDisplay(HWND, WORD, WORD, HWND)
//
//  PURPOSE:  Refreshes the process list.
//
//  PARAMETERS:
//    hwnd     - The window.         (unused)
//    wCommand - Command number      (unused)
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL                (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//


LRESULT CmdRefreshDisplay(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
  ListView_DeleteAllItems(g_hwndThread);
  ListView_DeleteAllItems(g_hwndModule);
  RefreshProcessList(g_hwndProcess);
  
  return 0;
}

//    CmdShowThreads     - Shows the Thread list window
LRESULT CmdShowThreads(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{

#if _WIN32_WCE > 211 //Rapier devices
  HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);      
#elif _WIN32_WCE < 212//non-Rapier devices
  HMENU hm = CommandBar_GetMenu(hwndCB, 0);      
#endif
  CheckMenuRadioItem(hm, ID_VIEW_THREADS, ID_VIEW_MODULES, ID_VIEW_THREADS, MF_BYCOMMAND);
  fActiveWindow = ThreadWindow;
  ShowWindow(g_hwndThread, SW_SHOW);
  ShowWindow(g_hwndModule, SW_HIDE);
  
  ListView_DeleteAllItems(g_hwndThread);
  //RefreshProcessList(g_hwndProcess); //Not Nes.
  
  return 0;
}

//    CmdShowModules     - Shows the Module list window
LRESULT CmdShowModules(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
#if _WIN32_WCE > 211 //Rapier devices
  HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);      
#elif _WIN32_WCE < 212//non-Rapier devices
  HMENU hm = CommandBar_GetMenu(hwndCB, 0);      
#endif
  CheckMenuRadioItem(hm, ID_VIEW_THREADS, ID_VIEW_MODULES, ID_VIEW_MODULES, MF_BYCOMMAND);
  fActiveWindow = ModuleWindow;
  ShowWindow(g_hwndModule, SW_SHOW);
  ShowWindow(g_hwndThread, SW_HIDE);
  
  ListView_DeleteAllItems(g_hwndModule);
  //RefreshProcessList(g_hwndProcess); //Not Nes.
  
  return 0;
}

//
//  FUNCTION: CmdKillProcess(HWND, WORD, WORD, HWND)
//
//  PURPOSE:  Kills a user-specified process.
//
//  PARAMETERS:
//    hwnd     - The window.         (unused)
//    wCommand - Command number      (unused)
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL                (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//

LRESULT CmdKillProcess(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
  DWORD dwPID;
  int   nKill;
  TCHAR  szMsg[MAX_PATH + 50];
  TCHAR  szExe[MAX_PATH];
  
  
  dwPID = ListView_GetSelectedPid(g_hwndProcess, szExe, sizeof(szExe));
  
  // First, make sure there is a process selected.  If so, ask user if
  // he/she is sure that the process should be killed.  Only when the
  // user is sure will we kill the process.
  
  if (dwPID != 0)
  {
    wsprintf (szMsg, L"Are you sure you want to kill\n%s", szExe);
    nKill = MessageBox (g_hwndProcess, 
      szMsg, 
      szTitle, 
      MB_YESNO|MB_DEFBUTTON2);
    if (nKill == IDYES)
    {
      KillProcess (dwPID);
      RefreshProcessList (g_hwndProcess);
    }
  }
  
  return 0;
}


//
//  FUNCTION: CmdExit(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Exit the application.
//
//  PARAMETERS:
//    hwnd     -  The window.         (unused)
//    wCommand -  Command number      (unused)
//    wNotify  -  Notification number (unused)
//    hwndCtrl -  NULL                (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//

LRESULT CmdExit(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
  DestroyWindow(hwnd);
  return 0;
}
