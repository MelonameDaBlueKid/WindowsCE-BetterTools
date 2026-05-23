// MathsPpg.cpp : Implementation of the CMaths1PropPage property page class.

#include "stdafx.h"
#include "Maths1.h"
#include "mathsppg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMaths1PropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMaths1PropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMaths1PropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMaths1PropPage, "MATHS.Maths1PropPage.1",
	0x183cb004, 0xbeed, 0x11ce, 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf)


/////////////////////////////////////////////////////////////////////////////
// CMaths1PropPage::CMaths1PropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMaths1PropPage

BOOL CMaths1PropPage::CMaths1PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_Maths1_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1PropPage::CMaths1PropPage - Constructor

CMaths1PropPage::CMaths1PropPage() :
	COlePropertyPage(IDD, IDS_Maths1_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMaths1PropPage)
	m_bOpposite = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1PropPage::DoDataExchange - Moves data between page and properties

void CMaths1PropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMaths1PropPage)
	DDP_Check(pDX, IDC_CHECK1, m_bOpposite, _T("Opposite") );
	DDX_Check(pDX, IDC_CHECK1, m_bOpposite);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1PropPage message handlers
