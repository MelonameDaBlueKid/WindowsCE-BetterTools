/*---------------------------------------------------------------------------*\
 *
 * (c) Copyright Microsoft Corp. 1997 All Rights Reserved
 *
 *  module: svcsampl.h
 *
 *  purpose: Sample Service Private Definitions
 *
\*---------------------------------------------------------------------------*/

#ifndef _SVCSAMPL_H_
#define _SVCSAMPL_H_

// Maximum size of a directory
// we assume filenames are never longer than 2*MAX_DIR_SIZE
#define MAX_DIR_SIZE	    256

// Assumed maximum size of key data stored in registry
#define MAX_HANDLE_SIZE	    64

// Max number of messages this library works with
// this number was arbitrarily chosen to limit the amount
// of memory used.  If we were writing a "real" service,
// we would have allowed an unlimited number of messages
// (or limited the number to a service-specifed max) and
// used dynamic memory allocation
#define MAX_MSGS	    64

// macro used to record error information
#define ERR(e)  return (hService->iErrLine = __LINE__,hService->iErr = TRANS_ERR_##e,FALSE)

// short cut for specifying unicode text
#ifndef _T
#define _T(x) TEXT(x)
#endif

// These are the error numbers used for error returns
#define	TRANS_ERR_NONE		    0
#define	TRANS_ERR_NO_SVC_DIR	    1
#define	TRANS_ERR_HANDLE_NOT_ALLOC  2
#define TRANS_ERR_CANT_SEND	    3
#define TRANS_ERR_CANT_OPEN	    4
#define TRANS_ERR_INV_MSG_ID	    5
#define TRANS_ERR_NO_MSG_BUF	    6
#define TRANS_ERR_READ		    7

// this is our private definition of the service.  everything
// outside our library only has a handle to this structure
typedef struct tagservice {
    int		iErr;			// in case of an error, this
					// value gets the number of the
					// error.
    int		iErrLine;		// in case of an error, this
					// value gets the source line
					// of the error, it is then
					// displayed by pmail
    HWND	hWndNotify;		// window to send notification
					// messages to
    BOOL	(*CallBack)(int,BOOL);	// this is used to hold the
					// address of the callback routine
					// specified in Connect
    BOOL	fRecActive;		// this flag tells us if the
					// service is currently active for
					// receiving (it is not used in
					// this example).
    BOOL	fTransActive;		// this flag tells us if the
					// service is currently active for
					// transmission (it is not used
					// in this example).
    WORD	wNumMsgs;		// Number of messages stored on service
    WORD	wHighNum;		// Highest message number used by
					// service (this is used for the
					// creation of new messages).
    WCHAR	szMailDir[MAX_DIR_SIZE];// This is the name of the directory
					// which holds all of the messages
    WCHAR	szRetAddr[128];		// This field holds the return address of the
					// service
    WCHAR	Uids[MAX_MSGS][11];	// This array holds the unique ids
					// of each message in the service.
					// This memory needs to be allocated
					// during the Connect() and kept alive
					// for as long as the service is active.
					// Dynamic allocation on the libary's private
					// heap should probably be used instead of
					// static allocation.
} SERVICE, *LPSERVICE;

// This structure contains values that are used during the
// parsing of messages
typedef struct msgxtra {
    WORD    BufSize;			// size of message buffer
    WORD    BufPos;			// current position in msgbuf
    WORD    BodySize;			// allocated size of body
    WORD    BodyLen;			// number of bytes used (strlen) of body
} MSGXTRA, *LPMSGXTRA;

extern HINSTANCE	g_hinst;	// instance of library
extern HANDLE		ghLibHeap;	// global heap used for libary
					// Each message has a heap which
					// is used for data relating to
					// that message.  This is used
					// for variables related to the
					// library itself.	

// support function headers

// This routine parses the incoming headers from a file and places
// them into MsgPtr->pwcHeaders.  It returns a FALSE if it fails.
BOOL  ParseHeaders(
    LPSERVICE hService,	    // Service handle.  This is only passed
			    // to allow for returns of error conditions.
    LPCWSTR szMsgTxt,	    // This is a buffer containing the entire
			    // text of the message (headers & body).
    MailMsg * MsgPtr,	    // This is a pointer to the structure into
			    // which the headers will be placed
    LPMSGXTRA XtraPtr	    // This structure contains extra information
			    // used for processing
);

// This routine is called by ParseHeaders() and sets the message's time
// to the current system time
void ParseDate(
    MailMsg *MsgPtr	    // Message pointer to get file time
);

// This routine parses the body of an incoming message.  It counts
// the number of lines and bytes and truncates the message after the
// specified number of lines or max message size.  This routine, in
// order to be efficient in the use of memory, allocates the buffer for
// the message body in small blocks and lets this grow as necessary.
BOOL ParseBody(
    LPSERVICE hService,	    // Service handle.  This is only passed
			    // to allow for returns of error conditions.
    LPCWSTR szMsgTxt,	    // This is a buffer containing the entire
			    // text of the message (headers & body).
    MailMsg * MsgPtr,	    // This is a pointer to the structure into
			    // which the body will be placed.
    LPMSGXTRA XtraPtr	    // This structure contains extra information
			    // used for processing
);

// This routine reads the next line of text from szMsgTxt (a line
// is always terminated with \r\n).  It uses pointers in XtraPtr to
// keep its offset from the start of the buffer.
// This routine returns -1 if there are no lines left or the number
// of characters placed into Line
int  GetLine(
    LPCWSTR szMsgTxt,	    // This is a buffer containing the entire
			    // text of the message (headers & body)
    LPMSGXTRA XtraPtr,	    // This structure contains extra information,
			    // such as the current offset from the start
			    // of the message and the total size of the
			    // message.
    LPWSTR Line,	    // This is a character buffer which will
			    // receive the next line of text
    WORD wBufLen	    // This tells the max size of the buffer. At
			    // most, wBufLen-1 chars will be written into
			    // Line
);

#endif
