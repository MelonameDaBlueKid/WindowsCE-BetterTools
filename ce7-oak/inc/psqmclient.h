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

#ifndef PSQMCLIENT_H__
#define PSQMCLIENT_H__

#include <winioctl.h>
#include "sqmpublic.h"

// SQM message identifiers (MID-s).
#define SQMMID_SqmGetSession              1
#define SQMMID_SqmEndSession              2
#define SQMMID_SqmStartSession            3
#define SQMMID_SqmGetSessionStartTime     4
#define SQMMID_SqmGetEnabled              5
#define SQMMID_SqmSetEnabled              6
#define SQMMID_SqmGetFlags                7
#define SQMMID_SqmSetFlags                8
#define SQMMID_SqmClearFlags              9
#define SQMMID_SqmGetMachineId            10
#define SQMMID_SqmGetUserId               11
#define SQMMID_SqmSetMachineId            12
#define SQMMID_SqmSetUserId               13
#define SQMMID_SqmCreateNewId             14
#define SQMMID_SqmReadSharedMachineId     15
#define SQMMID_SqmReadSharedUserId        16
#define SQMMID_SqmWriteSharedMachineId    17
#define SQMMID_SqmWriteSharedUserId       18
#define SQMMID_SqmSetAppVersion           19
#define SQMMID_SqmSet                     20
#define SQMMID_SqmIncrement               21
#define SQMMID_SqmSetBits                 22
#define SQMMID_SqmSetIfMax                23
#define SQMMID_SqmSetIfMin                24
#define SQMMID_SqmAddToAverage            25
#define SQMMID_SqmAddToStream             26
#define SQMMID_SqmGet                     27
#define SQMMID_SqmTimerStart              28
#define SQMMID_SqmTimerRecord             29
#define SQMMID_SqmTimerAccumulate         30
#define SQMMID_SqmTimerAddToAverage       31
#define SQMMID_SqmSet64                   32
#define SQMMID_SqmSetBool                 33
#define SQMMID_SqmGet64                   34
#define SQMMID_SqmStartUpload             35
#define SQMMID_SqmAbortUpload             36
#define SQMMID_SqmSaveSession             37
#define SQMMID_SqmDetachProcess           38
#define SQMMID_SqmAddToStreamStringW	  39
#define SQMMID_SqmSetStringW              40
#define SQMMID_SqmAddToStreamDWORD     41

// SQM IOCTL set.
#define IOCTL_SQM_GET_SESSION             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGetSession, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_END_SESSION             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmEndSession, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_START_SESSION           CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmStartSession, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET_SESSION_START_TIME  CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGetSessionStartTime, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET_ENABLED             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGetEnabled, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_ENABLED             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetEnabled, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET_FLAGS               CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGetFlags, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_FLAGS               CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetFlags, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_CLEAR_FLAGS             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmClearFlags, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET_MACHINE_ID          CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGetMachineId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET_USER_ID             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGetUserId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_MACHINE_ID          CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetMachineId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_USER_ID             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetUserId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_CREATE_NEW_ID           CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmCreateNewId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_READ_SHARED_MACHINE_ID  CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmReadSharedMachineId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_READ_SHARED_USER_ID     CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmReadSharedUserId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_WRITE_SHARED_MACHINE_ID CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmWriteSharedMachineId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_WRITE_SHARED_USER_ID    CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmWriteSharedUserId, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_APP_VERSION         CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetAppVersion, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET                     CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSet, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_STRINGW		  CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetStringW, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_INCREMENT               CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmIncrement, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_BITS                CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetBits, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_IF_MAX              CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetIfMax, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_IF_MIN              CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetIfMin, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_ADD_TO_AVERAGE          CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmAddToAverage, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_ADD_TO_STREAM           CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmAddToStream, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_ADD_TO_STREAM_STRINGW   CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmAddToStreamStringW, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_ADD_TO_STREAM_DWORD   CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmAddToStreamDWORD, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET                     CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGet, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_TIMER_START             CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmTimerStart, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_TIMER_RECORD            CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmTimerRecord, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_TIMER_ACCUMULATE        CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmTimerAccumulate, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_TIMER_ADD_TO_AVERAGE    CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmTimerAddToAverage, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_64                  CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSet64, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SET_BOOL                CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSetBool, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_GET_64                  CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmGet64, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_START_UPLOAD            CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmStartUpload, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_ABORT_UPLOAD            CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmAbortUpload, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_SAVE_SESSION            CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmSaveSession, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SQM_DETACH_PROCESS          CTL_CODE(FILE_DEVICE_SQM, SQMMID_SqmDetachProcess, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define SQM_MAX_NUM_ARGS    15

// SQM message argument packets (MAP-s).
typedef union _SQMMAP
{
    struct
    {
        HANDLE      hProcess;
        WCHAR       szSessionIdentifier[MAX_PATH];
        DWORD       cbSessionIdentifier;
        DWORD       cbMaxSessionSize;
        DWORD       dwFlags;
        HSQMSESSION hReturn;
    } MapSqmGetSession;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        WCHAR       szPattern[MAX_PATH];
        DWORD       cbPattern;
        DWORD       dwMaxFilesToQueue;
        DWORD       dwFlags;
    } MapSqmEndSession;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
    } MapSqmStartSession;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        FILETIME    ftReturn;
    } MapSqmGetSessionStartTime;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        BOOL        fReturn;
    } MapSqmGetEnabled;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        BOOL        fEnabled;
    } MapSqmSetEnabled;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwFlags;
    } MapSqmGetFlags;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwFlags;
    } MapSqmSetFlags;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwFlags;
    } MapSqmClearFlags;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        GUID        guid;
    } MapSqmGetMachineId;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        GUID        guid;
    } MapSqmGetUserId;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        GUID        guid;
    } MapSqmSetMachineId;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        GUID        guid;
    } MapSqmSetUserId;

    struct
    {
        HANDLE hProcess;
        GUID   guid;
        BOOL   fReturn;
    } MapSqmCreateNewId;

    struct
    {
        HANDLE hProcess;
        GUID   guid;
        BOOL   fReturn;
    } MapSqmReadSharedMachineId;

    struct
    {
        HANDLE hProcess;
        GUID   guid;
        BOOL   fReturn;
    } MapSqmReadSharedUserId;

    struct
    {
        HANDLE hProcess;
        GUID   guid;
        BOOL   fReturn;
    } MapSqmWriteSharedMachineId;

    struct
    {
        HANDLE hProcess;
        GUID   guid;
        BOOL   fReturn;
    } MapSqmWriteSharedUserId;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwVersionHigh;
        DWORD       dwVersionLow;
    } MapSqmSetAppVersion;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwVal;
    } MapSqmSet;

    struct
    {
        HANDLE hProcess;
        HSQMSESSION hSession;
        DWORD dwId;
        LPWSTR pwszVal[SQM_MAX_STRING_LENGTH];
    } MapSqmSetStringW;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwInc;
    } MapSqmIncrement;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwOrBits;
    } MapSqmSetBits;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwVal;
    } MapSqmSetIfMax;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwVal;
    } MapSqmSetIfMin;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwVal;
    } MapSqmAddToAverage;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       nArgs;
        DWORD       dwArgs[SQM_MAX_NUM_ARGS];
    } MapSqmAddToStream;

    struct
    {
        HANDLE hProcess;
        HSQMSESSION hSession;
        DWORD dwId;
        DWORD cTuple;
        LPWSTR pwszVal[SQM_MAX_STRING_LENGTH];
    } MapSqmAddToStreamStringW;

    struct
    {
        HANDLE hProcess;
        HSQMSESSION hSession;
        DWORD dwId;
        DWORD cTuple;
        DWORD dwVal;               
    } MapSqmAddToStreamDWORD;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwVal;
        BOOL        fReturn;
    } MapSqmGet;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
    } MapSqmTimerStart;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
    } MapSqmTimerRecord;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
    } MapSqmTimerAccumulate;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
    } MapSqmTimerAddToAverage;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD64     qwVal;
    } MapSqmSet64;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD       dwVal;
    } MapSqmSetBool;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
        DWORD       dwId;
        DWORD64     qwVal;
        BOOL        fReturn;
    } MapSqmGet64;

    struct
    {
        HANDLE            hProcess;
        WCHAR             szPattern[MAX_PATH];
        DWORD             cbPattern;
        WCHAR             szUrl[MAX_PATH]; 
        DWORD             cbUrl;
        WCHAR             szSecureUrl[MAX_PATH];
        DWORD             cbSecureUrl;
        DWORD             dwFlags;
        SQMUPLOADCALLBACK pfnCallback;
        DWORD             dwReturn;
    } MapSqmStartUpload;

    struct
    {
        HANDLE hProcess;
        DWORD  dwTimeoutMilliseconds;
    } MapSqmAbortUpload;

    struct
    {
        HANDLE      hProcess;
        HSQMSESSION hSession;
    } MapSqmSaveSession;

    struct
    {
        HANDLE hProcess;
    } MapSqmDetachProcess;

} SQMMAP, *LPSQMMAP;

#endif // PSQMCLIENT_H__
