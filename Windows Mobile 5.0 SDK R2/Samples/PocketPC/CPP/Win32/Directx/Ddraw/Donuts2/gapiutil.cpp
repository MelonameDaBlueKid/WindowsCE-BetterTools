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