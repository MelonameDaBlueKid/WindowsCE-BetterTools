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
#define Menu			   111
#define IDC_COMMANDBAR	   110
#define IDM_DLGEDITDIALOG  101  /* menuitem id's */
#define IDM_SPINTESTSTATS  102
#define IDM_ABOUT          103
#define IDM_EXIT           104
#define SPINTESTICON       105
#define ID_OPTIONS_EXIT    106

#define BORDER             4

//
// Spincube window styles as defined in spincube.h.
//

#define SS_ERASE                0x0001
#define SS_INMOTION             0x0002



/******************************************************************************\
*                               GLOBAL VARIABLES
\******************************************************************************/

HANDLE ghInst;
HWND   gahwndSpin[4];


/******************************************************************************\
*                              FUNCTION PROTOTYPES
\******************************************************************************/

LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
BOOL	CALLBACK DlgProc     (HWND, UINT, WPARAM, LPARAM);
