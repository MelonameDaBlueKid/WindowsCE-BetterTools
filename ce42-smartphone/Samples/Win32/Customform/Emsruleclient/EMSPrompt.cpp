/******************************************************************************

	File: EMSPrompt.cpp
    
    Purpose: Implement EMS processing for user propmt object

    Author: Matthew S. Baker (mbaker)

    Date: 11/9/2002

    Remarks:

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
