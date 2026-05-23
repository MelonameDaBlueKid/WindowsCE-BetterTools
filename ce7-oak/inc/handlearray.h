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
#pragma once

#pragma warning (disable:4100) // 'identifier' : unreferenced formal parameter
#pragma warning (disable:4514) // 'function' : unreferenced inline function has been removed
#pragma warning (push, 3)
#include <windows.h>
#pragma warning (pop)

inline BOOL IS_VALID_HANDLE(HANDLE h) { return ((NULL != h) && (INVALID_HANDLE_VALUE != h)); }

#define E_NOT_READY HRESULT_FROM_WIN32(ERROR_NOT_READY)
#define E_NOT_FOUND HRESULT_FROM_WIN32(ERROR_NOT_FOUND)

#ifndef COMPILETIME_ASSERT
#define COMPILETIME_ASSERT(f) switch (0) case 0: case f:
#endif

#define ZONE_TRACE      DEBUGZONE(0)
#define ZONE_NOTIFY     DEBUGZONE(3)
#define ZONE_ERROR      DEBUGZONE(15)

class CNotifiable
{
protected:
    LONG m_ObjRefCount;

public:
    CNotifiable();
    virtual ~CNotifiable();

    ULONG AddRef();
    ULONG Release();

    virtual HANDLE GetWaitObject() = 0;
    virtual DWORD GetWaitTimeout(DWORD dwTickCount) = 0;
    virtual HRESULT Refresh() = 0;
    virtual HRESULT Notify(DWORD dwTickCount) = 0;
    virtual HRESULT Timeout(DWORD dwTickCount) = 0;
};

class CHandleArray
{
protected:
    CRITICAL_SECTION m_cs; // protects m_NotifyCount and m_rgNotifyList
    LONG m_NotifyCount; // count of items in m_rgNotifyList; -1 means array is uninitialized or invalid
    CNotifiable * m_rgNotifyList[MAXIMUM_WAIT_OBJECTS-1]; // the list of CNotifable objects
    HANDLE m_hThread; // the notify thread
    HANDLE m_hEvent; // the event that will force the notify thread to break out of WaitForMultipleObjects

    static const DWORD m_dwThreadDeathTimeout; // the max time in milliseconds to wait for the notify thread to die

    void ProcessNotifications();

    static DWORD WINAPI ThreadProc(LPVOID pHandleArray);

public:
    CHandleArray();
    ~CHandleArray();

    HRESULT Add(CNotifiable * pNotify);
    HRESULT Remove(CNotifiable * pNotify);
    HRESULT Refresh(CNotifiable * pNotify);
    HRESULT RefreshAll();
};


