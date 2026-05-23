// MenuDemo.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <winuserm.h>
#include "resource.h"
#include "newres.h"

// useful macro
#define ARRAY_LENGTH(x)(sizeof(x)/sizeof((x)[0]))

#define DIALOGWINDOWCLASS TEXT("Dialog")


//  global variables
HINSTANCE   g_hInst;            // Local copy of hInstance
HWND        g_hWndMenuBarCurrent;   // Current active menubar
HWND        g_hWndMenuBar1;         // Handle to menu bar #1
HWND        g_hWndMenuBar2;         // Handle to menu bar #2
BOOL        g_fChecked_Sk;          // True if "Disable SoftKey" is checked
BOOL        g_fChecked_Swap;        // True if "Swap SoftKeys" is checked
BOOL        g_fChecked_Quit;        // True if "Disable Options->Quit" is checked
UINT        g_uiSk_Id1;             // The current command ID of the action Softkey on Menubar 1
UINT        g_uiSk_Id2;             // The current command ID of the action Softkey on Menubar 2


//  function declarations
BOOL CALLBACK DialogProc(
    const HWND hWnd, 
    const UINT Msg, 
    const WPARAM wParam,
    const LPARAM lParam
);
BOOL ProcessCheckBox(
    const HWND hWnd, 
    const WPARAM wParam 
);
BOOL OnMenuPopup(
    const HWND hWnd, 
    const WPARAM wParam
);
BOOL ProcessSwapMenuBar(
    const HWND hWnd
);
BOOL InitDialog(
    const HWND hDlg 
);
BOOL UncheckAll(
    const HWND hWnd
);
BOOL ProcessListBox(
    const HWND hWnd
);
BOOL ProcessSkCheckBox();

//
//  FUNCTION: WinMain(HANDLE, HANDLE, LPWSTR, int)
//
//  PURPOSE: Entry point for the application
//
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nShowCmd
)
{
    INT iResult         = 0;
    HWND hMenuWnd       = NULL;	
    
	//Check if MenuDemo.exe is running. If it's running then focus on the window
	hMenuWnd = FindWindow(DIALOGWINDOWCLASS, (LPCTSTR)LoadString(hInstance, IDS_MENU_TITLE, NULL, 0));

    if (NULL != hMenuWnd) 
	{
		SetForegroundWindow(hMenuWnd);    
		return iResult;
	}

	// store the hInstance in global
	g_hInst = hInstance;
		
	// create the new dialog box
	iResult = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_MENU_DIALOG), 0,(DLGPROC)DialogProc);

	return iResult;
}

//
//  FUNCTION: DialogProc
//
//  PURPOSE:  Processes mesasges for the main dialog box.
//
BOOL CALLBACK DialogProc(
    const HWND hWnd,
    const UINT Msg, 
    const WPARAM wParam,
    const LPARAM lParam
    ) 
{   
	BOOL bProcessedMsg = TRUE;

    switch (Msg)
    {
        case WM_INITDIALOG:
            if (FALSE == InitDialog(hWnd))
            {
                EndDialog(hWnd, -1);
            }
            break;

        case WM_ACTIVATE:
            if (WA_INACTIVE != LOWORD(wParam)) 
            {
                SetFocus(hWnd);
            }
            break;

        case WM_CLOSE:
			EndDialog(hWnd, 0);
		    break;

        // called before the menu pops up
        case WM_INITMENUPOPUP:
            OnMenuPopup(hWnd, wParam);
            break;

        case WM_COMMAND:
            switch LOWORD(wParam)
            {
                // quit
                case IDM_MENU_QUIT:
			        EndDialog(hWnd, 0);
                    break;

                // "uncheck all" menu option was chosen
                case IDM_MENU_UNCHECK:
                    UncheckAll(hWnd); 
                    break;
                
                // the spinner selection changed
                case IDC_LIST:
                    if (LBN_SELCHANGE == HIWORD(wParam))
                    {
                        ProcessListBox(hWnd);
                    }
                    break;

                // handle the checkboxes
                case IDC_SK_CHECKBOX:
                case IDC_SWAP_CHECKBOX:
                case IDC_QUIT_CHECKBOX:
                    ProcessCheckBox(hWnd, wParam);
                    break;
                    
                // user pressed the Back key... we close the dialog box
                case IDCANCEL:
                    EndDialog(hWnd, 0);
                    break;

                default:
                    bProcessedMsg = FALSE;
            }
            break;

        default:
            bProcessedMsg = FALSE;
    }
    
    return bProcessedMsg;
}

//
//  FUNCTION:   InitDialog
// 
//  PURPOSE:    Initialize the proper settings to create the dialog.
//
BOOL InitDialog(const HWND hWnd)
{
    HWND            hListBox;
    TCHAR           psz[80];
    LRESULT         lResult;

    ZeroMemory(psz, sizeof(psz));

    // initialize dialog box, specifying that it should stretch full screen
    SHINITDLGINFO sid;
	ZeroMemory(&sid, sizeof(sid));
    sid.dwMask  = SHIDIM_FLAGS;
    sid.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
    sid.hDlg    = hWnd;

    // initialize menubar(s)
    // menubar #2
    SHMENUBARINFO mbi;
	ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	mbi.cbSize      = sizeof(SHMENUBARINFO);
	mbi.hwndParent  = hWnd;
	mbi.nToolBarId  = IDR_MENU_MENU2;
	mbi.hInstRes    = g_hInst;

    if (FALSE == SHCreateMenuBar(&mbi))
    {
        return FALSE;
    }
    g_hWndMenuBar2 = mbi.hwndMB;

    // menubar #1
	ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	mbi.cbSize      = sizeof(SHMENUBARINFO);
	mbi.hwndParent  = hWnd;
	mbi.nToolBarId  = IDR_MENU_MENU1;
	mbi.hInstRes    = g_hInst;

    if (FALSE == SHCreateMenuBar(&mbi))
    {
        return FALSE;
    }
    g_hWndMenuBar1 = mbi.hwndMB;
    // --

    // initialize the dialog
	if (FALSE == SHInitDialog(&sid))
    {
	    return FALSE;
	}
    
    // show the first menubar, set the "current" handle
    ShowWindow(g_hWndMenuBar1, SW_HIDE);
    ShowWindow(g_hWndMenuBar2, SW_SHOW);
    g_hWndMenuBarCurrent = g_hWndMenuBar2;

	// set the title bar
	VERIFY(SetWindowText(hWnd, (LPCTSTR)LoadString(g_hInst, IDS_MENU_TITLE, NULL, 0)));

    // set up spinner options, and SK button text
    hListBox = GetDlgItem(hWnd, IDC_LIST);

    // load the "Quit" string into the listbox
    lResult = SendMessage(hListBox, LB_ADDSTRING, 0,
        LoadString(g_hInst, IDS_MENU_QUIT, NULL, 0));

    if (LB_ERR == lResult || LB_ERRSPACE == lResult)
    {
        return FALSE;
    }
        // load the "Uncheck" string
    
    lResult = SendMessage(hListBox, LB_ADDSTRING, 0,
        LoadString(g_hInst, IDS_MENU_UNCHECK, NULL, 0));
    if (LB_ERR == lResult || LB_ERRSPACE == lResult)
    {
        return FALSE;
    }
        // set the initial selection of the listbox
    if (LB_ERR == SendMessage(hListBox, LB_SETCURSEL, 0, 0))
    {
        return FALSE;
    }
    // --

    // set button flags
    g_fChecked_Sk = FALSE;
    g_fChecked_Swap = FALSE;
    g_fChecked_Quit = FALSE;

    g_uiSk_Id1 = IDM_MENU_QUIT;
    g_uiSk_Id2 = IDM_MENU_QUIT;

	return TRUE;
}

//
//  FUNCTION:   OnMenuPopup
//  
//  PURPOSE:    Process necessary changes to menu before it pops up.
//
BOOL OnMenuPopup(
    const HWND hWnd, 
    const WPARAM wParam
    )
{
    if (g_fChecked_Quit)
    {
        EnableMenuItem((HMENU)wParam, IDM_MENU_QUIT, MF_BYCOMMAND | MF_GRAYED);
    }
    else
    {
        EnableMenuItem((HMENU)wParam, IDM_MENU_QUIT, MF_BYCOMMAND | MF_ENABLED);
    }

    return TRUE;
}

//
//  FUNCTION:   ProcessCheckBox
//
//  PURPOSE:    Handle changes in the state of the checkboxes.
//
BOOL ProcessCheckBox(
    const HWND hWnd, 
    const WPARAM wParam
    )
{
    switch LOWORD(wParam)
    {
        // "Disable Softkey"
        case IDC_SK_CHECKBOX:
            if (BN_CLICKED == HIWORD(wParam) && IsWindowEnabled(GetDlgItem(hWnd, IDC_SK_CHECKBOX)))
            {
                if (BST_CHECKED == SendDlgItemMessage(hWnd, IDC_SK_CHECKBOX, BM_GETCHECK, 0, 0))
                    g_fChecked_Sk = TRUE;
                else
                    g_fChecked_Sk = FALSE;
            }
            ProcessSkCheckBox();
            break;

        // "Swap Softkey"
        case IDC_SWAP_CHECKBOX:
            if (BN_CLICKED == HIWORD(wParam) && IsWindowEnabled(GetDlgItem(hWnd, IDC_SWAP_CHECKBOX)))
            {
                if (BST_CHECKED == SendDlgItemMessage(hWnd, IDC_SWAP_CHECKBOX, BM_GETCHECK, 0, 0))
                    g_fChecked_Swap = TRUE;
                else
                    g_fChecked_Swap = FALSE;
            }
            ProcessSwapMenuBar(hWnd);
            break;
        
        // "Disable Options->Quit"
        case IDC_QUIT_CHECKBOX:
            if (BN_CLICKED == HIWORD(wParam) && IsWindowEnabled(GetDlgItem(hWnd, IDC_QUIT_CHECKBOX)))
            {
                if (BST_CHECKED == SendDlgItemMessage(hWnd, IDC_QUIT_CHECKBOX, BM_GETCHECK, 0, 0))
                    g_fChecked_Quit = TRUE;
                else
                    g_fChecked_Quit = FALSE;
            }
            break;
        default:
            break;
    }
    return TRUE;
}

//
//  FUNCTION:   UncheckAll
//
//  PURPOSE:    Unchecks all the checkboxes that have been checked.
//
BOOL UncheckAll(
    const HWND hWnd
    )
{
    // uncheck "Disable SK" 
    if (BST_CHECKED == SendDlgItemMessage(hWnd, IDC_SK_CHECKBOX, BM_GETCHECK, 0, 0))
    {
        SendDlgItemMessage(hWnd, IDC_SK_CHECKBOX, BM_SETCHECK, BST_UNCHECKED, 0);
        g_fChecked_Sk = FALSE;
        ProcessSkCheckBox();
    }

    // uncheck "Swap" 
    if (BST_CHECKED == SendDlgItemMessage(hWnd, IDC_SWAP_CHECKBOX, BM_GETCHECK, 0, 0))
    {
        SendDlgItemMessage(hWnd, IDC_SWAP_CHECKBOX, BM_SETCHECK, BST_UNCHECKED, 0);
        g_fChecked_Swap = FALSE;
        ProcessSwapMenuBar(hWnd);
    }

    // uncheck "Quit" 
    if (BST_CHECKED == SendDlgItemMessage(hWnd, IDC_QUIT_CHECKBOX, BM_GETCHECK, 0, 0))
    {
        SendDlgItemMessage(hWnd, IDC_QUIT_CHECKBOX, BM_SETCHECK, BST_UNCHECKED, 0);
        g_fChecked_Quit = FALSE;
    }
    return TRUE;
}

//
//  FUNCTION:   ProcessSkCheckBox
//
//  PURPOSE:    Handles the enabling/disabling of Sk.
//
BOOL ProcessSkCheckBox()
{
    UINT            uiCurSkId;
    TBBUTTONINFO    buttonInfo;

    ZeroMemory(&buttonInfo, sizeof(TBBUTTONINFO));
    buttonInfo.cbSize   = sizeof(TBBUTTONINFO);
    buttonInfo.dwMask   = TBIF_STATE;

    if (g_hWndMenuBarCurrent == g_hWndMenuBar1)
    {
        uiCurSkId = g_uiSk_Id1;
    }
    else
    {
        uiCurSkId = g_uiSk_Id2;
    }

    if (g_fChecked_Sk)
    {
        buttonInfo.fsState = TBSTATE_INDETERMINATE;
        SendMessage(g_hWndMenuBarCurrent, TB_SETBUTTONINFO, uiCurSkId,(LPARAM)(LPTBBUTTONINFO)&buttonInfo);
    }
    else
    {
        buttonInfo.fsState = TBSTATE_ENABLED;
        SendMessage(g_hWndMenuBarCurrent, TB_SETBUTTONINFO, uiCurSkId,(LPARAM)(LPTBBUTTONINFO)&buttonInfo);
    }
    return TRUE;
}

//
//  FUNCTION:   ProcessListBox
//
//  PURPOSE:    Handles the change in selection of the listbox/spinner.
//
BOOL ProcessListBox(
    const HWND hWnd
    ) 
{
    HWND            hListBox;
    TCHAR           psz[80];
    UINT            uiIndex = 0;
    TBBUTTONINFO    buttonInfo;

    ZeroMemory(&buttonInfo, sizeof(TBBUTTONINFO));
    ZeroMemory(psz, sizeof(psz));

    hListBox = GetDlgItem(hWnd, IDC_LIST);
    uiIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
    SendMessage(hListBox, LB_GETTEXT, uiIndex,(LPARAM)psz);
                        
    buttonInfo.cbSize   = sizeof(TBBUTTONINFO);
    buttonInfo.dwMask   = TBIF_TEXT | TBIF_COMMAND;
    buttonInfo.pszText  = psz;

    if (!_tcscmp(psz, TEXT("Uncheck All")))
    {
        buttonInfo.idCommand = IDM_MENU_UNCHECK;
    }
    else
    {
        buttonInfo.idCommand = IDM_MENU_QUIT;
    }

    //  set the proper menubar's action Softkey
    if (g_hWndMenuBar1 == g_hWndMenuBarCurrent)
    {
        SendMessage(g_hWndMenuBarCurrent, TB_SETBUTTONINFO, g_uiSk_Id1,(LPARAM)(LPTBBUTTONINFO)&buttonInfo);
        g_uiSk_Id1 = buttonInfo.idCommand;
    }
    else
    {
        SendMessage(g_hWndMenuBarCurrent, TB_SETBUTTONINFO, g_uiSk_Id2,(LPARAM)(LPTBBUTTONINFO)&buttonInfo);
        g_uiSk_Id2 = buttonInfo.idCommand;
    }   

    return TRUE;
}

//
//  FUNCTION:   ProcessSwapMenuBar
//
//  PURPOSE:    Called when state of the "Swap" checkbox is changed.  Handles
//              changing the menu bar if necessary.
//
BOOL ProcessSwapMenuBar(
    const HWND hWnd
    )
{
    //  swap the active menu bar
    if (TRUE == g_fChecked_Swap)
    {
        ShowWindow(g_hWndMenuBar2, SW_HIDE);
        ShowWindow(g_hWndMenuBar1, SW_SHOW);
        g_hWndMenuBarCurrent = g_hWndMenuBar1;
    }
    else
    {
        ShowWindow(g_hWndMenuBar1, SW_HIDE);
        ShowWindow(g_hWndMenuBar2, SW_SHOW);
        g_hWndMenuBarCurrent = g_hWndMenuBar2;
    }

    //  relabel and reenable the SK button according to the ListBox selection
    ProcessListBox(hWnd);
    ProcessSkCheckBox();
    return TRUE;
}

// end MenuDemo.cpp
