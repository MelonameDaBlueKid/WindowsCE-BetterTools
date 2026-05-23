// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
// PURPOSE:
//    Contains declarations for all globally scoped names in the program.
//

//-------------------------------------------------------------------------
// Product identifier string defines

//#define APPNAME       PViewCE
//#define SZAPPNAME     "PViewCE"
//#define SZDESCRIPTION "Process Viewer Application"
//#define SZABOUT       "About PViewCE"
//#define SZVERSION     "Version 4.0"
/// include stdafx.h ///
/**********************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

**********************************************************************/
/////////////////////////// Rapier only samples ///////////////////////
#if _WIN32_WCE > 211  //non-Rapier devices
#include <aygshell.h>
#endif

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
/// end include stdafx.h ///


//-------------------------------------------------------------------------
// Functions for handling main window messages.  The message-dispatching
// mechanism expects all message-handling functions to have the following
// prototype:
//
//     LRESULT FunctionName(HWND, UINT, WPARAM, LPARAM);

LRESULT MsgCommand(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgPaint(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgSize(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgLButtonDown(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgLButtonUp(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgMouseMove(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgNotify(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgActivateApp(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgDisplayChange(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgCreate(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgDestroy(HWND, UINT, WPARAM, LPARAM);



//-------------------------------------------------------------------------
// Functions for handling main window commands--ie. functions for
// processing WM_COMMAND messages based on the wParam value.
// The message-dispatching mechanism expects all command-handling
// functions to have the following prototype:
//
//     LRESULT FunctionName(HWND, WORD, WORD, HWND);

LRESULT CmdExit(HWND, WORD, WORD, HWND);
LRESULT CmdRefreshDisplay(HWND, WORD, WORD, HWND);
LRESULT CmdKillProcess(HWND, WORD, WORD, HWND);
LRESULT CmdAbout(HWND, WORD, WORD, HWND);
LRESULT CmdShowThreads(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl);
LRESULT CmdShowModules(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl);

//-------------------------------------------------------------------------
// Global function prototypes.

BOOL InitApplication(HINSTANCE, int);
BOOL CenterWindow(HWND, HWND);
HWND CreateAppToolbar(HWND hwndParent, WORD wID);
void DrawResizeLine(HWND hwnd, LONG yPos);
BOOL InitApp(void);

    // Callback functions.  These are called by Windows.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//-------------------------------------------------------------------------
// Global variable declarations.  Definition location is in parenthesis.

extern HINSTANCE hInst;          // The current instance handle (INIT.C)
extern TCHAR      szAppName[];    // The name of this application (INIT.C)
extern TCHAR      szTitle[];      // The title bar text (INIT.C)

extern HWND g_hwndMain;          // Main window's handle (PViewCE.C)
extern HWND g_hwndProcess;       // Process listview's handle (PViewCE.C)
extern HWND g_hwndThread;        // Thread listview's handle (PViewCE.C)
extern HWND g_hwndModule;        // Thread listview's handle (PViewCE.C)
extern HWND hwndCB;

#define hwndMDIClient NULL        /* Stub for NON-MDI applications. */

extern enum eActiveList {ThreadWindow, ModuleWindow} fActiveWindow;

//-------------------------------------------------------------------------
// Message and command dispatch infrastructure.  The following type
// definitions and functions are used by the message and command dispatching
// mechanism and do not need to be changed.

    // Function pointer prototype for message handling functions.
typedef LRESULT (*PFNMSG)(HWND,UINT,WPARAM,LPARAM);

    // Function pointer prototype for command handling functions.
typedef LRESULT (*PFNCMD)(HWND,WORD,WORD,HWND);

    // Enumerated type used to determine which default window procedure
    // should be called by the message- and command-dispatching mechanism
    // if a message or command is not handled explicitly.
typedef enum
{
   edwpNone,            // Do not call any default procedure.
   edwpWindow,          // Call DefWindowProc.
   edwpDialog,          // Call DefDlgProc (This should be used only for
                        // custom dialogs - standard dialog use edwpNone).
   edwpMDIChild,        // Call DefMDIChildProc.
   edwpMDIFrame         // Call DefFrameProc.
} EDWP;                // Enumeration for Default Window Procedures

    // This structure maps messages to message handling functions.
typedef struct _MSD
{
    UINT   uMessage;
    PFNMSG pfnmsg;
} MSD;                 // MeSsage Dispatch structure

    // This structure contains all of the information that a window
    // procedure passes to DispMessage in order to define the message
    // dispatching behavior for the window.
typedef struct _MSDI
{
    int  cmsd;          // Number of message dispatch structs in rgmsd
    MSD *rgmsd;         // Table of message dispatch structures
    EDWP edwp;          // Type of default window handler needed.
} MSDI, FAR *LPMSDI;   // MeSsage Dipatch Information

    // This structure maps command IDs to command handling functions.
typedef struct _CMD
{
    WORD   wCommand;
    PFNCMD pfncmd;
} CMD;                 // CoMmand Dispatch structure

    // This structure contains all of the information that a command
    // message procedure passes to DispCommand in order to define the
    // command dispatching behavior for the window.
typedef struct _CMDI
{
    int  ccmd;          // Number of command dispatch structs in rgcmd
    CMD *rgcmd;         // Table of command dispatch structures
    EDWP edwp;          // Type of default window handler needed.
} CMDI, FAR *LPCMDI;   // CoMmand Dispatch Information

    // Message and command dispatching functions.  They look up messages
    // and commands in the dispatch tables and call the appropriate handler
    // function.
LRESULT DispMessage(LPMSDI, HWND, UINT, WPARAM, LPARAM);
LRESULT DispCommand(LPCMDI, HWND, WPARAM, LPARAM);

    // Message dispatch information for the main window
extern MSDI msdiMain;
    // Command dispatch information for the main window
extern CMDI cmdiMain;
