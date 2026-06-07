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
//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//
//--------------------------------------------------------------------------;
//  File:       ddmm.h
//  Content:    Routines for using DirectDraw on a multimonitor system
//--------------------------------------------------------------------------;

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

typedef HRESULT (WINAPI * LPDIRECTDRAWENUMERATEEX)(LPDDENUMCALLBACKEX lpCallback, LPVOID lpContext, DWORD dwFlags);
typedef HRESULT (*PDRAWCREATE)(IID *,LPDIRECTDRAW *,LPUNKNOWN);
typedef HRESULT (*PDRAWENUM)(LPDDENUMCALLBACKEX, LPVOID);

IDirectDraw * DirectDrawCreateFromDevice(LPSTR, PDRAWCREATE, PDRAWENUM);
IDirectDraw * DirectDrawCreateFromDeviceEx(LPSTR, PDRAWCREATE, LPDIRECTDRAWENUMERATEEX);
INT_PTR DeviceFromWindow(HWND hwnd, LPSTR szDevice, RECT*prc);
HMONITOR OneMonitorFromWindow(HWND hwnd);

#ifdef __cplusplus
}
#endif	/* __cplusplus */
