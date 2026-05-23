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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//

#pragma once
#if 0

Building the typedefs below with WINCEMACRO defined results in a compiler error.

This file is needed since auto_xxx.hxx implicitly include winbase.h, and since
auto_xxx.hxx is included by files built with WINCEMACRO defined.

#endif

#include "auto_xxx.hxx"
#include <winbase.h>

namespace ce
{
    typedef auto_xxx<HANDLE, BOOL (__stdcall*)(HANDLE), DeactivateDevice, NULL> auto_hdevice;

    typedef auto_xxx<HANDLE, BOOL (__stdcall*)(HANDLE), DeactivateDevice, NULL,ref_counting> smart_hdevice;
}; // namespace ce
