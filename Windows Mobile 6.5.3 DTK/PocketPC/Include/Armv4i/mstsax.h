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

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Sun May 23 16:20:17 2004
 */
/* Compiler settings for ..\mstsax.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __mstsax_h__
#define __mstsax_h__

/* Forward Declarations */ 

#ifndef __IMsTscNonScriptable_FWD_DEFINED__
#define __IMsTscNonScriptable_FWD_DEFINED__
typedef interface IMsTscNonScriptable IMsTscNonScriptable;
#endif 	/* __IMsTscNonScriptable_FWD_DEFINED__ */


#ifndef __IMsRdpClientNonScriptable_FWD_DEFINED__
#define __IMsRdpClientNonScriptable_FWD_DEFINED__
typedef interface IMsRdpClientNonScriptable IMsRdpClientNonScriptable;
#endif 	/* __IMsRdpClientNonScriptable_FWD_DEFINED__ */


#ifndef __IMsRdpClientNonScriptable2_FWD_DEFINED__
#define __IMsRdpClientNonScriptable2_FWD_DEFINED__
typedef interface IMsRdpClientNonScriptable2 IMsRdpClientNonScriptable2;
#endif 	/* __IMsRdpClientNonScriptable2_FWD_DEFINED__ */


#ifndef __IMsRdpClientNonScriptable3_FWD_DEFINED__
#define __IMsRdpClientNonScriptable3_FWD_DEFINED__
typedef interface IMsRdpClientNonScriptable3 IMsRdpClientNonScriptable3;
#endif 	/* __IMsRdpClientNonScriptable3_FWD_DEFINED__ */


#ifndef __IMsTscSecuredSettings_FWD_DEFINED__
#define __IMsTscSecuredSettings_FWD_DEFINED__
typedef interface IMsTscSecuredSettings IMsTscSecuredSettings;
#endif 	/* __IMsTscSecuredSettings_FWD_DEFINED__ */


#ifndef __IMsRdpClientSecuredSettings_FWD_DEFINED__
#define __IMsRdpClientSecuredSettings_FWD_DEFINED__
typedef interface IMsRdpClientSecuredSettings IMsRdpClientSecuredSettings;
#endif 	/* __IMsRdpClientSecuredSettings_FWD_DEFINED__ */


#ifndef __IMsTscDebug_FWD_DEFINED__
#define __IMsTscDebug_FWD_DEFINED__
typedef interface IMsTscDebug IMsTscDebug;
#endif 	/* __IMsTscDebug_FWD_DEFINED__ */


#ifndef __ITSRemoteApplication_FWD_DEFINED__
#define __ITSRemoteApplication_FWD_DEFINED__
typedef interface ITSRemoteApplication ITSRemoteApplication;
#endif 	/* __ITSRemoteApplication_FWD_DEFINED__ */


#ifndef __IMsRdpClientTransportSettings_FWD_DEFINED__
#define __IMsRdpClientTransportSettings_FWD_DEFINED__
typedef interface IMsRdpClientTransportSettings IMsRdpClientTransportSettings;
#endif 	/* __IMsRdpClientTransportSettings_FWD_DEFINED__ */


#ifndef __IMsRdpClientShell_FWD_DEFINED__
#define __IMsRdpClientShell_FWD_DEFINED__
typedef interface IMsRdpClientShell IMsRdpClientShell;
#endif 	/* __IMsRdpClientShell_FWD_DEFINED__ */


#ifndef __IMsTscAdvancedSettings_FWD_DEFINED__
#define __IMsTscAdvancedSettings_FWD_DEFINED__
typedef interface IMsTscAdvancedSettings IMsTscAdvancedSettings;
#endif 	/* __IMsTscAdvancedSettings_FWD_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings_FWD_DEFINED__
#define __IMsRdpClientAdvancedSettings_FWD_DEFINED__
typedef interface IMsRdpClientAdvancedSettings IMsRdpClientAdvancedSettings;
#endif 	/* __IMsRdpClientAdvancedSettings_FWD_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings2_FWD_DEFINED__
#define __IMsRdpClientAdvancedSettings2_FWD_DEFINED__
typedef interface IMsRdpClientAdvancedSettings2 IMsRdpClientAdvancedSettings2;
#endif 	/* __IMsRdpClientAdvancedSettings2_FWD_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings3_FWD_DEFINED__
#define __IMsRdpClientAdvancedSettings3_FWD_DEFINED__
typedef interface IMsRdpClientAdvancedSettings3 IMsRdpClientAdvancedSettings3;
#endif 	/* __IMsRdpClientAdvancedSettings3_FWD_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings4_FWD_DEFINED__
#define __IMsRdpClientAdvancedSettings4_FWD_DEFINED__
typedef interface IMsRdpClientAdvancedSettings4 IMsRdpClientAdvancedSettings4;
#endif 	/* __IMsRdpClientAdvancedSettings4_FWD_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings5_FWD_DEFINED__
#define __IMsRdpClientAdvancedSettings5_FWD_DEFINED__
typedef interface IMsRdpClientAdvancedSettings5 IMsRdpClientAdvancedSettings5;
#endif 	/* __IMsRdpClientAdvancedSettings5_FWD_DEFINED__ */


#ifndef __IMsTscAx_FWD_DEFINED__
#define __IMsTscAx_FWD_DEFINED__
typedef interface IMsTscAx IMsTscAx;
#endif 	/* __IMsTscAx_FWD_DEFINED__ */


#ifndef __IMsRdpClient_FWD_DEFINED__
#define __IMsRdpClient_FWD_DEFINED__
typedef interface IMsRdpClient IMsRdpClient;
#endif 	/* __IMsRdpClient_FWD_DEFINED__ */


#ifndef __IMsRdpClient2_FWD_DEFINED__
#define __IMsRdpClient2_FWD_DEFINED__
typedef interface IMsRdpClient2 IMsRdpClient2;
#endif 	/* __IMsRdpClient2_FWD_DEFINED__ */


#ifndef __IMsRdpClient3_FWD_DEFINED__
#define __IMsRdpClient3_FWD_DEFINED__
typedef interface IMsRdpClient3 IMsRdpClient3;
#endif 	/* __IMsRdpClient3_FWD_DEFINED__ */


#ifndef __IMsRdpClient4_FWD_DEFINED__
#define __IMsRdpClient4_FWD_DEFINED__
typedef interface IMsRdpClient4 IMsRdpClient4;
#endif 	/* __IMsRdpClient4_FWD_DEFINED__ */


#ifndef __IMsRdpClient5_FWD_DEFINED__
#define __IMsRdpClient5_FWD_DEFINED__
typedef interface IMsRdpClient5 IMsRdpClient5;
#endif 	/* __IMsRdpClient5_FWD_DEFINED__ */


#ifndef __IMsTscAxEvents_FWD_DEFINED__
#define __IMsTscAxEvents_FWD_DEFINED__
typedef interface IMsTscAxEvents IMsTscAxEvents;
#endif 	/* __IMsTscAxEvents_FWD_DEFINED__ */


#ifndef __MsTscAx_FWD_DEFINED__
#define __MsTscAx_FWD_DEFINED__

#ifdef __cplusplus
typedef class MsTscAx MsTscAx;
#else
typedef struct MsTscAx MsTscAx;
#endif /* __cplusplus */

#endif 	/* __MsTscAx_FWD_DEFINED__ */


#ifndef __MsRdpClient_FWD_DEFINED__
#define __MsRdpClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class MsRdpClient MsRdpClient;
#else
typedef struct MsRdpClient MsRdpClient;
#endif /* __cplusplus */

#endif 	/* __MsRdpClient_FWD_DEFINED__ */


#ifndef __MsRdpClient2_FWD_DEFINED__
#define __MsRdpClient2_FWD_DEFINED__

#ifdef __cplusplus
typedef class MsRdpClient2 MsRdpClient2;
#else
typedef struct MsRdpClient2 MsRdpClient2;
#endif /* __cplusplus */

#endif 	/* __MsRdpClient2_FWD_DEFINED__ */


#ifndef __MsRdpClient3_FWD_DEFINED__
#define __MsRdpClient3_FWD_DEFINED__

#ifdef __cplusplus
typedef class MsRdpClient3 MsRdpClient3;
#else
typedef struct MsRdpClient3 MsRdpClient3;
#endif /* __cplusplus */

#endif 	/* __MsRdpClient3_FWD_DEFINED__ */


#ifndef __MsRdpClient4_FWD_DEFINED__
#define __MsRdpClient4_FWD_DEFINED__

#ifdef __cplusplus
typedef class MsRdpClient4 MsRdpClient4;
#else
typedef struct MsRdpClient4 MsRdpClient4;
#endif /* __cplusplus */

#endif 	/* __MsRdpClient4_FWD_DEFINED__ */


#ifndef __MsRdpClient5_FWD_DEFINED__
#define __MsRdpClient5_FWD_DEFINED__

#ifdef __cplusplus
typedef class MsRdpClient5 MsRdpClient5;
#else
typedef struct MsRdpClient5 MsRdpClient5;
#endif /* __cplusplus */

#endif 	/* __MsRdpClient5_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_mstsax_0000 */
/* [local] */ 

#define	AUDIOREDIRECT_TO_CLIENT	( 0 )

#define	AUDIOREDIRECT_ON_SERVER	( 1 )

#define	AUDIOREDIRECT_NOAUDIO	( 2 )

#define	DISPID_METHOD_CONNECT	( 30 )

#define	DISPID_METHOD_DISCONNECT	( 31 )

#define	DISPID_METHOD_CREATEVIRTUALCHANNELS	( 33 )

#define	DISPID_METHOD_SENDONVIRTUALCHANNEL	( 34 )

#define	DISPID_PROP_SERVER	( 1 )

#define	DISPID_PROP_DOMAIN	( 2 )

#define	DISPID_PROP_USERNAME	( 3 )

#define	DISPID_PROP_DISCONNECTED_TEXT	( 4 )

#define	DISPID_PROP_CONNECTING_TEXT	( 5 )

#define	DISPID_PROP_CONNECTED	( 6 )

#define	DISPID_PROP_DESKTOPWIDTH	( 12 )

#define	DISPID_PROP_DESKTOPHEIGHT	( 13 )

#define	DISPID_PROP_STARTCONNECTED	( 16 )

#define	DISPID_PROP_HORIZSCROLLBAR	( 17 )

#define	DISPID_PROP_VERTSCROLLBAR	( 18 )

#define	DISPID_PROP_FULLSCREENTITLE	( 19 )

#define	DISPID_PROP_CIPHERSTRENGTH	( 20 )

#define	DISPID_PROP_VERSION	( 21 )

#define	DISPID_PROP_SECUREDSETTINGSENABLED	( 22 )

#define	DISPID_PROP_SECUREDSETTINGS	( 97 )

#define	DISPID_PROP_ADVSETTINGS	( 98 )

#define	DISPID_PROP_DEBUGGER	( 99 )

#define	DISPID_METHOD_SET_VIRTUALCHANNELOPTIONS	( 35 )

#define	DISPID_METHOD_GET_VIRTUALCHANNELOPTIONS	( 36 )

#define	DISPID_METHOD_REQUESTCLOSE	( 37 )

#define	DISPID_PROP_COLORDEPTH	( 100 )

#define	DISPID_PROP_ADVSETTINGS2	( 101 )

#define	DISPID_PROP_SECUREDSETTINGS2	( 102 )

#define	DISPID_PROP_EXTENDEDDISCONNECTREASON	( 103 )

#define	DISPID_PROP_FULLSCREEN	( 104 )

#define	DISPID_PROP_ADVSETTINGS3	( 200 )

#define	DISPID_PROP_CONNECTED_STATUS_TEXT	( 201 )

#define	DISPID_PROP_ADVSETTINGS4	( 300 )

#define	DISPID_PROP_ADVSETTINGS5	( 400 )

#define	DISPID_PROP_RAIL	( 500 )

#define	DISPID_PROP_TRANSPORT_CONNECTION	( 501 )

#define	DISPID_PROP_MSRDPCLIENTSHELL	( 502 )

#define	DISPID_METHOD_CENTERWINDOW	( 503 )

#define	DISPID_PROP_ADVSETTINGS6	( 504 )

#define	DISPID_PROP_ADV_COMPRESS	( 121 )

#define	DISPID_PROP_ADV_BITMAPPERISTENCE	( 122 )

#define	DISPID_PROP_ADV_ALLOWBACKGROUNDINPUT	( 161 )

#define	DISPID_PROP_ADV_KEYBOARDLAYOUTSTR	( 162 )

#define	DISPID_PROP_ADV_PLUGINDLLS	( 170 )

#define	DISPID_PROP_ADV_ICONFILE	( 171 )

#define	DISPID_PROP_ADV_ICONINDEX	( 172 )

#define	DISPID_PROP_ADV_CONTAINER_FULLSCREEN	( 173 )

#define	DISPID_PROP_ADV_DISABLE_RDPDR	( 174 )

#define	DISPID_PROP_ADV_SMOOTHSCROLL	( 101 )

#define	DISPID_PROP_ADV_ACCELERATORPASSTHROUGH	( 102 )

#define	DISPID_PROP_ADV_SHADOWBITMAP	( 103 )

#define	DISPID_PROP_ADV_TRANSPORTTYPE	( 104 )

#define	DISPID_PROP_ADV_SASSEQUENCE	( 105 )

#define	DISPID_PROP_ADV_ENCRYPTIONENABLED	( 106 )

#define	DISPID_PROP_ADV_DEDICATEDTERMINAL	( 107 )

#define	DISPID_PROP_ADV_RDPPORT	( 108 )

#define	DISPID_PROP_ADV_ENABLEMOUSE	( 109 )

#define	DISPID_PROP_ADV_DISABLECTRLALTDEL	( 110 )

#define	DISPID_PROP_ADV_ENABLEWINDOWSKEY	( 111 )

#define	DISPID_PROP_ADV_DOUBLECLICKDETECT	( 112 )

#define	DISPID_PROP_ADV_MAXIMIZESHELL	( 113 )

#define	DISPID_PROP_ADV_HOTKEYFULLSCREEN	( 114 )

#define	DISPID_PROP_ADV_HOTKEYCTRLESC	( 115 )

#define	DISPID_PROP_ADV_HOTKEYALTESC	( 116 )

#define	DISPID_PROP_ADV_HOTKEYALTTAB	( 117 )

#define	DISPID_PROP_ADV_HOTKEYALTSHIFTTAB	( 118 )

#define	DISPID_PROP_ADV_HOTKEYALTSPACE	( 119 )

#define	DISPID_PROP_ADV_HOTKEYCTRLALTDEL	( 120 )

#define	DISPID_PROP_ADV_ORDERDRAWTHRESHOLD	( 123 )

#define	DISPID_PROP_ADV_BITMAPCACHESIZE	( 124 )

#define	DISPID_PROP_ADV_BITMAPVIRTUALCACHESIZE	( 125 )

#define	DISPID_PROP_ADV_NUMBITMAPCACHES	( 126 )

#define	DISPID_PROP_ADV_CACHEPERSISTENCEACTIVE	( 127 )

#define	DISPID_PROP_ADV_PERSISTCACHEDIRECTORY	( 138 )

#define	DISPID_PROP_ADV_BRUSHSUPPORTLEVEL	( 156 )

#define	DISPID_PROP_ADV_MININPUTSENDINTERVAL	( 157 )

#define	DISPID_PROP_ADV_INPUTEVENTSATONCE	( 158 )

#define	DISPID_PROP_ADV_MAXEVENTCOUNT	( 159 )

#define	DISPID_PROP_ADV_KEEPALIVEINTERVAL	( 160 )

#define	DISPID_PROP_ADV_SHUTDOWNTIMEOUT	( 163 )

#define	DISPID_PROP_ADV_OVERALLCONNECTIONTIMEOUT	( 164 )

#define	DISPID_PROP_ADV_SINGLECONNECTIONTIMEOUT	( 165 )

#define	DISPID_PROP_ADV_KEYBOARDTYPE	( 166 )

#define	DISPID_PROP_ADV_KEYBOARDSUBTYPE	( 167 )

#define	DISPID_PROP_ADV_KEYBOARDFUNCTIONKEY	( 168 )

#define	DISPID_PROP_ADV_WINCEFIXEDPALETTE	( 169 )

#define	DISPID_PROP_ADV_SCALEBITMAPCACHESBYBPP	( 175 )

#define	DISPID_PROP_ADV_CONNECT_TO_SERVER_CONSOLE	( 178 )

#define	DISPID_PROP_ADV_BITMAPPERSISTENCE	( 182 )

#define	DISPID_PROP_ADV_MINUTESTOIDLETIMEOUT	( 183 )

#define	DISPID_PROP_ADV_SMART_SIZING	( 184 )

#define	DISPID_PROP_ADV_RDPDR_LOCALPRINTINGDOCNAME	( 185 )

#define	DISPID_PROP_ADV_CLEARTEXTPASSWORD	( 186 )

#define	DISPID_PROP_ADV_DISPLAYCONNECTIONBAR	( 187 )

#define	DISPID_PROP_ADV_PINCONNECTIONBAR	( 188 )

#define	DISPID_PROP_ADV_GRABFOCUSONCONNECT	( 189 )

#define	DISPID_PROP_ADV_LOADBALANCE_INFO	( 190 )

#define	DISPID_PROP_ADV_REDIRECT_DRIVES	( 191 )

#define	DISPID_PROP_ADV_REDIRECT_PRINTERS	( 192 )

#define	DISPID_PROP_ADV_REDIRECT_PORTS	( 193 )

#define	DISPID_PROP_ADV_REDIRECT_SMARTCARDS	( 194 )

#define	DISPID_PROP_ADV_BITMAPVIRTUALCACHE16BPPSIZE	( 195 )

#define	DISPID_PROP_ADV_BITMAPVIRTUALCACHE24BPPSIZE	( 196 )

#define	DISIPD_PROP_ADV_PERFORMANCEFLAGS	( 200 )

#define	DISPID_PROP_ADV_RDPDR_CLIPCLEANTEMPDIR_STRING	( 201 )

#define	DISPID_PROP_ADV_RDPDR_CLIPPASTEINFO_STRING	( 202 )

#define	DISPID_PROP_ADV_CONNECTIONSOCKET	( 203 )

#define	DISPID_PROP_ADV_NOTIFYTSPUBLICKEY	( 204 )

#define	DISPID_PROP_ADV_CANAUTORECONNECT	( 205 )

#define	DISPID_PROP_ADV_ENABLEAUTORECONNECT	( 206 )

#define	DISPID_PROP_ADV_MAXRECONNECTATTEMPTS	( 207 )

#define	DISPID_PROP_ADV_CONBAR_SHOWMINIMIZE	( 210 )

#define	DISPID_PROP_ADV_CONBAR_SHOWRESTORE	( 211 )

#define	DISPID_PROP_ADV_AUTH_LEVEL	( 212 )

#define	DISPID_PROP_ADV_PUBLIC_MODE	( 213 )

#define	DISPID_PROP_ADV_REDIRECT_CLIPBOARD	( 214 )

#define	DISPID_PROP_ADV_CLEARTEXT_SC_PIN	( 215 )

#define	DISPID_PROP_ADV_PROMPT_FOR_SC_INSERTION	( 216 )

#define	DISPID_PROP_ADV_AUDIO_REDIRECTION_MODE	( 217 )

#define	DISPID_PROP_ADV_REDIECT_DESKTOP	( 218 )

#define	DISPID_PROP_ADV_REDIRECT_MYDOCS	( 219 )

#define	DISPID_PROP_ADV_HIDE_SERVER_LOCAL_DRIVES	( 220 )

#define	DISPID_PROP_ADV_HIDE_SERVER_NETWORK_DRIVES	( 221 )

#define	DISPID_PROP_ADV_CONBAR_SHOWPIN	( 222 )

#define	DISPID_PROP_SECURED_STARTPROGRAM	( 1 )

#define	DISPID_PROP_SECURED_WORKDIR	( 2 )

#define	DISPID_PROP_SECURED_FULLSCREEN	( 3 )

#define	DISPID_PROP_SECURED_KEYBOARD_HOOKING_MODE	( 4 )

#define	DISPID_PROP_SECURED_AUDIO_REDIRECTION_MODE	( 5 )

#define	DISPID_PROP_DBG_HATCH_BMP_PDU	( 200 )

#define	DISPID_PROP_DBG_HATCH_SSB_ORDER	( 201 )

#define	DISPID_PROP_DBG_HATCH_MEMBLT_ORDER	( 202 )

#define	DISPID_PROP_DBG_HATCH_INDEX_PDU	( 203 )

#define	DISPID_PROP_DBG_LABEL_MEMBLT	( 204 )

#define	DISPID_PROP_DBG_BMP_CACHE_MON	( 205 )

#define	DISPID_PROP_DBG_MALLOC_FAILURES	( 206 )

#define	DISPID_PROP_DBG_MALLOC_HUGE_FAILURES	( 207 )

#define	DISPID_PROP_DBG_NET_THRUPUT	( 208 )

#define	DISPID_PROP_DBG_CLX_CMDLINE	( 209 )

#define	DISPID_PROP_DBG_CLX_CLXDLL	( 210 )

#define	DISPID_PROP_RAIL_REMOTEAPPLICATIONMODE	( 200 )

#define	DISPID_RAIL_SERVER_START_APPLICATION	( 201 )

#define	DISPID_PROP_TRANSPORT_HTTP_PROXYURL	( 210 )

#define	DISPID_PROP_TRANSPORT_HTTP_PROXYUSERNAME	( 211 )

#define	DISPID_PROP_TRANSPORT_HTTP_PROXYDOMAIN	( 212 )

#define	DISPID_PROP_TRANSPORT_HTTP_PROXYPASSWORD	( 213 )

#define	DISPID_PROP_TRANSPORT_HTTP_PROXYUSAGEMETHOD	( 214 )

#define	DISPID_PROP_TRANSPORT_HTTP_PROXYCREDSSOURCE	( 215 )

#define	DISPID_METHOD_RESET_PROXYPASSWORD	( 216 )

#define	DISPID_PROP_TRANSPORT_PROXYPIN	( 217 )

#define	DISPID_METHOD_RESET_PROXYPIN	( 218 )

#define	DISPID_METHOD_CLIENTSHELL_LAUNCH	( 201 )

#define	DISPID_PROP_CLIENTSHELL_RDPFILE_CONTENTS	( 202 )

#define	DISPID_METHOD_CLIENTSHELL_SET_RDPPROPERTY	( 203 )

#define	DISPID_METHOD_CLIENTSHELL_GET_RDPPROPERTY	( 204 )

#define	DISPID_PROP_CLIENTSHELL_REMOTE_APP_CLIENT_INSTALLED	( 205 )

#define	DISPID_PROP_CLIENTSHELL_VERSION_MAJOR	( 206 )

#define	DISPID_PROP_CLIENTSHELL_VERSION_MINOR	( 207 )

#define	DISPID_PROP_CLIENTSHELL_VERSION_BUILD	( 208 )

#define	DISPID_PROP_CLIENTSHELL_VERSION_QFE	( 209 )

#define	DISPID_PROP_CLIENTSHELL_VERSION_STRING	( 210 )

#define	DISPID_PROP_CLIENTSHELL_PUBLIC_MODE	( 211 )

#define	DISPID_METHOD_CLIENTSHELL_SHOW_TRUSTED_SITES_DLG	( 212 )

#define	DISPID_PROP_CLEARTEXTPASSWORD	( 1 )

#define	DISPID_PROP_PORTABLEPASSWORD	( 2 )

#define	DISPID_PROP_PORTABLESALT	( 3 )

#define	DISPID_PROP_BINARYPASSWORD	( 4 )

#define	DISPID_PROP_BINARYSALT	( 5 )

#define	DISPID_METHOD_RESETPASSWORD	( 10 )

#define	DISPID_METHOD_NOTIFY_REDIRECT_DEVICE_CHANGE	( 11 )

#define	DISPID_METHOD_SENDKEYS	( 12 )

#define	DISPID_PROP_UI_PARENT_WINDOW_HANDLE	( 13 )

#define	DISPID_PROP_SHOW_RDRWARN_DLG	( 14 )

#define	DISPID_CONNECTING	( 1 )

#define	DISPID_CONNECTED	( 2 )

#define	DISPID_LOGINCOMPLETE	( 3 )

#define	DISPID_DISCONNECTED	( 4 )

#define	DISPID_ENTERFULLSCREENMODE	( 5 )

#define	DISPID_LEAVEFULLSCREENMODE	( 6 )

#define	DISPID_CHANNELRECEIVEDDATA	( 7 )

#define	DISPID_REQUESTGOFULLSCREEN	( 8 )

#define	DISPID_REQUESTLEAVEFULLSCREEN	( 9 )

#define	DISPID_FATALERROR	( 10 )

#define	DISPID_WARNING	( 11 )

#define	DISPID_REMOTEDESKTOPSIZECHANGE	( 12 )

#define	DISPID_IDLETIMEOUTNOTIFICATION	( 13 )

#define	DISPID_REQUESTCONTAINERMINIMIZE	( 14 )

#define	DISPID_CONFIRMCLOSE	( 15 )

#define	DISPID_RECEVIEDTSPUBLICKEY	( 16 )

#define	DISPID_AUTORECONNECTING	( 17 )

#define	DISPID_INTERNALDIALOGDISPLAYED	( 18 )

#define	DISPID_INTERNALDIALOGDISMISSED	( 19 )

#define	DISPID_ONREMOTEAPPLICATIONRESULT	( 20 )

#define	DISPID_ONREMOTEAPPLICATIONDISPLAYED	( 21 )

#define	DISPID_LOGONERROR	( 22 )

#define	DISPID_CREDSINFO	( 23 )

#define	DISPID_AXTOCONTAINER	( 24 )



extern RPC_IF_HANDLE __MIDL_itf_mstsax_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstsax_0000_v0_0_s_ifspec;

#ifndef __IMsTscNonScriptable_INTERFACE_DEFINED__
#define __IMsTscNonScriptable_INTERFACE_DEFINED__

/* interface IMsTscNonScriptable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMsTscNonScriptable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c1e6743a-41c1-4a74-832a-0dd06c1c7a0e")
    IMsTscNonScriptable : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClearTextPassword( 
            /* [in] */ BSTR newClearTextPass) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PortablePassword( 
            /* [in] */ BSTR newPortablePassVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PortablePassword( 
            /* [retval][out] */ BSTR __RPC_FAR *pPortablePass) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PortableSalt( 
            /* [in] */ BSTR newPortableSalt) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PortableSalt( 
            /* [retval][out] */ BSTR __RPC_FAR *pPortableSalt) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BinaryPassword( 
            /* [in] */ BSTR newPassword) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BinaryPassword( 
            /* [retval][out] */ BSTR __RPC_FAR *pBinaryPassword) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BinarySalt( 
            /* [in] */ BSTR newSalt) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BinarySalt( 
            /* [retval][out] */ BSTR __RPC_FAR *pSalt) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetPassword( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsTscNonScriptableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsTscNonScriptable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsTscNonScriptable __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newClearTextPass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortablePassword )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newPortablePassVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortablePassword )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortablePass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortableSalt )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newPortableSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortableSalt )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortableSalt);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinaryPassword )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newPassword);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinaryPassword )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pBinaryPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinarySalt )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinarySalt )( 
            IMsTscNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pSalt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassword )( 
            IMsTscNonScriptable __RPC_FAR * This);
        
        END_INTERFACE
    } IMsTscNonScriptableVtbl;

    interface IMsTscNonScriptable
    {
        CONST_VTBL struct IMsTscNonScriptableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsTscNonScriptable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsTscNonScriptable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsTscNonScriptable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsTscNonScriptable_put_ClearTextPassword(This,newClearTextPass)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,newClearTextPass)

#define IMsTscNonScriptable_put_PortablePassword(This,newPortablePassVal)	\
    (This)->lpVtbl -> put_PortablePassword(This,newPortablePassVal)

#define IMsTscNonScriptable_get_PortablePassword(This,pPortablePass)	\
    (This)->lpVtbl -> get_PortablePassword(This,pPortablePass)

#define IMsTscNonScriptable_put_PortableSalt(This,newPortableSalt)	\
    (This)->lpVtbl -> put_PortableSalt(This,newPortableSalt)

#define IMsTscNonScriptable_get_PortableSalt(This,pPortableSalt)	\
    (This)->lpVtbl -> get_PortableSalt(This,pPortableSalt)

#define IMsTscNonScriptable_put_BinaryPassword(This,newPassword)	\
    (This)->lpVtbl -> put_BinaryPassword(This,newPassword)

#define IMsTscNonScriptable_get_BinaryPassword(This,pBinaryPassword)	\
    (This)->lpVtbl -> get_BinaryPassword(This,pBinaryPassword)

#define IMsTscNonScriptable_put_BinarySalt(This,newSalt)	\
    (This)->lpVtbl -> put_BinarySalt(This,newSalt)

#define IMsTscNonScriptable_get_BinarySalt(This,pSalt)	\
    (This)->lpVtbl -> get_BinarySalt(This,pSalt)

#define IMsTscNonScriptable_ResetPassword(This)	\
    (This)->lpVtbl -> ResetPassword(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_put_ClearTextPassword_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [in] */ BSTR newClearTextPass);


void __RPC_STUB IMsTscNonScriptable_put_ClearTextPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_put_PortablePassword_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [in] */ BSTR newPortablePassVal);


void __RPC_STUB IMsTscNonScriptable_put_PortablePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_get_PortablePassword_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pPortablePass);


void __RPC_STUB IMsTscNonScriptable_get_PortablePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_put_PortableSalt_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [in] */ BSTR newPortableSalt);


void __RPC_STUB IMsTscNonScriptable_put_PortableSalt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_get_PortableSalt_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pPortableSalt);


void __RPC_STUB IMsTscNonScriptable_get_PortableSalt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_put_BinaryPassword_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [in] */ BSTR newPassword);


void __RPC_STUB IMsTscNonScriptable_put_BinaryPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_get_BinaryPassword_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pBinaryPassword);


void __RPC_STUB IMsTscNonScriptable_get_BinaryPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_put_BinarySalt_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [in] */ BSTR newSalt);


void __RPC_STUB IMsTscNonScriptable_put_BinarySalt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_get_BinarySalt_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pSalt);


void __RPC_STUB IMsTscNonScriptable_get_BinarySalt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsTscNonScriptable_ResetPassword_Proxy( 
    IMsTscNonScriptable __RPC_FAR * This);


void __RPC_STUB IMsTscNonScriptable_ResetPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsTscNonScriptable_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientNonScriptable_INTERFACE_DEFINED__
#define __IMsRdpClientNonScriptable_INTERFACE_DEFINED__

/* interface IMsRdpClientNonScriptable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientNonScriptable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2f079c4c-87b2-4afd-97ab-20cdb43038ae")
    IMsRdpClientNonScriptable : public IMsTscNonScriptable
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRedirectDeviceChange( 
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendKeys( 
            /* [in] */ LONG numKeys,
            /* [in] */ VARIANT_BOOL __RPC_FAR *pbArrayKeyUp,
            /* [in] */ LONG __RPC_FAR *plKeyData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientNonScriptableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientNonScriptable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientNonScriptable __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newClearTextPass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortablePassword )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newPortablePassVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortablePassword )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortablePass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortableSalt )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newPortableSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortableSalt )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortableSalt);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinaryPassword )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newPassword);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinaryPassword )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pBinaryPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinarySalt )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ BSTR newSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinarySalt )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pSalt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassword )( 
            IMsRdpClientNonScriptable __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyRedirectDeviceChange )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendKeys )( 
            IMsRdpClientNonScriptable __RPC_FAR * This,
            /* [in] */ LONG numKeys,
            /* [in] */ VARIANT_BOOL __RPC_FAR *pbArrayKeyUp,
            /* [in] */ LONG __RPC_FAR *plKeyData);
        
        END_INTERFACE
    } IMsRdpClientNonScriptableVtbl;

    interface IMsRdpClientNonScriptable
    {
        CONST_VTBL struct IMsRdpClientNonScriptableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientNonScriptable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientNonScriptable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientNonScriptable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientNonScriptable_put_ClearTextPassword(This,newClearTextPass)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,newClearTextPass)

#define IMsRdpClientNonScriptable_put_PortablePassword(This,newPortablePassVal)	\
    (This)->lpVtbl -> put_PortablePassword(This,newPortablePassVal)

#define IMsRdpClientNonScriptable_get_PortablePassword(This,pPortablePass)	\
    (This)->lpVtbl -> get_PortablePassword(This,pPortablePass)

#define IMsRdpClientNonScriptable_put_PortableSalt(This,newPortableSalt)	\
    (This)->lpVtbl -> put_PortableSalt(This,newPortableSalt)

#define IMsRdpClientNonScriptable_get_PortableSalt(This,pPortableSalt)	\
    (This)->lpVtbl -> get_PortableSalt(This,pPortableSalt)

#define IMsRdpClientNonScriptable_put_BinaryPassword(This,newPassword)	\
    (This)->lpVtbl -> put_BinaryPassword(This,newPassword)

#define IMsRdpClientNonScriptable_get_BinaryPassword(This,pBinaryPassword)	\
    (This)->lpVtbl -> get_BinaryPassword(This,pBinaryPassword)

#define IMsRdpClientNonScriptable_put_BinarySalt(This,newSalt)	\
    (This)->lpVtbl -> put_BinarySalt(This,newSalt)

#define IMsRdpClientNonScriptable_get_BinarySalt(This,pSalt)	\
    (This)->lpVtbl -> get_BinarySalt(This,pSalt)

#define IMsRdpClientNonScriptable_ResetPassword(This)	\
    (This)->lpVtbl -> ResetPassword(This)


#define IMsRdpClientNonScriptable_NotifyRedirectDeviceChange(This,wParam,lParam)	\
    (This)->lpVtbl -> NotifyRedirectDeviceChange(This,wParam,lParam)

#define IMsRdpClientNonScriptable_SendKeys(This,numKeys,pbArrayKeyUp,plKeyData)	\
    (This)->lpVtbl -> SendKeys(This,numKeys,pbArrayKeyUp,plKeyData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientNonScriptable_NotifyRedirectDeviceChange_Proxy( 
    IMsRdpClientNonScriptable __RPC_FAR * This,
    /* [in] */ WPARAM wParam,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IMsRdpClientNonScriptable_NotifyRedirectDeviceChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientNonScriptable_SendKeys_Proxy( 
    IMsRdpClientNonScriptable __RPC_FAR * This,
    /* [in] */ LONG numKeys,
    /* [in] */ VARIANT_BOOL __RPC_FAR *pbArrayKeyUp,
    /* [in] */ LONG __RPC_FAR *plKeyData);


void __RPC_STUB IMsRdpClientNonScriptable_SendKeys_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientNonScriptable_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientNonScriptable2_INTERFACE_DEFINED__
#define __IMsRdpClientNonScriptable2_INTERFACE_DEFINED__

/* interface IMsRdpClientNonScriptable2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientNonScriptable2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("17a5e535-4072-4fa4-af32-c8d0d47345e9")
    IMsRdpClientNonScriptable2 : public IMsRdpClientNonScriptable
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UIParentWindowHandle( 
            /* [in] */ HWND hwndUIParentWindowHandle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UIParentWindowHandle( 
            /* [retval][out] */ HWND __RPC_FAR *phwndUIParentWindowHandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientNonScriptable2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ BSTR newClearTextPass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortablePassword )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ BSTR newPortablePassVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortablePassword )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortablePass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortableSalt )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ BSTR newPortableSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortableSalt )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortableSalt);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinaryPassword )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ BSTR newPassword);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinaryPassword )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pBinaryPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinarySalt )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ BSTR newSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinarySalt )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pSalt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassword )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyRedirectDeviceChange )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendKeys )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ LONG numKeys,
            /* [in] */ VARIANT_BOOL __RPC_FAR *pbArrayKeyUp,
            /* [in] */ LONG __RPC_FAR *plKeyData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UIParentWindowHandle )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [in] */ HWND hwndUIParentWindowHandle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UIParentWindowHandle )( 
            IMsRdpClientNonScriptable2 __RPC_FAR * This,
            /* [retval][out] */ HWND __RPC_FAR *phwndUIParentWindowHandle);
        
        END_INTERFACE
    } IMsRdpClientNonScriptable2Vtbl;

    interface IMsRdpClientNonScriptable2
    {
        CONST_VTBL struct IMsRdpClientNonScriptable2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientNonScriptable2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientNonScriptable2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientNonScriptable2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientNonScriptable2_put_ClearTextPassword(This,newClearTextPass)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,newClearTextPass)

#define IMsRdpClientNonScriptable2_put_PortablePassword(This,newPortablePassVal)	\
    (This)->lpVtbl -> put_PortablePassword(This,newPortablePassVal)

#define IMsRdpClientNonScriptable2_get_PortablePassword(This,pPortablePass)	\
    (This)->lpVtbl -> get_PortablePassword(This,pPortablePass)

#define IMsRdpClientNonScriptable2_put_PortableSalt(This,newPortableSalt)	\
    (This)->lpVtbl -> put_PortableSalt(This,newPortableSalt)

#define IMsRdpClientNonScriptable2_get_PortableSalt(This,pPortableSalt)	\
    (This)->lpVtbl -> get_PortableSalt(This,pPortableSalt)

#define IMsRdpClientNonScriptable2_put_BinaryPassword(This,newPassword)	\
    (This)->lpVtbl -> put_BinaryPassword(This,newPassword)

#define IMsRdpClientNonScriptable2_get_BinaryPassword(This,pBinaryPassword)	\
    (This)->lpVtbl -> get_BinaryPassword(This,pBinaryPassword)

#define IMsRdpClientNonScriptable2_put_BinarySalt(This,newSalt)	\
    (This)->lpVtbl -> put_BinarySalt(This,newSalt)

#define IMsRdpClientNonScriptable2_get_BinarySalt(This,pSalt)	\
    (This)->lpVtbl -> get_BinarySalt(This,pSalt)

#define IMsRdpClientNonScriptable2_ResetPassword(This)	\
    (This)->lpVtbl -> ResetPassword(This)


#define IMsRdpClientNonScriptable2_NotifyRedirectDeviceChange(This,wParam,lParam)	\
    (This)->lpVtbl -> NotifyRedirectDeviceChange(This,wParam,lParam)

#define IMsRdpClientNonScriptable2_SendKeys(This,numKeys,pbArrayKeyUp,plKeyData)	\
    (This)->lpVtbl -> SendKeys(This,numKeys,pbArrayKeyUp,plKeyData)


#define IMsRdpClientNonScriptable2_put_UIParentWindowHandle(This,hwndUIParentWindowHandle)	\
    (This)->lpVtbl -> put_UIParentWindowHandle(This,hwndUIParentWindowHandle)

#define IMsRdpClientNonScriptable2_get_UIParentWindowHandle(This,phwndUIParentWindowHandle)	\
    (This)->lpVtbl -> get_UIParentWindowHandle(This,phwndUIParentWindowHandle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientNonScriptable2_put_UIParentWindowHandle_Proxy( 
    IMsRdpClientNonScriptable2 __RPC_FAR * This,
    /* [in] */ HWND hwndUIParentWindowHandle);


void __RPC_STUB IMsRdpClientNonScriptable2_put_UIParentWindowHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientNonScriptable2_get_UIParentWindowHandle_Proxy( 
    IMsRdpClientNonScriptable2 __RPC_FAR * This,
    /* [retval][out] */ HWND __RPC_FAR *phwndUIParentWindowHandle);


void __RPC_STUB IMsRdpClientNonScriptable2_get_UIParentWindowHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientNonScriptable2_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientNonScriptable3_INTERFACE_DEFINED__
#define __IMsRdpClientNonScriptable3_INTERFACE_DEFINED__

/* interface IMsRdpClientNonScriptable3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientNonScriptable3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b3378d90-0728-45c7-8ed7-b6159fb92219")
    IMsRdpClientNonScriptable3 : public IMsRdpClientNonScriptable2
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowRedirectionWarningDialog( 
            /* [in] */ VARIANT_BOOL fShowRdrDlg) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowRedirectionWarningDialog( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRdrDlg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientNonScriptable3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ BSTR newClearTextPass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortablePassword )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ BSTR newPortablePassVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortablePassword )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortablePass);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortableSalt )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ BSTR newPortableSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortableSalt )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPortableSalt);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinaryPassword )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ BSTR newPassword);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinaryPassword )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pBinaryPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BinarySalt )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ BSTR newSalt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BinarySalt )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pSalt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassword )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyRedirectDeviceChange )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendKeys )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ LONG numKeys,
            /* [in] */ VARIANT_BOOL __RPC_FAR *pbArrayKeyUp,
            /* [in] */ LONG __RPC_FAR *plKeyData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UIParentWindowHandle )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ HWND hwndUIParentWindowHandle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UIParentWindowHandle )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [retval][out] */ HWND __RPC_FAR *phwndUIParentWindowHandle);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowRedirectionWarningDialog )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowRdrDlg);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowRedirectionWarningDialog )( 
            IMsRdpClientNonScriptable3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRdrDlg);
        
        END_INTERFACE
    } IMsRdpClientNonScriptable3Vtbl;

    interface IMsRdpClientNonScriptable3
    {
        CONST_VTBL struct IMsRdpClientNonScriptable3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientNonScriptable3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientNonScriptable3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientNonScriptable3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientNonScriptable3_put_ClearTextPassword(This,newClearTextPass)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,newClearTextPass)

#define IMsRdpClientNonScriptable3_put_PortablePassword(This,newPortablePassVal)	\
    (This)->lpVtbl -> put_PortablePassword(This,newPortablePassVal)

#define IMsRdpClientNonScriptable3_get_PortablePassword(This,pPortablePass)	\
    (This)->lpVtbl -> get_PortablePassword(This,pPortablePass)

#define IMsRdpClientNonScriptable3_put_PortableSalt(This,newPortableSalt)	\
    (This)->lpVtbl -> put_PortableSalt(This,newPortableSalt)

#define IMsRdpClientNonScriptable3_get_PortableSalt(This,pPortableSalt)	\
    (This)->lpVtbl -> get_PortableSalt(This,pPortableSalt)

#define IMsRdpClientNonScriptable3_put_BinaryPassword(This,newPassword)	\
    (This)->lpVtbl -> put_BinaryPassword(This,newPassword)

#define IMsRdpClientNonScriptable3_get_BinaryPassword(This,pBinaryPassword)	\
    (This)->lpVtbl -> get_BinaryPassword(This,pBinaryPassword)

#define IMsRdpClientNonScriptable3_put_BinarySalt(This,newSalt)	\
    (This)->lpVtbl -> put_BinarySalt(This,newSalt)

#define IMsRdpClientNonScriptable3_get_BinarySalt(This,pSalt)	\
    (This)->lpVtbl -> get_BinarySalt(This,pSalt)

#define IMsRdpClientNonScriptable3_ResetPassword(This)	\
    (This)->lpVtbl -> ResetPassword(This)


#define IMsRdpClientNonScriptable3_NotifyRedirectDeviceChange(This,wParam,lParam)	\
    (This)->lpVtbl -> NotifyRedirectDeviceChange(This,wParam,lParam)

#define IMsRdpClientNonScriptable3_SendKeys(This,numKeys,pbArrayKeyUp,plKeyData)	\
    (This)->lpVtbl -> SendKeys(This,numKeys,pbArrayKeyUp,plKeyData)


#define IMsRdpClientNonScriptable3_put_UIParentWindowHandle(This,hwndUIParentWindowHandle)	\
    (This)->lpVtbl -> put_UIParentWindowHandle(This,hwndUIParentWindowHandle)

#define IMsRdpClientNonScriptable3_get_UIParentWindowHandle(This,phwndUIParentWindowHandle)	\
    (This)->lpVtbl -> get_UIParentWindowHandle(This,phwndUIParentWindowHandle)


#define IMsRdpClientNonScriptable3_put_ShowRedirectionWarningDialog(This,fShowRdrDlg)	\
    (This)->lpVtbl -> put_ShowRedirectionWarningDialog(This,fShowRdrDlg)

#define IMsRdpClientNonScriptable3_get_ShowRedirectionWarningDialog(This,pfShowRdrDlg)	\
    (This)->lpVtbl -> get_ShowRedirectionWarningDialog(This,pfShowRdrDlg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientNonScriptable3_put_ShowRedirectionWarningDialog_Proxy( 
    IMsRdpClientNonScriptable3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fShowRdrDlg);


void __RPC_STUB IMsRdpClientNonScriptable3_put_ShowRedirectionWarningDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientNonScriptable3_get_ShowRedirectionWarningDialog_Proxy( 
    IMsRdpClientNonScriptable3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRdrDlg);


void __RPC_STUB IMsRdpClientNonScriptable3_get_ShowRedirectionWarningDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientNonScriptable3_INTERFACE_DEFINED__ */


#ifndef __IMsTscSecuredSettings_INTERFACE_DEFINED__
#define __IMsTscSecuredSettings_INTERFACE_DEFINED__

/* interface IMsTscSecuredSettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsTscSecuredSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c9d65442-a0f9-45b2-8f73-d61d2db8cbb6")
    IMsTscSecuredSettings : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartProgram( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartProgram( 
            /* [retval][out] */ BSTR __RPC_FAR *pStartProgram) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WorkDir( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WorkDir( 
            /* [retval][out] */ BSTR __RPC_FAR *pWorkDir) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FullScreen( 
            /* [in] */ BOOL fFullScreen) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FullScreen( 
            /* [retval][out] */ BOOL __RPC_FAR *pfFullScreen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsTscSecuredSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsTscSecuredSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsTscSecuredSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartProgram )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartProgram )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pStartProgram);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WorkDir )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WorkDir )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pWorkDir);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [in] */ BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsTscSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfFullScreen);
        
        END_INTERFACE
    } IMsTscSecuredSettingsVtbl;

    interface IMsTscSecuredSettings
    {
        CONST_VTBL struct IMsTscSecuredSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsTscSecuredSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsTscSecuredSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsTscSecuredSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsTscSecuredSettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsTscSecuredSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsTscSecuredSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsTscSecuredSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsTscSecuredSettings_put_StartProgram(This,newVal)	\
    (This)->lpVtbl -> put_StartProgram(This,newVal)

#define IMsTscSecuredSettings_get_StartProgram(This,pStartProgram)	\
    (This)->lpVtbl -> get_StartProgram(This,pStartProgram)

#define IMsTscSecuredSettings_put_WorkDir(This,newVal)	\
    (This)->lpVtbl -> put_WorkDir(This,newVal)

#define IMsTscSecuredSettings_get_WorkDir(This,pWorkDir)	\
    (This)->lpVtbl -> get_WorkDir(This,pWorkDir)

#define IMsTscSecuredSettings_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsTscSecuredSettings_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscSecuredSettings_put_StartProgram_Proxy( 
    IMsTscSecuredSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscSecuredSettings_put_StartProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscSecuredSettings_get_StartProgram_Proxy( 
    IMsTscSecuredSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pStartProgram);


void __RPC_STUB IMsTscSecuredSettings_get_StartProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscSecuredSettings_put_WorkDir_Proxy( 
    IMsTscSecuredSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscSecuredSettings_put_WorkDir_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscSecuredSettings_get_WorkDir_Proxy( 
    IMsTscSecuredSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pWorkDir);


void __RPC_STUB IMsTscSecuredSettings_get_WorkDir_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscSecuredSettings_put_FullScreen_Proxy( 
    IMsTscSecuredSettings __RPC_FAR * This,
    /* [in] */ BOOL fFullScreen);


void __RPC_STUB IMsTscSecuredSettings_put_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscSecuredSettings_get_FullScreen_Proxy( 
    IMsTscSecuredSettings __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfFullScreen);


void __RPC_STUB IMsTscSecuredSettings_get_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsTscSecuredSettings_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientSecuredSettings_INTERFACE_DEFINED__
#define __IMsRdpClientSecuredSettings_INTERFACE_DEFINED__

/* interface IMsRdpClientSecuredSettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientSecuredSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("605befcf-39c1-45cc-a811-068fb7be346d")
    IMsRdpClientSecuredSettings : public IMsTscSecuredSettings
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyboardHookMode( 
            /* [in] */ LONG keyboardHookMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyboardHookMode( 
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardHookMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioRedirectionMode( 
            /* [in] */ LONG audioRedirectionMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioRedirectionMode( 
            /* [retval][out] */ LONG __RPC_FAR *pAudioRedirectionMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientSecuredSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartProgram )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartProgram )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pStartProgram);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WorkDir )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WorkDir )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pWorkDir);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardHookMode )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ LONG keyboardHookMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardHookMode )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardHookMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AudioRedirectionMode )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [in] */ LONG audioRedirectionMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioRedirectionMode )( 
            IMsRdpClientSecuredSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pAudioRedirectionMode);
        
        END_INTERFACE
    } IMsRdpClientSecuredSettingsVtbl;

    interface IMsRdpClientSecuredSettings
    {
        CONST_VTBL struct IMsRdpClientSecuredSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientSecuredSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientSecuredSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientSecuredSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientSecuredSettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientSecuredSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientSecuredSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientSecuredSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientSecuredSettings_put_StartProgram(This,newVal)	\
    (This)->lpVtbl -> put_StartProgram(This,newVal)

#define IMsRdpClientSecuredSettings_get_StartProgram(This,pStartProgram)	\
    (This)->lpVtbl -> get_StartProgram(This,pStartProgram)

#define IMsRdpClientSecuredSettings_put_WorkDir(This,newVal)	\
    (This)->lpVtbl -> put_WorkDir(This,newVal)

#define IMsRdpClientSecuredSettings_get_WorkDir(This,pWorkDir)	\
    (This)->lpVtbl -> get_WorkDir(This,pWorkDir)

#define IMsRdpClientSecuredSettings_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsRdpClientSecuredSettings_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)


#define IMsRdpClientSecuredSettings_put_KeyboardHookMode(This,keyboardHookMode)	\
    (This)->lpVtbl -> put_KeyboardHookMode(This,keyboardHookMode)

#define IMsRdpClientSecuredSettings_get_KeyboardHookMode(This,pkeyboardHookMode)	\
    (This)->lpVtbl -> get_KeyboardHookMode(This,pkeyboardHookMode)

#define IMsRdpClientSecuredSettings_put_AudioRedirectionMode(This,audioRedirectionMode)	\
    (This)->lpVtbl -> put_AudioRedirectionMode(This,audioRedirectionMode)

#define IMsRdpClientSecuredSettings_get_AudioRedirectionMode(This,pAudioRedirectionMode)	\
    (This)->lpVtbl -> get_AudioRedirectionMode(This,pAudioRedirectionMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientSecuredSettings_put_KeyboardHookMode_Proxy( 
    IMsRdpClientSecuredSettings __RPC_FAR * This,
    /* [in] */ LONG keyboardHookMode);


void __RPC_STUB IMsRdpClientSecuredSettings_put_KeyboardHookMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientSecuredSettings_get_KeyboardHookMode_Proxy( 
    IMsRdpClientSecuredSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pkeyboardHookMode);


void __RPC_STUB IMsRdpClientSecuredSettings_get_KeyboardHookMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientSecuredSettings_put_AudioRedirectionMode_Proxy( 
    IMsRdpClientSecuredSettings __RPC_FAR * This,
    /* [in] */ LONG audioRedirectionMode);


void __RPC_STUB IMsRdpClientSecuredSettings_put_AudioRedirectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientSecuredSettings_get_AudioRedirectionMode_Proxy( 
    IMsRdpClientSecuredSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pAudioRedirectionMode);


void __RPC_STUB IMsRdpClientSecuredSettings_get_AudioRedirectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientSecuredSettings_INTERFACE_DEFINED__ */


#ifndef __IMsTscDebug_INTERFACE_DEFINED__
#define __IMsTscDebug_INTERFACE_DEFINED__

/* interface IMsTscDebug */
/* [unique][helpstring][dual][hidden][uuid][object] */ 


EXTERN_C const IID IID_IMsTscDebug;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("209d0eb9-6254-47b1-9033-a98dae55bb27")
    IMsTscDebug : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HatchBitmapPDU( 
            /* [in] */ BOOL hatchBitmapPDU) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HatchBitmapPDU( 
            /* [retval][out] */ BOOL __RPC_FAR *phatchBitmapPDU) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HatchSSBOrder( 
            /* [in] */ BOOL hatchSSBOrder) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HatchSSBOrder( 
            /* [retval][out] */ BOOL __RPC_FAR *phatchSSBOrder) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HatchMembltOrder( 
            /* [in] */ BOOL hatchMembltOrder) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HatchMembltOrder( 
            /* [retval][out] */ BOOL __RPC_FAR *phatchMembltOrder) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HatchIndexPDU( 
            /* [in] */ BOOL hatchIndexPDU) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HatchIndexPDU( 
            /* [retval][out] */ BOOL __RPC_FAR *phatchIndexPDU) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LabelMemblt( 
            /* [in] */ BOOL labelMemblt) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LabelMemblt( 
            /* [retval][out] */ BOOL __RPC_FAR *plabelMemblt) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapCacheMonitor( 
            /* [in] */ BOOL bitmapCacheMonitor) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapCacheMonitor( 
            /* [retval][out] */ BOOL __RPC_FAR *pbitmapCacheMonitor) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MallocFailuresPercent( 
            /* [in] */ LONG mallocFailures) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MallocFailuresPercent( 
            /* [retval][out] */ LONG __RPC_FAR *pmallocFailuresPercent) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MallocHugeFailuresPercent( 
            /* [in] */ LONG mallocHugeFailures) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MallocHugeFailuresPercent( 
            /* [retval][out] */ LONG __RPC_FAR *pmallocHugeFailuresPercent) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NetThroughput( 
            /* [in] */ LONG netThroughput) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NetThroughput( 
            /* [retval][out] */ LONG __RPC_FAR *netThroughput) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CLXCmdLine( 
            /* [in] */ BSTR CLXCmdLine) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CLXCmdLine( 
            /* [retval][out] */ BSTR __RPC_FAR *pCLXCmdLine) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CLXDll( 
            /* [in] */ BSTR CLXDll) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CLXDll( 
            /* [retval][out] */ BSTR __RPC_FAR *pCLXDll) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsTscDebugVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsTscDebug __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsTscDebug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsTscDebug __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HatchBitmapPDU )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BOOL hatchBitmapPDU);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HatchBitmapPDU )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *phatchBitmapPDU);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HatchSSBOrder )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BOOL hatchSSBOrder);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HatchSSBOrder )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *phatchSSBOrder);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HatchMembltOrder )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BOOL hatchMembltOrder);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HatchMembltOrder )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *phatchMembltOrder);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HatchIndexPDU )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BOOL hatchIndexPDU);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HatchIndexPDU )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *phatchIndexPDU);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LabelMemblt )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BOOL labelMemblt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelMemblt )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *plabelMemblt);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapCacheMonitor )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BOOL bitmapCacheMonitor);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapCacheMonitor )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbitmapCacheMonitor);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MallocFailuresPercent )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ LONG mallocFailures);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MallocFailuresPercent )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmallocFailuresPercent);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MallocHugeFailuresPercent )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ LONG mallocHugeFailures);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MallocHugeFailuresPercent )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmallocHugeFailuresPercent);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NetThroughput )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ LONG netThroughput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetThroughput )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *netThroughput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CLXCmdLine )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BSTR CLXCmdLine);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CLXCmdLine )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pCLXCmdLine);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CLXDll )( 
            IMsTscDebug __RPC_FAR * This,
            /* [in] */ BSTR CLXDll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CLXDll )( 
            IMsTscDebug __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pCLXDll);
        
        END_INTERFACE
    } IMsTscDebugVtbl;

    interface IMsTscDebug
    {
        CONST_VTBL struct IMsTscDebugVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsTscDebug_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsTscDebug_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsTscDebug_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsTscDebug_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsTscDebug_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsTscDebug_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsTscDebug_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsTscDebug_put_HatchBitmapPDU(This,hatchBitmapPDU)	\
    (This)->lpVtbl -> put_HatchBitmapPDU(This,hatchBitmapPDU)

#define IMsTscDebug_get_HatchBitmapPDU(This,phatchBitmapPDU)	\
    (This)->lpVtbl -> get_HatchBitmapPDU(This,phatchBitmapPDU)

#define IMsTscDebug_put_HatchSSBOrder(This,hatchSSBOrder)	\
    (This)->lpVtbl -> put_HatchSSBOrder(This,hatchSSBOrder)

#define IMsTscDebug_get_HatchSSBOrder(This,phatchSSBOrder)	\
    (This)->lpVtbl -> get_HatchSSBOrder(This,phatchSSBOrder)

#define IMsTscDebug_put_HatchMembltOrder(This,hatchMembltOrder)	\
    (This)->lpVtbl -> put_HatchMembltOrder(This,hatchMembltOrder)

#define IMsTscDebug_get_HatchMembltOrder(This,phatchMembltOrder)	\
    (This)->lpVtbl -> get_HatchMembltOrder(This,phatchMembltOrder)

#define IMsTscDebug_put_HatchIndexPDU(This,hatchIndexPDU)	\
    (This)->lpVtbl -> put_HatchIndexPDU(This,hatchIndexPDU)

#define IMsTscDebug_get_HatchIndexPDU(This,phatchIndexPDU)	\
    (This)->lpVtbl -> get_HatchIndexPDU(This,phatchIndexPDU)

#define IMsTscDebug_put_LabelMemblt(This,labelMemblt)	\
    (This)->lpVtbl -> put_LabelMemblt(This,labelMemblt)

#define IMsTscDebug_get_LabelMemblt(This,plabelMemblt)	\
    (This)->lpVtbl -> get_LabelMemblt(This,plabelMemblt)

#define IMsTscDebug_put_BitmapCacheMonitor(This,bitmapCacheMonitor)	\
    (This)->lpVtbl -> put_BitmapCacheMonitor(This,bitmapCacheMonitor)

#define IMsTscDebug_get_BitmapCacheMonitor(This,pbitmapCacheMonitor)	\
    (This)->lpVtbl -> get_BitmapCacheMonitor(This,pbitmapCacheMonitor)

#define IMsTscDebug_put_MallocFailuresPercent(This,mallocFailures)	\
    (This)->lpVtbl -> put_MallocFailuresPercent(This,mallocFailures)

#define IMsTscDebug_get_MallocFailuresPercent(This,pmallocFailuresPercent)	\
    (This)->lpVtbl -> get_MallocFailuresPercent(This,pmallocFailuresPercent)

#define IMsTscDebug_put_MallocHugeFailuresPercent(This,mallocHugeFailures)	\
    (This)->lpVtbl -> put_MallocHugeFailuresPercent(This,mallocHugeFailures)

#define IMsTscDebug_get_MallocHugeFailuresPercent(This,pmallocHugeFailuresPercent)	\
    (This)->lpVtbl -> get_MallocHugeFailuresPercent(This,pmallocHugeFailuresPercent)

#define IMsTscDebug_put_NetThroughput(This,netThroughput)	\
    (This)->lpVtbl -> put_NetThroughput(This,netThroughput)

#define IMsTscDebug_get_NetThroughput(This,netThroughput)	\
    (This)->lpVtbl -> get_NetThroughput(This,netThroughput)

#define IMsTscDebug_put_CLXCmdLine(This,CLXCmdLine)	\
    (This)->lpVtbl -> put_CLXCmdLine(This,CLXCmdLine)

#define IMsTscDebug_get_CLXCmdLine(This,pCLXCmdLine)	\
    (This)->lpVtbl -> get_CLXCmdLine(This,pCLXCmdLine)

#define IMsTscDebug_put_CLXDll(This,CLXDll)	\
    (This)->lpVtbl -> put_CLXDll(This,CLXDll)

#define IMsTscDebug_get_CLXDll(This,pCLXDll)	\
    (This)->lpVtbl -> get_CLXDll(This,pCLXDll)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_HatchBitmapPDU_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BOOL hatchBitmapPDU);


void __RPC_STUB IMsTscDebug_put_HatchBitmapPDU_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_HatchBitmapPDU_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *phatchBitmapPDU);


void __RPC_STUB IMsTscDebug_get_HatchBitmapPDU_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_HatchSSBOrder_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BOOL hatchSSBOrder);


void __RPC_STUB IMsTscDebug_put_HatchSSBOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_HatchSSBOrder_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *phatchSSBOrder);


void __RPC_STUB IMsTscDebug_get_HatchSSBOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_HatchMembltOrder_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BOOL hatchMembltOrder);


void __RPC_STUB IMsTscDebug_put_HatchMembltOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_HatchMembltOrder_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *phatchMembltOrder);


void __RPC_STUB IMsTscDebug_get_HatchMembltOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_HatchIndexPDU_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BOOL hatchIndexPDU);


void __RPC_STUB IMsTscDebug_put_HatchIndexPDU_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_HatchIndexPDU_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *phatchIndexPDU);


void __RPC_STUB IMsTscDebug_get_HatchIndexPDU_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_LabelMemblt_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BOOL labelMemblt);


void __RPC_STUB IMsTscDebug_put_LabelMemblt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_LabelMemblt_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *plabelMemblt);


void __RPC_STUB IMsTscDebug_get_LabelMemblt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_BitmapCacheMonitor_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BOOL bitmapCacheMonitor);


void __RPC_STUB IMsTscDebug_put_BitmapCacheMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_BitmapCacheMonitor_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbitmapCacheMonitor);


void __RPC_STUB IMsTscDebug_get_BitmapCacheMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_MallocFailuresPercent_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ LONG mallocFailures);


void __RPC_STUB IMsTscDebug_put_MallocFailuresPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_MallocFailuresPercent_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pmallocFailuresPercent);


void __RPC_STUB IMsTscDebug_get_MallocFailuresPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_MallocHugeFailuresPercent_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ LONG mallocHugeFailures);


void __RPC_STUB IMsTscDebug_put_MallocHugeFailuresPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_MallocHugeFailuresPercent_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pmallocHugeFailuresPercent);


void __RPC_STUB IMsTscDebug_get_MallocHugeFailuresPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_NetThroughput_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ LONG netThroughput);


void __RPC_STUB IMsTscDebug_put_NetThroughput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_NetThroughput_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *netThroughput);


void __RPC_STUB IMsTscDebug_get_NetThroughput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_CLXCmdLine_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BSTR CLXCmdLine);


void __RPC_STUB IMsTscDebug_put_CLXCmdLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_CLXCmdLine_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pCLXCmdLine);


void __RPC_STUB IMsTscDebug_get_CLXCmdLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_put_CLXDll_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [in] */ BSTR CLXDll);


void __RPC_STUB IMsTscDebug_put_CLXDll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscDebug_get_CLXDll_Proxy( 
    IMsTscDebug __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pCLXDll);


void __RPC_STUB IMsTscDebug_get_CLXDll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsTscDebug_INTERFACE_DEFINED__ */


#ifndef __ITSRemoteApplication_INTERFACE_DEFINED__
#define __ITSRemoteApplication_INTERFACE_DEFINED__

/* interface ITSRemoteApplication */
/* [unique][helpstring][dual][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITSRemoteApplication;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDD029F9-467A-4c49-8529-64B521DBD1B4")
    ITSRemoteApplication : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteApplicationMode( 
            /* [in] */ VARIANT_BOOL vboolRemoteApplicationMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteApplicationMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvboolRemoteApplicationMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ServerStartApplication( 
            /* [in] */ BSTR bstrExecutablePath,
            /* [in] */ BSTR bstrFilePath,
            /* [in] */ BSTR bstrVerb,
            /* [in] */ BSTR bstrWorkingDirectory,
            /* [in] */ VARIANT_BOOL vbExpandEnvVarInWorkingDirectoryOnServer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITSRemoteApplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITSRemoteApplication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITSRemoteApplication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteApplicationMode )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vboolRemoteApplicationMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteApplicationMode )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvboolRemoteApplicationMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ServerStartApplication )( 
            ITSRemoteApplication __RPC_FAR * This,
            /* [in] */ BSTR bstrExecutablePath,
            /* [in] */ BSTR bstrFilePath,
            /* [in] */ BSTR bstrVerb,
            /* [in] */ BSTR bstrWorkingDirectory,
            /* [in] */ VARIANT_BOOL vbExpandEnvVarInWorkingDirectoryOnServer);
        
        END_INTERFACE
    } ITSRemoteApplicationVtbl;

    interface ITSRemoteApplication
    {
        CONST_VTBL struct ITSRemoteApplicationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITSRemoteApplication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITSRemoteApplication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITSRemoteApplication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITSRemoteApplication_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITSRemoteApplication_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITSRemoteApplication_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITSRemoteApplication_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITSRemoteApplication_put_RemoteApplicationMode(This,vboolRemoteApplicationMode)	\
    (This)->lpVtbl -> put_RemoteApplicationMode(This,vboolRemoteApplicationMode)

#define ITSRemoteApplication_get_RemoteApplicationMode(This,pvboolRemoteApplicationMode)	\
    (This)->lpVtbl -> get_RemoteApplicationMode(This,pvboolRemoteApplicationMode)

#define ITSRemoteApplication_ServerStartApplication(This,bstrExecutablePath,bstrFilePath,bstrVerb,bstrWorkingDirectory,vbExpandEnvVarInWorkingDirectoryOnServer)	\
    (This)->lpVtbl -> ServerStartApplication(This,bstrExecutablePath,bstrFilePath,bstrVerb,bstrWorkingDirectory,vbExpandEnvVarInWorkingDirectoryOnServer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSRemoteApplication_put_RemoteApplicationMode_Proxy( 
    ITSRemoteApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vboolRemoteApplicationMode);


void __RPC_STUB ITSRemoteApplication_put_RemoteApplicationMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSRemoteApplication_get_RemoteApplicationMode_Proxy( 
    ITSRemoteApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvboolRemoteApplicationMode);


void __RPC_STUB ITSRemoteApplication_get_RemoteApplicationMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITSRemoteApplication_ServerStartApplication_Proxy( 
    ITSRemoteApplication __RPC_FAR * This,
    /* [in] */ BSTR bstrExecutablePath,
    /* [in] */ BSTR bstrFilePath,
    /* [in] */ BSTR bstrVerb,
    /* [in] */ BSTR bstrWorkingDirectory,
    /* [in] */ VARIANT_BOOL vbExpandEnvVarInWorkingDirectoryOnServer);


void __RPC_STUB ITSRemoteApplication_ServerStartApplication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITSRemoteApplication_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientTransportSettings_INTERFACE_DEFINED__
#define __IMsRdpClientTransportSettings_INTERFACE_DEFINED__

/* interface IMsRdpClientTransportSettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientTransportSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("720298C0-A099-46f5-9F82-96921BAE4701")
    IMsRdpClientTransportSettings : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyUrl( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyUrl( 
            /* [retval][out] */ BSTR __RPC_FAR *pProxyUrl) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyUsername( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyUsername( 
            /* [retval][out] */ BSTR __RPC_FAR *pProxyUsername) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyDomain( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyDomain( 
            /* [retval][out] */ BSTR __RPC_FAR *pProxyDomain) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyUsageMethod( 
            /* [in] */ ULONG ulProxyMethod) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyUsageMethod( 
            /* [retval][out] */ ULONG __RPC_FAR *pulProxyUsageMethod) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyCredsSource( 
            /* [in] */ ULONG ulProxyCredsSource) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyCredsSource( 
            /* [retval][out] */ ULONG __RPC_FAR *pulProxyCredsSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetProxyPassword( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyPin( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetProxyPin( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientTransportSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientTransportSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientTransportSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyUrl )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyUrl )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pProxyUrl);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyUsername )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyUsername )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pProxyUsername);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyDomain )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyDomain )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pProxyDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPassword )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyUsageMethod )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ ULONG ulProxyMethod);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyUsageMethod )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulProxyUsageMethod);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyCredsSource )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ ULONG ulProxyCredsSource);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyCredsSource )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulProxyCredsSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetProxyPassword )( 
            IMsRdpClientTransportSettings __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPin )( 
            IMsRdpClientTransportSettings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetProxyPin )( 
            IMsRdpClientTransportSettings __RPC_FAR * This);
        
        END_INTERFACE
    } IMsRdpClientTransportSettingsVtbl;

    interface IMsRdpClientTransportSettings
    {
        CONST_VTBL struct IMsRdpClientTransportSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientTransportSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientTransportSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientTransportSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientTransportSettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientTransportSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientTransportSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientTransportSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientTransportSettings_put_ProxyUrl(This,newVal)	\
    (This)->lpVtbl -> put_ProxyUrl(This,newVal)

#define IMsRdpClientTransportSettings_get_ProxyUrl(This,pProxyUrl)	\
    (This)->lpVtbl -> get_ProxyUrl(This,pProxyUrl)

#define IMsRdpClientTransportSettings_put_ProxyUsername(This,newVal)	\
    (This)->lpVtbl -> put_ProxyUsername(This,newVal)

#define IMsRdpClientTransportSettings_get_ProxyUsername(This,pProxyUsername)	\
    (This)->lpVtbl -> get_ProxyUsername(This,pProxyUsername)

#define IMsRdpClientTransportSettings_put_ProxyDomain(This,newVal)	\
    (This)->lpVtbl -> put_ProxyDomain(This,newVal)

#define IMsRdpClientTransportSettings_get_ProxyDomain(This,pProxyDomain)	\
    (This)->lpVtbl -> get_ProxyDomain(This,pProxyDomain)

#define IMsRdpClientTransportSettings_put_ProxyPassword(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPassword(This,newVal)

#define IMsRdpClientTransportSettings_put_ProxyUsageMethod(This,ulProxyMethod)	\
    (This)->lpVtbl -> put_ProxyUsageMethod(This,ulProxyMethod)

#define IMsRdpClientTransportSettings_get_ProxyUsageMethod(This,pulProxyUsageMethod)	\
    (This)->lpVtbl -> get_ProxyUsageMethod(This,pulProxyUsageMethod)

#define IMsRdpClientTransportSettings_put_ProxyCredsSource(This,ulProxyCredsSource)	\
    (This)->lpVtbl -> put_ProxyCredsSource(This,ulProxyCredsSource)

#define IMsRdpClientTransportSettings_get_ProxyCredsSource(This,pulProxyCredsSource)	\
    (This)->lpVtbl -> get_ProxyCredsSource(This,pulProxyCredsSource)

#define IMsRdpClientTransportSettings_ResetProxyPassword(This)	\
    (This)->lpVtbl -> ResetProxyPassword(This)

#define IMsRdpClientTransportSettings_put_ProxyPin(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPin(This,newVal)

#define IMsRdpClientTransportSettings_ResetProxyPin(This)	\
    (This)->lpVtbl -> ResetProxyPin(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyUrl_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_get_ProxyUrl_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pProxyUrl);


void __RPC_STUB IMsRdpClientTransportSettings_get_ProxyUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyUsername_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyUsername_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_get_ProxyUsername_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pProxyUsername);


void __RPC_STUB IMsRdpClientTransportSettings_get_ProxyUsername_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyDomain_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyDomain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_get_ProxyDomain_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pProxyDomain);


void __RPC_STUB IMsRdpClientTransportSettings_get_ProxyDomain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyPassword_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyUsageMethod_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ ULONG ulProxyMethod);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyUsageMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_get_ProxyUsageMethod_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulProxyUsageMethod);


void __RPC_STUB IMsRdpClientTransportSettings_get_ProxyUsageMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyCredsSource_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ ULONG ulProxyCredsSource);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyCredsSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_get_ProxyCredsSource_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulProxyCredsSource);


void __RPC_STUB IMsRdpClientTransportSettings_get_ProxyCredsSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_ResetProxyPassword_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This);


void __RPC_STUB IMsRdpClientTransportSettings_ResetProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_put_ProxyPin_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClientTransportSettings_put_ProxyPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientTransportSettings_ResetProxyPin_Proxy( 
    IMsRdpClientTransportSettings __RPC_FAR * This);


void __RPC_STUB IMsRdpClientTransportSettings_ResetProxyPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientTransportSettings_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientShell_INTERFACE_DEFINED__
#define __IMsRdpClientShell_INTERFACE_DEFINED__

/* interface IMsRdpClientShell */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientShell;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d012ae6d-c19a-4bfe-b367-201f8911f134")
    IMsRdpClientShell : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Launch( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RdpFileContents( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpFileContents( 
            /* [retval][out] */ BSTR __RPC_FAR *pszRdpFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRdpProperty( 
            /* [in] */ BSTR szProperty,
            /* [in] */ VARIANT Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRdpProperty( 
            /* [in] */ BSTR szProperty,
            /* [retval][out] */ VARIANT __RPC_FAR *pValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsRemoteApplicationClientInstalled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClientInstalled) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpClientMajorVersion( 
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientMajorVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpClientMinorVersion( 
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientMinorVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpClientBuildVersion( 
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientBuildVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpClientQfeVersion( 
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientQfeVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpClientVersionString( 
            /* [retval][out] */ BSTR __RPC_FAR *pszRdpVersion) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PublicMode( 
            /* [in] */ VARIANT_BOOL fPublicMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PublicMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPublicMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowTrustedSitesManagementDialog( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientShellVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientShell __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientShell __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Launch )( 
            IMsRdpClientShell __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpFileContents )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpFileContents )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pszRdpFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRdpProperty )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ BSTR szProperty,
            /* [in] */ VARIANT Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRdpProperty )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ BSTR szProperty,
            /* [retval][out] */ VARIANT __RPC_FAR *pValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsRemoteApplicationClientInstalled )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClientInstalled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpClientMajorVersion )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientMajorVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpClientMinorVersion )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientMinorVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpClientBuildVersion )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientBuildVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpClientQfeVersion )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientQfeVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpClientVersionString )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pszRdpVersion);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PublicMode )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPublicMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PublicMode )( 
            IMsRdpClientShell __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPublicMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowTrustedSitesManagementDialog )( 
            IMsRdpClientShell __RPC_FAR * This);
        
        END_INTERFACE
    } IMsRdpClientShellVtbl;

    interface IMsRdpClientShell
    {
        CONST_VTBL struct IMsRdpClientShellVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientShell_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientShell_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientShell_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientShell_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientShell_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientShell_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientShell_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientShell_Launch(This)	\
    (This)->lpVtbl -> Launch(This)

#define IMsRdpClientShell_put_RdpFileContents(This,newVal)	\
    (This)->lpVtbl -> put_RdpFileContents(This,newVal)

#define IMsRdpClientShell_get_RdpFileContents(This,pszRdpFile)	\
    (This)->lpVtbl -> get_RdpFileContents(This,pszRdpFile)

#define IMsRdpClientShell_SetRdpProperty(This,szProperty,Value)	\
    (This)->lpVtbl -> SetRdpProperty(This,szProperty,Value)

#define IMsRdpClientShell_GetRdpProperty(This,szProperty,pValue)	\
    (This)->lpVtbl -> GetRdpProperty(This,szProperty,pValue)

#define IMsRdpClientShell_get_IsRemoteApplicationClientInstalled(This,pbClientInstalled)	\
    (This)->lpVtbl -> get_IsRemoteApplicationClientInstalled(This,pbClientInstalled)

#define IMsRdpClientShell_get_RdpClientMajorVersion(This,pulRdpClientMajorVersion)	\
    (This)->lpVtbl -> get_RdpClientMajorVersion(This,pulRdpClientMajorVersion)

#define IMsRdpClientShell_get_RdpClientMinorVersion(This,pulRdpClientMinorVersion)	\
    (This)->lpVtbl -> get_RdpClientMinorVersion(This,pulRdpClientMinorVersion)

#define IMsRdpClientShell_get_RdpClientBuildVersion(This,pulRdpClientBuildVersion)	\
    (This)->lpVtbl -> get_RdpClientBuildVersion(This,pulRdpClientBuildVersion)

#define IMsRdpClientShell_get_RdpClientQfeVersion(This,pulRdpClientQfeVersion)	\
    (This)->lpVtbl -> get_RdpClientQfeVersion(This,pulRdpClientQfeVersion)

#define IMsRdpClientShell_get_RdpClientVersionString(This,pszRdpVersion)	\
    (This)->lpVtbl -> get_RdpClientVersionString(This,pszRdpVersion)

#define IMsRdpClientShell_put_PublicMode(This,fPublicMode)	\
    (This)->lpVtbl -> put_PublicMode(This,fPublicMode)

#define IMsRdpClientShell_get_PublicMode(This,pfPublicMode)	\
    (This)->lpVtbl -> get_PublicMode(This,pfPublicMode)

#define IMsRdpClientShell_ShowTrustedSitesManagementDialog(This)	\
    (This)->lpVtbl -> ShowTrustedSitesManagementDialog(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_Launch_Proxy( 
    IMsRdpClientShell __RPC_FAR * This);


void __RPC_STUB IMsRdpClientShell_Launch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_put_RdpFileContents_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClientShell_put_RdpFileContents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_RdpFileContents_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pszRdpFile);


void __RPC_STUB IMsRdpClientShell_get_RdpFileContents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_SetRdpProperty_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [in] */ BSTR szProperty,
    /* [in] */ VARIANT Value);


void __RPC_STUB IMsRdpClientShell_SetRdpProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_GetRdpProperty_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [in] */ BSTR szProperty,
    /* [retval][out] */ VARIANT __RPC_FAR *pValue);


void __RPC_STUB IMsRdpClientShell_GetRdpProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_IsRemoteApplicationClientInstalled_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClientInstalled);


void __RPC_STUB IMsRdpClientShell_get_IsRemoteApplicationClientInstalled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_RdpClientMajorVersion_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientMajorVersion);


void __RPC_STUB IMsRdpClientShell_get_RdpClientMajorVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_RdpClientMinorVersion_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientMinorVersion);


void __RPC_STUB IMsRdpClientShell_get_RdpClientMinorVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_RdpClientBuildVersion_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientBuildVersion);


void __RPC_STUB IMsRdpClientShell_get_RdpClientBuildVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_RdpClientQfeVersion_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulRdpClientQfeVersion);


void __RPC_STUB IMsRdpClientShell_get_RdpClientQfeVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_RdpClientVersionString_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pszRdpVersion);


void __RPC_STUB IMsRdpClientShell_get_RdpClientVersionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_put_PublicMode_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fPublicMode);


void __RPC_STUB IMsRdpClientShell_put_PublicMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_get_PublicMode_Proxy( 
    IMsRdpClientShell __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPublicMode);


void __RPC_STUB IMsRdpClientShell_get_PublicMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClientShell_ShowTrustedSitesManagementDialog_Proxy( 
    IMsRdpClientShell __RPC_FAR * This);


void __RPC_STUB IMsRdpClientShell_ShowTrustedSitesManagementDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientShell_INTERFACE_DEFINED__ */


#ifndef __IMsTscAdvancedSettings_INTERFACE_DEFINED__
#define __IMsTscAdvancedSettings_INTERFACE_DEFINED__

/* interface IMsTscAdvancedSettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsTscAdvancedSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("809945cc-4b3b-4a92-a6b0-dbf9b5f2ef2d")
    IMsTscAdvancedSettings : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Compress( 
            /* [in] */ LONG compress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Compress( 
            /* [retval][out] */ LONG __RPC_FAR *pcompress) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapPeristence( 
            /* [in] */ LONG bitmapPeristence) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapPeristence( 
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_allowBackgroundInput( 
            /* [in] */ LONG allowBackgroundInput) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_allowBackgroundInput( 
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyBoardLayoutStr( 
            /* [in] */ BSTR KeyBoardLayoutStr) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PluginDlls( 
            /* [in] */ BSTR PluginDlls) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IconFile( 
            /* [in] */ BSTR IconFile) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IconIndex( 
            /* [in] */ LONG IconIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContainerHandledFullScreen( 
            /* [in] */ BOOL ContainerHandledFullScreen) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContainerHandledFullScreen( 
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisableRdpdr( 
            /* [in] */ BOOL DisableRdpdr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisableRdpdr( 
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsTscAdvancedSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsTscAdvancedSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsTscAdvancedSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compress )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG compress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compress )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcompress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPeristence )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPeristence )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_allowBackgroundInput )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG allowBackgroundInput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_allowBackgroundInput )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyBoardLayoutStr )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR KeyBoardLayoutStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PluginDlls )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR PluginDlls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconFile )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR IconFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconIndex )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG IconIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerHandledFullScreen )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ BOOL ContainerHandledFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerHandledFullScreen )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableRdpdr )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [in] */ BOOL DisableRdpdr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableRdpdr )( 
            IMsTscAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);
        
        END_INTERFACE
    } IMsTscAdvancedSettingsVtbl;

    interface IMsTscAdvancedSettings
    {
        CONST_VTBL struct IMsTscAdvancedSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsTscAdvancedSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsTscAdvancedSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsTscAdvancedSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsTscAdvancedSettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsTscAdvancedSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsTscAdvancedSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsTscAdvancedSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsTscAdvancedSettings_put_Compress(This,compress)	\
    (This)->lpVtbl -> put_Compress(This,compress)

#define IMsTscAdvancedSettings_get_Compress(This,pcompress)	\
    (This)->lpVtbl -> get_Compress(This,pcompress)

#define IMsTscAdvancedSettings_put_BitmapPeristence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPeristence(This,bitmapPeristence)

#define IMsTscAdvancedSettings_get_BitmapPeristence(This,pbitmapPeristence)	\
    (This)->lpVtbl -> get_BitmapPeristence(This,pbitmapPeristence)

#define IMsTscAdvancedSettings_put_allowBackgroundInput(This,allowBackgroundInput)	\
    (This)->lpVtbl -> put_allowBackgroundInput(This,allowBackgroundInput)

#define IMsTscAdvancedSettings_get_allowBackgroundInput(This,pallowBackgroundInput)	\
    (This)->lpVtbl -> get_allowBackgroundInput(This,pallowBackgroundInput)

#define IMsTscAdvancedSettings_put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)	\
    (This)->lpVtbl -> put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)

#define IMsTscAdvancedSettings_put_PluginDlls(This,PluginDlls)	\
    (This)->lpVtbl -> put_PluginDlls(This,PluginDlls)

#define IMsTscAdvancedSettings_put_IconFile(This,IconFile)	\
    (This)->lpVtbl -> put_IconFile(This,IconFile)

#define IMsTscAdvancedSettings_put_IconIndex(This,IconIndex)	\
    (This)->lpVtbl -> put_IconIndex(This,IconIndex)

#define IMsTscAdvancedSettings_put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)	\
    (This)->lpVtbl -> put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)

#define IMsTscAdvancedSettings_get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)	\
    (This)->lpVtbl -> get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)

#define IMsTscAdvancedSettings_put_DisableRdpdr(This,DisableRdpdr)	\
    (This)->lpVtbl -> put_DisableRdpdr(This,DisableRdpdr)

#define IMsTscAdvancedSettings_get_DisableRdpdr(This,pDisableRdpdr)	\
    (This)->lpVtbl -> get_DisableRdpdr(This,pDisableRdpdr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_Compress_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG compress);


void __RPC_STUB IMsTscAdvancedSettings_put_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_get_Compress_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pcompress);


void __RPC_STUB IMsTscAdvancedSettings_get_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_BitmapPeristence_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bitmapPeristence);


void __RPC_STUB IMsTscAdvancedSettings_put_BitmapPeristence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_get_BitmapPeristence_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);


void __RPC_STUB IMsTscAdvancedSettings_get_BitmapPeristence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_allowBackgroundInput_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG allowBackgroundInput);


void __RPC_STUB IMsTscAdvancedSettings_put_allowBackgroundInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_get_allowBackgroundInput_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);


void __RPC_STUB IMsTscAdvancedSettings_get_allowBackgroundInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_KeyBoardLayoutStr_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR KeyBoardLayoutStr);


void __RPC_STUB IMsTscAdvancedSettings_put_KeyBoardLayoutStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_PluginDlls_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR PluginDlls);


void __RPC_STUB IMsTscAdvancedSettings_put_PluginDlls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_IconFile_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR IconFile);


void __RPC_STUB IMsTscAdvancedSettings_put_IconFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_IconIndex_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG IconIndex);


void __RPC_STUB IMsTscAdvancedSettings_put_IconIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_ContainerHandledFullScreen_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ BOOL ContainerHandledFullScreen);


void __RPC_STUB IMsTscAdvancedSettings_put_ContainerHandledFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_get_ContainerHandledFullScreen_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);


void __RPC_STUB IMsTscAdvancedSettings_get_ContainerHandledFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_put_DisableRdpdr_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [in] */ BOOL DisableRdpdr);


void __RPC_STUB IMsTscAdvancedSettings_put_DisableRdpdr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAdvancedSettings_get_DisableRdpdr_Proxy( 
    IMsTscAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);


void __RPC_STUB IMsTscAdvancedSettings_get_DisableRdpdr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsTscAdvancedSettings_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings_INTERFACE_DEFINED__
#define __IMsRdpClientAdvancedSettings_INTERFACE_DEFINED__

/* interface IMsRdpClientAdvancedSettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientAdvancedSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3c65b4ab-12b3-465b-acd4-b8dad3bff9e2")
    IMsRdpClientAdvancedSettings : public IMsTscAdvancedSettings
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SmoothScroll( 
            /* [in] */ LONG smoothScroll) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SmoothScroll( 
            /* [retval][out] */ LONG __RPC_FAR *psmoothScroll) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AcceleratorPassthrough( 
            /* [in] */ LONG acceleratorPassthrough) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AcceleratorPassthrough( 
            /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShadowBitmap( 
            /* [in] */ LONG shadowBitmap) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShadowBitmap( 
            /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TransportType( 
            /* [in] */ LONG transportType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransportType( 
            /* [retval][out] */ LONG __RPC_FAR *ptransportType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SasSequence( 
            /* [in] */ LONG sasSequence) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SasSequence( 
            /* [retval][out] */ LONG __RPC_FAR *psasSequence) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncryptionEnabled( 
            /* [in] */ LONG encryptionEnabled) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncryptionEnabled( 
            /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DedicatedTerminal( 
            /* [in] */ LONG dedicatedTerminal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DedicatedTerminal( 
            /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RDPPort( 
            /* [in] */ LONG rdpPort) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RDPPort( 
            /* [retval][out] */ LONG __RPC_FAR *prdpPort) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableMouse( 
            /* [in] */ LONG enableMouse) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableMouse( 
            /* [retval][out] */ LONG __RPC_FAR *penableMouse) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisableCtrlAltDel( 
            /* [in] */ LONG disableCtrlAltDel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisableCtrlAltDel( 
            /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableWindowsKey( 
            /* [in] */ LONG enableWindowsKey) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableWindowsKey( 
            /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DoubleClickDetect( 
            /* [in] */ LONG doubleClickDetect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DoubleClickDetect( 
            /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaximizeShell( 
            /* [in] */ LONG maximizeShell) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaximizeShell( 
            /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyFullScreen( 
            /* [in] */ LONG hotKeyFullScreen) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyFullScreen( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyCtrlEsc( 
            /* [in] */ LONG hotKeyCtrlEsc) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyCtrlEsc( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyAltEsc( 
            /* [in] */ LONG hotKeyAltEsc) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyAltEsc( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyAltTab( 
            /* [in] */ LONG hotKeyAltTab) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyAltTab( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyAltShiftTab( 
            /* [in] */ LONG hotKeyAltShiftTab) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyAltShiftTab( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyAltSpace( 
            /* [in] */ LONG hotKeyAltSpace) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyAltSpace( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HotKeyCtrlAltDel( 
            /* [in] */ LONG hotKeyCtrlAltDel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HotKeyCtrlAltDel( 
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_orderDrawThreshold( 
            /* [in] */ LONG orderDrawThreshold) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_orderDrawThreshold( 
            /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapCacheSize( 
            /* [in] */ LONG bitmapCacheSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapCacheSize( 
            /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapVirtualCacheSize( 
            /* [in] */ LONG bitmapVirtualCacheSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapVirtualCacheSize( 
            /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleBitmapCachesByBPP( 
            /* [in] */ LONG bScale) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleBitmapCachesByBPP( 
            /* [retval][out] */ LONG __RPC_FAR *pbScale) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumBitmapCaches( 
            /* [in] */ LONG numBitmapCaches) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumBitmapCaches( 
            /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CachePersistenceActive( 
            /* [in] */ LONG cachePersistenceActive) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CachePersistenceActive( 
            /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PersistCacheDirectory( 
            /* [in] */ BSTR PersistCacheDirectory) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_brushSupportLevel( 
            /* [in] */ LONG brushSupportLevel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_brushSupportLevel( 
            /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_minInputSendInterval( 
            /* [in] */ LONG minInputSendInterval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_minInputSendInterval( 
            /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputEventsAtOnce( 
            /* [in] */ LONG inputEventsAtOnce) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputEventsAtOnce( 
            /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_maxEventCount( 
            /* [in] */ LONG maxEventCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_maxEventCount( 
            /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_keepAliveInterval( 
            /* [in] */ LONG keepAliveInterval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_keepAliveInterval( 
            /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_shutdownTimeout( 
            /* [in] */ LONG shutdownTimeout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_shutdownTimeout( 
            /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_overallConnectionTimeout( 
            /* [in] */ LONG overallConnectionTimeout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_overallConnectionTimeout( 
            /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_singleConnectionTimeout( 
            /* [in] */ LONG singleConnectionTimeout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_singleConnectionTimeout( 
            /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyboardType( 
            /* [in] */ LONG keyboardType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyboardType( 
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyboardSubType( 
            /* [in] */ LONG keyboardSubType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyboardSubType( 
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyboardFunctionKey( 
            /* [in] */ LONG keyboardFunctionKey) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyboardFunctionKey( 
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WinceFixedPalette( 
            /* [in] */ LONG winceFixedPalette) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WinceFixedPalette( 
            /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectToServerConsole( 
            /* [in] */ VARIANT_BOOL connectToServerConsole) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectToServerConsole( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapPersistence( 
            /* [in] */ LONG bitmapPeristence) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapPersistence( 
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinutesToIdleTimeout( 
            /* [in] */ LONG minutesToIdleTimeout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinutesToIdleTimeout( 
            /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SmartSizing( 
            /* [in] */ VARIANT_BOOL fSmartSizing) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SmartSizing( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RdpdrLocalPrintingDocName( 
            /* [in] */ BSTR localPrintingDocName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpdrLocalPrintingDocName( 
            /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RdpdrClipCleanTempDirString( 
            /* [in] */ BSTR clipCleanTempDirString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpdrClipCleanTempDirString( 
            /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RdpdrClipPasteInfoString( 
            /* [in] */ BSTR clipPasteInfoString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RdpdrClipPasteInfoString( 
            /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClearTextPassword( 
            /* [in] */ BSTR clearTextPassword) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayConnectionBar( 
            /* [in] */ VARIANT_BOOL fDisplayConnectionBar) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayConnectionBar( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PinConnectionBar( 
            /* [in] */ VARIANT_BOOL fPinConnectionBar) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PinConnectionBar( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GrabFocusOnConnect( 
            /* [in] */ VARIANT_BOOL fGrabFocusOnConnect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GrabFocusOnConnect( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LoadBalanceInfo( 
            /* [in] */ BSTR newLBInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LoadBalanceInfo( 
            /* [retval][out] */ BSTR __RPC_FAR *pLBInfo) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectDrives( 
            /* [in] */ VARIANT_BOOL redirectDrives) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectDrives( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectPrinters( 
            /* [in] */ VARIANT_BOOL redirectPrinters) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectPrinters( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectPorts( 
            /* [in] */ VARIANT_BOOL redirectPorts) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectPorts( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectSmartCards( 
            /* [in] */ VARIANT_BOOL redirectSmartCards) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectSmartCards( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapVirtualCache16BppSize( 
            /* [in] */ LONG bitmapVirtualCache16BppSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapVirtualCache16BppSize( 
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BitmapVirtualCache24BppSize( 
            /* [in] */ LONG bitmapVirtualCache24BppSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BitmapVirtualCache24BppSize( 
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PerformanceFlags( 
            /* [in] */ LONG DisableList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PerformanceFlags( 
            /* [retval][out] */ LONG __RPC_FAR *pDisableList) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectWithEndpoint( 
            /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NotifyTSPublicKey( 
            /* [in] */ VARIANT_BOOL fNotify) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NotifyTSPublicKey( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientAdvancedSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compress )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG compress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compress )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcompress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG allowBackgroundInput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyBoardLayoutStr )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR KeyBoardLayoutStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PluginDlls )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR PluginDlls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconFile )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR IconFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconIndex )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG IconIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BOOL ContainerHandledFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BOOL DisableRdpdr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmoothScroll )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG smoothScroll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmoothScroll )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psmoothScroll);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG acceleratorPassthrough);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG shadowBitmap);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransportType )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG transportType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportType )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *ptransportType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SasSequence )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG sasSequence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SasSequence )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psasSequence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG encryptionEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG dedicatedTerminal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RDPPort )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG rdpPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RDPPort )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *prdpPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableMouse )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG enableMouse);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableMouse )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableMouse);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG disableCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG enableWindowsKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG doubleClickDetect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaximizeShell )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG maximizeShell);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaximizeShell )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltShiftTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG orderDrawThreshold);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bScale);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbScale);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG numBitmapCaches);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG cachePersistenceActive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PersistCacheDirectory )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR PersistCacheDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG brushSupportLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG minInputSendInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG inputEventsAtOnce);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxEventCount )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG maxEventCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxEventCount )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG keepAliveInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG shutdownTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG overallConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG singleConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardType )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG keyboardType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardType )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG keyboardSubType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG keyboardFunctionKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG winceFixedPalette);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL connectToServerConsole);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG minutesToIdleTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmartSizing )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSmartSizing);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmartSizing )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR localPrintingDocName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR clipCleanTempDirString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR clipPasteInfoString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR clearTextPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fDisplayConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPinConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fGrabFocusOnConnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ BSTR newLBInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLBInfo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectDrives )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectDrives )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPrinters);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPorts )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPorts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPorts )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectSmartCards);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ LONG DisableList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pDisableList);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectWithEndpoint )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify);
        
        END_INTERFACE
    } IMsRdpClientAdvancedSettingsVtbl;

    interface IMsRdpClientAdvancedSettings
    {
        CONST_VTBL struct IMsRdpClientAdvancedSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientAdvancedSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientAdvancedSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientAdvancedSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientAdvancedSettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientAdvancedSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientAdvancedSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientAdvancedSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientAdvancedSettings_put_Compress(This,compress)	\
    (This)->lpVtbl -> put_Compress(This,compress)

#define IMsRdpClientAdvancedSettings_get_Compress(This,pcompress)	\
    (This)->lpVtbl -> get_Compress(This,pcompress)

#define IMsRdpClientAdvancedSettings_put_BitmapPeristence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPeristence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings_get_BitmapPeristence(This,pbitmapPeristence)	\
    (This)->lpVtbl -> get_BitmapPeristence(This,pbitmapPeristence)

#define IMsRdpClientAdvancedSettings_put_allowBackgroundInput(This,allowBackgroundInput)	\
    (This)->lpVtbl -> put_allowBackgroundInput(This,allowBackgroundInput)

#define IMsRdpClientAdvancedSettings_get_allowBackgroundInput(This,pallowBackgroundInput)	\
    (This)->lpVtbl -> get_allowBackgroundInput(This,pallowBackgroundInput)

#define IMsRdpClientAdvancedSettings_put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)	\
    (This)->lpVtbl -> put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)

#define IMsRdpClientAdvancedSettings_put_PluginDlls(This,PluginDlls)	\
    (This)->lpVtbl -> put_PluginDlls(This,PluginDlls)

#define IMsRdpClientAdvancedSettings_put_IconFile(This,IconFile)	\
    (This)->lpVtbl -> put_IconFile(This,IconFile)

#define IMsRdpClientAdvancedSettings_put_IconIndex(This,IconIndex)	\
    (This)->lpVtbl -> put_IconIndex(This,IconIndex)

#define IMsRdpClientAdvancedSettings_put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)	\
    (This)->lpVtbl -> put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings_get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)	\
    (This)->lpVtbl -> get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings_put_DisableRdpdr(This,DisableRdpdr)	\
    (This)->lpVtbl -> put_DisableRdpdr(This,DisableRdpdr)

#define IMsRdpClientAdvancedSettings_get_DisableRdpdr(This,pDisableRdpdr)	\
    (This)->lpVtbl -> get_DisableRdpdr(This,pDisableRdpdr)


#define IMsRdpClientAdvancedSettings_put_SmoothScroll(This,smoothScroll)	\
    (This)->lpVtbl -> put_SmoothScroll(This,smoothScroll)

#define IMsRdpClientAdvancedSettings_get_SmoothScroll(This,psmoothScroll)	\
    (This)->lpVtbl -> get_SmoothScroll(This,psmoothScroll)

#define IMsRdpClientAdvancedSettings_put_AcceleratorPassthrough(This,acceleratorPassthrough)	\
    (This)->lpVtbl -> put_AcceleratorPassthrough(This,acceleratorPassthrough)

#define IMsRdpClientAdvancedSettings_get_AcceleratorPassthrough(This,pacceleratorPassthrough)	\
    (This)->lpVtbl -> get_AcceleratorPassthrough(This,pacceleratorPassthrough)

#define IMsRdpClientAdvancedSettings_put_ShadowBitmap(This,shadowBitmap)	\
    (This)->lpVtbl -> put_ShadowBitmap(This,shadowBitmap)

#define IMsRdpClientAdvancedSettings_get_ShadowBitmap(This,pshadowBitmap)	\
    (This)->lpVtbl -> get_ShadowBitmap(This,pshadowBitmap)

#define IMsRdpClientAdvancedSettings_put_TransportType(This,transportType)	\
    (This)->lpVtbl -> put_TransportType(This,transportType)

#define IMsRdpClientAdvancedSettings_get_TransportType(This,ptransportType)	\
    (This)->lpVtbl -> get_TransportType(This,ptransportType)

#define IMsRdpClientAdvancedSettings_put_SasSequence(This,sasSequence)	\
    (This)->lpVtbl -> put_SasSequence(This,sasSequence)

#define IMsRdpClientAdvancedSettings_get_SasSequence(This,psasSequence)	\
    (This)->lpVtbl -> get_SasSequence(This,psasSequence)

#define IMsRdpClientAdvancedSettings_put_EncryptionEnabled(This,encryptionEnabled)	\
    (This)->lpVtbl -> put_EncryptionEnabled(This,encryptionEnabled)

#define IMsRdpClientAdvancedSettings_get_EncryptionEnabled(This,pencryptionEnabled)	\
    (This)->lpVtbl -> get_EncryptionEnabled(This,pencryptionEnabled)

#define IMsRdpClientAdvancedSettings_put_DedicatedTerminal(This,dedicatedTerminal)	\
    (This)->lpVtbl -> put_DedicatedTerminal(This,dedicatedTerminal)

#define IMsRdpClientAdvancedSettings_get_DedicatedTerminal(This,pdedicatedTerminal)	\
    (This)->lpVtbl -> get_DedicatedTerminal(This,pdedicatedTerminal)

#define IMsRdpClientAdvancedSettings_put_RDPPort(This,rdpPort)	\
    (This)->lpVtbl -> put_RDPPort(This,rdpPort)

#define IMsRdpClientAdvancedSettings_get_RDPPort(This,prdpPort)	\
    (This)->lpVtbl -> get_RDPPort(This,prdpPort)

#define IMsRdpClientAdvancedSettings_put_EnableMouse(This,enableMouse)	\
    (This)->lpVtbl -> put_EnableMouse(This,enableMouse)

#define IMsRdpClientAdvancedSettings_get_EnableMouse(This,penableMouse)	\
    (This)->lpVtbl -> get_EnableMouse(This,penableMouse)

#define IMsRdpClientAdvancedSettings_put_DisableCtrlAltDel(This,disableCtrlAltDel)	\
    (This)->lpVtbl -> put_DisableCtrlAltDel(This,disableCtrlAltDel)

#define IMsRdpClientAdvancedSettings_get_DisableCtrlAltDel(This,pdisableCtrlAltDel)	\
    (This)->lpVtbl -> get_DisableCtrlAltDel(This,pdisableCtrlAltDel)

#define IMsRdpClientAdvancedSettings_put_EnableWindowsKey(This,enableWindowsKey)	\
    (This)->lpVtbl -> put_EnableWindowsKey(This,enableWindowsKey)

#define IMsRdpClientAdvancedSettings_get_EnableWindowsKey(This,penableWindowsKey)	\
    (This)->lpVtbl -> get_EnableWindowsKey(This,penableWindowsKey)

#define IMsRdpClientAdvancedSettings_put_DoubleClickDetect(This,doubleClickDetect)	\
    (This)->lpVtbl -> put_DoubleClickDetect(This,doubleClickDetect)

#define IMsRdpClientAdvancedSettings_get_DoubleClickDetect(This,pdoubleClickDetect)	\
    (This)->lpVtbl -> get_DoubleClickDetect(This,pdoubleClickDetect)

#define IMsRdpClientAdvancedSettings_put_MaximizeShell(This,maximizeShell)	\
    (This)->lpVtbl -> put_MaximizeShell(This,maximizeShell)

#define IMsRdpClientAdvancedSettings_get_MaximizeShell(This,pmaximizeShell)	\
    (This)->lpVtbl -> get_MaximizeShell(This,pmaximizeShell)

#define IMsRdpClientAdvancedSettings_put_HotKeyFullScreen(This,hotKeyFullScreen)	\
    (This)->lpVtbl -> put_HotKeyFullScreen(This,hotKeyFullScreen)

#define IMsRdpClientAdvancedSettings_get_HotKeyFullScreen(This,photKeyFullScreen)	\
    (This)->lpVtbl -> get_HotKeyFullScreen(This,photKeyFullScreen)

#define IMsRdpClientAdvancedSettings_put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)	\
    (This)->lpVtbl -> put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings_get_HotKeyCtrlEsc(This,photKeyCtrlEsc)	\
    (This)->lpVtbl -> get_HotKeyCtrlEsc(This,photKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings_put_HotKeyAltEsc(This,hotKeyAltEsc)	\
    (This)->lpVtbl -> put_HotKeyAltEsc(This,hotKeyAltEsc)

#define IMsRdpClientAdvancedSettings_get_HotKeyAltEsc(This,photKeyAltEsc)	\
    (This)->lpVtbl -> get_HotKeyAltEsc(This,photKeyAltEsc)

#define IMsRdpClientAdvancedSettings_put_HotKeyAltTab(This,hotKeyAltTab)	\
    (This)->lpVtbl -> put_HotKeyAltTab(This,hotKeyAltTab)

#define IMsRdpClientAdvancedSettings_get_HotKeyAltTab(This,photKeyAltTab)	\
    (This)->lpVtbl -> get_HotKeyAltTab(This,photKeyAltTab)

#define IMsRdpClientAdvancedSettings_put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)	\
    (This)->lpVtbl -> put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings_get_HotKeyAltShiftTab(This,photKeyAltShiftTab)	\
    (This)->lpVtbl -> get_HotKeyAltShiftTab(This,photKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings_put_HotKeyAltSpace(This,hotKeyAltSpace)	\
    (This)->lpVtbl -> put_HotKeyAltSpace(This,hotKeyAltSpace)

#define IMsRdpClientAdvancedSettings_get_HotKeyAltSpace(This,photKeyAltSpace)	\
    (This)->lpVtbl -> get_HotKeyAltSpace(This,photKeyAltSpace)

#define IMsRdpClientAdvancedSettings_put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)	\
    (This)->lpVtbl -> put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings_get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)	\
    (This)->lpVtbl -> get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings_put_orderDrawThreshold(This,orderDrawThreshold)	\
    (This)->lpVtbl -> put_orderDrawThreshold(This,orderDrawThreshold)

#define IMsRdpClientAdvancedSettings_get_orderDrawThreshold(This,porderDrawThreshold)	\
    (This)->lpVtbl -> get_orderDrawThreshold(This,porderDrawThreshold)

#define IMsRdpClientAdvancedSettings_put_BitmapCacheSize(This,bitmapCacheSize)	\
    (This)->lpVtbl -> put_BitmapCacheSize(This,bitmapCacheSize)

#define IMsRdpClientAdvancedSettings_get_BitmapCacheSize(This,pbitmapCacheSize)	\
    (This)->lpVtbl -> get_BitmapCacheSize(This,pbitmapCacheSize)

#define IMsRdpClientAdvancedSettings_put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings_get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings_put_ScaleBitmapCachesByBPP(This,bScale)	\
    (This)->lpVtbl -> put_ScaleBitmapCachesByBPP(This,bScale)

#define IMsRdpClientAdvancedSettings_get_ScaleBitmapCachesByBPP(This,pbScale)	\
    (This)->lpVtbl -> get_ScaleBitmapCachesByBPP(This,pbScale)

#define IMsRdpClientAdvancedSettings_put_NumBitmapCaches(This,numBitmapCaches)	\
    (This)->lpVtbl -> put_NumBitmapCaches(This,numBitmapCaches)

#define IMsRdpClientAdvancedSettings_get_NumBitmapCaches(This,pnumBitmapCaches)	\
    (This)->lpVtbl -> get_NumBitmapCaches(This,pnumBitmapCaches)

#define IMsRdpClientAdvancedSettings_put_CachePersistenceActive(This,cachePersistenceActive)	\
    (This)->lpVtbl -> put_CachePersistenceActive(This,cachePersistenceActive)

#define IMsRdpClientAdvancedSettings_get_CachePersistenceActive(This,pcachePersistenceActive)	\
    (This)->lpVtbl -> get_CachePersistenceActive(This,pcachePersistenceActive)

#define IMsRdpClientAdvancedSettings_put_PersistCacheDirectory(This,PersistCacheDirectory)	\
    (This)->lpVtbl -> put_PersistCacheDirectory(This,PersistCacheDirectory)

#define IMsRdpClientAdvancedSettings_put_brushSupportLevel(This,brushSupportLevel)	\
    (This)->lpVtbl -> put_brushSupportLevel(This,brushSupportLevel)

#define IMsRdpClientAdvancedSettings_get_brushSupportLevel(This,pbrushSupportLevel)	\
    (This)->lpVtbl -> get_brushSupportLevel(This,pbrushSupportLevel)

#define IMsRdpClientAdvancedSettings_put_minInputSendInterval(This,minInputSendInterval)	\
    (This)->lpVtbl -> put_minInputSendInterval(This,minInputSendInterval)

#define IMsRdpClientAdvancedSettings_get_minInputSendInterval(This,pminInputSendInterval)	\
    (This)->lpVtbl -> get_minInputSendInterval(This,pminInputSendInterval)

#define IMsRdpClientAdvancedSettings_put_InputEventsAtOnce(This,inputEventsAtOnce)	\
    (This)->lpVtbl -> put_InputEventsAtOnce(This,inputEventsAtOnce)

#define IMsRdpClientAdvancedSettings_get_InputEventsAtOnce(This,pinputEventsAtOnce)	\
    (This)->lpVtbl -> get_InputEventsAtOnce(This,pinputEventsAtOnce)

#define IMsRdpClientAdvancedSettings_put_maxEventCount(This,maxEventCount)	\
    (This)->lpVtbl -> put_maxEventCount(This,maxEventCount)

#define IMsRdpClientAdvancedSettings_get_maxEventCount(This,pmaxEventCount)	\
    (This)->lpVtbl -> get_maxEventCount(This,pmaxEventCount)

#define IMsRdpClientAdvancedSettings_put_keepAliveInterval(This,keepAliveInterval)	\
    (This)->lpVtbl -> put_keepAliveInterval(This,keepAliveInterval)

#define IMsRdpClientAdvancedSettings_get_keepAliveInterval(This,pkeepAliveInterval)	\
    (This)->lpVtbl -> get_keepAliveInterval(This,pkeepAliveInterval)

#define IMsRdpClientAdvancedSettings_put_shutdownTimeout(This,shutdownTimeout)	\
    (This)->lpVtbl -> put_shutdownTimeout(This,shutdownTimeout)

#define IMsRdpClientAdvancedSettings_get_shutdownTimeout(This,pshutdownTimeout)	\
    (This)->lpVtbl -> get_shutdownTimeout(This,pshutdownTimeout)

#define IMsRdpClientAdvancedSettings_put_overallConnectionTimeout(This,overallConnectionTimeout)	\
    (This)->lpVtbl -> put_overallConnectionTimeout(This,overallConnectionTimeout)

#define IMsRdpClientAdvancedSettings_get_overallConnectionTimeout(This,poverallConnectionTimeout)	\
    (This)->lpVtbl -> get_overallConnectionTimeout(This,poverallConnectionTimeout)

#define IMsRdpClientAdvancedSettings_put_singleConnectionTimeout(This,singleConnectionTimeout)	\
    (This)->lpVtbl -> put_singleConnectionTimeout(This,singleConnectionTimeout)

#define IMsRdpClientAdvancedSettings_get_singleConnectionTimeout(This,psingleConnectionTimeout)	\
    (This)->lpVtbl -> get_singleConnectionTimeout(This,psingleConnectionTimeout)

#define IMsRdpClientAdvancedSettings_put_KeyboardType(This,keyboardType)	\
    (This)->lpVtbl -> put_KeyboardType(This,keyboardType)

#define IMsRdpClientAdvancedSettings_get_KeyboardType(This,pkeyboardType)	\
    (This)->lpVtbl -> get_KeyboardType(This,pkeyboardType)

#define IMsRdpClientAdvancedSettings_put_KeyboardSubType(This,keyboardSubType)	\
    (This)->lpVtbl -> put_KeyboardSubType(This,keyboardSubType)

#define IMsRdpClientAdvancedSettings_get_KeyboardSubType(This,pkeyboardSubType)	\
    (This)->lpVtbl -> get_KeyboardSubType(This,pkeyboardSubType)

#define IMsRdpClientAdvancedSettings_put_KeyboardFunctionKey(This,keyboardFunctionKey)	\
    (This)->lpVtbl -> put_KeyboardFunctionKey(This,keyboardFunctionKey)

#define IMsRdpClientAdvancedSettings_get_KeyboardFunctionKey(This,pkeyboardFunctionKey)	\
    (This)->lpVtbl -> get_KeyboardFunctionKey(This,pkeyboardFunctionKey)

#define IMsRdpClientAdvancedSettings_put_WinceFixedPalette(This,winceFixedPalette)	\
    (This)->lpVtbl -> put_WinceFixedPalette(This,winceFixedPalette)

#define IMsRdpClientAdvancedSettings_get_WinceFixedPalette(This,pwinceFixedPalette)	\
    (This)->lpVtbl -> get_WinceFixedPalette(This,pwinceFixedPalette)

#define IMsRdpClientAdvancedSettings_put_ConnectToServerConsole(This,connectToServerConsole)	\
    (This)->lpVtbl -> put_ConnectToServerConsole(This,connectToServerConsole)

#define IMsRdpClientAdvancedSettings_get_ConnectToServerConsole(This,pConnectToConsole)	\
    (This)->lpVtbl -> get_ConnectToServerConsole(This,pConnectToConsole)

#define IMsRdpClientAdvancedSettings_put_BitmapPersistence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPersistence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings_get_BitmapPersistence(This,pbitmapPersistence)	\
    (This)->lpVtbl -> get_BitmapPersistence(This,pbitmapPersistence)

#define IMsRdpClientAdvancedSettings_put_MinutesToIdleTimeout(This,minutesToIdleTimeout)	\
    (This)->lpVtbl -> put_MinutesToIdleTimeout(This,minutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings_get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)	\
    (This)->lpVtbl -> get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings_put_SmartSizing(This,fSmartSizing)	\
    (This)->lpVtbl -> put_SmartSizing(This,fSmartSizing)

#define IMsRdpClientAdvancedSettings_get_SmartSizing(This,pfSmartSizing)	\
    (This)->lpVtbl -> get_SmartSizing(This,pfSmartSizing)

#define IMsRdpClientAdvancedSettings_put_RdpdrLocalPrintingDocName(This,localPrintingDocName)	\
    (This)->lpVtbl -> put_RdpdrLocalPrintingDocName(This,localPrintingDocName)

#define IMsRdpClientAdvancedSettings_get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)	\
    (This)->lpVtbl -> get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)

#define IMsRdpClientAdvancedSettings_put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings_get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings_put_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> put_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings_get_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> get_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings_put_ClearTextPassword(This,clearTextPassword)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,clearTextPassword)

#define IMsRdpClientAdvancedSettings_put_DisplayConnectionBar(This,fDisplayConnectionBar)	\
    (This)->lpVtbl -> put_DisplayConnectionBar(This,fDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings_get_DisplayConnectionBar(This,pDisplayConnectionBar)	\
    (This)->lpVtbl -> get_DisplayConnectionBar(This,pDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings_put_PinConnectionBar(This,fPinConnectionBar)	\
    (This)->lpVtbl -> put_PinConnectionBar(This,fPinConnectionBar)

#define IMsRdpClientAdvancedSettings_get_PinConnectionBar(This,pPinConnectionBar)	\
    (This)->lpVtbl -> get_PinConnectionBar(This,pPinConnectionBar)

#define IMsRdpClientAdvancedSettings_put_GrabFocusOnConnect(This,fGrabFocusOnConnect)	\
    (This)->lpVtbl -> put_GrabFocusOnConnect(This,fGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings_get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)	\
    (This)->lpVtbl -> get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings_put_LoadBalanceInfo(This,newLBInfo)	\
    (This)->lpVtbl -> put_LoadBalanceInfo(This,newLBInfo)

#define IMsRdpClientAdvancedSettings_get_LoadBalanceInfo(This,pLBInfo)	\
    (This)->lpVtbl -> get_LoadBalanceInfo(This,pLBInfo)

#define IMsRdpClientAdvancedSettings_put_RedirectDrives(This,redirectDrives)	\
    (This)->lpVtbl -> put_RedirectDrives(This,redirectDrives)

#define IMsRdpClientAdvancedSettings_get_RedirectDrives(This,pRedirectDrives)	\
    (This)->lpVtbl -> get_RedirectDrives(This,pRedirectDrives)

#define IMsRdpClientAdvancedSettings_put_RedirectPrinters(This,redirectPrinters)	\
    (This)->lpVtbl -> put_RedirectPrinters(This,redirectPrinters)

#define IMsRdpClientAdvancedSettings_get_RedirectPrinters(This,pRedirectPrinters)	\
    (This)->lpVtbl -> get_RedirectPrinters(This,pRedirectPrinters)

#define IMsRdpClientAdvancedSettings_put_RedirectPorts(This,redirectPorts)	\
    (This)->lpVtbl -> put_RedirectPorts(This,redirectPorts)

#define IMsRdpClientAdvancedSettings_get_RedirectPorts(This,pRedirectPorts)	\
    (This)->lpVtbl -> get_RedirectPorts(This,pRedirectPorts)

#define IMsRdpClientAdvancedSettings_put_RedirectSmartCards(This,redirectSmartCards)	\
    (This)->lpVtbl -> put_RedirectSmartCards(This,redirectSmartCards)

#define IMsRdpClientAdvancedSettings_get_RedirectSmartCards(This,pRedirectSmartCards)	\
    (This)->lpVtbl -> get_RedirectSmartCards(This,pRedirectSmartCards)

#define IMsRdpClientAdvancedSettings_put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings_get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings_put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings_get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings_put_PerformanceFlags(This,DisableList)	\
    (This)->lpVtbl -> put_PerformanceFlags(This,DisableList)

#define IMsRdpClientAdvancedSettings_get_PerformanceFlags(This,pDisableList)	\
    (This)->lpVtbl -> get_PerformanceFlags(This,pDisableList)

#define IMsRdpClientAdvancedSettings_put_ConnectWithEndpoint(This,ConnectEndpoint)	\
    (This)->lpVtbl -> put_ConnectWithEndpoint(This,ConnectEndpoint)

#define IMsRdpClientAdvancedSettings_put_NotifyTSPublicKey(This,fNotify)	\
    (This)->lpVtbl -> put_NotifyTSPublicKey(This,fNotify)

#define IMsRdpClientAdvancedSettings_get_NotifyTSPublicKey(This,pfNotify)	\
    (This)->lpVtbl -> get_NotifyTSPublicKey(This,pfNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_SmoothScroll_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG smoothScroll);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_SmoothScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_SmoothScroll_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *psmoothScroll);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_SmoothScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_AcceleratorPassthrough_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG acceleratorPassthrough);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_AcceleratorPassthrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_AcceleratorPassthrough_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_AcceleratorPassthrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_ShadowBitmap_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG shadowBitmap);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_ShadowBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_ShadowBitmap_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_ShadowBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_TransportType_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG transportType);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_TransportType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_TransportType_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *ptransportType);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_TransportType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_SasSequence_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG sasSequence);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_SasSequence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_SasSequence_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *psasSequence);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_SasSequence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_EncryptionEnabled_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG encryptionEnabled);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_EncryptionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_EncryptionEnabled_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_EncryptionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_DedicatedTerminal_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG dedicatedTerminal);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_DedicatedTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_DedicatedTerminal_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_DedicatedTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RDPPort_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG rdpPort);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RDPPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RDPPort_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *prdpPort);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RDPPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_EnableMouse_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG enableMouse);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_EnableMouse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_EnableMouse_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *penableMouse);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_EnableMouse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_DisableCtrlAltDel_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG disableCtrlAltDel);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_DisableCtrlAltDel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_DisableCtrlAltDel_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_DisableCtrlAltDel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_EnableWindowsKey_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG enableWindowsKey);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_EnableWindowsKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_EnableWindowsKey_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_EnableWindowsKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_DoubleClickDetect_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG doubleClickDetect);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_DoubleClickDetect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_DoubleClickDetect_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_DoubleClickDetect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_MaximizeShell_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG maximizeShell);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_MaximizeShell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_MaximizeShell_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_MaximizeShell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyFullScreen_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyFullScreen);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyFullScreen_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyCtrlEsc_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyCtrlEsc);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyCtrlEsc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyCtrlEsc_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyCtrlEsc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyAltEsc_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyAltEsc);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyAltEsc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyAltEsc_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyAltEsc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyAltTab_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyAltTab);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyAltTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyAltTab_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyAltTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyAltShiftTab_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyAltShiftTab);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyAltShiftTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyAltShiftTab_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyAltShiftTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyAltSpace_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyAltSpace);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyAltSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyAltSpace_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyAltSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_HotKeyCtrlAltDel_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG hotKeyCtrlAltDel);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_HotKeyCtrlAltDel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_HotKeyCtrlAltDel_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_HotKeyCtrlAltDel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_orderDrawThreshold_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG orderDrawThreshold);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_orderDrawThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_orderDrawThreshold_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_orderDrawThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_BitmapCacheSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bitmapCacheSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_BitmapCacheSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_BitmapCacheSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_BitmapCacheSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_BitmapVirtualCacheSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bitmapVirtualCacheSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_BitmapVirtualCacheSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_BitmapVirtualCacheSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_BitmapVirtualCacheSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_ScaleBitmapCachesByBPP_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bScale);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_ScaleBitmapCachesByBPP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_ScaleBitmapCachesByBPP_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pbScale);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_ScaleBitmapCachesByBPP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_NumBitmapCaches_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG numBitmapCaches);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_NumBitmapCaches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_NumBitmapCaches_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_NumBitmapCaches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_CachePersistenceActive_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG cachePersistenceActive);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_CachePersistenceActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_CachePersistenceActive_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_CachePersistenceActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_PersistCacheDirectory_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR PersistCacheDirectory);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_PersistCacheDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_brushSupportLevel_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG brushSupportLevel);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_brushSupportLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_brushSupportLevel_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_brushSupportLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_minInputSendInterval_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG minInputSendInterval);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_minInputSendInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_minInputSendInterval_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_minInputSendInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_InputEventsAtOnce_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG inputEventsAtOnce);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_InputEventsAtOnce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_InputEventsAtOnce_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_InputEventsAtOnce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_maxEventCount_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG maxEventCount);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_maxEventCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_maxEventCount_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_maxEventCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_keepAliveInterval_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG keepAliveInterval);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_keepAliveInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_keepAliveInterval_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_keepAliveInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_shutdownTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG shutdownTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_shutdownTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_shutdownTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_shutdownTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_overallConnectionTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG overallConnectionTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_overallConnectionTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_overallConnectionTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_overallConnectionTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_singleConnectionTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG singleConnectionTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_singleConnectionTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_singleConnectionTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_singleConnectionTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_KeyboardType_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG keyboardType);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_KeyboardType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_KeyboardType_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pkeyboardType);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_KeyboardType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_KeyboardSubType_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG keyboardSubType);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_KeyboardSubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_KeyboardSubType_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_KeyboardSubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_KeyboardFunctionKey_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG keyboardFunctionKey);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_KeyboardFunctionKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_KeyboardFunctionKey_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_KeyboardFunctionKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_WinceFixedPalette_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG winceFixedPalette);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_WinceFixedPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_WinceFixedPalette_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_WinceFixedPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_ConnectToServerConsole_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL connectToServerConsole);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_ConnectToServerConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_ConnectToServerConsole_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_ConnectToServerConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_BitmapPersistence_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bitmapPeristence);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_BitmapPersistence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_BitmapPersistence_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_BitmapPersistence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_MinutesToIdleTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG minutesToIdleTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_MinutesToIdleTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_MinutesToIdleTimeout_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_MinutesToIdleTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_SmartSizing_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fSmartSizing);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_SmartSizing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_SmartSizing_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_SmartSizing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RdpdrLocalPrintingDocName_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR localPrintingDocName);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RdpdrLocalPrintingDocName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RdpdrLocalPrintingDocName_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RdpdrLocalPrintingDocName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RdpdrClipCleanTempDirString_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR clipCleanTempDirString);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RdpdrClipCleanTempDirString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RdpdrClipCleanTempDirString_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RdpdrClipCleanTempDirString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RdpdrClipPasteInfoString_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR clipPasteInfoString);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RdpdrClipPasteInfoString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RdpdrClipPasteInfoString_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RdpdrClipPasteInfoString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_ClearTextPassword_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR clearTextPassword);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_ClearTextPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_DisplayConnectionBar_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fDisplayConnectionBar);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_DisplayConnectionBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_DisplayConnectionBar_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_DisplayConnectionBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_PinConnectionBar_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fPinConnectionBar);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_PinConnectionBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_PinConnectionBar_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_PinConnectionBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_GrabFocusOnConnect_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fGrabFocusOnConnect);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_GrabFocusOnConnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_GrabFocusOnConnect_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_GrabFocusOnConnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_LoadBalanceInfo_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ BSTR newLBInfo);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_LoadBalanceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_LoadBalanceInfo_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pLBInfo);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_LoadBalanceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RedirectDrives_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL redirectDrives);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RedirectDrives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RedirectDrives_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RedirectDrives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RedirectPrinters_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL redirectPrinters);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RedirectPrinters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RedirectPrinters_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RedirectPrinters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RedirectPorts_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL redirectPorts);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RedirectPorts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RedirectPorts_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RedirectPorts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_RedirectSmartCards_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL redirectSmartCards);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_RedirectSmartCards_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_RedirectSmartCards_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_RedirectSmartCards_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_BitmapVirtualCache16BppSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bitmapVirtualCache16BppSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_BitmapVirtualCache16BppSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_BitmapVirtualCache16BppSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_BitmapVirtualCache16BppSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_BitmapVirtualCache24BppSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG bitmapVirtualCache24BppSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_BitmapVirtualCache24BppSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_BitmapVirtualCache24BppSize_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_BitmapVirtualCache24BppSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_PerformanceFlags_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ LONG DisableList);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_PerformanceFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_PerformanceFlags_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pDisableList);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_PerformanceFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_ConnectWithEndpoint_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_ConnectWithEndpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_put_NotifyTSPublicKey_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fNotify);


void __RPC_STUB IMsRdpClientAdvancedSettings_put_NotifyTSPublicKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings_get_NotifyTSPublicKey_Proxy( 
    IMsRdpClientAdvancedSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify);


void __RPC_STUB IMsRdpClientAdvancedSettings_get_NotifyTSPublicKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientAdvancedSettings_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings2_INTERFACE_DEFINED__
#define __IMsRdpClientAdvancedSettings2_INTERFACE_DEFINED__

/* interface IMsRdpClientAdvancedSettings2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientAdvancedSettings2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9ac42117-2b76-4320-aa44-0e616ab8437b")
    IMsRdpClientAdvancedSettings2 : public IMsRdpClientAdvancedSettings
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanAutoReconnect( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAutoReconnect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableAutoReconnect( 
            /* [in] */ VARIANT_BOOL fEnableAutoReconnect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableAutoReconnect( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfEnableAutoReconnect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxReconnectAttempts( 
            /* [in] */ LONG MaxReconnectAttempts) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxReconnectAttempts( 
            /* [retval][out] */ LONG __RPC_FAR *pMaxReconnectAttempts) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientAdvancedSettings2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compress )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG compress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compress )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcompress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG allowBackgroundInput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyBoardLayoutStr )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR KeyBoardLayoutStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PluginDlls )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR PluginDlls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconFile )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR IconFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconIndex )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG IconIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BOOL ContainerHandledFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BOOL DisableRdpdr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmoothScroll )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG smoothScroll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmoothScroll )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psmoothScroll);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG acceleratorPassthrough);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG shadowBitmap);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransportType )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG transportType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportType )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *ptransportType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SasSequence )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG sasSequence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SasSequence )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psasSequence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG encryptionEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG dedicatedTerminal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RDPPort )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG rdpPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RDPPort )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *prdpPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableMouse )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG enableMouse);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableMouse )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableMouse);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG disableCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG enableWindowsKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG doubleClickDetect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaximizeShell )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG maximizeShell);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaximizeShell )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltShiftTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG orderDrawThreshold);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bitmapCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bScale);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbScale);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG numBitmapCaches);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG cachePersistenceActive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PersistCacheDirectory )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR PersistCacheDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG brushSupportLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG minInputSendInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG inputEventsAtOnce);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxEventCount )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG maxEventCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxEventCount )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG keepAliveInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG shutdownTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG overallConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG singleConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardType )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG keyboardType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardType )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG keyboardSubType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG keyboardFunctionKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG winceFixedPalette);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL connectToServerConsole);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG minutesToIdleTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmartSizing )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSmartSizing);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmartSizing )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR localPrintingDocName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR clipCleanTempDirString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR clipPasteInfoString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR clearTextPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fDisplayConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPinConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fGrabFocusOnConnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ BSTR newLBInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLBInfo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectDrives )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectDrives )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPrinters);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPorts )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPorts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPorts )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectSmartCards);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG DisableList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pDisableList);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectWithEndpoint )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanAutoReconnect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fEnableAutoReconnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfEnableAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [in] */ LONG MaxReconnectAttempts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pMaxReconnectAttempts);
        
        END_INTERFACE
    } IMsRdpClientAdvancedSettings2Vtbl;

    interface IMsRdpClientAdvancedSettings2
    {
        CONST_VTBL struct IMsRdpClientAdvancedSettings2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientAdvancedSettings2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientAdvancedSettings2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientAdvancedSettings2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientAdvancedSettings2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientAdvancedSettings2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientAdvancedSettings2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientAdvancedSettings2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientAdvancedSettings2_put_Compress(This,compress)	\
    (This)->lpVtbl -> put_Compress(This,compress)

#define IMsRdpClientAdvancedSettings2_get_Compress(This,pcompress)	\
    (This)->lpVtbl -> get_Compress(This,pcompress)

#define IMsRdpClientAdvancedSettings2_put_BitmapPeristence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPeristence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings2_get_BitmapPeristence(This,pbitmapPeristence)	\
    (This)->lpVtbl -> get_BitmapPeristence(This,pbitmapPeristence)

#define IMsRdpClientAdvancedSettings2_put_allowBackgroundInput(This,allowBackgroundInput)	\
    (This)->lpVtbl -> put_allowBackgroundInput(This,allowBackgroundInput)

#define IMsRdpClientAdvancedSettings2_get_allowBackgroundInput(This,pallowBackgroundInput)	\
    (This)->lpVtbl -> get_allowBackgroundInput(This,pallowBackgroundInput)

#define IMsRdpClientAdvancedSettings2_put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)	\
    (This)->lpVtbl -> put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)

#define IMsRdpClientAdvancedSettings2_put_PluginDlls(This,PluginDlls)	\
    (This)->lpVtbl -> put_PluginDlls(This,PluginDlls)

#define IMsRdpClientAdvancedSettings2_put_IconFile(This,IconFile)	\
    (This)->lpVtbl -> put_IconFile(This,IconFile)

#define IMsRdpClientAdvancedSettings2_put_IconIndex(This,IconIndex)	\
    (This)->lpVtbl -> put_IconIndex(This,IconIndex)

#define IMsRdpClientAdvancedSettings2_put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)	\
    (This)->lpVtbl -> put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings2_get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)	\
    (This)->lpVtbl -> get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings2_put_DisableRdpdr(This,DisableRdpdr)	\
    (This)->lpVtbl -> put_DisableRdpdr(This,DisableRdpdr)

#define IMsRdpClientAdvancedSettings2_get_DisableRdpdr(This,pDisableRdpdr)	\
    (This)->lpVtbl -> get_DisableRdpdr(This,pDisableRdpdr)


#define IMsRdpClientAdvancedSettings2_put_SmoothScroll(This,smoothScroll)	\
    (This)->lpVtbl -> put_SmoothScroll(This,smoothScroll)

#define IMsRdpClientAdvancedSettings2_get_SmoothScroll(This,psmoothScroll)	\
    (This)->lpVtbl -> get_SmoothScroll(This,psmoothScroll)

#define IMsRdpClientAdvancedSettings2_put_AcceleratorPassthrough(This,acceleratorPassthrough)	\
    (This)->lpVtbl -> put_AcceleratorPassthrough(This,acceleratorPassthrough)

#define IMsRdpClientAdvancedSettings2_get_AcceleratorPassthrough(This,pacceleratorPassthrough)	\
    (This)->lpVtbl -> get_AcceleratorPassthrough(This,pacceleratorPassthrough)

#define IMsRdpClientAdvancedSettings2_put_ShadowBitmap(This,shadowBitmap)	\
    (This)->lpVtbl -> put_ShadowBitmap(This,shadowBitmap)

#define IMsRdpClientAdvancedSettings2_get_ShadowBitmap(This,pshadowBitmap)	\
    (This)->lpVtbl -> get_ShadowBitmap(This,pshadowBitmap)

#define IMsRdpClientAdvancedSettings2_put_TransportType(This,transportType)	\
    (This)->lpVtbl -> put_TransportType(This,transportType)

#define IMsRdpClientAdvancedSettings2_get_TransportType(This,ptransportType)	\
    (This)->lpVtbl -> get_TransportType(This,ptransportType)

#define IMsRdpClientAdvancedSettings2_put_SasSequence(This,sasSequence)	\
    (This)->lpVtbl -> put_SasSequence(This,sasSequence)

#define IMsRdpClientAdvancedSettings2_get_SasSequence(This,psasSequence)	\
    (This)->lpVtbl -> get_SasSequence(This,psasSequence)

#define IMsRdpClientAdvancedSettings2_put_EncryptionEnabled(This,encryptionEnabled)	\
    (This)->lpVtbl -> put_EncryptionEnabled(This,encryptionEnabled)

#define IMsRdpClientAdvancedSettings2_get_EncryptionEnabled(This,pencryptionEnabled)	\
    (This)->lpVtbl -> get_EncryptionEnabled(This,pencryptionEnabled)

#define IMsRdpClientAdvancedSettings2_put_DedicatedTerminal(This,dedicatedTerminal)	\
    (This)->lpVtbl -> put_DedicatedTerminal(This,dedicatedTerminal)

#define IMsRdpClientAdvancedSettings2_get_DedicatedTerminal(This,pdedicatedTerminal)	\
    (This)->lpVtbl -> get_DedicatedTerminal(This,pdedicatedTerminal)

#define IMsRdpClientAdvancedSettings2_put_RDPPort(This,rdpPort)	\
    (This)->lpVtbl -> put_RDPPort(This,rdpPort)

#define IMsRdpClientAdvancedSettings2_get_RDPPort(This,prdpPort)	\
    (This)->lpVtbl -> get_RDPPort(This,prdpPort)

#define IMsRdpClientAdvancedSettings2_put_EnableMouse(This,enableMouse)	\
    (This)->lpVtbl -> put_EnableMouse(This,enableMouse)

#define IMsRdpClientAdvancedSettings2_get_EnableMouse(This,penableMouse)	\
    (This)->lpVtbl -> get_EnableMouse(This,penableMouse)

#define IMsRdpClientAdvancedSettings2_put_DisableCtrlAltDel(This,disableCtrlAltDel)	\
    (This)->lpVtbl -> put_DisableCtrlAltDel(This,disableCtrlAltDel)

#define IMsRdpClientAdvancedSettings2_get_DisableCtrlAltDel(This,pdisableCtrlAltDel)	\
    (This)->lpVtbl -> get_DisableCtrlAltDel(This,pdisableCtrlAltDel)

#define IMsRdpClientAdvancedSettings2_put_EnableWindowsKey(This,enableWindowsKey)	\
    (This)->lpVtbl -> put_EnableWindowsKey(This,enableWindowsKey)

#define IMsRdpClientAdvancedSettings2_get_EnableWindowsKey(This,penableWindowsKey)	\
    (This)->lpVtbl -> get_EnableWindowsKey(This,penableWindowsKey)

#define IMsRdpClientAdvancedSettings2_put_DoubleClickDetect(This,doubleClickDetect)	\
    (This)->lpVtbl -> put_DoubleClickDetect(This,doubleClickDetect)

#define IMsRdpClientAdvancedSettings2_get_DoubleClickDetect(This,pdoubleClickDetect)	\
    (This)->lpVtbl -> get_DoubleClickDetect(This,pdoubleClickDetect)

#define IMsRdpClientAdvancedSettings2_put_MaximizeShell(This,maximizeShell)	\
    (This)->lpVtbl -> put_MaximizeShell(This,maximizeShell)

#define IMsRdpClientAdvancedSettings2_get_MaximizeShell(This,pmaximizeShell)	\
    (This)->lpVtbl -> get_MaximizeShell(This,pmaximizeShell)

#define IMsRdpClientAdvancedSettings2_put_HotKeyFullScreen(This,hotKeyFullScreen)	\
    (This)->lpVtbl -> put_HotKeyFullScreen(This,hotKeyFullScreen)

#define IMsRdpClientAdvancedSettings2_get_HotKeyFullScreen(This,photKeyFullScreen)	\
    (This)->lpVtbl -> get_HotKeyFullScreen(This,photKeyFullScreen)

#define IMsRdpClientAdvancedSettings2_put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)	\
    (This)->lpVtbl -> put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings2_get_HotKeyCtrlEsc(This,photKeyCtrlEsc)	\
    (This)->lpVtbl -> get_HotKeyCtrlEsc(This,photKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings2_put_HotKeyAltEsc(This,hotKeyAltEsc)	\
    (This)->lpVtbl -> put_HotKeyAltEsc(This,hotKeyAltEsc)

#define IMsRdpClientAdvancedSettings2_get_HotKeyAltEsc(This,photKeyAltEsc)	\
    (This)->lpVtbl -> get_HotKeyAltEsc(This,photKeyAltEsc)

#define IMsRdpClientAdvancedSettings2_put_HotKeyAltTab(This,hotKeyAltTab)	\
    (This)->lpVtbl -> put_HotKeyAltTab(This,hotKeyAltTab)

#define IMsRdpClientAdvancedSettings2_get_HotKeyAltTab(This,photKeyAltTab)	\
    (This)->lpVtbl -> get_HotKeyAltTab(This,photKeyAltTab)

#define IMsRdpClientAdvancedSettings2_put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)	\
    (This)->lpVtbl -> put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings2_get_HotKeyAltShiftTab(This,photKeyAltShiftTab)	\
    (This)->lpVtbl -> get_HotKeyAltShiftTab(This,photKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings2_put_HotKeyAltSpace(This,hotKeyAltSpace)	\
    (This)->lpVtbl -> put_HotKeyAltSpace(This,hotKeyAltSpace)

#define IMsRdpClientAdvancedSettings2_get_HotKeyAltSpace(This,photKeyAltSpace)	\
    (This)->lpVtbl -> get_HotKeyAltSpace(This,photKeyAltSpace)

#define IMsRdpClientAdvancedSettings2_put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)	\
    (This)->lpVtbl -> put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings2_get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)	\
    (This)->lpVtbl -> get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings2_put_orderDrawThreshold(This,orderDrawThreshold)	\
    (This)->lpVtbl -> put_orderDrawThreshold(This,orderDrawThreshold)

#define IMsRdpClientAdvancedSettings2_get_orderDrawThreshold(This,porderDrawThreshold)	\
    (This)->lpVtbl -> get_orderDrawThreshold(This,porderDrawThreshold)

#define IMsRdpClientAdvancedSettings2_put_BitmapCacheSize(This,bitmapCacheSize)	\
    (This)->lpVtbl -> put_BitmapCacheSize(This,bitmapCacheSize)

#define IMsRdpClientAdvancedSettings2_get_BitmapCacheSize(This,pbitmapCacheSize)	\
    (This)->lpVtbl -> get_BitmapCacheSize(This,pbitmapCacheSize)

#define IMsRdpClientAdvancedSettings2_put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings2_get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings2_put_ScaleBitmapCachesByBPP(This,bScale)	\
    (This)->lpVtbl -> put_ScaleBitmapCachesByBPP(This,bScale)

#define IMsRdpClientAdvancedSettings2_get_ScaleBitmapCachesByBPP(This,pbScale)	\
    (This)->lpVtbl -> get_ScaleBitmapCachesByBPP(This,pbScale)

#define IMsRdpClientAdvancedSettings2_put_NumBitmapCaches(This,numBitmapCaches)	\
    (This)->lpVtbl -> put_NumBitmapCaches(This,numBitmapCaches)

#define IMsRdpClientAdvancedSettings2_get_NumBitmapCaches(This,pnumBitmapCaches)	\
    (This)->lpVtbl -> get_NumBitmapCaches(This,pnumBitmapCaches)

#define IMsRdpClientAdvancedSettings2_put_CachePersistenceActive(This,cachePersistenceActive)	\
    (This)->lpVtbl -> put_CachePersistenceActive(This,cachePersistenceActive)

#define IMsRdpClientAdvancedSettings2_get_CachePersistenceActive(This,pcachePersistenceActive)	\
    (This)->lpVtbl -> get_CachePersistenceActive(This,pcachePersistenceActive)

#define IMsRdpClientAdvancedSettings2_put_PersistCacheDirectory(This,PersistCacheDirectory)	\
    (This)->lpVtbl -> put_PersistCacheDirectory(This,PersistCacheDirectory)

#define IMsRdpClientAdvancedSettings2_put_brushSupportLevel(This,brushSupportLevel)	\
    (This)->lpVtbl -> put_brushSupportLevel(This,brushSupportLevel)

#define IMsRdpClientAdvancedSettings2_get_brushSupportLevel(This,pbrushSupportLevel)	\
    (This)->lpVtbl -> get_brushSupportLevel(This,pbrushSupportLevel)

#define IMsRdpClientAdvancedSettings2_put_minInputSendInterval(This,minInputSendInterval)	\
    (This)->lpVtbl -> put_minInputSendInterval(This,minInputSendInterval)

#define IMsRdpClientAdvancedSettings2_get_minInputSendInterval(This,pminInputSendInterval)	\
    (This)->lpVtbl -> get_minInputSendInterval(This,pminInputSendInterval)

#define IMsRdpClientAdvancedSettings2_put_InputEventsAtOnce(This,inputEventsAtOnce)	\
    (This)->lpVtbl -> put_InputEventsAtOnce(This,inputEventsAtOnce)

#define IMsRdpClientAdvancedSettings2_get_InputEventsAtOnce(This,pinputEventsAtOnce)	\
    (This)->lpVtbl -> get_InputEventsAtOnce(This,pinputEventsAtOnce)

#define IMsRdpClientAdvancedSettings2_put_maxEventCount(This,maxEventCount)	\
    (This)->lpVtbl -> put_maxEventCount(This,maxEventCount)

#define IMsRdpClientAdvancedSettings2_get_maxEventCount(This,pmaxEventCount)	\
    (This)->lpVtbl -> get_maxEventCount(This,pmaxEventCount)

#define IMsRdpClientAdvancedSettings2_put_keepAliveInterval(This,keepAliveInterval)	\
    (This)->lpVtbl -> put_keepAliveInterval(This,keepAliveInterval)

#define IMsRdpClientAdvancedSettings2_get_keepAliveInterval(This,pkeepAliveInterval)	\
    (This)->lpVtbl -> get_keepAliveInterval(This,pkeepAliveInterval)

#define IMsRdpClientAdvancedSettings2_put_shutdownTimeout(This,shutdownTimeout)	\
    (This)->lpVtbl -> put_shutdownTimeout(This,shutdownTimeout)

#define IMsRdpClientAdvancedSettings2_get_shutdownTimeout(This,pshutdownTimeout)	\
    (This)->lpVtbl -> get_shutdownTimeout(This,pshutdownTimeout)

#define IMsRdpClientAdvancedSettings2_put_overallConnectionTimeout(This,overallConnectionTimeout)	\
    (This)->lpVtbl -> put_overallConnectionTimeout(This,overallConnectionTimeout)

#define IMsRdpClientAdvancedSettings2_get_overallConnectionTimeout(This,poverallConnectionTimeout)	\
    (This)->lpVtbl -> get_overallConnectionTimeout(This,poverallConnectionTimeout)

#define IMsRdpClientAdvancedSettings2_put_singleConnectionTimeout(This,singleConnectionTimeout)	\
    (This)->lpVtbl -> put_singleConnectionTimeout(This,singleConnectionTimeout)

#define IMsRdpClientAdvancedSettings2_get_singleConnectionTimeout(This,psingleConnectionTimeout)	\
    (This)->lpVtbl -> get_singleConnectionTimeout(This,psingleConnectionTimeout)

#define IMsRdpClientAdvancedSettings2_put_KeyboardType(This,keyboardType)	\
    (This)->lpVtbl -> put_KeyboardType(This,keyboardType)

#define IMsRdpClientAdvancedSettings2_get_KeyboardType(This,pkeyboardType)	\
    (This)->lpVtbl -> get_KeyboardType(This,pkeyboardType)

#define IMsRdpClientAdvancedSettings2_put_KeyboardSubType(This,keyboardSubType)	\
    (This)->lpVtbl -> put_KeyboardSubType(This,keyboardSubType)

#define IMsRdpClientAdvancedSettings2_get_KeyboardSubType(This,pkeyboardSubType)	\
    (This)->lpVtbl -> get_KeyboardSubType(This,pkeyboardSubType)

#define IMsRdpClientAdvancedSettings2_put_KeyboardFunctionKey(This,keyboardFunctionKey)	\
    (This)->lpVtbl -> put_KeyboardFunctionKey(This,keyboardFunctionKey)

#define IMsRdpClientAdvancedSettings2_get_KeyboardFunctionKey(This,pkeyboardFunctionKey)	\
    (This)->lpVtbl -> get_KeyboardFunctionKey(This,pkeyboardFunctionKey)

#define IMsRdpClientAdvancedSettings2_put_WinceFixedPalette(This,winceFixedPalette)	\
    (This)->lpVtbl -> put_WinceFixedPalette(This,winceFixedPalette)

#define IMsRdpClientAdvancedSettings2_get_WinceFixedPalette(This,pwinceFixedPalette)	\
    (This)->lpVtbl -> get_WinceFixedPalette(This,pwinceFixedPalette)

#define IMsRdpClientAdvancedSettings2_put_ConnectToServerConsole(This,connectToServerConsole)	\
    (This)->lpVtbl -> put_ConnectToServerConsole(This,connectToServerConsole)

#define IMsRdpClientAdvancedSettings2_get_ConnectToServerConsole(This,pConnectToConsole)	\
    (This)->lpVtbl -> get_ConnectToServerConsole(This,pConnectToConsole)

#define IMsRdpClientAdvancedSettings2_put_BitmapPersistence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPersistence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings2_get_BitmapPersistence(This,pbitmapPersistence)	\
    (This)->lpVtbl -> get_BitmapPersistence(This,pbitmapPersistence)

#define IMsRdpClientAdvancedSettings2_put_MinutesToIdleTimeout(This,minutesToIdleTimeout)	\
    (This)->lpVtbl -> put_MinutesToIdleTimeout(This,minutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings2_get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)	\
    (This)->lpVtbl -> get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings2_put_SmartSizing(This,fSmartSizing)	\
    (This)->lpVtbl -> put_SmartSizing(This,fSmartSizing)

#define IMsRdpClientAdvancedSettings2_get_SmartSizing(This,pfSmartSizing)	\
    (This)->lpVtbl -> get_SmartSizing(This,pfSmartSizing)

#define IMsRdpClientAdvancedSettings2_put_RdpdrLocalPrintingDocName(This,localPrintingDocName)	\
    (This)->lpVtbl -> put_RdpdrLocalPrintingDocName(This,localPrintingDocName)

#define IMsRdpClientAdvancedSettings2_get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)	\
    (This)->lpVtbl -> get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)

#define IMsRdpClientAdvancedSettings2_put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings2_get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings2_put_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> put_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings2_get_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> get_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings2_put_ClearTextPassword(This,clearTextPassword)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,clearTextPassword)

#define IMsRdpClientAdvancedSettings2_put_DisplayConnectionBar(This,fDisplayConnectionBar)	\
    (This)->lpVtbl -> put_DisplayConnectionBar(This,fDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings2_get_DisplayConnectionBar(This,pDisplayConnectionBar)	\
    (This)->lpVtbl -> get_DisplayConnectionBar(This,pDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings2_put_PinConnectionBar(This,fPinConnectionBar)	\
    (This)->lpVtbl -> put_PinConnectionBar(This,fPinConnectionBar)

#define IMsRdpClientAdvancedSettings2_get_PinConnectionBar(This,pPinConnectionBar)	\
    (This)->lpVtbl -> get_PinConnectionBar(This,pPinConnectionBar)

#define IMsRdpClientAdvancedSettings2_put_GrabFocusOnConnect(This,fGrabFocusOnConnect)	\
    (This)->lpVtbl -> put_GrabFocusOnConnect(This,fGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings2_get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)	\
    (This)->lpVtbl -> get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings2_put_LoadBalanceInfo(This,newLBInfo)	\
    (This)->lpVtbl -> put_LoadBalanceInfo(This,newLBInfo)

#define IMsRdpClientAdvancedSettings2_get_LoadBalanceInfo(This,pLBInfo)	\
    (This)->lpVtbl -> get_LoadBalanceInfo(This,pLBInfo)

#define IMsRdpClientAdvancedSettings2_put_RedirectDrives(This,redirectDrives)	\
    (This)->lpVtbl -> put_RedirectDrives(This,redirectDrives)

#define IMsRdpClientAdvancedSettings2_get_RedirectDrives(This,pRedirectDrives)	\
    (This)->lpVtbl -> get_RedirectDrives(This,pRedirectDrives)

#define IMsRdpClientAdvancedSettings2_put_RedirectPrinters(This,redirectPrinters)	\
    (This)->lpVtbl -> put_RedirectPrinters(This,redirectPrinters)

#define IMsRdpClientAdvancedSettings2_get_RedirectPrinters(This,pRedirectPrinters)	\
    (This)->lpVtbl -> get_RedirectPrinters(This,pRedirectPrinters)

#define IMsRdpClientAdvancedSettings2_put_RedirectPorts(This,redirectPorts)	\
    (This)->lpVtbl -> put_RedirectPorts(This,redirectPorts)

#define IMsRdpClientAdvancedSettings2_get_RedirectPorts(This,pRedirectPorts)	\
    (This)->lpVtbl -> get_RedirectPorts(This,pRedirectPorts)

#define IMsRdpClientAdvancedSettings2_put_RedirectSmartCards(This,redirectSmartCards)	\
    (This)->lpVtbl -> put_RedirectSmartCards(This,redirectSmartCards)

#define IMsRdpClientAdvancedSettings2_get_RedirectSmartCards(This,pRedirectSmartCards)	\
    (This)->lpVtbl -> get_RedirectSmartCards(This,pRedirectSmartCards)

#define IMsRdpClientAdvancedSettings2_put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings2_get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings2_put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings2_get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings2_put_PerformanceFlags(This,DisableList)	\
    (This)->lpVtbl -> put_PerformanceFlags(This,DisableList)

#define IMsRdpClientAdvancedSettings2_get_PerformanceFlags(This,pDisableList)	\
    (This)->lpVtbl -> get_PerformanceFlags(This,pDisableList)

#define IMsRdpClientAdvancedSettings2_put_ConnectWithEndpoint(This,ConnectEndpoint)	\
    (This)->lpVtbl -> put_ConnectWithEndpoint(This,ConnectEndpoint)

#define IMsRdpClientAdvancedSettings2_put_NotifyTSPublicKey(This,fNotify)	\
    (This)->lpVtbl -> put_NotifyTSPublicKey(This,fNotify)

#define IMsRdpClientAdvancedSettings2_get_NotifyTSPublicKey(This,pfNotify)	\
    (This)->lpVtbl -> get_NotifyTSPublicKey(This,pfNotify)


#define IMsRdpClientAdvancedSettings2_get_CanAutoReconnect(This,pfCanAutoReconnect)	\
    (This)->lpVtbl -> get_CanAutoReconnect(This,pfCanAutoReconnect)

#define IMsRdpClientAdvancedSettings2_put_EnableAutoReconnect(This,fEnableAutoReconnect)	\
    (This)->lpVtbl -> put_EnableAutoReconnect(This,fEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings2_get_EnableAutoReconnect(This,pfEnableAutoReconnect)	\
    (This)->lpVtbl -> get_EnableAutoReconnect(This,pfEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings2_put_MaxReconnectAttempts(This,MaxReconnectAttempts)	\
    (This)->lpVtbl -> put_MaxReconnectAttempts(This,MaxReconnectAttempts)

#define IMsRdpClientAdvancedSettings2_get_MaxReconnectAttempts(This,pMaxReconnectAttempts)	\
    (This)->lpVtbl -> get_MaxReconnectAttempts(This,pMaxReconnectAttempts)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings2_get_CanAutoReconnect_Proxy( 
    IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAutoReconnect);


void __RPC_STUB IMsRdpClientAdvancedSettings2_get_CanAutoReconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings2_put_EnableAutoReconnect_Proxy( 
    IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fEnableAutoReconnect);


void __RPC_STUB IMsRdpClientAdvancedSettings2_put_EnableAutoReconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings2_get_EnableAutoReconnect_Proxy( 
    IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfEnableAutoReconnect);


void __RPC_STUB IMsRdpClientAdvancedSettings2_get_EnableAutoReconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings2_put_MaxReconnectAttempts_Proxy( 
    IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
    /* [in] */ LONG MaxReconnectAttempts);


void __RPC_STUB IMsRdpClientAdvancedSettings2_put_MaxReconnectAttempts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings2_get_MaxReconnectAttempts_Proxy( 
    IMsRdpClientAdvancedSettings2 __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pMaxReconnectAttempts);


void __RPC_STUB IMsRdpClientAdvancedSettings2_get_MaxReconnectAttempts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientAdvancedSettings2_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings3_INTERFACE_DEFINED__
#define __IMsRdpClientAdvancedSettings3_INTERFACE_DEFINED__

/* interface IMsRdpClientAdvancedSettings3 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientAdvancedSettings3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19cd856b-c542-4c53-acee-f127e3be1a59")
    IMsRdpClientAdvancedSettings3 : public IMsRdpClientAdvancedSettings2
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionBarShowMinimizeButton( 
            /* [in] */ VARIANT_BOOL fShowMinimize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionBarShowMinimizeButton( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowMinimize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionBarShowRestoreButton( 
            /* [in] */ VARIANT_BOOL fShowRestore) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionBarShowRestoreButton( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRestore) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientAdvancedSettings3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compress )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG compress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compress )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcompress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG allowBackgroundInput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyBoardLayoutStr )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR KeyBoardLayoutStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PluginDlls )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR PluginDlls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconFile )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR IconFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconIndex )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG IconIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BOOL ContainerHandledFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BOOL DisableRdpdr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmoothScroll )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG smoothScroll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmoothScroll )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psmoothScroll);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG acceleratorPassthrough);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG shadowBitmap);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransportType )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG transportType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportType )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *ptransportType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SasSequence )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG sasSequence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SasSequence )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psasSequence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG encryptionEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG dedicatedTerminal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RDPPort )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG rdpPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RDPPort )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *prdpPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableMouse )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG enableMouse);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableMouse )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableMouse);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG disableCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG enableWindowsKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG doubleClickDetect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaximizeShell )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG maximizeShell);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaximizeShell )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltShiftTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG orderDrawThreshold);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bitmapCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bScale);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbScale);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG numBitmapCaches);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG cachePersistenceActive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PersistCacheDirectory )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR PersistCacheDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG brushSupportLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG minInputSendInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG inputEventsAtOnce);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxEventCount )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG maxEventCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxEventCount )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG keepAliveInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG shutdownTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG overallConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG singleConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardType )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG keyboardType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardType )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG keyboardSubType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG keyboardFunctionKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG winceFixedPalette);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL connectToServerConsole);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG minutesToIdleTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmartSizing )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSmartSizing);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmartSizing )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR localPrintingDocName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR clipCleanTempDirString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR clipPasteInfoString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR clearTextPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fDisplayConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPinConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fGrabFocusOnConnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ BSTR newLBInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLBInfo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectDrives )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectDrives )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPrinters);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPorts )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPorts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPorts )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectSmartCards);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG DisableList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pDisableList);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectWithEndpoint )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanAutoReconnect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fEnableAutoReconnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfEnableAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ LONG MaxReconnectAttempts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pMaxReconnectAttempts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowMinimizeButton )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowMinimize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowMinimizeButton )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowMinimize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowRestoreButton )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowRestore);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowRestoreButton )( 
            IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRestore);
        
        END_INTERFACE
    } IMsRdpClientAdvancedSettings3Vtbl;

    interface IMsRdpClientAdvancedSettings3
    {
        CONST_VTBL struct IMsRdpClientAdvancedSettings3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientAdvancedSettings3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientAdvancedSettings3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientAdvancedSettings3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientAdvancedSettings3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientAdvancedSettings3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientAdvancedSettings3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientAdvancedSettings3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientAdvancedSettings3_put_Compress(This,compress)	\
    (This)->lpVtbl -> put_Compress(This,compress)

#define IMsRdpClientAdvancedSettings3_get_Compress(This,pcompress)	\
    (This)->lpVtbl -> get_Compress(This,pcompress)

#define IMsRdpClientAdvancedSettings3_put_BitmapPeristence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPeristence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings3_get_BitmapPeristence(This,pbitmapPeristence)	\
    (This)->lpVtbl -> get_BitmapPeristence(This,pbitmapPeristence)

#define IMsRdpClientAdvancedSettings3_put_allowBackgroundInput(This,allowBackgroundInput)	\
    (This)->lpVtbl -> put_allowBackgroundInput(This,allowBackgroundInput)

#define IMsRdpClientAdvancedSettings3_get_allowBackgroundInput(This,pallowBackgroundInput)	\
    (This)->lpVtbl -> get_allowBackgroundInput(This,pallowBackgroundInput)

#define IMsRdpClientAdvancedSettings3_put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)	\
    (This)->lpVtbl -> put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)

#define IMsRdpClientAdvancedSettings3_put_PluginDlls(This,PluginDlls)	\
    (This)->lpVtbl -> put_PluginDlls(This,PluginDlls)

#define IMsRdpClientAdvancedSettings3_put_IconFile(This,IconFile)	\
    (This)->lpVtbl -> put_IconFile(This,IconFile)

#define IMsRdpClientAdvancedSettings3_put_IconIndex(This,IconIndex)	\
    (This)->lpVtbl -> put_IconIndex(This,IconIndex)

#define IMsRdpClientAdvancedSettings3_put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)	\
    (This)->lpVtbl -> put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings3_get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)	\
    (This)->lpVtbl -> get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings3_put_DisableRdpdr(This,DisableRdpdr)	\
    (This)->lpVtbl -> put_DisableRdpdr(This,DisableRdpdr)

#define IMsRdpClientAdvancedSettings3_get_DisableRdpdr(This,pDisableRdpdr)	\
    (This)->lpVtbl -> get_DisableRdpdr(This,pDisableRdpdr)


#define IMsRdpClientAdvancedSettings3_put_SmoothScroll(This,smoothScroll)	\
    (This)->lpVtbl -> put_SmoothScroll(This,smoothScroll)

#define IMsRdpClientAdvancedSettings3_get_SmoothScroll(This,psmoothScroll)	\
    (This)->lpVtbl -> get_SmoothScroll(This,psmoothScroll)

#define IMsRdpClientAdvancedSettings3_put_AcceleratorPassthrough(This,acceleratorPassthrough)	\
    (This)->lpVtbl -> put_AcceleratorPassthrough(This,acceleratorPassthrough)

#define IMsRdpClientAdvancedSettings3_get_AcceleratorPassthrough(This,pacceleratorPassthrough)	\
    (This)->lpVtbl -> get_AcceleratorPassthrough(This,pacceleratorPassthrough)

#define IMsRdpClientAdvancedSettings3_put_ShadowBitmap(This,shadowBitmap)	\
    (This)->lpVtbl -> put_ShadowBitmap(This,shadowBitmap)

#define IMsRdpClientAdvancedSettings3_get_ShadowBitmap(This,pshadowBitmap)	\
    (This)->lpVtbl -> get_ShadowBitmap(This,pshadowBitmap)

#define IMsRdpClientAdvancedSettings3_put_TransportType(This,transportType)	\
    (This)->lpVtbl -> put_TransportType(This,transportType)

#define IMsRdpClientAdvancedSettings3_get_TransportType(This,ptransportType)	\
    (This)->lpVtbl -> get_TransportType(This,ptransportType)

#define IMsRdpClientAdvancedSettings3_put_SasSequence(This,sasSequence)	\
    (This)->lpVtbl -> put_SasSequence(This,sasSequence)

#define IMsRdpClientAdvancedSettings3_get_SasSequence(This,psasSequence)	\
    (This)->lpVtbl -> get_SasSequence(This,psasSequence)

#define IMsRdpClientAdvancedSettings3_put_EncryptionEnabled(This,encryptionEnabled)	\
    (This)->lpVtbl -> put_EncryptionEnabled(This,encryptionEnabled)

#define IMsRdpClientAdvancedSettings3_get_EncryptionEnabled(This,pencryptionEnabled)	\
    (This)->lpVtbl -> get_EncryptionEnabled(This,pencryptionEnabled)

#define IMsRdpClientAdvancedSettings3_put_DedicatedTerminal(This,dedicatedTerminal)	\
    (This)->lpVtbl -> put_DedicatedTerminal(This,dedicatedTerminal)

#define IMsRdpClientAdvancedSettings3_get_DedicatedTerminal(This,pdedicatedTerminal)	\
    (This)->lpVtbl -> get_DedicatedTerminal(This,pdedicatedTerminal)

#define IMsRdpClientAdvancedSettings3_put_RDPPort(This,rdpPort)	\
    (This)->lpVtbl -> put_RDPPort(This,rdpPort)

#define IMsRdpClientAdvancedSettings3_get_RDPPort(This,prdpPort)	\
    (This)->lpVtbl -> get_RDPPort(This,prdpPort)

#define IMsRdpClientAdvancedSettings3_put_EnableMouse(This,enableMouse)	\
    (This)->lpVtbl -> put_EnableMouse(This,enableMouse)

#define IMsRdpClientAdvancedSettings3_get_EnableMouse(This,penableMouse)	\
    (This)->lpVtbl -> get_EnableMouse(This,penableMouse)

#define IMsRdpClientAdvancedSettings3_put_DisableCtrlAltDel(This,disableCtrlAltDel)	\
    (This)->lpVtbl -> put_DisableCtrlAltDel(This,disableCtrlAltDel)

#define IMsRdpClientAdvancedSettings3_get_DisableCtrlAltDel(This,pdisableCtrlAltDel)	\
    (This)->lpVtbl -> get_DisableCtrlAltDel(This,pdisableCtrlAltDel)

#define IMsRdpClientAdvancedSettings3_put_EnableWindowsKey(This,enableWindowsKey)	\
    (This)->lpVtbl -> put_EnableWindowsKey(This,enableWindowsKey)

#define IMsRdpClientAdvancedSettings3_get_EnableWindowsKey(This,penableWindowsKey)	\
    (This)->lpVtbl -> get_EnableWindowsKey(This,penableWindowsKey)

#define IMsRdpClientAdvancedSettings3_put_DoubleClickDetect(This,doubleClickDetect)	\
    (This)->lpVtbl -> put_DoubleClickDetect(This,doubleClickDetect)

#define IMsRdpClientAdvancedSettings3_get_DoubleClickDetect(This,pdoubleClickDetect)	\
    (This)->lpVtbl -> get_DoubleClickDetect(This,pdoubleClickDetect)

#define IMsRdpClientAdvancedSettings3_put_MaximizeShell(This,maximizeShell)	\
    (This)->lpVtbl -> put_MaximizeShell(This,maximizeShell)

#define IMsRdpClientAdvancedSettings3_get_MaximizeShell(This,pmaximizeShell)	\
    (This)->lpVtbl -> get_MaximizeShell(This,pmaximizeShell)

#define IMsRdpClientAdvancedSettings3_put_HotKeyFullScreen(This,hotKeyFullScreen)	\
    (This)->lpVtbl -> put_HotKeyFullScreen(This,hotKeyFullScreen)

#define IMsRdpClientAdvancedSettings3_get_HotKeyFullScreen(This,photKeyFullScreen)	\
    (This)->lpVtbl -> get_HotKeyFullScreen(This,photKeyFullScreen)

#define IMsRdpClientAdvancedSettings3_put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)	\
    (This)->lpVtbl -> put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings3_get_HotKeyCtrlEsc(This,photKeyCtrlEsc)	\
    (This)->lpVtbl -> get_HotKeyCtrlEsc(This,photKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings3_put_HotKeyAltEsc(This,hotKeyAltEsc)	\
    (This)->lpVtbl -> put_HotKeyAltEsc(This,hotKeyAltEsc)

#define IMsRdpClientAdvancedSettings3_get_HotKeyAltEsc(This,photKeyAltEsc)	\
    (This)->lpVtbl -> get_HotKeyAltEsc(This,photKeyAltEsc)

#define IMsRdpClientAdvancedSettings3_put_HotKeyAltTab(This,hotKeyAltTab)	\
    (This)->lpVtbl -> put_HotKeyAltTab(This,hotKeyAltTab)

#define IMsRdpClientAdvancedSettings3_get_HotKeyAltTab(This,photKeyAltTab)	\
    (This)->lpVtbl -> get_HotKeyAltTab(This,photKeyAltTab)

#define IMsRdpClientAdvancedSettings3_put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)	\
    (This)->lpVtbl -> put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings3_get_HotKeyAltShiftTab(This,photKeyAltShiftTab)	\
    (This)->lpVtbl -> get_HotKeyAltShiftTab(This,photKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings3_put_HotKeyAltSpace(This,hotKeyAltSpace)	\
    (This)->lpVtbl -> put_HotKeyAltSpace(This,hotKeyAltSpace)

#define IMsRdpClientAdvancedSettings3_get_HotKeyAltSpace(This,photKeyAltSpace)	\
    (This)->lpVtbl -> get_HotKeyAltSpace(This,photKeyAltSpace)

#define IMsRdpClientAdvancedSettings3_put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)	\
    (This)->lpVtbl -> put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings3_get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)	\
    (This)->lpVtbl -> get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings3_put_orderDrawThreshold(This,orderDrawThreshold)	\
    (This)->lpVtbl -> put_orderDrawThreshold(This,orderDrawThreshold)

#define IMsRdpClientAdvancedSettings3_get_orderDrawThreshold(This,porderDrawThreshold)	\
    (This)->lpVtbl -> get_orderDrawThreshold(This,porderDrawThreshold)

#define IMsRdpClientAdvancedSettings3_put_BitmapCacheSize(This,bitmapCacheSize)	\
    (This)->lpVtbl -> put_BitmapCacheSize(This,bitmapCacheSize)

#define IMsRdpClientAdvancedSettings3_get_BitmapCacheSize(This,pbitmapCacheSize)	\
    (This)->lpVtbl -> get_BitmapCacheSize(This,pbitmapCacheSize)

#define IMsRdpClientAdvancedSettings3_put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings3_get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings3_put_ScaleBitmapCachesByBPP(This,bScale)	\
    (This)->lpVtbl -> put_ScaleBitmapCachesByBPP(This,bScale)

#define IMsRdpClientAdvancedSettings3_get_ScaleBitmapCachesByBPP(This,pbScale)	\
    (This)->lpVtbl -> get_ScaleBitmapCachesByBPP(This,pbScale)

#define IMsRdpClientAdvancedSettings3_put_NumBitmapCaches(This,numBitmapCaches)	\
    (This)->lpVtbl -> put_NumBitmapCaches(This,numBitmapCaches)

#define IMsRdpClientAdvancedSettings3_get_NumBitmapCaches(This,pnumBitmapCaches)	\
    (This)->lpVtbl -> get_NumBitmapCaches(This,pnumBitmapCaches)

#define IMsRdpClientAdvancedSettings3_put_CachePersistenceActive(This,cachePersistenceActive)	\
    (This)->lpVtbl -> put_CachePersistenceActive(This,cachePersistenceActive)

#define IMsRdpClientAdvancedSettings3_get_CachePersistenceActive(This,pcachePersistenceActive)	\
    (This)->lpVtbl -> get_CachePersistenceActive(This,pcachePersistenceActive)

#define IMsRdpClientAdvancedSettings3_put_PersistCacheDirectory(This,PersistCacheDirectory)	\
    (This)->lpVtbl -> put_PersistCacheDirectory(This,PersistCacheDirectory)

#define IMsRdpClientAdvancedSettings3_put_brushSupportLevel(This,brushSupportLevel)	\
    (This)->lpVtbl -> put_brushSupportLevel(This,brushSupportLevel)

#define IMsRdpClientAdvancedSettings3_get_brushSupportLevel(This,pbrushSupportLevel)	\
    (This)->lpVtbl -> get_brushSupportLevel(This,pbrushSupportLevel)

#define IMsRdpClientAdvancedSettings3_put_minInputSendInterval(This,minInputSendInterval)	\
    (This)->lpVtbl -> put_minInputSendInterval(This,minInputSendInterval)

#define IMsRdpClientAdvancedSettings3_get_minInputSendInterval(This,pminInputSendInterval)	\
    (This)->lpVtbl -> get_minInputSendInterval(This,pminInputSendInterval)

#define IMsRdpClientAdvancedSettings3_put_InputEventsAtOnce(This,inputEventsAtOnce)	\
    (This)->lpVtbl -> put_InputEventsAtOnce(This,inputEventsAtOnce)

#define IMsRdpClientAdvancedSettings3_get_InputEventsAtOnce(This,pinputEventsAtOnce)	\
    (This)->lpVtbl -> get_InputEventsAtOnce(This,pinputEventsAtOnce)

#define IMsRdpClientAdvancedSettings3_put_maxEventCount(This,maxEventCount)	\
    (This)->lpVtbl -> put_maxEventCount(This,maxEventCount)

#define IMsRdpClientAdvancedSettings3_get_maxEventCount(This,pmaxEventCount)	\
    (This)->lpVtbl -> get_maxEventCount(This,pmaxEventCount)

#define IMsRdpClientAdvancedSettings3_put_keepAliveInterval(This,keepAliveInterval)	\
    (This)->lpVtbl -> put_keepAliveInterval(This,keepAliveInterval)

#define IMsRdpClientAdvancedSettings3_get_keepAliveInterval(This,pkeepAliveInterval)	\
    (This)->lpVtbl -> get_keepAliveInterval(This,pkeepAliveInterval)

#define IMsRdpClientAdvancedSettings3_put_shutdownTimeout(This,shutdownTimeout)	\
    (This)->lpVtbl -> put_shutdownTimeout(This,shutdownTimeout)

#define IMsRdpClientAdvancedSettings3_get_shutdownTimeout(This,pshutdownTimeout)	\
    (This)->lpVtbl -> get_shutdownTimeout(This,pshutdownTimeout)

#define IMsRdpClientAdvancedSettings3_put_overallConnectionTimeout(This,overallConnectionTimeout)	\
    (This)->lpVtbl -> put_overallConnectionTimeout(This,overallConnectionTimeout)

#define IMsRdpClientAdvancedSettings3_get_overallConnectionTimeout(This,poverallConnectionTimeout)	\
    (This)->lpVtbl -> get_overallConnectionTimeout(This,poverallConnectionTimeout)

#define IMsRdpClientAdvancedSettings3_put_singleConnectionTimeout(This,singleConnectionTimeout)	\
    (This)->lpVtbl -> put_singleConnectionTimeout(This,singleConnectionTimeout)

#define IMsRdpClientAdvancedSettings3_get_singleConnectionTimeout(This,psingleConnectionTimeout)	\
    (This)->lpVtbl -> get_singleConnectionTimeout(This,psingleConnectionTimeout)

#define IMsRdpClientAdvancedSettings3_put_KeyboardType(This,keyboardType)	\
    (This)->lpVtbl -> put_KeyboardType(This,keyboardType)

#define IMsRdpClientAdvancedSettings3_get_KeyboardType(This,pkeyboardType)	\
    (This)->lpVtbl -> get_KeyboardType(This,pkeyboardType)

#define IMsRdpClientAdvancedSettings3_put_KeyboardSubType(This,keyboardSubType)	\
    (This)->lpVtbl -> put_KeyboardSubType(This,keyboardSubType)

#define IMsRdpClientAdvancedSettings3_get_KeyboardSubType(This,pkeyboardSubType)	\
    (This)->lpVtbl -> get_KeyboardSubType(This,pkeyboardSubType)

#define IMsRdpClientAdvancedSettings3_put_KeyboardFunctionKey(This,keyboardFunctionKey)	\
    (This)->lpVtbl -> put_KeyboardFunctionKey(This,keyboardFunctionKey)

#define IMsRdpClientAdvancedSettings3_get_KeyboardFunctionKey(This,pkeyboardFunctionKey)	\
    (This)->lpVtbl -> get_KeyboardFunctionKey(This,pkeyboardFunctionKey)

#define IMsRdpClientAdvancedSettings3_put_WinceFixedPalette(This,winceFixedPalette)	\
    (This)->lpVtbl -> put_WinceFixedPalette(This,winceFixedPalette)

#define IMsRdpClientAdvancedSettings3_get_WinceFixedPalette(This,pwinceFixedPalette)	\
    (This)->lpVtbl -> get_WinceFixedPalette(This,pwinceFixedPalette)

#define IMsRdpClientAdvancedSettings3_put_ConnectToServerConsole(This,connectToServerConsole)	\
    (This)->lpVtbl -> put_ConnectToServerConsole(This,connectToServerConsole)

#define IMsRdpClientAdvancedSettings3_get_ConnectToServerConsole(This,pConnectToConsole)	\
    (This)->lpVtbl -> get_ConnectToServerConsole(This,pConnectToConsole)

#define IMsRdpClientAdvancedSettings3_put_BitmapPersistence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPersistence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings3_get_BitmapPersistence(This,pbitmapPersistence)	\
    (This)->lpVtbl -> get_BitmapPersistence(This,pbitmapPersistence)

#define IMsRdpClientAdvancedSettings3_put_MinutesToIdleTimeout(This,minutesToIdleTimeout)	\
    (This)->lpVtbl -> put_MinutesToIdleTimeout(This,minutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings3_get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)	\
    (This)->lpVtbl -> get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings3_put_SmartSizing(This,fSmartSizing)	\
    (This)->lpVtbl -> put_SmartSizing(This,fSmartSizing)

#define IMsRdpClientAdvancedSettings3_get_SmartSizing(This,pfSmartSizing)	\
    (This)->lpVtbl -> get_SmartSizing(This,pfSmartSizing)

#define IMsRdpClientAdvancedSettings3_put_RdpdrLocalPrintingDocName(This,localPrintingDocName)	\
    (This)->lpVtbl -> put_RdpdrLocalPrintingDocName(This,localPrintingDocName)

#define IMsRdpClientAdvancedSettings3_get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)	\
    (This)->lpVtbl -> get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)

#define IMsRdpClientAdvancedSettings3_put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings3_get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings3_put_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> put_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings3_get_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> get_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings3_put_ClearTextPassword(This,clearTextPassword)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,clearTextPassword)

#define IMsRdpClientAdvancedSettings3_put_DisplayConnectionBar(This,fDisplayConnectionBar)	\
    (This)->lpVtbl -> put_DisplayConnectionBar(This,fDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings3_get_DisplayConnectionBar(This,pDisplayConnectionBar)	\
    (This)->lpVtbl -> get_DisplayConnectionBar(This,pDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings3_put_PinConnectionBar(This,fPinConnectionBar)	\
    (This)->lpVtbl -> put_PinConnectionBar(This,fPinConnectionBar)

#define IMsRdpClientAdvancedSettings3_get_PinConnectionBar(This,pPinConnectionBar)	\
    (This)->lpVtbl -> get_PinConnectionBar(This,pPinConnectionBar)

#define IMsRdpClientAdvancedSettings3_put_GrabFocusOnConnect(This,fGrabFocusOnConnect)	\
    (This)->lpVtbl -> put_GrabFocusOnConnect(This,fGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings3_get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)	\
    (This)->lpVtbl -> get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings3_put_LoadBalanceInfo(This,newLBInfo)	\
    (This)->lpVtbl -> put_LoadBalanceInfo(This,newLBInfo)

#define IMsRdpClientAdvancedSettings3_get_LoadBalanceInfo(This,pLBInfo)	\
    (This)->lpVtbl -> get_LoadBalanceInfo(This,pLBInfo)

#define IMsRdpClientAdvancedSettings3_put_RedirectDrives(This,redirectDrives)	\
    (This)->lpVtbl -> put_RedirectDrives(This,redirectDrives)

#define IMsRdpClientAdvancedSettings3_get_RedirectDrives(This,pRedirectDrives)	\
    (This)->lpVtbl -> get_RedirectDrives(This,pRedirectDrives)

#define IMsRdpClientAdvancedSettings3_put_RedirectPrinters(This,redirectPrinters)	\
    (This)->lpVtbl -> put_RedirectPrinters(This,redirectPrinters)

#define IMsRdpClientAdvancedSettings3_get_RedirectPrinters(This,pRedirectPrinters)	\
    (This)->lpVtbl -> get_RedirectPrinters(This,pRedirectPrinters)

#define IMsRdpClientAdvancedSettings3_put_RedirectPorts(This,redirectPorts)	\
    (This)->lpVtbl -> put_RedirectPorts(This,redirectPorts)

#define IMsRdpClientAdvancedSettings3_get_RedirectPorts(This,pRedirectPorts)	\
    (This)->lpVtbl -> get_RedirectPorts(This,pRedirectPorts)

#define IMsRdpClientAdvancedSettings3_put_RedirectSmartCards(This,redirectSmartCards)	\
    (This)->lpVtbl -> put_RedirectSmartCards(This,redirectSmartCards)

#define IMsRdpClientAdvancedSettings3_get_RedirectSmartCards(This,pRedirectSmartCards)	\
    (This)->lpVtbl -> get_RedirectSmartCards(This,pRedirectSmartCards)

#define IMsRdpClientAdvancedSettings3_put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings3_get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings3_put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings3_get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings3_put_PerformanceFlags(This,DisableList)	\
    (This)->lpVtbl -> put_PerformanceFlags(This,DisableList)

#define IMsRdpClientAdvancedSettings3_get_PerformanceFlags(This,pDisableList)	\
    (This)->lpVtbl -> get_PerformanceFlags(This,pDisableList)

#define IMsRdpClientAdvancedSettings3_put_ConnectWithEndpoint(This,ConnectEndpoint)	\
    (This)->lpVtbl -> put_ConnectWithEndpoint(This,ConnectEndpoint)

#define IMsRdpClientAdvancedSettings3_put_NotifyTSPublicKey(This,fNotify)	\
    (This)->lpVtbl -> put_NotifyTSPublicKey(This,fNotify)

#define IMsRdpClientAdvancedSettings3_get_NotifyTSPublicKey(This,pfNotify)	\
    (This)->lpVtbl -> get_NotifyTSPublicKey(This,pfNotify)


#define IMsRdpClientAdvancedSettings3_get_CanAutoReconnect(This,pfCanAutoReconnect)	\
    (This)->lpVtbl -> get_CanAutoReconnect(This,pfCanAutoReconnect)

#define IMsRdpClientAdvancedSettings3_put_EnableAutoReconnect(This,fEnableAutoReconnect)	\
    (This)->lpVtbl -> put_EnableAutoReconnect(This,fEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings3_get_EnableAutoReconnect(This,pfEnableAutoReconnect)	\
    (This)->lpVtbl -> get_EnableAutoReconnect(This,pfEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings3_put_MaxReconnectAttempts(This,MaxReconnectAttempts)	\
    (This)->lpVtbl -> put_MaxReconnectAttempts(This,MaxReconnectAttempts)

#define IMsRdpClientAdvancedSettings3_get_MaxReconnectAttempts(This,pMaxReconnectAttempts)	\
    (This)->lpVtbl -> get_MaxReconnectAttempts(This,pMaxReconnectAttempts)


#define IMsRdpClientAdvancedSettings3_put_ConnectionBarShowMinimizeButton(This,fShowMinimize)	\
    (This)->lpVtbl -> put_ConnectionBarShowMinimizeButton(This,fShowMinimize)

#define IMsRdpClientAdvancedSettings3_get_ConnectionBarShowMinimizeButton(This,pfShowMinimize)	\
    (This)->lpVtbl -> get_ConnectionBarShowMinimizeButton(This,pfShowMinimize)

#define IMsRdpClientAdvancedSettings3_put_ConnectionBarShowRestoreButton(This,fShowRestore)	\
    (This)->lpVtbl -> put_ConnectionBarShowRestoreButton(This,fShowRestore)

#define IMsRdpClientAdvancedSettings3_get_ConnectionBarShowRestoreButton(This,pfShowRestore)	\
    (This)->lpVtbl -> get_ConnectionBarShowRestoreButton(This,pfShowRestore)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings3_put_ConnectionBarShowMinimizeButton_Proxy( 
    IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fShowMinimize);


void __RPC_STUB IMsRdpClientAdvancedSettings3_put_ConnectionBarShowMinimizeButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings3_get_ConnectionBarShowMinimizeButton_Proxy( 
    IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowMinimize);


void __RPC_STUB IMsRdpClientAdvancedSettings3_get_ConnectionBarShowMinimizeButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings3_put_ConnectionBarShowRestoreButton_Proxy( 
    IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fShowRestore);


void __RPC_STUB IMsRdpClientAdvancedSettings3_put_ConnectionBarShowRestoreButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings3_get_ConnectionBarShowRestoreButton_Proxy( 
    IMsRdpClientAdvancedSettings3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRestore);


void __RPC_STUB IMsRdpClientAdvancedSettings3_get_ConnectionBarShowRestoreButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientAdvancedSettings3_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings4_INTERFACE_DEFINED__
#define __IMsRdpClientAdvancedSettings4_INTERFACE_DEFINED__

/* interface IMsRdpClientAdvancedSettings4 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientAdvancedSettings4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FBA7F64E-7345-4405-AE50-FA4A763DC0DE")
    IMsRdpClientAdvancedSettings4 : public IMsRdpClientAdvancedSettings3
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AuthenticationLevel( 
            /* [in] */ UINT uiAuthLevel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AuthenticationLevel( 
            /* [retval][out] */ UINT __RPC_FAR *puiAuthLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientAdvancedSettings4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compress )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG compress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compress )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcompress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG allowBackgroundInput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyBoardLayoutStr )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR KeyBoardLayoutStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PluginDlls )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR PluginDlls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconFile )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR IconFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconIndex )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG IconIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BOOL ContainerHandledFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BOOL DisableRdpdr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmoothScroll )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG smoothScroll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmoothScroll )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psmoothScroll);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG acceleratorPassthrough);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG shadowBitmap);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransportType )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG transportType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportType )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *ptransportType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SasSequence )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG sasSequence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SasSequence )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psasSequence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG encryptionEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG dedicatedTerminal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RDPPort )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG rdpPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RDPPort )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *prdpPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableMouse )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG enableMouse);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableMouse )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableMouse);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG disableCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG enableWindowsKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG doubleClickDetect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaximizeShell )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG maximizeShell);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaximizeShell )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltShiftTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG orderDrawThreshold);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bitmapCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bScale);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbScale);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG numBitmapCaches);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG cachePersistenceActive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PersistCacheDirectory )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR PersistCacheDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG brushSupportLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG minInputSendInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG inputEventsAtOnce);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxEventCount )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG maxEventCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxEventCount )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG keepAliveInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG shutdownTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG overallConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG singleConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardType )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG keyboardType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardType )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG keyboardSubType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG keyboardFunctionKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG winceFixedPalette);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL connectToServerConsole);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG minutesToIdleTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmartSizing )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSmartSizing);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmartSizing )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR localPrintingDocName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR clipCleanTempDirString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR clipPasteInfoString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR clearTextPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fDisplayConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPinConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fGrabFocusOnConnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ BSTR newLBInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLBInfo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectDrives )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectDrives )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPrinters);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPorts )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPorts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPorts )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectSmartCards);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG DisableList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pDisableList);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectWithEndpoint )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanAutoReconnect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fEnableAutoReconnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfEnableAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ LONG MaxReconnectAttempts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pMaxReconnectAttempts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowMinimizeButton )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowMinimize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowMinimizeButton )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowMinimize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowRestoreButton )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowRestore);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowRestoreButton )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRestore);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AuthenticationLevel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [in] */ UINT uiAuthLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AuthenticationLevel )( 
            IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
            /* [retval][out] */ UINT __RPC_FAR *puiAuthLevel);
        
        END_INTERFACE
    } IMsRdpClientAdvancedSettings4Vtbl;

    interface IMsRdpClientAdvancedSettings4
    {
        CONST_VTBL struct IMsRdpClientAdvancedSettings4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientAdvancedSettings4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientAdvancedSettings4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientAdvancedSettings4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientAdvancedSettings4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientAdvancedSettings4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientAdvancedSettings4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientAdvancedSettings4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientAdvancedSettings4_put_Compress(This,compress)	\
    (This)->lpVtbl -> put_Compress(This,compress)

#define IMsRdpClientAdvancedSettings4_get_Compress(This,pcompress)	\
    (This)->lpVtbl -> get_Compress(This,pcompress)

#define IMsRdpClientAdvancedSettings4_put_BitmapPeristence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPeristence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings4_get_BitmapPeristence(This,pbitmapPeristence)	\
    (This)->lpVtbl -> get_BitmapPeristence(This,pbitmapPeristence)

#define IMsRdpClientAdvancedSettings4_put_allowBackgroundInput(This,allowBackgroundInput)	\
    (This)->lpVtbl -> put_allowBackgroundInput(This,allowBackgroundInput)

#define IMsRdpClientAdvancedSettings4_get_allowBackgroundInput(This,pallowBackgroundInput)	\
    (This)->lpVtbl -> get_allowBackgroundInput(This,pallowBackgroundInput)

#define IMsRdpClientAdvancedSettings4_put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)	\
    (This)->lpVtbl -> put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)

#define IMsRdpClientAdvancedSettings4_put_PluginDlls(This,PluginDlls)	\
    (This)->lpVtbl -> put_PluginDlls(This,PluginDlls)

#define IMsRdpClientAdvancedSettings4_put_IconFile(This,IconFile)	\
    (This)->lpVtbl -> put_IconFile(This,IconFile)

#define IMsRdpClientAdvancedSettings4_put_IconIndex(This,IconIndex)	\
    (This)->lpVtbl -> put_IconIndex(This,IconIndex)

#define IMsRdpClientAdvancedSettings4_put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)	\
    (This)->lpVtbl -> put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings4_get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)	\
    (This)->lpVtbl -> get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings4_put_DisableRdpdr(This,DisableRdpdr)	\
    (This)->lpVtbl -> put_DisableRdpdr(This,DisableRdpdr)

#define IMsRdpClientAdvancedSettings4_get_DisableRdpdr(This,pDisableRdpdr)	\
    (This)->lpVtbl -> get_DisableRdpdr(This,pDisableRdpdr)


#define IMsRdpClientAdvancedSettings4_put_SmoothScroll(This,smoothScroll)	\
    (This)->lpVtbl -> put_SmoothScroll(This,smoothScroll)

#define IMsRdpClientAdvancedSettings4_get_SmoothScroll(This,psmoothScroll)	\
    (This)->lpVtbl -> get_SmoothScroll(This,psmoothScroll)

#define IMsRdpClientAdvancedSettings4_put_AcceleratorPassthrough(This,acceleratorPassthrough)	\
    (This)->lpVtbl -> put_AcceleratorPassthrough(This,acceleratorPassthrough)

#define IMsRdpClientAdvancedSettings4_get_AcceleratorPassthrough(This,pacceleratorPassthrough)	\
    (This)->lpVtbl -> get_AcceleratorPassthrough(This,pacceleratorPassthrough)

#define IMsRdpClientAdvancedSettings4_put_ShadowBitmap(This,shadowBitmap)	\
    (This)->lpVtbl -> put_ShadowBitmap(This,shadowBitmap)

#define IMsRdpClientAdvancedSettings4_get_ShadowBitmap(This,pshadowBitmap)	\
    (This)->lpVtbl -> get_ShadowBitmap(This,pshadowBitmap)

#define IMsRdpClientAdvancedSettings4_put_TransportType(This,transportType)	\
    (This)->lpVtbl -> put_TransportType(This,transportType)

#define IMsRdpClientAdvancedSettings4_get_TransportType(This,ptransportType)	\
    (This)->lpVtbl -> get_TransportType(This,ptransportType)

#define IMsRdpClientAdvancedSettings4_put_SasSequence(This,sasSequence)	\
    (This)->lpVtbl -> put_SasSequence(This,sasSequence)

#define IMsRdpClientAdvancedSettings4_get_SasSequence(This,psasSequence)	\
    (This)->lpVtbl -> get_SasSequence(This,psasSequence)

#define IMsRdpClientAdvancedSettings4_put_EncryptionEnabled(This,encryptionEnabled)	\
    (This)->lpVtbl -> put_EncryptionEnabled(This,encryptionEnabled)

#define IMsRdpClientAdvancedSettings4_get_EncryptionEnabled(This,pencryptionEnabled)	\
    (This)->lpVtbl -> get_EncryptionEnabled(This,pencryptionEnabled)

#define IMsRdpClientAdvancedSettings4_put_DedicatedTerminal(This,dedicatedTerminal)	\
    (This)->lpVtbl -> put_DedicatedTerminal(This,dedicatedTerminal)

#define IMsRdpClientAdvancedSettings4_get_DedicatedTerminal(This,pdedicatedTerminal)	\
    (This)->lpVtbl -> get_DedicatedTerminal(This,pdedicatedTerminal)

#define IMsRdpClientAdvancedSettings4_put_RDPPort(This,rdpPort)	\
    (This)->lpVtbl -> put_RDPPort(This,rdpPort)

#define IMsRdpClientAdvancedSettings4_get_RDPPort(This,prdpPort)	\
    (This)->lpVtbl -> get_RDPPort(This,prdpPort)

#define IMsRdpClientAdvancedSettings4_put_EnableMouse(This,enableMouse)	\
    (This)->lpVtbl -> put_EnableMouse(This,enableMouse)

#define IMsRdpClientAdvancedSettings4_get_EnableMouse(This,penableMouse)	\
    (This)->lpVtbl -> get_EnableMouse(This,penableMouse)

#define IMsRdpClientAdvancedSettings4_put_DisableCtrlAltDel(This,disableCtrlAltDel)	\
    (This)->lpVtbl -> put_DisableCtrlAltDel(This,disableCtrlAltDel)

#define IMsRdpClientAdvancedSettings4_get_DisableCtrlAltDel(This,pdisableCtrlAltDel)	\
    (This)->lpVtbl -> get_DisableCtrlAltDel(This,pdisableCtrlAltDel)

#define IMsRdpClientAdvancedSettings4_put_EnableWindowsKey(This,enableWindowsKey)	\
    (This)->lpVtbl -> put_EnableWindowsKey(This,enableWindowsKey)

#define IMsRdpClientAdvancedSettings4_get_EnableWindowsKey(This,penableWindowsKey)	\
    (This)->lpVtbl -> get_EnableWindowsKey(This,penableWindowsKey)

#define IMsRdpClientAdvancedSettings4_put_DoubleClickDetect(This,doubleClickDetect)	\
    (This)->lpVtbl -> put_DoubleClickDetect(This,doubleClickDetect)

#define IMsRdpClientAdvancedSettings4_get_DoubleClickDetect(This,pdoubleClickDetect)	\
    (This)->lpVtbl -> get_DoubleClickDetect(This,pdoubleClickDetect)

#define IMsRdpClientAdvancedSettings4_put_MaximizeShell(This,maximizeShell)	\
    (This)->lpVtbl -> put_MaximizeShell(This,maximizeShell)

#define IMsRdpClientAdvancedSettings4_get_MaximizeShell(This,pmaximizeShell)	\
    (This)->lpVtbl -> get_MaximizeShell(This,pmaximizeShell)

#define IMsRdpClientAdvancedSettings4_put_HotKeyFullScreen(This,hotKeyFullScreen)	\
    (This)->lpVtbl -> put_HotKeyFullScreen(This,hotKeyFullScreen)

#define IMsRdpClientAdvancedSettings4_get_HotKeyFullScreen(This,photKeyFullScreen)	\
    (This)->lpVtbl -> get_HotKeyFullScreen(This,photKeyFullScreen)

#define IMsRdpClientAdvancedSettings4_put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)	\
    (This)->lpVtbl -> put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings4_get_HotKeyCtrlEsc(This,photKeyCtrlEsc)	\
    (This)->lpVtbl -> get_HotKeyCtrlEsc(This,photKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings4_put_HotKeyAltEsc(This,hotKeyAltEsc)	\
    (This)->lpVtbl -> put_HotKeyAltEsc(This,hotKeyAltEsc)

#define IMsRdpClientAdvancedSettings4_get_HotKeyAltEsc(This,photKeyAltEsc)	\
    (This)->lpVtbl -> get_HotKeyAltEsc(This,photKeyAltEsc)

#define IMsRdpClientAdvancedSettings4_put_HotKeyAltTab(This,hotKeyAltTab)	\
    (This)->lpVtbl -> put_HotKeyAltTab(This,hotKeyAltTab)

#define IMsRdpClientAdvancedSettings4_get_HotKeyAltTab(This,photKeyAltTab)	\
    (This)->lpVtbl -> get_HotKeyAltTab(This,photKeyAltTab)

#define IMsRdpClientAdvancedSettings4_put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)	\
    (This)->lpVtbl -> put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings4_get_HotKeyAltShiftTab(This,photKeyAltShiftTab)	\
    (This)->lpVtbl -> get_HotKeyAltShiftTab(This,photKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings4_put_HotKeyAltSpace(This,hotKeyAltSpace)	\
    (This)->lpVtbl -> put_HotKeyAltSpace(This,hotKeyAltSpace)

#define IMsRdpClientAdvancedSettings4_get_HotKeyAltSpace(This,photKeyAltSpace)	\
    (This)->lpVtbl -> get_HotKeyAltSpace(This,photKeyAltSpace)

#define IMsRdpClientAdvancedSettings4_put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)	\
    (This)->lpVtbl -> put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings4_get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)	\
    (This)->lpVtbl -> get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings4_put_orderDrawThreshold(This,orderDrawThreshold)	\
    (This)->lpVtbl -> put_orderDrawThreshold(This,orderDrawThreshold)

#define IMsRdpClientAdvancedSettings4_get_orderDrawThreshold(This,porderDrawThreshold)	\
    (This)->lpVtbl -> get_orderDrawThreshold(This,porderDrawThreshold)

#define IMsRdpClientAdvancedSettings4_put_BitmapCacheSize(This,bitmapCacheSize)	\
    (This)->lpVtbl -> put_BitmapCacheSize(This,bitmapCacheSize)

#define IMsRdpClientAdvancedSettings4_get_BitmapCacheSize(This,pbitmapCacheSize)	\
    (This)->lpVtbl -> get_BitmapCacheSize(This,pbitmapCacheSize)

#define IMsRdpClientAdvancedSettings4_put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings4_get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings4_put_ScaleBitmapCachesByBPP(This,bScale)	\
    (This)->lpVtbl -> put_ScaleBitmapCachesByBPP(This,bScale)

#define IMsRdpClientAdvancedSettings4_get_ScaleBitmapCachesByBPP(This,pbScale)	\
    (This)->lpVtbl -> get_ScaleBitmapCachesByBPP(This,pbScale)

#define IMsRdpClientAdvancedSettings4_put_NumBitmapCaches(This,numBitmapCaches)	\
    (This)->lpVtbl -> put_NumBitmapCaches(This,numBitmapCaches)

#define IMsRdpClientAdvancedSettings4_get_NumBitmapCaches(This,pnumBitmapCaches)	\
    (This)->lpVtbl -> get_NumBitmapCaches(This,pnumBitmapCaches)

#define IMsRdpClientAdvancedSettings4_put_CachePersistenceActive(This,cachePersistenceActive)	\
    (This)->lpVtbl -> put_CachePersistenceActive(This,cachePersistenceActive)

#define IMsRdpClientAdvancedSettings4_get_CachePersistenceActive(This,pcachePersistenceActive)	\
    (This)->lpVtbl -> get_CachePersistenceActive(This,pcachePersistenceActive)

#define IMsRdpClientAdvancedSettings4_put_PersistCacheDirectory(This,PersistCacheDirectory)	\
    (This)->lpVtbl -> put_PersistCacheDirectory(This,PersistCacheDirectory)

#define IMsRdpClientAdvancedSettings4_put_brushSupportLevel(This,brushSupportLevel)	\
    (This)->lpVtbl -> put_brushSupportLevel(This,brushSupportLevel)

#define IMsRdpClientAdvancedSettings4_get_brushSupportLevel(This,pbrushSupportLevel)	\
    (This)->lpVtbl -> get_brushSupportLevel(This,pbrushSupportLevel)

#define IMsRdpClientAdvancedSettings4_put_minInputSendInterval(This,minInputSendInterval)	\
    (This)->lpVtbl -> put_minInputSendInterval(This,minInputSendInterval)

#define IMsRdpClientAdvancedSettings4_get_minInputSendInterval(This,pminInputSendInterval)	\
    (This)->lpVtbl -> get_minInputSendInterval(This,pminInputSendInterval)

#define IMsRdpClientAdvancedSettings4_put_InputEventsAtOnce(This,inputEventsAtOnce)	\
    (This)->lpVtbl -> put_InputEventsAtOnce(This,inputEventsAtOnce)

#define IMsRdpClientAdvancedSettings4_get_InputEventsAtOnce(This,pinputEventsAtOnce)	\
    (This)->lpVtbl -> get_InputEventsAtOnce(This,pinputEventsAtOnce)

#define IMsRdpClientAdvancedSettings4_put_maxEventCount(This,maxEventCount)	\
    (This)->lpVtbl -> put_maxEventCount(This,maxEventCount)

#define IMsRdpClientAdvancedSettings4_get_maxEventCount(This,pmaxEventCount)	\
    (This)->lpVtbl -> get_maxEventCount(This,pmaxEventCount)

#define IMsRdpClientAdvancedSettings4_put_keepAliveInterval(This,keepAliveInterval)	\
    (This)->lpVtbl -> put_keepAliveInterval(This,keepAliveInterval)

#define IMsRdpClientAdvancedSettings4_get_keepAliveInterval(This,pkeepAliveInterval)	\
    (This)->lpVtbl -> get_keepAliveInterval(This,pkeepAliveInterval)

#define IMsRdpClientAdvancedSettings4_put_shutdownTimeout(This,shutdownTimeout)	\
    (This)->lpVtbl -> put_shutdownTimeout(This,shutdownTimeout)

#define IMsRdpClientAdvancedSettings4_get_shutdownTimeout(This,pshutdownTimeout)	\
    (This)->lpVtbl -> get_shutdownTimeout(This,pshutdownTimeout)

#define IMsRdpClientAdvancedSettings4_put_overallConnectionTimeout(This,overallConnectionTimeout)	\
    (This)->lpVtbl -> put_overallConnectionTimeout(This,overallConnectionTimeout)

#define IMsRdpClientAdvancedSettings4_get_overallConnectionTimeout(This,poverallConnectionTimeout)	\
    (This)->lpVtbl -> get_overallConnectionTimeout(This,poverallConnectionTimeout)

#define IMsRdpClientAdvancedSettings4_put_singleConnectionTimeout(This,singleConnectionTimeout)	\
    (This)->lpVtbl -> put_singleConnectionTimeout(This,singleConnectionTimeout)

#define IMsRdpClientAdvancedSettings4_get_singleConnectionTimeout(This,psingleConnectionTimeout)	\
    (This)->lpVtbl -> get_singleConnectionTimeout(This,psingleConnectionTimeout)

#define IMsRdpClientAdvancedSettings4_put_KeyboardType(This,keyboardType)	\
    (This)->lpVtbl -> put_KeyboardType(This,keyboardType)

#define IMsRdpClientAdvancedSettings4_get_KeyboardType(This,pkeyboardType)	\
    (This)->lpVtbl -> get_KeyboardType(This,pkeyboardType)

#define IMsRdpClientAdvancedSettings4_put_KeyboardSubType(This,keyboardSubType)	\
    (This)->lpVtbl -> put_KeyboardSubType(This,keyboardSubType)

#define IMsRdpClientAdvancedSettings4_get_KeyboardSubType(This,pkeyboardSubType)	\
    (This)->lpVtbl -> get_KeyboardSubType(This,pkeyboardSubType)

#define IMsRdpClientAdvancedSettings4_put_KeyboardFunctionKey(This,keyboardFunctionKey)	\
    (This)->lpVtbl -> put_KeyboardFunctionKey(This,keyboardFunctionKey)

#define IMsRdpClientAdvancedSettings4_get_KeyboardFunctionKey(This,pkeyboardFunctionKey)	\
    (This)->lpVtbl -> get_KeyboardFunctionKey(This,pkeyboardFunctionKey)

#define IMsRdpClientAdvancedSettings4_put_WinceFixedPalette(This,winceFixedPalette)	\
    (This)->lpVtbl -> put_WinceFixedPalette(This,winceFixedPalette)

#define IMsRdpClientAdvancedSettings4_get_WinceFixedPalette(This,pwinceFixedPalette)	\
    (This)->lpVtbl -> get_WinceFixedPalette(This,pwinceFixedPalette)

#define IMsRdpClientAdvancedSettings4_put_ConnectToServerConsole(This,connectToServerConsole)	\
    (This)->lpVtbl -> put_ConnectToServerConsole(This,connectToServerConsole)

#define IMsRdpClientAdvancedSettings4_get_ConnectToServerConsole(This,pConnectToConsole)	\
    (This)->lpVtbl -> get_ConnectToServerConsole(This,pConnectToConsole)

#define IMsRdpClientAdvancedSettings4_put_BitmapPersistence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPersistence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings4_get_BitmapPersistence(This,pbitmapPersistence)	\
    (This)->lpVtbl -> get_BitmapPersistence(This,pbitmapPersistence)

#define IMsRdpClientAdvancedSettings4_put_MinutesToIdleTimeout(This,minutesToIdleTimeout)	\
    (This)->lpVtbl -> put_MinutesToIdleTimeout(This,minutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings4_get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)	\
    (This)->lpVtbl -> get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings4_put_SmartSizing(This,fSmartSizing)	\
    (This)->lpVtbl -> put_SmartSizing(This,fSmartSizing)

#define IMsRdpClientAdvancedSettings4_get_SmartSizing(This,pfSmartSizing)	\
    (This)->lpVtbl -> get_SmartSizing(This,pfSmartSizing)

#define IMsRdpClientAdvancedSettings4_put_RdpdrLocalPrintingDocName(This,localPrintingDocName)	\
    (This)->lpVtbl -> put_RdpdrLocalPrintingDocName(This,localPrintingDocName)

#define IMsRdpClientAdvancedSettings4_get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)	\
    (This)->lpVtbl -> get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)

#define IMsRdpClientAdvancedSettings4_put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings4_get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings4_put_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> put_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings4_get_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> get_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings4_put_ClearTextPassword(This,clearTextPassword)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,clearTextPassword)

#define IMsRdpClientAdvancedSettings4_put_DisplayConnectionBar(This,fDisplayConnectionBar)	\
    (This)->lpVtbl -> put_DisplayConnectionBar(This,fDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings4_get_DisplayConnectionBar(This,pDisplayConnectionBar)	\
    (This)->lpVtbl -> get_DisplayConnectionBar(This,pDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings4_put_PinConnectionBar(This,fPinConnectionBar)	\
    (This)->lpVtbl -> put_PinConnectionBar(This,fPinConnectionBar)

#define IMsRdpClientAdvancedSettings4_get_PinConnectionBar(This,pPinConnectionBar)	\
    (This)->lpVtbl -> get_PinConnectionBar(This,pPinConnectionBar)

#define IMsRdpClientAdvancedSettings4_put_GrabFocusOnConnect(This,fGrabFocusOnConnect)	\
    (This)->lpVtbl -> put_GrabFocusOnConnect(This,fGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings4_get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)	\
    (This)->lpVtbl -> get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings4_put_LoadBalanceInfo(This,newLBInfo)	\
    (This)->lpVtbl -> put_LoadBalanceInfo(This,newLBInfo)

#define IMsRdpClientAdvancedSettings4_get_LoadBalanceInfo(This,pLBInfo)	\
    (This)->lpVtbl -> get_LoadBalanceInfo(This,pLBInfo)

#define IMsRdpClientAdvancedSettings4_put_RedirectDrives(This,redirectDrives)	\
    (This)->lpVtbl -> put_RedirectDrives(This,redirectDrives)

#define IMsRdpClientAdvancedSettings4_get_RedirectDrives(This,pRedirectDrives)	\
    (This)->lpVtbl -> get_RedirectDrives(This,pRedirectDrives)

#define IMsRdpClientAdvancedSettings4_put_RedirectPrinters(This,redirectPrinters)	\
    (This)->lpVtbl -> put_RedirectPrinters(This,redirectPrinters)

#define IMsRdpClientAdvancedSettings4_get_RedirectPrinters(This,pRedirectPrinters)	\
    (This)->lpVtbl -> get_RedirectPrinters(This,pRedirectPrinters)

#define IMsRdpClientAdvancedSettings4_put_RedirectPorts(This,redirectPorts)	\
    (This)->lpVtbl -> put_RedirectPorts(This,redirectPorts)

#define IMsRdpClientAdvancedSettings4_get_RedirectPorts(This,pRedirectPorts)	\
    (This)->lpVtbl -> get_RedirectPorts(This,pRedirectPorts)

#define IMsRdpClientAdvancedSettings4_put_RedirectSmartCards(This,redirectSmartCards)	\
    (This)->lpVtbl -> put_RedirectSmartCards(This,redirectSmartCards)

#define IMsRdpClientAdvancedSettings4_get_RedirectSmartCards(This,pRedirectSmartCards)	\
    (This)->lpVtbl -> get_RedirectSmartCards(This,pRedirectSmartCards)

#define IMsRdpClientAdvancedSettings4_put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings4_get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings4_put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings4_get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings4_put_PerformanceFlags(This,DisableList)	\
    (This)->lpVtbl -> put_PerformanceFlags(This,DisableList)

#define IMsRdpClientAdvancedSettings4_get_PerformanceFlags(This,pDisableList)	\
    (This)->lpVtbl -> get_PerformanceFlags(This,pDisableList)

#define IMsRdpClientAdvancedSettings4_put_ConnectWithEndpoint(This,ConnectEndpoint)	\
    (This)->lpVtbl -> put_ConnectWithEndpoint(This,ConnectEndpoint)

#define IMsRdpClientAdvancedSettings4_put_NotifyTSPublicKey(This,fNotify)	\
    (This)->lpVtbl -> put_NotifyTSPublicKey(This,fNotify)

#define IMsRdpClientAdvancedSettings4_get_NotifyTSPublicKey(This,pfNotify)	\
    (This)->lpVtbl -> get_NotifyTSPublicKey(This,pfNotify)


#define IMsRdpClientAdvancedSettings4_get_CanAutoReconnect(This,pfCanAutoReconnect)	\
    (This)->lpVtbl -> get_CanAutoReconnect(This,pfCanAutoReconnect)

#define IMsRdpClientAdvancedSettings4_put_EnableAutoReconnect(This,fEnableAutoReconnect)	\
    (This)->lpVtbl -> put_EnableAutoReconnect(This,fEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings4_get_EnableAutoReconnect(This,pfEnableAutoReconnect)	\
    (This)->lpVtbl -> get_EnableAutoReconnect(This,pfEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings4_put_MaxReconnectAttempts(This,MaxReconnectAttempts)	\
    (This)->lpVtbl -> put_MaxReconnectAttempts(This,MaxReconnectAttempts)

#define IMsRdpClientAdvancedSettings4_get_MaxReconnectAttempts(This,pMaxReconnectAttempts)	\
    (This)->lpVtbl -> get_MaxReconnectAttempts(This,pMaxReconnectAttempts)


#define IMsRdpClientAdvancedSettings4_put_ConnectionBarShowMinimizeButton(This,fShowMinimize)	\
    (This)->lpVtbl -> put_ConnectionBarShowMinimizeButton(This,fShowMinimize)

#define IMsRdpClientAdvancedSettings4_get_ConnectionBarShowMinimizeButton(This,pfShowMinimize)	\
    (This)->lpVtbl -> get_ConnectionBarShowMinimizeButton(This,pfShowMinimize)

#define IMsRdpClientAdvancedSettings4_put_ConnectionBarShowRestoreButton(This,fShowRestore)	\
    (This)->lpVtbl -> put_ConnectionBarShowRestoreButton(This,fShowRestore)

#define IMsRdpClientAdvancedSettings4_get_ConnectionBarShowRestoreButton(This,pfShowRestore)	\
    (This)->lpVtbl -> get_ConnectionBarShowRestoreButton(This,pfShowRestore)


#define IMsRdpClientAdvancedSettings4_put_AuthenticationLevel(This,uiAuthLevel)	\
    (This)->lpVtbl -> put_AuthenticationLevel(This,uiAuthLevel)

#define IMsRdpClientAdvancedSettings4_get_AuthenticationLevel(This,puiAuthLevel)	\
    (This)->lpVtbl -> get_AuthenticationLevel(This,puiAuthLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings4_put_AuthenticationLevel_Proxy( 
    IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
    /* [in] */ UINT uiAuthLevel);


void __RPC_STUB IMsRdpClientAdvancedSettings4_put_AuthenticationLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings4_get_AuthenticationLevel_Proxy( 
    IMsRdpClientAdvancedSettings4 __RPC_FAR * This,
    /* [retval][out] */ UINT __RPC_FAR *puiAuthLevel);


void __RPC_STUB IMsRdpClientAdvancedSettings4_get_AuthenticationLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientAdvancedSettings4_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClientAdvancedSettings5_INTERFACE_DEFINED__
#define __IMsRdpClientAdvancedSettings5_INTERFACE_DEFINED__

/* interface IMsRdpClientAdvancedSettings5 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClientAdvancedSettings5;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FBA7F64E-6783-4405-DA45-FA4A763DABD0")
    IMsRdpClientAdvancedSettings5 : public IMsRdpClientAdvancedSettings4
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PublicMode( 
            /* [in] */ VARIANT_BOOL fPublicMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PublicMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPublicMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectClipboard( 
            /* [in] */ VARIANT_BOOL fRedirectClipboard) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectClipboard( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectClipboard) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClearTextSmartCardPin( 
            /* [in] */ BSTR bstrClearTextPin) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PromptForSmartCardInsertion( 
            /* [in] */ VARIANT_BOOL fPromptForSmartCardInsertion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PromptForSmartCardInsertion( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPromptForSmartCardInsertion) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioRedirectionMode( 
            /* [in] */ UINT uiAudioRedirectionMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioRedirectionMode( 
            /* [retval][out] */ UINT __RPC_FAR *puiAudioRedirectionMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectMyDesktop( 
            /* [in] */ VARIANT_BOOL fRedirectMyDesktop) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectMyDesktop( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectMyDesktop) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RedirectMyDocuments( 
            /* [in] */ VARIANT_BOOL fRedirectMyDesktop) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RedirectMyDocuments( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectMyDocuments) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HideServerLocalDrives( 
            /* [in] */ VARIANT_BOOL fHideServerLocalDrives) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HideServerLocalDrives( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfHideServerLocalDrives) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HideServerNetworkDrives( 
            /* [in] */ VARIANT_BOOL fHideServerNetworkDrives) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HideServerNetworkDrives( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfHideServerNetworkDrives) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionBarShowPinButton( 
            /* [in] */ VARIANT_BOOL fShowPin) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionBarShowPinButton( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowPin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientAdvancedSettings5Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compress )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG compress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compress )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcompress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPeristence )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPeristence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG allowBackgroundInput);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_allowBackgroundInput )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pallowBackgroundInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyBoardLayoutStr )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR KeyBoardLayoutStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PluginDlls )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR PluginDlls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconFile )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR IconFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IconIndex )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG IconIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BOOL ContainerHandledFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerHandledFullScreen )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pContainerHandledFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BOOL DisableRdpdr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableRdpdr )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pDisableRdpdr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmoothScroll )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG smoothScroll);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmoothScroll )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psmoothScroll);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG acceleratorPassthrough);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AcceleratorPassthrough )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pacceleratorPassthrough);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG shadowBitmap);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShadowBitmap )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshadowBitmap);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransportType )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG transportType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportType )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *ptransportType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SasSequence )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG sasSequence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SasSequence )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psasSequence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG encryptionEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncryptionEnabled )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pencryptionEnabled);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG dedicatedTerminal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DedicatedTerminal )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdedicatedTerminal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RDPPort )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG rdpPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RDPPort )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *prdpPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableMouse )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG enableMouse);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableMouse )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableMouse);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG disableCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableCtrlAltDel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdisableCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG enableWindowsKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableWindowsKey )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *penableWindowsKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG doubleClickDetect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DoubleClickDetect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pdoubleClickDetect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaximizeShell )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG maximizeShell);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaximizeShell )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaximizeShell);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyFullScreen )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlEsc )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltEsc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltEsc )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltEsc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltTab )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltShiftTab);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltShiftTab )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltShiftTab);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyAltSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyAltSpace )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyAltSpace);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG hotKeyCtrlAltDel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKeyCtrlAltDel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *photKeyCtrlAltDel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG orderDrawThreshold);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_orderDrawThreshold )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *porderDrawThreshold);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bitmapCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapCacheSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCacheSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCacheSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapVirtualCacheSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bScale);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleBitmapCachesByBPP )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbScale);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG numBitmapCaches);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumBitmapCaches )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnumBitmapCaches);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG cachePersistenceActive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CachePersistenceActive )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcachePersistenceActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PersistCacheDirectory )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR PersistCacheDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG brushSupportLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushSupportLevel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbrushSupportLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG minInputSendInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_minInputSendInterval )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminInputSendInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG inputEventsAtOnce);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputEventsAtOnce )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pinputEventsAtOnce);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxEventCount )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG maxEventCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxEventCount )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pmaxEventCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG keepAliveInterval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_keepAliveInterval )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeepAliveInterval);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG shutdownTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_shutdownTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pshutdownTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG overallConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overallConnectionTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *poverallConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG singleConnectionTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_singleConnectionTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *psingleConnectionTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardType )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG keyboardType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardType )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG keyboardSubType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardSubType )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG keyboardFunctionKey);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyboardFunctionKey )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pkeyboardFunctionKey);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG winceFixedPalette);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinceFixedPalette )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pwinceFixedPalette);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL connectToServerConsole);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectToServerConsole )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pConnectToConsole);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bitmapPeristence);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapPersistence )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pbitmapPersistence);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG minutesToIdleTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinutesToIdleTimeout )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pminutesToIdleTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SmartSizing )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSmartSizing);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SmartSizing )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSmartSizing);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR localPrintingDocName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrLocalPrintingDocName )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLocalPrintingDocName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR clipCleanTempDirString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipCleanTempDirString )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipCleanTempDirString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR clipPasteInfoString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RdpdrClipPasteInfoString )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *clipPasteInfoString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextPassword )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR clearTextPassword);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fDisplayConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayConnectionBar )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDisplayConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPinConnectionBar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PinConnectionBar )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPinConnectionBar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fGrabFocusOnConnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GrabFocusOnConnect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfGrabFocusOnConnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR newLBInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadBalanceInfo )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pLBInfo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectDrives )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectDrives )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPrinters);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPrinters )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPrinters);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectPorts )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectPorts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectPorts )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectPorts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL redirectSmartCards);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectSmartCards )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pRedirectSmartCards);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache16BppSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache16BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG bitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitmapVirtualCache24BppSize )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitmapVirtualCache24BppSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG DisableList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PerformanceFlags )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pDisableList);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectWithEndpoint )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *ConnectEndpoint);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotifyTSPublicKey )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfNotify);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanAutoReconnect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCanAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fEnableAutoReconnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableAutoReconnect )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfEnableAutoReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ LONG MaxReconnectAttempts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxReconnectAttempts )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pMaxReconnectAttempts);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowMinimizeButton )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowMinimize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowMinimizeButton )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowMinimize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowRestoreButton )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowRestore);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowRestoreButton )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowRestore);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AuthenticationLevel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ UINT uiAuthLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AuthenticationLevel )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ UINT __RPC_FAR *puiAuthLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PublicMode )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPublicMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PublicMode )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPublicMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectClipboard )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fRedirectClipboard);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectClipboard )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectClipboard);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTextSmartCardPin )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ BSTR bstrClearTextPin);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PromptForSmartCardInsertion )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPromptForSmartCardInsertion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PromptForSmartCardInsertion )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPromptForSmartCardInsertion);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AudioRedirectionMode )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ UINT uiAudioRedirectionMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioRedirectionMode )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ UINT __RPC_FAR *puiAudioRedirectionMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectMyDesktop )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fRedirectMyDesktop);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectMyDesktop )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectMyDesktop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RedirectMyDocuments )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fRedirectMyDesktop);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RedirectMyDocuments )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectMyDocuments);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HideServerLocalDrives )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fHideServerLocalDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HideServerLocalDrives )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfHideServerLocalDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HideServerNetworkDrives )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fHideServerNetworkDrives);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HideServerNetworkDrives )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfHideServerNetworkDrives);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectionBarShowPinButton )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fShowPin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionBarShowPinButton )( 
            IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowPin);
        
        END_INTERFACE
    } IMsRdpClientAdvancedSettings5Vtbl;

    interface IMsRdpClientAdvancedSettings5
    {
        CONST_VTBL struct IMsRdpClientAdvancedSettings5Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClientAdvancedSettings5_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClientAdvancedSettings5_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClientAdvancedSettings5_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClientAdvancedSettings5_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClientAdvancedSettings5_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClientAdvancedSettings5_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClientAdvancedSettings5_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClientAdvancedSettings5_put_Compress(This,compress)	\
    (This)->lpVtbl -> put_Compress(This,compress)

#define IMsRdpClientAdvancedSettings5_get_Compress(This,pcompress)	\
    (This)->lpVtbl -> get_Compress(This,pcompress)

#define IMsRdpClientAdvancedSettings5_put_BitmapPeristence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPeristence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings5_get_BitmapPeristence(This,pbitmapPeristence)	\
    (This)->lpVtbl -> get_BitmapPeristence(This,pbitmapPeristence)

#define IMsRdpClientAdvancedSettings5_put_allowBackgroundInput(This,allowBackgroundInput)	\
    (This)->lpVtbl -> put_allowBackgroundInput(This,allowBackgroundInput)

#define IMsRdpClientAdvancedSettings5_get_allowBackgroundInput(This,pallowBackgroundInput)	\
    (This)->lpVtbl -> get_allowBackgroundInput(This,pallowBackgroundInput)

#define IMsRdpClientAdvancedSettings5_put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)	\
    (This)->lpVtbl -> put_KeyBoardLayoutStr(This,KeyBoardLayoutStr)

#define IMsRdpClientAdvancedSettings5_put_PluginDlls(This,PluginDlls)	\
    (This)->lpVtbl -> put_PluginDlls(This,PluginDlls)

#define IMsRdpClientAdvancedSettings5_put_IconFile(This,IconFile)	\
    (This)->lpVtbl -> put_IconFile(This,IconFile)

#define IMsRdpClientAdvancedSettings5_put_IconIndex(This,IconIndex)	\
    (This)->lpVtbl -> put_IconIndex(This,IconIndex)

#define IMsRdpClientAdvancedSettings5_put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)	\
    (This)->lpVtbl -> put_ContainerHandledFullScreen(This,ContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings5_get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)	\
    (This)->lpVtbl -> get_ContainerHandledFullScreen(This,pContainerHandledFullScreen)

#define IMsRdpClientAdvancedSettings5_put_DisableRdpdr(This,DisableRdpdr)	\
    (This)->lpVtbl -> put_DisableRdpdr(This,DisableRdpdr)

#define IMsRdpClientAdvancedSettings5_get_DisableRdpdr(This,pDisableRdpdr)	\
    (This)->lpVtbl -> get_DisableRdpdr(This,pDisableRdpdr)


#define IMsRdpClientAdvancedSettings5_put_SmoothScroll(This,smoothScroll)	\
    (This)->lpVtbl -> put_SmoothScroll(This,smoothScroll)

#define IMsRdpClientAdvancedSettings5_get_SmoothScroll(This,psmoothScroll)	\
    (This)->lpVtbl -> get_SmoothScroll(This,psmoothScroll)

#define IMsRdpClientAdvancedSettings5_put_AcceleratorPassthrough(This,acceleratorPassthrough)	\
    (This)->lpVtbl -> put_AcceleratorPassthrough(This,acceleratorPassthrough)

#define IMsRdpClientAdvancedSettings5_get_AcceleratorPassthrough(This,pacceleratorPassthrough)	\
    (This)->lpVtbl -> get_AcceleratorPassthrough(This,pacceleratorPassthrough)

#define IMsRdpClientAdvancedSettings5_put_ShadowBitmap(This,shadowBitmap)	\
    (This)->lpVtbl -> put_ShadowBitmap(This,shadowBitmap)

#define IMsRdpClientAdvancedSettings5_get_ShadowBitmap(This,pshadowBitmap)	\
    (This)->lpVtbl -> get_ShadowBitmap(This,pshadowBitmap)

#define IMsRdpClientAdvancedSettings5_put_TransportType(This,transportType)	\
    (This)->lpVtbl -> put_TransportType(This,transportType)

#define IMsRdpClientAdvancedSettings5_get_TransportType(This,ptransportType)	\
    (This)->lpVtbl -> get_TransportType(This,ptransportType)

#define IMsRdpClientAdvancedSettings5_put_SasSequence(This,sasSequence)	\
    (This)->lpVtbl -> put_SasSequence(This,sasSequence)

#define IMsRdpClientAdvancedSettings5_get_SasSequence(This,psasSequence)	\
    (This)->lpVtbl -> get_SasSequence(This,psasSequence)

#define IMsRdpClientAdvancedSettings5_put_EncryptionEnabled(This,encryptionEnabled)	\
    (This)->lpVtbl -> put_EncryptionEnabled(This,encryptionEnabled)

#define IMsRdpClientAdvancedSettings5_get_EncryptionEnabled(This,pencryptionEnabled)	\
    (This)->lpVtbl -> get_EncryptionEnabled(This,pencryptionEnabled)

#define IMsRdpClientAdvancedSettings5_put_DedicatedTerminal(This,dedicatedTerminal)	\
    (This)->lpVtbl -> put_DedicatedTerminal(This,dedicatedTerminal)

#define IMsRdpClientAdvancedSettings5_get_DedicatedTerminal(This,pdedicatedTerminal)	\
    (This)->lpVtbl -> get_DedicatedTerminal(This,pdedicatedTerminal)

#define IMsRdpClientAdvancedSettings5_put_RDPPort(This,rdpPort)	\
    (This)->lpVtbl -> put_RDPPort(This,rdpPort)

#define IMsRdpClientAdvancedSettings5_get_RDPPort(This,prdpPort)	\
    (This)->lpVtbl -> get_RDPPort(This,prdpPort)

#define IMsRdpClientAdvancedSettings5_put_EnableMouse(This,enableMouse)	\
    (This)->lpVtbl -> put_EnableMouse(This,enableMouse)

#define IMsRdpClientAdvancedSettings5_get_EnableMouse(This,penableMouse)	\
    (This)->lpVtbl -> get_EnableMouse(This,penableMouse)

#define IMsRdpClientAdvancedSettings5_put_DisableCtrlAltDel(This,disableCtrlAltDel)	\
    (This)->lpVtbl -> put_DisableCtrlAltDel(This,disableCtrlAltDel)

#define IMsRdpClientAdvancedSettings5_get_DisableCtrlAltDel(This,pdisableCtrlAltDel)	\
    (This)->lpVtbl -> get_DisableCtrlAltDel(This,pdisableCtrlAltDel)

#define IMsRdpClientAdvancedSettings5_put_EnableWindowsKey(This,enableWindowsKey)	\
    (This)->lpVtbl -> put_EnableWindowsKey(This,enableWindowsKey)

#define IMsRdpClientAdvancedSettings5_get_EnableWindowsKey(This,penableWindowsKey)	\
    (This)->lpVtbl -> get_EnableWindowsKey(This,penableWindowsKey)

#define IMsRdpClientAdvancedSettings5_put_DoubleClickDetect(This,doubleClickDetect)	\
    (This)->lpVtbl -> put_DoubleClickDetect(This,doubleClickDetect)

#define IMsRdpClientAdvancedSettings5_get_DoubleClickDetect(This,pdoubleClickDetect)	\
    (This)->lpVtbl -> get_DoubleClickDetect(This,pdoubleClickDetect)

#define IMsRdpClientAdvancedSettings5_put_MaximizeShell(This,maximizeShell)	\
    (This)->lpVtbl -> put_MaximizeShell(This,maximizeShell)

#define IMsRdpClientAdvancedSettings5_get_MaximizeShell(This,pmaximizeShell)	\
    (This)->lpVtbl -> get_MaximizeShell(This,pmaximizeShell)

#define IMsRdpClientAdvancedSettings5_put_HotKeyFullScreen(This,hotKeyFullScreen)	\
    (This)->lpVtbl -> put_HotKeyFullScreen(This,hotKeyFullScreen)

#define IMsRdpClientAdvancedSettings5_get_HotKeyFullScreen(This,photKeyFullScreen)	\
    (This)->lpVtbl -> get_HotKeyFullScreen(This,photKeyFullScreen)

#define IMsRdpClientAdvancedSettings5_put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)	\
    (This)->lpVtbl -> put_HotKeyCtrlEsc(This,hotKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings5_get_HotKeyCtrlEsc(This,photKeyCtrlEsc)	\
    (This)->lpVtbl -> get_HotKeyCtrlEsc(This,photKeyCtrlEsc)

#define IMsRdpClientAdvancedSettings5_put_HotKeyAltEsc(This,hotKeyAltEsc)	\
    (This)->lpVtbl -> put_HotKeyAltEsc(This,hotKeyAltEsc)

#define IMsRdpClientAdvancedSettings5_get_HotKeyAltEsc(This,photKeyAltEsc)	\
    (This)->lpVtbl -> get_HotKeyAltEsc(This,photKeyAltEsc)

#define IMsRdpClientAdvancedSettings5_put_HotKeyAltTab(This,hotKeyAltTab)	\
    (This)->lpVtbl -> put_HotKeyAltTab(This,hotKeyAltTab)

#define IMsRdpClientAdvancedSettings5_get_HotKeyAltTab(This,photKeyAltTab)	\
    (This)->lpVtbl -> get_HotKeyAltTab(This,photKeyAltTab)

#define IMsRdpClientAdvancedSettings5_put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)	\
    (This)->lpVtbl -> put_HotKeyAltShiftTab(This,hotKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings5_get_HotKeyAltShiftTab(This,photKeyAltShiftTab)	\
    (This)->lpVtbl -> get_HotKeyAltShiftTab(This,photKeyAltShiftTab)

#define IMsRdpClientAdvancedSettings5_put_HotKeyAltSpace(This,hotKeyAltSpace)	\
    (This)->lpVtbl -> put_HotKeyAltSpace(This,hotKeyAltSpace)

#define IMsRdpClientAdvancedSettings5_get_HotKeyAltSpace(This,photKeyAltSpace)	\
    (This)->lpVtbl -> get_HotKeyAltSpace(This,photKeyAltSpace)

#define IMsRdpClientAdvancedSettings5_put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)	\
    (This)->lpVtbl -> put_HotKeyCtrlAltDel(This,hotKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings5_get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)	\
    (This)->lpVtbl -> get_HotKeyCtrlAltDel(This,photKeyCtrlAltDel)

#define IMsRdpClientAdvancedSettings5_put_orderDrawThreshold(This,orderDrawThreshold)	\
    (This)->lpVtbl -> put_orderDrawThreshold(This,orderDrawThreshold)

#define IMsRdpClientAdvancedSettings5_get_orderDrawThreshold(This,porderDrawThreshold)	\
    (This)->lpVtbl -> get_orderDrawThreshold(This,porderDrawThreshold)

#define IMsRdpClientAdvancedSettings5_put_BitmapCacheSize(This,bitmapCacheSize)	\
    (This)->lpVtbl -> put_BitmapCacheSize(This,bitmapCacheSize)

#define IMsRdpClientAdvancedSettings5_get_BitmapCacheSize(This,pbitmapCacheSize)	\
    (This)->lpVtbl -> get_BitmapCacheSize(This,pbitmapCacheSize)

#define IMsRdpClientAdvancedSettings5_put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCacheSize(This,bitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings5_get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCacheSize(This,pbitmapVirtualCacheSize)

#define IMsRdpClientAdvancedSettings5_put_ScaleBitmapCachesByBPP(This,bScale)	\
    (This)->lpVtbl -> put_ScaleBitmapCachesByBPP(This,bScale)

#define IMsRdpClientAdvancedSettings5_get_ScaleBitmapCachesByBPP(This,pbScale)	\
    (This)->lpVtbl -> get_ScaleBitmapCachesByBPP(This,pbScale)

#define IMsRdpClientAdvancedSettings5_put_NumBitmapCaches(This,numBitmapCaches)	\
    (This)->lpVtbl -> put_NumBitmapCaches(This,numBitmapCaches)

#define IMsRdpClientAdvancedSettings5_get_NumBitmapCaches(This,pnumBitmapCaches)	\
    (This)->lpVtbl -> get_NumBitmapCaches(This,pnumBitmapCaches)

#define IMsRdpClientAdvancedSettings5_put_CachePersistenceActive(This,cachePersistenceActive)	\
    (This)->lpVtbl -> put_CachePersistenceActive(This,cachePersistenceActive)

#define IMsRdpClientAdvancedSettings5_get_CachePersistenceActive(This,pcachePersistenceActive)	\
    (This)->lpVtbl -> get_CachePersistenceActive(This,pcachePersistenceActive)

#define IMsRdpClientAdvancedSettings5_put_PersistCacheDirectory(This,PersistCacheDirectory)	\
    (This)->lpVtbl -> put_PersistCacheDirectory(This,PersistCacheDirectory)

#define IMsRdpClientAdvancedSettings5_put_brushSupportLevel(This,brushSupportLevel)	\
    (This)->lpVtbl -> put_brushSupportLevel(This,brushSupportLevel)

#define IMsRdpClientAdvancedSettings5_get_brushSupportLevel(This,pbrushSupportLevel)	\
    (This)->lpVtbl -> get_brushSupportLevel(This,pbrushSupportLevel)

#define IMsRdpClientAdvancedSettings5_put_minInputSendInterval(This,minInputSendInterval)	\
    (This)->lpVtbl -> put_minInputSendInterval(This,minInputSendInterval)

#define IMsRdpClientAdvancedSettings5_get_minInputSendInterval(This,pminInputSendInterval)	\
    (This)->lpVtbl -> get_minInputSendInterval(This,pminInputSendInterval)

#define IMsRdpClientAdvancedSettings5_put_InputEventsAtOnce(This,inputEventsAtOnce)	\
    (This)->lpVtbl -> put_InputEventsAtOnce(This,inputEventsAtOnce)

#define IMsRdpClientAdvancedSettings5_get_InputEventsAtOnce(This,pinputEventsAtOnce)	\
    (This)->lpVtbl -> get_InputEventsAtOnce(This,pinputEventsAtOnce)

#define IMsRdpClientAdvancedSettings5_put_maxEventCount(This,maxEventCount)	\
    (This)->lpVtbl -> put_maxEventCount(This,maxEventCount)

#define IMsRdpClientAdvancedSettings5_get_maxEventCount(This,pmaxEventCount)	\
    (This)->lpVtbl -> get_maxEventCount(This,pmaxEventCount)

#define IMsRdpClientAdvancedSettings5_put_keepAliveInterval(This,keepAliveInterval)	\
    (This)->lpVtbl -> put_keepAliveInterval(This,keepAliveInterval)

#define IMsRdpClientAdvancedSettings5_get_keepAliveInterval(This,pkeepAliveInterval)	\
    (This)->lpVtbl -> get_keepAliveInterval(This,pkeepAliveInterval)

#define IMsRdpClientAdvancedSettings5_put_shutdownTimeout(This,shutdownTimeout)	\
    (This)->lpVtbl -> put_shutdownTimeout(This,shutdownTimeout)

#define IMsRdpClientAdvancedSettings5_get_shutdownTimeout(This,pshutdownTimeout)	\
    (This)->lpVtbl -> get_shutdownTimeout(This,pshutdownTimeout)

#define IMsRdpClientAdvancedSettings5_put_overallConnectionTimeout(This,overallConnectionTimeout)	\
    (This)->lpVtbl -> put_overallConnectionTimeout(This,overallConnectionTimeout)

#define IMsRdpClientAdvancedSettings5_get_overallConnectionTimeout(This,poverallConnectionTimeout)	\
    (This)->lpVtbl -> get_overallConnectionTimeout(This,poverallConnectionTimeout)

#define IMsRdpClientAdvancedSettings5_put_singleConnectionTimeout(This,singleConnectionTimeout)	\
    (This)->lpVtbl -> put_singleConnectionTimeout(This,singleConnectionTimeout)

#define IMsRdpClientAdvancedSettings5_get_singleConnectionTimeout(This,psingleConnectionTimeout)	\
    (This)->lpVtbl -> get_singleConnectionTimeout(This,psingleConnectionTimeout)

#define IMsRdpClientAdvancedSettings5_put_KeyboardType(This,keyboardType)	\
    (This)->lpVtbl -> put_KeyboardType(This,keyboardType)

#define IMsRdpClientAdvancedSettings5_get_KeyboardType(This,pkeyboardType)	\
    (This)->lpVtbl -> get_KeyboardType(This,pkeyboardType)

#define IMsRdpClientAdvancedSettings5_put_KeyboardSubType(This,keyboardSubType)	\
    (This)->lpVtbl -> put_KeyboardSubType(This,keyboardSubType)

#define IMsRdpClientAdvancedSettings5_get_KeyboardSubType(This,pkeyboardSubType)	\
    (This)->lpVtbl -> get_KeyboardSubType(This,pkeyboardSubType)

#define IMsRdpClientAdvancedSettings5_put_KeyboardFunctionKey(This,keyboardFunctionKey)	\
    (This)->lpVtbl -> put_KeyboardFunctionKey(This,keyboardFunctionKey)

#define IMsRdpClientAdvancedSettings5_get_KeyboardFunctionKey(This,pkeyboardFunctionKey)	\
    (This)->lpVtbl -> get_KeyboardFunctionKey(This,pkeyboardFunctionKey)

#define IMsRdpClientAdvancedSettings5_put_WinceFixedPalette(This,winceFixedPalette)	\
    (This)->lpVtbl -> put_WinceFixedPalette(This,winceFixedPalette)

#define IMsRdpClientAdvancedSettings5_get_WinceFixedPalette(This,pwinceFixedPalette)	\
    (This)->lpVtbl -> get_WinceFixedPalette(This,pwinceFixedPalette)

#define IMsRdpClientAdvancedSettings5_put_ConnectToServerConsole(This,connectToServerConsole)	\
    (This)->lpVtbl -> put_ConnectToServerConsole(This,connectToServerConsole)

#define IMsRdpClientAdvancedSettings5_get_ConnectToServerConsole(This,pConnectToConsole)	\
    (This)->lpVtbl -> get_ConnectToServerConsole(This,pConnectToConsole)

#define IMsRdpClientAdvancedSettings5_put_BitmapPersistence(This,bitmapPeristence)	\
    (This)->lpVtbl -> put_BitmapPersistence(This,bitmapPeristence)

#define IMsRdpClientAdvancedSettings5_get_BitmapPersistence(This,pbitmapPersistence)	\
    (This)->lpVtbl -> get_BitmapPersistence(This,pbitmapPersistence)

#define IMsRdpClientAdvancedSettings5_put_MinutesToIdleTimeout(This,minutesToIdleTimeout)	\
    (This)->lpVtbl -> put_MinutesToIdleTimeout(This,minutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings5_get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)	\
    (This)->lpVtbl -> get_MinutesToIdleTimeout(This,pminutesToIdleTimeout)

#define IMsRdpClientAdvancedSettings5_put_SmartSizing(This,fSmartSizing)	\
    (This)->lpVtbl -> put_SmartSizing(This,fSmartSizing)

#define IMsRdpClientAdvancedSettings5_get_SmartSizing(This,pfSmartSizing)	\
    (This)->lpVtbl -> get_SmartSizing(This,pfSmartSizing)

#define IMsRdpClientAdvancedSettings5_put_RdpdrLocalPrintingDocName(This,localPrintingDocName)	\
    (This)->lpVtbl -> put_RdpdrLocalPrintingDocName(This,localPrintingDocName)

#define IMsRdpClientAdvancedSettings5_get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)	\
    (This)->lpVtbl -> get_RdpdrLocalPrintingDocName(This,pLocalPrintingDocName)

#define IMsRdpClientAdvancedSettings5_put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> put_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings5_get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)	\
    (This)->lpVtbl -> get_RdpdrClipCleanTempDirString(This,clipCleanTempDirString)

#define IMsRdpClientAdvancedSettings5_put_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> put_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings5_get_RdpdrClipPasteInfoString(This,clipPasteInfoString)	\
    (This)->lpVtbl -> get_RdpdrClipPasteInfoString(This,clipPasteInfoString)

#define IMsRdpClientAdvancedSettings5_put_ClearTextPassword(This,clearTextPassword)	\
    (This)->lpVtbl -> put_ClearTextPassword(This,clearTextPassword)

#define IMsRdpClientAdvancedSettings5_put_DisplayConnectionBar(This,fDisplayConnectionBar)	\
    (This)->lpVtbl -> put_DisplayConnectionBar(This,fDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings5_get_DisplayConnectionBar(This,pDisplayConnectionBar)	\
    (This)->lpVtbl -> get_DisplayConnectionBar(This,pDisplayConnectionBar)

#define IMsRdpClientAdvancedSettings5_put_PinConnectionBar(This,fPinConnectionBar)	\
    (This)->lpVtbl -> put_PinConnectionBar(This,fPinConnectionBar)

#define IMsRdpClientAdvancedSettings5_get_PinConnectionBar(This,pPinConnectionBar)	\
    (This)->lpVtbl -> get_PinConnectionBar(This,pPinConnectionBar)

#define IMsRdpClientAdvancedSettings5_put_GrabFocusOnConnect(This,fGrabFocusOnConnect)	\
    (This)->lpVtbl -> put_GrabFocusOnConnect(This,fGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings5_get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)	\
    (This)->lpVtbl -> get_GrabFocusOnConnect(This,pfGrabFocusOnConnect)

#define IMsRdpClientAdvancedSettings5_put_LoadBalanceInfo(This,newLBInfo)	\
    (This)->lpVtbl -> put_LoadBalanceInfo(This,newLBInfo)

#define IMsRdpClientAdvancedSettings5_get_LoadBalanceInfo(This,pLBInfo)	\
    (This)->lpVtbl -> get_LoadBalanceInfo(This,pLBInfo)

#define IMsRdpClientAdvancedSettings5_put_RedirectDrives(This,redirectDrives)	\
    (This)->lpVtbl -> put_RedirectDrives(This,redirectDrives)

#define IMsRdpClientAdvancedSettings5_get_RedirectDrives(This,pRedirectDrives)	\
    (This)->lpVtbl -> get_RedirectDrives(This,pRedirectDrives)

#define IMsRdpClientAdvancedSettings5_put_RedirectPrinters(This,redirectPrinters)	\
    (This)->lpVtbl -> put_RedirectPrinters(This,redirectPrinters)

#define IMsRdpClientAdvancedSettings5_get_RedirectPrinters(This,pRedirectPrinters)	\
    (This)->lpVtbl -> get_RedirectPrinters(This,pRedirectPrinters)

#define IMsRdpClientAdvancedSettings5_put_RedirectPorts(This,redirectPorts)	\
    (This)->lpVtbl -> put_RedirectPorts(This,redirectPorts)

#define IMsRdpClientAdvancedSettings5_get_RedirectPorts(This,pRedirectPorts)	\
    (This)->lpVtbl -> get_RedirectPorts(This,pRedirectPorts)

#define IMsRdpClientAdvancedSettings5_put_RedirectSmartCards(This,redirectSmartCards)	\
    (This)->lpVtbl -> put_RedirectSmartCards(This,redirectSmartCards)

#define IMsRdpClientAdvancedSettings5_get_RedirectSmartCards(This,pRedirectSmartCards)	\
    (This)->lpVtbl -> get_RedirectSmartCards(This,pRedirectSmartCards)

#define IMsRdpClientAdvancedSettings5_put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache16BppSize(This,bitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings5_get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache16BppSize(This,pBitmapVirtualCache16BppSize)

#define IMsRdpClientAdvancedSettings5_put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> put_BitmapVirtualCache24BppSize(This,bitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings5_get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)	\
    (This)->lpVtbl -> get_BitmapVirtualCache24BppSize(This,pBitmapVirtualCache24BppSize)

#define IMsRdpClientAdvancedSettings5_put_PerformanceFlags(This,DisableList)	\
    (This)->lpVtbl -> put_PerformanceFlags(This,DisableList)

#define IMsRdpClientAdvancedSettings5_get_PerformanceFlags(This,pDisableList)	\
    (This)->lpVtbl -> get_PerformanceFlags(This,pDisableList)

#define IMsRdpClientAdvancedSettings5_put_ConnectWithEndpoint(This,ConnectEndpoint)	\
    (This)->lpVtbl -> put_ConnectWithEndpoint(This,ConnectEndpoint)

#define IMsRdpClientAdvancedSettings5_put_NotifyTSPublicKey(This,fNotify)	\
    (This)->lpVtbl -> put_NotifyTSPublicKey(This,fNotify)

#define IMsRdpClientAdvancedSettings5_get_NotifyTSPublicKey(This,pfNotify)	\
    (This)->lpVtbl -> get_NotifyTSPublicKey(This,pfNotify)


#define IMsRdpClientAdvancedSettings5_get_CanAutoReconnect(This,pfCanAutoReconnect)	\
    (This)->lpVtbl -> get_CanAutoReconnect(This,pfCanAutoReconnect)

#define IMsRdpClientAdvancedSettings5_put_EnableAutoReconnect(This,fEnableAutoReconnect)	\
    (This)->lpVtbl -> put_EnableAutoReconnect(This,fEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings5_get_EnableAutoReconnect(This,pfEnableAutoReconnect)	\
    (This)->lpVtbl -> get_EnableAutoReconnect(This,pfEnableAutoReconnect)

#define IMsRdpClientAdvancedSettings5_put_MaxReconnectAttempts(This,MaxReconnectAttempts)	\
    (This)->lpVtbl -> put_MaxReconnectAttempts(This,MaxReconnectAttempts)

#define IMsRdpClientAdvancedSettings5_get_MaxReconnectAttempts(This,pMaxReconnectAttempts)	\
    (This)->lpVtbl -> get_MaxReconnectAttempts(This,pMaxReconnectAttempts)


#define IMsRdpClientAdvancedSettings5_put_ConnectionBarShowMinimizeButton(This,fShowMinimize)	\
    (This)->lpVtbl -> put_ConnectionBarShowMinimizeButton(This,fShowMinimize)

#define IMsRdpClientAdvancedSettings5_get_ConnectionBarShowMinimizeButton(This,pfShowMinimize)	\
    (This)->lpVtbl -> get_ConnectionBarShowMinimizeButton(This,pfShowMinimize)

#define IMsRdpClientAdvancedSettings5_put_ConnectionBarShowRestoreButton(This,fShowRestore)	\
    (This)->lpVtbl -> put_ConnectionBarShowRestoreButton(This,fShowRestore)

#define IMsRdpClientAdvancedSettings5_get_ConnectionBarShowRestoreButton(This,pfShowRestore)	\
    (This)->lpVtbl -> get_ConnectionBarShowRestoreButton(This,pfShowRestore)


#define IMsRdpClientAdvancedSettings5_put_AuthenticationLevel(This,uiAuthLevel)	\
    (This)->lpVtbl -> put_AuthenticationLevel(This,uiAuthLevel)

#define IMsRdpClientAdvancedSettings5_get_AuthenticationLevel(This,puiAuthLevel)	\
    (This)->lpVtbl -> get_AuthenticationLevel(This,puiAuthLevel)


#define IMsRdpClientAdvancedSettings5_put_PublicMode(This,fPublicMode)	\
    (This)->lpVtbl -> put_PublicMode(This,fPublicMode)

#define IMsRdpClientAdvancedSettings5_get_PublicMode(This,pfPublicMode)	\
    (This)->lpVtbl -> get_PublicMode(This,pfPublicMode)

#define IMsRdpClientAdvancedSettings5_put_RedirectClipboard(This,fRedirectClipboard)	\
    (This)->lpVtbl -> put_RedirectClipboard(This,fRedirectClipboard)

#define IMsRdpClientAdvancedSettings5_get_RedirectClipboard(This,pfRedirectClipboard)	\
    (This)->lpVtbl -> get_RedirectClipboard(This,pfRedirectClipboard)

#define IMsRdpClientAdvancedSettings5_put_ClearTextSmartCardPin(This,bstrClearTextPin)	\
    (This)->lpVtbl -> put_ClearTextSmartCardPin(This,bstrClearTextPin)

#define IMsRdpClientAdvancedSettings5_put_PromptForSmartCardInsertion(This,fPromptForSmartCardInsertion)	\
    (This)->lpVtbl -> put_PromptForSmartCardInsertion(This,fPromptForSmartCardInsertion)

#define IMsRdpClientAdvancedSettings5_get_PromptForSmartCardInsertion(This,pfPromptForSmartCardInsertion)	\
    (This)->lpVtbl -> get_PromptForSmartCardInsertion(This,pfPromptForSmartCardInsertion)

#define IMsRdpClientAdvancedSettings5_put_AudioRedirectionMode(This,uiAudioRedirectionMode)	\
    (This)->lpVtbl -> put_AudioRedirectionMode(This,uiAudioRedirectionMode)

#define IMsRdpClientAdvancedSettings5_get_AudioRedirectionMode(This,puiAudioRedirectionMode)	\
    (This)->lpVtbl -> get_AudioRedirectionMode(This,puiAudioRedirectionMode)

#define IMsRdpClientAdvancedSettings5_put_RedirectMyDesktop(This,fRedirectMyDesktop)	\
    (This)->lpVtbl -> put_RedirectMyDesktop(This,fRedirectMyDesktop)

#define IMsRdpClientAdvancedSettings5_get_RedirectMyDesktop(This,pfRedirectMyDesktop)	\
    (This)->lpVtbl -> get_RedirectMyDesktop(This,pfRedirectMyDesktop)

#define IMsRdpClientAdvancedSettings5_put_RedirectMyDocuments(This,fRedirectMyDesktop)	\
    (This)->lpVtbl -> put_RedirectMyDocuments(This,fRedirectMyDesktop)

#define IMsRdpClientAdvancedSettings5_get_RedirectMyDocuments(This,pfRedirectMyDocuments)	\
    (This)->lpVtbl -> get_RedirectMyDocuments(This,pfRedirectMyDocuments)

#define IMsRdpClientAdvancedSettings5_put_HideServerLocalDrives(This,fHideServerLocalDrives)	\
    (This)->lpVtbl -> put_HideServerLocalDrives(This,fHideServerLocalDrives)

#define IMsRdpClientAdvancedSettings5_get_HideServerLocalDrives(This,pfHideServerLocalDrives)	\
    (This)->lpVtbl -> get_HideServerLocalDrives(This,pfHideServerLocalDrives)

#define IMsRdpClientAdvancedSettings5_put_HideServerNetworkDrives(This,fHideServerNetworkDrives)	\
    (This)->lpVtbl -> put_HideServerNetworkDrives(This,fHideServerNetworkDrives)

#define IMsRdpClientAdvancedSettings5_get_HideServerNetworkDrives(This,pfHideServerNetworkDrives)	\
    (This)->lpVtbl -> get_HideServerNetworkDrives(This,pfHideServerNetworkDrives)

#define IMsRdpClientAdvancedSettings5_put_ConnectionBarShowPinButton(This,fShowPin)	\
    (This)->lpVtbl -> put_ConnectionBarShowPinButton(This,fShowPin)

#define IMsRdpClientAdvancedSettings5_get_ConnectionBarShowPinButton(This,pfShowPin)	\
    (This)->lpVtbl -> get_ConnectionBarShowPinButton(This,pfShowPin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_PublicMode_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fPublicMode);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_PublicMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_PublicMode_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPublicMode);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_PublicMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_RedirectClipboard_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fRedirectClipboard);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_RedirectClipboard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_RedirectClipboard_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectClipboard);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_RedirectClipboard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_ClearTextSmartCardPin_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ BSTR bstrClearTextPin);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_ClearTextSmartCardPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_PromptForSmartCardInsertion_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fPromptForSmartCardInsertion);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_PromptForSmartCardInsertion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_PromptForSmartCardInsertion_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfPromptForSmartCardInsertion);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_PromptForSmartCardInsertion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_AudioRedirectionMode_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ UINT uiAudioRedirectionMode);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_AudioRedirectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_AudioRedirectionMode_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ UINT __RPC_FAR *puiAudioRedirectionMode);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_AudioRedirectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_RedirectMyDesktop_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fRedirectMyDesktop);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_RedirectMyDesktop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_RedirectMyDesktop_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectMyDesktop);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_RedirectMyDesktop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_RedirectMyDocuments_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fRedirectMyDesktop);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_RedirectMyDocuments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_RedirectMyDocuments_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRedirectMyDocuments);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_RedirectMyDocuments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_HideServerLocalDrives_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fHideServerLocalDrives);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_HideServerLocalDrives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_HideServerLocalDrives_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfHideServerLocalDrives);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_HideServerLocalDrives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_HideServerNetworkDrives_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fHideServerNetworkDrives);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_HideServerNetworkDrives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_HideServerNetworkDrives_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfHideServerNetworkDrives);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_HideServerNetworkDrives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_put_ConnectionBarShowPinButton_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fShowPin);


void __RPC_STUB IMsRdpClientAdvancedSettings5_put_ConnectionBarShowPinButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClientAdvancedSettings5_get_ConnectionBarShowPinButton_Proxy( 
    IMsRdpClientAdvancedSettings5 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShowPin);


void __RPC_STUB IMsRdpClientAdvancedSettings5_get_ConnectionBarShowPinButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClientAdvancedSettings5_INTERFACE_DEFINED__ */


#ifndef __IMsTscAx_INTERFACE_DEFINED__
#define __IMsTscAx_INTERFACE_DEFINED__

/* interface IMsTscAx */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsTscAx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8C11EFAE-92C3-11D1-BC1E-00C04FA31489")
    IMsTscAx : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Server( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Server( 
            /* [retval][out] */ BSTR __RPC_FAR *pServer) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Domain( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Domain( 
            /* [retval][out] */ BSTR __RPC_FAR *pDomain) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pUserName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisconnectedText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisconnectedText( 
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectingText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectingText( 
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connected( 
            /* [retval][out] */ short __RPC_FAR *pIsConnected) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DesktopWidth( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DesktopWidth( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DesktopHeight( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DesktopHeight( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartConnected( 
            /* [in] */ BOOL fStartConnected) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartConnected( 
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalScrollBarVisible( 
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VerticalScrollBarVisible( 
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FullScreenTitle( 
            /* [in] */ BSTR fullScreenTitle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CipherStrength( 
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecuredSettingsEnabled( 
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecuredSettings( 
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvancedSettings( 
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Debugger( 
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateVirtualChannels( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendOnVirtualChannel( 
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsTscAxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsTscAx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsTscAx __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsTscAx __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pServer);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Domain )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Domain )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectedText )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectedText )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectingText )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectingText )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pIsConnected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopWidth )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopWidth )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopHeight )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopHeight )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartConnected )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BOOL fStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartConnected )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalScrollBarVisible )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalScrollBarVisible )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenTitle )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR fullScreenTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CipherStrength )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettingsEnabled )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debugger )( 
            IMsTscAx __RPC_FAR * This,
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IMsTscAx __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IMsTscAx __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVirtualChannels )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOnVirtualChannel )( 
            IMsTscAx __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData);
        
        END_INTERFACE
    } IMsTscAxVtbl;

    interface IMsTscAx
    {
        CONST_VTBL struct IMsTscAxVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsTscAx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsTscAx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsTscAx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsTscAx_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsTscAx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsTscAx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsTscAx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsTscAx_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IMsTscAx_get_Server(This,pServer)	\
    (This)->lpVtbl -> get_Server(This,pServer)

#define IMsTscAx_put_Domain(This,newVal)	\
    (This)->lpVtbl -> put_Domain(This,newVal)

#define IMsTscAx_get_Domain(This,pDomain)	\
    (This)->lpVtbl -> get_Domain(This,pDomain)

#define IMsTscAx_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IMsTscAx_get_UserName(This,pUserName)	\
    (This)->lpVtbl -> get_UserName(This,pUserName)

#define IMsTscAx_put_DisconnectedText(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectedText(This,newVal)

#define IMsTscAx_get_DisconnectedText(This,pDisconnectedText)	\
    (This)->lpVtbl -> get_DisconnectedText(This,pDisconnectedText)

#define IMsTscAx_put_ConnectingText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectingText(This,newVal)

#define IMsTscAx_get_ConnectingText(This,pConnectingText)	\
    (This)->lpVtbl -> get_ConnectingText(This,pConnectingText)

#define IMsTscAx_get_Connected(This,pIsConnected)	\
    (This)->lpVtbl -> get_Connected(This,pIsConnected)

#define IMsTscAx_put_DesktopWidth(This,newVal)	\
    (This)->lpVtbl -> put_DesktopWidth(This,newVal)

#define IMsTscAx_get_DesktopWidth(This,pVal)	\
    (This)->lpVtbl -> get_DesktopWidth(This,pVal)

#define IMsTscAx_put_DesktopHeight(This,newVal)	\
    (This)->lpVtbl -> put_DesktopHeight(This,newVal)

#define IMsTscAx_get_DesktopHeight(This,pVal)	\
    (This)->lpVtbl -> get_DesktopHeight(This,pVal)

#define IMsTscAx_put_StartConnected(This,fStartConnected)	\
    (This)->lpVtbl -> put_StartConnected(This,fStartConnected)

#define IMsTscAx_get_StartConnected(This,pfStartConnected)	\
    (This)->lpVtbl -> get_StartConnected(This,pfStartConnected)

#define IMsTscAx_get_HorizontalScrollBarVisible(This,pfHScrollVisible)	\
    (This)->lpVtbl -> get_HorizontalScrollBarVisible(This,pfHScrollVisible)

#define IMsTscAx_get_VerticalScrollBarVisible(This,pfVScrollVisible)	\
    (This)->lpVtbl -> get_VerticalScrollBarVisible(This,pfVScrollVisible)

#define IMsTscAx_put_FullScreenTitle(This,fullScreenTitle)	\
    (This)->lpVtbl -> put_FullScreenTitle(This,fullScreenTitle)

#define IMsTscAx_get_CipherStrength(This,pCipherStrength)	\
    (This)->lpVtbl -> get_CipherStrength(This,pCipherStrength)

#define IMsTscAx_get_Version(This,pVersion)	\
    (This)->lpVtbl -> get_Version(This,pVersion)

#define IMsTscAx_get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)	\
    (This)->lpVtbl -> get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)

#define IMsTscAx_get_SecuredSettings(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings(This,ppSecuredSettings)

#define IMsTscAx_get_AdvancedSettings(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings(This,ppAdvSettings)

#define IMsTscAx_get_Debugger(This,ppDebugger)	\
    (This)->lpVtbl -> get_Debugger(This,ppDebugger)

#define IMsTscAx_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IMsTscAx_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IMsTscAx_CreateVirtualChannels(This,newVal)	\
    (This)->lpVtbl -> CreateVirtualChannels(This,newVal)

#define IMsTscAx_SendOnVirtualChannel(This,ChanName,ChanData)	\
    (This)->lpVtbl -> SendOnVirtualChannel(This,ChanName,ChanData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_Server_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscAx_put_Server_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_Server_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pServer);


void __RPC_STUB IMsTscAx_get_Server_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_Domain_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscAx_put_Domain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_Domain_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pDomain);


void __RPC_STUB IMsTscAx_get_Domain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_UserName_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscAx_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_UserName_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pUserName);


void __RPC_STUB IMsTscAx_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_DisconnectedText_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscAx_put_DisconnectedText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_DisconnectedText_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);


void __RPC_STUB IMsTscAx_get_DisconnectedText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_ConnectingText_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscAx_put_ConnectingText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_ConnectingText_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);


void __RPC_STUB IMsTscAx_get_ConnectingText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_Connected_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pIsConnected);


void __RPC_STUB IMsTscAx_get_Connected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_DesktopWidth_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IMsTscAx_put_DesktopWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_DesktopWidth_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IMsTscAx_get_DesktopWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_DesktopHeight_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IMsTscAx_put_DesktopHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_DesktopHeight_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IMsTscAx_get_DesktopHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_StartConnected_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BOOL fStartConnected);


void __RPC_STUB IMsTscAx_put_StartConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_StartConnected_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);


void __RPC_STUB IMsTscAx_get_StartConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_HorizontalScrollBarVisible_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);


void __RPC_STUB IMsTscAx_get_HorizontalScrollBarVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_VerticalScrollBarVisible_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);


void __RPC_STUB IMsTscAx_get_VerticalScrollBarVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsTscAx_put_FullScreenTitle_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR fullScreenTitle);


void __RPC_STUB IMsTscAx_put_FullScreenTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_CipherStrength_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);


void __RPC_STUB IMsTscAx_get_CipherStrength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_Version_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVersion);


void __RPC_STUB IMsTscAx_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_SecuredSettingsEnabled_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);


void __RPC_STUB IMsTscAx_get_SecuredSettingsEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_SecuredSettings_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);


void __RPC_STUB IMsTscAx_get_SecuredSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_AdvancedSettings_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);


void __RPC_STUB IMsTscAx_get_AdvancedSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsTscAx_get_Debugger_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);


void __RPC_STUB IMsTscAx_get_Debugger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsTscAx_Connect_Proxy( 
    IMsTscAx __RPC_FAR * This);


void __RPC_STUB IMsTscAx_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsTscAx_Disconnect_Proxy( 
    IMsTscAx __RPC_FAR * This);


void __RPC_STUB IMsTscAx_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsTscAx_CreateVirtualChannels_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsTscAx_CreateVirtualChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsTscAx_SendOnVirtualChannel_Proxy( 
    IMsTscAx __RPC_FAR * This,
    /* [in] */ BSTR ChanName,
    /* [in] */ BSTR ChanData);


void __RPC_STUB IMsTscAx_SendOnVirtualChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsTscAx_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClient_INTERFACE_DEFINED__
#define __IMsRdpClient_INTERFACE_DEFINED__

/* interface IMsRdpClient */
/* [unique][helpstring][dual][uuid][object] */ 

typedef /* [public][public] */ 
enum __MIDL_IMsRdpClient_0001
    {	exDiscReasonNoInfo	= 0,
	exDiscReasonAPIInitiatedDisconnect	= 0x1,
	exDiscReasonAPIInitiatedLogoff	= 0x2,
	exDiscReasonServerIdleTimeout	= 0x3,
	exDiscReasonServerLogonTimeout	= 0x4,
	exDiscReasonReplacedByOtherConnection	= 0x5,
	exDiscReasonOutOfMemory	= 0x6,
	exDiscReasonServerDeniedConnection	= 0x7,
	exDiscReasonServerDeniedConnectionFips	= 0x8,
	exDiscReasonLicenseInternal	= 0x100,
	exDiscReasonLicenseNoLicenseServer	= 0x101,
	exDiscReasonLicenseNoLicense	= 0x102,
	exDiscReasonLicenseErrClientMsg	= 0x103,
	exDiscReasonLicenseHwidDoesntMatchLicense	= 0x104,
	exDiscReasonLicenseErrClientLicense	= 0x105,
	exDiscReasonLicenseCantFinishProtocol	= 0x106,
	exDiscReasonLicenseClientEndedProtocol	= 0x107,
	exDiscReasonLicenseErrClientEncryption	= 0x108,
	exDiscReasonLicenseCantUpgradeLicense	= 0x109,
	exDiscReasonLicenseNoRemoteConnections	= 0x10a,
	exDiscReasonProtocolRangeStart	= 0x1000,
	exDiscReasonProtocolRangeEnd	= 0x7fff
    }	ExtendedDisconnectReasonCode;

typedef /* [public][public] */ 
enum __MIDL_IMsRdpClient_0002
    {	controlCloseCanProceed	= 0,
	controlCloseWaitForEvents	= 0x1
    }	ControlCloseStatus;


EXTERN_C const IID IID_IMsRdpClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92b4a539-7115-4b7c-a5a9-e5d9efc2780a")
    IMsRdpClient : public IMsTscAx
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColorDepth( 
            /* [in] */ LONG colorDepth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColorDepth( 
            /* [retval][out] */ LONG __RPC_FAR *pcolorDepth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvancedSettings2( 
            /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecuredSettings2( 
            /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedDisconnectReason( 
            /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FullScreen( 
            /* [in] */ VARIANT_BOOL fFullScreen) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FullScreen( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVirtualChannelOptions( 
            /* [in] */ BSTR ChanName,
            /* [in] */ LONG chanOptions) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVirtualChannelOptions( 
            /* [in] */ BSTR ChanName,
            /* [retval][out] */ LONG __RPC_FAR *pChanOptions) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RequestClose( 
            /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClient __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pServer);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Domain )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Domain )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectedText )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectedText )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectingText )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectingText )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pIsConnected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopWidth )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopWidth )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopHeight )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopHeight )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartConnected )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BOOL fStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartConnected )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalScrollBarVisible )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalScrollBarVisible )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenTitle )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR fullScreenTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CipherStrength )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettingsEnabled )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debugger )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IMsRdpClient __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IMsRdpClient __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVirtualChannels )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOnVirtualChannel )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColorDepth )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ LONG colorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorDepth )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcolorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings2 )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings2 )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedDisconnectReason )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVirtualChannelOptions )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ LONG chanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVirtualChannelOptions )( 
            IMsRdpClient __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [retval][out] */ LONG __RPC_FAR *pChanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestClose )( 
            IMsRdpClient __RPC_FAR * This,
            /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus);
        
        END_INTERFACE
    } IMsRdpClientVtbl;

    interface IMsRdpClient
    {
        CONST_VTBL struct IMsRdpClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClient_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClient_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IMsRdpClient_get_Server(This,pServer)	\
    (This)->lpVtbl -> get_Server(This,pServer)

#define IMsRdpClient_put_Domain(This,newVal)	\
    (This)->lpVtbl -> put_Domain(This,newVal)

#define IMsRdpClient_get_Domain(This,pDomain)	\
    (This)->lpVtbl -> get_Domain(This,pDomain)

#define IMsRdpClient_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IMsRdpClient_get_UserName(This,pUserName)	\
    (This)->lpVtbl -> get_UserName(This,pUserName)

#define IMsRdpClient_put_DisconnectedText(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectedText(This,newVal)

#define IMsRdpClient_get_DisconnectedText(This,pDisconnectedText)	\
    (This)->lpVtbl -> get_DisconnectedText(This,pDisconnectedText)

#define IMsRdpClient_put_ConnectingText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectingText(This,newVal)

#define IMsRdpClient_get_ConnectingText(This,pConnectingText)	\
    (This)->lpVtbl -> get_ConnectingText(This,pConnectingText)

#define IMsRdpClient_get_Connected(This,pIsConnected)	\
    (This)->lpVtbl -> get_Connected(This,pIsConnected)

#define IMsRdpClient_put_DesktopWidth(This,newVal)	\
    (This)->lpVtbl -> put_DesktopWidth(This,newVal)

#define IMsRdpClient_get_DesktopWidth(This,pVal)	\
    (This)->lpVtbl -> get_DesktopWidth(This,pVal)

#define IMsRdpClient_put_DesktopHeight(This,newVal)	\
    (This)->lpVtbl -> put_DesktopHeight(This,newVal)

#define IMsRdpClient_get_DesktopHeight(This,pVal)	\
    (This)->lpVtbl -> get_DesktopHeight(This,pVal)

#define IMsRdpClient_put_StartConnected(This,fStartConnected)	\
    (This)->lpVtbl -> put_StartConnected(This,fStartConnected)

#define IMsRdpClient_get_StartConnected(This,pfStartConnected)	\
    (This)->lpVtbl -> get_StartConnected(This,pfStartConnected)

#define IMsRdpClient_get_HorizontalScrollBarVisible(This,pfHScrollVisible)	\
    (This)->lpVtbl -> get_HorizontalScrollBarVisible(This,pfHScrollVisible)

#define IMsRdpClient_get_VerticalScrollBarVisible(This,pfVScrollVisible)	\
    (This)->lpVtbl -> get_VerticalScrollBarVisible(This,pfVScrollVisible)

#define IMsRdpClient_put_FullScreenTitle(This,fullScreenTitle)	\
    (This)->lpVtbl -> put_FullScreenTitle(This,fullScreenTitle)

#define IMsRdpClient_get_CipherStrength(This,pCipherStrength)	\
    (This)->lpVtbl -> get_CipherStrength(This,pCipherStrength)

#define IMsRdpClient_get_Version(This,pVersion)	\
    (This)->lpVtbl -> get_Version(This,pVersion)

#define IMsRdpClient_get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)	\
    (This)->lpVtbl -> get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)

#define IMsRdpClient_get_SecuredSettings(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings(This,ppSecuredSettings)

#define IMsRdpClient_get_AdvancedSettings(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings(This,ppAdvSettings)

#define IMsRdpClient_get_Debugger(This,ppDebugger)	\
    (This)->lpVtbl -> get_Debugger(This,ppDebugger)

#define IMsRdpClient_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IMsRdpClient_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IMsRdpClient_CreateVirtualChannels(This,newVal)	\
    (This)->lpVtbl -> CreateVirtualChannels(This,newVal)

#define IMsRdpClient_SendOnVirtualChannel(This,ChanName,ChanData)	\
    (This)->lpVtbl -> SendOnVirtualChannel(This,ChanName,ChanData)


#define IMsRdpClient_put_ColorDepth(This,colorDepth)	\
    (This)->lpVtbl -> put_ColorDepth(This,colorDepth)

#define IMsRdpClient_get_ColorDepth(This,pcolorDepth)	\
    (This)->lpVtbl -> get_ColorDepth(This,pcolorDepth)

#define IMsRdpClient_get_AdvancedSettings2(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings2(This,ppAdvSettings)

#define IMsRdpClient_get_SecuredSettings2(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings2(This,ppSecuredSettings)

#define IMsRdpClient_get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)	\
    (This)->lpVtbl -> get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)

#define IMsRdpClient_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsRdpClient_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)

#define IMsRdpClient_SetVirtualChannelOptions(This,ChanName,chanOptions)	\
    (This)->lpVtbl -> SetVirtualChannelOptions(This,ChanName,chanOptions)

#define IMsRdpClient_GetVirtualChannelOptions(This,ChanName,pChanOptions)	\
    (This)->lpVtbl -> GetVirtualChannelOptions(This,ChanName,pChanOptions)

#define IMsRdpClient_RequestClose(This,pCloseStatus)	\
    (This)->lpVtbl -> RequestClose(This,pCloseStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_put_ColorDepth_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [in] */ LONG colorDepth);


void __RPC_STUB IMsRdpClient_put_ColorDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_get_ColorDepth_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pcolorDepth);


void __RPC_STUB IMsRdpClient_get_ColorDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_get_AdvancedSettings2_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);


void __RPC_STUB IMsRdpClient_get_AdvancedSettings2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_get_SecuredSettings2_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);


void __RPC_STUB IMsRdpClient_get_SecuredSettings2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_get_ExtendedDisconnectReason_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason);


void __RPC_STUB IMsRdpClient_get_ExtendedDisconnectReason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_put_FullScreen_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fFullScreen);


void __RPC_STUB IMsRdpClient_put_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_get_FullScreen_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen);


void __RPC_STUB IMsRdpClient_get_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_SetVirtualChannelOptions_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [in] */ BSTR ChanName,
    /* [in] */ LONG chanOptions);


void __RPC_STUB IMsRdpClient_SetVirtualChannelOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_GetVirtualChannelOptions_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [in] */ BSTR ChanName,
    /* [retval][out] */ LONG __RPC_FAR *pChanOptions);


void __RPC_STUB IMsRdpClient_GetVirtualChannelOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClient_RequestClose_Proxy( 
    IMsRdpClient __RPC_FAR * This,
    /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus);


void __RPC_STUB IMsRdpClient_RequestClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClient_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstsax_0163 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_mstsax_0163_0001
    {	disconnectReasonNoInfo	= 0,
	disconnectReasonLocalNotError	= 1,
	disconnectReasonRemoteByUser	= 2,
	disconnectReasonByServer	= 3,
	disconnectReasonDNSLookupFailed	= 260,
	disconnectReasonOutOfMemory	= 262,
	disconnectReasonConnectionTimedOut	= 264,
	disconnectReasonSocketConnectFailed	= 516,
	disconnectReasonOutOfMemory2	= 518,
	disconnectReasonHostNotFound	= 520,
	disconnectReasonWinsockSendFailed	= 772,
	disconnectReasonOutOfMemory3	= 774,
	disconnectReasonInvalidIPAddr	= 776,
	disconnectReasonSocketRecvFailed	= 1028,
	disconnectReasonInvalidSecurityData	= 1030,
	disconnectReasonInternalError	= 1032,
	disconnectReasonInvalidEncryption	= 1286,
	disconnectReasonDNSLookupFailed2	= 1288,
	disconnectReasonGetHostByNameFailed	= 1540,
	disconnectReasonInvalidServerSecurityInfo	= 1542,
	disconnectReasonTimerError	= 1544,
	disconnectReasonTimeoutOccurred	= 1796,
	disconnectReasonServerCertificateUnpackErr	= 1798,
	disconnectReasonInvalidIP	= 2052,
	disconnectReasonLicensingFailed	= 2056,
	disconnectReasonInternalSecurityError	= 2310,
	disconnectReasonAtClientWinsockFDCLOSE	= 2308,
	disconnectReasonLicensingTimeout	= 2312,
	disconnectReasonInternalSecurityError2	= 2566,
	disconnectReasonEncryptionError	= 2822,
	disconnectReasonDecryptionError	= 3078,
	disconnectReasonClientDecompressionError	= 3080
    }	DisconnectReasonCode;



extern RPC_IF_HANDLE __MIDL_itf_mstsax_0163_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstsax_0163_v0_0_s_ifspec;

#ifndef __IMsRdpClient2_INTERFACE_DEFINED__
#define __IMsRdpClient2_INTERFACE_DEFINED__

/* interface IMsRdpClient2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClient2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e7e17dc4-3b71-4ba7-a8e6-281ffadca28f")
    IMsRdpClient2 : public IMsRdpClient
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvancedSettings3( 
            /* [retval][out] */ IMsRdpClientAdvancedSettings2 __RPC_FAR *__RPC_FAR *ppAdvSettings) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectedStatusText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectedStatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *pConnectedStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClient2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClient2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClient2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pServer);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Domain )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Domain )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectedText )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectedText )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectingText )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectingText )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pIsConnected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopWidth )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopWidth )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopHeight )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopHeight )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartConnected )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BOOL fStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartConnected )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalScrollBarVisible )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalScrollBarVisible )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenTitle )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR fullScreenTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CipherStrength )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettingsEnabled )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debugger )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IMsRdpClient2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IMsRdpClient2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVirtualChannels )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOnVirtualChannel )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColorDepth )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ LONG colorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorDepth )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcolorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings2 )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings2 )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedDisconnectReason )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVirtualChannelOptions )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ LONG chanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVirtualChannelOptions )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [retval][out] */ LONG __RPC_FAR *pChanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestClose )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings3 )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings2 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectedStatusText )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectedStatusText )( 
            IMsRdpClient2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectedStatusText);
        
        END_INTERFACE
    } IMsRdpClient2Vtbl;

    interface IMsRdpClient2
    {
        CONST_VTBL struct IMsRdpClient2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClient2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClient2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClient2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClient2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClient2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClient2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClient2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClient2_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IMsRdpClient2_get_Server(This,pServer)	\
    (This)->lpVtbl -> get_Server(This,pServer)

#define IMsRdpClient2_put_Domain(This,newVal)	\
    (This)->lpVtbl -> put_Domain(This,newVal)

#define IMsRdpClient2_get_Domain(This,pDomain)	\
    (This)->lpVtbl -> get_Domain(This,pDomain)

#define IMsRdpClient2_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IMsRdpClient2_get_UserName(This,pUserName)	\
    (This)->lpVtbl -> get_UserName(This,pUserName)

#define IMsRdpClient2_put_DisconnectedText(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectedText(This,newVal)

#define IMsRdpClient2_get_DisconnectedText(This,pDisconnectedText)	\
    (This)->lpVtbl -> get_DisconnectedText(This,pDisconnectedText)

#define IMsRdpClient2_put_ConnectingText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectingText(This,newVal)

#define IMsRdpClient2_get_ConnectingText(This,pConnectingText)	\
    (This)->lpVtbl -> get_ConnectingText(This,pConnectingText)

#define IMsRdpClient2_get_Connected(This,pIsConnected)	\
    (This)->lpVtbl -> get_Connected(This,pIsConnected)

#define IMsRdpClient2_put_DesktopWidth(This,newVal)	\
    (This)->lpVtbl -> put_DesktopWidth(This,newVal)

#define IMsRdpClient2_get_DesktopWidth(This,pVal)	\
    (This)->lpVtbl -> get_DesktopWidth(This,pVal)

#define IMsRdpClient2_put_DesktopHeight(This,newVal)	\
    (This)->lpVtbl -> put_DesktopHeight(This,newVal)

#define IMsRdpClient2_get_DesktopHeight(This,pVal)	\
    (This)->lpVtbl -> get_DesktopHeight(This,pVal)

#define IMsRdpClient2_put_StartConnected(This,fStartConnected)	\
    (This)->lpVtbl -> put_StartConnected(This,fStartConnected)

#define IMsRdpClient2_get_StartConnected(This,pfStartConnected)	\
    (This)->lpVtbl -> get_StartConnected(This,pfStartConnected)

#define IMsRdpClient2_get_HorizontalScrollBarVisible(This,pfHScrollVisible)	\
    (This)->lpVtbl -> get_HorizontalScrollBarVisible(This,pfHScrollVisible)

#define IMsRdpClient2_get_VerticalScrollBarVisible(This,pfVScrollVisible)	\
    (This)->lpVtbl -> get_VerticalScrollBarVisible(This,pfVScrollVisible)

#define IMsRdpClient2_put_FullScreenTitle(This,fullScreenTitle)	\
    (This)->lpVtbl -> put_FullScreenTitle(This,fullScreenTitle)

#define IMsRdpClient2_get_CipherStrength(This,pCipherStrength)	\
    (This)->lpVtbl -> get_CipherStrength(This,pCipherStrength)

#define IMsRdpClient2_get_Version(This,pVersion)	\
    (This)->lpVtbl -> get_Version(This,pVersion)

#define IMsRdpClient2_get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)	\
    (This)->lpVtbl -> get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)

#define IMsRdpClient2_get_SecuredSettings(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings(This,ppSecuredSettings)

#define IMsRdpClient2_get_AdvancedSettings(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings(This,ppAdvSettings)

#define IMsRdpClient2_get_Debugger(This,ppDebugger)	\
    (This)->lpVtbl -> get_Debugger(This,ppDebugger)

#define IMsRdpClient2_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IMsRdpClient2_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IMsRdpClient2_CreateVirtualChannels(This,newVal)	\
    (This)->lpVtbl -> CreateVirtualChannels(This,newVal)

#define IMsRdpClient2_SendOnVirtualChannel(This,ChanName,ChanData)	\
    (This)->lpVtbl -> SendOnVirtualChannel(This,ChanName,ChanData)


#define IMsRdpClient2_put_ColorDepth(This,colorDepth)	\
    (This)->lpVtbl -> put_ColorDepth(This,colorDepth)

#define IMsRdpClient2_get_ColorDepth(This,pcolorDepth)	\
    (This)->lpVtbl -> get_ColorDepth(This,pcolorDepth)

#define IMsRdpClient2_get_AdvancedSettings2(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings2(This,ppAdvSettings)

#define IMsRdpClient2_get_SecuredSettings2(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings2(This,ppSecuredSettings)

#define IMsRdpClient2_get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)	\
    (This)->lpVtbl -> get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)

#define IMsRdpClient2_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsRdpClient2_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)

#define IMsRdpClient2_SetVirtualChannelOptions(This,ChanName,chanOptions)	\
    (This)->lpVtbl -> SetVirtualChannelOptions(This,ChanName,chanOptions)

#define IMsRdpClient2_GetVirtualChannelOptions(This,ChanName,pChanOptions)	\
    (This)->lpVtbl -> GetVirtualChannelOptions(This,ChanName,pChanOptions)

#define IMsRdpClient2_RequestClose(This,pCloseStatus)	\
    (This)->lpVtbl -> RequestClose(This,pCloseStatus)


#define IMsRdpClient2_get_AdvancedSettings3(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings3(This,ppAdvSettings)

#define IMsRdpClient2_put_ConnectedStatusText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectedStatusText(This,newVal)

#define IMsRdpClient2_get_ConnectedStatusText(This,pConnectedStatusText)	\
    (This)->lpVtbl -> get_ConnectedStatusText(This,pConnectedStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient2_get_AdvancedSettings3_Proxy( 
    IMsRdpClient2 __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientAdvancedSettings2 __RPC_FAR *__RPC_FAR *ppAdvSettings);


void __RPC_STUB IMsRdpClient2_get_AdvancedSettings3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMsRdpClient2_put_ConnectedStatusText_Proxy( 
    IMsRdpClient2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMsRdpClient2_put_ConnectedStatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient2_get_ConnectedStatusText_Proxy( 
    IMsRdpClient2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pConnectedStatusText);


void __RPC_STUB IMsRdpClient2_get_ConnectedStatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClient2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstsax_0164 */
/* [local] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_mstsax_0164_0001
    {	autoReconnectContinueAutomatic	= 0,
	autoReconnectContinueStop	= 1,
	autoReconnectContinueManual	= 2
    }	AutoReconnectContinueState;



extern RPC_IF_HANDLE __MIDL_itf_mstsax_0164_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstsax_0164_v0_0_s_ifspec;

#ifndef __IMsRdpClient3_INTERFACE_DEFINED__
#define __IMsRdpClient3_INTERFACE_DEFINED__

/* interface IMsRdpClient3 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClient3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("91b7cbc5-a72e-4fa0-9300-d647d7e897ff")
    IMsRdpClient3 : public IMsRdpClient2
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvancedSettings4( 
            /* [retval][out] */ IMsRdpClientAdvancedSettings3 __RPC_FAR *__RPC_FAR *ppAdvSettings) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClient3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClient3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClient3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pServer);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Domain )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Domain )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectedText )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectedText )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectingText )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectingText )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pIsConnected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopWidth )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopWidth )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopHeight )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopHeight )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartConnected )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BOOL fStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartConnected )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalScrollBarVisible )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalScrollBarVisible )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenTitle )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR fullScreenTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CipherStrength )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettingsEnabled )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debugger )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IMsRdpClient3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IMsRdpClient3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVirtualChannels )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOnVirtualChannel )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColorDepth )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ LONG colorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorDepth )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcolorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings2 )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings2 )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedDisconnectReason )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVirtualChannelOptions )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ LONG chanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVirtualChannelOptions )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [retval][out] */ LONG __RPC_FAR *pChanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestClose )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings3 )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings2 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectedStatusText )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectedStatusText )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectedStatusText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings4 )( 
            IMsRdpClient3 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings3 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        END_INTERFACE
    } IMsRdpClient3Vtbl;

    interface IMsRdpClient3
    {
        CONST_VTBL struct IMsRdpClient3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClient3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClient3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClient3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClient3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClient3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClient3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClient3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClient3_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IMsRdpClient3_get_Server(This,pServer)	\
    (This)->lpVtbl -> get_Server(This,pServer)

#define IMsRdpClient3_put_Domain(This,newVal)	\
    (This)->lpVtbl -> put_Domain(This,newVal)

#define IMsRdpClient3_get_Domain(This,pDomain)	\
    (This)->lpVtbl -> get_Domain(This,pDomain)

#define IMsRdpClient3_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IMsRdpClient3_get_UserName(This,pUserName)	\
    (This)->lpVtbl -> get_UserName(This,pUserName)

#define IMsRdpClient3_put_DisconnectedText(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectedText(This,newVal)

#define IMsRdpClient3_get_DisconnectedText(This,pDisconnectedText)	\
    (This)->lpVtbl -> get_DisconnectedText(This,pDisconnectedText)

#define IMsRdpClient3_put_ConnectingText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectingText(This,newVal)

#define IMsRdpClient3_get_ConnectingText(This,pConnectingText)	\
    (This)->lpVtbl -> get_ConnectingText(This,pConnectingText)

#define IMsRdpClient3_get_Connected(This,pIsConnected)	\
    (This)->lpVtbl -> get_Connected(This,pIsConnected)

#define IMsRdpClient3_put_DesktopWidth(This,newVal)	\
    (This)->lpVtbl -> put_DesktopWidth(This,newVal)

#define IMsRdpClient3_get_DesktopWidth(This,pVal)	\
    (This)->lpVtbl -> get_DesktopWidth(This,pVal)

#define IMsRdpClient3_put_DesktopHeight(This,newVal)	\
    (This)->lpVtbl -> put_DesktopHeight(This,newVal)

#define IMsRdpClient3_get_DesktopHeight(This,pVal)	\
    (This)->lpVtbl -> get_DesktopHeight(This,pVal)

#define IMsRdpClient3_put_StartConnected(This,fStartConnected)	\
    (This)->lpVtbl -> put_StartConnected(This,fStartConnected)

#define IMsRdpClient3_get_StartConnected(This,pfStartConnected)	\
    (This)->lpVtbl -> get_StartConnected(This,pfStartConnected)

#define IMsRdpClient3_get_HorizontalScrollBarVisible(This,pfHScrollVisible)	\
    (This)->lpVtbl -> get_HorizontalScrollBarVisible(This,pfHScrollVisible)

#define IMsRdpClient3_get_VerticalScrollBarVisible(This,pfVScrollVisible)	\
    (This)->lpVtbl -> get_VerticalScrollBarVisible(This,pfVScrollVisible)

#define IMsRdpClient3_put_FullScreenTitle(This,fullScreenTitle)	\
    (This)->lpVtbl -> put_FullScreenTitle(This,fullScreenTitle)

#define IMsRdpClient3_get_CipherStrength(This,pCipherStrength)	\
    (This)->lpVtbl -> get_CipherStrength(This,pCipherStrength)

#define IMsRdpClient3_get_Version(This,pVersion)	\
    (This)->lpVtbl -> get_Version(This,pVersion)

#define IMsRdpClient3_get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)	\
    (This)->lpVtbl -> get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)

#define IMsRdpClient3_get_SecuredSettings(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings(This,ppSecuredSettings)

#define IMsRdpClient3_get_AdvancedSettings(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings(This,ppAdvSettings)

#define IMsRdpClient3_get_Debugger(This,ppDebugger)	\
    (This)->lpVtbl -> get_Debugger(This,ppDebugger)

#define IMsRdpClient3_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IMsRdpClient3_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IMsRdpClient3_CreateVirtualChannels(This,newVal)	\
    (This)->lpVtbl -> CreateVirtualChannels(This,newVal)

#define IMsRdpClient3_SendOnVirtualChannel(This,ChanName,ChanData)	\
    (This)->lpVtbl -> SendOnVirtualChannel(This,ChanName,ChanData)


#define IMsRdpClient3_put_ColorDepth(This,colorDepth)	\
    (This)->lpVtbl -> put_ColorDepth(This,colorDepth)

#define IMsRdpClient3_get_ColorDepth(This,pcolorDepth)	\
    (This)->lpVtbl -> get_ColorDepth(This,pcolorDepth)

#define IMsRdpClient3_get_AdvancedSettings2(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings2(This,ppAdvSettings)

#define IMsRdpClient3_get_SecuredSettings2(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings2(This,ppSecuredSettings)

#define IMsRdpClient3_get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)	\
    (This)->lpVtbl -> get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)

#define IMsRdpClient3_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsRdpClient3_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)

#define IMsRdpClient3_SetVirtualChannelOptions(This,ChanName,chanOptions)	\
    (This)->lpVtbl -> SetVirtualChannelOptions(This,ChanName,chanOptions)

#define IMsRdpClient3_GetVirtualChannelOptions(This,ChanName,pChanOptions)	\
    (This)->lpVtbl -> GetVirtualChannelOptions(This,ChanName,pChanOptions)

#define IMsRdpClient3_RequestClose(This,pCloseStatus)	\
    (This)->lpVtbl -> RequestClose(This,pCloseStatus)


#define IMsRdpClient3_get_AdvancedSettings3(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings3(This,ppAdvSettings)

#define IMsRdpClient3_put_ConnectedStatusText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectedStatusText(This,newVal)

#define IMsRdpClient3_get_ConnectedStatusText(This,pConnectedStatusText)	\
    (This)->lpVtbl -> get_ConnectedStatusText(This,pConnectedStatusText)


#define IMsRdpClient3_get_AdvancedSettings4(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings4(This,ppAdvSettings)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient3_get_AdvancedSettings4_Proxy( 
    IMsRdpClient3 __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientAdvancedSettings3 __RPC_FAR *__RPC_FAR *ppAdvSettings);


void __RPC_STUB IMsRdpClient3_get_AdvancedSettings4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClient3_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClient4_INTERFACE_DEFINED__
#define __IMsRdpClient4_INTERFACE_DEFINED__

/* interface IMsRdpClient4 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClient4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("095E0738-D97D-488b-B9F6-DD0E8D66C0DE")
    IMsRdpClient4 : public IMsRdpClient3
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvancedSettings5( 
            /* [retval][out] */ IMsRdpClientAdvancedSettings4 __RPC_FAR *__RPC_FAR *ppAdvSettings) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClient4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClient4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClient4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pServer);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Domain )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Domain )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectedText )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectedText )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectingText )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectingText )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pIsConnected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopWidth )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopWidth )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopHeight )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopHeight )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartConnected )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BOOL fStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartConnected )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalScrollBarVisible )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalScrollBarVisible )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenTitle )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR fullScreenTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CipherStrength )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettingsEnabled )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debugger )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IMsRdpClient4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IMsRdpClient4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVirtualChannels )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOnVirtualChannel )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColorDepth )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ LONG colorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorDepth )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcolorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings2 )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings2 )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedDisconnectReason )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVirtualChannelOptions )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ LONG chanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVirtualChannelOptions )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [retval][out] */ LONG __RPC_FAR *pChanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestClose )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings3 )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings2 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectedStatusText )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectedStatusText )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectedStatusText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings4 )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings3 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings5 )( 
            IMsRdpClient4 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings4 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        END_INTERFACE
    } IMsRdpClient4Vtbl;

    interface IMsRdpClient4
    {
        CONST_VTBL struct IMsRdpClient4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClient4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClient4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClient4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClient4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClient4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClient4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClient4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClient4_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IMsRdpClient4_get_Server(This,pServer)	\
    (This)->lpVtbl -> get_Server(This,pServer)

#define IMsRdpClient4_put_Domain(This,newVal)	\
    (This)->lpVtbl -> put_Domain(This,newVal)

#define IMsRdpClient4_get_Domain(This,pDomain)	\
    (This)->lpVtbl -> get_Domain(This,pDomain)

#define IMsRdpClient4_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IMsRdpClient4_get_UserName(This,pUserName)	\
    (This)->lpVtbl -> get_UserName(This,pUserName)

#define IMsRdpClient4_put_DisconnectedText(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectedText(This,newVal)

#define IMsRdpClient4_get_DisconnectedText(This,pDisconnectedText)	\
    (This)->lpVtbl -> get_DisconnectedText(This,pDisconnectedText)

#define IMsRdpClient4_put_ConnectingText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectingText(This,newVal)

#define IMsRdpClient4_get_ConnectingText(This,pConnectingText)	\
    (This)->lpVtbl -> get_ConnectingText(This,pConnectingText)

#define IMsRdpClient4_get_Connected(This,pIsConnected)	\
    (This)->lpVtbl -> get_Connected(This,pIsConnected)

#define IMsRdpClient4_put_DesktopWidth(This,newVal)	\
    (This)->lpVtbl -> put_DesktopWidth(This,newVal)

#define IMsRdpClient4_get_DesktopWidth(This,pVal)	\
    (This)->lpVtbl -> get_DesktopWidth(This,pVal)

#define IMsRdpClient4_put_DesktopHeight(This,newVal)	\
    (This)->lpVtbl -> put_DesktopHeight(This,newVal)

#define IMsRdpClient4_get_DesktopHeight(This,pVal)	\
    (This)->lpVtbl -> get_DesktopHeight(This,pVal)

#define IMsRdpClient4_put_StartConnected(This,fStartConnected)	\
    (This)->lpVtbl -> put_StartConnected(This,fStartConnected)

#define IMsRdpClient4_get_StartConnected(This,pfStartConnected)	\
    (This)->lpVtbl -> get_StartConnected(This,pfStartConnected)

#define IMsRdpClient4_get_HorizontalScrollBarVisible(This,pfHScrollVisible)	\
    (This)->lpVtbl -> get_HorizontalScrollBarVisible(This,pfHScrollVisible)

#define IMsRdpClient4_get_VerticalScrollBarVisible(This,pfVScrollVisible)	\
    (This)->lpVtbl -> get_VerticalScrollBarVisible(This,pfVScrollVisible)

#define IMsRdpClient4_put_FullScreenTitle(This,fullScreenTitle)	\
    (This)->lpVtbl -> put_FullScreenTitle(This,fullScreenTitle)

#define IMsRdpClient4_get_CipherStrength(This,pCipherStrength)	\
    (This)->lpVtbl -> get_CipherStrength(This,pCipherStrength)

#define IMsRdpClient4_get_Version(This,pVersion)	\
    (This)->lpVtbl -> get_Version(This,pVersion)

#define IMsRdpClient4_get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)	\
    (This)->lpVtbl -> get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)

#define IMsRdpClient4_get_SecuredSettings(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings(This,ppSecuredSettings)

#define IMsRdpClient4_get_AdvancedSettings(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings(This,ppAdvSettings)

#define IMsRdpClient4_get_Debugger(This,ppDebugger)	\
    (This)->lpVtbl -> get_Debugger(This,ppDebugger)

#define IMsRdpClient4_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IMsRdpClient4_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IMsRdpClient4_CreateVirtualChannels(This,newVal)	\
    (This)->lpVtbl -> CreateVirtualChannels(This,newVal)

#define IMsRdpClient4_SendOnVirtualChannel(This,ChanName,ChanData)	\
    (This)->lpVtbl -> SendOnVirtualChannel(This,ChanName,ChanData)


#define IMsRdpClient4_put_ColorDepth(This,colorDepth)	\
    (This)->lpVtbl -> put_ColorDepth(This,colorDepth)

#define IMsRdpClient4_get_ColorDepth(This,pcolorDepth)	\
    (This)->lpVtbl -> get_ColorDepth(This,pcolorDepth)

#define IMsRdpClient4_get_AdvancedSettings2(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings2(This,ppAdvSettings)

#define IMsRdpClient4_get_SecuredSettings2(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings2(This,ppSecuredSettings)

#define IMsRdpClient4_get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)	\
    (This)->lpVtbl -> get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)

#define IMsRdpClient4_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsRdpClient4_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)

#define IMsRdpClient4_SetVirtualChannelOptions(This,ChanName,chanOptions)	\
    (This)->lpVtbl -> SetVirtualChannelOptions(This,ChanName,chanOptions)

#define IMsRdpClient4_GetVirtualChannelOptions(This,ChanName,pChanOptions)	\
    (This)->lpVtbl -> GetVirtualChannelOptions(This,ChanName,pChanOptions)

#define IMsRdpClient4_RequestClose(This,pCloseStatus)	\
    (This)->lpVtbl -> RequestClose(This,pCloseStatus)


#define IMsRdpClient4_get_AdvancedSettings3(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings3(This,ppAdvSettings)

#define IMsRdpClient4_put_ConnectedStatusText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectedStatusText(This,newVal)

#define IMsRdpClient4_get_ConnectedStatusText(This,pConnectedStatusText)	\
    (This)->lpVtbl -> get_ConnectedStatusText(This,pConnectedStatusText)


#define IMsRdpClient4_get_AdvancedSettings4(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings4(This,ppAdvSettings)


#define IMsRdpClient4_get_AdvancedSettings5(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings5(This,ppAdvSettings)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient4_get_AdvancedSettings5_Proxy( 
    IMsRdpClient4 __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientAdvancedSettings4 __RPC_FAR *__RPC_FAR *ppAdvSettings);


void __RPC_STUB IMsRdpClient4_get_AdvancedSettings5_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClient4_INTERFACE_DEFINED__ */


#ifndef __IMsRdpClient5_INTERFACE_DEFINED__
#define __IMsRdpClient5_INTERFACE_DEFINED__

/* interface IMsRdpClient5 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMsRdpClient5;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4eb5335b-6429-477d-b922-e06a28ecd8bf")
    IMsRdpClient5 : public IMsRdpClient4
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rail( 
            /* [retval][out] */ ITSRemoteApplication __RPC_FAR *__RPC_FAR *ppRail) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransportSettings( 
            /* [retval][out] */ IMsRdpClientTransportSettings __RPC_FAR *__RPC_FAR *ppXportSet) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MsRdpClientShell( 
            /* [retval][out] */ IMsRdpClientShell __RPC_FAR *__RPC_FAR *ppLauncher) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CenterClientWindow( 
            /* [in] */ UINT xRatio,
            /* [in] */ UINT yRatio) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvancedSettings6( 
            /* [retval][out] */ IMsRdpClientAdvancedSettings5 __RPC_FAR *__RPC_FAR *ppAdvSettings) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMsRdpClient5Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsRdpClient5 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsRdpClient5 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pServer);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Domain )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Domain )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDomain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectedText )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectedText )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDisconnectedText);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectingText )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectingText )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectingText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pIsConnected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopWidth )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopWidth )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DesktopHeight )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DesktopHeight )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartConnected )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BOOL fStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartConnected )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfStartConnected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalScrollBarVisible )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfHScrollVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalScrollBarVisible )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfVScrollVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenTitle )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR fullScreenTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CipherStrength )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCipherStrength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettingsEnabled )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pSecuredSettingsEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsTscSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsTscAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debugger )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsTscDebug __RPC_FAR *__RPC_FAR *ppDebugger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IMsRdpClient5 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IMsRdpClient5 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVirtualChannels )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOnVirtualChannel )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ BSTR ChanData);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColorDepth )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ LONG colorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorDepth )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pcolorDepth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings2 )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecuredSettings2 )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientSecuredSettings __RPC_FAR *__RPC_FAR *ppSecuredSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedDisconnectReason )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ ExtendedDisconnectReasonCode __RPC_FAR *pExtendedDisconnectReason);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfFullScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVirtualChannelOptions )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [in] */ LONG chanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVirtualChannelOptions )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR ChanName,
            /* [retval][out] */ LONG __RPC_FAR *pChanOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestClose )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ ControlCloseStatus __RPC_FAR *pCloseStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings3 )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings2 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConnectedStatusText )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectedStatusText )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConnectedStatusText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings4 )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings3 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings5 )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings4 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rail )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ ITSRemoteApplication __RPC_FAR *__RPC_FAR *ppRail);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportSettings )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientTransportSettings __RPC_FAR *__RPC_FAR *ppXportSet);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MsRdpClientShell )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientShell __RPC_FAR *__RPC_FAR *ppLauncher);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CenterClientWindow )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [in] */ UINT xRatio,
            /* [in] */ UINT yRatio);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvancedSettings6 )( 
            IMsRdpClient5 __RPC_FAR * This,
            /* [retval][out] */ IMsRdpClientAdvancedSettings5 __RPC_FAR *__RPC_FAR *ppAdvSettings);
        
        END_INTERFACE
    } IMsRdpClient5Vtbl;

    interface IMsRdpClient5
    {
        CONST_VTBL struct IMsRdpClient5Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsRdpClient5_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsRdpClient5_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsRdpClient5_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsRdpClient5_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsRdpClient5_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsRdpClient5_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsRdpClient5_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMsRdpClient5_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IMsRdpClient5_get_Server(This,pServer)	\
    (This)->lpVtbl -> get_Server(This,pServer)

#define IMsRdpClient5_put_Domain(This,newVal)	\
    (This)->lpVtbl -> put_Domain(This,newVal)

#define IMsRdpClient5_get_Domain(This,pDomain)	\
    (This)->lpVtbl -> get_Domain(This,pDomain)

#define IMsRdpClient5_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IMsRdpClient5_get_UserName(This,pUserName)	\
    (This)->lpVtbl -> get_UserName(This,pUserName)

#define IMsRdpClient5_put_DisconnectedText(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectedText(This,newVal)

#define IMsRdpClient5_get_DisconnectedText(This,pDisconnectedText)	\
    (This)->lpVtbl -> get_DisconnectedText(This,pDisconnectedText)

#define IMsRdpClient5_put_ConnectingText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectingText(This,newVal)

#define IMsRdpClient5_get_ConnectingText(This,pConnectingText)	\
    (This)->lpVtbl -> get_ConnectingText(This,pConnectingText)

#define IMsRdpClient5_get_Connected(This,pIsConnected)	\
    (This)->lpVtbl -> get_Connected(This,pIsConnected)

#define IMsRdpClient5_put_DesktopWidth(This,newVal)	\
    (This)->lpVtbl -> put_DesktopWidth(This,newVal)

#define IMsRdpClient5_get_DesktopWidth(This,pVal)	\
    (This)->lpVtbl -> get_DesktopWidth(This,pVal)

#define IMsRdpClient5_put_DesktopHeight(This,newVal)	\
    (This)->lpVtbl -> put_DesktopHeight(This,newVal)

#define IMsRdpClient5_get_DesktopHeight(This,pVal)	\
    (This)->lpVtbl -> get_DesktopHeight(This,pVal)

#define IMsRdpClient5_put_StartConnected(This,fStartConnected)	\
    (This)->lpVtbl -> put_StartConnected(This,fStartConnected)

#define IMsRdpClient5_get_StartConnected(This,pfStartConnected)	\
    (This)->lpVtbl -> get_StartConnected(This,pfStartConnected)

#define IMsRdpClient5_get_HorizontalScrollBarVisible(This,pfHScrollVisible)	\
    (This)->lpVtbl -> get_HorizontalScrollBarVisible(This,pfHScrollVisible)

#define IMsRdpClient5_get_VerticalScrollBarVisible(This,pfVScrollVisible)	\
    (This)->lpVtbl -> get_VerticalScrollBarVisible(This,pfVScrollVisible)

#define IMsRdpClient5_put_FullScreenTitle(This,fullScreenTitle)	\
    (This)->lpVtbl -> put_FullScreenTitle(This,fullScreenTitle)

#define IMsRdpClient5_get_CipherStrength(This,pCipherStrength)	\
    (This)->lpVtbl -> get_CipherStrength(This,pCipherStrength)

#define IMsRdpClient5_get_Version(This,pVersion)	\
    (This)->lpVtbl -> get_Version(This,pVersion)

#define IMsRdpClient5_get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)	\
    (This)->lpVtbl -> get_SecuredSettingsEnabled(This,pSecuredSettingsEnabled)

#define IMsRdpClient5_get_SecuredSettings(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings(This,ppSecuredSettings)

#define IMsRdpClient5_get_AdvancedSettings(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings(This,ppAdvSettings)

#define IMsRdpClient5_get_Debugger(This,ppDebugger)	\
    (This)->lpVtbl -> get_Debugger(This,ppDebugger)

#define IMsRdpClient5_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IMsRdpClient5_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IMsRdpClient5_CreateVirtualChannels(This,newVal)	\
    (This)->lpVtbl -> CreateVirtualChannels(This,newVal)

#define IMsRdpClient5_SendOnVirtualChannel(This,ChanName,ChanData)	\
    (This)->lpVtbl -> SendOnVirtualChannel(This,ChanName,ChanData)


#define IMsRdpClient5_put_ColorDepth(This,colorDepth)	\
    (This)->lpVtbl -> put_ColorDepth(This,colorDepth)

#define IMsRdpClient5_get_ColorDepth(This,pcolorDepth)	\
    (This)->lpVtbl -> get_ColorDepth(This,pcolorDepth)

#define IMsRdpClient5_get_AdvancedSettings2(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings2(This,ppAdvSettings)

#define IMsRdpClient5_get_SecuredSettings2(This,ppSecuredSettings)	\
    (This)->lpVtbl -> get_SecuredSettings2(This,ppSecuredSettings)

#define IMsRdpClient5_get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)	\
    (This)->lpVtbl -> get_ExtendedDisconnectReason(This,pExtendedDisconnectReason)

#define IMsRdpClient5_put_FullScreen(This,fFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,fFullScreen)

#define IMsRdpClient5_get_FullScreen(This,pfFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pfFullScreen)

#define IMsRdpClient5_SetVirtualChannelOptions(This,ChanName,chanOptions)	\
    (This)->lpVtbl -> SetVirtualChannelOptions(This,ChanName,chanOptions)

#define IMsRdpClient5_GetVirtualChannelOptions(This,ChanName,pChanOptions)	\
    (This)->lpVtbl -> GetVirtualChannelOptions(This,ChanName,pChanOptions)

#define IMsRdpClient5_RequestClose(This,pCloseStatus)	\
    (This)->lpVtbl -> RequestClose(This,pCloseStatus)


#define IMsRdpClient5_get_AdvancedSettings3(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings3(This,ppAdvSettings)

#define IMsRdpClient5_put_ConnectedStatusText(This,newVal)	\
    (This)->lpVtbl -> put_ConnectedStatusText(This,newVal)

#define IMsRdpClient5_get_ConnectedStatusText(This,pConnectedStatusText)	\
    (This)->lpVtbl -> get_ConnectedStatusText(This,pConnectedStatusText)


#define IMsRdpClient5_get_AdvancedSettings4(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings4(This,ppAdvSettings)


#define IMsRdpClient5_get_AdvancedSettings5(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings5(This,ppAdvSettings)


#define IMsRdpClient5_get_Rail(This,ppRail)	\
    (This)->lpVtbl -> get_Rail(This,ppRail)

#define IMsRdpClient5_get_TransportSettings(This,ppXportSet)	\
    (This)->lpVtbl -> get_TransportSettings(This,ppXportSet)

#define IMsRdpClient5_get_MsRdpClientShell(This,ppLauncher)	\
    (This)->lpVtbl -> get_MsRdpClientShell(This,ppLauncher)

#define IMsRdpClient5_CenterClientWindow(This,xRatio,yRatio)	\
    (This)->lpVtbl -> CenterClientWindow(This,xRatio,yRatio)

#define IMsRdpClient5_get_AdvancedSettings6(This,ppAdvSettings)	\
    (This)->lpVtbl -> get_AdvancedSettings6(This,ppAdvSettings)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient5_get_Rail_Proxy( 
    IMsRdpClient5 __RPC_FAR * This,
    /* [retval][out] */ ITSRemoteApplication __RPC_FAR *__RPC_FAR *ppRail);


void __RPC_STUB IMsRdpClient5_get_Rail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient5_get_TransportSettings_Proxy( 
    IMsRdpClient5 __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientTransportSettings __RPC_FAR *__RPC_FAR *ppXportSet);


void __RPC_STUB IMsRdpClient5_get_TransportSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient5_get_MsRdpClientShell_Proxy( 
    IMsRdpClient5 __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientShell __RPC_FAR *__RPC_FAR *ppLauncher);


void __RPC_STUB IMsRdpClient5_get_MsRdpClientShell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMsRdpClient5_CenterClientWindow_Proxy( 
    IMsRdpClient5 __RPC_FAR * This,
    /* [in] */ UINT xRatio,
    /* [in] */ UINT yRatio);


void __RPC_STUB IMsRdpClient5_CenterClientWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMsRdpClient5_get_AdvancedSettings6_Proxy( 
    IMsRdpClient5 __RPC_FAR * This,
    /* [retval][out] */ IMsRdpClientAdvancedSettings5 __RPC_FAR *__RPC_FAR *ppAdvSettings);


void __RPC_STUB IMsRdpClient5_get_AdvancedSettings6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMsRdpClient5_INTERFACE_DEFINED__ */



#ifndef __MSTSCLib_LIBRARY_DEFINED__
#define __MSTSCLib_LIBRARY_DEFINED__

/* library MSTSCLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSTSCLib;

#ifndef __IMsTscAxEvents_DISPINTERFACE_DEFINED__
#define __IMsTscAxEvents_DISPINTERFACE_DEFINED__

/* dispinterface IMsTscAxEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IMsTscAxEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("336d5562-efa8-482e-8cb3-c5c0fc7a7db6")
    IMsTscAxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMsTscAxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMsTscAxEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMsTscAxEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMsTscAxEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMsTscAxEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMsTscAxEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMsTscAxEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMsTscAxEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IMsTscAxEventsVtbl;

    interface IMsTscAxEvents
    {
        CONST_VTBL struct IMsTscAxEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMsTscAxEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMsTscAxEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMsTscAxEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMsTscAxEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMsTscAxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMsTscAxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMsTscAxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMsTscAxEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MsTscAx;

#ifdef __cplusplus

class DECLSPEC_UUID("a41a4187-5a86-4e26-b40a-856f9035d9cb")
MsTscAx;
#endif

EXTERN_C const CLSID CLSID_MsRdpClient;

#ifdef __cplusplus

class DECLSPEC_UUID("7cacbd7b-0d99-468f-ac33-22e495c0afe5")
MsRdpClient;
#endif

EXTERN_C const CLSID CLSID_MsRdpClient2;

#ifdef __cplusplus

class DECLSPEC_UUID("3523c2fb-4031-44e4-9a3b-f1e94986ee7f")
MsRdpClient2;
#endif

EXTERN_C const CLSID CLSID_MsRdpClient3;

#ifdef __cplusplus

class DECLSPEC_UUID("ace575fd-1fcf-4074-9401-ebab990fa9de")
MsRdpClient3;
#endif

EXTERN_C const CLSID CLSID_MsRdpClient4;

#ifdef __cplusplus

class DECLSPEC_UUID("6AE29350-321B-42be-BBE5-12FB5270C0DE")
MsRdpClient4;
#endif

EXTERN_C const CLSID CLSID_MsRdpClient5;

#ifdef __cplusplus

class DECLSPEC_UUID("4eb2f086-c818-447e-b32c-c51ce2b30d31")
MsRdpClient5;
#endif
#endif /* __MSTSCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long __RPC_FAR *, unsigned long            , HWND __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HWND_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HWND __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HWND_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HWND __RPC_FAR * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long __RPC_FAR *, HWND __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


