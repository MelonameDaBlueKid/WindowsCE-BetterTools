/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//
//  PARTICULAR PURPOSE.
//
// 
//
//  This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// CEGetDev.cpp : Demonstrates the use of GetDeviceCaps to report the capabilities of the device

#include <windows.h>
#include "CEGetDev.h"
#include <commctrl.h>



// Foward declarations of functions included in this code module:
BOOL InitInstance(
	HINSTANCE, 
	int
	);
LRESULT CALLBACK WndProc(
	HWND,
	UINT,
	WPARAM, 
	LPARAM);
void ExpandInfo(
	int,
	int
	);
static void ExpandLookup(
	const LookupEntry * lpTable, 
	int iValue, 
	UINT uNumEntries
	);
static void OutputFormattedString(
	LPCTSTR szFormat, 
	...
	);


// Global Variables:
HINSTANCE g_hInst;  // The current instance
HWND g_hwndListBox; // The listbox used to display the device capabilities 
LPCTSTR g_tszTitle; // The title bar text
const TCHAR * g_tszWindowClass = TEXT("CEGetDevApp");   // The window class name
TCHAR const g_tszSpace[] = _T("   %1!s!");  // template for outputting an indented string using OutputFormattedString
int g_nMenuHeight = 0;


// Purpose: Determine at runtime if the app is running on a smartphone device
static BOOL IsSmartphone() 
{
    TCHAR tszPlatform[64];

    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE,
         sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
    {
        if (0 == _tcsicmp(TEXT("Smartphone"), tszPlatform)) 
        {
            return TRUE;
        }
    }
    return FALSE;   
}

// Main windows	Msg loop
int WINAPI WinMain(	
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow
	)
{
	MSG msg;
    HANDLE hMutex = NULL;

	// load in program name and classname
	g_tszTitle = (LPCTSTR)LoadString(hInstance, IDS_CAP_TITLE, NULL, 0);
	if (!g_tszTitle)
		return FALSE;


	// Use a global mutex to detect another instance of CEGetDev
    hMutex = CreateMutex(0, 0, TEXT("_CE_GETDEVCAPS_EXE_MUTEX_"));


	if(NULL != hMutex)
	{
		if(ERROR_ALREADY_EXISTS == GetLastError())
		{ // There's already an instance running, so try to activate it...
			HWND hwnd;

			// release our reference to the mutex
            CloseHandle(hMutex);
            hMutex = NULL;

            // There is already an instance of this app
            // running.  Try to bring it to the foreground.

            hwnd = FindWindow(g_tszWindowClass, g_tszTitle);
            if(NULL == hwnd)
            {
                // It's possible that the other window is in the process of being created...
                Sleep(500);
                hwnd = FindWindow(g_tszWindowClass, g_tszTitle);
            }

            if(NULL != hwnd) 
            {
                // Set the previous instance as the foreground window

                // The "| 0x01" in the code below activates
                // the correct owned window of the
                // previous instance's main window.
                SetForegroundWindow((HWND) (((ULONG) hwnd) | 0x01));
				
				return FALSE;
            }

		}

	}
	else
	{
		return FALSE;
	}


	// At this point we are starting the first instance

	// Perform application initialization:
	if (FALSE == InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	
	// Main Msg loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}
	
	VERIFY(CloseHandle(hMutex));

	return msg.wParam;
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
	HWND	hWnd;
    WNDCLASS wc;

	g_hInst = hInstance;		// Store instance handle in our global variable
	

	// Register the class
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= 0;
	wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= g_tszWindowClass;
	
	if(!RegisterClass(&wc))
    {
        return(0);
    }

	
	if (!IsSmartphone())
	{
		g_nMenuHeight=26;
	}
	
	
	////////// Setting default main window size
	// This technique allows for you to create the main
	// window to allow for the postion of a menubar and/or
	// the SIP button at the bottom of the screen
	
	hWnd = CreateWindow(g_tszWindowClass, g_tszTitle, WS_VISIBLE ,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	if (NULL ==hWnd)
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
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit Msg and return
//
//
LRESULT CALLBACK WndProc(
	HWND hWnd, 
	UINT Msg, 
	WPARAM wParam, 
	LPARAM lParam)
{
	HDC hdc;
	int i;
	int value;
	
	switch (Msg) 
	{
		case WM_COMMAND:
			// Parse the menu selections:
			switch (LOWORD(wParam))
			{
				case IDM_FILE_EXIT:
					DestroyWindow(hWnd);
					break;
					
				default:
					return DefWindowProc(hWnd, Msg, wParam, lParam);
			}
			break;
		
		case WM_CREATE:
			{

				RECT rc;
				GetClientRect(hWnd, &rc);

				//Create a MenuBar
				SHMENUBARINFO mbi;
				memset(&mbi, 0, sizeof(SHMENUBARINFO));
				mbi.cbSize     = sizeof(SHMENUBARINFO);
				mbi.hwndParent = hWnd;
				mbi.nToolBarId = IDR_MENUBAR1;
				mbi.hInstRes   = g_hInst;
				mbi.nBmpId     = 0;
				mbi.cBmpImages = 0;	
    
				if (FALSE == SHCreateMenuBar(&mbi))
				{
					MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
				}
				
				// create the listbox that we will use to format our results. 
				// Set it to occupy the entire client rect of the app
				g_hwndListBox = CreateWindow(_T("LISTBOX"), NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL
					|LBS_NOINTEGRALHEIGHT|LBS_USETABSTOPS   , 
					rc.left, rc.top, rc.right, rc.bottom - g_nMenuHeight, hWnd, (HMENU)IDR_LISTBOX, g_hInst,NULL);
				
				
				if (NULL != g_hwndListBox)
				{
					//Iterate through the values to GetDeviceCaps
					hdc = GetDC (hWnd);
					for (i = 0; i < NINDEX ; i++) 
					{
						value = GetDeviceCaps (hdc , DevCaps[i].Value);
						OutputFormattedString (_T("%1!s! \t %2!8d!"), DevCaps[i].String, value);
						//Expand information returned from GetDeviceCaps if required
						ExpandInfo(DevCaps[i].Value, value);
					}
					ReleaseDC(hWnd,hdc);
					
					ShowWindow(g_hwndListBox, SW_SHOW);
					UpdateWindow(g_hwndListBox);

					// set the maximum horizontal extent of the listbox to the size of the buffer (in characters)
					// that we use for constructing the output.
					SendMessage(g_hwndListBox, LB_SETHORIZONTALEXTENT, MAX_PATH, 0);
				}
			}
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
			
		case WM_ACTIVATE:
			if (WA_INACTIVE != wParam) 
			{
				SetFocus(g_hwndListBox);
			}
			break;

		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
			break;
	}

	return 0;
}

// function: ExpandLookup()
// input parameters:
//		lpTable - an array of LookupEntry structures to extract attributes from
//		iValue  - the value to compare against lookup table entries
//		uNumEntries	- the number of entries in the table
// description:
//		Compares the bits set in the input, iValue with the individual flags in the lookup table. 
//		Where a bit in the input value matches a bit in the lookup table, the corresponding 
//		text value in the lookup table is added to the listbox.
static void ExpandLookup(
	const LookupEntry * lpTable, 
	int iValue, 
	UINT uNumEntries
	)
{
	UINT i;
	

	for (i = 0; i < uNumEntries; i++)
	{
		if (iValue & lpTable[i].Value)
		{
			OutputFormattedString(g_tszSpace, lpTable[i].String);
		}
	}
}

//function:  ExpandInfo()
//input parameters:
//    index - the input value which was sent to GetDeviceCaps().
//    value - the return value from calling GetDeviceCaps().
//description:
//		Expands return values from GetDeviceCaps that are flags rather than numeric values.
//		Where multiple flags may be set in the return value this function calls ExpandLookup() 
//		with the appropriate lookup table to extract and print the flags that are set.
static void ExpandInfo(
	int iIndex, 
	int iValue
	)
{
	const LookupEntry *lpLookUp; 
	UINT uMax = 0;
	
	switch (iIndex) 
	{
	case TECHNOLOGY   :
		// special case: returned value is unique, not ORable bit fields as in other cases.
		lpLookUp = NULL;
		while ((Device[uMax].Value != iValue) &&  (uMax < NDEVICE))
			uMax++;
		if (Device[uMax].Value == iValue)
		{
			OutputFormattedString(g_tszSpace, Device[uMax].String);
			
		}
		break;
		
	case CURVECAPS    :
		lpLookUp = CurveCaps;
		uMax = NCURVECAPS;
		break;
		
	case LINECAPS     :
		lpLookUp = LineCaps;
		uMax = NLINECAPS;
		break;
		
	case POLYGONALCAPS:
		lpLookUp = PolygonalCaps;
		uMax = NPOLYGONALCAPS;
		break;
		
	case TEXTCAPS     :
		lpLookUp = TextCaps;
		uMax = NTEXTCAPS;
		break;
		
	case CLIPCAPS     :
		lpLookUp = ClipCaps;
		uMax = NCLIPCAPS;
		break;
		
	case RASTERCAPS   :
		lpLookUp = RasterCaps;
		uMax = NRASTERCAPS;
		break;
		
	default:
		lpLookUp = NULL;
		break;
	}
	if (NULL != lpLookUp)
	{
		ExpandLookup(lpLookUp, iValue, uMax);
	}
}


// function: OutputFormattedString()
// input parameters:
//		szFormat: a valid FormatMessage Format String
//		...:		optional supporting arguments
// description:
//		Outputs a formatted string to the application's listbox	
static void OutputFormattedString(
	LPCTSTR szFormat,
	...
	)
{
    TCHAR tszBuffer[MAX_PATH];
    va_list vaMarker;

    va_start(vaMarker, szFormat);
    FormatMessage(FORMAT_MESSAGE_FROM_STRING, szFormat, 0, 0, tszBuffer, 
        ARRAY_SIZE(tszBuffer), &vaMarker);
    va_end(vaMarker);

    SendMessage(g_hwndListBox, LB_ADDSTRING, 0, (LPARAM)tszBuffer);
}
