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

//
// mybacklight.cpp
//

#include "myBackLight.h"



#define NUM_APPLETS		1
#define	ID_BATT			0
#define	ID_AC			1

//  The registry values pertaining to the backlight settings:
//
//  [HKEY_CURRENT_USER\ControlPanel\BackLight]
//		"BatteryTimeoutUnchecked"	; On Battery Power timeout, saved here when checkbox is unchecked, 0 otherwise (seconds)
//		"BatteryTimeout"			; On Battery Power timeout, saved here when checkbox is checked, 0 otherwise (seconds)
//		"ACTimeoutUnchecked"		; On AC Power timeout, saved here when checkbox is unchecked, 0 otherwise (seconds)
//		"ACTimeout"					; On AC Power timeout, saved here when checkbox is checked, 0 otherwise (seconds)
//		"BacklightOnTap"			; Whether to turn on backlight when user taps screen, when on battery power
//		"ACBacklightOnTap"			; As above, but when on AC Power
//
//	BacklightOnTap and ACBacklightOnTap are not demonstrated in this sample
//
#define REGKEY					TEXT("ControlPanel\\Backlight")
#define MYREGKEY				TEXT("ControlPanel\\MyBacklight")
#define BRIGHTNESS				TEXT("Brightness")
#define ACTIMEOUT				TEXT("ACTimeout")
#define ACTIMEOUTUNCHECKED		TEXT("ACTimeoutUnchecked")
#define BATTERYTIMEOUT			TEXT("BatteryTimeout")
#define BATTERYTIMEOUTUNCHECKED	TEXT("BatteryTimeoutUnchecked")

typedef enum tagRegistryOp
{
	eBrightness,
	eACPower,
	eBatt
} REGISTRYOP;

typedef struct tagApplets
{
    int icon;           // icon resource identifier
    int namestring;     // name-string resource identifier
    int descstring;     // description-string resource identifier
} APPLETS;

const APPLETS SystemApplets[] =
{
    {APPLET_ICON, APPLET_NAME, APPLET_DESC}
	// add more struct members here if supporting more than on applet
};


HINSTANCE	g_hInstance	= NULL;
BOOL CreatePropertySheet(HWND hWnd, int iApplet);

////////////////////////////////////////////////////////
//	DllMain
//
////////////////////////////////////////////////////////
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if (DLL_PROCESS_ATTACH == ul_reason_for_call)
		g_hInstance = (HINSTANCE)hModule;

    return TRUE;
}


////////////////////////////////////////////////////////
//	Do initialization, eg memory allocations, etc.
//  return TRUE if all OK and FALSE if applet shouldn't
//  be loaded
//
////////////////////////////////////////////////////////
BOOL InitApplet(HWND hwndParent)
{
    return TRUE;
}


////////////////////////////////////////////////////////
//	Do cleanup here
//  
////////////////////////////////////////////////////////
void TermApplet()
{
    return;
}

////////////////////////////////////////////////////////
//	This is the entry point called by ctlpnl.exe
//  
////////////////////////////////////////////////////////
extern "C"
__declspec(dllexport)
LONG WINAPI CPlApplet(HWND hwndCPL, UINT uMsg, LONG lParam1, LONG lParam2)
{
	static int		iInitCount = 0;
	int				iApplet;


    switch (uMsg)
	{
		// First message sent. It is sent only once to
		// allow the dll to initialize it's applet(s)
		case CPL_INIT:
			if (!iInitCount)
			{
				if (!InitApplet(hwndCPL))
					return FALSE;
			}
			iInitCount++;
			return TRUE;
			
		// Second message sent. Return the count of applets supported
		// by this dll
		case CPL_GETCOUNT:
			// Return the number of applets we support
			return (LONG)((sizeof(SystemApplets))/(sizeof(SystemApplets[0])));

		// Third message sent. Sent once for each applet supported by this dll.
		// The lParam1 contains the number that indicates which applet this is
		// for, from 0 to 1 less than the count of applets.
		// lParam2 is a NEWCPLINFO that should be filled with information about
		// this applet before returning
		case CPL_NEWINQUIRE:
			{
				LPNEWCPLINFO	lpNewCPlInfo;

				lpNewCPlInfo				= (LPNEWCPLINFO)lParam2;
				iApplet						= (int)lParam1;
				lpNewCPlInfo->dwSize		= (DWORD)sizeof(NEWCPLINFO);
				lpNewCPlInfo->dwFlags		= 0;
				lpNewCPlInfo->dwHelpContext	= 0;
				lpNewCPlInfo->lData			= SystemApplets[iApplet].icon;
				lpNewCPlInfo->hIcon			= LoadIcon(g_hInstance,(LPCTSTR)MAKEINTRESOURCE(SystemApplets[iApplet].icon));
				lpNewCPlInfo->szHelpFile[0]	= '\0';

				LoadString(g_hInstance,SystemApplets[iApplet].namestring,lpNewCPlInfo->szName,32);
				LoadString(g_hInstance,SystemApplets[iApplet].descstring,lpNewCPlInfo->szInfo,64);
			}

			break;

		// This is sent whenever the user clicks an icon in Settings for one of
		// the applets supported by this dll. lParam1 contains the number indicating
		// which applet. Return 0 if applet successfully launched, non-zero otherwise
		case CPL_DBLCLK:
			iApplet = (UINT)lParam1;
			if (!CreatePropertySheet(hwndCPL,iApplet))
				return 1;
			break;
			
		// Sent once per applet, before CPL_EXIT
		case CPL_STOP:
			break;
			
		// Sent once before the dll is unloaded
		case CPL_EXIT:
			iInitCount--;
			if (!iInitCount)
				TermApplet();
			break;
			
		default:
			break;
    }

    return 0;
}

////////////////////////////////////////////////////////
//	Called to retrieve the values corresponding to the
//  backlight stored in the registry. The necessary
//  registry values are described above
//
////////////////////////////////////////////////////////
HRESULT GetFromRegistry(REGISTRYOP eVal, DWORD *pdwValueChecked, DWORD *pdwValueUnchecked)
{
	HKEY	hKey;
	DWORD	dwSize;
	DWORD	dwType;
	HRESULT	hRes;

	TCHAR	*szRegistryKey;
	TCHAR	*szRegValue1;
	TCHAR	*szRegValue2;

	if (pdwValueChecked)
		*pdwValueChecked = 0;
	
	if (pdwValueUnchecked)
		*pdwValueUnchecked = 0;

	switch (eVal)
	{
		case eBrightness:
			szRegistryKey	= MYREGKEY;
			szRegValue1		= BRIGHTNESS;
			break;

		case eACPower:
			szRegistryKey	= REGKEY;
			szRegValue1		= ACTIMEOUT;
			szRegValue2		= ACTIMEOUTUNCHECKED;
			break;

		case eBatt:
			szRegistryKey	= REGKEY;
			szRegValue1		= BATTERYTIMEOUT;
			szRegValue2		= BATTERYTIMEOUTUNCHECKED;
			break;

		default:
			return E_FAIL;
	}

	hRes = RegOpenKeyExW(HKEY_CURRENT_USER,szRegistryKey,0,KEY_ALL_ACCESS,&hKey);
	if (hRes != ERROR_SUCCESS)
		goto Done;
	
	if (pdwValueChecked)
	{
		dwSize = sizeof(DWORD);
		hRes = RegQueryValueExW(hKey,szRegValue1,0,&dwType,(LPBYTE)pdwValueChecked,&dwSize);
		if (hRes != ERROR_SUCCESS)
			goto Done;
	}

	if (pdwValueUnchecked)
	{
		dwSize = sizeof(DWORD);
		hRes = RegQueryValueExW(hKey,szRegValue2,0,&dwType,(LPBYTE)pdwValueUnchecked,&dwSize);
	}

Done:
	RegCloseKey(hKey);
	return hRes;
}

////////////////////////////////////////////////////////
//	Called to save backlight related values to the
//  registry
//
////////////////////////////////////////////////////////
HRESULT SetToRegistry(REGISTRYOP eVal,DWORD dwValueChecked,DWORD dwValueUnchecked)
{
	HKEY	hKey;
	DWORD	dwDisp;
	HRESULT	hRes;

	TCHAR	*szRegistryKey;
	TCHAR	*szRegValue1;
	TCHAR	*szRegValue2;

	switch (eVal)
	{
		case eBrightness:
			szRegistryKey	= MYREGKEY;
			szRegValue1		= BRIGHTNESS;
			break;

		case eACPower:
			szRegistryKey	= REGKEY;
			szRegValue1		= ACTIMEOUT;
			szRegValue2		= ACTIMEOUTUNCHECKED;
			break;

		case eBatt:
			szRegistryKey	= REGKEY;
			szRegValue1		= BATTERYTIMEOUT;
			szRegValue2		= BATTERYTIMEOUTUNCHECKED;
			break;

		default:
			return E_FAIL;
	}
	
	hRes = RegCreateKeyExW(HKEY_CURRENT_USER, szRegistryKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);
	if (hRes != ERROR_SUCCESS)
	{
		TCHAR szDebug[80];
		wsprintf(szDebug,L"RegCreateKeyExW failed with %d\n",hRes);
		OutputDebugString(szDebug);
		return hRes;
	}
	else
		OutputDebugString(L"RegCreateKeyExW succeeded\n");
	
	hRes = RegSetValueExW(hKey,szRegValue1,0,REG_DWORD,(LPBYTE)&dwValueChecked,sizeof(DWORD));

	if (eVal != eBrightness)
		hRes = RegSetValueExW(hKey,szRegValue2,0,REG_DWORD,(LPBYTE)&dwValueUnchecked,sizeof(DWORD));

	RegCloseKey(hKey);                    
	
	return hRes;
}


////////////////////////////////////////////////////////
//	The DialogProc for the On Battery Power property page
//
////////////////////////////////////////////////////////
int CALLBACK BattPageProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HWND	hwndSlider;
	HWND	hwndCheck;
	DWORD	dwValueChecked;
	DWORD	dwValueUnchecked;
	DWORD	dwValue;

	LPPROPSHEETPAGE ppsp;
	TCHAR	szStatic[16];
	
	switch (uMsg)
	{
		case WM_INITDIALOG:        
			// get current slection
			GetFromRegistry(eBatt,&dwValueChecked,&dwValueUnchecked); 

			dwValue = (dwValueChecked>0?dwValueChecked:dwValueUnchecked)/60;

			hwndSlider = GetDlgItem(hwndDlg,IDC_SLIDER1);
			SendMessage(hwndSlider,TBM_SETRANGE,TRUE,MAKELONG(1, 15));	// range
			SendMessage(hwndSlider,TBM_SETTICFREQ,2,0L);				// tick freq.
			SendMessage(hwndSlider,TBM_SETPAGESIZE,0L,2);				// page up/dn size
			SendMessage(hwndSlider,TBM_SETPOS,TRUE,dwValue);   

			hwndCheck = GetDlgItem(hwndDlg,IDC_CHECK1);
			SendMessage(hwndCheck,BM_SETCHECK,(WPARAM)(dwValueChecked>0?BST_CHECKED:BST_UNCHECKED),0);

			wsprintf(szStatic,_T("%d min(s)"),dwValue);
			SendMessage(GetDlgItem(hwndDlg,IDC_STATIC1),WM_SETTEXT,0,(LPARAM)szStatic);

			GetFromRegistry(eBrightness,&dwValue,NULL);            // get current slection

			hwndSlider = GetDlgItem(hwndDlg,IDC_SLIDER2);
			SendMessage(hwndSlider,TBM_SETRANGE,TRUE,MAKELONG(1, 15));	// range
			SendMessage(hwndSlider,TBM_SETTICFREQ,2,0L);				// tick freq.
			SendMessage(hwndSlider,TBM_SETPAGESIZE,0L,2);				// page up/dn size
			SendMessage(hwndSlider,TBM_SETPOS,TRUE,dwValue);

			wsprintf(szStatic,_T("%d"),dwValue);
			SendMessage(GetDlgItem(hwndDlg,IDC_STATIC2),WM_SETTEXT,0,(LPARAM)szStatic);

			// lParam contains the PROPSHEETPAGE struct; store the HWND into the dword at the end of the struct
			ppsp = (LPPROPSHEETPAGE)lParam;
			*((HWND*)(ppsp + 1)) = hwndDlg;

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
					hwndSlider = GetDlgItem(hwndDlg,IDC_SLIDER1);
					if (hwndSlider == (HWND)lParam)
					{
						// The timeout minutes slider
						dwValue = SendMessage(hwndSlider,TBM_GETPOS,0,0);
						wsprintf(szStatic,_T("%d min(s)"),dwValue);
						SendMessage(GetDlgItem(hwndDlg,IDC_STATIC1),WM_SETTEXT,0,(LPARAM)szStatic);
					}
					else
					{
						// The brightness slider
						hwndSlider = GetDlgItem(hwndDlg,IDC_SLIDER2);
						dwValue = SendMessage(hwndSlider,TBM_GETPOS,0,0);
						wsprintf(szStatic,_T("%d"),dwValue);
						SendMessage(GetDlgItem(hwndDlg,IDC_STATIC2),WM_SETTEXT,0,(LPARAM)szStatic);
					}

					return TRUE;
				default:
					// Default case
					return FALSE;
			}
			break;
	}

	return FALSE;
}


////////////////////////////////////////////////////////
//	The DialogProc for the On AC Power property page
//
////////////////////////////////////////////////////////
int CALLBACK ACPowerPageProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HWND	hwndSlider;
	HWND	hwndCheck;
	DWORD	dwValueChecked;
	DWORD	dwValueUnchecked;
	DWORD	dwValue;
	TCHAR	szStatic[16];
	LPPROPSHEETPAGE ppsp;

	switch (uMsg)
	{
		case WM_INITDIALOG:        
			// get current slection
			GetFromRegistry(eACPower,&dwValueChecked,&dwValueUnchecked);
			dwValue = (dwValueChecked>0?dwValueChecked:dwValueUnchecked)/60;

			hwndSlider = GetDlgItem(hwndDlg,IDC_SLIDER1);
			SendMessage(hwndSlider,TBM_SETRANGE,TRUE,MAKELONG(1, 15));	// range
			SendMessage(hwndSlider,TBM_SETTICFREQ,2,0L);				// tick freq.
			SendMessage(hwndSlider,TBM_SETPAGESIZE,0L,2);				// page up/dn size
			SendMessage(hwndSlider,TBM_SETPOS,TRUE,dwValue);

			hwndCheck = GetDlgItem(hwndDlg,IDC_CHECK1);
			SendMessage(hwndCheck,BM_SETCHECK,(WPARAM)(dwValueChecked>0?BST_CHECKED:BST_UNCHECKED),0);

			wsprintf(szStatic,_T("%d min(s)"),dwValue);
			SendMessage(GetDlgItem(hwndDlg,IDC_STATIC1),WM_SETTEXT,0,(LPARAM)szStatic);

			// lParam contains the PROPSHEETPAGE struct; store the HWND into the dword at the end of the struct
			ppsp = (LPPROPSHEETPAGE)lParam;
			*((HWND*)(ppsp + 1)) = hwndDlg;

			return TRUE;

		case WM_HSCROLL:            // track bar message
			switch LOWORD(wParam) 
			{
				// Breaks 
				case TB_BOTTOM:
				case TB_THUMBPOSITION:
				case TB_LINEUP:
				case TB_LINEDOWN:
				case TB_PAGEUP:
				case TB_PAGEDOWN:
				case TB_TOP:
					dwValue = SendMessage(GetDlgItem(hwndDlg,IDC_SLIDER1),TBM_GETPOS,0,0);
					wsprintf(szStatic,_T("%d min(s)"),dwValue);
					SendMessage(GetDlgItem(hwndDlg,IDC_STATIC1),WM_SETTEXT,0,(LPARAM)szStatic);
					return TRUE;
				default:
					// Default case
					return FALSE;
			}
			break;
	}

	return FALSE;
}


////////////////////////////////////////////////////////
//	This callback is called when each property page gets
//  created and when it gets released.
////////////////////////////////////////////////////////
UINT CALLBACK PropSheetPageProc(HWND hwnd,UINT uMsg,LPPROPSHEETPAGE ppsp)
{
	HWND	hwndSlider;
	HWND	hwndCheck;
	HWND	hwndDlg;
	DWORD	dwValueChecked=0;
	DWORD	dwValueUnchecked=0;
	DWORD	dwBrightness;

	// Get the HWND of this property page that was tucked at the
	// end of the propsheetpage struct in the WM_INITDIALOG for this page
	hwndDlg = *((HWND*)(ppsp + 1));

	switch(uMsg) {
	case PSPCB_CREATE:
		//Return any non zero value to indicate success
		return 1;
		break;

	case PSPCB_RELEASE:
		//Make this a code block so declaration of iPage is local
		{
			int iPage = (int)ppsp->lParam;
			switch (iPage)
			{
				case ID_BATT:
					dwBrightness = SendMessage(GetDlgItem(hwndDlg,IDC_SLIDER2),TBM_GETPOS,0,0);
					SetToRegistry(eBrightness,dwBrightness,0);

				// Break intentionally left out so code falls through
				case ID_AC:
					hwndCheck = GetDlgItem(hwndDlg,IDC_CHECK1);
					hwndSlider = GetDlgItem(hwndDlg,IDC_SLIDER1);

					if (BST_UNCHECKED == SendMessage(hwndCheck,BM_GETCHECK,0,0))
						dwValueUnchecked = 60 * SendMessage(hwndSlider,TBM_GETPOS,0,0);
					else
						dwValueChecked = 60 * SendMessage(hwndSlider,TBM_GETPOS,0,0);

					SetToRegistry(iPage==ID_BATT?eBatt:eACPower,dwValueChecked,dwValueUnchecked);

					break;

				default:
					// We should never see this case.  If we do we want to know in debug builds.
					ASSERT(false);
					break;
			}

			// Signal the driver that the backlight settings
			// have changed so it reloads them from the registry
			HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, _T("BackLightChangeEvent"));
			if (hEvent != NULL)
				SetEvent(hEvent);
			CloseHandle(hEvent);

			// return value is ignored for this message
			return 0;
		}
		break;
	default:
		// We should never see this case.  If we do we want to know in debug builds.
		ASSERT(false);
		break;
	}
	//return for default case above
	return (UINT)-1;
}


////////////////////////////////////////////////////////
//	The PropSheetProc for the property sheet.
//
////////////////////////////////////////////////////////
int CALLBACK PropSheetProc(HWND hwndDlg,UINT uMsg,LPARAM lParam)
{
	switch (uMsg)
	{
		// Returning COMCTL32_VERSION to this message makes the
		// style of the property sheet to be that of the native
		// Pocket PC ones
		case PSCB_GETVERSION:
			return COMCTL32_VERSION;
		
		// The text copied into the lParam on receipt of this message
		// is displayed as the title of the propertysheet
		case PSCB_GETTITLE:
			wcscpy((TCHAR*)lParam,TEXT("Backlight Settings"));
			break;
		
		// The text copied into the lParam on receipt of this message
		// gets displayed as the link text at the bottom of the
		// propertysheet
		case PSCB_GETLINKTEXT:
			wcscpy((TCHAR*)lParam,TEXT("Go to <file:ctlpnl.exe cplmain.cpl,2,1{another}> applet."));
			break;
			
		default:
			break;
	}
	
	return 0;
}


////////////////////////////////////////////////////////
//	Called to display this applet as a property sheet
//
////////////////////////////////////////////////////////
BOOL CreatePropertySheet(HWND hwndParent, int iApplet)
{
	BOOL bReturn = FALSE;

	PROPSHEETHEADER psh;
	PROPSHEETPAGE ppsp;
	HPROPSHEETPAGE hpsp[2];

	int nPages=2;

	// Set all values for first property page
	ppsp.dwSize = sizeof(PROPSHEETPAGE)+sizeof(HWND); // Extra space at end of struct to tuck page's hwnd in when it's created
	ppsp.dwFlags = PSP_DEFAULT|PSP_USETITLE|PSP_USECALLBACK;
	ppsp.hInstance = g_hInstance;
	ppsp.pszTemplate = (LPTSTR)MAKEINTRESOURCE(IDD_PROPPAGE0);
	ppsp.hIcon = NULL;
	ppsp.pszTitle = TEXT("On Battery Power");
	ppsp.pfnDlgProc = BattPageProc;
	ppsp.lParam = (LONG)ID_BATT;
	ppsp.pfnCallback = PropSheetPageProc;
	ppsp.pcRefParent = NULL;

	hpsp[0] = CreatePropertySheetPage(&ppsp);
	if (NULL == hpsp[0]) {
		//Fail out of function
		return bReturn;
	}

	// Set all values for second perperty page
	ppsp.dwSize = sizeof(PROPSHEETPAGE)+sizeof(HWND); // Extra space at end of struct to tuck page's hwnd in when it's created
	ppsp.dwFlags = PSP_DEFAULT|PSP_USETITLE|PSP_USECALLBACK;
	ppsp.hInstance = g_hInstance;
	ppsp.pszTemplate = (LPTSTR)MAKEINTRESOURCE(IDD_PROPPAGE1);
	ppsp.hIcon = NULL;
	ppsp.pszTitle = TEXT("On AC Power");
	ppsp.pfnDlgProc = ACPowerPageProc;
	ppsp.lParam = (LONG)ID_AC;
	ppsp.pfnCallback = PropSheetPageProc;
	ppsp.pcRefParent = NULL;

	hpsp[1] = CreatePropertySheetPage(&ppsp);
	if (NULL ==hpsp[1]) {
		//Clean up the page we have created
		DestroyPropertySheetPage(hpsp[0]);

		//Fail out of function
		return bReturn;
	}
	
	psh.dwSize				= sizeof(psh);
	psh.dwFlags				= PSH_USECALLBACK|PSH_MAXIMIZE;
	psh.hwndParent			= hwndParent;
	psh.hInstance			= g_hInstance;
	psh.pszCaption			= NULL;
	psh.phpage				= hpsp;
	psh.nPages				= nPages;
	psh.nStartPage			= iApplet > (nPages-1)? (nPages-1): iApplet;
	psh.pfnCallback			= PropSheetProc;

	if(-1 != PropertySheet(&psh)) {
		bReturn = TRUE;
	}
	else 
	{
		//Clean up PropertySheetPages as they weren't used by the PropertySheet
		DestroyPropertySheetPage(hpsp[0]);
		DestroyPropertySheetPage(hpsp[1]);
	}

	return bReturn;
}
