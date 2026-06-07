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

#include "stdafx.h"
#include <cemapi.h>
#include "forms.h"
#include "msgview.h"
#include "tvconsts.h"
#include "resource.h"
#include <aygshell.h>

BOOL CMsgView::ms_fRegistered = FALSE;
extern "C" HINSTANCE g_hInst;

//*******************************************************************************************
//
// CMsgView - Constructor 
//
//*******************************************************************************************
CMsgView::CMsgView(CFormProvider* pFormProvider, CMsgForm* pForm, LPMESSAGE pMsg, LPMESSAGE pMsgBase, BOOL fCompose)
{
    // The view itself will build up the message
    if ((m_pMsg = pMsg) != NULL)
    {
        m_pMsg->AddRef();
    }

    ASSERT(pForm!= NULL);

    m_pForm = pForm;

    // Allow us to get mime details for messages later.
    m_pFormProvider = pFormProvider;
    m_pFormProvider->AddRef();

    m_hWnd     = NULL;
    m_fCompose = fCompose;

    // We may later have to prefill the form with an existing message's data.
    m_wType    = 0;

    if((m_pMsgBase = pMsgBase) != NULL)
    {
        m_pMsgBase->AddRef();
    }
}

//*******************************************************************************************
//
// ~CMsgView - Destructor 
//
//*******************************************************************************************
CMsgView::~CMsgView()
{
    // Finished building up the message.
    RELEASE_OBJ(m_pMsg);
    RELEASE_OBJ(m_pFormProvider);
    
    // If we have a base message for this view, release it now.
    RELEASE_OBJ(m_pMsgBase);
    
    if (m_hWnd != NULL)
    {
        DestroyWindow(m_hWnd);
    }
}


//*******************************************************************************************
//
// OnSendCommon
//
// Send a newly composed message.
//
//*******************************************************************************************
HRESULT CMsgView::OnSendCommon(CMsgView *pMsgView)
{
    HRESULT hr = S_OK;

    // Submit the message now. This will move it from Drafts folder to the Outbox.
    // This triggers a notification from the store to Inbox, which in turn will
    // call the loaded service provider to send the message.

    hr = m_pMsg->SubmitMessage(0);
    CHR(hr);
    
    // Everything worked ok.
    hr = S_OK;

Error:

    return hr;
}


//*******************************************************************************************
//
// CMsgView::PreTranslateMsg()
//
// This method is called by 'our' message pump before the message is translated.
//
//*******************************************************************************************
BOOL CMsgView::PreTranslateMsg(MSG* pmsg)
{
    // We don't handle anything so return FALSE to let someone else handle.
    return FALSE;
}


//*******************************************************************************************
//
// Init
//
// Initialize the MsgViewBase.
//
//*******************************************************************************************
HRESULT CMsgView::Init(MESSAGEFIELDS* pMsgFields)
{
    return S_OK;
}


//*******************************************************************************************
//
// SetMessage
//
//*******************************************************************************************
HRESULT CMsgView::SetMessage(WORD wType, LPMESSAGE pMsg)
{
    if(pMsg == NULL)
    {
        return MAPI_E_INVALID_PARAMETER;
    }

    // Type is Read, Reply, Reply All, Forward.
    m_wType = wType;

    if (pMsg)
    {
        pMsg->AddRef();
    }

    // If we have a message already loaded in the form, we're done with it now.
    if (m_pMsgBase)
    {
        m_pMsgBase->Release();

        // Now store the new message to be loaded in the form.
        m_pMsgBase = pMsg;
    }
    else
    {
        m_pMsg->Release();
        m_pMsg = pMsg;
    }

    //force a repaint
    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);

    return S_OK;
}


//*******************************************************************************************
//
// Create - Create the window for the message viewing object.
//
//*******************************************************************************************
BOOL CMsgView::Create(HWND hwndForm, HWND* phwndBody)
{
    HRESULT         hr                  = S_OK;
    BOOL            fSuccess            = FALSE;
    LPSPropValue    rgprops             = NULL;
    DWORD dwStyle = WS_CHILD | WS_VISIBLE;
    RECT rc;

    // Don't need to create it here if we've already created it.
    if (m_hWnd != NULL)
    {
        // Make sure the user can see it.
        SetForegroundWindow(m_hWnd);
        return TRUE;
    }

    m_hWndForm = hwndForm;


    CBR (GetClientRect(m_hWndForm, &rc));
    
    CBR (CreateTVWindow(kszTVWndClass, kszWTVindowTitle, dwStyle, &rc, hwndForm, NULL) != NULL)
    
    *phwndBody = m_hWnd;
    fSuccess = TRUE;

Error:
    return fSuccess;
   
}


//*******************************************************************************************
//
// ShowView - Show (or hide) the window.
//
//*******************************************************************************************
HRESULT CMsgView::ShowView(ULONG ulAction)
{
    return (ShowWindow(m_hWnd, (int)ulAction) ? S_OK : E_FAIL);
}


//*******************************************************************************************
//
// WndProc - WndProc for the message viewing object.
//
//*******************************************************************************************
LRESULT CMsgView::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRet = 0;

    
    switch (uMsg)
    {

        case WM_CREATE:
            m_hWnd = hWnd;
            break;

        case WM_COMMAND:
        {
            OnCommand(wParam, lParam);
            break;
        }

        case WM_PAINT:
        {
            HDC hDC;
            PAINTSTRUCT ps;

            hDC = BeginPaint(m_hWnd, &ps);

            OnPaint(hDC);

            EndPaint(m_hWnd, &ps);
            break;
        }

        case WM_DESTROY:
            SetWindowLong(m_hWnd, GWL_USERDATA, NULL);
            break;

        default:
            DefWindowProc(hWnd, uMsg, wParam, lParam);
            break;
    }

    return lRet;
}

void CMsgView::AddToField()
{
    HRESULT         hr          = S_OK;
    ULONG           rgProps[]   = {PR_RECIPIENT_TYPE, PR_EMAIL_ADDRESS, PR_ADDRTYPE, PR_MESSAGE_CLASS};
 
    int             cb;
 
    LPSRowSet       pRowSet     = NULL;
    LPSPropValue    pVal        = NULL;
    
    LPBYTE          pb          = NULL;
    
    // * 4 because there are 4 props
    cb  = sizeof(SRowSet) + sizeof(SPropValue) * 4; // SRowSet includes one SRow.
 
    // Now allocate a buffer.
    CPR((pb = new BYTE[cb]))
    
    // Copy the properties over.
    pRowSet = (LPSRowSet)pb;
    pVal    = (LPSPropValue)(pb + ( sizeof(SRowSet) + sizeof(SRow) ));
 
    // initialize
    pRowSet->aRow[0].cValues = 0;
    pRowSet->aRow[0].lpProps = pVal;
    
    // begin filling the values
    pVal->ulPropTag = PR_RECIPIENT_TYPE;
    pVal->Value.ul  = MAPI_TO;
    ++pVal;
    ++pRowSet->aRow[0].cValues;
 
    pVal->ulPropTag   = PR_EMAIL_ADDRESS;
    pVal->Value.lpszW = L"14255550000"; // a default number
    ++pVal;
    ++pRowSet->aRow[0].cValues;
 
    pVal->ulPropTag   = PR_ADDRTYPE;
    pVal->Value.lpszW = L"SMS";
    ++pVal;
    ++pRowSet->aRow[0].cValues;
 
    pVal->ulPropTag    = PR_MESSAGE_CLASS;
    pVal->Value.lpszW  = (LPTSTR)kszSMSMsgClass;
    ++pVal;
    ++pRowSet->aRow[0].cValues;
 
    pRowSet->cRows = 1;
    
    hr = m_pMsg->ModifyRecipients(MODRECIP_ADD, (LPADRLIST)pRowSet);
    CHR(hr);
    
Error:
     delete [] pb;
}

void CMsgView::OnCommand(WPARAM wParam, LPARAM lParam)
{
    HRESULT hr = S_OK;
    BOOL fSend = FALSE;

    switch (LOWORD(wParam))
    {
        case ID_RECORD:
        {
            fSend = TRUE;
            break;
        }

        case ID_IGNORE:
        {
            fSend = TRUE;
            break;
        }
    }

    if (fSend)
    {
        //The user wants to send, so let's fill in our return SMS number as the "to" field
        SPropValue rgProps[6];

        // Change the message class on this message to be a "normal" SMS
        rgProps[0].ulPropTag   = PR_MESSAGE_CLASS;
        rgProps[0].Value.lpszW = (TCHAR*)&(kszSMSMsgClass[0]);

        // Also change the subject to add the answer to our question
        ULONG cValues = 0;
        SPropValue *pspv = NULL;
        SizedSPropTagArray(1, spta) = { 1, PR_SUBJECT };
        BOOL fdrewsub = FALSE;

        if (m_pMsgBase)
        {
            hr = m_pMsgBase->GetProps((SPropTagArray *) &spta, MAPI_UNICODE, &cValues, &pspv);
            CHR(hr);
        }

        TCHAR szReplyText[160]; //max_sms
        wsprintf(szReplyText, L"%s: %s", LOWORD(wParam)==ID_RECORD ? L"RECORD" : L"IGNORE", pspv[0].Value.lpszW);
        rgProps[1].ulPropTag   = PR_SUBJECT;
        rgProps[1].Value.lpszW = szReplyText;

        rgProps[2].ulPropTag   = PR_CONTENT_LENGTH;
        rgProps[2].Value.ul    = 0;
 
        rgProps[3].ulPropTag   = PR_SENDER_EMAIL_ADDRESS;
        rgProps[3].Value.lpszW = L"14255550000";
 
        rgProps[4].ulPropTag   = PR_MSG_STATUS;
        rgProps[4].Value.ul    = MSGSTATUS_RECTYPE_SMS;
 
        rgProps[5].ulPropTag   = PR_PROOF_OF_DELIVERY_REQUESTED;
        rgProps[5].Value.ul    = 0;
    
        // Now set the new message properties
        hr = m_pMsg->SetProps(6, rgProps, NULL);
        CHR(hr);

        //and add our service as a recipient
        AddToField();

        hr = m_pMsg->SubmitMessage(0);
        CHR(hr);

        //and we're done with the form
        hr = m_pForm->SetMessageStatus(IMessageFormHostEx::CMS_SENT);
        CHR(hr);

        hr = m_pForm->CloseForm();
        CHR(hr);
    }

Error:
    return;
}

void CMsgView::OnPaint(HDC hdc)
{
    HRESULT hr = S_OK;

    //draw our TV screen
    HBITMAP hBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_TVSET));
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(memDC, hBitmap);

    RECT rc;
    GetClientRect(m_hWnd, &rc);

    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    StretchBlt(hdc, rc.top, rc.left, rc.right-rc.left, rc.bottom-rc.top, 
               memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    //cleanup bitmap drawing
    SelectObject(memDC, hBitmapOld);
    DeleteDC(memDC);
    DeleteObject(hBitmap);

    rc.left = 50;
    rc.right = 190;
    rc.top = 140;
    rc.bottom = 220;
   
    //black-on-white text
    SetTextColor(hdc, RGB(0,0,0));
    SetBkColor(hdc, RGB(255,255,255));

    ULONG cValues = 0;
    SPropValue *pspv = NULL;
    SizedSPropTagArray(1, spta) = { 1, PR_SUBJECT };
    BOOL fdrewsub = FALSE;

    if (m_pMsgBase)
    {
        hr = m_pMsgBase->GetProps((SPropTagArray *) &spta, MAPI_UNICODE, &cValues, &pspv);
        CHR(hr);

        if (cValues == 1)
        {
            if (pspv[0].Value.lpszW)
            {
                DrawText(hdc, pspv[0].Value.lpszW, -1, &rc, DT_NOPREFIX | DT_LEFT | DT_WORDBREAK);
                fdrewsub = TRUE;
            }
        }
    }

    if ((!fdrewsub) && (m_pMsg))
    {
        hr = m_pMsg->GetProps((SPropTagArray *) &spta, MAPI_UNICODE, &cValues, &pspv);
        CHR(hr);

        if (cValues == 1)
        {
            if (pspv[0].Value.lpszW)
            {
                DrawText(hdc, pspv[0].Value.lpszW, -1, &rc, DT_NOPREFIX | DT_LEFT | DT_WORDBREAK);
            }
        }
    }

Error:
    return;
}

//*******************************************************************************************
//
// WndProcStatic - Static WndProc entry point to redirect to the member WndProc
//
//*******************************************************************************************
LRESULT CALLBACK CMsgView::WndProcStatic(
    HWND hWnd,      // In: HWND for window
    UINT message,   // In: Message to process
    WPARAM wParam,  // In/Out: Message-specific WPARAM
    LPARAM lParam   // In/Out: Message-specific LPARAM
)
{
    CMsgView*   pMsgView = (CMsgView *)GetWindowLong(hWnd, GWL_USERDATA);
    LRESULT lResult = 0;

    switch (message)
    {
        case WM_CREATE:
            // Get the buffer we were passed and store it.
            pMsgView = (CMsgView*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, GWL_USERDATA, (LPARAM)pMsgView);
            if (NULL == pMsgView)
            {
                lResult = -1;
                break;
            }
            // Intentional fall-through
        default:
            if (NULL != pMsgView)
            {
                lResult = pMsgView->WndProc(hWnd, message, wParam, lParam);
            }
            break;
    }

    return lResult;
}

//*******************************************************************************************
//
// CreateTVWindow - Register the window class for the game and create the window.
//
//*******************************************************************************************
BOOL CMsgView::CreateTVWindow(
    LPCTSTR pszClass,
    LPCTSTR pszTitle,
    DWORD dwStyle,
    LPRECT pRC,
    HWND hwndForm,
    UINT nID)
{
    ASSERT (pszClass != NULL);

    WNDCLASS wc;

    if (!ms_fRegistered)
    {
        ASSERT( !GetClassInfo(g_hInst, pszClass, &wc) );
        ZeroMemory(&wc, sizeof(wc));

        wc.style            = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc      = CMsgView::WndProcStatic;
        wc.cbClsExtra       = 0;
        wc.cbWndExtra       = 0;
        wc.hInstance        = g_hInst;
        wc.hIcon            = NULL;
        wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground    = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.lpszMenuName     = NULL;
        wc.lpszClassName    = pszClass;

        ms_fRegistered = RegisterClass(&wc);
    }

    m_hWnd = ::CreateWindow(pszClass, pszTitle, dwStyle, 0, 0,
            (*pRC).right-(*pRC).left, (*pRC).bottom - (*pRC).top, hwndForm,
            (HMENU) nID, g_hInst, (LPVOID) this);

    //if this is a compose form, we need to add buttons for the user's choices
    if (m_fCompose)
    {
        ::CreateWindow(L"BUTTON", L"Record", WS_VISIBLE, 55, 190, 60, 25, m_hWnd, (HMENU)ID_RECORD, g_hInst, 0);
        ::CreateWindow(L"BUTTON", L"Ignore", WS_VISIBLE, 125, 190, 60, 25, m_hWnd, (HMENU)ID_IGNORE, g_hInst, 0);
    }

    return (NULL != m_hWnd);
}


