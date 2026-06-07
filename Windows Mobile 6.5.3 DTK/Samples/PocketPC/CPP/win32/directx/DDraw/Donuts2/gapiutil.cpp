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
//-----------------------------------------------------------------------------
// File: gapiutil.cpp
//
// Desc: GAPI routines for turning unfiltered button message mode on/off.
//
//
//-----------------------------------------------------------------------------


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include "gx.h"

extern "C" int OpenGapiInput(){
    return GXOpenInput();
}

extern "C" int CloseGapiInput(){
    return GXCloseInput();
}