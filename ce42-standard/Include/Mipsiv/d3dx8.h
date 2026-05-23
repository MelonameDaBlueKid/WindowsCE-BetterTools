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
///////////////////////////////////////////////////////////////////////////
//
//  File:       d3dx8.h
//  Content:    D3DX utility library
//
///////////////////////////////////////////////////////////////////////////

#ifndef __D3DX8_H__
#define __D3DX8_H__

#include <d3d8.h>
#include <limits.h>

#ifndef D3DXINLINE
#ifdef __cplusplus
#define D3DXINLINE inline
#else
#define D3DXINLINE _inline
#endif
#endif

#define D3DX_DEFAULT ULONG_MAX
#define D3DX_DEFAULT_FLOAT FLT_MAX

#include "d3dx8math.h"
#include "d3dx8tex.h"

#endif //__D3DX8_H__
