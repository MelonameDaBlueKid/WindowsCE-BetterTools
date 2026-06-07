//***************************************************************************
//
//	Copyright (c) 1997-1999  Microsoft Corporation.  All Rights Reserved.
//
//	File:
//			richink.h
//
//	Description:
//
//			Include file for WinCE RichInk Edit Control.
//
//***************************************************************************

#ifndef _RICHINK_INCLUDED_
#define _RICHINK_INCLUDED_

#include <windows.h>
#include <commctrl.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


// Constants

#define WC_RICHINKA   "RichInk"
#define WC_RICHINKW  L"RichInk"
#ifdef UNICODE
#define WC_RICHINK    WC_RICHINKW
#else
#define WC_RICHINK    WC_RICHINKA
#endif

// Application calls this function to load and initialize the control properly.
// The control can be inserted as a dialog custom control with class setting "RichInk"
//  (see constant WC_RICHINK above).
#ifdef _WIN32_WCE_EMULATION
void WINAPI InitRichInkDLL(void);
#else
void InitRichInkDLL(void);
#endif


// Defines and typedefs needed for the Rich Ink stream messages.

//---------------------------------------------------------
// EditStreamCallback
//
//	The EditStreamCallback function is an application-defined
//	callback function used with the EM_STREAMIN and EM_STREAMOUT
//	messages. It is used to transfer a stream of data into or
//	out of a rich edit control. The EDITSTREAMCALLBACK type defines
//	a pointer to this callback function. EditStreamCallback is a
//	placeholder for the application-defined function name. 
//
// SEE Microsoft Developer Studio Help or MSDN for more details.
//---------------------------------------------------------
typedef DWORD (CALLBACK *EDITSTREAMCALLBACK)
(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

DWORD CALLBACK EditStreamCallback(
  DWORD dwCookie, // application-defined value
  LPBYTE pbBuff,  // pointer to a buffer
  LONG cb,        // number of bytes to read or write
  LONG *pcb       // pointer to number of bytes transferred
);

typedef struct _editstream
{
	DWORD dwCookie;		/* user value passed to callback as first parameter */
 	DWORD dwError;		/* last error */
	EDITSTREAMCALLBACK pfnCallback;
} EDITSTREAM;

typedef struct tagCOOKIE
{
	HANDLE hFile;
	LPBYTE pbStart;
	LPBYTE pbCur;
	LONG   bCount;
	DWORD  dwError;
} COOKIE, * PCOOKIE;


// Stream formats:
#define SF_TEXT			0x0001
#define SF_RTF			0x0002

#define SF_UNICODE		0x0010							// Unicode data of some kind
#define SF_UTEXT		SF_TEXT | SF_UNICODE			// Unicode text file

#define SFF_PWI			0x0800		
#define SF_PWI			( SF_RTF | SFF_PWI | 0x010000 )	// Pocket Word Ink (PWI) format


// Supported EM_ and WM_ Messages:

//---------------------------------------------------------
//
//	EM_STREAMIN
//	
//	The EM_STREAMIN message replaces the contents of a rich ink
//	control with a stream of data provided by an application-defined
//	EditStreamCallback callback function.
//
//
//	wParam = (WPARAM) (UINT) uFormat; 
//	lParam = (LPARAM) (EDITSTREAM FAR *) lpStream; 
// 
//	Parameters
//
//		uFormat 
//
//		A set of bit flags that indicate the data format and replacement options.
//		This value must specify one of the following data formats.
//
//		SF_TEXT		Ascii Text 
//		SF_RTF		Rich Text Format (RTF) 
//		SF_UTEXT	Unicode text
//		SF_PWI		Pocket Word Ink (PWI)
//
//
//		lStream 
//		Pointer to an EDITSTREAM structure. On input, the pfnCallback member of
//		this structure must point to an application-defined EditStreamCallback
//		function. On output, the dwError member can contain a nonzero error code
//		if an error occurred. 
//
//		Return Values
//
//		Returns zero if no errors.
//
//		Remarks
//
//		When you send an EM_STREAMIN message, the rich ink control makes
//		repeated calls to the EditStreamCallback function specified by the
//		pfnCallback member of the EDITSTREAM structure. 
//		Each time the callback function is called, it fills a buffer with
//		data to read into the control. This continues until the callback
//		function indicates that the stream-in operation has been completed
//		or an error occurs.
//
//---------------------------------------------------------
#define EM_STREAMIN				(WM_USER + 73)
 

//---------------------------------------------------------
//
//	EM_STREAMOUT
//	
//	The EM_STREAMOUT message causes a rich ink control to pass
//	its contents to an application-defined EditStreamCallback callback
//	function. The callback function can then write the stream of data
//	to a file or any other location that it chooses. 
//
//	wParam = (WPARAM) (UINT) uFormat; 
//	lParam = (LPARAM) (EDITSTREAM FAR *) lpStream; 
// 
//	Parameters
//
//		uFormat 
//
//		A set of bit flags that indicate the data format and replacement options.
//		This value must specify one of the following data formats.
//
//		SF_TEXT		Ascii Text 
//		SF_RTF		Rich Text Format (RTF) 
//		SF_UTEXT	Unicode text
//		SF_PWI		Pocket Word Ink (PWI)
//
//
//		lStream 
//
//		Pointer to an EDITSTREAM structure. On input, the pfnCallback member
//		of this structure must point to an application-defined EditStreamCallback
//		function. On output, the dwError member can contain a nonzero error code
//		if an error occurred. 
//
//		Return Values
//
//		Returns zero if no errors.
//
//		Remarks
//
//		When you send an EM_STREAMOUT message, the rich ink control makes
//		repeated calls to the EditStreamCallback function specified by the
//		pfnCallback member of the EDITSTREAM structure. Each time it calls
//		the callback function, the control passes a buffer containing a
//		portion of the contents of the control. This process continues until
//		the control has passed all its contents to the callback function,
//		or until an error occurs.
//
//---------------------------------------------------------
#define EM_STREAMOUT			(WM_USER + 74)


//---------------------------------------------------------
// IMPORTANT COMPATIBILITY NOTE:
//
//	Previous versions of the richink.dll required the EM_STREAMIN
//	and EM_STREAMOUT messages to the uFormat parameter rather
//  than passing the uFormat directly.
//
//	DWORD	wpSF = SF_PWD;
//
//	SendMessage (hwndInk, EM_STREAMIN, (WPARAM)&wpSF, (LPARAM)&es);
//---------------------------------------------------------


//---------------------------------------------------------
//
//	EM_CLEARALL
//	
//	The EM_CLEARALL message causes a rich ink control to clear
//	all of the current documents data.
//
//	wParam = (WPARAM) (BOOL) fDirty; 
//	lParam = (LPARAM) 0; 
// 
//	Parameters
//
//		fDirty -- true to dirty window for repaint after clear. 
//
//---------------------------------------------------------
#define EM_CLEARALL				(WM_USER + 331)


//---------------------------------------------------------
//
// Other useful Rich Edit control and Windows messages 
//	that are supported by the Rich Ink control:
//
//		EM_GETSEL
//		EM_SETSEL
//		EM_REPLACESEL
//		EM_GETMODIFY
//		EM_SETMODIFY
//
//		WM_GETTEXTLENGTH
//		WM_GETTEXT
//		WM_SETTEXT 
//
//      WM_CUT
//      WM_COPY
//      WM_PASTE
//      WM_CLEAR
//      EM_CANPASTE
//
// See Microsoft Developer Studio Help or MSDN for more details.
//---------------------------------------------------------

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _RICHINK_INCLUDED_
