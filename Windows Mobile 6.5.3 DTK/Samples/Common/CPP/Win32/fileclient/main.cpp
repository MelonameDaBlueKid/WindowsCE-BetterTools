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
// ************************************************************
// main.cpp
// 
// Implementation of WinMain
//
//
// ************************************************************

#include "precomp.h"

HINSTANCE g_hInst;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       CmdShow)
{
    HRESULT         hr              = NOERROR;
    HANDLE          hevtMsgAvailable= NULL;
    HPUSHROUTER     hPushRouter     = NULL;
    PUSHMSG         PushMsg         = {0};

    memset(&PushMsg, 0, sizeof(PUSHMSG));
    PushMsg.cbSize = sizeof(PUSHMSG);

    g_hInst = hInstance;

    if(!_tcsicmp(lpCmdLine, TEXT("/register"))) 
    {
        hr = PushRouter_RegisterClient(c_szContentType, c_szAppId, c_szPath, c_szParams);
        RETAILMSG(SUCCEEDED(hr), (TEXT("FileClient: Client successfully registered.\r\n")));
        goto Error;
    } 
    else if(!_tcsicmp(lpCmdLine, TEXT("/unregister"))) 
    {
        hr = PushRouter_UnRegisterClient(c_szContentType, c_szAppId);
        RETAILMSG(SUCCEEDED(hr), (TEXT("FileClient: Client successfully unregistered.\r\n")));
        goto Error;
    }
    else if(!_tcsicmp(lpCmdLine, c_szParams)) 
    {
        hr = PushRouter_Open(c_szContentType, c_szAppId, &hevtMsgAvailable, &hPushRouter);
        CHR(hr);

        while(WaitForSingleObject(hevtMsgAvailable, 10000) != WAIT_TIMEOUT) 
        {
            hr = PushRouter_GetMessage(hPushRouter, &PushMsg);
            CHR(hr);

            hr = HandleMessage(&PushMsg);
            CHR(hr);

            PushRouter_FreeMessage(&PushMsg);
            memset(&PushMsg, 0, sizeof(PUSHMSG));
            PushMsg.cbSize = sizeof(PUSHMSG);
        }
    }
    else
    {
        // Unknown parameter.  Error out.
        MessageBox(NULL, (LPTSTR)LoadString(g_hInst, IDS_PARAM_ERROR, NULL, 0),
                   (LPTSTR)LoadString(g_hInst, IDS_ERROR, NULL, 0), MB_OK);
        CHR(E_INVALIDARG);
    }
                                              
Error:
    PushRouter_FreeMessage(&PushMsg);
    PushRouter_Close(hPushRouter);

    if (SUCCEEDED(hr))
    {
        return 0;
    }
    else
    {
        RETAILMSG(1, (TEXT("FileClient: FAILURE!!! (hr = 0x%08x)\r\n"), hr));
        return 1;
    }
}
