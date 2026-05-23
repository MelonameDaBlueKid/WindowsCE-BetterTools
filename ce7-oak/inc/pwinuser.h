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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:

ppwinuser.h

Abstract:

Private portion of winuser.h

Notes:


--*/

#pragma once

#ifndef _PRIV_WINUSER_
#define _PRIV_WINUSER_

#ifdef __cplusplus
extern "C"  {
#endif

#include <keybd.h>

// Non-Standard CE internal messages.
#define WM_QM_ACTIVATE          0x60
#define WM_HOOK_DO_CALLBACK     0x61
#define WM_SYSCOPYDATA          0x62


// wparam values for WM_SYSCOPYDATA
#define WMSCD_CHAR_RANKED_ALTS  0x01
#define WMSCD_DIALOGSCROLLBAR   0x02  



/*
 * Extended Window Styles
 */
#if(WINVER >= 0x0400)

#endif /* WINVER >= 0x0400 */

// Marker for end of accelerator tables.
#define FLASTKEY  0x80

// SetWindowPos internal flags
#define SWP_SYSTEMCAPTURE           0x80000000
#define SWP_FINDNEWFOREGROUND       0x40000000
#define SWP_MAXMIN                  0x20000000


// Internal values for hwnd for use in broadcasting messages
// Must be odd numbered.
#define HWND_TOPLEVELVISIBLEORPRE30     ((HWND)0xfffd)    // top level windows that are visible on screen or ver < 3.0
#define HWND_TOPLEVELCHILD              ((HWND)0xfffb)    // top level windows with the WS_CHILD bit set

/*
 * Predefined Clipboard Formats
 */
#define CF_METAFILEPICT     3
#define CF_ENHMETAFILE      14
#define CF_HDROP            15
#define IMAGE_ENHMETAFILE   3

void WINAPI SystemIdleTimerReset( void );

HWND WINAPI SetKeyboardTarget( HWND hWnd );
HWND WINAPI GetKeyboardTarget( VOID );
KEY_STATE_FLAGS WINAPI GetAsyncShiftFlags(UINT VKey);
WINUSERAPI void WINAPI AccessibilitySoundSentryEvent(void);
BOOL WINAPI ImmEnableIME(DWORD);
HKL WINAPI ImmGetKeyboardLayout(DWORD dwThreadId);

/*
 * ImmAssociateValueWithGwesMessageQueue flags
 * 
 * These is not hard & fast rule for the #s given below - just 
 * that they are ordered in pairs of get/set operations
 */
#define IMM_GETTHREADHKL                    1
#define IMM_SETTHREADHKL                    2
#define IMM_GETTHREADPREVHKL                3
#define IMM_SETTHREADPREVHKL                4

#define IMM_SETPROCESSHKL                   6

#define IMM_SET_THREAD_IME_DEFAULT_HWND     8
#define IMM_GET_LAYMGR_STATUS               9



void AudioUpdateFromRegistry(void);

/* Values for NotifyWinUserSystem */
#define NWUS_DOUBLE_TAP_CHANGED     1
#define NWUS_KEYBD_REPEAT_CHANGED   2
#define NWUS_MAX_IDLE_TIME_CHANGED  3

#define SPI_SETNOSEHFORVALIDATION   250

#define MOD_KEYUP_ALWAYS 0x2000

typedef struct tagPLATFORMVERSION {
    DWORD dwMajor;
    DWORD dwMinor;
} PLATFORMVERSION, *PPLATFORMVERSION;


#define SPI_PROJECT1    224
#define SPI_PROJECT2    225
#define SPI_PROJECT3    226
#define SPI_PROJECT4    227
#define SPI_PROJECT5    228
#define SPI_PROJECT6    229
#define SPI_PROJECT7    230
#define SPI_PROJECT8    231
#define SPI_PROJECT9    232
#define SPI_PROJECT10   233
#define SPI_PROJECT11   234
#define SPI_PROJECT12   235
#define SPI_PROJECT13   236
#define SPI_PROJECT14   237
#define SPI_PROJECT15   238
#define SPI_PROJECT16   239

#define SPI_GETPLATFORMTYPE           257
#define SPI_GETPLATFORMVERSION        SPI_PROJECT1    

#define VK_APP_LAUNCH1      0xC1
#define VK_APP_LAUNCH2      0xC2
#define VK_APP_LAUNCH3      0xC3
#define VK_APP_LAUNCH4      0xC4
#define VK_APP_LAUNCH5      0xC5
#define VK_APP_LAUNCH6      0xC6
#define VK_APP_LAUNCH7      0xC7
#define VK_APP_LAUNCH8      0xC8
#define VK_APP_LAUNCH9      0xC9
#define VK_APP_LAUNCH10     0xCA
#define VK_APP_LAUNCH11     0xCB
#define VK_APP_LAUNCH12     0xCC
#define VK_APP_LAUNCH13     0xCD
#define VK_APP_LAUNCH14     0xCE
#define VK_APP_LAUNCH15     0xCF




void WINAPI NotifyWinUserSystem( UINT    uEvent );

BOOL WINAPI RegisterTaskBar (HWND hwndTaskbar);
BOOL WINAPI RegisterTaskBarEx (HWND hwndTaskbar, BOOL bTaskBarOnTop);
BOOL WINAPI RegisterDesktop (HWND hwndDesktop);

WINUSERAPI BOOL WINAPI RectangleAnimation ( HWND hWnd, __in LPCRECT prc, BOOL fMaximize ) ;
void WINAPI ShellModalEnd( void );

//#define ExitWindows(dwReserved, Code) ExitWindowsEx(EWX_LOGOFF, 0xFFFFFFFF)
//WINUSERAPI BOOL WINAPI ExitWindowsEx( UINT uFlags,DWORD dwReserved);
void GwesPowerOffSystem (void);
BOOL GwesPowerDown (void);
void GwesPowerUp (BOOL);

void WINAPI BatteryGetLifeTimeInfo ( LPSYSTEMTIME pstLastChange, DWORD * pcmsCpuUsage, DWORD * pcmsPreviousCpuUsage );
LONG WINAPI BatteryDrvrGetLevels ( void );
BOOL WINAPI BatteryDrvrSupportsChangeNotification ( void );
void WINAPI BatteryNotifyOfTimeChange ( BOOL fForward, FILETIME * pftDelta );

// A system class built in to GWE for use by everyone
#define CS_SYSTEMCLASS 0x80000000

/* flags for DrawFrameControl */
//#define DFC_CAPTION             1
#define DFC_MENU                2
//#define DFC_SCROLL              3
//#define DFC_BUTTON              4
#define DFC_SPINNER             6

//#define DFCS_CAPTIONCLOSE       0x0000
//#define DFCS_CAPTIONMIN         0x0001
//#define DFCS_CAPTIONMAX         0x0002
//#define DFCS_CAPTIONRESTORE     0x0003
//#define DFCS_CAPTIONHELP        0x0004
//#define DFCS_CAPTIONOKBTN       0x0080
#define DFCS_CAPTIONROUNDOKBTN_WINCE    0x0010 
#define DFCS_CAPTIONROUNDCLOSE_WINCE    0x0020
#define DFCS_CAPTIONALL_WINCE           0x00F0

#define DFCS_MENUARROW          0x0000
#define DFCS_MENUCHECK          0x0001
#define DFCS_MENUBULLET         0x0002
#define DFCS_MENUARROWRIGHT     0x0004

//#define DFCS_SCROLLUP           0x0000
//#define DFCS_SCROLLDOWN         0x0001
//#define DFCS_SCROLLLEFT         0x0002
//#define DFCS_SCROLLRIGHT        0x0003
//#define DFCS_SCROLLCOMBOBOX     0x0005
#define DFCS_SCROLLSIZEGRIP     0x0008
#define DFCS_SCROLLSIZEGRIPRIGHT 0x0010

//#define DFCS_BUTTONCHECK        0x0000
#define DFCS_BUTTONRADIOIMAGE   0x0001
#define DFCS_BUTTONRADIOMASK    0x0002
//#define DFCS_BUTTONRADIO        0x0004
//#define DFCS_BUTTON3STATE       0x0008
//#define DFCS_BUTTONPUSH         0x0010

#define DFCS_SPINNERUP           0x0000
#define DFCS_SPINNERDOWN         0x0001
#define DFCS_SPINNERLEFT         0x0002
#define DFCS_SPINNERRIGHT        0x0003
#define DFCS_SPINNERBUTTON       0x0010
#define DFCS_SPINNERNOBORDER     0x0020

//#define DFCS_INACTIVE           0x0100
//#define DFCS_PUSHED             0x0200
//#define DFCS_CHECKED            0x0400
#define DFCS_ADJUSTRECT         0x2000
#define DFCS_FLAT               0x4000
#define DFCS_MONO               0x8000

#define MFT_NONOWNERSTRING      0x80000000L

//WINUSERAPI BOOL    WINAPI DrawFrameControl(HDC, LPRECT, UINT, UINT);

// NC messages
#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086

#define WM_NCMOUSEFIRST                 0x00A0
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9


#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#define WM_NCMOUSELAST                  0x00AD

#ifdef FAREAST
/* Class style for IME UI window */
#define CS_IME      0x00010000
#endif // FAREAST

#ifdef _WIN32_WCE_EMULATION
#ifdef CS_IME
#undef CS_IME
#endif
#define CS_IME      0x00010000
#endif

/* For internal APIs "exposed" to other internal pieces. */
#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif /*__cplusplus*/
#define INTAPI  EXTERN_C LONG __stdcall
#define INTAPI_(type) EXTERN_C type __stdcall

BOOL KeybdGetDeviceInfo( INT iIndex, __out LPVOID  lpOutput );
BOOL KeybdInitStates( __out KEY_STATE KeyState, __out void  *pKeybdDriverState );

UINT32 KeybdVKeyToUnicode(
    UINT32          VKey,
    KEY_STATE_FLAGS KeyEventFlags,
    __in KEY_STATE       KeyState,
    __in void            *KeybdDriverState,
    UINT32          cBufferSize,
    __out UINT32          *pcCharacters,
    __out_ecount(cBufferSize) KEY_STATE_FLAGS *pShiftStateBuffer,
    __out_ecount(cBufferSize) UINT32          *pCharacterBuffer
    );


// Maximum # of slots available in preload reg key.
#define MAX_HKL_PRELOAD_COUNT   20


#define WH_JOURNALRECORD    0
#define WH_JOURNALPLAYBACK  1
#define WH_KEYBOARD_LL      20
#define WH_MOUSE_LL         21


/*
 * Hook Codes
 */
#define HC_ACTION           0
#define HC_GETNEXT          1
#define HC_SKIP             2
#define HC_NOREMOVE         3
#define HC_NOREM            HC_NOREMOVE
#define HC_SYSMODALON       4
#define HC_SYSMODALOFF      5

typedef LRESULT (CALLBACK* HOOKPROC)(int code, WPARAM wParam, LPARAM lParam);

/*
 * Message Structure used in Journaling
 */
typedef struct tagEVENTMSG {
    UINT    message;
    UINT    paramL;
    UINT    paramH;
    DWORD    time;
    HWND    hwnd;
} EVENTMSG, *PEVENTMSGMSG, NEAR *NPEVENTMSGMSG, FAR *LPEVENTMSGMSG;

typedef struct tagEVENTMSG *PEVENTMSG, NEAR *NPEVENTMSG, FAR *LPEVENTMSG;


HHOOK
WINAPI
QASetWindowsJournalHook(
    int         nFilterType,
    HOOKPROC    pfnFilterProc,
    EVENTMSG    *pfnEventMsg
    );


BOOL
WINAPI
QAUnhookWindowsJournalHook(
    int            nFilterType
    );


BOOL
WINAPI
GetMessageWNoWait(
    __out PMSG    pMsg,
    HWND    hWnd,
    UINT    wMsgFilterMin,
    UINT    wMsgFilterMax
    );

BOOL
WINAPI
TouchCalibrate(
    void
    );

int
WINAPI
DisableCaretSystemWide(
    void
    );


int
WINAPI
EnableCaretSystemWide(
    void
    );


BOOL
WINAPI
EnableHardwareKeyboard(
    BOOL fEnable
    );

BOOL RegisterSIPanel (HWND hwndSIPanel);


void WINAPI SetAssociatedMenu (
    HWND hwnd,
    HMENU hmenu
    );

HMENU WINAPI GetAssociatedMenu (
    HWND hwnd
    );


BOOL
WINAPI
UnregisterFunc1(
    UINT    fsModifiers,
    UINT    vk
    );







typedef struct tagKBDLLHOOKSTRUCT {
    DWORD vkCode;        // virtual key code
    DWORD scanCode;        // scan code    DWORD flags;       // flags
    DWORD flags;        // unused
    DWORD time;            // time stamp for this message
    DWORD dwExtraInfo;    // extra info from the driver or keybd_event
} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

typedef struct {
    POINT pt;           // point of the cursor in screen coordinate
    DWORD mouseData;    // if WM_MOUSEWHEEL, the high-order word of this member is the wheel delta.
    DWORD flags;        // unused
    DWORD time;         // time stamp for this message
    DWORD dwExtraInfo;  // extra info
} MSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;

HHOOK
WINAPI
SetWindowsHookExW(
    int idHook,
    HOOKPROC lpfn,
    HINSTANCE hmod,
    DWORD dwThreadId);
#define SetWindowsHookEx  SetWindowsHookExW


BOOL
WINAPI
UnhookWindowsHookEx(
    HHOOK hhk);

LRESULT
WINAPI
CallNextHookEx(
    HHOOK hhk,
    int nCode,
    WPARAM wParam,
    LPARAM lParam);

typedef struct tagGetForegroundInfo
    {
    HWND    hwndActive;
    HWND    hwndFocus;
    HWND    hwndMenu;
    HWND    hwndKeyboardDest;
    DWORD    fdwConversion;
    DWORD    fdwSentence;
    BOOL    fOpen;
    DWORD    dwCompStrLen;
    HKL        KeyboardLayoutHandle;
    } GET_FOREGROUND_INFO;

BOOL
WINAPI
GetForegroundInfo(
    __out GET_FOREGROUND_INFO    *pgfi
    );

HWND GetForegroundKeyboardTarget(
    void
    );

HKL
GetForegroundKeyboardLayoutHandle(
    void
    );


BOOL
WINAPI
ShowStartupWindow(
    void
    );

BOOL
WINAPI
ShowStartupWindowBypassWantStartupScreen(
    void
    );


// Dialog Styles
#define DS_USEPIXELS        0x8000L // specifies use of pixels, not dialog coordinates

BOOL
WINAPI
SetDialogAutoScrollBar(
    HWND    hDlg
    );

BOOL
WINAPI
SetWindowPosOnRotate(
    HWND hWnd,
    HWND hWndInsertAfter,
    int X,
    int Y,
    int cx,
    int cy,
    UINT uFlags,
    BOOL fNoScroll
    );

// Refer to SB_* values in winuser.h (ex. SB_HORZ, SB_VERT, SB_CTL etc)
#define SB_CTL_HORZ         4     // Horizontal scrollbar indicator control (instead of non-client)
#define SB_CTL_VERT         5     // Vertical scrollbar indicator control (instead of non-client)

#define ARF_IMAGEFILE         0x00001
#define ARF_IMAGERES          0x00002
#define ARF_CLIENTSTARTRECT   0x00004 // specifies that the rcStart is in in client coordinates
#define ARF_CLIENTFINISHRECT  0x00008 // specifies that the rcFinish is in in client coordinates
#define ARF_SYNCHRONOUS       0x00010 // specifies that the animation happens synchronously
#define ARF_BITMAP            0x00020 // specifies that the hdc field contains a bitmap for the animation
#define ARF_BMPGROW           0x00040 // Bitmap animation "grows"
#define ARF_BMPUNCOVER        0x00080 // Bitmap animation "uncovers"
#define ARF_INCLUDELAST       0x00100 // include the last frame in the animation
#define ARF_ANIMATETIME       0x00200 // dwAnimateTime contains valid data
#define ARF_USEPARENT         0x00400 // hwnd should be used as the parent window for the animation

typedef struct
{
    HWND hwnd;
    RECT rcStart;
    RECT rcFinish;
    DWORD dwFlags;
    DWORD dwAnimateTime; // duration of animation in MS

    LPCTSTR pszResID;
    HINSTANCE hinst;
    LPTSTR pszFile;
    HBITMAP hbmAnimate;
} ANIMATERECTSINFO;

HRESULT AnimateRects(__in ANIMATERECTSINFO *pari);

//    This is taken directly from pbt.h.  Not all values are used or supported.

#ifndef WM_POWERBROADCAST
#define WM_POWERBROADCAST               0x218
#endif

#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001

#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003

#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005

#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008

#define PBTF_APMRESUMEFROMFAILURE       0x00000001

#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A

#define PBT_APMOEMEVENT                 0x000B

#define PBT_APMUSERIDLE                 0x000C
#define PBT_APMUSERACTIVE               0x000D


// @CESYSGEN IF GWES_MSGQUE
#define SQM_INPUT_EVENT_KEYBD       0x00000001
#define SQM_INPUT_EVENT_SOFTKEY     0x00000002

BOOL GetLastInputType(DWORD *pdwEvents);
BOOL SetLastInputType(DWORD dwEvents);

// @CESYSGEN ENDIF GWES_MSGQUE


// @CESYSGEN IF GWES_WINMGR

// Notifications sent by GWES to the shell

// Codes used in WM_SHELLNOTIFY
#define SHELLNOTIFY_WINDOWCREATED        0x0006
#define SHELLNOTIFY_WINDOWDESTROYED      0x0007
#define SHELLNOTIFY_WINDOWACTIVATED      0x0008
#define SHELLNOTIFY_REDRAW               0x0009
#define SHELLNOTIFY_LANGUAGE             0x000A
#define SHELLNOTIFY_CAPSLOCK             0x000B
#define SHELLNOTIFY_RESERVED0x000C       0x000C
#define SHELLNOTIFY_RESERVED0x000D       0x000D
#define SHELLNOTIFY_FOCUSCHANGE          0x000E
#define SHELLNOTIFY_ACTIVATIONCHANGED    0x000F

// @CESYSGEN ENDIF

// @CESYSGEN IF GWES_UIBASE

#define CURSORPREFERENCE_SYSTEM              0x0000 /* follow system preference */
#define CURSORPREFERENCE_TOUCH               0x0001 /* mouse cursor prefered   */
#define CURSORPREFERENCE_MOUSE               0x0002 /* touch cursor prefered   */



WINUSERAPI
DWORD
WINAPI
SetWindowCursorPreference(
    HWND hwnd,
    DWORD dwFlags
    );


WINUSERAPI
DWORD
WINAPI
GetWindowCursorPreference(
    HWND hwnd
    );

// @CESYSGEN ENDIF

// @CESYSGEN IF GWES_LBCTL

#define LBN_RESERVED0x8000                   0x8000

// @CESYSGEN ENDIF



// @CESYSGEN IF GWES_CURSOR || GWES_MCURSOR

WINUSERAPI
DWORD
WINAPI
SetSystemCursorPreference(
    DWORD dwFlags
    );


WINUSERAPI
DWORD
WINAPI
GetSystemCursorPreference(
    void
    );

// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_GWESCOMPOSITION_COMMON

int
WINAPI
UpdateWindowSurface(
    HWND hwnd,
    int nEscape,
    int cbInput,
    __in_bcount_opt(cbInput) LPCSTR lpszInData,
    int cbOutput,
    __out_bcount_opt(cbOutput) LPSTR lpszOutData
    );

// This struct is the input buffer passed on from the UpdateWindowSurface call to DrvEscape.
typedef struct {
    RECTL rcClient;    // This is the client rect, relative to the window rect
    int cbInput;       // This is the cbInput parameter to UpdateWindowSurface
    LPCSTR lpszInData; // This is the input buffer passed to UpdateWindowSurface
} UpdateWindowSurfaceInputParm;

// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_UIBASE

typedef HRESULT (CALLBACK* HITDETECT_CALLBACK)(
                DWORD  dwScreenX,
                DWORD  dwScreenY,
          __out HWND*  phWnd,
          __out DWORD* pdwWindowX,
          __out DWORD* pdwWindowY,
    __inout_opt LPVOID lpContext
          );

#if 0
HRESULT
WINAPI
ProcessUserInput(
    __callback HITDETECT_CALLBACK pFnHitDetectCallBack,
   __inout_opt LPVOID lpContext
    );    

HANDLE
WINAPI
GetUserInputReadyHandle(
    void
    );
#endif

// @CESYSGEN ENDIF

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _PRIV_WINUSER_ */
