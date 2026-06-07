//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#define INITGUID
#include "common.h"
#include <initguid.h>
#include <mapidefs.h>
#include <mapiutil.h>
#undef INITGUID

// Label for the menu extension
const TCHAR cszReplyUsing[] = TEXT("Reply using Outlook E-mail");

// Global Count of references to this DLL - defined in Main.cpp
extern UINT g_cDLLRefCount;


MenuExtension::MenuExtension() : 
    m_cRef(1), 
    m_pSite(NULL),
    m_pSession(NULL),
    m_idc(0)
{
    g_cDLLRefCount++;
}

MenuExtension::~MenuExtension()
{    
    RELEASE_OBJ(m_pSite);
    RELEASE_OBJ(m_pSession);

    ASSERT(0 == m_cRef);
    g_cDLLRefCount--;
}

HRESULT MenuExtension::Initialize() 
{
    HRESULT hr = S_OK;

    if (!m_pSession)
    {
        // Logon to MAPI if m_pSession has not been opened
        hr = MAPILogonEx(0, NULL, NULL, 0, &m_pSession);
    }

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// QueryInterface - IUnknown interface Method
//
//  Returns a pointer to a specified interface on an object to which a client 
//  currently holds an interface pointer. This method must call IUnknown::AddRef 
//  on the pointer it returns.
//
STDMETHODIMP MenuExtension::QueryInterface(REFIID iid, LPVOID * ppv)
{   HRESULT hr = S_OK;

    *ppv = NULL;

    if(IID_IUnknown == iid)
    {
        *ppv = static_cast<IObjectWithSite*>(this);
    }        
    else if(IID_IObjectWithSite == iid)
    {
        *ppv = static_cast<IObjectWithSite*>(this);
    }
    else if(IID_IContextMenu == iid)
    {
        *ppv = static_cast<IContextMenu*>(this);
    }
    else
    {
        CHR(E_NOINTERFACE); 
    }
    
    (reinterpret_cast<IUnknown*>(*ppv))->AddRef();

Error:
    return(hr);
}


///////////////////////////////////////////////////////////////////////////////
// AddRef - IUnknown interface Method
//
//  Increments the reference count for an interface on an object. It should be 
//  called for every new copy of a pointer to an interface on a specified object.
//
STDMETHODIMP_(ULONG) MenuExtension::AddRef() 
{
    return ::InterlockedIncrement(&m_cRef);
}


///////////////////////////////////////////////////////////////////////////////
// Release - IUnknown interface Method
//
//  Decrements the reference count for the calling interface on a object. If 
//  the reference count on the object falls to 0, the object is freed from 
//  memory.
//
STDMETHODIMP_(ULONG) MenuExtension::Release() 
{
    if(0 == ::InterlockedDecrement(&m_cRef)) 
    {
        delete this; 
        return(0);
    } 
    return(m_cRef);
}


///////////////////////////////////////////////////////////////////////////////
// SetSite - IObjectWithSite interface Method
//
//  Provides the site's IUnknown pointer to the object.
// 
//  This method is how the context menu extension gets a pointer to its context.
//  The "site" is a pointer to the object in the UI that the menu extension 
//  will be acting on.
//
STDMETHODIMP MenuExtension::SetSite(IUnknown* pSite)
{
    RELEASE_OBJ(m_pSite);

    if(pSite)
    {
        m_pSite = pSite;
        m_pSite->AddRef();
    }
    return(S_OK);
}

///////////////////////////////////////////////////////////////////////////////
// GetSite - IObjectWithSite interface Method
//
//  Implements the required interface method.
//  Retrieves the last site set with IObjectWithSite::SetSite. If there's no 
//  known site, the object returns a failure code.
// 
STDMETHODIMP MenuExtension::GetSite(REFIID riid, void** ppvSite)
{
    HRESULT hr = S_OK;
    if(m_pSite) 
    {
        hr = m_pSite->QueryInterface(riid, ppvSite);
        CHR(hr);       
    }
    else
    {    
        CHR(E_FAIL); 
    }
    
Error:
    return(hr);
}


///////////////////////////////////////////////////////////////////////////////
// InsertMenuItem
//      NOTE: in WinCE there is only InsertMenu
//
//  Simply insert the item in the menu
//
HRESULT MenuExtension::InsertMenuItem(HMENU hmenu, UINT indexMenu, UINT idCmd, LPCTSTR szText)
{
    HRESULT hr = S_OK;

    if(!::InsertMenu(hmenu, indexMenu, MF_BYPOSITION | MF_STRING, idCmd, szText))
    {
        hr = E_FAIL;
    }

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// QueryContextMenu - IContextMenu interface Method
//
//  Inserts the ReplyUsing item into the menu of the read view.
//  Properly enables the menu item based on the type of message being read.
// 
HRESULT STDMETHODCALLTYPE MenuExtension::QueryContextMenu(HMENU hmenu,
    UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
    HRESULT hr = S_OK;
    BOOL fEnableItem; 
    TCHAR szItemName[30];

    CBR(idCmdFirst <= idCmdLast);
    m_idc = idCmdFirst;

    // Get item text 
    hr = StringCchCopy(szItemName, ARRAYSIZE(szItemName), cszReplyUsing);
    CHR(hr);

    // Insert the item
    hr = InsertMenuItem(hmenu, indexMenu, m_idc, szItemName);
    CHR(hr);

    // Determine if this is a read view for an email account other than "Outlook E-mail"
    //  if it is not - then gray out this menu option
    fEnableItem = IsReplyUsingEnabled();
    ::EnableMenuItem(hmenu, m_idc, fEnableItem ? MF_ENABLED : MF_GRAYED);   

Error:
    return(hr);
}


///////////////////////////////////////////////////////////////////////////////
// InvokeCommand - IContextMenu interface Method
//
//  Called when the user actions upon an item implemented by a MenuExtension.
//  If the lpVerb matches the name of our menu extension, take the appropriate action.
// 
HRESULT STDMETHODCALLTYPE MenuExtension::InvokeCommand(LPCMINVOKECOMMANDINFO lpici)
{
    HRESULT hr = S_OK;

    if (lpici->lpVerb)
    {
        if (!_tcscmp(cszReplyUsing, (LPCTSTR)lpici->lpVerb))
        {
            hr = ReplyUsing();
            CHR(hr);                    
        }
        else
        {
            CHR(E_INVALIDARG);
        }
    }    

Error:
    return hr;

}


///////////////////////////////////////////////////////////////////////////////
// GetCommandString - IContextMenu interface Method
//
//  Returns the only command string associated with this MenuExtension
// 
HRESULT STDMETHODCALLTYPE MenuExtension::GetCommandString(UINT_PTR idCmd,
        UINT uType, UINT* pwReserved, LPSTR pszBad, UINT cchMax)
{
    return StringCchCopy((TCHAR *)pszBad, cchMax, cszReplyUsing);
}



///////////////////////////////////////////////////////////////////////////////
//  Create (Static method)
//
//  When the applications's menu is rendered, it checks to see if there are any 
//  menu extensions registered.  If so, DllGetClassObject (Main.cpp) will be 
//  called for each extension.  DllGetClassObject instantiates MyClassFactory 
//  (ClassFactory.cpp) which will call MyClassFactory::CreateInstance which 
//  will in turn call this method.
//
//  Creates and then initializes the MenuExtension.
// 
HRESULT MenuExtension::Create(IObjectWithSite** ppNew)
{
    HRESULT hr = S_OK;
    MenuExtension* pte = NULL;

    pte = new MenuExtension();
    CPR(pte);

    hr = pte->Initialize();
    CHR(hr);

    *ppNew = pte;
    pte = NULL;

Error:    
    delete pte;
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// IsReplyUsingEnabled
//
//  Returns TRUE if the current context menu is in a read view for a message
//  whose service is neither SMS nor ActiveSync.
//
BOOL MenuExtension::IsReplyUsingEnabled()
{
    HRESULT hr = S_OK;
    BOOL fIsEnabled = FALSE;

    const TCHAR cszSMSService[] = TEXT("SMS");
    const TCHAR cszASyncService[] = TEXT("ActiveSync");
    
    IMAPIProp *pProp = NULL;    
    LPSPropValue pval = NULL;

    hr = GetIMAPIPropForMsg(&pProp);
    CHR(hr);    

    hr = HrGetOneProp (pProp, PR_SERVICE_NAME, &pval);
    CHR(hr);

    if ( (wcscmp(pval->Value.lpszW, cszSMSService) != 0) &&
         (wcscmp(pval->Value.lpszW, cszASyncService) != 0) )
    {
        fIsEnabled = TRUE;
    }

Error:
    return fIsEnabled;
}


///////////////////////////////////////////////////////////////////////////////
// ReplyUsing
//
//  Composes a reply to the current message using the "Outlook E-mail" account
//
HRESULT MenuExtension::ReplyUsing(void)
{
    HRESULT hr = S_OK;

    IMAPIProp *pProp = NULL;    
    
    ULONG rgTags[] = {4, PR_MESSAGE_CLASS, PR_SENDER_EMAIL_ADDRESS, PR_SUBJECT, PR_BODY};
    ULONG cProps = 0;
    LPSPropValue rgProps = NULL;

    MAILCOMPOSEFIELDS mcfReply = {0};
    LPTSTR pszReplySubject = NULL;
    LPTSTR pszReplyBody = NULL;
    LPTSTR pszOriginalBody = NULL;

    hr = GetIMAPIPropForMsg(&pProp);
    CHR(hr);
                        
    // Get the properties we are interested in from the original message
    hr = pProp->GetProps((LPSPropTagArray) rgTags, MAPI_UNICODE, &cProps, &rgProps);
    CHR(hr);


    if (PR_MESSAGE_CLASS == rgProps[0].ulPropTag)
    {
        mcfReply.pszMsgClass = rgProps[0].Value.lpszW;
    }

    if (PR_SENDER_EMAIL_ADDRESS == rgProps[1].ulPropTag)
    {
        mcfReply.pszTo = rgProps[1].Value.lpszW;
    }

    if (PR_SUBJECT == rgProps[2].ulPropTag)
    {
        hr = GetSubjectForReply(rgProps[2].Value.lpszW, &pszReplySubject);
        if (SUCCEEDED(hr))
        {
            mcfReply.pszSubject = pszReplySubject;
        }
    }

    if (PR_BODY == rgProps[3].ulPropTag)
    {            
        pszOriginalBody = rgProps[4].Value.lpszW;
    }
    else 
    {
        // Note: In this sample, we are simply extracting the PR_BODY property of the message.
        // For MIME messages, you would need to open the PR_CE_MIME_TEXT property and then parse
        // the MIME headers and content to extract the original body text to include in the reply.            
        // That is beyond the scope of what we are demonstrating here, so GetBodyForReply will simply
        // return a default string if the PR_BODY value we pass in is empty.
    }
    hr = GetBodyForReply(pszOriginalBody, &pszReplyBody);
    if (SUCCEEDED(hr))
    {
        mcfReply.pszBody= pszReplyBody;
    }
    
    // This sample replies using ActiveSync account
    mcfReply.dwFlags = MCF_ACCOUNT_IS_NAME;
    mcfReply.pszAccount = TEXT("ActiveSync");

    mcfReply.cbSize = sizeof(mcfReply);

    hr = MailComposeMessage(&mcfReply);

Error:
    MAPIFreeBuffer(rgProps);
    delete[] pszReplySubject;
    delete[] pszReplyBody;
    
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// GetSubjectForReply
//
//  This allocates a new string containing the reply subject.  
//  Caller responsible for memory cleanup.
//
HRESULT MenuExtension::GetSubjectForReply(LPCTSTR pszOriginal, LPTSTR* ppszReplySubject)
{    
    HRESULT hr = S_OK;
    const TCHAR cszReplySubjectPrefix[] = TEXT("RE: ");
    UINT cchReplySubject;

    CPR(pszOriginal);

    cchReplySubject = lstrlen(pszOriginal) + ARRAYSIZE(cszReplySubjectPrefix);

    *ppszReplySubject = new TCHAR[cchReplySubject];
    CPR(*ppszReplySubject);

    hr = StringCchCopy(*ppszReplySubject, cchReplySubject, cszReplySubjectPrefix);
    CHR(hr);

    hr = StringCchCat(*ppszReplySubject, cchReplySubject, pszOriginal);
    CHR(hr);
    
Error:
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// GetBodyForReply
//
//  This allocates a new string containing the reply body.  
//  Caller responsible for memory cleanup.
//
HRESULT MenuExtension::GetBodyForReply(LPTSTR pszOriginal, LPTSTR* ppszReplyBody)
{
    HRESULT hr = S_OK;
    const TCHAR cszReplyBodyPrefix[] = TEXT("\n\n-- original message --\n");
    const TCHAR cszNoBodyInReply[] = TEXT("\n\n[original message not included in reply]");    
    UINT cchReplyBody;

    if (pszOriginal)
    {        
        cchReplyBody = lstrlen(pszOriginal) + ARRAYSIZE(cszReplyBodyPrefix);

        *ppszReplyBody = new TCHAR[cchReplyBody];
        CPR(*ppszReplyBody);

        hr = StringCchCopy(*ppszReplyBody, cchReplyBody, cszReplyBodyPrefix);
        CHR(hr);

        hr = StringCchCat(*ppszReplyBody, cchReplyBody, pszOriginal);
        CHR(hr);
    }
    else
    {
        cchReplyBody = ARRAYSIZE(cszNoBodyInReply);
        
        *ppszReplyBody = new TCHAR[cchReplyBody];
        CPR(*ppszReplyBody);
        
        hr = StringCchCopy(*ppszReplyBody, cchReplyBody, cszNoBodyInReply);
        CHR(hr);
    }

Error:    
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// IsMessage
//
//  Determines if the ItemRef is a Message
// 
BOOL MenuExtension::IsMessage(ItemRef *pir)
{
    return IsEqualGUID(*(pir->pType), ITI_MessageItemRef);
}


///////////////////////////////////////////////////////////////////////////////
// IsMessageFormEx
//
//  Returns TRUE if the ItemRef is a MessageForm, FALSE otherwise.
// 
BOOL MenuExtension::IsMessageFormEx(ItemRef *pir)
{
    return IsEqualGUID(*(pir->pType), ITI_MessageFormExItemRef);
}    


///////////////////////////////////////////////////////////////////////////////
// GetItemRefArray
//
//  Retrieve the ItemRefArray from the application site
// 
HRESULT MenuExtension::GetItemRefArray(ItemRefArray **ppItemArray)
{
    HRESULT hr = E_FAIL;
    
    IDataObject* pDataObj = NULL;
    
    FORMATETC fmt;
    ZeroMemory(&fmt, sizeof(fmt));
    fmt.cfFormat = ::RegisterClipboardFormat(CFNAME_ITEMREFARRAY);
    fmt.dwAspect = DVASPECT_CONTENT;
    fmt.lindex = -1;
    fmt.ptd = NULL;
    fmt.tymed = TYMED_HGLOBAL;

    STGMEDIUM stg;
    ZeroMemory(&stg, sizeof(stg));

    // Be sure that there is a site.  Remember the "site" is a pointer to the 
    //  object in the UI that the menu extension will be acting on.
    if(m_pSite)
    {
        // Get the IDataObject interface for the site 
        hr = m_pSite->QueryInterface(IID_IDataObject, (void**)&pDataObj);
        CHR(hr);

        if (pDataObj)
        {
            // Get the FORMATETC and the STGMEDIUM from the IDataObject
            hr = pDataObj->GetData(&fmt, &stg);
            CHR(hr);

            if ( NULL != stg.hGlobal)
            {
                // Pull the ItemRefArray out of the STGMEDIUM stucture.
                *ppItemArray = (ItemRefArray *)stg.hGlobal;
            }
            else
            {
                CHR(E_FAIL);
            }
        }
        else 
        {
            CHR(E_FAIL);
        }            
    }

Error:
    RELEASE_OBJ(pDataObj);
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// GetIMAPIPropForMsg
//
//  Retrieves an IMAPIProp interface to the current message
// 
HRESULT MenuExtension::GetIMAPIPropForMsg(IMAPIProp** ppProp)
{
    HRESULT hr = S_OK;
    
    ItemRefArray *pItemArray = NULL;
    ItemRef *pRefMsg = NULL;
    IMessage *pMsg = NULL;

    hr = GetItemRefArray(&pItemArray);
    CHR(hr);

    if (pItemArray)
    {          
        ULONG cbEntry = 0;
        ENTRYID *pEntryID = NULL;

        // Get the 1st item and verify that it is a Message item
        pRefMsg = &pItemArray->rgRefs[0];
        CBR(IsMessage(pRefMsg));

        // Get the Entry Size - cbEntryID from the ItemRef
        cbEntry = ((SBinary *)pRefMsg->pRef)->cb;
        CBR(cbEntry);
        
        // Get the pointer to the EntryID from the ItemRef
        pEntryID = (ENTRYID *) ((SBinary *)pRefMsg->pRef)->lpb;
        CPR(pEntryID);
        
        // Open the Message
        // Note if you have a Message's Entry ID you can go straight to it
        //   no need to open the folder first
        hr = m_pSession->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pMsg);
        CHR(hr);
        CPR(pMsg);
             
        // Get an IMAPIProp Interface
        hr = pMsg->QueryInterface(IID_IMAPIProp, (LPVOID *) ppProp);
    }

Error:
    RELEASE_OBJ(pMsg);  
    return hr;      
}
