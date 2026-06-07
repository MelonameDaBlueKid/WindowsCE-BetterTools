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

    File: MsgForm.cpp

    Purpose: CMsgForm class implementation

******************************************************************************/
#include "stdinc.h"
#include "form.h"
#include "msgform.h"
#include "msgview.h"


/******************************************************************************

    CMsgForm::CMsgForm - C'TOR
    
    Remarks:
    This class should only be instantiated by the CFormProvider object.

******************************************************************************/
CMsgForm::CMsgForm(IMessageFormHostEx* pHost, LPMESSAGE pMsg) :
m_cRef(1),
m_pHost(pHost),
m_pMsg(pMsg),
m_pView(NULL),
m_wType(0),
m_fDeleteOnClose(FALSE)
{
    //The host is Inbox.
    // Inbox created a message for us to fill already.
    if(NULL != m_pMsg)
    {
        m_pMsg->AddRef();
    }
}

/******************************************************************************

    CMsgForm::~CMsgForm - D'TOR

******************************************************************************/
CMsgForm::~CMsgForm()
{
    SAFE_RELEASE(m_pMsg);
    
    // The write view object is not a COM object. Nothing but the write form
    // references it, and the write form deletes the view on completion.
    SAFE_DELETE(m_pView);
}

/******************************************************************************

    CMsgForm::QueryInterface - Standard COM QueryInterface method.

    Params:
    iid[in] - specifies interface to retrieve
    ppvObject[in/out] - address to store the retrieved interface. Set to NULL 
                        if the interface requested is not supported.

    Returns:
    S_OK if the interface requested is available.
    MAPI_E_INTERFACE_NOT_SUPPORTED if the requested interface is not supported.
        Currently, only IUnknown and IFormProvider are supported.

    Remarks:
    Returns an AddRef()-ed reference to either the IUnknown interface or
    the IFormProvider interface, both of which are merely casts of the this
    pointer.  Querying for any other interface will result in a NULL
    ppvObject and a return value of E_NOINTERFACE.

******************************************************************************/
HRESULT CMsgForm::QueryInterface(REFIID iid, void** ppvObject)
{
    if(IID_IUnknown == iid)
    {
        *ppvObject = this;
    }
    else if(IID_IMessageFormEx == iid)
    {
        *ppvObject = reinterpret_cast<IMessageFormEx*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return(MAPI_E_INTERFACE_NOT_SUPPORTED);
    }

    //Increment the refcount and return success
    AddRef();
    return S_OK;
}

// **************************************************************************
// Function Name: AddRef
// 
// Purpose: Standard COM AddRef method.
//
// Arguments:
//    None.
//
// Return Values:
//    The new refcount on the object is returned.  This value is meant to be
//    used for diagnostic and testing purposes only.
//
// Side effects:  
//    The refcount will be incremented by 1.
// 
// Description:  
//    Increments the refcount by 1.
ULONG CMsgForm::AddRef()
{
    return InterlockedIncrement( (long*) &m_cRef );
}


/******************************************************************************

    CMsgForm::Release - Standard COM Release method.

    Params:
    None

    Returns:
    The new refcount on the object is returned.  This value is meant to be
    used for diagnostic and testing purposes only.

    Remarks:

******************************************************************************/
ULONG CMsgForm::Release()
{
    if(0 == InterlockedDecrement((long*)&m_cRef))
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

/******************************************************************************

    CMsgForm::CloseForm - IMessageForm::CloseForm implementation.

    Params:
    fSave[in] - Ignored

    Returns:
    S_OK

    Remarks:
    Allows the host or the view to close the form.

******************************************************************************/
HRESULT CMsgForm::CloseForm(BOOL fSave)
{
    m_pHost->FormClosing(this, m_pMsg, m_eMsgStatus);
    if(m_pView)
    {
        m_pView->OnClose();
    }
    return S_OK;
}

/******************************************************************************

    CMsgForm::SetMessage - IMessageForm::SetMessage implementation.
    
    Params:
    wType[in] - Form type (Read, Reply, Reply All, Forward).
    pMsg[in] - Message to initialize to.
    
    Returns:
    S_OK
    
    Remarks:
    Allows the host set or change the message for this form.
    
******************************************************************************/
HRESULT CMsgForm::SetMessage(WORD wType, LPMESSAGE pMsg)
{
    HRESULT hr = S_OK;

    CHP(pMsg);

    //Type is Read, Reply, Reply All, Forward.
    m_wType = wType;

    //Release any previously loaded form and store new one
    SAFE_RELEASE(m_pMsg);
    if((m_pMsg = pMsg) != NULL)
    {
        m_pMsg->AddRef();
    }
    
    //Pass up to view for updating
    if(m_pView)
    {
        m_pView->SetMessage(wType, pMsg);
    }

Exit:

    return S_OK;
}

/******************************************************************************

    CMsgForm::PreTranslateMsg - IMessageForm::PreTranslateMsg implementation.

    Params:
    pMsg[in] - Message from the message pump.
    pfProcessed[in/out] - Was the message processed?

    Returns:
    S_OK

    Remarks:
    Allows the form to process window messages pumped by the UI.  Currently
    al messages are just passed on to the view for it to process.

******************************************************************************/
HRESULT CMsgForm::PreTranslateMsg(MSG* pMsg, BOOL* pfProcessed)
{
    //Let view try to handle message first
    *pfProcessed = m_pView && m_pView->PreTranslateMsg(pMsg);

    if(!*pfProcessed) //View didn't handle it
    {
        switch(pMsg->message)
        {
            case WM_KEYDOWN:
                
                switch(pMsg->wParam)
                {
                    //We want the left and right keys to switch to the next/prev
                    //message, so pass that info to the host
                    case VK_TRIGHT:
                        RETAILMSG(TRUE, (_T("SDKEMS CMsgViewBase::PreTranslateMsg - VK_TRIGHT")));
                        m_pHost->DoAction(this, m_pMsg, IMessageFormHostEx::HOSTACT_GOTO_NEXT_MESSAGE, NULL);
                        break;
                    
                    case VK_TLEFT:
                        RETAILMSG(TRUE, (_T("SDKEMS CMsgViewBase::PreTranslateMsg - VK_TLEFT")));
                        m_pHost->DoAction(this, m_pMsg, IMessageFormHostEx::HOSTACT_GOTO_PREV_MESSAGE, NULL);
                        break;
                    
                    default:
                        RETAILMSG(TRUE, (_T("SDKEMS CMsgViewBase::PreTranslateMsg - WM_KEYDOWN...")));
                }
                break;

            default:
                return FALSE;
        }
    }
    return S_OK;
}

/******************************************************************************

    CMsgForm::GetMenuCapabilities - 

    Params:
    dwFlags[in] - Available flags to set/clear on the menu
    pdwEnable[in/out] - Set bits you want to enable only

    Returns:

    Remarks:

******************************************************************************/
HRESULT CMsgForm::GetMenuCapabilities(DWORD dwFlags, DWORD* pdwEnable)
{
    HRESULT hr = S_OK;

    //Disable all, we're not intrested in them for this sample
    *pdwEnable = 0;

    return hr;
}

/******************************************************************************

    CMsgForm::DoAction - 

    Params:
    actForm[] - 
    pfProcessed[in/out] - 

    Returns:

    Remarks:

******************************************************************************/
HRESULT CMsgForm::DoAction(FORMACTIONS actForm, DWORD dwValue, BOOL* pfProcessed) 
{
    /*
    Here we check if the form is closing, if so we need to clean up everything
    and notify the host to destroy the parent window
    */
    if(actForm == IMessageFormEx::FORMACT_POSTPONE)
    {
        m_pHost->DoAction(this, m_pMsg, IMessageFormHostEx::HOSTACT_CLOSE, NULL);
        CloseForm(FALSE);
        *pfProcessed = TRUE;
    }
    else
    if(actForm == IMessageFormEx::FORMACT_DELETE)
    {
        m_pHost->DoAction(this, m_pMsg, IMessageFormHostEx::HOSTACT_DELETE, NULL);
        CloseForm(FALSE);
        *pfProcessed = TRUE;
    }

    
    return S_OK;
}

/******************************************************************************

    CMsgForm::OnMessageModified - 

    Params:
    cbId[] - 
    pid[] - 
    props[] - 

    Returns:

    Remarks:

******************************************************************************/
HRESULT CMsgForm::OnMessageModified(ULONG cbId, 
                                    LPENTRYID pid, 
                                    LPSPropTagArray props)
{
    return S_OK;
}

/******************************************************************************

    CMsgForm::Init - Initialize the CMsgForm object

    Params:
    pFormProvider[in] - Form provider that created the form.
    hwndForm[in] - HWND of the form frame
    phwndBody[in/out] - HWND of the form-created body
    pMsgFields[in] - Message field flags

    Returns:

    Remarks:

******************************************************************************/
HRESULT CMsgForm::Init(CFormProvider* pFormProvider,
                       HWND hwndForm,
                       HWND* phwndBody,
                       MESSAGEFIELDS* pMsgFields)
{
    HRESULT hr;

    // We may need to delete the message if the user cancels later.
    if(pMsgFields)
    {
        m_fDeleteOnClose = pMsgFields->flags & MESSAGEFIELDS_FLAGS_DELETEONCLOSE;
    }
    
    m_eMsgStatus = (m_fDeleteOnClose)? IMessageFormHostEx::CMS_DELETE_PERMANENTLY : IMessageFormHostEx::CMS_NOT_AVAILABLE;
    
    //Create the view associated with this form.
    m_pView = new CMsgView(pFormProvider, this, m_pMsg);
    MAPI_EXIT_ON_NULL(m_pView);
    
    //Create the new view window, and prefill its fields if necessary.
    //Note that if it has already been created, the view will simply
    //show itself.
    if(!m_pView->Create(hwndForm, phwndBody))
    {
        RETAILMSG(TRUE, (_T("CMsgForm::Init - View Create failed\n")));
    }

    hr = m_pView->Init(pMsgFields);
        
    EXIT_ON_FAILED(hr);
   
Exit:
    // Everything worked ok.
    return hr;
}
