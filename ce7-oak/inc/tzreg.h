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
#ifndef _TZREG_H
#define _TZREG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTZREG {
    LONG    Bias;
    LONG    StandardBias;
    LONG    DaylightBias;
    SYSTEMTIME StandardDate;
    SYSTEMTIME DaylightDate;
} TZREG;

const TCHAR cszTimeZones[] = L"Time Zones";
const TCHAR cszID[] = L"ID";
const TCHAR szDefaultTZID[] = L"DefaultTZID";
const TCHAR cszTZI[] = L"TZI";
const TCHAR cszStd[] = L"Std";
const TCHAR cszDlt[] = L"Dlt";
const TCHAR cszDisplay[] = L"Display";

const TCHAR cszDynDST[] = L"Dynamic DST";
const TCHAR cszFirstEntry[] = L"FirstEntry";
const TCHAR cszLastEntry[] = L"LastEntry";

const TCHAR cszSystemTimezone[] = L"TimeZoneInformation";
const TCHAR cszSystemTime[] = L"Time";

const TCHAR cszTZID[] = L"TZID";

#ifdef __cplusplus
}
#endif

#endif /* _TZREG_H */
