/******************************************************************************

	File: EMSBase.cpp
    
    Purpose: Implement EMS processing base class

    Author: Matthew S. Baker (mbaker)

    Date: 11/9/2002

    Remarks:

******************************************************************************/
#include "SDKEMSViewerRuleClient.h"

/******************************************************************************

    CEMSBaseObject::CEMSBaseObject - C'TOR
    
    Params:
    lpData[in]       - Pointer to EMS header data
    cbData[in]       - Size of EMS header data in bytes
    ulBaseOffset[in] - For multipart EMS, this is how far we're into the text
                       overall, since each header only has knowledge of its user 
                       data
    szUserData[in]   - Text associated with SM.  This can be NULL.
    
    Returns:
    Nothing
    
    Remarks:
    
******************************************************************************/
CEMSBaseObject::CEMSBaseObject(LPBYTE lpData, 
                               ULONG cbData, 
                               ULONG ulBaseOffset, 
                               LPCTSTR szUserData) :
m_ulOffset(0),
m_cbData(0),
m_lpData(NULL),
m_szUserData(NULL),
m_fValidated(FALSE),    
m_fInitialized(FALSE)
{
    //validate params
    if((NULL != lpData) && (0 < cbData))
    {
        //allocate data buffer
        m_lpData = (LPBYTE)malloc(cbData);

        if(NULL != m_lpData)
        {
            m_ulOffset = ulBaseOffset;          //Save the base offset
            m_cbData = cbData;                  //Save data length
            memcpy(m_lpData, lpData, m_cbData); //copy the data buffer
            m_fInitialized = TRUE;              //Success

            //copy the user data if there is any
            if(NULL != szUserData)
            {
                m_szUserData = (LPTSTR)malloc((_tcslen(szUserData) + 1)*sizeof(TCHAR));
                
                __try
                {
                    _tcscpy(m_szUserData, szUserData);
                }
                __except(EXCEPTION_EXECUTE_HANDLER)
                {
                    m_fInitialized = FALSE; //OOM failure...
                }
            }
        }   
    }
}

/******************************************************************************

    CEMSBaseObject::~CEMSBaseObject - D'TOR, clean up memory allocations 

    Params:
    None

    Returns:
    Nothing

    Remarks:

******************************************************************************/
CEMSBaseObject::~CEMSBaseObject()
{
    //Free the data buffer
    if(m_lpData)
    {
        free(m_lpData);
    }
    //Free the user data
    if(m_szUserData)
    {
        free(m_szUserData);
    }
}