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
    static HRESULT Create(IObjectWithSite** ppNew);

    MenuExtension(); 
    virtual ~MenuExtension();


    ///////////////////////////////////////////////////////////////////////////////
    // IUnknown Interface Methods
    //
    STDMETHODIMP QueryInterface(REFIID iid, LPVOID * ppv);
    STDMETHODIMP_(ULONG) AddRef(); 
    STDMETHODIMP_(ULONG) Release(); 
    //
    ///////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////
    // IObjectWithSite Interface Methods
    //
    virtual STDMETHODIMP SetSite(IUnknown* pSite);
    virtual STDMETHODIMP GetSite(REFIID riid, void** ppvSite);
    //
    ///////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////
    // IContextMenu Interface Methods
    //
    virtual HRESULT STDMETHODCALLTYPE QueryContextMenu(HMENU hmenu,
        UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
    virtual HRESULT STDMETHODCALLTYPE InvokeCommand(LPCMINVOKECOMMANDINFO lpici);
    virtual HRESULT STDMETHODCALLTYPE GetCommandString(UINT_PTR idCmd,
        UINT uType, UINT* pwReserved, LPSTR pszBad, UINT cchMax);
    //
    ///////////////////////////////////////////////////////////////////////////////
    

    private:      
    HRESULT Initialize();
    
    BOOL IsReplyUsingEnabled(void);
    HRESULT InsertMenuItem(HMENU hmenu, UINT indexMenu, UINT idCmd, LPCTSTR szText);
    HRESULT ReplyUsing();
    HRESULT GetSubjectForReply(LPCTSTR pszOriginal, LPTSTR* ppszReplySubject);
    HRESULT GetBodyForReply(LPTSTR pszOriginal, LPTSTR* ppszReplyBody);

    BOOL IsMessage(ItemRef *pir);    
    BOOL IsMessageFormEx(ItemRef *pir);
    HRESULT GetItemRefArray(ItemRefArray **ppItemArray);
    HRESULT GetIMAPIPropForMsg(IMAPIProp** ppProp);

    private:
    LPMAPISESSION m_pSession;   // class scoped MAPI Session variable
    LONG m_cRef; // COM refcount
    IUnknown* m_pSite;
    UINT m_idc;    // menu command
};


