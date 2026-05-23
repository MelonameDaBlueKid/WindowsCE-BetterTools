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

#ifndef _RTLMISC_H_
#define _RTLMISC_H_

#pragma once

#include <wtypes.h>
#include <wdm.h>
#include <types.h>

typedef struct _OSVERSIONINFOEXA {
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    CHAR   szCSDVersion[ 128 ];     // Maintenance string for PSS usage
    USHORT wServicePackMajor;
    USHORT wServicePackMinor;
    USHORT wSuiteMask;
    UCHAR wProductType;
    UCHAR wReserved;
} OSVERSIONINFOEXA, *POSVERSIONINFOEXA, *LPOSVERSIONINFOEXA;

typedef struct _OSVERSIONINFOEXW {
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    WCHAR  szCSDVersion[ 128 ];     // Maintenance string for PSS usage
    USHORT wServicePackMajor;
    USHORT wServicePackMinor;
    USHORT wSuiteMask;
    UCHAR wProductType;
    UCHAR wReserved;
} OSVERSIONINFOEXW, *POSVERSIONINFOEXW, *LPOSVERSIONINFOEXW, RTL_OSVERSIONINFOEXW, *PRTL_OSVERSIONINFOEXW;
#ifdef UNICODE
typedef OSVERSIONINFOEXW OSVERSIONINFOEX;
typedef POSVERSIONINFOEXW POSVERSIONINFOEX;
typedef LPOSVERSIONINFOEXW LPOSVERSIONINFOEX;
#else
typedef OSVERSIONINFOEXA OSVERSIONINFOEX;
typedef POSVERSIONINFOEXA POSVERSIONINFOEX;
typedef LPOSVERSIONINFOEXA LPOSVERSIONINFOEX;
#endif // UNICODE

typedef OSVERSIONINFOW RTL_OSVERSIONINFOW, *PRTL_OSVERSIONINFOW;

#ifndef GET8
#define GET8(w)             ((ULONG)(((w) >> 8) & 0xff))
#endif

#ifndef GETHI4
#define GETHI4(w)           ((ULONG)(((w) >> 4) & 0xf))
#endif

#ifndef GETLO4
#define GETLO4(w)           ((ULONG)((w) & 0xf))
#endif

//
// Upcase data table
//

extern PUSHORT Nls844UnicodeUpcaseTable;
extern PUSHORT Nls844UnicodeLowercaseTable;

#define TRAVERSE844W(pTable, wch)                                               \
    ( (pTable)[(pTable)[(pTable)[GET8((wch))] + GETHI4((wch))] + GETLO4((wch))] )

#define NLS_UPCASE(wch) (                                                   \
    ((wch) < 'a' ?                                                          \
        (wch)                                                               \
    :                                                                       \
        ((wch) <= 'z' ?                                                     \
            (wch) - ('a'-'A')                                               \
        :                                                                   \
            ((WCHAR)((wch) + TRAVERSE844W(Nls844UnicodeUpcaseTable,(wch)))) \
        )                                                                   \
    )                                                                       \
)

#if 0  //  ntcompat
BOOLEAN
RtlEqualString(
    IN const STRING *String1,
    IN const STRING *String2,
    IN BOOLEAN CaseInSensitive
    );
#endif  //  ntcompat

NTSYSAPI
NTSTATUS
RtlGetVersion(
    OUT  PRTL_OSVERSIONINFOW lpVersionInformation
    );


#if 0
NTSTATUS RtlGUIDFromString(IN PUNICODE_STRING GuidString, OUT GUID *Guid);
#endif
// NTSYSAPI
NTSTATUS
NTAPI
RtlGUIDFromString(
    IN PUNICODE_STRING GuidString,
    OUT GUID* Guid
    );

NTSTATUS
RtlStringFromGUID(REFGUID Guid,
				  PUNICODE_STRING GuidString);

NTSTATUS
RtlIntegerToChar (
    __in ULONG Value,
    __in ULONG Base OPTIONAL,
    __in LONG OutputLength,
    __out_ecount(OutputLength) PSZ String
    );

NTSTATUS
RtlIntegerToUnicodeString (
    IN ULONG Value,
    IN ULONG Base OPTIONAL,
    IN OUT PUNICODE_STRING String
    );

#endif  //  _RTLMISC_H_

