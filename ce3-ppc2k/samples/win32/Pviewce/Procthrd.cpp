// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   procthrd.c
//
//  PURPOSE:  Implements process and thread enumeration/manipulation
//            functions. 
//
//  FUNCTIONS:
//    InitToolhelp32        - Dynamically resolves addresses of 32-bit 
//                            Toolhelp functions
//    RefreshThreadList     - Enumerates and displays active threads
//    RefreshProcessList    - Enumerates and displays active processes
//    GetProcessModule      - Gets information about a specific module in 
//                            a specified process
//    KillProcess           - Kills the specified process
//    GetModuleNameFromExe  - Returns a Win16 app/DLL's module name from
//                            its executable file.
//   
//
//  COMMENTS:
//

#include <windows.h>
#include <tlhelp32.h>              // Required for ToolHelp32 functions
#include <commctrl.h>
#include "procthrd.h"
#include "listview.h"
#include "globals.h"

//-------------------------------------------------------------------------
// Type definitions for functions pointers used to call 32-bit Toolhelp 
// functions.
typedef BOOL (WINAPI *MODULEWALK)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef BOOL (WINAPI *THREADWALK)(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID);




//
//  FUNCTION: InitToolhelp32(void)
//
//  PURPOSE:  Initializes pointers to the 32-bit Toolhelp APIs 
//            
//  PARAMETERS:
//    None.
//
//  RETURN VALUE:
//    TRUE if addresses of all needed 32-bit Toolhelp functions were 
//    retrieved.
//    FALSE if we couldn't get the address of even one needed 32-bit 
//    Toolhelp function
//
//  COMMENTS:
//    This function is needed to initialize the function pointers to the
//    32-bit Toolhelp functions.
//
//    In the case of this sample, this function is called in InitApplication
//    which will prevent this application from even running if it can't 
//    access the necessary functions.
//

BOOL InitToolhelp32 (void)
{
  BOOL   bRet;
  
  
  // Obtain a module handle to toolhelp.dll so that we can get the addresses of 
  // the 32-bit Toolhelp functions we need.
  HMODULE hKernel;
  
  hKernel = LoadLibrary(L"toolhelp.dll");
  
  if (hKernel)
  {
    bRet = TRUE;  // Couldn't even get a module handle to KERNEL.
  }
  else
    bRet = FALSE;  // Couldn't even get a module handle to KERNEL.

  return bRet;
}


//
//  FUNCTION: RefreshThreadList(HWND, DWORD)
//
//  PURPOSE:  Enumerates and displays the list of threads owned by a 
//            specified process.
//
//  PARAMETERS:
//    hListView    - Handle of the listview that lists thread information
//    dwOwnerPID   - ID of process whose threads we will list
//
//  RETURN VALUE:
//    TRUE if the threads were successfully enumerated and listed
//     FALSE if the threads could not be enumerated or listed
//
//  COMMENTS:
//

BOOL RefreshThreadList (HWND hListView, DWORD dwOwnerPID)
{
  HANDLE        hThreadSnap;
  BOOL          bRet;
  THREADENTRY32 te32        = {0};
  
  // Take a snapshot of all threads currently in the system.
  hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  
  if (hThreadSnap == (HANDLE)-1)
    return (FALSE);
  
  // Clear the current contents of the thread list view (which are now old).
  ListView_DeleteAllItems(g_hwndThread);
  
  // Size of the THREADENTRY32 structure must be filled out before use.
  te32.dwSize = sizeof(THREADENTRY32);
  
  // Walk thread snapshot to find all threads of the process we want.
  // If the thread belongs to the process we want, add its information  
  // to the display list.
  if (Thread32First(hThreadSnap, &te32))
    {
      do 
      {   
        if (te32.th32OwnerProcessID == dwOwnerPID)
        {   
          TINFO ti;
          
          ti.tid        = te32.th32ThreadID;
          ti.pidOwner   = te32.th32OwnerProcessID;
          ti.tpDeltaPri = te32.tpDeltaPri;
          ti.tpBasePri  = te32.tpBasePri;
          
          AddThreadItem(hListView, ti);
        }
      }
      while (Thread32Next(hThreadSnap, &te32));
      bRet = TRUE;
    }
    else
      bRet = FALSE;          // Couldn't walk the list of threads.
    
    // Don't forget to clean up the snapshot object...
    CloseHandle (hThreadSnap);
    
    return (bRet);
}

BOOL GetProcessPathName (DWORD dwPID, LPTSTR szExeName, LPTSTR szFullPathName)
{   
  BOOL          bRet;
  BOOL          bFound      = FALSE;
  HANDLE        hModuleSnap;
  MODULEENTRY32 me32        = {0};
  
  // Take a snapshot of all modules in the specified process.
  hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
  if (hModuleSnap == (HANDLE)-1)
    return (FALSE);
  
  // Size of the MODULEENTRY32 structure must be initialized before use!
  me32.dwSize = sizeof(MODULEENTRY32);
  
  // Walk the module list of the process and find the module we are 
  // interested in.  Then, copy the information to the buffer pointed to
  // by lpMe32 so that we can return it to the caller.
  if (Module32First(hModuleSnap, &me32))
  {
    do 
    {
      OutputDebugString(me32.szExePath);
      
      if (lstrcmp(me32.szModule, szExeName) == 0)
      {
        lstrcpy (szFullPathName, me32.szExePath);
        bFound = TRUE;
      }
    }
    while (!bFound && Module32Next(hModuleSnap, &me32));
    
    bRet = bFound;   // If this sets bRet to FALSE, then dwModuleID 
    // no longer exsists in the specified process.
  }
  else
    bRet = FALSE;    // Couldn't walk module list.
  
  // Don't forget to clean up the snapshot object...
  CloseHandle (hModuleSnap);
  
  return (bRet);
}

//
//  FUNCTION: RefreshProcessList(HWND)
//
//  PURPOSE:  Enumerates and displays the list of processes.
//
//  PARAMETERS:
//    hListView   - Handle of the listview that lists process information
//
//  RETURN VALUE:
//    TRUE if the processes were successfully enumerated and listed
//     FALSE if the processes could not be enumerated or listed
//
//  COMMENTS:
//     Refreshes the list of processes by making a process snapshot and
//    putting info about each process into the listview control specifed by
//    hListView.

BOOL RefreshProcessList (HWND hListView)
{
  HANDLE         hProcessSnap;
  BOOL           bRet;
  PROCESSENTRY32 pe32         = {0};
  
  // Take a snapshot of all processes currently in the system.
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == (HANDLE)-1)
    return (FALSE);
  
  // Clear the current contents of the process list view (which are now old).
  ListView_DeleteAllItems(g_hwndProcess);
  
  // Size of the PROCESSENTRY32 structure must be filled out before use.
  pe32.dwSize = sizeof(PROCESSENTRY32);
  
  // Walk the snapshot of processes and for each process, get information
  // to display.
    if (Process32First(hProcessSnap, &pe32))
    {
      PINFO         pi         = {{0}, 0};
      do
      {
          HANDLE hProcess;
          
          // Get actual priority class
          hProcess = OpenProcess (PROCESS_ALL_ACCESS, 
            FALSE, 
            pe32.th32ProcessID);
          //TODO: pi.dwPriorityClass = GetPriorityClass (hProcess);
          CloseHandle (hProcess);
          
          // Get process's base priority value
          pi.pcPriClassBase = pe32.pcPriClassBase;
          pi.pid            = pe32.th32ProcessID;
          pi.cntThreads     = pe32.cntThreads;
          
          //lstrcpy(pi.szFullPath, pe32.szExeFile);
					GetModuleFileName((HMODULE)pe32.th32ProcessID, pi.szFullPath, MAX_PATH);
          lstrcpy(pi.szModName, pe32.szExeFile);

          pi.uAppType = EXETYPE_32BIT;
          AddProcessItem(hListView, pi);
      }
      while (Process32Next(hProcessSnap, &pe32));
      bRet = TRUE;
    }
    else
      bRet = FALSE;    // Couldn't walk the list of processes.
    
    // Don't forget to clean up the snapshot object...
    CloseHandle (hProcessSnap);
    return (bRet);
}


//
//  FUNCTION: RefreshModuleList(HWND, DWORD)
//
//  PURPOSE:  Enumerates and displays the list of modules owned by a 
//            specified process.
//
//  PARAMETERS:
//    hListView    - Handle of the listview that lists thread information
//    dwOwnerPID   - ID of process whose threads we will list
//
//  RETURN VALUE:
//    TRUE if the threads were successfully enumerated and listed
//     FALSE if the threads could not be enumerated or listed
//
//  COMMENTS:
//

BOOL RefreshModuleList (HWND hListView, DWORD dwOwnerPID)
{
  HANDLE        hModuleSnap;
  BOOL          bRet;
  MODULEENTRY32 me32        = {0};
  
  // Take a snapshot of all threads currently in the system.
  hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwOwnerPID);
  
  if (hModuleSnap == (HANDLE)-1)
    return (FALSE);
  
  // Clear the current contents of the thread list view (which are now old).
  ListView_DeleteAllItems(g_hwndModule);
  
  // Size of the MODULEENTRY32 structure must be filled out before use.
  me32.dwSize = sizeof(MODULEENTRY32);
  
  // Walk module snapshot to find all modules of the process we want.
  if (Module32First(hModuleSnap, &me32))
    {
      do 
      {   
          MINFO mi;
          
          mi.GlblcntUsage   = me32.GlblcntUsage;
          mi.ProccntUsage   = me32.ProccntUsage;
          mi.modBaseAddr   = me32.modBaseAddr; //Base address of the module in the context of the owning process. 
          mi.modBaseSize   = me32.modBaseSize; //Size, in bytes, of the module. 
          mi.hModule   = me32.hModule ; //Handle to the module in the context of the owning process
          lstrcpy(mi.szModule, me32.szModule);
          //lstrcpy(mi.szExePath, me32.szExePath);
					GetModuleFileName(me32.hModule, mi.szExePath, MAX_PATH);
          
          AddModuleItem(hListView, mi);
      }
      while (Module32Next(hModuleSnap, &me32));
      bRet = TRUE;
    }
    else
      bRet = FALSE;          // Couldn't walk the list of modules.
    
    // Don't forget to clean up the snapshot object...
    CloseHandle (hModuleSnap);
    
    return (bRet);
  
}



//
//  FUNCTION: KillProcess(DWORD)
//
//  PURPOSE:  To kills a specified process
//
//  PARAMETERS:
//    dwPID      - Process ID of the process to kill
//
//  RETURN VALUE:
//    TRUE if the specified process was killed
//    FALSE if it wasn't killed.
//
//  COMMENTS:
//    KillProcess does not return until the process is terminated.
//

BOOL KillProcess (DWORD dwPID)
{
  BOOL   bRet;
  HANDLE hProcess;
  
  // Open the process to obtain a handle to it.  If we get a handle,
  // try to terminate the process.  Wait until the process is really
  // dead before returning.
  hProcess = OpenProcess (PROCESS_TERMINATE, FALSE, dwPID);
  if (hProcess != NULL)
  {    
    bRet = TerminateProcess (hProcess, 0xFFFFFFFF);
    
    // Don't want to wait if the terminate fails.  If the
    // process is still running and we can't terminate it,
    // then waiting for it would cause this process to stop
    // execution.
    if (bRet)
      WaitForSingleObject(hProcess, INFINITE);
    
    CloseHandle (hProcess);
  }
  else
    bRet = FALSE;
  
  return (bRet);
}



