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
/******************************************************************************

    File: MsgViewBase.h

    Purpose: CMsgViewBase class definintion

******************************************************************************/
#pragma once
#include "stdinc.h"
#include "msgform.h"

#define EDGE_OFFSET 5

/******************************************************************************

    CMsgViewBase - base class for handling the viewing of a message

******************************************************************************/
class CMsgViewBase
{
public:
    CMsgViewBase(CFormProvider* pFormProvider, CMsgForm *pForm, LPMESSAGE pMsg);
    ~CMsgViewBase();

    virtual HRESULT Init(MESSAGEFIELDS*  pMsgFields);
    virtual BOOL Create(HWND hwndForm, HWND* phwndBody);
    virtual BOOL PreTranslateMsg(MSG* pmsg);

    MAPIMETHOD(ShowView)(ULONG ulAction);
    MAPIMETHOD(SetMessage)(WORD wType, LPMESSAGE pmsg);

    HRESULT     OnClose(VOID);

protected:
    virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual BOOL CreateMainWindow(LPCTSTR pszClass, LPCTSTR pszTitle, DWORD dwStyle, LPPOINT pt, LPSIZE pSize, HWND hwndForm, UINT nID) = 0;
    virtual HRESULT FillFromMessage() = 0;

    //Has the window class already been registered?
    static BOOL ms_fRegistered;

    // Main window
    HWND    m_hWnd;
    
    //The message we have to fill from the contents of the view.
    LPMESSAGE m_pMsg;

    //For prefilling the form with an existing message's details if necessary.
    WORD      m_wType;

    //EMS stuff...
    TCHAR*      m_pszUserData;
    BITMAP*     m_pBitmaps;
    UINT        m_uNumBitmaps;

private:

    //Building up the message from the view and sending it...
    HRESULT OnSendCommon(CMsgView *pMsgView);

    
    //Access back to the form so we can tell it that the user wants to close the window.
    CMsgForm *m_pForm;

    //Allow us to get mime parts of messages.
    CFormProvider* m_pFormProvider;

    //A new message form can be initialized with some explicit recipients.
    MESSAGEFIELDS*  m_pMsgFields;
    BOOL            m_fInitWithoutInbox;

    BOOL m_fDeleteOrginal;

    //Store the field with focus so we can set it again on re-activation.
    HWND        m_hWndFocus;
    HWND        m_hWndForm;
    
    int         OnCreate(LPCREATESTRUCT pcs);
    void        OnCommand(WPARAM wParam, LPARAM lParam);
};

