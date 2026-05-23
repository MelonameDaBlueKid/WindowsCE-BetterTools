///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////
//
// WMHIBERNATE.CPP
//
// Mallocs memory until the system sends a WM_HIBERNATE message
//

#include <windows.h>
#include <winuserm.h>
#include <aygshell.h>
#include "resource.h"
#include "newres.h"

#define BUFSIZE			32
#define MALLOC_SIZE		131072
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

// Global variables
HINSTANCE	g_hInstance;
int			g_iTotalMalloc;

// Function Declarations
BOOL InitDialog(const HWND hDlg);
BOOL CALLBACK DialogProc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPTSTR lpCmdLine, int nShowCmd)
{
	// result code from dialog box
	int iResult = 0;

    // Use a globally named mutex to detect another instance of HelloSMS
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_WMHIBERNATE_EXE_MUTEX_"));

    // check the result code
	if(0 != hMutex) {
        // First instance running?  Okay to proceed...
		if(ERROR_ALREADY_EXISTS != GetLastError()) {
			// store the hInstance
			g_hInstance = hInstance;

			// create the dialog box
			iResult = DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DialogProc);
        }
        else {
            // Already an instance running - attempt to switch to it and then exit
            const HWND hWndExistingInstance = FindWindow(TEXT("Dialog"), TEXT("WMHibernate"));
			VERIFY((0 == hWndExistingInstance) || SetForegroundWindow(hWndExistingInstance));
        }
        VERIFY(CloseHandle(hMutex));
    }

	return 0;
}

BOOL CALLBACK DialogProc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam)
{
	BOOL	bProcessedMsg = TRUE;
	TCHAR	szTotalMalloc[BUFSIZE];
	
	switch(uiMessage)
	{
		case WM_INITDIALOG:
			// make sure the dialog box was created
			if (!InitDialog(hDlg)) {
				// return an error
				EndDialog(hDlg, -1);
			}
			break;

        case WM_COMMAND:
			switch(wParam) {
				case IDM_WMH_QUIT:
					EndDialog(hDlg, 0);
					break;
				case IDM_WMH_MALLOC:
					// try to malloc more memory
					if (!malloc(MALLOC_SIZE)) {
						MessageBox(NULL, TEXT("Unable to malloc memory"),
								   TEXT("Error!!!"), MB_OK | MB_ICONERROR);
					} else {
						// update the total counter and change the label
						g_iTotalMalloc += MALLOC_SIZE;

						_sntprintf(szTotalMalloc, ARRAY_LENGTH(szTotalMalloc),
								   TEXT("%d bytes"), g_iTotalMalloc);

						VERIFY(SetDlgItemText(hDlg, IDC_WMH_LBLTOTAL, szTotalMalloc));
					}
			}
			break;

		case WM_HOTKEY:
            // The following is necessary to get the appropriate Back key behavior 
			// (handle on key-up as per recommendations)
            if((VK_TBACK == HIWORD(lParam)) && (0 != (MOD_KEYUP & LOWORD(lParam)))) {
                // BUGBUG - might have to change
				SHNavigateBack();
            }
            break;

		case WM_HIBERNATE:
			MessageBox(NULL, TEXT("Received WM_HIBERNATE.  Closing."),
					   TEXT("Low Memory"), MB_OK);
			EndDialog(hDlg, 0);
			break;

		default:
			// nothing was processed
			bProcessedMsg = false;
			break;
	}

	return bProcessedMsg;
}

BOOL InitDialog(const HWND hDlg)
{
    // Specify that the dialog box should stretch full screen
	SHINITDLGINFO shidi;
	ZeroMemory(&shidi, sizeof(shidi));
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
    shidi.hDlg = hDlg;
    
	// Set up the menu bar
	SHMENUBARINFO shmbi;
	ZeroMemory(&shmbi, sizeof(shmbi));
    shmbi.cbSize = sizeof(shmbi);
    shmbi.hwndParent = hDlg;
    shmbi.nToolBarId = IDR_WMH_MENUBAR;
    shmbi.hInstRes = g_hInstance;

	// If we could not initialize the dialog box, return an error
	if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
		return FALSE;
	}

	// set the title bar
	VERIFY(SetWindowText(hDlg, TEXT("WMHibernate")));

	// set the global
	g_iTotalMalloc = 0;

    // In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
    (void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
					  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
								 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
}