//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
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


