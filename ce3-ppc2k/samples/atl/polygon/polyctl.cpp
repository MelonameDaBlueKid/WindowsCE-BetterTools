// PolyCtl.cpp : Implementation of CPolyCtl
#include "stdafx.h"
#include "Polygon.h"
#include "PolyCtl.h"


#ifdef UNDER_CE 
	#define GSC_MASK 0x80000000L
	#ifdef _WIN32_WCE_EMULATION
		#define GSC_SETBIT 0x00000000L
	#else
		#define GSC_SETBIT 0x04000000L
	#endif
	inline HRESULT wce_OleTranslateColor(OLE_COLOR clr, HPALETTE, COLORREF *retClr)
	{
		*retClr = (clr & GSC_MASK) ? GetSysColor(clr & (~GSC_MASK) | GSC_SETBIT) : (COLORREF)(clr & 0x00FFFFFF);
		return S_OK;
	}
#else
	#define wce_OleTranslateColor(x,y,z) OleTranslateColor(x,y,z)
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolyCtl

STDMETHODIMP CPolyCtl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPolyCtl,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPolyCtl::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	HDC hdc  = di.hdcDraw;

	COLORREF	colFore;
	HBRUSH		hOldBrush, hBrush;
	HPEN		hOldPen, hPen;

	// Translate m_colFore into a COLORREF type
	wce_OleTranslateColor(m_clrFillColor, NULL, &colFore);
	
	// Create and select the colors to draw the circle
	hPen = (HPEN)GetStockObject(BLACK_PEN);
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	const double pi = 3.14159265358979;
	POINT	ptCenter;
	double  dblRadiusx = (rc.right - rc.left) / 2;
	double  dblRadiusy = (rc.bottom - rc.top) / 2;
	double	dblAngle = 3 * pi / 2;			// Start at the top
	double	dblDiff  = 2 * pi / m_nSides;	// Angle each side will make
	ptCenter.x = (rc.left + rc.right) / 2;
	ptCenter.y = (rc.top + rc.bottom) / 2;
	
	// Calculate the points for each side
	for (int i = 0; i < m_nSides; i++)
	{
		m_arrPoint[i].x = (long)(dblRadiusx * cos(dblAngle) + ptCenter.x + 0.5);
		m_arrPoint[i].y = (long)(dblRadiusy * sin(dblAngle) + ptCenter.y + 0.5);
		dblAngle += dblDiff;
	}
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

	// Create and select the brush that will be used to fill the polygon
	hBrush	  = CreateSolidBrush(colFore);
	SelectObject(hdc, hBrush);
	Polygon(hdc, &m_arrPoint[0], m_nSides);

	POINT pp[2];
	dblAngle = pi + pi / 4.0;
	pp[0].x = (long)(dblRadiusx * cos(dblAngle) + ptCenter.x + 0.5);
	pp[0].y = (long)(dblRadiusy * sin(dblAngle) + ptCenter.y + 0.5);
	pp[1].x = ptCenter.x + ptCenter.x - pp[0].x;
	pp[1].y = ptCenter.y + ptCenter.y - pp[0].y;
	Polyline(hdc, pp, 2);

	// Select back the old pen and brush and delete the brush we created
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

	return S_OK;
}

LRESULT CPolyCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WORD xPos = LOWORD(lParam);  // horizontal position of cursor 
	WORD yPos = HIWORD(lParam);  // vertical position of cursor 
	
	// If the clicked point is in our polygon then fire the ClickIn
	//  event otherwise we fire the ClickOut event
	if(xPos * (m_rcPos.bottom - m_rcPos.top) > yPos * (m_rcPos.right - m_rcPos.left))
		ClickIn(xPos, yPos);
	else
		ClickOut(xPos, yPos);

	return 0;
}

LRESULT CPolyCtl::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WORD xPos = LOWORD(lParam);  // horizontal position of cursor 
	WORD yPos = HIWORD(lParam);  // vertical position of cursor 

	ClickOut(xPos, yPos);

	return 0;
}

STDMETHODIMP CPolyCtl::get_Sides(short *pVal)
{
	*pVal = m_nSides;
	return S_OK;
}

STDMETHODIMP CPolyCtl::put_Sides(short newVal)
{
	if (newVal > 2 && newVal < 101)
	{
		m_nSides = newVal;
		FireViewChange();
		return S_OK;
	}
	else 
	{
		TCHAR szBuf1[80] = _T("");
		int nResult = LoadString (_Module.m_hInst, IDS_ERROR, szBuf1, sizeof(szBuf1) );
		return Error(szBuf1);
	}
}
