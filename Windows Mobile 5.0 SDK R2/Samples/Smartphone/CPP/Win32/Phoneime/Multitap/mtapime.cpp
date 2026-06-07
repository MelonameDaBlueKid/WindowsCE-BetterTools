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

