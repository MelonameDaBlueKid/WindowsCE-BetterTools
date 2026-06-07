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

    File: MsgView.cpp

    Purpose: CMsgView class implementation

    Modified: 11/6/2002

******************************************************************************/
#include "stdinc.h"
#include <winuserm.h>
#include <tpcshell.h>
#include <cemapi.h>
#include "form.h"
#include "msgview.h"


/******************************************************************************

    CMsgView::CMsgView - C'TOR

    Params:
    pFormProvider[in] - Provider of the form
    pForm[in] - The form
    pMsg[in] - The message contained in the form

    Returns:
    NA

    Remarks:

******************************************************************************/
CMsgView::CMsgView(CFormProvider* pFormProvider, 
                   CMsgForm* pForm, 
                   LPMESSAGE pMsg) : CMsgViewBase(pFormProvider, pForm, pMsg)
{
}

/******************************************************************************

    CMsgView::~CMsgView - D'TOR

    Params:
    None

    Returns:
    NA

    Remarks:

******************************************************************************/
CMsgView::~CMsgView()
{
}

/******************************************************************************

    CMsgView::WndProcStatic - Static WndProc entry point to redirect to the 
                              member WndProc

    Params:
    Standard WNDPROC stuff

    Returns:

    Remarks:

******************************************************************************/
LRESULT CALLBACK CMsgView::WndProcStatic(HWND hWnd,
                                         UINT message,
                                         WPARAM wParam,
                                         LPARAM lParam)
{
    CMsgView*   pMsgView = NULL;
    LRESULT     lResult  = 0;

    pMsgView = (CMsgView*)GetWindowLong(hWnd, GWL_USERDATA);
    
    switch(message)
    {
        case WM_CREATE:
            //Get the buffer we were passed and store it.
            pMsgView = (CMsgView*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, GWL_USERDATA, (LPARAM)pMsgView);
            
            if(NULL == pMsgView)
            {
                lResult = -1;
                break;
            }
            //Intentional fall-through
        default:
            if(NULL != pMsgView)
            {
                lResult = pMsgView->WndProc(hWnd, message, wParam, lParam);
            }
            break;
    }

    return lResult;
}

/******************************************************************************

    CMsgView::WndProc - WndProc entry point for the CMsgView class's main wnd

    Params:
    Standard WNDPROC stuff

    Returns:

    Remarks:

******************************************************************************/
LRESULT CMsgView::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // For now, just let the base class do everything
    return CMsgViewBase::WndProc(hWnd, message, wParam, lParam);
}

/******************************************************************************

    CMsgView::CreateMainWindow - Register the window class and create the 
        main window.

    Params:
    pszClass[in] - Window class name
    pszTitle[in] - Window title
    dwStyle[in] - window style flags
    pt[in] - 
    pSize[in] - 
    hwndForm[in] - 
    nId[in] - 

    Returns:

    Remarks:

******************************************************************************/
BOOL CMsgView::CreateMainWindow(LPCTSTR pszClass,
                                LPCTSTR pszTitle,
                                DWORD dwStyle,
                                LPPOINT pt,
                                LPSIZE pSize,
                                HWND hwndForm,
                                UINT nID)
{
    WNDCLASS wc;

    ASSERT(NULL != pszClass);

    if(!ms_fRegistered)
    {
        ASSERT(!GetClassInfo(g_hInstance, pszClass, &wc));
        ZeroMemory(&wc, sizeof(wc));

        wc.style            = WS_CHILD | CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc      = CMsgView::WndProcStatic;
        wc.cbClsExtra       = 0;
        wc.cbWndExtra       = 0;
        wc.hInstance        = g_hInstance;
        wc.hIcon            = NULL;
        wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.lpszMenuName     = NULL;
        wc.lpszClassName    = pszClass;

        ms_fRegistered = RegisterClass(&wc);
    }

    m_hWnd = ::CreateWindow(pszClass, pszTitle, dwStyle, pt->x, pt->y,
            pSize->cx, pSize->cy, hwndForm,
            (HMENU) nID, g_hInstance, (LPVOID) this);

    return (NULL != m_hWnd);
}

/******************************************************************************
******************************************************************************/
HRESULT CMsgView::SetMessage(WORD wType, LPMESSAGE pMsg)
{
    //Let the base view know
    HRESULT hr = CMsgViewBase::SetMessage(wType, pMsg);
    
    if(SUCCEEDED(hr))
    {
        //Need to get new data and redraw the form
        FillFromMessage();
    }

    return hr;
}

/******************************************************************************

    CgView::FillFromMessage - Cleans up any old data, gets new data from the 
    message, and redraws the new message

******************************************************************************/
HRESULT CMsgView::FillFromMessage()
{
    HRESULT         hr          = E_FAIL;
    IStream*        pIStream    = NULL;
    STATSTG         statstg     = {0};
    LPSTREAM        pStmBody    = NULL;
    LPTSTR          pszBody     = NULL;
    DWORD           cbRead      = 0;
    UINT            uNumPics    = 0;
    LPEMSPICINFO    pEMSPicInfo = NULL;
    UINT            uIndex      = 0;
    int             cch         = 0;

    MAPI_CHP(m_pMsg);

    /*
    1.)  Cleanup any old memory we have storing bitmaps and Text
    */
    if(m_pszUserData)
    {
        free(m_pszUserData);
        m_pszUserData = NULL;
    }

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
 
    /*
    2.)  Try to read the body of the message we've stored
    */
    if(SUCCEEDED(m_pMsg->OpenProperty(PR_BODY, NULL, 
                            0, MAPI_MODIFY, (LPUNKNOWN*)&pStmBody)))
    {
        if(FAILED(hr = pStmBody->Stat(&statstg, 0)))
        {
            goto Exit;
        }

        //Body length should never be zero for these messages
        if((0 == statstg.cbSize.HighPart) && (0 < statstg.cbSize.LowPart))
        {
            int    cbBody   = 0;  //Bytes in body
            int    cchbody  = 0;  //TCHARS in body

            cbBody = statstg.cbSize.LowPart;
            cchbody = cbBody/sizeof(TCHAR);

            if(NULL == (pszBody = new TCHAR[cchbody + 1]))
            {
                RETAILMSG(TRUE, (_T("SDKEMS CFormProvider::CreateReadForm - OOM\n")));
                goto Exit;
            }

            if(FAILED(hr = pStmBody->Read((LPBYTE)pszBody, cbBody, &cbRead)) ||
                (cbBody != (int)cbRead))
            {
                RETAILMSG(TRUE, (_T("SDKEMS CFormProvider::CreateReadForm - Body read failed %x\n"), hr));

                //Didn't fail on read, but byte counts don't match...
                if(SUCCEEDED(hr))
                {
                    hr = E_FAIL;
                }

                goto Exit;
            }
            //Add trailing NULL
            pszBody[cbBody/sizeof(TCHAR)] = '\0';
        }
        else
        {
            //0 length message is not acceptable here
            goto Exit;
        }
    }
    ASSERT(pszBody);
    MAPI_CHP(pszBody);

    /*
    3.)  Extract the info from the body of the msg
    */
    //Check message ID
    if(0 != _tcsncmp(kszEMSID, pszBody, _tcslen(kszEMSID)))
    {
        goto Exit;
    }

    //ID is correct so now we can parse the rest of the body and extract
    //the objects we want.
    if(FAILED(hr = ExtractPicsFromBody(pszBody, &uNumPics, &pEMSPicInfo)))
    {
        goto Exit;
    }

    /*
    4.)  Create bitmaps and text from the extracted info
    */
    //Concatenate the user data (text) and add it to the view
    for(uIndex = 0; uIndex < uNumPics; uIndex++)
    {
        if(pEMSPicInfo[uIndex].pszText)
        {
            cch += _tcslen(pEMSPicInfo[uIndex].pszText);
        }
    }
    
    //Allocate mem for user data(text) string
    m_pszUserData = (TCHAR*)malloc(sizeof(TCHAR) * (cch+1));
    ZeroMemory(m_pszUserData, sizeof(TCHAR) * (cch+1));

    for(uIndex = 0; uIndex < uNumPics; uIndex++)
    {
        if(pEMSPicInfo[uIndex].pszText)
        {
            _tcscat(m_pszUserData, pEMSPicInfo[uIndex].pszText);
        }
    }
    RETAILMSG(TRUE, (_T("CMsgViewBase::SetMessage - m_pszUserData = %s"), m_pszUserData));

    //Allocate space to hold the bitmap data
    m_uNumBitmaps = uNumPics;
    m_pBitmaps = (LPBITMAP)malloc(sizeof(BITMAP)*m_uNumBitmaps);
    ZeroMemory(m_pBitmaps, sizeof(BITMAP)*m_uNumBitmaps);

    //Convert the pic data and save it in the bitmap array
    if(FAILED(hr = ConvertToMonoBitmap(m_uNumBitmaps, &pEMSPicInfo, m_pBitmaps)))
    {
        goto Exit;
    }

    /*
    5.)  Update the view (redraw the window)
    */
    InvalidateRect(m_hWnd, NULL, TRUE);
    
Exit:
    SAFE_RELEASE(pStmBody);
    
    if(pszBody)
    {
        delete [] pszBody;
        pszBody = NULL;
    }
    

    return hr;
}
