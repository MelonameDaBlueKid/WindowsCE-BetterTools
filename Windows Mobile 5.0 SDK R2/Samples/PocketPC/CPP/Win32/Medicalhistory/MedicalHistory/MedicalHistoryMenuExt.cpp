//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#include <objbase.h>
#include <initguid.h>

#include "stdafx.h"
#include "ClassFactory.h"

HINSTANCE g_hInst;

#include <shlguid.h>
#include <COGUID.H>
#undef INITGUID

static const WCHAR c_szMedicalHistoryMenu[] = L"Medical History";

// COM Medical History Menu Extension class that implements 
// IObjectWithSite and IContextMenu
class MedicalHistoryMenuExtension :
    public IObjectWithSite,
    public IContextMenu
{
private:
    LONG m_cRef; // COM refcount
    IUnknown* m_pSite;
    UINT m_idMenu;
    MedicalHistoryMenuExtension();
    virtual ~MedicalHistoryMenuExtension();
    void Reset();
    HRESULT Initialize();
    STDMETHODIMP QueryInterface(REFIID iid, LPVOID * ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    virtual STDMETHODIMP SetSite(IUnknown* pSite);
    virtual STDMETHODIMP GetSite(REFIID riid, void** ppvSite);
    virtual HRESULT STDMETHODCALLTYPE QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, 
                                                       UINT idCmdLast, UINT uFlags);
    virtual HRESULT STDMETHODCALLTYPE InvokeCommand(LPCMINVOKECOMMANDINFO lpici);
    virtual HRESULT STDMETHODCALLTYPE GetCommandString(UINT_PTR idCmd, UINT uType, UINT* pwReserved, 
                                                       LPSTR pszName, UINT cchMax);
public:
    static HRESULT Create(IObjectWithSite** ppNew);
};
// **************************************************************************
// Function Name: MedicalHistoryMenuExtension
// 
// Purpose: Constructor
//
MedicalHistoryMenuExtension::MedicalHistoryMenuExtension() : 
    m_cRef(1), 
    m_pSite(NULL),
    m_idMenu(0)
{
    Reset();
    g_dwDLLRefCount++;
}


// **************************************************************************
// Function Name: ~MedicalHistoryMenuExtension
// 
// Purpose: Destructor
//
MedicalHistoryMenuExtension::~MedicalHistoryMenuExtension()
{
    Reset();
    ASSERT(0 == m_cRef);
    g_dwDLLRefCount--;
}

// **************************************************************************
// Function Name: Reset
// 
// Purpose: Releases the m_pSite object
//
void MedicalHistoryMenuExtension::Reset()
{
    RELEASE_OBJ(m_pSite);
}

// **************************************************************************
// Function Name: Intialize
//
HRESULT MedicalHistoryMenuExtension::Initialize() 
{
    return(S_OK);
}

// **************************************************************************
// Function Name: QueryInterface
// 
// Purpose: Returns a pointer to a specified interface 
//
// Arguments:
//    IN  REFIID iid - Interface ID
//    OUT LPVOID ppv - Address of the pointer variable to receive the interface pointer
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT MedicalHistoryMenuExtension::QueryInterface(REFIID iid, LPVOID * ppv)
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
// **************************************************************************
// Function Name: AddRef
// 
// Purpose: Increases the ref count by calling InterlockedIncrement
//
// Return Values:
//    HRESULT indicating success or failure
//
ULONG MedicalHistoryMenuExtension::AddRef() 
{
    return InterlockedIncrement(&m_cRef);
}

// **************************************************************************
// Function Name: Release
// 
// Purpose: Decrease the ref count by calling InterlockedDecrement
//
// Return Values:
//    HRESULT indicating success or failure
//
ULONG MedicalHistoryMenuExtension::Release() 
{
    if(0 == InterlockedDecrement(&m_cRef)) 
    {
        delete this; 
        return(0);
    } 

    return(m_cRef);
}


// IObjectWithSite methods

// **************************************************************************
// Function Name: SetSite
// 
// Purpose: Provides the site's IUnknown pointer to the object.
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT MedicalHistoryMenuExtension::SetSite(IUnknown* pSite)
{
    RELEASE_OBJ(m_pSite);

    if(pSite)
    {
        m_pSite = pSite;
        m_pSite->AddRef();
    }
    return(S_OK);
}

// **************************************************************************
// Function Name: GetSite
// 
// Purpose: Retrieves the last site set with IObjectWithSite::SetSite
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT MedicalHistoryMenuExtension::GetSite(REFIID riid, void** ppvSite)
{
    HRESULT hr = S_OK;
    CBR(m_pSite);
    
    hr = m_pSite->QueryInterface(riid, ppvSite);
    CHR(hr);
    
Error:
    return(hr);
}

// IDispatch methods

// **************************************************************************
// Function Name: QueryContextMenu
// 
// Purpose: Adds command to the shortcut menu.
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT STDMETHODCALLTYPE MedicalHistoryMenuExtension::QueryContextMenu(HMENU hmenu,
    UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
    HRESULT hr = S_OK;
    BOOL bRet;

    m_idMenu = idCmdFirst;

    bRet = InsertMenu(hmenu, indexMenu, MF_BYPOSITION | MF_STRING, m_idMenu, c_szMedicalHistoryMenu);
    CBR(bRet);

Error:
    return(hr);
}

// **************************************************************************
// Function Name: InvokeCommand
// 
// Purpose: Carries out the command associated with the shortcut menu item.
//          This is the function that is called when the user selects the Medical 
//          History menu extension
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT STDMETHODCALLTYPE MedicalHistoryMenuExtension::InvokeCommand(LPCMINVOKECOMMANDINFO lpici)
{
    HRESULT hr = S_OK;
    IDataObject* pobj = NULL;
    STGMEDIUM med = {0};

    if(m_pSite)
    {
        hr = m_pSite->QueryInterface(IID_IDataObject, (void**)&pobj);
        if(SUCCEEDED(hr))
        {
            FORMATETC form = {0};
            form.cfFormat = RegisterClipboardFormat(CFNAME_ITEMREFARRAY);
            form.lindex = -1;
            form.dwAspect = DVASPECT_CONTENT;
            form.tymed = TYMED_HGLOBAL;

            hr = pobj->GetData(&form, &med);
            if(SUCCEEDED(hr))
            {
                // Get the OID for this contact
                ItemRefArray *pIra;
                CEOID oidPatient;
                pIra = (ItemRefArray*)med.hGlobal;
                oidPatient = (CEOID) pIra->rgRefs[0].pRef;
                CBR(oidPatient != 0);

                // This function contains the logic to show the history and 
                // update the store
                CHR(ShowMedicalHistory(oidPatient));
            }
        }
    }

Error:
    ReleaseStgMedium(&med);

    RELEASE_OBJ(pobj);

    return hr;

}


// **************************************************************************
// Function Name: GetCommandString
// 
// Purpose: Retrieves the Menu string.
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT STDMETHODCALLTYPE MedicalHistoryMenuExtension::GetCommandString(UINT_PTR idCmd,
    UINT uType, UINT* pwReserved, LPSTR pszName, UINT cchMax)
{    
    HRESULT hr = S_OK;

    CBR(idCmd == m_idMenu);

    // This interface passes and array of TCHARs casted to LPSTR, 
    // we're just casting it back here
    CHR(StringCchCopy((TCHAR *)pszName, cchMax, c_szMedicalHistoryMenu));

Error:
    return(hr);
}


HRESULT MedicalHistoryMenuExtension::Create(IObjectWithSite** ppNew)
{
    HRESULT hr = S_OK;
    MedicalHistoryMenuExtension* pte = NULL;

    pte = new MedicalHistoryMenuExtension();
    CBR((!pte) || (1 == pte->m_cRef));

    CPR(pte);

    hr = pte->Initialize();
    CHR(hr);

Error:
    if (FAILED(hr))
    {
        delete(pte);
    }
    else
    {
        *ppNew = pte;
    }
    return(hr);
}

// **************************************************************************
// 
// Increase the reference count by one
//
ULONG MedicalHistoryClassFactory::AddRef() 
{ 
    return InterlockedIncrement(&m_cRef);
}

// **************************************************************************
//
// Decrement the reference count, if we get to 
// zero references, delete the object
//
ULONG MedicalHistoryClassFactory::Release() 
{
    if(0 == InterlockedDecrement(&m_cRef)) 
    {
        delete this; 
        return(0);
    } 

    return(m_cRef);
}
// **************************************************************************
// Function Name: MedicalHistoryClassFactory
// 
// Purpose: Constructor
//
MedicalHistoryClassFactory::MedicalHistoryClassFactory() :
    m_cRef(1)
{
}

// **************************************************************************
// Function Name: MedicalHistoryClassFactory
// 
// Purpose: Destructor
//
MedicalHistoryClassFactory::~MedicalHistoryClassFactory()
{
}

// **************************************************************************
// Function Name: QueryInterface
// 
// Purpose: Returns a pointer to the interface 
//
// Arguments:
//    IN  REFIID iid - Interface ID
//    OUT LPVOID ppv - Address of the pointer variable to receive the interface pointer
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT MedicalHistoryClassFactory::QueryInterface
(
    REFIID riid,
    void** ppObject
)
{
    HRESULT hr = S_OK;

    if(riid == IID_IUnknown || riid == IID_IClassFactory)
    {
        *ppObject= (IClassFactory*)this;
    }
    else
    {
        CHR(E_NOINTERFACE);
    }

    AddRef();

Error:
    return(hr);
}

// **************************************************************************
// Function Name: CreateInstance
// 
// Purpose: Returns an interface to a MedicalHistoryMenuExtension
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT MedicalHistoryClassFactory::CreateInstance
(
    IUnknown *pUnkOuter,
    REFIID riid,
    void** ppObject
)
{
    HRESULT hr = S_OK;
    IObjectWithSite* pows = NULL;

    *ppObject = NULL;

    if(pUnkOuter != NULL)
    {
        CHR(CLASS_E_NOAGGREGATION);
    }

    hr = MedicalHistoryMenuExtension::Create(&pows);
    CHR(hr);

    hr = pows->QueryInterface(riid, ppObject);
    CHR(hr);

Error:
    RELEASE_OBJ(pows);

    return hr;
}

// **************************************************************************
// Function Name: LockServer
// 
// Purpose: Increments or decrements the dllrefcount
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT MedicalHistoryClassFactory::LockServer(BOOL fLock)
{
    if(fLock)
    {
        g_dwDLLRefCount++;
    }
    else
    {
        g_dwDLLRefCount--;
    }
    return(S_OK);
}


