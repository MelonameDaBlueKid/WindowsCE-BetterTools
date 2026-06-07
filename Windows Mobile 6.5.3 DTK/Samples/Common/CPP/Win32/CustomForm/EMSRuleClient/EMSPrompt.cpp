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
/******************************************************************************

	File: EMSPrompt.cpp
    
    Purpose: Implement EMS processing for user propmt object

******************************************************************************/
#include "SDKEMSViewerRuleClient.h"

CEMSUserPrompt::CEMSUserPrompt(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_ulNumObjects(0)
{
}

/******************************************************************************

    - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
BOOL CEMSUserPrompt::ValidateData()
{
    return TRUE;
}

/******************************************************************************

    CEMSUserPrompt::ExtractInfoFromHeader - 

    Params:
    None

    Returns:
    TRUE if success, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSUserPrompt::ExtractInfoFromHeader()
{
    return TRUE;
}

/******************************************************************************

    CEMSUserPrompt::ToString - Convert to string that the custom form will 
        recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][NumObjects][Text Len][Text]

******************************************************************************/
BOOL CEMSUserPrompt::ToString(LPTSTR* ppszObjectData)
{
    return TRUE;
}
