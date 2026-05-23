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
#ifndef _TRUETYPEFONTDRIVER_HPP_INCLUDED_
#define _TRUETYPEFONTDRIVER_HPP_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

PIFIMETRICS
FntDrvQueryFont(
    DHPDEV     dhpdev,
    ULONG      hff,
    ULONG      iFace,
    ULONG_PTR* pid
    );

LONG
FntDrvQueryFontFile(
    ULONG  hff,
    ULONG  ulMode,
    ULONG  cjBuf,
    ULONG* pulBuf
    );

ULONG
APIENTRY
FntDrvLoadFontFile(
    ULONG         cFiles,
    ULONG_PTR*    piFile,
    PVOID*        ppvView,
    ULONG*        pcjView,
    struct DESIGNVECTOR* pdv,
    ULONG         ulLangId,
    ULONG         ulFastCheckSum
    );

BOOL
FntDrvUnloadFontFile(
    ULONG hff
    );

extern
LONG
FntDrvQueryFontData(
    DHPDEV     dhpdev,
    FONTOBJ*   pfo,
    ULONG      iMode,
    HGLYPH     hg,
    GLYPHDATA* pgd,
    PVOID      pv,
    ULONG      cjSize
    );

VOID
FntDrvDestroyFont(
    FONTOBJ* pfo
    );

ULONG
FntDrvQueryTrueTypeTable(
    ULONG   hff,
    ULONG   ulFont,  // always 1 for version 1.0 of tt
    ULONG   ulTag,   // tag identifying the tt table
    PTRDIFF dpStart, // offset into the table
    ULONG   cjBuf,   // size of the buffer to retrieve the table into
    PBYTE   pjBuf,   // ptr to buffer into which to return the data
    PBYTE*  ppjTable,// ptr to table in mapped font file
    ULONG*  pcjTable // size of the whole table in the file
    );

#ifdef __cplusplus
};
#endif

#endif // _TRUETYPEFONTDRIVER_HPP_INCLUDED_
