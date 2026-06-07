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

//
// PViewCE.CPP
//
// CE Process Viewer
//

#include <windows.h>
#include <aygshell.h>
#include <tpcshell.h>
#include <tlhelp32.h>

// Note: because this sample uses tlhelp32.h, it must be signed with a 
//       privileged certificate
#include <tlhelp32.h>

#include "newres.h"
#include "resource.h"

/*===========================================================================
 * Macro Definitions
*/

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))


/*===========================================================================
 * Type Definitions
*/

struct MODSNAP
{
    DWORD   dwOwnerPID;
    HANDLE  hSnapShot;
};


/*===========================================================================
 * Function Prototypes 
*/

BOOL CALLBACK MainDialogProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam, 
    const LPARAM lParam
    );
BOOL CALLBACK ProcessDialogProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam,
    const LPARAM lParam
    );
BOOL CALLBACK ThreadDialogProc(
    const HWND hDlg,
    const UINT uiMessage, 
    const WPARAM wParam,
    const LPARAM lParam
    );
BOOL CALLBACK ModuleDialogProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam,
    const LPARAM lPara
    );
static LPCTSTR StringFromResources(
    UINT uStringID
    );
static BOOL FillProcList(
    HANDLE hProcessSnap
    );
static BOOL FillThreadList(
    HANDLE hProcessSnap, 
    DWORD dwOwnerPID
    );
static BOOL FillModuleList(
    DWORD dwOwnerPID
    );
static BOOL InitModuleSnap(
    HANDLE hProcessSnap);
static int PID2ArrayID(
    DWORD dwOwnerPID
    );


/*===========================================================================
 * Global Variables
*/

HINSTANCE   g_hInst = NULL;

// Variable for snapshot info
MODSNAP* g_pmsModuleSnap = NULL;
HANDLE g_hProcessSnap = NULL;
int g_iTotalProcs = 0;

HWND g_hWndMain;
HWND g_hWndListViews[3];

LPCTSTR pszAppName;
LPCTSTR pszTitle;

//Menu height
int g_nMenuHeight = 0;

// define to index into g_hWndListViews
#define PROCESSLV 0
#define THREADLV 1
#define MODULELV 2

//Utility functions

// Purpose: Determine at runtime if the app is running on a smartphone device
static BOOL IsSmartphone() 
{
    TCHAR tszPlatform[64];

    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE,
         sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
    {
        if (0 == _tcsicmp(TEXT("Smartphone"), tszPlatform)) 
        {
            return TRUE;
        }
    }
    return FALSE;   
}


int MyMessageBox(HWND hWnd, LPCTSTR lpctszMessage)
{
    return MessageBox(hWnd, lpctszMessage, TEXT("PViewCE"), MB_OK);
}

static LPCTSTR StringFromResources(
    UINT uStringID
    )
{
    // NOTE: Passing NULL for the 3rd parameter of LoadString causes it to
    // return a pointer to the string in the resource file. It requires that
    // the resource file is compiled with the "/n" switch (see SDK docs).
    return (LPCTSTR) LoadString(g_hInst, uStringID, NULL, 0);
}

DWORD GetListViewProc()
{
    DWORD dwReturn = NULL;
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(lvi));
    lvi.iItem = ListView_GetSelectionMark(g_hWndListViews[PROCESSLV]);
    if (-1 != lvi.iItem)
    {
        lvi.mask = LVIF_PARAM;
        ListView_GetItem(g_hWndListViews[PROCESSLV], &lvi);
        dwReturn = lvi.lParam;
    }
    return dwReturn;
}

DWORD GetListViewThread()
{
    DWORD dwReturn = NULL;
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(lvi));
    lvi.iItem = ListView_GetSelectionMark(g_hWndListViews[THREADLV]);
    if (-1 != lvi.iItem)
    {
        lvi.mask = LVIF_PARAM;
        ListView_GetItem(g_hWndListViews[THREADLV], &lvi);
        dwReturn = lvi.lParam;
    }
    return dwReturn;
}

DWORD GetListViewModule()
{
    DWORD dwReturn = NULL;
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(lvi));
    lvi.iItem = ListView_GetSelectionMark(g_hWndListViews[MODULELV]);
    if (-1 != lvi.iItem)
    {
        lvi.mask = LVIF_PARAM;
        ListView_GetItem(g_hWndListViews[MODULELV], &lvi);
        dwReturn = lvi.lParam;
    }
    return dwReturn;
}

//Listbox management functions
BOOL InitListViews(
    HWND hWndParent
    )
{
    LVCOLUMN lvc;
    RECT rc;

    // Create each ListView and configure it
    GetClientRect(hWndParent, &rc);
    
    for (int x = 0; x < ARRAY_LENGTH(g_hWndListViews); x++) 
    {
        g_hWndListViews[x] = CreateWindow(WC_LISTVIEW, TEXT("ListItem"), 
            WS_CHILD | LVS_REPORT | LVS_SORTASCENDING | WS_VISIBLE | WS_HSCROLL | LVS_SINGLESEL, 
            0, 0, rc.right, rc.bottom, hWndParent, NULL, g_hInst, NULL); 
        if (NULL == g_hWndListViews[x])
        {
            return FALSE;
        }
        ListView_SetExtendedListViewStyle(g_hWndListViews[x], LVS_EX_FULLROWSELECT);
    }   
    

    // Now setup the ListView headers

    //Find out how big to make the right column (TID/PID/MID)
    int iIdWidth = 90;
    //int iIdWidth = SendMessage(g_hWndListViews[PROCESSLV], LVM_GETSTRINGWIDTH, 0, (LPARAM)TEXT("0x00000000"));

    // Configure PROCESSLV first
    ZeroMemory(&lvc, sizeof(lvc));
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    lvc.cx = (rc.right - rc.left) - iIdWidth;
    
    // Add column for Process
    lvc.pszText = (LPTSTR)StringFromResources(IDS_PROCESS);
    ListView_InsertColumn(g_hWndListViews[PROCESSLV], lvc.iSubItem, &lvc);
    
    // Add column for PID
    lvc.iSubItem++;
    lvc.pszText = (LPTSTR)StringFromResources(IDS_PID);
    lvc.cx = iIdWidth;
    ListView_InsertColumn(g_hWndListViews[PROCESSLV], lvc.iSubItem, &lvc);

    // Configure THREADLV
    ZeroMemory(&lvc, sizeof(lvc));
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    lvc.cx = (rc.right - rc.left) - iIdWidth;
    
    // Add column for Process
    lvc.pszText = (LPTSTR)StringFromResources(IDS_TID);
    ListView_InsertColumn(g_hWndListViews[THREADLV], lvc.iSubItem, &lvc);
    
    // Add column for PID
    lvc.iSubItem++;
    lvc.pszText = (LPTSTR)StringFromResources(IDS_BASEPRI);
    lvc.cx = iIdWidth;
    ListView_InsertColumn(g_hWndListViews[THREADLV], lvc.iSubItem, &lvc);

    // Configure MODULELV
    ZeroMemory(&lvc, sizeof(lvc));
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    lvc.cx = (rc.right - rc.left) - iIdWidth;
    
    // Add column for Process
    lvc.pszText = (LPTSTR)StringFromResources(IDS_MODULE);
    ListView_InsertColumn(g_hWndListViews[MODULELV], lvc.iSubItem, &lvc);
    
    // Add column for PID
    lvc.iSubItem++;
    lvc.pszText = (LPTSTR)StringFromResources(IDS_MID);
    lvc.cx = iIdWidth;
    ListView_InsertColumn(g_hWndListViews[MODULELV], lvc.iSubItem, &lvc);

    return TRUE;
}

BOOL GetSnapshots()
{
    // Check for old snapshot
    if (NULL != g_hProcessSnap)
    {
        VERIFY(CloseToolhelp32Snapshot(g_hProcessSnap));
    }
    
    if (NULL != g_pmsModuleSnap) 
    {
        free(g_pmsModuleSnap);
    }

    // Create a new snapshot
    g_hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (INVALID_HANDLE_VALUE  == g_hProcessSnap) 
    {
        MyMessageBox(NULL, StringFromResources(IDS_CREATESNAPSHOT_FAILED));
        return FALSE;
    }

    // Take all the module snapshots - if any of them fails, exit...
    // This will make the snapshot operation as a whole seem atomic
    if (FALSE == InitModuleSnap(g_hProcessSnap)) 
    {
        return FALSE;
    }

    return TRUE;
}

void CleanupListViewes()
{
    for (int x = 0; x < ARRAY_LENGTH(g_hWndListViews); x++)
    {
        if (TRUE == IsWindow(g_hWndListViews[x]))
        {
            DestroyWindow(g_hWndListViews[x]);
        }
    }
}

BOOL InitWindow(
    HWND hWnd
    )
{
    BOOL bReturn;
    SHMENUBARINFO mbi;
    
    // fill in the menubar info struct
    ZeroMemory(&mbi, sizeof(mbi));
    mbi.cbSize = sizeof(mbi);
    mbi.hwndParent = hWnd;
    mbi.nToolBarId = IDR_MENU_BAR;
    mbi.hInstRes = g_hInst;

    bReturn = SHCreateMenuBar(&mbi);

    if(TRUE == bReturn)
    {
        RECT rc;
        //Set menu height
        GetClientRect(mbi.hwndMB, &rc);
        g_nMenuHeight=rc.bottom - rc.top;
    }
    return bReturn;
}

LRESULT CALLBACK MainWndProc( 
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    )
{

    switch (Msg)
    {
    case WM_CREATE:
        if (FALSE == InitWindow(hWnd))
        {
            MyMessageBox(NULL, TEXT("Failed to init window"));
            //Failed to init window, lets quit
            DestroyWindow(hWnd);
            PostMessage(GetParent(hWnd), WM_CLOSE, NULL, NULL);
        }
    
        if (FALSE == InitListViews(hWnd))
        {
            MyMessageBox(NULL, TEXT("Failed to init window"));
            //Failed init, lets quit
            DestroyWindow(hWnd);
            PostMessage(GetParent(hWnd), WM_CLOSE, NULL, NULL);
        }

        PostMessage(hWnd, WM_COMMAND, IDM_MENU_REFRESH, NULL);
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case IDM_MENU_PROCESS:
            BringWindowToTop(g_hWndListViews[PROCESSLV]);
            SetFocus(g_hWndListViews[PROCESSLV]);
            break;

        case IDM_MENU_THREAD:
            FillThreadList(g_hProcessSnap, GetListViewProc());
            BringWindowToTop(g_hWndListViews[THREADLV]);
            SetFocus(g_hWndListViews[THREADLV]);
            break;

        case IDM_MENU_MODULE:
            FillModuleList(GetListViewProc());
            BringWindowToTop(g_hWndListViews[MODULELV]);
            SetFocus(g_hWndListViews[MODULELV]);
            break;

        case IDM_MENU_REFRESH:
            GetSnapshots();
            FillProcList(g_hProcessSnap);
            BringWindowToTop(g_hWndListViews[PROCESSLV]);
            SetFocus(g_hWndListViews[PROCESSLV]);
            break;

        case IDM_MENU_QUIT:
            DestroyWindow(hWnd);
            break;
        case IDM_MENU_SOFT1:
            {
                HWND hWndFocus = GetFocus();
                if (hWndFocus == g_hWndListViews[PROCESSLV])
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGPROCESS),
                        0, (DLGPROC)ProcessDialogProc); 
                    SetFocus(g_hWndListViews[PROCESSLV]);
                }
                else if (hWndFocus == g_hWndListViews[THREADLV])
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGTHREAD),
                        0, (DLGPROC)ThreadDialogProc);
                    SetFocus(g_hWndListViews[THREADLV]);
                }
                else if (hWndFocus == g_hWndListViews[MODULELV])
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGMODULE),
                        0, (DLGPROC)ModuleDialogProc);
                    SetFocus(g_hWndListViews[MODULELV]);
                }
            }
        }
        break;
    case WM_NOTIFY:
        {
            NMHDR* pnmhdr = (NMHDR*)lParam;
            if (LVN_ITEMACTIVATE  == pnmhdr->code)
            {
                NMLISTVIEW* pnmlv = (NMLISTVIEW*)lParam;
                if (pnmhdr->hwndFrom == g_hWndListViews[PROCESSLV])
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGPROCESS),
                        0, (DLGPROC)ProcessDialogProc); 
                    SetFocus(g_hWndListViews[PROCESSLV]);
                }
                else if (pnmhdr->hwndFrom == g_hWndListViews[THREADLV])
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGTHREAD),
                        0, (DLGPROC)ThreadDialogProc);
                    SetFocus(g_hWndListViews[THREADLV]);
                }
                else if (pnmhdr->hwndFrom == g_hWndListViews[MODULELV])
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGMODULE),
                        0, (DLGPROC)ModuleDialogProc);
                    SetFocus(g_hWndListViews[MODULELV]);
                }
            }
        }
        break;
    case WM_SETTINGCHANGE:
        {
            if(SETTINGCHANGE_RESET == wParam)
            {
                RECT rect;
                //Update the parent window
                SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, FALSE);
                MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, 
                    rect.bottom - rect.top - g_nMenuHeight, FALSE);
                //update the child windows
                for (int x = 0; x < ARRAY_LENGTH(g_hWndListViews); x++) 
                {
                    //Moving a child window, relative to parent window
                    MoveWindow(g_hWndListViews[x], 0, 0, rect.right - rect.left, 
                        rect.bottom - rect.top - g_nMenuHeight, FALSE);
                }
            }
        }

        break;

    case WM_DESTROY:
        CleanupListViewes();
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        {
            // Check to see if app is being Minimized
            if (SIZE_MINIMIZED == wParam) 
            {
                // App being minimized we'll just close instead
                DestroyWindow(hWnd);
            }
        }
        break;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);      
}

BOOL InitApplication()
{
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;
    wc.hInstance = g_hInst;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = pszAppName;
    
    return RegisterClass(&wc);
}

BOOL InitInstance(
    int iCmdShow
    )
{
    g_hWndMain = CreateWindow(pszAppName, pszTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, g_hInst, NULL);

    if (NULL == g_hWndMain)
    {
        return FALSE;
    }

    ShowWindow(g_hWndMain, iCmdShow);
    UpdateWindow(g_hWndMain);

    return TRUE;
}

int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance, 
    LPWSTR lpCmdLine, 
    int nShowCmd
    )

{
    MSG msg = {0};

    // Store the application instance in our global variable.
    g_hInst = hInstance;

    // Load strings
    pszAppName = StringFromResources(IDS_PVIEWCE_APPNAME);
    pszTitle = StringFromResources(IDS_PVIEWCE_TITLE);

    // Use a globally named mutex to detect another instance of HelloSMS
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_PVIEWCE_EXE_MUTEX_"));

    // check the result code
    if (0 != hMutex) 
    {
        // No other instances running? Okay to proceed...
        if (ERROR_ALREADY_EXISTS != GetLastError()) 
        if (true)
        {
            // initialize the application
            if (NULL != InitApplication())
            {
                // initialize the instance
                if (TRUE == InitInstance(nShowCmd))
                {
                    // begin message pump
                    while (GetMessage(&msg, NULL, 0,0))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
            }
            // Fall through to Cleanup
        }
        else 
        {
            // Already an instance running - attempt to switch to it and then exit
            const HWND hwndExistingInstance = FindWindow(pszAppName, pszTitle);
            if (NULL != hwndExistingInstance) 
            {
                SetForegroundWindow((HWND)(((ULONG)hwndExistingInstance) | 0x1));
            }

            // Fall through to Cleanup
        }
    }

    if (g_hProcessSnap != NULL) 
    {
        VERIFY(CloseToolhelp32Snapshot(g_hProcessSnap));
    }
    
    if (g_pmsModuleSnap != NULL) 
    {
        free(g_pmsModuleSnap);
    }
    
    if (0 != hMutex) 
    {
        VERIFY(CloseHandle(hMutex));
    }

    return msg.wParam;
}

BOOL FillProcList(
    HANDLE hProcessSnap
    )
{
    PROCESSENTRY32 pe32 = {0};
    LVITEM lvi;
    int iItem;
    TCHAR tszBuffer[11];

    ZeroMemory(&lvi, sizeof(lvi));

    // Clear the ListView
    SendMessage(g_hWndListViews[PROCESSLV], LVM_DELETEALLITEMS, 0, 0);

    // Size of the PROCESSENTRY32 structure must be filled out before use.
    pe32.dwSize = sizeof(PROCESSENTRY32);
  
    // Walk the snapshot of processes and for each process, add it to the list
    if (TRUE == Process32First(hProcessSnap, &pe32)) 
    {
        do 
        {
            // Subitem 0 is the Process name
            lvi.pszText = pe32.szExeFile;
            lvi.cchTextMax = MAX_PATH;
            lvi.mask = LVIF_TEXT | LVIF_PARAM;
            lvi.lParam = pe32.th32ProcessID;

            iItem = ListView_InsertItem(g_hWndListViews[PROCESSLV], &lvi);

            StringCchPrintf(tszBuffer, ARRAY_LENGTH(tszBuffer) ,TEXT("0x%08x"), pe32.th32ProcessID);

            lvi.mask = LVIF_TEXT;
            ListView_SetItemText(g_hWndListViews[PROCESSLV], iItem, 1, tszBuffer);
            
        } while (Process32Next(hProcessSnap, &pe32));

        ListView_SetItemState(g_hWndListViews[PROCESSLV], 0,
            LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
    } 
    else 
    {
        // Couldn't walk first node of list
        return FALSE;
    }
    
    return TRUE;
}


static BOOL FillThreadList(
    HANDLE hProcessSnap, 
    DWORD dwOwnerPID
    )
{
    THREADENTRY32 te32 = {0};
    TCHAR tszBuffer[11];
    LVITEM lvi;
    int iItem;

    // Prepare the LVITEM
    ZeroMemory(&lvi, sizeof(lvi));

    // Clear the ListView
    SendMessage(g_hWndListViews[THREADLV], LVM_DELETEALLITEMS, 0, 0);
  
    // Size of the THREADENTRY32 structure must be filled out before use.
    te32.dwSize = sizeof(THREADENTRY32);
  
    // Walk thread snapshot to find all threads of the process we want.
    // If the thread belongs to the process we want, add its information  
    // to the display list.
    if (Thread32First(hProcessSnap, &te32)) 
    {
        do 
        {   
            if (te32.th32OwnerProcessID == dwOwnerPID) 
            {
                StringCchPrintf(tszBuffer, ARRAY_LENGTH(tszBuffer), TEXT("0x%08x"), te32.th32ThreadID);

                // Subitem 0 is the Process name
                lvi.pszText = tszBuffer;
                lvi.cchTextMax = ARRAY_LENGTH(tszBuffer);
                lvi.mask = LVIF_TEXT | LVIF_PARAM;
                lvi.lParam = te32.th32ThreadID;

                iItem = ListView_InsertItem(g_hWndListViews[THREADLV], &lvi);

                StringCchPrintf(tszBuffer, ARRAY_LENGTH(tszBuffer), TEXT("0x%08x"), te32.tpBasePri);

                lvi.mask = LVIF_TEXT;
                ListView_SetItemText(g_hWndListViews[THREADLV], iItem, 1, tszBuffer);

            }
        } while (Thread32Next(hProcessSnap, &te32));
        ListView_SetItemState(g_hWndListViews[THREADLV], 0,
            LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
    } 
    else 
    {
        // Couldn't walk the list of threads.
        return FALSE; 
    }

    return TRUE;
}

static BOOL FillModuleList(
    DWORD dwOwnerPID
    )
{
    MODULEENTRY32 me32 = {0};
    LVITEM lvi;
    int iItem;
    TCHAR tszBuffer[11];
    int iSnapIndex = PID2ArrayID(dwOwnerPID);


    // sanity check
    if (iSnapIndex < 0) 
    {
        return FALSE;
    }

    // Prepare the LVITEM
    ZeroMemory(&lvi, sizeof(lvi));

    // Clear the ListView
    SendMessage(g_hWndListViews[MODULELV], LVM_DELETEALLITEMS, 0, 0);

    // Size of the MODULEENTRY32 structure must be filled out before use.
    me32.dwSize = sizeof(MODULEENTRY32);
  
    // Walk thread snapshot to find all modules of the process we want.
    // If the module belongs to the process we want, add its information  
    // to the display list.
    if (Module32First(g_pmsModuleSnap[iSnapIndex].hSnapShot, &me32)) 
    {
        do 
        {   
            // Subitem 0 is the Process name
            lvi.pszText = me32.szModule;
            lvi.cchTextMax = MAX_PATH;
            lvi.mask = LVIF_TEXT | LVIF_PARAM;
            lvi.lParam = me32.th32ModuleID;

            iItem = ListView_InsertItem(g_hWndListViews[MODULELV], &lvi);
             
            StringCchPrintf(tszBuffer, ARRAY_LENGTH(tszBuffer), TEXT("0x%08x"), me32.th32ModuleID);

            lvi.mask = LVIF_TEXT;
            ListView_SetItemText(g_hWndListViews[MODULELV], iItem, 1, tszBuffer);



        } while (Module32Next(g_pmsModuleSnap[iSnapIndex].hSnapShot, &me32));

        ListView_SetItemState(g_hWndListViews[MODULELV], 0,
            LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
    } 
    else 
    {
        // Couldn't walk the list of modules.
        return FALSE;          
    }

    return TRUE;
}


static BOOL InitModuleSnap(
    HANDLE hProcessSnap
    )
{
    PROCESSENTRY32  pe32 = {0};
    int             iCount = 0;
  
    // Size of the PROCESSENTRY32 structure must be filled out before use.
    pe32.dwSize = sizeof(PROCESSENTRY32);
  
    // Walk the snapshot of processes and for each process, count it
    if (Process32First(hProcessSnap, &pe32)) 
    {
        do 
        {
            ++iCount;
        } while (Process32Next(hProcessSnap, &pe32));
    } 
    else 
    {
        return FALSE;    // Couldn't walk the list of processes.
    }

    g_pmsModuleSnap = (MODSNAP*) malloc(sizeof(MODSNAP) * iCount);
    if (g_pmsModuleSnap == NULL) 
    {
        return FALSE;
    }

    // store the count
    g_iTotalProcs = iCount;
    
    // Walk the process list again, this time initializing the modinfo
    iCount = 0;
    if (Process32First(hProcessSnap, &pe32)) 
    {
        do 
        {
            g_pmsModuleSnap[iCount].dwOwnerPID = pe32.th32ProcessID;
            g_pmsModuleSnap[iCount].hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
            
            // was the snapshot successful?
            if (g_pmsModuleSnap[iCount].hSnapShot == (HANDLE) -1) 
            {
                return FALSE;
            }

            ++iCount;
        } while (Process32Next(hProcessSnap, &pe32));
    } 
    else 
    {
        return FALSE;    // Couldn't walk the list of processes.
    }
    
    return TRUE;
}


static int PID2ArrayID(
    DWORD dwOwnerPID
    )
{
    // sanity check
    ASSERT(g_pmsModuleSnap != NULL);
    
    for (int i = 0; i < g_iTotalProcs; i++) 
    {
        if (g_pmsModuleSnap[i].dwOwnerPID == dwOwnerPID) 
        {
            return i;
        }
    }
    
    // not found - return an impossible index
    return -1;
}


BOOL CALLBACK ProcessDialogProc
(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam, 
    const LPARAM lParam
)
{
    BOOL bProcessedMsg = true;
    DWORD dwProcess;

    switch(uiMessage)
    {
        case WM_INITDIALOG:
        {
            // Specify that the dialog box should stretch full screen
            SHINITDLGINFO shidi;
            ZeroMemory(&shidi, sizeof(shidi));
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
            if (FALSE == IsSmartphone())
            {
                shidi.dwFlags = shidi.dwFlags | SHIDIF_DONEBUTTON;
            }
            shidi.hDlg = hDlg;

            // If we could not initialize the dialog box, return an error
            if (!SHInitDialog(&shidi)) 
            {
                MessageBox( hDlg, StringFromResources(IDS_SHINITDIALOG_FAILED),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONSTOP );
                EndDialog(hDlg, -1);
                return TRUE;
            }

            // set up Soft Keys menu
            SHMENUBARINFO mbi;
            ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
            mbi.cbSize      = sizeof(SHMENUBARINFO);
            mbi.hwndParent  = hDlg;
            mbi.nToolBarId  = IDR_PVIEWCE_SUBMENU;
            mbi.hInstRes    = g_hInst;

            // If we could not initialize the dialog box, return an error
            if (!SHCreateMenuBar(&mbi)) 
            {
                MessageBox( hDlg, StringFromResources(IDS_SHCREATEMENUBAR_FAILED),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONSTOP );
                EndDialog(hDlg, -1);
                return TRUE;
            }

            dwProcess = GetListViewProc();

            // Now set the labels - look up the proc
            PROCESSENTRY32  pe32 = {0};
            pe32.dwSize = sizeof(pe32);
  
            // Walk the snapshot of processes
            if (Process32First(g_hProcessSnap, &pe32)) 
            {
                TCHAR   szPID[12];
                TCHAR   szPriority[4];
                TCHAR   szThreadCount[8];
                TCHAR   szFullPath[MAX_PATH];
                do 
                {
                    // if the current iteration is the process we are looking for
                    if (pe32.th32ProcessID == dwProcess) 
                    {
                        // process name
                        SetDlgItemText(hDlg, IDC_PVIEWCE_PROCESS, pe32.szExeFile);
                        
                        // process ID
                        StringCchPrintf(szPID, ARRAY_LENGTH(szPID), 
                             TEXT("0x%08X"), pe32.th32ProcessID);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_PID, szPID);
                        
                        // base priority
                        StringCchPrintf(szPriority, ARRAY_LENGTH(szPriority),
                             TEXT("%ld"), pe32.pcPriClassBase);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_BASEPRI, szPriority);

                        // thread count
                        StringCchPrintf(szThreadCount, ARRAY_LENGTH(szThreadCount),
                             TEXT("%ld"), pe32.cntThreads);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_NUMTH, szThreadCount);

                        // type - always 32-bit, 16-bit processes aren't available 
                        SetDlgItemText(hDlg, IDC_PVIEWCE_TYPE, TEXT("32-Bit"));

                        // full path
                        GetModuleFileName((HMODULE)pe32.th32ProcessID, 
                             szFullPath, MAX_PATH);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_PPATH, szFullPath);
                    }
                } while (Process32Next(g_hProcessSnap, &pe32));
            } 
            else 
            {
                // couldn't walk the list of processes
                EndDialog(hDlg, -1);
                return TRUE;
            }

            break;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                case IDM_PVIEWCE_BACK:
                    EndDialog(hDlg, 0);
                    break;

                default:
                    bProcessedMsg = false;
                    break;
            }
        default:
            // nothing was processed
            bProcessedMsg = false;
            break;
    }

    return bProcessedMsg;
}


BOOL CALLBACK ThreadDialogProc
(
    const HWND      hDlg, 
    const UINT      uiMessage, 
    const WPARAM    wParam, 
    const LPARAM    lParam
)
{
    BOOL bProcessedMsg = true;
    DWORD dwCurTID = GetListViewThread();


    switch(uiMessage)
    {
        case WM_INITDIALOG:
        {
            // Specify that the dialog box should stretch full screen
            SHINITDLGINFO shidi;
            ZeroMemory(&shidi, sizeof(shidi));
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
            if (FALSE == IsSmartphone())
            {
                shidi.dwFlags = shidi.dwFlags | SHIDIF_DONEBUTTON;
            }
            shidi.hDlg = hDlg;

            // If we could not initialize the dialog box, return an error
            if (!SHInitDialog(&shidi)) 
            {
                MessageBox( hDlg, StringFromResources(IDS_SHINITDIALOG_FAILED),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONSTOP );
                EndDialog(hDlg, -1);
                return TRUE;
            }

            // set up Soft Keys menu
            SHMENUBARINFO mbi;
            ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
            mbi.cbSize      = sizeof(SHMENUBARINFO);
            mbi.hwndParent  = hDlg;
            mbi.nToolBarId  = IDR_PVIEWCE_SUBMENU;
            mbi.hInstRes    = g_hInst;

            // If we could not initialize the dialog box, return an error
            if (!SHCreateMenuBar(&mbi)) 
            {
                MessageBox( hDlg, StringFromResources(IDS_SHCREATEMENUBAR_FAILED),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONSTOP );
                EndDialog(hDlg, -1);
                return TRUE;
            }


            // Now set the labels - look up the thread
            THREADENTRY32   te32 = {0};
            te32.dwSize = sizeof(THREADENTRY32);
  
            // Walk the snapshot of threads
            if (Thread32First(g_hProcessSnap, &te32)) 
            {
                TCHAR   szTID[12];
                TCHAR   szOPID[12];
                TCHAR   szPriority[12];
                do 
                {
                    // if the current iteration is the process we are looking for
                    if (te32.th32ThreadID == dwCurTID) 
                    {
                        // thread ID
                        StringCchPrintf(szTID, ARRAY_LENGTH(szTID), 
                            TEXT("0x%08X"), te32.th32ThreadID);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_TID, szTID);
                        
                        // owning PID
                        StringCchPrintf(szOPID, ARRAY_LENGTH(szOPID), 
                            TEXT("0x%08X"), te32.th32OwnerProcessID);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_OPID, szOPID);

                        // thread priority
                        StringCchPrintf(szPriority, ARRAY_LENGTH(szPriority),
                            TEXT("%ld"), te32.tpBasePri);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_THRPRI, szPriority);
                    }
                } while (Thread32Next(g_hProcessSnap, &te32));
            } 
            else 
            {
                // couldn't walk the list of threads
                EndDialog(hDlg, -1);
                return TRUE;
            }

            break;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                case IDM_PVIEWCE_BACK:
                    EndDialog(hDlg, 0);
                    break;

                default:
                    bProcessedMsg = false;
                    break;
            }
        
        default:
            // nothing was processed
            bProcessedMsg = false;
            break;
    }

    return bProcessedMsg;
}


BOOL CALLBACK ModuleDialogProc
(
    const HWND      hDlg, 
    const UINT      uiMessage, 
    const WPARAM    wParam, 
    const LPARAM    lParam
)
{
    BOOL bProcessedMsg   = true;
    int iSnapIndex = PID2ArrayID(GetListViewProc());
    DWORD dwCurMID = GetListViewModule();

    // sanity check
    if (iSnapIndex < 0) 
    {
        EndDialog(hDlg, -1);
    }

    switch(uiMessage)
    {
        case WM_INITDIALOG:
        {
            // Specify that the dialog box should stretch full screen
            SHINITDLGINFO shidi;
            ZeroMemory(&shidi, sizeof(shidi));
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
            if (FALSE == IsSmartphone())
            {
                shidi.dwFlags = shidi.dwFlags | SHIDIF_DONEBUTTON;
            }
            shidi.hDlg = hDlg;

            // If we could not initialize the dialog box, return an error
            if (!SHInitDialog(&shidi)) 
            {
                MessageBox( hDlg, StringFromResources(IDS_SHINITDIALOG_FAILED),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONSTOP );
                EndDialog(hDlg, -1);
                return TRUE;
            }

            // set up Soft Keys menu
            SHMENUBARINFO mbi;
            ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
            mbi.cbSize      = sizeof(SHMENUBARINFO);
            mbi.hwndParent  = hDlg;
            mbi.nToolBarId  = IDR_PVIEWCE_SUBMENU;
            mbi.hInstRes    = g_hInst;

            // If we could not initialize the dialog box, return an error
            if (!SHCreateMenuBar(&mbi)) 
            {
                MessageBox( hDlg, StringFromResources(IDS_SHCREATEMENUBAR_FAILED),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONSTOP );
                EndDialog(hDlg, -1);
                return TRUE;
            }

            // we need to figure out which snapshot to use
            MODULEENTRY32 me32 = {0};
            me32.dwSize = sizeof(MODULEENTRY32);
  
            // Walk the appropriate snapshot of modules
            if (Module32First(g_pmsModuleSnap[iSnapIndex].hSnapShot, &me32)) 
            {
                TCHAR   szHModule[12];
                TCHAR   szGUsage[12];
                TCHAR   szLUsage[12];
                TCHAR   szBaseAddr[12];
                TCHAR   szBaseSize[12];
                TCHAR   szFullPath[MAX_PATH];
                do 
                {
                    // if the current iteration is the process we are looking for
                    if (me32.th32ModuleID == dwCurMID) 
                    {
                        // Module Name
                        SetDlgItemText(hDlg, IDC_PVIEWCE_MODULE, me32.szModule);

                        // HModule
                        StringCchPrintf(szHModule, ARRAY_LENGTH(szHModule),
                            TEXT("0x%08X"), me32.hModule);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_HMOD, szHModule);

                        // Global Usage
                        StringCchPrintf(szGUsage, ARRAY_LENGTH(szGUsage),
                            TEXT("%ld"), me32.GlblcntUsage);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_GUSAGE, szGUsage);

                        // Local Usage
                        StringCchPrintf(szLUsage, ARRAY_LENGTH(szLUsage),
                            TEXT("%ld"), me32.ProccntUsage);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_LUSAGE, szLUsage);

                        // Base Address
                        StringCchPrintf(szBaseAddr, ARRAY_LENGTH(szBaseAddr),
                            TEXT("0x%08X"), me32.modBaseAddr);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_BASEADDR, szBaseAddr);

                        // Base Size
                        StringCchPrintf(szBaseSize, ARRAY_LENGTH(szBaseSize),
                            TEXT("%ld"), me32.modBaseSize);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_BASESIZE, szBaseSize);

                        // Full Path
                        GetModuleFileName(me32.hModule, szFullPath, MAX_PATH);
                        SetDlgItemText(hDlg, IDC_PVIEWCE_MPATH, szFullPath);
                    }
                } while (Module32Next(g_pmsModuleSnap[iSnapIndex].hSnapShot, &me32));
            } 
            else 
            {
                // couldn't walk the list of modules
                EndDialog(hDlg, -1);
                return TRUE;
            }

            break;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                case IDM_PVIEWCE_BACK:
                    EndDialog(hDlg, 0);
                    break;

                default:
                    bProcessedMsg = false;
                    break;
            }
        
        default:
            // nothing was processed
            bProcessedMsg = false;
            break;
    }

    return bProcessedMsg;
}

/* EOF */
