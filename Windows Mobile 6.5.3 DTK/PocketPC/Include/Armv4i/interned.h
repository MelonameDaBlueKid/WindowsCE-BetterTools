//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Tue Nov 10 18:45:46 2009
 */
/* Compiler settings for .\interned.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __interned_h__
#define __interned_h__

/* Forward Declarations */ 

#ifndef __ISelectionObject2_FWD_DEFINED__
#define __ISelectionObject2_FWD_DEFINED__
typedef interface ISelectionObject2 ISelectionObject2;
#endif 	/* __ISelectionObject2_FWD_DEFINED__ */


#ifndef __IHTMLEditor_FWD_DEFINED__
#define __IHTMLEditor_FWD_DEFINED__
typedef interface IHTMLEditor IHTMLEditor;
#endif 	/* __IHTMLEditor_FWD_DEFINED__ */


#ifndef __IHTMLPrivateWindow_FWD_DEFINED__
#define __IHTMLPrivateWindow_FWD_DEFINED__
typedef interface IHTMLPrivateWindow IHTMLPrivateWindow;
#endif 	/* __IHTMLPrivateWindow_FWD_DEFINED__ */


#ifndef __IHTMLPrivateWindow2_FWD_DEFINED__
#define __IHTMLPrivateWindow2_FWD_DEFINED__
typedef interface IHTMLPrivateWindow2 IHTMLPrivateWindow2;
#endif 	/* __IHTMLPrivateWindow2_FWD_DEFINED__ */


#ifndef __IHTMLPrivateWindow3_FWD_DEFINED__
#define __IHTMLPrivateWindow3_FWD_DEFINED__
typedef interface IHTMLPrivateWindow3 IHTMLPrivateWindow3;
#endif 	/* __IHTMLPrivateWindow3_FWD_DEFINED__ */


#ifndef __ISubDivisionProvider_FWD_DEFINED__
#define __ISubDivisionProvider_FWD_DEFINED__
typedef interface ISubDivisionProvider ISubDivisionProvider;
#endif 	/* __ISubDivisionProvider_FWD_DEFINED__ */


#ifndef __IElementBehaviorUI_FWD_DEFINED__
#define __IElementBehaviorUI_FWD_DEFINED__
typedef interface IElementBehaviorUI IElementBehaviorUI;
#endif 	/* __IElementBehaviorUI_FWD_DEFINED__ */


#ifndef __IElementAdorner_FWD_DEFINED__
#define __IElementAdorner_FWD_DEFINED__
typedef interface IElementAdorner IElementAdorner;
#endif 	/* __IElementAdorner_FWD_DEFINED__ */


#ifndef __IHTMLEditingServices_FWD_DEFINED__
#define __IHTMLEditingServices_FWD_DEFINED__
typedef interface IHTMLEditingServices IHTMLEditingServices;
#endif 	/* __IHTMLEditingServices_FWD_DEFINED__ */


#ifndef __IEditDebugServices_FWD_DEFINED__
#define __IEditDebugServices_FWD_DEFINED__
typedef interface IEditDebugServices IEditDebugServices;
#endif 	/* __IEditDebugServices_FWD_DEFINED__ */


#ifndef __IPrivacyServices_FWD_DEFINED__
#define __IPrivacyServices_FWD_DEFINED__
typedef interface IPrivacyServices IPrivacyServices;
#endif 	/* __IPrivacyServices_FWD_DEFINED__ */


#ifndef __IHTMLCEClientServices_FWD_DEFINED__
#define __IHTMLCEClientServices_FWD_DEFINED__
typedef interface IHTMLCEClientServices IHTMLCEClientServices;
#endif 	/* __IHTMLCEClientServices_FWD_DEFINED__ */


#ifndef __IHTMLCEPopupEvents_FWD_DEFINED__
#define __IHTMLCEPopupEvents_FWD_DEFINED__
typedef interface IHTMLCEPopupEvents IHTMLCEPopupEvents;
#endif 	/* __IHTMLCEPopupEvents_FWD_DEFINED__ */


#ifndef __IHTMLFilterPainter_FWD_DEFINED__
#define __IHTMLFilterPainter_FWD_DEFINED__
typedef interface IHTMLFilterPainter IHTMLFilterPainter;
#endif 	/* __IHTMLFilterPainter_FWD_DEFINED__ */


#ifndef __IHTMLFilterPaintSite_FWD_DEFINED__
#define __IHTMLFilterPaintSite_FWD_DEFINED__
typedef interface IHTMLFilterPaintSite IHTMLFilterPaintSite;
#endif 	/* __IHTMLFilterPaintSite_FWD_DEFINED__ */


#ifndef __IElementNamespacePrivate_FWD_DEFINED__
#define __IElementNamespacePrivate_FWD_DEFINED__
typedef interface IElementNamespacePrivate IElementNamespacePrivate;
#endif 	/* __IElementNamespacePrivate_FWD_DEFINED__ */


#ifndef __ICursorInfo_FWD_DEFINED__
#define __ICursorInfo_FWD_DEFINED__
typedef interface ICursorInfo ICursorInfo;
#endif 	/* __ICursorInfo_FWD_DEFINED__ */


#ifndef __IHttpHeaderInfo_FWD_DEFINED__
#define __IHttpHeaderInfo_FWD_DEFINED__
typedef interface IHttpHeaderInfo IHttpHeaderInfo;
#endif 	/* __IHttpHeaderInfo_FWD_DEFINED__ */


#ifndef __IHTMLDocumentRender_FWD_DEFINED__
#define __IHTMLDocumentRender_FWD_DEFINED__
typedef interface IHTMLDocumentRender IHTMLDocumentRender;
#endif 	/* __IHTMLDocumentRender_FWD_DEFINED__ */


#ifndef __IMobileDocumentServices_FWD_DEFINED__
#define __IMobileDocumentServices_FWD_DEFINED__
typedef interface IMobileDocumentServices IMobileDocumentServices;
#endif 	/* __IMobileDocumentServices_FWD_DEFINED__ */


#ifndef __IBrowserConnectionServices_FWD_DEFINED__
#define __IBrowserConnectionServices_FWD_DEFINED__
typedef interface IBrowserConnectionServices IBrowserConnectionServices;
#endif 	/* __IBrowserConnectionServices_FWD_DEFINED__ */


#ifndef __IMobileHTMLDocument_FWD_DEFINED__
#define __IMobileHTMLDocument_FWD_DEFINED__
typedef interface IMobileHTMLDocument IMobileHTMLDocument;
#endif 	/* __IMobileHTMLDocument_FWD_DEFINED__ */


#ifndef __IProgressStatusUpdate_FWD_DEFINED__
#define __IProgressStatusUpdate_FWD_DEFINED__
typedef interface IProgressStatusUpdate IProgressStatusUpdate;
#endif 	/* __IProgressStatusUpdate_FWD_DEFINED__ */


/* header files for imported files */
#include "dimm.h"
#include "mshtml.h"
#include "mshtmhst.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_interned_0000 */
/* [local] */ 

//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
//=--------------------------------------------------------------------------=
// internal.h
//=--------------------------------------------------------------------------=
// (C) Copyright 1998 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#pragma comment(lib,"uuid.lib")

//---------------------------------------------------------------------------=
// TRIDENT Editing Services Interfaces.
//

#ifndef INTERNAL_H_
#define INTERNAL_H_



extern RPC_IF_HANDLE __MIDL_itf_interned_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_interned_0000_v0_0_s_ifspec;


#ifndef __MSHTMLINTERNAL_LIBRARY_DEFINED__
#define __MSHTMLINTERNAL_LIBRARY_DEFINED__

/* library MSHTMLINTERNAL */
/* [uuid][version][helpstring][lcid] */ 

typedef 
enum _EDITOR_NOTIFICATION
    {	EDITOR_NOTIFY_TIMER_TICK	= 0,
	EDITOR_NOTIFY_DOC_ENDED	= 1,
	EDITOR_NOTIFY_DOC_CHANGED	= 2,
	EDITOR_NOTIFY_CARET_IN_CONTEXT	= 3,
	EDITOR_NOTIFY_EXIT_TREE	= 4,
	EDITOR_NOTIFY_LOSE_FOCUS_FRAME	= 5,
	EDITOR_NOTIFY_LOSE_FOCUS	= 6,
	EDITOR_NOTIFY_BEFORE_FOCUS	= 7,
	EDITOR_NOTIFY_YIELD_FOCUS	= 8,
	EDITOR_NOTIFY_EDITABLE_CHANGE	= 9,
	EDITOR_NOTIFY_BEGIN_SELECTION_UNDO	= 10,
	EDITOR_NOTIFY_ATTACH_WIN	= 11,
	EDITOR_NOTIFY_UPDATE_CARET	= 12,
	EDITOR_NOTIFY_BEFORE_CURRENCY_CHANGE	= 13,
	EDITOR_NOTIFY_SETTING_VIEW_LINK	= 14,
	EDITOR_NOTIFY_CONTAINER_ENDED	= 15,
	EDITOR_NOTIFICATION_Max	= 2147483647L
    }	EDITOR_NOTIFICATION;

typedef 
enum _DOCNAVFLAGS
    {	DOCNAVFLAG_DOCNAVIGATE	= 1,
	DOCNAVFLAG_DONTUPDATETLOG	= 2,
	DOCNAVFLAG_HTTPERRORPAGE	= 4,
	DOCNAVFLAG_OPENINNEWWINDOW	= 8,
	DOCNAVFLAG_REFRESH	= 16,
	DOCNAVFLAG_TRUSTEDFORACTIVEX	= 32,
	DOCNAVFLAG_UNTRUSTEDFORDOWNLOAD	= 64,
	DOCNAVFLAG_CALLERUNTRUSTED	= 128,
	DOCNAVFLAG_FULLSCREEN_DOCUMENT	= 256,
	DOCNAVFLAGS_Max	= 2147483647L
    }	DOCNAVFLAGS;

typedef 
enum _NAVIGATEEXOPTIONS
    {	NAVIGATEEX_NONE	= 0,
	NAVIGATEEX_DONTUPDATETRAVELLOG	= 1,
	NAVIGATEEXOPTIONS_Max	= 2147483647L
    }	NAVIGATEEXOPTIONS;

typedef 
enum _CHAR_FORMAT_FAMILY
    {	CHAR_FORMAT_None	= 0,
	CHAR_FORMAT_FontStyle	= 1,
	CHAR_FORMAT_FontInfo	= 2,
	CHAR_FORMAT_FontName	= 4,
	CHAR_FORMAT_ColorInfo	= 8,
	CHAR_FORMAT_ParaFormat	= 16,
	CHAR_FORMAT_FAMILY_Max	= 2147483647L
    }	CHAR_FORMAT_FAMILY;

typedef 
enum _LAYOUT_MOVE_UNIT
    {	LAYOUT_MOVE_UNIT_PreviousLine	= 1,
	LAYOUT_MOVE_UNIT_NextLine	= 2,
	LAYOUT_MOVE_UNIT_CurrentLineStart	= 3,
	LAYOUT_MOVE_UNIT_CurrentLineEnd	= 4,
	LAYOUT_MOVE_UNIT_NextLineStart	= 5,
	LAYOUT_MOVE_UNIT_PreviousLineEnd	= 6,
	LAYOUT_MOVE_UNIT_TopOfWindow	= 7,
	LAYOUT_MOVE_UNIT_BottomOfWindow	= 8,
	LAYOUT_MOVE_UNIT_OuterLineStart	= 9,
	LAYOUT_MOVE_UNIT_OuterLineEnd	= 10,
	LAYOUT_MOVE_UNIT_Max	= 2147483647L
    }	LAYOUT_MOVE_UNIT;

typedef 
enum _CARET_GRAVITY
    {	CARET_GRAVITY_NoChange	= 0,
	CARET_GRAVITY_BeginningOfLine	= 1,
	CARET_GRAVITY_EndOfLine	= 2,
	CARET_GRAVITY_Max	= 2147483647L
    }	CARET_GRAVITY;

typedef 
enum _CARET_VISIBILITY
    {	CARET_TYPE_Hide	= 0,
	CARET_TYPE_Show	= 1,
	CARET_VISIBILITY_Max	= 2147483647L
    }	CARET_VISIBILITY;

typedef 
enum _POINTER_SCROLLPIN
    {	POINTER_SCROLLPIN_TopLeft	= 0,
	POINTER_SCROLLPIN_BottomRight	= 1,
	POINTER_SCROLLPIN_Minimal	= 2,
	POINTER_SCROLLPIN_Max	= 2147483647L
    }	POINTER_SCROLLPIN;

typedef 
enum _ADORNER_HTI
    {	ADORNER_HTI_NONE	= 0,
	ADORNER_HTI_TOPBORDER	= 1,
	ADORNER_HTI_LEFTBORDER	= 2,
	ADORNER_HTI_BOTTOMBORDER	= 3,
	ADORNER_HTI_RIGHTBORDER	= 4,
	ADORNER_HTI_TOPLEFTHANDLE	= 5,
	ADORNER_HTI_LEFTHANDLE	= 6,
	ADORNER_HTI_TOPHANDLE	= 7,
	ADORNER_HTI_BOTTOMLEFTHANDLE	= 8,
	ADORNER_HTI_TOPRIGHTHANDLE	= 9,
	ADORNER_HTI_BOTTOMHANDLE	= 10,
	ADORNER_HTI_RIGHTHANDLE	= 11,
	ADORNER_HTI_BOTTOMRIGHTHANDLE	= 12,
	ADORNER_HTI_Max	= 2147483647L
    }	ADORNER_HTI;

typedef 
enum _FILTER_DRAW_LAYERS
    {	FILTER_DRAW_BORDER	= 0x1,
	FILTER_DRAW_BACKGROUND	= 0x2,
	FILTER_DRAW_CONTENT	= 0x4,
	FILTER_DRAW_ALLLAYERS	= 0x7,
	FILTER_DRAW_LAYERS_Max	= 2147483647L
    }	FILTER_DRAW_LAYERS;

typedef 
enum _FILTER_FLAGS
    {	FILTER_FLAGS_PAGETRANSITION	= 0x1,
	FILTER_FLAGS_Max	= 2147483647L
    }	FILTER_FLAGS;

typedef 
enum _SUSPEND_FLAGS
    {	SUSPEND_FLAG_ANIMATIONS	= 0x1,
	SUSPEND_FLAG_EMBEDS	= 0x2,
	SUSPEND_FLAG_TIMERS	= 0x4,
	SUSPEND_FLAG_SCRIPT	= 0x8,
	SUSPEND_FLAG_MOUSE	= 0x10,
	SUSPEND_FLAGS_Max	= 2147483647L
    }	SUSPEND_FLAGS;

typedef 
enum _FREEZE_FLAGS
    {	FREEZE_FLAG_OLESITES	= 0x1,
	FREEZE_FLAG_EVENTS	= 0x2,
	FREEZE_FLAG_ANIMATIONS	= 0x4,
	FREEZE_FLAG_LAYOUT	= 0x8,
	FREEZE_FLAG_TIMERS	= 0x10,
	FREEZE_FLAG_DEFERREDMETHODS	= 0x20,
	FREEZE_FLAG_PARSER	= 0x40,
	FREEZE_FLAG_SCRIPTS	= 0x80,
	FREEZE_FLAG_SCROLLING	= 0x100,
	FREEZE_FLAG_ALL	= 0xffffffff
    }	FREEZE_FLAGS;

typedef struct _HTMLPtrDispInfoRec
    {
    DWORD dwSize;
    LONG lBaseline;
    LONG lXPosition;
    LONG lLineHeight;
    LONG lTextHeight;
    LONG lDescent;
    LONG lTextDescent;
    BOOL fRTLLine;
    BOOL fRTLFlow;
    BOOL fAligned;
    BOOL fHasNestedRunOwner;
    }	HTMLPtrDispInfoRec;

typedef 
enum _ZOOM_FLAGS
    {	ZOOM_PAGE_OVERVIEW	= 0x1,
	ZOOM_PAGE_READ	= 0x2,
	ZOOM_POINT_VALID	= 0x4,
	ZOOM_DBLCLK	= 0x8,
	ZOOM_NO_SCROLL	= 0x10,
	ZOOM_NO_ALIGN	= 0x20
    }	ZOOM_FLAGS;

typedef 
enum _ZOOM_DEFAULTS
    {	ZOOM_DEFAULT_PAGE_OVERVIEW	= 0x1
    }	ZOOM_DEFAULTS;

typedef 
enum _LINKHIGHLIGHT_MODE
    {	LINKHIGHLIGHT_MODE_NORMAL	= 0x1,
	LINKHIGHLIGHT_MODE_BORDERONLY	= 0x2,
	LINKHIGHLIGHT_MODE_BORDERANDFILL	= 0x3
    }	LINKHIGHLIGHT_MODE;




EXTERN_C const IID LIBID_MSHTMLINTERNAL;

#ifndef __ISelectionObject2_INTERFACE_DEFINED__
#define __ISelectionObject2_INTERFACE_DEFINED__

/* interface ISelectionObject2 */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_ISelectionObject2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f7fc-98b5-11cf-bb82-00aa00bdce0b")
    ISelectionObject2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Select( 
            /* [in] */ ISegmentList __RPC_FAR *pISegmentList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsPointerInSelection( 
            /* [in] */ IDisplayPointer __RPC_FAR *pIDispPointer,
            /* [out] */ BOOL __RPC_FAR *pfPointerInSelection,
            /* [in] */ POINT __RPC_FAR *pptGlobal,
            /* [in] */ IHTMLElement __RPC_FAR *pIElementOver) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EmptySelection( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DestroySelection( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DestroyAllSelection( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISelectionObject2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISelectionObject2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISelectionObject2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISelectionObject2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Select )( 
            ISelectionObject2 __RPC_FAR * This,
            /* [in] */ ISegmentList __RPC_FAR *pISegmentList);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPointerInSelection )( 
            ISelectionObject2 __RPC_FAR * This,
            /* [in] */ IDisplayPointer __RPC_FAR *pIDispPointer,
            /* [out] */ BOOL __RPC_FAR *pfPointerInSelection,
            /* [in] */ POINT __RPC_FAR *pptGlobal,
            /* [in] */ IHTMLElement __RPC_FAR *pIElementOver);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EmptySelection )( 
            ISelectionObject2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DestroySelection )( 
            ISelectionObject2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DestroyAllSelection )( 
            ISelectionObject2 __RPC_FAR * This);
        
        END_INTERFACE
    } ISelectionObject2Vtbl;

    interface ISelectionObject2
    {
        CONST_VTBL struct ISelectionObject2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISelectionObject2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISelectionObject2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISelectionObject2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISelectionObject2_Select(This,pISegmentList)	\
    (This)->lpVtbl -> Select(This,pISegmentList)

#define ISelectionObject2_IsPointerInSelection(This,pIDispPointer,pfPointerInSelection,pptGlobal,pIElementOver)	\
    (This)->lpVtbl -> IsPointerInSelection(This,pIDispPointer,pfPointerInSelection,pptGlobal,pIElementOver)

#define ISelectionObject2_EmptySelection(This)	\
    (This)->lpVtbl -> EmptySelection(This)

#define ISelectionObject2_DestroySelection(This)	\
    (This)->lpVtbl -> DestroySelection(This)

#define ISelectionObject2_DestroyAllSelection(This)	\
    (This)->lpVtbl -> DestroyAllSelection(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISelectionObject2_Select_Proxy( 
    ISelectionObject2 __RPC_FAR * This,
    /* [in] */ ISegmentList __RPC_FAR *pISegmentList);


void __RPC_STUB ISelectionObject2_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISelectionObject2_IsPointerInSelection_Proxy( 
    ISelectionObject2 __RPC_FAR * This,
    /* [in] */ IDisplayPointer __RPC_FAR *pIDispPointer,
    /* [out] */ BOOL __RPC_FAR *pfPointerInSelection,
    /* [in] */ POINT __RPC_FAR *pptGlobal,
    /* [in] */ IHTMLElement __RPC_FAR *pIElementOver);


void __RPC_STUB ISelectionObject2_IsPointerInSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISelectionObject2_EmptySelection_Proxy( 
    ISelectionObject2 __RPC_FAR * This);


void __RPC_STUB ISelectionObject2_EmptySelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISelectionObject2_DestroySelection_Proxy( 
    ISelectionObject2 __RPC_FAR * This);


void __RPC_STUB ISelectionObject2_DestroySelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISelectionObject2_DestroyAllSelection_Proxy( 
    ISelectionObject2 __RPC_FAR * This);


void __RPC_STUB ISelectionObject2_DestroyAllSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISelectionObject2_INTERFACE_DEFINED__ */


#ifndef __IHTMLEditor_INTERFACE_DEFINED__
#define __IHTMLEditor_INTERFACE_DEFINED__

/* interface IHTMLEditor */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLEditor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f7fa-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLEditor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PreHandleEvent( 
            /* [in] */ DISPID inEvtDispId,
            /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostHandleEvent( 
            /* [in] */ DISPID inEvtDispId,
            /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ DISPID inEvtDispId,
            /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IUnknown __RPC_FAR *pIDocument,
            /* [in] */ IUnknown __RPC_FAR *pIContainer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ EDITOR_NOTIFICATION eSelectionNotification,
            /* [in] */ IUnknown __RPC_FAR *pUnknown,
            /* [in] */ DWORD dword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCommandTarget( 
            /* [in] */ IUnknown __RPC_FAR *pContext,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetElementToTabFrom( 
            /* [in] */ BOOL fForward,
            /* [out][in] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElement,
            /* [out][in] */ BOOL __RPC_FAR *pfFindNext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsEditContextUIActive( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TerminateIMEComposition( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLEditorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLEditor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLEditor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PreHandleEvent )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ DISPID inEvtDispId,
            /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostHandleEvent )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ DISPID inEvtDispId,
            /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TranslateAccelerator )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ DISPID inEvtDispId,
            /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pIDocument,
            /* [in] */ IUnknown __RPC_FAR *pIContainer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Notify )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ EDITOR_NOTIFICATION eSelectionNotification,
            /* [in] */ IUnknown __RPC_FAR *pUnknown,
            /* [in] */ DWORD dword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommandTarget )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pContext,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTarget);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetElementToTabFrom )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ BOOL fForward,
            /* [out][in] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElement,
            /* [out][in] */ BOOL __RPC_FAR *pfFindNext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsEditContextUIActive )( 
            IHTMLEditor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TerminateIMEComposition )( 
            IHTMLEditor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableModeless )( 
            IHTMLEditor __RPC_FAR * This,
            /* [in] */ BOOL fEnable);
        
        END_INTERFACE
    } IHTMLEditorVtbl;

    interface IHTMLEditor
    {
        CONST_VTBL struct IHTMLEditorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLEditor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLEditor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLEditor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLEditor_PreHandleEvent(This,inEvtDispId,pIEventObj)	\
    (This)->lpVtbl -> PreHandleEvent(This,inEvtDispId,pIEventObj)

#define IHTMLEditor_PostHandleEvent(This,inEvtDispId,pIEventObj)	\
    (This)->lpVtbl -> PostHandleEvent(This,inEvtDispId,pIEventObj)

#define IHTMLEditor_TranslateAccelerator(This,inEvtDispId,pIEventObj)	\
    (This)->lpVtbl -> TranslateAccelerator(This,inEvtDispId,pIEventObj)

#define IHTMLEditor_Initialize(This,pIDocument,pIContainer)	\
    (This)->lpVtbl -> Initialize(This,pIDocument,pIContainer)

#define IHTMLEditor_Notify(This,eSelectionNotification,pUnknown,dword)	\
    (This)->lpVtbl -> Notify(This,eSelectionNotification,pUnknown,dword)

#define IHTMLEditor_GetCommandTarget(This,pContext,ppUnkTarget)	\
    (This)->lpVtbl -> GetCommandTarget(This,pContext,ppUnkTarget)

#define IHTMLEditor_GetElementToTabFrom(This,fForward,ppElement,pfFindNext)	\
    (This)->lpVtbl -> GetElementToTabFrom(This,fForward,ppElement,pfFindNext)

#define IHTMLEditor_IsEditContextUIActive(This)	\
    (This)->lpVtbl -> IsEditContextUIActive(This)

#define IHTMLEditor_TerminateIMEComposition(This)	\
    (This)->lpVtbl -> TerminateIMEComposition(This)

#define IHTMLEditor_EnableModeless(This,fEnable)	\
    (This)->lpVtbl -> EnableModeless(This,fEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLEditor_PreHandleEvent_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ DISPID inEvtDispId,
    /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj);


void __RPC_STUB IHTMLEditor_PreHandleEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_PostHandleEvent_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ DISPID inEvtDispId,
    /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj);


void __RPC_STUB IHTMLEditor_PostHandleEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_TranslateAccelerator_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ DISPID inEvtDispId,
    /* [in] */ IHTMLEventObj __RPC_FAR *pIEventObj);


void __RPC_STUB IHTMLEditor_TranslateAccelerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_Initialize_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pIDocument,
    /* [in] */ IUnknown __RPC_FAR *pIContainer);


void __RPC_STUB IHTMLEditor_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_Notify_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ EDITOR_NOTIFICATION eSelectionNotification,
    /* [in] */ IUnknown __RPC_FAR *pUnknown,
    /* [in] */ DWORD dword);


void __RPC_STUB IHTMLEditor_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_GetCommandTarget_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pContext,
    /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTarget);


void __RPC_STUB IHTMLEditor_GetCommandTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_GetElementToTabFrom_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ BOOL fForward,
    /* [out][in] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElement,
    /* [out][in] */ BOOL __RPC_FAR *pfFindNext);


void __RPC_STUB IHTMLEditor_GetElementToTabFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_IsEditContextUIActive_Proxy( 
    IHTMLEditor __RPC_FAR * This);


void __RPC_STUB IHTMLEditor_IsEditContextUIActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_TerminateIMEComposition_Proxy( 
    IHTMLEditor __RPC_FAR * This);


void __RPC_STUB IHTMLEditor_TerminateIMEComposition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditor_EnableModeless_Proxy( 
    IHTMLEditor __RPC_FAR * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IHTMLEditor_EnableModeless_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLEditor_INTERFACE_DEFINED__ */


#ifndef __IHTMLPrivateWindow_INTERFACE_DEFINED__
#define __IHTMLPrivateWindow_INTERFACE_DEFINED__

/* interface IHTMLPrivateWindow */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLPrivateWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f6dc-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLPrivateWindow : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SuperNavigate( 
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrShortcut,
            /* [in] */ BSTR bstrFrameName,
            /* [in] */ VARIANT __RPC_FAR *pvarPostData,
            /* [in] */ VARIANT __RPC_FAR *pvarHeaders,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPendingUrl( 
            /* [out] */ LPOLESTR __RPC_FAR *pstrURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPICSTarget( 
            /* [in] */ IOleCommandTarget __RPC_FAR *pctPICS) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PICSComplete( 
            /* [in] */ BOOL fApproved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindWindowByName( 
            /* [in] */ LPCOLESTR pstrTargeName,
            /* [out] */ IHTMLWindow2 __RPC_FAR *__RPC_FAR *ppWindow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAddressBarUrl( 
            /* [out] */ BSTR __RPC_FAR *pbstrURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLPrivateWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLPrivateWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLPrivateWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SuperNavigate )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrShortcut,
            /* [in] */ BSTR bstrFrameName,
            /* [in] */ VARIANT __RPC_FAR *pvarPostData,
            /* [in] */ VARIANT __RPC_FAR *pvarHeaders,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPendingUrl )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *pstrURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPICSTarget )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [in] */ IOleCommandTarget __RPC_FAR *pctPICS);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PICSComplete )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [in] */ BOOL fApproved);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindWindowByName )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [in] */ LPCOLESTR pstrTargeName,
            /* [out] */ IHTMLWindow2 __RPC_FAR *__RPC_FAR *ppWindow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAddressBarUrl )( 
            IHTMLPrivateWindow __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrURL);
        
        END_INTERFACE
    } IHTMLPrivateWindowVtbl;

    interface IHTMLPrivateWindow
    {
        CONST_VTBL struct IHTMLPrivateWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLPrivateWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLPrivateWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLPrivateWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLPrivateWindow_SuperNavigate(This,bstrURL,bstrLocation,bstrShortcut,bstrFrameName,pvarPostData,pvarHeaders,dwFlags)	\
    (This)->lpVtbl -> SuperNavigate(This,bstrURL,bstrLocation,bstrShortcut,bstrFrameName,pvarPostData,pvarHeaders,dwFlags)

#define IHTMLPrivateWindow_GetPendingUrl(This,pstrURL)	\
    (This)->lpVtbl -> GetPendingUrl(This,pstrURL)

#define IHTMLPrivateWindow_SetPICSTarget(This,pctPICS)	\
    (This)->lpVtbl -> SetPICSTarget(This,pctPICS)

#define IHTMLPrivateWindow_PICSComplete(This,fApproved)	\
    (This)->lpVtbl -> PICSComplete(This,fApproved)

#define IHTMLPrivateWindow_FindWindowByName(This,pstrTargeName,ppWindow)	\
    (This)->lpVtbl -> FindWindowByName(This,pstrTargeName,ppWindow)

#define IHTMLPrivateWindow_GetAddressBarUrl(This,pbstrURL)	\
    (This)->lpVtbl -> GetAddressBarUrl(This,pbstrURL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow_SuperNavigate_Proxy( 
    IHTMLPrivateWindow __RPC_FAR * This,
    /* [in] */ BSTR bstrURL,
    /* [in] */ BSTR bstrLocation,
    /* [in] */ BSTR bstrShortcut,
    /* [in] */ BSTR bstrFrameName,
    /* [in] */ VARIANT __RPC_FAR *pvarPostData,
    /* [in] */ VARIANT __RPC_FAR *pvarHeaders,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IHTMLPrivateWindow_SuperNavigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow_GetPendingUrl_Proxy( 
    IHTMLPrivateWindow __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *pstrURL);


void __RPC_STUB IHTMLPrivateWindow_GetPendingUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow_SetPICSTarget_Proxy( 
    IHTMLPrivateWindow __RPC_FAR * This,
    /* [in] */ IOleCommandTarget __RPC_FAR *pctPICS);


void __RPC_STUB IHTMLPrivateWindow_SetPICSTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow_PICSComplete_Proxy( 
    IHTMLPrivateWindow __RPC_FAR * This,
    /* [in] */ BOOL fApproved);


void __RPC_STUB IHTMLPrivateWindow_PICSComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow_FindWindowByName_Proxy( 
    IHTMLPrivateWindow __RPC_FAR * This,
    /* [in] */ LPCOLESTR pstrTargeName,
    /* [out] */ IHTMLWindow2 __RPC_FAR *__RPC_FAR *ppWindow);


void __RPC_STUB IHTMLPrivateWindow_FindWindowByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow_GetAddressBarUrl_Proxy( 
    IHTMLPrivateWindow __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrURL);


void __RPC_STUB IHTMLPrivateWindow_GetAddressBarUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLPrivateWindow_INTERFACE_DEFINED__ */


#ifndef __IHTMLPrivateWindow2_INTERFACE_DEFINED__
#define __IHTMLPrivateWindow2_INTERFACE_DEFINED__

/* interface IHTMLPrivateWindow2 */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLPrivateWindow2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f7e5-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLPrivateWindow2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NavigateEx( 
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrUnencodedUrl,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrContext,
            /* [in] */ IBindCtx __RPC_FAR *pBindCtx,
            /* [in] */ DWORD dwNavOptions,
            /* [in] */ DWORD dwFHLFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInnerWindowUnknown( 
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnknown) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLPrivateWindow2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLPrivateWindow2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLPrivateWindow2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLPrivateWindow2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigateEx )( 
            IHTMLPrivateWindow2 __RPC_FAR * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrUnencodedUrl,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrContext,
            /* [in] */ IBindCtx __RPC_FAR *pBindCtx,
            /* [in] */ DWORD dwNavOptions,
            /* [in] */ DWORD dwFHLFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInnerWindowUnknown )( 
            IHTMLPrivateWindow2 __RPC_FAR * This,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnknown);
        
        END_INTERFACE
    } IHTMLPrivateWindow2Vtbl;

    interface IHTMLPrivateWindow2
    {
        CONST_VTBL struct IHTMLPrivateWindow2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLPrivateWindow2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLPrivateWindow2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLPrivateWindow2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLPrivateWindow2_NavigateEx(This,bstrURL,bstrUnencodedUrl,bstrLocation,bstrContext,pBindCtx,dwNavOptions,dwFHLFlags)	\
    (This)->lpVtbl -> NavigateEx(This,bstrURL,bstrUnencodedUrl,bstrLocation,bstrContext,pBindCtx,dwNavOptions,dwFHLFlags)

#define IHTMLPrivateWindow2_GetInnerWindowUnknown(This,ppUnknown)	\
    (This)->lpVtbl -> GetInnerWindowUnknown(This,ppUnknown)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow2_NavigateEx_Proxy( 
    IHTMLPrivateWindow2 __RPC_FAR * This,
    /* [in] */ BSTR bstrURL,
    /* [in] */ BSTR bstrUnencodedUrl,
    /* [in] */ BSTR bstrLocation,
    /* [in] */ BSTR bstrContext,
    /* [in] */ IBindCtx __RPC_FAR *pBindCtx,
    /* [in] */ DWORD dwNavOptions,
    /* [in] */ DWORD dwFHLFlags);


void __RPC_STUB IHTMLPrivateWindow2_NavigateEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow2_GetInnerWindowUnknown_Proxy( 
    IHTMLPrivateWindow2 __RPC_FAR * This,
    /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnknown);


void __RPC_STUB IHTMLPrivateWindow2_GetInnerWindowUnknown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLPrivateWindow2_INTERFACE_DEFINED__ */


#ifndef __IHTMLPrivateWindow3_INTERFACE_DEFINED__
#define __IHTMLPrivateWindow3_INTERFACE_DEFINED__

/* interface IHTMLPrivateWindow3 */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLPrivateWindow3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f840-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLPrivateWindow3 : public IHTMLPrivateWindow2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OpenEx( 
            /* [in] */ BSTR url,
            /* [in] */ BSTR urlContext,
            /* [in] */ BSTR name,
            /* [in] */ BSTR features,
            /* [in] */ VARIANT_BOOL replace,
            /* [out] */ IHTMLWindow2 __RPC_FAR *__RPC_FAR *pomWindowResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLPrivateWindow3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLPrivateWindow3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLPrivateWindow3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLPrivateWindow3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigateEx )( 
            IHTMLPrivateWindow3 __RPC_FAR * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrUnencodedUrl,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrContext,
            /* [in] */ IBindCtx __RPC_FAR *pBindCtx,
            /* [in] */ DWORD dwNavOptions,
            /* [in] */ DWORD dwFHLFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInnerWindowUnknown )( 
            IHTMLPrivateWindow3 __RPC_FAR * This,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnknown);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenEx )( 
            IHTMLPrivateWindow3 __RPC_FAR * This,
            /* [in] */ BSTR url,
            /* [in] */ BSTR urlContext,
            /* [in] */ BSTR name,
            /* [in] */ BSTR features,
            /* [in] */ VARIANT_BOOL replace,
            /* [out] */ IHTMLWindow2 __RPC_FAR *__RPC_FAR *pomWindowResult);
        
        END_INTERFACE
    } IHTMLPrivateWindow3Vtbl;

    interface IHTMLPrivateWindow3
    {
        CONST_VTBL struct IHTMLPrivateWindow3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLPrivateWindow3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLPrivateWindow3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLPrivateWindow3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLPrivateWindow3_NavigateEx(This,bstrURL,bstrUnencodedUrl,bstrLocation,bstrContext,pBindCtx,dwNavOptions,dwFHLFlags)	\
    (This)->lpVtbl -> NavigateEx(This,bstrURL,bstrUnencodedUrl,bstrLocation,bstrContext,pBindCtx,dwNavOptions,dwFHLFlags)

#define IHTMLPrivateWindow3_GetInnerWindowUnknown(This,ppUnknown)	\
    (This)->lpVtbl -> GetInnerWindowUnknown(This,ppUnknown)


#define IHTMLPrivateWindow3_OpenEx(This,url,urlContext,name,features,replace,pomWindowResult)	\
    (This)->lpVtbl -> OpenEx(This,url,urlContext,name,features,replace,pomWindowResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLPrivateWindow3_OpenEx_Proxy( 
    IHTMLPrivateWindow3 __RPC_FAR * This,
    /* [in] */ BSTR url,
    /* [in] */ BSTR urlContext,
    /* [in] */ BSTR name,
    /* [in] */ BSTR features,
    /* [in] */ VARIANT_BOOL replace,
    /* [out] */ IHTMLWindow2 __RPC_FAR *__RPC_FAR *pomWindowResult);


void __RPC_STUB IHTMLPrivateWindow3_OpenEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLPrivateWindow3_INTERFACE_DEFINED__ */


#ifndef __ISubDivisionProvider_INTERFACE_DEFINED__
#define __ISubDivisionProvider_INTERFACE_DEFINED__

/* interface ISubDivisionProvider */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_ISubDivisionProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4d2-98b5-11cf-bb82-00aa00bdce0b")
    ISubDivisionProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSubDivisionCount( 
            /* [out][retval] */ LONG __RPC_FAR *pcSubDivision) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSubDivisionTabs( 
            /* [in] */ LONG cTabs,
            /* [out][retval] */ LONG __RPC_FAR *pSubDivisionTabs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubDivisionFromPt( 
            /* [in] */ POINT pt,
            /* [out][retval] */ LONG __RPC_FAR *piSubDivision) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISubDivisionProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISubDivisionProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISubDivisionProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubDivisionCount )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [out][retval] */ LONG __RPC_FAR *pcSubDivision);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubDivisionTabs )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [in] */ LONG cTabs,
            /* [out][retval] */ LONG __RPC_FAR *pSubDivisionTabs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubDivisionFromPt )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [in] */ POINT pt,
            /* [out][retval] */ LONG __RPC_FAR *piSubDivision);
        
        END_INTERFACE
    } ISubDivisionProviderVtbl;

    interface ISubDivisionProvider
    {
        CONST_VTBL struct ISubDivisionProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISubDivisionProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISubDivisionProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISubDivisionProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISubDivisionProvider_GetSubDivisionCount(This,pcSubDivision)	\
    (This)->lpVtbl -> GetSubDivisionCount(This,pcSubDivision)

#define ISubDivisionProvider_GetSubDivisionTabs(This,cTabs,pSubDivisionTabs)	\
    (This)->lpVtbl -> GetSubDivisionTabs(This,cTabs,pSubDivisionTabs)

#define ISubDivisionProvider_SubDivisionFromPt(This,pt,piSubDivision)	\
    (This)->lpVtbl -> SubDivisionFromPt(This,pt,piSubDivision)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISubDivisionProvider_GetSubDivisionCount_Proxy( 
    ISubDivisionProvider __RPC_FAR * This,
    /* [out][retval] */ LONG __RPC_FAR *pcSubDivision);


void __RPC_STUB ISubDivisionProvider_GetSubDivisionCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubDivisionProvider_GetSubDivisionTabs_Proxy( 
    ISubDivisionProvider __RPC_FAR * This,
    /* [in] */ LONG cTabs,
    /* [out][retval] */ LONG __RPC_FAR *pSubDivisionTabs);


void __RPC_STUB ISubDivisionProvider_GetSubDivisionTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubDivisionProvider_SubDivisionFromPt_Proxy( 
    ISubDivisionProvider __RPC_FAR * This,
    /* [in] */ POINT pt,
    /* [out][retval] */ LONG __RPC_FAR *piSubDivision);


void __RPC_STUB ISubDivisionProvider_SubDivisionFromPt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISubDivisionProvider_INTERFACE_DEFINED__ */


#ifndef __IElementBehaviorUI_INTERFACE_DEFINED__
#define __IElementBehaviorUI_INTERFACE_DEFINED__

/* interface IElementBehaviorUI */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IElementBehaviorUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4bf-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorUI : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnReceiveFocus( 
            /* [in] */ BOOL fFocus,
            /* [in] */ LONG lSubDivision) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSubDivisionProvider( 
            /* [out][retval] */ ISubDivisionProvider __RPC_FAR *__RPC_FAR *ppProvider) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanTakeFocus( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorUI __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorUI __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorUI __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnReceiveFocus )( 
            IElementBehaviorUI __RPC_FAR * This,
            /* [in] */ BOOL fFocus,
            /* [in] */ LONG lSubDivision);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubDivisionProvider )( 
            IElementBehaviorUI __RPC_FAR * This,
            /* [out][retval] */ ISubDivisionProvider __RPC_FAR *__RPC_FAR *ppProvider);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanTakeFocus )( 
            IElementBehaviorUI __RPC_FAR * This);
        
        END_INTERFACE
    } IElementBehaviorUIVtbl;

    interface IElementBehaviorUI
    {
        CONST_VTBL struct IElementBehaviorUIVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorUI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorUI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorUI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorUI_OnReceiveFocus(This,fFocus,lSubDivision)	\
    (This)->lpVtbl -> OnReceiveFocus(This,fFocus,lSubDivision)

#define IElementBehaviorUI_GetSubDivisionProvider(This,ppProvider)	\
    (This)->lpVtbl -> GetSubDivisionProvider(This,ppProvider)

#define IElementBehaviorUI_CanTakeFocus(This)	\
    (This)->lpVtbl -> CanTakeFocus(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IElementBehaviorUI_OnReceiveFocus_Proxy( 
    IElementBehaviorUI __RPC_FAR * This,
    /* [in] */ BOOL fFocus,
    /* [in] */ LONG lSubDivision);


void __RPC_STUB IElementBehaviorUI_OnReceiveFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IElementBehaviorUI_GetSubDivisionProvider_Proxy( 
    IElementBehaviorUI __RPC_FAR * This,
    /* [out][retval] */ ISubDivisionProvider __RPC_FAR *__RPC_FAR *ppProvider);


void __RPC_STUB IElementBehaviorUI_GetSubDivisionProvider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IElementBehaviorUI_CanTakeFocus_Proxy( 
    IElementBehaviorUI __RPC_FAR * This);


void __RPC_STUB IElementBehaviorUI_CanTakeFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorUI_INTERFACE_DEFINED__ */


#ifndef __IElementAdorner_INTERFACE_DEFINED__
#define __IElementAdorner_INTERFACE_DEFINED__

/* interface IElementAdorner */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IElementAdorner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f607-98b5-11cf-bb82-00aa00bdce0b")
    IElementAdorner : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ HDC hdc,
            /* [in] */ LPRECT prc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HitTestPoint( 
            /* [in] */ POINT __RPC_FAR *pt,
            /* [in] */ LPRECT prc,
            /* [out][in] */ BOOL __RPC_FAR *fResult,
            /* [out][in] */ ADORNER_HTI __RPC_FAR *peAdornerHTI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [in] */ SIZE __RPC_FAR *pSizeElem,
            /* [in] */ SIZE __RPC_FAR *pSizeAdorn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [in] */ POINT __RPC_FAR *pPosElem,
            /* [in] */ POINT __RPC_FAR *pPosAdorn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnPositionSet( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementAdornerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementAdorner __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementAdorner __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementAdorner __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IElementAdorner __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ LPRECT prc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HitTestPoint )( 
            IElementAdorner __RPC_FAR * This,
            /* [in] */ POINT __RPC_FAR *pt,
            /* [in] */ LPRECT prc,
            /* [out][in] */ BOOL __RPC_FAR *fResult,
            /* [out][in] */ ADORNER_HTI __RPC_FAR *peAdornerHTI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IElementAdorner __RPC_FAR * This,
            /* [in] */ SIZE __RPC_FAR *pSizeElem,
            /* [in] */ SIZE __RPC_FAR *pSizeAdorn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPosition )( 
            IElementAdorner __RPC_FAR * This,
            /* [in] */ POINT __RPC_FAR *pPosElem,
            /* [in] */ POINT __RPC_FAR *pPosAdorn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPositionSet )( 
            IElementAdorner __RPC_FAR * This);
        
        END_INTERFACE
    } IElementAdornerVtbl;

    interface IElementAdorner
    {
        CONST_VTBL struct IElementAdornerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementAdorner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementAdorner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementAdorner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementAdorner_Draw(This,hdc,prc)	\
    (This)->lpVtbl -> Draw(This,hdc,prc)

#define IElementAdorner_HitTestPoint(This,pt,prc,fResult,peAdornerHTI)	\
    (This)->lpVtbl -> HitTestPoint(This,pt,prc,fResult,peAdornerHTI)

#define IElementAdorner_GetSize(This,pSizeElem,pSizeAdorn)	\
    (This)->lpVtbl -> GetSize(This,pSizeElem,pSizeAdorn)

#define IElementAdorner_GetPosition(This,pPosElem,pPosAdorn)	\
    (This)->lpVtbl -> GetPosition(This,pPosElem,pPosAdorn)

#define IElementAdorner_OnPositionSet(This)	\
    (This)->lpVtbl -> OnPositionSet(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IElementAdorner_Draw_Proxy( 
    IElementAdorner __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ LPRECT prc);


void __RPC_STUB IElementAdorner_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IElementAdorner_HitTestPoint_Proxy( 
    IElementAdorner __RPC_FAR * This,
    /* [in] */ POINT __RPC_FAR *pt,
    /* [in] */ LPRECT prc,
    /* [out][in] */ BOOL __RPC_FAR *fResult,
    /* [out][in] */ ADORNER_HTI __RPC_FAR *peAdornerHTI);


void __RPC_STUB IElementAdorner_HitTestPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IElementAdorner_GetSize_Proxy( 
    IElementAdorner __RPC_FAR * This,
    /* [in] */ SIZE __RPC_FAR *pSizeElem,
    /* [in] */ SIZE __RPC_FAR *pSizeAdorn);


void __RPC_STUB IElementAdorner_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IElementAdorner_GetPosition_Proxy( 
    IElementAdorner __RPC_FAR * This,
    /* [in] */ POINT __RPC_FAR *pPosElem,
    /* [in] */ POINT __RPC_FAR *pPosAdorn);


void __RPC_STUB IElementAdorner_GetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IElementAdorner_OnPositionSet_Proxy( 
    IElementAdorner __RPC_FAR * This);


void __RPC_STUB IElementAdorner_OnPositionSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementAdorner_INTERFACE_DEFINED__ */


#ifndef __IHTMLEditingServices_INTERFACE_DEFINED__
#define __IHTMLEditingServices_INTERFACE_DEFINED__

/* interface IHTMLEditingServices */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLEditingServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f7fb-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLEditingServices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
            /* [in] */ BOOL fAdjustPointers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Paste( 
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
            /* [in] */ BSTR bstrText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PasteFromClipboard( 
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
            /* [in] */ IDataObject __RPC_FAR *pDO) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LaunderSpaces( 
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertSanitizedText( 
            /* [in] */ IMarkupPointer __RPC_FAR *InsertHere,
            /* [in] */ OLECHAR __RPC_FAR *pstrText,
            /* [in] */ LONG cChInput,
            /* [in] */ BOOL fDataBinding) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UrlAutoDetectCurrentWord( 
            /* [in] */ IMarkupPointer __RPC_FAR *pWord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UrlAutoDetectRange( 
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShouldUpdateAnchorText( 
            /* [in] */ OLECHAR __RPC_FAR *pstrHref,
            /* [in] */ OLECHAR __RPC_FAR *pstrAnchorText,
            /* [out] */ BOOL __RPC_FAR *pfResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdjustPointerForInsert( 
            /* [in] */ IDisplayPointer __RPC_FAR *pDispWhereIThinkIAm,
            /* [in] */ BOOL fFurtherInDocument,
            /* [in] */ IMarkupPointer __RPC_FAR *pConstraintStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pConstraintEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindSiteSelectableElement( 
            /* [in] */ IMarkupPointer __RPC_FAR *pPointerStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pPointerEnd,
            /* [in] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppIHTMLElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsElementSiteSelectable( 
            /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement,
            /* [out] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppIElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsElementUIActivatable( 
            /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsElementAtomic( 
            /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PositionPointersInMaster( 
            /* [in] */ IHTMLElement __RPC_FAR *pIElement,
            /* [in] */ IMarkupPointer __RPC_FAR *pIStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pIEnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLEditingServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLEditingServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLEditingServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
            /* [in] */ BOOL fAdjustPointers);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Paste )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
            /* [in] */ BSTR bstrText);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PasteFromClipboard )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
            /* [in] */ IDataObject __RPC_FAR *pDO);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LaunderSpaces )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertSanitizedText )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *InsertHere,
            /* [in] */ OLECHAR __RPC_FAR *pstrText,
            /* [in] */ LONG cChInput,
            /* [in] */ BOOL fDataBinding);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UrlAutoDetectCurrentWord )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pWord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UrlAutoDetectRange )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShouldUpdateAnchorText )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ OLECHAR __RPC_FAR *pstrHref,
            /* [in] */ OLECHAR __RPC_FAR *pstrAnchorText,
            /* [out] */ BOOL __RPC_FAR *pfResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdjustPointerForInsert )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IDisplayPointer __RPC_FAR *pDispWhereIThinkIAm,
            /* [in] */ BOOL fFurtherInDocument,
            /* [in] */ IMarkupPointer __RPC_FAR *pConstraintStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pConstraintEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindSiteSelectableElement )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pPointerStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pPointerEnd,
            /* [in] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppIHTMLElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsElementSiteSelectable )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement,
            /* [out] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppIElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsElementUIActivatable )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsElementAtomic )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PositionPointersInMaster )( 
            IHTMLEditingServices __RPC_FAR * This,
            /* [in] */ IHTMLElement __RPC_FAR *pIElement,
            /* [in] */ IMarkupPointer __RPC_FAR *pIStart,
            /* [in] */ IMarkupPointer __RPC_FAR *pIEnd);
        
        END_INTERFACE
    } IHTMLEditingServicesVtbl;

    interface IHTMLEditingServices
    {
        CONST_VTBL struct IHTMLEditingServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLEditingServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLEditingServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLEditingServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLEditingServices_Delete(This,pStart,pEnd,fAdjustPointers)	\
    (This)->lpVtbl -> Delete(This,pStart,pEnd,fAdjustPointers)

#define IHTMLEditingServices_Paste(This,pStart,pEnd,bstrText)	\
    (This)->lpVtbl -> Paste(This,pStart,pEnd,bstrText)

#define IHTMLEditingServices_PasteFromClipboard(This,pStart,pEnd,pDO)	\
    (This)->lpVtbl -> PasteFromClipboard(This,pStart,pEnd,pDO)

#define IHTMLEditingServices_LaunderSpaces(This,pStart,pEnd)	\
    (This)->lpVtbl -> LaunderSpaces(This,pStart,pEnd)

#define IHTMLEditingServices_InsertSanitizedText(This,InsertHere,pstrText,cChInput,fDataBinding)	\
    (This)->lpVtbl -> InsertSanitizedText(This,InsertHere,pstrText,cChInput,fDataBinding)

#define IHTMLEditingServices_UrlAutoDetectCurrentWord(This,pWord)	\
    (This)->lpVtbl -> UrlAutoDetectCurrentWord(This,pWord)

#define IHTMLEditingServices_UrlAutoDetectRange(This,pStart,pEnd)	\
    (This)->lpVtbl -> UrlAutoDetectRange(This,pStart,pEnd)

#define IHTMLEditingServices_ShouldUpdateAnchorText(This,pstrHref,pstrAnchorText,pfResult)	\
    (This)->lpVtbl -> ShouldUpdateAnchorText(This,pstrHref,pstrAnchorText,pfResult)

#define IHTMLEditingServices_AdjustPointerForInsert(This,pDispWhereIThinkIAm,fFurtherInDocument,pConstraintStart,pConstraintEnd)	\
    (This)->lpVtbl -> AdjustPointerForInsert(This,pDispWhereIThinkIAm,fFurtherInDocument,pConstraintStart,pConstraintEnd)

#define IHTMLEditingServices_FindSiteSelectableElement(This,pPointerStart,pPointerEnd,ppIHTMLElement)	\
    (This)->lpVtbl -> FindSiteSelectableElement(This,pPointerStart,pPointerEnd,ppIHTMLElement)

#define IHTMLEditingServices_IsElementSiteSelectable(This,pIHTMLElement,ppIElement)	\
    (This)->lpVtbl -> IsElementSiteSelectable(This,pIHTMLElement,ppIElement)

#define IHTMLEditingServices_IsElementUIActivatable(This,pIHTMLElement)	\
    (This)->lpVtbl -> IsElementUIActivatable(This,pIHTMLElement)

#define IHTMLEditingServices_IsElementAtomic(This,pIHTMLElement)	\
    (This)->lpVtbl -> IsElementAtomic(This,pIHTMLElement)

#define IHTMLEditingServices_PositionPointersInMaster(This,pIElement,pIStart,pIEnd)	\
    (This)->lpVtbl -> PositionPointersInMaster(This,pIElement,pIStart,pIEnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLEditingServices_Delete_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
    /* [in] */ BOOL fAdjustPointers);


void __RPC_STUB IHTMLEditingServices_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_Paste_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
    /* [in] */ BSTR bstrText);


void __RPC_STUB IHTMLEditingServices_Paste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_PasteFromClipboard_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pEnd,
    /* [in] */ IDataObject __RPC_FAR *pDO);


void __RPC_STUB IHTMLEditingServices_PasteFromClipboard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_LaunderSpaces_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pEnd);


void __RPC_STUB IHTMLEditingServices_LaunderSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_InsertSanitizedText_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *InsertHere,
    /* [in] */ OLECHAR __RPC_FAR *pstrText,
    /* [in] */ LONG cChInput,
    /* [in] */ BOOL fDataBinding);


void __RPC_STUB IHTMLEditingServices_InsertSanitizedText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_UrlAutoDetectCurrentWord_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pWord);


void __RPC_STUB IHTMLEditingServices_UrlAutoDetectCurrentWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_UrlAutoDetectRange_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pEnd);


void __RPC_STUB IHTMLEditingServices_UrlAutoDetectRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_ShouldUpdateAnchorText_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ OLECHAR __RPC_FAR *pstrHref,
    /* [in] */ OLECHAR __RPC_FAR *pstrAnchorText,
    /* [out] */ BOOL __RPC_FAR *pfResult);


void __RPC_STUB IHTMLEditingServices_ShouldUpdateAnchorText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_AdjustPointerForInsert_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IDisplayPointer __RPC_FAR *pDispWhereIThinkIAm,
    /* [in] */ BOOL fFurtherInDocument,
    /* [in] */ IMarkupPointer __RPC_FAR *pConstraintStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pConstraintEnd);


void __RPC_STUB IHTMLEditingServices_AdjustPointerForInsert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_FindSiteSelectableElement_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pPointerStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pPointerEnd,
    /* [in] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppIHTMLElement);


void __RPC_STUB IHTMLEditingServices_FindSiteSelectableElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_IsElementSiteSelectable_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement,
    /* [out] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppIElement);


void __RPC_STUB IHTMLEditingServices_IsElementSiteSelectable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_IsElementUIActivatable_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement);


void __RPC_STUB IHTMLEditingServices_IsElementUIActivatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_IsElementAtomic_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IHTMLElement __RPC_FAR *pIHTMLElement);


void __RPC_STUB IHTMLEditingServices_IsElementAtomic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLEditingServices_PositionPointersInMaster_Proxy( 
    IHTMLEditingServices __RPC_FAR * This,
    /* [in] */ IHTMLElement __RPC_FAR *pIElement,
    /* [in] */ IMarkupPointer __RPC_FAR *pIStart,
    /* [in] */ IMarkupPointer __RPC_FAR *pIEnd);


void __RPC_STUB IHTMLEditingServices_PositionPointersInMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLEditingServices_INTERFACE_DEFINED__ */


#ifndef __IEditDebugServices_INTERFACE_DEFINED__
#define __IEditDebugServices_INTERFACE_DEFINED__

/* interface IEditDebugServices */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IEditDebugServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f60b-98b5-11cf-bb82-00aa00bdce0b")
    IEditDebugServices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCp( 
            /* [in] */ IMarkupPointer __RPC_FAR *pIPointer,
            /* [out] */ long __RPC_FAR *pcp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDebugName( 
            /* [in] */ IMarkupPointer __RPC_FAR *pIPointer,
            /* [in] */ LPCTSTR strDbgName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDisplayPointerDebugName( 
            /* [in] */ IDisplayPointer __RPC_FAR *pDispPointer,
            /* [in] */ LPCTSTR strDbgName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DumpTree( 
            /* [in] */ IMarkupPointer __RPC_FAR *pIPointer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LinesInElement( 
            /* [in] */ IHTMLElement __RPC_FAR *pIElement,
            /* [out] */ long __RPC_FAR *piLines) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FontsOnLine( 
            /* [in] */ IHTMLElement __RPC_FAR *pIElement,
            /* [in] */ long iLine,
            /* [out] */ BSTR __RPC_FAR *pbstrFonts) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPixel( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [out] */ long __RPC_FAR *piColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsUsingBckgrnRecalc( 
            /* [out] */ BOOL __RPC_FAR *pfUsingBckgrnRecalc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsEncodingAutoSelect( 
            /* [out] */ BOOL __RPC_FAR *pfEncodingAutoSelect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableEncodingAutoSelect( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsUsingTableIncRecalc( 
            /* [out] */ BOOL __RPC_FAR *pfUsingTableIncRecalc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEditDebugServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEditDebugServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEditDebugServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCp )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pIPointer,
            /* [out] */ long __RPC_FAR *pcp);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDebugName )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pIPointer,
            /* [in] */ LPCTSTR strDbgName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDisplayPointerDebugName )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ IDisplayPointer __RPC_FAR *pDispPointer,
            /* [in] */ LPCTSTR strDbgName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DumpTree )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ IMarkupPointer __RPC_FAR *pIPointer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LinesInElement )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ IHTMLElement __RPC_FAR *pIElement,
            /* [out] */ long __RPC_FAR *piLines);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FontsOnLine )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ IHTMLElement __RPC_FAR *pIElement,
            /* [in] */ long iLine,
            /* [out] */ BSTR __RPC_FAR *pbstrFonts);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPixel )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [out] */ long __RPC_FAR *piColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUsingBckgrnRecalc )( 
            IEditDebugServices __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pfUsingBckgrnRecalc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsEncodingAutoSelect )( 
            IEditDebugServices __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pfEncodingAutoSelect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableEncodingAutoSelect )( 
            IEditDebugServices __RPC_FAR * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUsingTableIncRecalc )( 
            IEditDebugServices __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pfUsingTableIncRecalc);
        
        END_INTERFACE
    } IEditDebugServicesVtbl;

    interface IEditDebugServices
    {
        CONST_VTBL struct IEditDebugServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEditDebugServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEditDebugServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEditDebugServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEditDebugServices_GetCp(This,pIPointer,pcp)	\
    (This)->lpVtbl -> GetCp(This,pIPointer,pcp)

#define IEditDebugServices_SetDebugName(This,pIPointer,strDbgName)	\
    (This)->lpVtbl -> SetDebugName(This,pIPointer,strDbgName)

#define IEditDebugServices_SetDisplayPointerDebugName(This,pDispPointer,strDbgName)	\
    (This)->lpVtbl -> SetDisplayPointerDebugName(This,pDispPointer,strDbgName)

#define IEditDebugServices_DumpTree(This,pIPointer)	\
    (This)->lpVtbl -> DumpTree(This,pIPointer)

#define IEditDebugServices_LinesInElement(This,pIElement,piLines)	\
    (This)->lpVtbl -> LinesInElement(This,pIElement,piLines)

#define IEditDebugServices_FontsOnLine(This,pIElement,iLine,pbstrFonts)	\
    (This)->lpVtbl -> FontsOnLine(This,pIElement,iLine,pbstrFonts)

#define IEditDebugServices_GetPixel(This,X,Y,piColor)	\
    (This)->lpVtbl -> GetPixel(This,X,Y,piColor)

#define IEditDebugServices_IsUsingBckgrnRecalc(This,pfUsingBckgrnRecalc)	\
    (This)->lpVtbl -> IsUsingBckgrnRecalc(This,pfUsingBckgrnRecalc)

#define IEditDebugServices_IsEncodingAutoSelect(This,pfEncodingAutoSelect)	\
    (This)->lpVtbl -> IsEncodingAutoSelect(This,pfEncodingAutoSelect)

#define IEditDebugServices_EnableEncodingAutoSelect(This,fEnable)	\
    (This)->lpVtbl -> EnableEncodingAutoSelect(This,fEnable)

#define IEditDebugServices_IsUsingTableIncRecalc(This,pfUsingTableIncRecalc)	\
    (This)->lpVtbl -> IsUsingTableIncRecalc(This,pfUsingTableIncRecalc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEditDebugServices_GetCp_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pIPointer,
    /* [out] */ long __RPC_FAR *pcp);


void __RPC_STUB IEditDebugServices_GetCp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_SetDebugName_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pIPointer,
    /* [in] */ LPCTSTR strDbgName);


void __RPC_STUB IEditDebugServices_SetDebugName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_SetDisplayPointerDebugName_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ IDisplayPointer __RPC_FAR *pDispPointer,
    /* [in] */ LPCTSTR strDbgName);


void __RPC_STUB IEditDebugServices_SetDisplayPointerDebugName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_DumpTree_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ IMarkupPointer __RPC_FAR *pIPointer);


void __RPC_STUB IEditDebugServices_DumpTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_LinesInElement_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ IHTMLElement __RPC_FAR *pIElement,
    /* [out] */ long __RPC_FAR *piLines);


void __RPC_STUB IEditDebugServices_LinesInElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_FontsOnLine_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ IHTMLElement __RPC_FAR *pIElement,
    /* [in] */ long iLine,
    /* [out] */ BSTR __RPC_FAR *pbstrFonts);


void __RPC_STUB IEditDebugServices_FontsOnLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_GetPixel_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [out] */ long __RPC_FAR *piColor);


void __RPC_STUB IEditDebugServices_GetPixel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_IsUsingBckgrnRecalc_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pfUsingBckgrnRecalc);


void __RPC_STUB IEditDebugServices_IsUsingBckgrnRecalc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_IsEncodingAutoSelect_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pfEncodingAutoSelect);


void __RPC_STUB IEditDebugServices_IsEncodingAutoSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_EnableEncodingAutoSelect_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IEditDebugServices_EnableEncodingAutoSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditDebugServices_IsUsingTableIncRecalc_Proxy( 
    IEditDebugServices __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pfUsingTableIncRecalc);


void __RPC_STUB IEditDebugServices_IsUsingTableIncRecalc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEditDebugServices_INTERFACE_DEFINED__ */


#ifndef __IPrivacyServices_INTERFACE_DEFINED__
#define __IPrivacyServices_INTERFACE_DEFINED__

/* interface IPrivacyServices */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IPrivacyServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f84b-98b5-11cf-bb82-00aa00bdce0b")
    IPrivacyServices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddPrivacyInfoToList( 
            /* [in] */ LPOLESTR pstrUrl,
            /* [in] */ LPOLESTR pstrPolicyRef,
            /* [in] */ LPOLESTR pstrP3PHeader,
            /* [in] */ LONG dwReserved,
            /* [in] */ DWORD privacyFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrivacyServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPrivacyServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPrivacyServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPrivacyServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPrivacyInfoToList )( 
            IPrivacyServices __RPC_FAR * This,
            /* [in] */ LPOLESTR pstrUrl,
            /* [in] */ LPOLESTR pstrPolicyRef,
            /* [in] */ LPOLESTR pstrP3PHeader,
            /* [in] */ LONG dwReserved,
            /* [in] */ DWORD privacyFlags);
        
        END_INTERFACE
    } IPrivacyServicesVtbl;

    interface IPrivacyServices
    {
        CONST_VTBL struct IPrivacyServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrivacyServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrivacyServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrivacyServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrivacyServices_AddPrivacyInfoToList(This,pstrUrl,pstrPolicyRef,pstrP3PHeader,dwReserved,privacyFlags)	\
    (This)->lpVtbl -> AddPrivacyInfoToList(This,pstrUrl,pstrPolicyRef,pstrP3PHeader,dwReserved,privacyFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPrivacyServices_AddPrivacyInfoToList_Proxy( 
    IPrivacyServices __RPC_FAR * This,
    /* [in] */ LPOLESTR pstrUrl,
    /* [in] */ LPOLESTR pstrPolicyRef,
    /* [in] */ LPOLESTR pstrP3PHeader,
    /* [in] */ LONG dwReserved,
    /* [in] */ DWORD privacyFlags);


void __RPC_STUB IPrivacyServices_AddPrivacyInfoToList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrivacyServices_INTERFACE_DEFINED__ */


#ifndef __IHTMLCEClientServices_INTERFACE_DEFINED__
#define __IHTMLCEClientServices_INTERFACE_DEFINED__

/* interface IHTMLCEClientServices */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLCEClientServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F5DA371-53F4-4270-B80B-5CDF575C3A85")
    IHTMLCEClientServices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BeforeWindowOpen( 
            /* [in] */ BSTR url,
            /* [in] */ BSTR urlContext,
            /* [in] */ BSTR name,
            /* [in] */ BSTR features,
            /* [in] */ IUnknown __RPC_FAR *punkEvents) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPrintAbortProc( 
            void __RPC_FAR *__RPC_FAR *ppfnAbort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLCEClientServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLCEClientServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLCEClientServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLCEClientServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeforeWindowOpen )( 
            IHTMLCEClientServices __RPC_FAR * This,
            /* [in] */ BSTR url,
            /* [in] */ BSTR urlContext,
            /* [in] */ BSTR name,
            /* [in] */ BSTR features,
            /* [in] */ IUnknown __RPC_FAR *punkEvents);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrintAbortProc )( 
            IHTMLCEClientServices __RPC_FAR * This,
            void __RPC_FAR *__RPC_FAR *ppfnAbort);
        
        END_INTERFACE
    } IHTMLCEClientServicesVtbl;

    interface IHTMLCEClientServices
    {
        CONST_VTBL struct IHTMLCEClientServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLCEClientServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLCEClientServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLCEClientServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLCEClientServices_BeforeWindowOpen(This,url,urlContext,name,features,punkEvents)	\
    (This)->lpVtbl -> BeforeWindowOpen(This,url,urlContext,name,features,punkEvents)

#define IHTMLCEClientServices_GetPrintAbortProc(This,ppfnAbort)	\
    (This)->lpVtbl -> GetPrintAbortProc(This,ppfnAbort)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLCEClientServices_BeforeWindowOpen_Proxy( 
    IHTMLCEClientServices __RPC_FAR * This,
    /* [in] */ BSTR url,
    /* [in] */ BSTR urlContext,
    /* [in] */ BSTR name,
    /* [in] */ BSTR features,
    /* [in] */ IUnknown __RPC_FAR *punkEvents);


void __RPC_STUB IHTMLCEClientServices_BeforeWindowOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLCEClientServices_GetPrintAbortProc_Proxy( 
    IHTMLCEClientServices __RPC_FAR * This,
    void __RPC_FAR *__RPC_FAR *ppfnAbort);


void __RPC_STUB IHTMLCEClientServices_GetPrintAbortProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLCEClientServices_INTERFACE_DEFINED__ */


#ifndef __IHTMLCEPopupEvents_INTERFACE_DEFINED__
#define __IHTMLCEPopupEvents_INTERFACE_DEFINED__

/* interface IHTMLCEPopupEvents */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLCEPopupEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5E602DAB-7EF0-442c-9A01-D52FBD2C0E4D")
    IHTMLCEPopupEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Count( 
            /* [out] */ long __RPC_FAR *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Event( 
            /* [in] */ int index,
            /* [out] */ DWORD __RPC_FAR *pdispidEvt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLCEPopupEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLCEPopupEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLCEPopupEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLCEPopupEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Count )( 
            IHTMLCEPopupEvents __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Event )( 
            IHTMLCEPopupEvents __RPC_FAR * This,
            /* [in] */ int index,
            /* [out] */ DWORD __RPC_FAR *pdispidEvt);
        
        END_INTERFACE
    } IHTMLCEPopupEventsVtbl;

    interface IHTMLCEPopupEvents
    {
        CONST_VTBL struct IHTMLCEPopupEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLCEPopupEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLCEPopupEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLCEPopupEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLCEPopupEvents_Count(This,pCount)	\
    (This)->lpVtbl -> Count(This,pCount)

#define IHTMLCEPopupEvents_Event(This,index,pdispidEvt)	\
    (This)->lpVtbl -> Event(This,index,pdispidEvt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLCEPopupEvents_Count_Proxy( 
    IHTMLCEPopupEvents __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pCount);


void __RPC_STUB IHTMLCEPopupEvents_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLCEPopupEvents_Event_Proxy( 
    IHTMLCEPopupEvents __RPC_FAR * This,
    /* [in] */ int index,
    /* [out] */ DWORD __RPC_FAR *pdispidEvt);


void __RPC_STUB IHTMLCEPopupEvents_Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLCEPopupEvents_INTERFACE_DEFINED__ */


#ifndef __IHTMLFilterPainter_INTERFACE_DEFINED__
#define __IHTMLFilterPainter_INTERFACE_DEFINED__

/* interface IHTMLFilterPainter */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLFilterPainter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f6de-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLFilterPainter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InvalidateRectUnfiltered( 
            /* [in] */ RECT __RPC_FAR *prcInvalid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRgnUnfiltered( 
            /* [in] */ HRGN hrgnInvalid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeElementVisibility( 
            /* [in] */ BOOL fVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLFilterPainterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLFilterPainter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLFilterPainter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLFilterPainter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRectUnfiltered )( 
            IHTMLFilterPainter __RPC_FAR * This,
            /* [in] */ RECT __RPC_FAR *prcInvalid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRgnUnfiltered )( 
            IHTMLFilterPainter __RPC_FAR * This,
            /* [in] */ HRGN hrgnInvalid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeElementVisibility )( 
            IHTMLFilterPainter __RPC_FAR * This,
            /* [in] */ BOOL fVisible);
        
        END_INTERFACE
    } IHTMLFilterPainterVtbl;

    interface IHTMLFilterPainter
    {
        CONST_VTBL struct IHTMLFilterPainterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLFilterPainter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLFilterPainter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLFilterPainter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLFilterPainter_InvalidateRectUnfiltered(This,prcInvalid)	\
    (This)->lpVtbl -> InvalidateRectUnfiltered(This,prcInvalid)

#define IHTMLFilterPainter_InvalidateRgnUnfiltered(This,hrgnInvalid)	\
    (This)->lpVtbl -> InvalidateRgnUnfiltered(This,hrgnInvalid)

#define IHTMLFilterPainter_ChangeElementVisibility(This,fVisible)	\
    (This)->lpVtbl -> ChangeElementVisibility(This,fVisible)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLFilterPainter_InvalidateRectUnfiltered_Proxy( 
    IHTMLFilterPainter __RPC_FAR * This,
    /* [in] */ RECT __RPC_FAR *prcInvalid);


void __RPC_STUB IHTMLFilterPainter_InvalidateRectUnfiltered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPainter_InvalidateRgnUnfiltered_Proxy( 
    IHTMLFilterPainter __RPC_FAR * This,
    /* [in] */ HRGN hrgnInvalid);


void __RPC_STUB IHTMLFilterPainter_InvalidateRgnUnfiltered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPainter_ChangeElementVisibility_Proxy( 
    IHTMLFilterPainter __RPC_FAR * This,
    /* [in] */ BOOL fVisible);


void __RPC_STUB IHTMLFilterPainter_ChangeElementVisibility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLFilterPainter_INTERFACE_DEFINED__ */


#ifndef __IHTMLFilterPaintSite_INTERFACE_DEFINED__
#define __IHTMLFilterPaintSite_INTERFACE_DEFINED__

/* interface IHTMLFilterPaintSite */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLFilterPaintSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f6d3-98b5-11cf-bb82-00aa00bdce0b")
    IHTMLFilterPaintSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DrawUnfiltered( 
            /* [in] */ HDC hdc,
            /* [in] */ IUnknown __RPC_FAR *punkDrawObject,
            /* [in] */ RECT rcBounds,
            /* [in] */ RECT rcUpdate,
            /* [in] */ LONG lDrawLayers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HitTestPointUnfiltered( 
            /* [in] */ POINT pt,
            /* [in] */ LONG lDrawLayers,
            /* [out][retval] */ BOOL __RPC_FAR *pbHit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRectFiltered( 
            /* [in] */ RECT __RPC_FAR *prcInvalid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRgnFiltered( 
            /* [in] */ HRGN hrgnInvalid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeFilterVisibility( 
            /* [in] */ BOOL fVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnsureViewForFilterSite( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDirectDraw( 
            /* [out][retval] */ void __RPC_FAR *__RPC_FAR *ppDirectDraw) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFilterFlags( 
            /* [out][retval] */ DWORD __RPC_FAR *nFlagVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLFilterPaintSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLFilterPaintSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLFilterPaintSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawUnfiltered )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ IUnknown __RPC_FAR *punkDrawObject,
            /* [in] */ RECT rcBounds,
            /* [in] */ RECT rcUpdate,
            /* [in] */ LONG lDrawLayers);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HitTestPointUnfiltered )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [in] */ POINT pt,
            /* [in] */ LONG lDrawLayers,
            /* [out][retval] */ BOOL __RPC_FAR *pbHit);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRectFiltered )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [in] */ RECT __RPC_FAR *prcInvalid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRgnFiltered )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [in] */ HRGN hrgnInvalid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeFilterVisibility )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [in] */ BOOL fVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnsureViewForFilterSite )( 
            IHTMLFilterPaintSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDirectDraw )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [out][retval] */ void __RPC_FAR *__RPC_FAR *ppDirectDraw);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFilterFlags )( 
            IHTMLFilterPaintSite __RPC_FAR * This,
            /* [out][retval] */ DWORD __RPC_FAR *nFlagVal);
        
        END_INTERFACE
    } IHTMLFilterPaintSiteVtbl;

    interface IHTMLFilterPaintSite
    {
        CONST_VTBL struct IHTMLFilterPaintSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLFilterPaintSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLFilterPaintSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLFilterPaintSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLFilterPaintSite_DrawUnfiltered(This,hdc,punkDrawObject,rcBounds,rcUpdate,lDrawLayers)	\
    (This)->lpVtbl -> DrawUnfiltered(This,hdc,punkDrawObject,rcBounds,rcUpdate,lDrawLayers)

#define IHTMLFilterPaintSite_HitTestPointUnfiltered(This,pt,lDrawLayers,pbHit)	\
    (This)->lpVtbl -> HitTestPointUnfiltered(This,pt,lDrawLayers,pbHit)

#define IHTMLFilterPaintSite_InvalidateRectFiltered(This,prcInvalid)	\
    (This)->lpVtbl -> InvalidateRectFiltered(This,prcInvalid)

#define IHTMLFilterPaintSite_InvalidateRgnFiltered(This,hrgnInvalid)	\
    (This)->lpVtbl -> InvalidateRgnFiltered(This,hrgnInvalid)

#define IHTMLFilterPaintSite_ChangeFilterVisibility(This,fVisible)	\
    (This)->lpVtbl -> ChangeFilterVisibility(This,fVisible)

#define IHTMLFilterPaintSite_EnsureViewForFilterSite(This)	\
    (This)->lpVtbl -> EnsureViewForFilterSite(This)

#define IHTMLFilterPaintSite_GetDirectDraw(This,ppDirectDraw)	\
    (This)->lpVtbl -> GetDirectDraw(This,ppDirectDraw)

#define IHTMLFilterPaintSite_GetFilterFlags(This,nFlagVal)	\
    (This)->lpVtbl -> GetFilterFlags(This,nFlagVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_DrawUnfiltered_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ IUnknown __RPC_FAR *punkDrawObject,
    /* [in] */ RECT rcBounds,
    /* [in] */ RECT rcUpdate,
    /* [in] */ LONG lDrawLayers);


void __RPC_STUB IHTMLFilterPaintSite_DrawUnfiltered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_HitTestPointUnfiltered_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [in] */ POINT pt,
    /* [in] */ LONG lDrawLayers,
    /* [out][retval] */ BOOL __RPC_FAR *pbHit);


void __RPC_STUB IHTMLFilterPaintSite_HitTestPointUnfiltered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_InvalidateRectFiltered_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [in] */ RECT __RPC_FAR *prcInvalid);


void __RPC_STUB IHTMLFilterPaintSite_InvalidateRectFiltered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_InvalidateRgnFiltered_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [in] */ HRGN hrgnInvalid);


void __RPC_STUB IHTMLFilterPaintSite_InvalidateRgnFiltered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_ChangeFilterVisibility_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [in] */ BOOL fVisible);


void __RPC_STUB IHTMLFilterPaintSite_ChangeFilterVisibility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_EnsureViewForFilterSite_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This);


void __RPC_STUB IHTMLFilterPaintSite_EnsureViewForFilterSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_GetDirectDraw_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [out][retval] */ void __RPC_FAR *__RPC_FAR *ppDirectDraw);


void __RPC_STUB IHTMLFilterPaintSite_GetDirectDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLFilterPaintSite_GetFilterFlags_Proxy( 
    IHTMLFilterPaintSite __RPC_FAR * This,
    /* [out][retval] */ DWORD __RPC_FAR *nFlagVal);


void __RPC_STUB IHTMLFilterPaintSite_GetFilterFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLFilterPaintSite_INTERFACE_DEFINED__ */


#ifndef __IElementNamespacePrivate_INTERFACE_DEFINED__
#define __IElementNamespacePrivate_INTERFACE_DEFINED__

/* interface IElementNamespacePrivate */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IElementNamespacePrivate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f7ff-98b5-11cf-bb82-00aa00bdce0b")
    IElementNamespacePrivate : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddTagPrivate( 
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrBaseTagName,
            /* [in] */ LONG lFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementNamespacePrivateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementNamespacePrivate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementNamespacePrivate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementNamespacePrivate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTagPrivate )( 
            IElementNamespacePrivate __RPC_FAR * This,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrBaseTagName,
            /* [in] */ LONG lFlags);
        
        END_INTERFACE
    } IElementNamespacePrivateVtbl;

    interface IElementNamespacePrivate
    {
        CONST_VTBL struct IElementNamespacePrivateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementNamespacePrivate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementNamespacePrivate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementNamespacePrivate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementNamespacePrivate_AddTagPrivate(This,bstrTagName,bstrBaseTagName,lFlags)	\
    (This)->lpVtbl -> AddTagPrivate(This,bstrTagName,bstrBaseTagName,lFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IElementNamespacePrivate_AddTagPrivate_Proxy( 
    IElementNamespacePrivate __RPC_FAR * This,
    /* [in] */ BSTR bstrTagName,
    /* [in] */ BSTR bstrBaseTagName,
    /* [in] */ LONG lFlags);


void __RPC_STUB IElementNamespacePrivate_AddTagPrivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementNamespacePrivate_INTERFACE_DEFINED__ */


#ifndef __ICursorInfo_INTERFACE_DEFINED__
#define __ICursorInfo_INTERFACE_DEFINED__

/* interface ICursorInfo */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_ICursorInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70301738-94EC-4C88-BA9B-7356FA6290AC")
    ICursorInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CaptureCursor( 
            /* [in] */ BOOL bCapture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCaretState( 
            /* [in] */ BOOL bActive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetComboBoxState( 
            /* [in] */ BOOL bActive,
            /* [in] */ BOOL bDropDown) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyLayoutChange( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessSingleTap( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsAcceleratedCursorMovement( 
            /* [out] */ BOOL __RPC_FAR *pbIsAccelerate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetScrollbarState( 
            /* [in] */ BOOL bIsScrollbar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsSelectionMode( 
            /* [out] */ BOOL __RPC_FAR *pbSelectionMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICursorInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICursorInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICursorInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICursorInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CaptureCursor )( 
            ICursorInfo __RPC_FAR * This,
            /* [in] */ BOOL bCapture);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCaretState )( 
            ICursorInfo __RPC_FAR * This,
            /* [in] */ BOOL bActive);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetComboBoxState )( 
            ICursorInfo __RPC_FAR * This,
            /* [in] */ BOOL bActive,
            /* [in] */ BOOL bDropDown);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyLayoutChange )( 
            ICursorInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProcessSingleTap )( 
            ICursorInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAcceleratedCursorMovement )( 
            ICursorInfo __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbIsAccelerate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScrollbarState )( 
            ICursorInfo __RPC_FAR * This,
            /* [in] */ BOOL bIsScrollbar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSelectionMode )( 
            ICursorInfo __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbSelectionMode);
        
        END_INTERFACE
    } ICursorInfoVtbl;

    interface ICursorInfo
    {
        CONST_VTBL struct ICursorInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICursorInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICursorInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICursorInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICursorInfo_CaptureCursor(This,bCapture)	\
    (This)->lpVtbl -> CaptureCursor(This,bCapture)

#define ICursorInfo_SetCaretState(This,bActive)	\
    (This)->lpVtbl -> SetCaretState(This,bActive)

#define ICursorInfo_SetComboBoxState(This,bActive,bDropDown)	\
    (This)->lpVtbl -> SetComboBoxState(This,bActive,bDropDown)

#define ICursorInfo_NotifyLayoutChange(This)	\
    (This)->lpVtbl -> NotifyLayoutChange(This)

#define ICursorInfo_ProcessSingleTap(This)	\
    (This)->lpVtbl -> ProcessSingleTap(This)

#define ICursorInfo_IsAcceleratedCursorMovement(This,pbIsAccelerate)	\
    (This)->lpVtbl -> IsAcceleratedCursorMovement(This,pbIsAccelerate)

#define ICursorInfo_SetScrollbarState(This,bIsScrollbar)	\
    (This)->lpVtbl -> SetScrollbarState(This,bIsScrollbar)

#define ICursorInfo_IsSelectionMode(This,pbSelectionMode)	\
    (This)->lpVtbl -> IsSelectionMode(This,pbSelectionMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICursorInfo_CaptureCursor_Proxy( 
    ICursorInfo __RPC_FAR * This,
    /* [in] */ BOOL bCapture);


void __RPC_STUB ICursorInfo_CaptureCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_SetCaretState_Proxy( 
    ICursorInfo __RPC_FAR * This,
    /* [in] */ BOOL bActive);


void __RPC_STUB ICursorInfo_SetCaretState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_SetComboBoxState_Proxy( 
    ICursorInfo __RPC_FAR * This,
    /* [in] */ BOOL bActive,
    /* [in] */ BOOL bDropDown);


void __RPC_STUB ICursorInfo_SetComboBoxState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_NotifyLayoutChange_Proxy( 
    ICursorInfo __RPC_FAR * This);


void __RPC_STUB ICursorInfo_NotifyLayoutChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_ProcessSingleTap_Proxy( 
    ICursorInfo __RPC_FAR * This);


void __RPC_STUB ICursorInfo_ProcessSingleTap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_IsAcceleratedCursorMovement_Proxy( 
    ICursorInfo __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbIsAccelerate);


void __RPC_STUB ICursorInfo_IsAcceleratedCursorMovement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_SetScrollbarState_Proxy( 
    ICursorInfo __RPC_FAR * This,
    /* [in] */ BOOL bIsScrollbar);


void __RPC_STUB ICursorInfo_SetScrollbarState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICursorInfo_IsSelectionMode_Proxy( 
    ICursorInfo __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbSelectionMode);


void __RPC_STUB ICursorInfo_IsSelectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICursorInfo_INTERFACE_DEFINED__ */


#ifndef __IHttpHeaderInfo_INTERFACE_DEFINED__
#define __IHttpHeaderInfo_INTERFACE_DEFINED__

/* interface IHttpHeaderInfo */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHttpHeaderInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0B9C155B-19BF-434c-9968-A4875AEAD66A")
    IHttpHeaderInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetExtraHeaders( 
            /* [out] */ LPWSTR __RPC_FAR *ppszExtraHeaders) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAcceptHeader( 
            /* [out] */ LPWSTR __RPC_FAR *ppszAcceptHeader) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHttpHeaderInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHttpHeaderInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHttpHeaderInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHttpHeaderInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExtraHeaders )( 
            IHttpHeaderInfo __RPC_FAR * This,
            /* [out] */ LPWSTR __RPC_FAR *ppszExtraHeaders);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAcceptHeader )( 
            IHttpHeaderInfo __RPC_FAR * This,
            /* [out] */ LPWSTR __RPC_FAR *ppszAcceptHeader);
        
        END_INTERFACE
    } IHttpHeaderInfoVtbl;

    interface IHttpHeaderInfo
    {
        CONST_VTBL struct IHttpHeaderInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHttpHeaderInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHttpHeaderInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHttpHeaderInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHttpHeaderInfo_GetExtraHeaders(This,ppszExtraHeaders)	\
    (This)->lpVtbl -> GetExtraHeaders(This,ppszExtraHeaders)

#define IHttpHeaderInfo_GetAcceptHeader(This,ppszAcceptHeader)	\
    (This)->lpVtbl -> GetAcceptHeader(This,ppszAcceptHeader)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHttpHeaderInfo_GetExtraHeaders_Proxy( 
    IHttpHeaderInfo __RPC_FAR * This,
    /* [out] */ LPWSTR __RPC_FAR *ppszExtraHeaders);


void __RPC_STUB IHttpHeaderInfo_GetExtraHeaders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHttpHeaderInfo_GetAcceptHeader_Proxy( 
    IHttpHeaderInfo __RPC_FAR * This,
    /* [out] */ LPWSTR __RPC_FAR *ppszAcceptHeader);


void __RPC_STUB IHttpHeaderInfo_GetAcceptHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHttpHeaderInfo_INTERFACE_DEFINED__ */


#ifndef __IHTMLDocumentRender_INTERFACE_DEFINED__
#define __IHTMLDocumentRender_INTERFACE_DEFINED__

/* interface IHTMLDocumentRender */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IHTMLDocumentRender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19A210B6-E213-4816-A8E6-D37464658D07")
    IHTMLDocumentRender : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DrawToDC( 
            /* [in] */ HDC hdc,
            /* [in] */ RECT __RPC_FAR *prcDraw,
            /* [in] */ float __RPC_FAR *pClientScale) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawToDCEx( 
            /* [in] */ HDC hdc,
            /* [in] */ IUnknown __RPC_FAR *punkDrawObject,
            /* [in] */ RECT __RPC_FAR *prcDraw,
            /* [in] */ float __RPC_FAR *pClientScale) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHTMLDocumentRenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHTMLDocumentRender __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHTMLDocumentRender __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHTMLDocumentRender __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawToDC )( 
            IHTMLDocumentRender __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ RECT __RPC_FAR *prcDraw,
            /* [in] */ float __RPC_FAR *pClientScale);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawToDCEx )( 
            IHTMLDocumentRender __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ IUnknown __RPC_FAR *punkDrawObject,
            /* [in] */ RECT __RPC_FAR *prcDraw,
            /* [in] */ float __RPC_FAR *pClientScale);
        
        END_INTERFACE
    } IHTMLDocumentRenderVtbl;

    interface IHTMLDocumentRender
    {
        CONST_VTBL struct IHTMLDocumentRenderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLDocumentRender_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHTMLDocumentRender_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHTMLDocumentRender_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHTMLDocumentRender_DrawToDC(This,hdc,prcDraw,pClientScale)	\
    (This)->lpVtbl -> DrawToDC(This,hdc,prcDraw,pClientScale)

#define IHTMLDocumentRender_DrawToDCEx(This,hdc,punkDrawObject,prcDraw,pClientScale)	\
    (This)->lpVtbl -> DrawToDCEx(This,hdc,punkDrawObject,prcDraw,pClientScale)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHTMLDocumentRender_DrawToDC_Proxy( 
    IHTMLDocumentRender __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ RECT __RPC_FAR *prcDraw,
    /* [in] */ float __RPC_FAR *pClientScale);


void __RPC_STUB IHTMLDocumentRender_DrawToDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHTMLDocumentRender_DrawToDCEx_Proxy( 
    IHTMLDocumentRender __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ IUnknown __RPC_FAR *punkDrawObject,
    /* [in] */ RECT __RPC_FAR *prcDraw,
    /* [in] */ float __RPC_FAR *pClientScale);


void __RPC_STUB IHTMLDocumentRender_DrawToDCEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHTMLDocumentRender_INTERFACE_DEFINED__ */


#ifndef __IMobileDocumentServices_INTERFACE_DEFINED__
#define __IMobileDocumentServices_INTERFACE_DEFINED__

/* interface IMobileDocumentServices */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IMobileDocumentServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D1459857-0A7D-4d3b-B501-C4E9407D91EE")
    IMobileDocumentServices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsMobileOptimized( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SuspendDocument( 
            /* [in] */ DWORD nFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResumeDocument( 
            /* [in] */ DWORD nFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreezeDocument( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnfreezeDocument( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExecuteDeferredMessages( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawViewRect( 
            /* [in] */ RECT __RPC_FAR *prcInvalid,
            /* [in] */ BOOL bSyncPublishView,
            /* [in] */ BOOL bForceUpdate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ZoomDocument( 
            /* [in] */ DWORD dwZoomPercentage,
            /* [in] */ POINT ptCenter,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetZoomRange( 
            /* [out] */ DWORD __RPC_FAR *pdwZoomMinPercentage,
            /* [out] */ DWORD __RPC_FAR *pdwZoomMaxPercentage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOverviewZoomPortraitLevel( 
            /* [out] */ DWORD __RPC_FAR *pdwZoomLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOverviewZoomLandscapeLevel( 
            /* [out] */ DWORD __RPC_FAR *pdwZoomLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsLevelInteractive( 
            /* [in] */ DWORD dwZoomPercentage,
            /* [out] */ BOOL __RPC_FAR *pfInteractive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetZoomLevel( 
            /* [out] */ DWORD __RPC_FAR *pdwZoomPercentage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetZoomDefaults( 
            /* [in] */ DWORD dwDefaults) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayBufferDC( 
            /* [out] */ HDC __RPC_FAR *pHDC,
            /* [out] */ POINT __RPC_FAR *pptBufferOrigin,
            /* [out] */ RECT __RPC_FAR *prcValidRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisableCacheDrawing( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetScrollRenderMode( 
            /* [in] */ BOOL fSync) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetElementHighlight( 
            /* [in] */ LINKHIGHLIGHT_MODE nHighlightMode,
            /* [in] */ IHTMLElement __RPC_FAR *pElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveElementHighlight( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMobileDocumentServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMobileDocumentServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMobileDocumentServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMobileOptimized )( 
            IMobileDocumentServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SuspendDocument )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD nFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResumeDocument )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD nFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreezeDocument )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnfreezeDocument )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteDeferredMessages )( 
            IMobileDocumentServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawViewRect )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ RECT __RPC_FAR *prcInvalid,
            /* [in] */ BOOL bSyncPublishView,
            /* [in] */ BOOL bForceUpdate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZoomDocument )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD dwZoomPercentage,
            /* [in] */ POINT ptCenter,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZoomRange )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwZoomMinPercentage,
            /* [out] */ DWORD __RPC_FAR *pdwZoomMaxPercentage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOverviewZoomPortraitLevel )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwZoomLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOverviewZoomLandscapeLevel )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwZoomLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsLevelInteractive )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD dwZoomPercentage,
            /* [out] */ BOOL __RPC_FAR *pfInteractive);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZoomLevel )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwZoomPercentage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZoomDefaults )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ DWORD dwDefaults);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayBufferDC )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [out] */ HDC __RPC_FAR *pHDC,
            /* [out] */ POINT __RPC_FAR *pptBufferOrigin,
            /* [out] */ RECT __RPC_FAR *prcValidRect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisableCacheDrawing )( 
            IMobileDocumentServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScrollRenderMode )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ BOOL fSync);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetElementHighlight )( 
            IMobileDocumentServices __RPC_FAR * This,
            /* [in] */ LINKHIGHLIGHT_MODE nHighlightMode,
            /* [in] */ IHTMLElement __RPC_FAR *pElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveElementHighlight )( 
            IMobileDocumentServices __RPC_FAR * This);
        
        END_INTERFACE
    } IMobileDocumentServicesVtbl;

    interface IMobileDocumentServices
    {
        CONST_VTBL struct IMobileDocumentServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMobileDocumentServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMobileDocumentServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMobileDocumentServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMobileDocumentServices_IsMobileOptimized(This)	\
    (This)->lpVtbl -> IsMobileOptimized(This)

#define IMobileDocumentServices_SuspendDocument(This,nFlags)	\
    (This)->lpVtbl -> SuspendDocument(This,nFlags)

#define IMobileDocumentServices_ResumeDocument(This,nFlags)	\
    (This)->lpVtbl -> ResumeDocument(This,nFlags)

#define IMobileDocumentServices_FreezeDocument(This,dwFlags)	\
    (This)->lpVtbl -> FreezeDocument(This,dwFlags)

#define IMobileDocumentServices_UnfreezeDocument(This,dwFlags)	\
    (This)->lpVtbl -> UnfreezeDocument(This,dwFlags)

#define IMobileDocumentServices_ExecuteDeferredMessages(This)	\
    (This)->lpVtbl -> ExecuteDeferredMessages(This)

#define IMobileDocumentServices_DrawViewRect(This,prcInvalid,bSyncPublishView,bForceUpdate)	\
    (This)->lpVtbl -> DrawViewRect(This,prcInvalid,bSyncPublishView,bForceUpdate)

#define IMobileDocumentServices_ZoomDocument(This,dwZoomPercentage,ptCenter,dwFlags)	\
    (This)->lpVtbl -> ZoomDocument(This,dwZoomPercentage,ptCenter,dwFlags)

#define IMobileDocumentServices_GetZoomRange(This,pdwZoomMinPercentage,pdwZoomMaxPercentage)	\
    (This)->lpVtbl -> GetZoomRange(This,pdwZoomMinPercentage,pdwZoomMaxPercentage)

#define IMobileDocumentServices_GetOverviewZoomPortraitLevel(This,pdwZoomLevel)	\
    (This)->lpVtbl -> GetOverviewZoomPortraitLevel(This,pdwZoomLevel)

#define IMobileDocumentServices_GetOverviewZoomLandscapeLevel(This,pdwZoomLevel)	\
    (This)->lpVtbl -> GetOverviewZoomLandscapeLevel(This,pdwZoomLevel)

#define IMobileDocumentServices_IsLevelInteractive(This,dwZoomPercentage,pfInteractive)	\
    (This)->lpVtbl -> IsLevelInteractive(This,dwZoomPercentage,pfInteractive)

#define IMobileDocumentServices_GetZoomLevel(This,pdwZoomPercentage)	\
    (This)->lpVtbl -> GetZoomLevel(This,pdwZoomPercentage)

#define IMobileDocumentServices_SetZoomDefaults(This,dwDefaults)	\
    (This)->lpVtbl -> SetZoomDefaults(This,dwDefaults)

#define IMobileDocumentServices_GetDisplayBufferDC(This,pHDC,pptBufferOrigin,prcValidRect)	\
    (This)->lpVtbl -> GetDisplayBufferDC(This,pHDC,pptBufferOrigin,prcValidRect)

#define IMobileDocumentServices_DisableCacheDrawing(This)	\
    (This)->lpVtbl -> DisableCacheDrawing(This)

#define IMobileDocumentServices_SetScrollRenderMode(This,fSync)	\
    (This)->lpVtbl -> SetScrollRenderMode(This,fSync)

#define IMobileDocumentServices_SetElementHighlight(This,nHighlightMode,pElement)	\
    (This)->lpVtbl -> SetElementHighlight(This,nHighlightMode,pElement)

#define IMobileDocumentServices_RemoveElementHighlight(This)	\
    (This)->lpVtbl -> RemoveElementHighlight(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMobileDocumentServices_IsMobileOptimized_Proxy( 
    IMobileDocumentServices __RPC_FAR * This);


void __RPC_STUB IMobileDocumentServices_IsMobileOptimized_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_SuspendDocument_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD nFlags);


void __RPC_STUB IMobileDocumentServices_SuspendDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_ResumeDocument_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD nFlags);


void __RPC_STUB IMobileDocumentServices_ResumeDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_FreezeDocument_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMobileDocumentServices_FreezeDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_UnfreezeDocument_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMobileDocumentServices_UnfreezeDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_ExecuteDeferredMessages_Proxy( 
    IMobileDocumentServices __RPC_FAR * This);


void __RPC_STUB IMobileDocumentServices_ExecuteDeferredMessages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_DrawViewRect_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ RECT __RPC_FAR *prcInvalid,
    /* [in] */ BOOL bSyncPublishView,
    /* [in] */ BOOL bForceUpdate);


void __RPC_STUB IMobileDocumentServices_DrawViewRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_ZoomDocument_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD dwZoomPercentage,
    /* [in] */ POINT ptCenter,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMobileDocumentServices_ZoomDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_GetZoomRange_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwZoomMinPercentage,
    /* [out] */ DWORD __RPC_FAR *pdwZoomMaxPercentage);


void __RPC_STUB IMobileDocumentServices_GetZoomRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_GetOverviewZoomPortraitLevel_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwZoomLevel);


void __RPC_STUB IMobileDocumentServices_GetOverviewZoomPortraitLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_GetOverviewZoomLandscapeLevel_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwZoomLevel);


void __RPC_STUB IMobileDocumentServices_GetOverviewZoomLandscapeLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_IsLevelInteractive_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD dwZoomPercentage,
    /* [out] */ BOOL __RPC_FAR *pfInteractive);


void __RPC_STUB IMobileDocumentServices_IsLevelInteractive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_GetZoomLevel_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwZoomPercentage);


void __RPC_STUB IMobileDocumentServices_GetZoomLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_SetZoomDefaults_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ DWORD dwDefaults);


void __RPC_STUB IMobileDocumentServices_SetZoomDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_GetDisplayBufferDC_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [out] */ HDC __RPC_FAR *pHDC,
    /* [out] */ POINT __RPC_FAR *pptBufferOrigin,
    /* [out] */ RECT __RPC_FAR *prcValidRect);


void __RPC_STUB IMobileDocumentServices_GetDisplayBufferDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_DisableCacheDrawing_Proxy( 
    IMobileDocumentServices __RPC_FAR * This);


void __RPC_STUB IMobileDocumentServices_DisableCacheDrawing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_SetScrollRenderMode_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ BOOL fSync);


void __RPC_STUB IMobileDocumentServices_SetScrollRenderMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_SetElementHighlight_Proxy( 
    IMobileDocumentServices __RPC_FAR * This,
    /* [in] */ LINKHIGHLIGHT_MODE nHighlightMode,
    /* [in] */ IHTMLElement __RPC_FAR *pElement);


void __RPC_STUB IMobileDocumentServices_SetElementHighlight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMobileDocumentServices_RemoveElementHighlight_Proxy( 
    IMobileDocumentServices __RPC_FAR * This);


void __RPC_STUB IMobileDocumentServices_RemoveElementHighlight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMobileDocumentServices_INTERFACE_DEFINED__ */


#ifndef __IBrowserConnectionServices_INTERFACE_DEFINED__
#define __IBrowserConnectionServices_INTERFACE_DEFINED__

/* interface IBrowserConnectionServices */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IBrowserConnectionServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d9eb19e3-5260-4b03-95c1-72d890857520")
    IBrowserConnectionServices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNavigationUrl( 
            /* [in] */ BSTR bstrUrl,
            /* [out] */ BSTR __RPC_FAR *bstrNavigationUrl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowserConnectionServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBrowserConnectionServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBrowserConnectionServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBrowserConnectionServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNavigationUrl )( 
            IBrowserConnectionServices __RPC_FAR * This,
            /* [in] */ BSTR bstrUrl,
            /* [out] */ BSTR __RPC_FAR *bstrNavigationUrl);
        
        END_INTERFACE
    } IBrowserConnectionServicesVtbl;

    interface IBrowserConnectionServices
    {
        CONST_VTBL struct IBrowserConnectionServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowserConnectionServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBrowserConnectionServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBrowserConnectionServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBrowserConnectionServices_GetNavigationUrl(This,bstrUrl,bstrNavigationUrl)	\
    (This)->lpVtbl -> GetNavigationUrl(This,bstrUrl,bstrNavigationUrl)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBrowserConnectionServices_GetNavigationUrl_Proxy( 
    IBrowserConnectionServices __RPC_FAR * This,
    /* [in] */ BSTR bstrUrl,
    /* [out] */ BSTR __RPC_FAR *bstrNavigationUrl);


void __RPC_STUB IBrowserConnectionServices_GetNavigationUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowserConnectionServices_INTERFACE_DEFINED__ */


#ifndef __IMobileHTMLDocument_INTERFACE_DEFINED__
#define __IMobileHTMLDocument_INTERFACE_DEFINED__

/* interface IMobileHTMLDocument */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IMobileHTMLDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77FD0F56-82C8-48FE-97AE-3573BF02C4FA")
    IMobileHTMLDocument : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetClickable( 
            /* [out] */ IHTMLElementCollection __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMobileHTMLDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMobileHTMLDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMobileHTMLDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMobileHTMLDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClickable )( 
            IMobileHTMLDocument __RPC_FAR * This,
            /* [out] */ IHTMLElementCollection __RPC_FAR *__RPC_FAR *ppDisp);
        
        END_INTERFACE
    } IMobileHTMLDocumentVtbl;

    interface IMobileHTMLDocument
    {
        CONST_VTBL struct IMobileHTMLDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMobileHTMLDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMobileHTMLDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMobileHTMLDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMobileHTMLDocument_GetClickable(This,ppDisp)	\
    (This)->lpVtbl -> GetClickable(This,ppDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMobileHTMLDocument_GetClickable_Proxy( 
    IMobileHTMLDocument __RPC_FAR * This,
    /* [out] */ IHTMLElementCollection __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IMobileHTMLDocument_GetClickable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMobileHTMLDocument_INTERFACE_DEFINED__ */


#ifndef __IProgressStatusUpdate_INTERFACE_DEFINED__
#define __IProgressStatusUpdate_INTERFACE_DEFINED__

/* interface IProgressStatusUpdate */
/* [uuid][unique][object] */ 


EXTERN_C const IID IID_IProgressStatusUpdate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ded1cd1b-65ce-4028-9eba-4c02655a59fe")
    IProgressStatusUpdate : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetBytesDownloaded( 
            /* [in] */ DWORD dwBytesDownloaded,
            /* [in] */ DWORD dwMaxBytes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProgressStatusUpdateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProgressStatusUpdate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProgressStatusUpdate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProgressStatusUpdate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBytesDownloaded )( 
            IProgressStatusUpdate __RPC_FAR * This,
            /* [in] */ DWORD dwBytesDownloaded,
            /* [in] */ DWORD dwMaxBytes);
        
        END_INTERFACE
    } IProgressStatusUpdateVtbl;

    interface IProgressStatusUpdate
    {
        CONST_VTBL struct IProgressStatusUpdateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProgressStatusUpdate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProgressStatusUpdate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProgressStatusUpdate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProgressStatusUpdate_SetBytesDownloaded(This,dwBytesDownloaded,dwMaxBytes)	\
    (This)->lpVtbl -> SetBytesDownloaded(This,dwBytesDownloaded,dwMaxBytes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IProgressStatusUpdate_SetBytesDownloaded_Proxy( 
    IProgressStatusUpdate __RPC_FAR * This,
    /* [in] */ DWORD dwBytesDownloaded,
    /* [in] */ DWORD dwMaxBytes);


void __RPC_STUB IProgressStatusUpdate_SetBytesDownloaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProgressStatusUpdate_INTERFACE_DEFINED__ */

#endif /* __MSHTMLINTERNAL_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_interned_0641 */
/* [local] */ 

#endif //INTERNAL_H_


extern RPC_IF_HANDLE __MIDL_itf_interned_0641_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_interned_0641_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


