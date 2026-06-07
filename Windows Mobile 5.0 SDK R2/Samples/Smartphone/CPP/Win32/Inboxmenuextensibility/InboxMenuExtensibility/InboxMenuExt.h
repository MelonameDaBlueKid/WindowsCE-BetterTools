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
    HRESULT GetCommandStringHelper(int idCmd, TCHAR *pszName, UINT ccName);
    BOOL IsMessage(ItemRef *pir);
    BOOL IsFolder(ItemRef *pir);
    HRESULT GetItemRefArray(ItemRefArray **ppItemArray);
    BOOL EnableAddSenderToContacts();
    BOOL AreThereMessagesInFolder();
    HRESULT InsertMenuItem(HMENU hmenu, UINT indexMenu, UINT idCmd, LPCTSTR szText);
    HRESULT AddSenderToContacts();
    HRESULT MarkAllInFolderAsRead();
    HRESULT DeleteAllInFolder();
    HRESULT GetWastebasketForFolder(LPMAPIFOLDER pfldr, LPMAPIFOLDER* ppfldrWastebasket);
    HRESULT CreateEntryList(SRowSet *pRows, ENTRYLIST **ppList);
    

    LPMAPISESSION m_pSession;   // class scoped MAPI Session variable
    LONG m_cRef;                // COM refcount
    IUnknown* m_pSite;  //  a pointer to the object in the UI that the menu extension 
                        // will be acting on.
    UINT m_idc1;    // menu command 1
    UINT m_idc2;    // menu command 2
    ExtensionType m_ExtensionType;  // type of extension Context, Softkey, etc..
};


