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

#ifndef __ENGINE_H__
#define __ENGINE_H__

typedef HANDLE HCONVENG;

#define CE_SPELL_MODE           0x00000001          // Spell (multitap) mode
#define CE_NUMBERS_MODE         0x00000002          // Numbers mode
#define CE_SHIFT_MODE           0x00000100          // Shift mode
#define CE_CAPSLOCK_MODE        0x00000200          // CapsLock mode
#define CE_INSERT_MODE          0x00000400          // Insert (composition) mode
#define CE_EXTSPELL_MODE        0x00000800          // Extended spell mode in which client provides characters.

#define NUMBERS_MODE(dwState)   (((dwState) & (CE_NUMBERS_MODE | CE_SPELL_MODE)) == CE_NUMBERS_MODE)
#define SPELL_MODE(dwState)     (((dwState) & (CE_NUMBERS_MODE | CE_SPELL_MODE)) == CE_SPELL_MODE)
#define SHIFT_MODE(dwState)     ((dwState) & CE_SHIFT_MODE)
#define CAPSLOCK_MODE(dwState)  ((dwState) & CE_CAPSLOCK_MODE)
#define EXTSPELL_MODE(dwState)  ((dwState) & CE_EXTSPELL_MODE)

// In insert mode while there is a composition string
#define INSERT_MODE(dwState)    (dwState & CE_INSERT_MODE)

// Request types
typedef enum _CONVENG_REQUEST
{
    crSetTimer,                         // SetTimer
    crNextSymbol,                       // Get Next Symbol
} CONVENG_REQUEST;

// Symbol info
typedef struct _CRD_SYMBOL_INFO
{
    UINT uVKey;                         // Key
    TCHAR chSymbol;                     // Current symbol & next symbol
} CRD_SYMBOL_INFO, *PCRD_SYMBOL_INFO;

// Request data
typedef struct _CONVENG_REQUEST_DATA
{
    DWORD cbSize;                       // Struct size
    CONVENG_REQUEST cr;                 // Request type
    union                               // Info specific to each type
    {
        CRD_SYMBOL_INFO si;             // Symbol info
    } info;

} CONVENG_REQUEST_DATA, *PCONVENG_REQUEST_DATA;

typedef HRESULT (* CONVENG_CALLBACK)(HCONVENG, CONVENG_REQUEST_DATA*, LPARAM);

// Callback implemented by client
HRESULT ConvEngine_Callback(HCONVENG hce, 
                            CONVENG_REQUEST_DATA* pcrd,
                            LPARAM lpUser);

// Initialize engine
HRESULT ConvEngine_Init(CONVENG_CALLBACK pfnCallBack, LPARAM lpUser, HCONVENG* phce);
// Terminate engine
HRESULT ConvEngine_Terminate(HCONVENG hce);
// Get state, like mode composition string state etc.
HRESULT ConvEngine_GetState(HCONVENG hce, DWORD* pdwState);
// Set state, like mode, composition string state etc.
HRESULT ConvEngine_SetState(HCONVENG hce, DWORD dwState, DWORD dwMask);
// Process new key 
HRESULT ConvEngine_ProcessKey(HCONVENG hce, UINT uVKey, TCHAR* pch);
// MultiTap timer timed out
HRESULT ConvEngine_TimedOut(HCONVENG hce);

#endif //__ENGINE_H__
