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
// COMMON.H - common includes

#pragma once

#ifndef UNDER_CE
#define ASSERT(cond) if ((cond) == FALSE) { DebugBreak(); }
#endif //!UNDER_CE

#pragma warning(push, 3)
#include <windows.h>
#include <objbase.h>
#pragma warning(pop)
#pragma warning(disable: 4514) // unreferenced inline/local function removed
#include <shlguid.h>
#include <shlobj.h>
#include <ocidl.h>
#include <aygshell.h>
#include <astdtapi.h>
#include <winuserm.h>
#include "guids.h"
#include "ctxmenu.h"
#include "clsfact.h"
#include "resource.h"
