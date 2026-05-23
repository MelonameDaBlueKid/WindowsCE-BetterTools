// CComCtrl.cpp : Implementation of CComCtrl
#include "stdafx.h"
#include "CompCtrl.h"
#include "CComCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CComCtrl

void CComCtrl::IncrementSides()
{
	IPolyCtl* pIPolyCtl;
	HRESULT hr = GetDlgControl(IDC_POLYCTL1, IID_IPolyCtl, (void**)&pIPolyCtl );
	if(SUCCEEDED(hr))
	{
		short nSides;
		pIPolyCtl->get_Sides(&nSides);
		nSides++;
		pIPolyCtl->put_Sides(nSides);
		UpdateNumberOfSides(0,0,0);
	}
}

void CComCtrl::DecrementSides()
{
	IPolyCtl* pIPolyCtl;
	HRESULT hr = GetDlgControl(IDC_POLYCTL1, IID_IPolyCtl, (void**)&pIPolyCtl );
	if(SUCCEEDED(hr))
	{
		short nSides;
		pIPolyCtl->get_Sides(&nSides);
		if(nSides > 3)
		{
			nSides--;
			pIPolyCtl->put_Sides(nSides);
			UpdateNumberOfSides(0,0,0);
		}
	}
}

int CComCtrl::UpdateNumberOfSides(DWORD x, int y, long z)
{
	IPolyCtl* pIPolyCtl;
	HRESULT hr = GetDlgControl(IDC_POLYCTL1, IID_IPolyCtl, (void**)&pIPolyCtl );
	if(SUCCEEDED(hr))
	{
		short nSides;
		pIPolyCtl->get_Sides(&nSides);

		TCHAR szBuf1[40] = _T("");
		int nResult = LoadString (_Module.m_hInst, IDS_SIDES, szBuf1, sizeof(szBuf1) );

		TCHAR szBuff[20];
		wsprintf(szBuff, szBuf1, nSides);
		SetDlgItemText(IDC_SIDES, szBuff);
	}
	int res = x + y + z;
	return(res);
}

void CComCtrl::UpdateSmileState()
{
	IDispatch* pISmiley;
	HRESULT hr = GetDlgControl(IDC_SMILECTRL1, IID_IDispatch, (void**)&pISmiley );
	if(SUCCEEDED(hr))
	{
		// get property(Sad)
		DISPPARAMS	dispparams;
		VARIANT		vArg;
		VARIANT		vVarResult;

		dispparams.cArgs = 0;
		dispparams.cNamedArgs = 0;
		dispparams.rgdispidNamedArgs = NULL;
		dispparams.rgvarg = NULL;
			
		hr = pISmiley->Invoke(1, IID_NULL, 0, DISPATCH_PROPERTYGET, &dispparams, &vVarResult, NULL, NULL);
		if(SUCCEEDED(hr))
		{
			// put property(Sad)
			DISPID		dispidNamed = DISPID_PROPERTYPUT;
			DISPPARAMS	dispparams;

			vArg.vt = VT_BOOL;
			vArg.boolVal = vVarResult.boolVal;

			dispparams.cArgs = 1;
			dispparams.cNamedArgs = 1;
			dispparams.rgdispidNamedArgs = &dispidNamed;
			dispparams.rgvarg = &vArg;
			
			pISmiley->Invoke(1, IID_NULL, 0, DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);
		}
	}
}
