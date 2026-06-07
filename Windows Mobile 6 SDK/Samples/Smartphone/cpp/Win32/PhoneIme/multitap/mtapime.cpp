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

// MtapIme.cpp : IME wrapper for input converter. 
//               CMTapIME class implemention.

#include "mtapime.h"
#include "mtapconv.h"
#include <winuserm.h>
#include <tpcshell.h>

// Create CIME
CIME* CreateIME(HINSTANCE hinst)
{
    CMTapIME *pMTapIme = new CMTapIME(hinst);

    return (CIME*)pMTapIme;
}

// Delete CIME
void DeleteIME(CIME* pime)
{
    if (pime)
    {
        delete (CMTapIME*)pime;
    }
}

// Init CIME
CMTapIME::CMTapIME(HINSTANCE hinst) :   // In: Instance handle
    CIME(hinst)
{
    if (m_pConverter)
    {
        ((CMTapConverter*)m_pConverter)->SetIME(this);
    }
}

