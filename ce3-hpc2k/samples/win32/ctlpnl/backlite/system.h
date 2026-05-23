//*******************************************************************************************
//
// Filename : system.h
//	
// Copyright (c) 1997 Microsoft Corporation. All rights reserved
//
//*******************************************************************************************

extern HINSTANCE g_hinst;
extern HWND hwndMain;
extern HWND hwndGeneral, hwndSystem;
extern HWND hwndTabDlg;
extern HWND hwndTab;
extern int CurrApplet;

BOOL APIENTRY SystemDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);
BOOL APIENTRY GeneralDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam);
BOOL APIENTRY TabDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);
void SetTabControl(void);
void DisplayTabDialog(int i);
void TabNotify(HWND hDlg, UINT message, UINT wParam, LONG lParam);
BOOL IsTabDialogMessage(HWND hwndTabDlg, LPMSG msg);
HRESULT SaveToRegsitry(void);
void  MsgToDialogs(UINT msg, WPARAM wp, LPARAM lp);

#define NUM_APPLETS (sizeof(SystemApplets)/sizeof(SystemApplets[0]))


#ifdef DEBUG_MSGS
extern TCHAR 	szDPF[];    // debug printouts

#define	DPF(x)	OutputDebugString(TEXT(x))
#define	DPF1(x,y)	{ \
					wsprintf(szDPF, TEXT(x), y); \
					OutputDebugString(szDPF);	 \
					}

#define	DPF2(x,y,z) { \
					wsprintf(szDPF, TEXT(x), y,z); \
					OutputDebugString(szDPF);	 \
					}

#define	DPF3(x,y,z,w) { \
					wsprintf(szDPF, TEXT(x), y,z,w); \
					OutputDebugString(szDPF);	 \
					}
#else
#define	DPF(x)	
#define	DPF1(x,y)
#define	DPF2(x,y,z)
#define	DPF3(x,y,z,w)
#endif

