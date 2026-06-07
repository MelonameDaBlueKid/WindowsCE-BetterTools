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
/***********************************************************************
	  MODULE: 
	  Tty.c
	  
		ABSTRACT: 
		This Windows CE application shows how to open, configure, and close a
		serial communications port and perform read/write operations for a TTY
		terminal emulation application.
		
***********************************************************************/
#include <windows.h>
#include <commctrl.h>
#include <aygshell.h>
#include "tty.h"
#include "resource.h"

#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))

HWND g_hMainWnd,                          // Main window handle
	g_hTermWnd,                          // Terminal window handle
	g_hCmdBarWnd,                        // The command bar window handle
	g_hDTRWnd,                           // DTR check box window handle
	g_hRTSWnd,                           // RTS check box window handle
	g_hDSRWnd,                           // DSR check box window handle
	g_hCTSWnd,                           // CTS check box window handle
	g_hDCDWnd,                           // DCD check box window handle
	g_hRINGWnd;                          // RING check box window handle

HINSTANCE g_hInst;                        // hInstance of the application
TCHAR g_tszTitle[] = TEXT("Tty");          // Main window name
TCHAR g_tszAppName[] = TEXT("Tty Sample Application");
// Main window class name
LPTSTR g_lptszDevName;                     // Communication port name
HFONT g_hFont = NULL;                     // Handle to the font to use
HANDLE g_hReadThread = NULL;              // Handle to the read thread
HANDLE g_hPort = INVALID_HANDLE_VALUE;    // Handle to the serial port

TERM_SCREEN g_Screen;                     

DWORD dwBaudRates[] = {300, 1200, 2400, 4800, 9600, 14400, 19200, 38400,
57600, 115200};  // List of baud

#define MENU_HEIGHT       26
#define BUTTONBAR_HEIGHT  16            // Height of the check box bar
#define BUTTON_HEIGHT     14            // Height of the check boxes
#define NUM_BAUD_RATES (sizeof(dwBaudRates) / sizeof(DWORD))
#define MAX_BUFFER_LEN    80
// Number of baud in the baud
// list
/***********************************************************************

  FUNCTION: 
  SetLightIndicators
  
	PURPOSE: 
	Sets the check state of the check boxes. 
	
***********************************************************************/
VOID SetLightIndicators(
	DWORD dwCommModemStatus
	)
{
	SendMessage(g_hDSRWnd, BM_SETCHECK, 
		dwCommModemStatus & MS_DSR_ON, 0);
	SendMessage(g_hCTSWnd, BM_SETCHECK, 
		dwCommModemStatus & MS_CTS_ON, 0);
	SendMessage(g_hDCDWnd, BM_SETCHECK, 
		dwCommModemStatus & MS_RLSD_ON, 0);
	SendMessage(g_hRINGWnd, BM_SETCHECK, 
		dwCommModemStatus & MS_RING_ON, 0);
}


/***********************************************************************

  FUNCTION: 
  CommDlgProc
  
	PURPOSE: 
	Processes messages sent to the Communications dialog box window. 
	
***********************************************************************/
LRESULT CALLBACK CommDlgProc(
	HWND hDlg, 
	UINT uMsg, 
	WPARAM wParam,
	LPARAM lParam
	)
{
	LRESULT lResult;
	HWND hCtrlWnd ;
	DCB PortDCB = {0};
	int index;
	TCHAR tszTmpString[MAX_BUFFER_LEN];
	
	switch (uMsg) 
	{
    case WM_INITDIALOG:
		{
			//On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
			// with an OK button in the upper corner. You should get/set any program settings
			// during each modal dialog creation and destruction
			SHINITDLGINFO shidi = {0};
			// Create a Done button and size it.
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			//initialzes the dialog based on the dwFlags parameter
			SHInitDialog(&shidi);
			
			StringCchPrintf(tszTmpString, ARRAYSIZE(tszTmpString), TEXT("Communications settings for '%s'"),
                g_lptszDevName);

			SetWindowText(GetDlgItem(hDlg, IDC_PORTLABEL), tszTmpString);
			
			PortDCB.DCBlength = sizeof(DCB);
			
			// Get the default port setting information.
			GetCommState(g_hPort, &PortDCB);
			
			// Add strings to the baud combo box and select an item.
			hCtrlWnd = GetDlgItem(hDlg, IDC_BAUDRATE);
			
			for (index = 0; index < NUM_BAUD_RATES; ++index) 
			{
				StringCchPrintf(tszTmpString, ARRAYSIZE(tszTmpString), TEXT("%d"), dwBaudRates[index]);
				SendMessage(hCtrlWnd, CB_INSERTSTRING, index,(LPARAM)tszTmpString);
			}
			
			StringCchPrintf(tszTmpString, ARRAYSIZE(tszTmpString), TEXT("%d"), PortDCB.BaudRate);
			lResult = SendMessage(hCtrlWnd, CB_FINDSTRINGEXACT, 0, 
				(LPARAM)tszTmpString);
			SendMessage(hCtrlWnd, CB_SETCURSEL, lResult, 0);
			
			// Add strings to the data bits combo box and select an item.
			hCtrlWnd = GetDlgItem(hDlg, IDC_DATABITS);
			
			for (index = 4; index <= 8; index++) 
			{
				StringCchPrintf(tszTmpString, ARRAYSIZE(tszTmpString), TEXT("%d"), index);
				SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)tszTmpString);
			}
			
			_stprintf(tszTmpString, TEXT("%d"), PortDCB.ByteSize);
			lResult = SendMessage(hCtrlWnd, CB_FINDSTRINGEXACT, 0, 
				(LPARAM)tszTmpString);
			SendMessage(hCtrlWnd, CB_SETCURSEL, lResult, 0);
			
			// Add strings to the stop bits combo box and select an item.
			hCtrlWnd = GetDlgItem(hDlg, IDC_STOPBITS);
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("1"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("1.5"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("2"));
			SendMessage(hCtrlWnd, CB_SETCURSEL,(WPARAM)PortDCB.StopBits, 0);
			
			// Add strings to the parity combo box and select an item.
			hCtrlWnd = GetDlgItem(hDlg, IDC_PARITY);
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("None"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("Odd"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("Even"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("Mark"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("Space"));
			SendMessage(hCtrlWnd, CB_SETCURSEL,(WPARAM)PortDCB.Parity, 0);
			
			// Add strings to the flow control combo box and select an item.
			hCtrlWnd = GetDlgItem(hDlg, IDC_FLOWCTRL);
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("None"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("RTS/CTS"));
			SendMessage(hCtrlWnd, CB_ADDSTRING, 0,(LPARAM)TEXT("XON/XOFF"));
			
			if (PortDCB.fOutX) 
			{
				index = 2;
			}
			else if (PortDCB.fOutxCtsFlow) 
			{
				index = 1;
			}
			else
			{
				index = 0;
			}
			
			SendMessage(hCtrlWnd, CB_SETCURSEL,(WPARAM)index, 0);
			
			// Set the state of DSR Sensitivity check box.
			SendMessage(GetDlgItem(hDlg, IDC_DSR_SENS), 
				BM_SETCHECK,
				(WPARAM)(PortDCB.fDsrSensitivity ? 1 : 0),
				(LPARAM)0);
			
			return TRUE;
		}
		
    case WM_COMMAND:
		
		switch(LOWORD(wParam)) 
		{
        case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
			
        case IDOK:
			// Save the settings for the serial communications device.
			
			// Save the baud.
			GetWindowText(GetDlgItem(hDlg, IDC_BAUDRATE),
				tszTmpString, 
				sizeof(tszTmpString) / sizeof(TCHAR));
			PortDCB.BaudRate = _ttol(tszTmpString);
			
			// Save the data bits.
			GetWindowText(GetDlgItem(hDlg, IDC_DATABITS), 
				tszTmpString,
				sizeof(tszTmpString) / sizeof(TCHAR));
			PortDCB.ByteSize =(BYTE)_ttol(tszTmpString);
			
			// Save the stop bits.
			PortDCB.StopBits =(BYTE)SendMessage(
				GetDlgItem(hDlg, IDC_STOPBITS),
				CB_GETCURSEL,
				(WPARAM)0, 
				(LPARAM)0);
			// Save the parity.
			PortDCB.Parity =(BYTE)SendMessage(
				GetDlgItem(hDlg, IDC_PARITY),
				CB_GETCURSEL,
				(WPARAM)0, 
				(LPARAM)0);
			
			// Set to no flow control.
			lResult = SendMessage(GetDlgItem(hDlg, IDC_FLOWCTRL),
				CB_GETCURSEL,
				(WPARAM)0, 
				(LPARAM)0);
			PortDCB.fOutX = FALSE;
			PortDCB.fInX = FALSE;
			PortDCB.fOutxCtsFlow = FALSE;
			PortDCB.fRtsControl = RTS_CONTROL_ENABLE;
			
			if (lResult == 1) 
			{
				PortDCB.fOutxCtsFlow = TRUE;
				PortDCB.fRtsControl = RTS_CONTROL_HANDSHAKE;
			}
			else if (lResult == 2) 
			{
				PortDCB.fOutX = TRUE;
				PortDCB.fInX = TRUE;
			} 
			
			// Save the DSR Sensitivity.
			lResult = SendMessage(GetDlgItem(hDlg, IDC_DSR_SENS), 
				BM_GETCHECK,
				(WPARAM)0, 
				(LPARAM)0);
			if (BST_CHECKED == lResult) 
			{
				PortDCB.fDsrSensitivity = 1;
			}
			else
			{
				PortDCB.fDsrSensitivity =0;
			}
			
			// Configure the port according to the DCB structure.
			SetCommState(g_hPort, &PortDCB);
			
			EndDialog(hDlg, TRUE);
			return TRUE;
		}
		break;
  }
  
  return FALSE;
}


/***********************************************************************

FUNCTION: 
TermWndProc

PURPOSE: 
Processes messages sent to the terminal window.

***********************************************************************/
LRESULT CALLBACK TermWndProc(
	HWND hWnd, 
	UINT uMsg, 
	WPARAM wParam,
	LPARAM lParam
	)
{
	HDC hDC;
	PAINTSTRUCT ps;
	  
	switch(uMsg)
	{
	case WM_SETFOCUS:
		g_Screen.bHaveFocus = TRUE;
		CreateCaret(hWnd, NULL, g_Screen.CharWidth, g_Screen.CharHeight);
		
		if (ON_SCREEN(g_Screen.CursorRow, g_Screen.CursorCol))
		{
			SetCaretPos(COLX(g_Screen.CursorCol), ROWY(g_Screen.CursorRow));
			ShowCaret(hWnd);    
		}
		break;
		
	case WM_KILLFOCUS:
		g_Screen.bHaveFocus = FALSE;
		HideCaret(hWnd);
		DestroyCaret();
		break;
		
	case WM_SIZE:
		// Resize everything.
		InitScreenSettings(hWnd);
		break;
		
	case WM_PAINT:
		HideCaret(g_hTermWnd);
		hDC = BeginPaint(hWnd, &ps);
		PaintScreen(hWnd, hDC, &(ps.rcPaint));
		EndPaint(hWnd, &ps);
		ShowCaret(g_hTermWnd);
		break;
		
	case WM_CHAR:
		if (g_hPort != INVALID_HANDLE_VALUE)
		{
			// Writing to the port.
			PortWrite((BYTE)(wParam & 0xFF));
		}
		else 
		{
			// Display on the screen.
			ProcessChar((BYTE)(wParam & 0xFF));
		}
		break;
		
	case WM_VSCROLL:
		switch(LOWORD(wParam))
		{
		case SB_LINEUP:
			ScrollDown(-1);
			break;
			
		case SB_LINEDOWN:
			ScrollDown(1);
			break;
			
		case SB_PAGEUP:
			ScrollDown(-(g_Screen.ScreenRows - 1));
			break;
			
		case SB_PAGEDOWN:
			ScrollDown(g_Screen.ScreenRows - 1);
			break;
			
		case SB_TOP:
			ScrollDown(-g_Screen.NumRows);
			break;
			
		case SB_BOTTOM:
			ScrollDown(g_Screen.NumRows);
			break;
			
		case SB_THUMBPOSITION:
			ScrollDown(HIWORD(wParam) - g_Screen.TopRow);
			break;
			
		case SB_THUMBTRACK:
			break;
			
		case SB_ENDSCROLL:
			break;
		}
		break;
		
	case WM_HSCROLL:
		switch(LOWORD(wParam))
		{
		case SB_LINELEFT:
			ScrollRight(-1);
			break;
			
		case SB_LINERIGHT:
			ScrollRight(1);
			break;
			
		case SB_PAGELEFT:
			ScrollRight(-(g_Screen.ScreenCols - 1));
			break;
			
		case SB_PAGERIGHT:
			ScrollRight(g_Screen.ScreenCols - 1);
			break;
			
		case SB_LEFT:
			ScrollRight(-g_Screen.NumCols);
			break;
			
		case SB_RIGHT:
			ScrollRight(g_Screen.NumCols);
			break;
			
		case SB_THUMBPOSITION:
			ScrollRight(HIWORD(wParam) - g_Screen.LeftCol);
			break;
			
		case SB_THUMBTRACK:
			break;
			
		case SB_ENDSCROLL:
			break;
		}
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}


/***********************************************************************

  FUNCTION: 
  MainWndProc
  
	PURPOSE: 
	Processes messages sent to the main window.
	
	  ***********************************************************************/
	  LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		  LPARAM lParam)
	  {
		  HDC hDC;
		  RECT rect;
		  HBRUSH hBrush;
		  PAINTSTRUCT ps;
		  
		  switch(uMsg)
		  {
		  case WM_CREATE:
			  {
				  SHMENUBARINFO mbi;
				  
				  memset(&mbi, 0, sizeof(SHMENUBARINFO));
				  mbi.cbSize     = sizeof(SHMENUBARINFO);
				  mbi.hwndParent = hWnd;
				  mbi.nToolBarId = IDM_MAIN_MENU;
				  mbi.hInstRes   = g_hInst;
				  mbi.nBmpId     = 0;
				  mbi.cBmpImages = 0;    
				  
				  if (!SHCreateMenuBar(&mbi))
				  {
					  MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
					  return -1;
				  }
				  
				  g_hCmdBarWnd = mbi.hwndMB;
				  return 0;
			  }
			  
		  case WM_PAINT:
			  hDC = BeginPaint(hWnd, &ps);
			  
			  // Draw the gray background for the button bar.
			  hBrush =(HBRUSH)GetStockObject(LTGRAY_BRUSH);
			  GetClientRect(hWnd, &rect);
			  rect.bottom = BUTTONBAR_HEIGHT;
			  FillRect(hDC, &rect, hBrush);
			  DeleteObject(hBrush);
			  
			  // Draw the black background for rest of the area.
			  hBrush =(HBRUSH)GetStockObject(BLACK_BRUSH);
			  rect.top = BUTTONBAR_HEIGHT - 1;
			  FillRect(hDC, &rect, hBrush);
			  DeleteObject(hBrush);
			  
			  EndPaint(hWnd, &ps);
			  return 0;
			  
		  case WM_SETFOCUS:
			  // Give the focus to the terminal window.
			  SetFocus(g_hTermWnd);
			  return 0;
			  
		  case WM_SIZE:
			  GetClientRect(hWnd, &rect);
			  //rect.top = MENU_HEIGHT;
			  //rect.top += BUTTONBAR_HEIGHT;
			  SetWindowPos(g_hTermWnd, HWND_TOP, rect.left, rect.top,
				  rect.right - rect.left, rect.bottom - rect.top, 0);
			  ShowWindow(g_hTermWnd, SW_SHOWNORMAL);
			  return 0;
			  
		  case WM_COMMAND:
			  switch(LOWORD(wParam))
			  {
			  case ID_FILE_EXIT:
				  DestroyWindow(hWnd);
				  break;
				  
			  case ID_EDIT_CLEARBUFFER:
				  ClearScreen();
				  break;
				  
			  case ID_SETTINGS:
				  DialogBox(g_hInst, MAKEINTRESOURCE(IDD_COMMUNICATIONS),
					  hWnd,(DLGPROC)CommDlgProc);
				  break;
				  
			  case ID_HELP_ABOUTTTY:
				  MessageBox(hWnd, 
					  TEXT("TTY Sample Application\r\n")
					  TEXT("(c) Microsoft 1999"),
					  TEXT("About TTY"), 
					  MB_OK);
				  break;
				  
			  case ID_DTR_BTN:
				  if (SendMessage(g_hDTRWnd, BM_GETCHECK, 0, 0))
					  EscapeCommFunction(g_hPort, SETDTR);
				  else
					  EscapeCommFunction(g_hPort, CLRDTR);
				  
				  SetFocus(g_hTermWnd);
				  break;
				  
			  case ID_RTS_BTN:
				  if (SendMessage(g_hRTSWnd, BM_GETCHECK, 0, 0))
					  EscapeCommFunction(g_hPort, SETRTS);
				  else 
					  EscapeCommFunction(g_hPort, CLRRTS);
				  
				  SetFocus(g_hTermWnd);
				  break;
				  
			  case ID_DSR_BTN:
			  case ID_CTS_BTN:
			  case ID_DCD_BTN:
			  case ID_RING_BTN:
				  SetFocus(g_hTermWnd);
				  break;
				  

			  }
			  return 0;
			  
			  case WM_DESTROY:
				  {
					  // Clear all events to be monitored for the port. 
					  SetCommMask(g_hPort, 0);
					  
					  // Close the serial port.
					  PortClose(g_hPort);
					  
					  PostQuitMessage(0);
					  return 0;
				  }
}

return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

/***********************************************************************

FUNCTION: 
InitApplication

PURPOSE: 
Initialize and register window class.

***********************************************************************/
BOOL InitApplication(
	HINSTANCE hInstance
	)
{
	WNDCLASS  wc;
	
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc =(WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon =(HICON)NULL;
	wc.hCursor = NULL;
	wc.hbrBackground =(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = g_tszAppName;
	
	if (0 == RegisterClass(&wc))
	{
		return FALSE;
	}
	
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc =(WNDPROC)TermWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon =(HICON)NULL;
	wc.hCursor = NULL;
	wc.hbrBackground =(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("TermClass");
	
	return RegisterClass(&wc);
}

/***********************************************************************

FUNCTION: 
InitInstance

PURPOSE: 
Create and display the main window.

***********************************************************************/
BOOL InitInstance(
	HINSTANCE hInstance, 
	int nCmdShow
	)
{
	RECT rect;
	DWORD dwStyle;
	DWORD dwError;



	if (NULL != FindWindow(g_tszAppName, g_tszTitle))
	{
        //Notify other instance and exit
        SetForegroundWindow(FindWindow(g_tszAppName, g_tszTitle));
		return FALSE;
	}
	
	g_hMainWnd = CreateWindowEx(0, g_tszAppName, g_tszTitle,
		WS_CLIPCHILDREN, 0,0, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,	hInstance, NULL);

	if (NULL == g_hMainWnd)
	{
		dwError = GetLastError();
		return FALSE;
	}
	
	ShowWindow(g_hMainWnd, nCmdShow);
	UpdateWindow(g_hMainWnd);
	
	GetClientRect(g_hMainWnd, &rect);
	rect.top = MENU_HEIGHT;
	rect.bottom -= 2*BUTTONBAR_HEIGHT;
	
	// Window style
	dwStyle = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX;
	
	g_hDTRWnd = CreateWindow(TEXT("button"), TEXT("DTR"), dwStyle, 
		rect.left + 5, rect.bottom, 50, BUTTON_HEIGHT,
		g_hMainWnd,(HMENU)ID_DTR_BTN, hInstance, NULL);
	
	g_hRTSWnd = CreateWindow(TEXT("button"), TEXT("RTS"), dwStyle,
		rect.left + 65, rect.bottom, 50, BUTTON_HEIGHT, 
		g_hMainWnd,(HMENU)ID_RTS_BTN, hInstance, NULL);
	
	// Create the following check box for monitoring a set of events.
	// Because these checkboxes are used for monitoring events only, 
	// make all of them disabled upon creation.
	
	// Window style
	dwStyle = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_DISABLED;
	rect.bottom += BUTTONBAR_HEIGHT;
	
	g_hDSRWnd = CreateWindow(TEXT("button"), TEXT("DSR"), dwStyle, 
		rect.left + 5, rect.bottom, 50, BUTTON_HEIGHT, 
		g_hMainWnd,(HMENU)ID_DSR_BTN, hInstance, NULL);
	
	g_hCTSWnd = CreateWindow(TEXT("button"), TEXT("CTS"), dwStyle, 
		rect.left + 65, rect.bottom, 50, BUTTON_HEIGHT, 
		g_hMainWnd,(HMENU)ID_CTS_BTN, hInstance, NULL);
	
	g_hDCDWnd = CreateWindow(TEXT("button"), TEXT("DCD"), dwStyle, 
		rect.left + 125, rect.bottom, 50, BUTTON_HEIGHT, 
		g_hMainWnd,(HMENU)ID_DCD_BTN, hInstance, NULL);
	
	g_hRINGWnd = CreateWindow(TEXT("button"), TEXT("RING"), dwStyle, 
		rect.left + 185, rect.bottom, 60, BUTTON_HEIGHT, 
		g_hMainWnd,(HMENU)ID_RING_BTN, hInstance,NULL);
	
	// Terminal window style
	dwStyle = WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_BORDER;
	rect.bottom -= BUTTONBAR_HEIGHT;
	
	// Create the terminal window.
	g_hTermWnd = CreateWindowEx(0, TEXT("TermClass"),	TEXT("PSPC TTY"),
		dwStyle, rect.left, rect.top, rect.right - rect.left,
		rect.bottom - rect.top,	g_hMainWnd, NULL,	hInstance, NULL);
	if (NULL == g_hTermWnd)
	{
		dwError = GetLastError();
		return FALSE;
	}
	
	SetFocus(g_hTermWnd);
	
	return TRUE;
}



/***********************************************************************

FUNCTION: 
WinMain

PURPOSE: 
The WinMain function of the application. It is called by the system as
the initial entry point for this WindowsCE-based application.

***********************************************************************/
int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR lpCmdLine, 
	int nCmdShow
	)
{
	MSG msg;
	DWORD dwCommModemStatus;

	//set a default return value
	msg.wParam = (WPARAM)-1;
	
	g_hInst = hInstance;
	
	if (!hPrevInstance)
	{
		if (!InitApplication(hInstance))
			return 0;
	}
	
	if (!InitInstance(hInstance, nCmdShow))
	{
		if (g_hTermWnd)
			DestroyWindow(g_hTermWnd);
		
		goto ExitMain;
	}
	
	// Initialize the screen.
	if (!InitScreenSettings(g_hTermWnd))
	{
		MessageBox(g_hMainWnd, 
			TEXT("Unable to allocate screen buffer"),
			TEXT("Fatal Error"), 
			MB_OK);
		
		DestroyWindow(g_hTermWnd);
		goto ExitMain;
	}
	
	// Clear the screen.
	ClearScreen();
	
	// Assign the port name. If the port name is NULL, assign the default
	// value as "COM1:".
	if (*lpCmdLine == TEXT('\0')) 
		g_lptszDevName = TEXT("COM1:");
	else
		g_lptszDevName = lpCmdLine;
	
	// Initialize the port.
	if (!PortInitialize(g_lptszDevName))
	{
		DestroyWindow(g_hTermWnd);
		goto ExitMain;
	}
	
	// Set the state of the DTR and RTS check boxes.
	SendMessage(g_hDTRWnd, BM_SETCHECK, TRUE, 0);
	SendMessage(g_hRTSWnd, BM_SETCHECK, TRUE, 0);
	
	// Initialize the indicator lights.
	GetCommModemStatus(g_hPort, &dwCommModemStatus);
	SetLightIndicators(dwCommModemStatus);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
ExitMain:
	
	if (g_hFont)
	{
		DeleteObject((HGDIOBJ)g_hFont);
	}
	
	return 1;
}


