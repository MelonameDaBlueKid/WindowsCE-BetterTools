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
#ifndef __INCLUDE_SIPDEV__
#define __INCLUDE_SIPDEV__

#ifdef __cplusplus
extern "C" {
#endif


//  Device io control commands for the sip.
//  Also used as dwCode for WM_SIPTHREADCALL.
#define SIPDEV_SHOW_IM                1
#define SIPDEV_GET_INFO               2
#define SIPDEV_SET_INFO               3
#define SIPDEV_GET_CURRENT_IM  4
#define SIPDEV_SET_CURRENT_IM  5
#define SIPDEV_REGISTER_UI         6
#define SIPDEV_DEFAULT_RECT      7

//IO control code 8 was used by SIPDEV_ENUMERATE on 5.1x and previous versions of WinCE
#define SIPDEV_RESERVED8            8

#define SIPDEV_IMM_SET_ACTIVE_CONTEXT     9
#define SIPDEV_GET_IM_COUNT                       10
#define SIPDEV_GET_IM_ENUMINFO_LIST        11
#define SIPDEV_GET_IM_INPUTLANGUAGE_COUNT  12
#define SIPDEV_GET_IM_INPUTLANGUAGE_LIST   13
#define SIPDEV_GET_IM_ICON          14
#define SIPDEV_PREFERENCE           15


struct SIP_IMM_SET_ACTIVE_CONTEXT
    {
    HWND    hwnd;
    BOOL    bOpen;
    DWORD   dwConversion;
    DWORD   dwSentence;
    HKL     hkl;
    };



#ifdef __cplusplus
};
#endif

#endif//__INCLUDE_SIPDEV__
