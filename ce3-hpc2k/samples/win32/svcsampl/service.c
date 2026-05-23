/*---------------------------------------------------------------------------*\
 *
 * (c) Copyright Microsoft Corp. 1997 All Rights Reserved
 *
 *  module: service.c
 *
 *  purpose: This file contains the API routines and DllMain for the
 *           sample service library
 *
\*---------------------------------------------------------------------------*/
#include <windows.h>

#include <msgstore.h>

#include "transprt.h"
#include "svcsampl.h"

HINSTANCE       g_hinst         = NULL;     // instance of library
HANDLE          ghLibHeap       = NULL;     // global heap used for libary
					    // Each message has a heap which
					    // is used for data relating to
					    // that message.  This is used
					    // for variables related to the
					    // library itself.

// this is the root directory where all mail messages will be stored, one
// message per file
#define MAIL_DIR        _T("\\maildir")

// this is the return address which will be used for all messages.  Normally
// this would be a field entered by the user in the property sheet and stored
// in the registry.
#define RETURN_ADDR     _T("user@inbox.com")

// empty string to prevent access to null pointer
#define NULL_STR        _T("")

/*****************************************************************************/
/* Initialize transport                                                      */
/*****************************************************************************/

// initialize transport.
//      - creates handle
//      - pulls logon information from registry
//      - starts ras if necessary
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
BOOL TransportInit(
    HANDLE *NewService,         // Pointer to hold new service
    LPWSTR  szCommonKey,        // Top level registry key
    LPWSTR  szTransportKey)     // This transport's reg key
{
    LPSERVICE hService;

	// make sure we received a valid pointer
	if (!NewService)        return FALSE;

	// make sure handle that was passed in is NULL in case
	// of an error
	*NewService=NULL;
	
	// try to allocate the service handle and return an error condition
	// if it fails.  ERR() is not used since there is no handle in which
	// to store the error line and error code.
	if ((hService = HeapAlloc(ghLibHeap, 0, sizeof(SERVICE)))==NULL) {
	    return FALSE;
	}

	// set the new service handle and initialize it
	*NewService = hService;
	hService->iErr = TRANS_ERR_NONE;

	// set directory & return address
	lstrcpy(hService->szMailDir, MAIL_DIR);
	lstrcpy(hService->szRetAddr, RETURN_ADDR);

	return TRUE;
}
/*****************************************************************************/
/* Connect to transport                                                      */
/*****************************************************************************/

// Connect to a service for transmission/receiving
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
BOOL TransportConnect(
    HANDLE  InPtr,      // Service
    DWORD   dwFlags,// Transmit/Receive Flags
				    // Values specified above
    HWND    hWndNotify,		    // This is the window that will
				    // receive any notification messages
				    // we choose to send
    BOOL    (*CallBack)(int,BOOL))  // Callback routine.  If this
				    // routine is not NULL, it
				    // will be called periodically
				    // and given an integer between
				    // 0-99 indicating the progress
				    // towards completion.
				    // A return value of FALSE
				    // from this routine will cause
				    // the current action to be
				    // cancelled.  (This is currently
				    // not implemented).
				    // The second param should be TRUE if
				    // the MAX value could be >99 (unknown max)
{
    LPSERVICE hService=(LPSERVICE)InPtr;
    DWORD dwAttrib;

	// verify that the handle exists
	if (!hService)      return FALSE;
	hService->iErr = TRANS_ERR_NONE;

	// store passed in values
	hService->CallBack   = CallBack;
	
	hService->fRecActive    = (dwFlags & TRANSPORT_RECV) ? TRUE: FALSE;
	hService->fTransActive  = (dwFlags & TRANSPORT_SEND) ? TRUE: FALSE;

	hService->hWndNotify	= hWndNotify;

	// make sure directory exists...
	CreateDirectory(hService->szMailDir, NULL);
	dwAttrib = GetFileAttributes( hService->szMailDir);
	if (!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) ERR(NO_SVC_DIR);
	
	// get count of messages
	return TransportCount(InPtr, NULL);
}
/*****************************************************************************/
/* Return last error                                                         */
/*****************************************************************************/

// Get last mail error as integer
int TransportError(
    HANDLE InPtr)               // Service
{
    return (InPtr) ? ((LPSERVICE)InPtr)->iErr :
		TRANS_ERR_HANDLE_NOT_ALLOC;
}

/*****************************************************************************/
/* Return text string from last error                                        */
/*****************************************************************************/

// initialize transport.
//      - creates handle
//      - pulls logon information from registry
//      - starts ras if necessary
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
int TransportErrorMsg(                  // Get last mail error (printable)
    HANDLE  InPtr,                      // Service
    LPWSTR  szBuf,                      // Buffer to fill
    int     iBufLen,                    // Length of buffer in chars
    int*    piSrcLine)                  // Line where error occured (or NULL)
{
    LPSERVICE hService=(LPSERVICE)InPtr;
    int Err;
    int ErrLine;

	// if the handle is non NULL, the error line and code should
	// be stored there
	if (hService) {
	    Err = hService->iErr;
	    ErrLine = hService->iErrLine;
	}
	else {
	    // otherwise, there was an error in the allocation of the
	    // handle
	    Err = TRANS_ERR_HANDLE_NOT_ALLOC;
	    ErrLine = 0;
	}

	// load the error message from the resource string
	if (!LoadString(g_hinst,Err,szBuf,iBufLen))
	    wsprintf(szBuf,_T("Unknown error"));

	// set the error line in the source
	if (piSrcLine)  *piSrcLine   = ErrLine;

	return Err;
}

/*****************************************************************************/
/* disconnect from services                                                  */
/*****************************************************************************/

// Disconnect from current connection
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
BOOL TransportDisconnect(
    HANDLE InPtr)           // service handle
{
	// At this point, any message that the user marked for deletion
	// (by calling TransportDel) should actually be removed on the
	// service
	return TRUE;
}
/*****************************************************************************/
/* free up all memory allocated for transport                                */
/*****************************************************************************/

BOOL TransportRelease(
    HANDLE InPtr)           // service handle
{
    LPSERVICE hService = (LPSERVICE)InPtr;
    BOOL RetCode=TRUE;

	
	// if service is out there, free it.
	if (hService) {
	    hService->iErr = TRANS_ERR_NONE;
	    RetCode=TransportDisconnect(InPtr);
	    HeapFree(ghLibHeap,0,hService);
	}
	return RetCode;
}
/*****************************************************************************/
/* send message out thru server                                              */
/*****************************************************************************/

// send specified message
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
BOOL TransportSend(
    HANDLE InPtr,               // Service
    MailMsg *MsgPtr)            // Message to send
{
    LPSERVICE hService = (LPSERVICE)InPtr;
    WCHAR Line[256];
    LPWSTR Data;
    int SentSoFar =0;
	int TotalSize =0;
    LPWSTR LineStart, LineEnd;
    WCHAR szFileName[2*MAX_DIR_SIZE];
    HANDLE  hFile;
    DWORD   dwBytesWritten;


	// verify that the handle exists
	if (!hService)      return FALSE;
	hService->iErr = TRANS_ERR_NONE;

	// generate filename - right now, any mail that is sent (to any address)
	// ends up in our inbox
	wsprintf(szFileName,_T("%s\\%d.txt"), hService->szMailDir,
	    (hService->wHighNum)+1);

	// now, open file
	hFile = CreateFile( szFileName, GENERIC_WRITE, 0,
		    NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile==INVALID_HANDLE_VALUE)    ERR(CANT_SEND);

	// update counts and uid
	wsprintf((hService->Uids)[(hService->wNumMsgs)++],_T("%d.txt"),
		++(hService->wHighNum));

	// calculate sizes to for callback routine
	if (hService->CallBack) {
	    TotalSize = lstrlen(MsgPtr->szBody);
	    SentSoFar = 0;
	}

	// write to, from, cc, subject each as a separate line.
	// ignore all other headers
	Data=MailGetField(MsgPtr, _T("To"), FALSE);
	if (!Data)      Data= NULL_STR;
	wsprintf(Line, _T("%s\r\n"), Data);
	WriteFile(hFile, Line, sizeof(WCHAR)*lstrlen(Line),
		&dwBytesWritten, NULL);

	wsprintf(Line, _T("%s\r\n"), hService->szRetAddr);
	WriteFile(hFile, Line, sizeof(WCHAR)*lstrlen(Line),
		&dwBytesWritten, NULL);

	Data=MailGetField(MsgPtr, _T("Cc"), FALSE);
	if (!Data)      Data= NULL_STR;
	wsprintf(Line, _T("%s\r\n"), Data);
	WriteFile(hFile, Line, sizeof(WCHAR)*lstrlen(Line),
		&dwBytesWritten, NULL);

	Data=MailGetField(MsgPtr, _T("Subject"), FALSE);
	if (!Data)      Data= NULL_STR;
	wsprintf(Line, _T("%s\r\n"), Data);
	WriteFile(hFile, Line, sizeof(WCHAR)*lstrlen(Line),
		&dwBytesWritten, NULL);
	
	// now go thru message line by line
	// this is only necessary so we can call progress Callback routine
	LineStart = MsgPtr->szBody;
	while ((LineStart) && (*LineStart)) {
	    if (LineEnd = wcschr(LineStart, _T('\r'))) {

		// we found \r
		// terminate string and send
		// NOTE:  We're assuming the msgbody is writable.
		//        if it is not, we'd need to copy each line into
		//        a temp string...
		*LineEnd = _T('\0');
	    }

	    // now write line to file
	    WriteFile(hFile, LineStart, sizeof(WCHAR)*lstrlen(LineStart),
			&dwBytesWritten, NULL);
	    WriteFile(hFile, _T("\r\n"), 4, &dwBytesWritten, NULL);

	    // call callback
	    if (hService->CallBack && LineEnd) {
		SentSoFar += LineEnd-LineStart + 2;
		(*(hService->CallBack))(100*SentSoFar/TotalSize, FALSE);
	    }

	    if (LineEnd) {
		// put \r back into msg (so we don't change original)
		// is this really necessary??
		*LineEnd = _T('\r');
		LineEnd += 2;
	    }
	    // we'll set linestart to NULL or start of line
	    LineStart = LineEnd;
	}

	CloseHandle(hFile);

	return TRUE;
}
/*****************************************************************************/
/* Get the number of messages waiting in the mailbox                         */
/*****************************************************************************/

BOOL TransportCount(
    HANDLE InPtr,           // Service Pointer
    LPWORD lpNumMsgs)       // pointer to receive number of messages
{
    LPSERVICE           hService=(LPSERVICE)InPtr;
    WORD                wCount;
    WORD                wHighNum,x;
    HANDLE              hFind;
    WCHAR               szFName[MAX_DIR_SIZE+20];
    WIN32_FIND_DATA     sFData;


	// verify handle exists
	if (!hService)      return FALSE;
	hService->iErr = TRANS_ERR_NONE;

	// form directory name
	lstrcpy(szFName, hService->szMailDir);
	lstrcat(szFName, _T("\\*"));

	// set counter to 0
	wCount = wHighNum = 0;

	// look for first file...
	hFind=FindFirstFile(szFName, &sFData);
	if (hFind!=INVALID_HANDLE_VALUE) {
	    // we found one, so keep looking
	    while (1) {
		// if this file isn't a directory, we'll assume it
		// is a mail message
		if (!(sFData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
		    // while we're looking at files, keep track of the
		    // highest file number we see (as in 100.txt) so
		    // we know what number to use for storing the next
		    // file.   The numbers of the files will not match
		    // the number of messages, since the use can delete
		    // files
		    x=(WORD)_wtol(sFData.cFileName);
		    if (x>wHighNum)     wHighNum = x;

		    // now set uid and increment count
		    lstrcpy((hService->Uids)[wCount++], sFData.cFileName);
		}

		// get next file, and if there isn't one, exit
		if (!FindNextFile(hFind, &sFData))      break;
	    }

	    // now close handle
	    FindClose(hFind);
	}

	// save counts
	hService->wNumMsgs = wCount;
	hService->wHighNum = wHighNum;

	// if a pointer was passed in, set it
	if (lpNumMsgs)      *lpNumMsgs = wCount;

	return TRUE;
}
/*****************************************************************************/
/* Get a particular message from server                                      */
/*****************************************************************************/

BOOL TransportRecv(
    HANDLE InPtr,               // Service
    WORD wSessionId,// Msg Id to read.  Should
				    // be in range 1 to NumMsgs.
					// It is assumed that this id will never
					// change while we are connected to the
					// service. (during the session)
				    // If this value is 0, it is
				    // assumed that the Unique
				    // Message Id is specified
				    // in msg
    short sNumLines,// Number of lines to receive
				    // positive value of lines to read
				    // or see #defines in .h file
    MailMsg *MsgPtr,// Mail Message that will contain
				    // Message.  Memory is allocated
				    // in here that needs to be
				    // freed by TransportFreeMsg()
    HANDLE Reserved)            // this parameter is not currently used
				// and should be forced to NULL
{
    LPSERVICE hService = (LPSERVICE)InPtr;
    WCHAR szFileName[2*MAX_DIR_SIZE];
    HANDLE hFile;
    MSGXTRA Xtra;
    DWORD   dwNumRead;
    LPWSTR  szMsgTxt;

	if (!hService)      return FALSE;
	hService->iErr = TRANS_ERR_NONE;

	// if wSessionId is 0, then the UID is specified in the msg
	// structure.
	if (wSessionId == 0) {
	    for ( ; wSessionId < hService->wNumMsgs; wSessionId++) {
		if (!lstrcmpi((hService->Uids)[wSessionId], MsgPtr->szSvcId))   break;
	    }
	    // now increment, since table is 0 based, but message list
	    // starts at 1
	    wSessionId++;
	}

	if ((wSessionId < 1) || (wSessionId>hService->wNumMsgs)) ERR(INV_MSG_ID);

	// if we're just looking for id, we found it
	if (sNumLines==TRANSPORT_MSG_EXIST) {
	    // now set pointer to unique id

	    // NOTE: this cannot allocate any space since pmail will not
	    // do anything to free this space.
	    // this information needs to be kept in a table which will
	    // remain allocated for as long as the service is connected.
	    MsgPtr->szSvcId = (hService->Uids)[wSessionId-1];
	    MsgPtr->hHeap = NULL;
	    return TRUE;
	}
	
	// create filename string
	wsprintf(szFileName,_T("%s\\%s"), hService->szMailDir,
	    (hService->Uids)[wSessionId-1]);

	// now try to open file
	hFile = CreateFile( szFileName, GENERIC_READ, 0,
		    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile==INVALID_HANDLE_VALUE)    ERR(CANT_OPEN);
	
	MsgPtr->dwMsgLen = GetFileSize(hFile, NULL);

	// create msg's heap
	if ((MsgPtr->hHeap = HeapCreate(0,2048,0))==NULL) {
	    CloseHandle(hFile);
	    ERR(NO_MSG_BUF);
	}

	// allocate buffer for entire message.
	// in practice, this is probably a bad idea since messages
	// can be rather large.  if this were a real service, we'd
	// probably want to read the message in line by line
	szMsgTxt=(LPWSTR)HeapAlloc(MsgPtr->hHeap, 0, sizeof(WCHAR)*(MsgPtr->dwMsgLen+1));
	if (!szMsgTxt) {
	    CloseHandle(hFile);
	    ERR(NO_MSG_BUF);
	}

	// now read entire message
	if (!ReadFile(hFile, szMsgTxt, MsgPtr->dwMsgLen,
		&dwNumRead, NULL)) {
	    HeapFree(MsgPtr->hHeap, 0, szMsgTxt);
	    CloseHandle(hFile);
	    ERR(NO_MSG_BUF);
	}
	szMsgTxt[MsgPtr->dwMsgLen] = _T('\0');
	CloseHandle(hFile);

	// if we are requesting a specific number of lines >0, ask for the
	// the number of lines+1 so that we can determine if we're truncating
	// the message
	if (sNumLines>0)    sNumLines+=1;

	// initialize extra info
	memset( &Xtra, 0x00, sizeof(MSGXTRA));
	Xtra.BufSize = (WORD)MsgPtr->dwMsgLen;

	// now read headers
	if (!ParseHeaders(hService, szMsgTxt, MsgPtr, &Xtra)) {
	    HeapFree(MsgPtr->hHeap, 0, szMsgTxt);
	    return FALSE;
	}

	// were we only looking at headers?
	if (sNumLines == TRANSPORT_HEADERS) {
	    // set body to NULL
	    MsgPtr->szBody = NULL;
	}
	else {
	    // now read message
	    if (!ParseBody(hService, szMsgTxt, MsgPtr, &Xtra)){
		HeapFree(MsgPtr->hHeap, 0, szMsgTxt);
		return FALSE;
	    }
	}

	// now set pointer to unique id
	MsgPtr->szSvcId = (LPWSTR)(hService->Uids[wSessionId-1]);
	HeapFree(MsgPtr->hHeap, 0, szMsgTxt);
	return TRUE;
}
/*****************************************************************************/
/* Release memory allocated for incoming mail msg                            */
/*****************************************************************************/

// Free buffer space allocated by TransportRecv()
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
BOOL TransportFreeMsg(MailMsg * MsgPtr)
{
	// Free all memory associated with this mail message
	if (MsgPtr && MsgPtr->hHeap) {
	    HeapDestroy(MsgPtr->hHeap);

	    // now that memory is free, make sure we reset all pointers to NULL
	    MsgPtr->hHeap = MsgPtr->pwcHeaders = MsgPtr->szBody = NULL;
	    return TRUE;
	}

	return FALSE;
}
/*****************************************************************************/
/* Delete a particular message                                               */
/*****************************************************************************/

// Delete the message specified by MsgPtr
// Returns: TRUE if routine successful
//          FALSE if unsuccessful (use TransportError() to get error)
BOOL TransportDel(
    HANDLE InPtr,           // service handle
    MailMsg *MsgPtr)    // this structure has its unique id field set
						// to specify the message we wish to delete
{
    LPSERVICE hService = (LPSERVICE)InPtr;
    WCHAR szFileName[2*MAX_DIR_SIZE];
    int wSessionId;

	// make sure message is valid
	if (!hService)      return FALSE;
	hService->iErr = TRANS_ERR_NONE;

	// verify that this message exists
	for (wSessionId=0; wSessionId<hService->wNumMsgs; wSessionId++) {
	    if (!lstrcmpi((hService->Uids)[wSessionId], MsgPtr->szSvcId))       break;
	}

	if ((wSessionId < 0) || (wSessionId>=hService->wNumMsgs))   ERR(INV_MSG_ID);

	// now, delete file
	// create filename string
	wsprintf(szFileName,_T("%s\\%s"), hService->szMailDir,
	    (hService->Uids)[wSessionId]);
	
	// This is actually a bug... we should be marking this message for
	// deletion and only removing it on a transportdisconnect()
	DeleteFile(szFileName);

	// at this point, we can't compress the array of uids
	// because we can't change the session ids (1-NumMsgs)
	// We also don't want to change the count yet.
	
	return TRUE;
}
/*****************************************************************************/
/* Update transport properties from the user                                 */
/*****************************************************************************/

BOOL TransportProps(
    HWND    hwndParent,         // Parent window for dialog/wizard
    LPWSTR  szCommonKey,        // Top level registry key
    LPWSTR  szTransportKey)     // This transport's reg key
{
    return TRUE;
}

/*****************************************************************************/
/* View a mail message (most transports just return FALSE for this call)     */
/*****************************************************************************/

BOOL TransportView(
    HWND    hwndParent,         // Parent window
    MailMsg *MsgPtr)            // Message to view.
{
    MessageBox(hwndParent,_T("Got debug request to view message"),
	_T("SVCSAMPL.DLL TransportView()"),MB_OK);
    return TRUE;
}
/*****************************************************************************/
/* The entry point into this DLL.                                            */
/*****************************************************************************/

BOOL CALLBACK DllMain(
    HINSTANCE   hinst,
    DWORD       dwReason,
    LPVOID      lpv)
{

    switch (dwReason) {
	case DLL_PROCESS_ATTACH:
	    if (!g_hinst)   g_hinst = hinst;
	    if ((ghLibHeap = HeapCreate(0,2048,0))==NULL) {
		return FALSE;
	    }
	    break;
	case DLL_PROCESS_DETACH:
	    if (ghLibHeap)      HeapDestroy( ghLibHeap);
	    break;
    }
    return TRUE;
}

