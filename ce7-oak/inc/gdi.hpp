//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//

#ifndef __GDI_HPP_INCLUDED__
#define __GDI_HPP_INCLUDED__

enum PVBITSORIGIN
{
    PVBITS_RSRC = 0,    // resource (don't free)
    PVBITS_GWE,         // gwe space (localfree)
    PVBITS_CLIENT       // client space (remotefree)
};

class Gdi
{

public:

    static
    BOOL
    Initialize(
        HINSTANCE    hinst
        );

    static
    void
    ProcessCleanup(
        HPROCESS    hprc
        );


    static
    WINGDIAPI int WINAPI
    AddFontResourceW_I(
        __in const WCHAR* lpszFilename
        );

    static
    WINGDIAPI BOOL WINAPI
    BitBlt_I(HDC, int, int, int, int, HDC, int, int, DWORD);

    static
    WINGDIAPI int WINAPI
    CombineRgn_I(HRGN, HRGN, HRGN, int);

    static
    WINGDIAPI HDC WINAPI
    CreateCompatibleDC_I(
        HDC hdcIn
        );

    static
    WINGDIAPI HBRUSH WINAPI
    CreateDIBPatternBrushPt_I(const void *, unsigned int);

    static
    WINGDIAPI HBRUSH WINAPI
    CreateDIBPatternBrushPt_E(const void *, size_t, unsigned int);

    static
    unsigned int
    DibByteWidth(
        unsigned int    N,
        unsigned int    W
        );

    static
    unsigned int
    DibSize(
        unsigned int    N,
        unsigned int    W,
        int                H
        );


    static
    WINGDIAPI HBITMAP WINAPI
    CreateDIBSectionStub(
        HDC   hdc,
        BOOL  fAllowNullDC,
        const BITMAPINFO *pbmi,
        void* pvBits,
        unsigned int  iUsage);

    static
    WINGDIAPI HBITMAP WINAPI
    CreateDIBSectionStub(
        HDC   hdc,
        BOOL  fAllowNullDC,
        const BITMAPINFO *pbmi,
        void* pvBits,
        PVBITSORIGIN pvBitsOrigin,
        unsigned int  iUsage);

    static
    WINGDIAPI
    HBITMAP
    WINAPI
    Gdi::
    CreateDIBSectionStub_E(
        HDC    hdc,
        BOOL   fAllowNullDC,
        __in_bcount(cbBmi) const BITMAPINFO* pbmi,
        size_t cbBmi,
        __in_bcount(cbBits) void* pvBits,
        size_t cbBits,
        UINT   iUsage);

    static
    HBITMAP WINAPI
    CreatePermanentDIBSection(
        HDC              hdc,
        CONST BITMAPINFO *pbmi,
        UINT             iUsage,
        void             **ppvBits,
        HANDLE           hSection,
        DWORD            dwOffset);

    static
    HBITMAP
    CreateMonoBitmapFromDIB(
        const BITMAPINFO *pbmi,
        void  *pvBits,
        PVBITSORIGIN pvBitsOrigin = PVBITS_RSRC
        );

    static
    WINGDIAPI UINT WINAPI
    GetDIBColorTable_I(
        HDC                hdc,
        UINT            uStartIndex,
        UINT            cEntries,
        __out_ecount(cEntries) RGBQUAD *        pColors
        );

    static
    WINGDIAPI UINT WINAPI
    GetDIBColorTable_E(
        HDC                hdc,
        UINT            uStartIndex,
        UINT            cEntries,
        __out_bcount(cbColors) RGBQUAD *        pColors,
        size_t          cbColors
        );

    static
    WINGDIAPI UINT WINAPI
    SetDIBColorTable_I(
        HDC             hdc,
        UINT             uStartIndex,
        UINT             cEntries,
        __in_ecount(cEntries) CONST RGBQUAD *        pColors
        );

    static
    WINGDIAPI UINT WINAPI
    SetDIBColorTable_E(
        HDC             hdc,
        UINT            uStartIndex,
        UINT            cEntries,
        __in_bcount(cbColors) CONST RGBQUAD *        pColors,
        size_t          cbColors
        );

    static
    WINGDIAPI int WINAPI
    StretchDIBits_I(
        HDC                hdc,
        int             XDest,
        int                YDest,
        int             nDestWidth,
        int             nDestHeight,
        int                XSrc,
        int                YSrc,
        int                nSrcWidth,
        int                nSrcHeight,
        CONST VOID*         lpBits,
        CONST BITMAPINFO *lpBitsInfo,
        UINT            iUsage,
        DWORD             dwRop);

    static
    WINGDIAPI int WINAPI
    StretchDIBits_E(
        HDC                hdc,
        int             XDest,
        int                YDest,
        int             nDestWidth,
        int             nDestHeight,
        int                XSrc,
        int                YSrc,
        int                nSrcWidth,
        int                nSrcHeight,
        CONST VOID*         lpBits,
        CONST BITMAPINFO *lpBitsInfo,
        UINT            iUsage,
        DWORD             dwRop);

    static
    WINGDIAPI int WINAPI
    SetDIBitsToDevice_I(
        HDC             hdc,
        int             XDest,
        int             YDest,
        DWORD           dwWidth,
        DWORD           dwHeight,
        int             XSrc,
        int             YSrc,
        UINT            uStartScan,
        UINT            cScanLines,
        CONST VOID *lpvBits,
        CONST BITMAPINFO *lpbmi,
        UINT fuColorUse);

    static
    WINGDIAPI int WINAPI
    SetDIBitsToDevice_E(
        HDC             hdc,
        int             XDest,
        int             YDest,
        DWORD           dwWidth,
        DWORD           dwHeight,
        int             XSrc,
        int             YSrc,
        UINT            uStartScan,
        UINT            cScanLines,
        CONST VOID *lpvBits,
        __in_bcount(cbBmi) CONST BITMAPINFO *lpbmi,
        size_t          cbBmi,
        UINT fuColorUse);

    static
    WINGDIAPI
    HFONT
    WINAPI
    CreateFontIndirectW_I(
        __in const    LOGFONTW*
        );

    static
    WINGDIAPI
    HFONT
    WINAPI
    CreateFontIndirectW_E(
        __in_bcount(cblf) const    LOGFONTW* lplf,
        size_t  cblf
        );

    static
    WINGDIAPI HRGN WINAPI
    CreateRectRgnIndirect_I(
        __in const    RECT*
        );

    static
    WINGDIAPI HRGN WINAPI
    CreateRectRgnIndirect_E(
        __in_bcount(cbRect) const RECT* pRect,
        size_t  cbRect
        );

    static
    WINGDIAPI HPEN WINAPI
    CreatePenIndirect_I(
        __in const LOGPEN *lplgpn
        );

    static
    WINGDIAPI HPEN WINAPI
    CreatePenIndirect_E(
        __in_bcount(cblgpn) const LOGPEN *lplgpn,
        size_t cblgpn
        );

    static
    WINGDIAPI HBRUSH WINAPI
    CreateSolidBrush_I(
        COLORREF crColor
        );

    static
    WINGDIAPI BOOL WINAPI
    DeleteDC_I(
        HDC hdc
        );

    static
    WINGDIAPI
    BOOL
    WINAPI
    DeleteObject_I(
        HGDIOBJ hgdiobj
        );

    static
    WINUSERAPI BOOL WINAPI
    DrawEdge_I(HDC, __in RECT*, unsigned int, unsigned int);

    static
    WINUSERAPI BOOL WINAPI
    DrawEdge_E(
        HDC hdc,
        __in_bcount(cbrc) RECT* prc,
        size_t cbrc,
        unsigned int edge,
        unsigned int grfFlags
        );

    static
    WINUSERAPI BOOL WINAPI
    DrawFocusRect_I(HDC, __in const RECT *);

    static
    WINUSERAPI BOOL WINAPI
    DrawFocusRect_E(
        HDC hdc,
        __in const RECT * prc,
        size_t cbrc
        );

    static
    WINUSERAPI int WINAPI
    DrawTextW_I(
        HDC hdc,
        __in_ecount(cchString) const WCHAR* pszString,
        int cchString,
        __in RECT *pRect,
        unsigned int uFormats
        );

    static
    WINUSERAPI int WINAPI
    DrawTextW_E(
        HDC hdc,
        __in_bcount(cbString) const WCHAR* pszString,
        size_t cbString,
        int cchString,
        __in_bcount(cbRect) RECT *pRect,
        size_t cbRect,
        unsigned int uFormats
        );

    static
    WINGDIAPI BOOL WINAPI
    Ellipse_I(HDC, int, int, int, int);

    static
    int
    EnumFontFamiliesW_I(HDC, __in_opt const WCHAR*, FONTENUMPROC, HPROCESS, LPARAM);

    static
    WINGDIAPI int WINAPI
    EnumFontFamiliesW_E(HDC, __in_opt const WCHAR*, FONTENUMPROC, LPARAM);

    static
    WINGDIAPI int WINAPI
    EnumFontFamiliesW_IW(HDC, __in_opt const WCHAR*, FONTENUMPROC, LPARAM);

    static
    WINGDIAPI int WINAPI
    EnumFontsW_IW(
        HDC hdc,
        __in_opt const WCHAR* lpFaceName,
        FONTENUMPROC lpFontFunc,
        LPARAM lParam
        );

    static
    WINGDIAPI int WINAPI
    EnumFontsW_E(
        HDC hdc,
        __in_opt const WCHAR* lpFaceName,
        FONTENUMPROC lpFontFunc,
        LPARAM lParam
        );

    static
    WINGDIAPI int WINAPI
    ExcludeClipRect_I(HDC, int, int, int, int);


    static
    WINGDIAPI BOOL WINAPI
    ExtTextOutW_I(
        HDC         hdc,
        int         X,
        int         Y,
        unsigned int        fuOptions,
        __in const RECT *lprc,
        __in_ecount(cchCount) const WCHAR*     lpszString,
        unsigned int        cchCount,
        __in_ecount_opt(cchCount) const int   *lpDx
        );

    static
    WINGDIAPI BOOL WINAPI
    ExtTextOutW_E(
        HDC         hdc,
        int         X,
        int         Y,
        unsigned int        fuOptions,
        __in_bcount_opt(cbrc) const RECT *lprc,
        size_t  cbrc,
        __in_ecount(cbszString) const WCHAR*     lpszString,
        size_t  cbszString,
        unsigned int        cchCount,
        __in_bcount_opt(cbDx) const int   *lpDx,
        size_t  cbDx
        );

    static
    WINGDIAPI BOOL WINAPI
    GetCharWidth32_I(
        HDC           hdc,
        UINT         iFirstChar,
        UINT         iLastChar,
        __out LPINT        lpBuffer);

    static
    WINGDIAPI BOOL WINAPI
    GetCharWidth32_E(
        HDC         hdc,
        UINT        iFirstChar,
        UINT        iLastChar,
        __out_bcount(cbBuffer) LPINT        lpBuffer,
        size_t      cbBuffer
        );

    static
    WINGDIAPI BOOL WINAPI
    GetCharABCWidths_I(
        HDC         hdc,
        UINT        uFirstChar,
        UINT        uLastChar,
        __out LPABC       lpabc
    );

    static
    WINGDIAPI BOOL WINAPI
    GetCharABCWidths_E(
        HDC         hdc,
        UINT        uFirstChar,
        UINT        uLastChar,
        __out_bcount(cbabc) LPABC       lpabc,
        size_t      cbabc
    );

    static
    WINGDIAPI BOOL WINAPI
    GetCharABCWidthsI_I(
        HDC hdc,
        UINT giFirst,
        UINT cgi,
        __in_ecount_opt(cgi) LPWORD pgi,
        __out_ecount(cgi) LPABC lpabc
        );

    static
    WINGDIAPI BOOL WINAPI
    GetCharABCWidthsI_E(
        HDC hdc,
        UINT giFirst,
        UINT cgi,
        __in_bcount_opt(cbgi) LPWORD pgi,
        size_t  cbgi,
        __out_bcount(cbabc) LPABC lpabc,
        size_t  cbabc
        );

    static
    WINGDIAPI UINT WINAPI
    SetTextAlign_I(
        HDC         hdc,
        UINT        fMode
        );

    static
    WINGDIAPI UINT WINAPI
    GetTextAlign_I(
        HDC           hdc
        );

    static
    WINGDIAPI int WINAPI
    SetTextCharacterExtra_I(
        HDC hdc,
        int nCharExtra
        );

    static
    WINGDIAPI int WINAPI
    GetTextCharacterExtra_I(
        HDC hdc
        );

    static
    WINUSERAPI int WINAPI
    FillRect_I(
        HDC,
        __in const RECT *,
        HBRUSH
        );

    static
    WINUSERAPI int WINAPI
    FillRect_E(
        HDC hdc,
        __in_bcount(cbRect) const RECT * pRect,
        size_t cbRect,
        HBRUSH hbr
        );

    static
    WINGDIAPI COLORREF WINAPI
    GetBkColor_I(
        HDC hdc
        );

    static
    WINGDIAPI int WINAPI
    GetBkMode_I(
        HDC hdc
        );

    static
    WINGDIAPI int WINAPI
    GetClipRgn_I(HDC, HRGN);

    static
    WINGDIAPI HGDIOBJ WINAPI
    GetCurrentObject_I(
        HDC hdc,
        unsigned int uObjectType
        );

    static
    WINGDIAPI int WINAPI
    GetDeviceCaps_I(
        HDC hdc,
        int nIndex
        );

    static
    WINGDIAPI COLORREF WINAPI
    GetNearestColor_I(HDC, COLORREF);

    static
    WINGDIAPI int WINAPI
    GetObjectW_I(
        HGDIOBJ hgdiobj,
        int cbBuffer,
        __out_bcount_opt(cbBuffer) void* lpvObject
        );

    static
    WINGDIAPI int WINAPI
    GetObjectW_E(
        HGDIOBJ hgdiobj,
        __out_bcount_opt(cbBuffer) void* lpvObject,
        int cbBuffer
        );

    static
    WINGDIAPI DWORD WINAPI
    GetObjectType_I(
        HGDIOBJ hgdiobj
        );

    static
    WINGDIAPI COLORREF WINAPI
    GetPixel_I(HDC, int, int nYPos);

    static
    WINGDIAPI DWORD WINAPI
    GetRegionData_I(
        HRGN hrgn,
        DWORD dwCount,
        __out_bcount_opt(dwCount) RGNDATA* lpRgnData
        );

    static
    WINGDIAPI DWORD WINAPI
    GetRegionData_E(
        HRGN hrgn,
        __out_bcount_opt(dwCount) RGNDATA* lpRgnData,
        DWORD dwCount
        );

    static
    WINGDIAPI int WINAPI
    GetRgnBox_I(HRGN, __out RECT *);

    static
    WINGDIAPI int WINAPI
    GetRgnBox_E(
        HRGN hrgn,
        __out_bcount(cbRect) RECT * pRect,
        size_t cbRect
        );

    static
    BOOL WINAPI
    PatBlt_I(HDC, int, int, int, int, DWORD);

    static
    WINGDIAPI COLORREF WINAPI
    GetTextColor_I(
        HDC hdc
        );

    static
    WINGDIAPI BOOL WINAPI
    GetTextExtentExPointW_I(
        HDC     hdc,
        __in_ecount(cchString) const WCHAR* lpszStr,
        int     cchString,
        int     nMaxExtent,
        __out_opt int*   lpnFit,
        __out_ecount_opt(cchString) int*   alpDx,
        __out SIZE*  lpSize);

    static
    WINGDIAPI BOOL WINAPI
    GetTextExtentExPointW_E(
        HDC     hdc,
        __in_bcount(cbStr) const WCHAR* lpszStr,
        size_t  cbStr,
        int     cchString,
        int     nMaxExtent,
        __out_opt int*   lpnFit,
        __out_bcount_opt(cbDx) int*   alpDx,
        size_t  cbDx,
        __out_bcount(cbSize) SIZE*  lpSize,
        size_t  cbSize
        );

    static
    WINGDIAPI int WINAPI
    GetTextFaceW_I(
        HDC hdc,
        int nCount,
        __out_ecount_opt(nCount) WCHAR* lpszString
        );

    static
    WINGDIAPI int WINAPI
    GetTextFaceW_E(
        HDC hdc,
        int nCount,
        __out_bcount_opt(cbString) WCHAR* lpszString,
        size_t  cbString
        );

    static
    WINGDIAPI
    BOOL
    WINAPI
    GetTextMetricsW_I(
        HDC hdc,
        __out TEXTMETRIC* lptm);

    static
    WINGDIAPI
    BOOL
    WINAPI
    GetTextMetricsW_E(
        HDC hdc,
        __out_bcount(cbtm) TEXTMETRIC* lptm,
        size_t cbtm
        );

    static
    WINGDIAPI
    UINT
    WINAPI
    GetOutlineTextMetricsW_I(
        HDC hdc,
        UINT cbData,
        __out_bcount_opt(cbData) LPOUTLINETEXTMETRICW lpOTM
        );

    static
    WINGDIAPI
    UINT
    WINAPI
    GetOutlineTextMetricsW_E(
        HDC hdc,
        __out_bcount_opt(cbData) LPOUTLINETEXTMETRICW lpOTM,
        UINT cbData
        );

    static
    WINGDIAPI BOOL WINAPI
    MaskBlt_I(HDC, int, int, int, int, HDC, int, int, HBITMAP, int, int, DWORD);

    static
    WINGDIAPI int WINAPI
    OffsetRgn_I(HRGN, int, int);

    static
    WINGDIAPI BOOL WINAPI
    GetCurrentPositionEx_I(HDC,__out POINT *);

    static
    WINGDIAPI BOOL WINAPI
    GetCurrentPositionEx_E(
        HDC hdc,
        __out_bcount(cbpt) POINT * ppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    MoveToEx_I(HDC,int,int,__out_opt POINT *);

    static
    WINGDIAPI BOOL WINAPI
    MoveToEx_E(
        HDC hdc,
        int x,
        int y,
        __out_bcount_opt(cbpt) POINT * ppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    LineTo_I(HDC,int,int);

    static
    WINGDIAPI BOOL WINAPI
    Polygon_I(
        HDC hdc,
        __in_ecount(nPoints) const POINT * pPoints,
        int nPoints);

    static
    WINGDIAPI BOOL WINAPI
    Polygon_E(
        HDC hdc,
        __in_bcount(cbPoints) const POINT * pPoints,
        size_t cbPoints,
        int nPoints);

    static
    WINGDIAPI BOOL WINAPI
    Polyline_I(
        HDC hdc,
        __in_ecount(nPoints) const POINT * pPoints,
        int nPoints
        );

    static
    WINGDIAPI BOOL WINAPI
    Polyline_E(
        HDC hdc,
        __in_bcount(cbPoints) const POINT * pPoints,
        size_t cbPoints,
        int nPoints
        );

    static
    WINGDIAPI BOOL WINAPI
    PtInRegion_I(HRGN, int, int);

    static
    WINGDIAPI BOOL WINAPI
    Rectangle_I(HDC, int, int, int, int);

    static
    WINGDIAPI BOOL WINAPI
    RectInRegion_I(HRGN, __in const RECT *);

    static
    WINGDIAPI BOOL WINAPI
    RectInRegion_E(
        HRGN hrgn,
        __in_bcount(cbRect) const RECT * pRect,
        size_t cbRect
        );

    static
    WINGDIAPI BOOL WINAPI
    RemoveFontResourceW_I(
        __in const WCHAR* lpFileName
        );

    static
    WINGDIAPI BOOL WINAPI
    RestoreDC_I(HDC, int);

    static
    WINGDIAPI BOOL WINAPI
    RoundRect_I(HDC, int, int, int, int, int, int);

    static
    WINGDIAPI int WINAPI
    SaveDC_I(HDC);

    static
    WINGDIAPI int WINAPI
    SelectClipRgn_I(
        HDC hdc,
        HRGN hrgn
        );

    static
    WINGDIAPI HGDIOBJ WINAPI
    SelectObject_I(
        HDC hdc,
        HGDIOBJ hgdiobj
        );

    static
    WINGDIAPI COLORREF WINAPI
    SetBkColor_I(
        HDC hdc,
        COLORREF crColor
        );

    static
    WINGDIAPI int WINAPI
    SetBkMode_I(
        HDC hdc,
        int iBkMode
        );

    static
    WINGDIAPI BOOL WINAPI
    SetBrushOrgEx_I(HDC, int, int, __out_opt POINT*);

    static
    WINGDIAPI BOOL WINAPI
    SetBrushOrgEx_E(
        HDC hdc,
        int nXOrg,
        int nYOrg,
        __out_bcount_opt(cbpt) POINT* lppt,
        size_t cbpt
        );

    static
    WINGDIAPI COLORREF WINAPI
    SetPixel_I(HDC, int, int, COLORREF);


    static
    WINGDIAPI COLORREF WINAPI
    SetTextColor_I(
        HDC hdc,
        COLORREF crColor
        );

    static
    WINGDIAPI BOOL WINAPI
    StretchBlt_I(HDC, int, int, int, int, HDC, int, int, int, int, DWORD);

    static
    WINGDIAPI HBITMAP WINAPI
    CreateBitmap_I(
        int nWidth,
        int nHeight,
        unsigned int cPlanes,
        unsigned int cBitsPerPlane,
        __in_opt const void * lpvBits
        );

    static
    WINGDIAPI HBITMAP WINAPI
    CreateBitmap_E(
        int nWidth,
        int nHeight,
        unsigned int cPlanes,
        unsigned int cBitsPerPlane,
        __in_bcount_opt(cbBits) const void * lpvBits,
        size_t cbBits
        );

    static
    WINGDIAPI LONG WINAPI
    SetBitmapBits_I(
        HBITMAP hbmp,
        DWORD cBytes,
        __in_bcount(cBytes) CONST VOID * lpBits
        );

    static
    WINGDIAPI LONG WINAPI
    SetBitmapBits_E(
        HBITMAP hbmp,
        __in_bcount(cBytes) CONST VOID * lpBits,
        DWORD cBytes
        );

    static
    WINGDIAPI HBITMAP WINAPI
    CreateCompatibleBitmap_I(HDC, int, int);

    static
    WINGDIAPI HBRUSH WINAPI
    GetSysColorBrush_I(int);

    static
    WINGDIAPI int WINAPI
    IntersectClipRect_I(HDC, int, int, int, int);

    static
    WINGDIAPI int WINAPI
    GetClipBox_I(HDC, __out RECT *);

    static
    WINGDIAPI int WINAPI
    GetClipBox_E(
        HDC hdc,
        __out_bcount(cbrc) RECT * lprc,
        size_t  cbrc
        );

    static
    WINGDIAPI BOOL WINAPI
    CeRemoveFontResource_I(
        CEOID oid
        );

    static
    WINGDIAPI DWORD WINAPI
    GetFontData_I(
        HDC     hdc,
        DWORD   dwTable,
        DWORD   dwOffset,
        __out_bcount_opt(cbData) LPVOID  lpvBuffer,
        DWORD   cbData
        );

    static
    BOOL
    WINAPI
    EnableEUDC_I(BOOL fEnableEUDC);


    static
    WINGDIAPI HDC   WINAPI
    CreateEnhMetaFileW_I(
        HDC hdcRef,
        __in_opt const WCHAR* lpszFileName,
        __in_opt const RECT * lpRect,
        __in_opt const WCHAR* lpDescription
        );

    static
    WINGDIAPI BOOL  WINAPI
    DeleteEnhMetaFile_I(HENHMETAFILE);

    static
    WINGDIAPI BOOL  WINAPI
    PlayEnhMetaFile_I(
        HDC hdc,
        HENHMETAFILE hemf,
        __in const RECT * lpRect
        );

    static
    WINGDIAPI HPALETTE WINAPI
    CreatePalette_I(__in const LOGPALETTE *);

    static
    WINGDIAPI HPALETTE WINAPI
    CreatePalette_E(
        __in_bcount(cblgpl) const LOGPALETTE * lgpl,
        size_t  cblgpl
        );

    static
    WINGDIAPI HPALETTE WINAPI
    SelectPalette_I(HDC, HPALETTE, BOOL);

    static
    WINGDIAPI unsigned int WINAPI
    RealizePalette_I(HDC);

    static
    WINGDIAPI unsigned int WINAPI
    GetPaletteEntries_I(
        HPALETTE hpal,
        unsigned int iStartIndex,
        unsigned int nEntries,
        __out_ecount_opt(nEntries) PALETTEENTRY* lppe
        );

    static
    WINGDIAPI unsigned int WINAPI
    GetPaletteEntries_E(
        HPALETTE hpal,
        unsigned int iStartIndex,
        unsigned int nEntries,
        __out_bcount_opt(cbpe) PALETTEENTRY* lppe,
        size_t cbpe
        );

    static
    WINGDIAPI unsigned int WINAPI
    SetPaletteEntries_I(
        HPALETTE hpal,
        unsigned int iStartIndex,
        unsigned int nEntries,
        __in_ecount(nEntries) const PALETTEENTRY * lppe
        );

    static
    WINGDIAPI unsigned int WINAPI
    SetPaletteEntries_E(
        HPALETTE hpal,
        unsigned int iStartIndex,
        unsigned int nEntries,
        __in_bcount(cbpe) const PALETTEENTRY * lppe,
        size_t cbpe
        );

    static
    WINGDIAPI unsigned int WINAPI
    GetSystemPaletteEntries_I(
        HDC hdc,
        unsigned int iStartIndex,
        unsigned int nEntries,
        __out_ecount_opt(nEntries) PALETTEENTRY* lppe
        );

    static
    WINGDIAPI unsigned int WINAPI
    GetSystemPaletteEntries_E(
        HDC hdc,
        unsigned int iStartIndex,
        unsigned int nEntries,
        __out_bcount_opt(cbpe) PALETTEENTRY* lppe,
        size_t cbpe
        );

    static
    WINGDIAPI unsigned int WINAPI
    GetNearestPaletteIndex_I(HPALETTE, COLORREF);


    static
    WINGDIAPI HPEN WINAPI
    CreatePen_I(int, int, COLORREF);

    static
    WINGDIAPI int WINAPI
    StartDocW_I(HDC, __in const DOCINFOW *);

    static
    WINGDIAPI int WINAPI
    StartDocW_E(
        HDC hdc,
        __in_bcount(cbdi) const DOCINFOW * lpdi,
        size_t cbdi
        );

    static
    WINGDIAPI int WINAPI
    EndDoc_I(HDC);

    static
    WINGDIAPI int WINAPI
    StartPage_I(HDC);

    static
    WINGDIAPI int WINAPI
    EndPage_I(HDC);

    static
    WINGDIAPI int WINAPI
    AbortDoc_I(HDC);

    static
    WINGDIAPI int WINAPI
    SetAbortProc_I(HDC, ABORTPROC);

    static
    WINGDIAPI HDC WINAPI
    CreateDCW_I(__in_opt const WCHAR*, __in const WCHAR*, __in const WCHAR*, __in_opt const DEVMODEW *);

    static
    WINGDIAPI HDC WINAPI
    CreateDCW_E(
        __in_opt const WCHAR* lpszDriver,
        __in const WCHAR* lpszDevice,
        __in const WCHAR* lpszOutput,
        __in_bcount_opt(cbInitData) const DEVMODEW * lpInitData,
        size_t cbInitData
        );

    static
    WINGDIAPI HRGN WINAPI
    CreateRectRgn_I(int, int, int, int);

    static
    WINGDIAPI HRGN WINAPI
    ExtCreateRegion_I(
        __in_opt const XFORM * lpXform,
        DWORD nCount,
        __in_bcount(nCount) const RGNDATA * lpRgnData
        );

    static
    WINGDIAPI HRGN WINAPI
    ExtCreateRegion_E(
        __in_opt const XFORM * lpXform,
        size_t  cbXform,
        __in_bcount(nCount) const RGNDATA * lpRgnData,
        DWORD nCount
        );

    static
    WINGDIAPI BOOL WINAPI
    FillRgn_I(HDC, HRGN, HBRUSH);

    static
    WINGDIAPI int WINAPI
    SetROP2_I(HDC, int);

    static
    WINGDIAPI int WINAPI
    GetROP2_I(HDC);


    static
    WINGDIAPI BOOL WINAPI
    SetRectRgn_I(HRGN, int, int, int, int);

    static
    WINGDIAPI BOOL WINAPI
    RectVisible_I(HDC, __in const RECT *);

    static
    WINGDIAPI BOOL WINAPI
    RectVisible_E(
        HDC hdc,
        __in_bcount(cbrc) const RECT * lprc,
        size_t  cbrc
        );

    static
    WINGDIAPI HBRUSH WINAPI
    CreatePatternBrush_I(HBITMAP);

    static
    WINGDIAPI BOOL WINAPI
    SetViewportOrgEx_I(
        HDC hdc,
        int nXOrg,
        int nYOrg,
        __out_opt POINT* lppt
        );

    static
    WINGDIAPI BOOL WINAPI
    SetViewportOrgEx_E(
        HDC hdc,
        int nXOrg,
        int nYOrg,
        __out_bcount_opt(cbpt) POINT* lppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    GetViewportOrgEx_I(
        HDC hdc,
        __out POINT* lppt
        );

    static
    WINGDIAPI BOOL WINAPI
    GetViewportOrgEx_E(
        HDC hdc,
        __out_bcount(cbpt) POINT* lppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    OffsetViewportOrgEx_I(
        HDC hdc,
        int nXOffset,
        int nYOffset,
        __out_opt POINT* lppt
        );

    static
    WINGDIAPI BOOL WINAPI
    OffsetViewportOrgEx_E(
        HDC hdc,
        int nXOffset,
        int nYOffset,
        __out_bcount_opt(cbpt) POINT* lppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    SetWindowOrgEx_I(
        HDC hdc,
        int X,
        int Y,
        __out_opt POINT* lppt
        );

    static
    WINGDIAPI BOOL WINAPI
    SetWindowOrgEx_E(
        HDC hdc,
        int X,
        int Y,
        __out_bcount_opt(cbpt) POINT* lppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    GetWindowOrgEx_I(
        HDC hdc,
        __out POINT* lppt
        );

    static
    WINGDIAPI BOOL WINAPI
    GetWindowOrgEx_E(
        HDC hdc,
        __out_bcount(cbpt) POINT* lppt,
        size_t cbpt
        );

    static
    WINGDIAPI BOOL WINAPI
    GetWindowExtEx_I(
        HDC hdc,
        __out SIZE* lppt
        );

    static
    WINGDIAPI BOOL WINAPI
    GetWindowExtEx_E(
        HDC hdc,
        __out_bcount(cbSize) SIZE* lppt,
        size_t cbSize
        );

    static
    WINGDIAPI BOOL WINAPI
    GetViewportExtEx_I(
        HDC hdc,
        __out SIZE* lpSize
        );

    static
    WINGDIAPI BOOL WINAPI
    GetViewportExtEx_E(
        HDC hdc,
        __out_bcount(cbSize) SIZE* lpSize,
        size_t cbSize
        );

    static
    WINGDIAPI BOOL WINAPI
    TransparentImage_I(HDC, int, int, int, int, HANDLE, int, int, int, int, COLORREF);

    static
    BOOL
    GdiSetObjectOwner_I(HGDIOBJ, HPROCESS);


    static
    WINGDIAPI BOOL WINAPI
    TranslateCharsetInfo_I(
        __inout DWORD *lpSrc,
        __out CHARSETINFO* lpCs,
        DWORD dwFlags
        );

    static
    WINGDIAPI BOOL WINAPI
    TranslateCharsetInfo_E(
        DWORD dwSrc,
        __inout_bcount(cbSrcCs) DWORD* lpSrcCs,
        size_t cbSrcCs,
        __out_bcount(cbCs) CHARSETINFO* lpCs,
        size_t cbCs,
        DWORD dwFlags
        );

    static
    WINGDIAPI int WINAPI
    ExtEscape_I(
        HDC hdc,
        int nEscape,
        int cbInput,
        __in_bcount_opt(cbInput) const char* lpszInData,
        int cbOutput,
        __out_bcount_opt(cbOutput) char* lpszOutData
        );

    static
    WINGDIAPI int WINAPI
    ExtEscape_E(
        HDC hdc,
        int nEscape,
        __in_bcount_opt(cbInput) const char* lpszInData,
        int cbInput,
        __out_bcount_opt(cbOutput) char* lpszOutData,
        int cbOutput
        );

    static
    WINGDIAPI int WINAPI
    BitmapEscape_I(
        HBITMAP hbmp,
        int nEscape,
        int cbInput,
        __in_bcount_opt(cbInput) const char* lpszInData,
        int cbOutput,
        __out_bcount_opt(cbOutput) char* lpszOutData
        );

    static
    WINGDIAPI int WINAPI
    BitmapEscape_E(
        HBITMAP hbmp,
        int nEscape,
        __in_bcount_opt(cbInput) const char* lpszInData,
        int cbInput,
        __out_bcount_opt(cbOutput) char* lpszOutData,
        int cbOutput
        );

    static
    BOOL
    InternalEscapeCode(
        int iEscape
    );

    static
    WINUSERAPI BOOL WINAPI
    InvertRect_I(HDC, __in const RECT *);

    static
    WINUSERAPI BOOL WINAPI
    InvertRect_E(
        HDC hdc,
        __in_bcount(cbrc) const RECT *lprc,
        size_t cbrc
        );

    static
    int
    InternalScrollDC(
        HDC        hdc,
        int        dx,
        int        dy,
        const RECT*    prcSrc,                // client coordinates
        const RECT*    prcClip,            // client coordinates
        HRGN    hrgnInvalid,        // screen coordinates
        HRGN    hrgnUpdate,            // output as either
        RECT*    prcUpdate,            // output as client coordinates
        BOOL    fWantClientCoords    // does caller want hrgnUpdate in client coordinates?
        );

    static
    WINGDIAPI BOOL WINAPI
    ScrollDC_I(
        HDC hdc,
        int dx,
        int dy,
        __in_opt const RECT *lprcScroll,
        __in_opt const RECT *lprcClip ,
        HRGN hrgnUpdate,
        __out_opt RECT* lprcUpdate
        );

    static
    WINGDIAPI BOOL WINAPI
    ScrollDC_E(
        HDC hdc,
        int dx,
        int dy,
        __in_bcount_opt(cbrcScroll) const RECT *lprcScroll,
        size_t  cbrcScroll,
        __in_bcount_opt(cbrcClip) const RECT *lprcClip ,
        size_t  cbrcClip,
        HRGN hrgnUpdate,
        __out_bcount_opt(cbrcUpdate) RECT* lprcUpdate,
        size_t  cbrcUpdate
        );

    static
    BOOL
    IsValidRgn_I(
        HRGN    hrgn
        );

    static
    void
    LogFontFromRegistry(
        LOGFONT*    pLogFont,
        WCHAR*        pRegKey,
        LONG        DefaultWeight
        );

    static
    BOOL
    EnumDisplayMonitors_I(
        HDC                hdcPaint,
        __in_opt LPCRECT      lprcPaint,
        __in MONITORENUMPROC    lpfnEnum,
        LPARAM            lData,
        HPROCESS         hProcCallingContext
        );

    static
    BOOL
    WINAPI
    EnumDisplayMonitors_IW(
        HDC                hdcPaint,
        __in_bcount_opt(cbrcPaint) LPCRECT      lprcPaint,
        size_t              cbrcPaint,
        __in MONITORENUMPROC    lpfnEnum,
        LPARAM            lData
        );

    static
    BOOL
    WINAPI
    EnumDisplayMonitors_E(
        HDC              hdcPaint,
        __in_bcount_opt(cbrcPaint) LPCRECT    lprcPaint,
        size_t           cbrcPaint,
        __in MONITORENUMPROC  lpfnEnum,
        LPARAM           lData
        );

    static
    BOOL
    WINAPI
    GetMonitorInfo_I(
        HMONITOR        hMonitor,
        __inout LPMONITORINFO    lpmi
        );

    static
    BOOL
    WINAPI
    GetMonitorInfo_E(
        HMONITOR        hMonitor,
        __out_bcount(cbmi) LPMONITORINFO    lpmi,
        size_t          cbmi
        );

    static
    HMONITOR
    WINAPI
    MonitorFromWindow_I(
        HWND    hwnd,
        DWORD    dwFlag
        );


    static
    HMONITOR
    WINAPI
    MonitorFromRect_I(
        __in LPCRECT        lprc,
        DWORD        dwFlag
        );

    static
    HMONITOR
    WINAPI
    MonitorFromRect_E(
        __in_bcount(cbrc) LPCRECT        lprc,
        size_t       cbrc,
        DWORD        dwFlag
        );

    static
    HMONITOR
    WINAPI
    MonitorFromPoint_I(
        POINT    pt,
        DWORD    dwFlag
        );

    static
    int
    ClearAllGlyphCaches(
        );

    static
    BOOL
    GradientFill_I(
        HDC         hdc,
        __in_ecount(nVertex) PTRIVERTEX  pVertex,
        ULONG       nVertex,
        __in_ecount(nCount) PVOID       pMesh,
        ULONG       nCount,
        ULONG       ulMode
        );

    static
    BOOL
    GradientFill_E(
        HDC         hdc,
        __in_bcount(cbVertex) PTRIVERTEX  pVertex,
        size_t      cbVertex,
        ULONG       nVertex,
        __in_bcount(cbMesh) PVOID       pMesh,
        size_t      cbMesh,
        ULONG       nCount,
        ULONG       ulMode
        );

    static
    BOOL
    EnumDisplaySettings_I(
        __in_opt LPCTSTR    lpszDeviceName,
        DWORD      iModeNum,
        __inout LPDEVMODEW lpDevMode
        );

    static
    BOOL
    EnumDisplaySettings_E(
        __in_opt LPCTSTR    lpszDeviceName,
        DWORD      iModeNum,
        __inout_bcount(cbDevMode) LPDEVMODEW lpDevMode,
        size_t      cbDevMode
        );

    static
    BOOL
    EnumDisplayDevices_I(
        __in_opt LPCTSTR         lpDevice,
        DWORD           iModeNum,
        __inout PDISPLAY_DEVICE lpDisplayDevice,
        DWORD           dwFlags
        );

    static
    BOOL
    EnumDisplayDevices_E(
        __in_opt LPCTSTR         lpDevice,
        DWORD           iModeNum,
        __inout_bcount(cbDisplayDevice) PDISPLAY_DEVICE lpDisplayDevice,
        size_t          cbDisplayDevice,
        DWORD           dwFlags
        );

    static
    int
    GetStretchBltMode_I(
        HDC    hdc
        );

    static
    int
    SetStretchBltMode_I(
        HDC    hdc,
        int    mode
        );

    static
    BOOL
    AlphaBlend_I(
        HDC hdcDest,
        int nXOriginDest,
        int nYOriginDest,
        int nWidthDest,
        int nHeightDest,
        HDC hdcSrc,
        int nXOriginSrc,
        int nYOriginSrc,
        int nWidthSrc,
        int nHeightSrc,
        BLENDFUNCTION blendFunction
        );

    static
    int
    EnumFontFamiliesExW_I(
        HDC          hdc,
        __in LPLOGFONTW   pLogFont,
        FONTENUMPROC pfnFontEnumProc,
        HPROCESS         hCallerProcess,
        LPARAM       lParam,
        DWORD        dwFlags
        );

    static
    WINGDIAPI int WINAPI
    EnumFontFamiliesExW_E(
        HDC          hdc,
        __in_bcount(cbLogFont) LPLOGFONTW   pLogFont,
        size_t       cbLogFont,
        FONTENUMPROC pfnFontEnumProc,
        LPARAM       lParam,
        DWORD        dwFlags
        );

    static
    WINGDIAPI int WINAPI
    EnumFontFamiliesExW_IW(
        HDC          hdc,
        __in_bcount(cbLogFont) LPLOGFONTW   pLogFont,
        size_t       cbLogFont,
        FONTENUMPROC pfnFontEnumProc,
        LPARAM       lParam,
        DWORD        dwFlags
        );

    static
    DWORD
    SetLayout_I(
        HDC hdc,
        DWORD dwLayout
        );

    static
    DWORD
    GetLayout_I(
        HDC hdc
        );

    static
    WINGDIAPI BOOL WINAPI
    DeleteDC_E(
        HDC hdc
        );

    static
    WINGDIAPI
    BOOL
    WINAPI
    DeleteObject_E(
        HGDIOBJ hgdiobj,
        __out_opt LPVOID * ppvDIBUserMem
        );

    static
    WINGDIAPI
    HANDLE
    WINAPI
    AddFontMemResourceEx_I(
        __in_bcount(cbFont) PVOID   pbFont,
        DWORD   cbFont,
        __in_opt PVOID   pdv,
        __out DWORD   *pcFonts
        );

    static
    WINGDIAPI
    BOOL
    WINAPI
    RemoveFontMemResourceEx_I(
        HANDLE  fh
        );

    static
    WINGDIAPI
    DWORD
    OpenDisplayConfiguration_I(
        HDC hDC
        );

    static
    WINGDIAPI
    BOOL
    CloseDisplayConfiguration_I(
        DWORD dwDisplayConfigurationID
        );

    static
    WINGDIAPI
    BOOL
    GetFallbackModuleNamesForDisplayConfiguration_I(
        const __in_z LPCWSTR pwszModuleBase,
        __deref_out_ecount(*pcszModuleNames) LPWSTR **pprgwszModuleNames,
        __out DWORD *pcszModuleNames,
        const __in_z LPCWSTR pwszType,
        DWORD dwDisplayConfigurationID
    );
};

WINGDIAPI HENHMETAFILE WINAPI
CloseEnhMetaFile_I(HDC);


#endif

