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

    File: MsgViewBase.cpp

    Purpose: CMsgViewBase class implementation

    Modified: 11/6/2002

******************************************************************************/
#include <windows.h>
#include <winuserm.h>
#include <tpcshell.h>
#include <cemapi.h>
#include "form.h"
#include "msgviewbase.h"
#include "msgform.h"

BOOL CMsgViewBase::ms_fRegistered = FALSE;

/******************************************************************************

    CMsgViewBase::CMsgViewBase - C'TOR

    Params:
    pFormProvider[in] - The form provider
    pForm[in] - The form
    pMsg[in] - The message

    Returns:
    NA

    Remarks:

******************************************************************************/
CMsgViewBase::CMsgViewBase(CFormProvider* pFormProvider, 
                           CMsgForm* pForm, 
                           LPMESSAGE pMsg) :
m_pForm(pForm),
m_pMsgFields(NULL),
m_hWndForm(NULL),
m_hWnd(NULL),
m_hWndFocus(NULL),
m_wType(0),
m_pMsg(pMsg),
m_pszUserData(NULL),
m_pBitmaps(NULL),
m_fDeleteOrginal(FALSE)
{
    //The view itself will build up the message
    if(NULL != m_pMsg)
    {
        m_pMsg->AddRef();
    }

    ASSERT(pForm!= NULL);

    //Allow us to get mime details for messages later.
    m_pFormProvider = pFormProvider;
    m_pFormProvider->AddRef();
}

/******************************************************************************

    CMsgViewBase::~CMsgViewBase - D'TOR

******************************************************************************/
CMsgViewBase::~CMsgViewBase()
{
    SAFE_RELEASE(m_pMsg);
    SAFE_RELEASE(m_pFormProvider);
    
    delete [] (LPBYTE) m_pMsgFields;

    if(m_pszUserData)
    {
        free(m_pszUserData);
    }

    if(NULL != m_hWnd)
    {
        DestroyWindow(m_hWnd);
    }
}

/******************************************************************************

    CMsgViewBase::OnSendCommon - Send a newly composed message
    
    Params:
    pMsgView[in] - Message to submit
    
    Returns:
    IMessage::SubmitMessage()
    
    Remarks:
    Send a newly composed message
    
******************************************************************************/
HRESULT CMsgViewBase::OnSendCommon(CMsgView *pMsgView)
{
    HRESULT hr = E_FAIL;

    //Submit the message now. This will move it from Drafts folder to the Outbox.
    //This triggers a notification from the store to Inbox, which in turn will
    //call the loaded service provider to send the message.
    hr = m_pMsg->SubmitMessage(0);
    
    EXIT_ON_FAILED(hr);
    
    hr = S_OK;

Exit:
    return hr;
}

/******************************************************************************

    CMsgViewBase::PreTranslateMsg - This method is called by 'our' message pump 
        before the message is translated. (Placeholder)

    Params:
    pMsg[in] - Message to get pretranslated

    Returns:
    FALSE

    Remarks:

******************************************************************************/
BOOL CMsgViewBase::PreTranslateMsg(MSG* pmsg)
{
    return FALSE;
}

/******************************************************************************

    CMsgViewBase::Init - Initialize the message view base

    Params:
    pMsgFields[in] - Message fields

    Returns:
    S_OK

    Remarks:
    Placeholder

******************************************************************************/
HRESULT CMsgViewBase::Init(MESSAGEFIELDS* pMsgFields)
{
    return S_OK;
}

/******************************************************************************

    CMsgViewBase::SetMessage - Sets the current message

    Params:
    wType[in] - type of message (ignored)
    pMsg[in] - Message to set

    Returns:
    MAPI_E_INVALID_PARAMETER on bad param
    S_OK if successful

    Remarks:

******************************************************************************/
HRESULT CMsgViewBase::SetMessage(WORD wType, LPMESSAGE pMsg)
{
    if(pMsg == NULL)
    {
        return ERROR_INVALID_PARAMETER;
    }

    m_wType = wType;

    //Release any previously loaded form
    SAFE_RELEASE(m_pMsg);

    if((m_pMsg = pMsg) != NULL)
    {
        m_pMsg->AddRef();
    }

    return S_OK;
}

/******************************************************************************

    CMsgViewBase::Create - Create the window for the message viewing object.

    Params:
    hwndForm[in] - form view window will reside in
    phwndBody[in/out] - View window to create and pass back

    Returns:
    TRUE on SUCCESS, FALSE OTW

    Remarks:

******************************************************************************/
BOOL CMsgViewBase::Create(HWND hwndForm, HWND* phwndBody)
{
    DWORD           dwStyle         = WS_CHILD;
    BOOL            fSuccess        = FALSE;
    LPSPropValue    rgprops         = NULL;
    RECT            rc              = {0};
    POINT           pt              = {0};
    SIZE            sz              = {0};

    //Check if window already exists
    if(NULL != m_hWnd)
    {
        SetForegroundWindow(m_hWnd);
        return TRUE;
    }

    m_hWndForm  = hwndForm;

    //Get client area
    if(!GetClientRect(hwndForm, &rc))
    {
        DEBUGMSG(TRUE, (_T("CMsgViewBase::Create GetClientRect failed\n")));
        goto Exit;
    }
    
    pt.x = rc.left;
    pt.y = rc.top;
    sz.cx = rc.right - rc.left;
    sz.cy = rc.bottom - rc.top;

    if(NULL == CreateMainWindow(_T("SDKEMSVIEWERCLASS"), _T("SDKEMSVIEWERWND"), 
        dwStyle, &pt, &sz, hwndForm, NULL))
    {
        RETAILMSG(TRUE, (_T("CMsgViewBase::Create wnd failed\n")));
        goto Exit;
    }
    *phwndBody = m_hWnd;

    ShowWindow(m_hWnd, SW_SHOW); 
    UpdateWindow(m_hWnd); 

    fSuccess = TRUE;

Exit:

    ASSERT(fSuccess);

    return fSuccess;
}

/******************************************************************************

    CMsgViewBase::ShowView - Show (or hide) the window.

    Params:
    ulAction[in] - same as nCmdShow param in ShowWindow() WINAPI

    Returns:
    Same as ShowWindow()

    Remarks:

******************************************************************************/
HRESULT CMsgViewBase::ShowView(ULONG ulAction)
{
    return (ShowWindow(m_hWnd, (int)ulAction) ? S_OK : E_FAIL);
}

/******************************************************************************

    CMsgViewBase::WndProc - WndProc for the message viewing object.

    Params:
    Standard WNDPROC stuff

    Returns:

    Remarks:

******************************************************************************/
LRESULT CMsgViewBase::WndProc(HWND hWnd, 
                              UINT uMsg, 
                              WPARAM wParam, 
                              LPARAM lParam)
{
    LRESULT lRet = 0;
    
    switch (uMsg)
    {
        case WM_CREATE:
        {
            m_hWnd = hWnd;

            lRet = OnCreate((LPCREATESTRUCT)lParam);
            if(-1 == lRet)
            {
                m_hWnd = NULL;
            }
            break;
        }

        case WM_COMMAND:
        {
            OnCommand(wParam, lParam);
            break;
        }

        /*
        Draw whatever data we have
        */
        case WM_PAINT:
        {
            RECT        rc          = {0};
            RECT        rcUserData  = {0};
            HDC         hDC         = NULL;
            PAINTSTRUCT ps          = {0};
            TEXTMETRIC  tm          = {0};
            
            hDC = BeginPaint(m_hWnd, &ps);

            GetClientRect(m_hWnd, &rc);
            memcpy(&rcUserData, &rc, sizeof(RECT));
            rcUserData.bottom = rcUserData.top;

            //Calculate the text box for the user data
            if(m_pszUserData)
            {
                UINT uWidth = rc.left - rc.right;
                UINT uHeight = rc.bottom - rc.top;
                UINT uCharsPerLine = 0;

                GetTextMetrics(hDC, &tm);

                //Find the max chars I can fit on one line
                uCharsPerLine = uWidth / tm.tmMaxCharWidth;

                //Adjust the height of the text box
                rcUserData.bottom = rcUserData.top + 
                    tm.tmHeight * (_tcslen(m_pszUserData) / uCharsPerLine) +
                    tm.tmHeight;

                
                DrawText(hDC, m_pszUserData,
                -1, &rcUserData, DT_LEFT | DT_TOP | DT_WORDBREAK);
                
                
                //Draw bounding Rect -- maybe remove this
                HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
                HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                SelectObject(hDC, hBrush);
                SelectObject(hDC, hPen);
                Rectangle(hDC, 
                    rcUserData.left, 
                    rcUserData.top, 
                    rcUserData.right, 
                    rcUserData.bottom);
                DeleteObject(hPen);

                SelectObject(hDC, (HBRUSH)GetStockObject(BLACK_BRUSH));
                SelectObject(hDC, (HPEN)GetStockObject(BLACK_PEN));
            }
           
            if(m_pBitmaps)
            {
                UINT    uIndex      = 0;
                int     iTop        = rcUserData.bottom + EDGE_OFFSET;
                int     iLeft       = EDGE_OFFSET;
                int     iMaxHeight  = 0;
                HBITMAP hBM         = NULL;
                HDC     hMemDC = CreateCompatibleDC(hDC);

                //Draw each
                for(uIndex = 0; uIndex < m_uNumBitmaps; uIndex++)
                {
                    //Text only
                    if(NULL == (m_pBitmaps + uIndex)->bmBits)
                    {
                        continue;
                    }

                    if(iMaxHeight < (m_pBitmaps + uIndex)->bmHeight)
                    {
                        iMaxHeight = (m_pBitmaps + uIndex)->bmHeight;
                    }

                    hBM = CreateBitmap((m_pBitmaps + uIndex)->bmWidth, 
                                       (m_pBitmaps + uIndex)->bmHeight, 
                                       (m_pBitmaps + uIndex)->bmPlanes, 
                                       (m_pBitmaps + uIndex)->bmBitsPixel, 
                                       (m_pBitmaps + uIndex)->bmBits);
                    SelectObject(hMemDC, hBM);

                    //Check if bitmap won't fit on current line
                    if(iLeft + (m_pBitmaps + uIndex)->bmWidth > rcUserData.right)
                    {
                        iTop += iMaxHeight + EDGE_OFFSET;
                        iLeft = EDGE_OFFSET;
                    }

                    BitBlt(
                        hDC, 
                        iLeft, 
                        iTop, 
                        (m_pBitmaps + uIndex)->bmWidth,
                        (m_pBitmaps + uIndex)->bmHeight, 
                        hMemDC, 
                        0, 
                        0, 
                        SRCCOPY);

                    //Shift next bitmap over
                    iLeft += (m_pBitmaps + uIndex)->bmWidth + EDGE_OFFSET;
               
                    DeleteObject(hBM);  
                    hBM = NULL;

                }
                DeleteDC(hMemDC);
            }

            EndPaint(m_hWnd, &ps);
            break;
        }

        case WM_DESTROY:
        {
            SetWindowLong(m_hWnd, GWL_USERDATA, NULL);
            break;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/******************************************************************************

    CMsgViewBase::OnCommand - Message form WM_COMMAND handling.

    Params:
    wParam[in] - WPARAM of WM_COMMAND
    lParam[in] - LPARAM of WM_COMMAND

    Returns:
    None

    Remarks:

******************************************************************************/
void CMsgViewBase::OnCommand(WPARAM wParam, LPARAM lParam)
{
    
}

/******************************************************************************

    CMsgViewBase::OnCreate - Initialize the newly created message viewing object.

    Params:
    pcs[in] - creation struct passed from WNDPROC, WM_CREATE

    Returns:
    0 if processed and ok, -1 will will cause CreateWindow() to fail

    Remarks:

******************************************************************************/
int CMsgViewBase::OnCreate(LPCREATESTRUCT pcs)
{
    return 0;
}

/******************************************************************************

    CMsgViewBase::OnClose - Called when window is closing

    Params:
    None

    Returns:

    Remarks:

******************************************************************************/
HRESULT CMsgViewBase::OnClose(VOID)
{
    HRESULT hr = S_OK;
    UINT uIndex = 0;
    
    //free the user data (text)
    if(m_pszUserData)
    {
        free(m_pszUserData);
    }

    //Clean up bitmaps
    if(m_pBitmaps)
    {
        //delete each set of stored bits
        for(uIndex = 0; uIndex < m_uNumBitmaps; uIndex++)
        {
            if((m_pBitmaps + uIndex)->bmBits)
            {
                free((m_pBitmaps + uIndex)->bmBits);
                (m_pBitmaps + uIndex)->bmBits = NULL;
            }
        }
        free(m_pBitmaps);
        m_pBitmaps = NULL;
        m_uNumBitmaps = 0;
    }

    //Tell parent window to close, we must do this before we destroy ourselves
    PostMessage(m_hWndForm, WM_CLOSE, 0, 0);

    //Destroy the window LAST
    if(m_hWnd)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = NULL;
    }

    return hr;
}