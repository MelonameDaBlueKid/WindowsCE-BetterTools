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

#include "stdafx.h"
#include "pmsample.h"
#include <windows.h>
#include <commctrl.h>
#include <pm.h>


TCHAR tszAppName[] = TEXT("PMSAMPLE");
TCHAR tszTitle[]   = TEXT("Power Manager Sample");


HINSTANCE g_hInst = NULL;                     // Local copy of hInstance
HANDLE    g_hEventShutDown = NULL;            
HANDLE    g_hPowerNotificationThread = NULL;  
HWND      g_hSystemState = NULL;


DWORD PowerNotificationThread(LPVOID pVoid);


//***************************************************************************
// Function Name: SetBacklightRequirement
//
// Purpose: Sets or releases the device power requirement to keep the 
//          backlight at D0
//
// Arguments:
//  IN BOOL fBacklightOn - TRUE to leave the backlight on
//
void SetBacklightRequirement(BOOL fBacklightOn)
{
    // the name of the backlight device
    TCHAR tszBacklightName[] = TEXT("BKL1:"); 

    static HANDLE s_hBacklightReq = NULL;
    
    if (fBacklightOn) 
    {
        if (NULL == s_hBacklightReq) 
        {
            // Set the requirement that the backlight device must remain
            // in device state D0 (full power)
            s_hBacklightReq = SetPowerRequirement(tszBacklightName, D0, 
                                                  POWER_NAME, NULL, 0);
            if (!s_hBacklightReq)
            {
                RETAILMSG(1, (L"SetPowerRequirement failed: %X\n", 
                              GetLastError()));
            }
        }
    } 
    else 
    {
        if (s_hBacklightReq) 
        {
            if (ERROR_SUCCESS != ReleasePowerRequirement(s_hBacklightReq))
            {
                RETAILMSG(1, (L"ReleasePowerRequirement failed: %X\n",
                              GetLastError()));
            }
            s_hBacklightReq = NULL;
        }
    }
}


//***************************************************************************
// Function Name: UpdatePowerState
//
// Purpose: Updates the name of the current power state in the dialog
//
void UpdatePowerState( void ) 
{
    TCHAR szState[MAX_PATH];
    DWORD dwState;

    if (g_hSystemState) 
    {
        if (ERROR_SUCCESS == GetSystemPowerState(szState, MAX_PATH, &dwState)) 
        {
            SetWindowText(g_hSystemState, szState);
        }
    }

}

//***************************************************************************
// Function Name: InitWindow
//
// Purpose: Initializes dialog and soft key menus
//
BOOL InitWindow(const HWND hDlg, UINT nToolBarId)
{
        // Specify that the dialog box should stretch full screen
        SHINITDLGINFO shidi;
        ZeroMemory(&shidi, sizeof(shidi));
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;

        // set up Soft Keys menu
        SHMENUBARINFO mbi;
        ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
        mbi.cbSize = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hDlg;
        mbi.nToolBarId = nToolBarId;
        mbi.hInstRes = g_hInst;

        // If we could not initialize the dialog box, return an error
        if (FALSE == (SHInitDialog(&shidi) && SHCreateMenuBar(&mbi)))
        {
            return FALSE;
        }

        // set the title bar
        SetWindowText(hDlg, tszTitle);

        return TRUE;
}

//***************************************************************************
// Function Name: WndProc(HWND, unsigned, WORD, LONG)
//
// Purpose: Processes messages for the main window.
//
BOOL CALLBACK DlgProc (
        HWND hwnd, 
        UINT Msg, 
        WPARAM wParam, 
        LPARAM lParam)
{
    BOOL fReturn = TRUE;
    HANDLE hThread = NULL;
    HWND hwndBacklight = NULL;
    static BOOL s_fIdled = FALSE;

    switch(Msg)
    {
        case WM_INITDIALOG:

            // Initialize the dialog and softkey menu
            if (FALSE == InitWindow(hwnd, IDR_MENU))
            {
                EndDialog(hwnd, -1);
            }

            // Start up the thread to get the power notifications
            g_hEventShutDown = CreateEvent(NULL, FALSE, FALSE, NULL);
            if (NULL != g_hEventShutDown)  
            {
                g_hPowerNotificationThread = 
                    CreateThread(0, 0, PowerNotificationThread, NULL, 0, 0);
            }

            g_hSystemState = GetDlgItem(hwnd, IDC_SYSTEMSTATE);
    
            // Update the current state in the dialog
            UpdatePowerState();
            break;

        case WM_COMMAND:

            switch (wParam)
            {
                case IDM_QUIT:
                    EndDialog(hwnd, IDOK);
                    break;

                case IDC_CHECKBACKLIGHT:
                    hwndBacklight = GetDlgItem(hwnd, IDC_CHECKBACKLIGHT);
                    SetBacklightRequirement((BST_CHECKED == SendMessage(hwndBacklight, 
                                             BM_GETCHECK, 0, 0)));
                    break;

                case IDC_BUTTON1:
                    // Set the system power state to idle, and set a timer
                    // to turn it back to full power after 5 seconds.
                    // The screen will go black if the backlight requirement 
                    // is not checked in IDC_CHECKBACKLIGHT above (depending
                    // upon the power policy of the device).
                    if (FALSE == s_fIdled)
                    {
                        // Some platforms may restrict which system power 
                        // states can be set by applications.  
                        // Can also send the system to other POWER_STATES 
                        // using this API (POWER_STATE_SUSPEND, etc.)
                        DWORD dwRet = SetSystemPowerState(NULL, POWER_STATE_IDLE, 0);
                        if (ERROR_SUCCESS == dwRet) 
                        {
                            s_fIdled = TRUE;
                            SetTimer(hwnd, 1, 5000, NULL);
                        }
                        else 
                        {
                            RETAILMSG(1, (L"SetSystemPowerState failed, error: %X\n",
                                          dwRet));
                        }
                    }
                    break;

                default:
                    fReturn = FALSE;
            }
            break;

        case WM_TIMER:
            // Set the system state to full power
            KillTimer(hwnd, 1);
            SetSystemPowerState(NULL, POWER_STATE_ON, 0);
            s_fIdled = FALSE;
            break;

        case WM_DESTROY:
            SetBacklightRequirement(FALSE);

            // Kill the power notification thread
            if (NULL != g_hEventShutDown)
            {
                SetEvent(g_hEventShutDown);

                if (NULL != g_hPowerNotificationThread)
                {
                    WaitForSingleObject(g_hPowerNotificationThread , INFINITE);
                    CloseHandle(g_hPowerNotificationThread);
                }

                CloseHandle(g_hEventShutDown);
            }    
            break;

        default:
            fReturn = FALSE;
            break;
    }

    return fReturn;
}

//***************************************************************************
// Function: WinMain
//  
// Purpose: Standard Win32 Entry point
//      
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    int nResult = 0;

    // Create mutex to track whether or not an application is already running
    HANDLE hMutex = CreateMutex(0, 0, _T("_PMSAMPLE_EXE_MUTEX_"));

    // check the result code
    if (NULL != hMutex)
    {
        if (ERROR_ALREADY_EXISTS != GetLastError())
        {
            // If the mutex doesn't already exist, create the dialog and start it.
            g_hInst = hInstance;

            nResult = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOGPOWER),
                                NULL, (DLGPROC)DlgProc);
        }
        else
        {
            // Already an instance running - attempt to switch to it and then exit
            HWND hWndExistingInstance = FindWindow(_T("Dialog"), tszTitle);

            if (NULL != hWndExistingInstance)
            {
                SetForegroundWindow(hWndExistingInstance);
            }
        }

        CloseHandle(hMutex);
    }

    return ( nResult >= 0 );
}


//***************************************************************************
// Function Name: PowerNotificationThread
//
// Purpose: listens for power change notifications
//
DWORD PowerNotificationThread(LPVOID pVoid)
{
    // size of a POWER_BROADCAST message
    DWORD cbPowerMsgSize = sizeof POWER_BROADCAST + (MAX_PATH * sizeof TCHAR);

    // Initialize our MSGQUEUEOPTIONS structure
    MSGQUEUEOPTIONS mqo;
    mqo.dwSize = sizeof(MSGQUEUEOPTIONS); 
    mqo.dwFlags = MSGQUEUE_NOPRECOMMIT;
    mqo.dwMaxMessages = 4;
    mqo.cbMaxMessage = cbPowerMsgSize;
    mqo.bReadAccess = TRUE;              
                                         
    // Create a message queue to receive power notifications
    HANDLE hPowerMsgQ = CreateMsgQueue(NULL, &mqo);
    if (NULL == hPowerMsgQ) 
    {
        RETAILMSG(1, (L"CreateMsgQueue failed: %x\n", GetLastError()));
        goto Error;
    }

    // Request power notifications 
    HANDLE hPowerNotifications = RequestPowerNotifications(hPowerMsgQ,
                                                           PBT_TRANSITION | 
                                                           PBT_RESUME | 
                                                           PBT_POWERINFOCHANGE);
    if (NULL == hPowerNotifications) 
    {
        RETAILMSG(1, (L"RequestPowerNotifications failed: %x\n", GetLastError()));
        goto Error;
    }

    HANDLE rgHandles[2] = {0};
    rgHandles[0] = hPowerMsgQ;
    rgHandles[1] = g_hEventShutDown;

    // Wait for a power notification or for the app to exit
    while(WaitForMultipleObjects(2, rgHandles, FALSE, INFINITE) == WAIT_OBJECT_0)
    {
        DWORD cbRead;
        DWORD dwFlags;
        POWER_BROADCAST *ppb = (POWER_BROADCAST*) new BYTE[cbPowerMsgSize];
            
        // loop through in case there is more than 1 msg 
        while(ReadMsgQueue(hPowerMsgQ, ppb, cbPowerMsgSize, &cbRead, 
                           0, &dwFlags))
        {
            switch (ppb->Message)
            {
                case PBT_TRANSITION:
                    RETAILMSG(1,(L"Power Notification Message: PBT_TRANSITION\n"));
                    RETAILMSG(1,(L"Flags: %lx", ppb->Flags));
                    RETAILMSG(1,(L"Length: %d", ppb->Length));
                    if (ppb->Length)
                    {
                        RETAILMSG(1,(L"SystemPowerState: %s\n", ppb->SystemPowerState));
                    }
                    break;

                case PBT_RESUME:
                    RETAILMSG(1,(L"Power Notification Message: PBT_RESUME\n"));
                    break;

                case PBT_POWERINFOCHANGE:
                {
                    RETAILMSG(1,(L"Power Notification Message: PBT_POWERINFOCHANGE\n"));

                    // PBT_POWERINFOCHANGE message embeds a 
                    // POWER_BROADCAST_POWER_INFO structure into the 
                    // SystemPowerState field
                    PPOWER_BROADCAST_POWER_INFO ppbpi =
                        (PPOWER_BROADCAST_POWER_INFO) ppb->SystemPowerState;
                    if (ppbpi) 
                    {
                        RETAILMSG(1,(L"Length: %d", ppb->Length));
                        RETAILMSG(1,(L"BatteryLifeTime = %d\n",ppbpi->dwBatteryLifeTime));
                        RETAILMSG(1,(L"BatterFullLifeTime = %d\n",
                                     ppbpi->dwBatteryFullLifeTime));
                        RETAILMSG(1,(L"BackupBatteryLifeTime = %d\n",
                                     ppbpi->dwBackupBatteryLifeTime));
                        RETAILMSG(1,(L"BackupBatteryFullLifeTime = %d\n",
                                     ppbpi->dwBackupBatteryFullLifeTime));
                        RETAILMSG(1,(L"ACLineStatus = %d\n",ppbpi->bACLineStatus));
                        RETAILMSG(1,(L"BatteryFlag = %d\n",ppbpi->bBatteryFlag));
                        RETAILMSG(1,(L"BatteryLifePercent = %d\n",
                                     ppbpi->bBatteryLifePercent));
                        RETAILMSG(1,(L"BackupBatteryFlag = %d\n",
                                     ppbpi->bBackupBatteryFlag));
                        RETAILMSG(1,(L"BackupBatteryLifePercent = %d\n",
                                     ppbpi->bBackupBatteryLifePercent));
                    }
                    break;
                }

                default:
                    break;
            }

            UpdatePowerState();
        }

        delete[] ppb;
    }

Error:
    if (hPowerNotifications)
        StopPowerNotifications(hPowerNotifications);

    if (hPowerMsgQ)
        CloseMsgQueue(hPowerMsgQ);

    return NULL;
}

