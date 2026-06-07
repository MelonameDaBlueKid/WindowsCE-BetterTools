//***************************************************************************
//
//	Copyright (c) 1997-1999  Microsoft Corporation.  All Rights Reserved.
//
//	File:
//			inkx.h
//
//	Description:
//
//			Include file for WinCE Ink Control.
//
//***************************************************************************

#ifndef _INKX_INCLUDED_
#define _INKX_INCLUDED_

#include <windows.h>
#include <commctrl.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


// Constants
#define WC_INKXA   "InkX"
#define WC_INKXW  L"InkX"
#ifdef UNICODE
#define WC_INKX    WC_INKXW
#else
#define WC_INKX    WC_INKXA
#endif

// Application calls this function to load and initialize the control properly.
// The control can be inserted as a dialog custom control with class setting "InkX"
//  (see constant WC_INKX above).
#ifdef _WIN32_WCE_EMULATION
void WINAPI InitInkX(void);
#else
void InitInkX(void);
#endif

//---------------------------------------------------------
// IM_SHOWCMDBAR
//
// Used to hide and show the command bar of the control.
// 
// wParam 	= (BOOL)fShow;	// Show the command bar if TRUE.
//							// Hide the command bar if FALSE.
// lParam 	= 0;			// not used, must be zero
// 
// Return Value:
//  This message does not return a value.
//---------------------------------------------------------
#define IM_SHOWCMDBAR	(WM_USER + 512)


//---------------------------------------------------------
// IM_GETDATALEN
//
// Used to return the length of the data.
//
// wParam 	= 0;	// not used, must be zero
// lParam 	= 0;	// not used, must be zero 
//
// Return Values:
//  This message returns the length in bytes of the ink data
//  in the main compose window. Application uses this value
//  to allocate buffer to store the ink data.
//---------------------------------------------------------
#define IM_GETDATALEN	(WM_USER + 514)


//---------------------------------------------------------
// IM_GETDATA
//
// Used to retrieve the data
//
// wParam 	= (INT)cbBuffer;	// Length of the buffer in bytes.
// lParam 	= (BYTE *)lpBuffer;	// Pointer to the buffer 
//
// Return Value:
//  This message returns the size of ink data stored in bytes.
//---------------------------------------------------------
#define IM_GETDATA		(WM_USER + 515)


//---------------------------------------------------------
// IM_SETDATA
//
// Used to set the data.  Stores the Ink data from a previous
// IM_GETDATA call which will be inserted into the current
// compose window.
//
// wParam 	= (INT)cbInkData;		// Length of the ink data buffer
// lParam 	= (BYTE *)lpInkData;	// Pointer to ink data buffer 
//
// Return Value:
//  This message does not return a value. 
//---------------------------------------------------------
#define IM_SETDATA		(WM_USER + 516)


//---------------------------------------------------------
// IM_CLEARALL
//
// Used to erase all contents from the current compose window.
//
// wParam 	= 0;	// not used, must be zero
// lParam 	= 0;	// not used, must be zero 
//
// Return Value:
//  This message does not return a value. 
//---------------------------------------------------------
#define IM_CLEARALL		(WM_USER + 519)

//---------------------------------------------------------
// IM_REINIT
//
// Now the same as IM_CLEARALL -- constant is provided here
//  for compatibility with previous header files.
//---------------------------------------------------------
#define IM_REINIT		(WM_USER + 521)


//---------------------------------------------------------
//
// NOTE:  The standard edit control messages EM_GETMODIFY
//		  and EM_SETMODIFY are supported.
//
//---------------------------------------------------------

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _INKX_INCLUDED_
