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


