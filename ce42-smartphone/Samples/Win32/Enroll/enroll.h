//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
#ifndef ENROLL_H
#define   ENROLL_H

// How we get output.
//MessageBox

#define OUTPUT_MAX_LEN 10000
#define BUILD_STRING(s,a)  _sntprintf(tHoldPrintString ,OUTPUT_MAX_LEN-1, _T(s), a);
#if 1
	#define OUTPUT(s) if(lpMessageBox) lpMessageBox(0,_T(s),L"Enrollment Tool",MB_OK)
	#define OUTPUT_1_ARG(s,a)if(lpMessageBox) {BUILD_STRING(s,a); lpMessageBox(0,tHoldPrintString,L"Enrollment Tool",MB_OK);}
#endif  

#if 0
	#define OUTPUT(s) _tprintf (_T(s));
	#define OUTPUT_1_ARG(s,a) _tprintf( _T(s),a); 
#endif  

#if 0
	#define OUTPUT(s) DEBUGMSG(0xFFFFFFFFFF, (_T(s))) 
	#define OUTPUT_1_ARG(s,a) DEBUGMSG(0xFFFFFFFFFF,( _T(s),a ) ) 
#endif 

// For debugging, we'll need a blank T_CHAR
extern TCHAR tHoldForOuput[OUTPUT_MAX_LEN];
extern TCHAR tHoldPrintString[OUTPUT_MAX_LEN];
#define SAFE_COPY_TO_OUT(s) mbstowcs( tHoldForOuput, s, OUTPUT_MAX_LEN -1  ); tHoldForOuput[OUTPUT_MAX_LEN-1] = 0; 

#define NUM_AUTH_FAIL 5  /*The number of times we'll allow the user to fail authentication before bailing.*/

// For regular output we'll use MessageBox.
typedef int (STDAPICALLTYPE *PMessageBox)(HWND,LPCTSTR , LPCTSTR , UINT) ;
extern PMessageBox lpMessageBox;

#endif // ENROLL_H
