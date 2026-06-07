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

	File: EMSBase.cpp
    
    Purpose: Implement EMS processing base class

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