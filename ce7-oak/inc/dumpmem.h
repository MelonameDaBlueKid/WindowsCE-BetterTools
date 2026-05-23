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
#if 0
    Implementation Library: cclib.lib

    Usage: 

    // Dumping a blob to debug out:

       DEB_DUMP_MEM(ZONE_TRACE,L"Storage Key",keyStorage,sizeof(keyStorage));

    // Defining and using your own PFN_PRINT_LINE

       void PrintLineToStdOutWithSquiggles(wchar_t const * const line )
       {
           wprintf(L"~~%s~~\n",line); 
       }

       DumpMemViaFunction(keyStorage,sizeof(keyStorage), PrintLineToStdOutWithSquiggles);
#endif 

#pragma once 

#if defined (__cplusplus)
extern "C"  { 
#endif 

typedef void (*PFN_PRINT_LINE)(wchar_t const * const );

void DumpMemViaFunction(void const * const Ptr, const size_t Len, const PFN_PRINT_LINE);

//NOTE: Prefix must be NULL terminated and cchPrefix is the character count NOT INCLUDING the terminating NULL character
void DumpMemWithPrefixViaFunction (void const * const Ptr, const size_t Len, WCHAR const * const Prefix, const size_t cchPrefix, const PFN_PRINT_LINE);

// Defined for BC.
void DumpMem (void const * const Ptr, const size_t Len);

void DumpMemWithPrefix (void const * const Ptr, const size_t Len, WCHAR const * const Prefix, const size_t cchPrefix);

// Built in PFN_PRINT_LINE's
void PrintLineToDbgOut(wchar_t const * const);

// This is a macro so DEB_0 can display the calling function name.
#define  DEB_DUMP_MEM(ZONE,Msg, p, cb)\
    DEB_0(ZONE,Msg);\
    if ((ZONE)) DumpMem((p),(cb));


#if defined (__cplusplus)
}  
#endif  // CPLUSPLUS
