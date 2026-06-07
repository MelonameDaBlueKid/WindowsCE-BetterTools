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
#include "tvconsts.h"
#include "forms.h"
#include "msgview.h"

// **************************************************************************
// Function Name: FormFactoryEx
// 
// Purpose: Entrypoint for the Inbox application to use to create forms.
//
// Arguments:
//    IN LPCWSTR pszMsgClass - specifies message class for forms
//    IN OUT IFormProviderEx** ppvObject - address to store the retrieved
//          interface.  Set to NULL if the incoming parameters are valid but
//          the object could not be created.  Not touched if the incoming
//          parameters are invalid.
//
// Return Values:
//    S_OK if the object implementing the interface requested is available
//          and created.
//    MAPI_E_INVALID_PARAMETER if one or both of the incoming parameters
//          is NULL.
//    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
//
// Side effects:  
//    A CFormProvider object is created.
// 
// Description:  
//    This is the entrypoint in the DLL that the Inbox application will look
//    for in order to retrieve an IFormProviderEx interface.  This interface
//    provides two methods that the app will use to create message forms,
//    CreateComposeForm() and CreateReadForm(), as well as a method to
//    retrieve the index of the image to be used in the application's
//    listview for this type of message, GetMsgStatusIconIndex().
HRESULT WINAPI FormFactoryEx(
    LPCWSTR pszMsgClass,
    IFormProviderEx** ppvObject)
{
    HRESULT hr;

    // Validate input
    ASSERT(NULL != pszMsgClass);
    ASSERT(NULL != ppvObject);
    if (NULL == pszMsgClass ||
        NULL == ppvObject)
    {
        DEBUGMSG(1, (TEXT("FormFactoryEx::Invalid argument\n")));
        return MAPI_E_INVALID_PARAMETER;
    }

    // Create the new CFormProvider object to hand back to the application.
    *ppvObject = new CFormProvider;
    if (NULL == *ppvObject)
    {
        DEBUGMSG(1, (TEXT("FormFactoryEx::Out of Memory\n")));
        return MAPI_E_NOT_ENOUGH_MEMORY;
    }

    // Now take any action required to use the provider.
    hr = ((CFormProvider*)(*ppvObject))->Init(pszMsgClass);
    if(FAILED(hr))
    {
        // Free up anything on failure.
        DEBUGMSG(1, (TEXT("FormFactoryEx::Init failed %x\n"), hr));
        delete *ppvObject;
        *ppvObject = NULL;
    }

    return hr;
}


// **************************************************************************
// Function Name: CFormProvider constructor
// 
// Purpose: Constructor initialization for the CFormProvider object.
//
// Arguments:
//    None.
//
// Return Values:
//    None.
//
// Side effects:  
//    None.
// 
// Description:  
//    Initializes the CFormProvider object.  The refcount is initialized to 1
//    to reflect the reference held by the code that created it via a new().
CFormProvider::CFormProvider() :
    m_cRef(1),
    m_pMsg(NULL),
    m_pMsgStore(NULL),
    m_pSession(NULL),
    m_pszMessageClass(NULL)
{
}


// **************************************************************************
// Function Name: ~CFormProvider destructor
// 
// Purpose: Destructor deinitialization for the CFormProvider object.
//
// Arguments:
//    None.
//
// Return Values:
//    None.
//
// Side effects:  
//    None.
// 
// Description:  
//    Deinitializes the CFormProvider object.  All member variables are
//    released and cleared, and all memory allocated is freed.
CFormProvider::~CFormProvider()
{
    RELEASE_OBJ(m_pMsg);
    RELEASE_OBJ(m_pMsgStore);
    RELEASE_OBJ(m_pSession);
    delete [] m_pszMessageClass;
}





// **************************************************************************
//
// CFormProvider - IFormProviderEx implementation
//
// **************************************************************************


// **************************************************************************
// Function Name: QueryInterface
// 
// Purpose: Standard COM QueryInterface method.
//
// Arguments:
//    IN REFIID iid - specifies interface to retrieve
//    IN OUT void** ppvObject - address to store the retrieved interface.
//          Set to NULL if the interface requested is not supported.
//
// Return Values:
//    S_OK if the interface requested is available.
//    MAPI_E_INTERFACE_NOT_SUPPORTED if the requested interface is not
//          supported.  Currently, only IUnknown and IFormProviderEx are
//          supported.
//
// Side effects:  
//    On a successful query, the refcount will be incremented by 1.
// 
// Description:  
//    Returns an AddRef()-ed reference to either the IUnknown interface or
//    the IFormProviderEx interface, both of which are merely casts of the this
//    pointer.  Querying for any other interface will result in a NULL
//    ppvObject and a return value of E_NOINTERFACE.
HRESULT CFormProvider::QueryInterface(
    REFIID iid,
    void** ppvObject)
{
    // Any interface on this object is the object pointer
    if( iid == IID_IUnknown )
    {
        *ppvObject = (IFormProviderEx*) this;
    }
    else if( iid == IID_IFormProviderEx )
    {
        *ppvObject = (IFormProviderEx*) this;
    }
    else
    {
        *ppvObject = NULL;
        return(MAPI_E_INTERFACE_NOT_SUPPORTED);
    }

    // Increment the refcount and return success
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
ULONG CFormProvider::AddRef()
{
    return InterlockedIncrement( (long*) &m_cRef );
}


// **************************************************************************
// Function Name: Release
// 
// Purpose: Standard COM Release method.
//
// Arguments:
//    None.
//
// Return Values:
//    The new refcount on the object is returned.  This value is meant to be
//    used for diagnostic and testing purposes only.
//
// Side effects:  
//    The refcount will be decremented by 1.  If the resulting refcount is 0,
//    the destructor for the object will be called.
// 
// Description:  
//    Decrements the refcount by 1.
ULONG CFormProvider::Release()
{
    if ( InterlockedDecrement( (long*) &m_cRef ) == 0 )
    {
        delete this;
        return 0;
    }
    return m_cRef;
}


// **************************************************************************
// Function Name: GetMsgStatusIconIndex
// 
// Purpose: IFormProviderEx::GetMsgStatusIconIndex implementation.
//
// Arguments:
//    IN LPMAPIFOLDER - ignored
//    IN LPENTRYID - ignored
//    IN ULONG - ignored
//    IN ULONG - ignored
//    IN ULONG - ignored
//    IN LPCWSTR - ignored
//    IN ULONG - ignored
//    IN OUT ULONG* pnIndex - image index to use for the message icon
//
// Return Values:
//    S_OK is always returned when pnIndex is non-NULL.
//    MAPI_E_INVALID_PARAMETER is returned when pnIndex is NULL.
//
// Side effects:  
//    None.
// 
// Description:  
//    Returns the image index to use for the message icon.  Currently, only
//    0 is returned, which indicates the standard unread normal message icon
//    index.
HRESULT CFormProvider::GetMsgStatusIconIndex(
    LPMAPIFOLDER /*pfldr*/,
    LPENTRYID /*pid*/,
    ULONG /*cbId*/,
    ULONG ffFlags,
    ULONG /*ffStatus*/,
    LPCWSTR /*pszMsgClass*/,
    ULONG /*cAttachments*/,
    ULONG* pnIndex)
{
    HRESULT hr = S_OK;

    // Validate input
    CBR(NULL != pnIndex);
    
    // Start off with Unread normal message.
    *pnIndex = 1;

    if ( ffFlags & MSGFLAG_READ )
    {
        *pnIndex = 0;
    }

Error:
    return hr;
}


// **************************************************************************
// Function Name: CreateComposeForm
// 
// Purpose: IFormProviderEx::CreateComposeForm implementation.
//
// Arguments:
//    IN IMessageFormHostEx* pHost - Interface for the Inbox application.
//    IN LPMESSAGE pMsg - Interface of message to be composed.
//    IN FORMTYPE eFormType - Form type (Read, Reply, Reply All, Forward)
//    IN LPMESSAGE pMsgBase - Base message for pMsg
//    IN MESSAGEFIELDS*  pMsgFields - Message field flags
//    IN HWND hwndForm - HWND of the form frame
//    IN OUT HWND* phwndBody - HWND of the form-created body
//    IN OUT IMessageFormEx** ppForm - Interface of compose form for created.
//
// Return Values:
//    S_OK if the compose form was successfully created.
//    MAPI_E_INVALID_PARAMETER if ppForm is NULL.
//    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
//    E_FAIL if any other error occurs.
//
// Side effects:
//    None.
// 
// Description:  
//    Creates a compose message form and returns an interface to that form's
//    IMessageForm interface to the caller.
HRESULT CFormProvider::CreateComposeForm(
    IMessageFormHostEx* pHost, 
    LPMESSAGE       pMsg,       // Object to compose
    FORMTYPE        eFormType,  // Reply, Reply All, Forward
    LPMESSAGE       pMsgBase,   // Message to prefill the form if necessary
    MESSAGEFIELDS*  pMsgFields, // message fields for the new message
    HWND            hwndForm,   // HWND of the form frame
    HWND*           phwndBody,  // HWND of the form-created body
    IMessageFormEx**  ppForm    // Form object
)
{
    HRESULT hr = S_OK;
    CMsgForm* pForm = NULL;

    // Validate input
    CBR(NULL != ppForm);
    *ppForm = NULL;

    // Create the form used to compose a new message.
    pForm = new CMsgForm(pHost, pMsg, TRUE);
    CPR(pForm);
    
    // Let the form know if we'll be prefilling with an existing message's data.
    hr = pForm->SetMessage(eFormType, pMsgBase);
    CHR(hr);
    
    // Now initialize the form.
    hr = pForm->Init(this, hwndForm, phwndBody, pMsgFields);
    CHR(hr);

    // Everything worked ok.
    *ppForm = pForm;

Error:

    if (FAILED(hr) && pForm)
    {
        pForm->Release();
    }

    return hr;
}


// **************************************************************************
// Function Name: CreateReadForm
// 
// Purpose: IFormProviderEx::CreateReadForm implementation.
//
// Arguments:
//    IN IMessageFormHostEx* pHost - Interface for the Inbox application.
//    IN LPMESSAGE pMsg - Message to fill the form.
//    IN HWND hwndForm - HWND of the form frame
//    IN OUT HWND* phwndBody - HWND of the form-created body
//    IN OUT IMessageFormEx** ppForm - Interface of read form for created.
//
// Return Values:
//    S_OK if the read form was successfully created.
//    MAPI_E_INVALID_PARAMETER if ppForm is NULL.
//    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
//    Also, any valid return value from MAPILogonEx(), OpenMsgStore(), or
//    GetIDsFromNames() may be returned if one of those calls fails.
//
// Side effects:
//    Can send a reply message.
// 
// Description:  
//    Creates a read message form and returns an interface to that form's
//    IMessageForm interface to the caller.
//
HRESULT CFormProvider::CreateReadForm(
    IMessageFormHostEx* pHost,
    LPMESSAGE       pMsg,       // Object to compose
    HWND            hwndForm,   // HWND of the form frame
    HWND*           phwndBody,  // HWND of the form-created body
    IMessageFormEx**  ppForm    // Form object
)
{
    HRESULT             hr              = S_OK;
    ULONG               cItems          = 0;
    LPSPropValue        pid             = NULL;
    LPMAPIFOLDER        pDraftsFldr     = NULL;
    FORMFACTORYEXFUNC   fnFactoryEx     = NULL;
    HWND                hWndChild       = NULL;
    LPTSTR              lpszWndName     = NULL;
    CMsgForm        *   pForm           = NULL;

    ULONG               rgDraftsFoldertags[] = { 0, PR_CE_IPM_DRAFTS_ENTRYID };

    // For finding the class of the base msg for the form.
    LPSPropValue rgetProps  = NULL;
    ULONG        cValues    = 0;

    MESSAGEFIELDS msgFields = {0};

    // Validate input
    CBR (pMsg != NULL);
    CBR (NULL != ppForm);
    *ppForm = NULL;
    
    // Clean up any other previous sessions
    CleanUpReadForm();

    // Inbox cleans up this new, when the form calls CloseForm.  This is
    // done whenever the user quits, sends, replies, or deletes a form.
    pForm = new CMsgForm(pHost, pMsg, FALSE);
    CPR(pForm);
    
    // Let the form know if we'll be prefilling with an existing message's data.
    hr = pForm->SetMessage(0, pMsg);
    CHR(hr);
    
    msgFields.flags |= MESSAGEFIELDS_FLAGS_DELETEONCLOSE;
    msgFields.flags |= MESSAGEFIELDS_FLAGS_SMSSERVICE;

    // Now initialize the form.
    hr = pForm->Init(this, hwndForm, phwndBody, &msgFields);
    CHR(hr);
    
    // Everything worked ok.
    *ppForm = pForm;

Error:

    if (pid)
    {
        MAPIFreeBuffer(pid);
    }

    if (rgetProps)
    {
        MAPIFreeBuffer(rgetProps);
    }

    return hr;
}





// **************************************************************************
//
// CFormProvider - utility member methods
//
// **************************************************************************


// **************************************************************************
// Function Name: Init
// 
// Purpose: Initialize the CFormProvider object
//
// Arguments:
//    IN LPCWSTR pszMsgClass - Message class for this form.
//
// Return Values:
//    S_OK if the initialization completes successfully.
//    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
//    Also, any valid return value from MAPILogonEx(), OpenMsgStore(), or
//    GetIDsFromNames() may be returned if one of those calls fails.
//
// Side effects:
//    None.
// 
// Description:  
//    Initializes the CFormProvider object, caching off the message class and
//    optionally initializing the property tags for .
HRESULT WINAPI CFormProvider::Init(LPCWSTR pszMsgClass)
{
    int cchMsgClass = 0;

    // It's possible that the same dll will be used to handle multiple message types,
    // (eg note.dll may be used to read/compose both e-mail and SMS messages). We'll
    // need to know later in the calls to instances of the form provider, what class 
    // of message that instance handles. So store the message class for the message 
    // here, to examine it later where necessary.
    // The only place this is called is from FormFactoryEx(), which has already
    // aborted if pszMsgClass was NULL.
    ASSERT (NULL != pszMsgClass);
    ASSERT (m_pszMessageClass == NULL);

    cchMsgClass = lstrlen(pszMsgClass) + 1;

    if ((m_pszMessageClass = new WCHAR[cchMsgClass]) == NULL)
    {
        DEBUGMSG(1, (TEXT("CFormProvider::Init Out of memory\n")));
        return MAPI_E_NOT_ENOUGH_MEMORY;
    }
    
    StringCchCopy(m_pszMessageClass, cchMsgClass, pszMsgClass);

    return S_OK;
}


// **************************************************************************
// Function Name: CleanUpReadForm
// 
// Purpose: Do cleanup of any already-open read form handles.
//
// Arguments:
//    None.
//
// Return Values:
//    S_OK is always returned
//
// Side effects:
//    All MAPI handles are released.
// 
// Description:  
//    Releases the reference held on the message, message store, and MAPI
//    session.
HRESULT CFormProvider::CleanUpReadForm()
{
    // Release the message and message store
    RELEASE_OBJ(m_pMsg);
    RELEASE_OBJ(m_pMsgStore);
    
    // Release session object last
    RELEASE_OBJ(m_pSession);

    return S_OK;
}



// **************************************************************************
// Function Name: CMsgForm constructor
// 
// Purpose: Constructor initialization for the CMsgForm object.
//
// Arguments:
//    None.
//
// Return Values:
//    None.
//
// Side effects:  
//    None.
// 
// Description:  
//    Initializes the CMsgForm object.  The refcount is initialized to 1
//    to reflect the reference held by the code that created it via a new().
CMsgForm::CMsgForm(
    IMessageFormHostEx* pHost,
    LPMESSAGE pMsg,
    BOOL fCompose) :
    m_cRef(1),
    m_pHost(pHost),
    m_pMsg(pMsg),
    m_wType(0),
    m_pMsgBase(NULL),
    m_pView(NULL),
    m_fCompose(fCompose)

{
    // Inbox created a message for us to fill already.
    if (NULL != m_pMsg)
    {
        m_pMsg->AddRef();
    }
}


// **************************************************************************
// Function Name: ~CMsgForm destructor
// 
// Purpose: Destructor deinitialization for the CMsgForm object.
//
// Arguments:
//    None.
//
// Return Values:
//    None.
//
// Side effects:  
//    None.
// 
// Description:  
//    Deinitializes the CMsgForm object.  All member variables are
//    released and cleared, and all memory allocated is freed.
CMsgForm::~CMsgForm()
{
    RELEASE_OBJ(m_pMsg);
}

// **************************************************************************
// Function Name: QueryInterface
// 
// Purpose: Standard COM QueryInterface method.
//
// Arguments:
//    IN REFIID iid - specifies interface to retrieve
//    IN OUT void** ppvObject - address to store the retrieved interface.
//          Set to NULL if the interface requested is not supported.
//
// Return Values:
//    S_OK if the interface requested is available.
//    MAPI_E_INTERFACE_NOT_SUPPORTED if the requested interface is not
//          supported.  Currently, only IUnknown and IFormProvider are
//          supported.
//
// Side effects:  
//    On a successful query, the refcount will be incremented by 1.
// 
// Description:  
//    Returns an AddRef()-ed reference to either the IUnknown interface or
//    the IFormProvider interface, both of which are merely casts of the this
//    pointer.  Querying for any other interface will result in a NULL
//    ppvObject and a return value of E_NOINTERFACE.
HRESULT CMsgForm::QueryInterface(
    REFIID iid,
    void** ppvObject)
{
    // Any interface on this object is the object pointer
    if( iid == IID_IUnknown )
    {
        *ppvObject = this;
    }
    else if( iid == IID_IMessageFormEx )
    {
        *ppvObject = (IMessageFormEx*) this;
    }
    else
    {
        *ppvObject = NULL;
        return(MAPI_E_INTERFACE_NOT_SUPPORTED);
    }

    // Increment the refcount and return success
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


// **************************************************************************
// Function Name: Release
// 
// Purpose: Standard COM Release method.
//
// Arguments:
//    None.
//
// Return Values:
//    The new refcount on the object is returned.  This value is meant to be
//    used for diagnostic and testing purposes only.
//
// Side effects:  
//    The refcount will be decremented by 1.  If the resulting refcount is 0,
//    the destructor for the object will be called.
// 
// Description:  
//    Decrements the refcount by 1.
ULONG CMsgForm::Release()
{
    if ( InterlockedDecrement( (long*) &m_cRef ) == 0 )
    {
        delete this;
        return 0;
    }
    return m_cRef;
}


// **************************************************************************
// Function Name: CloseForm
// 
// Purpose: IMessageForm::CloseForm implementation.
//
// Arguments:
//    IN BOOL fSave = FALSE - Not used
//
// Return Values:
//    S_OK is always returned.
//
// Side effects:
//    None.
// 
// Description:  
//    Allows the host or the view to close the form.
HRESULT CMsgForm::CloseForm(
    BOOL fSave)
{
    // Now tell the host that the form is being closed down, in case it wasn't
    // the host that initiated the close. It doesn't matter if we tell the host 
    // and it already knows. If the host had AddRef's this form, then it will
    // Release it beneath this.
    m_pHost->FormClosing(this, m_pMsg, m_eMsgStatus);
    SendMessage(m_hwndParent, WM_CLOSE, 0, 0);
    return S_OK;
}


// **************************************************************************
// Function Name: SetMessage
// 
// Purpose: IMessageForm::SetMessage implementation.
//
// Arguments:
//    IN WORD wType - Form type (Read, Reply, Reply All, Forward).
//    IN LPMESSAGE pMsg - Message to initialize to.
//
// Return Values:
//    S_OK is always returned.
//
// Side effects:
//    None.
// 
// Description:  
//    Allows the host set or change the message for this form.
HRESULT CMsgForm::SetMessage(
    WORD wType,
    LPMESSAGE pMsg)
{
    HRESULT hr = S_OK;

    // Type is Read, Reply, Reply All, Forward.
    m_wType = wType;

    if (NULL != pMsg)
    {
        pMsg->AddRef();
    }

    // If we have a message already loaded in the form, we're done with it now.
    RELEASE_OBJ(m_pMsgBase);
    
    // Now store the new message to be loaded in the form.
    m_pMsgBase = pMsg;

    // Pass the notification on up to the view for it to update as well.
    if (m_pView)
    {
        m_pView->SetMessage(wType, pMsg);
    }

    return hr;
}


// **************************************************************************
// Function Name: PreTranslateMsg
// 
// Purpose: IMessageForm::PreTranslateMsg implementation.
//
// Arguments:
//    IN MSG* pMsg - Message from the message pump.
//    IN OUT BOOL* pfProcessed - Was the message processed?
//
// Return Values:
//    S_OK is always returned.
//
// Side effects:
//    None.
// 
// Description:  
//    Allows the form to process window messages pumped by the UI.  Currently
//    al messages are just passed on to the view for it to process.
HRESULT CMsgForm::PreTranslateMsg(
    MSG* pMsg,
    BOOL* pfProcessed)
{
    *pfProcessed = m_pView && m_pView->PreTranslateMsg(pMsg);

    return S_OK;
}

HRESULT CMsgForm::DoAction(FORMACTIONS actForm, DWORD dwValue, BOOL* pfProcessed)
{
    switch (actForm)
    {
        case FORMACT_POSTPONE:
        {
            CloseForm();
            break;
        }

        case FORMACT_DELETE:
        {
            m_pHost->DoAction(this, m_pMsg, IMessageFormHostEx::HOSTACT_DELETE, NULL);
            break;
        }

        case FORMACT_REPLY:
        {
            m_pHost->DoAction(this, m_pMsg, IMessageFormHostEx::HOSTACT_FORWARD, NULL);
            break;
        }
    }

    return S_OK;    
}

HRESULT CMsgForm::GetMenuCapabilities(DWORD dwFlags, DWORD* pdwEnable)
{
    *pdwEnable = (MESSAGEFORMHOST2_CMDBARCAP_REPLY & dwFlags); 
    return S_OK;
}


// **************************************************************************
//
// CMsgForm - utility member methods
//
// **************************************************************************


// **************************************************************************
// Function Name: Init
// 
// Purpose: Initialize the CMsgForm object
//
// Arguments:
//    IN CFormProvider* pFormProvider - Form provider that created the form.
//    IN HWND hwndForm - HWND of the form frame
//    IN OUT HWND* phwndBody - HWND of the form-created body
//    IN MESSAGEFIELDS* pMsgFields - Message field flags
//
// Return Values:
//    S_OK if the initialization completes successfully.
//    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
//
// Side effects:
//    None.
// 
// Description:  
//    Initializes the CMsgForm object, caching off the message class and
//    optionally initializing the property tags for .
HRESULT CMsgForm::Init(
    CFormProvider* pFormProvider,
    HWND            hwndForm,   // HWND of the form frame
    HWND*           phwndBody,  // HWND of the form-created body
    MESSAGEFIELDS*  pMsgFields)
{
    HRESULT hr = S_OK;

    m_eMsgStatus = IMessageFormHostEx::CMS_NOT_AVAILABLE;
    m_hwndParent = hwndForm;

    // Create the view associated with this form.
    m_pView = new CMsgView(pFormProvider, this, m_pMsg, m_pMsgBase, m_fCompose);
    CPR(m_pView);
    
    // Create the new view window, and prefill its fields if necessary.
    // Note that if it has already been created, the view will simply
    // show itself.
    CBR(m_pView->Create(hwndForm, phwndBody));

    hr = m_pView->Init(pMsgFields);
    CHR(hr);

Error:
    // Everything worked ok.
    return hr;
}

