// SketcCtl.cpp : Implementation of CSketcCtl
#include "stdafx.h"
#include "Sketch.h"
#include "SketcCtl.h"

/////////////////////////////////////////////////////////////////////////////
// CSketcCtl

STDMETHODIMP CSketcCtl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISketcCtl,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CSketcCtl::get_PenWidth(short *pVal)
{
	*pVal = m_PenWidth;
	return S_OK;
}

STDMETHODIMP CSketcCtl::put_PenWidth(short newVal)
{
	if (newVal > 0 && newVal < 7)
	{
		m_PenWidth = newVal;
		return S_OK;
	}

	else 
			{
		TCHAR szBuf1[80] = _T("");
		int nResult = LoadString (_Module.m_hInst, IDS_ERROR, szBuf1, sizeof(szBuf1) );
		return Error(szBuf1);
	}
}


HRESULT CSketcCtl::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	HBRUSH hBrush, hOldBrush;
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(di.hdcDraw, hBrush);

	left = rc.left;
	top = rc.top;
	right = rc.right;
	bottom = rc.bottom;
	Rectangle(di.hdcDraw, left, top, right, bottom);
	SelectObject(di.hdcDraw, hOldBrush);

	return S_OK;
}


LRESULT CSketcCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, 
                                LPARAM lParam, BOOL& bHandled) 
{
	HWND hWnd;
	hWnd = ::SetCapture(m_hWnd);
	bLBDown = TRUE;
	line[0].x = LOWORD(lParam);
	line[0].y = HIWORD(lParam);
	return 0;
}

LRESULT CSketcCtl::OnLButtonUp(UINT uMsg, WPARAM wParam, 
                                LPARAM lParam, BOOL& bHandled) 
{
	ReleaseCapture();
	bLBDown = FALSE;
	line[1].x = LOWORD(lParam);
	line[1].y = HIWORD(lParam);
	return 0;
}


LRESULT CSketcCtl::OnMouseMove(UINT uMsg, WPARAM wParam, 
                                LPARAM lParam, BOOL& bHandled) 
{ 
	static BOOL bThere = FALSE;

	if ((::GetCapture() == m_hWnd) )
	{
		if (LOWORD(lParam) < 65000 && HIWORD(lParam) < 65000)
		{
			if (bThere)
			{
				bThere = FALSE;
				line[0].x = LOWORD(lParam);
				line[0].y = HIWORD(lParam);
			}
			else
			{
				line[1].x = LOWORD(lParam);
				line[1].y = HIWORD(lParam);
				if ( (line[0].x != line[1].x || line[0].y != line[1].y) )
				{
					HDC hdc = GetDC();
					SelectObject(hdc, CreatePen(PS_SOLID, (m_PenWidth - 1), 0));

					Polyline(hdc, line, 2);
					line[0] = line[1];
					ReleaseDC(hdc);
				}
			}
		}
		else
		{
			bThere = TRUE;
		}
	}
	return 0;      
} 


STDMETHODIMP CSketcCtl::Erase()
{
	HDC hdc = GetDC();
	Rectangle(hdc, left, top, right, bottom);
	ReleaseDC(hdc);
	return S_OK;
}
