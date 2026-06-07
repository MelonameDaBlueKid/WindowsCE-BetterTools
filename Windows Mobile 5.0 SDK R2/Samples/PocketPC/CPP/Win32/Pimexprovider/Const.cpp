//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.


#include "PimExProvider.h"

// Define our consts

const LPWSTR     g_szDllName = L"PimExProvider.dll";

// Custom background RBG color for the appointment in the Calendar Agenda View
const COLORREF   g_crCalendarBackground  = RGB(0, 255, 0);

// Registry location where we store this sample providers info.
const WCHAR      g_wszOurKey[]           = L"Software\\PimExProvider";

// Reg value name for the source id used by this samepl provider.
const WCHAR      g_wszOurValueName[]     = L"Id";


// GUID for this source provider.
//
// NOTE:
// If you are creating new source provider based on this code
// you absolutely must create your own CLSIDs!  
// Visual Studio's Guidgen.exe is an excellent tool for this
const LPTSTR g_szCLSID_SampleProvider = 
    TEXT("{504C7C2F-35E4-4909-94B3-9113E1B8BD38}");

const GUID CLSID_SampleProvider = 
    { 0x504c7c2f, 0x35e4, 0x4909, { 0x94, 0xb3, 0x91, 0x13, 0xe1, 0xb8, 0xbd, 0x38 } };

