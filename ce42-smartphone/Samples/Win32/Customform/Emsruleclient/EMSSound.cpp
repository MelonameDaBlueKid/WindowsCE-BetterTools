/******************************************************************************

	File: EMSSound.cpp
    
    Purpose: Implement EMS processing for predefined and userdefined sounds

    Author: Matthew S. Baker (mbaker)

    Date: 11/9/2002

    Remarks:

******************************************************************************/
#include "SDKEMSViewerRuleClient.h"

/******************************************************************************

    CEMSPredefinedSound::CEMSPredefinedSound - C'TOR 

    Params:
    See base class

    Returns:
    Nothing

    Remarks:

******************************************************************************/
CEMSPredefinedSound::CEMSPredefinedSound(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_eSound(EMS_PREDEFINEDSOUND::EMSPS_CHIMESHIGH)
{
    //Initialize and chain to base class
}

/******************************************************************************

    CEMSPredefinedSound::ValidateData - 

    Params:
    None

    Returns:
    TRUE on success, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSPredefinedSound::ValidateData()
{
    return TRUE;
}

/******************************************************************************

    CEMSPredefinedSound::ExtractInfoFromHeader - 

    Params:
    None

    Returns:
    TRUE on success FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSPredefinedSound::ExtractInfoFromHeader()
{
    return TRUE;
}    

/******************************************************************************

    CEMSPredefinedSound::ToString - Convert to string that the custom form will 
        recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][Index][Text Len][Text]


******************************************************************************/
BOOL CEMSPredefinedSound::ToString(LPTSTR* ppszObjectData)
{
    return TRUE;
}

/******************************************************************************

    - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
CEMSUserdefinedSound::CEMSUserdefinedSound(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_lpiMelody(NULL),
m_cbiMelody(0)
{
}

/******************************************************************************

    - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
CEMSUserdefinedSound::~CEMSUserdefinedSound()
{
}

/******************************************************************************

    CEMSUserdefinedSound::ValidateData - 

    Params:
    None

    Returns:
    TRUE on success, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSUserdefinedSound::ValidateData()
{
    return TRUE;
}

/******************************************************************************

    - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
BOOL CEMSUserdefinedSound::ExtractInfoFromHeader()
{
    return TRUE;
}


/******************************************************************************

    CEMSUserdefinedSound::ToString - Convert to string that the custom form will 
        recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][iMelody][Text Len][Text]

******************************************************************************/
BOOL CEMSUserdefinedSound::ToString(LPTSTR* ppszObjectData)
{
    return TRUE;
}