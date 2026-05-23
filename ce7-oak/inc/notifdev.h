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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

notifdev.h

Abstract:

Private portion of notify.h - Header for User Notifications

Notes: 


--*/
#ifndef _DEV_NOTIFY_H_
#define _DEV_NOTIFY_H_

#include <winioctl.h>
#include <notify.h>

#ifdef __cplusplus
extern "C"  {
#endif

#define NOTFIDEV_IOCTL_CeSetUserNotificationEx                  CTL_CODE(FILE_DEVICE_NOTIFY, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeClearUserNotification                  CTL_CODE(FILE_DEVICE_NOTIFY, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeRunAppAtTime                           CTL_CODE(FILE_DEVICE_NOTIFY, 3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeRunAppAtEvent                          CTL_CODE(FILE_DEVICE_NOTIFY, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeHandleAppNotifications                 CTL_CODE(FILE_DEVICE_NOTIFY, 5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeGetUserNotificationPreferences         CTL_CODE(FILE_DEVICE_NOTIFY, 6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeEventHasOccurred                       CTL_CODE(FILE_DEVICE_NOTIFY, 7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeGetUserNotificationHandles             CTL_CODE(FILE_DEVICE_NOTIFY, 8, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeGetUserNotification                    CTL_CODE(FILE_DEVICE_NOTIFY, 9, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NOTFIDEV_IOCTL_CeGetNotificationThreadId                CTL_CODE(FILE_DEVICE_NOTIFY, 10, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define UPDATE_BASED_ON_OFFSET(val, type, base)\
if (val) {\
	val = (type) ((DWORD)(base) + (DWORD)(val));\
}

 // used in NFY_IOControl to ensure embedded pointers don't point outside of the copied buffer
__inline
BOOL
SafeUpdateBasedOnOffset(void **val, void *base, DWORD max)
{
    if (*val)
    { 
        if((DWORD) (*val) < (DWORD) (max))
        {
	        *val = (void *)((DWORD)(base) + (DWORD)(*val));
        }
        else
        {
            return FALSE;
        }
    }
    return TRUE;
}


#define CREATE_OFFSET_BASED_ON_VALUE(val, type, base)\
if (val) {\
	val = (type) ((DWORD)(val) - (DWORD)(base));\
}

#define COPY_STRING_AND_UPDATE_OFFSET(base, offset, size, val, src)\
if (src) {\
    val = (LPTSTR) (offset);\
    memcpy(((LPBYTE)(base) + offset), (LPBYTE)(src), (wcslen(src)+1)*sizeof(WCHAR));\
    offset += size;\
}

inline DWORD StrLenDWAligned(WCHAR* str)
{
    return ((((wcslen(str) + 1) * sizeof(WCHAR)) + 0x3) & ~0x3);
}

typedef struct _NOTIFY_RET_PREFERENCES_BUF {
    WCHAR wszSound[MAX_PATH];
    DWORD ActionFlags;
}NOTIFY_RET_PREFERENCES_BUF, *PNOTIFY_RET_PREFERENCES_BUF;

typedef union __notify_arg_buffer {

    struct {
        HANDLE h;
    } CeClearUserNotification_p;

    struct {
        WCHAR      lpszAppName[MAX_PATH];
        SYSTEMTIME stTime;
        BOOL fRemove;
    } CeRunAppAtTime_p;

    struct {
        WCHAR      lpszAppName[MAX_PATH];
        LONG       lWhichEvent;
    } CeRunAppAtEvent_p;

    struct {
        WCHAR      lpszAppName[MAX_PATH];
    } CeHandleAppNotifications_p;

    struct {
        LONG    lWhichEvent;
        WCHAR   pwszEndOfCommandLine[MAX_PATH];
    } CeEventHasOccurred_p;

    struct {
        HANDLE *rghNotifications;
        DWORD   cHandleCount;
        DWORD  *cHandlesNeeded;
    } CeGetUserNotificationHandles_p;

    struct {
        HANDLE  hNotification;
        DWORD   cBytes;
        DWORD  *pcBytesNeeded;
        BYTE   *pBuffer;
    } CeGetUserNotification_p;


} NotifyArgBuffer;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _DEV_NOTIFY_H_ */
