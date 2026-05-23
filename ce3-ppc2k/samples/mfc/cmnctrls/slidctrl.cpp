// SlidCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ctrldemo.h"
#include "SlidCtrl.h"
#include "sliddlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSliderCtrlDlg * g_pSlidCtrlDlg=NULL;
/////////////////////////////////////////////////////////////////////////////
// CSliderCtrlPage property page

IMPLEMENT_DYNCREATE(CSliderCtrlPage, CPropertyPage)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSliderCtrlPage::CSliderCtrlPage() : CPropertyPage(CSliderCtrlPage::IDD)
{
	//{{AFX_DATA_INIT(CSliderCtrlPage)
	m_bAutoticks = TRUE;
	m_bEnablesel = FALSE;
	m_bFixed = FALSE;
	m_uiLine = 10;
	m_bNothumb = FALSE;
	m_bNoticks = FALSE;
	m_iOrientation = 0;
	m_uiPage = 50;
	m_iTickpos = 0;
	m_uiRangeFrom = 0;
	m_uiRangeTo = 100;
	m_uiSelRangeFrom = 20;
	m_uiSelRangeTo = 80;
	m_uiTickFreq = 20;
	//}}AFX_DATA_INIT
}

CSliderCtrlPage::~CSliderCtrlPage()
{
}

void CSliderCtrlPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSliderCtrlPage)
	DDX_Control(pDX, IDC_NOTIFICATIONS, m_Notifications);
	DDX_Text(pDX, IDC_SLIDER_LINE, m_uiLine);
	DDV_MinMaxUInt(pDX, m_uiLine, 0, 65535);
	DDX_Text(pDX, IDC_SLIDER_PAGE, m_uiPage);
	DDV_MinMaxUInt(pDX, m_uiPage, 0, 65535);
	DDX_Text(pDX, IDC_SLIDER_RANGEFROM, m_uiRangeFrom);
	DDV_MinMaxUInt(pDX, m_uiRangeFrom, 0, 65535);
	DDX_Text(pDX, IDC_SLIDER_RANGETO, m_uiRangeTo);
	DDV_MinMaxUInt(pDX, m_uiRangeTo, 0, 65535);
	DDX_Text(pDX, IDC_SLIDER_SELRANGEFROM, m_uiSelRangeFrom);
	DDV_MinMaxUInt(pDX, m_uiSelRangeFrom, 0, 65535);
	DDX_Text(pDX, IDC_SLIDER_SELRANGETO, m_uiSelRangeTo);
	DDV_MinMaxUInt(pDX, m_uiSelRangeTo, 0, 65535);
	DDX_Text(pDX, IDC_SLIDER_TICKFREQ, m_uiTickFreq);
	DDV_MinMaxUInt(pDX, m_uiTickFreq, 0, 65535);
	//}}AFX_DATA_MAP
}

BOOL CSliderCtrlPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Initially create slider control in horizontal position
	CWnd* pWnd =
		GetDlgItem( IDC_SLIDER_HORZPOS );
	CRect rect;
	pWnd->GetWindowRect( &rect );
	ScreenToClient( &rect );

	// Initialise controls
	m_Slider.Create( WS_VISIBLE|WS_CHILD|TBS_HORZ|TBS_BOTH|TBS_AUTOTICKS|WS_TABSTOP,
					 rect, this, IDC_SLIDER );
	m_Slider.SetTicFreq( m_uiTickFreq );	// Send TBM_SETTICFREQ
	m_Slider.SetLineSize( m_uiLine );		// Send TBM_SETLINESIZE
	m_Slider.SetPageSize( m_uiPage );		// Send TBM_SETPAGESIZE
	m_Slider.SetRange( m_uiRangeFrom, m_uiRangeTo, TRUE );
											// Send TBM_SETRANGE
	return TRUE;
}

void CSliderCtrlPage::ChangeCtrlStyle( long lStyle, BOOL bSetBit)
{
	long	lStyleOld;

	lStyleOld = GetWindowLong( m_Slider.GetSafeHwnd(), GWL_STYLE );
	if ( bSetBit )
		lStyleOld |= lStyle;
	else
		lStyleOld &= ~lStyle;
	SetWindowLong( m_Slider.GetSafeHwnd(), GWL_STYLE, lStyleOld );
	m_Slider.SetWindowPos( NULL, 0, 0, 0, 0, SWP_DRAWFRAME|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER );
}

BEGIN_MESSAGE_MAP(CSliderCtrlPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSliderCtrlPage)
	ON_EN_KILLFOCUS(IDC_SLIDER_TICKFREQ, OnTickfreq)
	ON_EN_KILLFOCUS(IDC_SLIDER_LINE, OnLine)
	ON_EN_KILLFOCUS(IDC_SLIDER_PAGE, OnPage)
	ON_EN_KILLFOCUS(IDC_SLIDER_RANGEFROM, OnRangefrom)
	ON_EN_KILLFOCUS(IDC_SLIDER_RANGETO, OnRangeto)
	ON_EN_KILLFOCUS(IDC_SLIDER_SELRANGEFROM, OnSelrangefrom)
	ON_EN_KILLFOCUS(IDC_SLIDER_SELRANGETO, OnSelrangeto)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	//	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliderCtrlPage message handlers

void CSliderCtrlPage::OnTickfreq() 
{
	UpdateData();
	if ( m_bAutoticks )
		// Set tick marks at given frequency (1 = tick at every increment)
		m_Slider.SetTicFreq( m_uiTickFreq );	// Send TBM_SETTICFREQ - need TBS_AUTOTICKS
	m_Slider.InvalidateRect(NULL,FALSE);
}

void CSliderCtrlPage::OnLine() 
{
	UpdateData();

	// Set line size (determines effect of arrow keys)
	if (m_uiLine > (m_uiRangeTo-m_uiRangeFrom))
	{
		m_uiLine = m_uiRangeTo-m_uiRangeFrom;
		UpdateData(FALSE);
	}

	m_Slider.SetLineSize( m_uiLine );		// Send TBM_SETLINESIZE
	m_Slider.InvalidateRect(NULL,FALSE);
}

void CSliderCtrlPage::OnPage() 
{
	UpdateData();

	// Set page size (determines effect of PageUp/PageDown keys)
	if (m_uiPage > (m_uiRangeTo-m_uiRangeFrom))
	{
		m_uiPage = m_uiRangeTo-m_uiRangeFrom;
		UpdateData(FALSE);
	}
	m_Slider.SetPageSize( m_uiPage );		// Send TBM_SETPAGESIZE
	m_Slider.InvalidateRect(NULL,FALSE);
}

void CSliderCtrlPage::OnRangefrom() 
{
	resetSliderRange();
}

void CSliderCtrlPage::OnRangeto() 
{
	resetSliderRange();
}

void CSliderCtrlPage::OnSelrangefrom() 
{
	resetSliderRange();
}

void CSliderCtrlPage::OnSelrangeto() 
{
	resetSliderRange();
}

void CSliderCtrlPage::OnMore() 
{	
	g_pSlidCtrlDlg = new CSliderCtrlDlg;

	g_pSlidCtrlDlg->m_bAutoticks = m_bAutoticks;
	g_pSlidCtrlDlg->m_bEnablesel = m_bEnablesel;
	g_pSlidCtrlDlg->m_bFixed = m_bFixed;
	g_pSlidCtrlDlg->m_bNothumb = m_bNothumb;
	g_pSlidCtrlDlg->m_bNoticks = m_bNoticks;
	g_pSlidCtrlDlg->m_iOrientation = m_iOrientation;
	g_pSlidCtrlDlg->m_iTickpos = m_iTickpos;

	if(g_pSlidCtrlDlg->DoModal() == IDOK)
	{
		m_bAutoticks = g_pSlidCtrlDlg->m_bAutoticks;
		m_bEnablesel = g_pSlidCtrlDlg->m_bEnablesel;
		m_bFixed = g_pSlidCtrlDlg->m_bFixed;
		m_bNothumb = g_pSlidCtrlDlg->m_bNothumb;
		m_bNoticks = g_pSlidCtrlDlg->m_bNoticks;
		m_iOrientation = g_pSlidCtrlDlg->m_iOrientation;
		m_iTickpos = g_pSlidCtrlDlg->m_iTickpos;
		SetSliderCtrlStyle();
	}

	delete g_pSlidCtrlDlg;
	g_pSlidCtrlDlg=NULL;
}
 
 
void CSliderCtrlPage::SetSliderCtrlStyle()
{	
	long lStyle = 0;
	long lMask = TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_FIXEDLENGTH |
		         TBS_NOTHUMB | TBS_NOTICKS | TBS_VERT | TBS_HORZ |
				 TBS_BOTH | TBS_TOP | TBS_BOTTOM;

	// Set boolean styles
	if(m_bAutoticks)
		lStyle |= TBS_AUTOTICKS;
	if(m_bEnablesel)
		lStyle |= TBS_ENABLESELRANGE;
	if(m_bFixed)
		lStyle |= TBS_FIXEDLENGTH;
	if(m_bNothumb)
		lStyle |= TBS_NOTHUMB;
	if(m_bNoticks)
		lStyle |= TBS_NOTICKS;
	if(m_iOrientation) 
		lStyle |= TBS_VERT;
	else 
		lStyle |= TBS_HORZ;
	switch ( m_iTickpos )
	{
	case 0:
		lStyle |= TBS_BOTH;
		break;
	case 1:
		lStyle |= TBS_TOP;
		break;
	case 2:
		lStyle |= TBS_BOTTOM;
		break;
	default:
		break;
	}

	long lNewStyle = GetWindowLong( m_Slider.GetSafeHwnd(), GWL_STYLE );
	lNewStyle &= ~lMask; 
	lNewStyle = lNewStyle | lStyle;
	SetWindowLong( m_Slider.GetSafeHwnd(), GWL_STYLE, lNewStyle );
	m_Slider.SetWindowPos( NULL, 0, 0, 0, 0, SWP_DRAWFRAME|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER );

	if ( m_bAutoticks ) {
		// Set tick marks with given frequency (1 = tick at every increment)
		m_Slider.SetTicFreq( m_uiTickFreq );	// Send TBM_SETTICFREQ - need TBS_AUTOTICKS
		m_Slider.InvalidateRect(NULL,FALSE);
	}
	else
		// Clear tick marks
		m_Slider.ClearTics( TRUE );
	if ( m_bEnablesel ) {
		// Set selection range
		m_Slider.SetSelection( m_uiSelRangeFrom, m_uiSelRangeTo );	// Send TBM_SETSEL
		m_Slider.InvalidateRect(NULL,FALSE);	
	}
	else
		// Clear selection range
		m_Slider.ClearSel( TRUE );

	// Enable/disable edit controls
	GetDlgItem( IDC_SLIDER_TICKFREQ )->EnableWindow( m_bAutoticks );
	GetDlgItem( IDC_SLIDER_SELRANGEFROM )->EnableWindow( m_bEnablesel );
	GetDlgItem( IDC_SLIDER_SELRANGETO )->EnableWindow( m_bEnablesel );
	GetDlgItem( IDC_SELRANGE_STATIC )->EnableWindow( m_bEnablesel );

	// Obtain horz/vert place marker (static control)
	CWnd* pWnd =
		GetDlgItem( (0==m_iOrientation)?IDC_SLIDER_HORZPOS:IDC_SLIDER_VERTPOS );
	CRect rect;
	pWnd->GetWindowRect( &rect );
	ScreenToClient( &rect );
	// Move control to horz/vert position
	m_Slider.SetWindowPos( NULL,
						   rect.left, rect.top,
						   rect.Width(), rect.Height(),
						   SWP_NOZORDER|SWP_SHOWWINDOW );
	Invalidate();
}

void CSliderCtrlPage::resetSliderRange()
{
	int nChanged = 0;
	UpdateData();
	
	if (m_uiRangeFrom > m_uiRangeTo) 
	{
		SWAP(m_uiRangeFrom, m_uiRangeTo);
		nChanged++;
	}
	if (m_uiSelRangeFrom > m_uiSelRangeTo) 
	{
		SWAP(m_uiSelRangeFrom, m_uiSelRangeTo);
		nChanged++;
	}
	if (m_uiSelRangeFrom < m_uiRangeFrom)
	{
		m_uiSelRangeFrom = m_uiRangeFrom;
		nChanged++;
	}
	if (m_uiSelRangeTo > m_uiRangeTo)
	{
		m_uiSelRangeTo = m_uiRangeTo;
		nChanged++;
	}
	if (nChanged > 0)
		UpdateData(FALSE);

	m_Slider.SetRangeMin( m_uiRangeFrom, TRUE );	            // Send TBM_SETRANGE
	m_Slider.SetRangeMax( m_uiRangeTo, TRUE );	                // Send TBM_SETRANGE
	m_Slider.SetSelection( m_uiSelRangeFrom, m_uiSelRangeTo );	// Send TBM_SETSEL
	m_Slider.SetSelection( m_uiSelRangeFrom, m_uiSelRangeTo );	// Send TBM_SETSEL
	m_Slider.InvalidateRect(NULL,FALSE);
}
