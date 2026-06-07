//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#pragma once
#pragma check_stack(on)

// Workaround for a Whidbey Beta bug
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

#include <windows.h>
#include "Macros.h"     // SDK macros file (ie CHR, CBR etc)
#include <initguid.h>   // For COM INIT_GUID defns
#include <pimstore.h>   // POOM header file
#include <aygshell.h>   // For all SH* functions like SHCreateMenuBar etc)
#include <commctrl.h>   // For the ListView common control
#include "resource.h"   // For dialog resource defns

#define MAX_LOADSTRING  255


// Global Variables
static HINSTANCE                g_hInst     = 0;
static HWND                     g_hWnd      = 0;
static IPOutlookApp2            *g_polApp   = NULL;
static IPOutlookItemCollection  *g_pCol     = NULL;
static const int c_iPrevInstTries           = 3;
static const int c_iWindowCreationLatency   = 500; //This is in milliseconds
static const LPWSTR g_szClassName           = L"CalendarView";

// Titles to print for the listview item columns
static const LPTSTR g_rgCols[] = 
{
    TEXT("Subject    "),
    TEXT("Start Time "),
    TEXT("Duration   "),    
    TEXT("IsReccuring"),    
    TEXT("Categories "),
    TEXT("OID        "),    
};

// Properties to query POOM for. (corresponds to the titles in g_rgCols)
static const CEPROPID g_pPropIDs[] = {
    PIMPR_SUBJECT, 
    PIMPR_START, 
    PIMPR_DURATION,    
    PIMPR_IS_RECURRING,
    PIMPR_CATEGORIES, 
    PIMPR_OID,
};



// Forward function declarations
OlDefaultFolders ItemTypeToFolder(int olItemType);
LRESULT CALLBACK DlgMainProc(HWND, UINT, WPARAM, LPARAM);
int     InitApp (HINSTANCE hInstance, WNDCLASS *lpWndClass);
BOOL    InitInstance(HINSTANCE hInstance, int nCmdShow);
HRESULT InitLV(HWND hDlg);
HRESULT InitSKMenu(HWND hDlg, UINT nToolBarId);
HRESULT RefreshItems(HWND hwndLV);
HRESULT ProcessMainMenu(HWND hDlg, WORD wLo);
HRESULT PrettyPrintPropVal(CEPROPVAL *pPropVal, LPWSTR pszPrintBuffer, int cBufferSize);
HRESULT SubscribeToNotifications(IPOutlookApp2 *pPoom, int olItemType, uint uiNotificationsType);
HRESULT InitPOOM2();
HRESULT UnInitPOOM2();
void    ShowHR(HRESULT hr);
HRESULT FindPreviousInstance(const TCHAR *pwszClass, const TCHAR *pwszTitle,
    HANDLE *phMutex, HWND *phWnd, BOOL *pfFound, BOOL fActivateWindow);


