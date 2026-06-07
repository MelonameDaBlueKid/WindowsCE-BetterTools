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

    File: MsgForm.h

    Purpose: CMsgForm class definintion

******************************************************************************/
#pragma once

//Forward decl
class CFormProvider;
class CMsgView;
class CMsgViewBase;


/******************************************************************************

    CMsgForm - IMessageFormEx implementation

******************************************************************************/
class CMsgForm : public IMessageFormEx
{
public:

    CMsgForm(IMessageFormHostEx* pHost, LPMESSAGE pMsg);
    ~CMsgForm();

    //IUnknown methods
    MAPIMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
    MAPIMETHOD_(ULONG, AddRef)();
    MAPIMETHOD_(ULONG, Release)();

    MAPIMETHOD(SetMessage)(WORD wType, LPMESSAGE pMsg);
    MAPIMETHOD(CloseForm)(BOOL fSave = FALSE);
    MAPIMETHOD(PreTranslateMsg)(MSG* pMsg, BOOL* pfProcessed);
    MAPIMETHOD(OnMessageModified)(ULONG cbId, LPENTRYID pid, LPSPropTagArray props);
    MAPIMETHOD(DoAction)(FORMACTIONS actForm, DWORD dwValue, BOOL* pfProcessed);
    MAPIMETHOD(GetMenuCapabilities)(DWORD dwFlags, DWORD* pdwEnable);

    //Not part of interface
    MAPIMETHOD(DoAction)(IMessageFormEx* pform, IMessage* pMsg,
        IMessageFormHostEx::HOSTACTIONS act, MESSAGEFIELDS *pMsgFields)
    {
        return m_pHost->DoAction(pform, pMsg, act, pMsgFields);
    }
    MAPIMETHOD(SetMessageStatus)(IMessageFormHostEx::CLOSINGMSGSTATUS status)
    {
        m_eMsgStatus = status;
        return S_OK;
    }

    //NOT PART OF INTERFACE
    MAPIMETHOD(Init)(CFormProvider* pFormProvider, HWND hwndForm, HWND* phwndBody, MESSAGEFIELDS*  pMsgFields);
    
private: 

    //RefCounting
    ULONG m_cRef;

    //For prefilling the form with an existing message's details if necessary.
    WORD      m_wType;

    IMessageFormHostEx* m_pHost;
    LPMESSAGE         m_pMsg;
    CMsgView*         m_pView;   

    //Delete the base message if the user Cancels.
    BOOL m_fDeleteOnClose;

    IMessageFormHostEx::CLOSINGMSGSTATUS m_eMsgStatus;
};