/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

 

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/

/*-------------------------------------------------------------------*\
Module: SysInfo.cpp

\*-------------------------------------------------------------------*/

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <aygshell.h>
#include "resource.h"

//------------------------------------------------------
// Local Support Macros
//------------------------------------------------------

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// Struct of name and index pairs
typedef struct
{
	LPCTSTR lptszName; // Name of the index value
	int iIndex; // Index value
} SNameIndexPair;

//Generates the name from the index definition to enter into a table
#define NAME_INDEX_PAIR(a) {TEXT(#a), a}


//------------------------------------------------------
// Globals
//------------------------------------------------------

HINSTANCE	g_hInst = NULL;	// Local copy of hInstance
HWND		g_hwndChild = NULL;	// Handle to the Edit Control

const TCHAR tszAppName[] = TEXT("SysInfo Application");	//Window Class
const TCHAR tszTitle[]   = TEXT("SysInfo");				//Window Title


static const SNameIndexPair g_SystemMetricTable[] =
{
	NAME_INDEX_PAIR(SM_CXSCREEN),
	NAME_INDEX_PAIR(SM_CYSCREEN),
	NAME_INDEX_PAIR(SM_CXVSCROLL),
	NAME_INDEX_PAIR(SM_CYHSCROLL),
	NAME_INDEX_PAIR(SM_CYCAPTION),
	NAME_INDEX_PAIR(SM_CXBORDER),
	NAME_INDEX_PAIR(SM_CYBORDER),
	NAME_INDEX_PAIR(SM_CXDLGFRAME),
	NAME_INDEX_PAIR(SM_CYDLGFRAME),
	NAME_INDEX_PAIR(SM_CXICON),
	NAME_INDEX_PAIR(SM_CYICON),
	NAME_INDEX_PAIR(SM_CYMENU),
	NAME_INDEX_PAIR(SM_MOUSEPRESENT),
	NAME_INDEX_PAIR(SM_CYVSCROLL),
	NAME_INDEX_PAIR(SM_CXHSCROLL),
	NAME_INDEX_PAIR(SM_DEBUG),
	NAME_INDEX_PAIR(SM_CXDOUBLECLK),
	NAME_INDEX_PAIR(SM_CYDOUBLECLK),
	NAME_INDEX_PAIR(SM_CXICONSPACING),
	NAME_INDEX_PAIR(SM_CYICONSPACING),
	NAME_INDEX_PAIR(SM_CXEDGE),
	NAME_INDEX_PAIR(SM_CYEDGE),
	NAME_INDEX_PAIR(SM_CXSMICON),
	NAME_INDEX_PAIR(SM_CYSMICON),
	NAME_INDEX_PAIR(SM_CXFIXEDFRAME),
	NAME_INDEX_PAIR(SM_CYFIXEDFRAME)
};

static const SNameIndexPair  g_SysColorsTable[] =
{
	NAME_INDEX_PAIR(COLOR_SCROLLBAR),
	NAME_INDEX_PAIR(COLOR_BACKGROUND),
	NAME_INDEX_PAIR(COLOR_ACTIVECAPTION),
	NAME_INDEX_PAIR(COLOR_INACTIVECAPTION),
	NAME_INDEX_PAIR(COLOR_MENU),
	NAME_INDEX_PAIR(COLOR_WINDOW),
	NAME_INDEX_PAIR(COLOR_WINDOWFRAME),
	NAME_INDEX_PAIR(COLOR_MENUTEXT),
	NAME_INDEX_PAIR(COLOR_WINDOWTEXT),
	NAME_INDEX_PAIR(COLOR_CAPTIONTEXT),
	NAME_INDEX_PAIR(COLOR_ACTIVEBORDER),
	NAME_INDEX_PAIR(COLOR_INACTIVEBORDER),
	NAME_INDEX_PAIR(COLOR_APPWORKSPACE),
	NAME_INDEX_PAIR(COLOR_HIGHLIGHT),
	NAME_INDEX_PAIR(COLOR_HIGHLIGHTTEXT),
	NAME_INDEX_PAIR(COLOR_BTNFACE),
	NAME_INDEX_PAIR(COLOR_BTNSHADOW),
	NAME_INDEX_PAIR(COLOR_GRAYTEXT),
	NAME_INDEX_PAIR(COLOR_BTNTEXT),
	NAME_INDEX_PAIR(COLOR_INACTIVECAPTIONTEXT),
	NAME_INDEX_PAIR(COLOR_BTNHIGHLIGHT),
	NAME_INDEX_PAIR(COLOR_3DDKSHADOW),
	NAME_INDEX_PAIR(COLOR_3DLIGHT),
	NAME_INDEX_PAIR(COLOR_INFOTEXT),
	NAME_INDEX_PAIR(COLOR_INFOBK),
	NAME_INDEX_PAIR(COLOR_STATIC),
	NAME_INDEX_PAIR(COLOR_STATICTEXT),
	NAME_INDEX_PAIR(COLOR_DESKTOP),
	NAME_INDEX_PAIR(COLOR_3DFACE),
	NAME_INDEX_PAIR(COLOR_3DSHADOW),
	NAME_INDEX_PAIR(COLOR_3DHIGHLIGHT),
	NAME_INDEX_PAIR(COLOR_3DHILIGHT)
};

//------------------------------------------------------
// Local Support Functions
//------------------------------------------------------

static LPCTSTR StringFromResources(
    UINT uStringID
    )
{
    // NOTE: Passing NULL for the 3rd parameter of LoadString causes it to
    // return a pointer to the string in the resource file. It requires that 
    // the resource file is compiled with the "/n" switch (see SDK docs).
    return (LPCTSTR) LoadString(g_hInst, uStringID, NULL, 0);
}

static void Clear(
    )
{
	Edit_SetText(g_hwndChild, TEXT(""));
}

static void OutputString(
    LPCTSTR lptszBuffer
    )
{
	Edit_SetSel(g_hwndChild, Edit_GetTextLength(g_hwndChild), Edit_GetTextLength(g_hwndChild));
	Edit_ReplaceSel(g_hwndChild, lptszBuffer);
}

static void OutputResource(
    UINT uResourceID
    )
{
	OutputString(StringFromResources(uResourceID));
}

static void OutputTitle(
    UINT uResourceID
    )
{
	OutputString(TEXT("\r\n\r\n"));
	OutputResource(uResourceID);
	OutputString(TEXT(":\r\n"));
}

static void OutputFormattedString(
    LPCTSTR tszFormat,
    ...
    )
{
    TCHAR tszBuffer[MAX_PATH];
    va_list vaMarker;

    va_start(vaMarker, tszFormat);
    FormatMessage(FORMAT_MESSAGE_FROM_STRING, tszFormat, 0, 0, tszBuffer, 
        ARRAY_SIZE(tszBuffer), &vaMarker);
    va_end(vaMarker);

    OutputString(tszBuffer);
}



//------------------------------------------------------
// Local Functions
//------------------------------------------------------
static void ShowCPUInfo(
    WORD wProcessorArchitecture, 
    WORD wProcessorLevel,
    WORD wProcessorRevision
    )
{
	const TCHAR *lptszCPUArch;
	const TCHAR *lptszCPULevel;
	const TCHAR *lptszCPURev;
	const TCHAR *lptszUnknown;

	lptszUnknown = StringFromResources(IDS_UNKNOWN);
	lptszCPULevel = lptszUnknown;
	lptszCPURev = lptszUnknown;
	
    switch(wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_ARM:
        lptszCPUArch = TEXT("ARM"); 
        break;
        
    case PROCESSOR_ARCHITECTURE_INTEL: 
        lptszCPUArch = TEXT("INTEL"); 
        
        switch(wProcessorLevel)
        {
        case 4:
            lptszCPULevel = TEXT("80486");
            break;
        case 5:
            lptszCPULevel = TEXT("Pentium");
            break;
        case 6:
            lptszCPULevel = TEXT("Pentium Pro");
            break;
        }
        break;
        
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
    default:
        lptszCPUArch = lptszUnknown;
        break;
    }
    
	OutputString(TEXT("wProcessorArchitecture: "));
	OutputString(lptszCPUArch);
	OutputResource(IDS_PROCESSOR_ARCHITECTURE);
	
	OutputString(TEXT("wProcessorLevel: "));
	OutputString(lptszCPULevel);
	OutputResource(IDS_PROCESSOR_LEVEL);
	
	OutputString(TEXT("wProcessorRevision: "));
	OutputString(lptszCPURev);
	OutputResource(IDS_PROCESSOR_REVISION);
}


//void GetSystemInfo(LPSYSTEM_INFO lpSystemInfo); 
static void ShowGetSystemInfo(
    )
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	
	OutputTitle(IDS_TITLE_SYSTEMINFO);
	
	OutputFormattedString(TEXT("dwPageSize: %1!lu!\r\n"), (ULONG)si.dwPageSize);
	OutputResource(IDS_PAGE_SIZE);
	
	OutputFormattedString(TEXT("lpMinimumAppAddr: 0x%1!p!\r\n"), si.lpMinimumApplicationAddress);
	OutputResource(IDS_MINIMUM_ADDRESS);
	
	OutputFormattedString(TEXT("lpMaximumAppAddr: 0x%1!p!\r\n"), si.lpMaximumApplicationAddress);
	OutputResource(IDS_MAXIMUM_ADDRESS);
	
	OutputFormattedString(TEXT("dwActiveProcessorMask: %1!lu!\r\n"), (ULONG)si.dwActiveProcessorMask);
	OutputResource(IDS_ACTIVE_PROCESSOR_MASK);

	OutputFormattedString(TEXT("dwNumberOfProcessors: %1!lu!\r\n"), (ULONG)si.dwNumberOfProcessors);
	OutputResource(IDS_NUMBER_OF_PROCESSORS);
	 
    switch(si.dwProcessorType)
    {
    case PROCESSOR_INTEL_486:
        OutputString(TEXT("dwProcessorType: 486 \r\n"));
        break;
    case PROCESSOR_INTEL_PENTIUM:
        OutputString(TEXT("dwProcessorType: Pentium \r\n"));
        break;
    case PROCESSOR_INTEL_PENTIUMII:
        OutputString(TEXT("dwProcessorType: Pentium II\r\n"));
        break;
    case PROCESSOR_STRONGARM:
        OutputString(TEXT("dwProcessorType: StrongARM\r\n"));
        break;
    case PROCESSOR_ARM720:
        OutputString(TEXT("dwProcessorType: ARM 720\r\n"));
        break;
    case PROCESSOR_ARM820:
        OutputString(TEXT("dwProcessorType: ARM 820\r\n"));
        break;
    case PROCESSOR_ARM920:
        OutputString(TEXT("dwProcessorType: ARM 920\r\n"));
        break;
    case PROCESSOR_ARM_7TDMI:
        OutputString(TEXT("dwProcessorType: ARM 7TDMI\r\n"));
        break;
    }

	OutputResource(IDS_PROCESSOR_TYPE);
	
	ShowCPUInfo(si.wProcessorArchitecture, si.wProcessorLevel, si.wProcessorRevision);
		
	OutputFormattedString(TEXT("dwAllocationGranularity: %1!lu!\r\n"),(ULONG)si.dwAllocationGranularity);
	OutputResource(IDS_ALLOCATION_GRANULARITY);
}


void ShowGetStoreInformation(
    )
{
	BOOL iRet;
	STORE_INFORMATION si;
	iRet = GetStoreInformation(&si);
	
	OutputTitle(IDS_TITLE_STOREINFO);
	
	OutputFormattedString(StringFromResources(IDS_RETURN_VALUE), iRet);
	
	OutputFormattedString(TEXT("dwStoreSize: %1!lu!\r\n"),(ULONG)si.dwStoreSize);
	OutputResource(IDS_STORE_SIZE);
	
	OutputFormattedString(TEXT("dwFreeSize: %1!lu!\r\n"),(ULONG)si.dwFreeSize);
	OutputResource(IDS_FREE_SIZE);
}


void ShowGlobalMemoryStatus(
    )
{
	MEMORYSTATUS st;
	GlobalMemoryStatus(&st);
	
	OutputTitle(IDS_TITLE_GLOBALMEMORYSTATUS);
	
	OutputFormattedString(TEXT("dwMemoryLoad: %1!lu!\r\n"), (ULONG)st.dwMemoryLoad);
	OutputResource(IDS_MEMORY_LOAD);

	OutputFormattedString(TEXT("dwTotalPhys: %1!lu!\r\n"), (ULONG)st.dwTotalPhys);
	OutputResource(IDS_TOTAL_PHYSICAL);
	
	OutputFormattedString(TEXT("dwTotalPageFile: %1!lu!\r\n"), (ULONG)st.dwTotalPageFile);
	OutputResource(IDS_TOTAL_PAGEFILE);
	
	OutputFormattedString(TEXT("dwAvailPageFile: %1!lu!\r\n"), (ULONG)st.dwAvailPageFile);
	OutputResource(IDS_AVAIL_PAGEFILE);
	
	OutputFormattedString(TEXT("dwTotalVirtual: %1!lu!\r\n"), (ULONG)st.dwTotalVirtual);
	OutputResource(IDS_TOTAL_VIRTUAL);
	
	OutputFormattedString(TEXT("dwAvailVirtual: %1!lu!\r\n"), (ULONG)st.dwAvailVirtual);
	OutputResource(IDS_AVAIL_VIRTUAL);
}

void ShowGetVersionEx(
    )
{
	BOOL iRet;
	OSVERSIONINFO vi;

	ZeroMemory(&vi, sizeof(vi));
	vi.dwOSVersionInfoSize = sizeof(vi);
	iRet = GetVersionEx(&vi);
	
	OutputTitle(IDS_TITLE_SYSTEMVERSION);
	
	OutputFormattedString(TEXT("dwMajorVersion: %1!lu!\r\n"), (ULONG)vi.dwMajorVersion);
	OutputResource(IDS_MAJOR_VERSION);
	
	OutputFormattedString(TEXT("dwMinorVersion: %1!lu!\r\n"), (ULONG)vi.dwMinorVersion);
	OutputResource(IDS_MINOR_VERSION);
	
	OutputFormattedString(TEXT("dwBuildNumber: %1!lu!\r\n"), (ULONG)vi.dwBuildNumber);
	OutputResource(IDS_BUILD_NUMBER);
	
	OutputFormattedString(TEXT("dwPlatformId: %1!lu!\r\n"), (ULONG)vi.dwPlatformId);
	OutputResource(IDS_PLATFORM_ID);

	OutputFormattedString(TEXT("szCSDVersion: %1!s!\r\n"), vi.szCSDVersion);
	OutputResource(IDS_SERVICE_PACK);
}




void ShowGetSystemMetrics(
    )
{
	unsigned i;
	
	OutputTitle(IDS_TITLE_SYSTEMMETRICS);

	for(i = 0; i < ARRAY_SIZE(g_SystemMetricTable); i++)
	{
		OutputFormattedString(TEXT("%1!s!: %2!d!\r\n"),
			g_SystemMetricTable[i].lptszName,
			GetSystemMetrics(g_SystemMetricTable[i].iIndex));
	}
}



void ShowGetSystemPowerStatusEx(
    )
{
	BOOL iRet;
	SYSTEM_POWER_STATUS_EX status;
	
	iRet = GetSystemPowerStatusEx(&status, TRUE);
	
	OutputTitle(IDS_TITLE_POWERSTATUS);

	OutputFormattedString(StringFromResources(IDS_RETURN_VALUE), iRet);
	OutputFormattedString(TEXT("ACLineStatus: %1!d!\r\n"), (INT)status.ACLineStatus);
	OutputFormattedString(TEXT("BatteryFlag: %1!d!\r\n"), (INT)status.BatteryFlag);
	OutputFormattedString(TEXT("BatteryLifePercent: %1!d!\r\n"), (INT)status.BatteryLifePercent);
	OutputFormattedString(TEXT("BatteryLifeTime: %1!lu!\r\n"), (ULONG)status.BatteryLifeTime);
	OutputFormattedString(TEXT("BatteryFullLifeTime: %1!lu!\r\n"), (ULONG)status.BatteryFullLifeTime);
	OutputFormattedString(TEXT("BackupBatteryFlag: %1!d!\r\n"), (INT)status.BackupBatteryFlag);
	OutputFormattedString(TEXT("BackupBatteryLifePercent: %1!d!\r\n"), (INT)status.BackupBatteryLifePercent);
	OutputFormattedString(TEXT("BackupBatteryLifeTime: %1!lu!\r\n"), (ULONG)status.BackupBatteryLifeTime);
	OutputFormattedString(TEXT("BackupBatteryFullLifeTime: %1!lu!\r\n"), (ULONG)status.BackupBatteryFullLifeTime);
	OutputResource(IDS_REFERENCE_LIFETIME);
}

static void ShowSysColors(
    )
{
    unsigned i;
    DWORD rgbColor;

	OutputTitle(IDS_TITLE_SYSCOLORS);

    SetLastError(ERROR_SUCCESS);
    for(i = 0; i < ARRAY_SIZE(g_SysColorsTable); i++) 
    {
        rgbColor = GetSysColor(g_SysColorsTable[i].iIndex);

        // A return value of 0 from GetSysColor might indicate failure, or it might
        // indicate that system color is set to black [RGB(0,0,0)]. We need to
        // check GetLastError() to be sure.
        if((0 != rgbColor) || (ERROR_SUCCESS == GetLastError())) 
        {
			OutputFormattedString(TEXT("%1!s!: %2!06lx!\r\n"), g_SysColorsTable[i].lptszName, rgbColor);
        } 
        else 
        {
			OutputFormattedString(TEXT("%1!s!: %2!s!\r\n"), g_SysColorsTable[i].lptszName, StringFromResources(IDS_FAILED));
        }
    }
}


static void OutputTime(
    const SYSTEMTIME* pcTime
    )
{
    ASSERT(pcTime != NULL);

    OutputFormattedString(TEXT("wYear: %1!d!\r\n"), pcTime->wYear);
    OutputFormattedString(TEXT("wMonth: %1!d!\r\n"), pcTime->wMonth);
    OutputFormattedString(TEXT("wDayOfWeek: %1!d!\r\n"), pcTime->wDayOfWeek);
    OutputFormattedString(TEXT("wDay: %1!d!\r\n"), pcTime->wDay);
    OutputFormattedString(TEXT("wHour: %1!d!\r\n"), pcTime->wHour);
    OutputFormattedString(TEXT("wMinute: %1!d!\r\n"), pcTime->wMinute);
    OutputFormattedString(TEXT("wSecond: %1!d!\r\n"), pcTime->wSecond);
    OutputFormattedString(TEXT("wMilliseconds: %1!d!\r\n"), pcTime->wMilliseconds);   
}


static void ShowLocalTime(
    )
{
    SYSTEMTIME  st;

    GetLocalTime(&st);

    OutputTitle(IDS_TITLE_GETLOCALTIME);
	OutputTime(&st);
}


static void ShowSystemTime(
    )
{
    SYSTEMTIME  st;

    GetSystemTime(&st);

    OutputTitle(IDS_TITLE_GETSYSTEMTIME);
    OutputTime(&st);
}



//------------------------------------------------------
//   MainWndProc
//------------------------------------------------------

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT Msg, WPARAM wp, LPARAM lp)
{
	LRESULT	lResult = TRUE;
	
	switch(Msg)
	{
		case WM_CREATE:
		{
			RECT rect;
			SHMENUBARINFO mbi;

			//Create a MenuBar
			ZeroMemory(&mbi, sizeof(mbi));
			mbi.cbSize     = sizeof(mbi);
			mbi.hwndParent = hwnd;
			mbi.nToolBarId = IDM_MAIN_MENU;
			mbi.hInstRes   = g_hInst;

			if(TRUE == SHCreateMenuBar(&mbi))
			{
				GetClientRect(hwnd, &rect);

				//Create an edit box the size of the parent window
				g_hwndChild = CreateWindow(TEXT("edit"), NULL,
                    WS_CHILD  | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,  
                    rect.left, rect.top,  rect.right,  rect.bottom, 
                    hwnd, (HMENU)ID_CHILD,  g_hInst, NULL);
				if(NULL != g_hwndChild)
				{
					ShowWindow(g_hwndChild, SW_SHOW);
					UpdateWindow(g_hwndChild);

					//Now show the information
					PostMessage(hwnd, WM_COMMAND, MAKELONG(IDM_VIEW_TEST, 0), 0);
					break;
				}
			}

			MessageBox(hwnd,
				StringFromResources(IDS_ERROR_WINDOW_FAILED),
				StringFromResources(IDS_CAPTION_ERROR),
				MB_OK | MB_ICONERROR);

			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
		    break;
			
		case WM_COMMAND:
			switch(GET_WM_COMMAND_ID(wp, lp))
			{
			case IDM_VIEW_TEST:
				Clear();
				ShowGetSystemPowerStatusEx();
				ShowGetStoreInformation();
				ShowGetSystemInfo();
				ShowGetVersionEx();
				ShowGlobalMemoryStatus();
				ShowGetSystemMetrics();
				ShowSysColors();
				ShowLocalTime();
				ShowSystemTime();

				SetFocus(g_hwndChild);
				break;
				
			case IDM_MAIN_MENUITEM2:
				DestroyWindow(hwnd);
				break;

			default:
				lResult = DefWindowProc(hwnd, Msg, wp, lp);
				break;
			}
			break;
			
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_ACTIVATE:
			if(wp)
			{
				SetFocus(g_hwndChild);
			}
			
			//Drop through
		default:
			lResult = DefWindowProc(hwnd, Msg, wp, lp);
			break;
	}

	return lResult;
}


//------------------------------------------------------
//  InitInstance
//------------------------------------------------------

BOOL InitInstance(HINSTANCE hInstance, int CmdShow)
{
	HWND hWndMain;

	g_hInst = hInstance;
	
    hWndMain = CreateWindow(tszAppName, tszTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, NULL, hInstance, NULL);

	if(NULL == hWndMain)		
    {
		return FALSE;
    }

	ShowWindow(hWndMain, CmdShow);
	UpdateWindow(hWndMain);

	return TRUE;
}



//------------------------------------------------------
//   InitApplication
//------------------------------------------------------

BOOL InitApplication(
    HINSTANCE hInstance
    )
{
	WNDCLASS wc;
	
	InitCommonControls();
	
	wc.style = CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = NULL;                                              // No cursor if target is not NT
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = tszAppName;
	
	return RegisterClass(&wc);
}


//------------------------------------------------------
//  WinMain
//------------------------------------------------------

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance, 
    LPTSTR lpCmdLine, 
    int CmdShow
    )
{
	MSG Msg;
	HWND hWndPrevious;

	//Check to see if app is running then pop to foreground
	hWndPrevious = FindWindow(tszAppName, tszTitle);	
	if(NULL != hWndPrevious) 
	{
		SetForegroundWindow((HWND)(((ULONG)hWndPrevious) | 0x01));    
		return 0;
	}

	if(FALSE == InitApplication(hInstance))
    {
	    return FALSE; 
    }

	if(FALSE == InitInstance(hInstance, CmdShow))
    {
		return FALSE;
    }

	while(GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
