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

#define MESSAGEFIELDS_FLAGS_DELETEONCLOSE   0x00000001
#define MESSAGEFIELDS_FLAGS_SMSSERVICE      0x00000002

const DWORD kdwOptionValueNone = 0;
const DWORD kdwOptionValueAll  = 0xFFFFFFFF;

const WCHAR kszCapHTMLMail[]                    = L"HTMLMail";
const WCHAR kszCapAmountToFetch[]               = L"FetchSize";
const WCHAR kszCapAttachAmount[]                = L"AttachFetchSize";
const WCHAR kszCapAgeFilter[]                   = L"AgeFilter";
const WCHAR kszCapSaveSent[]                    = L"SaveSent";
const WCHAR kszCapSMSUnicode[]                  = L"SMSUnicode";
const WCHAR kszCapSMTPAuthenticate[]            = L"SMTPAuthenticate";
const WCHAR kszCapIncludeOriginal[]             = L"IncludeOriginal";
const WCHAR kszCapIndentBody[]                  = L"IndentBody";
const WCHAR kszCapAddLeading[]                  = L"AddLeading";
const WCHAR kszCapLeadChar[]                    = L"LeadChar";
const WCHAR kszCapSMSRequestStatus[]            = L"SMSRequestStatus";
const WCHAR kszCapSyncMsgClasses[]              = L"SyncMsgClasses";
const WCHAR kszCapSyncMsgClassDef[]             = L"SyncMsgClassDef";
const WCHAR kszCapPropDialog[]                  = L"PropDialog";
const WCHAR kszCapSMTPAllowAuthLogin[]          = L"SMTPAllowAuthLogin";
const WCHAR kszCapSyncHierarchy[]               = L"SyncHierarchy";
const WCHAR kszCapDeleteAction[]                = L"DeleteAction";
const WCHAR kszCapMoveToTrash[]                 = L"TrashMoves";

const WCHAR kszCapReturnAddress[]               = L"ReturnAddress";
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

#define PR_CE_IMAP_UID              PROP_TAG(PT_LONG,    0x8100)
#define PR_CE_MIME_TEXT             PROP_TAG(PT_BINARY,  0x8103)    // This is CHAR text
#define PR_CE_IPM_DRAFTS_ENTRYID    PROP_TAG(PT_BINARY,  0x8104)
#define PR_CE_IPM_INBOX_ENTRYID     PROP_TAG(PT_BINARY,  0x8106)
#define PR_CONTENT_LENGTH_EX        PROP_TAG(PT_LONG,    0x8108)    // Full size of the message on the server.

#define PR_CE_XPRT_MSG_STATUS       PROP_TAG(PT_LONG,    0x8102)    // For transport flags.
#define PR_CE_XPRT_MESSAGE_FLAGS    PROP_TAG(PT_LONG,    0x810b)

#define PR_CE_ITEM_GENERATION       PROP_TAG(PT_LONG,    0x810c)    // Item generation

// This is the index of the item in a sorted folder list.  It's
// only returned from a IMAPITable::QueryRows() call.
#define PR_CE_ITEM_INDEX            PROP_TAG(PT_LONG,    0x810d)

// This property contains a single wide string
// for all x-headers, (including all the \r\n).
#define PR_CE_XHEADERS              PROP_TAG(PT_UNICODE, 0x8110)

#ifndef PR_MESSAGE_SIZE_EX
#define PR_MESSAGE_SIZE_EX          PROP_TAG(PT_LONG,    0x8111)
#endif

// This property, when set, suppresses pop-up notification of the message's arrival
#define PR_CE_NO_NOTIFICATION       PROP_TAG(PT_BOOLEAN, 0x8112)

// This property is to uniquely identify a store. It's a guid.
#define PR_CE_UNIQUE_STORE_ID       PROP_TAG(PT_CLSID, 0x8113)

// This property is for storing EMS header data that comes with a SMS message
#define PR_CE_EMS_HEADER_DATA       PROP_TAG(PT_BINARY, 0x8114)

// Set this property on a message store to prevent it from being shown on the today page/homescreen unread counts
#define PR_CE_HIDE_FROM_TODAY_PAGE  PROP_TAG (PT_BOOLEAN, 0x8115)






// For quick recognition of the recipient types for a message.
#define MSGSTATUS_RECTYPE_SMTP      0x00020000
#define MSGSTATUS_RECTYPE_SMS       0x00040000

// Re-use the above flags for incoming SMS status messages
// which are mutually exclusive from outgoing messages.
#define MSGSTATUS_SMSSTATUS_SUCCESS 0x00020000

// To determine if any transport still needs to send the message...
#define MSGSTATUS_RECTYPE_ALLTYPES  (MSGSTATUS_RECTYPE_SMTP | MSGSTATUS_RECTYPE_SMS)

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
        FORMACT_LAST
    };

    MAPIMETHOD(DoAction)(FORMACTIONS actForm, DWORD dwValue, BOOL* pfProcessed) _PURE;
    MAPIMETHOD(GetMenuCapabilities)(DWORD dwFlags, DWORD* pdwEnable) _PURE;

};



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


// Error codes...

#define CEMAPI_E_PLAINTEXT_NOTSUPPORTED         MAKE_MAPI_E(0x901)
#define CEMAPI_E_PROTOCOL_ERROR                 MAKE_MAPI_E(0x902)
#define CEMAPI_E_NO_ACCOUNT_INFO                MAKE_MAPI_E(0x903)
#define CEMAPI_E_NEED_TO_CONNECT                MAKE_MAPI_E(0x904)
#define CEMAPI_E_MUST_SYNC_ONCE                 MAKE_MAPI_E(0x905)


#endif // eof...
