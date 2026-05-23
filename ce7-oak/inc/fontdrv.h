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
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


Module Name:

    font.h

Abstract:

    TrueType data types and prototypes

-------------------------------------------------------------------*/

#ifndef _FONT_H_
#define _FONT_H_

//
// Default height used if user passes in zero for lfHeight in the LOGFONT -- 12 point.
//
#define GDI_DEFAULT_LFHEIGHT    (-16)

//#define DO_SHUTDOWN               // commenting out this line should disable all system
                                    // shutdown code such as freeing memory, etc.


/* Specific types and definitions       */

#define DRV_ERROR               0xFFFFFFFF

#define DWORD_ALIGN(x) (((x) + 3L) & ~3L)

#define CJ_CTGD(cx,cy) (DWORD_ALIGN(offsetof(GLYPHBITS,aj)) + DWORD_ALIGN((cx) * (cy)))

/* types defined for font driver interface  */

typedef PIFIMETRICS (* FDQUERYFONT)( DHPDEV, ULONG, ULONG, ULONG* );
typedef LONG        (* FDQUERYFONTFILE)( ULONG, ULONG, ULONG, ULONG* );
typedef LONG        (* FDQUERYFONTDATA)( DHPDEV, FONTOBJ*, ULONG, HGLYPH, GLYPHDATA*, PVOID, ULONG );
typedef void        (* FDDESTROYFONT)( FONTOBJ* );
typedef ULONG       (* FDLOADFONTFILE)( ULONG, ULONG_PTR*, PVOID*, ULONG*, struct DESIGNVECTOR*, ULONG, ULONG );
typedef BOOL        (* FDUNLOADFONTFILE)( ULONG );
typedef ULONG       (* FDGETFONTTABLE)( ULONG, ULONG, ULONG, PTRDIFF, ULONG, PBYTE, PBYTE*, ULONG* );

typedef struct 
{
    HINSTANCE           library;
    FDQUERYFONT         pfnQueryFont;
    FDQUERYFONTFILE     pfnQueryFontFile;
    FDQUERYFONTDATA     pfnQueryFontData;
    FDDESTROYFONT       pfnDestroyFont;
    FDLOADFONTFILE      pfnLoadFontFile;
    FDUNLOADFONTFILE    pfnUnLoadFontFile;
    FDGETFONTTABLE      pfnGetFontTable;
} FD_INTERFACE, *LPFD_INTERFACE;

typedef struct
{
    DWORD dwLogPixelsX;
    DWORD dwLogPixelsY;
} DriverDpi_t;

//
// ClearType helper functions, located in the mgct component.
//
VOID vMergeClearTypeGlyphs(
    STROBJ         *pstro,
    PUCHAR          pjDstStart,
    LONG            cbDstSize
    );

extern "C" ULONG ulClearTypeFilter(
    GLYPHBITS*  pgb, 
    GLYPHDATA*  pgd,
    PIFIMETRICS pifi
    );

// Masks to extract pitch and family values from LOGFONT member lfPitchAndFamily
#define PITCH_SET (DEFAULT_PITCH | FIXED_PITCH | VARIABLE_PITCH)
#define FF_SET    (FF_DONTCARE | FF_ROMAN | FF_SWISS | FF_MODERN | FF_SCRIPT | FF_DECORATIVE)

#define WIN31_BITMAP_EMBOLDEN_CRITERIA(lPen)       (lPen>(FW_BOLD-FW_NORMAL)/2)
#define FM_WEIGHT_SIMULATED_WEIGHT        ((FW_BOLD-FW_NORMAL)*2/5)

/* API definitions  */
/* text function prototypes */

SCODE       LoadFontFile(
                LPTSTR  lpFileName,
                BYTE**  lppMem,
                UINT32* piFileSize,
                DWORD*  pdwOID,
                DWORD*  pdwFileType,
                HANDLE* phMapping,
                PVOID   pbFont,
                DWORD   cbFont
                );

void        UnloadFontFile (void *lppMem, DWORD dwFileType, HANDLE hMapping);

BOOL        InitText();
void        ShutdownText();

SCODE       deAddProcessOwnedFont(
                LPCTSTR lpFileName,
                UINT32  pid,
                UINT32* cbFontsAdded,
                PVOID   pbFont,
                DWORD   cbFont,
                HANDLE* phFont);

SCODE       deRemoveProcessOwnedFont(
                LPCTSTR lpFileName,
                UINT32  pid,
                UINT32* cbFontsRemoved
                );

void        deRemoveAllProcessFonts(UINT32 pid, UINT32 *cbResourcesRemoved);

SCODE       deEnumFonts(DriverDpi_t * pDriverDpi, LPCTSTR lpszFamName, BYTE *pEnumData, 
                UINT32 iEnumAlloc, UINT32 *piEnumActual);
SCODE       deEnumFontsEx(DriverDpi_t * pDriverDpi, LPCTSTR lpszFamName, BYTE *pEnumData, 
                UINT32 iEnumAlloc, UINT32 *piEnumActual, BYTE CharSet);

bool        GetMemFontName(
                PVOID  hMemFont,
                LPTSTR szName,
                UINT32 ccName);

#endif // _FONT_H_
