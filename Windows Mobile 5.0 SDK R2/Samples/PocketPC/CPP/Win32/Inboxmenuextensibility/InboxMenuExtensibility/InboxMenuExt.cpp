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
#include <pimstore.h>
#include <mapiutil.h>
#undef INITGUID


// Global Count of references to this DLL - defined in Main.cpp
extern UINT g_cDLLRefCount;


// These are the texts to be used on the new menu items this menu extension
// will add.  In production these would likely be pulled from a resource
// file which could be localized
const TCHAR cszAddSender[] = TEXT("Add Sender to Contacts");
const TCHAR cszMarkAll[] = TEXT("Mark All as Read");
const TCHAR cszDeleteAll[] = TEXT("Delete All");



///////////////////////////////////////////////////////////////////////////////
// GetPOOM
//
//  Helper function to CoCreate the IPOutloookApp2 Application
//
//  NOTE: POutlook.exe will be running (if it is not already running) after 
//  this function is called
//
//  Arguments:
//      [OUT] IPOutlookApp2 **ppPOOM - an unitialized pointer to pointer to the 
//          Pocket Outlook application object model. (POOM)
//
//  Return Values:
//      HRESULT - returns S_OK / E_FAIL.
//
//
HRESULT GetPOOM(IPOutlookApp2 **ppPOOM)
{
    HRESULT hr = E_FAIL;
    IUnknown * pUnknown = NULL;
    IPOutlookApp2 * polApp = NULL;

    hr = ::CoCreateInstance(CLSID_Application, 
                 NULL, CLSCTX_INPROC_SERVER, 
                 IID_IPOutlookApp2, 
                 (void **)&polApp);
    CHR(hr);
    CPR(polApp);

    hr = polApp->Logon(NULL);
    CHR(hr);

    *ppPOOM = polApp;
                 
Error:
    RELEASE_OBJ(pUnknown);
    return hr;
}




///////////////////////////////////////////////////////////////////////////////
// MenuExtension::MenuExtension - Constructor
//
//  Initializes member variables and increments the g_cDLLRefCount
//
//  Arguments:
//      [IN] ExtenstionType extensionType - a value from the enum ExtensionType
//          which indicates which type of menu extension to instantiate
//
//  Return Values:
//      MenuExtension object
//
MenuExtension::MenuExtension(ExtensionType extensionType) : 
    m_cRef(1), 
    m_pSite(NULL),
    m_pSession(NULL),
    m_idc1(0),
    m_idc2(0)
{
    g_cDLLRefCount++;
    m_ExtensionType = extensionType;
}


///////////////////////////////////////////////////////////////////////////////
// MenuExtension::MenuExtension - DeConstructor
//
//  Cleans up and de-crements the g_cDLLRefCount
//
//  Arguments:
//      None
//
//  Return Values:
//      None
//
MenuExtension::~MenuExtension()
{
    RELEASE_OBJ(m_pSite);
    ASSERT(0 == m_cRef);
    g_cDLLRefCount--;
}



///////////////////////////////////////////////////////////////////////////////
// Initialize
//
//  This method should be called after calling the constructor.  
//
//  Arguments:
//      None
//
//  Return Values:
//      HRESULT - currently always returns S_OK
//
HRESULT MenuExtension::Initialize() 
{

    // If you have logic in your constructor which MAY cause the constructor
    // to fail - you should pull it from the constructor and put it in this 
    // method, reducing the likelihood of a constructor failure
    return(S_OK);
}


///////////////////////////////////////////////////////////////////////////////
// QueryInterface - IUnknown interface Method
//
//  Returns a pointer to a specified interface on an object to which a client 
//  currently holds an interface pointer. This method must call IUnknown::AddRef 
//  on the pointer it returns.
//
//  Arguments:
//      [IN] REFIID iid - the interface ID we are testing for
//      [OUT] LPVOID *ppv - a pointer the object 
//
//  Return Values:
//      HRESULT - S_OK on success, E_NOINTERFACE if the inteface ID passed in
//          using iid is not supported by this object
//
STDMETHODIMP MenuExtension::QueryInterface(REFIID iid, LPVOID *ppv)
{ 
    HRESULT hr = S_OK;

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
//  Arguments:
//      none
//
//  Return Values:
//      ULONG - the current reference count to this object
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
//  Arguments:
//      none
//
//  Return Values:
//      ULONG - the current reference count to this object
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
//  will be acting on, i.e. the menu it will be extending
//
//  Arguments:
//      [IN] IUnknown* pSite - a pointer to the object in the Application's UI
//
//  Return Values:
//      HRESULT - always will be S_OK
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
//  Retrieves the last site set with SetSite. If there's no known site, the 
//  this returns a failure code.
// 
//  Arguments:
//      [IN] REFIID iid - the interface ID we are testing the site to see if it 
//          handles
//      [OUT] void** ppvSite - a pointer to the object will be returned
//          if the QI is succesful
//
//  Return Values:
//      HRESULT - S_OK on success else E_FAIL or other HRESULT returned by the 
//          site's QI method (potentially E_NOINTERFACE)
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
//  Arguments:
//      [IN] HMENU hmenu - a handle the menu to insert into
//      [IN] UINT indexMenu - the position the item will be inserted after
//      [IN] UINT idCmd - the ID of the new item
//      [IN] LPCTSTR szText - the menu text of the new item 
//
//  Return Values:
//      HRESULT - S_OK on success else E_FAIL
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
//  Adds the extra menu items to the context menu.  This method is called when 
//  the menu which our menu extension is extended is being created
//
//  Arguments:
//      [IN] HMENU hmenu - a handle the menu to insert into
//      [IN] UINT indexMenu - the position the item will be inserted after
//      [IN] UINT idCmdFirst - the lowest possible ID for a new command to use
//      [IN] UINT idCmdLast - the highest possible ID for a new command to use
//      [IN] LPCTSTR szText - the menu text of the new item 
//      [IN] UINT uFlags - a set of flags indicating what type of insertion and 
//          extension is allowed.  Please see the QueryContextMenu topic in the 
//          the SDK documentation for a complete list of these flags
//          NOTE:  The inbox application will only ever send CMF_NORMAL 
//          
//
//  Return Values:
//      HRESULT - S_OK on success else E_FAIL
//
HRESULT STDMETHODCALLTYPE MenuExtension::QueryContextMenu(HMENU hmenu,
    UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
    HRESULT hr = S_OK;

    m_idc1 = idCmdFirst;
    m_idc2 = idCmdFirst + 1; 

    CBR(m_idc2 <= idCmdLast);

    BOOL fEnableItem; 
    TCHAR szItemName[30];
    switch(m_ExtensionType)
    {
        case Context:            
            // Get item text 
            hr = GetCommandStringHelper(m_idc1, szItemName, ARRAYSIZE(szItemName));
            CHR(hr);

            // Insert the item
            hr = InsertMenuItem(hmenu, indexMenu, m_idc1, szItemName);
            CHR(hr);

            // Determine if we are in an appropriate folder and 
            //  have only a SINGLE item selected
            //  if NOT - then gray out this menu option
            fEnableItem = EnableAddSenderToContacts();
            ::EnableMenuItem(hmenu, m_idc1, fEnableItem ? MF_ENABLED : MF_GRAYED);
                
            break;
            
        case Softkey:

            // Get item text 
            hr = GetCommandStringHelper(m_idc1, szItemName, ARRAYSIZE(szItemName));
            CHR(hr);

            // Insert the item
            hr = InsertMenuItem(hmenu, indexMenu, m_idc1, szItemName);
            CHR(hr);

            // Get item text                 
            hr = GetCommandStringHelper(m_idc2, szItemName, ARRAYSIZE(szItemName));                
            CHR(hr);

            // Insert the item
            hr = InsertMenuItem(hmenu, indexMenu, m_idc2, szItemName);
            CHR(hr);

            // Determine if there are items in the ListView
            //  if there are no items - then gray out these menu options
            fEnableItem = AreThereMessagesInFolder();
            ::EnableMenuItem(hmenu, m_idc1, fEnableItem ? MF_ENABLED : MF_GRAYED);
            ::EnableMenuItem(hmenu, m_idc2, fEnableItem ? MF_ENABLED : MF_GRAYED);
            break;
            
    }
   

Error:
    return(hr);
}


///////////////////////////////////////////////////////////////////////////////
// InvokeCommand - IContextMenu interface Method
//
//  Runs a context menu command when the user selects one that was 
//  inserted with QueryContextMenu.  This method is called by the shell when one
//  of the items added by the menu extension is actioned uponed
// 
//  Arguments:
//      [IN] LPCMINVOKECOMMANDINFO lpici - a pointer to a CMINVOKECOMMANDINFO 
//          structure which contains data about the menu item clicked on by a 
//          user.  
//
//  Return Values:
//      HRESULT - S_OK on success. E_INVALIDARG, E_FAIL and other HRESULTS are
//          possible on failure
//
HRESULT STDMETHODCALLTYPE MenuExtension::InvokeCommand(LPCMINVOKECOMMANDINFO lpici)
{
    HRESULT hr = S_OK;

    if (lpici->lpVerb)
    {
        switch(m_ExtensionType)
        {   
            case Context:
                if (!_tcscmp(cszAddSender, (LPCTSTR)lpici->lpVerb))
                {
                    hr = AddSenderToContacts();
                    CHR(hr);
                }
                else
                {
                    CHR(E_INVALIDARG);
                }
            break;

            case Softkey:
                if (!_tcscmp(cszMarkAll, (LPCTSTR)lpici->lpVerb))
                {
                    hr = MarkAllInFolderAsRead();
                    CHR(hr);                    
                }
                else if (!_tcscmp(cszDeleteAll, (LPCTSTR)lpici->lpVerb))
                {
                    hr = DeleteAllInFolder();
                    CHR(hr);
                }
                else
                {
                    CHR(E_INVALIDARG);
                }

            break;
            
        }
    }    
    

Error:
    return hr;

}


///////////////////////////////////////////////////////////////////////////////
// GetCommandString - IContextMenu interface Method
//
//  Called by the shell to validate that the command exists, to get the command 
//  name, or to get the command help text.
//
//  Arguments:
//      [IN] Specifies the menu item ID, offset from the idCmdFirst 
//          parameter of QueryContextMenu. 
//      [IN] UINT uType - Bitmask that specifies that GetCommandString should 
//          either validate that the command exists, get the command name 
//          string, or get the help text string. For a list of possible flag 
//          values, see the table in IContextMenu::GetCommandString Documentation
//          NOTE:  The inbox application will only ever send GCS_VERB
//      [IN] UINT *pwReserved - Reserved (ignored, must pass NULL). 
//      [OUT] LPSTR pszName - Specifies the string buffer. 
//      [IN] UINT cchMax - Specifies the size of the string buffer (pszName)
//
//  Return Values:
//      HRESULT - S_OK on success. E_INVALIDARG, E_FAIL and other HRESULTS are
//          possible on failure
//
HRESULT STDMETHODCALLTYPE MenuExtension::GetCommandString(UINT_PTR idCmd,
        UINT uType, UINT* pwReserved, LPSTR pszName, UINT cchMax)
{

        return GetCommandStringHelper(idCmd, (TCHAR *) pszName, cchMax);    
}


///////////////////////////////////////////////////////////////////////////////
//  Create (Static method)
//
//  When the applications's menu is rendered, it checks to see if there are any 
//  menu extensions registered.  If so DllGetClassObject (See Main.cpp) will be 
//  called for each extension.  DllGetClassObject instantiates MyClassFactory 
//  (see ClassFactory.cpp) which will call MyClassFactory::CreateInstance which 
//  will in turn call this method
//
//  Create then calls the MenuExtension constructor.
//
//  Arguments:
//      [OUT] IObjectWithSite** ppNew - a pointer to our new Menu Extension
//      [IN] ExtensionType extensionType - which type of extension is this
//
//  Return Values:
//      HRESULT - S_OK on success. E_OUTOFMEMORY, E_FAIL and other HRESULTS are
//          possible on failure
// 
HRESULT MenuExtension::Create(IObjectWithSite** ppNew, ExtensionType extensionType)
{
    HRESULT hr = S_OK;
    MenuExtension* pte = NULL;

    pte = new MenuExtension(extensionType);
    CPR(pte);

    hr = pte->Initialize();
        
    if (SUCCEEDED(hr))
    {
        *ppNew = pte;
        pte = NULL;
    }

Error:
    delete(pte);

    return(hr);    
}


///////////////////////////////////////////////////////////////////////////////
// EnableAddSenderToContacts
//
//  Determine if the folder we are on is an incoming mail folder.  Drafts, 
//  Outbox, and Sent Items are NOT incoming mail folders, all others are 
//
//  Determine if there is only 1 selected message.  If there are more than 
//      1 selected we can not do Add Sender to contacts
// 
//  Notes: We know that the first item in the ItemRefArray is always a FOLDER 
//      item if this is a ListView Extension.  We also know that the rest of the 
//      items are selected messages.  
//
//  Arguments:
//      none
//
//  Return Values:
//      BOOL - TRUE if the menu item should be enabled
// 
BOOL MenuExtension::EnableAddSenderToContacts()
{      
    BOOL fResult = FALSE;
    HRESULT hr = E_FAIL;
    
    ItemRefArray *pItemArray = NULL;
    ItemRef *pRef = NULL;

    IMAPIFolder *pFolder = NULL;
    IMAPIProp *pProp = NULL;

    // Get the ItemRefArray
    hr = GetItemRefArray(&pItemArray);
    CHR(hr);

    // Make sure we have a valid pointer the ItemRefArray
    if (pItemArray)
    {   

            // REMINDER
            // ItemRefArray and ItemRef stuctures
            //
            //  struct ItemRefArray
            //  {
            //      int cRefs;         // count of ItemRefs in rgRefs
            //      ItemRef rgRefs[];  // rgRefs has cRefs entries
            //  };

            //  struct ItemRef
            //  {
            //      ITEM_TYPE_ID* pType; // identifies the the type of pRef
            //      void* pRef;          // a pointer to the data
            //  };

    
        // Make sure that there are only 2 items in the array
        //  1st is the folder
        //  2nd is the selected message
        fResult = (2 == pItemArray->cRefs);
        
        if (fResult)
        {
            // Get the 1st ItemRef from the ItemRefArray
            pRef = &pItemArray->rgRefs[0];

            // Check if the 1st item is a folder 
            fResult = IsFolder(pRef);

            // Check if the folder is NOT Drafts, Outbox or Sent Items
            if (fResult)
            {
                ULONG cbEntry = 0;
                ENTRYID *pEntryID = NULL;
                ULONG cValues = 0;
                ULONG rgTags[] = {1, PR_FOLDER_TYPE};
                SPropValue *rgProps= NULL;

                // We know that pRef is an ItemRef and that 
                // pRef->pType == ITI_FolderItemRef      see IsFolder(pRef)
                // pRef->pRef is of type SBinary
                // REMINDER    
                //typedef struct _SBinary
                //  {
                //      ULONG       cb;     // count in bytes of lpb
                //      LPBYTE      lpb;    // pointer (to an EntryID)
                //  } SBinary
                    
                
                // Get the Entry Size - cbEntryID from the ItemRef
                cbEntry = ((SBinary *)pRef->pRef)->cb;
                CBR(cbEntry);
                
                // Get the pointer to the EntryID from the ItemRef
                pEntryID = (ENTRYID *) ((SBinary *)pRef->pRef)->lpb;
                CPR(pEntryID);
                
                // Logon to MAPI                                                       
                hr = MAPILogonEx(0, NULL, NULL, 0, &m_pSession);
                CHR(hr);

                // Open the Folder    
                hr = m_pSession->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pFolder);
                CHR(hr);
                CPR(pFolder);
                     
                // Get an IMAPIProp Interface
                hr = pFolder->QueryInterface(IID_IMAPIProp, (LPVOID *) &pProp);
                CHR(hr);
                CPR(pProp);
                                
                // Get the Folder Type property
                hr = pProp->GetProps((LPSPropTagArray)rgTags, MAPI_UNICODE, &cValues, &rgProps);
                CHR(hr);
                CBR(PR_FOLDER_TYPE == rgProps[0].ulPropTag);
                
                // Make sure that this folder is NOT Drafts, Outbox, or Sent Items
                if ((rgProps[0].Value.ul & FOLDER_OUTBOX) ||
                    (rgProps[0].Value.ul & FOLDER_DRAFTS) ||
                    (rgProps[0].Value.ul & FOLDER_SENT_ITEMS))
                {
                    fResult = FALSE;
                }                
                MAPIFreeBuffer(rgProps);                  
            }                            

            if (fResult)
            {
                // Now we are sure that there are only 2 elements in the array  
                // Now we are sure we are in a valid folder for this feature
                // Now make sure that the 2nd item is indeed a message
                pRef = &pItemArray->rgRefs[1];
                fResult= IsMessage(pRef);
            }     
        }
    }      

Error:
    if FAILED(hr)
    {
        fResult = FALSE;
    }
    RELEASE_OBJ(pProp);
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(m_pSession);            

    return fResult;
}
    
    
///////////////////////////////////////////////////////////////////////////////
// AreThereMessagesInFolder
//
//  Determine if there are messages in the current folder.  
//  
//  Arguments:
//      none
//
//  Return Values:
//      BOOL - TRUE if there are messages in the current folder
// 
BOOL MenuExtension::AreThereMessagesInFolder()
{
    BOOL fResult = FALSE;
    HRESULT hr = E_FAIL;
    
    ItemRefArray *pItemArray = NULL;
    ItemRef *pRef = NULL;

    IMAPIFolder *pFolder = NULL;
    IMAPIProp *pProp = NULL;
    SPropValue *rgProps= NULL;
    
    hr = GetItemRefArray(&pItemArray);
    CHR(hr);
    
    if (pItemArray)
    {           
        // Check if the item 1 is a folder 
        pRef = &pItemArray->rgRefs[0];
        fResult = IsFolder(pRef);

        // Check if the COUNT of items in the folder
        if (fResult)
        {
            ULONG cbEntry = 0;
            ENTRYID *pEntryID = NULL;
            ULONG cValues = 0;
            ULONG rgTags[] = {1, PR_CONTENT_COUNT};

            // Get the Entry Size - cbEntryID from the ItemRef
            cbEntry = ((SBinary *)pRef->pRef)->cb;
            CBR(cbEntry);
            
            // Get the pointer to the EntryID from the ItemRef
            pEntryID = (ENTRYID *) ((SBinary *)pRef->pRef)->lpb;
            CPR(pEntryID);
            
            // Logon to MAPI                                                       
            hr = MAPILogonEx(0, NULL, NULL, 0, &m_pSession);
            CHR(hr);

            // Open the Folder
            hr = m_pSession->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pFolder);
            CHR(hr);
            CPR(pFolder);
                 
            // Get an IMAPIProp Interface
            hr = pFolder->QueryInterface(IID_IMAPIProp, (LPVOID *) &pProp);
            CHR(hr);
            CPR(pProp);
                            
            // Get the Folder PR_CONTENT_COUNT property
            hr = pProp->GetProps((LPSPropTagArray)rgTags, MAPI_UNICODE, &cValues, &rgProps);
            CHR(hr);
            CBR(PR_CONTENT_COUNT == rgProps[0].ulPropTag);

            fResult = (rgProps[0].Value.ul > 0);          
                   
        }
    } 
    
Error:
    if FAILED(hr)
    {
        fResult = FALSE;
    }

    MAPIFreeBuffer(rgProps);                  
    RELEASE_OBJ(pProp);
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(m_pSession);            
            
    return fResult;
}
        



///////////////////////////////////////////////////////////////////////////////
// GetCommandStringHelper
//
//  Determines which Command string we should use based on 
//  the current ExtensionType and current command ID
// 
//  Arguments:
//      [IN] int idCmd - the command ID
//      [OUT] TCHAR *pszName - a buffer to place the string into
//      [IN] UINT idCmd - the size of the buffer (pszName)
//
//  Return Values:
//      HRESULT - S_OK on success, E_INVALIDARG if idCmd does not make sense
//          plus other failing HRESULTS are possible
// 
HRESULT MenuExtension::GetCommandStringHelper(int idCmd, TCHAR *pszName, UINT cchName)
{
    HRESULT hr = E_INVALIDARG;
    
    if (pszName) 
    {      
        switch (m_ExtensionType)
        {
            case Context:
            {
                if (idCmd == m_idc1)
                {
                    // Add Sender to Contacts
                    hr = StringCchCopy(pszName, cchName, cszAddSender);
                    CHR(hr);
                }
                else
                {
                    CHR(E_INVALIDARG);
                }
            }
            break;

            case Softkey:
            {
                if (idCmd == m_idc1)
                {
                    // Mark all as read
                    hr = StringCchCopy(pszName, cchName, cszMarkAll);
                    CHR(hr);
                }
                else if (idCmd == m_idc2)
                {
                    // Delete all
                    hr = StringCchCopy(pszName, cchName, cszDeleteAll);
                    CHR(hr);
                }
                else
                {
                    CHR(E_INVALIDARG);
                }
            }
            break;
        }
    }        

Error:
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// IsMessage
//
//  Determines if the incoming ItemRef is a Message
// 
//  Arguments:
//      [IN] ItemRef *pir - pointer to an ItemRef to investigate
//
//  Return Values:
//      BOOL - true if this is a Message  (ITI_MessageItemRef)
// 
BOOL MenuExtension::IsMessage(ItemRef *pir)
{
    return IsEqualGUID(*(pir->pType), ITI_MessageItemRef);
}



///////////////////////////////////////////////////////////////////////////////
// IsFolder
//
//  Determines if the incoming ItemRef is a Folder
//
//  Arguments:
//      [IN] ItemRef *pir - pointer to an ItemRef to investigate
//
//  Return Values:
//      BOOL - true if this is a Folder (ITI_FolderItemRef)
//
BOOL MenuExtension::IsFolder(ItemRef *pir)
{
    return IsEqualGUID(*(pir->pType), ITI_FolderItemRef);
 }


///////////////////////////////////////////////////////////////////////////////
// GetItemRefArray
//
//  Retrieve the ItemRefArray from the application site.  The data which the
//  application passes to the Menu Extension is packaged in an ItemRefArray.
//
//  The contents of this ItemRefArray will vary depending on which type of 
//  menu extension you are implementing.  See the SDK documentation for more
//  details on what data is packed into this ItemRefArray for each of the 
//  different types of menu extensions
//
//  Arguments:
//      [OUT] ItemRef *pir - pointer to an ItemRefArray pulled from m_pSite
//
//  Return Values:
//      HRESULT - S_OK on success
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
// AddSenderToContacts
//
//  This method actually does the work of adding the sender of a message to the
//  contacts store.
//
//  Since we have good logic to prevent the Add Sender To Contacts menu item 
//  from being enabled when it should not - we should be able to trust that
//  when this method is hit 
//      1) the folder we are on is an incoming mail folder.  
//      2) there is only 1 selected message.  
//  So we don't have to scrutinize the contents of the ItemRefArray as much 
//  in this method.  
// 
//  Notes: We KNOW that the FIRST item is in the ItemRefArray is always a FOLDER 
//      item if are a ListView Extension.  We also know that the rest of the 
//      items are selected messages.  
//    
//  Arguments:
//      none
//
//  Return Values:
//      HRESULT - S_OK on success
//
HRESULT MenuExtension::AddSenderToContacts()
{
    HRESULT hr = E_FAIL;

    ItemRefArray *pItemArray = NULL;
    ItemRef *pRef = NULL;

    IMessage *pMsg = NULL;
    IMAPIProp *pProp = NULL;    
    SPropValue *rgProps= NULL;
    IPOutlookApp2 *pPOOM = NULL;    
    IContact *pContact = NULL; 


    hr = GetItemRefArray(&pItemArray);
    CHR(hr);
    
    if (pItemArray)
    {       

        // If we have made it here... we are good to get
        // the Display Name and Email Address of the sender
        // We should be able to trust that
        //      1) the folder we are on is an incoming mail folder.  
        //      2) there is only 1 selected message.  

        ULONG cbEntry = 0;
        ENTRYID *pEntryID = NULL;
        ULONG cValues = 0;
        ULONG rgTags[] = {2, PR_SENDER_NAME, PR_SENDER_EMAIL_ADDRESS};

        // Get the 2nd item and double check that the is indeed a Message item
        pRef = &pItemArray->rgRefs[1];
        CBR(IsMessage(pRef));

        // Get the Entry Size - cbEntryID from the ItemRef
        cbEntry = ((SBinary *)pRef->pRef)->cb;
        CBR(cbEntry);
        
        // Get the pointer to the EntryID from the ItemRef
        pEntryID = (ENTRYID *) ((SBinary *)pRef->pRef)->lpb;
        CPR(pEntryID);
        
        // Logon to MAPI                                                       
        hr = MAPILogonEx(0, NULL, NULL, 0, &m_pSession);
        CHR(hr);
        
        // Open the Message
        // Note if you have a Message's Entry ID you can go straight to it
        //   no need to open the folder first
        hr = m_pSession->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pMsg);
        CHR(hr);
        CPR(pMsg);
             
        // Get an IMAPIProp Interface
        hr = pMsg->QueryInterface(IID_IMAPIProp, (LPVOID *) &pProp);
        CHR(hr);
        CPR(pProp);
                        
        // Get the pMsg PR_SENDER_NAME and PR_SENDER_EMAIL_ADDRESS property
        hr = pProp->GetProps((LPSPropTagArray)rgTags, MAPI_UNICODE, &cValues, &rgProps);
        CHR(hr);

        LPTSTR szDisplayName = NULL;
        LPTSTR szEmailAddress = NULL;
    
        // NOTE: Sender Name may be missing - so first validate that the prop came back
        // then validate there is a value, then get the value.
        // 
        // NOTE:  Sender name may be "First Last" or "Last, First" or other
        //  but we are not doing any additional parsing here.
        if (PR_SENDER_NAME == rgProps[0].ulPropTag)
        {
            if (rgProps[0].Value.lpszW)
            {
                szDisplayName = (LPTSTR)rgProps[0].Value.lpszW;
            }
        }

        // NOTE: Email address may be missing - but it is unlikely - either way 
        //  first validate that the prop came back, then validate
        //  that there is a value, then get the value.
        //
        // NOTE:  The email address MAY be formed as 
        //      "Display Name" <email@address.com> 
        //  So additional parsing may be necessary here.  It all depends on how
        //  the email address of the message was created.
        if (PR_SENDER_EMAIL_ADDRESS == rgProps[1].ulPropTag)
        {
            if (rgProps[1].Value.lpszW)
            {
                szEmailAddress= (LPTSTR)rgProps[1].Value.lpszW;
            }
        }

        // Create the contact

        // Use POOM APIs to create new contact
        hr = GetPOOM(&pPOOM);
        CHR(hr);
        
        // Create a Contact object
        hr = pPOOM->CreateItem (olContactItem, (IDispatch **) &pContact);
        CHR(hr); 

        // Although POOM and Contacts supports FIRST and LAST name fields 
        // We are not going parse the display name (PR_SENDER_NAME) 
        // Instead will will put the entire display name (PR_SENDER_NAME) 
        // in the "File As" field. First and Last name fields will be blank
        if (szDisplayName)
        {   
            hr = pContact->put_FileAs(szDisplayName);
            CHR(hr);
        }

        // Store the Email Adddress      
        // NOTE: As noted above this may be more than just an email address
        //   depending on which software created the email
        if (szEmailAddress)
        {   
            hr = pContact->put_Email1Address(szEmailAddress);
            CHR(hr);
        }

        // Save the new contact
        hr = pContact->Save();
        CHR(hr);

        // Display the new Contact
        hr = pContact->Display();
        CHR(hr);

        // NOTE: we could first LOOK-UP on "Email Address" or "File As" to prevent 
        // making lots of the same record.  But that is outside the scope of this example
    } 
    
Error:
    // Make sure we do not leak memory
    MAPIFreeBuffer(rgProps);      
    
    if (pPOOM)
    {   hr = pPOOM->Logoff();
    }
        
    RELEASE_OBJ(pPOOM);
    RELEASE_OBJ(pContact);
    RELEASE_OBJ(pProp);
    RELEASE_OBJ(pMsg);
    RELEASE_OBJ(m_pSession);            

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// DeleteAllInFolder
//
//  This method actually does the work of deleting all of the email in the 
//  current folder
//
//  Since we have good logic to prevent the Delete All In Folder menu item 
//  from being enabled when it should not - we should be able to trust that
//  when this method is hit 
//      1) the folder we are on is has mail in it.  
// 
//  Deleting items in any folder other than the Deleted Items folder means 
//  moving the items to the Deleted Items folder.  But in the Deleted Items 

//  Folder - deleting means deleting.
//
//  Notes: We KNOW that the FIRST item is in the ItemRefArray is always a FOLDER 
//      item if are a ListView Extension. 
//    
//  Arguments:
//      none
//
//  Return Values:
//      HRESULT - S_OK on success
//
HRESULT MenuExtension::DeleteAllInFolder()
{
    HRESULT hr = E_FAIL;
    ItemRefArray *pItemArray = NULL;
    ItemRef *pRef = NULL;

    IMAPIFolder *pFolder = NULL;
    IMAPIProp *pProp = NULL;    
    IMAPIFolder *pWasteBasket= NULL;
    LPENTRYLIST lpmsgEntryList = NULL;
    SPropValue *rgFolderProps= NULL;
    SRowSet *pRows = NULL;
        
    hr = GetItemRefArray(&pItemArray);
    CHR(hr);
    
    if (pItemArray)
    {       
        // Double check that the 1st item is indeed a Folder item
        pRef = &pItemArray->rgRefs[0];
        CBR(IsFolder(pRef));

        ULONG cbEntry = 0;
        ENTRYID *pEntryID = NULL;
        ULONG cValues = 0;
        ULONG rgTags[] = {2, PR_CONTENT_COUNT, PR_FOLDER_TYPE};
        ULONG cMsgCount = 0;
        BOOL IsDeletedItems = FALSE;
                    
        // Get the Entry Size - cbEntryID from the ItemRef
        cbEntry = ((SBinary *)pRef->pRef)->cb;
        CBR(cbEntry);
        
        // Get the pointer to the EntryID from the ItemRef
        pEntryID = (ENTRYID *) ((SBinary *)pRef->pRef)->lpb;
        CPR(pEntryID);
        
        // Logon to MAPI                                                       
        hr = MAPILogonEx(0, NULL, NULL, 0, &m_pSession);
        CHR(hr);

        // Open the Folder
        hr = m_pSession->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pFolder);
        CHR(hr);
        CPR(pFolder);
            
        // Get an IMAPIProp Interface
        hr = pFolder->QueryInterface(IID_IMAPIProp, (LPVOID *) &pProp);
        CHR(hr);
        CPR(pProp);

        // Get the Folder PR_CONTENT_COUNT property
        hr = pProp->GetProps((LPSPropTagArray)rgTags, MAPI_UNICODE, &cValues, &rgFolderProps);
        CHR(hr);
        CBR(PR_CONTENT_COUNT == rgFolderProps[0].ulPropTag);            
        CBR(PR_FOLDER_TYPE == rgFolderProps[1].ulPropTag);            

        // Store the COUNT of messages in this folder
        cMsgCount = rgFolderProps[0].Value.ul;

        // Check if we are currently in the Deleted Items folder 
        // If yes - THEN we will be permanently deleting
        IsDeletedItems = (rgFolderProps[1].Value.ul & FOLDER_DELETED_ITEMS)? TRUE : FALSE;

        if (IsDeletedItems)
        {
            // Warn user that they will be permanently deleting 
            int iResult = ::MessageBox(GetActiveWindow(), 
                        TEXT("Are you sure you want to permanently delete all messages?"), 
                        TEXT("Permanently Delete Items"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2);

            // If IDYES - then continue / else exit method now
            hr = (iResult == IDYES) ? S_OK : E_FAIL;                        
            CHR(hr);

        }    
        else
        {
            // If we are not currently in the Deleted Items folder 
            // then get the Deleted Items folder
            //  since we will eventually be moving items there
            hr = GetWastebasketForFolder(pFolder, &pWasteBasket);
            CHR(hr);
            CPR(pWasteBasket);
        }
        
        // Get contents of the folder
        IMAPITable *pTable; 
        pFolder->GetContentsTable(MAPI_UNICODE, &pTable);

        // We only care about the EntryID. 
        SizedSPropTagArray (1, spta) = {1, PR_ENTRYID};
        pTable->SetColumns((SPropTagArray *)&spta, 0);

        BOOL done = FALSE;
        
        while(cMsgCount > 0)
        {
            // 10 is the max number of rows which QueryRows can return
            int cCurrentQuery = 0;

            if (cMsgCount > 10)
            {
                cCurrentQuery = 10;
            }
            else
            {
                cCurrentQuery = cMsgCount;
            }
            
            hr = pTable->QueryRows(cCurrentQuery, 0, &pRows);
            CHR(hr);
            
            // Did we hit the end of the table?
            if (pRows->cRows == 0)
            {   
                break;
            }

            // Since we are in a loop here and we are re-using lpmsgEntryList 
            // we may need to free the memory from the previous iteration first
            // In the case of the last iteration or Error - this will be freed at Error:
            MAPIFreeBuffer(lpmsgEntryList);
            lpmsgEntryList = NULL;
            
            // Otherwise - Get the List of EntryIDs from the RowSet as an EntryList
            //  Note: the resulting will EntryList be dependant on the RowSet so don't free until later
            hr = CreateEntryList(pRows, &lpmsgEntryList);
            
            CHR(hr);  

            if (IsDeletedItems)
            {
                // We are in the Deleted Items folder - so 
                // permanently delete the items 
                hr = pFolder->DeleteMessages(lpmsgEntryList, NULL, NULL, NULL);
            }
            else
            {   
                // We are not in the Deleted Items folder - so 
                // *move* the messages into the to the deleted items folder.                                
                hr = pFolder->CopyMessages(lpmsgEntryList, NULL, pWasteBasket, 0, NULL, MAPI_MOVE);
            }
            CHR(hr);           
            
            cMsgCount -= pRows->cRows;
        }   
    }

Error:
    // Make sure we do not leak memory
    FreeProws(pRows);
    MAPIFreeBuffer(rgFolderProps);  
    MAPIFreeBuffer(lpmsgEntryList);
    RELEASE_OBJ(pProp);
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(pWasteBasket);
    RELEASE_OBJ(m_pSession);            

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// MarkAllInFolderAsRead
//
//  This method actually does the wok of marking all messaages in the current
//  folder as read
//

//  Since we have good logic to prevent the Mark All As Read menu item 
//  from being enabled when it should not - we should be able to trust that
//  when this method is hit 
//      1) the folder we are on is has mail in it.  
// 
//  Notes: We KNOW that the FIRST item is in the ItemRefArray is always a FOLDER 
//      item if are a ListView Extension. 
//
//  Arguments:
//      none
//
//  Return Values:
//      HRESULT - S_OK on success
//
HRESULT MenuExtension::MarkAllInFolderAsRead()
{
    HRESULT hr = E_FAIL;
    ItemRefArray *pItemArray = NULL;
    ItemRef *pRef = NULL;

    IMAPIFolder *pFolder = NULL;
    IMAPIProp *pProp = NULL;    
    IMessage *pMsg = NULL;    
    SPropValue *rgFolderProps= NULL;
    SPropValue *rgMsgProps= NULL;
    SRowSet *pRows = NULL;
    
 
    hr = GetItemRefArray(&pItemArray);
    CHR(hr);
    
    if (pItemArray)
    {       
        // Double check that the 1st item is indeed a Folder item
        pRef = &pItemArray->rgRefs[0];
        CBR(IsFolder(pRef));

        ULONG cbEntry = 0;
        ENTRYID *pEntryID = NULL;
        ULONG cValues = 0;
        ULONG rgFolderTags[] = {1, PR_CONTENT_COUNT};
        ULONG rgMsgTags[] = {1, PR_MESSAGE_FLAGS};
        ULONG cMsgCount = 0;
                    
        // Get the Entry Size - cbEntryID from the ItemRef
        cbEntry = ((SBinary *)pRef->pRef)->cb;
        CBR(cbEntry);
        
        // Get the pointer to the EntryID from the ItemRef
        pEntryID = (ENTRYID *) ((SBinary *)pRef->pRef)->lpb;
        CPR(pEntryID);
        
        // Logon to MAPI                                                       
        hr = MAPILogonEx(0, NULL, NULL, 0, &m_pSession);
        CHR(hr);

        // Open the Folder
        hr = m_pSession->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pFolder);
        CHR(hr);
        CPR(pFolder);
            
        // Get an IMAPIProp Interface
        hr = pFolder->QueryInterface(IID_IMAPIProp, (LPVOID *) &pProp);
        CHR(hr);
        CPR(pProp);

        // Get the Folder PR_CONTENT_COUNT property
        hr = pProp->GetProps((LPSPropTagArray)rgFolderTags, MAPI_UNICODE, &cValues, &rgFolderProps);
        CHR(hr);
        CBR(PR_CONTENT_COUNT == rgFolderProps[0].ulPropTag);            

        // Store the COUNT of messages in this folder
        cMsgCount = rgFolderProps[0].Value.ul;
        
        // Get contents of the folder
        IMAPITable *pTable; 
        pFolder->GetContentsTable(MAPI_UNICODE, &pTable);

        // We only care about the EntryID. 
        SizedSPropTagArray (1, spta) = {1, PR_ENTRYID};
        pTable->SetColumns((SPropTagArray *)&spta, 0);

        BOOL done = FALSE;
        
        while(cMsgCount > 0)
        {
            // 10 is the max number of rows which QueryRows can return
            int cCurrentQuery = 0;

            if (cMsgCount > 10)
                cCurrentQuery = 10;
            else
                cCurrentQuery = cMsgCount;
            
            hr = pTable->QueryRows(cCurrentQuery, 0, &pRows);
            CHR(hr);
            
            // Did we hit the end of the table?
            if (pRows->cRows == 0)
            {   
                break;
            }

            // Otherwise - iterate through the message EntryIDS
            // and get the messages.  Then make sure that they are 
            // marked as read
            for (int i = 0; i < (int)pRows->cRows; i++)
            {
                // Get the EntryID and count of bytes
                cbEntry = pRows->aRow[i].lpProps[0].Value.bin.cb;
                pEntryID = (ENTRYID *)pRows->aRow[i].lpProps[0].Value.bin.lpb;          
                 
                // Get the Message
                hr = pFolder->OpenEntry(cbEntry, pEntryID, NULL, 0, NULL, (LPUNKNOWN *)&pMsg);
                CHR(hr);
                CPR(pMsg);

                // Get an IMAPIProp Interface
                hr = pMsg->QueryInterface(IID_IMAPIProp, (LPVOID *) &pProp);
                CHR(hr);
                CPR(pProp);

                // Get the Messages PR_FLAGS property
                hr = pProp->GetProps((LPSPropTagArray)rgMsgTags, MAPI_UNICODE, &cValues, &rgMsgProps);
                CHR(hr);
                CBR(PR_MESSAGE_FLAGS == rgMsgProps[0].ulPropTag);            

                // If Not already marked Read
                if (!(rgMsgProps[0].Value.ul & MSGFLAG_READ))
                {
                    // OR in the READ flag - so you don't disturb other flags
                    rgMsgProps[0].Value.ul |= MSGFLAG_READ;
                    hr = pProp->SetProps(1, rgMsgProps, NULL);
                }
    
            }
            
            cMsgCount -= pRows->cRows;
        }    
    }

Error:
    // Make sure we do not leak memory
    FreeProws(pRows);
    MAPIFreeBuffer(rgFolderProps);      
    MAPIFreeBuffer(rgMsgProps);
    RELEASE_OBJ(pProp);
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(pMsg);
    RELEASE_OBJ(m_pSession);            

    return hr;

}


///////////////////////////////////////////////////////////////////////////////
// GetWastebasketForFolder
//
// This method will find the appropriate wastebasket for the given folder.  It
// does this by finding the message store for the folder and then gets the
// ENTRYID of the wastebasket and then gets the wastebasket folder
//
//  This method assumes that the CALLER already logged on to a MAPISession and 
//      m_pSession is not NULL.
//
//  Arguments:
//      [IN] LPMAPIFOLDER pFolder - a pointer the current folder
//      [OUT] LPMAPIFOLDER* ppfldrWastebasket - this is used to return the 
//          pointer to the appropraite "deleted items" folder for the current
//          folder
//
//  Return Values:
//      HRESULT - S_OK on success
//
HRESULT MenuExtension::GetWastebasketForFolder(LPMAPIFOLDER pFolder,
        LPMAPIFOLDER* ppfldrWastebasket)
{
    HRESULT hr = E_FAIL;
    IMsgStore* pms = NULL;
    ULONG cItems;
    ULONG rgtagsFldr[] = { 1, PR_OWN_STORE_ENTRYID };
    ULONG rgtagsMsgStore[] = { 1, PR_IPM_WASTEBASKET_ENTRYID };
    LPSPropValue rgprops = NULL;

    // This method assumes that the CALLER already logged on to a MAPISession
    if (!m_pSession)
        CHR(E_FAIL);  

    // Now request the PR_OWN_STORE_ENTRYID on the folder.  This is the
    // ENTRYID of the message store that owns the folder object.
    hr = pFolder->GetProps((LPSPropTagArray)rgtagsFldr, MAPI_UNICODE, &cItems, &rgprops);
    CHR(hr);

    CBR(PR_OWN_STORE_ENTRYID == rgprops[0].ulPropTag);

    // Now open the message store object.
    hr = m_pSession->OpenEntry(rgprops[0].Value.bin.cb,
            (LPENTRYID)rgprops[0].Value.bin.lpb,
            NULL, 0, NULL, (LPUNKNOWN*)&pms);
    CHR(hr);

    MAPIFreeBuffer(rgprops);
    rgprops = NULL;

    // Get the ENTRYID of the wastebasket for the message store
    hr = pms->GetProps((LPSPropTagArray)rgtagsMsgStore, MAPI_UNICODE, &cItems, &rgprops);
    CHR(hr);

    // Now open the correct wastebasket and return it to the caller.
    CBR(PR_IPM_WASTEBASKET_ENTRYID == rgprops[0].ulPropTag);

    hr = m_pSession->OpenEntry(rgprops[0].Value.bin.cb,
            (LPENTRYID)rgprops[0].Value.bin.lpb,
            NULL, 0, NULL, (LPUNKNOWN*)ppfldrWastebasket);
    CHR(hr);

Error:
    MAPIFreeBuffer(rgprops);
    RELEASE_OBJ(pms);

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// CreateEntryList
//
//  This method will create an ENTRYLIST from an SRowSet which 
//
//  Arguments:
//      [IN] SRowSet *pRows - a pointer the row set (obtained from an IMAPITable)
//      [OUT] ENTRYLIST **ppList - the resulting new EntryList.  
//          NOTE:  The caller is responsible for calling MAPIFreeBuffer 
//          on this returned list
//
//  Return Values:
//      HRESULT - S_OK on success
//
HRESULT MenuExtension::CreateEntryList(SRowSet *pRows, ENTRYLIST **ppList)
{
    HRESULT hr;
    ENTRYLIST* plist = NULL;
    
    // How much space do we need to create this entry list??
    ULONG cbNeeded = sizeof(SBinaryArray) + (pRows->cRows * (sizeof(SBinary)));

    // Allocate one buffer to hold all the data for the list.
    hr = MAPIAllocateBuffer(cbNeeded, (LPVOID*)&plist);
    CHR(hr);
    CPR(plist);

    // Set the number of items in the EntryList 
    plist->cValues = pRows->cRows;

    // Set plist->lpbin to the place in the buffer where the array items will be
    // filled in
    BYTE* pb;
    pb = (BYTE*)plist;
    pb += sizeof(SBinaryArray);
    plist->lpbin = (SBinary*) pb;

    // Loop through the list setting the contents of the EntryList to the contents
    // of the incoming SRowSet
    for (int cItems = 0; cItems < (int)plist->cValues; cItems++)
    {
        plist->lpbin[cItems].cb = pRows->aRow[cItems].lpProps[0].Value.bin.cb;
        plist->lpbin[cItems].lpb = pRows->aRow[cItems].lpProps[0].Value.bin.lpb;

        // Track our memory usage 
        pb += sizeof(SBinary);
    }

    // Make sure that we didn't write off the end of our buffer...
    CBR(pb <= ((BYTE*)plist + cbNeeded));

Error:

    if (FAILED(hr))
    {
        MAPIFreeBuffer(plist);
        plist = NULL;
    }

    *ppList = plist;

    return hr;
}



