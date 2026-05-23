/******************************************************************************

	File: EMSPicture.cpp
    
    Purpose: Implement EMS processing for Picture objects

    Author: Matthew S. Baker (mbaker)

    Date: 11/9/2002

    Remarks:

******************************************************************************/
#include "SDKEMSViewerRuleClient.h"


/******************************************************************************

    CEMSPicture::CEMSPicture - C'TOR

    Params:
    Chain to base class, see CEMSBaseObject

    Returns:
    Nothing

    Remarks:

******************************************************************************/
CEMSPicture::CEMSPicture(LPBYTE lpData, ULONG cbData, ULONG ulBaseOffset, LPCTSTR szUserData, int iType) :
CEMSBaseObject(lpData, cbData, ulBaseOffset, szUserData),
m_lpPicData(NULL),
m_uHorzRes(32),
m_uVertRes(32),
m_ePicType((CEMSPicture::EMS_PICTURETYPE)iType)
{
    //Initialize and chain to base class
}

/******************************************************************************

    CEMSPicture::~CEMSPicture - D'TOR

    Params:
    None

    Returns:
    Nothing

    Remarks:
    Frees allocated data for picture pixels

******************************************************************************/
CEMSPicture::~CEMSPicture()
{
    if(m_lpPicData)
    {
        free(m_lpPicData);
    }
}

/******************************************************************************

    CEMSPicture::ValidateData - Attempts to validate picture object 

    Params:
    None

    Returns:
    TRUE if object appears valid, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CEMSPicture::ValidateData()
{
    BOOL bRet = TRUE;
    
    ASSERT(m_fInitialized);
    CBR((m_fInitialized), bRet);

    //Check if resolution matches type
    if(EMSPT_LARGE == m_ePicType)
    {
        CBR(((PICTURE_RES_LARGE == m_uHorzRes) && (PICTURE_RES_LARGE == m_uVertRes)), bRet);
    }
    else
    if(EMSPT_SMALL == m_ePicType)
    {
        CBR(((PICTURE_RES_SMALL == m_uHorzRes) && (PICTURE_RES_SMALL == m_uVertRes)), bRet);
    }

    //Variable could be any resolution...    

Exit:
    return bRet;
}

/******************************************************************************

    CEMSPicture::ExtractInfoFromHeader - 

    Params:

    Returns:

    Remarks:

******************************************************************************/
BOOL CEMSPicture::ExtractInfoFromHeader()
{
    BOOL bRet   = TRUE;
    UINT uIndex = 0;
    UINT uLast  = 0;

    ASSERT(m_lpData);
    ASSERT(m_cbData);
    ASSERT(m_fInitialized);

    CBR((m_fInitialized), bRet);

    __try
    {
        //First octet is the offset
        m_ulOffset += m_lpData[uIndex];
        uIndex++;

        if(EMSPT_LARGE == m_ePicType)
        {
            //Large picture
            m_uHorzRes = m_uVertRes = PICTURE_RES_LARGE;
        }
        else
        if(EMSPT_SMALL == m_ePicType)
        {
            //Small picture
            m_uHorzRes = m_uVertRes = PICTURE_RES_SMALL;
        }
        else
        {
            //Variable picture
            m_uHorzRes = m_lpData[uIndex] * 8;
            uIndex++;
            m_uVertRes = m_lpData[uIndex];
            uIndex++;                        
        }

        //The rest of the buffer should equal the bytes needed for the current resolution
        ASSERT((m_cbData - uIndex) == ((m_uHorzRes/8) * m_uVertRes));
        CBR((m_cbData - uIndex) == ((m_uHorzRes/8) * m_uVertRes), bRet);

        //Allocate the buffer for the picture
        m_lpPicData = (LPBYTE)malloc(m_cbData - uIndex);
        CBR((NULL != m_lpPicData), bRet);

        //Now read in the picture data
        memcpy(m_lpPicData, &m_lpData[uIndex], m_cbData - uIndex);        
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        bRet = FALSE;
    }

Exit:
    
    if(bRet)
    {
        //If everything's ok, we don't need the header info anymore
        if(m_lpData)
        {
            free(m_lpData);
        }
    }

    return bRet;
}

/******************************************************************************

    CEMSPicture::ToString - Convert to string that the custom form will 
        recognize

    Params:
    ppszObjectData[in/out] - pointer where string will be written
    
    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Format is - [ID][Offset][HorzRes][VertRes][Pixel Data(HxV)][Text Len][Text]

******************************************************************************/
BOOL CEMSPicture::ToString(LPTSTR* ppszObjectData)
{
    BOOL    bRet            = TRUE;
    UINT    uBufferLen      = 0;
    TCHAR   szBuffer[10]    = _T("");
    TCHAR*  pszBuffer       = szBuffer;
    UINT    uTemp           = 0x00;
    UINT    uIndex          = 0;
    UINT    uChar           = 0;
    
    ASSERT(ppszObjectData);
    CBR((NULL != ppszObjectData), bRet);

    //There isn't always text...
    
    //calculate the length of buffer needed
    uBufferLen = sizeof(TCHAR)*
        ( 2                                 //Text length 
        + 2                                 //Horz resolution
        + 2                                 //Vert resolution
        + (2*(m_uHorzRes/8 * m_uVertRes))   //Pixel data, two TCHARs per byte(8 pixels)
        + 2                                 //Offset
        + 2                                 //ID
        + 1);                               //NULL

    if(NULL != m_szUserData)
    {
        //Text string
        uBufferLen += sizeof(TCHAR)*(_tcslen(m_szUserData));
    }
    

    //Allocate buffer for string
    *ppszObjectData = (LPTSTR)malloc(uBufferLen);
    
    //Check for OOM
    CBR((NULL != *ppszObjectData), bRet);

    //Clear the buffer
    ZeroMemory(*ppszObjectData, uBufferLen);

    //Convert and write the object ID
    if(EMSPT_LARGE == m_ePicType)
    {
        uTemp = IEI_LARGE_PICTURE;
    }
    else
    if(EMSPT_SMALL == m_ePicType)
    {
        uTemp = IEI_SMALL_PICTURE;
    }
    else
    if(EMSPT_VARIABLE == m_ePicType)
    {
        uTemp = IEI_VARIABLE_PICTURE;
    }
    szBuffer[0] = _T('0');
    uChar = (uTemp < 0x10) ? 1 : 0;
    _itot(uTemp, &(szBuffer[uChar]), BASE_HEX);
    _tcscat(*ppszObjectData, szBuffer);
    
    //Write the offset
    szBuffer[0] = _T('0');
    uChar = (m_ulOffset < 0x10) ? 1 : 0;
    _itot(m_ulOffset, &(szBuffer[uChar]), BASE_HEX);
    _tcscat(*ppszObjectData, szBuffer);
    
    //Write the horizontal resoultion
    szBuffer[0] = _T('0');
    uChar = (m_uHorzRes < 0x10) ? 1 : 0;
    _itot(m_uHorzRes, &(szBuffer[uChar]), BASE_HEX);
    _tcscat(*ppszObjectData, szBuffer);
    
    //Write the vertical resoultion
    szBuffer[0] = _T('0');
    uChar = (m_uVertRes < 0x10) ? 1 : 0;
    _itot(m_uVertRes, &(szBuffer[uChar]), BASE_HEX);
    _tcscat(*ppszObjectData, szBuffer);
    
    //write out the pixel data
    uTemp = m_uHorzRes/8 * m_uVertRes;
    for(uIndex = 0; uIndex < uTemp; uIndex++)
    {
        szBuffer[0] = _T('0');
        uChar = (m_lpPicData[uIndex] < 0x10) ? 1 : 0;
        _itot(m_lpPicData[uIndex], &(szBuffer[uChar]), BASE_HEX);
        _tcscat(*ppszObjectData, szBuffer);
    }

    if(NULL != m_szUserData)
    {
        //Write the text length
        szBuffer[0] = _T('0');
        uChar = ((_tcslen(m_szUserData) + 1) < 0x10) ? 1 : 0;
        _itot((_tcslen(m_szUserData) + 1), &(szBuffer[uChar]), BASE_HEX);
        _tcscat(*ppszObjectData, szBuffer);
    
        //Write the text
        _tcscat(*ppszObjectData, m_szUserData);
    }
    else
    {
        //Write the text length
        szBuffer[0] = _T('0');
        _itot(0, &(szBuffer[1]), BASE_HEX);
        _tcscat(*ppszObjectData, szBuffer);
    }

    //This gets truncated for some reason???
    DEBUGMSG(TRUE, (_T("CEMSPicture::ToString - %s"), *ppszObjectData));
    

Exit:
    return bRet;
}

