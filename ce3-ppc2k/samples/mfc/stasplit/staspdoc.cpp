// staspdoc.cpp : implementation of the CStaticSplitDoc class
//

#include "stdafx.h"
#include "stasplit.h"

#include "staspdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitDoc

IMPLEMENT_DYNCREATE(CStaticSplitDoc, CDocument)

BEGIN_MESSAGE_MAP(CStaticSplitDoc, CDocument)
	//{{AFX_MSG_MAP(CStaticSplitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitDoc construction/destruction

CStaticSplitDoc::CStaticSplitDoc()
{
}

CStaticSplitDoc::~CStaticSplitDoc()
{
}

BOOL CStaticSplitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_arstrPoem.SetSize(12);
	m_arstrPoem[0].LoadString(IDS_ARSTRPOEM0);
	m_arstrPoem[1].LoadString(IDS_ARSTRPOEM1);
	m_arstrPoem[2].LoadString(IDS_ARSTRPOEM2);
	m_arstrPoem[3].LoadString(IDS_ARSTRPOEM3);
	m_arstrPoem[4].LoadString(IDS_ARSTRPOEM4);
	m_arstrPoem[5].LoadString(IDS_ARSTRPOEM5);
	m_arstrPoem[6].LoadString(IDS_ARSTRPOEM6);
	m_arstrPoem[7].LoadString(IDS_ARSTRPOEM7);
	m_arstrPoem[8].LoadString(IDS_ARSTRPOEM8);
	m_arstrPoem[9].LoadString(IDS_ARSTRPOEM9);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitDoc serialization

void CStaticSplitDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitDoc diagnostics

#ifdef _DEBUG
void CStaticSplitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStaticSplitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitDoc commands
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
void CStaticSplitDoc::FillDocument()
{
	m_arstrPoem.SetSize(12);
	m_arstrPoem[0].LoadString(IDS_ARSTRPOEM0);
	m_arstrPoem[1].LoadString(IDS_ARSTRPOEM1);
	m_arstrPoem[2].LoadString(IDS_ARSTRPOEM2);
	m_arstrPoem[3].LoadString(IDS_ARSTRPOEM3);
	m_arstrPoem[4].LoadString(IDS_ARSTRPOEM4);
	m_arstrPoem[5].LoadString(IDS_ARSTRPOEM5);
	m_arstrPoem[6].LoadString(IDS_ARSTRPOEM6);
	m_arstrPoem[7].LoadString(IDS_ARSTRPOEM7);
	m_arstrPoem[8].LoadString(IDS_ARSTRPOEM8);
	m_arstrPoem[9].LoadString(IDS_ARSTRPOEM9);

	UpdateAllViews(NULL);
}

void CStaticSplitDoc::EmptyDocument()
{
	m_arstrPoem.SetSize(12);
	m_arstrPoem[0].LoadString(IDS_EMPTY);
	m_arstrPoem[1].LoadString(IDS_EMPTY);
	m_arstrPoem[2].LoadString(IDS_EMPTY);
	m_arstrPoem[3].LoadString(IDS_EMPTY);
	m_arstrPoem[4].LoadString(IDS_EMPTY);
	m_arstrPoem[5].LoadString(IDS_EMPTY);
	m_arstrPoem[6].LoadString(IDS_EMPTY);
	m_arstrPoem[7].LoadString(IDS_EMPTY);
	m_arstrPoem[8].LoadString(IDS_EMPTY);
	m_arstrPoem[9].LoadString(IDS_EMPTY);

	UpdateAllViews(NULL);
}
#endif