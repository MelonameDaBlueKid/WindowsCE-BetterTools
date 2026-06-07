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
// LISTVIEW.H
#include "resource.h"
// constants                            
#define ID_LISTVIEW     1000

#define NUM_ITEMS       9
#define NUM_COLUMNS     5
#define MAX_ITEMLEN     64
#define MAX_ADDRESS     64
#define MAX_CITY        16
#define MAX_PRICE       12
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   16
#define LG_BITMAP_WIDTH	32
#define LG_BITMAP_HEIGHT 32

// menu commands

// Options menu

#define IDM_LARGEICON   100
#define IDM_SMALLICON   101
#define IDM_LISTVIEW    102
#define IDM_REPORTVIEW  103
#define IDM_EXIT        104

// Help menu
#define IDM_ABOUT       300

// icons
#define APP_ICON        400
#define REDMOND         401
#define BELLEVUE        402
#define SEATTLE         403

// stringtable defines
#define IDS_ADDRESS     1
#define IDS_CITY        2
#define IDS_PRICE       3
#define IDS_BEDS        4
#define IDS_BATHS       5

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND CreateListView(HWND);
LRESULT NotifyHandler(HWND, UINT, WPARAM, LPARAM);
int CALLBACK ListViewCompareProc(LPARAM, LPARAM, LPARAM);

// structures
typedef struct tagHOUSEINFO
{
    TCHAR szAddress[MAX_ADDRESS];
    TCHAR szCity[MAX_CITY];
    int iPrice;
    int iBeds;
    int iBaths;
} HOUSEINFO;



