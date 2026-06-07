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
// ************************************************************
// utils.h
//
// ************************************************************


// ************************************************************
//
// Error-handling macros
//
// ************************************************************

// Check HRESULT
#define CHR(hResult)\
    do {hr = (hResult); if(FAILED(hr)) goto Error;} while (0,0)

// Check boolean result
#define CBR(e)\
    do {if (!(e)) {hr = E_FAIL; goto Error;} } while (0,0)


// ************************************************************
//
// Resource ID
//
// ************************************************************

#define IDS_PROVXML     1


