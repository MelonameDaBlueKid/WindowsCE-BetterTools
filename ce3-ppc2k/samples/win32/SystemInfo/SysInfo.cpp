/*-------------------------------------------------------------------*\
Module: SysInfo.cpp

\*-------------------------------------------------------------------*/

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commctrl.h>

/// 
/**********************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

**********************************************************************/
/////////////////////////// Rapier only samples ///////////////////////
#if _WIN32_WCE < 212//non-Rapier devices
#error 'This sample works on Rapier devices only'
#endif
#include <aygshell.h>

//Menu Bar Height
#define MENU_HEIGHT 26

////////////////////////// SHGetMenu Macro's
#if _WIN32_WCE > 211 //Rapier devices

//#define SHCMBM_SETSUBMENU   (WM_USER + 400)
//#define SHCMBM_GETSUBMENU   (WM_USER + 401) // lParam == ID
//#define SHCMBM_GETMENU      (WM_USER + 402) // get the owning hmenu (as specified in the load resource)

#define SHGetMenu(hWndMB)  (HMENU)SendMessage((hWndMB), SHCMBM_GETMENU, (WPARAM)0, (LPARAM)0);
#define SHGetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);
#define SHSetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_SETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

//Alternate definition
#define SHMenuBar_GetMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

#else //non-Rapier devices

#define SHGetMenu(hWndCB) (HMENU)CommandBar_GetMenu(hWndCB, 0)
#define SHGetSubMenu(hWndCB,ID_MENU) (HMENU)GetSubMenu((HMENU)CommandBar_GetMenu(hWndCB, 0), ID_MENU)
#define SHSetSubMenu(hWndMB,ID_MENU)

#endif
/// end 


#include "resource.h"
#include "resrc1.h"


//------------------------------------------------------
// Globals
//------------------------------------------------------


HINSTANCE g_hInst = NULL;  // Local copy of hInstance, used in Commandbar_Create & Commandbar_InsertMenubar
HWND      g_hwndMain = NULL;    // Handle to Main window returned from CreateWindow
HWND			g_hwndCBr =NULL;       // Handle to a commandband
HMENU			g_hMenu =NULL;       // Handle to a commandbar0 menu
HWND			g_hwndChild = NULL;    // Handle to Main window returned from CreateWindow
HWND			g_hCommandCombo = NULL;
UINT			g_nCBrHeight = 0;

TCHAR szAppName[] = TEXT("SysInfo Application");
TCHAR szTitle[]   = TEXT("SysInfo");

TCHAR szTextChild[] = TEXT("TEXTChild");
BOOL iRet = FALSE;

//------------------------------------------------------
// Forward Declares
//------------------------------------------------------

BOOL CALLBACK  AboutDlgProc(HWND, WORD, WORD, LONG);

//------------------------------------------------------
// Local Support Functions
//------------------------------------------------------

void Clear()
{
	Edit_SetText(g_hwndChild,TEXT(""));
}

void OutputString(LPTSTR lptBuffer)
{
	Edit_SetSel(g_hwndChild, Edit_GetTextLength(g_hwndChild), Edit_GetTextLength(g_hwndChild));
	Edit_ReplaceSel(g_hwndChild, lptBuffer);
}

void OutputStringAtPos(LPTSTR lptBuffer, int iPos)
{
	Edit_SetSel(g_hwndChild, iPos, iPos);
	Edit_ReplaceSel(g_hwndChild, lptBuffer);
}

void OutputStringAtCurrentPos(LPTSTR lptBuffer)
{
	Edit_ReplaceSel(g_hwndChild, lptBuffer);
}

//------------------------------------------------------
// Local Functions
//------------------------------------------------------
void ShowCPUInfo (WORD wProcessorArchitecture, WORD wProcessorLevel, WORD wProcessorRevision){
	TCHAR szBufW[MAX_PATH];
	TCHAR szCPUArch[64];
	TCHAR szCPULevel[64];
	TCHAR szCPURev[64];
	szCPULevel[0] = 0;
	szCPURev[0] = 0;
	
	switch (wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_INTEL: 
		lstrcpy(szCPUArch, __TEXT("INTEL")); 
		switch (wProcessorLevel) {
		case 3: case 4:
			wsprintf(szCPULevel, __TEXT("80%c86"), wProcessorLevel + '0');
			lstrcpy(szCPURev, __TEXT("(unknown)"));
			break;
		case 5:
			wsprintf(szCPULevel, __TEXT("Pentium"));
			lstrcpy(szCPURev, __TEXT("(unknown)"));
			break;
		case 6:
			wsprintf(szCPULevel, __TEXT("Pentium Pro"));
			lstrcpy(szCPURev, __TEXT("(unknown)"));
			break;
		}
		break;
		
		case PROCESSOR_ARCHITECTURE_MIPS:  
			lstrcpy(szCPUArch, __TEXT("MIPS")); 
			wsprintf(szCPULevel, __TEXT("R%04d"), LOBYTE(wProcessorLevel) * 1000);
			wsprintf(szCPURev, __TEXT("%d"), LOBYTE(wProcessorRevision));
			break;
			
		case PROCESSOR_ARCHITECTURE_ALPHA: 
			lstrcpy(szCPUArch, __TEXT("ALPHA"));
			wsprintf(szCPULevel, __TEXT("%d"), wProcessorLevel);
			wsprintf(szCPURev, __TEXT("Model %c, Pass %d"), 
				HIBYTE(wProcessorRevision) + __TEXT('A'), 
				LOBYTE(wProcessorRevision));
			break;
			
		case PROCESSOR_ARCHITECTURE_PPC:   
			lstrcpy(szCPUArch, __TEXT("PPC"));
			switch (wProcessorLevel) {
			case 1: case 3: case 4: case 20:
				wsprintf(szCPULevel, __TEXT("%d"), 
					600 + wProcessorLevel);
				break;
			case 6:
				wsprintf(szCPULevel, __TEXT("603+"), 
					wProcessorLevel);
				break;
			case 9:
				wsprintf(szCPULevel, __TEXT("604+"), 
					wProcessorLevel);
				break;
			}
			wsprintf(szCPURev, __TEXT("%d.%d"), 
				HIBYTE(wProcessorRevision), 
				LOBYTE(wProcessorRevision));
			break;
      
      case PROCESSOR_ARCHITECTURE_UNKNOWN:
      default:
				wsprintf(szCPUArch, __TEXT("Unknown"));
				break;
	}
	
	wsprintf(szBufW,TEXT("wProcessorLevel: %s \r\n"),szCPUArch);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the system's processor architecture.\r\n")); 
	
	wsprintf(szBufW,TEXT("wProcessorLevel: %s \r\n"),szCPULevel);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the system's architecture-dependent processor level.\r\n")); 
	
	wsprintf(szBufW,TEXT("wProcessorRevision: %s \r\n"),szCPURev );
	OutputString(szBufW);
	OutputString(TEXT("    Specifies an architecture-dependent processor revision. \r\n")); 
}

void ShowGetStoreInformation()
{
	TCHAR szBufW[MAX_PATH];
/*
typedef struct STORE_INFORMATION {
DWORD dwStoreSize;
DWORD dwFreeSize;
} STORE_INFORMATION, *LPSTORE_INFORMATION;
	*/
	STORE_INFORMATION si;
	iRet = GetStoreInformation(&si);
	
	wsprintf(szBufW,TEXT("\r\nStore Info: \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("Return Value: %d \r\n"), iRet);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("dwStoreSize: %lu \r\n"),(ULONG)si.dwStoreSize);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the size, in bytes, of the object store.\r\n")); 
	wsprintf(szBufW,TEXT("dwFreeSize: %lu \r\n"),(ULONG)si.dwFreeSize);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the amount of free space, in bytes, in the object store.\r\n")); 
	
}
//void GetSystemInfo(LPSYSTEM_INFO lpSystemInfo); 
void ShowGetSystemInfo()
{
	TCHAR szBufW[MAX_PATH];
/*
typedef struct _SYSTEM_INFO {
DWORD dwOemId;
DWORD dwPageSize;
LPVOID lpMinimumApplicationAddress;
LPVOID lpMaximumApplicationAddress;
DWORD dwActiveProcessorMask;
DWORD dwNumberOfProcessors;
DWORD dwProcessorType;
DWORD dwAllocationGranularity;
DWORD dwReserved;
} SYSTEM_INFO, *LPSYSTEM_INFO;*/
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	
	wsprintf(szBufW,TEXT("\r\nSystem Info: \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("dwPageSize: %lu \r\n"),(ULONG)si.dwPageSize);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the page size and the granularity of page protection and commitment. This is the page size used by the VirtualAlloc function.\r\n")); 
	wsprintf(szBufW,TEXT("lpMinimumAppAddr: %lu \r\n"),(ULONG)si.lpMinimumApplicationAddress);
	OutputString(szBufW);
	OutputString(TEXT("    Pointer to the lowest memory address accessible to applications and dynamic-link libraries (DLLs). \r\n")); 
	wsprintf(szBufW,TEXT("lpMaximumAppAddr: %lu \r\n"),(ULONG)si.lpMaximumApplicationAddress);
	OutputString(szBufW);
	OutputString(TEXT("    Pointer to the highest memory address accessible to applications and DLLs. \r\n")); 
	wsprintf(szBufW,TEXT("dwActiveProcessorMask: %lu \r\n"),(ULONG)si.dwActiveProcessorMask);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies a mask representing the set of processors configured into the system. Bit 0 is processor 0; bit 31 is processor 31. \r\n")); 
	wsprintf(szBufW,TEXT("dwNumberOfProcessors: %lu \r\n"),(ULONG)si.dwNumberOfProcessors);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the number of processors in the system. \r\n"));
	 
	switch (si.dwProcessorType)
	{
		case PROCESSOR_INTEL_386:
			OutputString(TEXT("dwProcessorType: 386 \r\n"));
			break;
		case PROCESSOR_INTEL_486:
			OutputString(TEXT("dwProcessorType: 486 \r\n"));
			break;
		case PROCESSOR_INTEL_PENTIUM:
			OutputString(TEXT("dwProcessorType: Pentium \r\n"));
			break;
		case PROCESSOR_MIPS_R4000:
			OutputString(TEXT("dwProcessorType: R4000 \r\n"));
			break;
		case PROCESSOR_ALPHA_21064:
			OutputString(TEXT("dwProcessorType: 21064 \r\n"));
			break;
	}
	OutputString(TEXT("    Specifies the type of processor in the system.\r\n")); 
	
	ShowCPUInfo (si.wProcessorArchitecture, si.wProcessorLevel, si.wProcessorRevision);
		
	wsprintf(szBufW,TEXT("dwAllocationGranularity: %lu \r\n"),(ULONG)si.dwAllocationGranularity);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies the granularity with which virtual memory is allocated.\r\n")); 
	
}
//void GlobalMemoryStatus(LPMEMORYSTATUS lpmst);
void ShowGlobalMemoryStatus()
{
	TCHAR szBufW[MAX_PATH];
	
/*
typedef struct _MEMORYSTATUS { // mst 
DWORD dwLength;        // sizeof(MEMORYSTATUS) 
DWORD dwMemoryLoad;    // percent of memory in use 
DWORD dwTotalPhys;     // bytes of physical memory 
DWORD dwAvailPhys;     // free physical memory bytes 
DWORD dwTotalPageFile; // bytes of paging file 
DWORD dwAvailPageFile; // free bytes of paging file 
DWORD dwTotalVirtual;  // user bytes of address space 
DWORD dwAvailVirtual;  // free user bytes } MEMORYSTATUS, *LPMEMORYSTATUS;  
	*/
	MEMORYSTATUS st;
	GlobalMemoryStatus(&st);
	
	wsprintf(szBufW,TEXT("\r\nGlobal Memory Status: \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("dwMemoryLoad: %lu \r\n"),(ULONG)st.dwMemoryLoad);
	OutputString(szBufW);
	OutputString(TEXT("    Specifies a number between 0 and 100 that gives a general idea of current memory utilization, in which 0 indicates no memory use and 100 indicates full memory use. \r\n"));
	wsprintf(szBufW,TEXT("dwTotalPhys: %lu \r\n"),(ULONG)st.dwTotalPhys);
	OutputString(szBufW);
	OutputString(TEXT("    Indicates the total number of bytes of physical memory. \r\n"));
	wsprintf(szBufW,TEXT("dwTotalPageFile: %lu \r\n"),(ULONG)st.dwTotalPageFile);
	OutputString(szBufW);
	OutputString(TEXT("    Indicates the number of bytes of physical memory available.\r\n"));
	wsprintf(szBufW,TEXT("dwAvailPageFile: %lu \r\n"),(ULONG)st.dwAvailPageFile);
	OutputString(szBufW);
	OutputString(TEXT("    Indicates the total number of bytes that can be stored in the paging file.  \r\n"));
	wsprintf(szBufW,TEXT("dwTotalVirtual: %lu \r\n"),(ULONG)st.dwTotalVirtual);
	OutputString(szBufW);
	OutputString(TEXT("    Indicates the total number of bytes that can be described in the user mode portion of the virtual address space of the calling process.\r\n"));
	wsprintf(szBufW,TEXT("dwAvailVirtual: %lu \r\n"),(ULONG)st.dwAvailVirtual);
	OutputString(szBufW);
	OutputString(TEXT("    Indicates the number of bytes of unreserved and uncommitted memory in the user mode portion of the virtual address space of the calling process\r\n"));
	
}
//BOOL GetVersionEx(LPOSVERSIONINFO lpVersionInformation); 
void ShowGetVersionEx()
{
	TCHAR szBufW[MAX_PATH];
/*
typedef struct _OSVERSIONINFO{ 
DWORD dwOSVersionInfoSize; 
DWORD dwMajorVersion; 
DWORD dwMinorVersion; 
DWORD dwBuildNumber; 
DWORD dwPlatformId; 
TCHAR szCSDVersion[ 128 ]; 
} OSVERSIONINFO; 
*/
	OSVERSIONINFO vi;
	memset(&vi, 0, sizeof(OSVERSIONINFO));
	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	iRet = GetVersionEx(&vi);
	
	wsprintf(szBufW,TEXT("\r\nSystem Version Info: \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("dwMajorVersion: %lu \r\n"),(ULONG)vi.dwMajorVersion);
	OutputString(szBufW);
	OutputString(TEXT("    Identifies the major version number of the operating system.  \r\n"));
	wsprintf(szBufW,TEXT("dwMinorVersion: %lu \r\n"),(ULONG)vi.dwMinorVersion);
	OutputString(szBufW);
	OutputString(TEXT("    Identifies the minor version number of the operating system.  \r\n"));
	wsprintf(szBufW,TEXT("dwBuildNumber: %lu \r\n"),(ULONG)vi.dwBuildNumber);
	OutputString(szBufW);
	OutputString(TEXT("    Identifies the build number of the operating system.  \r\n"));
	wsprintf(szBufW,TEXT("dwPlatformId: %lu \r\n"), (ULONG)vi.dwPlatformId);
	OutputString(szBufW);
	OutputString(TEXT("    Identifies the platformID.  \r\n"));
	wsprintf(szBufW,TEXT("szCSDVersion: %s \r\n"), vi.szCSDVersion);
	OutputString(szBufW);
	OutputString(TEXT("    Indicates the latest Service Pack installed on the system.  \r\n"));

}

//int GetSystemMetrics(int nIndex); 
void ShowGetSystemMetrics()
{
	TCHAR szBufW[MAX_PATH];
	
	wsprintf(szBufW,TEXT("\r\nSystem Metrics: \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("SM_CXSCREEN: %d \r\n"),(INT)GetSystemMetrics(SM_CXSCREEN));
	OutputString(szBufW);
	//#define SM_CYSCREEN             1
	wsprintf(szBufW,TEXT("SM_CYSCREEN: %d \r\n"),(INT)GetSystemMetrics(SM_CYSCREEN));
	OutputString(szBufW);
	//#define SM_CXVSCROLL            2
	wsprintf(szBufW,TEXT("SM_CXVSCROLL: %d \r\n"),(INT)GetSystemMetrics(SM_CXVSCROLL));
	OutputString(szBufW);
	//#define SM_CYHSCROLL            3
	wsprintf(szBufW,TEXT("SM_CYHSCROLL: %d \r\n"),(INT)GetSystemMetrics(SM_CYHSCROLL));
	OutputString(szBufW);
	//#define SM_CYCAPTION            4
	wsprintf(szBufW,TEXT("SM_CYCAPTION: %d \r\n"),(INT)GetSystemMetrics(SM_CYCAPTION));
	OutputString(szBufW);
	//#define SM_CXBORDER             5
	wsprintf(szBufW,TEXT("SM_CXBORDER: %d \r\n"),(INT)GetSystemMetrics(SM_CXBORDER));
	OutputString(szBufW);
	//#define SM_CYBORDER             6
	wsprintf(szBufW,TEXT("SM_CYBORDER: %d \r\n"),(INT)GetSystemMetrics(SM_CYBORDER));
	OutputString(szBufW);
	//#define SM_CXDLGFRAME           7
	wsprintf(szBufW,TEXT("SM_CXDLGFRAME: %d \r\n"),(INT)GetSystemMetrics(SM_CXDLGFRAME));
	OutputString(szBufW);
	//#define SM_CYDLGFRAME           8
	wsprintf(szBufW,TEXT("SM_CYDLGFRAME: %d \r\n"),(INT)GetSystemMetrics(SM_CYDLGFRAME));
	OutputString(szBufW);
	//#define SM_CXICON               11
	wsprintf(szBufW,TEXT("SM_CXICON: %d \r\n"),(INT)GetSystemMetrics(SM_CXICON));
	OutputString(szBufW);
	//#define SM_CYICON               12
	wsprintf(szBufW,TEXT("SM_CYICON: %d \r\n"),(INT)GetSystemMetrics(SM_CYICON));
	OutputString(szBufW);
	//#define SM_CYMENU               15
	wsprintf(szBufW,TEXT("SM_CYMENU: %d \r\n"),(INT)GetSystemMetrics(SM_CYMENU));
	OutputString(szBufW);
	//#define SM_MOUSEPRESENT         19
	wsprintf(szBufW,TEXT("SM_MOUSEPRESENT: %d \r\n"),(INT)GetSystemMetrics(SM_MOUSEPRESENT));
	OutputString(szBufW);
	//#define SM_CYVSCROLL            20
	wsprintf(szBufW,TEXT("SM_CYVSCROLL: %d \r\n"),(INT)GetSystemMetrics(SM_CYVSCROLL));
	OutputString(szBufW);
	//#define SM_CXHSCROLL            21
	wsprintf(szBufW,TEXT("SM_CXHSCROLL: %d \r\n"),(INT)GetSystemMetrics(SM_CXHSCROLL));
	OutputString(szBufW);
	//#define SM_DEBUG                22
	wsprintf(szBufW,TEXT("SM_DEBUG: %d \r\n"),(INT)GetSystemMetrics(SM_DEBUG));
	OutputString(szBufW);
	//#define SM_CXDOUBLECLK          36
	wsprintf(szBufW,TEXT("SM_CXDOUBLECLK: %d \r\n"),(INT)GetSystemMetrics(SM_CXDOUBLECLK));
	OutputString(szBufW);
	//#define SM_CYDOUBLECLK          37
	wsprintf(szBufW,TEXT("SM_CYDOUBLECLK: %d \r\n"),(INT)GetSystemMetrics(SM_CYDOUBLECLK));
	OutputString(szBufW);
	//#define SM_CXICONSPACING        38
	wsprintf(szBufW,TEXT("SM_CXICONSPACING: %d \r\n"),(INT)GetSystemMetrics(SM_CXICONSPACING));
	OutputString(szBufW);
	//#define SM_CYICONSPACING        39
	wsprintf(szBufW,TEXT("SM_CYICONSPACING: %d \r\n"),(INT)GetSystemMetrics(SM_CYICONSPACING));
	OutputString(szBufW);
	//#define SM_CXEDGE               45
	wsprintf(szBufW,TEXT("SM_CXEDGE: %d \r\n"),(INT)GetSystemMetrics(SM_CXEDGE));
	OutputString(szBufW);
	//#define SM_CYEDGE               46
	wsprintf(szBufW,TEXT("SM_CYEDGE: %d \r\n"),(INT)GetSystemMetrics(SM_CYEDGE));
	OutputString(szBufW);
	//#define SM_CXSMICON             49
	wsprintf(szBufW,TEXT("SM_CXSMICON: %d \r\n"),(INT)GetSystemMetrics(SM_CXSMICON));
	OutputString(szBufW);
	//#define SM_CYSMICON             50
	wsprintf(szBufW,TEXT("SM_CYSMICON: %d \r\n"),(INT)GetSystemMetrics(SM_CYSMICON));
	OutputString(szBufW);
	//#define SM_CXFIXEDFRAME         SM_CXDLGFRAME
	wsprintf(szBufW,TEXT("SM_CXFIXEDFRAME: %d \r\n"),(INT)GetSystemMetrics(SM_CXFIXEDFRAME));
	OutputString(szBufW);
	//#define SM_CYFIXEDFRAME         SM_CYDLGFRAME
	wsprintf(szBufW,TEXT("SM_CYFIXEDFRAME: %d \r\n"),(INT)GetSystemMetrics(SM_CYFIXEDFRAME));
	OutputString(szBufW);
	
}
void ShowGetSystemPowerStatusEx()
{
	TCHAR szBufW[MAX_PATH];
#ifndef _WIN32_WCE_EMULATION
	
	/*
  SYSTEM_POWER_STATUS_EX
  The SYSTEM_POWER_STATUS_EX structure contains information about the 
  power status of the system.
	
		Syntax
		typedef struct _SYSTEM_POWER_STATUS_EX {
		BYTE ACLineStatus;
		BYTE BatteryFlag;
		BYTE BatteryLifePercent;
		BYTE Reserved1;
		DWORD BatteryLifeTime;
		DWORD BatteryFullLifeTime;
		BYTE Reserved2;
		BYTE BackupBatteryFlag;
		BYTE BackupBatteryLifePercent;
		BYTE Reserved3;
		DWORD BackupBatteryLifeTime;
		DWORD BackupBatteryFullLifeTime;
		} SYSTEM_POWER_STATUS_EX, *PSYSTEM_POWER_STATUS_EX, *LPSYSTEM_POWER_STATUS_EX;
	*/
	SYSTEM_POWER_STATUS_EX status;
	
	/*
  GetSystemPowerStatusEx
  The GetSystemPowerStatusEx function retrieves the power status of the system. 
  /The status indicates whether the system is running on AC or DC power, 
  whether or not the batteries are currently charging, and the remaining life 
  of main and backup batteries.
	
		Syntax
		BOOL GetSystemPowerStatusEx(PSYSTEM_POWER_STATUS_EX pstatus, BOOL fUpdate);
	*/
  
	iRet = GetSystemPowerStatusEx(&status, TRUE);
	
	wsprintf(szBufW,TEXT("\r\nPowerStatus \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("Return Value: %d \r\n"), iRet);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("ACLineStatus: %d \r\n"),(INT)status.ACLineStatus);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BatteryFlag: %d \r\n"),(INT)status.BatteryFlag);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BatteryLifePercent: %d \r\n"),(INT)status.BatteryLifePercent);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BatteryLifeTime: %lu \r\n"),(ULONG)status.BatteryLifeTime);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BatteryFullLifeTime: %lu \r\n"),(ULONG)status.BatteryFullLifeTime);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BackupBatteryFlag: %d \r\n"),(INT)status.BackupBatteryFlag);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BackupBatteryLifePercent: %d \r\n"),(INT)status.BackupBatteryLifePercent);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BackupBatteryLifeTime: %lu \r\n"),(ULONG)status.BackupBatteryLifeTime);
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("BackupBatteryFullLifeTime: %lu \r\n"),(ULONG)status.BackupBatteryFullLifeTime);
	OutputString(szBufW);
	
	wsprintf(szBufW,TEXT("ReferenceLifeTime: %lu \r\n"),(ULONG)0xFFFFFFFF);
	OutputString(szBufW);
	
#else
	wsprintf(szBufW,TEXT("PowerStatus \r\n"));
	OutputString(szBufW);
	wsprintf(szBufW,TEXT("Not Supported in Emulation \r\n"));
	OutputString(szBufW);
#endif
}

//------------------------------------------------------
//   MainWndProc
//------------------------------------------------------

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
  LRESULT	lResult = TRUE;
	RECT    rect;
	
	switch(msg)
	{
		case WM_CREATE:
			{

//Create a MenuBar
       SHMENUBARINFO mbi;
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hwnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = g_hInst;
        mbi.nBmpId     = 0;
        mbi.cBmpImages = 0;	
        
        SHCreateMenuBar(&mbi);
      if (!SHCreateMenuBar(&mbi))
        MessageBox(hwnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
        g_hwndCBr = mbi.hwndMB;
        

				GetClientRect(hwnd, &rect);
				g_hwndChild = CreateWindow(TEXT("edit"),
										NULL,
										WS_CHILD  | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL	| ES_MULTILINE ,  
										rect.left, 
										rect.top, 
										rect.right, 
										rect.bottom, 
										hwnd,
										(HMENU)ID_CHILD, 
										g_hInst,
										NULL);
				if ( g_hwndChild )
				{
					ShowWindow(g_hwndChild, SW_SHOW);
					UpdateWindow(g_hwndChild);
				}
			}
			break;
			
		case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp))
			{
			case IDM_VIEW_TEST:
				Clear();
				ShowGetSystemPowerStatusEx();
				ShowGetStoreInformation();
				ShowGetSystemInfo();
				ShowGetVersionEx();
				ShowGlobalMemoryStatus();
				ShowGetSystemMetrics();
				break;
				
			default:
				return DefWindowProc(hwnd, msg, wp, lp);
			}
			break; //WM_COMMAND
			
			case WM_CLOSE:
				DestroyWindow(hwnd);
				break; //WM_CLOSE
				
			case WM_DESTROY:
				PostQuitMessage(0);
				break; //WM_DESTROY
				
			default:
				lResult = DefWindowProc(hwnd, msg, wp, lp);
				break;
	}
	return (lResult);
}


//------------------------------------------------------
//  InitInstance
//------------------------------------------------------


BOOL InitInstance (HINSTANCE hInstance, int CmdShow )
{
	
	g_hInst = hInstance;
	
		////////// Setting default main window size
	// This technique allows for you to create the main
	// window to allow for the postion of a menubar and/or
	// the SIP button at the bottom of the screen
	
	SIPINFO si = {0};
	//Set default window creation sizd info
	int iDelta, x = CW_USEDEFAULT, y = CW_USEDEFAULT, cx, cy;
	
	si.cbSize = sizeof(si);
	SHSipInfo(SPI_GETSIPINFO, 0, &si, 0);
		
	//Consider the menu at the bottom, please.
	iDelta = (si.fdwFlags & SIPF_ON) ? 0 : MENU_HEIGHT;
	cx = si.rcVisibleDesktop.right - si.rcVisibleDesktop.left;
	cy = si.rcVisibleDesktop.bottom - si.rcVisibleDesktop.top - iDelta;
		
				
	g_hwndMain = CreateWindow(szAppName, szTitle, WS_VISIBLE ,
		x, y, cx, cy, NULL, NULL, g_hInst, NULL);

	
	if ( !g_hwndMain )		
	{
		return FALSE;
	}
	ShowWindow(g_hwndMain, CmdShow );
	UpdateWindow(g_hwndMain);
	return TRUE;
}

//------------------------------------------------------
//   InitApplication
//------------------------------------------------------


BOOL InitApplication ( HINSTANCE hInstance )
{
	WNDCLASS wc;
	BOOL f;
	
  InitCommonControls();
	
	wc.style = CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//NULL;
	wc.hInstance = hInstance;
	wc.hCursor = NULL;                                              // No cursor if target is not NT
	wc.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	
	f = (RegisterClass(&wc));
	
	
	return f;
}

//------------------------------------------------------
//  WinMain
//------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int CmdShow)
{
	MSG msg;
	HWND hThisWnd = NULL;
	//Check to see if app is running then pop to foreground
	hThisWnd = FindWindow(szAppName, szTitle);	
	if (hThisWnd) 
	{
		SetForegroundWindow (hThisWnd);    
		return 0;
	}
	if ( !hPrevInstance )
	{
		if ( !InitApplication ( hInstance ) )
		{ 
			return (FALSE); 
		}
	}
	if ( !InitInstance( hInstance, CmdShow )  )
		return (FALSE);
	while ( GetMessage( &msg, NULL, 0,0 ) )
	{
		TranslateMessage (&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}
