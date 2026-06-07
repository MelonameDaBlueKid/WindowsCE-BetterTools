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

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Tue May 02 19:01:52 2006
 */
/* Compiler settings for .\msinkaut.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __msinkaut_h__
#define __msinkaut_h__

/* Forward Declarations */ 

#ifndef __IInkRectangle_FWD_DEFINED__
#define __IInkRectangle_FWD_DEFINED__
typedef interface IInkRectangle IInkRectangle;
#endif 	/* __IInkRectangle_FWD_DEFINED__ */


#ifndef __IInkExtendedProperty_FWD_DEFINED__
#define __IInkExtendedProperty_FWD_DEFINED__
typedef interface IInkExtendedProperty IInkExtendedProperty;
#endif 	/* __IInkExtendedProperty_FWD_DEFINED__ */


#ifndef __IInkExtendedProperties_FWD_DEFINED__
#define __IInkExtendedProperties_FWD_DEFINED__
typedef interface IInkExtendedProperties IInkExtendedProperties;
#endif 	/* __IInkExtendedProperties_FWD_DEFINED__ */


#ifndef __IInkDrawingAttributes_FWD_DEFINED__
#define __IInkDrawingAttributes_FWD_DEFINED__
typedef interface IInkDrawingAttributes IInkDrawingAttributes;
#endif 	/* __IInkDrawingAttributes_FWD_DEFINED__ */


#ifndef __IInkStrokeDisp_FWD_DEFINED__
#define __IInkStrokeDisp_FWD_DEFINED__
typedef interface IInkStrokeDisp IInkStrokeDisp;
#endif 	/* __IInkStrokeDisp_FWD_DEFINED__ */


#ifndef __IInkTransform_FWD_DEFINED__
#define __IInkTransform_FWD_DEFINED__
typedef interface IInkTransform IInkTransform;
#endif 	/* __IInkTransform_FWD_DEFINED__ */


#ifndef __IInkRecognizer_FWD_DEFINED__
#define __IInkRecognizer_FWD_DEFINED__
typedef interface IInkRecognizer IInkRecognizer;
#endif 	/* __IInkRecognizer_FWD_DEFINED__ */


#ifndef __IInkRecognizers_FWD_DEFINED__
#define __IInkRecognizers_FWD_DEFINED__
typedef interface IInkRecognizers IInkRecognizers;
#endif 	/* __IInkRecognizers_FWD_DEFINED__ */


#ifndef ___IInkRecognitionEvents_FWD_DEFINED__
#define ___IInkRecognitionEvents_FWD_DEFINED__
typedef interface _IInkRecognitionEvents _IInkRecognitionEvents;
#endif 	/* ___IInkRecognitionEvents_FWD_DEFINED__ */


#ifndef __IInkRecognizerContext_FWD_DEFINED__
#define __IInkRecognizerContext_FWD_DEFINED__
typedef interface IInkRecognizerContext IInkRecognizerContext;
#endif 	/* __IInkRecognizerContext_FWD_DEFINED__ */


#ifndef __IInkRecognitionResult_FWD_DEFINED__
#define __IInkRecognitionResult_FWD_DEFINED__
typedef interface IInkRecognitionResult IInkRecognitionResult;
#endif 	/* __IInkRecognitionResult_FWD_DEFINED__ */


#ifndef __IInkRecognitionAlternate_FWD_DEFINED__
#define __IInkRecognitionAlternate_FWD_DEFINED__
typedef interface IInkRecognitionAlternate IInkRecognitionAlternate;
#endif 	/* __IInkRecognitionAlternate_FWD_DEFINED__ */


#ifndef __IInkRecognitionAlternates_FWD_DEFINED__
#define __IInkRecognitionAlternates_FWD_DEFINED__
typedef interface IInkRecognitionAlternates IInkRecognitionAlternates;
#endif 	/* __IInkRecognitionAlternates_FWD_DEFINED__ */


#ifndef __IInkWordList_FWD_DEFINED__
#define __IInkWordList_FWD_DEFINED__
typedef interface IInkWordList IInkWordList;
#endif 	/* __IInkWordList_FWD_DEFINED__ */


#ifndef __IInkDisp_FWD_DEFINED__
#define __IInkDisp_FWD_DEFINED__
typedef interface IInkDisp IInkDisp;
#endif 	/* __IInkDisp_FWD_DEFINED__ */


#ifndef __IInkStrokes_FWD_DEFINED__
#define __IInkStrokes_FWD_DEFINED__
typedef interface IInkStrokes IInkStrokes;
#endif 	/* __IInkStrokes_FWD_DEFINED__ */


#ifndef __IInkCustomStrokes_FWD_DEFINED__
#define __IInkCustomStrokes_FWD_DEFINED__
typedef interface IInkCustomStrokes IInkCustomStrokes;
#endif 	/* __IInkCustomStrokes_FWD_DEFINED__ */


#ifndef __IInkRenderer_FWD_DEFINED__
#define __IInkRenderer_FWD_DEFINED__
typedef interface IInkRenderer IInkRenderer;
#endif 	/* __IInkRenderer_FWD_DEFINED__ */


#ifndef __IInkCursor_FWD_DEFINED__
#define __IInkCursor_FWD_DEFINED__
typedef interface IInkCursor IInkCursor;
#endif 	/* __IInkCursor_FWD_DEFINED__ */


#ifndef __IInkOverlay_FWD_DEFINED__
#define __IInkOverlay_FWD_DEFINED__
typedef interface IInkOverlay IInkOverlay;
#endif 	/* __IInkOverlay_FWD_DEFINED__ */


#ifndef ___IInkEvents_FWD_DEFINED__
#define ___IInkEvents_FWD_DEFINED__
typedef interface _IInkEvents _IInkEvents;
#endif 	/* ___IInkEvents_FWD_DEFINED__ */


#ifndef ___IInkStrokesEvents_FWD_DEFINED__
#define ___IInkStrokesEvents_FWD_DEFINED__
typedef interface _IInkStrokesEvents _IInkStrokesEvents;
#endif 	/* ___IInkStrokesEvents_FWD_DEFINED__ */


#ifndef ___IInkOverlayEvents_FWD_DEFINED__
#define ___IInkOverlayEvents_FWD_DEFINED__
typedef interface _IInkOverlayEvents _IInkOverlayEvents;
#endif 	/* ___IInkOverlayEvents_FWD_DEFINED__ */


#ifndef __InkRectangle_FWD_DEFINED__
#define __InkRectangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRectangle InkRectangle;
#else
typedef struct InkRectangle InkRectangle;
#endif /* __cplusplus */

#endif 	/* __InkRectangle_FWD_DEFINED__ */


#ifndef __InkProperty_FWD_DEFINED__
#define __InkProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkProperty InkProperty;
#else
typedef struct InkProperty InkProperty;
#endif /* __cplusplus */

#endif 	/* __InkProperty_FWD_DEFINED__ */


#ifndef __InkProperties_FWD_DEFINED__
#define __InkProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkProperties InkProperties;
#else
typedef struct InkProperties InkProperties;
#endif /* __cplusplus */

#endif 	/* __InkProperties_FWD_DEFINED__ */


#ifndef __InkDrawingAttributes_FWD_DEFINED__
#define __InkDrawingAttributes_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkDrawingAttributes InkDrawingAttributes;
#else
typedef struct InkDrawingAttributes InkDrawingAttributes;
#endif /* __cplusplus */

#endif 	/* __InkDrawingAttributes_FWD_DEFINED__ */


#ifndef __InkTransform_FWD_DEFINED__
#define __InkTransform_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkTransform InkTransform;
#else
typedef struct InkTransform InkTransform;
#endif /* __cplusplus */

#endif 	/* __InkTransform_FWD_DEFINED__ */


#ifndef __InkDisp_FWD_DEFINED__
#define __InkDisp_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkDisp InkDisp;
#else
typedef struct InkDisp InkDisp;
#endif /* __cplusplus */

#endif 	/* __InkDisp_FWD_DEFINED__ */


#ifndef __InkStrokes_FWD_DEFINED__
#define __InkStrokes_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkStrokes InkStrokes;
#else
typedef struct InkStrokes InkStrokes;
#endif /* __cplusplus */

#endif 	/* __InkStrokes_FWD_DEFINED__ */


#ifndef __InkRenderer_FWD_DEFINED__
#define __InkRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRenderer InkRenderer;
#else
typedef struct InkRenderer InkRenderer;
#endif /* __cplusplus */

#endif 	/* __InkRenderer_FWD_DEFINED__ */


#ifndef __InkOverlay_FWD_DEFINED__
#define __InkOverlay_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkOverlay InkOverlay;
#else
typedef struct InkOverlay InkOverlay;
#endif /* __cplusplus */

#endif 	/* __InkOverlay_FWD_DEFINED__ */


#ifndef __InkRecognizers_FWD_DEFINED__
#define __InkRecognizers_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRecognizers InkRecognizers;
#else
typedef struct InkRecognizers InkRecognizers;
#endif /* __cplusplus */

#endif 	/* __InkRecognizers_FWD_DEFINED__ */


#ifndef __InkRecognizerContext_FWD_DEFINED__
#define __InkRecognizerContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRecognizerContext InkRecognizerContext;
#else
typedef struct InkRecognizerContext InkRecognizerContext;
#endif /* __cplusplus */

#endif 	/* __InkRecognizerContext_FWD_DEFINED__ */


#ifndef __InkWordList_FWD_DEFINED__
#define __InkWordList_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkWordList InkWordList;
#else
typedef struct InkWordList InkWordList;
#endif /* __cplusplus */

#endif 	/* __InkWordList_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_msinkaut_0000 */
/* [local] */ 

#define _XFORM_
#include <WLiteError.h> 
#pragma once
typedef /* [hidden] */ 
enum DISPID_INKRECTANGLE
    {	DISPID_IRTOP	= 1,
    DISPID_IRLEFT	= DISPID_IRTOP + 1,
    DISPID_IRBOTTOM	= DISPID_IRLEFT + 1,
    DISPID_IRRIGHT	= DISPID_IRBOTTOM + 1,
    DISPID_IRGETRECTANGLE	= DISPID_IRRIGHT + 1,
    DISPID_IRSETRECTANGLE	= DISPID_IRGETRECTANGLE + 1,
    DISPID_IRDATA	= DISPID_IRSETRECTANGLE + 1
    }	DISPID_INKRECTANGLE;

typedef /* [hidden] */ 
enum DISPID_INKEXTENDEDPROPERTY
    {	DISPID_IEPGUID	= 1,
    DISPID_IEPDATA	= DISPID_IEPGUID + 1
    }	DISPID_INKEXTENDEDPROPERTY;

typedef /* [hidden] */ 
enum DISPID_INKEXTENDEDPROPERTIES
    {	DISPID_IEPS_NEWENUM	= DISPID_NEWENUM,
    DISPID_IEPSITEM	= DISPID_VALUE,
    DISPID_IEPSCOUNT	= 1,
    DISPID_IEPSADD	= DISPID_IEPSCOUNT + 1,
    DISPID_IEPSREMOVE	= DISPID_IEPSADD + 1,
    DISPID_IEPSCLEAR	= DISPID_IEPSREMOVE + 1,
    DISPID_IEPSDOESPROPERTYEXIST	= DISPID_IEPSCLEAR + 1
    }	DISPID_INKEXTENDEDPROPERTIES;

typedef /* [hidden] */ 
enum DISPID_INKDRAWINGATTRIBUTES
    {	DISPID_DAHEIGHT	= 1,
    DISPID_DACOLOR	= DISPID_DAHEIGHT + 1,
    DISPID_DAWIDTH	= DISPID_DACOLOR + 1,
    DISPID_DAFITTOCURVE	= DISPID_DAWIDTH + 1,
    DISPID_DAIGNOREPRESSURE	= DISPID_DAFITTOCURVE + 1,
    DISPID_DAANTIALIASED	= DISPID_DAIGNOREPRESSURE + 1,
    DISPID_DATRANSPARENCY	= DISPID_DAANTIALIASED + 1,
    DISPID_DARASTEROPERATION	= DISPID_DATRANSPARENCY + 1,
    DISPID_DAPENTIP	= DISPID_DARASTEROPERATION + 1,
    DISPID_DACLONE	= DISPID_DAPENTIP + 1,
    DISPID_DAEXTENDEDPROPERTIES	= DISPID_DACLONE + 1
    }	DISPID_INKDRAWINGATTRIBUTES;

typedef /* [hidden] */ 
enum DISPID_INKSTROKEDISP
    {	DISPID_ISDINKINDEX	= 1,
    DISPID_ISDID	= DISPID_ISDINKINDEX + 1,
    DISPID_ISDGETBOUNDINGBOX	= DISPID_ISDID + 1,
    DISPID_ISDDRAWINGATTRIBUTES	= DISPID_ISDGETBOUNDINGBOX + 1,
    DISPID_ISDFINDINTERSECTIONS	= DISPID_ISDDRAWINGATTRIBUTES + 1,
    DISPID_ISDGETRECTANGLEINTERSECTIONS	= DISPID_ISDFINDINTERSECTIONS + 1,
    DISPID_ISDCLIP	= DISPID_ISDGETRECTANGLEINTERSECTIONS + 1,
    DISPID_ISDHITTESTCIRCLE	= DISPID_ISDCLIP + 1,
    DISPID_ISDNEARESTPOINT	= DISPID_ISDHITTESTCIRCLE + 1,
    DISPID_ISDSPLIT	= DISPID_ISDNEARESTPOINT + 1,
    DISPID_ISDEXTENDEDPROPERTIES	= DISPID_ISDSPLIT + 1,
    DISPID_ISDINK	= DISPID_ISDEXTENDEDPROPERTIES + 1,
    DISPID_ISDBEZIERPOINTS	= DISPID_ISDINK + 1,
    DISPID_ISDPOLYLINECUSPS	= DISPID_ISDBEZIERPOINTS + 1,
    DISPID_ISDBEZIERCUSPS	= DISPID_ISDPOLYLINECUSPS + 1,
    DISPID_ISDSELFINTERSECTIONS	= DISPID_ISDBEZIERCUSPS + 1,
    DISPID_ISDPACKETCOUNT	= DISPID_ISDSELFINTERSECTIONS + 1,
    DISPID_ISDPACKETSIZE	= DISPID_ISDPACKETCOUNT + 1,
    DISPID_ISDPACKETDESCRIPTION	= DISPID_ISDPACKETSIZE + 1,
    DISPID_ISDDELETED	= DISPID_ISDPACKETDESCRIPTION + 1,
    DISPID_ISDGETPACKETDESCRIPTIONPROPERTYMETRICS	= DISPID_ISDDELETED + 1,
    DISPID_ISDGETPOINTS	= DISPID_ISDGETPACKETDESCRIPTIONPROPERTYMETRICS + 1,
    DISPID_ISDSETPOINTS	= DISPID_ISDGETPOINTS + 1,
    DISPID_ISDGETPACKETDATA	= DISPID_ISDSETPOINTS + 1,
    DISPID_ISDGETPACKETVALUESBYPROPERTY	= DISPID_ISDGETPACKETDATA + 1,
    DISPID_ISDSETPACKETVALUESBYPROPERTY	= DISPID_ISDGETPACKETVALUESBYPROPERTY + 1,
    DISPID_ISDGETFLATTENEDBEZIERPOINTS	= DISPID_ISDSETPACKETVALUESBYPROPERTY + 1,
    DISPID_ISDSCALETORECTANGLE	= DISPID_ISDGETFLATTENEDBEZIERPOINTS + 1,
    DISPID_ISDTRANSFORM	= DISPID_ISDSCALETORECTANGLE + 1,
    DISPID_ISDMOVE	= DISPID_ISDTRANSFORM + 1,
    DISPID_ISDROTATE	= DISPID_ISDMOVE + 1,
    DISPID_ISDSHEAR	= DISPID_ISDROTATE + 1,
    DISPID_ISDSCALE	= DISPID_ISDSHEAR + 1
    }	DISPID_INKSTROKEDISP;

typedef /* [hidden] */ 
enum DISPID_INKTRANSFORM
    {	DISPID_ITRESET	= 1,
    DISPID_ITTRANSLATE	= DISPID_ITRESET + 1,
    DISPID_ITROTATE	= DISPID_ITTRANSLATE + 1,
    DISPID_ITREFLECT	= DISPID_ITROTATE + 1,
    DISPID_ITSHEAR	= DISPID_ITREFLECT + 1,
    DISPID_ITSCALE	= DISPID_ITSHEAR + 1,
    DISPID_ITEM11	= DISPID_ITSCALE + 1,
    DISPID_ITEM12	= DISPID_ITEM11 + 1,
    DISPID_ITEM21	= DISPID_ITEM12 + 1,
    DISPID_ITEM22	= DISPID_ITEM21 + 1,
    DISPID_ITEDX	= DISPID_ITEM22 + 1,
    DISPID_ITEDY	= DISPID_ITEDX + 1,
    DISPID_ITGETTRANSFORM	= DISPID_ITEDY + 1,
    DISPID_ITSETTRANSFORM	= DISPID_ITGETTRANSFORM + 1,
    DISPID_ITDATA	= DISPID_ITSETTRANSFORM + 1
    }	DISPID_INKTRANSFORM;

typedef /* [hidden] */ 
enum DISPID_INK
    {	DISPID_ISTROKES	= 1,
    DISPID_IEXTENDEDPROPERTIES	= DISPID_ISTROKES + 1,
    DISPID_IGETBOUNDINGBOX	= DISPID_IEXTENDEDPROPERTIES + 1,
    DISPID_IDELETESTROKES	= DISPID_IGETBOUNDINGBOX + 1,
    DISPID_IDELETESTROKE	= DISPID_IDELETESTROKES + 1,
    DISPID_IEXTRACTSTROKES	= DISPID_IDELETESTROKE + 1,
    DISPID_IEXTRACTWITHRECTANGLE	= DISPID_IEXTRACTSTROKES + 1,
    DISPID_IDIRTY	= DISPID_IEXTRACTWITHRECTANGLE + 1,
    DISPID_ICUSTOMSTROKES	= DISPID_IDIRTY + 1,
    DISPID_ICLONE	= DISPID_ICUSTOMSTROKES + 1,
    DISPID_IHITTESTCIRCLE	= DISPID_ICLONE + 1,
    DISPID_IHITTESTWITHRECTANGLE	= DISPID_IHITTESTCIRCLE + 1,
    DISPID_IHITTESTWITHLASSO	= DISPID_IHITTESTWITHRECTANGLE + 1,
    DISPID_INEARESTPOINT	= DISPID_IHITTESTWITHLASSO + 1,
    DISPID_ICREATESTROKES	= DISPID_INEARESTPOINT + 1,
    DISPID_ICREATESTROKE	= DISPID_ICREATESTROKES + 1,
    DISPID_IADDSTROKESATRECTANGLE	= DISPID_ICREATESTROKE + 1,
    DISPID_ICLIP	= DISPID_IADDSTROKESATRECTANGLE + 1,
    DISPID_ISAVE	= DISPID_ICLIP + 1,
    DISPID_ILOAD	= DISPID_ISAVE + 1,
    DISPID_ICREATESTROKEFROMPOINTS	= DISPID_ILOAD + 1,
    DISPID_ICLIPBOARDCOPYWITHRECTANGLE	= DISPID_ICREATESTROKEFROMPOINTS + 1,
    DISPID_ICLIPBOARDCOPY	= DISPID_ICLIPBOARDCOPYWITHRECTANGLE + 1,
    DISPID_ICANPASTE	= DISPID_ICLIPBOARDCOPY + 1,
    DISPID_ICLIPBOARDPASTE	= DISPID_ICANPASTE + 1
    }	DISPID_INK;

typedef /* [hidden] */ 
enum DISPID_INKEVENT
    {	DISPID_IEINKADDED	= 1,
    DISPID_IEINKDELETED	= DISPID_IEINKADDED + 1
    }	DISPID_INKEVENT;

typedef /* [hidden] */ 
enum DISPID_INKSTROKES
    {	DISPID_ISS_NEWENUM	= DISPID_NEWENUM,
    DISPID_ISSITEM	= DISPID_VALUE,
    DISPID_ISSCOUNT	= 1,
    DISPID_ISSVALID	= DISPID_ISSCOUNT + 1,
    DISPID_ISSINK	= DISPID_ISSVALID + 1,
    DISPID_ISSADD	= DISPID_ISSINK + 1,
    DISPID_ISSADDSTROKES	= DISPID_ISSADD + 1,
    DISPID_ISSREMOVE	= DISPID_ISSADDSTROKES + 1,
    DISPID_ISSREMOVESTROKES	= DISPID_ISSREMOVE + 1,
    DISPID_ISSTOSTRING	= DISPID_ISSREMOVESTROKES + 1,
    DISPID_ISSMODIFYDRAWINGATTRIBUTES	= DISPID_ISSTOSTRING + 1,
    DISPID_ISSGETBOUNDINGBOX	= DISPID_ISSMODIFYDRAWINGATTRIBUTES + 1,
    DISPID_ISSSCALETORECTANGLE	= DISPID_ISSGETBOUNDINGBOX + 1,
    DISPID_ISSTRANSFORM	= DISPID_ISSSCALETORECTANGLE + 1,
    DISPID_ISSMOVE	= DISPID_ISSTRANSFORM + 1,
    DISPID_ISSROTATE	= DISPID_ISSMOVE + 1,
    DISPID_ISSSHEAR	= DISPID_ISSROTATE + 1,
    DISPID_ISSSCALE	= DISPID_ISSSHEAR + 1,
    DISPID_ISSCLIP	= DISPID_ISSSCALE + 1,
    DISPID_ISSRECOGNITIONRESULT	= DISPID_ISSCLIP + 1,
    DISPID_ISSREMOVERECOGNITIONRESULT	= DISPID_ISSRECOGNITIONRESULT + 1
    }	DISPID_INKSTROKES;

typedef /* [hidden] */ 
enum DISPID_STROKEEVENT
    {	DISPID_SESTROKESADDED	= 1,
    DISPID_SESTROKESREMOVED	= DISPID_SESTROKESADDED + 1
    }	DISPID_STROKEEVENT;

typedef /* [hidden] */ 
enum DISPID_INKCUSTOMSTROKES
    {	DISPID_ICSS_NEWENUM	= DISPID_NEWENUM,
    DISPID_ICSSITEM	= DISPID_VALUE,
    DISPID_ICSSCOUNT	= 1,
    DISPID_ICSSADD	= DISPID_ICSSCOUNT + 1,
    DISPID_ICSSREMOVE	= DISPID_ICSSADD + 1,
    DISPID_ICSSCLEAR	= DISPID_ICSSREMOVE + 1
    }	DISPID_INKCUSTOMSTROKES;

typedef /* [hidden] */ 
enum DISPID_INKRENDERER
    {	DISPID_IRGETVIEWTRANSFORM	= 1,
    DISPID_IRSETVIEWTRANSFORM	= DISPID_IRGETVIEWTRANSFORM + 1,
    DISPID_IRGETOBJECTTRANSFORM	= DISPID_IRSETVIEWTRANSFORM + 1,
    DISPID_IRSETOBJECTTRANSFORM	= DISPID_IRGETOBJECTTRANSFORM + 1,
    DISPID_IRDRAW	= DISPID_IRSETOBJECTTRANSFORM + 1,
    DISPID_IRDRAWSTROKE	= DISPID_IRDRAW + 1,
    DISPID_IRPIXELTOINKSPACE	= DISPID_IRDRAWSTROKE + 1,
    DISPID_IRINKSPACETOPIXEL	= DISPID_IRPIXELTOINKSPACE + 1,
    DISPID_IRPIXELTOINKSPACEFROMPOINTS	= DISPID_IRINKSPACETOPIXEL + 1,
    DISPID_IRINKSPACETOPIXELFROMPOINTS	= DISPID_IRPIXELTOINKSPACEFROMPOINTS + 1,
    DISPID_IRMEASURE	= DISPID_IRINKSPACETOPIXELFROMPOINTS + 1,
    DISPID_IRMEASURESTROKE	= DISPID_IRMEASURE + 1,
    DISPID_IRMOVE	= DISPID_IRMEASURESTROKE + 1,
    DISPID_IRROTATE	= DISPID_IRMOVE + 1,
    DISPID_IRSCALE	= DISPID_IRROTATE + 1
    }	DISPID_INKRENDERER;

#pragma once
#pragma once
#pragma once
typedef /* [helpcontext][helpstring] */ 
enum InkPenTip
    {	IPT_Ball	= 0
    }	InkPenTip;

typedef /* [helpcontext][helpstring] */ 
enum InkRasterOperation
    {	IRO_Black	= 1,
    IRO_NotMergePen	= 2,
    IRO_MaskNotPen	= 3,
    IRO_NotCopyPen	= 4,
    IRO_MaskPenNot	= 5,
    IRO_Not	= 6,
    IRO_XOrPen	= 7,
    IRO_NotMaskPen	= 8,
    IRO_MaskPen	= 9,
    IRO_NotXOrPen	= 10,
    IRO_NoOperation	= 11,
    IRO_MergeNotPen	= 12,
    IRO_CopyPen	= 13,
    IRO_MergePenNot	= 14,
    IRO_MergePen	= 15,
    IRO_White	= 16
    }	InkRasterOperation;

#define IRO_Last (IRO_White+1)
typedef /* [helpcontext][helpstring] */ 
enum InkBoundingBoxMode
    {	IBBM_Default	= 0,
    IBBM_NoCurveFit	= 1,
    IBBM_CurveFit	= 2,
    IBBM_PointsOnly	= 3,
    IBBM_Union	= 4
    }	InkBoundingBoxMode;

#define IBBM_Last (IBBM_Union+1)
typedef /* [helpcontext][helpstring] */ 
enum ItemSelectionConstants
    {	ISC_FirstElement	= 0,
    ISC_AllElements	= -1
    }	InkSelectionConstants;

typedef /* [helpcontext][helpstring] */ 
enum InkExtractFlags
    {	IEF_CopyFromOriginal	= 0,
    IEF_RemoveFromOriginal	= 0x1,
    IEF_Default	= IEF_RemoveFromOriginal
    }	InkExtractFlags;

typedef /* [helpcontext][helpstring] */ 
enum InkPersistenceFormat
    {	IPF_InkSerializedFormat	= 0,
    IPF_Base64InkSerializedFormat	= 1,
    IPF_GIF	= 2,
    IPF_Base64GIF	= 3
    }	InkPersistenceFormat;

typedef /* [helpcontext][helpstring] */ 
enum InkPersistenceCompressionMode
    {	IPCM_Default	= 0
    }	InkPersistenceCompressionMode;

typedef /* [helpcontext][helpstring] */ 
enum InkClipboardModes
    {	ICB_Copy	= 0,
    ICB_Cut	= 0x1,
    ICB_Default	= ICB_Copy
    }	InkClipboardModes;

typedef /* [helpcontext][helpstring] */ 
enum InkClipboardFormats
    {	ICF_InkSerializedFormat	= 0x1,
    ICF_Bitmap	= 0x40,
    ICF_Default	= ICF_Bitmap | ICF_InkSerializedFormat
    }	InkClipboardFormats;

#ifndef _XFORM_
#define _XFORM_
typedef /* [hidden] */ struct tagXFORM
    {
    float eM11;
    float eM12;
    float eM21;
    float eM22;
    float eDx;
    float eDy;
    }	XFORM;

#endif
typedef 
enum InkCollectorEventInterest
    {	ICEI_DefaultEvents	= -1,
    ICEI_Stroke	= ICEI_DefaultEvents + 1,
    ICEI_MouseDown	= ICEI_Stroke + 1,
    ICEI_MouseMove	= ICEI_MouseDown + 1,
    ICEI_MouseUp	= ICEI_MouseMove + 1,
    ICEI_DblClick	= ICEI_MouseUp + 1,
    ICEI_AllEvents	= ICEI_DblClick + 1
    }	InkCollectorEventInterest;

typedef 
enum InkMouseButton
    {	IMF_Left	= 1,
    IMF_Right	= 2,
    IMF_Middle	= 4
    }	InkMouseButton;

typedef 
enum InkShiftKeyModifierFlags
    {	IKM_Shift	= 0x1,
    IKM_Control	= 0x2,
    IKM_Alt	= 0x4
    }	InkShiftKeyModifierFlags;

typedef /* [hidden] */ 
enum DISPID_InkCursor
    {	DISPID_ICSRNAME	= DISPID_VALUE,
    DISPID_ICSRID	= 1,
    DISPID_ICSRDRAWINGATTRIBUTES	= DISPID_ICSRID + 1,
    DISPID_ICSRBUTTONS	= DISPID_ICSRDRAWINGATTRIBUTES + 1,
    DISPID_ICSRINVERTED	= DISPID_ICSRBUTTONS + 1,
    DISPID_ICSRTABLET	= DISPID_ICSRINVERTED + 1
    }	DISPID_InkCursor;

typedef /* [hidden] */ 
enum DISPID_InkCollectorEvent
    {	DISPID_ICESTROKE	= 1,
    DISPID_ICECURSORDOWN	= DISPID_ICESTROKE + 1,
    DISPID_ICESYSTEMGESTURE	= DISPID_ICECURSORDOWN + 1,
    DISPID_IOEPAINTING	= DISPID_ICESYSTEMGESTURE + 1,
    DISPID_IOEPAINTED	= DISPID_IOEPAINTING + 1,
    DISPID_IOESELECTIONCHANGED	= DISPID_IOEPAINTED + 1,
    DISPID_IOESELECTIONMOVED	= DISPID_IOESELECTIONCHANGED + 1,
    DISPID_IOESELECTIONRESIZED	= DISPID_IOESELECTIONMOVED + 1,
    DISPID_IOESTROKESDELETING	= DISPID_IOESELECTIONRESIZED + 1,
    DISPID_IOESTROKESDELETED	= DISPID_IOESTROKESDELETING + 1,
    DISPID_IPECLICK	= DISPID_IOESTROKESDELETED + 1,
    DISPID_IPEDBLCLICK	= DISPID_IPECLICK + 1,
    DISPID_IPEINVALIDATED	= DISPID_IPEDBLCLICK + 1,
    DISPID_IPEMOUSEDOWN	= DISPID_IPEINVALIDATED + 1,
    DISPID_IPEMOUSEMOVE	= DISPID_IPEMOUSEDOWN + 1,
    DISPID_IPEMOUSEUP	= DISPID_IPEMOUSEMOVE + 1,
    DISPID_IPESIZEMODECHANGED	= DISPID_IPEMOUSEUP + 1,
    DISPID_IPERESIZE	= DISPID_IPESIZEMODECHANGED + 1,
    DISPID_IPESIZECHANGED	= DISPID_IPERESIZE + 1
    }	DISPID_InkCollectorEvent;

typedef /* [hidden] */ 
enum DISPID_InkCollector
    {	DISPID_ICENABLED	= 1,
    DISPID_ICHWND	= DISPID_ICENABLED + 1,
    DISPID_ICPAINT	= DISPID_ICHWND + 1,
    DISPID_ICTEXT	= DISPID_ICPAINT + 1,
    DISPID_ICDEFAULTDRAWINGATTRIBUTES	= DISPID_ICTEXT + 1,
    DISPID_ICRENDERER	= DISPID_ICDEFAULTDRAWINGATTRIBUTES + 1,
    DISPID_ICINK	= DISPID_ICRENDERER + 1,
    DISPID_ICAUTOREDRAW	= DISPID_ICINK + 1,
    DISPID_ICCOLLECTINGINK	= DISPID_ICAUTOREDRAW + 1,
    DISPID_ICSETEVENTINTEREST	= DISPID_ICCOLLECTINGINK + 1,
    DISPID_ICGETEVENTINTEREST	= DISPID_ICSETEVENTINTEREST + 1,
    DISPID_IOEDITINGMODE	= DISPID_ICGETEVENTINTEREST + 1,
    DISPID_IOSELECTION	= DISPID_IOEDITINGMODE + 1,
    DISPID_IOATTACHMODE	= DISPID_IOSELECTION + 1,
    DISPID_IOHITTESTSELECTION	= DISPID_IOATTACHMODE + 1,
    DISPID_IODRAW	= DISPID_IOHITTESTSELECTION + 1,
    DISPID_IPPICTURE	= DISPID_IODRAW + 1,
    DISPID_IPSIZEMODE	= DISPID_IPPICTURE + 1,
    DISPID_IPBACKCOLOR	= DISPID_IPSIZEMODE + 1,
    DISPID_ICCURSORS	= DISPID_IPBACKCOLOR + 1,
    DISPID_ICMARGINX	= DISPID_ICCURSORS + 1,
    DISPID_ICMARGINY	= DISPID_ICMARGINX + 1,
    DISPID_ICSETWINDOWINPUTRECTANGLE	= DISPID_ICMARGINY + 1,
    DISPID_ICGETWINDOWINPUTRECTANGLE	= DISPID_ICSETWINDOWINPUTRECTANGLE + 1,
    DISPID_ICCOLLECTIONMODE	= DISPID_ICGETWINDOWINPUTRECTANGLE + 1,
    DISPID_ICDYNAMICRENDERING	= DISPID_ICCOLLECTIONMODE + 1,
    DISPID_ICDESIREDPACKETDESCRIPTION	= DISPID_ICDYNAMICRENDERING + 1,
    DISPID_IOERASERMODE	= DISPID_ICDESIREDPACKETDESCRIPTION + 1,
    DISPID_IPINKENABLED	= DISPID_IOERASERMODE + 1,
    DISPID_ICSUPPORTHIGHCONTRASTINK	= DISPID_IPINKENABLED + 1,
    DISPID_IOSUPPORTHIGHCONTRASTSELECTIONUI	= DISPID_ICSUPPORTHIGHCONTRASTINK + 1
    }	DISPID_INKCOLLECTOR;

typedef /* [helpcontext][helpstring] */ 
enum InkOverlayEditingMode
    {	IOEM_Ink	= 0,
    IOEM_Delete	= 1,
    IOEM_Select	= 2
    }	InkOverlayEditingMode;

#define IOEM_Last IOEM_Select + 1
typedef /* [helpcontext][helpstring] */ 
enum InkOverlayEraserMode
    {	IOERM_StrokeErase	= 0
    }	InkOverlayEraserMode;

typedef 
enum InkCollectionMode
    {	ICM_InkOnly	= 0
    }	InkCollectionMode;

typedef /* [helpcontext][helpstring] */ 
enum SelectionHitResult
    {	SHR_None	= 0,
    SHR_NW	= SHR_None + 1,
    SHR_SE	= SHR_NW + 1,
    SHR_NE	= SHR_SE + 1,
    SHR_SW	= SHR_NE + 1,
    SHR_E	= SHR_SW + 1,
    SHR_W	= SHR_E + 1,
    SHR_N	= SHR_W + 1,
    SHR_S	= SHR_N + 1,
    SHR_Selection	= SHR_S + 1
    }	SelectionHitResult;

typedef /* [helpcontext][helpstring] */ 
enum InkRecognitionStatus
    {	IRS_NoError	= 0,
    IRS_Interrupted	= 0x1,
    IRS_ProcessFailed	= 0x2,
    IRS_InkAddedFailed	= 0x4,
    IRS_SetAutoCompletionModeFailed	= 0x8,
    IRS_SetStrokesFailed	= 0x10,
    IRS_SetGuideFailed	= 0x20,
    IRS_SetFlagsFailed	= 0x40,
    IRS_SetFactoidFailed	= 0x80,
    IRS_SetPrefixSuffixFailed	= 0x100,
    IRS_SetWordListFailed	= 0x200
    }	InkRecognitionStatus;

typedef 
enum InkRecognitionConfidence
    {	IRC_Strong	= 0,
    IRC_Intermediate	= 1,
    IRC_Poor	= 2
    }	InkRecognitionConfidence;

typedef /* [hidden] */ 
enum DISPID_InkWordList
    {	DISPID_INKWORDLIST_ADDWORD	= 0,
    DISPID_INKWORDLIST_REMOVEWORD	= DISPID_INKWORDLIST_ADDWORD + 1,
    DISPID_INKWORDLIST_MERGE	= DISPID_INKWORDLIST_REMOVEWORD + 1
    }	DISPID_InkWordList;

typedef /* [hidden] */ 
enum DISPID_InkRecognizer
    {	DISPID_RECOCLSID	= 1,
    DISPID_RECONAME	= 2,
    DISPID_RECOVENDOR	= 3,
    DISPID_RECOCAPABILITIES	= 4,
    DISPID_RECOLANGUAGEID	= 5,
    DISPID_RECOPREFERREDPACKETDESCRIPTION	= 6,
    DISPID_RECOCREATERECOGNIZERCONTEXT	= 7,
    DISPID_RECOSUPPORTEDPROPERTIES	= 8
    }	DISPID_InkRecognizer;

typedef 
enum InkRecognizerCapabilities
    {	IRC_DontCare	= 1,
    IRC_Object	= 2,
    IRC_FreeInput	= 4,
    IRC_LinedInput	= 8,
    IRC_BoxedInput	= 16,
    IRC_CharacterAutoCompletionInput	= 32,
    IRC_RightAndDown	= 64,
    IRC_LeftAndDown	= 128,
    IRC_DownAndLeft	= 256,
    IRC_DownAndRight	= 512,
    IRC_ArbitraryAngle	= 1024,
    IRC_Lattice	= 2048,
    IRC_AdviseInkChange	= 4096,
    IRC_StrokeReorder	= 8192
    }	InkRecognizerCapabilities;

typedef /* [hidden] */ 
enum DISPID_InkRecognizers
    {	DISPID_IRECOS_NEWENUM	= DISPID_NEWENUM,
    DISPID_IRECOSITEM	= DISPID_VALUE,
    DISPID_IRECOSCOUNT	= 1,
    DISPID_IRECOSGETDEFAULTRECOGNIZER	= DISPID_IRECOSCOUNT + 1
    }	DISPID_InkRecognizers;

typedef /* [hidden] */ 
enum DISPID_InkRecoContext
    {	DISPID_IRECOCTX_STROKES	= 1,
    DISPID_IRECOCTX_CHARACTERAUTOCOMPLETIONMODE	= DISPID_IRECOCTX_STROKES + 1,
    DISPID_IRECOCTX_FACTOID	= DISPID_IRECOCTX_CHARACTERAUTOCOMPLETIONMODE + 1,
    DISPID_IRECOCTX_WORDLIST	= DISPID_IRECOCTX_FACTOID + 1,
    DISPID_IRECOCTX_RECOGNIZER	= DISPID_IRECOCTX_WORDLIST + 1,
    DISPID_IRECOCTX_GUIDE	= DISPID_IRECOCTX_RECOGNIZER + 1,
    DISPID_IRECOCTX_FLAGS	= DISPID_IRECOCTX_GUIDE + 1,
    DISPID_IRECOCTX_PREFIXTEXT	= DISPID_IRECOCTX_FLAGS + 1,
    DISPID_IRECOCTX_SUFFIXTEXT	= DISPID_IRECOCTX_PREFIXTEXT + 1,
    DISPID_IRECOCTX_STOPRECOGNITION	= DISPID_IRECOCTX_SUFFIXTEXT + 1,
    DISPID_IRECOCTX_CLONE	= DISPID_IRECOCTX_STOPRECOGNITION + 1,
    DISPID_IRECOCTX_RECOGNIZE	= DISPID_IRECOCTX_CLONE + 1,
    DISPID_IRECOCTX_STOPBACKGROUNDRECOGNITION	= DISPID_IRECOCTX_RECOGNIZE + 1,
    DISPID_IRECOCTX_ENDINKINPUT	= DISPID_IRECOCTX_STOPBACKGROUNDRECOGNITION + 1,
    DISPID_IRECOCTX_BACKGROUNDRECOGNIZE	= DISPID_IRECOCTX_ENDINKINPUT + 1,
    DISPID_IRECOCTX_BACKGROUNDRECOGNIZEWITHALTERNATES	= DISPID_IRECOCTX_BACKGROUNDRECOGNIZE + 1,
    DISPID_IRECOCTX_ISSTRINGSUPPORTED	= DISPID_IRECOCTX_BACKGROUNDRECOGNIZEWITHALTERNATES + 1
    }	DISPID_InkRecoContext;

typedef /* [hidden] */ 
enum DISPID_InkRecognitionEvent
    {	DISPID_IRERECOGNITIONWITHALTERNATES	= 1,
    DISPID_IRERECOGNITION	= DISPID_IRERECOGNITIONWITHALTERNATES + 1
    }	DISPID_InkRecognitionEvent;

typedef 
enum InkRecognizerCharacterAutoCompletionMode
    {	IRCACM_Full	= 0,
    IRCACM_Prefix	= IRCACM_Full + 1,
    IRCACM_Random	= IRCACM_Prefix + 1
    }	InkRecognizerCharacterAutoCompletionMode;

typedef 
enum InkRecognitionModes
    {	IRM_None	= 0,
    IRM_WordModeOnly	= 1,
    IRM_Coerce	= 2,
    IRM_TopInkBreaksOnly	= 4,
    IRM_Max	= 8
    }	InkRecognitionModes;

typedef /* [helpcontext][helpstring] */ 
enum InkRecognitionAlternatesSelection
    {	IRAS_Start	= 0,
    IRAS_DefaultCount	= 10,
    IRAS_All	= -1
    }	InkRecognitionAlternatesSelection;

typedef /* [hidden] */ 
enum DISPID_InkRecognitionResult
    {	DISPID_INKRECOGNITIONRESULT_TOPSTRING	= 1,
    DISPID_INKRECOGNITIONRESULT_TOPALTERNATE	= DISPID_INKRECOGNITIONRESULT_TOPSTRING + 1,
    DISPID_INKRECOGNITIONRESULT_STROKES	= DISPID_INKRECOGNITIONRESULT_TOPALTERNATE + 1,
    DISPID_INKRECOGNITIONRESULT_TOPCONFIDENCE	= DISPID_INKRECOGNITIONRESULT_STROKES + 1,
    DISPID_INKRECOGNITIONRESULT_ALTERNATESFROMSELECTION	= DISPID_INKRECOGNITIONRESULT_TOPCONFIDENCE + 1,
    DISPID_INKRECOGNITIONRESULT_MODIFYTOPALTERNATE	= DISPID_INKRECOGNITIONRESULT_ALTERNATESFROMSELECTION + 1,
    DISPID_INKRECOGNITIONRESULT_SETRESULTONSTROKES	= DISPID_INKRECOGNITIONRESULT_MODIFYTOPALTERNATE + 1
    }	DISPID_InkRecognitionResult;

typedef /* [hidden] */ 
enum DISPID_InkRecoAlternate
    {	DISPID_INKRECOALTERNATE_STRING	= 1,
    DISPID_INKRECOALTERNATE_LINENUMBER	= DISPID_INKRECOALTERNATE_STRING + 1,
    DISPID_INKRECOALTERNATE_BASELINE	= DISPID_INKRECOALTERNATE_LINENUMBER + 1,
    DISPID_INKRECOALTERNATE_MIDLINE	= DISPID_INKRECOALTERNATE_BASELINE + 1,
    DISPID_INKRECOALTERNATE_ASCENDER	= DISPID_INKRECOALTERNATE_MIDLINE + 1,
    DISPID_INKRECOALTERNATE_DESCENDER	= DISPID_INKRECOALTERNATE_ASCENDER + 1,
    DISPID_INKRECOALTERNATE_CONFIDENCE	= DISPID_INKRECOALTERNATE_DESCENDER + 1,
    DISPID_INKRECOALTERNATE_STROKES	= DISPID_INKRECOALTERNATE_CONFIDENCE + 1,
    DISPID_INKRECOALTERNATE_GETSTROKESFROMSTROKERANGES	= DISPID_INKRECOALTERNATE_STROKES + 1,
    DISPID_INKRECOALTERNATE_GETSTROKESFROMTEXTRANGE	= DISPID_INKRECOALTERNATE_GETSTROKESFROMSTROKERANGES + 1,
    DISPID_INKRECOALTERNATE_GETTEXTRANGEFROMSTROKES	= DISPID_INKRECOALTERNATE_GETSTROKESFROMTEXTRANGE + 1,
    DISPID_INKRECOALTERNATE_GETPROPERTYVALUE	= DISPID_INKRECOALTERNATE_GETTEXTRANGEFROMSTROKES + 1,
    DISPID_INKRECOALTERNATE_LINEALTERNATES	= DISPID_INKRECOALTERNATE_GETPROPERTYVALUE + 1,
    DISPID_INKRECOALTERNATE_CONFIDENCEALTERNATES	= DISPID_INKRECOALTERNATE_LINEALTERNATES + 1,
    DISPID_INKRECOALTERNATE_ALTERNATESWITHCONSTANTPROPERTYVALUES	= DISPID_INKRECOALTERNATE_CONFIDENCEALTERNATES + 1
    }	DISPID_InkRecoAlternate;

typedef /* [hidden] */ 
enum DISPID_InkRecognitionAlternates
    {	DISPID_INKRECOGNITIONALTERNATES_NEWENUM	= DISPID_NEWENUM,
    DISPID_INKRECOGNITIONALTERNATES_ITEM	= DISPID_VALUE,
    DISPID_INKRECOGNITIONALTERNATES_COUNT	= 1,
    DISPID_INKRECOGNITIONALTERNATES_STROKES	= DISPID_INKRECOGNITIONALTERNATES_COUNT + 1
    }	DISPID_InkRecognitionAlternates;

typedef 
enum tagKEYMODIFIERS
    {	KEYMOD_SHIFT	= 0x1,
    KEYMOD_CONTROL	= 0x2,
    KEYMOD_ALT	= 0x4
    }	KEYMODIFIERS;

typedef 
enum tagMOUSEBUTTONS
    {	MOUSEBUTTON_LEFT	= 0x1,
    MOUSEBUTTON_RIGHT	= 0x2,
    MOUSEBUTTON_MIDDLE	= 0x4
    }	MOUSEBUTTONS;












extern RPC_IF_HANDLE __MIDL_itf_msinkaut_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msinkaut_0000_v0_0_s_ifspec;

#ifndef __IInkRectangle_INTERFACE_DEFINED__
#define __IInkRectangle_INTERFACE_DEFINED__

/* interface IInkRectangle */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRectangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9794FF82-6071-4717-8A8B-6AC7C64A686E")
    IInkRectangle : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *plUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long lUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *plUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long lUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bottom( 
            /* [retval][out] */ long __RPC_FAR *plUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bottom( 
            /* [in] */ long lUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Right( 
            /* [retval][out] */ long __RPC_FAR *plUnits) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Right( 
            /* [in] */ long lUnits) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ RECT __RPC_FAR *prcData) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ RECT rcData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRectangle( 
            /* [out] */ long __RPC_FAR *plTop,
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plBottom,
            /* [out] */ long __RPC_FAR *plRight) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRectangle( 
            /* [in] */ long lTop,
            /* [in] */ long lLeft,
            /* [in] */ long lBottom,
            /* [in] */ long lRight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRectangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRectangle __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRectangle __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRectangle __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IInkRectangle __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plUnits);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ long lUnits);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IInkRectangle __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plUnits);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ long lUnits);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bottom )( 
            IInkRectangle __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plUnits);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Bottom )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ long lUnits);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Right )( 
            IInkRectangle __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plUnits);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Right )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ long lUnits);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IInkRectangle __RPC_FAR * This,
            /* [retval][out] */ RECT __RPC_FAR *prcData);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ RECT rcData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRectangle )( 
            IInkRectangle __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plTop,
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plBottom,
            /* [out] */ long __RPC_FAR *plRight);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRectangle )( 
            IInkRectangle __RPC_FAR * This,
            /* [in] */ long lTop,
            /* [in] */ long lLeft,
            /* [in] */ long lBottom,
            /* [in] */ long lRight);
        
        END_INTERFACE
    } IInkRectangleVtbl;

    interface IInkRectangle
    {
        CONST_VTBL struct IInkRectangleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRectangle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRectangle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRectangle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRectangle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRectangle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRectangle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRectangle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRectangle_get_Top(This,plUnits)	\
    (This)->lpVtbl -> get_Top(This,plUnits)

#define IInkRectangle_put_Top(This,lUnits)	\
    (This)->lpVtbl -> put_Top(This,lUnits)

#define IInkRectangle_get_Left(This,plUnits)	\
    (This)->lpVtbl -> get_Left(This,plUnits)

#define IInkRectangle_put_Left(This,lUnits)	\
    (This)->lpVtbl -> put_Left(This,lUnits)

#define IInkRectangle_get_Bottom(This,plUnits)	\
    (This)->lpVtbl -> get_Bottom(This,plUnits)

#define IInkRectangle_put_Bottom(This,lUnits)	\
    (This)->lpVtbl -> put_Bottom(This,lUnits)

#define IInkRectangle_get_Right(This,plUnits)	\
    (This)->lpVtbl -> get_Right(This,plUnits)

#define IInkRectangle_put_Right(This,lUnits)	\
    (This)->lpVtbl -> put_Right(This,lUnits)

#define IInkRectangle_get_Data(This,prcData)	\
    (This)->lpVtbl -> get_Data(This,prcData)

#define IInkRectangle_put_Data(This,rcData)	\
    (This)->lpVtbl -> put_Data(This,rcData)

#define IInkRectangle_GetRectangle(This,plTop,plLeft,plBottom,plRight)	\
    (This)->lpVtbl -> GetRectangle(This,plTop,plLeft,plBottom,plRight)

#define IInkRectangle_SetRectangle(This,lTop,lLeft,lBottom,lRight)	\
    (This)->lpVtbl -> SetRectangle(This,lTop,lLeft,lBottom,lRight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Top_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plUnits);


void __RPC_STUB IInkRectangle_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Top_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [in] */ long lUnits);


void __RPC_STUB IInkRectangle_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Left_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plUnits);


void __RPC_STUB IInkRectangle_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Left_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [in] */ long lUnits);


void __RPC_STUB IInkRectangle_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Bottom_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plUnits);


void __RPC_STUB IInkRectangle_get_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Bottom_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [in] */ long lUnits);


void __RPC_STUB IInkRectangle_put_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Right_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plUnits);


void __RPC_STUB IInkRectangle_get_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Right_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [in] */ long lUnits);


void __RPC_STUB IInkRectangle_put_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Data_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [retval][out] */ RECT __RPC_FAR *prcData);


void __RPC_STUB IInkRectangle_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Data_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [in] */ RECT rcData);


void __RPC_STUB IInkRectangle_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRectangle_GetRectangle_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plTop,
    /* [out] */ long __RPC_FAR *plLeft,
    /* [out] */ long __RPC_FAR *plBottom,
    /* [out] */ long __RPC_FAR *plRight);


void __RPC_STUB IInkRectangle_GetRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRectangle_SetRectangle_Proxy( 
    IInkRectangle __RPC_FAR * This,
    /* [in] */ long lTop,
    /* [in] */ long lLeft,
    /* [in] */ long lBottom,
    /* [in] */ long lRight);


void __RPC_STUB IInkRectangle_SetRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRectangle_INTERFACE_DEFINED__ */


#ifndef __IInkExtendedProperty_INTERFACE_DEFINED__
#define __IInkExtendedProperty_INTERFACE_DEFINED__

/* interface IInkExtendedProperty */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkExtendedProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB489209-B7C3-411D-90F6-1548CFFF271E")
    IInkExtendedProperty : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Guid( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkExtendedPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkExtendedProperty __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkExtendedProperty __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Guid )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IInkExtendedProperty __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IInkExtendedPropertyVtbl;

    interface IInkExtendedProperty
    {
        CONST_VTBL struct IInkExtendedPropertyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkExtendedProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkExtendedProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkExtendedProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkExtendedProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkExtendedProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkExtendedProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkExtendedProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkExtendedProperty_get_Guid(This,pVal)	\
    (This)->lpVtbl -> get_Guid(This,pVal)

#define IInkExtendedProperty_get_Data(This,pVal)	\
    (This)->lpVtbl -> get_Data(This,pVal)

#define IInkExtendedProperty_put_Data(This,newVal)	\
    (This)->lpVtbl -> put_Data(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperty_get_Guid_Proxy( 
    IInkExtendedProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IInkExtendedProperty_get_Guid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperty_get_Data_Proxy( 
    IInkExtendedProperty __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IInkExtendedProperty_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperty_put_Data_Proxy( 
    IInkExtendedProperty __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IInkExtendedProperty_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkExtendedProperty_INTERFACE_DEFINED__ */


#ifndef __IInkExtendedProperties_INTERFACE_DEFINED__
#define __IInkExtendedProperties_INTERFACE_DEFINED__

/* interface IInkExtendedProperties */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkExtendedProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("89F2A8BE-95A9-4530-8B8F-88E971E3E25F")
    IInkExtendedProperties : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            BSTR bstrGuid,
            VARIANT Data,
            IInkExtendedProperty __RPC_FAR *__RPC_FAR *ppunkInkProperty) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT varID,
            IInkExtendedProperty __RPC_FAR *__RPC_FAR *ppunkInkProperty) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT varID) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DoesPropertyExist( 
            /* [in] */ BSTR Guid,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *DoesPropertyExist) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkExtendedPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkExtendedProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkExtendedProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IInkExtendedProperties __RPC_FAR * This,
            BSTR bstrGuid,
            VARIANT Data,
            IInkExtendedProperty __RPC_FAR *__RPC_FAR *ppunkInkProperty);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IInkExtendedProperties __RPC_FAR * This,
            VARIANT varID,
            IInkExtendedProperty __RPC_FAR *__RPC_FAR *ppunkInkProperty);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IInkExtendedProperties __RPC_FAR * This,
            VARIANT varID);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IInkExtendedProperties __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoesPropertyExist )( 
            IInkExtendedProperties __RPC_FAR * This,
            /* [in] */ BSTR Guid,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *DoesPropertyExist);
        
        END_INTERFACE
    } IInkExtendedPropertiesVtbl;

    interface IInkExtendedProperties
    {
        CONST_VTBL struct IInkExtendedPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkExtendedProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkExtendedProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkExtendedProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkExtendedProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkExtendedProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkExtendedProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkExtendedProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkExtendedProperties_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IInkExtendedProperties_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IInkExtendedProperties_Add(This,bstrGuid,Data,ppunkInkProperty)	\
    (This)->lpVtbl -> Add(This,bstrGuid,Data,ppunkInkProperty)

#define IInkExtendedProperties_Item(This,varID,ppunkInkProperty)	\
    (This)->lpVtbl -> Item(This,varID,ppunkInkProperty)

#define IInkExtendedProperties_Remove(This,varID)	\
    (This)->lpVtbl -> Remove(This,varID)

#define IInkExtendedProperties_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IInkExtendedProperties_DoesPropertyExist(This,Guid,DoesPropertyExist)	\
    (This)->lpVtbl -> DoesPropertyExist(This,Guid,DoesPropertyExist)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_get_Count_Proxy( 
    IInkExtendedProperties __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IInkExtendedProperties_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_get__NewEnum_Proxy( 
    IInkExtendedProperties __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IInkExtendedProperties_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Add_Proxy( 
    IInkExtendedProperties __RPC_FAR * This,
    BSTR bstrGuid,
    VARIANT Data,
    IInkExtendedProperty __RPC_FAR *__RPC_FAR *ppunkInkProperty);


void __RPC_STUB IInkExtendedProperties_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Item_Proxy( 
    IInkExtendedProperties __RPC_FAR * This,
    VARIANT varID,
    IInkExtendedProperty __RPC_FAR *__RPC_FAR *ppunkInkProperty);


void __RPC_STUB IInkExtendedProperties_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Remove_Proxy( 
    IInkExtendedProperties __RPC_FAR * This,
    VARIANT varID);


void __RPC_STUB IInkExtendedProperties_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Clear_Proxy( 
    IInkExtendedProperties __RPC_FAR * This);


void __RPC_STUB IInkExtendedProperties_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_DoesPropertyExist_Proxy( 
    IInkExtendedProperties __RPC_FAR * This,
    /* [in] */ BSTR Guid,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *DoesPropertyExist);


void __RPC_STUB IInkExtendedProperties_DoesPropertyExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkExtendedProperties_INTERFACE_DEFINED__ */


#ifndef __IInkDrawingAttributes_INTERFACE_DEFINED__
#define __IInkDrawingAttributes_INTERFACE_DEFINED__

/* interface IInkDrawingAttributes */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDrawingAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BF519B75-0A15-4623-ADC9-C00D436A8092")
    IInkDrawingAttributes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ long __RPC_FAR *CurrentColor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ long NewColor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ float __RPC_FAR *CurrentWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ float NewWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FitToCurve( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FitToCurve( 
            /* [in] */ VARIANT_BOOL Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AntiAliased( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AntiAliased( 
            /* [in] */ VARIANT_BOOL Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Transparency( 
            /* [retval][out] */ long __RPC_FAR *CurrentTransparency) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Transparency( 
            /* [in] */ long NewTransparency) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RasterOperation( 
            /* [retval][out] */ InkRasterOperation __RPC_FAR *CurrentRasterOperation) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RasterOperation( 
            /* [in] */ InkRasterOperation NewRasterOperation) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PenTip( 
            /* [retval][out] */ InkPenTip __RPC_FAR *CurrentPenTip) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PenTip( 
            /* [in] */ InkPenTip NewPenTip) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedProperties( 
            /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *DrawingAttributes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDrawingAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkDrawingAttributes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkDrawingAttributes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *CurrentColor);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ long NewColor);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *CurrentWidth);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ float NewWidth);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FitToCurve )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Flag);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FitToCurve )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Flag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AntiAliased )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Flag);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AntiAliased )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Flag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Transparency )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *CurrentTransparency);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Transparency )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ long NewTransparency);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RasterOperation )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ InkRasterOperation __RPC_FAR *CurrentRasterOperation);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RasterOperation )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ InkRasterOperation NewRasterOperation);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PenTip )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ InkPenTip __RPC_FAR *CurrentPenTip);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PenTip )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [in] */ InkPenTip NewPenTip);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedProperties )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IInkDrawingAttributes __RPC_FAR * This,
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *DrawingAttributes);
        
        END_INTERFACE
    } IInkDrawingAttributesVtbl;

    interface IInkDrawingAttributes
    {
        CONST_VTBL struct IInkDrawingAttributesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDrawingAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDrawingAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDrawingAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDrawingAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDrawingAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDrawingAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDrawingAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDrawingAttributes_get_Color(This,CurrentColor)	\
    (This)->lpVtbl -> get_Color(This,CurrentColor)

#define IInkDrawingAttributes_put_Color(This,NewColor)	\
    (This)->lpVtbl -> put_Color(This,NewColor)

#define IInkDrawingAttributes_get_Width(This,CurrentWidth)	\
    (This)->lpVtbl -> get_Width(This,CurrentWidth)

#define IInkDrawingAttributes_put_Width(This,NewWidth)	\
    (This)->lpVtbl -> put_Width(This,NewWidth)

#define IInkDrawingAttributes_get_FitToCurve(This,Flag)	\
    (This)->lpVtbl -> get_FitToCurve(This,Flag)

#define IInkDrawingAttributes_put_FitToCurve(This,Flag)	\
    (This)->lpVtbl -> put_FitToCurve(This,Flag)

#define IInkDrawingAttributes_get_AntiAliased(This,Flag)	\
    (This)->lpVtbl -> get_AntiAliased(This,Flag)

#define IInkDrawingAttributes_put_AntiAliased(This,Flag)	\
    (This)->lpVtbl -> put_AntiAliased(This,Flag)

#define IInkDrawingAttributes_get_Transparency(This,CurrentTransparency)	\
    (This)->lpVtbl -> get_Transparency(This,CurrentTransparency)

#define IInkDrawingAttributes_put_Transparency(This,NewTransparency)	\
    (This)->lpVtbl -> put_Transparency(This,NewTransparency)

#define IInkDrawingAttributes_get_RasterOperation(This,CurrentRasterOperation)	\
    (This)->lpVtbl -> get_RasterOperation(This,CurrentRasterOperation)

#define IInkDrawingAttributes_put_RasterOperation(This,NewRasterOperation)	\
    (This)->lpVtbl -> put_RasterOperation(This,NewRasterOperation)

#define IInkDrawingAttributes_get_PenTip(This,CurrentPenTip)	\
    (This)->lpVtbl -> get_PenTip(This,CurrentPenTip)

#define IInkDrawingAttributes_put_PenTip(This,NewPenTip)	\
    (This)->lpVtbl -> put_PenTip(This,NewPenTip)

#define IInkDrawingAttributes_get_ExtendedProperties(This,Properties)	\
    (This)->lpVtbl -> get_ExtendedProperties(This,Properties)

#define IInkDrawingAttributes_Clone(This,DrawingAttributes)	\
    (This)->lpVtbl -> Clone(This,DrawingAttributes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Color_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *CurrentColor);


void __RPC_STUB IInkDrawingAttributes_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Color_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ long NewColor);


void __RPC_STUB IInkDrawingAttributes_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Width_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *CurrentWidth);


void __RPC_STUB IInkDrawingAttributes_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Width_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ float NewWidth);


void __RPC_STUB IInkDrawingAttributes_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_FitToCurve_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Flag);


void __RPC_STUB IInkDrawingAttributes_get_FitToCurve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_FitToCurve_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Flag);


void __RPC_STUB IInkDrawingAttributes_put_FitToCurve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_AntiAliased_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Flag);


void __RPC_STUB IInkDrawingAttributes_get_AntiAliased_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_AntiAliased_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Flag);


void __RPC_STUB IInkDrawingAttributes_put_AntiAliased_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Transparency_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *CurrentTransparency);


void __RPC_STUB IInkDrawingAttributes_get_Transparency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Transparency_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ long NewTransparency);


void __RPC_STUB IInkDrawingAttributes_put_Transparency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_RasterOperation_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ InkRasterOperation __RPC_FAR *CurrentRasterOperation);


void __RPC_STUB IInkDrawingAttributes_get_RasterOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_RasterOperation_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ InkRasterOperation NewRasterOperation);


void __RPC_STUB IInkDrawingAttributes_put_RasterOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_PenTip_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ InkPenTip __RPC_FAR *CurrentPenTip);


void __RPC_STUB IInkDrawingAttributes_get_PenTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_PenTip_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [in] */ InkPenTip NewPenTip);


void __RPC_STUB IInkDrawingAttributes_put_PenTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_ExtendedProperties_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties);


void __RPC_STUB IInkDrawingAttributes_get_ExtendedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_Clone_Proxy( 
    IInkDrawingAttributes __RPC_FAR * This,
    /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *DrawingAttributes);


void __RPC_STUB IInkDrawingAttributes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDrawingAttributes_INTERFACE_DEFINED__ */


#ifndef __IInkStrokeDisp_INTERFACE_DEFINED__
#define __IInkStrokeDisp_INTERFACE_DEFINED__

/* interface IInkStrokeDisp */
/* [unique][dual][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkStrokeDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43242FEA-91D1-4a72-963E-FBB91829CFA2")
    IInkStrokeDisp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long __RPC_FAR *ID) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BezierPoints( 
            /* [retval][out] */ VARIANT __RPC_FAR *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *DrawAttrs) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DrawingAttributes( 
            /* [in] */ IInkDrawingAttributes __RPC_FAR *DrawAttrs) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedProperties( 
            /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PolylineCusps( 
            /* [retval][out] */ VARIANT __RPC_FAR *Cusps) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BezierCusps( 
            /* [retval][out] */ VARIANT __RPC_FAR *Cusps) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelfIntersections( 
            /* [retval][out] */ VARIANT __RPC_FAR *Intersections) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PacketCount( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Deleted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Deleted) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingBox( 
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FindIntersections( 
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [retval][out] */ VARIANT __RPC_FAR *Intersections) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRectangleIntersections( 
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle,
            /* [retval][out] */ VARIANT __RPC_FAR *Intersections) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestCircle( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float Radius,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Intersects) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Split( 
            /* [in] */ float SplitAt,
            /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *NewStroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPoints( 
            /* [in][defaultvalue] */ long Index,
            /* [in][defaultvalue] */ long Count,
            /* [retval][out] */ VARIANT __RPC_FAR *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPoints( 
            /* [in] */ VARIANT Points,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *NumberOfPointsSet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IInkTransform __RPC_FAR *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleToRectangle( 
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Shear( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkStrokeDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkStrokeDisp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkStrokeDisp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *ID);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BezierPoints )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Points);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DrawingAttributes )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *DrawAttrs);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_DrawingAttributes )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ IInkDrawingAttributes __RPC_FAR *DrawAttrs);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ink )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedProperties )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PolylineCusps )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Cusps);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BezierCusps )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Cusps);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelfIntersections )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Intersections);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PacketCount )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Deleted )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Deleted);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBoundingBox )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindIntersections )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [retval][out] */ VARIANT __RPC_FAR *Intersections);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRectangleIntersections )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle,
            /* [retval][out] */ VARIANT __RPC_FAR *Intersections);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clip )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HitTestCircle )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float Radius,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Intersects);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Split )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ float SplitAt,
            /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *NewStroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPoints )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in][defaultvalue] */ long Index,
            /* [in][defaultvalue] */ long Count,
            /* [retval][out] */ VARIANT __RPC_FAR *Points);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPoints )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ VARIANT Points,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *NumberOfPointsSet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Transform )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ IInkTransform __RPC_FAR *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleToRectangle )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shear )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleTransform )( 
            IInkStrokeDisp __RPC_FAR * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        END_INTERFACE
    } IInkStrokeDispVtbl;

    interface IInkStrokeDisp
    {
        CONST_VTBL struct IInkStrokeDispVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkStrokeDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkStrokeDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkStrokeDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkStrokeDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkStrokeDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkStrokeDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkStrokeDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkStrokeDisp_get_ID(This,ID)	\
    (This)->lpVtbl -> get_ID(This,ID)

#define IInkStrokeDisp_get_BezierPoints(This,Points)	\
    (This)->lpVtbl -> get_BezierPoints(This,Points)

#define IInkStrokeDisp_get_DrawingAttributes(This,DrawAttrs)	\
    (This)->lpVtbl -> get_DrawingAttributes(This,DrawAttrs)

#define IInkStrokeDisp_putref_DrawingAttributes(This,DrawAttrs)	\
    (This)->lpVtbl -> putref_DrawingAttributes(This,DrawAttrs)

#define IInkStrokeDisp_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkStrokeDisp_get_ExtendedProperties(This,Properties)	\
    (This)->lpVtbl -> get_ExtendedProperties(This,Properties)

#define IInkStrokeDisp_get_PolylineCusps(This,Cusps)	\
    (This)->lpVtbl -> get_PolylineCusps(This,Cusps)

#define IInkStrokeDisp_get_BezierCusps(This,Cusps)	\
    (This)->lpVtbl -> get_BezierCusps(This,Cusps)

#define IInkStrokeDisp_get_SelfIntersections(This,Intersections)	\
    (This)->lpVtbl -> get_SelfIntersections(This,Intersections)

#define IInkStrokeDisp_get_PacketCount(This,plCount)	\
    (This)->lpVtbl -> get_PacketCount(This,plCount)

#define IInkStrokeDisp_get_Deleted(This,Deleted)	\
    (This)->lpVtbl -> get_Deleted(This,Deleted)

#define IInkStrokeDisp_GetBoundingBox(This,BoundingBoxMode,Rectangle)	\
    (This)->lpVtbl -> GetBoundingBox(This,BoundingBoxMode,Rectangle)

#define IInkStrokeDisp_FindIntersections(This,Strokes,Intersections)	\
    (This)->lpVtbl -> FindIntersections(This,Strokes,Intersections)

#define IInkStrokeDisp_GetRectangleIntersections(This,Rectangle,Intersections)	\
    (This)->lpVtbl -> GetRectangleIntersections(This,Rectangle,Intersections)

#define IInkStrokeDisp_Clip(This,Rectangle)	\
    (This)->lpVtbl -> Clip(This,Rectangle)

#define IInkStrokeDisp_HitTestCircle(This,X,Y,Radius,Intersects)	\
    (This)->lpVtbl -> HitTestCircle(This,X,Y,Radius,Intersects)

#define IInkStrokeDisp_Split(This,SplitAt,NewStroke)	\
    (This)->lpVtbl -> Split(This,SplitAt,NewStroke)

#define IInkStrokeDisp_GetPoints(This,Index,Count,Points)	\
    (This)->lpVtbl -> GetPoints(This,Index,Count,Points)

#define IInkStrokeDisp_SetPoints(This,Points,Index,Count,NumberOfPointsSet)	\
    (This)->lpVtbl -> SetPoints(This,Points,Index,Count,NumberOfPointsSet)

#define IInkStrokeDisp_Transform(This,Transform,ApplyOnPenWidth)	\
    (This)->lpVtbl -> Transform(This,Transform,ApplyOnPenWidth)

#define IInkStrokeDisp_ScaleToRectangle(This,Rectangle)	\
    (This)->lpVtbl -> ScaleToRectangle(This,Rectangle)

#define IInkStrokeDisp_Move(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Move(This,HorizontalComponent,VerticalComponent)

#define IInkStrokeDisp_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkStrokeDisp_Shear(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> Shear(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkStrokeDisp_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_ID_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *ID);


void __RPC_STUB IInkStrokeDisp_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_BezierPoints_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Points);


void __RPC_STUB IInkStrokeDisp_get_BezierPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_DrawingAttributes_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *DrawAttrs);


void __RPC_STUB IInkStrokeDisp_get_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_putref_DrawingAttributes_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ IInkDrawingAttributes __RPC_FAR *DrawAttrs);


void __RPC_STUB IInkStrokeDisp_putref_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_Ink_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink);


void __RPC_STUB IInkStrokeDisp_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_ExtendedProperties_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties);


void __RPC_STUB IInkStrokeDisp_get_ExtendedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_PolylineCusps_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Cusps);


void __RPC_STUB IInkStrokeDisp_get_PolylineCusps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_BezierCusps_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Cusps);


void __RPC_STUB IInkStrokeDisp_get_BezierCusps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_SelfIntersections_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Intersections);


void __RPC_STUB IInkStrokeDisp_get_SelfIntersections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_PacketCount_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IInkStrokeDisp_get_PacketCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_Deleted_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Deleted);


void __RPC_STUB IInkStrokeDisp_get_Deleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetBoundingBox_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
    /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);


void __RPC_STUB IInkStrokeDisp_GetBoundingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_FindIntersections_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *Strokes,
    /* [retval][out] */ VARIANT __RPC_FAR *Intersections);


void __RPC_STUB IInkStrokeDisp_FindIntersections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetRectangleIntersections_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rectangle,
    /* [retval][out] */ VARIANT __RPC_FAR *Intersections);


void __RPC_STUB IInkStrokeDisp_GetRectangleIntersections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Clip_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rectangle);


void __RPC_STUB IInkStrokeDisp_Clip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_HitTestCircle_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [in] */ float Radius,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Intersects);


void __RPC_STUB IInkStrokeDisp_HitTestCircle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Split_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ float SplitAt,
    /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *NewStroke);


void __RPC_STUB IInkStrokeDisp_Split_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetPoints_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in][defaultvalue] */ long Index,
    /* [in][defaultvalue] */ long Count,
    /* [retval][out] */ VARIANT __RPC_FAR *Points);


void __RPC_STUB IInkStrokeDisp_GetPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_SetPoints_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ VARIANT Points,
    /* [defaultvalue][in] */ long Index,
    /* [defaultvalue][in] */ long Count,
    /* [retval][out] */ long __RPC_FAR *NumberOfPointsSet);


void __RPC_STUB IInkStrokeDisp_SetPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Transform_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ IInkTransform __RPC_FAR *Transform,
    /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);


void __RPC_STUB IInkStrokeDisp_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_ScaleToRectangle_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rectangle);


void __RPC_STUB IInkStrokeDisp_ScaleToRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Move_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkStrokeDisp_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Rotate_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkStrokeDisp_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Shear_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokeDisp_Shear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_ScaleTransform_Proxy( 
    IInkStrokeDisp __RPC_FAR * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokeDisp_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkStrokeDisp_INTERFACE_DEFINED__ */


#ifndef __IInkTransform_INTERFACE_DEFINED__
#define __IInkTransform_INTERFACE_DEFINED__

/* interface IInkTransform */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("615F1D43-8703-4565-88E2-8201D2ECD7B7")
    IInkTransform : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Translate( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Reflect( 
            /* [in] */ VARIANT_BOOL Horizontally,
            /* [in] */ VARIANT_BOOL Vertically) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Shear( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransform( 
            /* [out] */ float __RPC_FAR *eM11,
            /* [out] */ float __RPC_FAR *eM12,
            /* [out] */ float __RPC_FAR *eM21,
            /* [out] */ float __RPC_FAR *eM22,
            /* [out] */ float __RPC_FAR *eDx,
            /* [out] */ float __RPC_FAR *eDy) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTransform( 
            /* [in] */ float eM11,
            /* [in] */ float eM12,
            /* [in] */ float eM21,
            /* [in] */ float eM22,
            /* [in] */ float eDx,
            /* [in] */ float eDy) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM11( 
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM11( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM12( 
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM12( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM21( 
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM21( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM22( 
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM22( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eDx( 
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eDx( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eDy( 
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eDy( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ XFORM __RPC_FAR *XForm) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ XFORM XForm) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkTransform __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkTransform __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkTransform __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IInkTransform __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Translate )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reflect )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Horizontally,
            /* [in] */ VARIANT_BOOL Vertically);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shear )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleTransform )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransform )( 
            IInkTransform __RPC_FAR * This,
            /* [out] */ float __RPC_FAR *eM11,
            /* [out] */ float __RPC_FAR *eM12,
            /* [out] */ float __RPC_FAR *eM21,
            /* [out] */ float __RPC_FAR *eM22,
            /* [out] */ float __RPC_FAR *eDx,
            /* [out] */ float __RPC_FAR *eDy);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransform )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float eM11,
            /* [in] */ float eM12,
            /* [in] */ float eM21,
            /* [in] */ float eM22,
            /* [in] */ float eDx,
            /* [in] */ float eDy);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_eM11 )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_eM11 )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_eM12 )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_eM12 )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_eM21 )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_eM21 )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_eM22 )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_eM22 )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_eDx )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_eDx )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_eDy )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_eDy )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Data )( 
            IInkTransform __RPC_FAR * This,
            /* [retval][out] */ XFORM __RPC_FAR *XForm);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Data )( 
            IInkTransform __RPC_FAR * This,
            /* [in] */ XFORM XForm);
        
        END_INTERFACE
    } IInkTransformVtbl;

    interface IInkTransform
    {
        CONST_VTBL struct IInkTransformVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkTransform_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkTransform_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IInkTransform_Translate(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Translate(This,HorizontalComponent,VerticalComponent)

#define IInkTransform_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkTransform_Reflect(This,Horizontally,Vertically)	\
    (This)->lpVtbl -> Reflect(This,Horizontally,Vertically)

#define IInkTransform_Shear(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Shear(This,HorizontalComponent,VerticalComponent)

#define IInkTransform_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkTransform_GetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)	\
    (This)->lpVtbl -> GetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)

#define IInkTransform_SetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)	\
    (This)->lpVtbl -> SetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)

#define IInkTransform_get_eM11(This,Value)	\
    (This)->lpVtbl -> get_eM11(This,Value)

#define IInkTransform_put_eM11(This,Value)	\
    (This)->lpVtbl -> put_eM11(This,Value)

#define IInkTransform_get_eM12(This,Value)	\
    (This)->lpVtbl -> get_eM12(This,Value)

#define IInkTransform_put_eM12(This,Value)	\
    (This)->lpVtbl -> put_eM12(This,Value)

#define IInkTransform_get_eM21(This,Value)	\
    (This)->lpVtbl -> get_eM21(This,Value)

#define IInkTransform_put_eM21(This,Value)	\
    (This)->lpVtbl -> put_eM21(This,Value)

#define IInkTransform_get_eM22(This,Value)	\
    (This)->lpVtbl -> get_eM22(This,Value)

#define IInkTransform_put_eM22(This,Value)	\
    (This)->lpVtbl -> put_eM22(This,Value)

#define IInkTransform_get_eDx(This,Value)	\
    (This)->lpVtbl -> get_eDx(This,Value)

#define IInkTransform_put_eDx(This,Value)	\
    (This)->lpVtbl -> put_eDx(This,Value)

#define IInkTransform_get_eDy(This,Value)	\
    (This)->lpVtbl -> get_eDy(This,Value)

#define IInkTransform_put_eDy(This,Value)	\
    (This)->lpVtbl -> put_eDy(This,Value)

#define IInkTransform_get_Data(This,XForm)	\
    (This)->lpVtbl -> get_Data(This,XForm)

#define IInkTransform_put_Data(This,XForm)	\
    (This)->lpVtbl -> put_Data(This,XForm)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Reset_Proxy( 
    IInkTransform __RPC_FAR * This);


void __RPC_STUB IInkTransform_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Translate_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkTransform_Translate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Rotate_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkTransform_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Reflect_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Horizontally,
    /* [in] */ VARIANT_BOOL Vertically);


void __RPC_STUB IInkTransform_Reflect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Shear_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkTransform_Shear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_ScaleTransform_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkTransform_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_GetTransform_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [out] */ float __RPC_FAR *eM11,
    /* [out] */ float __RPC_FAR *eM12,
    /* [out] */ float __RPC_FAR *eM21,
    /* [out] */ float __RPC_FAR *eM22,
    /* [out] */ float __RPC_FAR *eDx,
    /* [out] */ float __RPC_FAR *eDy);


void __RPC_STUB IInkTransform_GetTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_SetTransform_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float eM11,
    /* [in] */ float eM12,
    /* [in] */ float eM21,
    /* [in] */ float eM22,
    /* [in] */ float eDx,
    /* [in] */ float eDy);


void __RPC_STUB IInkTransform_SetTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM11_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB IInkTransform_get_eM11_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM11_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM11_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM12_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB IInkTransform_get_eM12_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM12_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM12_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM21_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB IInkTransform_get_eM21_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM21_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM21_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM22_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB IInkTransform_get_eM22_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM22_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM22_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eDx_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB IInkTransform_get_eDx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eDx_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eDx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eDy_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB IInkTransform_get_eDy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eDy_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eDy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_Data_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [retval][out] */ XFORM __RPC_FAR *XForm);


void __RPC_STUB IInkTransform_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_Data_Proxy( 
    IInkTransform __RPC_FAR * This,
    /* [in] */ XFORM XForm);


void __RPC_STUB IInkTransform_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkTransform_INTERFACE_DEFINED__ */


#ifndef __IInkRecognizer_INTERFACE_DEFINED__
#define __IInkRecognizer_INTERFACE_DEFINED__

/* interface IInkRecognizer */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("782BF7CF-034B-4396-8A32-3A1833CF6B56")
    IInkRecognizer : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Vendor( 
            /* [retval][out] */ BSTR __RPC_FAR *Vendor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Capabilities( 
            /* [retval][out] */ InkRecognizerCapabilities __RPC_FAR *CapabilitiesFlags) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Languages( 
            /* [retval][out] */ VARIANT __RPC_FAR *Languages) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportedProperties( 
            /* [retval][out] */ VARIANT __RPC_FAR *SupportedProperties) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredPacketDescription( 
            /* [retval][out] */ VARIANT __RPC_FAR *PreferredPacketDescription) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateRecognizerContext( 
            /* [retval][out] */ IInkRecognizerContext __RPC_FAR *__RPC_FAR *Context) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRecognizer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRecognizer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRecognizer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRecognizer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRecognizer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRecognizer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRecognizer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Vendor )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Vendor);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Capabilities )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ InkRecognizerCapabilities __RPC_FAR *CapabilitiesFlags);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Languages )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Languages);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SupportedProperties )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *SupportedProperties);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredPacketDescription )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *PreferredPacketDescription);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateRecognizerContext )( 
            IInkRecognizer __RPC_FAR * This,
            /* [retval][out] */ IInkRecognizerContext __RPC_FAR *__RPC_FAR *Context);
        
        END_INTERFACE
    } IInkRecognizerVtbl;

    interface IInkRecognizer
    {
        CONST_VTBL struct IInkRecognizerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizer_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IInkRecognizer_get_Vendor(This,Vendor)	\
    (This)->lpVtbl -> get_Vendor(This,Vendor)

#define IInkRecognizer_get_Capabilities(This,CapabilitiesFlags)	\
    (This)->lpVtbl -> get_Capabilities(This,CapabilitiesFlags)

#define IInkRecognizer_get_Languages(This,Languages)	\
    (This)->lpVtbl -> get_Languages(This,Languages)

#define IInkRecognizer_get_SupportedProperties(This,SupportedProperties)	\
    (This)->lpVtbl -> get_SupportedProperties(This,SupportedProperties)

#define IInkRecognizer_get_PreferredPacketDescription(This,PreferredPacketDescription)	\
    (This)->lpVtbl -> get_PreferredPacketDescription(This,PreferredPacketDescription)

#define IInkRecognizer_CreateRecognizerContext(This,Context)	\
    (This)->lpVtbl -> CreateRecognizerContext(This,Context)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Name_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB IInkRecognizer_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Vendor_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Vendor);


void __RPC_STUB IInkRecognizer_get_Vendor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Capabilities_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ InkRecognizerCapabilities __RPC_FAR *CapabilitiesFlags);


void __RPC_STUB IInkRecognizer_get_Capabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Languages_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Languages);


void __RPC_STUB IInkRecognizer_get_Languages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_SupportedProperties_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *SupportedProperties);


void __RPC_STUB IInkRecognizer_get_SupportedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_PreferredPacketDescription_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *PreferredPacketDescription);


void __RPC_STUB IInkRecognizer_get_PreferredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_CreateRecognizerContext_Proxy( 
    IInkRecognizer __RPC_FAR * This,
    /* [retval][out] */ IInkRecognizerContext __RPC_FAR *__RPC_FAR *Context);


void __RPC_STUB IInkRecognizer_CreateRecognizerContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizer_INTERFACE_DEFINED__ */


#ifndef __IInkRecognizers_INTERFACE_DEFINED__
#define __IInkRecognizers_INTERFACE_DEFINED__

/* interface IInkRecognizers */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CCC4F12-B0B7-4a8b-BF58-4AECA4E8CEFD")
    IInkRecognizers : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDefaultRecognizer( 
            /* [defaultvalue][in] */ long lcid,
            /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *DefaultRecognizer) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *InkRecognizer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRecognizers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRecognizers __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRecognizers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRecognizers __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRecognizers __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRecognizers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRecognizers __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IInkRecognizers __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IInkRecognizers __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDefaultRecognizer )( 
            IInkRecognizers __RPC_FAR * This,
            /* [defaultvalue][in] */ long lcid,
            /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *DefaultRecognizer);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IInkRecognizers __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *InkRecognizer);
        
        END_INTERFACE
    } IInkRecognizersVtbl;

    interface IInkRecognizers
    {
        CONST_VTBL struct IInkRecognizersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizers_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkRecognizers_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkRecognizers_GetDefaultRecognizer(This,lcid,DefaultRecognizer)	\
    (This)->lpVtbl -> GetDefaultRecognizer(This,lcid,DefaultRecognizer)

#define IInkRecognizers_Item(This,Index,InkRecognizer)	\
    (This)->lpVtbl -> Item(This,Index,InkRecognizer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_get_Count_Proxy( 
    IInkRecognizers __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IInkRecognizers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_get__NewEnum_Proxy( 
    IInkRecognizers __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);


void __RPC_STUB IInkRecognizers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_GetDefaultRecognizer_Proxy( 
    IInkRecognizers __RPC_FAR * This,
    /* [defaultvalue][in] */ long lcid,
    /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *DefaultRecognizer);


void __RPC_STUB IInkRecognizers_GetDefaultRecognizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_Item_Proxy( 
    IInkRecognizers __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *InkRecognizer);


void __RPC_STUB IInkRecognizers_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizers_INTERFACE_DEFINED__ */


#ifndef __IInkRecognizerContext_INTERFACE_DEFINED__
#define __IInkRecognizerContext_INTERFACE_DEFINED__

/* interface IInkRecognizerContext */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizerContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C68F52F9-32A3-4625-906C-44FC23B40958")
    IInkRecognizerContext : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Strokes( 
            /* [in] */ IInkStrokes __RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharacterAutoCompletionMode( 
            /* [retval][out] */ InkRecognizerCharacterAutoCompletionMode __RPC_FAR *Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CharacterAutoCompletionMode( 
            /* [in] */ InkRecognizerCharacterAutoCompletionMode Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Factoid( 
            /* [retval][out] */ BSTR __RPC_FAR *Factoid) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Factoid( 
            /* [in] */ BSTR factoid) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PrefixText( 
            /* [retval][out] */ BSTR __RPC_FAR *Prefix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PrefixText( 
            /* [in] */ BSTR Prefix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SuffixText( 
            /* [retval][out] */ BSTR __RPC_FAR *Suffix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SuffixText( 
            /* [in] */ BSTR Suffix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognitionFlags( 
            /* [retval][out] */ InkRecognitionModes __RPC_FAR *Modes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecognitionFlags( 
            /* [in] */ InkRecognitionModes Modes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WordList( 
            /* [retval][out] */ IInkWordList __RPC_FAR *__RPC_FAR *WordList) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_WordList( 
            /* [in] */ IInkWordList __RPC_FAR *WordList) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Recognizer( 
            /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *Recognizer) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Recognize( 
            /* [out][in] */ InkRecognitionStatus __RPC_FAR *RecognitionStatus,
            /* [retval][out] */ IInkRecognitionResult __RPC_FAR *__RPC_FAR *RecognitionResult) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInkRecognizerContext __RPC_FAR *__RPC_FAR *RecoContext) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IsStringSupported( 
            /* [in] */ BSTR String,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Supported) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizerContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRecognizerContext __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRecognizerContext __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Strokes )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Strokes )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CharacterAutoCompletionMode )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ InkRecognizerCharacterAutoCompletionMode __RPC_FAR *Mode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CharacterAutoCompletionMode )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ InkRecognizerCharacterAutoCompletionMode Mode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Factoid )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Factoid);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Factoid )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ BSTR factoid);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrefixText )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Prefix);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrefixText )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ BSTR Prefix);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SuffixText )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Suffix);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SuffixText )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ BSTR Suffix);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecognitionFlags )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ InkRecognitionModes __RPC_FAR *Modes);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecognitionFlags )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ InkRecognitionModes Modes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WordList )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ IInkWordList __RPC_FAR *__RPC_FAR *WordList);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_WordList )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ IInkWordList __RPC_FAR *WordList);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Recognizer )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *Recognizer);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Recognize )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [out][in] */ InkRecognitionStatus __RPC_FAR *RecognitionStatus,
            /* [retval][out] */ IInkRecognitionResult __RPC_FAR *__RPC_FAR *RecognitionResult);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [retval][out] */ IInkRecognizerContext __RPC_FAR *__RPC_FAR *RecoContext);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsStringSupported )( 
            IInkRecognizerContext __RPC_FAR * This,
            /* [in] */ BSTR String,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Supported);
        
        END_INTERFACE
    } IInkRecognizerContextVtbl;

    interface IInkRecognizerContext
    {
        CONST_VTBL struct IInkRecognizerContextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizerContext_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizerContext_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizerContext_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizerContext_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizerContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizerContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizerContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizerContext_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognizerContext_putref_Strokes(This,Strokes)	\
    (This)->lpVtbl -> putref_Strokes(This,Strokes)

#define IInkRecognizerContext_get_CharacterAutoCompletionMode(This,Mode)	\
    (This)->lpVtbl -> get_CharacterAutoCompletionMode(This,Mode)

#define IInkRecognizerContext_put_CharacterAutoCompletionMode(This,Mode)	\
    (This)->lpVtbl -> put_CharacterAutoCompletionMode(This,Mode)

#define IInkRecognizerContext_get_Factoid(This,Factoid)	\
    (This)->lpVtbl -> get_Factoid(This,Factoid)

#define IInkRecognizerContext_put_Factoid(This,factoid)	\
    (This)->lpVtbl -> put_Factoid(This,factoid)

#define IInkRecognizerContext_get_PrefixText(This,Prefix)	\
    (This)->lpVtbl -> get_PrefixText(This,Prefix)

#define IInkRecognizerContext_put_PrefixText(This,Prefix)	\
    (This)->lpVtbl -> put_PrefixText(This,Prefix)

#define IInkRecognizerContext_get_SuffixText(This,Suffix)	\
    (This)->lpVtbl -> get_SuffixText(This,Suffix)

#define IInkRecognizerContext_put_SuffixText(This,Suffix)	\
    (This)->lpVtbl -> put_SuffixText(This,Suffix)

#define IInkRecognizerContext_get_RecognitionFlags(This,Modes)	\
    (This)->lpVtbl -> get_RecognitionFlags(This,Modes)

#define IInkRecognizerContext_put_RecognitionFlags(This,Modes)	\
    (This)->lpVtbl -> put_RecognitionFlags(This,Modes)

#define IInkRecognizerContext_get_WordList(This,WordList)	\
    (This)->lpVtbl -> get_WordList(This,WordList)

#define IInkRecognizerContext_putref_WordList(This,WordList)	\
    (This)->lpVtbl -> putref_WordList(This,WordList)

#define IInkRecognizerContext_get_Recognizer(This,Recognizer)	\
    (This)->lpVtbl -> get_Recognizer(This,Recognizer)

#define IInkRecognizerContext_Recognize(This,RecognitionStatus,RecognitionResult)	\
    (This)->lpVtbl -> Recognize(This,RecognitionStatus,RecognitionResult)

#define IInkRecognizerContext_Clone(This,RecoContext)	\
    (This)->lpVtbl -> Clone(This,RecoContext)

#define IInkRecognizerContext_IsStringSupported(This,String,Supported)	\
    (This)->lpVtbl -> IsStringSupported(This,String,Supported)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Strokes_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkRecognizerContext_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_putref_Strokes_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *Strokes);


void __RPC_STUB IInkRecognizerContext_putref_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_CharacterAutoCompletionMode_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ InkRecognizerCharacterAutoCompletionMode __RPC_FAR *Mode);


void __RPC_STUB IInkRecognizerContext_get_CharacterAutoCompletionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_CharacterAutoCompletionMode_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ InkRecognizerCharacterAutoCompletionMode Mode);


void __RPC_STUB IInkRecognizerContext_put_CharacterAutoCompletionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Factoid_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Factoid);


void __RPC_STUB IInkRecognizerContext_get_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_Factoid_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ BSTR factoid);


void __RPC_STUB IInkRecognizerContext_put_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_PrefixText_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Prefix);


void __RPC_STUB IInkRecognizerContext_get_PrefixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_PrefixText_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ BSTR Prefix);


void __RPC_STUB IInkRecognizerContext_put_PrefixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_SuffixText_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Suffix);


void __RPC_STUB IInkRecognizerContext_get_SuffixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_SuffixText_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ BSTR Suffix);


void __RPC_STUB IInkRecognizerContext_put_SuffixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_RecognitionFlags_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ InkRecognitionModes __RPC_FAR *Modes);


void __RPC_STUB IInkRecognizerContext_get_RecognitionFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_RecognitionFlags_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ InkRecognitionModes Modes);


void __RPC_STUB IInkRecognizerContext_put_RecognitionFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_WordList_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ IInkWordList __RPC_FAR *__RPC_FAR *WordList);


void __RPC_STUB IInkRecognizerContext_get_WordList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_putref_WordList_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ IInkWordList __RPC_FAR *WordList);


void __RPC_STUB IInkRecognizerContext_putref_WordList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Recognizer_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ IInkRecognizer __RPC_FAR *__RPC_FAR *Recognizer);


void __RPC_STUB IInkRecognizerContext_get_Recognizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_Recognize_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [out][in] */ InkRecognitionStatus __RPC_FAR *RecognitionStatus,
    /* [retval][out] */ IInkRecognitionResult __RPC_FAR *__RPC_FAR *RecognitionResult);


void __RPC_STUB IInkRecognizerContext_Recognize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_Clone_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [retval][out] */ IInkRecognizerContext __RPC_FAR *__RPC_FAR *RecoContext);


void __RPC_STUB IInkRecognizerContext_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_IsStringSupported_Proxy( 
    IInkRecognizerContext __RPC_FAR * This,
    /* [in] */ BSTR String,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Supported);


void __RPC_STUB IInkRecognizerContext_IsStringSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizerContext_INTERFACE_DEFINED__ */


#ifndef __IInkRecognitionResult_INTERFACE_DEFINED__
#define __IInkRecognitionResult_INTERFACE_DEFINED__

/* interface IInkRecognitionResult */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognitionResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BC129A8-86CD-45ad-BDE8-E0D32D61C16D")
    IInkRecognitionResult : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TopString( 
            /* [retval][out] */ BSTR __RPC_FAR *TopString) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TopAlternate( 
            /* [retval][out] */ IInkRecognitionAlternate __RPC_FAR *__RPC_FAR *TopAlternate) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TopConfidence( 
            /* [retval][out] */ InkRecognitionConfidence __RPC_FAR *TopConfidence) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AlternatesFromSelection( 
            /* [defaultvalue][in] */ long selectionStart,
            /* [defaultvalue][in] */ long selectionLength,
            /* [defaultvalue][in] */ long maximumAlternates,
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *AlternatesFromSelection) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyTopAlternate( 
            /* [in] */ IInkRecognitionAlternate __RPC_FAR *Alternate) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetResultOnStrokes( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognitionResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRecognitionResult __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRecognitionResult __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopString )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *TopString);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopAlternate )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [retval][out] */ IInkRecognitionAlternate __RPC_FAR *__RPC_FAR *TopAlternate);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopConfidence )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [retval][out] */ InkRecognitionConfidence __RPC_FAR *TopConfidence);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Strokes )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AlternatesFromSelection )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [defaultvalue][in] */ long selectionStart,
            /* [defaultvalue][in] */ long selectionLength,
            /* [defaultvalue][in] */ long maximumAlternates,
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *AlternatesFromSelection);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyTopAlternate )( 
            IInkRecognitionResult __RPC_FAR * This,
            /* [in] */ IInkRecognitionAlternate __RPC_FAR *Alternate);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetResultOnStrokes )( 
            IInkRecognitionResult __RPC_FAR * This);
        
        END_INTERFACE
    } IInkRecognitionResultVtbl;

    interface IInkRecognitionResult
    {
        CONST_VTBL struct IInkRecognitionResultVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognitionResult_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognitionResult_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognitionResult_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognitionResult_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognitionResult_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognitionResult_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognitionResult_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognitionResult_get_TopString(This,TopString)	\
    (This)->lpVtbl -> get_TopString(This,TopString)

#define IInkRecognitionResult_get_TopAlternate(This,TopAlternate)	\
    (This)->lpVtbl -> get_TopAlternate(This,TopAlternate)

#define IInkRecognitionResult_get_TopConfidence(This,TopConfidence)	\
    (This)->lpVtbl -> get_TopConfidence(This,TopConfidence)

#define IInkRecognitionResult_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognitionResult_AlternatesFromSelection(This,selectionStart,selectionLength,maximumAlternates,AlternatesFromSelection)	\
    (This)->lpVtbl -> AlternatesFromSelection(This,selectionStart,selectionLength,maximumAlternates,AlternatesFromSelection)

#define IInkRecognitionResult_ModifyTopAlternate(This,Alternate)	\
    (This)->lpVtbl -> ModifyTopAlternate(This,Alternate)

#define IInkRecognitionResult_SetResultOnStrokes(This)	\
    (This)->lpVtbl -> SetResultOnStrokes(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_TopString_Proxy( 
    IInkRecognitionResult __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *TopString);


void __RPC_STUB IInkRecognitionResult_get_TopString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_TopAlternate_Proxy( 
    IInkRecognitionResult __RPC_FAR * This,
    /* [retval][out] */ IInkRecognitionAlternate __RPC_FAR *__RPC_FAR *TopAlternate);


void __RPC_STUB IInkRecognitionResult_get_TopAlternate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_TopConfidence_Proxy( 
    IInkRecognitionResult __RPC_FAR * This,
    /* [retval][out] */ InkRecognitionConfidence __RPC_FAR *TopConfidence);


void __RPC_STUB IInkRecognitionResult_get_TopConfidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_Strokes_Proxy( 
    IInkRecognitionResult __RPC_FAR * This,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkRecognitionResult_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_AlternatesFromSelection_Proxy( 
    IInkRecognitionResult __RPC_FAR * This,
    /* [defaultvalue][in] */ long selectionStart,
    /* [defaultvalue][in] */ long selectionLength,
    /* [defaultvalue][in] */ long maximumAlternates,
    /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *AlternatesFromSelection);


void __RPC_STUB IInkRecognitionResult_AlternatesFromSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_ModifyTopAlternate_Proxy( 
    IInkRecognitionResult __RPC_FAR * This,
    /* [in] */ IInkRecognitionAlternate __RPC_FAR *Alternate);


void __RPC_STUB IInkRecognitionResult_ModifyTopAlternate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_SetResultOnStrokes_Proxy( 
    IInkRecognitionResult __RPC_FAR * This);


void __RPC_STUB IInkRecognitionResult_SetResultOnStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognitionResult_INTERFACE_DEFINED__ */


#ifndef __IInkRecognitionAlternate_INTERFACE_DEFINED__
#define __IInkRecognitionAlternate_INTERFACE_DEFINED__

/* interface IInkRecognitionAlternate */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognitionAlternate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7E660AD-77E4-429b-ADDA-873780D1FC4A")
    IInkRecognitionAlternate : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_String( 
            /* [retval][out] */ BSTR __RPC_FAR *RecoString) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Confidence( 
            /* [retval][out] */ InkRecognitionConfidence __RPC_FAR *Confidence) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Baseline( 
            /* [retval][out] */ VARIANT __RPC_FAR *Baseline) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Midline( 
            /* [retval][out] */ VARIANT __RPC_FAR *Midline) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ascender( 
            /* [retval][out] */ VARIANT __RPC_FAR *Ascender) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Descender( 
            /* [retval][out] */ VARIANT __RPC_FAR *Descender) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineNumber( 
            /* [retval][out] */ long __RPC_FAR *LineNumber) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineAlternates( 
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *LineAlternates) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfidenceAlternates( 
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *ConfidenceAlternates) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStrokesFromStrokeRanges( 
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *GetStrokesFromStrokeRanges) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStrokesFromTextRange( 
            /* [out][in] */ long __RPC_FAR *selectionStart,
            /* [out][in] */ long __RPC_FAR *selectionLength,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *GetStrokesFromTextRange) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTextRangeFromStrokes( 
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [out][in] */ long __RPC_FAR *selectionStart,
            /* [out][in] */ long __RPC_FAR *selectionLength) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AlternatesWithConstantPropertyValues( 
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *AlternatesWithConstantPropertyValues) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyValue( 
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *PropertyValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognitionAlternateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRecognitionAlternate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRecognitionAlternate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_String )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *RecoString);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Confidence )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ InkRecognitionConfidence __RPC_FAR *Confidence);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Baseline )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Baseline);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Midline )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Midline);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ascender )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Ascender);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Descender )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Descender);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LineNumber )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *LineNumber);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Strokes )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LineAlternates )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *LineAlternates);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConfidenceAlternates )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *ConfidenceAlternates);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStrokesFromStrokeRanges )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *GetStrokesFromStrokeRanges);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStrokesFromTextRange )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [out][in] */ long __RPC_FAR *selectionStart,
            /* [out][in] */ long __RPC_FAR *selectionLength,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *GetStrokesFromTextRange);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTextRangeFromStrokes )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [out][in] */ long __RPC_FAR *selectionStart,
            /* [out][in] */ long __RPC_FAR *selectionLength);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AlternatesWithConstantPropertyValues )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *AlternatesWithConstantPropertyValues);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropertyValue )( 
            IInkRecognitionAlternate __RPC_FAR * This,
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *PropertyValue);
        
        END_INTERFACE
    } IInkRecognitionAlternateVtbl;

    interface IInkRecognitionAlternate
    {
        CONST_VTBL struct IInkRecognitionAlternateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognitionAlternate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognitionAlternate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognitionAlternate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognitionAlternate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognitionAlternate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognitionAlternate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognitionAlternate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognitionAlternate_get_String(This,RecoString)	\
    (This)->lpVtbl -> get_String(This,RecoString)

#define IInkRecognitionAlternate_get_Confidence(This,Confidence)	\
    (This)->lpVtbl -> get_Confidence(This,Confidence)

#define IInkRecognitionAlternate_get_Baseline(This,Baseline)	\
    (This)->lpVtbl -> get_Baseline(This,Baseline)

#define IInkRecognitionAlternate_get_Midline(This,Midline)	\
    (This)->lpVtbl -> get_Midline(This,Midline)

#define IInkRecognitionAlternate_get_Ascender(This,Ascender)	\
    (This)->lpVtbl -> get_Ascender(This,Ascender)

#define IInkRecognitionAlternate_get_Descender(This,Descender)	\
    (This)->lpVtbl -> get_Descender(This,Descender)

#define IInkRecognitionAlternate_get_LineNumber(This,LineNumber)	\
    (This)->lpVtbl -> get_LineNumber(This,LineNumber)

#define IInkRecognitionAlternate_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognitionAlternate_get_LineAlternates(This,LineAlternates)	\
    (This)->lpVtbl -> get_LineAlternates(This,LineAlternates)

#define IInkRecognitionAlternate_get_ConfidenceAlternates(This,ConfidenceAlternates)	\
    (This)->lpVtbl -> get_ConfidenceAlternates(This,ConfidenceAlternates)

#define IInkRecognitionAlternate_GetStrokesFromStrokeRanges(This,Strokes,GetStrokesFromStrokeRanges)	\
    (This)->lpVtbl -> GetStrokesFromStrokeRanges(This,Strokes,GetStrokesFromStrokeRanges)

#define IInkRecognitionAlternate_GetStrokesFromTextRange(This,selectionStart,selectionLength,GetStrokesFromTextRange)	\
    (This)->lpVtbl -> GetStrokesFromTextRange(This,selectionStart,selectionLength,GetStrokesFromTextRange)

#define IInkRecognitionAlternate_GetTextRangeFromStrokes(This,Strokes,selectionStart,selectionLength)	\
    (This)->lpVtbl -> GetTextRangeFromStrokes(This,Strokes,selectionStart,selectionLength)

#define IInkRecognitionAlternate_AlternatesWithConstantPropertyValues(This,PropertyType,AlternatesWithConstantPropertyValues)	\
    (This)->lpVtbl -> AlternatesWithConstantPropertyValues(This,PropertyType,AlternatesWithConstantPropertyValues)

#define IInkRecognitionAlternate_GetPropertyValue(This,PropertyType,PropertyValue)	\
    (This)->lpVtbl -> GetPropertyValue(This,PropertyType,PropertyValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_String_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *RecoString);


void __RPC_STUB IInkRecognitionAlternate_get_String_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Confidence_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ InkRecognitionConfidence __RPC_FAR *Confidence);


void __RPC_STUB IInkRecognitionAlternate_get_Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Baseline_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Baseline);


void __RPC_STUB IInkRecognitionAlternate_get_Baseline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Midline_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Midline);


void __RPC_STUB IInkRecognitionAlternate_get_Midline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Ascender_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Ascender);


void __RPC_STUB IInkRecognitionAlternate_get_Ascender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Descender_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Descender);


void __RPC_STUB IInkRecognitionAlternate_get_Descender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_LineNumber_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *LineNumber);


void __RPC_STUB IInkRecognitionAlternate_get_LineNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Strokes_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkRecognitionAlternate_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_LineAlternates_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *LineAlternates);


void __RPC_STUB IInkRecognitionAlternate_get_LineAlternates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_ConfidenceAlternates_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *ConfidenceAlternates);


void __RPC_STUB IInkRecognitionAlternate_get_ConfidenceAlternates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetStrokesFromStrokeRanges_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *Strokes,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *GetStrokesFromStrokeRanges);


void __RPC_STUB IInkRecognitionAlternate_GetStrokesFromStrokeRanges_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetStrokesFromTextRange_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [out][in] */ long __RPC_FAR *selectionStart,
    /* [out][in] */ long __RPC_FAR *selectionLength,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *GetStrokesFromTextRange);


void __RPC_STUB IInkRecognitionAlternate_GetStrokesFromTextRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetTextRangeFromStrokes_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *Strokes,
    /* [out][in] */ long __RPC_FAR *selectionStart,
    /* [out][in] */ long __RPC_FAR *selectionLength);


void __RPC_STUB IInkRecognitionAlternate_GetTextRangeFromStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_AlternatesWithConstantPropertyValues_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [in] */ BSTR PropertyType,
    /* [retval][out] */ IInkRecognitionAlternates __RPC_FAR *__RPC_FAR *AlternatesWithConstantPropertyValues);


void __RPC_STUB IInkRecognitionAlternate_AlternatesWithConstantPropertyValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetPropertyValue_Proxy( 
    IInkRecognitionAlternate __RPC_FAR * This,
    /* [in] */ BSTR PropertyType,
    /* [retval][out] */ VARIANT __RPC_FAR *PropertyValue);


void __RPC_STUB IInkRecognitionAlternate_GetPropertyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognitionAlternate_INTERFACE_DEFINED__ */


#ifndef __IInkRecognitionAlternates_INTERFACE_DEFINED__
#define __IInkRecognitionAlternates_INTERFACE_DEFINED__

/* interface IInkRecognitionAlternates */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognitionAlternates;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("286A167F-9F19-4c61-9D53-4F07BE622B84")
    IInkRecognitionAlternates : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognitionAlternate __RPC_FAR *__RPC_FAR *InkRecoAlternate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognitionAlternatesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRecognitionAlternates __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRecognitionAlternates __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Strokes )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IInkRecognitionAlternates __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognitionAlternate __RPC_FAR *__RPC_FAR *InkRecoAlternate);
        
        END_INTERFACE
    } IInkRecognitionAlternatesVtbl;

    interface IInkRecognitionAlternates
    {
        CONST_VTBL struct IInkRecognitionAlternatesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognitionAlternates_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognitionAlternates_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognitionAlternates_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognitionAlternates_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognitionAlternates_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognitionAlternates_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognitionAlternates_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognitionAlternates_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkRecognitionAlternates_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkRecognitionAlternates_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognitionAlternates_Item(This,Index,InkRecoAlternate)	\
    (This)->lpVtbl -> Item(This,Index,InkRecoAlternate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_get_Count_Proxy( 
    IInkRecognitionAlternates __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IInkRecognitionAlternates_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_get__NewEnum_Proxy( 
    IInkRecognitionAlternates __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);


void __RPC_STUB IInkRecognitionAlternates_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_get_Strokes_Proxy( 
    IInkRecognitionAlternates __RPC_FAR * This,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkRecognitionAlternates_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_Item_Proxy( 
    IInkRecognitionAlternates __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkRecognitionAlternate __RPC_FAR *__RPC_FAR *InkRecoAlternate);


void __RPC_STUB IInkRecognitionAlternates_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognitionAlternates_INTERFACE_DEFINED__ */


#ifndef __IInkWordList_INTERFACE_DEFINED__
#define __IInkWordList_INTERFACE_DEFINED__

/* interface IInkWordList */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkWordList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("76BA3491-CB2F-406b-9961-0E0C4CDAAEF2")
    IInkWordList : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWord( 
            /* [in] */ BSTR NewWord) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveWord( 
            /* [in] */ BSTR RemoveWord) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Merge( 
            /* [in] */ IInkWordList __RPC_FAR *MergeWordList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkWordListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkWordList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkWordList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkWordList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWord )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ BSTR NewWord);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveWord )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ BSTR RemoveWord);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Merge )( 
            IInkWordList __RPC_FAR * This,
            /* [in] */ IInkWordList __RPC_FAR *MergeWordList);
        
        END_INTERFACE
    } IInkWordListVtbl;

    interface IInkWordList
    {
        CONST_VTBL struct IInkWordListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkWordList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkWordList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkWordList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkWordList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkWordList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkWordList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkWordList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkWordList_AddWord(This,NewWord)	\
    (This)->lpVtbl -> AddWord(This,NewWord)

#define IInkWordList_RemoveWord(This,RemoveWord)	\
    (This)->lpVtbl -> RemoveWord(This,RemoveWord)

#define IInkWordList_Merge(This,MergeWordList)	\
    (This)->lpVtbl -> Merge(This,MergeWordList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkWordList_AddWord_Proxy( 
    IInkWordList __RPC_FAR * This,
    /* [in] */ BSTR NewWord);


void __RPC_STUB IInkWordList_AddWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkWordList_RemoveWord_Proxy( 
    IInkWordList __RPC_FAR * This,
    /* [in] */ BSTR RemoveWord);


void __RPC_STUB IInkWordList_RemoveWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkWordList_Merge_Proxy( 
    IInkWordList __RPC_FAR * This,
    /* [in] */ IInkWordList __RPC_FAR *MergeWordList);


void __RPC_STUB IInkWordList_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkWordList_INTERFACE_DEFINED__ */


#ifndef __IInkDisp_INTERFACE_DEFINED__
#define __IInkDisp_INTERFACE_DEFINED__

/* interface IInkDisp */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9D398FA0-C4E2-4fcd-9973-975CAAF47EA6")
    IInkDisp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedProperties( 
            /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dirty( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Dirty) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Dirty( 
            /* [in] */ VARIANT_BOOL Dirty) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomStrokes( 
            /* [retval][out] */ IInkCustomStrokes __RPC_FAR *__RPC_FAR *ppunkInkCustomStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingBox( 
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteStrokes( 
            /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *Strokes = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteStroke( 
            /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ExtractStrokes( 
            /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [defaultvalue][in] */ InkExtractFlags ExtractFlags,
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *ExtractedInk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *NewInk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestCircle( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float radius,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestWithRectangle( 
            /* [in] */ IInkRectangle __RPC_FAR *SelectionRectangle,
            /* [in] */ float IntersectPercent,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestWithLasso( 
            /* [in] */ VARIANT Points,
            /* [in] */ float IntersectPercent,
            /* [defaultvalue][out][in] */ VARIANT __RPC_FAR *LassoPoints,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStrokes( 
            /* [defaultvalue][in] */ VARIANT StrokeIds,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddStrokesAtRectangle( 
            /* [in] */ IInkStrokes __RPC_FAR *SourceStrokes,
            /* [in] */ IInkRectangle __RPC_FAR *TargetRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ InkPersistenceFormat PersistenceFormat,
            /* [defaultvalue][in] */ InkPersistenceCompressionMode CompressionMode,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT Data) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStroke( 
            /* [in] */ VARIANT PacketData,
            /* [in] */ VARIANT PacketDescription,
            /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardCopy( 
            /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *strokes,
            /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
            /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
            /* [retval][out] */ IDataObject __RPC_FAR *__RPC_FAR *DataObject) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CanPaste( 
            /* [defaultvalue][in] */ IDataObject __RPC_FAR *DataObject,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *CanPaste) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardPaste( 
            /* [defaultvalue][in] */ long x,
            /* [defaultvalue][in] */ long y,
            /* [defaultvalue][in] */ IDataObject __RPC_FAR *DataObject,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkDisp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkDisp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkDisp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Strokes )( 
            IInkDisp __RPC_FAR * This,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedProperties )( 
            IInkDisp __RPC_FAR * This,
            /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dirty )( 
            IInkDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Dirty);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Dirty )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Dirty);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CustomStrokes )( 
            IInkDisp __RPC_FAR * This,
            /* [retval][out] */ IInkCustomStrokes __RPC_FAR *__RPC_FAR *ppunkInkCustomStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBoundingBox )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteStrokes )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteStroke )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExtractStrokes )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [defaultvalue][in] */ InkExtractFlags ExtractFlags,
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *ExtractedInk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clip )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IInkDisp __RPC_FAR * This,
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *NewInk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HitTestCircle )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float radius,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HitTestWithRectangle )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *SelectionRectangle,
            /* [in] */ float IntersectPercent,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HitTestWithLasso )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ VARIANT Points,
            /* [in] */ float IntersectPercent,
            /* [defaultvalue][out][in] */ VARIANT __RPC_FAR *LassoPoints,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStrokes )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT StrokeIds,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddStrokesAtRectangle )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *SourceStrokes,
            /* [in] */ IInkRectangle __RPC_FAR *TargetRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ InkPersistenceFormat PersistenceFormat,
            /* [defaultvalue][in] */ InkPersistenceCompressionMode CompressionMode,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ VARIANT Data);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStroke )( 
            IInkDisp __RPC_FAR * This,
            /* [in] */ VARIANT PacketData,
            /* [in] */ VARIANT PacketDescription,
            /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClipboardCopy )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *strokes,
            /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
            /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
            /* [retval][out] */ IDataObject __RPC_FAR *__RPC_FAR *DataObject);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanPaste )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ IDataObject __RPC_FAR *DataObject,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *CanPaste);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClipboardPaste )( 
            IInkDisp __RPC_FAR * This,
            /* [defaultvalue][in] */ long x,
            /* [defaultvalue][in] */ long y,
            /* [defaultvalue][in] */ IDataObject __RPC_FAR *DataObject,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        END_INTERFACE
    } IInkDispVtbl;

    interface IInkDisp
    {
        CONST_VTBL struct IInkDispVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDisp_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkDisp_get_ExtendedProperties(This,Properties)	\
    (This)->lpVtbl -> get_ExtendedProperties(This,Properties)

#define IInkDisp_get_Dirty(This,Dirty)	\
    (This)->lpVtbl -> get_Dirty(This,Dirty)

#define IInkDisp_put_Dirty(This,Dirty)	\
    (This)->lpVtbl -> put_Dirty(This,Dirty)

#define IInkDisp_get_CustomStrokes(This,ppunkInkCustomStrokes)	\
    (This)->lpVtbl -> get_CustomStrokes(This,ppunkInkCustomStrokes)

#define IInkDisp_GetBoundingBox(This,BoundingBoxMode,Rectangle)	\
    (This)->lpVtbl -> GetBoundingBox(This,BoundingBoxMode,Rectangle)

#define IInkDisp_DeleteStrokes(This,Strokes)	\
    (This)->lpVtbl -> DeleteStrokes(This,Strokes)

#define IInkDisp_DeleteStroke(This,Stroke)	\
    (This)->lpVtbl -> DeleteStroke(This,Stroke)

#define IInkDisp_ExtractStrokes(This,Strokes,ExtractFlags,ExtractedInk)	\
    (This)->lpVtbl -> ExtractStrokes(This,Strokes,ExtractFlags,ExtractedInk)

#define IInkDisp_Clip(This,Rectangle)	\
    (This)->lpVtbl -> Clip(This,Rectangle)

#define IInkDisp_Clone(This,NewInk)	\
    (This)->lpVtbl -> Clone(This,NewInk)

#define IInkDisp_HitTestCircle(This,X,Y,radius,Strokes)	\
    (This)->lpVtbl -> HitTestCircle(This,X,Y,radius,Strokes)

#define IInkDisp_HitTestWithRectangle(This,SelectionRectangle,IntersectPercent,Strokes)	\
    (This)->lpVtbl -> HitTestWithRectangle(This,SelectionRectangle,IntersectPercent,Strokes)

#define IInkDisp_HitTestWithLasso(This,Points,IntersectPercent,LassoPoints,Strokes)	\
    (This)->lpVtbl -> HitTestWithLasso(This,Points,IntersectPercent,LassoPoints,Strokes)

#define IInkDisp_CreateStrokes(This,StrokeIds,Strokes)	\
    (This)->lpVtbl -> CreateStrokes(This,StrokeIds,Strokes)

#define IInkDisp_AddStrokesAtRectangle(This,SourceStrokes,TargetRectangle)	\
    (This)->lpVtbl -> AddStrokesAtRectangle(This,SourceStrokes,TargetRectangle)

#define IInkDisp_Save(This,PersistenceFormat,CompressionMode,Data)	\
    (This)->lpVtbl -> Save(This,PersistenceFormat,CompressionMode,Data)

#define IInkDisp_Load(This,Data)	\
    (This)->lpVtbl -> Load(This,Data)

#define IInkDisp_CreateStroke(This,PacketData,PacketDescription,Stroke)	\
    (This)->lpVtbl -> CreateStroke(This,PacketData,PacketDescription,Stroke)

#define IInkDisp_ClipboardCopy(This,strokes,ClipboardFormats,ClipboardModes,DataObject)	\
    (This)->lpVtbl -> ClipboardCopy(This,strokes,ClipboardFormats,ClipboardModes,DataObject)

#define IInkDisp_CanPaste(This,DataObject,CanPaste)	\
    (This)->lpVtbl -> CanPaste(This,DataObject,CanPaste)

#define IInkDisp_ClipboardPaste(This,x,y,DataObject,Strokes)	\
    (This)->lpVtbl -> ClipboardPaste(This,x,y,DataObject,Strokes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_Strokes_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_ExtendedProperties_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [retval][out] */ IInkExtendedProperties __RPC_FAR *__RPC_FAR *Properties);


void __RPC_STUB IInkDisp_get_ExtendedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_Dirty_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Dirty);


void __RPC_STUB IInkDisp_get_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDisp_put_Dirty_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Dirty);


void __RPC_STUB IInkDisp_put_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_CustomStrokes_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [retval][out] */ IInkCustomStrokes __RPC_FAR *__RPC_FAR *ppunkInkCustomStrokes);


void __RPC_STUB IInkDisp_get_CustomStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_GetBoundingBox_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
    /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);


void __RPC_STUB IInkDisp_GetBoundingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_DeleteStrokes_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_DeleteStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_DeleteStroke_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke);


void __RPC_STUB IInkDisp_DeleteStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ExtractStrokes_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *Strokes,
    /* [defaultvalue][in] */ InkExtractFlags ExtractFlags,
    /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *ExtractedInk);


void __RPC_STUB IInkDisp_ExtractStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Clip_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rectangle);


void __RPC_STUB IInkDisp_Clip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Clone_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *NewInk);


void __RPC_STUB IInkDisp_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_HitTestCircle_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [in] */ float radius,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_HitTestCircle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_HitTestWithRectangle_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *SelectionRectangle,
    /* [in] */ float IntersectPercent,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_HitTestWithRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_HitTestWithLasso_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ VARIANT Points,
    /* [in] */ float IntersectPercent,
    /* [defaultvalue][out][in] */ VARIANT __RPC_FAR *LassoPoints,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_HitTestWithLasso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_CreateStrokes_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT StrokeIds,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_CreateStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_AddStrokesAtRectangle_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *SourceStrokes,
    /* [in] */ IInkRectangle __RPC_FAR *TargetRectangle);


void __RPC_STUB IInkDisp_AddStrokesAtRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Save_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ InkPersistenceFormat PersistenceFormat,
    /* [defaultvalue][in] */ InkPersistenceCompressionMode CompressionMode,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB IInkDisp_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Load_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ VARIANT Data);


void __RPC_STUB IInkDisp_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_CreateStroke_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [in] */ VARIANT PacketData,
    /* [in] */ VARIANT PacketDescription,
    /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *Stroke);


void __RPC_STUB IInkDisp_CreateStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ClipboardCopy_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ IInkStrokes __RPC_FAR *strokes,
    /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
    /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
    /* [retval][out] */ IDataObject __RPC_FAR *__RPC_FAR *DataObject);


void __RPC_STUB IInkDisp_ClipboardCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_CanPaste_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ IDataObject __RPC_FAR *DataObject,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *CanPaste);


void __RPC_STUB IInkDisp_CanPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ClipboardPaste_Proxy( 
    IInkDisp __RPC_FAR * This,
    /* [defaultvalue][in] */ long x,
    /* [defaultvalue][in] */ long y,
    /* [defaultvalue][in] */ IDataObject __RPC_FAR *DataObject,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkDisp_ClipboardPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDisp_INTERFACE_DEFINED__ */


#ifndef __IInkStrokes_INTERFACE_DEFINED__
#define __IInkStrokes_INTERFACE_DEFINED__

/* interface IInkStrokes */
/* [unique][dual][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkStrokes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1F4C9D8-590A-4963-B3AE-1935671BB6F3")
    IInkStrokes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognitionResult( 
            /* [retval][out] */ IInkRecognitionResult __RPC_FAR *__RPC_FAR *RecognitionResult) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToString( 
            /* [retval][out] */ BSTR __RPC_FAR *ToString) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IInkStrokeDisp __RPC_FAR *InkStroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddStrokes( 
            /* [in] */ IInkStrokes __RPC_FAR *InkStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ IInkStrokeDisp __RPC_FAR *InkStroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveStrokes( 
            /* [in] */ IInkStrokes __RPC_FAR *InkStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyDrawingAttributes( 
            /* [in] */ IInkDrawingAttributes __RPC_FAR *DrawAttrs) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingBox( 
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *BoundingBox) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IInkTransform __RPC_FAR *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleToRectangle( 
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Shear( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveRecognitionResult( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkStrokesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkStrokes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkStrokes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkStrokes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IInkStrokes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IInkStrokes __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ink )( 
            IInkStrokes __RPC_FAR * This,
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecognitionResult )( 
            IInkStrokes __RPC_FAR * This,
            /* [retval][out] */ IInkRecognitionResult __RPC_FAR *__RPC_FAR *RecognitionResult);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ToString )( 
            IInkStrokes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ToString);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkStrokeDisp __RPC_FAR *InkStroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddStrokes )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *InkStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkStrokeDisp __RPC_FAR *InkStroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveStrokes )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *InkStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyDrawingAttributes )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkDrawingAttributes __RPC_FAR *DrawAttrs);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBoundingBox )( 
            IInkStrokes __RPC_FAR * This,
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *BoundingBox);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Transform )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkTransform __RPC_FAR *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleToRectangle )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shear )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleTransform )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clip )( 
            IInkStrokes __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveRecognitionResult )( 
            IInkStrokes __RPC_FAR * This);
        
        END_INTERFACE
    } IInkStrokesVtbl;

    interface IInkStrokes
    {
        CONST_VTBL struct IInkStrokesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkStrokes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkStrokes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkStrokes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkStrokes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkStrokes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkStrokes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkStrokes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkStrokes_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkStrokes_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkStrokes_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkStrokes_get_RecognitionResult(This,RecognitionResult)	\
    (This)->lpVtbl -> get_RecognitionResult(This,RecognitionResult)

#define IInkStrokes_ToString(This,ToString)	\
    (This)->lpVtbl -> ToString(This,ToString)

#define IInkStrokes_Item(This,Index,Stroke)	\
    (This)->lpVtbl -> Item(This,Index,Stroke)

#define IInkStrokes_Add(This,InkStroke)	\
    (This)->lpVtbl -> Add(This,InkStroke)

#define IInkStrokes_AddStrokes(This,InkStrokes)	\
    (This)->lpVtbl -> AddStrokes(This,InkStrokes)

#define IInkStrokes_Remove(This,InkStroke)	\
    (This)->lpVtbl -> Remove(This,InkStroke)

#define IInkStrokes_RemoveStrokes(This,InkStrokes)	\
    (This)->lpVtbl -> RemoveStrokes(This,InkStrokes)

#define IInkStrokes_ModifyDrawingAttributes(This,DrawAttrs)	\
    (This)->lpVtbl -> ModifyDrawingAttributes(This,DrawAttrs)

#define IInkStrokes_GetBoundingBox(This,BoundingBoxMode,BoundingBox)	\
    (This)->lpVtbl -> GetBoundingBox(This,BoundingBoxMode,BoundingBox)

#define IInkStrokes_Transform(This,Transform,ApplyOnPenWidth)	\
    (This)->lpVtbl -> Transform(This,Transform,ApplyOnPenWidth)

#define IInkStrokes_ScaleToRectangle(This,Rectangle)	\
    (This)->lpVtbl -> ScaleToRectangle(This,Rectangle)

#define IInkStrokes_Move(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Move(This,HorizontalComponent,VerticalComponent)

#define IInkStrokes_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkStrokes_Shear(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> Shear(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkStrokes_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkStrokes_Clip(This,Rectangle)	\
    (This)->lpVtbl -> Clip(This,Rectangle)

#define IInkStrokes_RemoveRecognitionResult(This)	\
    (This)->lpVtbl -> RemoveRecognitionResult(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get_Count_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IInkStrokes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get__NewEnum_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);


void __RPC_STUB IInkStrokes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get_Ink_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink);


void __RPC_STUB IInkStrokes_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get_RecognitionResult_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [retval][out] */ IInkRecognitionResult __RPC_FAR *__RPC_FAR *RecognitionResult);


void __RPC_STUB IInkStrokes_get_RecognitionResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ToString_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ToString);


void __RPC_STUB IInkStrokes_ToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Item_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkStrokeDisp __RPC_FAR *__RPC_FAR *Stroke);


void __RPC_STUB IInkStrokes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Add_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkStrokeDisp __RPC_FAR *InkStroke);


void __RPC_STUB IInkStrokes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_AddStrokes_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *InkStrokes);


void __RPC_STUB IInkStrokes_AddStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Remove_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkStrokeDisp __RPC_FAR *InkStroke);


void __RPC_STUB IInkStrokes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_RemoveStrokes_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *InkStrokes);


void __RPC_STUB IInkStrokes_RemoveStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ModifyDrawingAttributes_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkDrawingAttributes __RPC_FAR *DrawAttrs);


void __RPC_STUB IInkStrokes_ModifyDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_GetBoundingBox_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
    /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *BoundingBox);


void __RPC_STUB IInkStrokes_GetBoundingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Transform_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkTransform __RPC_FAR *Transform,
    /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);


void __RPC_STUB IInkStrokes_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ScaleToRectangle_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rectangle);


void __RPC_STUB IInkStrokes_ScaleToRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Move_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkStrokes_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Rotate_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkStrokes_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Shear_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokes_Shear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ScaleTransform_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokes_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Clip_Proxy( 
    IInkStrokes __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rectangle);


void __RPC_STUB IInkStrokes_Clip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_RemoveRecognitionResult_Proxy( 
    IInkStrokes __RPC_FAR * This);


void __RPC_STUB IInkStrokes_RemoveRecognitionResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkStrokes_INTERFACE_DEFINED__ */


#ifndef __IInkCustomStrokes_INTERFACE_DEFINED__
#define __IInkCustomStrokes_INTERFACE_DEFINED__

/* interface IInkCustomStrokes */
/* [unique][dual][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkCustomStrokes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E23A88F-C30E-420f-9BDB-28902543F0C1")
    IInkCustomStrokes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Identifier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCustomStrokesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkCustomStrokes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkCustomStrokes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IInkCustomStrokes __RPC_FAR * This,
            /* [in] */ VARIANT Identifier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IInkCustomStrokes __RPC_FAR * This);
        
        END_INTERFACE
    } IInkCustomStrokesVtbl;

    interface IInkCustomStrokes
    {
        CONST_VTBL struct IInkCustomStrokesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCustomStrokes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCustomStrokes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCustomStrokes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCustomStrokes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCustomStrokes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCustomStrokes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCustomStrokes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCustomStrokes_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkCustomStrokes_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkCustomStrokes_Item(This,Identifier,Strokes)	\
    (This)->lpVtbl -> Item(This,Identifier,Strokes)

#define IInkCustomStrokes_Add(This,Name,Strokes)	\
    (This)->lpVtbl -> Add(This,Name,Strokes)

#define IInkCustomStrokes_Remove(This,Identifier)	\
    (This)->lpVtbl -> Remove(This,Identifier)

#define IInkCustomStrokes_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_get_Count_Proxy( 
    IInkCustomStrokes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IInkCustomStrokes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_get__NewEnum_Proxy( 
    IInkCustomStrokes __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *_NewEnum);


void __RPC_STUB IInkCustomStrokes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Item_Proxy( 
    IInkCustomStrokes __RPC_FAR * This,
    /* [in] */ VARIANT Identifier,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Strokes);


void __RPC_STUB IInkCustomStrokes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Add_Proxy( 
    IInkCustomStrokes __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ IInkStrokes __RPC_FAR *Strokes);


void __RPC_STUB IInkCustomStrokes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Remove_Proxy( 
    IInkCustomStrokes __RPC_FAR * This,
    /* [in] */ VARIANT Identifier);


void __RPC_STUB IInkCustomStrokes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Clear_Proxy( 
    IInkCustomStrokes __RPC_FAR * This);


void __RPC_STUB IInkCustomStrokes_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCustomStrokes_INTERFACE_DEFINED__ */


#ifndef __IInkRenderer_INTERFACE_DEFINED__
#define __IInkRenderer_INTERFACE_DEFINED__

/* interface IInkRenderer */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6257A9C-B511-4f4c-A8B0-A7DBC9506B83")
    IInkRenderer : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetViewTransform( 
            /* [in] */ IInkTransform __RPC_FAR *ViewTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetViewTransform( 
            /* [in] */ IInkTransform __RPC_FAR *ViewTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObjectTransform( 
            /* [in] */ IInkTransform __RPC_FAR *ObjectTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObjectTransform( 
            /* [in] */ IInkTransform __RPC_FAR *ObjectTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ long hDC,
            /* [in] */ IInkStrokes __RPC_FAR *pstcStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawStroke( 
            /* [in] */ long hDC,
            /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes __RPC_FAR *DrawingAttributes = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE PixelToInkSpace( 
            /* [in] */ long hDC,
            /* [out][in] */ long __RPC_FAR *x,
            /* [out][in] */ long __RPC_FAR *y) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE InkSpaceToPixel( 
            /* [in] */ long hdcDisplay,
            /* [out][in] */ long __RPC_FAR *x,
            /* [out][in] */ long __RPC_FAR *y) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE PixelToInkSpaceFromPoints( 
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT __RPC_FAR *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE InkSpaceToPixelFromPoints( 
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT __RPC_FAR *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Measure( 
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE MeasureStroke( 
            /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes __RPC_FAR *DrawingAttributes,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth = -1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkRenderer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkRenderer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkRenderer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetViewTransform )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ IInkTransform __RPC_FAR *ViewTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetViewTransform )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ IInkTransform __RPC_FAR *ViewTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectTransform )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ IInkTransform __RPC_FAR *ObjectTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectTransform )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ IInkTransform __RPC_FAR *ObjectTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ long hDC,
            /* [in] */ IInkStrokes __RPC_FAR *pstcStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawStroke )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ long hDC,
            /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes __RPC_FAR *DrawingAttributes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PixelToInkSpace )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ long hDC,
            /* [out][in] */ long __RPC_FAR *x,
            /* [out][in] */ long __RPC_FAR *y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkSpaceToPixel )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ long hdcDisplay,
            /* [out][in] */ long __RPC_FAR *x,
            /* [out][in] */ long __RPC_FAR *y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PixelToInkSpaceFromPoints )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT __RPC_FAR *Points);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkSpaceToPixelFromPoints )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT __RPC_FAR *Points);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Measure )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *Strokes,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MeasureStroke )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes __RPC_FAR *DrawingAttributes,
            /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleTransform )( 
            IInkRenderer __RPC_FAR * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);
        
        END_INTERFACE
    } IInkRendererVtbl;

    interface IInkRenderer
    {
        CONST_VTBL struct IInkRendererVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRenderer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRenderer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRenderer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRenderer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRenderer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRenderer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRenderer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRenderer_GetViewTransform(This,ViewTransform)	\
    (This)->lpVtbl -> GetViewTransform(This,ViewTransform)

#define IInkRenderer_SetViewTransform(This,ViewTransform)	\
    (This)->lpVtbl -> SetViewTransform(This,ViewTransform)

#define IInkRenderer_GetObjectTransform(This,ObjectTransform)	\
    (This)->lpVtbl -> GetObjectTransform(This,ObjectTransform)

#define IInkRenderer_SetObjectTransform(This,ObjectTransform)	\
    (This)->lpVtbl -> SetObjectTransform(This,ObjectTransform)

#define IInkRenderer_Draw(This,hDC,pstcStrokes)	\
    (This)->lpVtbl -> Draw(This,hDC,pstcStrokes)

#define IInkRenderer_DrawStroke(This,hDC,Stroke,DrawingAttributes)	\
    (This)->lpVtbl -> DrawStroke(This,hDC,Stroke,DrawingAttributes)

#define IInkRenderer_PixelToInkSpace(This,hDC,x,y)	\
    (This)->lpVtbl -> PixelToInkSpace(This,hDC,x,y)

#define IInkRenderer_InkSpaceToPixel(This,hdcDisplay,x,y)	\
    (This)->lpVtbl -> InkSpaceToPixel(This,hdcDisplay,x,y)

#define IInkRenderer_PixelToInkSpaceFromPoints(This,hDC,Points)	\
    (This)->lpVtbl -> PixelToInkSpaceFromPoints(This,hDC,Points)

#define IInkRenderer_InkSpaceToPixelFromPoints(This,hDC,Points)	\
    (This)->lpVtbl -> InkSpaceToPixelFromPoints(This,hDC,Points)

#define IInkRenderer_Measure(This,Strokes,Rectangle)	\
    (This)->lpVtbl -> Measure(This,Strokes,Rectangle)

#define IInkRenderer_MeasureStroke(This,Stroke,DrawingAttributes,Rectangle)	\
    (This)->lpVtbl -> MeasureStroke(This,Stroke,DrawingAttributes,Rectangle)

#define IInkRenderer_Move(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Move(This,HorizontalComponent,VerticalComponent)

#define IInkRenderer_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkRenderer_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier,ApplyOnPenWidth)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier,ApplyOnPenWidth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_GetViewTransform_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ IInkTransform __RPC_FAR *ViewTransform);


void __RPC_STUB IInkRenderer_GetViewTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_SetViewTransform_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ IInkTransform __RPC_FAR *ViewTransform);


void __RPC_STUB IInkRenderer_SetViewTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_GetObjectTransform_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ IInkTransform __RPC_FAR *ObjectTransform);


void __RPC_STUB IInkRenderer_GetObjectTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_SetObjectTransform_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ IInkTransform __RPC_FAR *ObjectTransform);


void __RPC_STUB IInkRenderer_SetObjectTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Draw_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ long hDC,
    /* [in] */ IInkStrokes __RPC_FAR *pstcStrokes);


void __RPC_STUB IInkRenderer_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_DrawStroke_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ long hDC,
    /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke,
    /* [defaultvalue][in] */ IInkDrawingAttributes __RPC_FAR *DrawingAttributes);


void __RPC_STUB IInkRenderer_DrawStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_PixelToInkSpace_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ long hDC,
    /* [out][in] */ long __RPC_FAR *x,
    /* [out][in] */ long __RPC_FAR *y);


void __RPC_STUB IInkRenderer_PixelToInkSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_InkSpaceToPixel_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ long hdcDisplay,
    /* [out][in] */ long __RPC_FAR *x,
    /* [out][in] */ long __RPC_FAR *y);


void __RPC_STUB IInkRenderer_InkSpaceToPixel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_PixelToInkSpaceFromPoints_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ long hDC,
    /* [out][in] */ VARIANT __RPC_FAR *Points);


void __RPC_STUB IInkRenderer_PixelToInkSpaceFromPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_InkSpaceToPixelFromPoints_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ long hDC,
    /* [out][in] */ VARIANT __RPC_FAR *Points);


void __RPC_STUB IInkRenderer_InkSpaceToPixelFromPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Measure_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *Strokes,
    /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);


void __RPC_STUB IInkRenderer_Measure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_MeasureStroke_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ IInkStrokeDisp __RPC_FAR *Stroke,
    /* [defaultvalue][in] */ IInkDrawingAttributes __RPC_FAR *DrawingAttributes,
    /* [retval][out] */ IInkRectangle __RPC_FAR *__RPC_FAR *Rectangle);


void __RPC_STUB IInkRenderer_MeasureStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Move_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkRenderer_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Rotate_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkRenderer_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_ScaleTransform_Proxy( 
    IInkRenderer __RPC_FAR * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier,
    /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);


void __RPC_STUB IInkRenderer_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRenderer_INTERFACE_DEFINED__ */


#ifndef __IInkCursor_INTERFACE_DEFINED__
#define __IInkCursor_INTERFACE_DEFINED__

/* interface IInkCursor */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkCursor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD30C630-40C5-4350-8405-9C71012FC558")
    IInkCursor : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ long __RPC_FAR *Id) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Inverted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Status) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *Attributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DrawingAttributes( 
            /* [in] */ IInkDrawingAttributes __RPC_FAR *Attributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tablet( void) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Buttons( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCursorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkCursor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkCursor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkCursor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkCursor __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkCursor __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkCursor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkCursor __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IInkCursor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Id )( 
            IInkCursor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Id);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Inverted )( 
            IInkCursor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Status);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DrawingAttributes )( 
            IInkCursor __RPC_FAR * This,
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *Attributes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_DrawingAttributes )( 
            IInkCursor __RPC_FAR * This,
            /* [in] */ IInkDrawingAttributes __RPC_FAR *Attributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tablet )( 
            IInkCursor __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Buttons )( 
            IInkCursor __RPC_FAR * This);
        
        END_INTERFACE
    } IInkCursorVtbl;

    interface IInkCursor
    {
        CONST_VTBL struct IInkCursorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCursor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCursor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCursor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCursor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCursor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCursor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCursor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCursor_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IInkCursor_get_Id(This,Id)	\
    (This)->lpVtbl -> get_Id(This,Id)

#define IInkCursor_get_Inverted(This,Status)	\
    (This)->lpVtbl -> get_Inverted(This,Status)

#define IInkCursor_get_DrawingAttributes(This,Attributes)	\
    (This)->lpVtbl -> get_DrawingAttributes(This,Attributes)

#define IInkCursor_putref_DrawingAttributes(This,Attributes)	\
    (This)->lpVtbl -> putref_DrawingAttributes(This,Attributes)

#define IInkCursor_get_Tablet(This)	\
    (This)->lpVtbl -> get_Tablet(This)

#define IInkCursor_get_Buttons(This)	\
    (This)->lpVtbl -> get_Buttons(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Name_Proxy( 
    IInkCursor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB IInkCursor_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Id_Proxy( 
    IInkCursor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Id);


void __RPC_STUB IInkCursor_get_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Inverted_Proxy( 
    IInkCursor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Status);


void __RPC_STUB IInkCursor_get_Inverted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_DrawingAttributes_Proxy( 
    IInkCursor __RPC_FAR * This,
    /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *Attributes);


void __RPC_STUB IInkCursor_get_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkCursor_putref_DrawingAttributes_Proxy( 
    IInkCursor __RPC_FAR * This,
    /* [in] */ IInkDrawingAttributes __RPC_FAR *Attributes);


void __RPC_STUB IInkCursor_putref_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Tablet_Proxy( 
    IInkCursor __RPC_FAR * This);


void __RPC_STUB IInkCursor_get_Tablet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Buttons_Proxy( 
    IInkCursor __RPC_FAR * This);


void __RPC_STUB IInkCursor_get_Buttons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCursor_INTERFACE_DEFINED__ */


#ifndef __IInkOverlay_INTERFACE_DEFINED__
#define __IInkOverlay_INTERFACE_DEFINED__

/* interface IInkOverlay */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkOverlay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b82a463b-c1c5-45a3-997c-deab5651b67a")
    IInkOverlay : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long __RPC_FAR *CurrentWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hWnd( 
            /* [in] */ long NewWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultDrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *CurrentAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DefaultDrawingAttributes( 
            /* [in] */ IInkDrawingAttributes __RPC_FAR *NewAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Renderer( 
            /* [retval][out] */ IInkRenderer __RPC_FAR *__RPC_FAR *CurrentInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Renderer( 
            /* [in] */ IInkRenderer __RPC_FAR *NewInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Ink( 
            /* [in] */ IInkDisp __RPC_FAR *NewInk) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRedraw( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRedraw( 
            /* [in] */ VARIANT_BOOL AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectingInk( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectionMode( 
            /* [retval][out] */ InkCollectionMode __RPC_FAR *Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CollectionMode( 
            /* [in] */ InkCollectionMode Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DynamicRendering( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DynamicRendering( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EditingMode( 
            /* [retval][out] */ InkOverlayEditingMode __RPC_FAR *EditingMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EditingMode( 
            /* [in] */ InkOverlayEditingMode EditingMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Selection( 
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Selection) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Selection( 
            /* [in] */ IInkStrokes __RPC_FAR *Selection) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EraserMode( 
            /* [retval][out] */ InkOverlayEraserMode __RPC_FAR *EraserMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EraserMode( 
            /* [in] */ InkOverlayEraserMode EraserMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastInk( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastInk( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastSelectionUI( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastSelectionUI( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ IInkRectangle __RPC_FAR *Rect) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowInputRectangle( 
            /* [out][in] */ IInkRectangle __RPC_FAR *__RPC_FAR *WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowInputRectangle( 
            /* [in] */ IInkRectangle __RPC_FAR *WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkOverlayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInkOverlay __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInkOverlay __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInkOverlay __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hWnd )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *CurrentWindow);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hWnd )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ long NewWindow);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Collecting);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultDrawingAttributes )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *CurrentAttributes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_DefaultDrawingAttributes )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ IInkDrawingAttributes __RPC_FAR *NewAttributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Renderer )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ IInkRenderer __RPC_FAR *__RPC_FAR *CurrentInkRenderer);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Renderer )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ IInkRenderer __RPC_FAR *NewInkRenderer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ink )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Ink )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ IInkDisp __RPC_FAR *NewInk);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoRedraw )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AutoRedraw);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoRedraw )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL AutoRedraw);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CollectingInk )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CollectionMode )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ InkCollectionMode __RPC_FAR *Mode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CollectionMode )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ InkCollectionMode Mode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DynamicRendering )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DynamicRendering )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EditingMode )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ InkOverlayEditingMode __RPC_FAR *EditingMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EditingMode )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ InkOverlayEditingMode EditingMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Selection )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Selection);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Selection )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ IInkStrokes __RPC_FAR *Selection);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EraserMode )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ InkOverlayEraserMode __RPC_FAR *EraserMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EraserMode )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ InkOverlayEraserMode EraserMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SupportHighContrastInk )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SupportHighContrastInk )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SupportHighContrastSelectionUI )( 
            IInkOverlay __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SupportHighContrastSelectionUI )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *Rect);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowInputRectangle )( 
            IInkOverlay __RPC_FAR * This,
            /* [out][in] */ IInkRectangle __RPC_FAR *__RPC_FAR *WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWindowInputRectangle )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ IInkRectangle __RPC_FAR *WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventInterest )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEventInterest )( 
            IInkOverlay __RPC_FAR * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen);
        
        END_INTERFACE
    } IInkOverlayVtbl;

    interface IInkOverlay
    {
        CONST_VTBL struct IInkOverlayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkOverlay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkOverlay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkOverlay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkOverlay_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkOverlay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkOverlay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkOverlay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkOverlay_get_hWnd(This,CurrentWindow)	\
    (This)->lpVtbl -> get_hWnd(This,CurrentWindow)

#define IInkOverlay_put_hWnd(This,NewWindow)	\
    (This)->lpVtbl -> put_hWnd(This,NewWindow)

#define IInkOverlay_get_Enabled(This,Collecting)	\
    (This)->lpVtbl -> get_Enabled(This,Collecting)

#define IInkOverlay_put_Enabled(This,Collecting)	\
    (This)->lpVtbl -> put_Enabled(This,Collecting)

#define IInkOverlay_get_DefaultDrawingAttributes(This,CurrentAttributes)	\
    (This)->lpVtbl -> get_DefaultDrawingAttributes(This,CurrentAttributes)

#define IInkOverlay_putref_DefaultDrawingAttributes(This,NewAttributes)	\
    (This)->lpVtbl -> putref_DefaultDrawingAttributes(This,NewAttributes)

#define IInkOverlay_get_Renderer(This,CurrentInkRenderer)	\
    (This)->lpVtbl -> get_Renderer(This,CurrentInkRenderer)

#define IInkOverlay_putref_Renderer(This,NewInkRenderer)	\
    (This)->lpVtbl -> putref_Renderer(This,NewInkRenderer)

#define IInkOverlay_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkOverlay_putref_Ink(This,NewInk)	\
    (This)->lpVtbl -> putref_Ink(This,NewInk)

#define IInkOverlay_get_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> get_AutoRedraw(This,AutoRedraw)

#define IInkOverlay_put_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> put_AutoRedraw(This,AutoRedraw)

#define IInkOverlay_get_CollectingInk(This,Collecting)	\
    (This)->lpVtbl -> get_CollectingInk(This,Collecting)

#define IInkOverlay_get_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> get_CollectionMode(This,Mode)

#define IInkOverlay_put_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> put_CollectionMode(This,Mode)

#define IInkOverlay_get_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> get_DynamicRendering(This,Enabled)

#define IInkOverlay_put_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> put_DynamicRendering(This,Enabled)

#define IInkOverlay_get_EditingMode(This,EditingMode)	\
    (This)->lpVtbl -> get_EditingMode(This,EditingMode)

#define IInkOverlay_put_EditingMode(This,EditingMode)	\
    (This)->lpVtbl -> put_EditingMode(This,EditingMode)

#define IInkOverlay_get_Selection(This,Selection)	\
    (This)->lpVtbl -> get_Selection(This,Selection)

#define IInkOverlay_put_Selection(This,Selection)	\
    (This)->lpVtbl -> put_Selection(This,Selection)

#define IInkOverlay_get_EraserMode(This,EraserMode)	\
    (This)->lpVtbl -> get_EraserMode(This,EraserMode)

#define IInkOverlay_put_EraserMode(This,EraserMode)	\
    (This)->lpVtbl -> put_EraserMode(This,EraserMode)

#define IInkOverlay_get_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastInk(This,Support)

#define IInkOverlay_put_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastInk(This,Support)

#define IInkOverlay_get_SupportHighContrastSelectionUI(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastSelectionUI(This,Support)

#define IInkOverlay_put_SupportHighContrastSelectionUI(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastSelectionUI(This,Support)

#define IInkOverlay_Draw(This,Rect)	\
    (This)->lpVtbl -> Draw(This,Rect)

#define IInkOverlay_GetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> GetWindowInputRectangle(This,WindowInputRectangle)

#define IInkOverlay_SetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> SetWindowInputRectangle(This,WindowInputRectangle)

#define IInkOverlay_GetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> GetEventInterest(This,EventId,Listen)

#define IInkOverlay_SetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> SetEventInterest(This,EventId,Listen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_hWnd_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *CurrentWindow);


void __RPC_STUB IInkOverlay_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_hWnd_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ long NewWindow);


void __RPC_STUB IInkOverlay_put_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Enabled_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Collecting);


void __RPC_STUB IInkOverlay_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_Enabled_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Collecting);


void __RPC_STUB IInkOverlay_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_DefaultDrawingAttributes_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ IInkDrawingAttributes __RPC_FAR *__RPC_FAR *CurrentAttributes);


void __RPC_STUB IInkOverlay_get_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_DefaultDrawingAttributes_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ IInkDrawingAttributes __RPC_FAR *NewAttributes);


void __RPC_STUB IInkOverlay_putref_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Renderer_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ IInkRenderer __RPC_FAR *__RPC_FAR *CurrentInkRenderer);


void __RPC_STUB IInkOverlay_get_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_Renderer_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ IInkRenderer __RPC_FAR *NewInkRenderer);


void __RPC_STUB IInkOverlay_putref_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Ink_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ IInkDisp __RPC_FAR *__RPC_FAR *Ink);


void __RPC_STUB IInkOverlay_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_Ink_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ IInkDisp __RPC_FAR *NewInk);


void __RPC_STUB IInkOverlay_putref_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_AutoRedraw_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AutoRedraw);


void __RPC_STUB IInkOverlay_get_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_AutoRedraw_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL AutoRedraw);


void __RPC_STUB IInkOverlay_put_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_CollectingInk_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Collecting);


void __RPC_STUB IInkOverlay_get_CollectingInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_CollectionMode_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ InkCollectionMode __RPC_FAR *Mode);


void __RPC_STUB IInkOverlay_get_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_CollectionMode_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ InkCollectionMode Mode);


void __RPC_STUB IInkOverlay_put_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_DynamicRendering_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);


void __RPC_STUB IInkOverlay_get_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_DynamicRendering_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB IInkOverlay_put_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_EditingMode_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ InkOverlayEditingMode __RPC_FAR *EditingMode);


void __RPC_STUB IInkOverlay_get_EditingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_EditingMode_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ InkOverlayEditingMode EditingMode);


void __RPC_STUB IInkOverlay_put_EditingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Selection_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ IInkStrokes __RPC_FAR *__RPC_FAR *Selection);


void __RPC_STUB IInkOverlay_get_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_Selection_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ IInkStrokes __RPC_FAR *Selection);


void __RPC_STUB IInkOverlay_put_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_EraserMode_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ InkOverlayEraserMode __RPC_FAR *EraserMode);


void __RPC_STUB IInkOverlay_get_EraserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_EraserMode_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ InkOverlayEraserMode EraserMode);


void __RPC_STUB IInkOverlay_put_EraserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_SupportHighContrastInk_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Support);


void __RPC_STUB IInkOverlay_get_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_SupportHighContrastInk_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkOverlay_put_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_SupportHighContrastSelectionUI_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Support);


void __RPC_STUB IInkOverlay_get_SupportHighContrastSelectionUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_SupportHighContrastSelectionUI_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkOverlay_put_SupportHighContrastSelectionUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_Draw_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *Rect);


void __RPC_STUB IInkOverlay_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_GetWindowInputRectangle_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [out][in] */ IInkRectangle __RPC_FAR *__RPC_FAR *WindowInputRectangle);


void __RPC_STUB IInkOverlay_GetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetWindowInputRectangle_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ IInkRectangle __RPC_FAR *WindowInputRectangle);


void __RPC_STUB IInkOverlay_SetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_GetEventInterest_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Listen);


void __RPC_STUB IInkOverlay_GetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetEventInterest_Proxy( 
    IInkOverlay __RPC_FAR * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkOverlay_SetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkOverlay_INTERFACE_DEFINED__ */



#ifndef __MSINKAUTLib_LIBRARY_DEFINED__
#define __MSINKAUTLib_LIBRARY_DEFINED__

/* library MSINKAUTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSINKAUTLib;

#ifndef ___IInkEvents_DISPINTERFACE_DEFINED__
#define ___IInkEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("427B1865-CA3F-479a-83A9-0F420F2A0073")
    _IInkEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IInkEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IInkEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IInkEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IInkEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IInkEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IInkEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IInkEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IInkEventsVtbl;

    interface _IInkEvents
    {
        CONST_VTBL struct _IInkEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IInkStrokesEvents_DISPINTERFACE_DEFINED__
#define ___IInkStrokesEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkStrokesEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkStrokesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F33053EC-5D25-430a-928F-76A6491DDE15")
    _IInkStrokesEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkStrokesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IInkStrokesEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IInkStrokesEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IInkStrokesEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IInkStrokesEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IInkStrokesEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IInkStrokesEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IInkStrokesEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IInkStrokesEventsVtbl;

    interface _IInkStrokesEvents
    {
        CONST_VTBL struct _IInkStrokesEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkStrokesEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkStrokesEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkStrokesEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkStrokesEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkStrokesEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkStrokesEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkStrokesEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkStrokesEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IInkOverlayEvents_DISPINTERFACE_DEFINED__
#define ___IInkOverlayEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkOverlayEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkOverlayEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("31179b69-e563-489e-b16f-712f1e8a0651")
    _IInkOverlayEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkOverlayEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IInkOverlayEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IInkOverlayEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IInkOverlayEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IInkOverlayEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IInkOverlayEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IInkOverlayEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IInkOverlayEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IInkOverlayEventsVtbl;

    interface _IInkOverlayEvents
    {
        CONST_VTBL struct _IInkOverlayEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkOverlayEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkOverlayEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkOverlayEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkOverlayEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkOverlayEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkOverlayEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkOverlayEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkOverlayEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_InkRectangle;

#ifdef __cplusplus

class DECLSPEC_UUID("43B07326-AAE0-4B62-A83D-5FD768B7353C")
InkRectangle;
#endif

EXTERN_C const CLSID CLSID_InkProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("6B719B44-4DE1-4B4F-B016-F922A8C3F110")
InkProperty;
#endif

EXTERN_C const CLSID CLSID_InkProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("C787B7AF-C67E-45A6-8873-C82058DD4627")
InkProperties;
#endif

EXTERN_C const CLSID CLSID_InkDrawingAttributes;

#ifdef __cplusplus

class DECLSPEC_UUID("D8BF32A2-05A5-44c3-B3AA-5E80AC7D2576")
InkDrawingAttributes;
#endif

EXTERN_C const CLSID CLSID_InkTransform;

#ifdef __cplusplus

class DECLSPEC_UUID("E3D5D93C-1663-4A78-A1A7-22375DFEBAEE")
InkTransform;
#endif

EXTERN_C const CLSID CLSID_InkDisp;

#ifdef __cplusplus

class DECLSPEC_UUID("937C1A34-151D-4610-9CA6-A8CC9BDB5D83")
InkDisp;
#endif

EXTERN_C const CLSID CLSID_InkStrokes;

#ifdef __cplusplus

class DECLSPEC_UUID("48F491BC-240E-4860-B079-A1E94D3D2C86")
InkStrokes;
#endif

EXTERN_C const CLSID CLSID_InkRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("9C1CC6E4-D7EB-4eeb-9091-15A7C8791ED9")
InkRenderer;
#endif

EXTERN_C const CLSID CLSID_InkOverlay;

#ifdef __cplusplus

class DECLSPEC_UUID("65d00646-cde3-4a88-9163-6769f0f1a97d")
InkOverlay;
#endif

EXTERN_C const CLSID CLSID_InkRecognizers;

#ifdef __cplusplus

class DECLSPEC_UUID("9FD4E808-F6E6-4e65-98D3-AA39054C1255")
InkRecognizers;
#endif

EXTERN_C const CLSID CLSID_InkRecognizerContext;

#ifdef __cplusplus

class DECLSPEC_UUID("AAC46A37-9229-4fc0-8CCE-4497569BF4D1")
InkRecognizerContext;
#endif

EXTERN_C const CLSID CLSID_InkWordList;

#ifdef __cplusplus

class DECLSPEC_UUID("9DE85094-F71F-44f1-8471-15A2FA76FCF3")
InkWordList;
#endif
#endif /* __MSINKAUTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


