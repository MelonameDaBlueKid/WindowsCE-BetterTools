/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

#define WM_REG_NOTIFICATION             ( WM_USER + 100 )
#define WM_DATA_CHANGED                 ( WM_USER + 101 )

class CStocks
{
public:
    CStocks( HWND hwndMain, HWND hwndLv );
    ~CStocks();

    BOOL SetupDlg( HWND hDlg, UINT uParam );
    BOOL Open( LPTSTR lpszFile, BOOL fFailOnNew );
    BOOL Add( HWND hDlg );
    BOOL Change( HWND hDlg, UINT uParam );
    void SyncNow( void );
    void Delete( UINT uParam );
    BOOL BeforeAddChg( void );
    void OnDataChange( void );
    void FillDetails(HWND hDlg, CEOID oid);

private:
    void    Close( void );
    void    UpdateView( void );
    BOOL    DoAddChg( HWND hDlg, CEOID oid );
    int     ShowMsg( LPTSTR lpszText, int iLastErr = -1, UINT uFlags = 0 );
    void    SetViewItemText( UINT ix, CEPROPVAL *rgProps, UINT cProps );
    void    AddItem( CEOID oid, CEPROPVAL *rgProps, UINT cProps );

    HWND    m_hwndMain, m_hwndLv, m_hwndNotify;
    CEOID   m_oidDatabase;
    HANDLE  m_hDatabase;
};
