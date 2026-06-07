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
/***********************************************************************

MODULE: 
  CeDialer.h

ABSTRACT: 
  This is a header file of the CeDialer Windows CE sample application.

***********************************************************************/

#ifndef _CEDIALER_H_
#define _CEDIALER_H_

typedef struct tagLINEINFO
{
  HLINE hLine;              // Line handle returned by lineOpen
  BOOL  bVoiceLine;         // Indicates if the line is a voice line
  DWORD dwAPIVersion;       // API version that the line supports
  DWORD dwNumOfAddress;     // Number of available addresses on the line
  DWORD dwPermanentLineID;  // Permanent line identifier
  TCHAR szLineName[256];    // Name of the line
} LINEINFO, *LPLINEINFO;

int WINAPI WinMain (HINSTANCE, HINSTANCE, LPTSTR, int);

BOOL CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialingProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ConnectUsingProc (HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK tapiCallback (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);

DWORD InitializeTAPI ();
DWORD GetLineInfo (DWORD, LPLINEINFO);
VOID MakePhoneCall (LPCTSTR);
VOID CurrentLineClose ();
VOID HangupCall ();

BOOL MakeCanonicalNum (LPTSTR);
BOOL InitLineCB (HWND, DWORD, DWORD);
BOOL InitAddrCB (HWND, HWND, DWORD, DWORD);
  
#endif 
