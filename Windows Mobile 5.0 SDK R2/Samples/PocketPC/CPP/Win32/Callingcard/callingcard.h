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

#pragma once

#include <pimstore.h>
///////////////////////////////////////////////////////////////////////////
// Calling card and contact information Structure
//

// Maximum length in chars of the numbers (calling card number and pin) we read in from the registry
#define MAX_NUMBER_LEN 64

typedef struct
{
    BSTR bstrFileAs;    
    BSTR bstrHomeNumber;
    BSTR bstrCellNumber;
    BSTR bstrWorkNumber;
} CINFO, *PCINFO;

typedef struct
{
    TCHAR pszCardNumber[MAX_NUMBER_LEN];
    TCHAR pszPin[MAX_NUMBER_LEN];
    DWORD dwFirstPause;
    DWORD dwSecondPause;
}CARDINFO, *PCARDINFO;

class MenuExtension :
    public IObjectWithSite,
    public IContextMenu
{

    public:
    static HRESULT Create(IObjectWithSite** ppNew, ExtensionType extensionType);

    ///////////////////////////////////////////////////////////////////////////
    // IUnknown Interface Methods
    //
    STDMETHODIMP QueryInterface(REFIID iid, LPVOID * ppv);
    STDMETHODIMP_(ULONG) AddRef(); 
    STDMETHODIMP_(ULONG) Release(); 
    //
    ///////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////
    // IObjectWithSite Interface Methods
    //
    virtual STDMETHODIMP SetSite(IUnknown* pSite);
    virtual STDMETHODIMP GetSite(REFIID riid, void** ppvSite);
    //
    ///////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////
    // IContextMenu Interface Methods
    //
    virtual HRESULT STDMETHODCALLTYPE QueryContextMenu(HMENU hmenu,
        UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
    virtual HRESULT STDMETHODCALLTYPE InvokeCommand(LPCMINVOKECOMMANDINFO lpici);
    virtual HRESULT STDMETHODCALLTYPE GetCommandString(UINT_PTR idCmd,
        UINT uType, UINT* pwReserved, LPSTR pszBad, UINT cchMax);
    //
    ///////////////////////////////////////////////////////////////////////////
    

    private:    
    MenuExtension(ExtensionType extensionType); 
    virtual ~MenuExtension();
    HRESULT Initialize();

    /////// Helpers
    
    HRESULT GetCommandStringHelper(int idCmd, TCHAR *pszName, UINT ccName);
    BOOL GetContactsOidFromSelection(IDataObject *pdo, CEOID *poidOut);
    HRESULT InsertMenuItem(HMENU hmenu, UINT indexMenu, UINT idCmd, LPCTSTR szText); 
    void FreeContactInfo();
    void ClearCardInfo();
    BOOL GetContactInfo();
    HRESULT CallContact(UINT idCmd);
    HRESULT LaunchSettings();
    HRESULT ReadSettings();
    HRESULT BuildDialString(TCHAR *pszBuffer, UINT cchBuffer, TCHAR* pszNumber); 

    private:
    LONG m_cRef;                // COM refcount
    IUnknown* m_pSite;  //  a pointer to the object in the UI that the menu extension 
                        // will be acting on.
    UINT m_idcCallCell;    // menu commands
    UINT m_idcCallWork;
    UINT m_idcCallHome;

    IPOutlookApp2 *m_polApp;
    
    BOOL m_fInitialized;   // Have we read in 
    ExtensionType m_ExtensionType;  // type of extension Context, Softkey, etc..
    CINFO m_contactInfo;    // Highlighted contact info
    CARDINFO m_cardInfo;    // Calling card parameters
};


