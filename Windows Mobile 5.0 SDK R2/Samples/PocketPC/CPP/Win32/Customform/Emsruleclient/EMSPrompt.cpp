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
