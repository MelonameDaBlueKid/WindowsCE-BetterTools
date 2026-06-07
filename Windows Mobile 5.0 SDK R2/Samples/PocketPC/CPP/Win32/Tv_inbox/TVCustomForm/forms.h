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

class CFormProvider : 
    public IFormProviderEx
{
public:
    // Constructor and destructor
    CFormProvider();
    ~CFormProvider();

    // IFormProvider methods
    MAPIMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
    MAPIMETHOD_(ULONG, AddRef)();
    MAPIMETHOD_(ULONG, Release)();

    MAPIMETHOD(GetMsgStatusIconIndex)(
            LPMAPIFOLDER    pfldr,          // Folder for message
            LPENTRYID       pid,            // Id of message
            ULONG           cbid,           // count of bytes for the id
            ULONG           ffFlags,        // Flags for the message
            ULONG           ffStatus,       // Status for the message
            LPCWSTR         pszMsgClass, 
            ULONG           cAttachments,
            ULONG*          pnIndex         // OUT: Index for the correct glyph
    );

    MAPIMETHOD(CreateComposeForm)(
            IMessageFormHostEx* pHost, 
            LPMESSAGE       pMsg,       // Object to compose
            FORMTYPE        eFormType,  // Reply, Reply All, Forward
            LPMESSAGE       pMsgBase,   // Message to prefill the form if necessary
            MESSAGEFIELDS*  pMsgFields, // message fields for the new message
            HWND            hwndForm,   // HWND of the form frame
            HWND*           phwndBody,  // HWND of the form-created body
            IMessageFormEx**  ppForm    // Form object
    );

    MAPIMETHOD(CreateReadForm)(
            IMessageFormHostEx* pHost,
            LPMESSAGE       pMsg,       // Object to read
            HWND            hwndForm,   // HWND of the form frame
            HWND*           phwndBody,  // HWND of the form-created body
            IMessageFormEx**  ppForm    // Form object
    );

    // Other public methods
    MAPIMETHOD(Init)(LPCWSTR pszMessageClass);


private:
    HRESULT CleanUpReadForm(VOID);

    ULONG           m_cRef;
    LPTSTR          m_pszMessageClass;
    ICEMAPISession* m_pSession;
    IMsgStore*      m_pMsgStore;
    LPMESSAGE       m_pMsg;
};

class CMsgView;

// Message form class to do stuff both Read and Write require.
class CMsgForm : public IMessageFormEx
{
public:

    CMsgForm(IMessageFormHostEx* pHost, LPMESSAGE pMsg, BOOL fCompose);
    ~CMsgForm();

    MAPIMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
    MAPIMETHOD_(ULONG, AddRef)();
    MAPIMETHOD_(ULONG, Release)();

    MAPIMETHOD(Init)(CFormProvider* pFormProvider, HWND hwndForm, HWND* phwndBody, MESSAGEFIELDS*  pMsgFields);

    MAPIMETHOD(CloseForm)(BOOL fSave = FALSE);

    MAPIMETHOD(PreTranslateMsg)(MSG* pMsg, BOOL* pfProcessed);

    MAPIMETHOD(SetMessage)(WORD wType, LPMESSAGE pMsg);

    MAPIMETHOD(GetActiveMessage)(LPMESSAGE*  /*ppMsg*/)
    {
        return S_OK;
    }

    MAPIMETHOD(OnMessageModified)(ULONG /*cbId*/, LPENTRYID /*pid*/, LPSPropTagArray /*props*/)
    {
        return S_OK;
    }

    MAPIMETHOD(SetCaptionText)(LPCWSTR /*pszCaptionText*/)
    {
        return S_OK;
    }

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

    MAPIMETHOD(DoAction)(FORMACTIONS actForm, DWORD dwValue, BOOL* pfProcessed);
    MAPIMETHOD(GetMenuCapabilities)(DWORD dwFlags, DWORD* pdwEnable);
    
private: 

    // RefCounting
    ULONG m_cRef;

    // For prefilling the form with an existing message's details if necessary.
    WORD      m_wType;
    LPMESSAGE m_pMsgBase;

    BOOL m_fCompose;

    CMsgView* m_pView;

    IMessageFormHostEx* m_pHost;
    LPMESSAGE         m_pMsg;

    IMessageFormHostEx::CLOSINGMSGSTATUS m_eMsgStatus;
    HWND m_hwndParent;
};
