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

#include <windows.h>
#include <CmNet.h>
#include <ProxyDBS.h>



class BaseCmWrapper
{
public:
    BaseCmWrapper()
        : m_mod(NULL)
    {
    }
    virtual ~BaseCmWrapper()
    {
        DeInit();
    }

    virtual BOOL Init() = 0;

    virtual void DeInit()
    {
        if (m_mod)
        {
            FreeLibrary(m_mod);
            m_mod = NULL;
        }
    }

    virtual BOOL IsInitialized() const
    {
        return m_mod != NULL;
    }

protected:
    HMODULE m_mod;
};


#define INIT_FUNC_MEMBER(name,sname) \
            if (error == ERROR_SUCCESS) { \
                FARPROC proc = GetProcAddressW(m_mod, sname); \
                if (proc) { \
                    m_pfn##name = (PFN_##name)proc; \
                } else { \
                    error = GetLastError(); \
                    if (error == ERROR_SUCCESS) { \
                        ASSERT(!"GLE shouldn't be ERROR_SUCCESS when GetProcAddress returns NULL."); \
                        error = (DWORD)E_FAIL; \
                    } \
                    DEBUGMSG(1, (L"[CmWrapper::Init] GetProcAddress failed on \"%s\", GLE=%u.\r\n", sname, error)); \
                } \
            }


/////////////////////////////////////////////////////////////////////////
//
// Wrapper to allow delayed load of CmNet.dll.
// When adding or changing the function signature, search for "TASK:" in this file.
//
class CmWrapper : public BaseCmWrapper
{
public:
    virtual BOOL Init()
    {
        DWORD error = ERROR_SUCCESS;

        // Should not have been initialized already.
        ASSERT(!m_mod);
        m_mod = LoadLibraryW(L"CmNet.dll");

        if (m_mod)
        {
            //
            // TASK: When adding a new API...
            // [1] Do GetProc here.
            //

            INIT_FUNC_MEMBER(CmIsServiceAvailable, L"CmIsServiceAvailable");

            // Initialization APIs
            INIT_FUNC_MEMBER(CmApiInit, L"CmApiInit");
            INIT_FUNC_MEMBER(CmApiDeinit, L"CmApiDeinit");

            // Session API's...
            INIT_FUNC_MEMBER(CmCreateSession, L"CmCreateSession");
            INIT_FUNC_MEMBER(CmCreateSessionReference, L"CmCreateSessionReference");
            INIT_FUNC_MEMBER(CmCloseSession, L"CmCloseSession");
            INIT_FUNC_MEMBER(CmSetRequirements, L"CmSetRequirements");
            INIT_FUNC_MEMBER(CmSetPreferences, L"CmSetPreferences");

            // Connection API's...
            INIT_FUNC_MEMBER(CmGetFirstCandidateConnection, L"CmGetFirstCandidateConnection");
            INIT_FUNC_MEMBER(CmGetNextCandidateConnection, L"CmGetNextCandidateConnection");
            INIT_FUNC_MEMBER(CmGetConnectionDetailsByHandle, L"CmGetConnectionDetailsByHandle");
            INIT_FUNC_MEMBER(CmAcquireConnection, L"CmAcquireConnection");
            INIT_FUNC_MEMBER(CmReleaseConnection, L"CmReleaseConnection");

            // address resolver API's...
            INIT_FUNC_MEMBER(CmGetFirstIpAddr, L"CmGetFirstIpAddr");
            INIT_FUNC_MEMBER(CmGetNextIpAddr, L"CmGetNextIpAddr");

            //config API's...
            INIT_FUNC_MEMBER(CmAddConnectionConfig, L"CmAddConnectionConfig");
            INIT_FUNC_MEMBER(CmGetToUpdateConnectionConfig, L"CmGetToUpdateConnectionConfig");
            INIT_FUNC_MEMBER(CmUpdateConnectionConfig, L"CmUpdateConnectionConfig");
            INIT_FUNC_MEMBER(CmDeleteConnectionConfig, L"CmDeleteConnectionConfig");
            INIT_FUNC_MEMBER(CmGetToUpdatePolicyConfig, L"CmGetToUpdatePolicyConfig");
            INIT_FUNC_MEMBER(CmUpdatePolicyConfig, L"CmUpdatePolicyConfig");

            if (error == ERROR_SUCCESS)
            {
                BOOL fResult = TRUE;
                fResult = m_pfnCmApiInit();

                if (fResult == FALSE)
                {
                    DEBUGMSG(1, (L"[CmWrapper::Init] Found the dll, but CmApiInit failed \r\n"));
                    ASSERT(!"CmApiInit failed");
                    DeInit();
                    goto quit;
                }

                if (!m_pfnCmIsServiceAvailable())
                {
                    DEBUGMSG(1, (L"[CmWrapper::Init] Found the dll, but the service is not available.\r\n"));
                    DeInit();
                }
            }
            else // One of the GetProc failed.
            {
                ASSERT(!"Found the dll, but could not load one of the exported functions.");
                DeInit();
            }
        } // if (m_mod)

    quit:
        return m_mod != NULL;
    }

    virtual void DeInit()
    {
        if (m_mod && m_pfnCmApiDeinit)
        {
            m_pfnCmApiDeinit();
        }

        BaseCmWrapper::DeInit();
    }

    //
    // TASK: When adding a new API...
    // [2] Add the new wrapper function here.
    //

    CM_SESSION_HANDLE CmCreateSession()
    {
        ASSERT(IsInitialized());
        CM_SESSION_HANDLE sess = m_pfnCmCreateSession();
        return sess;
    }

    CM_SESSION_HANDLE CmCreateSessionReference(
        CM_SESSION_HANDLE hSession)
    {
        ASSERT(IsInitialized());
        CM_SESSION_HANDLE clonedSess = m_pfnCmCreateSessionReference(hSession);
        return clonedSess;
    }

    CM_RESULT CmCloseSession(
        CM_SESSION_HANDLE hSession)
    {
        ASSERT(IsInitialized());
        return m_pfnCmCloseSession(hSession);
    }
    
    CM_RESULT CmGetFirstCandidateConnection(
        __in const CM_SESSION_HANDLE hSession,
        __in const WCHAR* const pszHost,
        __in const CM_CONNECTION_SELECTION_OPTION Option,
        __out CM_CONNECTION_HANDLE* phConnection)
    {
        ASSERT(IsInitialized());
        return m_pfnCmGetFirstCandidateConnection(
            hSession,
            pszHost,
            Option,
            phConnection);
    }

    CM_RESULT CmGetNextCandidateConnection(
        __in const CM_SESSION_HANDLE hSession,
        __out CM_CONNECTION_HANDLE* phConnection)
    {
        ASSERT(IsInitialized());
        return m_pfnCmGetNextCandidateConnection(
            hSession,
            phConnection);
    }

    CM_RESULT CmGetConnectionDetailsByHandle(
        __in CM_CONNECTION_HANDLE hConnection,
        __out_bcount_opt(*pcbDetails) CM_CONNECTION_DETAILS* pDetails,
        __inout DWORD* pcbDetails)
    {
        ASSERT(IsInitialized());
        return m_pfnCmGetConnectionDetailsByHandle(
            hConnection,
            pDetails,
            pcbDetails);
    }

    CM_RESULT CmAcquireConnection(
        __in const CM_CONNECTION_HANDLE hConnection)
    {
        ASSERT(IsInitialized());
        return m_pfnCmAcquireConnection(hConnection);
    }

    CM_RESULT CmReleaseConnection(
        __in const CM_CONNECTION_HANDLE hConnection)
    {
        ASSERT(IsInitialized());
        return m_pfnCmReleaseConnection(hConnection);
    }

    CM_RESULT CmGetFirstIpAddr(
        __in const CM_CONNECTION_HANDLE hConnection,
        __in const WCHAR* const pszHost,
        __in const ADDRESS_FAMILY AddrFamily,
        __in const USHORT SrcPort,
        __in const USHORT DstPort,
        __out_bcount_opt(*pcbAddressPair) CM_ADDRESS_PAIR* pAddressPair,
        __inout DWORD* pcbAddressPair)
    {
        ASSERT(IsInitialized());
        return m_pfnCmGetFirstIpAddr(
            hConnection,
            pszHost,
            AddrFamily,
            SrcPort,
            DstPort,
            pAddressPair,
            pcbAddressPair);
    }

    CM_RESULT CmGetNextIpAddr(
        __in const CM_CONNECTION_HANDLE hConnection,
        __out_bcount_opt(*pcbAddressPair) CM_ADDRESS_PAIR* pAddressPair,
        __inout DWORD* pcbAddressPair)
    {
        return m_pfnCmGetNextIpAddr(
            hConnection,
            pAddressPair,
            pcbAddressPair);
    }

    CM_RESULT CmSetRequirements(
        __in CM_SESSION_HANDLE hSession,
        __in_bcount(cbRequirements) const CM_REQUIREMENTS* pRequirements,
        __in DWORD cbRequirements)
    {
        ASSERT(IsInitialized());
        return m_pfnCmSetRequirements(
            hSession,
            pRequirements,
            cbRequirements);
    }

    CM_RESULT CmSetPreferences(
        __in CM_SESSION_HANDLE hSession,
        __in_bcount(cbPreferences) const CM_PREFERENCES* pPreferences,
        __in DWORD cbPreferences)
    {
        ASSERT(IsInitialized());
        return m_pfnCmSetPreferences(
            hSession,
            pPreferences,
            cbPreferences);
    }

    //
    // Configuration API's
    //

    CM_RESULT CmAddConnectionConfig(
        __in const WCHAR* pszConnection,
        __in_bcount(cbConfig) CM_CONNECTION_CONFIG* pConfig,
        __in DWORD cbConfig)
    {
        ASSERT(IsInitialized());
        return m_pfnCmAddConnectionConfig( 
            pszConnection, 
            pConfig, 
            cbConfig );
    }

    CM_RESULT CmGetToUpdateConnectionConfig(
        __in const WCHAR* pszConnection,
        __inout_bcount(*pcbConfig) CM_CONNECTION_CONFIG* pConfig,
        __inout DWORD* pcbConfig,
        __out CM_CONFIG_CHANGE_HANDLE* phConfig)
    {
        ASSERT(IsInitialized());
        return m_pfnCmGetToUpdateConnectionConfig( 
            pszConnection, 
            pConfig, 
            pcbConfig, 
            phConfig );
    }

    CM_RESULT CmUpdateConnectionConfig(
        __in CM_CONFIG_CHANGE_HANDLE hConfig,
        __in CM_CONFIG_OPTION Option,
        __in_bcount(cbConfig) CM_CONNECTION_CONFIG* pConfig,
        __in DWORD cbConfig)
    {
        ASSERT(IsInitialized());
        return m_pfnCmUpdateConnectionConfig( hConfig, Option, pConfig, cbConfig );
    }


    CM_RESULT CmDeleteConnectionConfig(
        __in const WCHAR* pszConnection)
    {
        ASSERT(IsInitialized());
        return m_pfnCmDeleteConnectionConfig( pszConnection );
    }

    CM_RESULT CmGetToUpdatePolicyConfig(
        __in_bcount(cbKey) CM_POLICY_CONFIG_KEY* pKey,
        __in DWORD cbKey,
        __out_bcount(*pcbData) CM_POLICY_CONFIG_DATA* pData,
        __inout DWORD* pcbData,   
        __out CM_CONFIG_CHANGE_HANDLE* phConfig)
    {
        ASSERT(IsInitialized());
        return m_pfnCmGetToUpdatePolicyConfig(pKey, cbKey, pData, pcbData, phConfig);
    }
  
     CM_RESULT CmUpdatePolicyConfig(
        __in CM_CONFIG_CHANGE_HANDLE hConfig,
        __in_bcount(cbData) CM_POLICY_CONFIG_DATA* pData,
        __in DWORD cbData)
     {
        ASSERT(IsInitialized());
        return m_pfnCmUpdatePolicyConfig(hConfig, pData,cbData); 
     }

private:
    //
    // TASK: When adding a new API...
    // [3] Typedef the function signature.
    // [4] Add the member pointer of the new function signature here.
    //

    typedef BOOL (WINAPI* PFN_CmIsServiceAvailable)();
    PFN_CmIsServiceAvailable m_pfnCmIsServiceAvailable;

    //
    // Initialization API's
    //

    typedef BOOL (WINAPI* PFN_CmApiInit)();
    PFN_CmApiInit m_pfnCmApiInit;

    typedef void (WINAPI* PFN_CmApiDeinit)();
    PFN_CmApiDeinit m_pfnCmApiDeinit;

    //
    // Session API's...
    //
    
    typedef CM_SESSION_HANDLE (WINAPI* PFN_CmCreateSession)();
    PFN_CmCreateSession m_pfnCmCreateSession;

    typedef CM_SESSION_HANDLE (WINAPI* PFN_CmCreateSessionReference)(
        __in CM_SESSION_HANDLE hSession);
    PFN_CmCreateSessionReference m_pfnCmCreateSessionReference;
    
    typedef CM_RESULT (WINAPI* PFN_CmSetRequirements)(
        __in CM_SESSION_HANDLE hSession,
        __in_bcount(cbRequirements) const CM_REQUIREMENTS* pRequirements,
        __in DWORD cbRequirements);
    PFN_CmSetRequirements m_pfnCmSetRequirements;

    typedef CM_RESULT (WINAPI* PFN_CmSetPreferences)(
        __in CM_SESSION_HANDLE hSession,
        __in_bcount(cbPreferences) const CM_PREFERENCES* pPreferences,
        __in DWORD cbPreferences);
    PFN_CmSetPreferences m_pfnCmSetPreferences;
    
    typedef CM_RESULT (WINAPI* PFN_CmCloseSession)(
        __in CM_SESSION_HANDLE hSession);
    PFN_CmCloseSession  m_pfnCmCloseSession;


    //
    // Connection API's...
    //
    
    typedef CM_RESULT (WINAPI* PFN_CmGetFirstCandidateConnection)(
        __in const CM_SESSION_HANDLE hSession,
        __in const WCHAR* const pszHost,
        __in const CM_CONNECTION_SELECTION_OPTION Option,
        __out CM_CONNECTION_HANDLE* phConnection);
    PFN_CmGetFirstCandidateConnection m_pfnCmGetFirstCandidateConnection;

    typedef CM_RESULT (WINAPI* PFN_CmGetNextCandidateConnection)(
        __in const CM_SESSION_HANDLE hSession,
        __out CM_CONNECTION_HANDLE* phConnection);
    PFN_CmGetNextCandidateConnection m_pfnCmGetNextCandidateConnection;

    typedef CM_RESULT (WINAPI* PFN_CmGetConnectionDetailsByHandle)(
        __in CM_CONNECTION_HANDLE hConnection,
        __out_bcount_opt(*pcbDetails) CM_CONNECTION_DETAILS* pDetails,
        __inout DWORD* pcbDetails);
    PFN_CmGetConnectionDetailsByHandle m_pfnCmGetConnectionDetailsByHandle;

    typedef CM_RESULT (WINAPI* PFN_CmAcquireConnection)(
        __in const CM_CONNECTION_HANDLE hConnection);
    PFN_CmAcquireConnection m_pfnCmAcquireConnection;

    typedef CM_RESULT (WINAPI* PFN_CmReleaseConnection)(
        __in const CM_CONNECTION_HANDLE hConnection);
    PFN_CmReleaseConnection m_pfnCmReleaseConnection;


    //
    // Address enumeration API's...
    //

    typedef CM_RESULT (WINAPI* PFN_CmGetFirstIpAddr)(
        __in const CM_CONNECTION_HANDLE hConnection,
        __in const WCHAR* const pszHost,
        __in const ADDRESS_FAMILY AddrFamily,
        __in const USHORT SrcPort,
        __in const USHORT DstPort,
        __out_bcount_opt(*pcbAddressPair) CM_ADDRESS_PAIR* pAddressPair,
        __inout DWORD* pcbAddressPair);
    PFN_CmGetFirstIpAddr m_pfnCmGetFirstIpAddr;

    typedef CM_RESULT (WINAPI* PFN_CmGetNextIpAddr)(
        __in const CM_CONNECTION_HANDLE hConnection,
        __out_bcount_opt(*pcbAddressPair) CM_ADDRESS_PAIR* pAddressPair,
        __inout DWORD* pcbAddressPair);
    PFN_CmGetNextIpAddr m_pfnCmGetNextIpAddr;

    //
    // Configuration API's
    //

    typedef CM_RESULT (WINAPI* PFN_CmAddConnectionConfig)(
        __in const WCHAR* pszConnection,
        __in_bcount(cbConfig) CM_CONNECTION_CONFIG* pConfig,
        __in DWORD cbConfig);
    PFN_CmAddConnectionConfig m_pfnCmAddConnectionConfig;

    typedef CM_RESULT (WINAPI* PFN_CmGetToUpdateConnectionConfig)(
    __in const WCHAR* pszConnection,
    __inout_bcount(*pcbConfig) CM_CONNECTION_CONFIG* pConfig,
    __inout DWORD* pcbConfig,
    __out CM_CONFIG_CHANGE_HANDLE* phConfig);
    PFN_CmGetToUpdateConnectionConfig m_pfnCmGetToUpdateConnectionConfig;

    typedef CM_RESULT (WINAPI* PFN_CmUpdateConnectionConfig)(
        __in CM_CONFIG_CHANGE_HANDLE hConfig,
        __in CM_CONFIG_OPTION Option,
        __in_bcount(cbConfig) CM_CONNECTION_CONFIG* pConfig,
        __in DWORD cbConfig);
    PFN_CmUpdateConnectionConfig m_pfnCmUpdateConnectionConfig;


    typedef CM_RESULT (WINAPI* PFN_CmDeleteConnectionConfig)(
        __in const WCHAR* pszConnection);
    PFN_CmDeleteConnectionConfig m_pfnCmDeleteConnectionConfig;

    typedef CM_RESULT (*PFN_CmGetToUpdatePolicyConfig)(
        __in_bcount(cbKey) CM_POLICY_CONFIG_KEY* pKey,
        __in DWORD cbKey,
        __out_bcount(*pcbData) CM_POLICY_CONFIG_DATA* pData,
        __inout DWORD* pcbData,   
        __out CM_CONFIG_CHANGE_HANDLE* phConfig);
     PFN_CmGetToUpdatePolicyConfig m_pfnCmGetToUpdatePolicyConfig;

     typedef CM_RESULT (*PFN_CmUpdatePolicyConfig)(
        __in CM_CONFIG_CHANGE_HANDLE hConfig,
        __in_bcount(cbData) CM_POLICY_CONFIG_DATA* pData,
        __in DWORD cbData);
     PFN_CmUpdatePolicyConfig m_pfnCmUpdatePolicyConfig;

};


/////////////////////////////////////////////////////////////////////////
//
// Wrapper to allow delayed load of ProxyDBS.dll.
// When adding or changing the function signature, search for "TASK:" in this file.
//
class CmProxyWrapper : public BaseCmWrapper
{
public:
    virtual BOOL Init()
    {
        DWORD error = ERROR_SUCCESS;

        // Should not have been initialized already.
        ASSERT(!m_mod);
        m_mod = LoadLibraryW(L"ProxyDBS.dll");

        if (m_mod)
        {
            //
            // TASK: When adding a new API...
            // [1] Do GetProc here.
            //

            INIT_FUNC_MEMBER(PsInit, L"PsInit");
            INIT_FUNC_MEMBER(PsDeInit, L"PsDeInit");

            INIT_FUNC_MEMBER(PsGetProxy, L"PsGetProxy");
            INIT_FUNC_MEMBER(PsFreeGetProxy, L"PsFreeGetProxy");

            INIT_FUNC_MEMBER(PsSetProxy, L"PsSetProxy");
            INIT_FUNC_MEMBER(PsDelProxy, L"PsDelProxy");


            if (error == ERROR_SUCCESS)
            {
                error = m_pfnPsInit();

                if (error != ERROR_SUCCESS)
                {
                    DEBUGMSG(1, (L"[CmProxyWrapper::Init] Found the dll, but PsInit failed with error=%u.\r\n",
                        error));
                    ASSERT(!"PsInit failed");
                    DeInit();
                }
            }
            else // One of the GetProc failed.
            {
                ASSERT(!"Found the dll, but could not load one of the exported functions.");
                DeInit();
            }
        } // if (m_mod)

        return m_mod != NULL;
    }

    virtual void DeInit()
    {
        if (m_mod && m_pfnPsDeInit)
        {
            DWORD error = m_pfnPsDeInit();

            if (error != ERROR_SUCCESS)
            {
                DEBUGMSG(1, (L"Could not cleanup CM proxy service, PsDeInit error=%u.\r\n", error));
            }
        }

        BaseCmWrapper::DeInit();
    }

    //
    // TASK: When adding a new API...
    // [2] Add the new wrapper function here.
    //

    DWORD PsGetProxy(
        __in const wchar_t* strConnectName,
        __in const PS_PROXYTYPE Type,
        __out PS_PROXYINFO* pProxyInfo)
    {
        ASSERT(IsInitialized());
        return m_pfnPsGetProxy(
            strConnectName,
            Type,
            pProxyInfo);
    }

    DWORD PsFreeGetProxy(
        __inout PS_PROXYINFO* pProxyInfo)
    {
        ASSERT(IsInitialized());
        return m_pfnPsFreeGetProxy(
            pProxyInfo);
    }

    DWORD PsSetProxy(
        __in const wchar_t* strConnectionName,
        __in const PS_PROXYTYPE Type,
        __in const PS_PROXYINFO* pProxyInfo)
    {
        ASSERT(IsInitialized());
        return m_pfnPsSetProxy(
            strConnectionName,
            Type,
            pProxyInfo);
    }

    DWORD PsDelProxy(
        __in const wchar_t* strConnectionName,
        __in const PS_PROXYTYPE Type)
    {
        ASSERT(IsInitialized());
        return m_pfnPsDelProxy(
            strConnectionName,
            Type);
    }


private:
    //
    // TASK: When adding a new API...
    // [3] Typedef the function signature.
    // [4] Add the member pointer of the new function signature here.
    //


    //
    // Startup / Shutdown API's...
    //

    typedef DWORD (WINAPI* PFN_PsInit)();
    PFN_PsInit m_pfnPsInit;

    typedef DWORD (WINAPI* PFN_PsDeInit)();
    PFN_PsDeInit m_pfnPsDeInit;


    //
    // GET API's...
    //

    typedef DWORD (WINAPI* PFN_PsGetProxy)(
        __in const wchar_t* strConnectName,
        __in const PS_PROXYTYPE Type,
        __out PS_PROXYINFO* pProxyInfo);
    PFN_PsGetProxy m_pfnPsGetProxy;

    typedef DWORD (WINAPI* PFN_PsFreeGetProxy)(
        __inout PS_PROXYINFO* pProxyInfo);
    PFN_PsFreeGetProxy m_pfnPsFreeGetProxy;


    //
    // SET API's...
    //

    typedef DWORD (WINAPI* PFN_PsSetProxy)(
        __in const wchar_t* strConnectionName,
        __in const PS_PROXYTYPE Type,
        __in const PS_PROXYINFO* pProxyInfo);
    PFN_PsSetProxy m_pfnPsSetProxy;

    typedef DWORD (WINAPI* PFN_PsDelProxy)(
        __in const wchar_t* strConnectionName,
        __in const PS_PROXYTYPE Type);
    PFN_PsDelProxy m_pfnPsDelProxy;

};

