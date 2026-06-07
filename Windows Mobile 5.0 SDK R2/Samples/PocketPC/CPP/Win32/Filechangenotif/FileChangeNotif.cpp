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


#define MAX_LOADSTRING 100
#define TRAY_NOTIFYICON WM_USER + 2005
#define ID_VIRUS_CATCH_TRAY    5000
#define VCHECKT_REG_ENTRY TEXT("Software\\VirusScan\\Vcheckt")

// Global Variables
TCHAR        g_szLogPath[MAX_PATH];
HANDLE        g_hLogFile;

#define CountOf(x) (sizeof(x)/sizeof(*x))

// Global Variables:
HICON                g_hIcon;            //Global hIcon for tray messages
HINSTANCE            g_hInst;            //Global hInstance
HWND                g_hWnd;                //Global hWnd
SHCHANGENOTIFYENTRY g_schneNotifyEntry;
TCHAR                g_tszWatchDir[MAX_PATH];
BOOL                g_bRecursive;
BOOL                g_bStarted;

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(
    HINSTANCE, 
    LPTSTR
    );
BOOL InitInstance(
    HINSTANCE,
    int
    );
LRESULT CALLBACK WndProc(
    HWND,
    UINT,
    WPARAM, 
    LPARAM
    );
LRESULT CALLBACK SHCNEListener(
    HWND,
    UINT, 
    WPARAM,
    LPARAM
    );
LRESULT CALLBACK Options(
    HWND,
    UINT, 
    WPARAM,
    LPARAM
    );
HWND CreateRpCommandBar(
    HWND
    );

// Event logging functions
BOOL InitLog();
BOOL LogSHCNEEvent(
    FILECHANGEINFO*
    );
void WriteToLog(
    LPTSTR tszLine
    );


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
    )
{
    MSG msg;
    
    // Perform application initialization:
    if (FALSE == InitInstance(hInstance, nCmdShow)) 
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

// Tray Icons and Notification ------------------------------

BOOL TrayMessage(
    HWND hwnd, 
    DWORD dwMessage, 
    UINT uID, 
    HICON hIcon, 
    LPTSTR pszTip)
{
    BOOL            res        = FALSE;
    NOTIFYICONDATA    tnd;
    
    memset(&tnd, 0, sizeof(NOTIFYICONDATA));
    tnd.cbSize                = sizeof(NOTIFYICONDATA);
    tnd.hWnd                = hwnd;
    tnd.uID                    = uID;                        // icon id
    tnd.uFlags                = NIF_MESSAGE|NIF_ICON;        //|NIF_TIP;
    tnd.uCallbackMessage    = TRAY_NOTIFYICON;            // call back Msg
    tnd.hIcon                = hIcon;
    tnd.szTip[0]            = '\0';
    
    res = Shell_NotifyIcon(dwMessage, &tnd);
    
    return res;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    It is important to call this function so that the application 
//    will get 'well formed' small icons associated with it.
//
ATOM MyRegisterClass(
    HINSTANCE hInstance, 
    LPTSTR ptszWindowClass
    )
{
    WNDCLASS    wc;
    
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc        = (WNDPROC) WndProc;
    wc.cbClsExtra        = 0;
    wc.cbWndExtra        = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FILECHANGENOTIF));
    wc.hCursor            = 0;
    wc.hbrBackground    = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName        = 0;
    wc.lpszClassName    = ptszWindowClass;
    
    return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
//
//  PURPOSE: Saves instance handle and creates main window
//
//  COMMENTS:
//
//    In this function, we save the instance handle in a global variable and
//    create and display the main program window.
//
BOOL InitInstance(
    HINSTANCE hInstance, 
    int nCmdShow
    )
{
    HWND    hWnd = NULL;
    TCHAR    tszTitle[MAX_LOADSTRING];            // The title bar text
    TCHAR    tszWindowClass[MAX_LOADSTRING];        // The window class name
    
    // Store instance handle in our global variable
    g_hInst = hInstance;        
    
    // Initialize global strings
    LoadString(hInstance, IDC_FILECHANGENOTIF, tszWindowClass, MAX_LOADSTRING);
    LoadString(hInstance, IDS_APP_TITLE, tszTitle, MAX_LOADSTRING);
    
    //If it is already running, then focus on the window
    hWnd = FindWindow(tszWindowClass, tszTitle);    
    if (NULL != hWnd) 
    {
        SetForegroundWindow (hWnd);    
        return FALSE;
    } 
    
    MyRegisterClass(hInstance, tszWindowClass);
    
    //Load the icon
    g_hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_FILECHANGENOTIF),
        IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    
    g_hWnd = CreateWindow(tszWindowClass, NULL, WS_NONAVDONEBUTTON, 0, 0, 0, 
        0,NULL, NULL, hInstance, NULL);
    if (NULL == g_hWnd)
    {    
        return FALSE;
    }
    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND    - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY    - post a quit message and return
//
//
LRESULT CALLBACK WndProc(
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    )
{
    BOOL bRtn;
    int wmId;
    int wmEvent;
    
    // Structures for handling the File Change Information
    FILECHANGENOTIFY    *lpfcn;
    FILECHANGEINFO        *lpfci;    
    
    switch (Msg) 
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam); 
        wmEvent = HIWORD(wParam); 
        // Parse the menu selections:
        switch (wmId)
        {    
        case IDOK:
            SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
            SendMessage (hWnd, WM_CLOSE, 0, 0);
            break;
        
        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }
        break;
        
        case WM_CREATE:
            // create our new button
            bRtn = TrayMessage(hWnd, NIM_ADD, ID_VIRUS_CATCH_TRAY, g_hIcon , NULL);
            break;
            
        case WM_DESTROY:
            bRtn = TrayMessage(hWnd, NIM_DELETE, ID_VIRUS_CATCH_TRAY, g_hIcon, NULL);
            SHChangeNotifyDeregister(hWnd);
            PostQuitMessage(0);
            break;
        
        case TRAY_NOTIFYICON:
            switch (lParam)
            {
            case WM_LBUTTONDOWN:
                if (wParam == ID_VIRUS_CATCH_TRAY)
                {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_SHCNELISTENER), NULL, (DLGPROC)SHCNEListener);                        
                }
                break;
        
            default:
                break;
            }
            
            case WM_SETTINGCHANGE:
                SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
                break;
            
            case WM_FILECHANGEINFO:
                // see if the pointer to the file change notify struct is valid
                lpfcn = (FILECHANGENOTIFY *)lParam;
                if (NULL == lpfcn)
                {
                    break;
                }
                // see if the pointer to the file change info structure
                lpfci = &(lpfcn->fci);
                if (NULL == lpfci)
                {
                    break;
                }
                else
                {
                    if (FALSE == LogSHCNEEvent(lpfci))
                    {
                        MessageBox(g_hWnd, TEXT("SCHNE Event was not logged"),
                            TEXT("Program Error"), MB_OK);
                    }                    
                }
                
                SHChangeNotifyFree(lpfcn);
                break;            
                
            default:
                return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
    return 0;
}

// Mesage handler for the SCH Event Listener Dialog
LRESULT CALLBACK SHCNEListener(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    )
{
    SHINITDLGINFO shidi;
    SHMENUBARINFO mbi;
    LPTSTR ptszFileBuffer;
    DWORD dwBytesRead;
    TCHAR szLogPath[MAX_PATH];
    HANDLE hLogFile;
    int iFileSize;
    
    BOOL bReturn;
    
    switch (Msg)
    {
    case WM_INITDIALOG:
        
        // Create command bar
        memset(&mbi, 0, sizeof(mbi));
        mbi.cbSize = sizeof(mbi);
        mbi.hwndParent = hDlg;
        //mbi.dwFlags = SHCMBF_EMPTYBAR;
        mbi.nToolBarId = IDM_MENU;
        mbi.hInstRes = g_hInst;
        
        bReturn = SHCreateMenuBar(&mbi);
        
        // Create a Done button and size it.  
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        SHInitDialog(&shidi);
        
        // Display the log file
        if (g_bStarted)
        {
            PostMessage(hDlg, WM_COMMAND, IDC_REFRESH, NULL);
        }
        break;
        
        
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            break;
            
        case IDC_START:
            //register the app to hear SHCHangeNotify messages
            g_bStarted = TRUE;
            g_schneNotifyEntry.dwEventMask = SHCNE_ALLEVENTS;
            g_schneNotifyEntry.pszWatchDir = NULL;
            g_schneNotifyEntry.fRecursive = TRUE;
            if (NULL == SHChangeNotifyRegister(g_hWnd, &g_schneNotifyEntry))
            {
                MessageBox(hDlg, TEXT("Cannnot register app for file notifications.  Program Execution Aborted."),
                    TEXT("Program Error:"), MB_OK);
                EndDialog(hDlg, LOWORD(wParam));
                SendMessage(g_hWnd, WM_CLOSE, 0, 0);
            }
            
            // register our window for SHCNE Events from the shell
            if (FALSE == InitLog())
            {
                MessageBox(hDlg, TEXT("Cannnot create log file.  Program Execution Aborted."),
                    TEXT("Program Error:"), MB_OK);
                EndDialog(hDlg, LOWORD(wParam));
                SendMessage(g_hWnd, WM_CLOSE, 0, 0);
            }
            else
            {
                PostMessage(hDlg, WM_COMMAND, IDC_REFRESH, NULL);
            }
            break;
            
        case IDC_STOP:
            EndDialog(hDlg, LOWORD(wParam));
            SendMessage(g_hWnd, WM_CLOSE, 0, 0);
            break;
            
        case IDM_TOOLS_OPTIONS:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_OPTIONSBOX), NULL, (DLGPROC)Options);
            break;
            
        case IDC_REFRESH:
            LoadString(g_hInst, IDS_LOG_PATH, szLogPath, MAX_PATH);
            hLogFile = CreateFile(szLogPath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
            if (INVALID_HANDLE_VALUE != hLogFile)
            {
                iFileSize = GetFileSize(hLogFile, NULL);
                ptszFileBuffer = (LPTSTR)LocalAlloc(LPTR, iFileSize);
                if (NULL != ptszFileBuffer)
                {
                    //File contents are ascii/unicode based on compilation,
                    // therefore no conversion is needed
                    ReadFile(hLogFile, ptszFileBuffer,  iFileSize, &dwBytesRead, NULL);
                    SetDlgItemText(hDlg, IDE_RESULTS_DISPLAY, ptszFileBuffer);
                    LocalFree(ptszFileBuffer);
                    g_bStarted = TRUE;
                }
                CloseHandle(hLogFile);
            }
            else
            {
                MessageBox(hDlg, TEXT("Log view failed."), TEXT("Program Error:"), MB_OK);
            }
            break;
            
        default:
            break;
        }
        break;
    }
    
    return FALSE;
}

// Mesage handler for the Options Dialog
LRESULT CALLBACK Options(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    )
{
    
    SHINITDLGINFO shidi;
    HWND hCheckHandle = GetDlgItem(hDlg, IDC_RECURSIVE);
    BOOL bIsChecked = 0;
    
    switch (Msg)
    {
    case WM_INITDIALOG:
        // make the checkbox checked
        SendMessage(hCheckHandle, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);            
        
        // Create a Done button and size it.  
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        SHInitDialog(&shidi);
        break;
        
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) 
        {
            GetDlgItemText(hDlg, IDC_ROOTDIR, g_tszWatchDir, MAX_PATH);
            
            if (BST_CHECKED == (int)SendMessage(hCheckHandle, BM_GETCHECK, 0, 0))
            {
                bIsChecked = TRUE;
            }
            else
            {
                bIsChecked = FALSE;
            }
            SHChangeNotifyDeregister(g_hWnd);
            
            // set up the new stuff and re-register the app
            g_schneNotifyEntry.dwEventMask = SHCNE_ALLEVENTS;
            g_schneNotifyEntry.pszWatchDir = g_tszWatchDir;
            g_schneNotifyEntry.fRecursive = bIsChecked;
            
            if (NULL == SHChangeNotifyRegister(g_hWnd, &g_schneNotifyEntry))
            {
                MessageBox(hDlg, TEXT("Cannnot register app for file notifications.  Program Execution Aborted."), TEXT("Program Error:"), MB_OK);
                EndDialog(hDlg, LOWORD(wParam));
                SendMessage(g_hWnd, WM_CLOSE, 0, 0);
            }
            
            // register our window for SHCNE Events from the shell
            if (FALSE == InitLog())
            {
                MessageBox(hDlg, TEXT("Cannnot create log file.  Program Execution Aborted."), TEXT("Program Error:"), MB_OK);
                EndDialog(hDlg, LOWORD(wParam));
                SendMessage(g_hWnd, WM_CLOSE, 0, 0);
            }
            
            EndDialog(hDlg, LOWORD(wParam));                
        }
        break;
    }
    return FALSE;
}

BOOL LogSHCNEEvent(
    FILECHANGEINFO *lpfci
    )
{
    TCHAR            tszInfoBuffer[MAX_PATH];
    FILETIME        ftLocalTime;
    SYSTEMTIME        sCurrentTime;
    BOOL            bReturn = FALSE;
    TCHAR*            ptszSystemDate = (TCHAR*)LocalAlloc(LPTR, MAX_PATH);
    
    if (ptszSystemDate)
    {
        if (lpfci->wEventId != SHCNE_UPDATEITEM)
        {
            g_hLogFile = CreateFile(g_szLogPath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, 
                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
            SetFilePointer(g_hLogFile, 0, NULL, FILE_END);    
        }    
        
        switch (lpfci->wEventId)
        {
        case SHCNE_RENAMEITEM: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_RENAMEITEM:N"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Old File Name: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            
            // show thte new name of the file
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("New File Name: %s\r\n"), lpfci->dwItem2);
            WriteToLog(tszInfoBuffer);
            
            // show the file size
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("File Size: %u\r\n"), lpfci->nFileSize);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_CREATE:
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_CREATE:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("New File Name: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            
            // show the file size
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("File Size: %u\r\n"), lpfci->nFileSize);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_DELETE:
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_DELETE:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Deleted File Name: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_MKDIR:
            // save event title to log
            _sntprintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_MKDIR:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("New Directory Name: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_RMDIR: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_RMDIR:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Old Directory Name: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            
            // show thte new name of the file
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("New Directory Name: %s\r\n"), lpfci->dwItem2);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_MEDIAINSERTED: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_MEDIAINSERTED:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Media Inserted Text: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_MEDIAREMOVED: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_MEDIAREMOVED:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Media Removed Text: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_DRIVEADD: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_DRIVEADD:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Drive Added Text: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_DRIVEREMOVED: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_DRIVEREMOVED:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Drive Removed Text: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_NETSHARE: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_NETSHARE:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Netshare Added: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_NETUNSHARE: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_NETUNSHARE:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Netshare Removed: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_ATTRIBUTES: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_ATTRIBUTES:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Item/Folder: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            
            // show the file size
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("File Size: %u\r\n"), lpfci->nFileSize);
            WriteToLog(tszInfoBuffer);
            
            break;
            
        case SHCNE_UPDATEDIR: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_UPDATEDIR:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Updated Directory: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_SERVERDISCONNECT: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_SERVERDISCONNECT:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Disconnected from: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            break;
            
        case SHCNE_RENAMEFOLDER: 
            // save event title to log
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("SHCNE_RENAMEFOLDER:\r\n"));
            WriteToLog(tszInfoBuffer);
            
            // get event date/time and save it to log
            FileTimeToLocalFileTime(&(lpfci->ftModified), &ftLocalTime);
            FileTimeToSystemTime(&ftLocalTime, &sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Event Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Folder Old Name: %s\r\n"), lpfci->dwItem1);
            WriteToLog(tszInfoBuffer);
            
            // show the old name of the file    
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("Folder New Name: %s\r\n"), lpfci->dwItem2);
            WriteToLog(tszInfoBuffer);
            break;
            
        default:
            break;
        }
    
        CloseHandle(g_hLogFile);
        LocalFree(ptszSystemDate);
        bReturn = TRUE;
    }
    
    return bReturn;
}

// This function could write ASCII log files instead of unicode, but internationalization
// was important for this sample
void WriteToLog(
    LPTSTR tszLine
    )
{
    DWORD dwWritten;

    WriteFile(g_hLogFile, tszLine, _tcslen(tszLine) * sizeof(*tszLine), &dwWritten, NULL);
}

// create the log file (if not created) and set the global log path string
BOOL InitLog()
{
    TCHAR*            ptszSystemDate;
    TCHAR            tszInfoBuffer[MAX_PATH];
    SYSTEMTIME        sCurrentTime;
    BOOL            bReturn    = FALSE;
    
    LoadString(g_hInst, IDS_LOG_PATH, g_szLogPath, MAX_PATH);
    g_hLogFile = CreateFile(g_szLogPath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, 
                          CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
    
    if (INVALID_HANDLE_VALUE == g_hLogFile)
    {
        MessageBox(NULL, TEXT("Cannot create log file"), 
            TEXT("vChecker Status:"), MB_OK);
        //bReturn = FALSE; //for readability - already set to false
    }
    else
    {
        // estasblish buffer
        ptszSystemDate = (TCHAR*)LocalAlloc(LPTR, MAX_PATH);
        if (NULL != ptszSystemDate)
        {
            //move torward end
            SetFilePointer(g_hLogFile, 0, NULL, FILE_END);
            TCHAR szFileHeader[MAX_PATH] = TEXT("VcheckerTest 1.0 Log of Events\r\n");
            
            // establish file header
            WriteToLog(szFileHeader);
            
            //     gets current date and time
            GetLocalTime(&sCurrentTime);
            GetDateFormatW(NULL, DATE_LONGDATE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("System Date: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            GetTimeFormatW(NULL, LOCALE_NOUSEROVERRIDE, &sCurrentTime, NULL, ptszSystemDate, MAX_PATH);
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("System Time: %s\r\n"), ptszSystemDate);
            WriteToLog(tszInfoBuffer);
            
            StringCchPrintf(tszInfoBuffer, CountOf(tszInfoBuffer), TEXT("*************************\r\n"));
            WriteToLog(tszInfoBuffer);
            
            CloseHandle(g_hLogFile);
            LocalFree(ptszSystemDate);
            bReturn = TRUE;
        }
    }
    return bReturn;

}