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
/******************************************************************************

    File: MsgView.h

    Purpose: CMsgView class definintion

******************************************************************************/
#pragma once
#include "stdinc.h"
#include "msgviewbase.h"
#include "msgform.h"


/******************************************************************************

    CMsgView - Handles viewing the message, can add functionality beyond what
               the base class provides

******************************************************************************/
class CMsgView : public CMsgViewBase
{
public:

    CMsgView(CFormProvider* pFormProvider, CMsgForm *pForm, LPMESSAGE pMsg);
    ~CMsgView();

    MAPIMETHOD(SetMessage)(WORD wType, LPMESSAGE pmsg);

protected:
    virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual BOOL CreateMainWindow(LPCTSTR pszClass, LPCTSTR pszTitle, DWORD dwStyle, LPPOINT pt, LPSIZE pSize, HWND hwndForm, UINT nID);

private:
    static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    HRESULT FillFromMessage();
};


