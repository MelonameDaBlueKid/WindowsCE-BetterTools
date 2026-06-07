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


#ifndef _CEINVOKE_H_
#define _CEINVOKE_H_

#define cchSzMax     256
#define cchSzLarge   1024

#ifdef DEBUG
    void DOUT( UINT uZone, TCHAR *szFmt, ...);

	#define DOUT0(s)                    DOUT( TEXT( s ) )
	#define DOUT1(s, p1)                DOUT( TEXT( s ), p1 )
	#define DOUT2(s, p1, p2)            DOUT( TEXT( s ), p1, p2 )
	#define DOUT3(s, p1, p2, p3)        DOUT( TEXT( s ), p1, p2, p3 )
	#define DOUT4(s, p1, p2, p3, p4)    DOUT( TEXT( s ), p1, p2, p3, p4 )
	#define DOUT5(s, p1, p2, p3, p4, p5) DOUT(TEXT( s ), p1, p2, p3, p4, p5 )
#else
    #define DOUT                        1? (void) 0 : (void)
	#define DOUT0(s)                    (0)
	#define DOUT1(s, p1)                (0)
	#define DOUT2(s, p1, p2)            (0)
	#define DOUT3(s, p1, p2, p3)        (0)
	#define DOUT4(s, p1, p2, p3, p4)    (0)
	#define DOUT5(s, p1, p2, p3, p4, p5) (0)
#endif

const WCHAR c_szDllName[] = L"CeInvoke";
const WCHAR c_szFnBlock[] = L"FnBlockMode";
const WCHAR c_szFnStreamMode1[] = L"FnStreamMode1";
const WCHAR c_szFnStreamMode2[] = L"FnStreamMode2";

const WCHAR c_szGetStoreInfo[] = L"GetStoreInfo";
const WCHAR c_szGetActiveTasks[] = L"GetActiveTasks";

const char  c_szStoreInfo[] = "StoreInfo";
const char  c_szStream1[] = "S1";
const char  c_szStream2[] = "S2";

const char  c_szDone[] = "_Done_";
const WCHAR  c_wszDone[] = L"_Done_";

#endif // _CEINVOKE_H_
