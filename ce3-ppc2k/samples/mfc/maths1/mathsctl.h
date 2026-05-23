// Maths1Ctl.h : Declaration of the CMaths1Ctrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctl : See MathsCtl.cpp for implementation.

class CMaths1Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CMaths1Ctrl)

// Constructor
public:
	CMaths1Ctrl();


// Attributes
protected:

// Overrides
public:
	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CMaths1Ctrl();

	// Hit Testing Helper
	BOOL InEllipse(const CPoint& pt, int x1, int y1, int x2, int y2);


	DECLARE_OLECREATE_EX(CMaths1Ctrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMaths1Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMaths1Ctrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMaths1Ctrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMaths1Ctrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMaths1Ctrl)
	BOOL m_bOpposite;
	afx_msg void OnOppositeChanged();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMaths1Ctrl)
	void FireOutside()
		{FireEvent(eventidOutside,EVENT_PARAM(VTS_NONE));}
	void FireInside(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
		{FireEvent(eventidInside,EVENT_PARAM(VTS_XPOS_PIXELS  VTS_YPOS_PIXELS), x, y);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMaths1Ctrl)
	dispidOpposite = 1L,
	eventidOutside = 1L,
	eventidInside = 2L,
	//}}AFX_DISP_ID
	};
};
