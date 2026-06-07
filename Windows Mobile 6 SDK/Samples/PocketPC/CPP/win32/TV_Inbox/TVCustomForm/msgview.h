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

class CMsgView
{
public:

    CMsgView(CFormProvider* pFormProvider, CMsgForm *pForm, LPMESSAGE pMsg, LPMESSAGE pMsgBase, BOOL fCompose);
    ~CMsgView();

    virtual HRESULT Init(MESSAGEFIELDS*  pMsgFields);
    virtual BOOL Create(HWND hwndForm, HWND* phwndBody);

    virtual BOOL PreTranslateMsg(MSG* pmsg);
    
    MAPIMETHOD(ShowView)(ULONG ulAction);

    MAPIMETHOD(SetMessage)(
            WORD            wType, 
            LPMESSAGE       pmsg
    );


protected:
    virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual BOOL CreateTVWindow(LPCTSTR pszClass, LPCTSTR pszTitle, DWORD dwStyle, LPRECT pRC, HWND hwndForm, UINT nID);

    // Has the window class already been registered?
    static BOOL ms_fRegistered;

    // Main window
    HWND        m_hWnd;

private:
    static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Building up the message from the view and sending it...
    HRESULT OnSendCommon(CMsgView *pMsgView);

    // The message we have to fill from the contents of the view.
    LPMESSAGE m_pMsg;

    // For prefilling the form with an existing message's details if necessary.
    WORD      m_wType;
    LPMESSAGE m_pMsgBase;

    // Access back to the form so we can tell it that the user wants to close the window.
    CMsgForm *m_pForm;
    HWND m_hWndForm;

    // Allow us to get mime parts of messages.
    CFormProvider* m_pFormProvider;

    BOOL m_fCompose;

private:
    int         OnCreate(LPCREATESTRUCT pcs);
    void        OnCommand(WPARAM wParam, LPARAM lParam);
    void        OnPaint(HDC hdc);
    void        AddToField();
};


