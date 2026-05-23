// ***************************************************************************
// REGISTRY.H
//
// Function Declarations for accessing the registry data for Minesweeper
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#pragma once

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

// some key/value definitions
#define REGISTRY_ROOT				(HKEY_CURRENT_USER)
#define REGISTRY_KEY				(TEXT("Software\\Microsoft\\Minesweeper"))
#define REGISTRY_VALUE_HIGHNAME		(TEXT("HighName"))
#define REGISTRY_VALUE_HIGHTIME		(TEXT("HighTime"))
#define REGISTRY_VALUE_GAMEDATA		(TEXT("GameData"))

// function declarations
BOOL InitRegistry(LPDWORD dwDisposition);
BOOL GetRegString(LPCTSTR szValue, LPTSTR *szRetval);
BOOL SetRegString(LPCTSTR szValue, LPTSTR szRetval);
BOOL GetRegDWORD(LPCTSTR szValue, LPDWORD dwResult);
BOOL SetRegDWORD(LPCTSTR szValue, DWORD dwResult);
BOOL GetRegBinary(LPCTSTR szValue, PBYTE lpData, DWORD dwSize);
BOOL SetRegBinary(LPCTSTR szValue, PBYTE lpData, DWORD dwSize);

#endif