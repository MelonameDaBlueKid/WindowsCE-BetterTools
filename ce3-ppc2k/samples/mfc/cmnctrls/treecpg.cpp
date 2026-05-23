// TreeCtrlPage.cpp : implementation file
//

#include "stdafx.h"
#include "ctrldemo.h"
#include "treecpg.h"
#include "mtreectl.h"
#include "treedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTreeCtrlDlg * g_ptreeCtrlDlg=NULL;
/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlPage property page

IMPLEMENT_DYNCREATE(CTreeCtrlPage, CPropertyPage)

CTreeCtrlPage::CTreeCtrlPage() : CPropertyPage(CTreeCtrlPage::IDD)
{
	//{{AFX_DATA_INIT(CTreeCtrlPage)
	m_bDisableDragDrop = FALSE;
	m_bHasButtons = FALSE;
	m_bHasLines = FALSE;
	m_bLinesAtRoot = FALSE;
	m_bEditLabels = FALSE;
	m_bShowSelAlways = FALSE;
	m_cstrStatus = _T("");
	//}}AFX_DATA_INIT
}

CTreeCtrlPage::~CTreeCtrlPage()
{
}

void CTreeCtrlPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeCtrlPage)
	DDX_Control(pDX, IDC_TREESTATUS, m_notifshowcase);
	DDX_Control(pDX, IDC_TREEVIEW1, m_mytreectrl);
	DDX_Text(pDX, IDC_TREESTATUS, m_cstrStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeCtrlPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTreeCtrlPage)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_GETDISPINFO, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_SETDISPINFO, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREEVIEW1, ShowNotification)
	ON_NOTIFY(TVN_DELETEITEM, IDC_TREEVIEW1, ShowNotification)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlPage message handlers
BOOL CTreeCtrlPage::OnInitDialog()
{
	CImageList			*pimagelist;
	CBitmap				bitmap;
	CCtrldemoApp		*pApp;
	int					iItem;
	UINT				nID;
	TV_INSERTSTRUCT		tvstruct;
	TCHAR				rgszItems[12][18];
	
	_tcscpy(rgszItems[0], (LPCTSTR)CString((LPCTSTR)IDS_DOGS));
	_tcscpy(rgszItems[1], (LPCTSTR)CString((LPCTSTR)IDS_SHEPHERD));
	_tcscpy(rgszItems[2], (LPCTSTR)CString((LPCTSTR)IDS_DALMATIAN));
	_tcscpy(rgszItems[3], (LPCTSTR)CString((LPCTSTR)IDS_DANE));

	_tcscpy(rgszItems[4], (LPCTSTR)CString((LPCTSTR)IDS_BIRDS));
	_tcscpy(rgszItems[5], (LPCTSTR)CString((LPCTSTR)IDS_HUMMINGBIRD));
	_tcscpy(rgszItems[6], (LPCTSTR)CString((LPCTSTR)IDS_PIGEON));
	_tcscpy(rgszItems[7], (LPCTSTR)CString((LPCTSTR)IDS_EAGLE));

	_tcscpy(rgszItems[8], (LPCTSTR)CString((LPCTSTR)IDS_FISH));
	_tcscpy(rgszItems[9], (LPCTSTR)CString((LPCTSTR)IDS_SNAPPER));
	_tcscpy(rgszItems[10], (LPCTSTR)CString((LPCTSTR)IDS_SOLE));
	_tcscpy(rgszItems[11], (LPCTSTR)CString((LPCTSTR)IDS_SALMON));

	pApp = (CCtrldemoApp *)AfxGetApp();
	CPropertyPage::OnInitDialog();  // let the base class do the default work
	pimagelist = new CImageList();
	pimagelist->Create(32, 16, TRUE/*bMask*/, 6, 4);

	for (nID = IDB_BMTREEFIRST; nID <= IDB_BMTREELAST; nID++)  // load bitmaps for dog, bird and fish
	{
		bitmap.LoadBitmap(nID);
		pimagelist->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();
	}

	m_mytreectrl.SetImageList(pimagelist, TVSIL_NORMAL);
	for (iItem = 0; iItem < CELEMS(rgszItems); iItem ++)
	{
		tvstruct.hParent = (iItem % 4 == 0)? NULL : m_rghItem[iItem / 4 * 4];
		tvstruct.hInsertAfter = TVI_SORT;
		tvstruct.item.iImage = iItem / 4 * 2;
		tvstruct.item.iSelectedImage = tvstruct.item.iImage + 1;
		tvstruct.item.pszText = rgszItems[iItem];
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		m_rghItem[iItem] = m_mytreectrl.InsertItem(&tvstruct);
	}

	return FALSE;
}

void CTreeCtrlPage::ShowNotification(LPNMHDR pnmhdr, LRESULT *pResult)
{
	((CNotifyShowCase *)GetDlgItem(IDC_TREESTATUS))->ShowNotification(pnmhdr->code);
}

void CTreeCtrlPage::OnMore() 
{
	g_ptreeCtrlDlg = new CTreeCtrlDlg;

	g_ptreeCtrlDlg->m_bEditLabels = m_bEditLabels;
	g_ptreeCtrlDlg->m_bHasButtons = m_bHasButtons;
	g_ptreeCtrlDlg->m_bHasLines = m_bHasLines;
	g_ptreeCtrlDlg->m_bLinesAtRoot = m_bLinesAtRoot;
	g_ptreeCtrlDlg->m_bDisableDragDrop = m_bDisableDragDrop;
	g_ptreeCtrlDlg->m_bShowSelAlways = m_bShowSelAlways;

	if(g_ptreeCtrlDlg->DoModal() == IDOK)
	{
		m_bEditLabels = g_ptreeCtrlDlg->m_bEditLabels;
		m_bHasButtons = g_ptreeCtrlDlg->m_bHasButtons;
		m_bHasLines = g_ptreeCtrlDlg->m_bHasLines;
		m_bLinesAtRoot = g_ptreeCtrlDlg->m_bLinesAtRoot;
		m_bDisableDragDrop = g_ptreeCtrlDlg->m_bDisableDragDrop;
		m_bShowSelAlways = g_ptreeCtrlDlg->m_bShowSelAlways;
		SetTreeCtrlStyle();
	}
	
	delete g_ptreeCtrlDlg;
	g_ptreeCtrlDlg=NULL;
}

void CTreeCtrlPage::SetTreeCtrlStyle()
{	
	m_mytreectrl.SetNewStyle(TVS_EDITLABELS, m_bEditLabels);
	m_mytreectrl.SetNewStyle(TVS_HASBUTTONS, m_bHasButtons);
	m_mytreectrl.SetNewStyle(TVS_HASLINES, m_bHasLines);
	m_mytreectrl.SetNewStyle(TVS_LINESATROOT, m_bLinesAtRoot);
	m_mytreectrl.SetNewStyle(TVS_DISABLEDRAGDROP, m_bDisableDragDrop);
	m_mytreectrl.SetNewStyle(TVS_SHOWSELALWAYS, m_bShowSelAlways);
}
