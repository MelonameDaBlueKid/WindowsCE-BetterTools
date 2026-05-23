/****************************************************************************
*
*    PROGRAM: system.c
*
*   Copyright (c) 1997 Microsoft Corporation. All rights reserved
*
*    A sample control panel  to create 'backlite.cpl'
*
*    If you place this .cpl files in the windows directory, it can be
*    activated within control panel
*
*    Or, it can be activated programatically by calling:
*    'ctlpnl.exe backlite.cpl,BackLight,0,0'
*    Formnat is: 'ctlpnl.exe cpl_filename.cpl,applet_name,applet_index,tab_index'
****************************************************************************/

#include <windows.h>
#include <cpl.h>
#include <commctrl.h>
#include "system.h"
#include "resource.h"

#ifdef DEBUG_MSGS                                                               
TCHAR   szDPF[256];    // debug printouts
#endif

typedef struct tagApplets
{
    int icon;           // icon resource identifier
    int namestring;     // name-string resource identifier
    int descstring;     // description-string resource identifier
    int dlgtemplate;    // dialog box template resource identifier
    DLGPROC dlgfn;      // dialog box procedure
} APPLETS;

const APPLETS SystemApplets[] =
{
    SYSTEM_ICON, SYSTEM_NAME, SYSTEM_DESC, GENERAL_DLG, GeneralDlgProc,
    // To Do: your control panel, has more then one applet, add them here
};


HWND hwndGeneral = NULL, hwndSystem = NULL;
HWND hwndMain = NULL;
HWND hwndTabDlg;
HWND hwndTab = NULL;
HINSTANCE g_hinst = NULL;
int CurrApplet;

static const TCHAR szClassPrefix[]  = TEXT("CPL_");
static const TCHAR szTitleSystem[] = TEXT("BackLight Properties");

static const LPCTSTR szTitle[]= {
                     szTitleSystem,
                     }; 
static const LPTSTR HelpFileTbl[] = {
                //  TEXT("file:cp_sys.htp"),
                    TEXT("file:ctpnl.htm"),
                    };

static const TCHAR szRegistryKey[] =  TEXT("ControlPanel\\Backlite");
static const TCHAR szRegValue[] =    TEXT("Light");


void  GetAppletClassName(LPTSTR szName)
{
    TCHAR   szString[32];

    LoadString (g_hinst, SystemApplets[CurrApplet].namestring,  szString, 32);

    lstrcpy(szName, szClassPrefix);
    lstrcat(szName, szString);
}


void  MsgToDialogs(UINT msg, WPARAM wp, LPARAM lp)
{

    if (hwndGeneral)    
        SendMessage(hwndGeneral, msg, wp, lp);

    if (hwndSystem) 
        SendMessage(hwndSystem, msg, wp, lp);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hwndOldFocus;

    switch (msg) 
    {
        case WM_ACTIVATE:                   
            if (LOWORD(wp) == WA_INACTIVE)
            {
                hwndOldFocus = GetFocus();
            }
            else
            {
                SetFocus(hwndOldFocus);
            }
            break;
            
        case WM_HELP:
            CreateProcess(TEXT("peghelp"), HelpFileTbl[CurrApplet], NULL,NULL,FALSE,0,NULL,NULL,NULL,NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wp))     
            {
                case IDOK:
                    DPF("WndProc: got IDOK\r\n");

                    MsgToDialogs(WM_COMMAND, IDOK, lp);
                    DestroyWindow(hwnd);
                    break;
                case IDCANCEL:
                    DPF("WndProc: got IDCANCEL\r\n");
exit:
                    MsgToDialogs(WM_COMMAND, IDCANCEL, lp);
                    DestroyWindow(hwnd);
                    break;
            }
            break;
                                                    
        case WM_CLOSE:
            DPF("WndProc: got WM_CLOSE\r\n");
            goto exit;
                        
        case WM_DESTROY:
            hwndMain = NULL;
            break;
            
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

/*------------------------------------------------------------------------*/
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS wc;
    TCHAR szClassName[60];

    GetAppletClassName(szClassName);

    wc.style         = CS_HREDRAW | CS_VREDRAW; // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)WndProc;        // Window Procedure
    wc.cbClsExtra    = 0;                       // No per-class extra data.
    wc.cbWndExtra    = 0;                       // No per-window extra data.
    wc.hInstance     = hInstance;               // Owner of this class

    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(SystemApplets[CurrApplet].icon));
    wc.hCursor       = 0;
    
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;                    // Menu name from .RC
    wc.lpszClassName = szClassName;             // Name to register as

    return RegisterClass(&wc);

} /* InitApplication()
   */


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND hwndParent)

{
    TCHAR szClassName[60];
#ifdef _WIN32_WCE_EMULATION                         
    int nWidth, nHeight;

    nWidth = 485;
    nHeight = 215;
#endif


    GetAppletClassName(szClassName);

#ifdef _WIN32_WCE_EMULATION                         
    hwndMain = CreateWindowEx(WS_EX_CAPTIONOKBTN | WS_EX_WINDOWEDGE | WS_EX_CONTEXTHELP,
                            szClassName,
                            szTitle[CurrApplet],
                            WS_SYSMENU | WS_CAPTION | WS_VISIBLE,
                            0,
                            0,
                            nWidth,
                            nHeight,
                            hwndParent,
                            NULL,
                            hInstance,
                            NULL);
#else
    hwndMain = CreateWindowEx( WS_EX_CAPTIONOKBTN | WS_EX_WINDOWEDGE | WS_EX_CONTEXTHELP,
                            szClassName,
                            szTitle[CurrApplet],
                            WS_SYSMENU | WS_CAPTION | WS_VISIBLE,
                            0,
                            0,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            hwndParent,
                            NULL,
                            hInstance,
                            NULL);
#endif

    if (!hwndMain) 
    {
        return FALSE;
    }

    SendMessage(hwndMain,WM_SETICON, FALSE,
                    (LPARAM)LoadImage(hInstance, MAKEINTRESOURCE(SystemApplets[CurrApplet].icon),
                    IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR));

    ShowWindow(hwndMain, nCmdShow);
    return TRUE;
    
} /* InitInstance()
   */



/****************************************************************************
*
*    FUNCTION: DllMain(PVOID, ULONG, PCONTEXT)
*
*    PURPOSE: Win 32 Initialization DLL
*
*    COMMENTS:
*
*
****************************************************************************/

BOOL WINAPI DllMain(
IN PVOID hmod,
IN ULONG ulReason,
IN PCONTEXT pctx OPTIONAL)
{
    if (ulReason != DLL_PROCESS_ATTACH)
    {
        return TRUE;
    }
    else
    {
        g_hinst = hmod;
    }

    return TRUE;

    UNREFERENCED_PARAMETER(pctx);
}


/****************************************************************************
*
*    FUNCTION: InitApplet(HWND)
*
*    PURPOSE: loads the caption string for the Control Panel
*
*    COMMENTS:
*
*
****************************************************************************/

BOOL InitApplet (HWND hwndParent)
{
    return TRUE;

    UNREFERENCED_PARAMETER(hwndParent);
}


/****************************************************************************
*
*    FUNCTION: TermApplet()
*
*    PURPOSE: termination procedure for the Screen applets
*
*    COMMENTS:
*
*
****************************************************************************/

void TermApplet()
{
    return;
}

/****************************************************************************
*
*    FUNCTION: CPIApplet(HWND, UINT, LONG, LONG)
*
*    PURPOSE: Processes messages for control panel applets
*
*    COMMENTS:
*
*
****************************************************************************/
LONG CALLBACK CPlApplet (hwndCPL, uMsg, lParam1, lParam2)
HWND hwndCPL;       // handle of Control Panel window
UINT uMsg;          // message
LONG lParam1;       // first message parameter
LONG lParam2;       // second message parameter
{
    int iApplet;
    LPNEWCPLINFO lpNewCPlInfo;
    static iInitCount = 0;
    MSG msg;

    switch (uMsg) 
    {
        case CPL_INIT:              // first message, sent once
            if (!iInitCount)    
            {
                if (!InitApplet(hwndCPL))
                {
                    return FALSE;
                }
            }
            iInitCount++;
            return TRUE;

        case CPL_GETCOUNT:          // second message, sent once
            return (LONG)NUM_APPLETS;

        case CPL_NEWINQUIRE:        // third message, sent once per app
            lpNewCPlInfo = (LPNEWCPLINFO) lParam2;

            iApplet = (int)(LONG)lParam1;
            lpNewCPlInfo->dwSize = (DWORD) sizeof(NEWCPLINFO);
            lpNewCPlInfo->dwFlags = 0;
            lpNewCPlInfo->dwHelpContext = 0;
            lpNewCPlInfo->lData = SystemApplets[iApplet].icon;
            lpNewCPlInfo->hIcon = LoadIcon (g_hinst,
                        (LPCTSTR) MAKEINTRESOURCE(SystemApplets[iApplet].icon));
            lpNewCPlInfo->szHelpFile[0] = '\0';

            LoadString (g_hinst, SystemApplets[iApplet].namestring,
                        lpNewCPlInfo->szName, 32);

            LoadString (g_hinst, SystemApplets[iApplet].descstring,
                        lpNewCPlInfo->szInfo, 64);
            break;
#ifdef _WIN32_WCE_EMULATION
        case CPL_SELECT:            // application icon selected, never called in WinCE
            break;
#endif
        case CPL_DBLCLK:            // application icon double-clicked
            CurrApplet = LOWORD(lParam1);  // what applet is required

            InitApplication(g_hinst);

            if (!InitInstance(g_hinst, SW_SHOW, hwndCPL))
            {
                return FALSE;
            }
            
            SetTabControl();

            iApplet = HIWORD(lParam1);      // tab to start from
            DisplayTabDialog(iApplet);
            
            while (IsWindow(hwndMain) && GetMessage(&msg, NULL, 0, 0)) 
            {
                if (IsWindow(hwndTabDlg) && IsTabDialogMessage(hwndTabDlg, &msg) )
                {
                    goto next_msg;
                }
                    
                if ( IsWindow(hwndGeneral) && IsDialogMessage(hwndGeneral, &msg) )  
                {
                    goto next_msg;
                }

                if ( IsWindow(hwndSystem) && IsDialogMessage(hwndSystem, &msg) )    
                {
                    goto next_msg;
                }

                TranslateMessage(&msg);
                DispatchMessage(&msg);
next_msg:;
            }   
            hwndMain = NULL;
            break;

         case CPL_STOP:              // sent once per app. before CPL_EXIT
            break;

         case CPL_EXIT:              // sent once before FreeLibrary called
            iInitCount--;
            if (!iInitCount)
            {
                TermApplet();
            }
            break;

         default:
            break;
    }
    return 0;
}

// Implement your code to set BackLight to the device
void HW_SetBacklight(int BackLight)
{}

// Implement your code to get value from the regsitry
HRESULT GetFromRegistry(DWORD *pPos)    
{
    HKEY    hKey;
    DWORD   dwSize, dwType;
    long    hRes;

    *pPos= 0;       
    hRes = RegOpenKeyExW(HKEY_CURRENT_USER, szRegistryKey, 0, KEY_ALL_ACCESS, &hKey);
    if (hRes != ERROR_SUCCESS) 
    {
        return hRes;
    }

    dwSize = sizeof(DWORD);
    hRes = RegQueryValueExW(hKey, szRegValue, 0, &dwType, (LPBYTE)pPos, &dwSize);
    if (hRes != ERROR_SUCCESS)
    {
        DPF("Error reading registry\r\n");
    }

    RegCloseKey(hKey);
    DPF1("Get from Registry pPos=%d  \r\n",*pPos);
    return hRes;
}

// Implement your code to save value to the regsitry
HRESULT SetToRegistry(DWORD Pos)    
{
    HKEY    hKey;
    DWORD   Disp;
    HRESULT hRes;

    hRes = RegCreateKeyExW(HKEY_CURRENT_USER, szRegistryKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &Disp);
    if (hRes != ERROR_SUCCESS) 
    {
        return hRes;
    }

    hRes = RegSetValueExW(hKey, szRegValue,0,REG_DWORD, (LPBYTE)&Pos, sizeof(DWORD));
    RegCloseKey(hKey);                  

    DPF3("Save to Registry '%s' Value=%d hRes=%x \r\n", szRegistryKey, Pos, hRes);
    return hRes;
}

// System tab dialog proc
BOOL APIENTRY SystemDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam)
{       
    static HWND hwndSlider;
    static long orgPos;         // original Backlight value
    long pos;

    switch (message)     
    {
        case WM_INITDIALOG:     
            GetFromRegistry(&orgPos);           // get current slection
            
            SetDlgItemInt(hDlg, IDC_STATIC_NUM, orgPos, FALSE);

            hwndSlider = GetDlgItem(hDlg, IDC_TRACKBAR);
            SendMessage( hwndSlider, TBM_SETRANGE, TRUE, MAKELONG(1, 15)); // range
            SendMessage( hwndSlider, TBM_SETTICFREQ, 2, 0L);              // tick freq.
            SendMessage( hwndSlider, TBM_SETPAGESIZE, 0L, 2);             // page up/dn size
            SendMessage( hwndSlider, TBM_SETPOS,TRUE, orgPos);  
            return TRUE;

        case WM_HSCROLL:            // track bar message
            switch LOWORD(wParam) 
            {
                case TB_BOTTOM:
                case TB_THUMBPOSITION:
                case TB_LINEUP:
                case TB_LINEDOWN:
                case TB_PAGEUP:
                case TB_PAGEDOWN:
                case TB_TOP:
                    pos = SendMessage(hwndSlider, TBM_GETPOS, 0, 0);
                    SetDlgItemInt(hDlg, IDC_STATIC_NUM, pos, FALSE);

                    // To Do: If needed place a call to the HW to adjust Baccklite in here
                    HW_SetBacklight(pos);
                    return (TRUE);
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                    DPF("SystemDlgProc: Got IDOK \r\n");
                    pos = SendMessage(hwndSlider, TBM_GETPOS, 0, 0);
                    // To Do: Place a call to the HW to adjust Baccklite in here
                    HW_SetBacklight(pos);
                    // To Do: Save it in registry
                    SetToRegistry(pos);     
                    return TRUE;
                case IDCANCEL:  
                    DPF("SystemDlgProc: got IDCANCEL\r\n");
                    // To Do: restore original settings
                    HW_SetBacklight(orgPos);        
                    hwndSystem = NULL;  
                    DestroyWindow(hDlg);
                    return TRUE;
            }
            break;
    } //switch (message)
    return (FALSE);
}


BOOL APIENTRY GeneralDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam)
{       

    switch (message)     
    {
        case WM_INITDIALOG: 
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                    DPF("GeneralDlgProc: Got IDOK \r\n");
                    return TRUE;
                case IDCANCEL:  
                    DPF("GeneralDlgProc: got IDCANCEL\r\n");
                    hwndGeneral = NULL; 
                    DestroyWindow(hDlg);
                    return TRUE;
            }
            break;
    }
    return (FALSE);
}


