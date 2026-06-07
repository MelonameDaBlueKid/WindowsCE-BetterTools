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

	File: EMSAnimation.cpp
    
    Purpose: Implement EMS processing for predefined and userdefined animations

******************************************************************************/
#include "SDKEMSViewerRuleClient.h"

/******************************************************************************

    CEMSPredefinedAnimation::CEMSPredefinedAnimation - C'TOR 

    Params:
    See base class

    Returns:
    Nothing

    Remarks:

******************************************************************************/
CEMSPredefinedAnimation::CEMSPredefinedAnimation(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_eAnimation(EMSPA_IAMIRONICFLIRTY)
{
    //Initialize and chain to base class
}

/******************************************************************************

    CEMSPredefinedAnimation::ValidateData - 

    Params:
    None

    Returns:
    TRUE on success, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSPredefinedAnimation::ValidateData()
{
    return TRUE;
}

/******************************************************************************

    CEMSPredefinedAnimation::ExtractInfoFromHeader - 

    Params:
    None

    Returns:
    TRUE on success FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSPredefinedAnimation::ExtractInfoFromHeader()
{
    return TRUE;
}    

/******************************************************************************

    CEMSPredefinedAnimation::ToString - Convert to string that the custom form 
        will recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][Index][Text Len][Text]


******************************************************************************/
BOOL CEMSPredefinedAnimation::ToString(LPTSTR* ppszObjectData)
{
    return TRUE;
}

/******************************************************************************

    CEMSAnimation::CEMSAnimation - C'TOR

    Params:
    See base class

    Returns:
    Nothing

    Remarks:

******************************************************************************/
CEMSAnimation::CEMSAnimation(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData, int iType) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_uRes(0)
{
}

/******************************************************************************

    - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
CEMSAnimation::~CEMSAnimation()
{
}

/******************************************************************************

    CEMSAnimation::ValidateData - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
BOOL CEMSAnimation::ValidateData()
{
    return TRUE;
}

/******************************************************************************

    CEMSAnimation::ExtractInfoFromHeader -  

    Params:
    None

    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    

******************************************************************************/
BOOL CEMSAnimation::ExtractInfoFromHeader()
{
    return TRUE;
}

/******************************************************************************

    CEMSAnimation::ToString - Convert to string that the custom form will 
        recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][Frame1][Frame2][Frame3][Frame4][Text Len][Text] 
    
******************************************************************************/
BOOL CEMSAnimation::ToString(LPTSTR* ppszObjectData)
{
    return TRUE;
}
