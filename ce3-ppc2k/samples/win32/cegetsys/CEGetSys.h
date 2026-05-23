
#if !defined(AFX_CEGETSYS_H__B7C123A0_0FBD_11D3_8067_525400DA9DDD__INCLUDED_)
#define AFX_CEGETSYS_H__B7C123A0_0FBD_11D3_8067_525400DA9DDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**********************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

**********************************************************************/
/////////////////////////// Rapier only samples ///////////////////////
#if _WIN32_WCE < 212  //non-Rapier devices
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


#include "resource.h"

void doSysColors (HWND);
void doInfo      (HWND);
void doDirectory (HWND);
void doMetrics   (HWND);
void doPalette   (HWND);
void doLocalTime (HWND);
void doTime      (HWND);
void doVersionEx (HWND);


/* declare global variable to be used by all of the do... functions */
TCHAR szbufW[MAX_PATH];

/* structure for the lookup tables.  */
typedef struct tagLookupEntry{
    int     Value;
    TCHAR    String[100];
} LookupEntry;


/* GetSysColor() codes from WINUSER.H */
#define NSYSCOLORS 32
LookupEntry  SysColors[NSYSCOLORS] =
    {{ COLOR_SCROLLBAR          , _T("COLOR_SCROLLBAR        \t%06lx")},
     { COLOR_BACKGROUND         , _T("COLOR_BACKGROUND       \t%06lx")},
     { COLOR_ACTIVECAPTION      , _T("COLOR_ACTIVECAPTION    \t%06lx")},
     { COLOR_INACTIVECAPTION    , _T("COLOR_INACTIVECAPTION  \t%06lx")},
     { COLOR_MENU               , _T("COLOR_MENU             \t%06lx")},
     { COLOR_WINDOW             , _T("COLOR_WINDOW           \t%06lx")},
     { COLOR_WINDOWFRAME        , _T("COLOR_WINDOWFRAME      \t%06lx")},
     { COLOR_MENUTEXT           , _T("COLOR_MENUTEXT         \t%06lx")},
     { COLOR_WINDOWTEXT         , _T("COLOR_WINDOWTEXT       \t%06lx")},
     { COLOR_CAPTIONTEXT        , _T("COLOR_CAPTIONTEXT      \t%06lx")},
     { COLOR_ACTIVEBORDER       , _T("COLOR_ACTIVEBORDER     \t%06lx")},
     { COLOR_INACTIVEBORDER     , _T("COLOR_INACTIVEBORDER   \t%06lx")},
     { COLOR_APPWORKSPACE       , _T("COLOR_APPWORKSPACE     \t%06lx")},
     { COLOR_HIGHLIGHT          , _T("COLOR_HIGHLIGHT        \t%06lx")},
     { COLOR_HIGHLIGHTTEXT      , _T("COLOR_HIGHLIGHTTEXT    \t%06lx")},
     { COLOR_BTNFACE            , _T("COLOR_BTNFACE          \t%06lx")},
     { COLOR_BTNSHADOW          , _T("COLOR_BTNSHADOW        \t%06lx")},
     { COLOR_GRAYTEXT           , _T("COLOR_GRAYTEXT         \t%06lx")},
     { COLOR_BTNTEXT            , _T("COLOR_BTNTEXT          \t%06lx")},
     { COLOR_INACTIVECAPTIONTEXT, _T("COLOR_INACTIVECAPTEXT  \t%06lx")},
     { COLOR_BTNHIGHLIGHT       , _T("COLOR_BTNHIGHLIGHT     \t%06lx")},
     {  COLOR_3DDKSHADOW        , _T("COLOR_BTNHIGHLIGHT     \t%06lx")},
     {  COLOR_3DLIGHT           , _T("COLOR_3DLIGHT          \t%06lx")},
     {  COLOR_INFOTEXT          , _T("COLOR_INFOTEXT         \t%06lx")},
     {  COLOR_INFOBK            , _T("COLOR_INFOBK           \t%06lx")},
     {  COLOR_STATIC            , _T("COLOR_STATIC           \t%06lx")},
     {  COLOR_STATICTEXT        , _T("COLOR_STATICTEXT       \t%06lx")},
     {  COLOR_DESKTOP           , _T("COLOR_DESKTOP          \t%06lx")},
     {  COLOR_3DFACE            , _T("COLOR_3DFACE           \t%06lx")},
     {  COLOR_3DSHADOW          , _T("COLOR_3DSHADOW         \t%06lx")},
     {  COLOR_3DHIGHLIGHT       , _T("COLOR_3DHIGHLIGHT      \t%06lx")},
     {  COLOR_3DHILIGHT         , _T("COLOR_3DHILIGHT        \t%06lx")}
};


/* GetSystemMetrics() codes from WINUSER.H */
LookupEntry  SystemMetrics[] =
    {{ SM_CXSCREEN         , _T("SM_CXSCREEN      \t%d")},
     { SM_CYSCREEN         , _T("SM_CYSCREEN      \t%d")},
     { SM_CXVSCROLL        , _T("SM_CXVSCROLL     \t%d")},
     { SM_CYHSCROLL        , _T("SM_CYHSCROLL     \t%d")},
     { SM_CYCAPTION        , _T("SM_CYCAPTION     \t%d")},
     { SM_CXBORDER         , _T("SM_CXBORDER      \t%d")},
     { SM_CYBORDER         , _T("SM_CYBORDER      \t%d")},
     { SM_CXDLGFRAME       , _T("SM_CXDLGFRAME    \t%d")},
     { SM_CYDLGFRAME       , _T("SM_CYDLGFRAME    \t%d")},
//     { SM_CYVTHUMB         , _T("SM_CYVTHUMB      \t%d")},
//     { SM_CXHTHUMB         , _T("SM_CXHTHUMB      \t%d")},
     { SM_CXICON           , _T("SM_CXICON        \t%d")},
     { SM_CYICON           , _T("SM_CYICON        \t%d")},
//     { SM_CXCURSOR         , _T("SM_CXCURSOR      \t%d")},
//     { SM_CYCURSOR         , _T("SM_CYCURSOR      \t%d")},
     { SM_CYMENU           , _T("SM_CYMENU        \t%d")},
//     { SM_CXFULLSCREEN     , _T("SM_CXFULLSCREEN  \t%d")},
//     { SM_CYFULLSCREEN     , _T("SM_CYFULLSCREEN  \t%d")},
//     { SM_CYKANJIWINDOW    , _T("SM_CYKANJIWINDOW \t%d")},
     { SM_MOUSEPRESENT     , _T("SM_MOUSEPRESENT  \t%d")},
     { SM_CYVSCROLL        , _T("SM_CYVSCROLL     \t%d")},
     { SM_CXHSCROLL        , _T("SM_CXHSCROLL     \t%d")},
     { SM_DEBUG            , _T("SM_DEBUG         \t%d")},
//     { SM_SWAPBUTTON       , _T("SM_SWAPBUTTON    \t%d")},
//     { SM_RESERVED1        , _T("SM_RESERVED1     \t%d")},
//     { SM_RESERVED2        , _T("SM_RESERVED2     \t%d")},
//     { SM_RESERVED3        , _T("SM_RESERVED3     \t%d")},
//     { SM_RESERVED4        , _T("SM_RESERVED4     \t%d")},
//     { SM_CXMIN            , _T("SM_CXMIN         \t%d")},
//     { SM_CYMIN            , _T("SM_CYMIN         \t%d")},
//     { SM_CXSIZE           , _T("SM_CXSIZE        \t%d")},
//     { SM_CYSIZE           , _T("SM_CYSIZE        \t%d")},
//     { SM_CXFRAME          , _T("SM_CXFRAME       \t%d")},
//     { SM_CYFRAME          , _T("SM_CYFRAME       \t%d")},
//     { SM_CXMINTRACK       , _T("SM_CXMINTRACK    \t%d")},
//     { SM_CYMINTRACK       , _T("SM_CYMINTRACK    \t%d")},
     { SM_CXDOUBLECLK      , _T("SM_CXDOUBLECLK   \t%d")},
     { SM_CYDOUBLECLK      , _T("SM_CYDOUBLECLK   \t%d")},
     { SM_CXICONSPACING    , _T("SM_CXICONSPACING \t%d")},
     { SM_CYICONSPACING    , _T("SM_CYICONSPACING \t%d")},
//     { SM_MENUDROPALIGNMENT, _T("SM_MENUDROPALIGNMENT\t%d")},
//     { SM_PENWINDOWS       , _T("SM_PENWINDOWS    \t%d")},
//     { SM_DBCSENABLED      , _T("SM_DBCSENABLED   \t%d")},
//     { SM_CMOUSEBUTTONS    , _T("SM_CMOUSEBUTTONS \t%d")},

#if(WINVER >= 0x0400)
//     {  SM_SECURE            , _T("SM_SECURE          \t%d")},
     {  SM_CXEDGE            , _T("SM_CXEDGE          \t%d")},
     {  SM_CYEDGE            , _T("SM_CYEDGE          \t%d")},
//     {  SM_CXMINSPACING      , _T("SM_CXMINSPACING    \t%d")},
//     {  SM_CYMINSPACING      , _T("SM_CYMINSPACING    \t%d")},
     {  SM_CXSMICON          , _T("SM_CXSMICON        \t%d")},
     {  SM_CYSMICON          , _T("SM_CYSMICON        \t%d")},
//     {  SM_CYSMCAPTION       , _T("SM_CYSMCAPTION     \t%d")},
//     {  SM_CXSMSIZE          , _T("SM_CXSMSIZE        \t%d")},
//     {  SM_CYSMSIZE          , _T("SM_CYSMSIZE        \t%d")},
//     {  SM_CXMENUSIZE        , _T("SM_CXMENUSIZE      \t%d")},
//     {  SM_CYMENUSIZE        , _T("SM_CYMENUSIZE      \t%d")},
//     {  SM_ARRANGE           , _T("SM_ARRANGE         \t%d")},
//     {  SM_CXMINIMIZED       , _T("SM_CXMINIMIZED     \t%d")},
//     {  SM_CYMINIMIZED       , _T("SM_CYMINIMIZED     \t%d")},
//     {  SM_CXMAXTRACK        , _T("SM_CXMAXTRACK      \t%d")},
//     {  SM_CYMAXTRACK        , _T("SM_CYMAXTRACK      \t%d")},
//     {  SM_CXMAXIMIZED       , _T("SM_CXMAXIMIZED     \t%d")},
//     {  SM_CYMAXIMIZED       , _T("SM_CYMAXIMIZED     \t%d")},
//     {  SM_NETWORK           , _T("SM_NETWORK         \t%d")},
//     {  SM_CLEANBOOT         , _T("SM_CLEANBOOT       \t%d")},
//     {  SM_CXDRAG            , _T("SM_CXDRAG          \t%d")},
//     {  SM_CYDRAG            , _T("SM_CYDRAG          \t%d")},
#endif /* WINVER >= 0x0400 */

//     {  SM_SHOWSOUNDS        , _T("SM_SHOWSOUNDS      \t%d")},

#if(WINVER >= 0x0400)
//     {  SM_CXMENUCHECK       , _T("SM_CXMENUCHECK     \t%d")},
//     {  SM_CYMENUCHECK       , _T("SM_CYMENUCHECK     \t%d")},
//     {  SM_SLOWMACHINE       , _T("SM_SLOWMACHINE     \t%d")},
//     {  SM_MIDEASTENABLED    , _T("SM_MIDEASTENABLED  \t%d")},
#endif /* WINVER >= 0x0400 */
     };

#endif // !defined(AFX_CEGETSYS_H__B7C123A0_0FBD_11D3_8067_525400DA9DDD__INCLUDED_)
