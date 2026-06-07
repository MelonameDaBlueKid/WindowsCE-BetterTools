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

#if !defined(AR_SUPPORT_H_82979792424)
#define AR_SUPPORT_H_82979792424

#include "authreset.h"

namespace arc
{
    //  Registry keys and values that LAP uses
    //  to support authentication reset.
    //
    __declspec(selectany) LPCTSTR
        AuthResetPolicyKey = L"Comm\\Security\\Policy\\LASSD\\AuthReset";
    __declspec(selectany) LPCTSTR
        AuthResetPolicyValue = L"AuthenticationReset";
    __declspec(selectany) LPCTSTR
        AuthResetKey = L"Comm\\Security\\LASSD\\AuthReset";
    __declspec(selectany) LPCTSTR
        AuthResetDllValue = L"Dll";
    __declspec(selectany) LPCTSTR
        AuthResetDataValue = L"Data";

    //  The state of the AR on the device
    enum ARState
    {
        INVALID = 0
      , ENABLED         // AR has been setup, AR request can be performed
      , DISABLED        // AR has not been setup
    };

    //  These are the high level methods that LAP uses
    //  to perform AR setup, request and check for AR status.

    HRESULT SetupAR(HWND parent, LPCTSTR passwd);
    HRESULT RequestAR(HWND parent);
    HRESULT CheckARState(arc::ARState & state);
}

#endif  // AR_SUPPORT_H_82979792424
