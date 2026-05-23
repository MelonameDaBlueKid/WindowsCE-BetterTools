// MathsPpg.cpp : Implementation of the CMaths2PropPage property page class.

#include "stdafx.h"
#include "Maths2.h"
#include "mathsppg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMaths2PropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMaths2PropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMaths2PropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMaths2PropPage, "MATHS.Maths2PropPage.1",
	0x181cb004, 0xbeed, 0x11ce, 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf)


/////////////////////////////////////////////////////////////////////////////
// CMaths2PropPage::CMaths2PropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMaths2PropPage

BOOL CMaths2PropPage::CMaths2PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_Maths2_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2PropPage::CMaths2PropPage - Constructor

CMaths2PropPage::CMaths2PropPage() :
	COlePropertyPage(IDD, IDS_Maths2_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMaths2PropPage)
	m_bOpposite = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2PropPage::DoDataExchange - Moves data between page and properties

void CMaths2PropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMaths2PropPage)
	DDP_Check(pDX, IDC_CHECK1, m_bOpposite, _T("Opposite") );
	DDX_Check(pDX, IDC_CHECK1, m_bOpposite);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2PropPage message handlers
