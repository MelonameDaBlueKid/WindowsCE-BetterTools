//*****************************************************************************
//
// Filename : spintest.h
//  
// Copyright (c) 1997 Microsoft Corporation. All rights reserved
//
/******************************************************************************

/******************************************************************************\
*                             SYMBOLIC CONSTANTS
\******************************************************************************/
#define IDM_DLGEDITDIALOG  101  /* menuitem id's */
#define IDM_SPINTESTSTATS  102
#define IDM_ABOUT          103
#define IDM_EXIT           104

#define IDM_MAIN_MENUITEM1 401
#define IDS_MAIN_MENUITEM1 410
#define IDM_MAIN_MENU      450

#define BORDER             4

//
// Spincube window styles as defined in spincube.h.
//

#define SS_ERASE                0x0001
#define SS_INMOTION             0x0002



/******************************************************************************\
*                               GLOBAL VARIABLES
\******************************************************************************/

HINSTANCE ghInst;
HWND   gahwndSpin[4];


/******************************************************************************\
*                              FUNCTION PROTOTYPES
\******************************************************************************/

LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
BOOL  CALLBACK DlgProc     (HWND, UINT, WPARAM, LPARAM);
