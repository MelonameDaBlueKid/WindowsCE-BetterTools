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

#ifndef __MTAPIME_H__
#define __MTAPIME_H__

#include "..\phoneime.h"

class CMTapConverter;

// IME
class CMTapIME : public CIME
{
public:
    CMTapIME(HINSTANCE hinst);
    ~CMTapIME() {};
    
    CMTapConverter* GetMTapConverter() { return (CMTapConverter*)m_pConverter; }
};

#endif //__MTAPIME_H__
