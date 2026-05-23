// TrayTaskList.cpp : Defines the entry point for the application.
//
/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
#ifdef _WIN32_WCE_EMULATION
#error 'This does not work under emulation'
#endif

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>

#define TRAY_NOTIFYICON WM_USER + 2001
#define WMO_PALMTRAYTASKLIST WM_USER + 2002
#define ID_TRAY	5000
#define TITLE_SIZE          64 
#define PROCESS_SIZE        MAX_PATH 

#define MAX_TASKS           256 


// 
// task list structure 
// 
typedef struct _TASK_LIST { 
  DWORD cntUsage;     
  DWORD dwProcessId;// same as th32ProcessID; 
  DWORD dwInheritedFromProcessId;// same as th32ParentProcessID;     
  DWORD cntThreads; 
  DWORD th32ModuleID;     
  DWORD th32DefaultHeapID;     
  LONG  pcPriClassBase;     
  BOOL        flags; 
  HWND        hwnd; 
  TCHAR       ProcessName[PROCESS_SIZE]; 
  TCHAR       WindowTitle[TITLE_SIZE]; 
} TASK_LIST, *PTASK_LIST; 

typedef struct _TASK_LIST_ENUM { 
  PTASK_LIST  tlist; 
  DWORD       numtasks; 
} TASK_LIST_ENUM, *PTASK_LIST_ENUM; 
//
// Variables
DWORD numTasks; 
TASK_LIST tlist[MAX_TASKS]; 
DWORD             i; 
TASK_LIST_ENUM    te; 
BOOL              fTree; 
int   nSelectedTask; //tlist array index of select item in listbox

// === Function Prototypes ====================================================

BOOL WINAPI MainDlgProc( HWND, UINT, WPARAM, LPARAM );
BOOL WINAPI SampleDlgProc( HWND, UINT, WPARAM, LPARAM );
typedef BOOL (WINAPI *PROCESSWALK)(HINSTANCE hSnapshot, LPPROCESSENTRY32 lppe); 
typedef HINSTANCE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID); 
void InitProcessList(HWND hwndPPSCtList);
DWORD GetTaskListCE( PTASK_LIST  pTask, DWORD dwNumTasks ); 
BOOL EnableDebugPriv95( VOID ); 
BOOL EnableDebugPrivNT( VOID ); 
BOOL KillProcess( PTASK_LIST tlist, BOOL fForce ); 
BOOL ActivateProcess( PTASK_LIST tlist);
VOID GetWindowTitles( PTASK_LIST_ENUM te ); 
void EnableButtons();

// === Global Variables =======================================================

HINSTANCE g_hInstance;
HWND g_hMainDlg;

BOOL g_WinHide = FALSE;
BOOL g_PalmTrayTaskListActive = FALSE;

// Tray Icons and Notification ------------------------------

BOOL TrayMessage(HWND hwnd, DWORD dwMessage, UINT uID, HICON hIcon, PTSTR pszTip)
{
  BOOL res = FALSE;
  NOTIFYICONDATA tnd;
  
  tnd.cbSize		= sizeof(NOTIFYICONDATA);
  tnd.hWnd		= hwnd;
  tnd.uID			= uID;
  tnd.uFlags		= NIF_MESSAGE|NIF_ICON; //|NIF_TIP;
  tnd.uCallbackMessage	= TRAY_NOTIFYICON;
  tnd.hIcon		= hIcon;
  tnd.szTip[0] = '\0';
  
  res = Shell_NotifyIcon(dwMessage, &tnd);
  return res;
}

void TrayIconDelete(HWND hwnd, UINT uID, HICON hIcon, PTSTR pszTip)
{
  TrayMessage(hwnd, NIM_DELETE, uID, hIcon, NULL);
}

void TrayIconModify(HWND hwnd, UINT uID, HICON hIcon, PTSTR pszTip) //animate icons
{
  TrayMessage(hwnd, NIM_MODIFY, uID, hIcon, NULL);
}

void TrayIconAdd(HWND hwnd, UINT uID, HICON hIcon, PTSTR pszTip)
{
  TrayMessage(hwnd, NIM_ADD, uID,  hIcon, NULL);
}


// === Application Entry Point ================================================

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrev, LPTSTR lpCmd, int nShow )
{
  HWND hwnd;
  if (hwnd = FindWindow(NULL, L"TrayTaskList"))
  {
    SetFocus (hwnd);
    return (TRUE);
  }
  
  int retcode;
  
  g_hInstance = hInstance;   //  Save instance handle in global
  InitCommonControls();
  
  retcode = DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_PALMTRAYTASKLIST), NULL, (DLGPROC)MainDlgProc );
  
  return( FALSE );
}

// === Main Window (dialog) Proc ==============================================
BOOL WINAPI MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
  switch( msg )
  {
    
  case WM_CLOSE:
	//Clean up on Close and remove tray icons
    TrayIconDelete(hDlg, ID_TRAY, LoadIcon( g_hInstance, MAKEINTRESOURCE(APP_ICON) ), NULL);
    EndDialog( hDlg, TRUE );
    return( TRUE );

  case WM_INITDIALOG:
    g_hMainDlg = hDlg;
    EnableButtons();
    //Set Tray Icon
    TrayIconAdd(hDlg, ID_TRAY, LoadIcon( g_hInstance, MAKEINTRESOURCE(APP_ICON) ), NULL);
    SetForegroundWindow(hDlg);	// make us come to the front
    //Show the List of Processes
    PostMessage(hDlg, WM_COMMAND, (WPARAM)IDC_REFRESHBUTTON, 0);
    //
    return( TRUE );
    
  case WM_COMMAND:
    {
      switch (GET_WM_COMMAND_ID(wParam,lParam))
      {
      case IDC_PROCESSLIST:
      {
        nSelectedTask = 0;
        int nIdx = ListBox_GetCurSel(GetDlgItem(hDlg, IDC_PROCESSLIST));
        nSelectedTask = ListBox_GetItemData(GetDlgItem(hDlg, IDC_PROCESSLIST), nIdx);
        EnableButtons();
      }
        break;
        
      case IDC_ACTIVATEBUTTON:
        if (nSelectedTask)
          ActivateProcess(&tlist[nSelectedTask]);
        break;
        
      case IDC_TERMINATEBUTTON:
      {
        BOOL fChecked;
        fChecked = (BST_CHECKED == Button_GetCheck(GetDlgItem(hDlg, IDC_FORCETERM)));
        if (nSelectedTask)
          KillProcess(&tlist[nSelectedTask], FALSE);
          //KillProcess(&tlist[nSelectedTask], fChecked);
          //Show the List of Processes
          SendMessage(hDlg, WM_COMMAND, (WPARAM)IDC_REFRESHBUTTON, 0);
      }
        break;
        
      case IDC_REFRESHBUTTON:
        //Show the List of Processes
        nSelectedTask = 0;
        InitProcessList(GetDlgItem(hDlg, IDC_PROCESSLIST));
        EnableButtons();
        break;
        
      case IDCANCEL:
        {
          g_PalmTrayTaskListActive = FALSE;
          TrayIconDelete(hDlg, ID_TRAY, LoadIcon( g_hInstance, MAKEINTRESOURCE(APP_ICON) ), NULL);
          EndDialog( hDlg, TRUE );
          return( TRUE );
        }
        break;
        
      case IDOK:
        {
          //Hide window 
          if (!g_WinHide)
          {
            ShowWindow(hDlg, SW_HIDE);
            g_WinHide = TRUE;
          }
          return( TRUE );               
        }
        break;
      }
    }
    
  case TRAY_NOTIFYICON:
    switch (lParam)
    {
    case WM_LBUTTONDOWN:
      if (wParam == ID_TRAY)
      {
        g_PalmTrayTaskListActive = FALSE;
        if (g_WinHide)
        {
          //Show the List of Processes
          SendMessage(hDlg, WM_COMMAND, (WPARAM)IDC_REFRESHBUTTON, 0);
          ShowWindow(hDlg, SW_SHOW);
          SetForegroundWindow(hDlg);	// make us come to the front
          g_WinHide = FALSE;
        } else {
          g_WinHide = TRUE;
        }
      }
    }
    break;
    break;
    
  }
  return( FALSE );
}


//
void InitProcessList(HWND hwListBox){
  TCHAR sbW[MAX_PATH];
  
  // reset listbox
  ListBox_ResetContent(hwListBox);
  ListBox_SetCurSel(hwListBox, -1);
  nSelectedTask = 0;
  
  // zero the tlist array
  memset(&tlist, 0, sizeof(TASK_LIST) * MAX_TASKS);
  // get the task list for the system 
  numTasks = GetTaskListCE( tlist, MAX_TASKS ); 
  // enumerate all windows and try to get the window titles for each task 
  te.tlist = tlist; 
  te.numtasks = numTasks; 
  GetWindowTitles( &te );
  // init task list
  int nIdx = ListBox_AddString(hwListBox, L"Process Name:\t Title:");
  //Store tlist index as itemdata  
  ListBox_SetItemData(hwListBox, nIdx, i);
 
  // add the task list 
  for (i=0; i<numTasks; i++) { 
    wsprintf(sbW,_T("%-16s "), tlist[i].ProcessName);
    // append window title
    if (tlist[i].hwnd) {
      lstrcat(sbW, L" \t ");
      lstrcat(sbW, tlist[i].WindowTitle);  
    }
    // add to listbox
    int nIdx = ListBox_AddString(hwListBox, sbW);
    //Store tlist index as itemdata  
    ListBox_SetItemData(hwListBox, nIdx, i);
  } 
}

DWORD GetTaskListCE( PTASK_LIST pTask, DWORD dwNumTasks ) { 
  HINSTANCE         hKernel        = NULL; 
  HINSTANCE         hProcessSnap   = NULL; 
  PROCESSENTRY32 pe32           = {0}; 
  DWORD          dwTaskCount    = 0; 
  
  if (dwNumTasks == 0) 
    return 0; 
  
  // Obtain a module handle to toolhelp.dll 
  hKernel = LoadLibrary(_T("toolhelp.dll")); 
  
  if (!hKernel) {
    MessageBox(NULL, L"Toolhelp.dll not found", L"TrayTaskList", MB_OK);
    return 0;
  }
  
  // all processes currently in the system. 
  hProcessSnap = (HINSTANCE)CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
  if (hProcessSnap == (HANDLE)-1) 
    return 0; 
  // Walk the snapshot of processes and for each process
  dwTaskCount = 0; 
  pe32.dwSize = sizeof(PROCESSENTRY32);   // must be filled out before use 
  if (Process32First(hProcessSnap, &pe32)) { 
    do { 
      LPTSTR pCurChar; 
      // strip path and leave executabe filename 
      if(_tcsstr(pe32.szExeFile, L"\\")) 
        pCurChar = _tcsrchr(pe32.szExeFile, '\\'); 
      else
        pCurChar = pe32.szExeFile;
      
      lstrcpy(pTask -> ProcessName, pCurChar); 
      
      pTask -> flags = 0; 
      pTask -> dwProcessId = pe32.th32ProcessID; 
      pTask->cntThreads = pe32.cntThreads;
      pTask->cntUsage = pe32.cntUsage;
      pTask->dwInheritedFromProcessId = pe32.th32ParentProcessID;
      pTask->th32ModuleID = pe32.th32ModuleID;
      
      ++dwTaskCount;   // keep track of how many tasks we've got so far 
      ++pTask;         // get to next task info block. 
    } 
    while (dwTaskCount < dwNumTasks && Process32Next(hProcessSnap, &pe32)); 
  } 
  else 
    dwTaskCount = 0;    // Couldn't walk the list of processes. 
  // Don't forget to clean up the snapshot object... 
  CloseHandle (hProcessSnap); 
  return dwTaskCount; 
} 

BOOL KillProcess( PTASK_LIST tlist, BOOL fForce ) { 
  HANDLE            hProcess; 
  
  if (!fForce && !tlist->hwnd){
    MessageBox(g_hMainDlg, L"Select the checkbox to FORCE terminate this process.\nCaution is ADVISED!", L"Be Careful!", MB_OK);
    return FALSE;
  }
  
  if (fForce || !tlist->hwnd) { 
    hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, tlist->dwProcessId ); 
    if (hProcess) { 
      hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, tlist->dwProcessId ); 
      if (hProcess == NULL) { 
        return FALSE; 
      } 
      if (!TerminateProcess( hProcess, 1 )) { 
        CloseHandle( hProcess ); 
        return FALSE; 
      } 
      CloseHandle( hProcess ); 
      return TRUE; 
    } 
  } 
  // kill the process 
  PostMessage( tlist->hwnd, WM_CLOSE, 0, 0 ); 
  return TRUE; 
} 

BOOL ActivateProcess( PTASK_LIST tlist) { 
  if (tlist->hwnd && tlist->WindowTitle) {
    PostMessage(g_hMainDlg, WM_COMMAND, (WPARAM)IDOK, 0);
    SetForegroundWindow(tlist->hwnd);
    SetActiveWindow(tlist->hwnd);
  }
  return TRUE; 
} 

BOOL CALLBACK EnumWindowsProc( HWND hwnd, DWORD lParam ) { 
  DWORD             pid = 0; 
  DWORD             i; 
  TCHAR             buf[TITLE_SIZE]; 
  PTASK_LIST_ENUM   te = (PTASK_LIST_ENUM)lParam; 
  PTASK_LIST        tlist = te->tlist; 
  DWORD             numTasks = te->numtasks; 
  
  // get the processid for this window 
  if (!GetWindowThreadProcessId( hwnd, &pid )) { 
    return TRUE; 
  } 
  // look for the task in the task list for this window 
  for (i=0; i<numTasks; i++) { 
    if (tlist[i].dwProcessId == pid) {
     if (IsWindowVisible(hwnd)) {
      tlist[i].hwnd = hwnd; 
      int nCnt = GetWindowText( hwnd, buf, TITLE_SIZE );
      buf[nCnt] = '\0';
      if (nCnt) { 
        lstrcpy( tlist[i].WindowTitle, buf ); 
      } 
     }
      break; 
    } 
  } 
  // continue the enumeration 
  return TRUE; 
}

//
void GetWindowTitles( PTASK_LIST_ENUM te ) { 
  // enumerate all windows 
  EnumWindows((WNDENUMPROC) EnumWindowsProc, (LPARAM) te ); 
} 

void EnableButtons(){
  if (nSelectedTask){
    EnableWindow(GetDlgItem(g_hMainDlg, IDC_ACTIVATEBUTTON), TRUE);
    EnableWindow(GetDlgItem(g_hMainDlg, IDC_TERMINATEBUTTON), TRUE);
    EnableWindow(GetDlgItem(g_hMainDlg, IDC_FORCETERM), TRUE);
  } else {
    EnableWindow(GetDlgItem(g_hMainDlg, IDC_ACTIVATEBUTTON), FALSE);
    EnableWindow(GetDlgItem(g_hMainDlg, IDC_TERMINATEBUTTON), FALSE);
    EnableWindow(GetDlgItem(g_hMainDlg, IDC_FORCETERM), FALSE);
  }
}