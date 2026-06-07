/*---------------------------------------------------------------------------*\
 *
 * (c) Copyright Microsoft Corp. 1998 All Rights Reserved
 *
 *  module: msgxport.h
 *  date:   981002
 *
 *  purpose: Definitions for Mail Transport Interface
 *
\*---------------------------------------------------------------------------*/

#ifndef MSGXPORT_H
#define MSGXPORT_H

#define TRANSPORT_SEND    0x0000001
#define TRANSPORT_RECV    0x0000002

//Messages that transport can send back to pmail
    // tell pmail that connection has closed in background
    // (this would be sent if, for example, you were connected
    // over RAS and lost the modem connection)
    // both wparam and lparam are ignored
    // return is always 0
#define TRANSPORT_CONN_LOST (WM_USER+1)

    // tell pmail to refresh its connection to the service
    // this would be used if pmail has an open connection to the service
    // and the service determines a new message has arrived
    // both wparam and lparam are ignored
    // return is always 0
#define TRANSPORT_REFRESH   (WM_USER+2)

#define TRANSPORT_HEADERS       0
#define TRANSPORT_ALL_LINES -1
#define TRANSPORT_MSG_EXIST -2


#define TRANSPORT_MSGFLAG_READ          0x00000001
#define TRANSPORT_MSGFLAG_ANSWERED      0x00000002
#define TRANSPORT_MSGFLAG_COMPOSED      0x00000004
#define TRANSPORT_MSGFLAG_FLAGGED       0x00000008

#ifdef __cplusplus
extern "C" {
#endif

BOOL TransportInit(HANDLE* serviceHandle_p, LPWSTR commonRegKey_p, LPWSTR serviceRegKey_p);
BOOL TransportCheckForNewMail(HANDLE serviceHandle_p, CHECKFORNEWMAILCALLBACK callBackFunction_p);
BOOL TransportConnect(HANDLE serviceHandle_p, DWORD flags_p, HWND notifyHwnd_p, CONNECTCALLBACK callBackFunction_p);
BOOL TransportCount(HANDLE serviceHandle_p, LPWORD messageCount_p);
BOOL TransportNonIpm(MailMsg * MsgPtr);
BOOL TransportRecv(HANDLE serviceHandle_p, WORD sessionId_p, short numberLines_p, MailMsg *mailMessage_p, lpMailAttArray * lplpMailArray);
BOOL TransportSetMsgFlags(HANDLE hService, MailMsg* pMsgPtr, DWORD dwFlags, BOOL fValue);
BOOL TransportDisconnect(HANDLE serviceHandle_p);
BOOL TransportRelease(HANDLE serviceHandle_p);
BOOL TransportSend(HANDLE serviceHandle_p, MailMsg* mailMessage_p);
BOOL TransportProps(HWND hwndParent_p, LPWSTR commonRegKey_p, LPWSTR serviceRegKey_p);
BOOL TransportDuplicateHandle(HANDLE hOld, HANDLE* phNew);
int TransportError(HANDLE serviceHandle_p);
int TransportErrorEx(HANDLE serviceHandle_p, BOOL* pfCritical);
int TransportErrorMsg(HANDLE serviceHandle_p, LPWSTR buffer_p, int bufferLen_p, int* lineNum_p);
BOOL TransportFreeMsg(MailMsg *mailMessage_p);
BOOL TransportDel(HANDLE serviceHandle_p, MailMsg *mailMessage_p);
BOOL TransportView(HWND hwndParent_p, MailMsg *mailMessage_p);
BOOL TransportDownloadAttachment(HANDLE serviceHandle_p, MailMsg* mailMessage_p, MailAtt* mailAtt_p);
BOOL TransportSetPassword(HANDLE serviceHandle_p, LPWSTR userPassword, BOOL remember);
BOOL TransportSetActiveFolder( HANDLE serviceHandle_p, LPWSTR szFolderID_p);
BOOL TransportGetFolders(HANDLE serviceHandle_p, LPWSTR szFolderID_p,
                                   lpTransportFolderList* ppFolders_p);
BOOL TransportFreeFolderList(HANDLE hService_p, lpTransportFolderList pFolders_p);
BOOL TransportUIDsChanged(HANDLE hService_p, BOOL* pfChanged);
BOOL TransportCancel(HANDLE hService_p);
BOOL TransportPut(HANDLE hService_p, LPWSTR szFolderID_p, MailMsg* MsgPtr_p);
BOOL TransportDelFolder(HANDLE hService_p, LPWSTR szFolderID);
BOOL TransportExpunge(HANDLE hService_p, lpTransportFolderList pFolders_p);
BOOL  TransportGetInboxId(HANDLE hService_p, LPWSTR* pszInboxID_p);
BOOL  TransportCopy(HANDLE hService_p, MailMsg* MsgPtr_p, LPWSTR szDestFolderID_p);
BOOL  TransportMove(HANDLE hService_p, MailMsg* MsgPtr_p, LPWSTR szDestFolderID_p);
BOOL  TransportPutFolder(HANDLE hService_p, LPWSTR szFolderName_p,
                                    LPWSTR szParentID_p, LPWSTR* pszCreatedID_p);
BOOL  TransportFreeFolderId(HANDLE hService_p, LPWSTR szFolderID_p);
BOOL TransportCountEx(HANDLE hService_p, LPWSTR szFolderID_p,WORD* pwNumMsg_p);
BOOL  TransportRecvEx(HANDLE hService_p, LPWSTR szFolderID_p,WORD wMsgID_p,
                                 short sNumLines_p, MailMsg* MsgPtr_p,
                                 lpMailAttArray*  lplpmaa_p);


#ifdef __cplusplus
};
#endif

#endif // MSGXPORT_H
