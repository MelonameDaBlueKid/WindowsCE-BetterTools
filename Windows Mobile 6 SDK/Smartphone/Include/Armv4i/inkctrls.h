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
// Copyright (c) Microsoft Corporation.  All rights reserved. 
//
// Use of this source code is subject to the terms of your Windows Mobile 
// Software Shared Source Premium Derivatives License Form or other 
// applicable Microsoft license agreement for the software. If you did not 
// accept the terms of such a license, you are not authorized to use this 
// source code.

//////////////////////////////////////////////////////////////////////
//  Module: InkCtrls.h
//
//  Description:
//
//      This file contains the public interfaces to the InkCtrls.dll
//////////////////////////////////////////////////////////////////////


#pragma once

#ifndef _INKCTRLS_H_
#define _INKCTRLS_H_

#include <windows.h>


// 
// Register the WLINKCANVAS window class. This MUST be called
// before creating a canvas window 
//
BOOL InitInkControls();


//
// InkCanvas Window Class constant
//

#define WC_INKCANVAS    L"WLINKCANVAS"


// Enum for pen types
enum IC_PENTYPE
{
    IC_PENTYPE_NORMAL, 
    IC_PENTYPE_HIGHLIGHTER
};

typedef enum IC_PENTYPE IC_PENTYPE;


// Enum for canvas types
enum IC_CANVASTYPE
{
    IC_CANVASTYPE_FIXEDCANVAS, 
    IC_CANVASTYPE_VARIABLECANVAS
};

typedef enum IC_CANVASTYPE IC_CANVASTYPE;


// Enum for editing mode
enum IC_EDITINGMODE
{
    IC_EDITINGMODE_INK = 1, 
    IC_EDITINGMODE_SELECT = 2, 
    IC_EDITINGMODE_DELETE = 3
};

typedef enum IC_EDITINGMODE IC_EDITINGMODE;


// Enum for ink encoding types
enum IC_INKENCODING
{
    IC_INKENCODING_BINARY, 
    IC_INKENCODING_BASE64,
    IC_INKENCODING_GIF,
    IC_INKENCODING_BASE64GIF
};

typedef enum IC_INKENCODING IC_INKENCODING;


// The penstyle strucutre
typedef struct PENSTYLE
{
    size_t         cbSize;              // The size of the structure
    float          dPenWidth;           // Widht of the pen in mm
    COLORREF       crColor;             // The color of the pen
    IC_PENTYPE     ptPenType;           // The type of the pen
}PENSTYLE;


// The structure for notifying the WM_CHAR message
// NM_CHAR is not defined on Windows CE
typedef struct NMCHR
{
    NMHDR hdr;              // contains additional info. about this notification
    UINT   ch;              // Character that is being processed. The wParam of the WM_CHAR message
    DWORD info;             // lParam of the WM_CHAR message
} NMCHR, *LPNMCHR;


// The structure for notifying the ICNM_STROKEADDED
// and ICNM_STROKEDELETED message
typedef struct NMSTROKE
{
    NMHDR hdr;              // contains additional info. about this notification
    long  lStrokeID;        // Stroke ID of the added/deleted strokes. If multiple strokes 
                            // are added/deleted, this is 0.
} NMSTROKE, *LPNMSTROKE;




//////////////////////////////////////////////////////////
// InkCanvas and InkControl Window Style definitinos

// ICS_FIXEDCANVAS
// This flag creates a fixed canvas
#define ICS_FIXEDCANVAS             0x00010000



#define ICM_BASE                (WM_USER + 500)


/////////////////////////////////////////////////////////////////////////////
// User defined messages that InkCanvas will handle
/////////////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------------
// ICM_GETMODE
//
// Returns the current editing mode
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
// Return value
// 
//      editingmode: One of the values of IC_EDITINGMODE
//
// --------------------------------------------------------------------------
#define ICM_GETMODE             ICM_BASE + 1 


// --------------------------------------------------------------------------
// ICM_SETMODE
//
// Sets the editing mode
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) (IC_EDITINGMODE) editingmode
//
//
// Parameters
//
//  editingmode
// 
//  The mode to which we wish to switch. One of IC_EDITINGMODE values.
//
// Return value
//
//  Returns 0 if there are errors
// --------------------------------------------------------------------------
#define ICM_SETMODE             ICM_BASE + 2 


// --------------------------------------------------------------------------
// ICM_GETINK
//
// Returns a reference to the ink object in the canvas
//
// lParam = (LPARAM) (IInkDisp**) ppInk
// wparam = (WPARAM) 0
//
//
// Parameters
//
//  ppInk
//
//  Pointer to a pointer to an ink object. Should not be NULL.
//
// Return value
//
//  Returns 0 if there are errors
// --------------------------------------------------------------------------
#define ICM_GETINK              ICM_BASE + 3  


// --------------------------------------------------------------------------
// ICM_GETINKDATA
//
// Returns the Ink data in the requested format
//
// lParam = (LPARAM) (VARIANT*) pvData
// wParam = (WPARAM) (IC_INKENCODING) encoding
//
//
// Parameters
//
//  pvData
//  
//  Pointer to a variant. The caller has to call VariantClear (to free the 
//  memory allocated for the data). 
//
//  encoding
//
//  The encoding in which the data is required. One of the IC_INKENCODING values.
//
// Return value
// 
//  Returns 0 if there are errors.
// 
// Remarks
//  Upon successfully saving the data *pvData will have the save ink data
//  Variant type is either 
//     VT_UI1|VT_ARRAY   - for binary formats: isf and gif
//     VT_BSTR           - for base64 formats: base64isf and base64gif
//  Caller has to call VariantClear() to free the memory allocated
// --------------------------------------------------------------------------
#define ICM_GETINKDATA          ICM_BASE + 4


// --------------------------------------------------------------------------
// ICM_GETINKDATAASBITMAP
//
// Returns a bitmap of the ink on the canvas.
//
// lParam = (LPARAM) (HBITMAP*) pHBitmap
// wParam = (WPARAM) 0
//
//
// Parameters
// 
//  pHBitmap
// 
//  Pointer to an HBITMAP. The bitmap is created by us and its the caller's 
//  responsibility to free it.
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_GETINKDATAASBITMAP  ICM_BASE + 5


// --------------------------------------------------------------------------
// ICM_LOADINKDATA
//
// Loads the ink data supplied into the canvas. This discards the existing 
// ink data.
//
// lParam = (LPARAM) (VARIANT*) pvData
// wParam = (WPARAM) 0
//
//
// Parameters
// 
//  pvData
// 
//  Pointer to a variant. The data supplied in the variant is loaded into the ink
//  on the canvas, replacing whatever is already there.
//
// Return value
// 
//  Returns 0 if there are errors.
//
// Remarks
//  Variant type is either 
//     VT_UI1|VT_ARRAY   - for binary formats: isf and gif
//     VT_BSTR           - for base64 formats: base64isf and base64gif
// --------------------------------------------------------------------------
#define ICM_LOADINKDATA         ICM_BASE + 6


// --------------------------------------------------------------------------
// ICM_CLEARCANVAS
//
// Clears the canvas. This action cannot be undone.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_CLEARCANVAS         ICM_BASE + 7


// --------------------------------------------------------------------------
// ICM_SETPENSTYLE
//
// Sets the supplied penstyle as the new penstyle for the canvas.
//
// lParam = (LPARAM) (PENSTYLE*) pPenstyle
// wParam = (WPARAM) 0
//
// Parameters
//
//  pPenstyle 
//
//  Pointer to a penstyle structure which has the new penstyle info. The size field
//  (cbSize) must be filled in by the caller.
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETPENSTYLE         ICM_BASE + 8


// --------------------------------------------------------------------------
// ICM_GETPENSTYLE
//
// Returns the current penstyle being used.
//
// lParam = (LPARAM) (PENSTYLE*) pPenstyle
// wParam = (WPARAM) 0
//
// Parameters
//
//  pPenstyle 
//
//  Pointer to a penstyle structure. This is where we fill in the current penstyle
//  info. The structure should be allocated by the caller and the size field (cbSize) 
//  must be filled in by the caller.
//  
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_GETPENSTYLE         ICM_BASE + 9


// --------------------------------------------------------------------------
// ICM_SETKBKGNDCOLOR
//
// Sets the background color of the canvas
//
// lParam = (LPARAM) (COLOREF) color
// wParam = (WPARAM) 0
//
// Parameters
//
//  color
//
//  The color which we want to set the background to. To create a COLORREF value, 
//  use the RGB macro.
//  
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETBKGNDCOLOR       ICM_BASE + 10


// --------------------------------------------------------------------------
// ICM_CANCOPY
//
// Returns if it's possible to copy data to the clipboard.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  nSelected: The number of strokes that can be copied. 0 if no data can be copied.
// --------------------------------------------------------------------------
#define ICM_CANCOPY             ICM_BASE + 11


// --------------------------------------------------------------------------
// ICM_CANPASTE
//
// Returns if it's possible to paste data from the clipboard to the canvas
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 0 if data cannot be pasted
// --------------------------------------------------------------------------
#define ICM_CANPASTE            ICM_BASE + 12


// --------------------------------------------------------------------------
// ICM_CANUNDO
//
// Returns if an undo operation can be performed
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 1 if undo can be performed
// --------------------------------------------------------------------------
#define ICM_CANUNDO             ICM_BASE + 13


// --------------------------------------------------------------------------
// ICM_CANREDO
//
// Returns if a redo operation can be performed
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 1 if a redo can be performed
// --------------------------------------------------------------------------
#define ICM_CANREDO             ICM_BASE + 14


// --------------------------------------------------------------------------
// ICM_GETZOOM
//
// Returns the current zoom level
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  nZoomLevel: The current zoom level in percentage
// --------------------------------------------------------------------------
#define ICM_GETZOOM             ICM_BASE + 15


// --------------------------------------------------------------------------
// ICM_SETZOOM
//
// Sets the current zoom level
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) (LONG) nZoomLevel
//
// Parameters
//
//  nZoomlevel
//
//  Zoom level as a percentage. The range is from 20% to 500%
//
// 
// Return value
// 
//  Returns 0 if there are errors
// --------------------------------------------------------------------------
#define ICM_SETZOOM             ICM_BASE + 16


// --------------------------------------------------------------------------
// ICM_GETCANVASSIZE
//
// Returns the size of the canvas in pixels.
//
// lParam = (LPARAM) (SIZE*) pCanvasSize
// wParam = (WPARAM) 0
//
// Parameters
//
//  pCanvasSize
//
//  Pointer to a user allocated SIZE structure. The dimensions returned are in 
//  pixels and they are the dimensions of the actual canvas.
//  
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_GETCANVASSIZE       ICM_BASE + 18


// --------------------------------------------------------------------------
// ICM_SETCANVASSIZE
//
// Set the size of the current canvas
//
// lParam = (LPARAM) (SIZE*) pCanvasSize
// wParam = (WPARAM) 0
//
// Parameters
//
//  pCanvasSize
//
//  Pointer to a SIZE structure. The dimensions are in pixles. The ink object is 
//  clipped to fit inside the canvas size supplied.
//  
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETCANVASSIZE       ICM_BASE + 19


// --------------------------------------------------------------------------
// ICM_REDO
//
// Redo the last undone action.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 0 if redo was unsuccessful
// --------------------------------------------------------------------------
#define ICM_REDO                ICM_BASE + 20


// --------------------------------------------------------------------------
// ICM_UNDO
//
// Undo the most recent undoable action
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 0 if undo was unsuccessful
// --------------------------------------------------------------------------
#define ICM_UNDO                ICM_BASE + 40


// --------------------------------------------------------------------------
// ICM_SETCANVASCOLOR
//
// Sets the color of the canvas.
//
// lParam = (LPARAM) (COLORREF) color
// wParam = (WPARAM) 0
//
// Parameters
//
//  color
//
//  The color which we want to set the canvas to. To create a COLORREF value, 
//  use the RGB macro. Note that this call is different from ICM_SETBKGNDCOLOR.
//  That color is used to paint the region on the window which lies outside the
//  canvas.
//  
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETCANVASCOLOR      ICM_BASE + 21


// --------------------------------------------------------------------------
// ICM_ERASEALLINK
//
// Erase all the ink on the canvas. This action can be undone.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_ERASEALLINK         ICM_BASE + 22


// --------------------------------------------------------------------------
// ICM_SETAUTOSCROLL
//
// Use this to enable/disable autoscrolling when the user inks near the end of
// the canvas window. By default autoscroll is off. This is only applicable for
// scrolling vertically.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) (VARIANT_BOOL) vbAutoScroll
//
// Parameters
//
//  vbAutoScroll
//
//  VARIANT_BOOL indicating whether scrolling should be on(VARIANT_TRUE) or 
//  off(VARIANT_FALSE).
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETAUTOSCROLL       ICM_BASE + 23


// --------------------------------------------------------------------------
// ICM_SETAUTOEXPAND
//
// Turns canvas expansion on or off. When enabled, the canvas is expanded when the 
// user inks near the edge of the canvas. Canvas expansion happens in both directions. 
// 
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) (VARIANT_BOOL) vbAutoScroll
//
// Parameters
//
//  vbAutoScroll
//
//  VARIANT_BOOL indicating whether expansion should be on(VARIANT_TRUE) or 
//  off(VARIANT_FALSE).
//
// Note
//  This can be enabled only for variable canvas types. This message is different 
//  from autoscroll. This merely expands the canvas but doesn't neccessarily scroll it. 
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETAUTOEXPAND       ICM_BASE + 24


// --------------------------------------------------------------------------
// ICM_GETUNDOCOUNT
//
// Returns the number of undo operations that can be performed.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
//
// Return value
// 
//  nUndoCount: The number of undo operations that can be performed.
// --------------------------------------------------------------------------
#define ICM_GETUNDOCOUNT        ICM_BASE + 25 


// --------------------------------------------------------------------------
// ICM_GETNOTIFICATIONMASK
//
// Returns the mask of the notifications the user has subscribed to.
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) 0
//
// Note
//  By default the ICMASK_DEFAULT is used. 
//  
// Return value
// 
//  lMask: The current notification mask.
// --------------------------------------------------------------------------
#define ICM_GETNOTIFICATIONMASK ICM_BASE + 26


// --------------------------------------------------------------------------
// ICM_SETNOTIFICATIONMASK
//
// Sets the mask of the notifications one would like to receive.
// 
//
// lParam = (LPARAM) 0
// wParam = (WPARAM) (LONG) lMask
//
// Parameters
//
//  lMask
//
//  This could be a bitwise OR of the various notifications. ICNM_xxx defines
//  the notifications that canvas provides.
//
// Return value
// 
//  Returns 0 if there are errors.
// --------------------------------------------------------------------------
#define ICM_SETNOTIFICATIONMASK ICM_BASE + 27


/////////////////////////////////////////////////////////////////////////////
// Notification codes that canvas passes on to the parent window by sending the
// WM_NOTIFY message. 
/////////////////////////////////////////////////////////////////////////////


// Base for the notification codes
#define ICNM_BASE               ICM_BASE + 100


// --------------------------------------------------------------------------
// ICNM_CHAR 
//
// A WM_NOTIFY message is sent to the parent with this notification code when
// we don't handle the WM_CHAR message. 
//
// lParam = (LPARAM) (LPNMHDR) pNmChar
// wParam = (WPARAM) (int) idCtrl
//
// Parameters
//
//  pNmChar 
//
//  Pointer to an NMCHR structure containing information about the character.
//
//  idCtrl
// 
//  The control ID of this window
//
// --------------------------------------------------------------------------
#define ICNM_CHAR               ICNM_BASE + 1


// --------------------------------------------------------------------------
// ICNM_STROKEADDED
//
// A WM_NOTIFY message is sent to the parent with this notification code when
// a new stroke is added.
//
// lParam = (LPARAM) (NMSTROKE*) pNmStroke
// wParam = (WPARAM) (int) idCtrl
//
// Parameters
//
//  pNmStroke
//
//  Pointer to an NMSTROKE structure containing information about the stroke added.
//
//  idCtrl
// 
//  The control ID of this window
//
// --------------------------------------------------------------------------
#define ICNM_STROKEADDED        ICNM_BASE + 2


// --------------------------------------------------------------------------
// ICNM_STROKEDELETED
//
// A WM_NOTIFY message is sent to the parent with this notification code when
// stroke(s) are deleted.
//
// lParam = (LPARAM) (NMSTROKE*) pNmStroke
// wParam = (WPARAM) (int) idCtrl
//
// Parameters
//
//  pNmStroke
//
//  Pointer to an NMSTROKE structure containing information about the deleted stroke(s).
//
//  idCtrl
// 
//  The control ID of this window
//
// --------------------------------------------------------------------------
#define ICNM_STROKEDELETED      ICNM_BASE + 4


// Notification masks that apps can set for receiving notifications

// Mask set to receive the ICNM_CHAR notification
#define ICMASK_CHAR             0x00000001

// Mask set to receive the ICNM_STROKEADDED notification
#define ICMASK_STROKEADDED      0x00000002

// Mask set to receive the ICNM_STROKEDELETED notification
#define ICMASK_STROKEDELETED    0x00000004

// The default mask. Only forwards the ICNM_CHAR notification
#define ICMASK_DEFAULT          0x00000001

#endif
