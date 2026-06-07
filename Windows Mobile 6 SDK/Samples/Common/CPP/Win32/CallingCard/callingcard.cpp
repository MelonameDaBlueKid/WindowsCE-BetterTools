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


#define INITGUID
#include "common.h"
#include <initguid.h>
#include <pimstore.h>
#include <mapiutil.h>
#undef INITGUID
#include <phone.h>
#include <regext.h>
#include "callingcard.h"

// Globals
// Global Count of references to this DLL - defined in Main.cpp
extern UINT g_cDLLRefCount;


#define MAX_BUF MAX_NUMBER_LEN * 4


// This is the text to be used in the menu items the  menu extension
// will add.  In production these would likely be pulled from a resource
// file which could be localized

const TCHAR cszCallWork[] = TEXT("Call Work using Calling Card");
const TCHAR cszCallHome[] = TEXT("Call Home using Calling Card");
const TCHAR cszCallCell[] = TEXT("Call Mobile using Calling Card");

// Registry paths for calling card settings
const TCHAR cszRegSettings[] = TEXT("Software\\Microsoft\\CallingCard");
const TCHAR cszRegNumber[] = TEXT("Number");
const TCHAR cszRegPause1[] = TEXT("Pause1");
const TCHAR cszRegPause2[] = TEXT("Pause2");
const TCHAR cszRegPIN[] = TEXT("Pin");


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
                 IID_IUnknown, 
                 (void **)&pUnknown);
    CHR(hr);

    hr = pUnknown->QueryInterface(IID_IPOutlookApp, (void**)&polApp);
    CHR(hr);

    hr = polApp->Logon(NULL);
    CHR(hr);

    *ppPOOM = polApp;
                 
Error:
    RELEASE_OBJ(pUnknown);
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// StripNonPhoneDigits
//
//  Helper function to strip out non-phone digits (+, (, ) ....) from a phone number 
//
//  
//  Arguments:
//      [OUT] TCHAR *pszDst - destination buffer large enough to store pszSrc and a null terminator
//                             The number without non-phone digits is written to this buffer
//      [IN] UINT ccDst - size in characters of pszDst.
//      [IN] TCHAR *pszSrc - source buffer containing original phone number
//      [IN] TCHAR ccSrc - size in characters of pszSrc.
//  Return Values:
//      HRESULT - returns S_OK / E_FAIL.
//
//
#define ISVALIDCHAR(ch)     (((ch) == TEXT('p')) || ((ch) == TEXT(',')) || ((ch) == TEXT('w')))     
#define ISPHONE_DIGIT(ch) ((isdigit(ch)) || (ISVALIDCHAR(ch)))
HRESULT StripNonPhoneDigits(TCHAR * pszDst, UINT ccDst, TCHAR *pszSrc, UINT ccSrc)
{
    HRESULT hr = S_OK;
    CBR(ccDst >= ccSrc);
   
    for (int i = 0; i < (int)ccSrc && pszSrc[i]; i++)
    {
        // Since ccDst >= ccSrc, we are sure we always write to memory we own
        if (ISPHONE_DIGIT(pszSrc[i]))
        {
            // Copy over phone digits
            *pszDst = pszSrc[i];
            pszDst++;
        }
    }

    // Safely null terminate the string
    pszDst[0] = NULL;

Error:
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
    m_idcCallCell(0),
    m_idcCallWork(0),
    m_idcCallHome(0),
    m_fInitialized(FALSE),
    m_polApp(NULL)
{
    RELEASE_OBJ(m_pSite);
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
    FreeContactInfo();
    ClearCardInfo();
    if (m_polApp)
    {  
        m_polApp->Logoff();
        m_polApp->Release();
        m_polApp = NULL;
    }
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
    ZeroMemory(&m_contactInfo, sizeof(CINFO));
    ZeroMemory(&m_cardInfo, sizeof(CARDINFO));

    ReadSettings();

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
    if(m_pSite)
    {
        m_pSite->Release();
        m_pSite = NULL;
    }

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

    if(!::InsertMenu(hmenu, indexMenu, MF_BYPOSITION, idCmd, szText))
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
//
//  Return Values:
//      HRESULT - S_OK on success else E_FAIL
//
HRESULT STDMETHODCALLTYPE MenuExtension::QueryContextMenu(HMENU hmenu,
    UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
    HRESULT hr = S_OK;
    BOOL fInserted = FALSE;

    m_idcCallCell = idCmdFirst;
    m_idcCallWork = m_idcCallCell + 1;
    m_idcCallHome = m_idcCallCell + 2;    
    
    ASSERT(m_idcCallHome <= idCmdLast);    

    if (!m_fInitialized)
    {
        // We haven't read in the calling card settings
        CHR(ReadSettings());
    }
    // Let's see if we have a contact highlighted and what info it has
    GetContactInfo(); 
    
    if (m_contactInfo.bstrCellNumber && m_contactInfo.bstrCellNumber[0])
    {       
        // You can call the Mobile number
        hr = InsertMenuItem(hmenu, indexMenu, m_idcCallCell, cszCallCell); 
        fInserted = TRUE;
    }
    if (m_contactInfo.bstrHomeNumber && m_contactInfo.bstrHomeNumber[0])
    {
        // You can call the Home Number
        hr = InsertMenuItem(hmenu, indexMenu, m_idcCallHome, cszCallHome); 
        fInserted = TRUE;
    }
    if (!fInserted || (m_contactInfo.bstrWorkNumber && m_contactInfo.bstrWorkNumber[0]))
    {
        // We should have at least one entry in the context/softkey menu 
        fInserted = (m_contactInfo.bstrWorkNumber && m_contactInfo.bstrWorkNumber[0]);
        hr = InsertMenuItem(hmenu, indexMenu, m_idcCallWork, cszCallWork); 
        if (!fInserted)
        {
            ::EnableMenuItem(hmenu, m_idcCallWork, MF_GRAYED);
        }            
        
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
    HRESULT hr = E_FAIL;

    if (lpici->lpVerb)
    {        
        if (0 == (_tcscmp(TEXT("Work"), (LPCTSTR)lpici->lpVerb)))
        {                       
            hr = CallContact(m_idcCallWork);                        
        }
        else if (0 == (_tcscmp(TEXT("Cell"), (LPCTSTR)lpici->lpVerb)))
        {
            hr = CallContact(m_idcCallCell);              
        }
        else if (0 == (_tcscmp(TEXT("Home"), (LPCTSTR)lpici->lpVerb)))
        {
            hr = CallContact(m_idcCallHome);  
        }        
        else
        {
            hr = E_INVALIDARG;
        }       
        
    }    

    return hr;

}

///////////////////////////////////////////////////////////////////////////////
// ReadSettings
//
//  Reads in the calling card settings from the registry. 
//
//  Arguments:
//      None
//
//  Return Values:
//      HRESULT - S_OK on success. E_FAIL and other HRESULTS are
//          possible on failure
//
HRESULT MenuExtension::ReadSettings()
{
    HRESULT hr = S_OK;
    UINT cchLen;    
    HKEY hKey = NULL;
    
    // First, let's see if the settings exist...
   
    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, cszRegSettings, 0, KEY_READ, &hKey))
    {
        CHR(E_FAIL);    
    }    
    // Next, let's initialize our cardinfo struct...  
    ClearCardInfo();

    // We store the settings as clear text in the Registry because the entire dial string
    // will be stored in the phone call history as clear text. Thus, there is no point in 
    // encrypting the pin in registry
    // Let's use the registry wrappers. Much easier than RegQueryValueEx...
    cchLen = MAX_NUMBER_LEN;
    CHR(RegistryGetString(hKey, NULL, cszRegNumber, m_cardInfo.pszCardNumber, cchLen));
    CHR(RegistryGetString(hKey, NULL, cszRegPIN, m_cardInfo.pszPin, cchLen));
    CHR(RegistryGetDWORD(hKey, NULL, cszRegPause1, &(m_cardInfo.dwFirstPause)));
    CHR(RegistryGetDWORD(hKey, NULL, cszRegPause2, &(m_cardInfo.dwSecondPause)));
    
Error:
    if (SUCCEEDED(hr))
    {
        m_fInitialized = TRUE;
    }
    else
    {
        // We need to clean up our struct
        ClearCardInfo();
    }
    RegCloseKey(hKey);
        
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
    if (pte)
    {
        hr = pte->Initialize();
           
        if (SUCCEEDED(hr))
        {
            *ppNew = pte;
            pte = NULL;
        }
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    delete(pte);

    return(hr);
    
}

///////////////////////////////////////////////////////////////////////////////
// FreeCardInfo
//
//  Frees any memory used by the card info struc
//
//  Arguments:
//      None
//
//  Return Values:
//      None
//
void MenuExtension::ClearCardInfo()
{   
    ZeroMemory(&m_cardInfo, sizeof(m_cardInfo));
    m_fInitialized = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// FreeContactInfo
//
//  Free Contact Info memory allocations.
//
//  Arguments:
//      None.
//
//  Return Values:
//      N/A
// 
void MenuExtension::FreeContactInfo()
{      
    // Free m_contactInfo data
    if (m_contactInfo.bstrFileAs)
    {
        SysFreeString(m_contactInfo.bstrFileAs);
        m_contactInfo.bstrFileAs = NULL;
    }    
    if (m_contactInfo.bstrHomeNumber)
    {
        SysFreeString(m_contactInfo.bstrHomeNumber);
        m_contactInfo.bstrHomeNumber = NULL;
    }
    if (m_contactInfo.bstrCellNumber)
    {        
        SysFreeString(m_contactInfo.bstrCellNumber);
        m_contactInfo.bstrCellNumber = NULL;
    }
    if (m_contactInfo.bstrWorkNumber)
    {
        SysFreeString(m_contactInfo.bstrWorkNumber);
        m_contactInfo.bstrWorkNumber = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// GetContactInfo
//
//  Get selected contact's first name, last name, home, mobile and work numbers, if any
//
//  Arguments:
//      None.
//
//  Return Values:
//      BOOL - TRUE if at least one number (home/work/mobile) retrieved, and we have valid
//             values for first and last name (empty string is valid).
// 
BOOL MenuExtension::GetContactInfo()
{      
    BOOL fResult = FALSE;
    HRESULT hr = E_FAIL;
    IDataObject* pobj;

    // Initialize Video Call Info
    FreeContactInfo();

    // Do not try to collect info if no contact is highlighted
    if (!m_pSite) 
    {
        return FALSE;
    }

    hr = m_pSite->QueryInterface(IID_IDataObject, (void**) &pobj);
    if (SUCCEEDED(hr))
    {
        CEOID oid;
    
        if (GetContactsOidFromSelection(pobj, &oid))
        {
            IContact *pContact = NULL;

            // Use POOM for Contacts
            if (!m_polApp)
            {
                hr = GetPOOM(&m_polApp);
            }

            if (SUCCEEDED(hr))
            {
                hr = m_polApp->GetItemFromOid(oid, reinterpret_cast<IDispatch**>(&pContact));
                if (SUCCEEDED(hr))
                {
                    // Obtain name plus phone numbers of selected contact
                    pContact->get_FileAs(&(m_contactInfo.bstrFileAs));                    
                    pContact->get_MobileTelephoneNumber(&(m_contactInfo.bstrCellNumber));
                    pContact->get_HomeTelephoneNumber(&(m_contactInfo.bstrHomeNumber));
                    pContact->get_BusinessTelephoneNumber(&(m_contactInfo.bstrWorkNumber));

                    // Check to see that we have at least one number to call
                    if ((m_contactInfo.bstrFileAs) &&                        
                        ((m_contactInfo.bstrCellNumber && m_contactInfo.bstrCellNumber[0]) ||
                         (m_contactInfo.bstrHomeNumber && m_contactInfo.bstrHomeNumber[0]) ||
                         (m_contactInfo.bstrWorkNumber && m_contactInfo.bstrWorkNumber[0]))
                       )                     
                    {
                        // We have at least one number to work with
                        fResult = TRUE;
                    }
                    else
                    {
                        // We have no contact info
                        FreeContactInfo();
                    }

                    // Free IContact data
                    pContact->Release();
                    pContact = NULL;
                }
            }
        }

        pobj->Release();
    }

    return fResult;
}


///////////////////////////////////////////////////////////////////////////////
// GetContactInfo
//
//  Read oid/etc. for selected item
//
//  Arguments:
//      [IN] IDataObject *pdo     IDataObject for item
//      [OUT] CEIOD *poidOut      pointer to oid of contact selected 
//  BOOL    (ret) TRUE if Contacts Oid obtained.  FALSE otherwise.
//
//  Return Values:
//      BOOL - TRUE if Contact oid obtained. FALSE otherwise
//
BOOL MenuExtension::GetContactsOidFromSelection(IDataObject *pdo, CEOID *poidOut)
{
    BOOL bRet = FALSE;
    HRESULT hr = S_OK;
    CEOID oid = 0;
    FORMATETC fmte;
    STGMEDIUM med;

    *poidOut = 0;
    
    memset(&fmte, 0, sizeof(fmte));
    memset(&med, 0, sizeof(med));
    fmte.cfFormat = RegisterClipboardFormat(CFNAME_ITEMREFARRAY);
    fmte.lindex = -1;
    fmte.tymed = TYMED_HGLOBAL;

    // Get selection info
    CHR(pdo->GetData(&fmte, &med)); 

    // Contacts give back ItemRef's    
    ItemRefArray * pArray;
    ItemRef * pRef;

    // Unpack selection info
    pArray = (ItemRefArray *) med.hGlobal;
    CPR(pArray); 

    // On SP we just get back one (no multiple-selection UI).
    // On PPC we can get back more than one, so let's pick the first one      
    pRef = &pArray->rgRefs[0];
    *poidOut = (CEOID) (pRef->pRef);

    // Make sure this is a Contact item
    if (IsEqualGUID(*(pRef->pType), ITI_ContactItemRef))
    {
        bRet = TRUE;
    }
 
    // Cleanup
    ReleaseStgMedium(&med);

  
  
Error:
    return bRet;
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
HRESULT MenuExtension::GetCommandStringHelper(int idCmd, TCHAR *pszName, UINT ccName)
{
    HRESULT hr = E_FAIL;
    
    if (pszName) 
    {      
        if (idCmd == m_idcCallCell)
        {
            hr = StringCchCopy(pszName, ccName, TEXT("Cell"));
        }
        else if (idCmd == m_idcCallWork)
        {
            hr = StringCchCopy(pszName, ccName, TEXT("Work"));
        }
        else if (idCmd == m_idcCallHome)
        {
            hr = StringCchCopy(pszName, ccName, TEXT("Home"));            
        }        
             
    }     

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// BuildDialString
//
//  Combines calling card number, pin and phone number into a complete dial string
//  that can be passed to the phone app
// 
//  Arguments:
//      [OUT] TCHAR *pszBuffer - a buffer to store the complete dial string in
//      [IN] UINT cchBuffer - size of pszBuffer in characters
//      [IN] TCHAR* pszNumber - buffer containing the phone number to be appended to 
//                               calling card info
//
//  Return Values:
//      HRESULT - S_OK on success, E_FAIL plus other failing HRESULTS if dial string creation fails
// 
HRESULT MenuExtension::BuildDialString(TCHAR *pszBuffer, UINT cchBuffer, TCHAR* pszNumber)
{

    // Since we are the only ones calling this function, we can assume that we have valid data here
    HRESULT hr = S_OK;    
    UINT cchRem = 0;
    TCHAR *pszNext;

    // We start with the calling card number
    CHR(StringCchCopyEx(pszBuffer, cchBuffer, m_cardInfo.pszCardNumber, &pszNext, &cchRem, STRSAFE_NULL_ON_FAILURE));
    
    // Then add the first pause between connecting to calling card number and request for pin
    if (m_cardInfo.dwFirstPause)
    {        
        int i;
        for (i = 0; i < (int)m_cardInfo.dwFirstPause && cchRem > 1; i++, cchRem--)
        {
            pszNext[i] = 'p';
        }
        pszNext += i;
    }
    else
    {
        // '0' for pauses indicates that user will press talk to send the pin
        CBR(cchRem > 1);
        pszNext[0] = 'w';
        pszNext++;
        cchRem--;
    }
    
    // Now let's copy the pin number
    CHR(StringCchCopyEx(pszNext, cchRem, m_cardInfo.pszPin, &pszNext, &cchRem, STRSAFE_NULL_ON_FAILURE));

    // Let's now add the pause between inputting the pin and the request for the number
    if (m_cardInfo.dwSecondPause)
    {
        int i;
        for (i = 0; i < (int)m_cardInfo.dwSecondPause && cchRem > 1; i++, cchRem--)
        {
            pszNext[i] = 'p';
        }
        pszNext += i;
    }
    else
    {
       // '0' for pauses indicates that user will press talk to send the phone number
       CBR(cchRem > 1);
       pszNext[0] = 'w';
       pszNext++;
       cchRem--;
    }   
    
    // Finally, let's copy the phone number
    CHR(StringCchCopy(pszNext, cchRem, pszNumber));

Error:
    return (hr);   
    
}

///////////////////////////////////////////////////////////////////////////////
// CallContact
//
//  This method actually does the work of making the phone call.
//  It is assumed that we have valid contact and calling card info.
//
//  Arguments:
//      none
//
//  Return Values:
//      HRESULT - S_OK on success
//
HRESULT MenuExtension::CallContact(UINT idCmd)
{
    HRESULT hr = S_OK;
    PHONEMAKECALLINFO phCallInfo;
    BSTR *pbstrNumber;
    TCHAR *pszDestNumber = NULL;
    UINT cchLen = 0;
    UINT cbSize = 0;
    
    TCHAR pszDialString[MAX_BUF]; 
    TCHAR pszCalledParty[128];
       
    // What number are we actually dialing?
    if (idCmd == m_idcCallCell)
    {
        pbstrNumber = &(m_contactInfo.bstrCellNumber);
    }
    else if (idCmd == m_idcCallHome)
    {
        pbstrNumber = &(m_contactInfo.bstrHomeNumber);
    }
    else if (idCmd == m_idcCallWork)
    {
        pbstrNumber = &(m_contactInfo.bstrWorkNumber);
    }
    else
    {
        CHR(E_INVALIDARG);
    }   



    // Now we need to strip out non-phone digits from the phone number
    // If we don't the phone will not send the correct DTMFs to the calling card system
    
    CHR(StringCchLength((TCHAR *)(*pbstrNumber), MAX_BUF, &cchLen));    
    // Since we know that cchLen will never be > MAX_BUF, we don't have to worry about overflow here
    cbSize = (cchLen + 1) * sizeof(TCHAR);
    pszDestNumber = (TCHAR *)LocalAlloc(LPTR, cbSize);
    CPR(pszDestNumber);
    // Strip out non digits
    CHR(StripNonPhoneDigits(pszDestNumber, cchLen + 1, (TCHAR *)(*pbstrNumber), cchLen));
        
    // Construct the calling card dialing string
    CHR(BuildDialString(pszDialString, ARRAYSIZE(pszDialString), pszDestNumber));    

    // If we pass in the FileAs name to display user friendly caller id
    CHR(StringCchPrintf(pszCalledParty, ARRAYSIZE(pszCalledParty), TEXT("%s"),
                    m_contactInfo.bstrFileAs));

    // Finally, we can make the actual call
    ZeroMemory(&phCallInfo, sizeof(phCallInfo));
    phCallInfo.cbSize = sizeof(phCallInfo);
    phCallInfo.dwFlags = PMCF_DEFAULT; 
    phCallInfo.pszDestAddress = pszDialString;
    phCallInfo.pszCalledParty = pszCalledParty;

    // Ring ring...
    PhoneMakeCall(&phCallInfo);

Error:
    if (pszDestNumber)
    {
        LocalFree(pszDestNumber);
    }
    return hr;    
}
