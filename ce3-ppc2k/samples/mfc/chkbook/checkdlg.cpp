// CheckDlg.cpp : implementation file for CCheckDlg
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "mainfrm.h"
#include "chkbook.h"
#include "CheckDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog


CCheckDlg::CCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckDlg)
	m_strMemo = _T("");
	m_strPayTo = _T("");
	m_strCheckNo = _T("");
	m_strDate = _T("");
	m_dwCents = 0;
	m_strAmount = _T("");
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg message handlers

BOOL GetDollarsCents(HWND hWnd, DWORD& dwCents)
{
	TCHAR szWindowText[20];
	::GetWindowText(hWnd, szWindowText, 19);
	DWORD dwDollars;
	int nCents;
	TCHAR* psz;
	TCHAR* pszDollars;
	TCHAR* pszCents;

	// strip leading blanks
	for (pszDollars = szWindowText;  *pszDollars == ' ';  pszDollars++)
	{
		if (*pszDollars == 0)
		{
			dwCents = 0;
			return TRUE;
		}
	}

	// parse dollar amount, before optional decimal point
	for (psz = pszDollars; (*psz != '.') && (*psz != ' ') && (*psz != 0); psz++)
	{
		if ((*psz < '0') || (*psz > '9'))
			return FALSE;
	}
	BOOL bDollarsOnly = (*psz == 0);
	*psz = 0;

	if (_tcslen(pszDollars) > 8)
		return FALSE;
	if (_tcslen(pszDollars) == 0)
	{
		dwDollars = 0L;
	}
	else
	{
		dwDollars = _ttol(pszDollars);
		if (dwDollars > ((DWORD)0xffffffff)/100)
			return FALSE;
	}

	if (bDollarsOnly)
	{
		nCents = 0;
	}
	else  // decimal point was found
	{
		// parse cents
		for (pszCents = ++psz; (*psz != 0) && (*psz != ' '); psz++)
		{
			if ((*psz < '0') || (*psz > '9'))
				return FALSE;
		}
		if (*psz == ' ')
		{
			for (psz++ ; *psz != 0; psz++)
			{
				if (*psz != ' ')
					return FALSE;
			}
		}

		int nCentsStrLen = _tcslen(pszCents);
		switch (nCentsStrLen)
		{
			case 0:
				nCents = 0;
				break;
			case 1:
				nCents = _ttoi(pszCents) * 10;
				break;
			case 2:
				nCents = _ttoi(pszCents);
				break;
			default:
				return FALSE;
		}
	}

	dwCents = dwDollars * 100 + nCents;
	return TRUE;
}

CString GetDollarsCentsFormatted(DWORD dwCents)
{
	DWORD dwDollars = dwCents / 100;
	WORD wCents = (WORD)(dwCents - 100 * dwDollars);

	CString str;
	str.Format(_T("%lu.%02u"), dwDollars, wCents);
	return str;
}

void SetDollarsCents(HWND hWnd, DWORD dwCents)
{
	// Convert the DWORD dollars/cents value to a string and
	// display it in the dollars/cents control.

	// If the dollar cent field has been previously determined by
	// DDX_DollarsCents() to be invalid, then don't update it.
	// Leave the invalid data in the field so the user can correct
	// it, rather than replace it with the literal translation
	// of the INVALID_DOLLARS_CENTS #define value.

	CString str = GetDollarsCentsFormatted(dwCents);
	::SetWindowText(hWnd, str.GetBufferSetLength(20));
}

void AFXAPI DDX_DollarsCents(CDataExchange* pDX, int nIDC, DWORD& dwCents)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		if (!GetDollarsCents(hWndCtrl, dwCents))
		{
			AfxMessageBox(CString((LPCTSTR)IDS_MESSAGE1));
			pDX->Fail();
		}
	}
	else
	{
		SetDollarsCents(hWndCtrl, dwCents);
	}
}

void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckDlg)
	DDX_Text(pDX, IDC_MEMO, m_strMemo);
	DDV_MaxChars(pDX, m_strMemo, 39);
	DDX_Text(pDX, IDC_PAYTO, m_strPayTo);
	DDV_MaxChars(pDX, m_strPayTo, 39);
	DDX_Text(pDX, IDC_CHECKNO, m_strCheckNo);
	DDV_MaxChars(pDX, m_strCheckNo, 10);
	DDX_Text(pDX, IDC_DATE, m_strDate);
	DDV_MaxChars(pDX, m_strDate, 9);
	DDX_DollarsCents(pDX, IDC_AMOUNTNUM, m_dwCents);
	DDX_Text(pDX, IDC_AMOUNTTEXT, m_strAmount);
	//}}AFX_DATA_MAP
}

CString CCheckDlg::GetDollarsCentsText(DWORD dwCents)
{
	CString str, strTemp;
	DWORD dwDollars = dwCents / 100;
	WORD wCents = (WORD)(dwCents - (dwDollars * 100));
	if (dwDollars == 0L)
	{
		str.LoadString(IDS_ONES_0);   // "Zero"
		str += ' ';
	}
	else
	{
		if (dwDollars >= 1000000)
		{
			DWORD dwMillions = dwDollars / 1000000;
			CString strMillions = HundredsTensOnes(dwMillions);
			strTemp.LoadString(IDS_MILLION);    // "Million"
			str = strMillions;
			str += ' ';
			str += strTemp;
			str += ' ';
			dwDollars -= (dwMillions * 1000000);
		}
		if (dwDollars >= 1000)
		{
			DWORD dwThousands = dwDollars / 1000;
			CString strThousands = HundredsTensOnes(dwThousands);
			strTemp.LoadString(IDS_THOUSAND);   // "Thousand"
			str += strThousands;
			str += ' ';
			str += strTemp;
			str += ' ';
			dwDollars -= (dwThousands * 1000);
		}
		if (dwDollars > 0)
		{
			CString strHundredsTensOnes = HundredsTensOnes(dwDollars);
			str += strHundredsTensOnes;
			str += ' ';
		}
	}
	CString strCents;
	strCents.Format(_T("%02u"), wCents);
	strTemp.LoadString(IDS_AND);    // "and"
	str += strTemp;
	str += ' ';
	str += strCents;
	strTemp.LoadString(IDS_HUNDRETHS_DOLLARS);  // "/100ths Dollars"
	str += strTemp;
	return str;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation

CString CCheckDlg::HundredsTensOnes(DWORD dwHundredsTensOnes)
{
	CString str, strTemp;
	if (dwHundredsTensOnes >= 100)
	{
		DWORD dwHundreds = dwHundredsTensOnes / 100;
		CString strHundreds;
		strHundreds.LoadString(IDS_ONES_0 + dwHundreds);
		strTemp.LoadString(IDS_HUNDRED);
		str = strHundreds;
		str += ' ';
		str += strTemp;
		str += ' ';
		dwHundredsTensOnes -= (dwHundreds * 100);
	}
	if (dwHundredsTensOnes > 0)
	{
		CString strTensOnes = TensOnes(dwHundredsTensOnes);
		str += strTensOnes;
	}
	return str;
}


CString CCheckDlg::TensOnes(DWORD dwTensOnes)
{
	CString str, strTemp;
	if (dwTensOnes > 19)
	{
		DWORD dwTens = dwTensOnes / 10;
		strTemp.LoadString(IDS_TENS_0 + dwTens);
		str += strTemp;
		dwTensOnes -= (dwTens * 10);
		if (dwTensOnes > 0)
		{
			CString strOnes;
			strOnes.LoadString(IDS_ONES_0 + dwTensOnes);
			str += '-';
			str += strOnes;
		}
	}
	else
	if (dwTensOnes >= 10)
	{
		CString strTeens;
		strTeens.LoadString(IDS_TEENS_10 + dwTensOnes - 10);
		str += strTeens;
	}
	else
	{
		CString strOnes;
		strOnes.LoadString(IDS_ONES_0 + dwTensOnes);
		str += strOnes;
	}
	return str;
}

LRESULT CCheckDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// The dialog box is either laid-out for an H/PC 2.0 or a Palm-Size PC. 
	// Now size-to-fit (move lower right corner so dialog box is same size as
	// the frame window). 
	if(message == WM_INITDIALOG)
	{
		CRect rect;
		GetParent()->GetClientRect(&rect);
		MoveWindow(&rect);
	}

	// Do not wish to close dialog until it is destroyed
	if ((message == WM_COMMAND) && (wParam <= 2))
		return 1;

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CCheckDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_SYSCHAR)
	{
		if (pMsg->wParam == (TCHAR)(_T('h')) ||
            pMsg->wParam == (TCHAR)(_T('H')) )
			return CWnd::PreTranslateMessage(pMsg);
	}


      HACCEL hAccel = ((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetAccelTable();
      if(!(hAccel && ::TranslateAccelerator(AfxGetApp()->m_pMainWnd->m_hWnd, hAccel, pMsg)))
           return CDialog::PreTranslateMessage(pMsg);
      else
         return TRUE;
}