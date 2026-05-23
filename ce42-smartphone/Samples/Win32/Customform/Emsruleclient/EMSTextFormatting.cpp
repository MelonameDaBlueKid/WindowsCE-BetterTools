/******************************************************************************

	File: EMSTextFormatting.cpp
    
    Purpose: Implement EMS processing for text formatting 

    Author: Matthew S. Baker (mbaker)

    Date: 11/9/2002

    Remarks:

******************************************************************************/
#include "SDKEMSViewerRuleClient.h"

/******************************************************************************

    CEMSTextFormatting::CEMSTextFormatting - C'TOR

    Params:
    Chain to base class, see CEMSBaseObject

    Returns:
    Nothing

    Remarks:

******************************************************************************/
CEMSTextFormatting::CEMSTextFormatting(LPBYTE lpData, 
                                       ULONG cbData, 
                                       ULONG ulBaseOffset, 
                                       LPCTSTR szUserData) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_chLen(0),
m_eAlignment(CEMSTextFormatting::EMSTF_ALIGN_LEFT),
m_eFontSize(CEMSTextFormatting::EMSTF_FONTSIZE_NORMAL),
m_fBold(FALSE),
m_fItalics(FALSE),
m_fUnderlined(FALSE),
m_fStrikethrough(FALSE),
m_ulBaseOffset(ulBaseOffset)
{
    //Initialize members and chain to base class...
}

/******************************************************************************

    CEMSTextFormatting::ValidateData - Attempt to validate the EMS data 

    Params:
    None

    Returns:
    TRUE if data is valid

    Remarks:

******************************************************************************/
BOOL CEMSTextFormatting::ValidateData()
{
    return TRUE;
}

/******************************************************************************

    CEMSTextFormatting::ExtractInfoFromHeader - Parse the EMS header data and 
        extract the relevant info for the text formatting object

    Params:
    None

    Returns:
    TRUE on success, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSTextFormatting::ExtractInfoFromHeader()
{
    return TRUE;
}

/******************************************************************************

    CEMSTextFormatting::ToString - Convert to string that the custom form will 
        recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][Format Len][Align][B][I][U][S][Text Len][Text]

******************************************************************************/
BOOL CEMSTextFormatting::ToString(LPTSTR* ppszObjectData)
{
    return TRUE;
}

