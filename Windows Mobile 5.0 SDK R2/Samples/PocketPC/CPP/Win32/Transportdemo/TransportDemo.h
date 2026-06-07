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





#define HrFromWSAError(x) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_INTERNET, (x))





#include <cemapi.h>



class CTransportSyncHandler : public IMailSyncHandler
{
public:
    CTransportSyncHandler();
    ~CTransportSyncHandler();
    
    virtual HRESULT STDMETHODCALLTYPE   QueryInterface  (REFIID rif, LPVOID * ppobj);
    virtual ULONG   STDMETHODCALLTYPE   AddRef();
    virtual ULONG   STDMETHODCALLTYPE   Release();


    MAPIMETHOD (Initialize) 
    (
        IMailSyncCallBack   *   pCallback,
        LPCWSTR                 pszProfileName,
        IMsgStore           *   pMsgStore
    );
    
    MAPIMETHOD (Synchronize) 
    (
        MAILSYNCREQUEST     *   pRqst
    );
    
    MAPIMETHOD (ShutDown) 
    (
        DWORD                   dwReserved
    );
    
    MAPIMETHOD (Install) 
    (
        LPCWSTR                 pszProfileName,
        LPCWSTR                 pszIncomingServer,
        LPCWSTR                 pszOutgoingServer,
        GUID                *   pidNetwork
    );
    
    MAPIMETHOD (UnInstall) 
    (
    );
    
    
    MAPIMETHOD (Connect) 
    (
        DWORD                   dwReserved,
        SYNCCREDENTIALS     *   pCredentials
    );
    
    MAPIMETHOD (Disconnect) 
    (
        DWORD                   dwReserved
    );

    MAPIMETHOD (DoProperties)
    (
        HWND                    hwndParent
    );
    
    MAPIMETHOD (GetCapability)
    (
        LPCWSTR                 pszName, 
        LPSPropValue            pval
    );

    MAPIMETHOD (SetCapability)
    (
        LPCWSTR pszName, 
        LPSPropValue pval
    );

    MAPIMETHOD (DecodeEvent)
    (
        TRANSPORTEVENT      *   pevt,
        LPWSTR              *   ppszEvent
    );

    MAPIMETHOD (GetFolderHierarchy)
    (
        FOLDERNODE          **  ppRootNode
    );    


    MAPIMETHOD (SetFolderOptions)
    (
        LPMAPIFOLDER            pfldr,
        FOLDERNODE          *   pnode,
        FOLDEROPTIONS           opts,
        LPSPropValue            pval
    );



protected:
    IMsgStore           *   m_pMsgStore;
    IMailSyncCallBack   *   m_pCallback;
    ULONG                   m_cRef;     
    BOOL                    m_fShutDown;
    SYNCPROGRESSITEM        m_SyncProgressItemPending;
    ULONG                   m_nDeleteAction;
    LPWSTR                  m_pszProfile;
    HANDLE                  m_hEventShutdown;
    
    
    
    void    SetStatusText                   (UINT nId);
    void    SendProgressMessage             (DWORD dwMask);
    void    HandlePendingProgressItem       (void);
    HRESULT LogErrorEvent                   (HRESULT hr, ULONG cbData);
    HRESULT OnFolderOptions_Download        (LPMAPIFOLDER pfldr, LPSPropValue pval);
    HRESULT OnFolderOptions_QueryDownload   (LPMAPIFOLDER pfldr, LPSPropValue pval);
    HRESULT OnFolderOptions_Create          (LPMAPIFOLDER * pfldr);
    HRESULT OnFolderOptions_QueryCreate     (LPMAPIFOLDER pfldr, LPSPropValue pval);
    HRESULT OnFolderOptions_SetFetchOption  (FOLDEROPTIONS opts, LPMAPIFOLDER pfldr, LPSPropValue pval);
    HRESULT OnFolderOptions_GetFetchOption  (FOLDEROPTIONS opts, LPMAPIFOLDER pfldr, LPSPropValue pval);
};


