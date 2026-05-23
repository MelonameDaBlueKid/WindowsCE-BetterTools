// EventsDlg.h : Declaration of the CEventsDlg

#ifndef __EVENTSDLG_H_
#define __EVENTSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEventsDlg
class CEventsDlg : public CDialogImpl<CEventsDlg>
{
public:
	CEventsDlg();
	~CEventsDlg();

	enum { IDD = IDD_EVENTSDLG };

   BEGIN_MSG_MAP(CEventsDlg)
	   MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	   COMMAND_ID_HANDLER(IDOK, OnOK)
   END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

   void AddEventToList(BSTR pszEvent);

private:
   HWND m_hwndEventsLst;
   int  m_nHorizExtent;
};

#endif //__EVENTSDLG_H_
