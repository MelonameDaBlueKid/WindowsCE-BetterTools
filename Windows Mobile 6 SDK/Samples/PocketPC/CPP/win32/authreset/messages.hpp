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

#if !defined(MESSAGES_HPP_24372934)
#define MESSAGES_HPP_24372934

#include "resourceppc.h"

namespace mes
{
//  This is a error code/message map that is used in ARCGetValue function

    struct MessagePair
    {
        DWORD value;
        DWORD message;
    };

    static MessagePair const startMessages[] = 
    {
        {AUTHRESET_VALUE_SETUP_MESSAGE,     IDS_SETUP},
        {AUTHRESET_VALUE_REQUEST_MESSAGE,   IDS_REQUEST},
        {0, 0}
    };

    struct MessagePair const okMessages[] =
    {
        {AUTHRESET_VALUE_SETUPRESULT_MESSAGE,   IDS_SETUP_RESULT_OK},
        {AUTHRESET_VALUE_REQUESTRESULT_MESSAGE, IDS_REQUEST_RESULT_OK},
        {0, 0}
    };

    struct MessagePair const genericErrorMessages[] =
    {
        {AUTHRESET_VALUE_SETUPRESULT_MESSAGE,   IDS_SETUP_ERROR_GENERIC},
        {AUTHRESET_VALUE_REQUESTRESULT_MESSAGE, IDS_REQUEST_ERROR_GENERIC},
        {0, 0}
    };

    struct MessagePair const errorMessages[] =
    {
        {(DWORD) E_ACCESSDENIED,                                IDS_ERROR_ACCESSDENIED},
        {(DWORD) E_ABORT,                                       IDS_ERROR_ABORT},
        {(DWORD) HRESULT_FROM_WIN32(ERROR_NO_NETWORK),          IDS_ERROR_NETWORK},
        {(DWORD) HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE),    IDS_ERROR_UNREACHABLE},
        {0, 0}
    };

    //  Get a message by its primary id
    CString GetMessage(DWORD primaryID);

    //  Get a message by primary and secondary id
    CString GetMessage(DWORD primaryID, DWORD secondaryID);
}

#endif  // MESSAGES_HPP_24372934
