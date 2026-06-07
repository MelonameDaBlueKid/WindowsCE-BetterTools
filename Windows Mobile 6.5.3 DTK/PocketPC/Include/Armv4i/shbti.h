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
/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    shbti.h

Abstract:

    Shell bubble tile extra structure.

--*/

#pragma once

// Struct used to extend SHNOTIFICATIONDATA and SH_BOXEX to allow for
// bubble tile information to passed into notification, bubbles, and
// toasts.
typedef struct _SHBUBBLETILEINFO
{
    HINSTANCE hinstBmp;                      // HINSTANCE for the bubble tile toolbar image 
    int       nBmpId;                        // ID in the resource for the bubble tile toolbar
    int       cBmpImages;                    // Count of images 
    UINT      uIDButton1;                    // Offset into nBmpId for image for Button1.
    UINT      uIDButton2;                    // Offset into nBmpId for image for Button2.
    LPCTSTR   pszButton1;                    // Text of Button1. Default is NULL.
    LPCTSTR   pszButton2;                    // Text of Button2. Default is NULL.
    int       nToolBarId;                    // The bubble tile toolbar id.
} SHBUBBLETILEINFO, *PSHBUBBLETILEINFO;
