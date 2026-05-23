/*---------------------------------------------------------------------------*\
 *
 * (c) Copyright Microsoft Corp. 1996 All Rights Reserved
 *
 *  module: htmlctrl.h
 *  date:
 *  author: scottsh
 *
\*---------------------------------------------------------------------------*/

#ifndef __HTMLCTRL_H__
#define __HTMLCTRL_H__

////////////////////////////////////////////////////////////////////////////////


#define DTM_ADDTEXT				(WM_USER + 101)
#define DTM_ADDTEXTW			(WM_USER + 102)
#define DTM_SETIMAGE			(WM_USER + 103)
#define DTM_ENDOFSOURCE			(WM_USER + 104)
#define DTM_ANCHOR				(WM_USER + 105)
#define DTM_ANCHORW				(WM_USER + 106)
#define DTM_ENABLESHRINK		(WM_USER + 107)
#define DTM_SCROLLINTOVIEW		(WM_USER + 108)
#define DTM_IMAGEFAIL			(WM_USER + 109)
#define DTM_REALLYDONE			(WM_USER + 110)
#define DTM_SELECTALL			(WM_USER + 111)
#define DTM_ISSELECTION			(WM_USER + 112)
#define DTM_CLEAR				(WM_USER + 113)
#define DTM_CLEAREXCEPTSCRIPT	(WM_USER + 114)

#define NM_HOTSPOT				(WM_USER + 101)
#define NM_INLINE_IMAGE			(WM_USER + 102)
#define NM_INLINE_SOUND			(WM_USER + 103)
#define NM_TITLE				(WM_USER + 104)
#define NM_META					(WM_USER + 105)
#define NM_BASE					(WM_USER + 106)
#define NM_CONTEXTMENU			(WM_USER + 107)

#define DISPLAYCLASS	TEXT("DISPLAYCLASS")

#ifdef __cplusplus
extern "C"
#endif
BOOL InitHTMLControl(HINSTANCE hinst);

typedef struct tagNM_HTMLVIEW { 
    NMHDR	hdr; 
  	LPSTR	szTarget;
	LPSTR	szData;
	DWORD	dwCookie;
} NM_HTMLVIEW; 

typedef struct tagINLINEIMAGEINFO {
	DWORD	dwCookie;
	// WHATEVER else... decimation %, etc...
	int iOrigHeight;
	int iOrigWidth;
	HBITMAP hbm;
	BOOL bOwnBitmap;
} INLINEIMAGEINFO, *LPINLINEIMAGEINFO;

// It's only a BACKGROUND hit if it didn't hit anything else interesing. :)
#define HTMLCONTEXT_BACKGROUND			0x00
#define HTMLCONTEXT_LINK				0x01
#define HTMLCONTEXT_IMAGE				0x02
#define HTMLCONTEXT_IMAGENOTLOADED		0x04

// BE CAREFUL.  The pointers in this structure are pointers to the real data
// in the HTML Control (no point to make copies really...)
// Just make sure you don't screw them up.

typedef struct tagNM_HTMLCONTEXT {
    NMHDR		hdr; 
	POINT		pt;
	UINT		uTypeFlags;
	LPTSTR		szLinkHREF;
	LPTSTR		szImageSrc;
	HBITMAP		hbmImage;
	DWORD		dwImageCookie;
	struct IImageRender *pImageRender;
} NM_HTMLCONTEXT;

////////////////////////////////////////////////////////////////////////////////

#endif //__HTMLCTRL_H__
