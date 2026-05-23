// MathsPpg.cpp : Implementation of the CMaths3PropPage property page class.

#include "stdafx.h"
#include "Maths3.h"
#include "mathsppg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMaths3PropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMaths3PropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMaths3PropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMaths3PropPage, "MATHS.Maths3PropPage.1",
	0x182cb004, 0xbeed, 0x11ce, 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf)


/////////////////////////////////////////////////////////////////////////////
// CMaths3PropPage::CMaths3PropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMaths3PropPage

BOOL CMaths3PropPage::CMaths3PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_Maths3_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths3PropPage::CMaths3PropPage - Constructor

CMaths3PropPage::CMaths3PropPage() :
	COlePropertyPage(IDD, IDS_Maths3_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMaths3PropPage)
	m_bOpposite = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMaths3PropPage::DoDataExchange - Moves data between page and properties

void CMaths3PropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMaths3PropPage)
	DDP_Check(pDX, IDC_CHECK1, m_bOpposite, _T("Opposite") );
	DDX_Check(pDX, IDC_CHECK1, m_bOpposite);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths3PropPage message handlers
