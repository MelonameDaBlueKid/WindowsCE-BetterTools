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


#include "stdafx.h"
#include "TransportDemo.h"

HRESULT Transport_OneStopFactory(
    IMailSyncHandler ** ppSyncHandler
    );

HINSTANCE g_hInst = NULL;


/////////////////////////////////////////////////////////////////////////////
//
// DllMain()
//
// DLL entry point.  Perform module initialization and clean-up.
//
/////////////////////////////////////////////////////////////////////////////

BOOL WINAPI DllMain(
    HANDLE hinstDLL, 
    DWORD dwReason, 
    LPVOID lpvReserved
    )
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Save the DLL's handle
        g_hInst =(HINSTANCE) hinstDLL;

        // We don't need DLL_THREAD_ATTACH/DLL_THREAD_DETACH notifications here
        // so we can disable them.
        DisableThreadLibraryCalls((HMODULE) g_hInst);

        // If you use a resource DLL, load it here.
        // g_hInstRes = LoadLibrary(g_kszResDll);
        break;
        
    case DLL_PROCESS_DETACH:
        // Perform any clean-up here
        break;
        
    default:
        break;
    }
    
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
// OneStopFactory()
//
//  Description:
//      This DLL entry point is used by the Inbox to create an instance of 
//      the transport object and to return the IMailSyncHandler interface 
//      to it.
//
//  Parameters:
//      pszType         IN      String identifying the name of the transport
//                              to create(e.g. L"IMAP4", L"POP3", ...)
//                              This allows multiple transports to reside 
//                              in a single DLL for efficiency.
//      ppSyncHandler   OUT     Pointer to the IMailSyncHandler interface
//                              for the requested transport.
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

extern "C" HRESULT WINAPI OneStopFactory(
    LPCWSTR pszType, 
    IMailSyncHandler ** ppSyncHandler
    )
{
    return Transport_OneStopFactory(ppSyncHandler);        
}    


/////////////////////////////////////////////////////////////////////////////
//
// Transport_OneStopFactory()
//
//  Description:
//      Creates an instance of the transport class and returns a pointer
//      to its IMailSyncHandler interface.
//
//  Parameters:
//      ppSyncHandler   OUT     Pointer to the IMailSyncHandler interface
//                              for the requested transport.
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT Transport_OneStopFactory(
    IMailSyncHandler ** ppSyncHandler
    )
{
    if(NULL == ppSyncHandler)
    {
        return E_INVALIDARG;
    }
    

    *ppSyncHandler = new CTransportSyncHandler;
    if(NULL == *ppSyncHandler)
    {
        return E_OUTOFMEMORY;
    }
    
    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTransportSyncHandler::CTransportSyncHandler
//
//  Description:
//      Constructor
//
//  Parameters:
//      
//  Returns: 
//
/////////////////////////////////////////////////////////////////////////////

CTransportSyncHandler::CTransportSyncHandler() :
    m_cRef(1),
    m_pCallback(NULL),
    m_pMsgStore(NULL),
    m_fShutDown(FALSE),
    m_hEventShutdown(NULL),
    m_pszProfile(NULL)
{  
    ZeroMemory(&m_SyncProgressItemPending, sizeof(m_SyncProgressItemPending));
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::~CTransportSyncHandler()
//
//  Description:
//      Destructor
//
//  Parameters:
//
//  Returns:    
//
/////////////////////////////////////////////////////////////////////////////

CTransportSyncHandler::~CTransportSyncHandler()
{
    if(NULL != m_hEventShutdown)
    {
        CloseHandle(m_hEventShutdown);
    }

    MAPIFreeBuffer(m_pszProfile);

    if(NULL != m_pMsgStore)
    {
        m_pMsgStore->Release();
    }

    if(NULL != m_pCallback)
    {
        m_pCallback->Release();
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::Initialize()
//
//  Description:
//      Called by Inbox to initializes settings for the sync handler.
//
//  Parameters:
//      pCallback       IN  Pointer to callback interface used to retrieve
//                          configuration information from and pass status 
//                          information back to Inbox during mail synchronization.
//      pszProfileName  IN  Name of active profile in Inbox.  Used in calls to
//                          some methods of IMailSyncCallBack.
//      pMsgStore       IN  Pointer to message store for this service
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::Initialize(
    IMailSyncCallBack* pCallback, 
    LPCWSTR pszProfileName, 
    IMsgStore*   pMsgStore
    )
{
    HRESULT         hr          =   S_OK;
    int             iProfileLen;
    LPMAPIFOLDER    pfldrInbox  = NULL;



    // Save a copy of the IMailSyncCallBack function pointer.
    // We'll use this to retrieve user credentials for the 
    // account and to pass status info back to Inbox later.
    m_pCallback = pCallback;
    m_pCallback->AddRef();


    // Perform any transport initialization here
    // e.g.  creation of thread syncronization objects,
    // data structures used during mail syncronization, etc.
    // [ Omitted ]


    // Save a copy of the profile name for use later.
    iProfileLen =(lstrlen(pszProfileName) + 1 ) * sizeof(TCHAR);
    hr = MAPIAllocateBuffer(iProfileLen,(LPVOID *) &m_pszProfile);
    if(FAILED(hr))
    {
        goto Exit;
    }

    memcpy(m_pszProfile, pszProfileName, iProfileLen);


    // Save a copy of the message store pointer for this service
    if(NULL == pMsgStore)
    {
        hr = E_INVALIDARG;
        goto Exit;
    }

    m_pMsgStore = pMsgStore; //set to the mail store.     
    pMsgStore->AddRef();     //add one to the ref counter.    
    

    // Load settings for the specified profile name.  These may 
    // be stored in the registry, or as named properties on the 
    // message store, or wherever is convenient.
    // [ Omitted ]

    
    // Most transports will want to register for an advise 
    // in order to receive CEMAPI notifications to track 
    // message creates/deletes/modifications/moves.
    // [ Omitted ]


    // Some transports may need to know the Entry IDs for
    // system folders(Inbox, Outbox, Drafts, Sent Items, 
    // Deleted Items(Wastebasket)).  This is a good place
    // to query the IMsgStore* to get those.
    // [ Omitted ]
    


Exit:
    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::Synchronize()
//
//  Description:
//      This DLL entry point is called by Inbox to synchronize the 
//      current service
//
//  Parameters:
//      pRqst   IN  Sync options requested by Inbox
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::Synchronize(
    MAILSYNCREQUEST * pRqst
    )
{
    HRESULT hr = MAPI_E_INVALID_PARAMETER;

    if(NULL == pRqst)
    {
        // Inbox is requesting a full sync.
        // Synchronize all folders and messages.
        // [ Omitted ]
        // [ Assumed to return hr ]
    }
    else
    {
        switch(pRqst->ffFlags)
        {
        case SYNC_NORMAL:
            // Inbox is requesting a full sync.
            // Synchronize all folders and messages.
            // [ Omitted ]
            // [ Assumed to return hr ]
            break;

        case SYNC_FOLDER:
            // Inbox is requesting to synchronize a specific folder.
            // [ Omitted ]
            // [ Assumed to return hr ]
            break;  

        case SYNC_RESETHIERARCHY:
            // Inbox is requesting to synchronize the folder hierarchy.
            // [ Omitted ]
            // [ Assumed to return hr ]
            break;

        case SYNC_CREATE_FOLDER:
            // The user created a folder, and Inbox is asking the 
            // transport to create the local and server folders for it.
            // [ Omitted ]
            // [ Assumed to return hr ]
            break;

        case SYNC_RENAME_FOLDER:
            // The user renamed a folder, and Inbox is asking the 
            // transport to rename the local and server folders for it.
            // [ Omitted ]
            // [ Assumed to return hr ]
            break;

        case SYNC_DELETE_FOLDER:
            // The user deleted a folder, and Inbox is asking the 
            // transport to delete the local and server folders for it.
            // [ Omitted ]
            // [ Assumed to return hr ]
            break;

        default:
            break;
        }
    }

    if(hr == E_OUTOFMEMORY)
    {
        LogErrorEvent(E_OUTOFMEMORY, TRUE);
    }

    if(FAILED(hr) &&(pRqst == NULL || pRqst->ffFlags == SYNC_NORMAL))
    {
        //Get the body fetch thread to close now
        m_fShutDown = TRUE;
        SendProgressMessage(SYNCPROGRESSITEM_DISCONNECTED);
    }

    ASSERT(m_pszProfile);


    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::ShutDown()
//
//  Description:
//      This DLL entry point is used by the Inbox to shut down the transport
//      object.  Perform any clean-up or thread signalling here.  After this
//      function returns, Inbox will likely Release() the IMailSyncHandler*.
//
//  Parameters:
//      dwReserved      IN      Reserved.
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::ShutDown(
    DWORD dwReserved
    )
{
    HRESULT hr = S_OK;

    m_fShutDown = TRUE;
    SetEvent(m_hEventShutdown);

    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::Install()
//
//  Description:
//      This DLL entry point is used by the Inbox to create a new service
//      using this transport.  
//
//  Parameters:
//      pszProfileName      IN  Name of the new service 
//      pszIncomingServer   IN  Name of the incoming server
//      pszOutgoingServer   IN  Name of the outgoing server
//      pidNetwork          IN  GUID that identifies the connection manager
//                              network to use to connect to these servers
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::Install 
(
    LPCWSTR     pszProfileName,
    LPCWSTR     pszIncomingServer,
    LPCWSTR     pszOutgoingServer,
    GUID    *   pidNetwork
)
{
    HRESULT hr = S_OK;
 
    // Most transports create a profile key in the registry and
    // store these settings under that key.  
    // [ Omitted ]

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::UnInstall()
//
//  Description:
//      This DLL entry point is used by the Inbox to remove a service that
//      uses this transport.
//
//
//  *** NOTE *** 
//      This is currently not used by Inbox.
//
//
//  Parameters:
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::UnInstall()
{
    HRESULT hr = S_OK;

    return hr;
}

                          
/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::Connect()
//
//  Description:
//      This DLL entry point is used by the Inbox to connect to the
//      network identified by the pidNetwork parameter passed to
//      the Install() method when the service was created.
//
//  Parameters:
//      dwReserved          IN  Reserved
//      pCredentials        IN  Account credentials specified by the user
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::Connect(
    DWORD dwReserved,
    SYNCCREDENTIALS* pCredentials
    )
{
    HRESULT             hr              =   S_OK;
    SYNCCREDENTIALS *   pCurrentCreds   =   pCredentials;
    ULONG               cTries          =   0;

    // The transport is no longer shut down
    ASSERT(m_hEventShutdown != NULL);
    m_fShutDown = FALSE;
    ResetEvent(m_hEventShutdown);

    while(TRUE)
    {
        // Do we need to prompt for account info?
        if(cTries || *pCurrentCreds->pszPassword == L'\0')
        {
            SYNCCREDENTIALS * pNewCreds = NULL;



            // Make a request to the Inbox for logon credentials.
            hr = m_pCallback->RequestCredentials(m_pszProfile, pCurrentCreds, &pNewCreds);
            if(FAILED(hr))
            {
                // Log an error...
                if (!m_fShutDown)
                {
                    LogErrorEvent(CEMAPI_E_NO_ACCOUNT_INFO, 0);
                }

                break;
            }

            // pNewCreds now contains the new info from the user.
            ASSERT(pNewCreds != NULL);

            // Check to see if 'pCurrentCreds' is *not* the ones passed in.
            // If they are not, then we need to free them.  This will happen
            // if the user has been asked more than once for the password.
            if(pCurrentCreds != pCredentials)
            {
                m_pCallback->FreeMem(pCurrentCreds);
            }

            pCurrentCreds = pNewCreds;
        }

        // Now try to connect to the mail server
        // [ Omitted ]
        // [ Assumed to return hr ]
        if(FAILED(hr))
        {
            if (!m_fShutDown)
            {
                LogErrorEvent(hr, 0);
            }
        
            break;
        }

        if(m_fShutDown)
        {
            hr = E_FAIL;
            break;
        }

        // Log in to the mail server
        SetStatusText(0/*IDS_TRANSPORT_CONNECTING*/);     // TODO:  Use an appropriate string resource
        // [ Omitted ]
        // [ Assumed to return hr ]

        // If the logon succeeded, we're done
        if(SUCCEEDED(hr))
        {
            break;
        }

        // If we failed due to anything but authentication errors, 
        // log the error and bail out
        if(hr != E_ACCESSDENIED)
        {
            // Log an error back to the application if user didn't himself ask for shutdown
            if (!m_fShutDown)
            {
                LogErrorEvent(hr, 0);
            }

            break;
        }

        // No success!  Need to hang up and ask the user for new
        // credentials.

        ++cTries;

        // Disconnect from the mail server
        // [ Omitted ]
        // [ Assumed to return hr ]

    }   // while(TRUE)


    if(FAILED(hr))
    {
        // Disconnect from the mail server
        // [ Omitted ]
        // [ Assumed to return hr ]
    }


    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::Disconnect()
//
//  Description:
//      This DLL entry point is used by the Inbox to disconnect the
//      transport from the network.
//
//  Parameters:
//      dwReserved          IN  Reserved
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::Disconnect(
    DWORD dwReserved
    )
{
    HRESULT hr = S_OK;            

    // Set the Inbox status bar to display "Disconnecting..."
    SetStatusText(0/*IDS_TRANSPORT_DISCONNECTING*/);       // TODO:  Use an appropriate string resource

    // Shut down the connection watching thread
    SetEvent(m_hEventShutdown);

    // Clear the Wastebasket if the option is set
    if(m_nDeleteAction != DELACTION_MANUALLY)
    {
        // Call a utility function to empty the Deleted Items folder
        // [ Omitted ]
        // [ Assumed to return hr ]
    }

    // Disconnect from the mail server
    // [ Omitted ]
    // [ Assumed to return hr ]

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::DoProperties()
//
//  Description:
//      This DLL entry point is used by the Inbox to display a properties 
//      dialog for the service.
//
//  *** NOTE ***  Pocket PC 2002 does not use this.
//
//  Parameters:
//      hwndParent  IN  Parent window
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::DoProperties(HWND hwndParent)
{
    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::GetCapability()
//
//  Description:
//      This DLL entry point is used by the Inbox to query the transport
//      for various settings and limits.  
//
//      cemapi.h defines these capabilities:
//
//      kszCapAmountToFetch         -   Number of bytes to fetch for each message
//      kszCapAttachAmount          -   Attachment fetch size limit(transport should 
//                                      skip attachments greater than this size)
//      kszCapAgeFilter             -   Number of days of mail to sync(older mail 
//                                      should age off device or not be retrieved)
//      kszCapFolders               -   Non-zero if the transport can sync folders.  
//      kszSyncHierarchy            -   Non-zero if the transport can sync folders.  
//      kszCapDeleteAction          -   DELACTION_MANUALLY or DELACTION_IMMEDIATELY.
//                                      If set to manual, deletes go to the trash folder
//                                      and the user is responsible for deleting them.
//                                      If set to immediately, deletes happen immediately.
//
//  Parameters:
//      pszName         IN      String identifying the capability being queried
//      pval            OUT     Value of the capability being queried
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::GetCapability(
    LPCWSTR pszName, 
    LPSPropValue pval
    )
{
    HRESULT     hr      =   S_OK;

    if ((!pszName) ||(!pval))
    {
        return E_INVALIDARG;
    }


    // Test pszName against the specific capability strings that the
    // transport supports, and return the requested value when a match
    // is found.  If no match is found, return MAPI_E_NOT_FOUND.
    // [ Omitted ]


    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::SetCapability()
//
//  Description:
//      This DLL entry point is used by the Inbox to set various settings 
//      and limits in the transport.  This is called when the user makes an 
//      alteration(e.g. via the wizard) to a service that uses this transport.
//
//      See GetCapability() for a list of capabilities.
//      
//  Parameters:
//      pszName         IN      String identifying the capability being queried
//      pval            IN      Value of the capability being queried
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::SetCapability(
    LPCWSTR pszName, 
    LPSPropValue pval
    )
{
    ULONG   *   pnVal   =   NULL;
    HRESULT     hr      =   S_OK;



    if ((pszName == NULL) ||(pval == NULL))
    {
        hr = E_INVALIDARG;
    }

    // Test pszName against the specific capability strings that the
    // transport supports, and set the requested value when a match
    // is found.  If no match is found, return MAPI_E_NOT_FOUND.
    // [ Omitted ]
    
    return hr;
}

                          



/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::DecodeEvent()
//
//  Description:
//      This DLL entry point is used by the Inbox to map a transport event
//      to an descriptive string.
//
//  Parameters:
//      pevt        IN  Event to map
//      ppszEvent   OUT String describing the event
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::DecodeEvent(
    TRANSPORTEVENT * pevt, 
    LPWSTR * ppszEvent
    )
{
    UINT    nStringId = 0;    
    LPCTSTR pszFormat;
    HRESULT hr;

    ASSERT(pevt != NULL);

    // We use cbData to determine whether the error is Send or Receive related.
    BOOL fReceiving =(pevt->cbData != 0);

    switch (pevt->hr)
    {
        // Map HRESULTs to error string resource IDs here:
        
        
        // General errors...
        case E_OUTOFMEMORY:
            //nStringId = IDS_ERROR_OUTOFMEMORY;
            break;

        // Socket errors.
        case HrFromWSAError(WSAETIMEDOUT):
            //nStringId = IDS_ERROR_TIMEDOUT;
            break;

        case HrFromWSAError(WSAHOST_NOT_FOUND):
        case HrFromWSAError(WSAENOTCONN):
        case HrFromWSAError(WSATRY_AGAIN):      //Non-Authoritative Host not found
        case HrFromWSAError(WSANOTINITIALISED): // Can be returned by GetHostByName / Successful WSASTARTUP not yet performed
            //nStringId =(fReceiving ? IDS_ERROR_SERVERNOTFOUND_INCOMING :
            //                          IDS_ERROR_SERVERNOTFOUND_OUTGOING);
            break;

        case HrFromWSAError(WSAECONNREFUSED):  // Happens if user supplied wrong port number.
            //nStringId =(fReceiving ? IDS_ERROR_SERVERNOTREADY_INCOMING :
            //                          IDS_ERROR_SERVERNOTREADY_OUTGOING);
            break;        

        case CEMAPI_E_PROTOCOL_ERROR:
            //nStringId = IDS_ERROR_LOGIN_INCOMING;
            break;

        case CEMAPI_E_PLAINTEXT_NOTSUPPORTED:
            //nStringId = IDS_IMAP_NO_PLAINTEXT;
            break;

        case CEMAPI_E_NO_ACCOUNT_INFO:
            //nStringId = IDS_ERROR_LOGIN_INCOMING;
            break;

        case E_FAIL: 
            //nStringId = IDS_ERROR_NO_NETWORK;
            break;

        // Logon error...
        case ERROR_LOGON_FAILURE:
            //nStringId =(fReceiving ? IDS_ERROR_LOGIN_INCOMING :
            //                          IDS_ERROR_LOGIN_OUTGOING);
            break;

        // POP uses this report that the server didn't like initial connection.
        case ERROR_NOT_READY:
            //nStringId = IDS_ERROR_SERVERNOTREADY_INCOMING;
            break;

        // Handle errors specific to this transport
        /*
        case TRANSPORTDEMO_???:
            nStringId = IDS_ERROR_SERVEROVERLOADED;
            break;
        */

        default: // General failure message.
            //nStringId =(fReceiving ? IDS_ERROR_UNKNOWN_INCOMING :
            //                          IDS_ERROR_UNKNOWN_OUTGOING);            
            break;
    }
    
    pszFormat =(LPCTSTR)LoadString(g_hInst, nStringId, 0, 0);
    if(NULL == pszFormat)
    {
        hr = E_FAIL;
        goto Exit;
    }
   

    hr = m_pCallback->AllocateMem((lstrlen(pszFormat) + 1) * sizeof(WCHAR),(LPBYTE*) ppszEvent);
    if(FAILED(hr))
    {
        goto Exit;
    }

    // Everything worked ok.
    wcscpy(*ppszEvent, pszFormat);

Exit:
    return hr;
}

                          



/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::GetFolderHierarchy()
//
//  Description:
//      This DLL entry point is used by the Inbox to retrieve the complete
//      folder hierarchy for the current service(m_pszProfile).
//
//  Parameters:
//      ppRootNode      OUT     Folder hierarchy
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::GetFolderHierarchy(
    FOLDERNODE ** ppRootNode
    )
{
    HRESULT hr = S_OK;
    
    ASSERT(ppRootNode);
   
    // Allocate the FOLDERNODE 
    hr = m_pCallback->AllocateMem(sizeof(FOLDERNODE),(LPBYTE *) ppRootNode);
    if(FAILED(hr))
    {
        hr = E_FAIL;
        goto Exit;
    }

    ZeroMemory(*ppRootNode, sizeof(FOLDERNODE));


    // Traverse the folder hierarchy and populate the ppRootNode tree.
    // This data can come from CEMAPI(GetHierarchyTable()), or some other 
    // data store if the CEMAPI folder hierarchy doesn't accurately represent
    // the server's hierarchy(eg, you only create synced folders in CEMAPI).
    // [ Omitted ]


Exit:    
    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::SetFolderOptions()
//
//  Description:
//      This DLL entry point is used by Inbox to perform various configuration
//      options on folders, if the transport supports folder synchronization.
//
//  Parameters:
//      pfldr       IN  Folder being modified
//      pnode       IN  Folder structure for folder being modified
//      opts        IN  Requested operation
//      pval        OUT Value requested(depends on opts)
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::SetFolderOptions(
    LPMAPIFOLDER pfldr,
    FOLDERNODE* pnode,
    FOLDEROPTIONS opts,
    LPSPropValue pval
    )
{
    HRESULT hr = MAPI_E_INVALID_PARAMETER;    

    if (!pfldr)
    {
        return hr;
    }

    switch (opts)
    {
        case IMailSyncHandler::koptDownload:
            if(pval != NULL && pval->ulPropTag == PT_BOOLEAN)
            {
                hr = OnFolderOptions_Download(pfldr, pval);
            }
            break;
        
        case IMailSyncHandler::koptQueryDownload:
            if(pval != NULL)
            {
                hr = OnFolderOptions_QueryDownload(pfldr, pval);
            }
            break;
 
        case IMailSyncHandler::koptCreate:
            hr = OnFolderOptions_Create(&pfldr);
            break;
        
        case IMailSyncHandler::koptQueryCreate:
            if(pval != NULL)
            {
                hr = OnFolderOptions_QueryCreate(pfldr, pval);
            }
            break;
        
        case IMailSyncHandler::koptSetAge:
        case IMailSyncHandler::koptSetBodyFetchSize:
        case IMailSyncHandler::koptSetAttachFetchSize:
            if(pval != NULL)
            {                                       
                hr = OnFolderOptions_SetFetchOption(opts, pfldr, pval);
            }
            break;
        
        case IMailSyncHandler::koptGetAge:
        case IMailSyncHandler::koptGetBodyFetchSize:
        case IMailSyncHandler::koptGetAttachFetchSize:
            if(pval != NULL)
            {
                hr = OnFolderOptions_GetFetchOption(opts, pfldr, pval);
            }
            break;
            
        default:
            break;
    }

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::SetStatusText()
//
//  Description:
//      Uses a callback to set the status bar text in Inbox.  
//
//  Parameters:
//      nId     IN  Resource ID for string to display
//      
//  Returns:    void
//
/////////////////////////////////////////////////////////////////////////////

void CTransportSyncHandler::SetStatusText(
    UINT nId
    )
{
    SYNCPROGRESSITEM item = { 0 };

    item.cbSize         =   sizeof(item);
    item.mask           =   SYNCPROGRESSITEM_STATUSTEXT;
    item.pwszStatusText =(LPCTSTR) LoadString(g_hInst, nId, 0, 0);

    ASSERT(item.pwszStatusText != NULL);

    if(m_pCallback != NULL)
    {
        m_pCallback->Progress(m_pszProfile, &item);
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::SendProgressMessage()
//
//  Description:
//      Uses a callback to set the sync progress in Inbox.  Currently
//      only appropriate for SYNCPROGRESSITEM_DISCONNECTED.  
//
//  Parameters:
//      dwMask      IN  SYNCPROGRESSITEM_xxx from cemapi.h
//      
//  Returns:    void
//
/////////////////////////////////////////////////////////////////////////////

void CTransportSyncHandler::SendProgressMessage(
    DWORD dwMask
    )
{
    SYNCPROGRESSITEM item = { 0 };

    item.cbSize =   sizeof(item);
    item.mask   =   dwMask;

    if(m_pCallback != NULL)
    {
        m_pCallback->Progress(m_pszProfile, &item);
    }
}



/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::HandlePendingProgressItem()
//
//  Description:
//      Uses a callback to inform the Inbox of any pending progress items
//      and then resets the global progress item.
//
//  Parameters:
//      
//  Returns:    void
//
/////////////////////////////////////////////////////////////////////////////

void CTransportSyncHandler::HandlePendingProgressItem()
{
    if(m_SyncProgressItemPending.mask != 0)
    {
        if(m_pCallback != NULL)
        {
            m_pCallback->Progress(m_pszProfile, &m_SyncProgressItemPending);
        }
    }

    ZeroMemory(&m_SyncProgressItemPending, sizeof(m_SyncProgressItemPending));
}



/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::LogErrorEvent()
//
//  Description:
//      Use a callback to log an error event with Inbox
//
//  Parameters:
//      hr          IN      HRESULT of error code
//      cbData      IN      Amount of data read from the server
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::LogErrorEvent(
    HRESULT hr, 
    ULONG cbData
    )
{
    TRANSPORTEVENT evt = { 0 };

    ASSERT(m_pszProfile);
    
    evt.pszSourceDLL        =   _T("TransportDemo");
    evt.pszSourceProfile    =   m_pszProfile;
    evt.hr                  =   hr;
    evt.cbData              =   cbData;
    evt.pbData              =   NULL;
    
    m_pCallback->LogEvent(&evt);

    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::QueryInterface()
//
//  Description:
//      COM plumbing
//
//  Parameters:
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT STDMETHODCALLTYPE CTransportSyncHandler::QueryInterface(
    REFIID rif, 
    LPVOID* ppobj
    )
{
    return E_NOINTERFACE;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::AddRef()
//
//  Description:
//      COM plumbing
//
//  Parameters:
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

ULONG STDMETHODCALLTYPE CTransportSyncHandler::AddRef()
{
    return ++m_cRef;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::Release()
//
//  Description:
//      COM plumbing
//
//  Parameters:
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

ULONG STDMETHODCALLTYPE CTransportSyncHandler::Release()
{
    --m_cRef;
    if(m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::OnFolderOptions_Download()
//
//  Description:
//      Called when the user sets the 'Marked for Download' flag on a folder
//
//  Parameters:
//      pfldr   IN  Folder marked for download
//      pval    IN  Boolean indicating whether to mark or unmark the folder
//                  for download
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::OnFolderOptions_Download(
    LPMAPIFOLDER pfldr,
    LPSPropValue pval
    )
{
    HRESULT hr = S_OK;
    
    // Mark or unmark the folder for sync.  The details of this
    // are transport-specific.
    // [ Omitted ]

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::OnFolderOptions_QueryDownload()
//
//  Description:
//      Called when Inbox tries to determine if the given folder
//      is marked for sync.
//
//  Parameters:
//      pfldr   IN  Folder marked for download
//      pval    OUT Boolean indicating whether the folder is marked for sync
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::OnFolderOptions_QueryDownload(
    LPMAPIFOLDER pfldr, 
    LPSPropValue pval
    )
{
    HRESULT hr = S_OK;
    
    // The details of this are transport-specific.
    // [ Omitted ]

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::OnFolderOptions_Create()
//
//  Description:
//      Called when the user creates a new folder to allow the transport
//      to set any properties it needs to on the folder, and add it to
//      its change tracking so that it can create the folder when the 
//      service connects next.
//
//  Parameters:
//      pfldr   IN  Newly created folder
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::OnFolderOptions_Create(
    LPMAPIFOLDER * ppfldrret
    )
{
    HRESULT hr = S_OK;
    
    // The details of this are transport-specific.
    // [ Omitted ]

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::OnFolderOptions_QueryCreate()
//
//  Description:
//      Called when Inbox wants to know if a folder has been marked
//      for creation on the server.
//
//  Parameters:
//      pfldr   IN  Folder to check
//      pval    OUT Boolean indicating whether the folder is marked for creation
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::OnFolderOptions_QueryCreate(
    LPMAPIFOLDER pfldr, 
    LPSPropValue pval
    )
{
    HRESULT hr = S_OK;
    
    // The details of this are transport-specific.
    // [ Omitted ]

    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::OnFolderOptions_SetFetchOption()
//
//  Description:
//      Called when the users sets the download options for a folder.
//
//  Parameters:
//      opts    IN  Folder options to set
//      pfldr   IN  Folder being modified
//      pval    IN  Property tag used to set the option
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::OnFolderOptions_SetFetchOption(
    FOLDEROPTIONS   opts,
    LPMAPIFOLDER    pfldr,
    LPSPropValue    pval
    )
{
    HRESULT hr = E_FAIL;

    pval->ulPropTag = 0;

    switch(opts)
    {
    case koptSetAge:
        pval->ulPropTag = 0; // Replace with named prop ID for max age
        break;

    case koptSetBodyFetchSize:
        pval->ulPropTag = 0; // Replace with named prop ID for max body size
        break;

    case koptSetAttachFetchSize:
        pval->ulPropTag = 0; // Replace with named prop ID for max attachment size
        break;

    default:
        ASSERT(FALSE);
        break;
    }

    if(pval->ulPropTag)
    {
        hr = pfldr->SetProps(1, pval, NULL);
    }


    return hr;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CTransportSyncHandler::OnFolderOptions_GetFetchOption()
//
//  Description:
//      Called when Inbox needs the download options for a folder
//
//  Parameters:
//      opts    IN  Folder options to set
//      pfldr   IN  Folder being modified
//      pval    OUT Property tag used to set the option
//      
//  Returns:    HRESULT
//
/////////////////////////////////////////////////////////////////////////////

HRESULT CTransportSyncHandler::OnFolderOptions_GetFetchOption(
    FOLDEROPTIONS opts,
    LPMAPIFOLDER pfldr,
    LPSPropValue pval
    )
{
    HRESULT hr          =   E_FAIL;
    ULONG   rgtags[]    =   { 1, 0 };

    switch(opts)
    {
    case koptGetAge:
        rgtags[1]       = 0; // Replace with named prop ID for max age
        pval->Value.ul  = 0; // Replace with default value for max age
        break;

    case koptGetBodyFetchSize:
        rgtags[1]       = 0; // Replace with named prop ID for max body size
        pval->Value.ul  = 0; // Replace with default value for max body size
        break;

    case koptSetAttachFetchSize:
        rgtags[1]       = 0; // Replace with named prop ID for max attachment size
        pval->Value.ul  = 0; // Replace with default value for max attachment size
        break;

    default:
        ASSERT(FALSE);
        break;
    }

    if(rgtags[1] != 0)
    {
        ULONG           cItems  =   0;
        LPSPropValue    rgvals  =   NULL;



        hr = pfldr->GetProps((LPSPropTagArray) rgtags, MAPI_UNICODE, &cItems, &rgvals);
        
        if(SUCCEEDED(hr))
        {
            ASSERT(cItems);

            // If we got a value return it to the caller; otherwise we initialized
            // to the default already.
            if(rgtags[1] == rgvals[0].ulPropTag)
            {
                pval->Value.ul = rgvals[0].Value.ul;
            }

            MAPIFreeBuffer(rgvals);
        }
    }


    return hr;
}
