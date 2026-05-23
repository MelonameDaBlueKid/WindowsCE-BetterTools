///////////////////////////////////////////////////////////////////////////////
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  This is "Sample Code" and is distributable subject to the terms of the 
//  end user license agreement.
///////////////////////////////////////////////////////////////////////////////
//
// REGDEMO.CPP
//
// Sample Program that demonstrates how to get and set registry values
//

#include <windows.h>
#include <aygshell.h>
#include "regdemo.h"
#include "resource.h"

/*===========================================================================
 * Macro Definitions
*/

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))


/*===========================================================================
 * Function Prototypes 
*/

BOOL CALLBACK DialogProc(
    const HWND hWndDlg, 
    const UINT Msg, 
    const WPARAM wParam,
    const LPARAM lParam
    );
static LPCTSTR StringFromResources(
    UINT uStringID
    );
static BOOL InitWindow(
    const HWND hWndDlg, 
    UINT nToolBarId
    );
static BOOL GetString1(
    HWND hWndDlg
    );
static BOOL GetDWORD1(
    HWND hWndDlg
    );


/*===========================================================================
 * Global Variables
*/

HINSTANCE   g_hInst = NULL;
HKEY        g_hkResult = NULL;


int WINAPI WinMain
(
    HINSTANCE hInstance,
    HINSTANCE hPreviousInstance,
    LPWSTR lpCmdLine,
    int nShowCmd
)
{
    int iResult;

    // Store the application instance in our global variable.
    g_hInst = hInstance;

    // Use a globally named mutex to detect another instance of RegDemo
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_REGDEMO_EXE_MUTEX_"));

    // check the result code
    if (0 != hMutex) 
    {
        // No other instances running? Okay to proceed...
        if (ERROR_ALREADY_EXISTS != GetLastError()) 
        {
            InitCommonControls();
            iResult = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1),
                0, (DLGPROC)DialogProc);

            if (iResult < 0) 
            {
                MessageBox(NULL, StringFromResources(IDS_DIALOG_ERROR),
                    StringFromResources(IDS_ERROR_TITLE), MB_OK | MB_ICONERROR);
            }
        }
        else 
        {
            // Already an instance running - attempt to switch to it and then exit
            LPCTSTR pszTitle = StringFromResources(IDS_REGDEMO_TITLE);
            const HWND hwndExistingInstance = FindWindow(TEXT("Dialog"), pszTitle);
            if (hwndExistingInstance != NULL) 
            {
                SetForegroundWindow((HWND)(((ULONG)hwndExistingInstance) | 0x1));
            }
        }
        VERIFY(CloseHandle(hMutex));
    }

    return TRUE;
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


BOOL CALLBACK DialogProc(
    const HWND hWndDlg, 
    const UINT Msg, 
    const WPARAM wParam, 
    const LPARAM lParam
)
{
    BOOL    bProcessedMsg = TRUE;
    DWORD   dwDisposition;
    DWORD   dwDWORD1;
    int     iResult;
    int     iLength;
    LPTSTR  lpszString1;
    HWND    hwndStr;

    switch(Msg)
    {
        case WM_INITDIALOG:
            if (FALSE == InitWindow(hWndDlg, IDR_REGDEMO_MAINMENU)) 
            {
                EndDialog(hWndDlg, -1);
            }

            // try to open the registry key
            if (RegCreateKeyEx(REGISTRY_ROOT, REGISTRY_KEY, (DWORD) 0, TEXT(""), 
                    (DWORD) 0, (REGSAM) 0, (LPSECURITY_ATTRIBUTES) NULL, 
                    &g_hkResult, &dwDisposition) != ERROR_SUCCESS) 
            {
                MessageBox(NULL, StringFromResources(IDS_REGCREATEKEYEX_FAILED), 
                    StringFromResources(IDS_ERROR_TITLE), MB_OK);
                EndDialog(hWndDlg, -1);
            }

            // get the keys, if they exist
            if (REG_OPENED_EXISTING_KEY == dwDisposition) 
            {
                // try to set the DWORD
                if (FALSE == GetDWORD1(hWndDlg)) 
                {
                    MessageBox(NULL, StringFromResources(IDS_GETDWORD1_FAILED), 
                        StringFromResources(IDS_ERROR_TITLE), MB_OK);
                    RegCloseKey(g_hkResult);
                    EndDialog(hWndDlg, -1);
                }

                // try to set the String
                if (FALSE == GetString1(hWndDlg)) 
                {
                    MessageBox(NULL, StringFromResources(IDS_GETSTRING1_FAILED), 
                        StringFromResources(IDS_ERROR_TITLE), MB_OK);
                    RegCloseKey(g_hkResult);
                    EndDialog(hWndDlg, -1);
                }
            }
            break;

        case WM_COMMAND:
            switch (wParam) 
            {
                case IDM_REGDEMO_UPDATE:
                    // Update the DWORD1 value
                    dwDWORD1 = GetDlgItemInt(hWndDlg, IDC_REGDEMO_DWORD1, NULL, FALSE);
                    iResult = RegSetValueEx(g_hkResult, REGISTRY_VALUE_DWORD1, (DWORD) 0,
                        REG_DWORD, (PBYTE) &dwDWORD1, sizeof(DWORD));

                    // Update the String1 value
                    hwndStr = GetDlgItem(hWndDlg, IDC_REGDEMO_STRING1);
					VERIFY(hwndStr != NULL);
                    iLength = GetWindowTextLength(hwndStr) + 1;
					lpszString1 = (LPTSTR) malloc(iLength * sizeof(TCHAR));
                    if (lpszString1 == NULL) 
					{
                        MessageBox(NULL, StringFromResources(IDS_MALLOC_FAILED), 
                            StringFromResources(IDS_ERROR_TITLE), MB_OK);
                        RegCloseKey(g_hkResult);
                        EndDialog(hWndDlg, 0);
                    }

                    GetDlgItemText(hWndDlg, IDC_REGDEMO_STRING1, lpszString1, iLength);
                    iResult = RegSetValueEx(g_hkResult, REGISTRY_VALUE_STRING1, (DWORD) 0,
						REG_SZ, (PBYTE) lpszString1, iLength * sizeof(TCHAR));
                    break;

                case IDM_REGDEMO_REMOVE:
                    iResult = RegDeleteValue(g_hkResult, REGISTRY_VALUE_DWORD1);
                    // show the error message box only if we get an error other than SUCCESS or
					// FILE_NOT_FOUND, which are to be expected.
					if (!((iResult == ERROR_SUCCESS) || 
                        (iResult == ERROR_FILE_NOT_FOUND))) 
					{
                        MessageBox(NULL, StringFromResources(IDS_REGDELETEVALUE_FAILED), 
                                   StringFromResources(IDS_ERROR_TITLE), MB_OK);
                        RegCloseKey(g_hkResult);
                        EndDialog(hWndDlg, 0);
                    }
                    
                    iResult = RegDeleteValue(g_hkResult, REGISTRY_VALUE_STRING1);
                    // show the error message box only if we get an error other than SUCCESS or
					// FILE_NOT_FOUND, which are to be expected.
					if (!((iResult == ERROR_SUCCESS) || 
                        (iResult == ERROR_FILE_NOT_FOUND))) 
					{
                        MessageBox(NULL, StringFromResources(IDS_REGDELETEVALUE_FAILED), 
                                   StringFromResources(IDS_ERROR_TITLE), MB_OK);
                        RegCloseKey(g_hkResult);
                        EndDialog(hWndDlg, 0);
                    }

                    // set the keys back to the default values
                    VERIFY(SetDlgItemInt(hWndDlg, IDC_REGDEMO_DWORD1, 0, 0));
                    VERIFY(SetDlgItemText(hWndDlg, IDC_REGDEMO_STRING1, TEXT("")));
                    break;
            
                case IDM_REGDEMO_QUIT:
                    RegCloseKey(g_hkResult);
                    EndDialog(hWndDlg, 0);
                    break;

                default:
                    bProcessedMsg = FALSE;
                    break;
            }
        
        default:
            bProcessedMsg = FALSE;
            break;
    }

    return bProcessedMsg;
}

static BOOL InitWindow(
    const HWND hWndDlg, 
    UINT nToolBarId
    )
{
    // Specify that the dialog box should stretch full screen
    SHINITDLGINFO shidi;
    ZeroMemory(&shidi, sizeof(shidi));
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
    shidi.hDlg = hWndDlg;

    // set up Soft Keys menu
    SHMENUBARINFO mbi;
    ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
    mbi.cbSize = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hWndDlg;
    mbi.nToolBarId = nToolBarId;
    mbi.hInstRes = g_hInst;

    // If we could not initialize the dialog box, return an error
    if ((FALSE == SHInitDialog(&shidi)) || (FALSE == SHCreateMenuBar(&mbi))) 
	{
        return FALSE;
    }

    // set the title bar
    VERIFY(SetWindowText(hWndDlg, StringFromResources(IDS_REGDEMO_TITLE)));

    // In order to make Back work properly, it's necessary to 
    // override it and then4 call the appropriate SH API
    (void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
		MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
			SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

    return TRUE;
}

static BOOL GetDWORD1(
    HWND hWndDlg
    )
{
    int     iResult;
    DWORD   dwDWORD1, dwSize = sizeof(DWORD);
    
    // sanity check
    VERIFY(g_hkResult);

    // get DWORD1
	iResult = RegQueryValueEx(g_hkResult, REGISTRY_VALUE_DWORD1, 
		(LPDWORD) NULL, (LPDWORD) NULL, (PBYTE) &dwDWORD1, &dwSize);

    if (ERROR_SUCCESS != iResult) 
	{
        // check iResult to make sure it was just a file not found
        if (ERROR_FILE_NOT_FOUND != iResult) 
		{
            return FALSE;
        }

        // set the value to be 0
        VERIFY(SetDlgItemInt(hWndDlg, IDC_REGDEMO_DWORD1, 0, 0));
    } 
	else 
	{
        // set the value in the edit box
        VERIFY(SetDlgItemInt(hWndDlg, IDC_REGDEMO_DWORD1, dwDWORD1, 0));
    }

    return TRUE;
}

static BOOL GetString1(
    HWND hWndDlg
    )
{
    int     iResult;
    DWORD   dwSize;
    LPTSTR  lpszString1;

    // get STRING1 - but first get the length
    dwSize = 0;
	iResult = RegQueryValueEx(g_hkResult, REGISTRY_VALUE_STRING1, 
		(LPDWORD) NULL, (LPDWORD) NULL, (PBYTE) NULL, &dwSize);
    if (ERROR_SUCCESS != iResult) 
	{
        // check iResult to make sure it was just an invalid parameter
        if (ERROR_FILE_NOT_FOUND != iResult) 
		{
            return FALSE;
        }

        // set the string to the default value
        VERIFY(SetDlgItemText(hWndDlg, IDC_REGDEMO_STRING1, TEXT("")));
    } 
	else 
	{
        // now that we have the length, get the string
        VERIFY(dwSize != 0);
		lpszString1 = (LPTSTR) malloc(dwSize * sizeof(TCHAR));
        if (lpszString1 == NULL) 
		{
            return FALSE;
        }

		iResult = RegQueryValueEx(g_hkResult, REGISTRY_VALUE_STRING1, 
			(LPDWORD) NULL, (LPDWORD) NULL, (PBYTE) lpszString1, &dwSize);
        if (iResult != ERROR_SUCCESS) 
		{
            free(lpszString1);
            return FALSE;
        } 
		else 
		{
            VERIFY(SetDlgItemText(hWndDlg, IDC_REGDEMO_STRING1, lpszString1));
            free(lpszString1);
        }
    }

    return TRUE;
}

/* EOF */
