// Counter.cpp : Implementation of CCounter
#include "stdafx.h"
#include "Count.h"
#include "Counter.h"

#include "Object1.h"

/////////////////////////////////////////////////////////////////////////////
// CCounter


HRESULT CCounter::OnDraw(ATL_DRAWINFO& di)
{
	HBRUSH hBrush, hOldBrush;
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(di.hdcDraw, hBrush);
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	SelectObject(di.hdcDraw, hOldBrush);

	return S_OK;
}

STDMETHODIMP CCounter::StartCounting()
{
	if(m_pIObject)
		m_pIObject->Start();

	return S_OK;
}

STDMETHODIMP CCounter::SetMaxCounter(int nMax)
{
	if(m_pIObject)
		m_pIObject->SetMax(nMax);

	return S_OK;
}

STDMETHODIMP CCounter::GetInfoFromCounter(BSTR pInfo)
{
	HDC hDC = GetDC();
	USES_CONVERSION;

	RECT rct;
	GetClientRect(&rct);

	PatBlt(hDC, 1, 1, rct.right - 2, rct.bottom - 2, WHITENESS);
	DrawText(hDC, OLE2T(pInfo), -1, &rct, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	ReleaseDC(hDC);

	return S_OK;
}
