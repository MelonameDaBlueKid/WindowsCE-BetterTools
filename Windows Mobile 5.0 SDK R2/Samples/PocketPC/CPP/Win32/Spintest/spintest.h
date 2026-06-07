//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
//*****************************************************************************
//
// Filename : spintest.h
//  
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
