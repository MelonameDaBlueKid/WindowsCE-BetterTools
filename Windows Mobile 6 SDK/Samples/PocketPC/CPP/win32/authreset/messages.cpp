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

#include "stdafx.h"

#include "messages.hpp"
#include "exception.hpp"

//  Implementation for the message map
//  that the sample ARC uses in ARCGetValue function
//

namespace
{
    //  Get a message from a specific table
    //
    CString GetMessageFromTable(DWORD id, mes::MessagePair const * table)
    {
        CString message;
        for (int i = 0; table[i].value; ++i)
        {
            if (table[i].value == id)
            {
                check_boolresult(message.LoadString(table[i].message));
                return message;
            }
        }

        return message;
    }
}

//  Get a message by its primary id
//
CString mes::GetMessage(DWORD primaryID)
{
    return GetMessageFromTable(primaryID, mes::startMessages);
}

//  Get a message by primary and secondary id
//
CString mes::GetMessage(DWORD primaryID, DWORD secondaryID)
{
    if (SUCCEEDED(secondaryID))
    {
        return GetMessageFromTable(primaryID, mes::okMessages);
    }
    else
    {
        CString genericMes = GetMessageFromTable(primaryID, mes::genericErrorMessages);
        CString specificMes = GetMessageFromTable(secondaryID, mes::errorMessages);

        if (specificMes.GetLength() == 0)
        {
            specificMes.LoadString(IDS_ERROR_UNEXPECTED);
        }

        return genericMes + L' ' + specificMes;
    }
}
