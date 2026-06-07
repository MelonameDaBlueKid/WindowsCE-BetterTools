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
/////////////////////////////////////////////////////////////////////////////
//
// AXSAMPLECTL.CPP
//
//      Implementation of CAXSampleCtl
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "axsample.h"
#include "axsamplectl.h"

/////////////////////////////////////////////////////////////////////////////
// CAXSampleCtl
/////////////////////////////////////////////////////////////////////////////
CAXSampleCtl::CAXSampleCtl
(
)
{
    m_crFillColor = RGB(0, 0, 255);

    m_dwCurrentSafety = INTERFACESAFE_FOR_UNTRUSTED_CALLER
                            | INTERFACESAFE_FOR_UNTRUSTED_DATA;
}

/////////////////////////////////////////////////////////////////////////////
// CAXSampleCtl::OnDraw
/////////////////////////////////////////////////////////////////////////////
HRESULT CAXSampleCtl::OnDraw
(
    ATL_DRAWINFO & di
)
{
    RECT rc = *((RECT*)di.prcBounds);
    HDC  hDC  = di.hdcDraw;

    HBRUSH hbrFill = CreateSolidBrush(m_crFillColor);

    HBRUSH hbrOld = (HBRUSH)SelectObject(hDC, hbrFill);

    Ellipse(hDC, 0, 0, (rc.right / 2), (rc.bottom / 2));
    Ellipse(hDC, (rc.right / 2), 0, rc.right, (rc.bottom / 2));
    Ellipse(hDC, 0, (rc.bottom / 2), (rc.right / 2), rc.bottom);
    Ellipse(hDC, (rc.right / 2), (rc.bottom / 2), rc.right, rc.bottom);

    SelectObject(hDC, hbrOld);

    DeleteObject(hbrFill);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CAXSampleCtl::OnLButtonDown
/////////////////////////////////////////////////////////////////////////////
LRESULT CAXSampleCtl::OnLButtonDown
(
    UINT    uMsg,
    WPARAM  wParam,
    LPARAM  lParam,
    BOOL &  bHandled
)
{
    POINT pt = { LOWORD(lParam), HIWORD(lParam) };

    RECT rcClient;
    GetClientRect(&rcClient);

    // Is the click in the upper left circle?
    if (PtInCircle(pt, 0, 0, (rcClient.right / 2), (rcClient.bottom / 2)))
        put_FillColor(~m_crFillColor);
    else
        MessageBeep(0);

    bHandled = TRUE;
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CAXSampleCtl::PtInCircle
/////////////////////////////////////////////////////////////////////////////
BOOL CAXSampleCtl::PtInCircle
(
    POINT & pt,
    INT     iLeft,
    INT     iTop,
    INT     iRight,
    INT     iBottom
)
{
    // Determine radii
    double a = (iRight - iLeft) / 2;
    double b = (iBottom - iTop) / 2;

    // Determine x, y
    double x = pt.x - (iLeft + iRight) / 2;
    double y = pt.y - (iTop + iBottom) / 2;

    // Apply ellipse formula
    return ((x * x) / (a * a) + (y * y) / (b * b) <= 1);
}

/////////////////////////////////////////////////////////////////////////////
// Interfaces
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IAXSampleCtl::put_FillColor
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAXSampleCtl::put_FillColor
(
    COLORREF crFillColor
)
{
    if (FireOnRequestEdit(DISPID_FILLCOLOR) == S_FALSE)
        return S_FALSE;

    m_crFillColor = crFillColor;

    m_bRequiresSave = TRUE;

    FireOnChanged(DISPID_FILLCOLOR);
    FireViewChange();
    SendOnDataChange(NULL);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IAXSampleCtl::get_FillColor
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAXSampleCtl::get_FillColor
(
    COLORREF * pcrFillColor
)
{
    if (pcrFillColor == NULL)
        return E_INVALIDARG;

    *pcrFillColor = m_crFillColor;
    return S_OK;
}
