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

// ****************************************************************************
// FILE: inky.cpp
// ABTRACT: This is the main implementation file.  It shows how to 
//          create a rich ink control, send messages to it and change
//          modes, how to save data from the control to a file and open
//          data from a file and insert it into the control.  
//          This sample also shows how to check and uncheck menu items in 
//          PocketPC devices.
// ****************************************************************************
//

#include "stdafx.h"
#include "inky.h"

#define MAX_LOADSTRING 100
#define SCROLLBARID 100
#define DEFAULT_FILE_NAME   TEXT("\\My Documents\\myink.ink")
#define SZWINDOWCLASS       TEXT("INKY")
#define SZTITLE             TEXT("Inky")

// this define makes the code that selects menus easier to read
#define SHGetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);


// Global Variables:
HINSTANCE           g_hInst;                    // The current instance
HWND                g_hwndCB;                   // The command bar handle
HWND                g_hRichInkWnd;
UINT                g_uiPenMode;
UINT                g_uiViewMode;
INT                 g_iSize;
int                 g_nMenuHeight;

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
ATOM                    MyRegisterClass     (HINSTANCE, LPTSTR);
BOOL                    InitInstance        (HINSTANCE, int);
LRESULT CALLBACK        WndProc             (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK        Save                (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK        Open                (HWND, UINT, WPARAM, LPARAM);
HWND                    CreateRpCommandBar  (HWND);
HWND                    CreateRichInkWindow (HWND, RECT*);
void                        UpdateRichInkWnd    (HWND hRichInkWnd);
static DWORD CALLBACK   WriteCallback       (DWORD, LPBYTE, LONG, LONG*);
static DWORD CALLBACK   ReadCallback        (DWORD, LPBYTE, LONG, LONG*);
void                    SetViewCheckMarks(WPARAM );
void                    SetPenCheckMarks(WPARAM );

int WINAPI WinMain( HINSTANCE g_hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    MSG msg;
    
    // Perform application initialization:
    if (!InitInstance (g_hInstance, nCmdShow)) 
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
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    It is important to call this function so that the application 
//    will get 'well formed' small icons associated with it.
//
ATOM MyRegisterClass(HINSTANCE g_hInstance, LPTSTR szWindowClass)
{
    WNDCLASS    wc;
    
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC) WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hInstance;
    wc.hIcon            = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_INKY));
    wc.hCursor          = 0;
    wc.hbrBackground    = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName     = 0;
    wc.lpszClassName    = szWindowClass;
    
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND    hWnd = NULL;
        
    g_hInst = hInstance;        // Store instance handle in our global variable
    
    //If it is already running, then focus on the window
    hWnd = FindWindow(SZWINDOWCLASS, SZTITLE);  
    if (hWnd) 
    {
        // set focus to foremost child window
        // The "| 0x01" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow ((HWND) (((DWORD)hWnd) | 0x01));    
        return 0;
    } 
    
    MyRegisterClass(hInstance, SZWINDOWCLASS);
    
    InitRichInkDLL();
    
    RECT    rect;
    GetClientRect(hWnd, &rect);
    
    hWnd = CreateWindow(SZWINDOWCLASS, SZTITLE, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (NULL == hWnd)
    {   
        return FALSE;
    }
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    
    switch (message) 
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam); 
        wmEvent = HIWORD(wParam); 
        
        // Parse the menu selections:
        switch (wmId)
        {   
        case ID_NEW:
            {
                RECT rc;
                GetClientRect(hWnd, &rc);
                DestroyWindow(g_hRichInkWnd);
                g_hRichInkWnd = CreateRichInkWindow(hWnd, &rc);
                UpdateRichInkWnd(g_hRichInkWnd);                
            }
            break;
            
        case ID_EDIT_UNDO:
            SendMessage(g_hRichInkWnd, EM_UNDOEVENT, NULL, NULL);
            break;
            
        case ID_EDIT_REDO:
            SendMessage(g_hRichInkWnd, EM_REDOEVENT, NULL, NULL);
            break;
            
        case ID_TOOLS_PENMODE_PEN:
            g_uiPenMode = MODE_PEN;
            UpdateRichInkWnd(g_hRichInkWnd);
            SetPenCheckMarks(wParam);
            break;
            
        case ID_TOOLS_PENMODE_SELECT:
            g_uiPenMode = MODE_SELECT;
            UpdateRichInkWnd(g_hRichInkWnd);
            SetPenCheckMarks(wParam);
            break;
            
        case ID_TOOLS_PENMODE_SPACE:
            g_uiPenMode = MODE_SPACE;
            UpdateRichInkWnd(g_hRichInkWnd);
            SetPenCheckMarks(wParam);
            break;          
            
        case ID_TOOLS_VIEWMODE_TYPING:
            g_uiViewMode = VT_TYPINGVIEW;
            UpdateRichInkWnd(g_hRichInkWnd);
            SetViewCheckMarks(wParam);
            break;
            
        case ID_TOOLS_VIEWMODE_WRITING:
            g_uiViewMode = VT_WRITINGVIEW;
            UpdateRichInkWnd(g_hRichInkWnd);
            SetViewCheckMarks(wParam);
            break;
            
        case ID_TOOLS_VIEWMODE_DRAWING:
            g_uiViewMode = VT_DRAWINGVIEW;
            UpdateRichInkWnd(g_hRichInkWnd);
            SetViewCheckMarks(wParam);
            break;
            
        case ID_TOOLS_OPEN:
            {
                HANDLE  hFileToOpen     = NULL;
                TCHAR*  pszFileToOpen   = NULL;
                
                // get rid of the current window content
                DestroyWindow(g_hRichInkWnd);
                SendMessage(hWnd, WM_COMMAND, (WPARAM)ID_NEW, NULL);
                
                // get the name of the file the user wishes to use          
                pszFileToOpen = (TCHAR*)DialogBox(g_hInst, (LPCTSTR)IDD_OPEN, NULL, (DLGPROC)Open);  
                
                // check to see if we returned null - means the user clicked cancel
                if(pszFileToOpen)
                {
                    // check to see if the file name has greater than 0 length
                    if(wcslen(pszFileToOpen))
                    {
                        hFileToOpen = CreateFile(pszFileToOpen, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                        
                        // free the memory allocated in the dialog control for the string
                        LocalFree(pszFileToOpen);
                        
                        // if we have a valid file handle, get the file contents
                        if(hFileToOpen)
                        {
                            EDITSTREAM  est;
                            COOKIE      cookie;
                            BYTE*       pBuffer;
                            INT         iFileSize = 0;
                            INT         iResult;
                            
                            // determine the file size
                            iFileSize = GetFileSize(hFileToOpen, NULL);
                            
                            // if the file size is not invalid, set up the structs required to get the file data into a buffer
                            if(iFileSize != 0xFFFFFFFF)
                            {
                                // buffer to store the file data in
                                pBuffer = (BYTE*)LocalAlloc(LPTR, iFileSize);
                                
                                cookie.dwError      = 0;
                                cookie.pbStart      = (LPBYTE)pBuffer;
                                cookie.pbCur        = cookie.pbStart;
                                cookie.bCount       = iFileSize;
                                cookie.hFile        = hFileToOpen;
                                
                                est.dwCookie        = (DWORD)&cookie;
                                est.dwError         = 0;
                                est.pfnCallback     = ReadCallback;
                                
                                // send the data into the control and the control paints the data to the screen
                                iResult = SendMessage (g_hRichInkWnd, EM_STREAMIN, (WPARAM)SF_PWI, (LPARAM)&est);
                                
                                LocalFree(pBuffer);
                            }
                            else
                            {
                                MessageBox(hWnd, TEXT("Could not determine file size"), TEXT("Open Error:"), MB_OK);
                            }
                            
                            CloseHandle(hFileToOpen);                               
                        }
                        else
                        {
                            MessageBox(hWnd, TEXT("Could not create file"), TEXT("Open Error:"), MB_OK);    
                        }
                        
                    }
                    else
                    {
                        MessageBox(hWnd, TEXT("File name invalid"), TEXT("Open Error:"), MB_OK);
                    }                   
                }
            }
            break;
            
        case ID_TOOLS_SAVE:
            {
                HANDLE  hFileToSave     = NULL;
                TCHAR*  pszFileToSave   = NULL;
                
                // get the name of the file the user wishes to save         
                pszFileToSave = (TCHAR*)DialogBox(g_hInst, (LPCTSTR)IDD_SAVE, NULL, (DLGPROC)Save);  
                
                // check to see if we returned null - means the user clicked cancel
                if(pszFileToSave)
                {
                    // check to see if the file name has greater than 0 length
                    if(pszFileToSave != NULL && wcslen((LPTSTR)pszFileToSave))
                    {
                        // always create a file named what the user gives (overwrite old files without prompting)
                        hFileToSave = CreateFile(pszFileToSave, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                        
                        // free memory used to save file name in the dialog
                        LocalFree(pszFileToSave);
                        
                        // if we have a valid file handle, we can save to the file
                        if(hFileToSave)
                        {
                            EDITSTREAM est;
                            COOKIE  cookie;
                            BYTE*   pBuffer;
                            INT     iDataSize = 0;
                            INT     iResult;
                            
                            // determine the size of the data to write out
                            cookie.dwError      = 0;
                            cookie.pbStart      = 0;
                            cookie.pbCur        = 0;
                            cookie.bCount       = 0;
                            cookie.hFile        = 0;
                            est.dwCookie        = (DWORD)&cookie;
                            est.dwError         = 0;
                            est.pfnCallback     = WriteCallback;
                            
                            iResult = SendMessage (g_hRichInkWnd, EM_STREAMOUT, (WPARAM)SF_PWI, (LPARAM)&est);
                            
                            // this is the size of the data we wish to write
                            iDataSize = cookie.pbCur - cookie.pbStart;
                            
                            // Allocate memory for the data
                            pBuffer = (BYTE*)LocalAlloc(LPTR, iDataSize);
                            
                            // now save the data to the file
                            cookie.dwError      = 0;
                            cookie.hFile        = hFileToSave;
                            cookie.pbStart      = (LPBYTE)pBuffer;
                            cookie.pbCur        = cookie.pbStart;
                            cookie.bCount       = iDataSize;
                            est.dwCookie        = (DWORD)&cookie;
                            est.dwError         = 0;
                            est.pfnCallback     = WriteCallback;
                            
                            
                            // get the data out of the control and into the file
                            iResult = SendMessage(g_hRichInkWnd, EM_STREAMOUT, (WPARAM)SF_PWI, (LPARAM)&est);
                            
                            CloseHandle(hFileToSave);
                            LocalFree(pBuffer);
                        }
                        else
                        {
                            MessageBox(hWnd, TEXT("Could not create file"), TEXT("Save Error:"), MB_OK);
                        }
                        
                    }
                    else
                    {
                        MessageBox(hWnd, TEXT("File name invalid"), TEXT("Save Error:"), MB_OK);
                    }   
                }                   
                
            }
            break;
            
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

    case WM_CREATE:
        {
            RECT rc;
            HMENU   hMenu = NULL;
            GetClientRect(hWnd, &rc);
            
            g_hwndCB = CreateRpCommandBar(hWnd);
            
            // create a rich ink window and set the default modes
            g_hRichInkWnd = CreateRichInkWindow(hWnd, &rc);
            g_uiPenMode = MODE_PEN;
            g_uiViewMode = VT_DRAWINGVIEW;
            UpdateRichInkWnd(g_hRichInkWnd);

            // check the menu items that correspond to default settings
            SetPenCheckMarks(ID_TOOLS_PENMODE_PEN);
            SetViewCheckMarks(ID_TOOLS_VIEWMODE_DRAWING);
            break;
        }
        
    case WM_DESTROY:
        CommandBar_Destroy(g_hwndCB);
        PostQuitMessage(0);
        break;
        
    case WM_SETTINGCHANGE:
        if ((SETTINGCHANGE_RESET == wParam) ||
            (SPI_SETSIPINFO == wParam))
        {
            //Orientation Change

            RECT rect;
            SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, FALSE);

            SIPINFO si = {0};
            si.cbSize = sizeof(si);
            SHSipInfo(SPI_GETSIPINFO, 0, &si, 0);

            //Change rect to be left/top/width/height
            rect.right = rect.right - rect.left;
            rect.bottom = rect.bottom - rect.top - g_nMenuHeight;

            if (SIPF_ON == (si.fdwFlags & SIPF_ON))
            {
                //SIP is shown, make space for it on bottom of screen
                rect.bottom = rect.bottom - (si.rcSipRect.bottom - si.rcSipRect.top);
            }

            MoveWindow(hWnd, rect.left, rect.top, rect.right, rect.bottom , FALSE);

            if(IsWindow(g_hRichInkWnd))
            {
                MoveWindow(g_hRichInkWnd, 0, 0, rect.right,
                    rect.bottom, FALSE);
            }


        }
        break;
    
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

HWND CreateRpCommandBar(HWND hwnd)
{
    SHMENUBARINFO mbi;
    
    memset(&mbi, 0, sizeof(SHMENUBARINFO));
    mbi.cbSize     = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hwnd;
    mbi.nToolBarId = IDM_MENU;
    mbi.hInstRes   = g_hInst;
    mbi.nBmpId     = 0;
    mbi.cBmpImages = 0;
    
    if (TRUE == SHCreateMenuBar(&mbi)) 
    {
        RECT rect;
        //Set menu height
        GetClientRect(mbi.hwndMB, &rect);
        g_nMenuHeight=rect.bottom - rect.top;
    }

    return mbi.hwndMB;
}

// Message handler for the Save dialog
LRESULT CALLBACK Save(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    SHINITDLGINFO shidi;
    
    switch (message)
    {
    case WM_INITDIALOG:
        // Create a Done button and size it.  
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        SHInitDialog(&shidi);
        
        // provide a default file name
        SetDlgItemText(hDlg, IDC_SAVENAME, DEFAULT_FILE_NAME);
        return TRUE; 
        
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) 
        {
            // allocate memory for the file name the user typed in
            TCHAR*  pszFileName = NULL;
            pszFileName = (TCHAR*)LocalAlloc(LPTR, MAX_PATH);
            
            if(pszFileName)
            {
                // get the file name
                GetDlgItemText(hDlg, IDC_SAVENAME, pszFileName, MAX_PATH);
                
                // end the dialog passing a pointer to the TCHAR string
                EndDialog(hDlg, (INT)pszFileName);
                
            }
            else
            {
                MessageBox(hDlg, TEXT("Cannot allocate memory to store file name"), TEXT("Save error"), MB_OK);
                EndDialog(hDlg, NULL);

            }
            return TRUE;
        }
        if(LOWORD(wParam) == IDC_CANCEL)
        {
            // send null as return value so we know the user clicked cancel
            EndDialog(hDlg, NULL);
            return TRUE;
        }
        
        break;
    }
    return FALSE;
}

// Mesage handler for the open dialog
LRESULT CALLBACK Open(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    SHINITDLGINFO shidi;
    
    switch (message)
    {
    case WM_INITDIALOG:
        // Create a Done button and size it.  
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        SHInitDialog(&shidi);
        
        // provide a default file name
        SetDlgItemText(hDlg, IDC_OPENFILE, DEFAULT_FILE_NAME);
        return TRUE; 
        
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) 
        {
            // allocate memory for the file name the user typed in
            TCHAR*  pszFileName = NULL;
            pszFileName = (TCHAR*)LocalAlloc(LPTR, MAX_PATH);
            
            if(pszFileName)
            {
                // get the file name
                GetDlgItemText(hDlg, IDC_OPENFILE, pszFileName, MAX_PATH);
                
                // end the dialog passing a pointer to the TCHAR string
                EndDialog(hDlg, (INT)pszFileName);
                
            }
            else
            {
                MessageBox(hDlg, TEXT("Cannot allocate memory to store file name"), TEXT("Save error"), MB_OK);
                EndDialog(hDlg, NULL);

            }
            return TRUE;
        }
        if(LOWORD(wParam) == IDC_CANCEL)
        {
            // send null as return value so we know the user clicked cancel
            EndDialog(hDlg, NULL);
            return TRUE;
        }
        
        break;
    }
    return FALSE;
}

// function to create a rich ink window of the specified rect size and position
// that is a child of hParent and has a vertical scroll bar
HWND CreateRichInkWindow(HWND hParent, LPRECT rc)
{
    HWND hReturn = CreateWindow(WC_RICHINK, NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL,
        rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, hParent, NULL, g_hInst, NULL);
    
    if(hReturn)
    {
        // adjust the default style to be zoomed to 200% and have ruled lines
        SendMessage(hReturn, EM_SETPAGESTYLE, (WPARAM)PS_RULEDLINES, NULL);
        SendMessage(hReturn, EM_SETZOOMPERCENT, NULL, (LPARAM)200);
    }
    return hReturn;
}

// update the rich ink control specified by hRichInkWnd with the pen mode
// and view the user chooses via the menubar
void UpdateRichInkWnd(HWND hRichInkWnd)
{
    SendMessage(hRichInkWnd, EM_SETPENMODE, (WPARAM)g_uiPenMode, 0);
    SendMessage(hRichInkWnd, EM_SETVIEW, (WPARAM)g_uiViewMode, 0);
}

// This is a callback function that reads from a file and stores the data into the buffer
// specified in the EDITSTREAM->COOKIE structure
static DWORD CALLBACK ReadCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    PCOOKIE pCookie = (PCOOKIE)dwCookie;
    // Zero the bytes read.
    *pcb = 0;
    
    
    if (ReadFile(pCookie->hFile, pbBuff, cb, (ULONG*)pcb, 0) == 0)
    {
        // if there is an error, we return the error code
        return (pCookie->dwError = GetLastError());
    }   
    
    return 0;
} 

// This is a callback function that saves to a file from data saved in a buffer
// specified in the EDITSTREAM->COOKIE structure
static DWORD CALLBACK WriteCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    PCOOKIE pCookie = (PCOOKIE)dwCookie;
    
    if (WriteFile(pCookie->hFile, pbBuff, cb, (ULONG*)pcb, 0) == 0)
    {
        // if there is an error, we return the error code
        return (pCookie->dwError = GetLastError());
    }

    return 0;
} 


void SetViewCheckMarks(WPARAM wParam)
{
    HMENU   hMenu = NULL;
    if(g_hwndCB)
    {
        // get the tools menu handle
        hMenu = SHGetSubMenu(g_hwndCB,ID_TOOLS) ;
        // uncheck all menu items
        CheckMenuItem(hMenu, ID_TOOLS_VIEWMODE_TYPING, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(hMenu, ID_TOOLS_VIEWMODE_WRITING, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(hMenu, ID_TOOLS_VIEWMODE_DRAWING, MF_BYCOMMAND | MF_UNCHECKED);

        // check the selected menu item
        CheckMenuItem(hMenu, LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
    }
}

void SetPenCheckMarks(WPARAM wParam)
{
    HMENU   hMenu = NULL;
    if(g_hwndCB)
    {
        // get the tools menu handle
        hMenu = SHGetSubMenu(g_hwndCB,ID_TOOLS) ;
        // uncheck all menu items
        CheckMenuItem(hMenu, ID_TOOLS_PENMODE_PEN, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(hMenu, ID_TOOLS_PENMODE_SELECT, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(hMenu, ID_TOOLS_PENMODE_SPACE, MF_BYCOMMAND | MF_UNCHECKED);

        // check the selected menu item
        CheckMenuItem(hMenu, LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
    }
}

