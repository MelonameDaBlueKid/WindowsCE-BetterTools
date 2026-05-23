// shell.cpp : Defines the entry point for the application.
//

#include "stdafx.h"


//////////////////////////////////////
// Global Variables Set in this file
//////////////////////////////////////
static BOOL g_fHibernated = FALSE;

//////////////////////////////////////
// Foward declarations of functions included in this code module:
//////////////////////////////////////
static BOOL HandleSIPChange();
static BOOL HandleCommand(HWND hwnd, WPARAM wp, LPARAM lp);
static BOOL HandleNotify(HWND hwnd, WPARAM wp, LPARAM lp);
static void HandlePaint(HWND hwnd, BOOL fForce);


//////////////////////////////////////
// Functions Segment
//////////////////////////////////////

//
//  FUNCTION: HandleCommand(HWND, WPARAM, LPARAN)
//
//  PURPOSE:  Processes WM_COMMAND messages for the main window.
//
//  TOOLBAR messages
//
//
BOOL HandleCommand(HWND hwnd, WPARAM wp, LPARAM lp)
{
INT		iCurSel = 0;
TCHAR	szName[100];

	switch(LOWORD(wp))
	{
		case IDM_FILEEXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
			
		case IDM_FILENEW:
			wsprintf(g_szHello, TEXT("File New Pressed"));
			g_szFile = NULL;
			EnablePropertyItem();
			break;

		case IDM_FILEOPEN:
			wsprintf(g_szHello, TEXT("File Open Pressed"));
			FileOpenSave(FOS_OPEN);
			break;
		
		case IDM_FILESAVE:
			wsprintf(g_szHello, TEXT("File Save Pressed"));
			break;

		case IDM_FILESAVEAS:
			FileOpenSave(FOS_SAVE);
			wsprintf(g_szHello, TEXT("File Save As Pressed"));
			break;
		
		case IDM_FILECLOSE:
			wsprintf(g_szHello, TEXT("File Close Pressed"));
			SendMessage(g_hwndMain, WM_CLOSE, 0, 0);
			break;
		
		case IDM_FILEFOLDERS:
			wsprintf(g_szHello, TEXT("File Folders Pressed"));
			FileFolder();
			break;
		
		case IDM_FILEPROPERTIES:
			wsprintf(g_szHello, TEXT("File Properties Pressed"));
			FileOpenSave(FOS_PROPERTIES);
			break;
		
		case IDM_EDITUNDO:
			wsprintf(g_szHello, TEXT("Edit Undo Pressed"));
			break;

		case IDM_EDITREDO:
			wsprintf(g_szHello, TEXT("Edit Redo Pressed"));
			break;

		case IDM_EDITCUT:
			wsprintf(g_szHello, TEXT("Edit Cut Pressed"));
			break;

		case IDM_EDITCOPY:
			wsprintf(g_szHello, TEXT("Edit Copy Pressed"));
			break;

		case IDM_EDITPASTE:
			wsprintf(g_szHello, TEXT("Edit Paste Pressed"));
			break;

		case IDM_EDITSELECTALL:
			wsprintf(g_szHello, TEXT("Edit Select All Pressed"));
			break;
		
		case IDM_COMBO:
			if (SendMessage((HWND) lp, CB_GETDROPPEDSTATE, iCurSel, (LPARAM) szName))
			{
				iCurSel = SendMessage((HWND) lp, CB_GETCURSEL, 0, 0);
				SendMessage((HWND) lp, CB_GETLBTEXT, iCurSel, (LPARAM) szName);
				wsprintf(g_szHello, TEXT("Combo Choice Made %s"), szName);
				SetFocus(g_hwndMain);
			}
			else
			{
				wsprintf(g_szHello, TEXT("Combo Choice Dropped"));
			}

			break;

		default:
			wsprintf(g_szHello, TEXT("Unknown message: %d Received"), LOWORD(wp));
			return FALSE;
	}

	return TRUE;
}


//
//  FUNCTION: HandleSIPChange()
//
//  PURPOSE:  Processes WM_SETTINGCHANGE messages from the SIP
//
//  Comment	  SIP change messages and WM_ACTIVATE messages end up calling this
//
//
BOOL HandleSIPChange()
{
	SHACTIVATEINFO sai;
	memset(&sai, 0, sizeof(SHACTIVATEINFO));

	//This will force a HWND resize depending on the SIP condition	
	SHHandleWMSettingChange(g_hwndMain, -1, 0, &sai);
	
	return TRUE;
}
	
//
//  FUNCTION: HandleHibernate()
//
//  PURPOSE:  Processes WM_HIBERNATE messages by freeing up memory
//
//  Comments need to release any memory possible at this point
//
//
void HandleHibernate()
{

	g_fHibernated = TRUE;
}

//
//  FUNCTION: HandleActivate()
//
//  PURPOSE:  Processes WM_ACTIVATE messages which are bringing the application back 
//
//  Comments need to set Focus and thaw hibernated items
//
//
void HandleActivate()
{
	// assume that the SIP has been changed
	HandleSIPChange();

	// set focus to foremost child window
	SetForegroundWindow((HWND)((ULONG) g_hwndMain | 0x00000001));  //Internal hack to ensure all 
	
	//if (g_fHibernated) {
	// restore anything that was hibernated
	//}
}


//
//  FUNCTION: HandlePaint(HWND, BOOL)
//
//  PURPOSE:  Processes WM_PAINT messages and paints the window on demand
//
//  Comments 
//
//
void HandlePaint(HWND hwnd, BOOL fForce)
{
	PAINTSTRUCT ps;
	HDC			hdc;
	RECT		rc;
	
	GetClientRect(hwnd, &rc);
	if (fForce) {
		InvalidateRect(hwnd, &rc, TRUE);
	}
	
	hdc = BeginPaint(hwnd, &ps);
	// TODO: Add any drawing code here...
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	InflateRect(&rc, -2, -2);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	InflateRect(&rc, -2, -2);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	InflateRect(&rc, -2, -2);

	// If line is longer than 32 characters then truncate in the middle of the string
	// and insert ...
	if (wcslen(g_szHello) > 32){
		TCHAR szTemp[256];

		wcsncpy(szTemp, g_szHello, 16);
		wcscat(szTemp, _T("..."));

		wcscat(szTemp, g_szHello + wcslen(g_szHello) - 16);
		wcscpy(g_szHello, szTemp);
		}


	DrawText(hdc, g_szHello, wcslen(g_szHello), &rc, (DT_CENTER | DT_VCENTER | DT_WORDBREAK));
		
	EndPaint(hwnd, &ps);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message) 
	{
		case WM_PAINT:
			HandlePaint(hwnd, FALSE);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		case WM_HIBERNATE:
			HandleHibernate();
			break;
		
		case WM_CLOSE:
			HandleHibernate();
			if (g_szFile)
				free (g_szFile);
			return DefWindowProc(hwnd, message, wParam, lParam);
			
		case WM_SETTINGCHANGE:           
			switch(wParam) {
				
			case SPI_SETSIPINFO:			// SIP up or down
				HandleSIPChange();
				break;
				
			case SPI_APPBUTTONCHANGE:		// Hotkey alterations
				//HandleAppButtonChange();
				break;
				
			default:
				return FALSE;
			}
			break;
			
			case WM_COMMAND:
				HandleCommand(hwnd, wParam, lParam);
				HandlePaint(hwnd, TRUE);
				break;
				
			case WM_ACTIVATE:
				switch (LOWORD(wParam)) {
				case WA_INACTIVE:
					return DefWindowProc(hwnd, message, wParam, lParam);
					
				case WA_ACTIVE:
				case WA_CLICKACTIVE:
					HandleActivate();
					break;
				}
				break;
				
				default:
					return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
	MSG		msg;
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
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

