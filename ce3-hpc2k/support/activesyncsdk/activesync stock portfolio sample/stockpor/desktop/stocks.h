/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/*++

Module Name:
    
      stocks.h

Abstract:

    Defines CStocks class

--*/
class CStocks
{
public:
    CStocks( HWND hwndMain, HWND hwndLv );
    ~CStocks();

    BOOL SetupDlg( HWND hDlg, UINT uParam );
    BOOL Open( LPSTR lpszFile, BOOL fFailOnNew );
    BOOL Add( HWND hDlg );
    BOOL Change( HWND hDlg, UINT uParam );
    void Delete( UINT uParam );
    void SyncNow( void );
    BOOL BeforeAddChg( void );
    void OnDataChange( void );

private:
    PSTOCK          FindStock( UINT uStockId, PUINT puix = NULL );
    void            UpdateView( void );
    void            SetViewItemText( UINT ix, PSTOCK pStock );
    void            AddItem( PSTOCK pStock );
    void            Close( void );

    HWND            m_hwndMain, m_hwndLv;
    char            m_szFile[ MAX_PATH ];
    HANDLE          m_hFile, m_hMapObj, m_hMutex;
    PPORTFILE       m_pStocks;
    HANDLE          m_hChgEvent;
};