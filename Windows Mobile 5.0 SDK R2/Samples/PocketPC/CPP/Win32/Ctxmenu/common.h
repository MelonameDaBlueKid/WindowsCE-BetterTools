//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
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
