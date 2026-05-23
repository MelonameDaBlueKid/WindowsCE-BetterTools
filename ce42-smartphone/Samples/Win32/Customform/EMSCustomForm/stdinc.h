#pragma once
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <aygshell.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <cemapi.h>
#include "resource.h"
#include "consts.h"

#ifndef ARRAYSIZEOF
#define ARRAYSIZEOF(s) (sizeof(s) / sizeof(s[0]))
#endif

#define SAFE_RELEASE(p) if(NULL != p){p->Release(); p = NULL; }
#define SAFE_DELETE(p) if(NULL != p){delete p; p = NULL; }

#define EXIT_ON_FAILED(_hr)     \
    if(FAILED(_hr))    \
    {   \
        RETAILMSG(TRUE, (_T("FAILED(0x%08x) at %hs:%d\n"), \
            _hr, __FILE__, __LINE__)); \
        goto Exit; \
    } 

#define EXIT_ON_FAILED_(_hr,_goto)     \
    if(FAILED(_hr))    \
    {   \
        RETAILMSG(TRUE, (_T("FAILED(0x%08x) at %hs:%d\n"), \
            _hr, __FILE__, __LINE__)); \
        goto _goto; \
    } 

#define EXIT_ON_NULL(_pv)     \
    if(NULL == _pv)    \
    {   \
        hr = E_OUTOFMEMORY; \
        RETAILMSG(TRUE, (_T("OOM at %hs:%d\n"), \
            __FILE__, __LINE__)); \
        goto Exit; \
    }

#define CHP(_pv)     \
    if(NULL == _pv)    \
    {   \
        hr = ERROR_INVALID_PARAMETER; \
        RETAILMSG(TRUE, (_T("Invalid parameter passed at %hs:%d\n"), \
            __FILE__, __LINE__)); \
        goto Exit; \
    }

#define CHN(_pv)     \
    if(NULL == _pv)    \
    {   \
        hr = E_FAIL; \
        RETAILMSG(TRUE, (_T("NULL pointer %hs:%d\n"), \
            __FILE__, __LINE__)); \
        goto Exit; \
    }


#define MAPI_EXIT_ON_NULL(_pv)     \
    if(NULL == _pv)    \
    {   \
        hr = MAPI_E_NOT_ENOUGH_MEMORY; \
        RETAILMSG(TRUE, (_T("OOM at %hs:%d\n"), \
            __FILE__, __LINE__)); \
        goto Exit; \
    }

#define MAPI_CHP(_pv)     \
    if(NULL == _pv)    \
    {   \
        hr = MAPI_E_INVALID_PARAMETER; \
        RETAILMSG(TRUE, (_T("Invalid parameter passed at %hs:%d\n"), \
            __FILE__, __LINE__)); \
        goto Exit; \
    }

extern HINSTANCE g_hInstance;

//Holds info on picture objects
//also used for text-only objects, thus the pic info is NULL
typedef struct _tagEMSPICINFO {
    UINT    uOffset;    //Offset into message
    UINT    uHRes;      //Horizontal resolution in pixels
    UINT    uVRes;      //Vertical resolution in pixels
    TCHAR*  pszData;    //Text version of pixel data
    TCHAR*  pszText;    //Text message (user data)
} EMSPICINFO, *LPEMSPICINFO;
