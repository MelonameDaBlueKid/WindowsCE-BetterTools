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
/*++


Module Name:

    winddif.h

Abstract:

    Private entry points, defines and types for Windows CE Font drivers.
    This is a private include file instead of part of the public winddi.h becuase
    the font driver is statically linked as part of MGDI.

--*/

#ifndef _WINDDIF_
#define _WINDDIF_

#define FD_ERROR  0xFFFFFFFF
#define DDI_ERROR 0xFFFFFFFF

#ifndef _PTRDIFF_T_DEFINED
typedef int ptrdiff_t;
#define _PTRDIFF_T_DEFINED
#endif

typedef ptrdiff_t PTRDIFF;
typedef PTRDIFF*  PPTRDIFF;
typedef FLOAT     FLOATL;

// HGLYPH data type can be used to hold a UTF16 character code point (2 bytes long 
// for non-surrogate chars and is 4 bytes long for surrogates) or a 16 bit glyph index
// with the hi-word set to non-surrogate value (0xFFFF) used as an indicator. Glyph 
// index value is assumed to be less than or equal to 0xFFFF.
typedef ULONG HGLYPH;
typedef HGLYPH *PHGLYPH;

// 0xFFFFFFFF is a Unicode non-character by standard
#define HGLYPH_INVALID ((HGLYPH)-1) 

inline HGLYPH CHAR_TO_HGLYPH(UINT32 ch)
{
    return (HGLYPH)ch;
}

// 0xFFFF is an invalid surrogate hi-word - so it is clearly a HGLYPH holding a GLYPHINDEX
inline HGLYPH GLYPHINDEX_TO_HGLYPH(UINT32 glyphIndex)
{
    ASSERT(glyphIndex<=0xFFFF);    
    return (HGLYPH)( 0xFFFF0000|glyphIndex );
}

inline UINT32 HGLYPH_TO_CHAR(HGLYPH hg)
{
    // Make sure that hg is not a glyph index.
    ASSERT( 0xFFFF!=HIWORD(hg) );
    return (UINT32)hg;
}

inline UINT32 HGLYPH_TO_GLYPHINDEX(HGLYPH hg)
{
    // Make sure that hg is indeed a glyph index.
    ASSERT( 0xFFFF==HIWORD(hg) );
    return (UINT32)( 0x0000FFFF&hg );
}

inline BOOL IS_HGLYPH_CHAR(HGLYPH hg)
{
    return (0xFFFF!=HIWORD(hg));
}

inline BOOL IS_HGLYPH_GLYPHINDEX(HGLYPH hg)
{
    return (0xFFFF==HIWORD(hg));
}

inline BOOL IS_CHAR_SURROGATE(UINT32 ch)
{
    return ( (HIWORD(ch)>=0xD800) && (HIWORD(ch)<=0xDBFF) && (LOWORD(ch)>=0xDC00) && (LOWORD(ch)<=0xDFFF) );
}

inline BOOL IS_HGLYPH_SURROGATE(HGLYPH hg)
{
    return ( (HIWORD(hg)>=0xD800) && (HIWORD(hg)<=0xDBFF) && (LOWORD(hg)>=0xDC00) && (LOWORD(hg)<=0xDFFF) );
}


// signed 16 bit integer type denoting number of FUnit's
typedef SHORT FWORD;

typedef struct _POINTE
{
    FLOATL x;
    FLOATL y;
} POINTE, *PPOINTE;

typedef struct _FD_XFROM
{
    FLOATL eXX;
    FLOATL eXY;
    FLOATL eYX;
    FLOATL eYY;
} FD_XFORM, *PFD_XFROM;

// point in the 32.32 bit precision

typedef struct _POINTQF    // ptq
{
    LARGE_INTEGER x;
    LARGE_INTEGER y;
} POINTQF, *PPOINTQF;

#define GX_IDENTITY     0L
#define GX_OFFSET       1L
#define GX_SCALE        2L
#define GX_GENERAL      3L

#define XF_LTOL         0L
#define XF_INV_LTOL     1L
#define XF_LTOFX        2L
#define XF_INV_FXTOL    3L

extern "C"
ULONG APIENTRY XFORMOBJ_iGetXform(
XFORMOBJ *pxo,
XFORM    *pxform);


/////////////////////////////////////////////////////////////////////////////
// Font specific definitions


// Belongs in wingdi.h:

#define HANGEUL_CHARSET         129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136



//
// IFIMETRICS::flInfo flags
//
#define FM_INFO_TECH_TRUETYPE               0x00000001
#define FM_INFO_TECH_BITMAP                 0x00000002
#define FM_INFO_TECH_STROKE                 0x00000004
#define FM_INFO_TECH_OUTLINE_NOT_TRUETYPE   0x00000008
#define FM_INFO_ARB_XFORMS                  0x00000010
#define FM_INFO_1BPP                        0x00000020
#define FM_INFO_4BPP                        0x00000040
#define FM_INFO_8BPP                        0x00000080
#define FM_INFO_16BPP                       0x00000100
#define FM_INFO_24BPP                       0x00000200
#define FM_INFO_32BPP                       0x00000400
#define FM_INFO_INTEGER_WIDTH               0x00000800
#define FM_INFO_CONSTANT_WIDTH              0x00001000
#define FM_INFO_NOT_CONTIGUOUS              0x00002000
#define FM_INFO_PID_EMBEDDED                0x00004000
#define FM_INFO_RETURNS_OUTLINES            0x00008000
#define FM_INFO_RETURNS_STROKES             0x00010000
#define FM_INFO_RETURNS_BITMAPS             0x00020000
#define FM_INFO_UNICODE_COMPLIANT           0x00040000
#define FM_INFO_RIGHT_HANDED                0x00080000
#define FM_INFO_INTEGRAL_SCALING            0x00100000
#define FM_INFO_90DEGREE_ROTATIONS          0x00200000
#define FM_INFO_OPTICALLY_FIXED_PITCH       0x00400000
#define FM_INFO_DO_NOT_ENUMERATE            0x00800000
#define FM_INFO_ISOTROPIC_SCALING_ONLY      0x01000000
#define FM_INFO_ANISOTROPIC_SCALING_ONLY    0x02000000
#define FM_INFO_TID_EMBEDDED                0x04000000
#define FM_INFO_FAMILY_EQUIV                0x08000000
#define FM_INFO_DBCS_FIXED_PITCH            0x10000000
#define FM_INFO_NONNEGATIVE_AC              0x20000000
#define FM_INFO_IGNORE_TC_RA_ABLE           0x40000000
#define FM_INFO_TECH_TYPE1                  0x80000000

//
// IFIMETRICS::ulPanoseCulture
//
#define  FM_PANOSE_CULTURE_LATIN     0x0


//
// IFMETRICS::fsSelection flags
//
#define  FM_SEL_ITALIC          0x0001
#define  FM_SEL_UNDERSCORE      0x0002
#define  FM_SEL_NEGATIVE        0x0004
#define  FM_SEL_OUTLINED        0x0008
#define  FM_SEL_STRIKEOUT       0x0010
#define  FM_SEL_BOLD            0x0020
#define  FM_SEL_REGULAR         0x0040


typedef struct _IFIMETRICS {
    ULONG    cjThis;           // includes attached information
    ULONG    cjIfiExtra;       // sizeof IFIEXTRA if any, formerly ulVersion
    PTRDIFF  dpwszFamilyName;
    PTRDIFF  dpwszStyleName;
    PTRDIFF  dpwszFaceName;
    PTRDIFF  dpwszUniqueName;
    PTRDIFF  dpFontSim;
    LONG     lEmbedId;
    LONG     lItalicAngle;
    LONG     lCharBias;

// dpCharSet field replaced alReserved[0].
// If the 3.51 pcl minidrivers are still to work on NT 4.0 this field must not
// move because they will have 0 at this position.

    PTRDIFF  dpCharSets;
    BYTE     jWinCharSet;           // as in LOGFONT::lfCharSet
    BYTE     jWinPitchAndFamily;    // as in LOGFONT::lfPitchAndFamily
    USHORT   usWinWeight;           // as in LOGFONT::lfWeight
    ULONG    flInfo;                // see above
    USHORT   fsSelection;           // see above
    USHORT   fsType;                // see above
    FWORD    fwdUnitsPerEm;         // em height
    FWORD    fwdLowestPPEm;         // readable limit
    FWORD    fwdWinAscender;
    FWORD    fwdWinDescender;
    FWORD    fwdMacAscender;
    FWORD    fwdMacDescender;
    FWORD    fwdMacLineGap;
    FWORD    fwdTypoAscender;
    FWORD    fwdTypoDescender;
    FWORD    fwdTypoLineGap;
    FWORD    fwdAveCharWidth;
    FWORD    fwdMaxCharInc;
    FWORD    fwdCapHeight;
    FWORD    fwdXHeight;
    FWORD    fwdSubscriptXSize;
    FWORD    fwdSubscriptYSize;
    FWORD    fwdSubscriptXOffset;
    FWORD    fwdSubscriptYOffset;
    FWORD    fwdSuperscriptXSize;
    FWORD    fwdSuperscriptYSize;
    FWORD    fwdSuperscriptXOffset;
    FWORD    fwdSuperscriptYOffset;
    FWORD    fwdUnderscoreSize;
    FWORD    fwdUnderscorePosition;
    FWORD    fwdStrikeoutSize;
    FWORD    fwdStrikeoutPosition;
    BYTE     chFirstChar;           // for win 3.1 compatibility
    BYTE     chLastChar;            // for win 3.1 compatibility
    BYTE     chDefaultChar;         // for win 3.1 compatibility
    BYTE     chBreakChar;           // for win 3.1 compatibility
    WCHAR    wcFirstChar;           // lowest supported code in Unicode set
    WCHAR    wcLastChar;            // highest supported code in Unicode set
    WCHAR    wcDefaultChar;
    WCHAR    wcBreakChar;
    POINTL   ptlBaseline;           //
    POINTL   ptlAspect;             // designed aspect ratio (bitmaps)
    POINTL   ptlCaret;              // points along caret
    RECTL    rclFontBox;            // bounding box for all glyphs (font space)
    BYTE     achVendId[4];          // as per TrueType
    ULONG    cKerningPairs;
    ULONG    ulPanoseCulture;
    PANOSE   panose;
} IFIMETRICS, *PIFIMETRICS;


typedef struct _FONTOBJ
{
    ULONG   iUniq;
    ULONG   iFace;
    ULONG   cxMax;
    FLONG   flFontType;
    ULONG   iTTUniq;
    ULONG   iFile;
    SIZE    sizLogResPpi;
    ULONG   ulStyleSize;
    PVOID   pvConsumer;
    PVOID   pvProducer;
} FONTOBJ;

typedef BYTE GAMMA_TABLES[2][256];

//
// FONTOBJ::flFontType
//
#define FO_TYPE_RASTER   RASTER_FONTTYPE     /* 0x1 */
#define FO_TYPE_DEVICE   DEVICE_FONTTYPE     /* 0x2 */
#define FO_TYPE_TRUETYPE TRUETYPE_FONTTYPE   /* 0x4 */
#define FO_SIM_BOLD      0x00002000
#define FO_SIM_ITALIC    0x00004000
#define FO_EM_HEIGHT     0x00008000
#define FO_GRAY16        0x00010000          /* [1] */
#define FO_NOGRAY16      0x00020000          /* [1] */
#define FO_NOHINTS       0x00040000          /* [3] */
#define FO_NO_CHOICE     0x00080000          /* [3] */
#define FO_CLEARTYPE     0x10000000
#define FO_CLEARTYPEHORIZONTAL 0x20000000
#define FO_CLEARTYPE_COMPAT_WIDTH 0x40000000 

/*
 *   FONTOBJ callbacks
 */

extern "C"
XFORMOBJ * APIENTRY FONTOBJ_pxoGetXform(FONTOBJ *pfo);

typedef struct _GLYPHBITS
{
    POINTL      ptlOrigin;
    SIZEL       sizlBitmap;
    ULONG       iBitmapFormat;
    BYTE        aj[1];
} GLYPHBITS;

#define FO_HGLYPHS          0L

typedef union _GLYPHDEF
{
    GLYPHBITS  *pgb;
    PATHOBJ    *ppo;
} GLYPHDEF;

typedef struct _GLYPHPOS    /* gp */
{
    HGLYPH      hg;
    GLYPHDEF   *pgdf;
    POINTL      ptl;
} GLYPHPOS,*PGLYPHPOS;


// individual glyph data

// r is a unit vector along the baseline in device coordinates.
// s is a unit vector in the ascent direction in device coordinates.
// A, B, and C, are simple tranforms of the notional space versions into
// (28.4) device coordinates.  The dot products of those vectors with r
// are recorded here.  Note that the high words of ptqD are also 28.4
// device coordinates.  The low words provide extra accuracy.

// THE STRUCTURE DIFFERS IN ORDERING FROM NT 3.51 VERSION OF THE STRUCTURE.
// ptqD has been moved to the bottom.
// This requires only recompile of all the drivers.

typedef struct _GLYPHDATA {
        GLYPHDEF gdf;               // pointer to GLYPHBITS or to PATHOBJ
        HGLYPH   hg;                // glyhp handle
        FIX      fxD;               // Character increment amount: D*r.
        FIX      fxA;               // Prebearing amount: A*r.
        FIX      fxAB;              // Advancing edge of character: (A+B)*r.
        FIX      fxInkTop;          // Baseline to inkbox top along s.
        FIX      fxInkBottom;       // Baseline to inkbox bottom along s.
        RECTL    rclInk;            // Ink box with sides parallel to x,y axes
        POINTQF  ptqD;              // Character increment vector: D=A+B+C.
} GLYPHDATA;


// flAccel flags for STROBJ

// SO_FLAG_DEFAULT_PLACEMENT // defult inc vectors used to position chars
// SO_HORIZONTAL             // "left to right" or "right to left"
// SO_VERTICAL               // "top to bottom" or "bottom to top"
// SO_REVERSED               // set if horiz & "right to left" or if vert &  "bottom to top"
// SO_ZERO_BEARINGS          // all glyphs have zero a and c spaces
// SO_CHAR_INC_EQUAL_BM_BASE // base == cx for horiz, == cy for vert.
// SO_MAXEXT_EQUAL_BM_SIDE   // side == cy for horiz, == cx for vert.

// do not substitute device font for tt font even if device font sub table
// tells the driver this should be done

// SO_DO_NOT_SUBSTITUTE_DEVICE_FONT

#define SO_FLAG_DEFAULT_PLACEMENT        0x00000001
#define SO_HORIZONTAL                    0x00000002
#define SO_VERTICAL                      0x00000004
#define SO_REVERSED                      0x00000008
#define SO_ZERO_BEARINGS                 0x00000010
#define SO_CHAR_INC_EQUAL_BM_BASE        0x00000020
#define SO_MAXEXT_EQUAL_BM_SIDE          0x00000040
#define SO_DO_NOT_SUBSTITUTE_DEVICE_FONT 0x00000080
#define SO_GLYPHINDEX_TEXTOUT            0x00000100
#define SO_DXDY                          0x00000400
#define SO_CHARACTER_EXTRA               0x00000800


typedef struct _STROBJ
{
    ULONG     cGlyphs;     // # of glyphs to render
    FLONG     flAccel;     // accel flags
    ULONG     ulCharInc;   // non-zero only if fixed pitch font, equal to advanced width.
    RECTL     rclBkGround; // bk ground  rect of the string in device coords
    GLYPHPOS *pgp;         // If non-NULL then has all glyphs.
    LPWSTR    pwszOrg;     // pointer to original unicode string.
    ULONG    *pdwStr;       //pointer to dword string if any, NULL indicates normal string.
} STROBJ;

/*
 * STROBJ callbacks
 */

//
//Flags for font linking enhancements
//
#define FL_LinkIgnoreLeadingPOS                  0x00000001
#define FL_LinkIgnoreLeadingNEG                  0x00000002

VOID APIENTRY STROBJ_vEnumStart(
STROBJ *pstro);

BOOL APIENTRY STROBJ_bEnum(
    STROBJ    *pstro,
    ULONG     *pc,
    PGLYPHPOS *ppgpos
    );

#define QFF_NUMFACES                        2L

#define QFD_GLYPHANDBITMAP                  1L
#define QFD_MAXEXTENTS                      3L
#define QFD_GLYPHANDBITMAP_MISSING_GLYPH    13L

typedef struct _FD_DEVICEMETRICS {       // devm
    FLONG  flRealizedType;
    POINTE pteBase;
    POINTE pteSide;
    LONG   lD;
    FIX    fxMaxAscender;
    FIX    fxMaxDescender;
    POINTL ptlUnderline1;
    POINTL ptlStrikeOut;
    POINTL ptlULThickness;
    POINTL ptlSOThickness;
    ULONG  cxMax;                      // max pel width of bitmaps

// the fields formerly in REALIZE_EXTRA as well as some new fields:

    ULONG cyMax;      // did not use to be here
    ULONG cjGlyphMax; // (cxMax + 7)/8 * cyMax, or at least it should be

    FD_XFORM  fdxQuantized;
    LONG      lNonLinearExtLeading;
    LONG      lNonLinearIntLeading;
    LONG      lNonLinearMaxCharWidth;
    LONG      lNonLinearAvgCharWidth;

// some new fields

    LONG      lMinA;
    LONG      lMinC;
    LONG      lMinD;

    LONG      alReserved[1]; // just in case we need it.

} FD_DEVICEMETRICS, *PFD_DEVICEMETRICS;

/*
 * Text Output
 */

BOOL APIENTRY DrvTextOut(
SURFOBJ  *pso,
STROBJ   *pstro,
FONTOBJ  *pfo,
CLIPOBJ  *pco,
XLATEOBJ *pxlo,
RECTL    *prclExtra,
RECTL    *prclOpaque,
BRUSHOBJ *pboFore,
BRUSHOBJ *pboOpaque,
POINTL   *pptlOrg,
MIX       mix);


#endif  //  _WINDDIF_
