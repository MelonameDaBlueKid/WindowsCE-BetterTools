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

#include "stdafx.h"
#include "RuleClient.h"
#include "tvconsts.h"

extern HANDLE g_hInst;

CRuleClient::CRuleClient()
{
    m_cRef = 1;
}

CRuleClient::~CRuleClient()
{
}

HRESULT CRuleClient::QueryInterface(REFIID rif, void** ppobj)
{   
    HRESULT hr = E_NOINTERFACE;

    if (!ppobj)
    {
        return E_INVALIDARG;
    }

    *ppobj = NULL;
    if ((rif == IID_IUnknown) || (rif == IID_IMailRuleClient))
    {
        *ppobj = (IMailRuleClient *) this;
    }

    if (*ppobj) 
    {
        ((LPUNKNOWN) *ppobj)->AddRef();
        hr = S_OK;
    }

    return hr;
}

ULONG CRuleClient::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

ULONG CRuleClient::Release()
{
    int nLocal = InterlockedDecrement(&m_cRef);
    
    if (!nLocal) 
    {
        delete this; 
    }

    return nLocal; 
}

// **************************************************************************
// Function Name: Initialize
// 
// Purpose: Allows us to specify the type of access we want on this store
//
// Arguments:
//    IN IMsgStore* pMsgStore - Message store in question.
//    OUT MRCACCESS *pmaDesired - Desired access on this message store.
//
// Description:  
//    This is the entry point for the mail rule client, and allows us to specify the type of access
//    we want for incoming messages in the store.  Write access will have lower priority (e.g. be
//    run after) read-only access, but has the option of modifying the message.

HRESULT CRuleClient::Initialize(IMsgStore *pMsgStore, MRCACCESS *pmaDesired)
{
    // We want to change the message class, so we'll need write access
    UNREFERENCED_PARAMETER(pMsgStore);
    *pmaDesired = MRC_ACCESS_WRITE;
    return S_OK;
}

// **************************************************************************
// Function Name: ProcessMessage
// 
// Purpose: Allows us to process an incoming message
//
// Arguments:
//    IN IMsgStore* pMsgStore - Message store containing the message
//    IN ULONG cbMsg - size of lpMsg
//    IN LPENTRYID lpMsg - ENTRYID of the message
//    IN ULONG cbDestFolder - size of lpDestFolder
//    IN LPENTRYID lpDestFolder - ENTRYID of the final destination of this message
//    OUT ULONG *pulEventType - Combination of fnevObject* flags describing what we did with this message
//    OUT MRCHANDLED *pHandled - Whether we handled this message, and whether we want others to see it.
//
// Description:  
//    This function is called for each incoming message on the SMS store.  It is called before the message is 
//    displayed to the user.  We check the subject of the message, and if it matches what we're expecting, we'll
//    change the message class of the message.  This marks it as our own, and will cause our custom forms
//    to be loaded
HRESULT CRuleClient::ProcessMessage(IMsgStore *pMsgStore, ULONG cbMsg, LPENTRYID lpMsg, 
            ULONG cbDestFolder, LPENTRYID lpDestFolder, ULONG *pulEventType, MRCHANDLED *pHandled)
{
    HRESULT hr = E_FAIL;
    IMessage *pMsg = NULL;
    SPropValue rgProps[3];
    SizedSPropTagArray(1, spta) = { 1, PR_SUBJECT }; 
    ULONG cValues = 0;
    SPropValue *pspv = NULL;
    ULONG ulEventType = 0;
    MRCHANDLED mrc = MRC_NOT_HANDLED;
    
    // Validate input
    CBR(NULL != lpMsg);
    CBR(NULL != pMsgStore);
    CBR(NULL != pHandled);
    CBR(NULL != pulEventType);

    // Read in the subject of the message
    hr = pMsgStore->OpenEntry(cbMsg, lpMsg, NULL, 0, NULL, (LPUNKNOWN *) &pMsg);
    CHR(hr);
    
    //For SMS, the entire message is in the subject field
    hr = pMsg->GetProps((SPropTagArray *) &spta, MAPI_UNICODE, &cValues, &pspv);
    CHR(hr);
    
    // Check if this SMS message is a TV request
    if ((cValues != 1) || wcsncmp(pspv[0].Value.lpszW, kszTVSMS, wcslen(kszTVSMS)) != 0)
    {
        goto Exit;
    }

    // Now that the message has been identified as one of this game class,
    // handle it by changing its message class.

    // Change the message class on this message
    rgProps[0].ulPropTag   = PR_MESSAGE_CLASS;
    rgProps[0].Value.lpszW = (TCHAR*)&(kszTVMsgClass[0]);

    // Also change the subject (to get rid of the {TV} marker)
    rgProps[1].ulPropTag   = PR_SUBJECT;
    rgProps[1].Value.lpszW = (TCHAR*)&(pspv[0].Value.lpszW[4]);

    //HOTTIP: Here's how to make sure the user doesn't see a notification bubble:
    rgProps[2].ulPropTag   = PR_CE_NO_NOTIFICATION;
    rgProps[2].Value.b = TRUE;
    
    // Now set the new message properties
    hr = pMsg->SetProps(3, rgProps, NULL);
    CHR(hr);
    
    // Everything worked ok.
    // We don't want anyone else handling this message, and all we did was modify it
    mrc = MRC_HANDLED_DONTCONTINUE;
    ulEventType = fnevObjectModified;
    hr = S_OK;

Error:
Exit:
    *pHandled = mrc;
    *pulEventType = ulEventType;
    
    MAPIFreeBuffer(pspv);
    RELEASE_OBJ(pMsg);
    
    return hr;
}
