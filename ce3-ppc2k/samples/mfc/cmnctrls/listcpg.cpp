// ListCtrlPage.cpp : implementation file
//

#include "stdafx.h"
#include "ctrldemo.h"
#include "listcpg.h"
#include "listdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListCtrlDlg * g_listCtrlDlg=NULL;

#define CELEMS(rgFoo) (sizeof(rgFoo) / sizeof(rgFoo[0]))

/////////////////////////////////////////////////////////////////////////////
// CListCtrlPage property page

IMPLEMENT_DYNCREATE(CListCtrlPage, CPropertyPage)

CListCtrlPage::CListCtrlPage() : CPropertyPage(CListCtrlPage::IDD)
{
	//{{AFX_DATA_INIT(CListCtrlPage)
	m_cstrStatus      = _T("");
	m_bSingleSel      = FALSE;
	m_bEditLabels     = FALSE;
	m_bNoLabelWrap    = FALSE;
	m_bNoColumnHeader = FALSE;
	m_bNoSortHeader   = FALSE;
	m_cstrViewMode.LoadString(IDS_REPORT);
	m_cstrSort.LoadString(IDS_NONE);
	m_cstrAlignMode.LoadString(IDS_TOP);
	//}}AFX_DATA_INIT

	m_pimagelist = NULL;
	m_pimagelistSmall = NULL;
}

CListCtrlPage::~CListCtrlPage()
{
	delete m_pimagelist;
	delete m_pimagelistSmall;
}


void CListCtrlPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlPage)
	DDX_Control(pDX, IDC_LISTVIEW1, m_listctrl);
	DDX_Text(pDX, IDC_STATUS, m_cstrStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListCtrlPage, CPropertyPage)
	//{{AFX_MSG_MAP(CListCtrlPage)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LISTVIEW1, ShowNotification)
	ON_NOTIFY(LVN_SETDISPINFO, IDC_LISTVIEW1, ShowNotification)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CListCtrlPage::FillListCtrl()
{
	CRect			rect;
	int				i, iIcon, iItem, iSubItem, iActualItem;
	LV_ITEM			lvitem;
	LV_COLUMN		lvcolumn;
	TCHAR			rgtsz[2][10];
	CCtrldemoApp	*pApp;
	TCHAR			rgtszIconDescrip[LISTICONCOUNT][50], rgtszIconShortDesc[LISTICONCOUNT][12];

	ASSERT(LISTICONCOUNT == 4);
	_tcscpy(rgtsz[0], (LPCTSTR)CString((LPCTSTR)IDS_MAINITEM));
	_tcscpy(rgtsz[1], (LPCTSTR)CString((LPCTSTR)IDS_SUBITEM));

	_tcscpy(rgtszIconDescrip[0], (LPCTSTR)CString((LPCTSTR)IDS_ICONDSP1));
	_tcscpy(rgtszIconDescrip[1], (LPCTSTR)CString((LPCTSTR)IDS_ICONDSP2));
	_tcscpy(rgtszIconDescrip[2], (LPCTSTR)CString((LPCTSTR)IDS_ICONDSP3));
	_tcscpy(rgtszIconDescrip[3], (LPCTSTR)CString((LPCTSTR)IDS_ICONDSP4));

	_tcscpy(rgtszIconShortDesc[0], (LPCTSTR)CString((LPCTSTR)IDS_ICONSHORT1));
	_tcscpy(rgtszIconShortDesc[1], (LPCTSTR)CString((LPCTSTR)IDS_ICONSHORT2));
	_tcscpy(rgtszIconShortDesc[2], (LPCTSTR)CString((LPCTSTR)IDS_ICONSHORT3));
	_tcscpy(rgtszIconShortDesc[3], (LPCTSTR)CString((LPCTSTR)IDS_ICONSHORT4));


	pApp = (CCtrldemoApp *)AfxGetApp();
	m_listctrl.SetImageList(m_pimagelist, LVSIL_NORMAL);
	m_listctrl.SetImageList(m_pimagelistSmall, LVSIL_SMALL);
	m_listctrl.GetWindowRect(&rect);

	for (i = 0; i < 2; i++)  // add the columns to the list control
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = rgtsz[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = rect.Width() * (i + 1) / 3;  // SubItem is twice as large
		m_listctrl.InsertColumn(i, &lvcolumn);  // assumes return value is OK.
	}

	for (iItem = 0; iItem < 50; iItem++)  // will now insert the items and subitems into the list view.
		for (iSubItem = 0; iSubItem < 2; iSubItem++)
		{
			if (iSubItem == 0)
				iIcon = Random() % 4;  // choose the icon and legend for the entry

			lvitem.mask = LVIF_TEXT | (iSubItem == 0? LVIF_IMAGE : 0);
			lvitem.iItem = (iSubItem == 0)? iItem : iActualItem;
			lvitem.iSubItem = iSubItem;
			lvitem.pszText = iSubItem == 0? rgtszIconShortDesc[iIcon] : rgtszIconDescrip[iIcon];

			lvitem.iImage = iIcon;
			if (iSubItem == 0)
				iActualItem = m_listctrl.InsertItem(&lvitem);
			else
				m_listctrl.SetItem(&lvitem);
		}
}


BOOL CListCtrlPage::OnInitDialog()
{
	CCtrldemoApp	*pApp;
	CRect			rect;

	CPropertyPage::OnInitDialog();  // let the base class do the default work
	pApp = (CCtrldemoApp *)AfxGetApp();
	m_pimagelist = new CImageList();		
	m_pimagelistSmall = new CImageList();
	ASSERT(m_pimagelist != NULL && m_pimagelistSmall != NULL);    // no serious allocation failure checking
	m_pimagelist->Create(32, 32, TRUE/*bMask*/,	LISTICONCOUNT/*nInitial*/, 4/*nGrow*/);
	m_pimagelistSmall->Create(16, 16, TRUE/*bMask*/, LISTICONCOUNT, 4);
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST1));
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST2));
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST3));
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST4));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST1));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST2));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST3));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST4));

	SetListControlStyle();
	return FALSE;  // there is no change in any control focus stuff here.
}

void CListCtrlPage::ShowNotification(LPNMHDR pnmhdr, LRESULT *pResult)
{
	((CNotifyShowCase *)GetDlgItem(IDC_LISTSTATUS))->ShowNotification(pnmhdr->code);
}

void CListCtrlPage::OnMore() 
{
	g_listCtrlDlg = new CListCtrlDlg;

	g_listCtrlDlg->m_bSingleSel      = m_bSingleSel;
	g_listCtrlDlg->m_bEditLabels     = m_bEditLabels;
	g_listCtrlDlg->m_bNoLabelWrap    = m_bNoLabelWrap;
	g_listCtrlDlg->m_bNoColumnHeader = m_bNoColumnHeader;
	g_listCtrlDlg->m_bNoSortHeader   = m_bNoSortHeader;
	g_listCtrlDlg->m_cstrViewMode    = m_cstrViewMode;
	g_listCtrlDlg->m_cstrSort        = m_cstrSort;
	g_listCtrlDlg->m_cstrAlignMode   = m_cstrAlignMode;

	if(g_listCtrlDlg->DoModal() == IDOK)
	{
		m_bSingleSel      = g_listCtrlDlg->m_bSingleSel;
		m_bEditLabels     = g_listCtrlDlg->m_bEditLabels;
		m_bNoLabelWrap    = g_listCtrlDlg->m_bNoLabelWrap;
		m_bNoColumnHeader = g_listCtrlDlg->m_bNoColumnHeader;
		m_bNoSortHeader   = g_listCtrlDlg->m_bNoSortHeader;
		m_cstrViewMode    = g_listCtrlDlg->m_cstrViewMode;
		m_cstrSort        = g_listCtrlDlg->m_cstrSort;
		m_cstrAlignMode   = g_listCtrlDlg->m_cstrAlignMode;
		SetListControlStyle();
	}

	delete g_listCtrlDlg;
	g_listCtrlDlg=NULL;
}
 
 
void CListCtrlPage::SetListControlStyle()
{	
	long lStyle = 0;
	long lMask = LVS_SINGLESEL | LVS_EDITLABELS |
	             LVS_NOLABELWRAP | LVS_NOCOLUMNHEADER | LVS_NOSORTHEADER |
	             LVS_ICON | LVS_SMALLICON | LVS_REPORT | LVS_LIST |
	             LVS_SORTASCENDING | LVS_SORTDESCENDING | LVS_ALIGNLEFT;
				
	// Set boolean styles
	if(m_bSingleSel)
		lStyle |= LVS_SINGLESEL;
	if(m_bEditLabels)
		lStyle |= LVS_EDITLABELS;
	if(m_bNoLabelWrap)
		lStyle |= LVS_NOLABELWRAP;
	if(m_bNoColumnHeader)
		lStyle |= LVS_NOCOLUMNHEADER;
	if(m_bNoSortHeader)
		lStyle |= LVS_NOSORTHEADER;

	// Set list type style
	if (m_cstrViewMode == CString((LPCTSTR)IDS_ICON))
		lStyle |= LVS_ICON;
	else if (m_cstrViewMode == CString((LPCTSTR)IDS_SMALLICON))
		lStyle |= LVS_SMALLICON;
	else if (m_cstrViewMode == CString((LPCTSTR)IDS_REPORT))
		lStyle |= LVS_REPORT;
	else
	{
		ASSERT(m_cstrViewMode == CString((LPCTSTR)IDS_LIST));
		lStyle |= LVS_LIST;
	}

	// Set sort style
	if (m_cstrSort == CString((LPCTSTR)IDS_ASCENDING))
		lStyle |= LVS_SORTASCENDING;
	else if (m_cstrSort == CString((LPCTSTR)IDS_DESCENDING))
		lStyle |= LVS_SORTDESCENDING;
	else
		ASSERT(m_cstrSort == CString((LPCTSTR)IDS_NONE));

	// Set alignment style
	if (m_cstrAlignMode == CString((LPCTSTR)IDS_LEFT))
		lStyle |= LVS_ALIGNLEFT;
	else
		ASSERT(m_cstrAlignMode == CString((LPCTSTR)IDS_TOP));

	// Calculate new style
	long lNewStyle = GetWindowLong(m_listctrl.m_hWnd, GWL_STYLE);
	lNewStyle &= ~lMask; // turn off all LVS bits
	lNewStyle = lNewStyle | lStyle;

	// Create new list control
	CRect rect;
	m_listctrl.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_listctrl.DestroyWindow();
	m_listctrl.Create(lNewStyle, rect, this, IDC_LISTVIEW1);
	m_listctrl.SetImageList(m_pimagelist, LVSIL_NORMAL);
	m_listctrl.SetImageList(m_pimagelistSmall, LVSIL_SMALL);

	// Fill up the list control
	FillListCtrl();
}
