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
/*
    Copyright (c) Microsoft Corporation. All rights reserved.
*/

#ifndef __cemapi_MAPI_H__
#define __cemapi_MAPI_H__

#include <mapidefs.h>
#include <mapicode.h>
#include <mapitags.h>
#include <mapispi.h>
#include <mapix.h>

#ifndef _PURE
#define _PURE =0
#endif // _PURE





const LPCTSTR kszAppInbox = TEXT ("tmail.exe");





const int g_knMaxSvcs   = 8;         // Max # of services
const int g_knMaxSvcLen = 32;       // Max length of a service name





//----------------------------------------------------------------------------
// MAIL SYNC HANDLER Interfaces
//----------------------------------------------------------------------------

#define SYNCPROGRESSITEM_STATUSTEXT                 0x0001
#define SYNCPROGRESSITEM_STATUSTYPE                 0x0002
#define SYNCPROGRESSITEM_PROGVALUE                  0x0004
#define SYNCPROGRESSITEM_MAXVALUE                   0x0008
#define SYNCPROGRESSITEM_DISCONNECTED               0x0010
#define SYNCPROGRESSITEM_TOTAL_NEW_MAIL             0x0020
#define SYNCPROGRESSITEM_NEW_MESSAGE                0x0040

typedef struct _SYNCPROGRESSITEM
{
    ULONG       cbSize;

    DWORD       mask;

    LPCWSTR     pwszStatusText;
    DWORD       dwStatusType;
    ULONG       ulProgValue;
    ULONG       ulMaxValue;

    ULONG       ulTotalNewMail;

    ULONG       cbIdNewMsg;
    LPENTRYID   pidNewMsg;

} SYNCPROGRESSITEM;

#define SYNC_NORMAL         0
#define SYNC_HIERARCHY      1
#define SYNC_CREATE_FOLDER  2
#define SYNC_RENAME_FOLDER  3
#define SYNC_DELETE_FOLDER  4
#define SYNC_RESETHIERARCHY  5
#define SYNC_FOLDER          6

typedef struct _MAILSYNCREQUEST
{
    DWORD       cbSize;
    DWORD       cbBufSize;

    DWORD       cbCookie;
    LPBYTE      pbCookie;

    ULONG       ffFlags;

    ULONG       objType;
    LPENTRYID   pid;
    DWORD       cbId;

    LPSPropValue  pval;

} MAILSYNCREQUEST;

typedef struct _SYNCCREDENTIALS
{
    DWORD       cbSize;
    DWORD       cbBufSize;
    LPTSTR      pszUsername;
    LPTSTR      pszDomain;
    LPTSTR      pszPassword;
} SYNCCREDENTIALS;

typedef struct _TRANSPORTEVENT
{
    LPCWSTR pszSourceDLL;
    LPCWSTR pszSourceProfile;
    HRESULT hr;
    DWORD   dwSeverity;
    DWORD   cbData;
    LPBYTE  pbData;
} TRANSPORTEVENT;

typedef struct _MESSAGEFIELDS
{
    LPCWSTR pszwTo;
    LPCWSTR pszwCc;
    LPCWSTR pszwBcc;
    LPCWSTR pszwSubject;
    LPCWSTR pszwBody;
    DWORD flags;
} MESSAGEFIELDS;


typedef enum
{
    MSG_FORMAT_UNKNOWN = 0,
    MSG_FORMAT_TEXT,
    MSG_FORMAT_HTML,
    MSG_FORMAT_RTF,
} MESSAGEFORMAT;


#define MESSAGEFIELDS_FLAGS_DELETEONCLOSE   0x00000001
#define MESSAGEFIELDS_FLAGS_SMSSERVICE      0x00000002

const DWORD kdwOptionValueNone = 0;
const DWORD kdwOptionValueAll  = 0xFFFFFFFF;


const WCHAR kszCapHTMLMail[]                    = L"HTMLMail";
const WCHAR kszCapAutoPostMeetingResponse[]     = L"AutoPostMeetingResponse";
const WCHAR kszCapAmountToFetch[]               = L"FetchSize";
const WCHAR kszCapAttachAmount[]                = L"AttachFetchSize";
const WCHAR kszCapAgeFilter[]                   = L"AgeFilter";
const WCHAR kszCapSaveSent[]                    = L"SaveSent";
const WCHAR kszCapSMSUnicode[]                  = L"SMSUnicode";
const WCHAR kszCapSMSDeliveryNotify[]           = L"SMSDeliveryNotify";
const WCHAR kszCapSMTPAuthenticate[]            = L"SMTPAuthenticate";
const WCHAR kszCapIncludeOriginal[]             = L"IncludeOriginal";
const WCHAR kszCapIndentBody[]                  = L"IndentBody";
const WCHAR kszCapAddLeading[]                  = L"AddLeading";
const WCHAR kszCapLeadChar[]                    = L"LeadChar";
const WCHAR kszCapSyncMsgClasses[]              = L"SyncMsgClasses";
const WCHAR kszCapSyncMsgClassDef[]             = L"SyncMsgClassDef";
const WCHAR kszCapPropDialog[]                  = L"PropDialog";                    // default: FALSE
const WCHAR kszCapSyncHierarchy[]               = L"SyncHierarchy";
const WCHAR kszCapDeleteAction[]                = L"DeleteAction";
const WCHAR kszCapMoveToTrash[]                 = L"TrashMoves";

const WCHAR kszCapReturnAddress[]               = L"ReturnAddress";
const WCHAR kszCapCurrentService[]              = L"CurrentService";
const WCHAR kszCapCreateSpecialFldrs[]          = L"CreateSpecialFolders";

// Boolean service capabilities which have default values.
// Override the default in GetCapability().
const WCHAR kszCapFolders[]                     = L"Folders";                       // default: TRUE
const WCHAR kszCapFolderNotifications[]         = L"FolderNotifications";           // default: FALSE

// New for 2003 devices
const WCHAR kszCapClearAll[]                    = L"ClearAll";                      // default: TRUE
const WCHAR kszCapEmptyDeleteItem[]             = L"EmptyDeleteItem";               // default: TRUE
const WCHAR kszCapEditProperties[]              = L"EditProperties";                // default: TRUE
const WCHAR kszCapFolderOptions[]               = L"EmptyFolderOptions";            // default: TRUE
const WCHAR kszCapMgmtFolder[]                  = L"MgmtFolder";                    // default: TRUE
const WCHAR kszCapSync[]                        = L"Sync";                          // default: TRUE
const WCHAR kszCapSyncOnDockEvent[]             = L"SyncOnDockEvent";               // default: TRUE
const WCHAR kszCapConnect[]                     = L"Connect";                       // default: TRUE
const WCHAR kszCapRequireRadio[]                = L"RequireRadio";                  // default: FALSE
const WCHAR kszCapMarkAttachments[]             = L"MarkAttachments";               // default: FALSE
const WCHAR kszCapReplyAll[]                    = L"ReplyAll";                      // default: TRUE (can't be TRUE if no compose capability)
const WCHAR kszCapAlwaysIncludeOriginal[]       = L"AlwaysIncludeOriginal";         // default: FALSE
const WCHAR kszCapCompose[]                     = L"Compose";                       // default: TRUE
const WCHAR kszCapOfflineStatus[]               = L"OfflineStatus";                 // default: TRUE
const WCHAR kszCapCallSender[]                  = L"CallSender";                    // default: FALSE
const WCHAR kszCapLanguage[]                    = L"Language";                      // default: TRUE
const WCHAR kszCapAttachments[]                 = L"Attachments";                   // default: TRUE
const WCHAR kszCapFolderManagementAllowCreate[] = L"FolderManagementAllowCreate";   // default: TRUE
const WCHAR kszCapFolderManagementAllowRename[] = L"FolderManagementAllowRename";   // default: TRUE
const WCHAR kszCapFolderManagementAllowDelete[] = L"FolderManagementAllowDelete";   // default: TRUE

const WCHAR kszCapSMIME[]                       = L"SMIME";                         // default: FALSE
const WCHAR kszCapCannotSendMeetingRequests[]   = L"CannotSendMeetingRequests";     // default: FALSE
const WCHAR kszCapClearAllOnServer[]            = L"ClearAllDeletesFromServer";     // default: TRUE
const WCHAR kszCapServiceFromMessage[]          = L"ServiceFromMessage";            // Only used in GetGlobalSetting


const WCHAR kszCapFollowUpFlags[]               = L"FollowUpFlags";                 // default: FALSE

// Fetch / AUTD
const WCHAR kszCapImmediateDownload[]           = L"ImmediateDownload";             // default: FALSE
const WCHAR kszCapSwitchFormat[]                = L"SwitchFormat";                  // default: FALSE
const WCHAR kszCapConnectHomeNetwork[]          = L"ConnectHomeNetwork";            // default: TRUE


// kszCapDeleteAction above allows the user to specify
// what delete options should be taken during laster syncs...
#define DELACTION_IMMEDIATELY            0x00000000
#define DELACTION_MANUALLY               0x00000001


// {96D2552D-B83B-4b48-8E89-DCC26512DBA4}
static const GUID IID_IMailRuleClient =
{ 0x96d2552d, 0xb83b, 0x4b48, { 0x8e, 0x89, 0xdc, 0xc2, 0x65, 0x12, 0xdb, 0xa4 } };

typedef enum _MRCACCESS
{
    MRC_ACCESS_NONE = 0,         // Client isn't interested in this message
    MRC_ACCESS_READ_ONLY = 1,    // Client is only interested in read access for messages
    MRC_ACCESS_WRITE = 2         // Client wants write access for messages
} MRCACCESS;

typedef enum _MRCHANDLED {
    MRC_NOT_HANDLED = 0,         // Client didn't handle the message
    MRC_HANDLED_CONTINUE = 1,    // Client handled message, let others handle too
    MRC_HANDLED_DONTCONTINUE = 2 // Client handled message, don't let others handle
} MRCHANDLED;

interface IMailRuleClient : public IUnknown
{
public:
    MAPIMETHOD(Initialize)(
            IMsgStore *pMsgStore,
            MRCACCESS *pmaDesired
            ) _PURE;

    MAPIMETHOD(ProcessMessage)(
            IMsgStore *pMsgStore,
            ULONG cbMsg,
            LPENTRYID lpMsg,
            ULONG cbDestFolder,
            LPENTRYID lpDestFolder,
            ULONG *pulEventType,
            MRCHANDLED *pHandled
            ) _PURE;
};


// forward declaration
class IMailSyncHandler;



// {447DAA3A-E420-4e87-B440-0045B9FE73BC}
static const GUID IID_IMailSyncCallBack =
{ 0x447daa3a, 0xe420, 0x4e87, { 0xb4, 0x40, 0x0, 0x45, 0xb9, 0xfe, 0x73, 0xbc } };

class IMailSyncCallBack : public IUnknown
{
public:
    MAPIMETHOD(RequestSync)(
            LPCWSTR pszProfile,
            DWORD cbCookie,
            LPBYTE pbCookie
            ) _PURE;

    MAPIMETHOD(Progress)(
            LPCWSTR pszProfile,
            SYNCPROGRESSITEM* pinfo
            ) _PURE;

    MAPIMETHOD(GetGlobalSetting)(
            LPCWSTR pszSetting,
            LPSPropValue pval
            ) _PURE;

    MAPIMETHOD_(UINT, DisplayMessageBox)(
            LPCWSTR pszProfile,
            LPCWSTR pszTitle,
            LPCWSTR pszMessage,
            UINT uType
            ) _PURE;

    MAPIMETHOD(RequestCredentials)(
            LPCWSTR pszProfile,
            SYNCCREDENTIALS*  ppcredsSource,
            SYNCCREDENTIALS** ppcreds
            ) _PURE;

    MAPIMETHOD(LogEvent)(
            TRANSPORTEVENT* pevt
            ) _PURE;

    MAPIMETHOD(AllocateMem)(
            DWORD cbSize,
            LPBYTE* ppb
            ) _PURE;

    MAPIMETHOD(FreeMem)(
            LPVOID pvmem
            ) _PURE;
};

#define FOLDER_HIDE             0x00010000
#define FOLDER_SPECIAL          0x00020000
#define FOLDER_INBOX            0x00040000
#define FOLDER_DELETED_ITEMS    0x00080000
#define FOLDER_SENT_ITEMS       0x00100000
#define FOLDER_OUTBOX           0x00200000
#define FOLDER_DRAFTS           0x00400000
#define FOLDER_IPM              0x00800000
#define FOLDER_SEARCH_ROOT      0x01000000

typedef struct _FOLDERNODE {
    _FOLDERNODE*    pSibbling;
    _FOLDERNODE*    pChild;
    _FOLDERNODE*    pParent;
    DWORD           ffFlags;
    LPWSTR          szName;
} FOLDERNODE;


// flag for Shutdown function
#define SHUTDOWNFLAG_LOSTCONNECTION     0x0001

class IMailSyncHandler : public IUnknown
{
public:
    MAPIMETHOD(Initialize)(
            IMailSyncCallBack* pCallBack,
            LPCWSTR pszProfileName,
            IMsgStore* pMsgStore
            ) _PURE;

    MAPIMETHOD(ShutDown)(
            DWORD dwReserved
            ) _PURE;

    MAPIMETHOD(Synchronize)(
            MAILSYNCREQUEST* pRqst
            ) _PURE;

    MAPIMETHOD(DoProperties)(
            HWND hwndParent
            ) _PURE;

    MAPIMETHOD(GetCapability)(
            LPCWSTR pszName,
            LPSPropValue pval
            ) _PURE;

    MAPIMETHOD(SetCapability)(
            LPCWSTR pszName,
            LPSPropValue pval
            ) _PURE;

    MAPIMETHOD(Install)(
            LPCWSTR pszProfileName,
            LPCWSTR pszIncomingServer,
            LPCWSTR pszOutgoingServer,
            GUID*   pidNetwork
            ) _PURE;

    MAPIMETHOD(UnInstall)(
            ) _PURE;

    MAPIMETHOD(DecodeEvent)(
            TRANSPORTEVENT* pevt,
            LPWSTR* ppszEvent
            ) _PURE;

    MAPIMETHOD(GetFolderHierarchy)(
            FOLDERNODE** ppRootNode
            ) _PURE;

    enum FOLDEROPTIONS {
        koptNA = 0,
        koptDownload,
        koptQueryDownload,
        koptNotifications,
        koptQueryNotifications,
        koptGetRemotePath,
        koptCreate,
        koptQueryCreate,
        koptSetAge,
        koptSetBodyFetchSize,
        koptSetAttachFetchSize,
        koptGetAge,
        koptGetBodyFetchSize,
        koptGetAttachFetchSize,
    };

    MAPIMETHOD(SetFolderOptions)(
            IMAPIFolder*    pfldr,
            FOLDERNODE*     pnode,
            FOLDEROPTIONS   opts,
            LPSPropValue    pval
            ) _PURE;

    MAPIMETHOD(Connect)(
            DWORD dwReserved,
            SYNCCREDENTIALS* pCredentials
            ) _PURE;

    MAPIMETHOD(Disconnect)(
            DWORD dwReserved
            ) _PURE;
};

#define MAX_ONESTOP_TYPE_NAME   32
#define MAX_MESSAGE_CLASS_NAME   64
#define MAX_MESSAGE_CLASS_DISPLAY_NAME      64
#define MAX_MESSAGE_CLASSES_SUPPORTED_STRING    1024

typedef HRESULT (WINAPI *ONESTOPFACTORYFUNC)(LPCWSTR pszType, IMailSyncHandler** ppObj);




typedef enum tagSMIME_SENDFLAG
{
    SMIME_SENDFLAG_SIGN    = 0x00000001,
    SMIME_SENDFLAG_ENCRYPT = 0x00000002
} SMIME_SENDFLAG;


//----------------------------------------------------------------------------
// ICEMAPISession Interface
//----------------------------------------------------------------------------

#define MAPI_ICEMAPISESSION_METHODS(IPURE)                              \
    MAPIMETHOD(CreateMsgStore)                                          \
        (THIS_  LPCWSTR                     pszDisplayName,             \
                IMsgStore**                 ppMsgStore) IPURE;          \
    MAPIMETHOD(DeleteMsgStore)                                          \
        (THIS_  ULONG                       cbEntryID,                  \
                LPENTRYID                   lpEntryID) IPURE;           \


#undef       INTERFACE
#define      INTERFACE  ICEMAPISession
DECLARE_MAPI_INTERFACE_(ICEMAPISession, IMAPISession)
{
public:
    BEGIN_INTERFACE
    MAPI_IUNKNOWN_METHODS(PURE)
    MAPI_IMAPISESSION_METHODS(PURE)
    MAPI_ICEMAPISESSION_METHODS(PURE)
};

//----------------------------------------------------------------------------
// Custom CE Property Tags
//----------------------------------------------------------------------------

#define PR_CE_IMAP_UID                      PROP_TAG(PT_LONG,    0x8100)
#define PR_CE_MIME_TEXT                     PROP_TAG(PT_BINARY,  0x8103)    // This is CHAR text
#define PR_CE_IPM_DRAFTS_ENTRYID            PROP_TAG(PT_BINARY,  0x8104)
#define PR_CE_IPM_SEARCH_ENTRYID            PROP_TAG(PT_BINARY,  0x8105)
#define PR_CE_IPM_INBOX_ENTRYID             PROP_TAG(PT_BINARY,  0x8106)
#define PR_CONTENT_LENGTH_EX                PROP_TAG(PT_LONG,    0x8108)    // Full size of the message on the server.

#define PR_CE_XPRT_MSG_STATUS               PROP_TAG(PT_LONG,    0x8102)    // For transport flags.
#define PR_CE_XPRT_MESSAGE_FLAGS            PROP_TAG(PT_LONG,    0x810b)

#define PR_CE_ITEM_GENERATION               PROP_TAG(PT_LONG,    0x810c)    // Item generation

// This is the index of the item in a sorted folder list.  It's
// only returned from a IMAPITable::QueryRows() call.
#define PR_CE_ITEM_INDEX                    PROP_TAG(PT_LONG,    0x810d)

// This property contains a single wide string
// for all x-headers, (including all the \r\n).
#define PR_CE_XHEADERS                      PROP_TAG(PT_UNICODE, 0x8110)

#ifndef PR_MESSAGE_SIZE_EX
#define PR_MESSAGE_SIZE_EX                  PROP_TAG(PT_LONG,    0x8111)
#endif

// This property, when set, suppresses pop-up notification of the message's arrival
#define PR_CE_NO_NOTIFICATION               PROP_TAG(PT_BOOLEAN, 0x8112)

// This property is to uniquely identify a store. It's a guid.
#define PR_CE_UNIQUE_STORE_ID               PROP_TAG(PT_CLSID, 0x8113)

// This property is for storing EMS header data that comes with a SMS message
#define PR_CE_EMS_HEADER_DATA               PROP_TAG(PT_BINARY, 0x8114)

// Set this property on a message store to prevent it from being shown on the today page/homescreen unread counts
#define PR_CE_HIDE_FROM_TODAY_PAGE          PROP_TAG(PT_BOOLEAN, 0x8115)

// a property to determine if a folder is a search folder or not
#define PR_CE_IS_SEARCH_FOLDER              PROP_TAG(PT_BOOLEAN, 0x8116)

// This property is the name of the transport used for an account (e.g. SMS, POP3)
// This name is not localized
#define PR_CE_TRANSPORT_NAME                PROP_TAG (PT_UNICODE, 0x8117)

// Set this property on a message to indicate that various menu commands should be greyed out
#define PR_CE_CONTEXT_FLAGS                 PROP_TAG (PT_LONG, 0x8118)
#define CE_CONTEXT_DISABLE_REPLY            0x00000001  // The Reply and Reply All menu item should be disabled for this message
#define CE_CONTEXT_DISABLE_FORWARD          0x00000002  // The Forward menu item should be disabled for this message
#define CE_CONTEXT_DISABLE_DELETE           0x00000004  // The Delete menu item should be disabled for this message
#define CE_CONTEXT_DISABLE_MOVE             0x00000008  // The Move menu item should be disabled for this message
#define CE_CONTEXT_DISABLE_FLAG             0x00000010  // The Flag-related menu items should be disabled for this message
#define CE_CONTEXT_DISABLE_MARKREAD         0x00000020  // The Mark as Read/Unread menu items should be disabled for this message

// Account signature
#define PR_CE_SIGNATURE                     PROP_TAG (PT_UNICODE, 0x8119)

// Indicates whether the signature should be used for new messages
#define PR_CE_USE_SIGNATURE                 PROP_TAG (PT_BOOLEAN, 0x811A)

// Indicates whether the signature should be included in replies
#define PR_CE_USE_SIGNATURE_REPLY_FORWARD   PROP_TAG (PT_BOOLEAN, 0x811B)

// Account domain
#define PR_CE_DOMAIN                PROP_TAG (PT_UNICODE, 0x811F)

// Number of minutes between syncs
#define PR_CE_CHECK_INTERVAL        PROP_TAG (PT_I4,      0x8120)

// Number of bytes to download for a message
#define PR_CE_FETCH_SIZE            PROP_TAG (PT_I4,      0x8121)

// Maximum attachment size
#define PR_CE_ATTACH_FETCH_SIZE     PROP_TAG (PT_I4,      0x8122)

// Number of days to display
#define PR_CE_AGE_FILTER            PROP_TAG (PT_I4,      0x8123)

// Indicates whether the SMTP server requires authentication
#define PR_CE_SMTP_AUTHENTICATION   PROP_TAG (PT_BOOLEAN, 0x8124)

// Mail server for receiving mail
#define PR_CE_INCOMING_SERVER       PROP_TAG (PT_UNICODE, 0x8125)

// Mail server for sending mail
#define PR_CE_OUTGOING_SERVER       PROP_TAG (PT_UNICODE, 0x8126)

// Connection used to connect to servers
#define PR_CE_CONNECTION_GUID       PROP_TAG (PT_CLSID,   0x8127)

// Account requires SSL
#define PR_CE_REQUIRE_SSL           PROP_TAG (PT_BOOLEAN, 0x8128)

// What is the alternative SMTP account name?
#define PR_CE_SMTPALT_ACCOUNT       PROP_TAG (PT_UNICODE, 0x8129)

// What is the alternative SMTP domain?
#define PR_CE_SMTPALT_DOMAIN        PROP_TAG (PT_UNICODE, 0x812A)

// Are alternative creds needed for SMTP server?
#define PR_CE_SMTPALT_ENABLED       PROP_TAG (PT_BOOLEAN, 0x812B)

// Does SMTP server require SSL?
#define PR_CE_SMTPALT_SSL           PROP_TAG (PT_BOOLEAN, 0x812C)

// The SMS callback number for a message (on networks supporting SMS callback)
#define PR_CE_SMS_CALLBACK          PROP_TAG (PT_UNICODE, 0x812D)


// Message Format properties
// -------------------------
// (legal values are members of the MESSAGEFORMAT enumeration)

// The message format that a transport should prefer to retrieve if available,
// unless overriden on a particular message by PR_CE_PENDING_BODY_FORMAT.
//
// Set and read on message stores.
#define PR_CE_PREFERRED_DOWNLOAD_FORMAT PROP_TAG (PT_I4, 0x812E)

// The message format that should be fetched on either the next out of band fetch
// or the next mark for download.
//
// Set and read on messages.
#define PR_CE_PENDING_BODY_FORMAT       PROP_TAG (PT_I4,      0x812F)

// The original message format as it exists on the server, since we can download
// a different format than the native. (Used only for messages sync'ed from a transport,
// not messages authored on the device for sending.)
//
// Set and read on received messages.
#define PR_CE_NATIVE_MESSAGE_FORMAT     PROP_TAG (PT_I4,      0x8130)

// Raw binary data from a raw SMS message
#define PR_CE_SMS_RAW_HEADER            PROP_TAG (PT_BINARY,  0x8131)
#define PR_CE_SMS_RAW_BODY              PROP_TAG (PT_BINARY,  0x8132)

// Fetch Failure Indication properties
// -----------------------------------
//
// Used in conjunction with kszCapImmediateDownload. These properties
// indicate via MAPI notifications whether an attempt to retrieve a
// message outside of the normal send/receive flow has failed.

// Indicates via notification that the attempt to retrieve the message
// body has failed. The value of this property is not used.
#define PR_CE_FETCH_BODY_FAILURE        PROP_TAG (PT_LONG,      0x8133)

// Indicates via notification that the attempt to retrieve attachments
// for the message has failed. The binary value is an array of ULONG
// indices of attachments that failed. The size of the array can be
// found by dividing the total binary size by sizeof(ULONG).
// The value is valid only until the next attachment failure.
#define PR_CE_FETCH_ATTACHMENT_FAILURE  PROP_TAG (PT_BINARY,    0x8134)


// An account property that indicates that the application should
// automatically invoke a Send/Receive when a message is sent to the Outbox.
#define PR_CE_SYNC_ON_SEND              PROP_TAG (PT_BOOLEAN,   0x8135)

// Indicates that the MAPI notification should not initiate
// an immediate download (fetch) of the modified object.
#define PR_CE_SUPPRESS_FETCH                    PROP_TAG (PT_LONG,  0x8136)

// Prevents an account from automatically connecting while roaming
#define PR_CE_SYNC_MANUALLY_WHEN_ROAMING        PROP_TAG (PT_LONG,  0x8137)


// For quick recognition of the recipient types for a message.
#define MSGSTATUS_RECTYPE_SMTP                  0x00020000
#define MSGSTATUS_RECTYPE_SMS                   0x00040000

// Re-use the above flags for incoming SMS status messages
// which are mutually exclusive from outgoing messages.
#define MSGSTATUS_SMSSTATUS_SUCCESS             0x00020000

// To determine if any transport still needs to send the message...
#define MSGSTATUS_RECTYPE_ALLTYPES              (MSGSTATUS_RECTYPE_SMTP | MSGSTATUS_RECTYPE_SMS)

// This flag should be set if only the header has been downloaded.
#define MSGSTATUS_HEADERONLY                    0x00010000

// This flag is set if the item should be partially downloaded.
#define MSGSTATUS_PARTIAL_DOWNLOAD              0x00080000

// This flag is set if the item is only partially downloaded.
#define MSGSTATUS_PARTIAL                       0x00100000

// This flag is set if the message has at least one attachment marked for downloaded.
#define MSGSTATUS_REMOTE_DOWNLOAD_ATTACH        0x00200000

// This flag is set if the MIME header needs to be downloaded.
#define MSGSTATUS_REMOTE_DOWNLOAD_HEADER        0x00400000

// This flag is set if the message has a TNEF blob attached.
#define MSGSTATUS_HAS_TNEF                      0x00800000

// This flag is set if the TNEF of a message needs to be downloaded.
#define MSGSTATUS_REMOTE_DOWNLOAD_TNEF          0x01000000

// This flag is set if the attachment has a copy on the server.
#define MSGSTATUS_GHOSTED_ATTACH                0x02000000

// This flag is set if there are attachments on the message that
// have not yet been downloaded.
#define MSGSTATUS_PENDING_ATTACHMENTS           0x04000000

// This flag is set if the message has PR_CE_MIME_TEXT property
#define MSGSTATUS_HAS_PR_CE_MIME_TEXT           0x08000000

// This flag is set if the message has PR_BODY property
#define MSGSTATUS_HAS_PR_BODY                   0x10000000

// This flag is set if the message has PR_CE_SMIME_TEXT property
#define MSGSTATUS_HAS_PR_CE_SMIME_TEXT          0x20000000

// This flag is set if the message has PR_CE_CRYPT_MIME_TEXT property
#define MSGSTATUS_HAS_PR_CE_CRYPT_MIME_TEXT     0x40000000

// This flag is set if the message has PR_BODY_HTML property
#define MSGSTATUS_HAS_PR_BODY_HTML              0x80000000




//===========================================================================
// Mail application functions
//===========================================================================

// MAILCOMPOSEFIELDS flag values
#define MCF_ACCOUNT_IS_NAME             0x01
#define MCF_ACCOUNT_IS_TRANSPORT        0x02
#define MCF_MAILTO_FORMAT               0x04  // pszTo is in "mailto" format
#define MCF_RUN_IN_BACKGROUND           0x08  // App should run in background, used with MailSyncMessages

// Structure of flags used for composing a new message
typedef struct _MAILCOMPOSEFIELDS
{
    DWORD cbSize;                    // Set to structure size
    DWORD dwFlags;                   // Combination of MCF_ flags above
    LPCTSTR pszTo;                   // To address
    LPCTSTR pszCc;                   // Cc address
    LPCTSTR pszBcc;                  // Bcc address
    LPCTSTR pszSubject;              // Message subject
    LPCTSTR pszBody;                 // Message body
    LPCTSTR pszAttachments;          // NULL-separated list of attachment file names
    UINT cAttachments;               // Number of attachments in pszAttachFiles
    LPCTSTR pszAccount;              // Name of account to use (whether is name of account or transport name is determined by dwFlags)
    LPCTSTR pszMsgClass;             // Name of message class to use (default if NULL)
} MAILCOMPOSEFIELDS;


extern "C"
{
 
// Displays a new message, determined by the information in MAILCOMPOSEFIELDS.  pmcf can be NULL.
HRESULT WINAPI MailComposeMessage(MAILCOMPOSEFIELDS *pmcf);
 
// Displays an existing message as opposed to creating a new one.  Message is determined by ENTRYID.
HRESULT WINAPI MailDisplayMessage(LPENTRYID lpEntryID, ULONG cbEntryID);

// Switches to a folder.  lpEntryID is the ENTRYID of the folder we want to switch to in listview, cbEntryID is the size of the ENTRYID.
HRESULT WINAPI MailSwitchToFolder(LPENTRYID lpEntryID, ULONG cbEntryID);

// Switches to an account.  Specify the account by name or transport (determined by dwFlags which takes an MCF_ value).
HRESULT WINAPI MailSwitchToAccount(LPCTSTR pszAccount, DWORD dwFlags);

// Syncs mail.  Specify the account by name or transport (determined by dwFlags which takes an MCF_ value).  
// If pszAccount is NULL, the current account is synced.
HRESULT WINAPI MailSyncMessages(LPCTSTR pszAccount, DWORD dwFlags);

// Launches the Messaging application and invokes the new account wizard. Returns immediately.
//
// return values - S_OK for success, error code if failure
HRESULT WINAPI MailLaunchNewAccountWizard();

}

//===========================================================================
// Message Forms
//===========================================================================

class IMessageFormEx;
class IFormProviderEx;

extern "C" {
HRESULT WINAPI FormFactoryEx(LPCWSTR pszMsgClass, IFormProviderEx** ppObj);
}

typedef HRESULT (WINAPI *FORMFACTORYEXFUNC)(LPCWSTR pszMsgClass, IFormProviderEx** ppObj);



#define MESSAGEFORMHOST2_CMDBARCAP_COPY                 0x1
#define MESSAGEFORMHOST2_CMDBARCAP_CUT                  0x2
#define MESSAGEFORMHOST2_CMDBARCAP_PASTE                0x4
#define MESSAGEFORMHOST2_CMDBARCAP_SELECTALL            0x8
#define MESSAGEFORMHOST2_CMDBARCAP_CLEAR                0x10
#define MESSAGEFORMHOST2_CMDBARCAP_SAVETOCONTACTS       0x20
#define MESSAGEFORMHOST2_CMDBARCAP_FORWARD              0x40
#define MESSAGEFORMHOST2_CMDBARCAP_REPLY                0x80
#define MESSAGEFORMHOST2_CMDBARCAP_REPLYALL             0x100
#define MESSAGEFORMHOST2_CMDBARCAP_MARKASUNREAD         0x200
#define MESSAGEFORMHOST2_CMDBARCAP_GETFULLMESSAGE       0x400
#define MESSAGEFORMHOST2_CMDBARCAP_MOVETO               0x800
#define MESSAGEFORMHOST2_CMDBARCAP_LANGUAGE             0x1000
#define MESSAGEFORMHOST2_CMDBARCAP_ADDATTACHMENT        0x2000
#define MESSAGEFORMHOST2_CMDBARCAP_SPELLCHECK           0x4000
#define MESSAGEFORMHOST2_CMDBARCAP_CHECKNAMES           0x8000
#define MESSAGEFORMHOST2_CMDBARCAP_OPTIONS              0x20000
#define MESSAGEFORMHOST2_CMDBARCAP_MYTEXTMESSAGE        0x40000
#define MESSAGEFORMHOST2_CMDBARCAP_MYTEXTMESSAGESEDIT   0x80000
#define MESSAGEFORMHOST2_CMDBARCAP_MTGACCEPT            0x100000
#define MESSAGEFORMHOST2_CMDBARCAP_MTGDECLINE           0x200000
#define MESSAGEFORMHOST2_CMDBARCAP_MTGTENTATIVE         0x400000
#define MESSAGEFORMHOST2_CMDBARCAP_MTGREMOVEFROMCAL     0x800000
#define MESSAGEFORMHOST2_CMDBARCAP_CONTACTSPICKER       0x1000000
#define MESSAGEFORMHOST2_CMDBARCAP_VOICERECORDER        0x2000000
#define MESSAGEFORMHOST2_CMDBARCAP_INSERTPICTURE        0x4000000
#define MESSAGEFORMHOST2_CMDBARCAP_CALLVOICEMAIL        0x8000000


// Extended command bar capabilities going though IMessageFormEx2
#define MESSAGEFORMHOST2_CMDBARCAP_EX_BASE              0x90000000
#define MESSAGEFORMHOST2_CMDBARCAP_EX_SAVE              MESSAGEFORMHOST2_CMDBARCAP_EX_BASE
#define MESSAGEFORMHOST2_CMDBARCAP_EX_VIEW_ZOOM         (MESSAGEFORMHOST2_CMDBARCAP_EX_BASE + 1)
#define MESSAGEFORMHOST2_CMDBARCAP_EX_GET_HTML          (MESSAGEFORMHOST2_CMDBARCAP_EX_BASE + 2)
#define MESSAGEFORMHOST2_CMDBARCAP_EX_FOLLOWUPFLAG      (MESSAGEFORMHOST2_CMDBARCAP_EX_BASE + 3)
#define MESSAGEFORMHOST2_CMDBARCAP_EX_DELETE            (MESSAGEFORMHOST2_CMDBARCAP_EX_BASE + 4)
#define MESSAGEFORMHOST2_CMDBARCAP_EX_FOLLOWUPFLAG_COMPLETE (MESSAGEFORMHOST2_CMDBARCAP_EX_BASE + 5)
#define MESSAGEFORMHOST2_CMDBARCAP_EX_MTGPROPOSENEWTIME (MESSAGEFORMHOST2_CMDBARCAP_EX_BASE + 6)   
#define MESSAGEFORMHOST2_CMDBARCAP_EX_MAX               MESSAGEFORMHOST2_CMDBARCAP_EX_MTGPROPOSENEWTIME

// GUID for QueryInterface only
// {9FF8D3A4-7A4A-4cce-B90B-754A8A8CC643}
static const GUID IID_IMessageFormHostEx =
{ 0x9ff8d3a4, 0x7a4a, 0x4cce, { 0xb9, 0xb, 0x75, 0x4a, 0x8a, 0x8c, 0xc6, 0x43 } };

class IMessageFormHostEx
{
public:
    enum CLOSINGMSGSTATUS {
        CMS_NOT_AVAILABLE = 0,
        CMS_SENT = 1,
        CMS_POSTPONED = 2,
        CMS_DELETE = 3,
        CMS_DELETE_PERMANENTLY = 4
    };
    virtual HRESULT FormClosing(IMessageFormEx* pform,
                        IMessage* pMsg, CLOSINGMSGSTATUS eCMS) _PURE;

    // This host method is the same one provided as part of IMailSyncCallBack.
    MAPIMETHOD(GetGlobalSetting)(LPCWSTR pszSetting, LPSPropValue pval) _PURE;
    MAPIMETHOD(SetGlobalSetting)(LPCWSTR pszSetting, LPSPropValue pval) _PURE;

    enum HOSTACTIONS {
        HOSTACT_NULL = 0,
        HOSTACT_FIRST = 0,
        HOSTACT_REPLY = 1,
        HOSTACT_REPLY_TO_ALL = 2,
        HOSTACT_FORWARD = 3,
        HOSTACT_DELETE = 4,
        HOSTACT_CLOSE = 5,
        HOSTACT_MOVE_TO_FOLDER = 6,
        HOSTACT_GOTO_NEXT_MESSAGE = 7,
        HOSTACT_GOTO_PREV_MESSAGE = 8,
        HOSTACT_COMPOSE_NEW = 9,
        HOSTACT_GET_FULL_MESSAGE = 10,
        HOSTACT_VIEW_ATTACHMENT = 11,
        HOSTACT_REPLY_WITH = 12,
        HOSTACT_SHOW = 13,
        HOSTACT_MARK_AS_UNREAD = 14,
        HOSTACT_VCARD_ACCEPT = 15,
        HOSTACT_SET_FOLLOW_UP_FLAG = 16,
        HOSTACT_COMPLETE_FOLLOW_UP_FLAG = 17,
        HOSTACT_CLEAR_FOLLOW_UP_FLAG = 18,
        HOSTACT_TOGGLE_FOLLOW_UP_FLAG = 19,
        HOSTACT_GET_HTML = 20,
        HOSTACT_TOGGLE_ATTACHMENT = 21,
        HOSTACT_LAST
    };

    virtual HRESULT DoAction(IMessageFormEx* pform, IMessage* pmsg,
            HOSTACTIONS act, MESSAGEFIELDS *pMsgFields) _PURE;
    virtual HRESULT CreateNewMessage(IMessage** ppmsg) _PURE;
};




// {501A8BFB-D672-4b34-BACF-85C42051868E}
static const GUID IID_IMessageFormEx =
{ 0x501a8bfb, 0xd672, 0x4b34, { 0xba, 0xcf, 0x85, 0xc4, 0x20, 0x51, 0x86, 0x8e } };

class IMessageFormEx : public IUnknown
{
public:
    MAPIMETHOD(SetMessage)(
            WORD            wType,
            LPMESSAGE       pmsg
    ) _PURE;

    MAPIMETHOD(CloseForm)(
                        BOOL fSave=FALSE
    ) _PURE;

    MAPIMETHOD(PreTranslateMsg)(
            MSG* pmsg,
            BOOL* pfProcessed           // Set TRUE if the message taken
    ) _PURE;

    MAPIMETHOD(OnMessageModified)(
        ULONG           cbId,
        LPENTRYID       pid,
        LPSPropTagArray props
    ) _PURE;

    enum FORMACTIONS {
        FORMACT_NULL = 0,
        FORMACT_FIRST = 0,
        FORMACT_POSTPONE = 1,
        FORMACT_COPY = 2,
        FORMACT_CUT = 3,
        FORMACT_PASTE = 4,
        FORMACT_SELECT_ALL = 5,
        FORMACT_CLEAR = 6,
        FORMACT_DELETE = 7,
        FORMACT_FORWARD = 8,
        FORMACT_REPLY = 9,
        FORMACT_REPLY_TO_ALL = 10,
        FORMACT_SEND = 11,
        FORMACT_MARK_AS_UNREAD = 12,
        FORMACT_MARK_FOR_DOWNLOAD = 13,
        FORMACT_MOVE_TO = 14,
        FORMACT_LANGUAGE = 15,
        FORMACT_ADD_ATTACHMENT = 16,
        FORMACT_SPELL_CHECK = 17,
        FORMACT_CHECK_NAMES = 18,
        FORMACT_OPTIONS = 19,
        FORMACT_MY_TEXT_MESSAGE = 20,
        FORMACT_MY_TEXT_MESSAGES_EDIT = 21,
        FORMACT_MEETING_ACCEPT = 22,
        FORMACT_MEETING_DECLINE = 23,
        FORMACT_MEETING_TENTATIVE = 24,
        FORMACT_MEETING_REMOVE_FROM_CALENDAR = 25,
        FORMACT_CONTACTS_PICKER = 26,
        FORMACT_VOICE_RECORDER = 27,
        FORMACT_INSERT_PICTURE = 28,
        FORMACT_SAVE_CONTACT = 29,
        FORMACT_CALL_VOICEMAIL = 30,
        FORMACT_SET_FOLLOW_UP_FLAG = 31,
        FORMACT_COMPLETE_FOLLOW_UP_FLAG = 32,
        FORMACT_CLEAR_FOLLOW_UP_FLAG = 33,
        FORMACT_TOGGLE_FOLLOW_UP_FLAG = 34,
        FORMACT_VIEW_SMALLEST = 35,
        FORMACT_VIEW_SMALLER = 36,
        FORMACT_VIEW_NORMAL = 37,
        FORMACT_VIEW_LARGER = 38,
        FORMACT_VIEW_LARGEST = 39,
        FORMACT_GET_HTML = 40,
        FORMACT_VCARD_ACCEPT = 41,
        FORMACT_MEETING_PROPOSE_NEW_TIME = 42,
        
        FORMACT_LAST
    };

    MAPIMETHOD(DoAction)(FORMACTIONS actForm, DWORD dwValue, BOOL* pfProcessed) _PURE;
    MAPIMETHOD(GetMenuCapabilities)(DWORD dwFlags, DWORD* pdwEnable) _PURE;

};


// {1C4B00EC-3D25-4906-A97C-C822935AC5A0}
static const GUID IID_IMessageFormEx2 = 
{ 0x1c4b00ec, 0x3d25, 0x4906, { 0xa9, 0x7c, 0xc8, 0x22, 0x93, 0x5a, 0xc5, 0xa0 } };

class __declspec(uuid("1C4B00EC-3D25-4906-A97C-C822935AC5A0"))
IMessageFormEx2 : public IMessageFormEx
{
public:
    MAPIMETHOD(GetMenuCapability)(
            DWORD           dwCapability,
            BOOL *          pfEnabled
    ) _PURE;
};


// Used with FORMACT_LANGUAGE
//  dwFlags == Query => Form should fill uiCodePage with current CP
//  dwFlags == Select => Form should use uiCodePage as current CP
//  dwFlags == Init => Form should not refresh its data on initial CP setting
typedef struct _FORMACTLANGUAGEDATA
{
    enum
    {
        Query   = 0x01,
        Select  = 0x02,
        Init    = 0x04,
    };

    DWORD   dwFlags;
    UINT    uiCodePage;
} FORMACTLANGUAGEDATA;


// GUID for QueryInterface only
// {F1BB10ED-4B19-4208-9C9C-80EE715DD976}
static const GUID IID_IFormProviderEx =
{ 0xf1bb10ed, 0x4b19, 0x4208, { 0x9c, 0x9c, 0x80, 0xee, 0x71, 0x5d, 0xd9, 0x76 } };
class IFormProviderEx : public IUnknown
{
public:

    enum FORMTYPE {
        FORMTYPE_NEW_MESSAGE = 0,
        FORMTYPE_REPLY = 1,
        FORMTYPE_REPLY_TO_ALL = 2,
        FORMTYPE_REPLY_WITH = 3,
        FORMTYPE_FORWARD = 4,
        FORMTYPE_LOAD = 5
    };

    MAPIMETHOD(GetMsgStatusIconIndex)(
            LPMAPIFOLDER    pfldr,     // Folder for message
            LPENTRYID       pid,       // Id of message
            ULONG           cbid,      // count of bytes for the id
            ULONG           ffFlags,   // Flags for the message
            ULONG           ffStatus,  // Status for the message
            LPCWSTR         pszMsgClass,
            ULONG           cAttachments,
            ULONG*          pnIndex    // OUT: Index for the correct glyph
    ) _PURE;

    MAPIMETHOD(CreateComposeForm)(
            IMessageFormHostEx* pHost,
            LPMESSAGE       pMsg,       // Object to compose
            FORMTYPE        eFormType,  // Reply, Reply All, Forward
            LPMESSAGE       pMsgBase,   // Message to prefill the form if necessary
            MESSAGEFIELDS*  pMsgFields, // message fields for the new message
            HWND            hwndForm,   // HWND of the form frame
            HWND*           phwndBody,  // HWND of the form-created body
            IMessageFormEx**  ppForm    // Form object
    ) _PURE;

    MAPIMETHOD(CreateReadForm)(
            IMessageFormHostEx* pHost,
            LPMESSAGE       pMsg,       // Object to compose
            HWND            hwndForm,   // HWND of the form frame
            HWND*           phwndBody,  // HWND of the form-created body
            IMessageFormEx**  ppForm    // Form object
    ) _PURE;
};


typedef struct _INBOXGLYPHINFO {
    ULONG cbSize;       // Total size of structure
    ULONG ResIdColor;   // Resource ID of the bitmap (color)
    ULONG ResIdMono;    // Resource ID of the bitmap (monographic)
    ULONG iUnRead;      // Index of "Read" glyph
    ULONG iRead;        // Index of "UnRead" glyph
    ULONG iRepliedTo;   // Index of "Replied To" glyph
    ULONG iForwarded;   // Index of "Forwarded" glyph
    ULONG iAttachment;  // Index of "Attachment" glyph
} INBOXGLYPHINFO;


// Menu extensions -- see appext.h for the definition of ItemRef
// Within the ItemRef array, pType will point to one of these GUIDs
// The value of pType determines what pRef points to as noted

// pRef will point to an SBinary structure containing the ENTRYID of a message and the size of that ENTRYID
// {412F24E9-87E6-4bd5-9820-23E9230D6E8D}
static const GUID ITI_MessageItemRef = 
{ 0x412f24e9, 0x87e6, 0x4bd5, { 0x98, 0x20, 0x23, 0xe9, 0x23, 0xd, 0x6e, 0x8d } };

// pRef will point to an SBinary structure containing the ENTRYID of a folder and the size of that ENTRYID
// {1477399E-B31D-4d3d-AFFA-070E71CA8719}
static const GUID ITI_FolderItemRef = 
{ 0x1477399e, 0xb31d, 0x4d3d, { 0xaf, 0xfa, 0x7, 0xe, 0x71, 0xca, 0x87, 0x19 } };

// pRef will point to an SBinary structure containing the ENTRYID of a store and the size of that ENTRYID
// {258E8499-B7C5-49a0-9A82-8B346D1E3976}
static const GUID ITI_StoreItemRef = 
{ 0x258e8499, 0xb7c5, 0x49a0, { 0x9a, 0x82, 0x8b, 0x34, 0x6d, 0x1e, 0x39, 0x76 } };

// pRef will point to the IMessageFormEx pointer of the active form
// {D241E414-74D9-45e3-A4E5-657F308C42AE}
static const GUID ITI_MessageFormExItemRef = 
{ 0xd241e414, 0x74d9, 0x45e3, { 0xa4, 0xe5, 0x65, 0x7f, 0x30, 0x8c, 0x42, 0xae } };


// Error codes...

#define CEMAPI_E_PLAINTEXT_NOTSUPPORTED         MAKE_MAPI_E(0x901)
#define CEMAPI_E_PROTOCOL_ERROR                 MAKE_MAPI_E(0x902)
#define CEMAPI_E_NO_ACCOUNT_INFO                MAKE_MAPI_E(0x903)
#define CEMAPI_E_NEED_TO_CONNECT                MAKE_MAPI_E(0x904)
#define CEMAPI_E_MUST_SYNC_ONCE                 MAKE_MAPI_E(0x905)
#define CEMAPI_E_STORE_UNAVAILABLE              MAKE_MAPI_E(0x906)


#endif // eof...
