//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of your Microsoft Windows CE
// Source Alliance Program license form.  If you did not accept the terms of
// such a license, you are not authorized to use this source code.
//
///////////////////////////////////////////////////////////////////////////
//
//  File:       d3dmx.h
//  Content:    D3DMX utility library
//
///////////////////////////////////////////////////////////////////////////

#ifndef __D3DMX_H__
#define __D3DMX_H__

#include <d3dm.h>
#include <limits.h>

#ifndef D3DMXINLINE
#ifdef __cplusplus
#define D3DMXINLINE inline
#else
#define D3DMXINLINE _inline
#endif
#endif

#define D3DMX_DEFAULT       ULONG_MAX
#define D3DMX_DEFAULT_FLOAT FLT_MAX

#include "d3dmxmath.h"
#include "d3dmxtex.h"

#endif //__D3DMX_H__
