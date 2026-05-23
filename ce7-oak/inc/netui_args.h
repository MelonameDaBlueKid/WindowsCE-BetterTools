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

#pragma once

#ifndef __NETUI_ARGS__INCLUDED__
#define __NETUI_ARGS__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#define WAIT_FOR_API_MAX_TIMEOUT 60000

//
// ----------------------------------------------------------------
//
// User-Mode UI Structures
//
// ----------------------------------------------------------------

//
// ----------------------------------------------------------------
//
// Netui Flag Definitions
//
// ----------------------------------------------------------------
#define NETUI_GETNETSTR_DIRECT_NAME              0
#define NETUI_GETNETSTR_OPEN_FILE_CONF           1
#define NETUI_GETNETSTR_BAD_RES_NAME             2
#define NETUI_GETNETSTR_ERR_ADDCONNECT           3
#define NETUI_GETNETSTR_ERR_INV_COMPNAME         4
#define NETUI_GETNETSTR_ERR_ADDNAME              5
#define NETUI_GETNETSTR_DISCON_ERROR             6
#define NETUI_GETNETSTR_SAVE_PWD                 7
#define NETUI_GETNETSTR_DFLT_LOCALNAME           8
#define NETUI_GETNETSTR_NO_IPADDR                9
#define NETUI_GETNETSTR_LEASE_EXPIRED           10
#define NETUI_GETNETSTR_CACHED_LEASE            11
#define NETUI_GETNETSTR_PRINT_COMPLETE          12
#define NETUI_GETNETSTR_PRINT_STATUS            13
#define NETUI_GETNETSTR_PRINT_STATUS_OFFLINE    14
#define NETUI_GETNETSTR_PRINT_STATUS_PAPER      15
#define NETUI_GETNETSTR_PRINT_STATUS_OTHER      16
#define NETUI_GETNETSTR_PRINT_STATUS_NETERR     17
#define NETUI_GETNETSTR_USB_INSTALL_FAILURE     18 
#define NETUI_GETNETSTR_ARP_CONFLICT_OLD_DHCP   19
#define NETUI_GETNETSTR_ARP_CONFLICT_OLD_STATIC 20
#define NETUI_GETNETSTR_ARP_CONFLICT_NETDOWN    21
#define NETUI_GETNETSTR_EAP_ERR_NOCERTIFICATE   22
#define NETUI_GETNETSTR_EAP_ERR_NOSMARTCARD     23

#define WIFI_LISTVIEW_X      7
#define WIFI_LISTVIEW_Y      29
#define WIFI_LISTVIEW_WIDTH  188
#define WIFI_LISTVIEW_HEIGHT 46

// Messages sent to IPAddress controls
#define IP_CLEARADDRESS WM_USER+100 // no parameters
#define IP_SETADDRESS   WM_USER+101 // lparam = TCP/IP address
#define IP_GETADDRESS   WM_USER+102 // lresult = TCP/IP address
#define IP_SETRANGE WM_USER+103 // wparam = field, lparam = range
#define IP_SETFOCUS WM_USER+104 // wparam = field

// IP Address style bits
#define IP_LEFT     0x00000001L // left justify fields
#define IP_RIGHT    0x00000002L // right justify fields
#define IP_CENTER   0x00000004L // center fields
#define IP_ZERO     0x00000008L // Zero fill the fields

// The following is a useful macro for passing the range values in the IP_SETRANGE message.
#define MAKERANGE(low, high)    ((LPARAM)(WORD)(((BYTE)(high) << 8) + (BYTE)(low)))

// This is a useful macro for making the IP Address to be passed as a LPARAM.
#define MAKEIPADDRESS(b1,b2,b3,b4)  ((LPARAM)(((DWORD)(b1)<<24)+((DWORD)(b2)<<16)+((DWORD)(b3)<<8)+((DWORD)(b4))))

// definitions for NetMsgBox flags
#define NMB_FL_OK          0x00000001
#define NMB_FL_EXCLAIM     0x00000002
#define NMB_FL_YESNO       0x00000004
#define NMB_FL_TOPMOST     0x00000008
#define NMB_FL_DEFBUTTON2  0x00000010
#define NMB_FL_INFORMATION 0x00000020

// Default title for MB is "Windows CE Networking". Override with these flags.
#define NMB_FL_TITLEUSB     0x00001000
#define NMB_FL_TITLEWIFI    0x00002000



//
// ----------------------------------------------------------------
//
// NetUI function argument definitions
//
// ----------------------------------------------------------------
#include "lmcons.h"

typedef struct _NETUI_USERPWD
{
    WCHAR   szUserName[UNLEN+1];
    WCHAR   szPassword[PWLEN+1];
    WCHAR   szDomain[DNLEN+1];
    DWORD   dwFlags;
#define NETUI_USERPWD_SAVEPWD           0x00000001  //  SavePwd box is checked
#define NETUI_USERPWD_SHOW_SAVEPWD      0x00000002  //  Show the SavePwd control
#define NETUI_USERPWD_SERVERLOGON       0x00000004  //  Connecting to network server
#define NETUI_USERPWD_NOPWD             0x00000008  //  Prompt for user identity only
#define NETUI_USERPWD_AUTH_FAIL         0x00000010
#define NETUI_USERPWD_WININET           0x00000020  //  Wininet style dialogs
#define NETUI_USERPWD_WININETPROXY      0x00000040  //  Site auth or Proxy auth type
#define NETUI_USERPWD_REALM             0x00000080  //  Realm style auth dialog
    WCHAR   szResourceName[RMLEN];  // Valid if SERVERLOGON flag set
    WCHAR   szRealm[RMLEN];         // Valid if REALM flag is set
} NETUI_USERPWD, *PNETUI_USERPWD;

typedef struct _NETUI_NEWPWD
{
    WCHAR   szNewPassword[PWLEN+1];
} NETUI_NEWPWD, *PNETUI_NEWPWD;


typedef struct _NETUI_RESPWD {
    WCHAR   szPassword[PWLEN + 1];
    WCHAR   szResourceName[RMLEN];
} NETUI_RESPWD, *PNETUI_RESPWD;

typedef struct {
    DWORD   dwVersion;
#define NETUI_LCD_STRUCTVER             1
    DWORD   dwBaudRate;                 // Baud Rate (i.e. 9600, 115200)
    DWORD   dwSettableBaud;             // Baud Rates Supported (see COMMPROP)
    BYTE    bByteSize;                  // Number of Bits/Byte 4-8
    BYTE    bParity;                    // 0-4=None, Odd, Even, Mark, Space
    BYTE    bStopBits;                  // 0,1,2 = 1, 1.5, 2
    BYTE    bReserved;                  // Alignment
    WORD    wSettableData;              // Settable data bits (see COMMPROP)
    WORD    wWaitBong;                  // Wait for Bong time
    DWORD   dwCallSetupFailTimer;       // Dial timeout
    DWORD   dwModemOptions;             // Modem Options
#define NETUI_LCD_MDMOPT_SOFT_FLOW      0x00000001  // Hardware flow control
#define NETUI_LCD_MDMOPT_HARD_FLOW      0x00000002  // Software flow control
#define NETUI_LCD_MDMOPT_BLIND_DIAL     0x00000004  // Blind Dial
#define NETUI_LCD_MDMOPT_AUTO_BAUD      0x00000008  // Enable DCC automatic baud rate detection

    DWORD   dwTermOptions;              // Terminal Options
#define NETUI_LCD_TRMOPT_MANUAL_DIAL    0x00000001  // Manual dial terminal
#define NETUI_LCD_TRMOPT_PRE_DIAL       0x00000002  // Pre-dial terminal
#define NETUI_LCD_TRMOPT_POST_DIAL      0x00000004  // Post-dial terminal

    DWORD   dwDdevCapFlags;             // Not supported yet.

#define NETUI_LCD_DIAL_MOD_LEN  256
    DWORD   dwModMaxLen;                // Length to allow user to edit.
    WCHAR   szDialModifier[NETUI_LCD_DIAL_MOD_LEN+1];
    WORD    wSettableStopParity;        // Which of the Byte/Stop/Parity
                                        // are settable (see COMMPROP)
} LINECONFIGDATA, *PLINECONFIGDATA;

#define DRIVER_NAME_LEN 128
#define INTERFACETYPE_USB  0x80000000
typedef struct _GETDRIVERNAMEPARMS {
    WCHAR DriverName[DRIVER_NAME_LEN];
    DWORD Socket;
    DWORD InterfaceType;
} GETDRIVERNAMEPARMS, * PGETDRIVERNAMEPARMS;


typedef struct _addconnect_dlgparams
{
    WCHAR LocalName[RMLEN + 10]; // Give space for "share on server"
    WCHAR RemoteName[RMLEN];
    BOOL  bReadOnly;             // If TRUE, make remote name read only
    
} ADDCONNECT_DLGPARAMS, *PADDCONNECT_DLGPARAMS;



//
// ----------------------------------------------------------------
//
// NetUI exposed API function type definitions
//
// ----------------------------------------------------------------
typedef int (WINAPI *PFN_GetNetString) (UINT uID, LPWSTR lpBuffer, int nBufferMax);
typedef BOOL (WINAPI *PFN_GetUsernamePassword)(HWND hParent, PNETUI_USERPWD pUserPwd);
typedef BOOL (WINAPI *PFN_GetUsernamePasswordEx)(HWND hParent, PNETUI_USERPWD pUserPwd, OUT OPTIONAL HWND *phDlg);
typedef BOOL (WINAPI *PFN_CloseUsernamePasswordDialog)(IN HWND hDlg);
typedef BOOL (WINAPI *PFN_GetNewPassword)(IN HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd);
typedef BOOL (WINAPI *PFN_GetNewPasswordEx)(IN HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd, OUT OPTIONAL HWND *phDlg);
typedef BOOL (WINAPI *PFN_GetResourcePassword)(HWND hParent, PNETUI_RESPWD pResPwd);
typedef BOOL (WINAPI *PFN_GetIPAddress)(HWND hParent);
typedef BOOL (WINAPI *PFN_LineConfigEdit)(HWND hParent, PLINECONFIGDATA pLineConfigData);
typedef BOOL (WINAPI *PFN_LineTranslateDialog)(HWND hParent, HWND *pDialogWnd);
typedef BOOL (WINAPI *PFN_ConnectionDialog)(HWND hParent, PADDCONNECT_DLGPARAMS pDlgParams);
typedef BOOL (WINAPI *PFN_DisconnectDialog)(HWND hParent, DWORD dwType);
typedef BOOL (WINAPI *PFN_NetMsgBox)(HWND hParent, DWORD dwFlags, WCHAR *szStr);
typedef BOOL (WINAPI *PFN_AdapterIPProperties)(HWND hWndOwner, LPWSTR szAdapterName);
typedef BOOL (WINAPI *PFN_GetDriverName)(HWND hParent, PGETDRIVERNAMEPARMS pDriverParms);



//
// ----------------------------------------------------------------
//
// NetUI exposed API
//
// ----------------------------------------------------------------
int GetNetStringSize (UINT uID);
int GetNetString (UINT uID, LPWSTR lpBuffer, int nBufferMax);
BOOL WINAPI GetUsernamePassword (HWND hParent, PNETUI_USERPWD pUserPwd);
BOOL WINAPI GetUsernamePasswordEx (HWND hParent, PNETUI_USERPWD pUserPwd, OUT OPTIONAL HWND *phDlg);
BOOL CloseUsernamePasswordDialog(IN HWND hDlg);
BOOL WINAPI GetNewPassword (HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd);
BOOL WINAPI GetNewPasswordEx (HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd, OUT OPTIONAL HWND *phDlg);
BOOL WINAPI GetResourcePassword (HWND hParent, PNETUI_RESPWD pResPwd);
DWORD GetIPAddress ( HWND hParent );
void WINAPI RegisterIPClass(HINSTANCE hInst);
void WINAPI UnregisterIPClass(HINSTANCE hInst);
BOOL WINAPI LineConfigEdit (HWND hParent, PLINECONFIGDATA pLineConfigData);
DWORD LineTranslateDialog ( HWND hParent, HWND *pDialogWnd );
BOOL WINAPI ConnectionDialog (HWND hParent, PADDCONNECT_DLGPARAMS pDlgParams);
BOOL WINAPI DisconnectDialog (HWND hParent, DWORD dwType);
BOOL WINAPI NetMsgBox (HWND hParent, DWORD dwFlags, WCHAR *szStr);
BOOL AdapterIPProperties (HWND hWndOwner, LPWSTR szAdapterName);
BOOL WINAPI GetDriverName (HWND hParent, PGETDRIVERNAMEPARMS pDriverParms);




//
// ----------------------------------------------------------------
//
// Kernel-Mode UI Structures
//
// ----------------------------------------------------------------
typedef struct _GetResourcePasswordArgs {
        BOOL retCode;
        HWND hParent;
        NETUI_RESPWD resPwd;
} GetResourcePasswordArgs, *PGetResourcePasswordArgs;


typedef struct _ConnectDialogArgs{
        BOOL retCode;    
        HWND hParent;
        ADDCONNECT_DLGPARAMS dlgParams;
} ConnectDialogArgs, *PConnectDialogArgs;


typedef struct _DisconnectDialogArgs{
        DWORD retCode;
        HWND hParent;
        DWORD dwType;
} DisconnectDialogArgs, *PDisconnectDialogArgs;


typedef struct _NetMsgBoxArgs{
        BOOL retCode;       
        HWND hParent;
        DWORD dwFlags;
        WCHAR szStr[1];
} NetMsgBoxArgs, *PNetMsgBoxArgs;


typedef struct _GetNetStringSizeArgs{
        int retCode;
        UINT uID;
} GetNetStringSizeArgs, *PGetNetStringSizeArgs;


typedef struct _GetNetStringArgs{
        int retCode;
        UINT uID;
        int nBufferMax;
        WCHAR buffer[1];
} GetNetStringArgs, *PGetNetStringArgs;


typedef struct _GetUsernamePasswordExArgs{
        DWORD retCode;
        HWND hParent;
        NETUI_USERPWD userPwd;
        HWND hDlg;  
} GetUsernamePasswordExArgs, *PGetUsernamePasswordExArgs;


typedef struct _GetNewPasswordExArgs{
        DWORD retCode;
        HWND hParent;
        NETUI_NEWPWD newPwd;
        HWND hDlg;  
} GetNewPasswordExArgs, *PGetNewPasswordExArgs;


typedef struct _CloseUsernamePasswordDialogArgs{
        DWORD retCode;
        HWND hDlg;  
} CloseUsernamePasswordDialogArgs, *PCloseUsernamePasswordDialogArgs;


typedef struct _GetIPAddressArgs{
        DWORD retCode;
        HWND hParent;
        DWORD ipAddress;    
} GetIPAddressArgs, *PGetIPAddressArgs;


typedef struct _MsgWaitForMultipleObjectsArgs {
        DWORD retCode;
        DWORD lastError;
        DWORD nCount;
        DWORD dwMilliseconds;
        DWORD dwWakeMask;
        DWORD dwFlags;
        HANDLE handles[1];
} MsgWaitForMultipleObjectsArgs, *PMsgWaitForMultipleObjectsArgs;


typedef struct _LoadLibraryArgs {
        HINSTANCE retCode;  
        DWORD lastError;    
        WCHAR LibFileName[1];
} LoadLibraryArgs, *PLoadLibraryArgs;


typedef struct _FreeLibraryArgs {
        BOOL retCode;   
        DWORD lastError;    
        HMODULE hLibModule;
} FreeLibraryArgs, *PFreeLibraryArgs;


typedef struct _LineConfigEditArgs{
        DWORD retCode;
        HWND hParent;
        LINECONFIGDATA lineCfgData;
} LineConfigEditArgs, *PLineConfigEditArgs;


typedef struct _LineTranslateDialogArgs{
        DWORD retCode;
        HWND hParent;
        HWND hDlg;
} LineTranslateDialogArgs, *PLineTranslateDialogArgs;


typedef struct _AdapterIPPropertiesArgs{
        BOOL retCode;
        HWND hParent;
        DWORD lastError;    
        WCHAR AdapterName[1];
} AdapterIPPropertiesArgs, *PAdapterIPPropertiesArgs;


typedef struct _GetDriverNameArgs{
        BOOL retCode;
        HWND hParent;
        DWORD lastError;    
        GETDRIVERNAMEPARMS getDrvNameParms;
} GetDriverNameArgs, *PGetDriverNameArgs;


typedef struct _PeekMessageArgs{
        BOOL retCode;
        DWORD lastError;
        HWND hWnd;
        UINT wMsgFilterMin;
        UINT wMsgFilterMax;
        UINT wRemoveMsg;
        MSG msg;
} PeekMessageArgs, *PPeekMessageArgs;


typedef struct _TranslateMessageArgs{
        BOOL retCode;
        DWORD lastError;
        MSG msg;
} TranslateMessageArgs, *PTranslateMessageArgs;


typedef struct _DispatchMessageArgs{
        BOOL retCode;
        DWORD lastError;
        MSG msg;
} DispatchMessageArgs, *PDispatchMessageArgs;

#ifdef __cplusplus
}
#endif

#endif
