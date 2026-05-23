// npdoc.cpp : implementation of the CNotepadDoc class
//

#include "stdafx.h"
#include "np.h"

#include "npdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadDoc

IMPLEMENT_DYNCREATE(CNotepadDoc, CDocument)

BEGIN_MESSAGE_MAP(CNotepadDoc, CDocument)
	//{{AFX_MSG_MAP(CNotepadDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotepadDoc construction/destruction

CNotepadDoc::CNotepadDoc()
{
}

CNotepadDoc::~CNotepadDoc()
{
}

BOOL CNotepadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	::SHSipPreference(AfxGetMainWnd()->m_hWnd, SIP_UP);
#endif
	CDocument::SetModifiedFlag(FALSE);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadDoc serialization

void CNotepadDoc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}
/////////////////////////////////////////////////////////////////////////////
// CNotepadDoc diagnostics

#ifdef _DEBUG
void CNotepadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNotepadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNotepadDoc commands
