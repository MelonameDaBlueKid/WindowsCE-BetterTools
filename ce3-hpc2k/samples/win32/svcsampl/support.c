/*---------------------------------------------------------------------------*\
 *
 * (c) Copyright Microsoft Corp. 1997 All Rights Reserved
 *
 *  module: support.c
 *
 *  purpose: This file contains the routines that support the API routines.
 *
\*---------------------------------------------------------------------------*/
#include <windows.h>
#include <tchar.h>

#include <msgstore.h>

#include "transprt.h"
#include "svcsampl.h"

/*****************************************************************************/
/* Get date information out of header					     */
/*****************************************************************************/
// This routine is called by ParseHeaders() and is used to set the msg time
void ParseDate(
    MailMsg *MsgPtr)	    // Message pointer to get file time
{
    SYSTEMTIME MsgTime;

	// set file time to 0 in case of error
	memset(&(MsgPtr->ftDate), 0x00, sizeof(FILETIME));

	// normally, we'd pull the message time out of the
	// message, but for now, we'll just use the current time.
	GetSystemTime( &MsgTime);

	SystemTimeToFileTime( &MsgTime, &(MsgPtr->ftDate));
}
/*****************************************************************************/
/* Parse header lines in incoming mail msg				     */
/*****************************************************************************/
// This routine parses the incoming headers from a file and places
// them into MsgPtr->pwcHeaders.  It returns FALSE if it fails.
BOOL  ParseHeaders(
    LPSERVICE hService,	    // Service handle.  This is only passed
			    // to allow for returns of error conditions.
    LPCWSTR szMsgTxt,	    // This is a buffer containing the entire
			    // text of the message (headers & body).
    MailMsg * MsgPtr,	    // This is a pointer to the structure into
			    // which the headers will be placed
    LPMSGXTRA XtraPtr)	    // This structure contains extra information
			    // used for processing
{
    // returns:
    //		    1 if successful
    //		    0 if error
    WCHAR InBuf[1030];
    WCHAR szHeader[1024];
	
	// setup header field in message
	MsgPtr->pwcHeaders=(WCHAR *)HeapAlloc(MsgPtr->hHeap, 0, sizeof(WCHAR));
	if (!(MsgPtr->pwcHeaders)) {
	    HeapFree(MsgPtr->hHeap, 0, szHeader);
	    ERR(NO_MSG_BUF);
	}
	
	*(MsgPtr->pwcHeaders) = _T('\0');

	// here is where we'd parse the headers.
	// In this example, we'll assume the first line is the to,
	// the second line is the from, the third line is cc
	// and fourth is subject
	GetLine(szMsgTxt, XtraPtr, InBuf, sizeof(InBuf)/sizeof(WCHAR));
	MailSetField(MsgPtr, _T("To"), InBuf);
	GetLine(szMsgTxt, XtraPtr, InBuf, sizeof(InBuf)/sizeof(WCHAR));
	MailSetField(MsgPtr, _T("From"), InBuf);
	GetLine(szMsgTxt, XtraPtr, InBuf, sizeof(InBuf)/sizeof(WCHAR));
	MailSetField(MsgPtr, _T("Cc"), InBuf);
	GetLine(szMsgTxt, XtraPtr, InBuf, sizeof(InBuf)/sizeof(WCHAR));
	MailSetField(MsgPtr, _T("Subject"), InBuf);

	// add time to message structure
	ParseDate(MsgPtr);
	return TRUE;
}

/*****************************************************************************/
/* Parse body of incoming mail msg					     */
/*****************************************************************************/
// This routine parses the body of an incoming message.  It should count
// the number of lines and bytes and truncate the message after the
// specified number of lines or max message size.  This routine should
// be efficient in the use of memory and should probably allocate the buffer for
// the message body in small blocks and lets this grow as necessary.
BOOL ParseBody(
    LPSERVICE hService,	    // Service handle.  This is only passed
			    // to allow for returns of error conditions.
    LPCWSTR szMsgTxt,	    // This is a buffer containing the entire
			    // text of the message (headers & body).
    MailMsg * MsgPtr,	    // This is a pointer to the structure into
			    // which the body will be placed.
    LPMSGXTRA XtraPtr)	    // This structure contains extra information
			    // used for processing
{
// these are the block sizes and max block sizes used by the store.
// Normally, we'd need to make sure there are never more than MAX_BODY_SIZE
// characters in the body of the message.   We'd also want to add a message
// to the end of the message (contained within the MAX_BODY_SIZE characters)
// saying that the message was truncated.
#define BLOCKSIZE	2046
#define MAX_BODY_SIZE	((16*BLOCKSIZE)-1)

    WCHAR InBuf[1030];
    int NumRead;
    WORD iGotSoFar=0;

	// allocate space for body
	XtraPtr->BodySize = XtraPtr->BufSize - XtraPtr->BufPos + 1;
	MsgPtr->szBody=(LPWSTR)HeapAlloc(MsgPtr->hHeap, 0,
			    sizeof(WCHAR)*XtraPtr->BodySize);
	// should probably return an error if this fails...
	if (!MsgPtr->szBody)	ERR(NO_MSG_BUF);
	
	*(MsgPtr->szBody) = _T('\0');

	XtraPtr->BodyLen = 0;

	while (1) {
	
	    // now read next line
	    NumRead=GetLine(szMsgTxt, XtraPtr, InBuf, sizeof(InBuf)/sizeof(WCHAR));
	    // are we done?
	    if (NumRead<0)  break;

	    // Report on (approximate) progress (approximately every 7 lines)
	    if (hService->CallBack && !(++iGotSoFar & 0x7))
		(*(hService->CallBack))(iGotSoFar >> 3, TRUE);
		
	    // normally, we'd check the number of lines, and once we
	    // pass the desired number, we'd through the rest of the data
	    // away.   Here, we'll assume the message is always small!
	
	    lstrcat(MsgPtr->szBody, InBuf);
		
	    lstrcat(MsgPtr->szBody, _T("\r\n"));
	    XtraPtr->BodyLen+=NumRead+2;
	}

	return TRUE;
}

/*****************************************************************************/
/* Get a single line back						     */
/*****************************************************************************/

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
    WORD wBufLen)	    // This tells the max size of the buffer. At
			    // most, wBufLen-1 chars will be written into
			    // Line
{
    WCHAR	* Ptr;
    int		LineLen;
    int		iCrLen;

	// are there any characters left?
	if (XtraPtr->BufPos > XtraPtr->BufSize)	    return -1;

	// now search for linefeed
	if (Ptr=wcsstr(szMsgTxt+XtraPtr->BufPos, _T("\r\n"))) {

	    // we found end of line, so copy data
	    *Ptr = _T('\0');
	    LineLen=Ptr-szMsgTxt-XtraPtr->BufPos;
	}
	else {
	    LineLen = lstrlen(szMsgTxt+XtraPtr->BufPos);
	}

	// since we don't know if we have a cr/lf, set length to 0
	iCrLen = 0;

	//now copy string into buffer
	if (LineLen > wBufLen-1)    wBufLen--;
	else {
	    wBufLen=LineLen;
	
	    // we need to account for cr/lf, so set len to 2
	    iCrLen=2;
	}
	wcsncpy(Line, szMsgTxt+XtraPtr->BufPos, wBufLen);
	Line[wBufLen] = _T('\0');

	// now, update msgpos
	XtraPtr->BufPos += wBufLen+iCrLen;

	return wBufLen;
}
