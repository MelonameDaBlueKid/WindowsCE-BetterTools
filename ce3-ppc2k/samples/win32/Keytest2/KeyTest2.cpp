/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
//
// keytest2.cpp : Defines the entry point for the application
//
#include "stdafx.h"

//
// globals
//
BOOL g_bHaveButtons = FALSE;

//
// GetKeyName
//   this is just a look up function for all the possible VK codes
//
void GetKeyName(WPARAM wParam, PTSTR szOut)
{
	switch (wParam)
	{
	case VK_LBUTTON:
		wsprintf(szOut, TEXT("VK_LBUTTON"));
		break;
	case VK_RBUTTON:
		wsprintf(szOut, TEXT("VK_RBUTTON"));
		break;
	case VK_CANCEL :
		wsprintf(szOut, TEXT("VK_CANCEL"));
		break;
	case VK_MBUTTON:
		wsprintf(szOut, TEXT("VK_MBUTTON"));
		break;
	case VK_KANA		:
		wsprintf(szOut, TEXT("VK_KANA"));
		break;
	case VK_KANJI	:
		wsprintf(szOut, TEXT("VK_KANJI	"));
		break;
	case VK_CONVERT	 :
		wsprintf(szOut, TEXT("VK_CONVERT"));
		break;
	case VK_NOCONVERT	:
		wsprintf(szOut, TEXT("VK_NOCONVERT"));
		break;
		//case VK_EXTEND_BSLASH:
	case VK_OEM_102:
		wsprintf(szOut, TEXT("VK_EXTEND_BSLASH"));
		break;
	case VK_ADD:
		wsprintf(szOut, TEXT("VK_ADD"));
		break;
	case VK_APOSTROPHE		:
		wsprintf(szOut, TEXT("VK_APOSTROPHE"));
		break;
	case VK_APPS :
		wsprintf(szOut, TEXT("VK_APPS"));
		break;
	case VK_ATTN :
		wsprintf(szOut, TEXT("VK_ATTN"));
		break;
	case VK_BACK :
		wsprintf(szOut, TEXT("VK_BACK"));
		break;
	case VK_BACKQUOTE		:
		wsprintf(szOut, TEXT("VK_BACKQUOTE"));
		break;
	case VK_BACKSLASH		:
		wsprintf(szOut, TEXT("VK_BACKSLASH"));
		break;
	case VK_CAPITAL:
		wsprintf(szOut, TEXT("VK_CAPITAL"));
		break;
	case VK_CLEAR:
		wsprintf(szOut, TEXT("VK_CLEAR"));
		break;
	case VK_COMMA			:
		wsprintf(szOut, TEXT("VK_COMMA"));
		break;
	case VK_CONTROL:
		wsprintf(szOut, TEXT("VK_CONTROL"));
		break;
	case VK_CRSEL:
		wsprintf(szOut, TEXT("VK_CRSEL"));
		break;
		// some VK codes are repeated.
#if 0
	case VK_DBE_ALPHANUMERIC:
		wsprintf(szOut, TEXT("VK_DBE_ALPHANUMERIC"));
		break;
	case VK_DBE_CODEINPUT :
		wsprintf(szOut, TEXT("VK_DBE_CODEINPUT"));
		break;
	case VK_DBE_DBCSCHAR:
		wsprintf(szOut, TEXT("VK_DBE_DBCSCHAR"));
		break;
	case VK_DBE_DETERMINESTRING :
		wsprintf(szOut, TEXT("VK_DBE_DETERMINESTRING"));
		break;
	case VK_DBE_ENTERDLGCONVERSIONMODE:
		wsprintf(szOut, TEXT("VK_DBE_ENTERDLGCONVERSIONMODE"));
		break;
	case VK_DBE_ENTERIMECONFIGMODE:
		wsprintf(szOut, TEXT("VK_DBE_ENTERIMECONFIGMODE"));
		break;
	case VK_DBE_ENTERWORDREGISTERMODE :
		wsprintf(szOut, TEXT("VK_DBE_ENTERWORDREGISTERMODE"));
		break;
	case VK_DBE_FLUSHSTRING :
		wsprintf(szOut, TEXT("VK_DBE_FLUSHSTRING"));
		break;
	case VK_DBE_HIRAGANA:
		wsprintf(szOut, TEXT("VK_DBE_HIRAGANA"));
		break;
	case VK_DBE_KATAKANA:
		wsprintf(szOut, TEXT("VK_DBE_KATAKANA"));
		break;
	case VK_DBE_NOCODEINPUT :
		wsprintf(szOut, TEXT("VK_DBE_NOCODEINPUT"));
		break;
	case VK_DBE_NOROMAN :
		wsprintf(szOut, TEXT("VK_DBE_NOROMAN"));
		break;
	case VK_DBE_ROMAN :
		wsprintf(szOut, TEXT("VK_DBE_ROMAN"));
		break;
	case VK_DBE_SBCSCHAR:
		wsprintf(szOut, TEXT("VK_DBE_SBCSCHAR"));
		break;
#endif
	case VK_DECIMAL:
		wsprintf(szOut, TEXT("VK_DECIMAL"));
		break;
	case VK_DELETE :
		wsprintf(szOut, TEXT("VK_DELETE"));
		break;
	case VK_DIVIDE :
		wsprintf(szOut, TEXT("VK_DIVIDE"));
		break;
	case VK_DOWN :
		wsprintf(szOut, TEXT("VK_DOWN"));
		break;
	case VK_END:
		wsprintf(szOut, TEXT("VK_END"));
		break;
	case VK_EQUAL			:
		wsprintf(szOut, TEXT("VK_EQUAL"));
		break;
	case VK_EREOF:
		wsprintf(szOut, TEXT("VK_EREOF"));
		break;
	case VK_ESCAPE :
		wsprintf(szOut, TEXT("VK_ESCAPE"));
		break;
	case VK_EXECUTE:
		wsprintf(szOut, TEXT("VK_EXECUTE"));
		break;
	case VK_EXSEL:
		wsprintf(szOut, TEXT("VK_EXSEL"));
		break;
	case VK_F1 :
		wsprintf(szOut, TEXT("VK_F1"));
		break;
	case VK_F10:
		wsprintf(szOut, TEXT("VK_F10"));
		break;
	case VK_F11:
		wsprintf(szOut, TEXT("VK_F11"));
		break;
	case VK_F12:
		wsprintf(szOut, TEXT("VK_F12"));
		break;
	case VK_F13:
		wsprintf(szOut, TEXT("VK_F13"));
		break;
	case VK_F14:
		wsprintf(szOut, TEXT("VK_F14"));
		break;
	case VK_F15:
		wsprintf(szOut, TEXT("VK_F15"));
		break;
	case VK_F16:
		wsprintf(szOut, TEXT("VK_F16"));
		break;
	case VK_F17:
		wsprintf(szOut, TEXT("VK_F17"));
		break;
	case VK_F18:
		wsprintf(szOut, TEXT("VK_F18"));
		break;
	case VK_F19:
		wsprintf(szOut, TEXT("VK_F19"));
		break;
	case VK_F2 :
		wsprintf(szOut, TEXT("VK_F2"));
		break;
	case VK_F20:
		wsprintf(szOut, TEXT("VK_F20"));
		break;
	case VK_F21:
		wsprintf(szOut, TEXT("VK_F21"));
		break;
	case VK_F22:
		wsprintf(szOut, TEXT("VK_F22"));
		break;
	case VK_F23:
		wsprintf(szOut, TEXT("VK_F23"));
		break;
	case VK_F24:
		wsprintf(szOut, TEXT("VK_F24"));
		break;
	case VK_F3 :
		wsprintf(szOut, TEXT("VK_F3"));
		break;
	case VK_F4 :
		wsprintf(szOut, TEXT("VK_F4"));
		break;
	case VK_F5 :
		wsprintf(szOut, TEXT("VK_F5"));
		break;
	case VK_F6 :
		wsprintf(szOut, TEXT("VK_F6"));
		break;
	case VK_F7 :
		wsprintf(szOut, TEXT("VK_F7"));
		break;
	case VK_F8 :
		wsprintf(szOut, TEXT("VK_F8"));
		break;
	case VK_F9 :
		wsprintf(szOut, TEXT("VK_F9"));
		break;
	case VK_HELP :
		wsprintf(szOut, TEXT("VK_HELP"));
		break;
	case VK_HOME :
		wsprintf(szOut, TEXT("VK_HOME"));
		break;
	case VK_HYPHEN			:
		wsprintf(szOut, TEXT("VK_HYPHEN"));
		break;
	case VK_INSERT :
		wsprintf(szOut, TEXT("VK_INSERT"));
		break;
	case VK_LBRACKET			:
		wsprintf(szOut, TEXT("VK_LBRACKET"));
		break;
	case VK_LCONTROL :
		wsprintf(szOut, TEXT("VK_LCONTROL"));
		break;
	case VK_LEFT :
		wsprintf(szOut, TEXT("VK_LEFT"));
		break;
	case VK_LMENU:
		wsprintf(szOut, TEXT("VK_LMENU"));
		break;
	case VK_LSHIFT :
		wsprintf(szOut, TEXT("VK_LSHIFT"));
		break;
	case VK_LWIN :
		wsprintf(szOut, TEXT("VK_LWIN"));
		break;
	case VK_MENU :
		wsprintf(szOut, TEXT("VK_MENU"));
		break;
	case VK_MULTIPLY :
		wsprintf(szOut, TEXT("VK_MULTIPLY"));
		break;
	case VK_NEXT :
		wsprintf(szOut, TEXT("VK_NEXT"));
		break;
	case VK_NONAME :
		wsprintf(szOut, TEXT("VK_NONAME"));
		break;
	case VK_NUMLOCK:
		wsprintf(szOut, TEXT("VK_NUMLOCK"));
		break;
	case VK_NUMPAD0:
		wsprintf(szOut, TEXT("VK_NUMPAD0"));
		break;
	case VK_NUMPAD1:
		wsprintf(szOut, TEXT("VK_NUMPAD1"));
		break;
	case VK_NUMPAD2:
		wsprintf(szOut, TEXT("VK_NUMPAD2"));
		break;
	case VK_NUMPAD3:
		wsprintf(szOut, TEXT("VK_NUMPAD3"));
		break;
	case VK_NUMPAD4:
		wsprintf(szOut, TEXT("VK_NUMPAD4"));
		break;
	case VK_NUMPAD5:
		wsprintf(szOut, TEXT("VK_NUMPAD5"));
		break;
	case VK_NUMPAD6:
		wsprintf(szOut, TEXT("VK_NUMPAD6"));
		break;
	case VK_NUMPAD7:
		wsprintf(szOut, TEXT("VK_NUMPAD7"));
		break;
	case VK_NUMPAD8:
		wsprintf(szOut, TEXT("VK_NUMPAD8"));
		break;
	case VK_NUMPAD9:
		wsprintf(szOut, TEXT("VK_NUMPAD9"));
		break;
	case VK_OEM_CLEAR:
		wsprintf(szOut, TEXT("VK_OEM_CLEAR"));
		break;
	case VK_OFF:
		wsprintf(szOut, TEXT("VK_OFF"));
		break;
	case VK_PA1:
		wsprintf(szOut, TEXT("VK_PA1"));
		break;
	case VK_PAUSE:
		wsprintf(szOut, TEXT("VK_PAUSE"));
		break;
	case VK_PERIOD			:
		wsprintf(szOut, TEXT("VK_PERIOD"));
		break;
	case VK_PLAY :
		wsprintf(szOut, TEXT("VK_PLAY"));
		break;
	case VK_PRINT:
		wsprintf(szOut, TEXT("VK_PRINT"));
		break;
	case VK_PRIOR:
		wsprintf(szOut, TEXT("VK_PRIOR"));
		break;
	case VK_PROCESSKEY :
		wsprintf(szOut, TEXT("VK_PROCESSKEY"));
		break;
	case VK_RBRACKET			:
		wsprintf(szOut, TEXT("VK_RBRACKET	"));
		break;
	case VK_RCONTROL :
		wsprintf(szOut, TEXT("VK_RCONTROL"));
		break;
	case VK_RETURN :
		wsprintf(szOut, TEXT("VK_RETURN"));
		break;
	case VK_RIGHT:
		wsprintf(szOut, TEXT("VK_RIGHT"));
		break;
	case VK_RMENU:
		wsprintf(szOut, TEXT("VK_RMENU"));
		break;
	case VK_RSHIFT :
		wsprintf(szOut, TEXT("VK_RSHIFT"));
		break;
	case VK_RWIN :
		wsprintf(szOut, TEXT("VK_RWIN"));
		break;
	case VK_SCROLL :
		wsprintf(szOut, TEXT("VK_SCROLL"));
		break;
	case VK_SELECT :
		wsprintf(szOut, TEXT("VK_SELECT"));
		break;
	case VK_SEMICOLON		:
		wsprintf(szOut, TEXT("VK_SEMICOLON"));
		break;
	case VK_SEPARATOR:
		wsprintf(szOut, TEXT("VK_SEPARATOR"));
		break;
	case VK_SHIFT:
		wsprintf(szOut, TEXT("VK_SHIFT"));
		break;
	case VK_SLASH			:
		wsprintf(szOut, TEXT("VK_SLASH"));
		break;
	case VK_SNAPSHOT :
		wsprintf(szOut, TEXT("VK_SNAPSHOT"));
		break;
	case VK_SPACE:
		wsprintf(szOut, TEXT("VK_SPACE"));
		break;
	case VK_SUBTRACT :
		wsprintf(szOut, TEXT("VK_SUBTRACT"));
		break;
	case VK_TAB:
		wsprintf(szOut, TEXT("VK_TAB"));
		break;
	case VK_UP :
		wsprintf(szOut, TEXT("VK_UP"));
		break;
	case VK_ZOOM :
		wsprintf(szOut, TEXT("VK_ZOOM"));
		break;
	case VK_APP_LAUNCH1 :
		wsprintf(szOut, TEXT("APP_LAUNCH1"));
		break;
	case VK_APP_LAUNCH2 :
		wsprintf(szOut, TEXT("APP_LAUNCH2"));
		break;
	case VK_APP_LAUNCH3 :
		wsprintf(szOut, TEXT("APP_LAUNCH3"));
		break;
	case VK_APP_LAUNCH4 :
		wsprintf(szOut, TEXT("APP_LAUNCH4"));
		break;
	case VK_APP_LAUNCH5 :
		wsprintf(szOut, TEXT("APP_LAUNCH5"));
		break;
	case VK_APP_LAUNCH6 :
		wsprintf(szOut, TEXT("APP_LAUNCH6"));
		break;
	case VK_APP_LAUNCH7 :
		wsprintf(szOut, TEXT("APP_LAUNCH7"));
		break;
	case VK_APP_LAUNCH8 :
		wsprintf(szOut, TEXT("APP_LAUNCH8"));
		break;
	case VK_APP_LAUNCH9 :
		wsprintf(szOut, TEXT("APP_LAUNCH9"));
		break;
	case VK_APP_LAUNCH10:
		wsprintf(szOut, TEXT("APP_LAUNCH10"));
		break;
	case VK_APP_LAUNCH11:
		wsprintf(szOut, TEXT("APP_LAUNCH11"));
		break;
	case VK_APP_LAUNCH12:
		wsprintf(szOut, TEXT("APP_LAUNCH12"));
		break;
	case VK_APP_LAUNCH13:
		wsprintf(szOut, TEXT("APP_LAUNCH13"));
		break;
	case VK_APP_LAUNCH14:
		wsprintf(szOut, TEXT("APP_LAUNCH14"));
		break;
	case VK_APP_LAUNCH15:
		wsprintf(szOut, TEXT("APP_LAUNCH15"));
		break;
	default:
		wsprintf(szOut, TEXT("%08x"), wParam);
		break;
  }
}


//
// CreateMenuBar
//   create the commandbar and add any menus and buttons to it you like
//   call AddAdornments to show close button which is only appropriate on H/PC devices
//
HWND CreateMenuBar(HWND hwnd, HWND hwndCB, BOOL bCreating)
{
	// always delete to avoid a leak
	if (hwndCB)
	{
		//Destroy MenuBar       
		DestroyWindow(hwndCB);
		hwndCB = NULL;
	}
	
	if (bCreating)
	{
		//Create a MenuBar
		SHMENUBARINFO mbi;
		memset(&mbi, 0, sizeof(SHMENUBARINFO));
		mbi.cbSize     = sizeof(SHMENUBARINFO);
		mbi.hwndParent = hwnd;
		mbi.nToolBarId = IDM_MAIN_MENU;
		mbi.hInstRes   = g_hinst;
		mbi.nBmpId     = 0;
		mbi.cBmpImages = 0;	
		
		SHCreateMenuBar(&mbi);
		if (!SHCreateMenuBar(&mbi))
			MessageBox(hwnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
		hwndCB = mbi.hwndMB;
	}
	
	return hwndCB;
	
}

//
// DoMenuCheckItem
void DoMenuCheckItem(UINT IDCTL){
	
	HMENU hm = SHGetSubMenu(g_hwndCB, IDM_MAIN_MENUITEM1);

	switch (IDCTL) {
	case ID_FILE_SHOW_WMKEYDOWN:
		if (fWM_KEYDOWN){
			fWM_KEYDOWN = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_KEYDOWN = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMCHAR:
		if (fWM_CHAR){
			fWM_CHAR = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_CHAR = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMKEYUP:
		if (fWM_KEYUP){
			fWM_KEYUP = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_KEYUP = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMLBUTTONDBLCLK:
		if (fWM_LBUTTONDBLCLK){
			fWM_LBUTTONDBLCLK = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_LBUTTONDBLCLK = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMLBUTTONDOWN:
		if (fWM_LBUTTONDOWN){
			fWM_LBUTTONDOWN = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_LBUTTONDOWN = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMLBUTTONUP:
		if (fWM_LBUTTONUP){
			fWM_LBUTTONUP = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_LBUTTONUP = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMMOUSEMOVE:
		if (fWM_MOUSEMOVE){
			fWM_MOUSEMOVE = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_MOUSEMOVE = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	}
}

//
// HandleCommand
//   will return FALSE if handled
//
BOOL HandleCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	
	// Parse the menu selections:
	switch (LOWORD(wParam))
	{
	case ID_FILE_SHOW_WMKEYDOWN:
	case ID_FILE_SHOW_WMCHAR:
	case ID_FILE_SHOW_WMKEYUP:
	case ID_FILE_SHOW_WMLBUTTONDBLCLK:
	case ID_FILE_SHOW_WMLBUTTONDOWN:
	case ID_FILE_SHOW_WMLBUTTONUP:
	case ID_FILE_SHOW_WMMOUSEMOVE:
		DoMenuCheckItem(LOWORD(wParam));
		return FALSE;
	}
	return TRUE;
}

//
// Mesage handler for the About box.
//  since this is a dialog proc, return TRUE if it was indeed handled
//   this is backwards from a window proc
//
LRESULT CALLBACK About(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SHINITDLGINFO shidi;
		// Create a Done button and size it.
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hwnd;
		SHInitDialog(&shidi);
		return TRUE;
		
		
    case WM_COMMAND:
		if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
		{
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

