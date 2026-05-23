/******************************************************************************

	File: EMSAnimation.cpp
    
    Purpose: Implement EMS processing for predefined and userdefined animations

    Author: Matthew S. Baker (mbaker)

    Date: 11/9/2002

    Remarks:

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
m_eAnimation(EMS_PREDEFINEDANIM::EMSPA_IAMIRONICFLIRTY)
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
