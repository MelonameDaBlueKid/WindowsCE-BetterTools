/******************************************************************************

    File: MsgView.h

    Purpose: CMsgView class definintion

    Author: Matthew S. Baker (mbaker)

    Modified: 11/6/2002

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


