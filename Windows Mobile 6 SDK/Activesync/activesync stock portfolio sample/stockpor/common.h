/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/
#define Dim( s )                ( sizeof( s ) / sizeof( (s)[0] ) )
#define ClearStruct( s )        memset( &(s), 0, sizeof( s ) );

// special Window messages
#define WM_DATA_CHANGED         ( WM_USER + 101 )

#define SZ_STOCKPOR     TEXT( "StockPor" )
#define SZ_WND_CLASS    TEXT( "StockPortSample" )
#define SZ_REG_ROOT     TEXT( "Software\\Microsoft\\Stock Portfolio" )

// Common values shared by the app and the sync module
#ifdef UNDER_CE

extern LPTSTR   v_lpszDBVol;

    #define DBTYPE_STOCKPOR         21238
    #define SZ_DEFAULT_PORTFILE     TEXT( "\\StockPor.DB" )
    #define SZ_REG_DBVOL            TEXT( "DBVol" )

    // bit mask used in the flag field of each stock record
    #define SF_CHANGED1     ((UINT)0x00000001)  // change to record hasn't be sync'ed with first PC partner, must be valued at 1
    #define SF_CHANGED2     ((UINT)0x00000002)  // change to record hasn't be sync'ed with second PC partner, must be valued at 2
    #define SF_CHG_IN_SYNC  ((UINT)0x00000004)  // this object is changed again during sync
    #define SF_UPDATE_VIEW  ((UINT)0x00000008)

    #define PROP_TAG( ulPropType, ulPropID )    ((((ULONG)(ulPropID))<<16)|((ULONG)(ulPropType)))
    #define PROP_TYPE(ulPropTag)                (((ULONG)(ulPropTag))&0x0000FFFF)

    // property tags used in the stock record
    #define HHPR_FLAGS      PROP_TAG( CEVT_UI2,        0x8200 )
    #define HHPR_SYMBOL     PROP_TAG( CEVT_LPWSTR,     0x8201 )
    #define HHPR_COMPANY    PROP_TAG( CEVT_LPWSTR,     0x8202 )
    #define HHPR_PRICE      PROP_TAG( CEVT_LPWSTR,     0x8203 )
    #define HHPR_PUR_DATE   PROP_TAG( CEVT_LPWSTR,     0x8204 )
    #define HHPR_PUR_PRICE  PROP_TAG( CEVT_LPWSTR,     0x8205 )
    #define HHPR_GAIN_LOSS  PROP_TAG( CEVT_LPWSTR,     0x8206 )
    #define HHPR_UP_TIME    PROP_TAG( CEVT_FILETIME,   0x8207 )
#else
    #define PORTFILE_VERSION        0x324FE323
    #define MAX_STOCKS              500             // support up to 500 stocks in the portfolio
    #define MUTEX_TIMEOUT           5000
    #define SZ_MUTEX                "StockPortMutex"
    #define SZ_CHANGE_EVENT         "StockPorChange"
    #define SZ_DEFAULT_PORTFILE     "\\demo.por"
    #define SZ_STORE_PROG_ID        "MS.WinCE.StockPor2"

    #define SF_IN_VIEW      ((UINT)0x00000001)

    // structure to store each stock's information
    typedef struct tagStock
    {
        UINT        uidStock;           // the stock id
        UINT        uFlags;             // see SF_* above
        FILETIME    ftViewTime;         // time stamp of the item showed in the list view
        FILETIME    ftUpdated;          // updated time of the stock
        FILETIME    ftLastModified;     // last modification time of this stock
        char        szSym[ 10 ];
        char        szCompany[ 80 ];
        char        szLastPrice[ 20 ];
        char        szPurDate[ 20 ];
        char        szPurPrice[ 20 ];
        char        szGain[ 20 ];
    } STOCK, *PSTOCK;

    // structure of the stock portfolio file (which is followed by array of STOCK)
    typedef struct tagPortFile
    {
        UINT        uVer1;          // must be equal to FILE_VERSION
        UINT        uidCurrStock;   // current stock ID

        // change/delete logs used by the sync module
        UINT        cChg, cDel;
        UINT        rgidChg[ MAX_STOCKS ], rgidDel[ MAX_STOCKS ];

        UINT        cStocks;        // # of stocks in the portfolio
        STOCK       rgStocks[ MAX_STOCKS ];

        UINT        uVer2;          // must be equal to FILE_VERSION
    } PORTFILE, *PPORTFILE;

#endif

// data structure used to synchronize a stock
// used by IReplObjHandler on both the desktop and device
// all strings are always in UNICODE
typedef struct tagStockPacket
{
    WCHAR       wszSym[ 10 ];
    WCHAR       wszCompany[ 80 ];
    WCHAR       wszLastPrice[ 20 ];
    WCHAR       wszPurDate[ 20 ];
    WCHAR       wszPurPrice[ 20 ];
    WCHAR       wszGain[ 20 ];
    FILETIME    ftUpdated;
} STPACKET, *PSTPACKET;
