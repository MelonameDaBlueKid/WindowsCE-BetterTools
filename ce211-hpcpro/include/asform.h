/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Sat Sep 19 22:28:26 1998
 */
/* Compiler settings for .\asform.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __asform_h__
#define __asform_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ActiveAPISet_FWD_DEFINED__
#define __ActiveAPISet_FWD_DEFINED__
typedef interface ActiveAPISet ActiveAPISet;
#endif 	/* __ActiveAPISet_FWD_DEFINED__ */


#ifndef __IASControls_FWD_DEFINED__
#define __IASControls_FWD_DEFINED__
typedef interface IASControls IASControls;
#endif 	/* __IASControls_FWD_DEFINED__ */


#ifndef __IASForm_FWD_DEFINED__
#define __IASForm_FWD_DEFINED__
typedef interface IASForm IASForm;
#endif 	/* __IASForm_FWD_DEFINED__ */


#ifndef __ActiveSmallFormEvents_FWD_DEFINED__
#define __ActiveSmallFormEvents_FWD_DEFINED__
typedef interface ActiveSmallFormEvents ActiveSmallFormEvents;
#endif 	/* __ActiveSmallFormEvents_FWD_DEFINED__ */


#ifndef __CActiveSmallForm_FWD_DEFINED__
#define __CActiveSmallForm_FWD_DEFINED__

#ifdef __cplusplus
typedef class CActiveSmallForm CActiveSmallForm;
#else
typedef struct CActiveSmallForm CActiveSmallForm;
#endif /* __cplusplus */

#endif 	/* __CActiveSmallForm_FWD_DEFINED__ */


#ifndef __IASExtendedControl_FWD_DEFINED__
#define __IASExtendedControl_FWD_DEFINED__
typedef interface IASExtendedControl IASExtendedControl;
#endif 	/* __IASExtendedControl_FWD_DEFINED__ */


#ifndef __ActiveSmallXObjectEvents_FWD_DEFINED__
#define __ActiveSmallXObjectEvents_FWD_DEFINED__
typedef interface ActiveSmallXObjectEvents ActiveSmallXObjectEvents;
#endif 	/* __ActiveSmallXObjectEvents_FWD_DEFINED__ */


#ifndef __CActiveSmallXObject_FWD_DEFINED__
#define __CActiveSmallXObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CActiveSmallXObject CActiveSmallXObject;
#else
typedef struct CActiveSmallXObject CActiveSmallXObject;
#endif /* __cplusplus */

#endif 	/* __CActiveSmallXObject_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ASFORM_LIBRARY_DEFINED__
#define __ASFORM_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ASFORM
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][version][uuid] */ 


typedef long OLE_XPOS_PIXELS;

typedef long OLE_YPOS_PIXELS;

typedef 
enum tagSCROLLSTYLE
    {	SCROLLSTYLE_NONE	= 0,
	SCROLLSTYLE_HORIZONTAL	= 1,
	SCROLLSTYLE_VERTICAL	= 2,
	SCROLLSTYLE_BOTH	= 3
    }	SCROLLSTYLE;

typedef 
enum tagDRAGSTATE
    {	DRAGSTATE_NONE	= 0,
	DRAGSTATE_ADD	= 1,
	DRAGSTATE_SELECT	= 2,
	DRAGSTATE_MOVE	= 3,
	DRAGSTATE_SIZE	= 4
    }	DRAGSTATE;


EXTERN_C const IID LIBID_ASFORM;

#ifndef __ActiveAPISet_DISPINTERFACE_DEFINED__
#define __ActiveAPISet_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ActiveAPISet
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][uuid] */ 



EXTERN_C const IID DIID_ActiveAPISet;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("2ECBC960-FF44-11cf-B8A5-A8AE00C10000")
    ActiveAPISet : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ActiveAPISetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ActiveAPISet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ActiveAPISet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ActiveAPISet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ActiveAPISet __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ActiveAPISet __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ActiveAPISet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ActiveAPISet __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ActiveAPISetVtbl;

    interface ActiveAPISet
    {
        CONST_VTBL struct ActiveAPISetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ActiveAPISet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ActiveAPISet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ActiveAPISet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ActiveAPISet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ActiveAPISet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ActiveAPISet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ActiveAPISet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ActiveAPISet_DISPINTERFACE_DEFINED__ */


#ifndef __IASControls_INTERFACE_DEFINED__
#define __IASControls_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IASControls
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IASControls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("2ECBC944-FF44-11cf-B8A5-A8AE00C10000")
    IASControls : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrClsid,
            /* [in] */ BSTR bstrName,
            /* [in] */ long nLeft,
            /* [in] */ long nTop,
            /* [in] */ long nWidth,
            /* [in] */ long nHeight,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IASControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IASControls __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IASControls __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IASControls __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IASControls __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IASControls __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IASControls __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IASControls __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IASControls __RPC_FAR * This,
            /* [in] */ BSTR bstrClsid,
            /* [in] */ BSTR bstrName,
            /* [in] */ long nLeft,
            /* [in] */ long nTop,
            /* [in] */ long nWidth,
            /* [in] */ long nHeight,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IASControls __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IASControls __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IASControls __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IASControls __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } IASControlsVtbl;

    interface IASControls
    {
        CONST_VTBL struct IASControlsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IASControls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IASControls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IASControls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IASControls_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IASControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IASControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IASControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IASControls_Add(This,bstrClsid,bstrName,nLeft,nTop,nWidth,nHeight,retval)	\
    (This)->lpVtbl -> Add(This,bstrClsid,bstrName,nLeft,nTop,nWidth,nHeight,retval)

#define IASControls_get_Count(This,retval)	\
    (This)->lpVtbl -> get_Count(This,retval)

#define IASControls_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)

#define IASControls_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define IASControls_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IASControls_Add_Proxy( 
    IASControls __RPC_FAR * This,
    /* [in] */ BSTR bstrClsid,
    /* [in] */ BSTR bstrName,
    /* [in] */ long nLeft,
    /* [in] */ long nTop,
    /* [in] */ long nWidth,
    /* [in] */ long nHeight,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IASControls_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASControls_get_Count_Proxy( 
    IASControls __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASControls_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASControls_get_Item_Proxy( 
    IASControls __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IASControls_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IASControls_get__NewEnum_Proxy( 
    IASControls __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IASControls_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IASControls_Remove_Proxy( 
    IASControls __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB IASControls_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IASControls_INTERFACE_DEFINED__ */


#ifndef __IASForm_INTERFACE_DEFINED__
#define __IASForm_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IASForm
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IASForm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("2ECBC941-FF44-11cf-B8A5-A8AE00C10000")
    IASForm : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR color) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderStyle( 
            /* [in] */ unsigned long style) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStyle( 
            /* [retval][out] */ unsigned long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR caption) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Controls( 
            /* [retval][out] */ IASControls __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DisabledScrollStyle( 
            /* [in] */ SCROLLSTYLE style) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DisabledScrollStyle( 
            /* [retval][out] */ SCROLLSTYLE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ OLE_COLOR color) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_hDC( 
            /* [retval][out] */ HDC __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long height) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ HWND __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long left) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Redraw( 
            /* [in] */ long redraw) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Redraw( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleHeight( 
            /* [in] */ long scaleheight) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleHeight( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleWidth( 
            /* [in] */ long scalewidth) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleWidth( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ScrollStyle( 
            /* [in] */ SCROLLSTYLE scrollstyle) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ScrollStyle( 
            /* [retval][out] */ SCROLLSTYLE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Selected( 
            /* [in] */ IUnknown __RPC_FAR *lpSelected) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Selected( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Focus( 
            /* [in] */ IUnknown __RPC_FAR *lpFocus) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Focus( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long top) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_UserMode( 
            /* [in] */ BOOL mode) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UserMode( 
            /* [retval][out] */ BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ViewportOrgX( 
            /* [in] */ long viewportorgx) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ViewportOrgX( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ViewportOrgY( 
            /* [in] */ long viewportorgy) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ViewportOrgY( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowExtX( 
            /* [in] */ long windowextx) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowExtX( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowExtY( 
            /* [in] */ long windowexty) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowExtY( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long width) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HandleEraseBkGnd( 
            /* [in] */ long width) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HandleEraseBkGnd( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ DWORD Style) = 0;
        
        virtual /* [id] */ void STDMETHODCALLTYPE FireViewChange( void) = 0;
        
        virtual /* [id] */ void STDMETHODCALLTYPE OutputDebugString( 
            BSTR sz) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveControl( 
            /* [in] */ LPUNKNOWN lpUnk,
            /* [in] */ LPCRECT lprc,
            /* [in] */ BOOL fUpdate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveControlToFront( 
            /* [in] */ LPUNKNOWN lpUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveControlToBack( 
            /* [in] */ LPUNKNOWN lpUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteControl( 
            /* [in] */ LPUNKNOWN lpUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ControlFromPoint( 
            /* [in] */ POINT pt,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *lplpUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ControlDispatchFromID( 
            /* [in] */ DWORD nID,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *lplpDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IASFormVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IASForm __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IASForm __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IASForm __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IASForm __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IASForm __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IASForm __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IASForm __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IASForm __RPC_FAR * This,
            /* [in] */ OLE_COLOR color);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BorderStyle )( 
            IASForm __RPC_FAR * This,
            /* [in] */ unsigned long style);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BorderStyle )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            IASForm __RPC_FAR * This,
            /* [in] */ BSTR caption);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Controls )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ IASControls __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisabledScrollStyle )( 
            IASForm __RPC_FAR * This,
            /* [in] */ SCROLLSTYLE style);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisabledScrollStyle )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ SCROLLSTYLE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ForeColor )( 
            IASForm __RPC_FAR * This,
            /* [in] */ OLE_COLOR color);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ForeColor )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hDC )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ HDC __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long height);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hWnd )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ HWND __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long left);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Redraw )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long redraw);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Redraw )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleHeight )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long scaleheight);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleHeight )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleWidth )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long scalewidth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleWidth )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScrollStyle )( 
            IASForm __RPC_FAR * This,
            /* [in] */ SCROLLSTYLE scrollstyle);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScrollStyle )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ SCROLLSTYLE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Selected )( 
            IASForm __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *lpSelected);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Selected )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Focus )( 
            IASForm __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *lpFocus);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Focus )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long top);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserMode )( 
            IASForm __RPC_FAR * This,
            /* [in] */ BOOL mode);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserMode )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ViewportOrgX )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long viewportorgx);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ViewportOrgX )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ViewportOrgY )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long viewportorgy);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ViewportOrgY )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowExtX )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long windowextx);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowExtX )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowExtY )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long windowexty);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowExtY )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long width);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HandleEraseBkGnd )( 
            IASForm __RPC_FAR * This,
            /* [in] */ long width);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HandleEraseBkGnd )( 
            IASForm __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IASForm __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IASForm __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IASForm __RPC_FAR * This,
            /* [in] */ DWORD Style);
        
        /* [id] */ void ( STDMETHODCALLTYPE __RPC_FAR *FireViewChange )( 
            IASForm __RPC_FAR * This);
        
        /* [id] */ void ( STDMETHODCALLTYPE __RPC_FAR *OutputDebugString )( 
            IASForm __RPC_FAR * This,
            BSTR sz);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveControl )( 
            IASForm __RPC_FAR * This,
            /* [in] */ LPUNKNOWN lpUnk,
            /* [in] */ LPCRECT lprc,
            /* [in] */ BOOL fUpdate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveControlToFront )( 
            IASForm __RPC_FAR * This,
            /* [in] */ LPUNKNOWN lpUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveControlToBack )( 
            IASForm __RPC_FAR * This,
            /* [in] */ LPUNKNOWN lpUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteControl )( 
            IASForm __RPC_FAR * This,
            /* [in] */ LPUNKNOWN lpUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlFromPoint )( 
            IASForm __RPC_FAR * This,
            /* [in] */ POINT pt,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *lplpUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlDispatchFromID )( 
            IASForm __RPC_FAR * This,
            /* [in] */ DWORD nID,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *lplpDisp);
        
        END_INTERFACE
    } IASFormVtbl;

    interface IASForm
    {
        CONST_VTBL struct IASFormVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IASForm_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IASForm_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IASForm_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IASForm_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IASForm_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IASForm_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IASForm_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IASForm_put_BackColor(This,color)	\
    (This)->lpVtbl -> put_BackColor(This,color)

#define IASForm_get_BackColor(This,retval)	\
    (This)->lpVtbl -> get_BackColor(This,retval)

#define IASForm_put_BorderStyle(This,style)	\
    (This)->lpVtbl -> put_BorderStyle(This,style)

#define IASForm_get_BorderStyle(This,retval)	\
    (This)->lpVtbl -> get_BorderStyle(This,retval)

#define IASForm_put_Caption(This,caption)	\
    (This)->lpVtbl -> put_Caption(This,caption)

#define IASForm_get_Caption(This,retval)	\
    (This)->lpVtbl -> get_Caption(This,retval)

#define IASForm_get_Controls(This,retval)	\
    (This)->lpVtbl -> get_Controls(This,retval)

#define IASForm_put_DisabledScrollStyle(This,style)	\
    (This)->lpVtbl -> put_DisabledScrollStyle(This,style)

#define IASForm_get_DisabledScrollStyle(This,retval)	\
    (This)->lpVtbl -> get_DisabledScrollStyle(This,retval)

#define IASForm_put_ForeColor(This,color)	\
    (This)->lpVtbl -> put_ForeColor(This,color)

#define IASForm_get_ForeColor(This,retval)	\
    (This)->lpVtbl -> get_ForeColor(This,retval)

#define IASForm_get_hDC(This,retval)	\
    (This)->lpVtbl -> get_hDC(This,retval)

#define IASForm_put_Height(This,height)	\
    (This)->lpVtbl -> put_Height(This,height)

#define IASForm_get_Height(This,retval)	\
    (This)->lpVtbl -> get_Height(This,retval)

#define IASForm_get_hWnd(This,retval)	\
    (This)->lpVtbl -> get_hWnd(This,retval)

#define IASForm_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IASForm_put_Left(This,left)	\
    (This)->lpVtbl -> put_Left(This,left)

#define IASForm_get_Left(This,retval)	\
    (This)->lpVtbl -> get_Left(This,retval)

#define IASForm_put_Redraw(This,redraw)	\
    (This)->lpVtbl -> put_Redraw(This,redraw)

#define IASForm_get_Redraw(This,retval)	\
    (This)->lpVtbl -> get_Redraw(This,retval)

#define IASForm_put_ScaleHeight(This,scaleheight)	\
    (This)->lpVtbl -> put_ScaleHeight(This,scaleheight)

#define IASForm_get_ScaleHeight(This,retval)	\
    (This)->lpVtbl -> get_ScaleHeight(This,retval)

#define IASForm_put_ScaleWidth(This,scalewidth)	\
    (This)->lpVtbl -> put_ScaleWidth(This,scalewidth)

#define IASForm_get_ScaleWidth(This,retval)	\
    (This)->lpVtbl -> get_ScaleWidth(This,retval)

#define IASForm_put_ScrollStyle(This,scrollstyle)	\
    (This)->lpVtbl -> put_ScrollStyle(This,scrollstyle)

#define IASForm_get_ScrollStyle(This,retval)	\
    (This)->lpVtbl -> get_ScrollStyle(This,retval)

#define IASForm_put_Selected(This,lpSelected)	\
    (This)->lpVtbl -> put_Selected(This,lpSelected)

#define IASForm_get_Selected(This,retval)	\
    (This)->lpVtbl -> get_Selected(This,retval)

#define IASForm_put_Focus(This,lpFocus)	\
    (This)->lpVtbl -> put_Focus(This,lpFocus)

#define IASForm_get_Focus(This,retval)	\
    (This)->lpVtbl -> get_Focus(This,retval)

#define IASForm_put_Top(This,top)	\
    (This)->lpVtbl -> put_Top(This,top)

#define IASForm_get_Top(This,retval)	\
    (This)->lpVtbl -> get_Top(This,retval)

#define IASForm_put_UserMode(This,mode)	\
    (This)->lpVtbl -> put_UserMode(This,mode)

#define IASForm_get_UserMode(This,retval)	\
    (This)->lpVtbl -> get_UserMode(This,retval)

#define IASForm_put_ViewportOrgX(This,viewportorgx)	\
    (This)->lpVtbl -> put_ViewportOrgX(This,viewportorgx)

#define IASForm_get_ViewportOrgX(This,retval)	\
    (This)->lpVtbl -> get_ViewportOrgX(This,retval)

#define IASForm_put_ViewportOrgY(This,viewportorgy)	\
    (This)->lpVtbl -> put_ViewportOrgY(This,viewportorgy)

#define IASForm_get_ViewportOrgY(This,retval)	\
    (This)->lpVtbl -> get_ViewportOrgY(This,retval)

#define IASForm_put_WindowExtX(This,windowextx)	\
    (This)->lpVtbl -> put_WindowExtX(This,windowextx)

#define IASForm_get_WindowExtX(This,retval)	\
    (This)->lpVtbl -> get_WindowExtX(This,retval)

#define IASForm_put_WindowExtY(This,windowexty)	\
    (This)->lpVtbl -> put_WindowExtY(This,windowexty)

#define IASForm_get_WindowExtY(This,retval)	\
    (This)->lpVtbl -> get_WindowExtY(This,retval)

#define IASForm_put_Width(This,width)	\
    (This)->lpVtbl -> put_Width(This,width)

#define IASForm_get_Width(This,retval)	\
    (This)->lpVtbl -> get_Width(This,retval)

#define IASForm_put_HandleEraseBkGnd(This,width)	\
    (This)->lpVtbl -> put_HandleEraseBkGnd(This,width)

#define IASForm_get_HandleEraseBkGnd(This,retval)	\
    (This)->lpVtbl -> get_HandleEraseBkGnd(This,retval)

#define IASForm_Hide(This)	\
    (This)->lpVtbl -> Hide(This)

#define IASForm_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IASForm_Show(This,Style)	\
    (This)->lpVtbl -> Show(This,Style)

#define IASForm_FireViewChange(This)	\
    (This)->lpVtbl -> FireViewChange(This)

#define IASForm_OutputDebugString(This,sz)	\
    (This)->lpVtbl -> OutputDebugString(This,sz)

#define IASForm_MoveControl(This,lpUnk,lprc,fUpdate)	\
    (This)->lpVtbl -> MoveControl(This,lpUnk,lprc,fUpdate)

#define IASForm_MoveControlToFront(This,lpUnk)	\
    (This)->lpVtbl -> MoveControlToFront(This,lpUnk)

#define IASForm_MoveControlToBack(This,lpUnk)	\
    (This)->lpVtbl -> MoveControlToBack(This,lpUnk)

#define IASForm_DeleteControl(This,lpUnk)	\
    (This)->lpVtbl -> DeleteControl(This,lpUnk)

#define IASForm_ControlFromPoint(This,pt,lplpUnk)	\
    (This)->lpVtbl -> ControlFromPoint(This,pt,lplpUnk)

#define IASForm_ControlDispatchFromID(This,nID,lplpDisp)	\
    (This)->lpVtbl -> ControlDispatchFromID(This,nID,lplpDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_BackColor_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ OLE_COLOR color);


void __RPC_STUB IASForm_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_BackColor_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *retval);


void __RPC_STUB IASForm_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_BorderStyle_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ unsigned long style);


void __RPC_STUB IASForm_put_BorderStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_BorderStyle_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ unsigned long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_BorderStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Caption_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ BSTR caption);


void __RPC_STUB IASForm_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Caption_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Controls_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ IASControls __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IASForm_get_Controls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_DisabledScrollStyle_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ SCROLLSTYLE style);


void __RPC_STUB IASForm_put_DisabledScrollStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_DisabledScrollStyle_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ SCROLLSTYLE __RPC_FAR *retval);


void __RPC_STUB IASForm_get_DisabledScrollStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_ForeColor_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ OLE_COLOR color);


void __RPC_STUB IASForm_put_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_ForeColor_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *retval);


void __RPC_STUB IASForm_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_hDC_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ HDC __RPC_FAR *retval);


void __RPC_STUB IASForm_get_hDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Height_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long height);


void __RPC_STUB IASForm_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Height_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_hWnd_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ HWND __RPC_FAR *retval);


void __RPC_STUB IASForm_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Name_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Left_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long left);


void __RPC_STUB IASForm_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Left_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Redraw_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long redraw);


void __RPC_STUB IASForm_put_Redraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Redraw_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Redraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_ScaleHeight_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long scaleheight);


void __RPC_STUB IASForm_put_ScaleHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_ScaleHeight_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_ScaleHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_ScaleWidth_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long scalewidth);


void __RPC_STUB IASForm_put_ScaleWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_ScaleWidth_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_ScaleWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_ScrollStyle_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ SCROLLSTYLE scrollstyle);


void __RPC_STUB IASForm_put_ScrollStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_ScrollStyle_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ SCROLLSTYLE __RPC_FAR *retval);


void __RPC_STUB IASForm_get_ScrollStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Selected_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *lpSelected);


void __RPC_STUB IASForm_put_Selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Selected_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IASForm_get_Selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Focus_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *lpFocus);


void __RPC_STUB IASForm_put_Focus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Focus_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IASForm_get_Focus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Top_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long top);


void __RPC_STUB IASForm_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Top_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_UserMode_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ BOOL mode);


void __RPC_STUB IASForm_put_UserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_UserMode_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *retval);


void __RPC_STUB IASForm_get_UserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_ViewportOrgX_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long viewportorgx);


void __RPC_STUB IASForm_put_ViewportOrgX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_ViewportOrgX_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_ViewportOrgX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_ViewportOrgY_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long viewportorgy);


void __RPC_STUB IASForm_put_ViewportOrgY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_ViewportOrgY_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_ViewportOrgY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_WindowExtX_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long windowextx);


void __RPC_STUB IASForm_put_WindowExtX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_WindowExtX_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_WindowExtX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_WindowExtY_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long windowexty);


void __RPC_STUB IASForm_put_WindowExtY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_WindowExtY_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_WindowExtY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_Width_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long width);


void __RPC_STUB IASForm_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_Width_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASForm_put_HandleEraseBkGnd_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ long width);


void __RPC_STUB IASForm_put_HandleEraseBkGnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASForm_get_HandleEraseBkGnd_Proxy( 
    IASForm __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IASForm_get_HandleEraseBkGnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IASForm_Hide_Proxy( 
    IASForm __RPC_FAR * This);


void __RPC_STUB IASForm_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IASForm_Refresh_Proxy( 
    IASForm __RPC_FAR * This);


void __RPC_STUB IASForm_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IASForm_Show_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ DWORD Style);


void __RPC_STUB IASForm_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ void STDMETHODCALLTYPE IASForm_FireViewChange_Proxy( 
    IASForm __RPC_FAR * This);


void __RPC_STUB IASForm_FireViewChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ void STDMETHODCALLTYPE IASForm_OutputDebugString_Proxy( 
    IASForm __RPC_FAR * This,
    BSTR sz);


void __RPC_STUB IASForm_OutputDebugString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IASForm_MoveControl_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ LPUNKNOWN lpUnk,
    /* [in] */ LPCRECT lprc,
    /* [in] */ BOOL fUpdate);


void __RPC_STUB IASForm_MoveControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IASForm_MoveControlToFront_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ LPUNKNOWN lpUnk);


void __RPC_STUB IASForm_MoveControlToFront_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IASForm_MoveControlToBack_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ LPUNKNOWN lpUnk);


void __RPC_STUB IASForm_MoveControlToBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IASForm_DeleteControl_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ LPUNKNOWN lpUnk);


void __RPC_STUB IASForm_DeleteControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IASForm_ControlFromPoint_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ POINT pt,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *lplpUnk);


void __RPC_STUB IASForm_ControlFromPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IASForm_ControlDispatchFromID_Proxy( 
    IASForm __RPC_FAR * This,
    /* [in] */ DWORD nID,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *lplpDisp);


void __RPC_STUB IASForm_ControlDispatchFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IASForm_INTERFACE_DEFINED__ */


#ifndef __ActiveSmallFormEvents_DISPINTERFACE_DEFINED__
#define __ActiveSmallFormEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ActiveSmallFormEvents
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][uuid] */ 



EXTERN_C const IID DIID_ActiveSmallFormEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("2ECBC942-FF44-11cf-B8A5-A8AE00C10000")
    ActiveSmallFormEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ActiveSmallFormEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ActiveSmallFormEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ActiveSmallFormEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ActiveSmallFormEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ActiveSmallFormEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ActiveSmallFormEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ActiveSmallFormEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ActiveSmallFormEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ActiveSmallFormEventsVtbl;

    interface ActiveSmallFormEvents
    {
        CONST_VTBL struct ActiveSmallFormEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ActiveSmallFormEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ActiveSmallFormEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ActiveSmallFormEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ActiveSmallFormEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ActiveSmallFormEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ActiveSmallFormEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ActiveSmallFormEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ActiveSmallFormEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CActiveSmallForm;

#ifdef __cplusplus

class DECLSPEC_UUID("2ECBC943-FF44-11cf-B8A5-A8AE00C10000")
CActiveSmallForm;
#endif

#ifndef __IASExtendedControl_INTERFACE_DEFINED__
#define __IASExtendedControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IASExtendedControl
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IASExtendedControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("2ECBC954-FF44-11cf-B8A5-A8AE00C10000")
    IASExtendedControl : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *pval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *pval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ HWND __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pname) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *pval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Parent( 
            /* [in] */ IUnknown __RPC_FAR *lpUnk) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *lplpUnk) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TabIndex( 
            /* [in] */ long val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TabIndex( 
            /* [retval][out] */ long __RPC_FAR *pval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TabStop( 
            /* [in] */ BOOL val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TabStop( 
            /* [retval][out] */ BOOL __RPC_FAR *pval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ long val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ long __RPC_FAR *pval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *pval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ BOOL val) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ BOOL __RPC_FAR *pval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IASExtendedControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IASExtendedControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IASExtendedControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IASExtendedControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ long val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ long val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hWnd )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ HWND __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ BSTR name);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pname);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ long val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *lpUnk);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *lplpUnk);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TabIndex )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ long val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TabIndex )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TabStop )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ BOOL val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TabStop )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ long val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ long val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IASExtendedControl __RPC_FAR * This,
            /* [in] */ BOOL val);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IASExtendedControl __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pval);
        
        END_INTERFACE
    } IASExtendedControlVtbl;

    interface IASExtendedControl
    {
        CONST_VTBL struct IASExtendedControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IASExtendedControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IASExtendedControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IASExtendedControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IASExtendedControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IASExtendedControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IASExtendedControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IASExtendedControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IASExtendedControl_put_Left(This,val)	\
    (This)->lpVtbl -> put_Left(This,val)

#define IASExtendedControl_get_Left(This,pval)	\
    (This)->lpVtbl -> get_Left(This,pval)

#define IASExtendedControl_put_Height(This,val)	\
    (This)->lpVtbl -> put_Height(This,val)

#define IASExtendedControl_get_Height(This,pval)	\
    (This)->lpVtbl -> get_Height(This,pval)

#define IASExtendedControl_get_hWnd(This,retval)	\
    (This)->lpVtbl -> get_hWnd(This,retval)

#define IASExtendedControl_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IASExtendedControl_get_Name(This,pname)	\
    (This)->lpVtbl -> get_Name(This,pname)

#define IASExtendedControl_put_Width(This,val)	\
    (This)->lpVtbl -> put_Width(This,val)

#define IASExtendedControl_get_Width(This,pval)	\
    (This)->lpVtbl -> get_Width(This,pval)

#define IASExtendedControl_put_Parent(This,lpUnk)	\
    (This)->lpVtbl -> put_Parent(This,lpUnk)

#define IASExtendedControl_get_Parent(This,lplpUnk)	\
    (This)->lpVtbl -> get_Parent(This,lplpUnk)

#define IASExtendedControl_put_TabIndex(This,val)	\
    (This)->lpVtbl -> put_TabIndex(This,val)

#define IASExtendedControl_get_TabIndex(This,pval)	\
    (This)->lpVtbl -> get_TabIndex(This,pval)

#define IASExtendedControl_put_TabStop(This,val)	\
    (This)->lpVtbl -> put_TabStop(This,val)

#define IASExtendedControl_get_TabStop(This,pval)	\
    (This)->lpVtbl -> get_TabStop(This,pval)

#define IASExtendedControl_put_Tag(This,val)	\
    (This)->lpVtbl -> put_Tag(This,val)

#define IASExtendedControl_get_Tag(This,pval)	\
    (This)->lpVtbl -> get_Tag(This,pval)

#define IASExtendedControl_put_Top(This,val)	\
    (This)->lpVtbl -> put_Top(This,val)

#define IASExtendedControl_get_Top(This,pval)	\
    (This)->lpVtbl -> get_Top(This,pval)

#define IASExtendedControl_put_Visible(This,val)	\
    (This)->lpVtbl -> put_Visible(This,val)

#define IASExtendedControl_get_Visible(This,pval)	\
    (This)->lpVtbl -> get_Visible(This,pval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Left_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ long val);


void __RPC_STUB IASExtendedControl_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Left_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Height_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ long val);


void __RPC_STUB IASExtendedControl_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Height_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_hWnd_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ HWND __RPC_FAR *retval);


void __RPC_STUB IASExtendedControl_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Name_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ BSTR name);


void __RPC_STUB IASExtendedControl_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Name_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pname);


void __RPC_STUB IASExtendedControl_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Width_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ long val);


void __RPC_STUB IASExtendedControl_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Width_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Parent_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *lpUnk);


void __RPC_STUB IASExtendedControl_put_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Parent_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *lplpUnk);


void __RPC_STUB IASExtendedControl_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_TabIndex_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ long val);


void __RPC_STUB IASExtendedControl_put_TabIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_TabIndex_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_TabIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_TabStop_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ BOOL val);


void __RPC_STUB IASExtendedControl_put_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_TabStop_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Tag_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ long val);


void __RPC_STUB IASExtendedControl_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Tag_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Top_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ long val);


void __RPC_STUB IASExtendedControl_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Top_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_put_Visible_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [in] */ BOOL val);


void __RPC_STUB IASExtendedControl_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IASExtendedControl_get_Visible_Proxy( 
    IASExtendedControl __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pval);


void __RPC_STUB IASExtendedControl_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IASExtendedControl_INTERFACE_DEFINED__ */


#ifndef __ActiveSmallXObjectEvents_DISPINTERFACE_DEFINED__
#define __ActiveSmallXObjectEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ActiveSmallXObjectEvents
 * at Sat Sep 19 22:28:26 1998
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][uuid] */ 



EXTERN_C const IID DIID_ActiveSmallXObjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("2ECBC955-FF44-11cf-B8A5-A8AE00C10000")
    ActiveSmallXObjectEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ActiveSmallXObjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ActiveSmallXObjectEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ActiveSmallXObjectEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ActiveSmallXObjectEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ActiveSmallXObjectEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ActiveSmallXObjectEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ActiveSmallXObjectEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ActiveSmallXObjectEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ActiveSmallXObjectEventsVtbl;

    interface ActiveSmallXObjectEvents
    {
        CONST_VTBL struct ActiveSmallXObjectEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ActiveSmallXObjectEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ActiveSmallXObjectEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ActiveSmallXObjectEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ActiveSmallXObjectEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ActiveSmallXObjectEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ActiveSmallXObjectEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ActiveSmallXObjectEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ActiveSmallXObjectEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CActiveSmallXObject;

#ifdef __cplusplus

class DECLSPEC_UUID("2ECBC956-FF44-11cf-B8A5-A8AE00C10000")
CActiveSmallXObject;
#endif
#endif /* __ASFORM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
