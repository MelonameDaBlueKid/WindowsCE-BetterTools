
#if !defined(AFX_SHELL_H__E85DECAC_69E5_11D2_987B_00C04F79DCF3__INCLUDED_)
#define AFX_SHELL_H__E85DECAC_69E5_11D2_987B_00C04F79DCF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//////////////////////////////////////
// Global variables
//////////////////////////////////////
extern HINSTANCE	g_hinst;						// current instance
extern INT			g_dyCB;							// height of CommandBar
extern HWND			g_hwndMain;						// main window
extern HWND			g_hwndCB;						// toolbar window
extern TCHAR		g_szHello[];					// string to print in window
extern TCHAR		*g_szFile;						// name of open file

//////////////////////////////////////
// Definitions
//////////////////////////////////////
#define FOS_SAVE				0					// FileOpenSave
#define FOS_OPEN				1					// FileOpenSave
#define FOS_FOLDER				2					// FileOpenSave
#define FOS_PROPERTIES			3					// FileOpenSave

//////////////////////////////////////
// Toolbar and Accelerator messages
//////////////////////////////////////
#define IDM_CMDBAR1				WM_USER + 100

//#define IDM_FILENEW			WM_USER + 101		// defined in resource.h
//#define IDM_FILEOPEN			WM_USER + 102		// defined in resource.h
#define IDM_FILESAVE			WM_USER + 103		// specific to toolbar (not in a menu)
#define IDM_COMBO				WM_USER + 104		// specific to toolbar


//////////////////////////////////////
// Application Registry Key
//////////////////////////////////////
#define HKEY_SHELL				TEXT("Software\\Samples\\Shell")
#define HVALUE_CBMENU			TEXT("CBMENU")
#define HVALUE_CBBUTTON			TEXT("CBBUTTON")


//////////////////////////////////////
// Function Prototypes
//////////////////////////////////////
BOOL	InitInstance(HINSTANCE, int);				// init.cpp
BOOL	CreateToolbar(HWND hwndParent);				// init.cpp
HWND CreateMenuBar(HWND hwndParent);							// init.cpp
void 	EnablePropertyItem();						// init.cpp

BOOL	FileOpenSave(DWORD fOpen);					// file.cpp
BOOL	FileFolder();								// file.cpp

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// shell.cpp

//
// from commdlg.h left off SDK - bug reported to MS
//
#define OFN_PROJECT					 0x00400000     // If this flag is set, the GetOpenFileName API will open the Project dialog for Gryphon
#define OFN_PROPERTY				 0x00800000     // If this flag is set, the GetSaveFileName API will open the Propery dialog for Gryphon
#define OFN_SHOW_ALL                 0x01000000     // If OFN_PROJECT is set,  show the <All Folders> item
//
// End workaround
//

#endif // !defined(AFX_SHELL_H__E85DECAC_69E5_11D2_987B_00C04F79DCF3__INCLUDED_)
