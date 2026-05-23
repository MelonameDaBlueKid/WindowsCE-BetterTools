// Object1.cpp : Implementation of CObject1
#include "stdafx.h"
#include "Count.h"
#include "Object1.h"
#include "resource.h"

#include "Counter.h"


/////////////////////////////////////////////////////////////////////////////
// CObject1

STDMETHODIMP CObject1::Initialize(DWORD pInterface)
{
	// Save IFullCtrl1 interface
	m_pICounter = (ICounter*)pInterface;

	return S_OK;
}

STDMETHODIMP CObject1::Start()
{
	if(m_pICounter != NULL)
	{
		for(int i = 1; i <= m_nMax; i++)
		{
			TCHAR szBuf1[40] = _T("");
			int nResult = LoadString (_Module.m_hInst, IDS_SENT_MESSAGES, szBuf1, sizeof(szBuf1) );

			TCHAR szBuf2[50];
			wsprintf(szBuf2, szBuf1, i );
			
			Sleep(500);

			m_pICounter->GetInfoFromCounter(T2BSTR(szBuf2));
		}
	}
	return S_OK;
}


STDMETHODIMP CObject1::SetMax(int nMax)
{
	m_nMax = nMax;

	return S_OK;
}
