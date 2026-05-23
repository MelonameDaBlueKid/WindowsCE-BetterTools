
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Tue May 06 19:04:18 2003
 */
/* Compiler settings for .\webvw.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __webvw_h__
#define __webvw_h__

/* Forward Declarations */ 

#ifndef __IBrowser_FWD_DEFINED__
#define __IBrowser_FWD_DEFINED__
typedef interface IBrowser IBrowser;
#endif 	/* __IBrowser_FWD_DEFINED__ */


#ifndef __IBrowser2_FWD_DEFINED__
#define __IBrowser2_FWD_DEFINED__
typedef interface IBrowser2 IBrowser2;
#endif 	/* __IBrowser2_FWD_DEFINED__ */


#ifndef __IBrowser3_FWD_DEFINED__
#define __IBrowser3_FWD_DEFINED__
typedef interface IBrowser3 IBrowser3;
#endif 	/* __IBrowser3_FWD_DEFINED__ */


#ifndef ___DPIEWebBrowserEvents2_FWD_DEFINED__
#define ___DPIEWebBrowserEvents2_FWD_DEFINED__
typedef interface _DPIEWebBrowserEvents2 _DPIEWebBrowserEvents2;
#endif 	/* ___DPIEWebBrowserEvents2_FWD_DEFINED__ */


#ifndef __Browser_FWD_DEFINED__
#define __Browser_FWD_DEFINED__

#ifdef __cplusplus
typedef class Browser Browser;
#else
typedef struct Browser Browser;
#endif /* __cplusplus */

#endif 	/* __Browser_FWD_DEFINED__ */


#ifndef __IPIEOmNavigator_FWD_DEFINED__
#define __IPIEOmNavigator_FWD_DEFINED__
typedef interface IPIEOmNavigator IPIEOmNavigator;
#endif 	/* __IPIEOmNavigator_FWD_DEFINED__ */


#ifndef __IPIEOmHistory_FWD_DEFINED__
#define __IPIEOmHistory_FWD_DEFINED__
typedef interface IPIEOmHistory IPIEOmHistory;
#endif 	/* __IPIEOmHistory_FWD_DEFINED__ */


#ifndef __IPIEHTMLElementCollection_FWD_DEFINED__
#define __IPIEHTMLElementCollection_FWD_DEFINED__
typedef interface IPIEHTMLElementCollection IPIEHTMLElementCollection;
#endif 	/* __IPIEHTMLElementCollection_FWD_DEFINED__ */


#ifndef __IPIEHTMLFormElementCollection_FWD_DEFINED__
#define __IPIEHTMLFormElementCollection_FWD_DEFINED__
typedef interface IPIEHTMLFormElementCollection IPIEHTMLFormElementCollection;
#endif 	/* __IPIEHTMLFormElementCollection_FWD_DEFINED__ */


#ifndef __IPIEHTMLLocation_FWD_DEFINED__
#define __IPIEHTMLLocation_FWD_DEFINED__
typedef interface IPIEHTMLLocation IPIEHTMLLocation;
#endif 	/* __IPIEHTMLLocation_FWD_DEFINED__ */


#ifndef __IPIEHTMLDocument_FWD_DEFINED__
#define __IPIEHTMLDocument_FWD_DEFINED__
typedef interface IPIEHTMLDocument IPIEHTMLDocument;
#endif 	/* __IPIEHTMLDocument_FWD_DEFINED__ */


#ifndef __IPIEHTMLDocument2_FWD_DEFINED__
#define __IPIEHTMLDocument2_FWD_DEFINED__
typedef interface IPIEHTMLDocument2 IPIEHTMLDocument2;
#endif 	/* __IPIEHTMLDocument2_FWD_DEFINED__ */


#ifndef __IPIEHTMLFrameSetElement_FWD_DEFINED__
#define __IPIEHTMLFrameSetElement_FWD_DEFINED__
typedef interface IPIEHTMLFrameSetElement IPIEHTMLFrameSetElement;
#endif 	/* __IPIEHTMLFrameSetElement_FWD_DEFINED__ */


#ifndef __PIEHTMLFrameSetElementEvents_FWD_DEFINED__
#define __PIEHTMLFrameSetElementEvents_FWD_DEFINED__
typedef interface PIEHTMLFrameSetElementEvents PIEHTMLFrameSetElementEvents;
#endif 	/* __PIEHTMLFrameSetElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLFrameSetElement_FWD_DEFINED__
#define __PIEHTMLFrameSetElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLFrameSetElement PIEHTMLFrameSetElement;
#else
typedef struct PIEHTMLFrameSetElement PIEHTMLFrameSetElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLFrameSetElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLFrameElement_FWD_DEFINED__
#define __IPIEHTMLFrameElement_FWD_DEFINED__
typedef interface IPIEHTMLFrameElement IPIEHTMLFrameElement;
#endif 	/* __IPIEHTMLFrameElement_FWD_DEFINED__ */


#ifndef __PIEHTMLFrameElement_FWD_DEFINED__
#define __PIEHTMLFrameElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLFrameElement PIEHTMLFrameElement;
#else
typedef struct PIEHTMLFrameElement PIEHTMLFrameElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLFrameElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLScreen_FWD_DEFINED__
#define __IPIEHTMLScreen_FWD_DEFINED__
typedef interface IPIEHTMLScreen IPIEHTMLScreen;
#endif 	/* __IPIEHTMLScreen_FWD_DEFINED__ */


#ifndef __IPIEHTMLImgElement_FWD_DEFINED__
#define __IPIEHTMLImgElement_FWD_DEFINED__
typedef interface IPIEHTMLImgElement IPIEHTMLImgElement;
#endif 	/* __IPIEHTMLImgElement_FWD_DEFINED__ */


#ifndef __PIEHTMLImgElement_FWD_DEFINED__
#define __PIEHTMLImgElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLImgElement PIEHTMLImgElement;
#else
typedef struct PIEHTMLImgElement PIEHTMLImgElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLImgElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLImageElementFactory_FWD_DEFINED__
#define __IPIEHTMLImageElementFactory_FWD_DEFINED__
typedef interface IPIEHTMLImageElementFactory IPIEHTMLImageElementFactory;
#endif 	/* __IPIEHTMLImageElementFactory_FWD_DEFINED__ */


#ifndef __IPIEHTMLOptionElement_FWD_DEFINED__
#define __IPIEHTMLOptionElement_FWD_DEFINED__
typedef interface IPIEHTMLOptionElement IPIEHTMLOptionElement;
#endif 	/* __IPIEHTMLOptionElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLOptionElementFactory_FWD_DEFINED__
#define __IPIEHTMLOptionElementFactory_FWD_DEFINED__
typedef interface IPIEHTMLOptionElementFactory IPIEHTMLOptionElementFactory;
#endif 	/* __IPIEHTMLOptionElementFactory_FWD_DEFINED__ */


#ifndef __IPIEHTMLWindow_FWD_DEFINED__
#define __IPIEHTMLWindow_FWD_DEFINED__
typedef interface IPIEHTMLWindow IPIEHTMLWindow;
#endif 	/* __IPIEHTMLWindow_FWD_DEFINED__ */


#ifndef __IPIEHTMLWindow2_FWD_DEFINED__
#define __IPIEHTMLWindow2_FWD_DEFINED__
typedef interface IPIEHTMLWindow2 IPIEHTMLWindow2;
#endif 	/* __IPIEHTMLWindow2_FWD_DEFINED__ */


#ifndef __PIEHTMLWindowEvents_FWD_DEFINED__
#define __PIEHTMLWindowEvents_FWD_DEFINED__
typedef interface PIEHTMLWindowEvents PIEHTMLWindowEvents;
#endif 	/* __PIEHTMLWindowEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLWindow_FWD_DEFINED__
#define __PIEHTMLWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLWindow PIEHTMLWindow;
#else
typedef struct PIEHTMLWindow PIEHTMLWindow;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLWindow_FWD_DEFINED__ */


#ifndef __IPIEHTMLAnchorElement_FWD_DEFINED__
#define __IPIEHTMLAnchorElement_FWD_DEFINED__
typedef interface IPIEHTMLAnchorElement IPIEHTMLAnchorElement;
#endif 	/* __IPIEHTMLAnchorElement_FWD_DEFINED__ */


#ifndef __PIEHTMLAnchorElementEvents_FWD_DEFINED__
#define __PIEHTMLAnchorElementEvents_FWD_DEFINED__
typedef interface PIEHTMLAnchorElementEvents PIEHTMLAnchorElementEvents;
#endif 	/* __PIEHTMLAnchorElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLAnchorElement_FWD_DEFINED__
#define __PIEHTMLAnchorElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLAnchorElement PIEHTMLAnchorElement;
#else
typedef struct PIEHTMLAnchorElement PIEHTMLAnchorElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLAnchorElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLFormElement_FWD_DEFINED__
#define __IPIEHTMLFormElement_FWD_DEFINED__
typedef interface IPIEHTMLFormElement IPIEHTMLFormElement;
#endif 	/* __IPIEHTMLFormElement_FWD_DEFINED__ */


#ifndef __PIEHTMLFormElementEvents_FWD_DEFINED__
#define __PIEHTMLFormElementEvents_FWD_DEFINED__
typedef interface PIEHTMLFormElementEvents PIEHTMLFormElementEvents;
#endif 	/* __PIEHTMLFormElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLFormElement_FWD_DEFINED__
#define __PIEHTMLFormElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLFormElement PIEHTMLFormElement;
#else
typedef struct PIEHTMLFormElement PIEHTMLFormElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLFormElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLControlElement_FWD_DEFINED__
#define __IPIEHTMLControlElement_FWD_DEFINED__
typedef interface IPIEHTMLControlElement IPIEHTMLControlElement;
#endif 	/* __IPIEHTMLControlElement_FWD_DEFINED__ */


#ifndef __PIEHTMLControlElement_FWD_DEFINED__
#define __PIEHTMLControlElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLControlElement PIEHTMLControlElement;
#else
typedef struct PIEHTMLControlElement PIEHTMLControlElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLControlElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLInputButtonElement_FWD_DEFINED__
#define __IPIEHTMLInputButtonElement_FWD_DEFINED__
typedef interface IPIEHTMLInputButtonElement IPIEHTMLInputButtonElement;
#endif 	/* __IPIEHTMLInputButtonElement_FWD_DEFINED__ */


#ifndef __PIEHTMLInputButtonElementEvents_FWD_DEFINED__
#define __PIEHTMLInputButtonElementEvents_FWD_DEFINED__
typedef interface PIEHTMLInputButtonElementEvents PIEHTMLInputButtonElementEvents;
#endif 	/* __PIEHTMLInputButtonElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLInputButtonElement_FWD_DEFINED__
#define __PIEHTMLInputButtonElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLInputButtonElement PIEHTMLInputButtonElement;
#else
typedef struct PIEHTMLInputButtonElement PIEHTMLInputButtonElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLInputButtonElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLOptionButtonElement_FWD_DEFINED__
#define __IPIEHTMLOptionButtonElement_FWD_DEFINED__
typedef interface IPIEHTMLOptionButtonElement IPIEHTMLOptionButtonElement;
#endif 	/* __IPIEHTMLOptionButtonElement_FWD_DEFINED__ */


#ifndef __PIEHTMLOptionButtonElementEvents_FWD_DEFINED__
#define __PIEHTMLOptionButtonElementEvents_FWD_DEFINED__
typedef interface PIEHTMLOptionButtonElementEvents PIEHTMLOptionButtonElementEvents;
#endif 	/* __PIEHTMLOptionButtonElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLOptionButtonElement_FWD_DEFINED__
#define __PIEHTMLOptionButtonElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLOptionButtonElement PIEHTMLOptionButtonElement;
#else
typedef struct PIEHTMLOptionButtonElement PIEHTMLOptionButtonElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLOptionButtonElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLSelectElement_FWD_DEFINED__
#define __IPIEHTMLSelectElement_FWD_DEFINED__
typedef interface IPIEHTMLSelectElement IPIEHTMLSelectElement;
#endif 	/* __IPIEHTMLSelectElement_FWD_DEFINED__ */


#ifndef __PIEHTMLSelectElementEvents_FWD_DEFINED__
#define __PIEHTMLSelectElementEvents_FWD_DEFINED__
typedef interface PIEHTMLSelectElementEvents PIEHTMLSelectElementEvents;
#endif 	/* __PIEHTMLSelectElementEvents_FWD_DEFINED__ */


#ifndef __IPIEHTMLSelectElement2_FWD_DEFINED__
#define __IPIEHTMLSelectElement2_FWD_DEFINED__
typedef interface IPIEHTMLSelectElement2 IPIEHTMLSelectElement2;
#endif 	/* __IPIEHTMLSelectElement2_FWD_DEFINED__ */


#ifndef __PIEHTMLSelectElement_FWD_DEFINED__
#define __PIEHTMLSelectElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLSelectElement PIEHTMLSelectElement;
#else
typedef struct PIEHTMLSelectElement PIEHTMLSelectElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLSelectElement_FWD_DEFINED__ */


#ifndef __PIEHTMLOptionElement_FWD_DEFINED__
#define __PIEHTMLOptionElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLOptionElement PIEHTMLOptionElement;
#else
typedef struct PIEHTMLOptionElement PIEHTMLOptionElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLOptionElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLInputTextElement_FWD_DEFINED__
#define __IPIEHTMLInputTextElement_FWD_DEFINED__
typedef interface IPIEHTMLInputTextElement IPIEHTMLInputTextElement;
#endif 	/* __IPIEHTMLInputTextElement_FWD_DEFINED__ */


#ifndef __PIEHTMLInputTextElementEvents_FWD_DEFINED__
#define __PIEHTMLInputTextElementEvents_FWD_DEFINED__
typedef interface PIEHTMLInputTextElementEvents PIEHTMLInputTextElementEvents;
#endif 	/* __PIEHTMLInputTextElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLInputTextElement_FWD_DEFINED__
#define __PIEHTMLInputTextElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLInputTextElement PIEHTMLInputTextElement;
#else
typedef struct PIEHTMLInputTextElement PIEHTMLInputTextElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLInputTextElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLTextAreaElement_FWD_DEFINED__
#define __IPIEHTMLTextAreaElement_FWD_DEFINED__
typedef interface IPIEHTMLTextAreaElement IPIEHTMLTextAreaElement;
#endif 	/* __IPIEHTMLTextAreaElement_FWD_DEFINED__ */


#ifndef __PIEHTMLTextAreaElementEvents_FWD_DEFINED__
#define __PIEHTMLTextAreaElementEvents_FWD_DEFINED__
typedef interface PIEHTMLTextAreaElementEvents PIEHTMLTextAreaElementEvents;
#endif 	/* __PIEHTMLTextAreaElementEvents_FWD_DEFINED__ */


#ifndef __PIEHTMLTextAreaElement_FWD_DEFINED__
#define __PIEHTMLTextAreaElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLTextAreaElement PIEHTMLTextAreaElement;
#else
typedef struct PIEHTMLTextAreaElement PIEHTMLTextAreaElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLTextAreaElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLInputHiddenElement_FWD_DEFINED__
#define __IPIEHTMLInputHiddenElement_FWD_DEFINED__
typedef interface IPIEHTMLInputHiddenElement IPIEHTMLInputHiddenElement;
#endif 	/* __IPIEHTMLInputHiddenElement_FWD_DEFINED__ */


#ifndef __PIEHTMLInputHiddenElement_FWD_DEFINED__
#define __PIEHTMLInputHiddenElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLInputHiddenElement PIEHTMLInputHiddenElement;
#else
typedef struct PIEHTMLInputHiddenElement PIEHTMLInputHiddenElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLInputHiddenElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLElement_FWD_DEFINED__
#define __IPIEHTMLElement_FWD_DEFINED__
typedef interface IPIEHTMLElement IPIEHTMLElement;
#endif 	/* __IPIEHTMLElement_FWD_DEFINED__ */


#ifndef __PIEHTMLElement_FWD_DEFINED__
#define __PIEHTMLElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLElement PIEHTMLElement;
#else
typedef struct PIEHTMLElement PIEHTMLElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLDivElement_FWD_DEFINED__
#define __IPIEHTMLDivElement_FWD_DEFINED__
typedef interface IPIEHTMLDivElement IPIEHTMLDivElement;
#endif 	/* __IPIEHTMLDivElement_FWD_DEFINED__ */


#ifndef __PIEHTMLDivElement_FWD_DEFINED__
#define __PIEHTMLDivElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLDivElement PIEHTMLDivElement;
#else
typedef struct PIEHTMLDivElement PIEHTMLDivElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLDivElement_FWD_DEFINED__ */


#ifndef __IPIEHTMLSpanElement_FWD_DEFINED__
#define __IPIEHTMLSpanElement_FWD_DEFINED__
typedef interface IPIEHTMLSpanElement IPIEHTMLSpanElement;
#endif 	/* __IPIEHTMLSpanElement_FWD_DEFINED__ */


#ifndef __PIEHTMLSpanElement_FWD_DEFINED__
#define __PIEHTMLSpanElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIEHTMLSpanElement PIEHTMLSpanElement;
#else
typedef struct PIEHTMLSpanElement PIEHTMLSpanElement;
#endif /* __cplusplus */

#endif 	/* __PIEHTMLSpanElement_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"
#include "urlmon.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_webvw_0000 */
/* [local] */ 

#pragma once
#pragma once


extern RPC_IF_HANDLE __MIDL_itf_webvw_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_webvw_0000_v0_0_s_ifspec;

#ifndef __IBrowser_INTERFACE_DEFINED__
#define __IBrowser_INTERFACE_DEFINED__

/* interface IBrowser */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("698E3FC9-70C3-11D0-81E8-00A0C90AD20A")
    IBrowser : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE navigate( 
            /* [in] */ BSTR bstrURL,
            /* [in] */ long dwFlags,
            /* [in] */ BSTR bstrTargetFrameName,
            /* [in] */ BSTR bstrPostData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Busy( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_title( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LocationURL( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsFrame( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIsFrame) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_IsFrame( 
            /* [in] */ VARIANT_BOOL vbIsFrame) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ScrollStyle( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ScrollStyle( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginWidth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginHeight( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FrameNavigate( 
            BSTR bstrURL,
            BSTR bstrTarget,
            BSTR bstrSource,
            BSTR bstrPostData,
            BOOL __RPC_FAR *Cancel) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedCodepage( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedCodepage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CBrowserPointer( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBrowser __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBrowser __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBrowser __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *navigate )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ long dwFlags,
            /* [in] */ BSTR bstrTargetFrameName,
            /* [in] */ BSTR bstrPostData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IBrowser __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IBrowser __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Busy )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_title )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationURL )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFrame )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIsFrame);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsFrame )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbIsFrame);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScrollStyle )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScrollStyle )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarginWidth )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarginWidth )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarginHeight )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarginHeight )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FrameNavigate )( 
            IBrowser __RPC_FAR * This,
            BSTR bstrURL,
            BSTR bstrTarget,
            BSTR bstrSource,
            BSTR bstrPostData,
            BOOL __RPC_FAR *Cancel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedCodepage )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelectedCodepage )( 
            IBrowser __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CBrowserPointer )( 
            IBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IBrowserVtbl;

    interface IBrowser
    {
        CONST_VTBL struct IBrowserVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBrowser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBrowser_navigate(This,bstrURL,dwFlags,bstrTargetFrameName,bstrPostData)	\
    (This)->lpVtbl -> navigate(This,bstrURL,dwFlags,bstrTargetFrameName,bstrPostData)

#define IBrowser_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IBrowser_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IBrowser_get_Busy(This,pVal)	\
    (This)->lpVtbl -> get_Busy(This,pVal)

#define IBrowser_get_title(This,pVal)	\
    (This)->lpVtbl -> get_title(This,pVal)

#define IBrowser_get_LocationURL(This,pVal)	\
    (This)->lpVtbl -> get_LocationURL(This,pVal)

#define IBrowser_get_IsFrame(This,pvbIsFrame)	\
    (This)->lpVtbl -> get_IsFrame(This,pvbIsFrame)

#define IBrowser_put_IsFrame(This,vbIsFrame)	\
    (This)->lpVtbl -> put_IsFrame(This,vbIsFrame)

#define IBrowser_get_ScrollStyle(This,pVal)	\
    (This)->lpVtbl -> get_ScrollStyle(This,pVal)

#define IBrowser_put_ScrollStyle(This,newVal)	\
    (This)->lpVtbl -> put_ScrollStyle(This,newVal)

#define IBrowser_get_MarginWidth(This,pVal)	\
    (This)->lpVtbl -> get_MarginWidth(This,pVal)

#define IBrowser_put_MarginWidth(This,newVal)	\
    (This)->lpVtbl -> put_MarginWidth(This,newVal)

#define IBrowser_get_MarginHeight(This,pVal)	\
    (This)->lpVtbl -> get_MarginHeight(This,pVal)

#define IBrowser_put_MarginHeight(This,newVal)	\
    (This)->lpVtbl -> put_MarginHeight(This,newVal)

#define IBrowser_FrameNavigate(This,bstrURL,bstrTarget,bstrSource,bstrPostData,Cancel)	\
    (This)->lpVtbl -> FrameNavigate(This,bstrURL,bstrTarget,bstrSource,bstrPostData,Cancel)

#define IBrowser_get_SelectedCodepage(This,pVal)	\
    (This)->lpVtbl -> get_SelectedCodepage(This,pVal)

#define IBrowser_put_SelectedCodepage(This,newVal)	\
    (This)->lpVtbl -> put_SelectedCodepage(This,newVal)

#define IBrowser_get_CBrowserPointer(This,pVal)	\
    (This)->lpVtbl -> get_CBrowserPointer(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IBrowser_navigate_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [in] */ BSTR bstrURL,
    /* [in] */ long dwFlags,
    /* [in] */ BSTR bstrTargetFrameName,
    /* [in] */ BSTR bstrPostData);


void __RPC_STUB IBrowser_navigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBrowser_Refresh_Proxy( 
    IBrowser __RPC_FAR * This);


void __RPC_STUB IBrowser_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBrowser_Stop_Proxy( 
    IBrowser __RPC_FAR * This);


void __RPC_STUB IBrowser_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_Busy_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_Busy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_title_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_LocationURL_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_LocationURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_IsFrame_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIsFrame);


void __RPC_STUB IBrowser_get_IsFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser_put_IsFrame_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbIsFrame);


void __RPC_STUB IBrowser_put_IsFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_ScrollStyle_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_ScrollStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser_put_ScrollStyle_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBrowser_put_ScrollStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_MarginWidth_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_MarginWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser_put_MarginWidth_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBrowser_put_MarginWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_MarginHeight_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_MarginHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser_put_MarginHeight_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBrowser_put_MarginHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBrowser_FrameNavigate_Proxy( 
    IBrowser __RPC_FAR * This,
    BSTR bstrURL,
    BSTR bstrTarget,
    BSTR bstrSource,
    BSTR bstrPostData,
    BOOL __RPC_FAR *Cancel);


void __RPC_STUB IBrowser_FrameNavigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_SelectedCodepage_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_SelectedCodepage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser_put_SelectedCodepage_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBrowser_put_SelectedCodepage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser_get_CBrowserPointer_Proxy( 
    IBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBrowser_get_CBrowserPointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowser_INTERFACE_DEFINED__ */


#ifndef __IBrowser2_INTERFACE_DEFINED__
#define __IBrowser2_INTERFACE_DEFINED__

/* interface IBrowser2 */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IBrowser2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("698E3FFF-70C3-11D0-81E8-00A0C90AD20A")
    IBrowser2 : public IBrowser
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutWidth( 
            /* [retval][out] */ int __RPC_FAR *piLayoutWidth) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutHeight( 
            /* [retval][out] */ int __RPC_FAR *piLayoutHeight) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LocationBaseURL( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrBaseLocationURL) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LocationBaseURL( 
            /* [in] */ BSTR bstrBaseLocationURL) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ClearTypeEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClearTypeEnabled) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ClearTypeEnabled( 
            /* [in] */ VARIANT_BOOL bClearTypeEnabled) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ScriptingEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbScriptingEnabled) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ScriptingEnabled( 
            /* [in] */ VARIANT_BOOL bScriptingEnabled) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FitToWindow( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFitToWindow) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FitToWindow( 
            /* [in] */ VARIANT_BOOL bFitToWindow) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowImages( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbShowImages) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowImages( 
            /* [in] */ VARIANT_BOOL bShowImages) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PlaySounds( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPlaySounds) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PlaySounds( 
            /* [in] */ VARIANT_BOOL bPlaySounds) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ZoomLevel( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwZoomLevel) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ZoomLevel( 
            /* [in] */ DWORD dwZoomLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowser2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBrowser2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBrowser2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBrowser2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *navigate )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ long dwFlags,
            /* [in] */ BSTR bstrTargetFrameName,
            /* [in] */ BSTR bstrPostData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IBrowser2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IBrowser2 __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Busy )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_title )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationURL )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFrame )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIsFrame);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsFrame )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbIsFrame);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScrollStyle )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScrollStyle )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarginWidth )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarginWidth )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarginHeight )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarginHeight )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FrameNavigate )( 
            IBrowser2 __RPC_FAR * This,
            BSTR bstrURL,
            BSTR bstrTarget,
            BSTR bstrSource,
            BSTR bstrPostData,
            BOOL __RPC_FAR *Cancel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedCodepage )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelectedCodepage )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CBrowserPointer )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LayoutWidth )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piLayoutWidth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LayoutHeight )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piLayoutHeight);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationBaseURL )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrBaseLocationURL);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocationBaseURL )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ BSTR bstrBaseLocationURL);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClearTypeEnabled )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClearTypeEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTypeEnabled )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bClearTypeEnabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScriptingEnabled )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbScriptingEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScriptingEnabled )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bScriptingEnabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FitToWindow )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFitToWindow);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FitToWindow )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bFitToWindow);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowImages )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbShowImages);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowImages )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bShowImages);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PlaySounds )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPlaySounds);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PlaySounds )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bPlaySounds);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ZoomLevel )( 
            IBrowser2 __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwZoomLevel);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ZoomLevel )( 
            IBrowser2 __RPC_FAR * This,
            /* [in] */ DWORD dwZoomLevel);
        
        END_INTERFACE
    } IBrowser2Vtbl;

    interface IBrowser2
    {
        CONST_VTBL struct IBrowser2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowser2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBrowser2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBrowser2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBrowser2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBrowser2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBrowser2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBrowser2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBrowser2_navigate(This,bstrURL,dwFlags,bstrTargetFrameName,bstrPostData)	\
    (This)->lpVtbl -> navigate(This,bstrURL,dwFlags,bstrTargetFrameName,bstrPostData)

#define IBrowser2_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IBrowser2_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IBrowser2_get_Busy(This,pVal)	\
    (This)->lpVtbl -> get_Busy(This,pVal)

#define IBrowser2_get_title(This,pVal)	\
    (This)->lpVtbl -> get_title(This,pVal)

#define IBrowser2_get_LocationURL(This,pVal)	\
    (This)->lpVtbl -> get_LocationURL(This,pVal)

#define IBrowser2_get_IsFrame(This,pvbIsFrame)	\
    (This)->lpVtbl -> get_IsFrame(This,pvbIsFrame)

#define IBrowser2_put_IsFrame(This,vbIsFrame)	\
    (This)->lpVtbl -> put_IsFrame(This,vbIsFrame)

#define IBrowser2_get_ScrollStyle(This,pVal)	\
    (This)->lpVtbl -> get_ScrollStyle(This,pVal)

#define IBrowser2_put_ScrollStyle(This,newVal)	\
    (This)->lpVtbl -> put_ScrollStyle(This,newVal)

#define IBrowser2_get_MarginWidth(This,pVal)	\
    (This)->lpVtbl -> get_MarginWidth(This,pVal)

#define IBrowser2_put_MarginWidth(This,newVal)	\
    (This)->lpVtbl -> put_MarginWidth(This,newVal)

#define IBrowser2_get_MarginHeight(This,pVal)	\
    (This)->lpVtbl -> get_MarginHeight(This,pVal)

#define IBrowser2_put_MarginHeight(This,newVal)	\
    (This)->lpVtbl -> put_MarginHeight(This,newVal)

#define IBrowser2_FrameNavigate(This,bstrURL,bstrTarget,bstrSource,bstrPostData,Cancel)	\
    (This)->lpVtbl -> FrameNavigate(This,bstrURL,bstrTarget,bstrSource,bstrPostData,Cancel)

#define IBrowser2_get_SelectedCodepage(This,pVal)	\
    (This)->lpVtbl -> get_SelectedCodepage(This,pVal)

#define IBrowser2_put_SelectedCodepage(This,newVal)	\
    (This)->lpVtbl -> put_SelectedCodepage(This,newVal)

#define IBrowser2_get_CBrowserPointer(This,pVal)	\
    (This)->lpVtbl -> get_CBrowserPointer(This,pVal)


#define IBrowser2_get_LayoutWidth(This,piLayoutWidth)	\
    (This)->lpVtbl -> get_LayoutWidth(This,piLayoutWidth)

#define IBrowser2_get_LayoutHeight(This,piLayoutHeight)	\
    (This)->lpVtbl -> get_LayoutHeight(This,piLayoutHeight)

#define IBrowser2_get_LocationBaseURL(This,bstrBaseLocationURL)	\
    (This)->lpVtbl -> get_LocationBaseURL(This,bstrBaseLocationURL)

#define IBrowser2_put_LocationBaseURL(This,bstrBaseLocationURL)	\
    (This)->lpVtbl -> put_LocationBaseURL(This,bstrBaseLocationURL)

#define IBrowser2_get_ClearTypeEnabled(This,pbClearTypeEnabled)	\
    (This)->lpVtbl -> get_ClearTypeEnabled(This,pbClearTypeEnabled)

#define IBrowser2_put_ClearTypeEnabled(This,bClearTypeEnabled)	\
    (This)->lpVtbl -> put_ClearTypeEnabled(This,bClearTypeEnabled)

#define IBrowser2_get_ScriptingEnabled(This,pbScriptingEnabled)	\
    (This)->lpVtbl -> get_ScriptingEnabled(This,pbScriptingEnabled)

#define IBrowser2_put_ScriptingEnabled(This,bScriptingEnabled)	\
    (This)->lpVtbl -> put_ScriptingEnabled(This,bScriptingEnabled)

#define IBrowser2_get_FitToWindow(This,pbFitToWindow)	\
    (This)->lpVtbl -> get_FitToWindow(This,pbFitToWindow)

#define IBrowser2_put_FitToWindow(This,bFitToWindow)	\
    (This)->lpVtbl -> put_FitToWindow(This,bFitToWindow)

#define IBrowser2_get_ShowImages(This,pbShowImages)	\
    (This)->lpVtbl -> get_ShowImages(This,pbShowImages)

#define IBrowser2_put_ShowImages(This,bShowImages)	\
    (This)->lpVtbl -> put_ShowImages(This,bShowImages)

#define IBrowser2_get_PlaySounds(This,pbPlaySounds)	\
    (This)->lpVtbl -> get_PlaySounds(This,pbPlaySounds)

#define IBrowser2_put_PlaySounds(This,bPlaySounds)	\
    (This)->lpVtbl -> put_PlaySounds(This,bPlaySounds)

#define IBrowser2_get_ZoomLevel(This,pdwZoomLevel)	\
    (This)->lpVtbl -> get_ZoomLevel(This,pdwZoomLevel)

#define IBrowser2_put_ZoomLevel(This,dwZoomLevel)	\
    (This)->lpVtbl -> put_ZoomLevel(This,dwZoomLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_LayoutWidth_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piLayoutWidth);


void __RPC_STUB IBrowser2_get_LayoutWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_LayoutHeight_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piLayoutHeight);


void __RPC_STUB IBrowser2_get_LayoutHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_LocationBaseURL_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrBaseLocationURL);


void __RPC_STUB IBrowser2_get_LocationBaseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_LocationBaseURL_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ BSTR bstrBaseLocationURL);


void __RPC_STUB IBrowser2_put_LocationBaseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_ClearTypeEnabled_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClearTypeEnabled);


void __RPC_STUB IBrowser2_get_ClearTypeEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_ClearTypeEnabled_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bClearTypeEnabled);


void __RPC_STUB IBrowser2_put_ClearTypeEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_ScriptingEnabled_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbScriptingEnabled);


void __RPC_STUB IBrowser2_get_ScriptingEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_ScriptingEnabled_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bScriptingEnabled);


void __RPC_STUB IBrowser2_put_ScriptingEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_FitToWindow_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFitToWindow);


void __RPC_STUB IBrowser2_get_FitToWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_FitToWindow_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bFitToWindow);


void __RPC_STUB IBrowser2_put_FitToWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_ShowImages_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbShowImages);


void __RPC_STUB IBrowser2_get_ShowImages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_ShowImages_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bShowImages);


void __RPC_STUB IBrowser2_put_ShowImages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_PlaySounds_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPlaySounds);


void __RPC_STUB IBrowser2_get_PlaySounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_PlaySounds_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bPlaySounds);


void __RPC_STUB IBrowser2_put_PlaySounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser2_get_ZoomLevel_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwZoomLevel);


void __RPC_STUB IBrowser2_get_ZoomLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser2_put_ZoomLevel_Proxy( 
    IBrowser2 __RPC_FAR * This,
    /* [in] */ DWORD dwZoomLevel);


void __RPC_STUB IBrowser2_put_ZoomLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowser2_INTERFACE_DEFINED__ */


#ifndef __IBrowser3_INTERFACE_DEFINED__
#define __IBrowser3_INTERFACE_DEFINED__

/* interface IBrowser3 */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IBrowser3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("698E3FFE-70C3-11D0-81E8-00A0C90AD20A")
    IBrowser3 : public IBrowser2
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_script( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IntegralPaging( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIntegralPaging) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_IntegralPaging( 
            /* [in] */ VARIANT_BOOL pvbIntegralPaging) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ContextMenuEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbContextMenu) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ContextMenuEnabled( 
            /* [in] */ VARIANT_BOOL pvbContextMenu) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveXEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbActiveXEnabled) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ActiveXEnabled( 
            /* [in] */ VARIANT_BOOL vbActiveXEnabled) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectionEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbSelectionEnabled) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectionEnabled( 
            /* [in] */ VARIANT_BOOL vbSelectionEnabled) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CanCopy( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbCanCopy) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FocusRectEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbFocusRectEnabled) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FocusRectEnabled( 
            /* [in] */ VARIANT_BOOL bFocusRectEnabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SuperFitToWindow( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuperFitToWindow) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SuperFitToWindow( 
            /* [in] */ VARIANT_BOOL bSuperFitToWindow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE addStyle( 
            /* [in] */ BSTR bstrStyle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowser3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBrowser3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBrowser3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBrowser3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *navigate )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ long dwFlags,
            /* [in] */ BSTR bstrTargetFrameName,
            /* [in] */ BSTR bstrPostData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IBrowser3 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IBrowser3 __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Busy )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_title )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationURL )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFrame )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIsFrame);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsFrame )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbIsFrame);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScrollStyle )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScrollStyle )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarginWidth )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarginWidth )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarginHeight )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarginHeight )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FrameNavigate )( 
            IBrowser3 __RPC_FAR * This,
            BSTR bstrURL,
            BSTR bstrTarget,
            BSTR bstrSource,
            BSTR bstrPostData,
            BOOL __RPC_FAR *Cancel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedCodepage )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelectedCodepage )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CBrowserPointer )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LayoutWidth )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piLayoutWidth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LayoutHeight )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piLayoutHeight);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationBaseURL )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrBaseLocationURL);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocationBaseURL )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ BSTR bstrBaseLocationURL);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClearTypeEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbClearTypeEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearTypeEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bClearTypeEnabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScriptingEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbScriptingEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScriptingEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bScriptingEnabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FitToWindow )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFitToWindow);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FitToWindow )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bFitToWindow);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowImages )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbShowImages);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowImages )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bShowImages);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PlaySounds )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPlaySounds);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PlaySounds )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bPlaySounds);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ZoomLevel )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwZoomLevel);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ZoomLevel )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ DWORD dwZoomLevel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_script )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IntegralPaging )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIntegralPaging);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IntegralPaging )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvbIntegralPaging);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContextMenuEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbContextMenu);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContextMenuEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvbContextMenu);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActiveXEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbActiveXEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ActiveXEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbActiveXEnabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectionEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbSelectionEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelectionEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbSelectionEnabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanCopy )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbCanCopy);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FocusRectEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbFocusRectEnabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FocusRectEnabled )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bFocusRectEnabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SuperFitToWindow )( 
            IBrowser3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuperFitToWindow);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SuperFitToWindow )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bSuperFitToWindow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addStyle )( 
            IBrowser3 __RPC_FAR * This,
            /* [in] */ BSTR bstrStyle);
        
        END_INTERFACE
    } IBrowser3Vtbl;

    interface IBrowser3
    {
        CONST_VTBL struct IBrowser3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowser3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBrowser3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBrowser3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBrowser3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBrowser3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBrowser3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBrowser3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBrowser3_navigate(This,bstrURL,dwFlags,bstrTargetFrameName,bstrPostData)	\
    (This)->lpVtbl -> navigate(This,bstrURL,dwFlags,bstrTargetFrameName,bstrPostData)

#define IBrowser3_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IBrowser3_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IBrowser3_get_Busy(This,pVal)	\
    (This)->lpVtbl -> get_Busy(This,pVal)

#define IBrowser3_get_title(This,pVal)	\
    (This)->lpVtbl -> get_title(This,pVal)

#define IBrowser3_get_LocationURL(This,pVal)	\
    (This)->lpVtbl -> get_LocationURL(This,pVal)

#define IBrowser3_get_IsFrame(This,pvbIsFrame)	\
    (This)->lpVtbl -> get_IsFrame(This,pvbIsFrame)

#define IBrowser3_put_IsFrame(This,vbIsFrame)	\
    (This)->lpVtbl -> put_IsFrame(This,vbIsFrame)

#define IBrowser3_get_ScrollStyle(This,pVal)	\
    (This)->lpVtbl -> get_ScrollStyle(This,pVal)

#define IBrowser3_put_ScrollStyle(This,newVal)	\
    (This)->lpVtbl -> put_ScrollStyle(This,newVal)

#define IBrowser3_get_MarginWidth(This,pVal)	\
    (This)->lpVtbl -> get_MarginWidth(This,pVal)

#define IBrowser3_put_MarginWidth(This,newVal)	\
    (This)->lpVtbl -> put_MarginWidth(This,newVal)

#define IBrowser3_get_MarginHeight(This,pVal)	\
    (This)->lpVtbl -> get_MarginHeight(This,pVal)

#define IBrowser3_put_MarginHeight(This,newVal)	\
    (This)->lpVtbl -> put_MarginHeight(This,newVal)

#define IBrowser3_FrameNavigate(This,bstrURL,bstrTarget,bstrSource,bstrPostData,Cancel)	\
    (This)->lpVtbl -> FrameNavigate(This,bstrURL,bstrTarget,bstrSource,bstrPostData,Cancel)

#define IBrowser3_get_SelectedCodepage(This,pVal)	\
    (This)->lpVtbl -> get_SelectedCodepage(This,pVal)

#define IBrowser3_put_SelectedCodepage(This,newVal)	\
    (This)->lpVtbl -> put_SelectedCodepage(This,newVal)

#define IBrowser3_get_CBrowserPointer(This,pVal)	\
    (This)->lpVtbl -> get_CBrowserPointer(This,pVal)


#define IBrowser3_get_LayoutWidth(This,piLayoutWidth)	\
    (This)->lpVtbl -> get_LayoutWidth(This,piLayoutWidth)

#define IBrowser3_get_LayoutHeight(This,piLayoutHeight)	\
    (This)->lpVtbl -> get_LayoutHeight(This,piLayoutHeight)

#define IBrowser3_get_LocationBaseURL(This,bstrBaseLocationURL)	\
    (This)->lpVtbl -> get_LocationBaseURL(This,bstrBaseLocationURL)

#define IBrowser3_put_LocationBaseURL(This,bstrBaseLocationURL)	\
    (This)->lpVtbl -> put_LocationBaseURL(This,bstrBaseLocationURL)

#define IBrowser3_get_ClearTypeEnabled(This,pbClearTypeEnabled)	\
    (This)->lpVtbl -> get_ClearTypeEnabled(This,pbClearTypeEnabled)

#define IBrowser3_put_ClearTypeEnabled(This,bClearTypeEnabled)	\
    (This)->lpVtbl -> put_ClearTypeEnabled(This,bClearTypeEnabled)

#define IBrowser3_get_ScriptingEnabled(This,pbScriptingEnabled)	\
    (This)->lpVtbl -> get_ScriptingEnabled(This,pbScriptingEnabled)

#define IBrowser3_put_ScriptingEnabled(This,bScriptingEnabled)	\
    (This)->lpVtbl -> put_ScriptingEnabled(This,bScriptingEnabled)

#define IBrowser3_get_FitToWindow(This,pbFitToWindow)	\
    (This)->lpVtbl -> get_FitToWindow(This,pbFitToWindow)

#define IBrowser3_put_FitToWindow(This,bFitToWindow)	\
    (This)->lpVtbl -> put_FitToWindow(This,bFitToWindow)

#define IBrowser3_get_ShowImages(This,pbShowImages)	\
    (This)->lpVtbl -> get_ShowImages(This,pbShowImages)

#define IBrowser3_put_ShowImages(This,bShowImages)	\
    (This)->lpVtbl -> put_ShowImages(This,bShowImages)

#define IBrowser3_get_PlaySounds(This,pbPlaySounds)	\
    (This)->lpVtbl -> get_PlaySounds(This,pbPlaySounds)

#define IBrowser3_put_PlaySounds(This,bPlaySounds)	\
    (This)->lpVtbl -> put_PlaySounds(This,bPlaySounds)

#define IBrowser3_get_ZoomLevel(This,pdwZoomLevel)	\
    (This)->lpVtbl -> get_ZoomLevel(This,pdwZoomLevel)

#define IBrowser3_put_ZoomLevel(This,dwZoomLevel)	\
    (This)->lpVtbl -> put_ZoomLevel(This,dwZoomLevel)


#define IBrowser3_get_document(This,ppDisp)	\
    (This)->lpVtbl -> get_document(This,ppDisp)

#define IBrowser3_get_script(This,ppDisp)	\
    (This)->lpVtbl -> get_script(This,ppDisp)

#define IBrowser3_get_IntegralPaging(This,pvbIntegralPaging)	\
    (This)->lpVtbl -> get_IntegralPaging(This,pvbIntegralPaging)

#define IBrowser3_put_IntegralPaging(This,pvbIntegralPaging)	\
    (This)->lpVtbl -> put_IntegralPaging(This,pvbIntegralPaging)

#define IBrowser3_get_ContextMenuEnabled(This,pvbContextMenu)	\
    (This)->lpVtbl -> get_ContextMenuEnabled(This,pvbContextMenu)

#define IBrowser3_put_ContextMenuEnabled(This,pvbContextMenu)	\
    (This)->lpVtbl -> put_ContextMenuEnabled(This,pvbContextMenu)

#define IBrowser3_get_ActiveXEnabled(This,pvbActiveXEnabled)	\
    (This)->lpVtbl -> get_ActiveXEnabled(This,pvbActiveXEnabled)

#define IBrowser3_put_ActiveXEnabled(This,vbActiveXEnabled)	\
    (This)->lpVtbl -> put_ActiveXEnabled(This,vbActiveXEnabled)

#define IBrowser3_get_SelectionEnabled(This,pvbSelectionEnabled)	\
    (This)->lpVtbl -> get_SelectionEnabled(This,pvbSelectionEnabled)

#define IBrowser3_put_SelectionEnabled(This,vbSelectionEnabled)	\
    (This)->lpVtbl -> put_SelectionEnabled(This,vbSelectionEnabled)

#define IBrowser3_get_CanCopy(This,pvbCanCopy)	\
    (This)->lpVtbl -> get_CanCopy(This,pvbCanCopy)

#define IBrowser3_get_FocusRectEnabled(This,pvbFocusRectEnabled)	\
    (This)->lpVtbl -> get_FocusRectEnabled(This,pvbFocusRectEnabled)

#define IBrowser3_put_FocusRectEnabled(This,bFocusRectEnabled)	\
    (This)->lpVtbl -> put_FocusRectEnabled(This,bFocusRectEnabled)

#define IBrowser3_get_SuperFitToWindow(This,pbSuperFitToWindow)	\
    (This)->lpVtbl -> get_SuperFitToWindow(This,pbSuperFitToWindow)

#define IBrowser3_put_SuperFitToWindow(This,bSuperFitToWindow)	\
    (This)->lpVtbl -> put_SuperFitToWindow(This,bSuperFitToWindow)

#define IBrowser3_addStyle(This,bstrStyle)	\
    (This)->lpVtbl -> addStyle(This,bstrStyle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_document_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IBrowser3_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_script_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IBrowser3_get_script_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_IntegralPaging_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIntegralPaging);


void __RPC_STUB IBrowser3_get_IntegralPaging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser3_put_IntegralPaging_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvbIntegralPaging);


void __RPC_STUB IBrowser3_put_IntegralPaging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_ContextMenuEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbContextMenu);


void __RPC_STUB IBrowser3_get_ContextMenuEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser3_put_ContextMenuEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvbContextMenu);


void __RPC_STUB IBrowser3_put_ContextMenuEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_ActiveXEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbActiveXEnabled);


void __RPC_STUB IBrowser3_get_ActiveXEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser3_put_ActiveXEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbActiveXEnabled);


void __RPC_STUB IBrowser3_put_ActiveXEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_SelectionEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbSelectionEnabled);


void __RPC_STUB IBrowser3_get_SelectionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser3_put_SelectionEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbSelectionEnabled);


void __RPC_STUB IBrowser3_put_SelectionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_CanCopy_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbCanCopy);


void __RPC_STUB IBrowser3_get_CanCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_FocusRectEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbFocusRectEnabled);


void __RPC_STUB IBrowser3_get_FocusRectEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IBrowser3_put_FocusRectEnabled_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bFocusRectEnabled);


void __RPC_STUB IBrowser3_put_FocusRectEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBrowser3_get_SuperFitToWindow_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuperFitToWindow);


void __RPC_STUB IBrowser3_get_SuperFitToWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBrowser3_put_SuperFitToWindow_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bSuperFitToWindow);


void __RPC_STUB IBrowser3_put_SuperFitToWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBrowser3_addStyle_Proxy( 
    IBrowser3 __RPC_FAR * This,
    /* [in] */ BSTR bstrStyle);


void __RPC_STUB IBrowser3_addStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowser3_INTERFACE_DEFINED__ */



#ifndef __WEBVIEWLib_LIBRARY_DEFINED__
#define __WEBVIEWLib_LIBRARY_DEFINED__

/* library WEBVIEWLib */
/* [version][uuid] */ 



EXTERN_C const IID LIBID_WEBVIEWLib;

#ifndef ___DPIEWebBrowserEvents2_DISPINTERFACE_DEFINED__
#define ___DPIEWebBrowserEvents2_DISPINTERFACE_DEFINED__

/* dispinterface _DPIEWebBrowserEvents2 */
/* [uuid] */ 


EXTERN_C const IID DIID__DPIEWebBrowserEvents2;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("698E3FBE-70C3-11D0-81E8-00A0C90AD20B")
    _DPIEWebBrowserEvents2 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPIEWebBrowserEvents2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _DPIEWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _DPIEWebBrowserEvents2Vtbl;

    interface _DPIEWebBrowserEvents2
    {
        CONST_VTBL struct _DPIEWebBrowserEvents2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPIEWebBrowserEvents2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DPIEWebBrowserEvents2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DPIEWebBrowserEvents2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DPIEWebBrowserEvents2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DPIEWebBrowserEvents2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DPIEWebBrowserEvents2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DPIEWebBrowserEvents2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPIEWebBrowserEvents2_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Browser;

#ifdef __cplusplus

class DECLSPEC_UUID("698E3FCA-70C3-11D0-81E8-00A0C90AD20A")
Browser;
#endif

#ifndef __IPIEOmNavigator_INTERFACE_DEFINED__
#define __IPIEOmNavigator_INTERFACE_DEFINED__

/* interface IPIEOmNavigator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEOmNavigator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2100")
    IPIEOmNavigator : public IDispatchEx
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_toString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_appCodeName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCodeName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_appName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_appVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_userAgent( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAgent) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_platform( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPlatform) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE javaEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbJavaEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE taintEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbTaintEnabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEOmNavigatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEOmNavigator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEOmNavigator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_appCodeName )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCodeName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_appName )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_appVersion )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_userAgent )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAgent);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_platform )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPlatform);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *javaEnabled )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbJavaEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *taintEnabled )( 
            IPIEOmNavigator __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbTaintEnabled);
        
        END_INTERFACE
    } IPIEOmNavigatorVtbl;

    interface IPIEOmNavigator
    {
        CONST_VTBL struct IPIEOmNavigatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEOmNavigator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEOmNavigator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEOmNavigator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEOmNavigator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEOmNavigator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEOmNavigator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEOmNavigator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEOmNavigator_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEOmNavigator_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEOmNavigator_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEOmNavigator_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEOmNavigator_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEOmNavigator_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEOmNavigator_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEOmNavigator_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEOmNavigator_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEOmNavigator_get_appCodeName(This,pbstrCodeName)	\
    (This)->lpVtbl -> get_appCodeName(This,pbstrCodeName)

#define IPIEOmNavigator_get_appName(This,pbstrName)	\
    (This)->lpVtbl -> get_appName(This,pbstrName)

#define IPIEOmNavigator_get_appVersion(This,pbstrVersion)	\
    (This)->lpVtbl -> get_appVersion(This,pbstrVersion)

#define IPIEOmNavigator_get_userAgent(This,pbstrUserAgent)	\
    (This)->lpVtbl -> get_userAgent(This,pbstrUserAgent)

#define IPIEOmNavigator_get_platform(This,pbstrPlatform)	\
    (This)->lpVtbl -> get_platform(This,pbstrPlatform)

#define IPIEOmNavigator_javaEnabled(This,pvbJavaEnabled)	\
    (This)->lpVtbl -> javaEnabled(This,pvbJavaEnabled)

#define IPIEOmNavigator_taintEnabled(This,pvbTaintEnabled)	\
    (This)->lpVtbl -> taintEnabled(This,pvbTaintEnabled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IPIEOmNavigator_get_toString_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrString);


void __RPC_STUB IPIEOmNavigator_get_toString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEOmNavigator_get_appCodeName_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCodeName);


void __RPC_STUB IPIEOmNavigator_get_appCodeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEOmNavigator_get_appName_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEOmNavigator_get_appName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEOmNavigator_get_appVersion_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion);


void __RPC_STUB IPIEOmNavigator_get_appVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEOmNavigator_get_userAgent_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrUserAgent);


void __RPC_STUB IPIEOmNavigator_get_userAgent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEOmNavigator_get_platform_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrPlatform);


void __RPC_STUB IPIEOmNavigator_get_platform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEOmNavigator_javaEnabled_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbJavaEnabled);


void __RPC_STUB IPIEOmNavigator_javaEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEOmNavigator_taintEnabled_Proxy( 
    IPIEOmNavigator __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbTaintEnabled);


void __RPC_STUB IPIEOmNavigator_taintEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEOmNavigator_INTERFACE_DEFINED__ */


#ifndef __IPIEOmHistory_INTERFACE_DEFINED__
#define __IPIEOmHistory_INTERFACE_DEFINED__

/* interface IPIEOmHistory */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEOmHistory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2104")
    IPIEOmHistory : public IDispatchEx
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_toString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [out][retval] */ long __RPC_FAR *plLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE back( 
            /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE forward( 
            /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE go( 
            /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEOmHistoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEOmHistory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEOmHistory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *back )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *forward )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *go )( 
            IPIEOmHistory __RPC_FAR * This,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance);
        
        END_INTERFACE
    } IPIEOmHistoryVtbl;

    interface IPIEOmHistory
    {
        CONST_VTBL struct IPIEOmHistoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEOmHistory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEOmHistory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEOmHistory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEOmHistory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEOmHistory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEOmHistory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEOmHistory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEOmHistory_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEOmHistory_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEOmHistory_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEOmHistory_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEOmHistory_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEOmHistory_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEOmHistory_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEOmHistory_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEOmHistory_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEOmHistory_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEOmHistory_back(This,pvtDistance)	\
    (This)->lpVtbl -> back(This,pvtDistance)

#define IPIEOmHistory_forward(This,pvtDistance)	\
    (This)->lpVtbl -> forward(This,pvtDistance)

#define IPIEOmHistory_go(This,pvtDistance)	\
    (This)->lpVtbl -> go(This,pvtDistance)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IPIEOmHistory_get_toString_Proxy( 
    IPIEOmHistory __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrString);


void __RPC_STUB IPIEOmHistory_get_toString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEOmHistory_get_length_Proxy( 
    IPIEOmHistory __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plLength);


void __RPC_STUB IPIEOmHistory_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEOmHistory_back_Proxy( 
    IPIEOmHistory __RPC_FAR * This,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance);


void __RPC_STUB IPIEOmHistory_back_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEOmHistory_forward_Proxy( 
    IPIEOmHistory __RPC_FAR * This,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance);


void __RPC_STUB IPIEOmHistory_forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEOmHistory_go_Proxy( 
    IPIEOmHistory __RPC_FAR * This,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtDistance);


void __RPC_STUB IPIEOmHistory_go_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEOmHistory_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLElementCollection_INTERFACE_DEFINED__
#define __IPIEHTMLElementCollection_INTERFACE_DEFINED__

/* interface IPIEHTMLElementCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLElementCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2105")
    IPIEHTMLElementCollection : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plLength) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE item( 
            /* [optional][in] */ VARIANT vtName,
            /* [optional][in] */ VARIANT vtIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLElementCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLElementCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLElementCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IPIEHTMLElementCollection __RPC_FAR * This,
            /* [optional][in] */ VARIANT vtName,
            /* [optional][in] */ VARIANT vtIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispItem);
        
        END_INTERFACE
    } IPIEHTMLElementCollectionVtbl;

    interface IPIEHTMLElementCollection
    {
        CONST_VTBL struct IPIEHTMLElementCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLElementCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLElementCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLElementCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLElementCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLElementCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLElementCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLElementCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLElementCollection_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLElementCollection_item(This,vtName,vtIndex,ppdispItem)	\
    (This)->lpVtbl -> item(This,vtName,vtIndex,ppdispItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElementCollection_get_length_Proxy( 
    IPIEHTMLElementCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLength);


void __RPC_STUB IPIEHTMLElementCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElementCollection_item_Proxy( 
    IPIEHTMLElementCollection __RPC_FAR * This,
    /* [optional][in] */ VARIANT vtName,
    /* [optional][in] */ VARIANT vtIndex,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispItem);


void __RPC_STUB IPIEHTMLElementCollection_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLElementCollection_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLFormElementCollection_INTERFACE_DEFINED__
#define __IPIEHTMLFormElementCollection_INTERFACE_DEFINED__

/* interface IPIEHTMLFormElementCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLFormElementCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE211A")
    IPIEHTMLFormElementCollection : public IPIEHTMLElementCollection
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLFormElementCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [optional][in] */ VARIANT vtName,
            /* [optional][in] */ VARIANT vtIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispItem);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLFormElementCollection __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        END_INTERFACE
    } IPIEHTMLFormElementCollectionVtbl;

    interface IPIEHTMLFormElementCollection
    {
        CONST_VTBL struct IPIEHTMLFormElementCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLFormElementCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLFormElementCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLFormElementCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLFormElementCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLFormElementCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLFormElementCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLFormElementCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLFormElementCollection_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLFormElementCollection_item(This,vtName,vtIndex,ppdispItem)	\
    (This)->lpVtbl -> item(This,vtName,vtIndex,ppdispItem)


#define IPIEHTMLFormElementCollection_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElementCollection_get_name_Proxy( 
    IPIEHTMLFormElementCollection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEHTMLFormElementCollection_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLFormElementCollection_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLLocation_INTERFACE_DEFINED__
#define __IPIEHTMLLocation_INTERFACE_DEFINED__

/* interface IPIEHTMLLocation */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLLocation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2109")
    IPIEHTMLLocation : public IDispatchEx
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_href( 
            /* [in] */ BSTR bstrHREF) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_href( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHREF) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_protocol( 
            /* [in] */ BSTR bstrProtocol) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_protocol( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrProtocol) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_host( 
            /* [in] */ BSTR bstrHost) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_host( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHost) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_hostname( 
            /* [in] */ BSTR bstrHostName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_hostname( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHostName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_port( 
            /* [in] */ BSTR bstrPort) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_port( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPort) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_pathname( 
            /* [in] */ BSTR bstrPathName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_pathname( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPathName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_search( 
            /* [in] */ BSTR bstrSearch) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_search( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrSearch) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_hash( 
            /* [in] */ BSTR bstrHash) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_hash( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHash) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE reload( 
            /* [defaultvalue][in] */ VARIANT_BOOL vbReloadSource = 0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE replace( 
            /* [in] */ BSTR bstrURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLLocationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLLocation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLLocation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_href )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrHREF);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_href )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHREF);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_protocol )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrProtocol);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_protocol )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrProtocol);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_host )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrHost);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_host )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHost);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hostname )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrHostName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hostname )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHostName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_port )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrPort);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_port )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPort);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pathname )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrPathName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pathname )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPathName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_search )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrSearch);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_search )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrSearch);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hash )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrHash);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hash )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHash);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *reload )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL vbReloadSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replace )( 
            IPIEHTMLLocation __RPC_FAR * This,
            /* [in] */ BSTR bstrURL);
        
        END_INTERFACE
    } IPIEHTMLLocationVtbl;

    interface IPIEHTMLLocation
    {
        CONST_VTBL struct IPIEHTMLLocationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLLocation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLLocation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLLocation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLLocation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLLocation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLLocation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLLocation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLLocation_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLLocation_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLLocation_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLLocation_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLLocation_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLLocation_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLLocation_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLLocation_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLLocation_put_href(This,bstrHREF)	\
    (This)->lpVtbl -> put_href(This,bstrHREF)

#define IPIEHTMLLocation_get_href(This,pbstrHREF)	\
    (This)->lpVtbl -> get_href(This,pbstrHREF)

#define IPIEHTMLLocation_put_protocol(This,bstrProtocol)	\
    (This)->lpVtbl -> put_protocol(This,bstrProtocol)

#define IPIEHTMLLocation_get_protocol(This,pbstrProtocol)	\
    (This)->lpVtbl -> get_protocol(This,pbstrProtocol)

#define IPIEHTMLLocation_put_host(This,bstrHost)	\
    (This)->lpVtbl -> put_host(This,bstrHost)

#define IPIEHTMLLocation_get_host(This,pbstrHost)	\
    (This)->lpVtbl -> get_host(This,pbstrHost)

#define IPIEHTMLLocation_put_hostname(This,bstrHostName)	\
    (This)->lpVtbl -> put_hostname(This,bstrHostName)

#define IPIEHTMLLocation_get_hostname(This,pbstrHostName)	\
    (This)->lpVtbl -> get_hostname(This,pbstrHostName)

#define IPIEHTMLLocation_put_port(This,bstrPort)	\
    (This)->lpVtbl -> put_port(This,bstrPort)

#define IPIEHTMLLocation_get_port(This,pbstrPort)	\
    (This)->lpVtbl -> get_port(This,pbstrPort)

#define IPIEHTMLLocation_put_pathname(This,bstrPathName)	\
    (This)->lpVtbl -> put_pathname(This,bstrPathName)

#define IPIEHTMLLocation_get_pathname(This,pbstrPathName)	\
    (This)->lpVtbl -> get_pathname(This,pbstrPathName)

#define IPIEHTMLLocation_put_search(This,bstrSearch)	\
    (This)->lpVtbl -> put_search(This,bstrSearch)

#define IPIEHTMLLocation_get_search(This,pbstrSearch)	\
    (This)->lpVtbl -> get_search(This,pbstrSearch)

#define IPIEHTMLLocation_put_hash(This,bstrHash)	\
    (This)->lpVtbl -> put_hash(This,bstrHash)

#define IPIEHTMLLocation_get_hash(This,pbstrHash)	\
    (This)->lpVtbl -> get_hash(This,pbstrHash)

#define IPIEHTMLLocation_reload(This,vbReloadSource)	\
    (This)->lpVtbl -> reload(This,vbReloadSource)

#define IPIEHTMLLocation_replace(This,bstrURL)	\
    (This)->lpVtbl -> replace(This,bstrURL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_href_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrHREF);


void __RPC_STUB IPIEHTMLLocation_put_href_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_href_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHREF);


void __RPC_STUB IPIEHTMLLocation_get_href_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_protocol_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrProtocol);


void __RPC_STUB IPIEHTMLLocation_put_protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_protocol_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrProtocol);


void __RPC_STUB IPIEHTMLLocation_get_protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_host_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrHost);


void __RPC_STUB IPIEHTMLLocation_put_host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_host_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHost);


void __RPC_STUB IPIEHTMLLocation_get_host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_hostname_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrHostName);


void __RPC_STUB IPIEHTMLLocation_put_hostname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_hostname_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHostName);


void __RPC_STUB IPIEHTMLLocation_get_hostname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_port_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrPort);


void __RPC_STUB IPIEHTMLLocation_put_port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_port_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrPort);


void __RPC_STUB IPIEHTMLLocation_get_port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_pathname_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrPathName);


void __RPC_STUB IPIEHTMLLocation_put_pathname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_pathname_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrPathName);


void __RPC_STUB IPIEHTMLLocation_get_pathname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_search_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrSearch);


void __RPC_STUB IPIEHTMLLocation_put_search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_search_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrSearch);


void __RPC_STUB IPIEHTMLLocation_get_search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_put_hash_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrHash);


void __RPC_STUB IPIEHTMLLocation_put_hash_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_get_hash_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHash);


void __RPC_STUB IPIEHTMLLocation_get_hash_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_reload_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL vbReloadSource);


void __RPC_STUB IPIEHTMLLocation_reload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLLocation_replace_Proxy( 
    IPIEHTMLLocation __RPC_FAR * This,
    /* [in] */ BSTR bstrURL);


void __RPC_STUB IPIEHTMLLocation_replace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLLocation_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLDocument_INTERFACE_DEFINED__
#define __IPIEHTMLDocument_INTERFACE_DEFINED__

/* interface IPIEHTMLDocument */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2101")
    IPIEHTMLDocument : public IDispatchEx
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_toString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_links( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_forms( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_anchors( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_frames( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_lastModified( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastModified) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_referrer( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferrer) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_location( 
            /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_title( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURL) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_bgColor( 
            /* [in] */ VARIANT vtBGColor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_bgColor( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBGColor) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_fgColor( 
            /* [in] */ VARIANT vtFGColor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_fgColor( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtFGColor) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_linkColor( 
            /* [in] */ VARIANT vtLinkColor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_linkColor( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtLinkColor) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_alinkColor( 
            /* [in] */ VARIANT vtALinkColor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_alinkColor( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtALinkColor) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_vlinkColor( 
            /* [in] */ VARIANT vtVLinkColor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_vlinkColor( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtVLinkColor) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_cookie( 
            /* [in] */ BSTR bstrCookie) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_cookie( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrCookie) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_domain( 
            /* [in] */ BSTR bstrDomain) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_domain( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE open( 
            /* [defaultvalue][in] */ BSTR bstrMimeType,
            /* [optional][in] */ VARIANT vtReplace) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE close( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE clear( void) = 0;
        
        virtual /* [id][vararg] */ HRESULT STDMETHODCALLTYPE write( 
            /* [in] */ SAFEARRAY __RPC_FAR * psaWrite) = 0;
        
        virtual /* [id][vararg] */ HRESULT STDMETHODCALLTYPE writeln( 
            /* [in] */ SAFEARRAY __RPC_FAR * psaWrite) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_links )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_forms )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_anchors )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_frames )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastModified )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastModified);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_referrer )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferrer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_location )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_title )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URL )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURL);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_bgColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ VARIANT vtBGColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_bgColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBGColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_fgColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ VARIANT vtFGColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fgColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtFGColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_linkColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ VARIANT vtLinkColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_linkColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtLinkColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_alinkColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ VARIANT vtALinkColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_alinkColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtALinkColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_vlinkColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ VARIANT vtVLinkColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vlinkColor )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtVLinkColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cookie )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrCookie);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cookie )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrCookie);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_domain )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrDomain);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_domain )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *open )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMimeType,
            /* [optional][in] */ VARIANT vtReplace);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *close )( 
            IPIEHTMLDocument __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clear )( 
            IPIEHTMLDocument __RPC_FAR * This);
        
        /* [id][vararg] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *write )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * psaWrite);
        
        /* [id][vararg] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *writeln )( 
            IPIEHTMLDocument __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * psaWrite);
        
        END_INTERFACE
    } IPIEHTMLDocumentVtbl;

    interface IPIEHTMLDocument
    {
        CONST_VTBL struct IPIEHTMLDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLDocument_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLDocument_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLDocument_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLDocument_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLDocument_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLDocument_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLDocument_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLDocument_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLDocument_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLDocument_get_links(This,ppElemCollection)	\
    (This)->lpVtbl -> get_links(This,ppElemCollection)

#define IPIEHTMLDocument_get_forms(This,ppElemCollection)	\
    (This)->lpVtbl -> get_forms(This,ppElemCollection)

#define IPIEHTMLDocument_get_anchors(This,ppElemCollection)	\
    (This)->lpVtbl -> get_anchors(This,ppElemCollection)

#define IPIEHTMLDocument_get_frames(This,ppElemCollection)	\
    (This)->lpVtbl -> get_frames(This,ppElemCollection)

#define IPIEHTMLDocument_get_lastModified(This,pbstrLastModified)	\
    (This)->lpVtbl -> get_lastModified(This,pbstrLastModified)

#define IPIEHTMLDocument_get_referrer(This,pbstrReferrer)	\
    (This)->lpVtbl -> get_referrer(This,pbstrReferrer)

#define IPIEHTMLDocument_get_location(This,ppLocation)	\
    (This)->lpVtbl -> get_location(This,ppLocation)

#define IPIEHTMLDocument_get_title(This,pbstrTitle)	\
    (This)->lpVtbl -> get_title(This,pbstrTitle)

#define IPIEHTMLDocument_get_URL(This,pbstrURL)	\
    (This)->lpVtbl -> get_URL(This,pbstrURL)

#define IPIEHTMLDocument_put_bgColor(This,vtBGColor)	\
    (This)->lpVtbl -> put_bgColor(This,vtBGColor)

#define IPIEHTMLDocument_get_bgColor(This,pvtBGColor)	\
    (This)->lpVtbl -> get_bgColor(This,pvtBGColor)

#define IPIEHTMLDocument_put_fgColor(This,vtFGColor)	\
    (This)->lpVtbl -> put_fgColor(This,vtFGColor)

#define IPIEHTMLDocument_get_fgColor(This,pvtFGColor)	\
    (This)->lpVtbl -> get_fgColor(This,pvtFGColor)

#define IPIEHTMLDocument_put_linkColor(This,vtLinkColor)	\
    (This)->lpVtbl -> put_linkColor(This,vtLinkColor)

#define IPIEHTMLDocument_get_linkColor(This,pvtLinkColor)	\
    (This)->lpVtbl -> get_linkColor(This,pvtLinkColor)

#define IPIEHTMLDocument_put_alinkColor(This,vtALinkColor)	\
    (This)->lpVtbl -> put_alinkColor(This,vtALinkColor)

#define IPIEHTMLDocument_get_alinkColor(This,pvtALinkColor)	\
    (This)->lpVtbl -> get_alinkColor(This,pvtALinkColor)

#define IPIEHTMLDocument_put_vlinkColor(This,vtVLinkColor)	\
    (This)->lpVtbl -> put_vlinkColor(This,vtVLinkColor)

#define IPIEHTMLDocument_get_vlinkColor(This,pvtVLinkColor)	\
    (This)->lpVtbl -> get_vlinkColor(This,pvtVLinkColor)

#define IPIEHTMLDocument_put_cookie(This,bstrCookie)	\
    (This)->lpVtbl -> put_cookie(This,bstrCookie)

#define IPIEHTMLDocument_get_cookie(This,bstrCookie)	\
    (This)->lpVtbl -> get_cookie(This,bstrCookie)

#define IPIEHTMLDocument_put_domain(This,bstrDomain)	\
    (This)->lpVtbl -> put_domain(This,bstrDomain)

#define IPIEHTMLDocument_get_domain(This,pbstrDomain)	\
    (This)->lpVtbl -> get_domain(This,pbstrDomain)

#define IPIEHTMLDocument_open(This,bstrMimeType,vtReplace)	\
    (This)->lpVtbl -> open(This,bstrMimeType,vtReplace)

#define IPIEHTMLDocument_close(This)	\
    (This)->lpVtbl -> close(This)

#define IPIEHTMLDocument_clear(This)	\
    (This)->lpVtbl -> clear(This)

#define IPIEHTMLDocument_write(This,psaWrite)	\
    (This)->lpVtbl -> write(This,psaWrite)

#define IPIEHTMLDocument_writeln(This,psaWrite)	\
    (This)->lpVtbl -> writeln(This,psaWrite)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_toString_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrString);


void __RPC_STUB IPIEHTMLDocument_get_toString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_links_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLDocument_get_links_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_forms_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLDocument_get_forms_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_anchors_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLDocument_get_anchors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_frames_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLDocument_get_frames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_lastModified_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrLastModified);


void __RPC_STUB IPIEHTMLDocument_get_lastModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_referrer_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrReferrer);


void __RPC_STUB IPIEHTMLDocument_get_referrer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_location_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation);


void __RPC_STUB IPIEHTMLDocument_get_location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_title_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);


void __RPC_STUB IPIEHTMLDocument_get_title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_URL_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrURL);


void __RPC_STUB IPIEHTMLDocument_get_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_bgColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ VARIANT vtBGColor);


void __RPC_STUB IPIEHTMLDocument_put_bgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_bgColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtBGColor);


void __RPC_STUB IPIEHTMLDocument_get_bgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_fgColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ VARIANT vtFGColor);


void __RPC_STUB IPIEHTMLDocument_put_fgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_fgColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtFGColor);


void __RPC_STUB IPIEHTMLDocument_get_fgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_linkColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ VARIANT vtLinkColor);


void __RPC_STUB IPIEHTMLDocument_put_linkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_linkColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtLinkColor);


void __RPC_STUB IPIEHTMLDocument_get_linkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_alinkColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ VARIANT vtALinkColor);


void __RPC_STUB IPIEHTMLDocument_put_alinkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_alinkColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtALinkColor);


void __RPC_STUB IPIEHTMLDocument_get_alinkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_vlinkColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ VARIANT vtVLinkColor);


void __RPC_STUB IPIEHTMLDocument_put_vlinkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_vlinkColor_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtVLinkColor);


void __RPC_STUB IPIEHTMLDocument_get_vlinkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_cookie_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ BSTR bstrCookie);


void __RPC_STUB IPIEHTMLDocument_put_cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_cookie_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrCookie);


void __RPC_STUB IPIEHTMLDocument_get_cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_put_domain_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ BSTR bstrDomain);


void __RPC_STUB IPIEHTMLDocument_put_domain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_get_domain_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain);


void __RPC_STUB IPIEHTMLDocument_get_domain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_open_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [defaultvalue][in] */ BSTR bstrMimeType,
    /* [optional][in] */ VARIANT vtReplace);


void __RPC_STUB IPIEHTMLDocument_open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_close_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This);


void __RPC_STUB IPIEHTMLDocument_close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_clear_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This);


void __RPC_STUB IPIEHTMLDocument_clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][vararg] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_write_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * psaWrite);


void __RPC_STUB IPIEHTMLDocument_write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][vararg] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument_writeln_Proxy( 
    IPIEHTMLDocument __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * psaWrite);


void __RPC_STUB IPIEHTMLDocument_writeln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLDocument_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLDocument2_INTERFACE_DEFINED__
#define __IPIEHTMLDocument2_INTERFACE_DEFINED__

/* interface IPIEHTMLDocument2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLDocument2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE21F1")
    IPIEHTMLDocument2 : public IPIEHTMLDocument
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_images( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLDocument2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLDocument2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLDocument2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_links )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_forms )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_anchors )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_frames )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastModified )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastModified);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_referrer )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrReferrer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_location )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_title )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URL )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURL);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_bgColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT vtBGColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_bgColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBGColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_fgColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT vtFGColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fgColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtFGColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_linkColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT vtLinkColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_linkColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtLinkColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_alinkColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT vtALinkColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_alinkColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtALinkColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_vlinkColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT vtVLinkColor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vlinkColor )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtVLinkColor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cookie )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ BSTR bstrCookie);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cookie )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrCookie);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_domain )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ BSTR bstrDomain);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_domain )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomain);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *open )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMimeType,
            /* [optional][in] */ VARIANT vtReplace);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *close )( 
            IPIEHTMLDocument2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clear )( 
            IPIEHTMLDocument2 __RPC_FAR * This);
        
        /* [id][vararg] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *write )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * psaWrite);
        
        /* [id][vararg] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *writeln )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * psaWrite);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_images )( 
            IPIEHTMLDocument2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        END_INTERFACE
    } IPIEHTMLDocument2Vtbl;

    interface IPIEHTMLDocument2
    {
        CONST_VTBL struct IPIEHTMLDocument2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLDocument2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLDocument2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLDocument2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLDocument2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLDocument2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLDocument2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLDocument2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLDocument2_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLDocument2_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLDocument2_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLDocument2_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLDocument2_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLDocument2_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLDocument2_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLDocument2_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLDocument2_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLDocument2_get_links(This,ppElemCollection)	\
    (This)->lpVtbl -> get_links(This,ppElemCollection)

#define IPIEHTMLDocument2_get_forms(This,ppElemCollection)	\
    (This)->lpVtbl -> get_forms(This,ppElemCollection)

#define IPIEHTMLDocument2_get_anchors(This,ppElemCollection)	\
    (This)->lpVtbl -> get_anchors(This,ppElemCollection)

#define IPIEHTMLDocument2_get_frames(This,ppElemCollection)	\
    (This)->lpVtbl -> get_frames(This,ppElemCollection)

#define IPIEHTMLDocument2_get_lastModified(This,pbstrLastModified)	\
    (This)->lpVtbl -> get_lastModified(This,pbstrLastModified)

#define IPIEHTMLDocument2_get_referrer(This,pbstrReferrer)	\
    (This)->lpVtbl -> get_referrer(This,pbstrReferrer)

#define IPIEHTMLDocument2_get_location(This,ppLocation)	\
    (This)->lpVtbl -> get_location(This,ppLocation)

#define IPIEHTMLDocument2_get_title(This,pbstrTitle)	\
    (This)->lpVtbl -> get_title(This,pbstrTitle)

#define IPIEHTMLDocument2_get_URL(This,pbstrURL)	\
    (This)->lpVtbl -> get_URL(This,pbstrURL)

#define IPIEHTMLDocument2_put_bgColor(This,vtBGColor)	\
    (This)->lpVtbl -> put_bgColor(This,vtBGColor)

#define IPIEHTMLDocument2_get_bgColor(This,pvtBGColor)	\
    (This)->lpVtbl -> get_bgColor(This,pvtBGColor)

#define IPIEHTMLDocument2_put_fgColor(This,vtFGColor)	\
    (This)->lpVtbl -> put_fgColor(This,vtFGColor)

#define IPIEHTMLDocument2_get_fgColor(This,pvtFGColor)	\
    (This)->lpVtbl -> get_fgColor(This,pvtFGColor)

#define IPIEHTMLDocument2_put_linkColor(This,vtLinkColor)	\
    (This)->lpVtbl -> put_linkColor(This,vtLinkColor)

#define IPIEHTMLDocument2_get_linkColor(This,pvtLinkColor)	\
    (This)->lpVtbl -> get_linkColor(This,pvtLinkColor)

#define IPIEHTMLDocument2_put_alinkColor(This,vtALinkColor)	\
    (This)->lpVtbl -> put_alinkColor(This,vtALinkColor)

#define IPIEHTMLDocument2_get_alinkColor(This,pvtALinkColor)	\
    (This)->lpVtbl -> get_alinkColor(This,pvtALinkColor)

#define IPIEHTMLDocument2_put_vlinkColor(This,vtVLinkColor)	\
    (This)->lpVtbl -> put_vlinkColor(This,vtVLinkColor)

#define IPIEHTMLDocument2_get_vlinkColor(This,pvtVLinkColor)	\
    (This)->lpVtbl -> get_vlinkColor(This,pvtVLinkColor)

#define IPIEHTMLDocument2_put_cookie(This,bstrCookie)	\
    (This)->lpVtbl -> put_cookie(This,bstrCookie)

#define IPIEHTMLDocument2_get_cookie(This,bstrCookie)	\
    (This)->lpVtbl -> get_cookie(This,bstrCookie)

#define IPIEHTMLDocument2_put_domain(This,bstrDomain)	\
    (This)->lpVtbl -> put_domain(This,bstrDomain)

#define IPIEHTMLDocument2_get_domain(This,pbstrDomain)	\
    (This)->lpVtbl -> get_domain(This,pbstrDomain)

#define IPIEHTMLDocument2_open(This,bstrMimeType,vtReplace)	\
    (This)->lpVtbl -> open(This,bstrMimeType,vtReplace)

#define IPIEHTMLDocument2_close(This)	\
    (This)->lpVtbl -> close(This)

#define IPIEHTMLDocument2_clear(This)	\
    (This)->lpVtbl -> clear(This)

#define IPIEHTMLDocument2_write(This,psaWrite)	\
    (This)->lpVtbl -> write(This,psaWrite)

#define IPIEHTMLDocument2_writeln(This,psaWrite)	\
    (This)->lpVtbl -> writeln(This,psaWrite)


#define IPIEHTMLDocument2_get_images(This,ppElemCollection)	\
    (This)->lpVtbl -> get_images(This,ppElemCollection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDocument2_get_images_Proxy( 
    IPIEHTMLDocument2 __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLDocument2_get_images_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLDocument2_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLFrameSetElement_INTERFACE_DEFINED__
#define __IPIEHTMLFrameSetElement_INTERFACE_DEFINED__

/* interface IPIEHTMLFrameSetElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLFrameSetElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2122")
    IPIEHTMLFrameSetElement : public IDispatchEx
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_rows( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRows) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_cols( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCols) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_border( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBorder) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_borderColor( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBorderColor) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLFrameSetElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rows )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRows);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cols )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCols);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_border )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBorder);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_borderColor )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtBorderColor);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLFrameSetElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        END_INTERFACE
    } IPIEHTMLFrameSetElementVtbl;

    interface IPIEHTMLFrameSetElement
    {
        CONST_VTBL struct IPIEHTMLFrameSetElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLFrameSetElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLFrameSetElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLFrameSetElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLFrameSetElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLFrameSetElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLFrameSetElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLFrameSetElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLFrameSetElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLFrameSetElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLFrameSetElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLFrameSetElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLFrameSetElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLFrameSetElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLFrameSetElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLFrameSetElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLFrameSetElement_get_document(This,ppDocument)	\
    (This)->lpVtbl -> get_document(This,ppDocument)

#define IPIEHTMLFrameSetElement_get_rows(This,pbstrRows)	\
    (This)->lpVtbl -> get_rows(This,pbstrRows)

#define IPIEHTMLFrameSetElement_get_cols(This,pbstrCols)	\
    (This)->lpVtbl -> get_cols(This,pbstrCols)

#define IPIEHTMLFrameSetElement_get_border(This,pvtBorder)	\
    (This)->lpVtbl -> get_border(This,pvtBorder)

#define IPIEHTMLFrameSetElement_get_borderColor(This,pvtBorderColor)	\
    (This)->lpVtbl -> get_borderColor(This,pvtBorderColor)

#define IPIEHTMLFrameSetElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameSetElement_get_document_Proxy( 
    IPIEHTMLFrameSetElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);


void __RPC_STUB IPIEHTMLFrameSetElement_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameSetElement_get_rows_Proxy( 
    IPIEHTMLFrameSetElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRows);


void __RPC_STUB IPIEHTMLFrameSetElement_get_rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameSetElement_get_cols_Proxy( 
    IPIEHTMLFrameSetElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCols);


void __RPC_STUB IPIEHTMLFrameSetElement_get_cols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameSetElement_get_border_Proxy( 
    IPIEHTMLFrameSetElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtBorder);


void __RPC_STUB IPIEHTMLFrameSetElement_get_border_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameSetElement_get_borderColor_Proxy( 
    IPIEHTMLFrameSetElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtBorderColor);


void __RPC_STUB IPIEHTMLFrameSetElement_get_borderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameSetElement_get_name_Proxy( 
    IPIEHTMLFrameSetElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEHTMLFrameSetElement_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLFrameSetElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLFrameSetElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLFrameSetElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLFrameSetElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLFrameSetElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE2122")
    PIEHTMLFrameSetElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLFrameSetElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLFrameSetElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLFrameSetElementEventsVtbl;

    interface PIEHTMLFrameSetElementEvents
    {
        CONST_VTBL struct PIEHTMLFrameSetElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLFrameSetElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLFrameSetElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLFrameSetElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLFrameSetElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLFrameSetElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLFrameSetElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLFrameSetElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLFrameSetElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLFrameSetElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2122")
PIEHTMLFrameSetElement;
#endif

#ifndef __IPIEHTMLFrameElement_INTERFACE_DEFINED__
#define __IPIEHTMLFrameElement_INTERFACE_DEFINED__

/* interface IPIEHTMLFrameElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLFrameElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2121")
    IPIEHTMLFrameElement : public IDispatchEx
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_src( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSRC) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_marginWidth( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtMarginWidth) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_marginHeight( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvtMarginHeight) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_noResize( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbNoResize) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_scrolling( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrScrolling) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLFrameElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLFrameElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLFrameElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_src )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSRC);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginWidth )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtMarginWidth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginHeight )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtMarginHeight);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_noResize )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbNoResize);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_scrolling )( 
            IPIEHTMLFrameElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrScrolling);
        
        END_INTERFACE
    } IPIEHTMLFrameElementVtbl;

    interface IPIEHTMLFrameElement
    {
        CONST_VTBL struct IPIEHTMLFrameElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLFrameElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLFrameElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLFrameElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLFrameElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLFrameElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLFrameElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLFrameElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLFrameElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLFrameElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLFrameElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLFrameElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLFrameElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLFrameElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLFrameElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLFrameElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLFrameElement_get_document(This,ppDocument)	\
    (This)->lpVtbl -> get_document(This,ppDocument)

#define IPIEHTMLFrameElement_get_src(This,pbstrSRC)	\
    (This)->lpVtbl -> get_src(This,pbstrSRC)

#define IPIEHTMLFrameElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLFrameElement_get_marginWidth(This,pvtMarginWidth)	\
    (This)->lpVtbl -> get_marginWidth(This,pvtMarginWidth)

#define IPIEHTMLFrameElement_get_marginHeight(This,pvtMarginHeight)	\
    (This)->lpVtbl -> get_marginHeight(This,pvtMarginHeight)

#define IPIEHTMLFrameElement_get_noResize(This,pvbNoResize)	\
    (This)->lpVtbl -> get_noResize(This,pvbNoResize)

#define IPIEHTMLFrameElement_get_scrolling(This,pbstrScrolling)	\
    (This)->lpVtbl -> get_scrolling(This,pbstrScrolling)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_document_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);


void __RPC_STUB IPIEHTMLFrameElement_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_src_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrSRC);


void __RPC_STUB IPIEHTMLFrameElement_get_src_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_name_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEHTMLFrameElement_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_marginWidth_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtMarginWidth);


void __RPC_STUB IPIEHTMLFrameElement_get_marginWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_marginHeight_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtMarginHeight);


void __RPC_STUB IPIEHTMLFrameElement_get_marginHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_noResize_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbNoResize);


void __RPC_STUB IPIEHTMLFrameElement_get_noResize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFrameElement_get_scrolling_Proxy( 
    IPIEHTMLFrameElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrScrolling);


void __RPC_STUB IPIEHTMLFrameElement_get_scrolling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLFrameElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLFrameElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2121")
PIEHTMLFrameElement;
#endif

#ifndef __IPIEHTMLScreen_INTERFACE_DEFINED__
#define __IPIEHTMLScreen_INTERFACE_DEFINED__

/* interface IPIEHTMLScreen */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLScreen;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2120")
    IPIEHTMLScreen : public IDispatchEx
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_colorDepth( 
            /* [out][retval] */ long __RPC_FAR *plColorDepth) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_width( 
            /* [out][retval] */ long __RPC_FAR *plWidth) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_height( 
            /* [out][retval] */ long __RPC_FAR *plHeight) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_availWidth( 
            /* [out][retval] */ long __RPC_FAR *plAvailWidth) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_availHeight( 
            /* [out][retval] */ long __RPC_FAR *plAvailHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLScreenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLScreen __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLScreen __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_colorDepth )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plColorDepth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_width )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plWidth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_height )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plHeight);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_availWidth )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plAvailWidth);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_availHeight )( 
            IPIEHTMLScreen __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plAvailHeight);
        
        END_INTERFACE
    } IPIEHTMLScreenVtbl;

    interface IPIEHTMLScreen
    {
        CONST_VTBL struct IPIEHTMLScreenVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLScreen_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLScreen_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLScreen_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLScreen_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLScreen_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLScreen_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLScreen_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLScreen_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLScreen_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLScreen_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLScreen_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLScreen_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLScreen_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLScreen_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLScreen_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLScreen_get_colorDepth(This,plColorDepth)	\
    (This)->lpVtbl -> get_colorDepth(This,plColorDepth)

#define IPIEHTMLScreen_get_width(This,plWidth)	\
    (This)->lpVtbl -> get_width(This,plWidth)

#define IPIEHTMLScreen_get_height(This,plHeight)	\
    (This)->lpVtbl -> get_height(This,plHeight)

#define IPIEHTMLScreen_get_availWidth(This,plAvailWidth)	\
    (This)->lpVtbl -> get_availWidth(This,plAvailWidth)

#define IPIEHTMLScreen_get_availHeight(This,plAvailHeight)	\
    (This)->lpVtbl -> get_availHeight(This,plAvailHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLScreen_get_colorDepth_Proxy( 
    IPIEHTMLScreen __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plColorDepth);


void __RPC_STUB IPIEHTMLScreen_get_colorDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLScreen_get_width_Proxy( 
    IPIEHTMLScreen __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plWidth);


void __RPC_STUB IPIEHTMLScreen_get_width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLScreen_get_height_Proxy( 
    IPIEHTMLScreen __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plHeight);


void __RPC_STUB IPIEHTMLScreen_get_height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLScreen_get_availWidth_Proxy( 
    IPIEHTMLScreen __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plAvailWidth);


void __RPC_STUB IPIEHTMLScreen_get_availWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLScreen_get_availHeight_Proxy( 
    IPIEHTMLScreen __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plAvailHeight);


void __RPC_STUB IPIEHTMLScreen_get_availHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLScreen_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLImgElement_INTERFACE_DEFINED__
#define __IPIEHTMLImgElement_INTERFACE_DEFINED__

/* interface IPIEHTMLImgElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLImgElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2204")
    IPIEHTMLImgElement : public IDispatchEx
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_border( 
            /* [in] */ VARIANT vtBorder) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_border( 
            /* [out][retval] */ VARIANT __RPC_FAR *pvtBorder) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_vspace( 
            /* [out][retval] */ long __RPC_FAR *plVSpace) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_hspace( 
            /* [out][retval] */ long __RPC_FAR *plHSpace) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_alt( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrAlt) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_src( 
            /* [in] */ BSTR bstrSrc) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_src( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrSrc) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_width( 
            long lWidth) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_width( 
            /* [out][retval] */ long __RPC_FAR *plWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_height( 
            long lHeight) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_height( 
            /* [out][retval] */ long __RPC_FAR *plHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLImgElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLImgElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLImgElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_border )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ VARIANT vtBorder);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_border )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ VARIANT __RPC_FAR *pvtBorder);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vspace )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plVSpace);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hspace )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plHSpace);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_alt )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrAlt);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_src )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_src )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrSrc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_width )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            long lWidth);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_width )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_height )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            long lHeight);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_height )( 
            IPIEHTMLImgElement __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plHeight);
        
        END_INTERFACE
    } IPIEHTMLImgElementVtbl;

    interface IPIEHTMLImgElement
    {
        CONST_VTBL struct IPIEHTMLImgElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLImgElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLImgElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLImgElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLImgElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLImgElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLImgElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLImgElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLImgElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLImgElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLImgElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLImgElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLImgElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLImgElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLImgElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLImgElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLImgElement_put_border(This,vtBorder)	\
    (This)->lpVtbl -> put_border(This,vtBorder)

#define IPIEHTMLImgElement_get_border(This,pvtBorder)	\
    (This)->lpVtbl -> get_border(This,pvtBorder)

#define IPIEHTMLImgElement_get_vspace(This,plVSpace)	\
    (This)->lpVtbl -> get_vspace(This,plVSpace)

#define IPIEHTMLImgElement_get_hspace(This,plHSpace)	\
    (This)->lpVtbl -> get_hspace(This,plHSpace)

#define IPIEHTMLImgElement_get_alt(This,pbstrAlt)	\
    (This)->lpVtbl -> get_alt(This,pbstrAlt)

#define IPIEHTMLImgElement_put_src(This,bstrSrc)	\
    (This)->lpVtbl -> put_src(This,bstrSrc)

#define IPIEHTMLImgElement_get_src(This,pbstrSrc)	\
    (This)->lpVtbl -> get_src(This,pbstrSrc)

#define IPIEHTMLImgElement_put_width(This,lWidth)	\
    (This)->lpVtbl -> put_width(This,lWidth)

#define IPIEHTMLImgElement_get_width(This,plWidth)	\
    (This)->lpVtbl -> get_width(This,plWidth)

#define IPIEHTMLImgElement_put_height(This,lHeight)	\
    (This)->lpVtbl -> put_height(This,lHeight)

#define IPIEHTMLImgElement_get_height(This,plHeight)	\
    (This)->lpVtbl -> get_height(This,plHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_put_border_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [in] */ VARIANT vtBorder);


void __RPC_STUB IPIEHTMLImgElement_put_border_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_border_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ VARIANT __RPC_FAR *pvtBorder);


void __RPC_STUB IPIEHTMLImgElement_get_border_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_vspace_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plVSpace);


void __RPC_STUB IPIEHTMLImgElement_get_vspace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_hspace_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plHSpace);


void __RPC_STUB IPIEHTMLImgElement_get_hspace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_alt_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrAlt);


void __RPC_STUB IPIEHTMLImgElement_get_alt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_put_src_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc);


void __RPC_STUB IPIEHTMLImgElement_put_src_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_src_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrSrc);


void __RPC_STUB IPIEHTMLImgElement_get_src_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_put_width_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    long lWidth);


void __RPC_STUB IPIEHTMLImgElement_put_width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_width_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plWidth);


void __RPC_STUB IPIEHTMLImgElement_get_width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_put_height_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    long lHeight);


void __RPC_STUB IPIEHTMLImgElement_put_height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImgElement_get_height_Proxy( 
    IPIEHTMLImgElement __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plHeight);


void __RPC_STUB IPIEHTMLImgElement_get_height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLImgElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLImgElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2204")
PIEHTMLImgElement;
#endif

#ifndef __IPIEHTMLImageElementFactory_INTERFACE_DEFINED__
#define __IPIEHTMLImageElementFactory_INTERFACE_DEFINED__

/* interface IPIEHTMLImageElementFactory */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLImageElementFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE22F4")
    IPIEHTMLImageElementFactory : public IDispatchEx
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE create( 
            /* [in][optional] */ VARIANT vtWidth,
            /* [in][optional] */ VARIANT vtHeight,
            /* [out][retval] */ IPIEHTMLImgElement __RPC_FAR *__RPC_FAR *ppImgElement) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLImageElementFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *create )( 
            IPIEHTMLImageElementFactory __RPC_FAR * This,
            /* [in][optional] */ VARIANT vtWidth,
            /* [in][optional] */ VARIANT vtHeight,
            /* [out][retval] */ IPIEHTMLImgElement __RPC_FAR *__RPC_FAR *ppImgElement);
        
        END_INTERFACE
    } IPIEHTMLImageElementFactoryVtbl;

    interface IPIEHTMLImageElementFactory
    {
        CONST_VTBL struct IPIEHTMLImageElementFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLImageElementFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLImageElementFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLImageElementFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLImageElementFactory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLImageElementFactory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLImageElementFactory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLImageElementFactory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLImageElementFactory_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLImageElementFactory_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLImageElementFactory_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLImageElementFactory_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLImageElementFactory_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLImageElementFactory_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLImageElementFactory_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLImageElementFactory_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLImageElementFactory_create(This,vtWidth,vtHeight,ppImgElement)	\
    (This)->lpVtbl -> create(This,vtWidth,vtHeight,ppImgElement)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLImageElementFactory_create_Proxy( 
    IPIEHTMLImageElementFactory __RPC_FAR * This,
    /* [in][optional] */ VARIANT vtWidth,
    /* [in][optional] */ VARIANT vtHeight,
    /* [out][retval] */ IPIEHTMLImgElement __RPC_FAR *__RPC_FAR *ppImgElement);


void __RPC_STUB IPIEHTMLImageElementFactory_create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLImageElementFactory_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLOptionElement_INTERFACE_DEFINED__
#define __IPIEHTMLOptionElement_INTERFACE_DEFINED__

/* interface IPIEHTMLOptionElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLOptionElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE210B")
    IPIEHTMLOptionElement : public IDispatchEx
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_selected( 
            /* [in] */ VARIANT_BOOL vbSelected) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_selected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbSelected) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_value( 
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_defaultSelected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDefaultSelected) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_index( 
            /* [retval][out] */ long __RPC_FAR *plIndex) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_text( 
            /* [in] */ BSTR bstrText) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_text( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLOptionElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLOptionElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLOptionElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_selected )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbSelected);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_selected )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbSelected);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_defaultSelected )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDefaultSelected);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_index )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plIndex);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_text )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [in] */ BSTR bstrText);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_text )( 
            IPIEHTMLOptionElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        END_INTERFACE
    } IPIEHTMLOptionElementVtbl;

    interface IPIEHTMLOptionElement
    {
        CONST_VTBL struct IPIEHTMLOptionElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLOptionElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLOptionElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLOptionElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLOptionElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLOptionElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLOptionElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLOptionElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLOptionElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLOptionElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLOptionElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLOptionElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLOptionElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLOptionElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLOptionElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLOptionElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLOptionElement_put_selected(This,vbSelected)	\
    (This)->lpVtbl -> put_selected(This,vbSelected)

#define IPIEHTMLOptionElement_get_selected(This,pvbSelected)	\
    (This)->lpVtbl -> get_selected(This,pvbSelected)

#define IPIEHTMLOptionElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLOptionElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLOptionElement_get_defaultSelected(This,pvbDefaultSelected)	\
    (This)->lpVtbl -> get_defaultSelected(This,pvbDefaultSelected)

#define IPIEHTMLOptionElement_get_index(This,plIndex)	\
    (This)->lpVtbl -> get_index(This,plIndex)

#define IPIEHTMLOptionElement_put_text(This,bstrText)	\
    (This)->lpVtbl -> put_text(This,bstrText)

#define IPIEHTMLOptionElement_get_text(This,pbstrText)	\
    (This)->lpVtbl -> get_text(This,pbstrText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_put_selected_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbSelected);


void __RPC_STUB IPIEHTMLOptionElement_put_selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_get_selected_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbSelected);


void __RPC_STUB IPIEHTMLOptionElement_get_selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_put_value_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB IPIEHTMLOptionElement_put_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_get_value_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);


void __RPC_STUB IPIEHTMLOptionElement_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_get_defaultSelected_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDefaultSelected);


void __RPC_STUB IPIEHTMLOptionElement_get_defaultSelected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_get_index_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plIndex);


void __RPC_STUB IPIEHTMLOptionElement_get_index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_put_text_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [in] */ BSTR bstrText);


void __RPC_STUB IPIEHTMLOptionElement_put_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElement_get_text_Proxy( 
    IPIEHTMLOptionElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrText);


void __RPC_STUB IPIEHTMLOptionElement_get_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLOptionElement_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLOptionElementFactory_INTERFACE_DEFINED__
#define __IPIEHTMLOptionElementFactory_INTERFACE_DEFINED__

/* interface IPIEHTMLOptionElementFactory */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLOptionElementFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE21FB")
    IPIEHTMLOptionElementFactory : public IDispatchEx
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE create( 
            /* [in][optional] */ VARIANT vtText,
            /* [in][optional] */ VARIANT vtValue,
            /* [in][optional] */ VARIANT vtDefaultSelected,
            /* [in][optional] */ VARIANT vtSelected,
            /* [out][retval] */ IPIEHTMLOptionElement __RPC_FAR *__RPC_FAR *ppOptionElement) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLOptionElementFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *create )( 
            IPIEHTMLOptionElementFactory __RPC_FAR * This,
            /* [in][optional] */ VARIANT vtText,
            /* [in][optional] */ VARIANT vtValue,
            /* [in][optional] */ VARIANT vtDefaultSelected,
            /* [in][optional] */ VARIANT vtSelected,
            /* [out][retval] */ IPIEHTMLOptionElement __RPC_FAR *__RPC_FAR *ppOptionElement);
        
        END_INTERFACE
    } IPIEHTMLOptionElementFactoryVtbl;

    interface IPIEHTMLOptionElementFactory
    {
        CONST_VTBL struct IPIEHTMLOptionElementFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLOptionElementFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLOptionElementFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLOptionElementFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLOptionElementFactory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLOptionElementFactory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLOptionElementFactory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLOptionElementFactory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLOptionElementFactory_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLOptionElementFactory_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLOptionElementFactory_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLOptionElementFactory_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLOptionElementFactory_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLOptionElementFactory_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLOptionElementFactory_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLOptionElementFactory_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLOptionElementFactory_create(This,vtText,vtValue,vtDefaultSelected,vtSelected,ppOptionElement)	\
    (This)->lpVtbl -> create(This,vtText,vtValue,vtDefaultSelected,vtSelected,ppOptionElement)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionElementFactory_create_Proxy( 
    IPIEHTMLOptionElementFactory __RPC_FAR * This,
    /* [in][optional] */ VARIANT vtText,
    /* [in][optional] */ VARIANT vtValue,
    /* [in][optional] */ VARIANT vtDefaultSelected,
    /* [in][optional] */ VARIANT vtSelected,
    /* [out][retval] */ IPIEHTMLOptionElement __RPC_FAR *__RPC_FAR *ppOptionElement);


void __RPC_STUB IPIEHTMLOptionElementFactory_create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLOptionElementFactory_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLWindow_INTERFACE_DEFINED__
#define __IPIEHTMLWindow_INTERFACE_DEFINED__

/* interface IPIEHTMLWindow */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2102")
    IPIEHTMLWindow : public IDispatchEx
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_toString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_location( 
            /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_history( 
            /* [retval][out] */ IPIEOmHistory __RPC_FAR *__RPC_FAR *ppOmHistory) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_navigator( 
            /* [retval][out] */ IPIEOmNavigator __RPC_FAR *__RPC_FAR *ppOmNavigator) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowParent) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_self( 
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowSelf) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_top( 
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowTop) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_window( 
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindow) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_frames( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_screen( 
            /* [retval][out] */ IPIEHTMLScreen __RPC_FAR *__RPC_FAR *ppScreen) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plLength) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setTimeout( 
            /* [in] */ BSTR bstrExpression,
            /* [in] */ long lMS,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
            /* [retval][out] */ long __RPC_FAR *plTimerID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE clearTimeout( 
            /* [in] */ long lTimerID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE alert( 
            /* [defaultvalue][in] */ BSTR bstrMessage = L"") = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE confirm( 
            /* [defaultvalue][in] */ BSTR bstrMessage,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbConfirmed) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE prompt( 
            /* [defaultvalue][in] */ BSTR bstrMessage,
            /* [defaultvalue][in] */ BSTR bstrDefaultValue,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtText) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE close( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE focus( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE blur( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE navigate( 
            /* [in] */ BSTR bstrURL) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE open( 
            /* [defaultvalue][in] */ BSTR bstrURL,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtName,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtFeatures,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtReplace,
            /* [out][retval] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE scroll( 
            /* [in] */ long lX,
            /* [in] */ long lY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_location )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_history )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEOmHistory __RPC_FAR *__RPC_FAR *ppOmHistory);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_navigator )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEOmNavigator __RPC_FAR *__RPC_FAR *ppOmNavigator);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowParent);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_self )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowSelf);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_top )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowTop);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_window )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindow);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_frames )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_screen )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLScreen __RPC_FAR *__RPC_FAR *ppScreen);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTimeout )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ BSTR bstrExpression,
            /* [in] */ long lMS,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
            /* [retval][out] */ long __RPC_FAR *plTimerID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clearTimeout )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ long lTimerID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *alert )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMessage);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *confirm )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMessage,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbConfirmed);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *prompt )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMessage,
            /* [defaultvalue][in] */ BSTR bstrDefaultValue,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtText);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *close )( 
            IPIEHTMLWindow __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLWindow __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLWindow __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *navigate )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ BSTR bstrURL);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *open )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrURL,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtName,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtFeatures,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtReplace,
            /* [out][retval] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *scroll )( 
            IPIEHTMLWindow __RPC_FAR * This,
            /* [in] */ long lX,
            /* [in] */ long lY);
        
        END_INTERFACE
    } IPIEHTMLWindowVtbl;

    interface IPIEHTMLWindow
    {
        CONST_VTBL struct IPIEHTMLWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLWindow_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLWindow_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLWindow_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLWindow_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLWindow_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLWindow_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLWindow_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLWindow_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLWindow_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLWindow_get_location(This,ppLocation)	\
    (This)->lpVtbl -> get_location(This,ppLocation)

#define IPIEHTMLWindow_get_history(This,ppOmHistory)	\
    (This)->lpVtbl -> get_history(This,ppOmHistory)

#define IPIEHTMLWindow_get_navigator(This,ppOmNavigator)	\
    (This)->lpVtbl -> get_navigator(This,ppOmNavigator)

#define IPIEHTMLWindow_get_document(This,ppDocument)	\
    (This)->lpVtbl -> get_document(This,ppDocument)

#define IPIEHTMLWindow_get_parent(This,ppWindowParent)	\
    (This)->lpVtbl -> get_parent(This,ppWindowParent)

#define IPIEHTMLWindow_get_self(This,ppWindowSelf)	\
    (This)->lpVtbl -> get_self(This,ppWindowSelf)

#define IPIEHTMLWindow_get_top(This,ppWindowTop)	\
    (This)->lpVtbl -> get_top(This,ppWindowTop)

#define IPIEHTMLWindow_get_window(This,ppWindow)	\
    (This)->lpVtbl -> get_window(This,ppWindow)

#define IPIEHTMLWindow_get_frames(This,ppElemCollection)	\
    (This)->lpVtbl -> get_frames(This,ppElemCollection)

#define IPIEHTMLWindow_get_screen(This,ppScreen)	\
    (This)->lpVtbl -> get_screen(This,ppScreen)

#define IPIEHTMLWindow_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLWindow_put_name(This,bstrName)	\
    (This)->lpVtbl -> put_name(This,bstrName)

#define IPIEHTMLWindow_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLWindow_setTimeout(This,bstrExpression,lMS,pvtLanguage,plTimerID)	\
    (This)->lpVtbl -> setTimeout(This,bstrExpression,lMS,pvtLanguage,plTimerID)

#define IPIEHTMLWindow_clearTimeout(This,lTimerID)	\
    (This)->lpVtbl -> clearTimeout(This,lTimerID)

#define IPIEHTMLWindow_alert(This,bstrMessage)	\
    (This)->lpVtbl -> alert(This,bstrMessage)

#define IPIEHTMLWindow_confirm(This,bstrMessage,pvbConfirmed)	\
    (This)->lpVtbl -> confirm(This,bstrMessage,pvbConfirmed)

#define IPIEHTMLWindow_prompt(This,bstrMessage,bstrDefaultValue,pvtText)	\
    (This)->lpVtbl -> prompt(This,bstrMessage,bstrDefaultValue,pvtText)

#define IPIEHTMLWindow_close(This)	\
    (This)->lpVtbl -> close(This)

#define IPIEHTMLWindow_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLWindow_blur(This)	\
    (This)->lpVtbl -> blur(This)

#define IPIEHTMLWindow_navigate(This,bstrURL)	\
    (This)->lpVtbl -> navigate(This,bstrURL)

#define IPIEHTMLWindow_open(This,bstrURL,pvtName,pvtFeatures,pvtReplace,ppWindowResult)	\
    (This)->lpVtbl -> open(This,bstrURL,pvtName,pvtFeatures,pvtReplace,ppWindowResult)

#define IPIEHTMLWindow_scroll(This,lX,lY)	\
    (This)->lpVtbl -> scroll(This,lX,lY)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_toString_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrString);


void __RPC_STUB IPIEHTMLWindow_get_toString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_location_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation);


void __RPC_STUB IPIEHTMLWindow_get_location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_history_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEOmHistory __RPC_FAR *__RPC_FAR *ppOmHistory);


void __RPC_STUB IPIEHTMLWindow_get_history_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_navigator_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEOmNavigator __RPC_FAR *__RPC_FAR *ppOmNavigator);


void __RPC_STUB IPIEHTMLWindow_get_navigator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_document_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);


void __RPC_STUB IPIEHTMLWindow_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_parent_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowParent);


void __RPC_STUB IPIEHTMLWindow_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_self_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowSelf);


void __RPC_STUB IPIEHTMLWindow_get_self_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_top_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowTop);


void __RPC_STUB IPIEHTMLWindow_get_top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_window_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindow);


void __RPC_STUB IPIEHTMLWindow_get_window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_frames_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLWindow_get_frames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_screen_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLScreen __RPC_FAR *__RPC_FAR *ppScreen);


void __RPC_STUB IPIEHTMLWindow_get_screen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_length_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLength);


void __RPC_STUB IPIEHTMLWindow_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_put_name_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IPIEHTMLWindow_put_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_get_name_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEHTMLWindow_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_setTimeout_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [in] */ BSTR bstrExpression,
    /* [in] */ long lMS,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
    /* [retval][out] */ long __RPC_FAR *plTimerID);


void __RPC_STUB IPIEHTMLWindow_setTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_clearTimeout_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [in] */ long lTimerID);


void __RPC_STUB IPIEHTMLWindow_clearTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_alert_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [defaultvalue][in] */ BSTR bstrMessage);


void __RPC_STUB IPIEHTMLWindow_alert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_confirm_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [defaultvalue][in] */ BSTR bstrMessage,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbConfirmed);


void __RPC_STUB IPIEHTMLWindow_confirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_prompt_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [defaultvalue][in] */ BSTR bstrMessage,
    /* [defaultvalue][in] */ BSTR bstrDefaultValue,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtText);


void __RPC_STUB IPIEHTMLWindow_prompt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_close_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This);


void __RPC_STUB IPIEHTMLWindow_close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_focus_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This);


void __RPC_STUB IPIEHTMLWindow_focus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_blur_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This);


void __RPC_STUB IPIEHTMLWindow_blur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_navigate_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [in] */ BSTR bstrURL);


void __RPC_STUB IPIEHTMLWindow_navigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_open_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [defaultvalue][in] */ BSTR bstrURL,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtName,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtFeatures,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtReplace,
    /* [out][retval] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowResult);


void __RPC_STUB IPIEHTMLWindow_open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow_scroll_Proxy( 
    IPIEHTMLWindow __RPC_FAR * This,
    /* [in] */ long lX,
    /* [in] */ long lY);


void __RPC_STUB IPIEHTMLWindow_scroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLWindow_INTERFACE_DEFINED__ */


#ifndef __IPIEHTMLWindow2_INTERFACE_DEFINED__
#define __IPIEHTMLWindow2_INTERFACE_DEFINED__

/* interface IPIEHTMLWindow2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLWindow2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE21F2")
    IPIEHTMLWindow2 : public IPIEHTMLWindow
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [out][retval] */ IPIEHTMLImageElementFactory __RPC_FAR *__RPC_FAR *ppImageFactory) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Option( 
            /* [out][retval] */ IPIEHTMLOptionElementFactory __RPC_FAR *__RPC_FAR *ppOptionFactory) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setTimeout( 
            /* [in] */ VARIANT __RPC_FAR *pvtExpression,
            /* [in] */ long lMS,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
            /* [retval][out] */ long __RPC_FAR *plTimerID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLWindow2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLWindow2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLWindow2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_location )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLLocation __RPC_FAR *__RPC_FAR *ppLocation);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_history )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEOmHistory __RPC_FAR *__RPC_FAR *ppOmHistory);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_navigator )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEOmNavigator __RPC_FAR *__RPC_FAR *ppOmNavigator);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLDocument __RPC_FAR *__RPC_FAR *ppDocument);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowParent);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_self )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowSelf);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_top )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowTop);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_window )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindow);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_frames )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_screen )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLScreen __RPC_FAR *__RPC_FAR *ppScreen);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTimeout )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ BSTR bstrExpression,
            /* [in] */ long lMS,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
            /* [retval][out] */ long __RPC_FAR *plTimerID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clearTimeout )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ long lTimerID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *alert )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMessage);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *confirm )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMessage,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbConfirmed);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *prompt )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrMessage,
            /* [defaultvalue][in] */ BSTR bstrDefaultValue,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtText);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *close )( 
            IPIEHTMLWindow2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLWindow2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLWindow2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *navigate )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ BSTR bstrURL);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *open )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [defaultvalue][in] */ BSTR bstrURL,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtName,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtFeatures,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtReplace,
            /* [out][retval] */ IPIEHTMLWindow __RPC_FAR *__RPC_FAR *ppWindowResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *scroll )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ long lX,
            /* [in] */ long lY);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Image )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [out][retval] */ IPIEHTMLImageElementFactory __RPC_FAR *__RPC_FAR *ppImageFactory);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Option )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [out][retval] */ IPIEHTMLOptionElementFactory __RPC_FAR *__RPC_FAR *ppOptionFactory);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTimeout )( 
            IPIEHTMLWindow2 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvtExpression,
            /* [in] */ long lMS,
            /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
            /* [retval][out] */ long __RPC_FAR *plTimerID);
        
        END_INTERFACE
    } IPIEHTMLWindow2Vtbl;

    interface IPIEHTMLWindow2
    {
        CONST_VTBL struct IPIEHTMLWindow2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLWindow2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLWindow2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLWindow2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLWindow2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLWindow2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLWindow2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLWindow2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLWindow2_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLWindow2_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLWindow2_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLWindow2_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLWindow2_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLWindow2_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLWindow2_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLWindow2_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLWindow2_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLWindow2_get_location(This,ppLocation)	\
    (This)->lpVtbl -> get_location(This,ppLocation)

#define IPIEHTMLWindow2_get_history(This,ppOmHistory)	\
    (This)->lpVtbl -> get_history(This,ppOmHistory)

#define IPIEHTMLWindow2_get_navigator(This,ppOmNavigator)	\
    (This)->lpVtbl -> get_navigator(This,ppOmNavigator)

#define IPIEHTMLWindow2_get_document(This,ppDocument)	\
    (This)->lpVtbl -> get_document(This,ppDocument)

#define IPIEHTMLWindow2_get_parent(This,ppWindowParent)	\
    (This)->lpVtbl -> get_parent(This,ppWindowParent)

#define IPIEHTMLWindow2_get_self(This,ppWindowSelf)	\
    (This)->lpVtbl -> get_self(This,ppWindowSelf)

#define IPIEHTMLWindow2_get_top(This,ppWindowTop)	\
    (This)->lpVtbl -> get_top(This,ppWindowTop)

#define IPIEHTMLWindow2_get_window(This,ppWindow)	\
    (This)->lpVtbl -> get_window(This,ppWindow)

#define IPIEHTMLWindow2_get_frames(This,ppElemCollection)	\
    (This)->lpVtbl -> get_frames(This,ppElemCollection)

#define IPIEHTMLWindow2_get_screen(This,ppScreen)	\
    (This)->lpVtbl -> get_screen(This,ppScreen)

#define IPIEHTMLWindow2_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLWindow2_put_name(This,bstrName)	\
    (This)->lpVtbl -> put_name(This,bstrName)

#define IPIEHTMLWindow2_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLWindow2_setTimeout(This,bstrExpression,lMS,pvtLanguage,plTimerID)	\
    (This)->lpVtbl -> setTimeout(This,bstrExpression,lMS,pvtLanguage,plTimerID)

#define IPIEHTMLWindow2_clearTimeout(This,lTimerID)	\
    (This)->lpVtbl -> clearTimeout(This,lTimerID)

#define IPIEHTMLWindow2_alert(This,bstrMessage)	\
    (This)->lpVtbl -> alert(This,bstrMessage)

#define IPIEHTMLWindow2_confirm(This,bstrMessage,pvbConfirmed)	\
    (This)->lpVtbl -> confirm(This,bstrMessage,pvbConfirmed)

#define IPIEHTMLWindow2_prompt(This,bstrMessage,bstrDefaultValue,pvtText)	\
    (This)->lpVtbl -> prompt(This,bstrMessage,bstrDefaultValue,pvtText)

#define IPIEHTMLWindow2_close(This)	\
    (This)->lpVtbl -> close(This)

#define IPIEHTMLWindow2_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLWindow2_blur(This)	\
    (This)->lpVtbl -> blur(This)

#define IPIEHTMLWindow2_navigate(This,bstrURL)	\
    (This)->lpVtbl -> navigate(This,bstrURL)

#define IPIEHTMLWindow2_open(This,bstrURL,pvtName,pvtFeatures,pvtReplace,ppWindowResult)	\
    (This)->lpVtbl -> open(This,bstrURL,pvtName,pvtFeatures,pvtReplace,ppWindowResult)

#define IPIEHTMLWindow2_scroll(This,lX,lY)	\
    (This)->lpVtbl -> scroll(This,lX,lY)


#define IPIEHTMLWindow2_get_Image(This,ppImageFactory)	\
    (This)->lpVtbl -> get_Image(This,ppImageFactory)

#define IPIEHTMLWindow2_get_Option(This,ppOptionFactory)	\
    (This)->lpVtbl -> get_Option(This,ppOptionFactory)

#define IPIEHTMLWindow2_setTimeout(This,pvtExpression,lMS,pvtLanguage,plTimerID)	\
    (This)->lpVtbl -> setTimeout(This,pvtExpression,lMS,pvtLanguage,plTimerID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow2_get_Image_Proxy( 
    IPIEHTMLWindow2 __RPC_FAR * This,
    /* [out][retval] */ IPIEHTMLImageElementFactory __RPC_FAR *__RPC_FAR *ppImageFactory);


void __RPC_STUB IPIEHTMLWindow2_get_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow2_get_Option_Proxy( 
    IPIEHTMLWindow2 __RPC_FAR * This,
    /* [out][retval] */ IPIEHTMLOptionElementFactory __RPC_FAR *__RPC_FAR *ppOptionFactory);


void __RPC_STUB IPIEHTMLWindow2_get_Option_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPIEHTMLWindow2_setTimeout_Proxy( 
    IPIEHTMLWindow2 __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvtExpression,
    /* [in] */ long lMS,
    /* [optional][in] */ VARIANT __RPC_FAR *pvtLanguage,
    /* [retval][out] */ long __RPC_FAR *plTimerID);


void __RPC_STUB IPIEHTMLWindow2_setTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLWindow2_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLWindowEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLWindowEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLWindowEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLWindowEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE2102")
    PIEHTMLWindowEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLWindowEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLWindowEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLWindowEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLWindowEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLWindowEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLWindowEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLWindowEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLWindowEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLWindowEventsVtbl;

    interface PIEHTMLWindowEvents
    {
        CONST_VTBL struct PIEHTMLWindowEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLWindowEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLWindowEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLWindowEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLWindowEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLWindowEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLWindowEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLWindowEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLWindowEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2102")
PIEHTMLWindow;
#endif

#ifndef __IPIEHTMLAnchorElement_INTERFACE_DEFINED__
#define __IPIEHTMLAnchorElement_INTERFACE_DEFINED__

/* interface IPIEHTMLAnchorElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLAnchorElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE210A")
    IPIEHTMLAnchorElement : public IDispatchEx
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_href( 
            /* [in] */ BSTR bstrHREF) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_href( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHREF) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_target( 
            /* [in] */ BSTR bstrTarget) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_target( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR bstrTarget) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_accessKey( 
            /* [in] */ BSTR bstrTarget) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_accessKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_protocol( 
            /* [in] */ BSTR bstrProtocol) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_protocol( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrProtocol) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_host( 
            /* [in] */ BSTR bstrHost) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_host( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHost) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_hostname( 
            /* [in] */ BSTR bstrHostName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_hostname( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHostName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_port( 
            /* [in] */ BSTR bstrPort) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_port( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPort) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_pathname( 
            /* [in] */ BSTR bstrPathName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_pathname( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPathName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_search( 
            /* [in] */ BSTR bstrSearch) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_search( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrSearch) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_hash( 
            /* [in] */ BSTR bstrHash) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_hash( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHash) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE focus( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE blur( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLAnchorElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLAnchorElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLAnchorElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_href )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrHREF);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_href )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHREF);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_target )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrTarget);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_target )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrTarget);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrTarget);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_protocol )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrProtocol);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_protocol )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrProtocol);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_host )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrHost);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_host )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHost);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hostname )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrHostName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hostname )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHostName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_port )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrPort);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_port )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPort);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pathname )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrPathName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pathname )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrPathName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_search )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrSearch);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_search )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrSearch);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hash )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [in] */ BSTR bstrHash);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hash )( 
            IPIEHTMLAnchorElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrHash);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLAnchorElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLAnchorElement __RPC_FAR * This);
        
        END_INTERFACE
    } IPIEHTMLAnchorElementVtbl;

    interface IPIEHTMLAnchorElement
    {
        CONST_VTBL struct IPIEHTMLAnchorElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLAnchorElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLAnchorElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLAnchorElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLAnchorElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLAnchorElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLAnchorElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLAnchorElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLAnchorElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLAnchorElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLAnchorElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLAnchorElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLAnchorElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLAnchorElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLAnchorElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLAnchorElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLAnchorElement_put_href(This,bstrHREF)	\
    (This)->lpVtbl -> put_href(This,bstrHREF)

#define IPIEHTMLAnchorElement_get_href(This,pbstrHREF)	\
    (This)->lpVtbl -> get_href(This,pbstrHREF)

#define IPIEHTMLAnchorElement_put_target(This,bstrTarget)	\
    (This)->lpVtbl -> put_target(This,bstrTarget)

#define IPIEHTMLAnchorElement_get_target(This,pbstrTarget)	\
    (This)->lpVtbl -> get_target(This,pbstrTarget)

#define IPIEHTMLAnchorElement_put_name(This,bstrTarget)	\
    (This)->lpVtbl -> put_name(This,bstrTarget)

#define IPIEHTMLAnchorElement_get_name(This,pbstrTarget)	\
    (This)->lpVtbl -> get_name(This,pbstrTarget)

#define IPIEHTMLAnchorElement_put_accessKey(This,bstrTarget)	\
    (This)->lpVtbl -> put_accessKey(This,bstrTarget)

#define IPIEHTMLAnchorElement_get_accessKey(This,pbstrTarget)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrTarget)

#define IPIEHTMLAnchorElement_put_protocol(This,bstrProtocol)	\
    (This)->lpVtbl -> put_protocol(This,bstrProtocol)

#define IPIEHTMLAnchorElement_get_protocol(This,pbstrProtocol)	\
    (This)->lpVtbl -> get_protocol(This,pbstrProtocol)

#define IPIEHTMLAnchorElement_put_host(This,bstrHost)	\
    (This)->lpVtbl -> put_host(This,bstrHost)

#define IPIEHTMLAnchorElement_get_host(This,pbstrHost)	\
    (This)->lpVtbl -> get_host(This,pbstrHost)

#define IPIEHTMLAnchorElement_put_hostname(This,bstrHostName)	\
    (This)->lpVtbl -> put_hostname(This,bstrHostName)

#define IPIEHTMLAnchorElement_get_hostname(This,pbstrHostName)	\
    (This)->lpVtbl -> get_hostname(This,pbstrHostName)

#define IPIEHTMLAnchorElement_put_port(This,bstrPort)	\
    (This)->lpVtbl -> put_port(This,bstrPort)

#define IPIEHTMLAnchorElement_get_port(This,pbstrPort)	\
    (This)->lpVtbl -> get_port(This,pbstrPort)

#define IPIEHTMLAnchorElement_put_pathname(This,bstrPathName)	\
    (This)->lpVtbl -> put_pathname(This,bstrPathName)

#define IPIEHTMLAnchorElement_get_pathname(This,pbstrPathName)	\
    (This)->lpVtbl -> get_pathname(This,pbstrPathName)

#define IPIEHTMLAnchorElement_put_search(This,bstrSearch)	\
    (This)->lpVtbl -> put_search(This,bstrSearch)

#define IPIEHTMLAnchorElement_get_search(This,pbstrSearch)	\
    (This)->lpVtbl -> get_search(This,pbstrSearch)

#define IPIEHTMLAnchorElement_put_hash(This,bstrHash)	\
    (This)->lpVtbl -> put_hash(This,bstrHash)

#define IPIEHTMLAnchorElement_get_hash(This,pbstrHash)	\
    (This)->lpVtbl -> get_hash(This,pbstrHash)

#define IPIEHTMLAnchorElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLAnchorElement_blur(This)	\
    (This)->lpVtbl -> blur(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_href_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrHREF);


void __RPC_STUB IPIEHTMLAnchorElement_put_href_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_href_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrHREF);


void __RPC_STUB IPIEHTMLAnchorElement_get_href_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_target_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrTarget);


void __RPC_STUB IPIEHTMLAnchorElement_put_target_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_target_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);


void __RPC_STUB IPIEHTMLAnchorElement_get_target_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_name_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrTarget);


void __RPC_STUB IPIEHTMLAnchorElement_put_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_name_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);


void __RPC_STUB IPIEHTMLAnchorElement_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_accessKey_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrTarget);


void __RPC_STUB IPIEHTMLAnchorElement_put_accessKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_accessKey_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);


void __RPC_STUB IPIEHTMLAnchorElement_get_accessKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_protocol_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrProtocol);


void __RPC_STUB IPIEHTMLAnchorElement_put_protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_protocol_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrProtocol);


void __RPC_STUB IPIEHTMLAnchorElement_get_protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_host_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrHost);


void __RPC_STUB IPIEHTMLAnchorElement_put_host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_host_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHost);


void __RPC_STUB IPIEHTMLAnchorElement_get_host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_hostname_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrHostName);


void __RPC_STUB IPIEHTMLAnchorElement_put_hostname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_hostname_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHostName);


void __RPC_STUB IPIEHTMLAnchorElement_get_hostname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_port_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrPort);


void __RPC_STUB IPIEHTMLAnchorElement_put_port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_port_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrPort);


void __RPC_STUB IPIEHTMLAnchorElement_get_port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_pathname_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrPathName);


void __RPC_STUB IPIEHTMLAnchorElement_put_pathname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_pathname_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrPathName);


void __RPC_STUB IPIEHTMLAnchorElement_get_pathname_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_search_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrSearch);


void __RPC_STUB IPIEHTMLAnchorElement_put_search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_search_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrSearch);


void __RPC_STUB IPIEHTMLAnchorElement_get_search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_put_hash_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [in] */ BSTR bstrHash);


void __RPC_STUB IPIEHTMLAnchorElement_put_hash_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_get_hash_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrHash);


void __RPC_STUB IPIEHTMLAnchorElement_get_hash_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_focus_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLAnchorElement_focus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLAnchorElement_blur_Proxy( 
    IPIEHTMLAnchorElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLAnchorElement_blur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLAnchorElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLAnchorElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLAnchorElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLAnchorElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLAnchorElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE210A")
    PIEHTMLAnchorElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLAnchorElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLAnchorElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLAnchorElementEventsVtbl;

    interface PIEHTMLAnchorElementEvents
    {
        CONST_VTBL struct PIEHTMLAnchorElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLAnchorElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLAnchorElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLAnchorElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLAnchorElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLAnchorElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLAnchorElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLAnchorElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLAnchorElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLAnchorElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE210A")
PIEHTMLAnchorElement;
#endif

#ifndef __IPIEHTMLFormElement_INTERFACE_DEFINED__
#define __IPIEHTMLFormElement_INTERFACE_DEFINED__

/* interface IPIEHTMLFormElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLFormElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE210C")
    IPIEHTMLFormElement : public IDispatchEx
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_toString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_action( 
            /* [in] */ BSTR bstrAction) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_action( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAction) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_encoding( 
            /* [in] */ BSTR bstrEncoding) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_encoding( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrEncoding) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_method( 
            /* [in] */ BSTR bstrMethod) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_method( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMethod) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_target( 
            /* [in] */ BSTR bstrTarget) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_target( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_elements( 
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE submit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE reset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLFormElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLFormElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLFormElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_action )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAction);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_action )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAction);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_encoding )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ BSTR bstrEncoding);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_encoding )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrEncoding);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_method )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ BSTR bstrMethod);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_method )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrMethod);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_target )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [in] */ BSTR bstrTarget);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_target )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_elements )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLFormElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *submit )( 
            IPIEHTMLFormElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *reset )( 
            IPIEHTMLFormElement __RPC_FAR * This);
        
        END_INTERFACE
    } IPIEHTMLFormElementVtbl;

    interface IPIEHTMLFormElement
    {
        CONST_VTBL struct IPIEHTMLFormElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLFormElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLFormElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLFormElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLFormElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLFormElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLFormElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLFormElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLFormElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLFormElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLFormElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLFormElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLFormElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLFormElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLFormElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLFormElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLFormElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLFormElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLFormElement_put_action(This,bstrAction)	\
    (This)->lpVtbl -> put_action(This,bstrAction)

#define IPIEHTMLFormElement_get_action(This,pbstrAction)	\
    (This)->lpVtbl -> get_action(This,pbstrAction)

#define IPIEHTMLFormElement_put_encoding(This,bstrEncoding)	\
    (This)->lpVtbl -> put_encoding(This,bstrEncoding)

#define IPIEHTMLFormElement_get_encoding(This,pbstrEncoding)	\
    (This)->lpVtbl -> get_encoding(This,pbstrEncoding)

#define IPIEHTMLFormElement_put_method(This,bstrMethod)	\
    (This)->lpVtbl -> put_method(This,bstrMethod)

#define IPIEHTMLFormElement_get_method(This,pbstrMethod)	\
    (This)->lpVtbl -> get_method(This,pbstrMethod)

#define IPIEHTMLFormElement_put_target(This,bstrTarget)	\
    (This)->lpVtbl -> put_target(This,bstrTarget)

#define IPIEHTMLFormElement_get_target(This,pbstrTarget)	\
    (This)->lpVtbl -> get_target(This,pbstrTarget)

#define IPIEHTMLFormElement_get_elements(This,ppElemCollection)	\
    (This)->lpVtbl -> get_elements(This,ppElemCollection)

#define IPIEHTMLFormElement_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLFormElement_submit(This)	\
    (This)->lpVtbl -> submit(This)

#define IPIEHTMLFormElement_reset(This)	\
    (This)->lpVtbl -> reset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_toString_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrString);


void __RPC_STUB IPIEHTMLFormElement_get_toString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_name_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEHTMLFormElement_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_put_action_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [in] */ BSTR bstrAction);


void __RPC_STUB IPIEHTMLFormElement_put_action_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_action_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrAction);


void __RPC_STUB IPIEHTMLFormElement_get_action_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_put_encoding_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [in] */ BSTR bstrEncoding);


void __RPC_STUB IPIEHTMLFormElement_put_encoding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_encoding_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrEncoding);


void __RPC_STUB IPIEHTMLFormElement_get_encoding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_put_method_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [in] */ BSTR bstrMethod);


void __RPC_STUB IPIEHTMLFormElement_put_method_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_method_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrMethod);


void __RPC_STUB IPIEHTMLFormElement_get_method_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_put_target_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [in] */ BSTR bstrTarget);


void __RPC_STUB IPIEHTMLFormElement_put_target_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_target_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTarget);


void __RPC_STUB IPIEHTMLFormElement_get_target_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_elements_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLElementCollection __RPC_FAR *__RPC_FAR *ppElemCollection);


void __RPC_STUB IPIEHTMLFormElement_get_elements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_get_length_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLength);


void __RPC_STUB IPIEHTMLFormElement_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_submit_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLFormElement_submit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLFormElement_reset_Proxy( 
    IPIEHTMLFormElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLFormElement_reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLFormElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLFormElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLFormElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLFormElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLFormElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE210C")
    PIEHTMLFormElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLFormElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLFormElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLFormElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLFormElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLFormElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLFormElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLFormElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLFormElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLFormElementEventsVtbl;

    interface PIEHTMLFormElementEvents
    {
        CONST_VTBL struct PIEHTMLFormElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLFormElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLFormElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLFormElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLFormElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLFormElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLFormElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLFormElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLFormElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLFormElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE210C")
PIEHTMLFormElement;
#endif

#ifndef __IPIEHTMLControlElement_INTERFACE_DEFINED__
#define __IPIEHTMLControlElement_INTERFACE_DEFINED__

/* interface IPIEHTMLControlElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLControlElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2106")
    IPIEHTMLControlElement : public IDispatchEx
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_toString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_value( 
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_accessKey( 
            /* [in] */ BSTR bstrAccesskey) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_accessKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE focus( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE blur( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLControlElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLControlElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLControlElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLControlElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLControlElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLControlElement __RPC_FAR * This);
        
        END_INTERFACE
    } IPIEHTMLControlElementVtbl;

    interface IPIEHTMLControlElement
    {
        CONST_VTBL struct IPIEHTMLControlElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLControlElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLControlElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLControlElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLControlElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLControlElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLControlElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLControlElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLControlElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLControlElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLControlElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLControlElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLControlElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLControlElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLControlElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLControlElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLControlElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLControlElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLControlElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLControlElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLControlElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLControlElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLControlElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLControlElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLControlElement_blur(This)	\
    (This)->lpVtbl -> blur(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_get_toString_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrString);


void __RPC_STUB IPIEHTMLControlElement_get_toString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_get_type_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrType);


void __RPC_STUB IPIEHTMLControlElement_get_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_put_value_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB IPIEHTMLControlElement_put_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_get_value_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);


void __RPC_STUB IPIEHTMLControlElement_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_get_name_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IPIEHTMLControlElement_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_put_accessKey_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [in] */ BSTR bstrAccesskey);


void __RPC_STUB IPIEHTMLControlElement_put_accessKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_get_accessKey_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);


void __RPC_STUB IPIEHTMLControlElement_get_accessKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_focus_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLControlElement_focus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLControlElement_blur_Proxy( 
    IPIEHTMLControlElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLControlElement_blur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLControlElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLControlElement;

#ifdef __cplusplus

class DECLSPEC_UUID("555C7786-BA95-11D0-81F1-00A0C90AD21A")
PIEHTMLControlElement;
#endif

#ifndef __IPIEHTMLInputButtonElement_INTERFACE_DEFINED__
#define __IPIEHTMLInputButtonElement_INTERFACE_DEFINED__

/* interface IPIEHTMLInputButtonElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLInputButtonElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2108")
    IPIEHTMLInputButtonElement : public IPIEHTMLControlElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_disabled( 
            /* [in] */ VARIANT_BOOL vbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_disabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_form( 
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE click( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLInputButtonElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *click )( 
            IPIEHTMLInputButtonElement __RPC_FAR * This);
        
        END_INTERFACE
    } IPIEHTMLInputButtonElementVtbl;

    interface IPIEHTMLInputButtonElement
    {
        CONST_VTBL struct IPIEHTMLInputButtonElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLInputButtonElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLInputButtonElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLInputButtonElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLInputButtonElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLInputButtonElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLInputButtonElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLInputButtonElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLInputButtonElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLInputButtonElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLInputButtonElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLInputButtonElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLInputButtonElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLInputButtonElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLInputButtonElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLInputButtonElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLInputButtonElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLInputButtonElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLInputButtonElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLInputButtonElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLInputButtonElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLInputButtonElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLInputButtonElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLInputButtonElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLInputButtonElement_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLInputButtonElement_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLInputButtonElement_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLInputButtonElement_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#define IPIEHTMLInputButtonElement_click(This)	\
    (This)->lpVtbl -> click(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputButtonElement_put_disabled_Proxy( 
    IPIEHTMLInputButtonElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbDisabled);


void __RPC_STUB IPIEHTMLInputButtonElement_put_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputButtonElement_get_disabled_Proxy( 
    IPIEHTMLInputButtonElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);


void __RPC_STUB IPIEHTMLInputButtonElement_get_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputButtonElement_get_form_Proxy( 
    IPIEHTMLInputButtonElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);


void __RPC_STUB IPIEHTMLInputButtonElement_get_form_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLInputButtonElement_click_Proxy( 
    IPIEHTMLInputButtonElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLInputButtonElement_click_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLInputButtonElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLInputButtonElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLInputButtonElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLInputButtonElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLInputButtonElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE2108")
    PIEHTMLInputButtonElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLInputButtonElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLInputButtonElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLInputButtonElementEventsVtbl;

    interface PIEHTMLInputButtonElementEvents
    {
        CONST_VTBL struct PIEHTMLInputButtonElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLInputButtonElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLInputButtonElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLInputButtonElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLInputButtonElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLInputButtonElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLInputButtonElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLInputButtonElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLInputButtonElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLInputButtonElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2108")
PIEHTMLInputButtonElement;
#endif

#ifndef __IPIEHTMLOptionButtonElement_INTERFACE_DEFINED__
#define __IPIEHTMLOptionButtonElement_INTERFACE_DEFINED__

/* interface IPIEHTMLOptionButtonElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLOptionButtonElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2110")
    IPIEHTMLOptionButtonElement : public IPIEHTMLControlElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_disabled( 
            /* [in] */ VARIANT_BOOL vbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_disabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_form( 
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_checked( 
            /* [in] */ VARIANT_BOOL vbChecked) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_checked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbChecked) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_defaultChecked( 
            /* [in] */ VARIANT_BOOL vbDefaultChecked) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_defaultChecked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDefaultChecked) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_indeterminate( 
            /* [in] */ VARIANT_BOOL vbIndeterminate) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_indeterminate( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIndeterminate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE click( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLOptionButtonElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_checked )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbChecked);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_checked )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbChecked);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_defaultChecked )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDefaultChecked);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_defaultChecked )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDefaultChecked);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_indeterminate )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbIndeterminate);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_indeterminate )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIndeterminate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *click )( 
            IPIEHTMLOptionButtonElement __RPC_FAR * This);
        
        END_INTERFACE
    } IPIEHTMLOptionButtonElementVtbl;

    interface IPIEHTMLOptionButtonElement
    {
        CONST_VTBL struct IPIEHTMLOptionButtonElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLOptionButtonElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLOptionButtonElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLOptionButtonElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLOptionButtonElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLOptionButtonElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLOptionButtonElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLOptionButtonElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLOptionButtonElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLOptionButtonElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLOptionButtonElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLOptionButtonElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLOptionButtonElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLOptionButtonElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLOptionButtonElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLOptionButtonElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLOptionButtonElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLOptionButtonElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLOptionButtonElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLOptionButtonElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLOptionButtonElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLOptionButtonElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLOptionButtonElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLOptionButtonElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLOptionButtonElement_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLOptionButtonElement_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLOptionButtonElement_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLOptionButtonElement_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#define IPIEHTMLOptionButtonElement_put_checked(This,vbChecked)	\
    (This)->lpVtbl -> put_checked(This,vbChecked)

#define IPIEHTMLOptionButtonElement_get_checked(This,pvbChecked)	\
    (This)->lpVtbl -> get_checked(This,pvbChecked)

#define IPIEHTMLOptionButtonElement_put_defaultChecked(This,vbDefaultChecked)	\
    (This)->lpVtbl -> put_defaultChecked(This,vbDefaultChecked)

#define IPIEHTMLOptionButtonElement_get_defaultChecked(This,pvbDefaultChecked)	\
    (This)->lpVtbl -> get_defaultChecked(This,pvbDefaultChecked)

#define IPIEHTMLOptionButtonElement_put_indeterminate(This,vbIndeterminate)	\
    (This)->lpVtbl -> put_indeterminate(This,vbIndeterminate)

#define IPIEHTMLOptionButtonElement_get_indeterminate(This,pvbIndeterminate)	\
    (This)->lpVtbl -> get_indeterminate(This,pvbIndeterminate)

#define IPIEHTMLOptionButtonElement_click(This)	\
    (This)->lpVtbl -> click(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_put_disabled_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbDisabled);


void __RPC_STUB IPIEHTMLOptionButtonElement_put_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_get_disabled_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);


void __RPC_STUB IPIEHTMLOptionButtonElement_get_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_get_form_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);


void __RPC_STUB IPIEHTMLOptionButtonElement_get_form_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_put_checked_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbChecked);


void __RPC_STUB IPIEHTMLOptionButtonElement_put_checked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_get_checked_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbChecked);


void __RPC_STUB IPIEHTMLOptionButtonElement_get_checked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_put_defaultChecked_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbDefaultChecked);


void __RPC_STUB IPIEHTMLOptionButtonElement_put_defaultChecked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_get_defaultChecked_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDefaultChecked);


void __RPC_STUB IPIEHTMLOptionButtonElement_get_defaultChecked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_put_indeterminate_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbIndeterminate);


void __RPC_STUB IPIEHTMLOptionButtonElement_put_indeterminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_get_indeterminate_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbIndeterminate);


void __RPC_STUB IPIEHTMLOptionButtonElement_get_indeterminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLOptionButtonElement_click_Proxy( 
    IPIEHTMLOptionButtonElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLOptionButtonElement_click_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLOptionButtonElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLOptionButtonElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLOptionButtonElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLOptionButtonElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLOptionButtonElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E0E269F3-87A7-45f8-9200-DDAA2940F78D")
    PIEHTMLOptionButtonElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLOptionButtonElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLOptionButtonElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLOptionButtonElementEventsVtbl;

    interface PIEHTMLOptionButtonElementEvents
    {
        CONST_VTBL struct PIEHTMLOptionButtonElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLOptionButtonElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLOptionButtonElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLOptionButtonElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLOptionButtonElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLOptionButtonElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLOptionButtonElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLOptionButtonElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLOptionButtonElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLOptionButtonElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2110")
PIEHTMLOptionButtonElement;
#endif

#ifndef __IPIEHTMLSelectElement_INTERFACE_DEFINED__
#define __IPIEHTMLSelectElement_INTERFACE_DEFINED__

/* interface IPIEHTMLSelectElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLSelectElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE210F")
    IPIEHTMLSelectElement : public IPIEHTMLControlElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_disabled( 
            /* [in] */ VARIANT_BOOL vbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_disabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_form( 
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_size( 
            /* [retval][out] */ long __RPC_FAR *plSize) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_multiple( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbMultiple) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_options( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOptions) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_selectedIndex( 
            /* [in] */ long lSelectedIndex) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_selectedIndex( 
            /* [retval][out] */ long __RPC_FAR *plSelectedIndex) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE item( 
            /* [optional][in] */ VARIANT vtName,
            /* [optional][in] */ VARIANT vtIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pdispItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLSelectElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLSelectElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLSelectElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLSelectElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLSelectElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_size )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSize);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_multiple )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbMultiple);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_options )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOptions);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_selectedIndex )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [in] */ long lSelectedIndex);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_selectedIndex )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSelectedIndex);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IPIEHTMLSelectElement __RPC_FAR * This,
            /* [optional][in] */ VARIANT vtName,
            /* [optional][in] */ VARIANT vtIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pdispItem);
        
        END_INTERFACE
    } IPIEHTMLSelectElementVtbl;

    interface IPIEHTMLSelectElement
    {
        CONST_VTBL struct IPIEHTMLSelectElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLSelectElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLSelectElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLSelectElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLSelectElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLSelectElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLSelectElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLSelectElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLSelectElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLSelectElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLSelectElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLSelectElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLSelectElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLSelectElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLSelectElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLSelectElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLSelectElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLSelectElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLSelectElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLSelectElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLSelectElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLSelectElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLSelectElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLSelectElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLSelectElement_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLSelectElement_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLSelectElement_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLSelectElement_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#define IPIEHTMLSelectElement_get_size(This,plSize)	\
    (This)->lpVtbl -> get_size(This,plSize)

#define IPIEHTMLSelectElement_get_multiple(This,pvbMultiple)	\
    (This)->lpVtbl -> get_multiple(This,pvbMultiple)

#define IPIEHTMLSelectElement_get_options(This,ppdispOptions)	\
    (This)->lpVtbl -> get_options(This,ppdispOptions)

#define IPIEHTMLSelectElement_put_selectedIndex(This,lSelectedIndex)	\
    (This)->lpVtbl -> put_selectedIndex(This,lSelectedIndex)

#define IPIEHTMLSelectElement_get_selectedIndex(This,plSelectedIndex)	\
    (This)->lpVtbl -> get_selectedIndex(This,plSelectedIndex)

#define IPIEHTMLSelectElement_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLSelectElement_item(This,vtName,vtIndex,pdispItem)	\
    (This)->lpVtbl -> item(This,vtName,vtIndex,pdispItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_put_disabled_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbDisabled);


void __RPC_STUB IPIEHTMLSelectElement_put_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_disabled_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);


void __RPC_STUB IPIEHTMLSelectElement_get_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_form_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);


void __RPC_STUB IPIEHTMLSelectElement_get_form_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_size_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plSize);


void __RPC_STUB IPIEHTMLSelectElement_get_size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_multiple_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbMultiple);


void __RPC_STUB IPIEHTMLSelectElement_get_multiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_options_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOptions);


void __RPC_STUB IPIEHTMLSelectElement_get_options_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_put_selectedIndex_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [in] */ long lSelectedIndex);


void __RPC_STUB IPIEHTMLSelectElement_put_selectedIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_selectedIndex_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plSelectedIndex);


void __RPC_STUB IPIEHTMLSelectElement_get_selectedIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_get_length_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLength);


void __RPC_STUB IPIEHTMLSelectElement_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement_item_Proxy( 
    IPIEHTMLSelectElement __RPC_FAR * This,
    /* [optional][in] */ VARIANT vtName,
    /* [optional][in] */ VARIANT vtIndex,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pdispItem);


void __RPC_STUB IPIEHTMLSelectElement_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLSelectElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLSelectElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLSelectElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLSelectElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLSelectElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE210F")
    PIEHTMLSelectElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLSelectElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLSelectElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLSelectElementEventsVtbl;

    interface PIEHTMLSelectElementEvents
    {
        CONST_VTBL struct PIEHTMLSelectElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLSelectElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLSelectElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLSelectElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLSelectElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLSelectElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLSelectElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLSelectElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLSelectElementEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IPIEHTMLSelectElement2_INTERFACE_DEFINED__
#define __IPIEHTMLSelectElement2_INTERFACE_DEFINED__

/* interface IPIEHTMLSelectElement2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLSelectElement2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B74D4AD5-D4E1-46ef-BE9F-682DFCD23618")
    IPIEHTMLSelectElement2 : public IPIEHTMLSelectElement
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE add( 
            /* [in] */ IPIEHTMLOptionElement __RPC_FAR *element,
            /* [in][optional] */ VARIANT before) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE remove( 
            /* [in][defaultvalue] */ long index = -1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLSelectElement2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_size )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSize);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_multiple )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbMultiple);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_options )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOptions);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_selectedIndex )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ long lSelectedIndex);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_selectedIndex )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSelectedIndex);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [optional][in] */ VARIANT vtName,
            /* [optional][in] */ VARIANT vtIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pdispItem);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *add )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in] */ IPIEHTMLOptionElement __RPC_FAR *element,
            /* [in][optional] */ VARIANT before);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *remove )( 
            IPIEHTMLSelectElement2 __RPC_FAR * This,
            /* [in][defaultvalue] */ long index);
        
        END_INTERFACE
    } IPIEHTMLSelectElement2Vtbl;

    interface IPIEHTMLSelectElement2
    {
        CONST_VTBL struct IPIEHTMLSelectElement2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLSelectElement2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLSelectElement2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLSelectElement2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLSelectElement2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLSelectElement2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLSelectElement2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLSelectElement2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLSelectElement2_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLSelectElement2_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLSelectElement2_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLSelectElement2_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLSelectElement2_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLSelectElement2_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLSelectElement2_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLSelectElement2_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLSelectElement2_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLSelectElement2_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLSelectElement2_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLSelectElement2_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLSelectElement2_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLSelectElement2_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLSelectElement2_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLSelectElement2_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLSelectElement2_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLSelectElement2_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLSelectElement2_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLSelectElement2_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#define IPIEHTMLSelectElement2_get_size(This,plSize)	\
    (This)->lpVtbl -> get_size(This,plSize)

#define IPIEHTMLSelectElement2_get_multiple(This,pvbMultiple)	\
    (This)->lpVtbl -> get_multiple(This,pvbMultiple)

#define IPIEHTMLSelectElement2_get_options(This,ppdispOptions)	\
    (This)->lpVtbl -> get_options(This,ppdispOptions)

#define IPIEHTMLSelectElement2_put_selectedIndex(This,lSelectedIndex)	\
    (This)->lpVtbl -> put_selectedIndex(This,lSelectedIndex)

#define IPIEHTMLSelectElement2_get_selectedIndex(This,plSelectedIndex)	\
    (This)->lpVtbl -> get_selectedIndex(This,plSelectedIndex)

#define IPIEHTMLSelectElement2_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IPIEHTMLSelectElement2_item(This,vtName,vtIndex,pdispItem)	\
    (This)->lpVtbl -> item(This,vtName,vtIndex,pdispItem)


#define IPIEHTMLSelectElement2_add(This,element,before)	\
    (This)->lpVtbl -> add(This,element,before)

#define IPIEHTMLSelectElement2_remove(This,index)	\
    (This)->lpVtbl -> remove(This,index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement2_add_Proxy( 
    IPIEHTMLSelectElement2 __RPC_FAR * This,
    /* [in] */ IPIEHTMLOptionElement __RPC_FAR *element,
    /* [in][optional] */ VARIANT before);


void __RPC_STUB IPIEHTMLSelectElement2_add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLSelectElement2_remove_Proxy( 
    IPIEHTMLSelectElement2 __RPC_FAR * This,
    /* [in][defaultvalue] */ long index);


void __RPC_STUB IPIEHTMLSelectElement2_remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLSelectElement2_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLSelectElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE210F")
PIEHTMLSelectElement;
#endif

EXTERN_C const CLSID CLSID_PIEHTMLOptionElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE210B")
PIEHTMLOptionElement;
#endif

#ifndef __IPIEHTMLInputTextElement_INTERFACE_DEFINED__
#define __IPIEHTMLInputTextElement_INTERFACE_DEFINED__

/* interface IPIEHTMLInputTextElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLInputTextElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE210D")
    IPIEHTMLInputTextElement : public IPIEHTMLControlElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_disabled( 
            /* [in] */ VARIANT_BOOL vbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_disabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_form( 
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_defaultValue( 
            /* [in] */ BSTR bstrDefaultValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_defaultValue( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_size( 
            /* [retval][out] */ long __RPC_FAR *plSize) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_maxLength( 
            /* [in] */ long lMaxLength) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_maxLength( 
            /* [retval][out] */ long __RPC_FAR *plMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE select( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLInputTextElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLInputTextElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLInputTextElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLInputTextElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLInputTextElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_defaultValue )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ BSTR bstrDefaultValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_defaultValue )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_size )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSize);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxLength )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [in] */ long lMaxLength);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxLength )( 
            IPIEHTMLInputTextElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *select )( 
            IPIEHTMLInputTextElement __RPC_FAR * This);
        
        END_INTERFACE
    } IPIEHTMLInputTextElementVtbl;

    interface IPIEHTMLInputTextElement
    {
        CONST_VTBL struct IPIEHTMLInputTextElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLInputTextElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLInputTextElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLInputTextElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLInputTextElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLInputTextElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLInputTextElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLInputTextElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLInputTextElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLInputTextElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLInputTextElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLInputTextElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLInputTextElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLInputTextElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLInputTextElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLInputTextElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLInputTextElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLInputTextElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLInputTextElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLInputTextElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLInputTextElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLInputTextElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLInputTextElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLInputTextElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLInputTextElement_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLInputTextElement_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLInputTextElement_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLInputTextElement_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#define IPIEHTMLInputTextElement_put_defaultValue(This,bstrDefaultValue)	\
    (This)->lpVtbl -> put_defaultValue(This,bstrDefaultValue)

#define IPIEHTMLInputTextElement_get_defaultValue(This,pbstrDefaultValue)	\
    (This)->lpVtbl -> get_defaultValue(This,pbstrDefaultValue)

#define IPIEHTMLInputTextElement_get_size(This,plSize)	\
    (This)->lpVtbl -> get_size(This,plSize)

#define IPIEHTMLInputTextElement_put_maxLength(This,lMaxLength)	\
    (This)->lpVtbl -> put_maxLength(This,lMaxLength)

#define IPIEHTMLInputTextElement_get_maxLength(This,plMaxLength)	\
    (This)->lpVtbl -> get_maxLength(This,plMaxLength)

#define IPIEHTMLInputTextElement_select(This)	\
    (This)->lpVtbl -> select(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_put_disabled_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbDisabled);


void __RPC_STUB IPIEHTMLInputTextElement_put_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_get_disabled_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);


void __RPC_STUB IPIEHTMLInputTextElement_get_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_get_form_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);


void __RPC_STUB IPIEHTMLInputTextElement_get_form_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_put_defaultValue_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [in] */ BSTR bstrDefaultValue);


void __RPC_STUB IPIEHTMLInputTextElement_put_defaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_get_defaultValue_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue);


void __RPC_STUB IPIEHTMLInputTextElement_get_defaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_get_size_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plSize);


void __RPC_STUB IPIEHTMLInputTextElement_get_size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_put_maxLength_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [in] */ long lMaxLength);


void __RPC_STUB IPIEHTMLInputTextElement_put_maxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_get_maxLength_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMaxLength);


void __RPC_STUB IPIEHTMLInputTextElement_get_maxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPIEHTMLInputTextElement_select_Proxy( 
    IPIEHTMLInputTextElement __RPC_FAR * This);


void __RPC_STUB IPIEHTMLInputTextElement_select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLInputTextElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLInputTextElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLInputTextElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLInputTextElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLInputTextElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE210D")
    PIEHTMLInputTextElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLInputTextElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLInputTextElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLInputTextElementEventsVtbl;

    interface PIEHTMLInputTextElementEvents
    {
        CONST_VTBL struct PIEHTMLInputTextElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLInputTextElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLInputTextElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLInputTextElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLInputTextElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLInputTextElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLInputTextElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLInputTextElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLInputTextElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLInputTextElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE210D")
PIEHTMLInputTextElement;
#endif

#ifndef __IPIEHTMLTextAreaElement_INTERFACE_DEFINED__
#define __IPIEHTMLTextAreaElement_INTERFACE_DEFINED__

/* interface IPIEHTMLTextAreaElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLTextAreaElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE210E")
    IPIEHTMLTextAreaElement : public IPIEHTMLInputTextElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_readOnly( 
            /* [in] */ VARIANT_BOOL vbReadOnly) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_readOnly( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbReadOnly) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_rows( 
            /* [retval][out] */ long __RPC_FAR *plRows) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_cols( 
            /* [retval][out] */ long __RPC_FAR *plCols) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLTextAreaElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_defaultValue )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ BSTR bstrDefaultValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_defaultValue )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_size )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plSize);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_maxLength )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ long lMaxLength);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_maxLength )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *select )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_readOnly )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbReadOnly);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_readOnly )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbReadOnly);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rows )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plRows);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cols )( 
            IPIEHTMLTextAreaElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCols);
        
        END_INTERFACE
    } IPIEHTMLTextAreaElementVtbl;

    interface IPIEHTMLTextAreaElement
    {
        CONST_VTBL struct IPIEHTMLTextAreaElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLTextAreaElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLTextAreaElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLTextAreaElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLTextAreaElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLTextAreaElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLTextAreaElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLTextAreaElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLTextAreaElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLTextAreaElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLTextAreaElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLTextAreaElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLTextAreaElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLTextAreaElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLTextAreaElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLTextAreaElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLTextAreaElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLTextAreaElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLTextAreaElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLTextAreaElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLTextAreaElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLTextAreaElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLTextAreaElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLTextAreaElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLTextAreaElement_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLTextAreaElement_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLTextAreaElement_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLTextAreaElement_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#define IPIEHTMLTextAreaElement_put_defaultValue(This,bstrDefaultValue)	\
    (This)->lpVtbl -> put_defaultValue(This,bstrDefaultValue)

#define IPIEHTMLTextAreaElement_get_defaultValue(This,pbstrDefaultValue)	\
    (This)->lpVtbl -> get_defaultValue(This,pbstrDefaultValue)

#define IPIEHTMLTextAreaElement_get_size(This,plSize)	\
    (This)->lpVtbl -> get_size(This,plSize)

#define IPIEHTMLTextAreaElement_put_maxLength(This,lMaxLength)	\
    (This)->lpVtbl -> put_maxLength(This,lMaxLength)

#define IPIEHTMLTextAreaElement_get_maxLength(This,plMaxLength)	\
    (This)->lpVtbl -> get_maxLength(This,plMaxLength)

#define IPIEHTMLTextAreaElement_select(This)	\
    (This)->lpVtbl -> select(This)


#define IPIEHTMLTextAreaElement_put_readOnly(This,vbReadOnly)	\
    (This)->lpVtbl -> put_readOnly(This,vbReadOnly)

#define IPIEHTMLTextAreaElement_get_readOnly(This,pvbReadOnly)	\
    (This)->lpVtbl -> get_readOnly(This,pvbReadOnly)

#define IPIEHTMLTextAreaElement_get_rows(This,plRows)	\
    (This)->lpVtbl -> get_rows(This,plRows)

#define IPIEHTMLTextAreaElement_get_cols(This,plCols)	\
    (This)->lpVtbl -> get_cols(This,plCols)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLTextAreaElement_put_readOnly_Proxy( 
    IPIEHTMLTextAreaElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbReadOnly);


void __RPC_STUB IPIEHTMLTextAreaElement_put_readOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLTextAreaElement_get_readOnly_Proxy( 
    IPIEHTMLTextAreaElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbReadOnly);


void __RPC_STUB IPIEHTMLTextAreaElement_get_readOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLTextAreaElement_get_rows_Proxy( 
    IPIEHTMLTextAreaElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plRows);


void __RPC_STUB IPIEHTMLTextAreaElement_get_rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLTextAreaElement_get_cols_Proxy( 
    IPIEHTMLTextAreaElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCols);


void __RPC_STUB IPIEHTMLTextAreaElement_get_cols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLTextAreaElement_INTERFACE_DEFINED__ */


#ifndef __PIEHTMLTextAreaElementEvents_DISPINTERFACE_DEFINED__
#define __PIEHTMLTextAreaElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface PIEHTMLTextAreaElementEvents */
/* [uuid][hidden] */ 


EXTERN_C const IID DIID_PIEHTMLTextAreaElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-10C04FAE210E")
    PIEHTMLTextAreaElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct PIEHTMLTextAreaElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PIEHTMLTextAreaElementEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } PIEHTMLTextAreaElementEventsVtbl;

    interface PIEHTMLTextAreaElementEvents
    {
        CONST_VTBL struct PIEHTMLTextAreaElementEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PIEHTMLTextAreaElementEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PIEHTMLTextAreaElementEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PIEHTMLTextAreaElementEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PIEHTMLTextAreaElementEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PIEHTMLTextAreaElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PIEHTMLTextAreaElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PIEHTMLTextAreaElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __PIEHTMLTextAreaElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLTextAreaElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE210E")
PIEHTMLTextAreaElement;
#endif

#ifndef __IPIEHTMLInputHiddenElement_INTERFACE_DEFINED__
#define __IPIEHTMLInputHiddenElement_INTERFACE_DEFINED__

/* interface IPIEHTMLInputHiddenElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLInputHiddenElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2111")
    IPIEHTMLInputHiddenElement : public IPIEHTMLControlElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_disabled( 
            /* [in] */ VARIANT_BOOL vbDisabled) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_disabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_defaultValue( 
            /* [in] */ BSTR bstrDefaultValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_defaultValue( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_form( 
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLInputHiddenElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_toString )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrString);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_value )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ BSTR bstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accessKey )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAccesskey);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accessKey )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAccesskey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *focus )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *blur )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_disabled )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbDisabled);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_disabled )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_defaultValue )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [in] */ BSTR bstrDefaultValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_defaultValue )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_form )( 
            IPIEHTMLInputHiddenElement __RPC_FAR * This,
            /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);
        
        END_INTERFACE
    } IPIEHTMLInputHiddenElementVtbl;

    interface IPIEHTMLInputHiddenElement
    {
        CONST_VTBL struct IPIEHTMLInputHiddenElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLInputHiddenElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLInputHiddenElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLInputHiddenElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLInputHiddenElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLInputHiddenElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLInputHiddenElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLInputHiddenElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLInputHiddenElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLInputHiddenElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLInputHiddenElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLInputHiddenElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLInputHiddenElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLInputHiddenElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLInputHiddenElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLInputHiddenElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLInputHiddenElement_get_toString(This,pbstrString)	\
    (This)->lpVtbl -> get_toString(This,pbstrString)

#define IPIEHTMLInputHiddenElement_get_type(This,pbstrType)	\
    (This)->lpVtbl -> get_type(This,pbstrType)

#define IPIEHTMLInputHiddenElement_put_value(This,bstrValue)	\
    (This)->lpVtbl -> put_value(This,bstrValue)

#define IPIEHTMLInputHiddenElement_get_value(This,pbstrValue)	\
    (This)->lpVtbl -> get_value(This,pbstrValue)

#define IPIEHTMLInputHiddenElement_get_name(This,pbstrName)	\
    (This)->lpVtbl -> get_name(This,pbstrName)

#define IPIEHTMLInputHiddenElement_put_accessKey(This,bstrAccesskey)	\
    (This)->lpVtbl -> put_accessKey(This,bstrAccesskey)

#define IPIEHTMLInputHiddenElement_get_accessKey(This,pbstrAccesskey)	\
    (This)->lpVtbl -> get_accessKey(This,pbstrAccesskey)

#define IPIEHTMLInputHiddenElement_focus(This)	\
    (This)->lpVtbl -> focus(This)

#define IPIEHTMLInputHiddenElement_blur(This)	\
    (This)->lpVtbl -> blur(This)


#define IPIEHTMLInputHiddenElement_put_disabled(This,vbDisabled)	\
    (This)->lpVtbl -> put_disabled(This,vbDisabled)

#define IPIEHTMLInputHiddenElement_get_disabled(This,pvbDisabled)	\
    (This)->lpVtbl -> get_disabled(This,pvbDisabled)

#define IPIEHTMLInputHiddenElement_put_defaultValue(This,bstrDefaultValue)	\
    (This)->lpVtbl -> put_defaultValue(This,bstrDefaultValue)

#define IPIEHTMLInputHiddenElement_get_defaultValue(This,pbstrDefaultValue)	\
    (This)->lpVtbl -> get_defaultValue(This,pbstrDefaultValue)

#define IPIEHTMLInputHiddenElement_get_form(This,ppForm)	\
    (This)->lpVtbl -> get_form(This,ppForm)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputHiddenElement_put_disabled_Proxy( 
    IPIEHTMLInputHiddenElement __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbDisabled);


void __RPC_STUB IPIEHTMLInputHiddenElement_put_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputHiddenElement_get_disabled_Proxy( 
    IPIEHTMLInputHiddenElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbDisabled);


void __RPC_STUB IPIEHTMLInputHiddenElement_get_disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputHiddenElement_put_defaultValue_Proxy( 
    IPIEHTMLInputHiddenElement __RPC_FAR * This,
    /* [in] */ BSTR bstrDefaultValue);


void __RPC_STUB IPIEHTMLInputHiddenElement_put_defaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputHiddenElement_get_defaultValue_Proxy( 
    IPIEHTMLInputHiddenElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDefaultValue);


void __RPC_STUB IPIEHTMLInputHiddenElement_get_defaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLInputHiddenElement_get_form_Proxy( 
    IPIEHTMLInputHiddenElement __RPC_FAR * This,
    /* [retval][out] */ IPIEHTMLFormElement __RPC_FAR *__RPC_FAR *ppForm);


void __RPC_STUB IPIEHTMLInputHiddenElement_get_form_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLInputHiddenElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLInputHiddenElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2111")
PIEHTMLInputHiddenElement;
#endif

#ifndef __IPIEHTMLElement_INTERFACE_DEFINED__
#define __IPIEHTMLElement_INTERFACE_DEFINED__

/* interface IPIEHTMLElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2201")
    IPIEHTMLElement : public IDispatchEx
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrID) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_innerHTML( 
            /* [in] */ BSTR bstrInnerHTML) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_innerHTML( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerHTML) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_innerText( 
            /* [in] */ BSTR bstrInnerText) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_innerText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_id )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrID);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_innerHTML )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ BSTR bstrInnerHTML);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_innerHTML )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerHTML);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_innerText )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [in] */ BSTR bstrInnerText);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_innerText )( 
            IPIEHTMLElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerText);
        
        END_INTERFACE
    } IPIEHTMLElementVtbl;

    interface IPIEHTMLElement
    {
        CONST_VTBL struct IPIEHTMLElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLElement_get_id(This,pbstrID)	\
    (This)->lpVtbl -> get_id(This,pbstrID)

#define IPIEHTMLElement_put_innerHTML(This,bstrInnerHTML)	\
    (This)->lpVtbl -> put_innerHTML(This,bstrInnerHTML)

#define IPIEHTMLElement_get_innerHTML(This,pbstrInnerHTML)	\
    (This)->lpVtbl -> get_innerHTML(This,pbstrInnerHTML)

#define IPIEHTMLElement_put_innerText(This,bstrInnerText)	\
    (This)->lpVtbl -> put_innerText(This,bstrInnerText)

#define IPIEHTMLElement_get_innerText(This,pbstrInnerText)	\
    (This)->lpVtbl -> get_innerText(This,pbstrInnerText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElement_get_id_Proxy( 
    IPIEHTMLElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrID);


void __RPC_STUB IPIEHTMLElement_get_id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElement_put_innerHTML_Proxy( 
    IPIEHTMLElement __RPC_FAR * This,
    /* [in] */ BSTR bstrInnerHTML);


void __RPC_STUB IPIEHTMLElement_put_innerHTML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElement_get_innerHTML_Proxy( 
    IPIEHTMLElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerHTML);


void __RPC_STUB IPIEHTMLElement_get_innerHTML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElement_put_innerText_Proxy( 
    IPIEHTMLElement __RPC_FAR * This,
    /* [in] */ BSTR bstrInnerText);


void __RPC_STUB IPIEHTMLElement_put_innerText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLElement_get_innerText_Proxy( 
    IPIEHTMLElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerText);


void __RPC_STUB IPIEHTMLElement_get_innerText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2201")
PIEHTMLElement;
#endif

#ifndef __IPIEHTMLDivElement_INTERFACE_DEFINED__
#define __IPIEHTMLDivElement_INTERFACE_DEFINED__

/* interface IPIEHTMLDivElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLDivElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2202")
    IPIEHTMLDivElement : public IPIEHTMLElement
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_align( 
            /* [in] */ BSTR bstrAlign) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_align( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAlign) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLDivElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLDivElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLDivElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_id )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrID);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_innerHTML )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ BSTR bstrInnerHTML);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_innerHTML )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerHTML);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_innerText )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ BSTR bstrInnerText);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_innerText )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerText);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_align )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [in] */ BSTR bstrAlign);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_align )( 
            IPIEHTMLDivElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAlign);
        
        END_INTERFACE
    } IPIEHTMLDivElementVtbl;

    interface IPIEHTMLDivElement
    {
        CONST_VTBL struct IPIEHTMLDivElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLDivElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLDivElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLDivElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLDivElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLDivElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLDivElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLDivElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLDivElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLDivElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLDivElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLDivElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLDivElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLDivElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLDivElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLDivElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLDivElement_get_id(This,pbstrID)	\
    (This)->lpVtbl -> get_id(This,pbstrID)

#define IPIEHTMLDivElement_put_innerHTML(This,bstrInnerHTML)	\
    (This)->lpVtbl -> put_innerHTML(This,bstrInnerHTML)

#define IPIEHTMLDivElement_get_innerHTML(This,pbstrInnerHTML)	\
    (This)->lpVtbl -> get_innerHTML(This,pbstrInnerHTML)

#define IPIEHTMLDivElement_put_innerText(This,bstrInnerText)	\
    (This)->lpVtbl -> put_innerText(This,bstrInnerText)

#define IPIEHTMLDivElement_get_innerText(This,pbstrInnerText)	\
    (This)->lpVtbl -> get_innerText(This,pbstrInnerText)


#define IPIEHTMLDivElement_put_align(This,bstrAlign)	\
    (This)->lpVtbl -> put_align(This,bstrAlign)

#define IPIEHTMLDivElement_get_align(This,pbstrAlign)	\
    (This)->lpVtbl -> get_align(This,pbstrAlign)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDivElement_put_align_Proxy( 
    IPIEHTMLDivElement __RPC_FAR * This,
    /* [in] */ BSTR bstrAlign);


void __RPC_STUB IPIEHTMLDivElement_put_align_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPIEHTMLDivElement_get_align_Proxy( 
    IPIEHTMLDivElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrAlign);


void __RPC_STUB IPIEHTMLDivElement_get_align_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPIEHTMLDivElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLDivElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2202")
PIEHTMLDivElement;
#endif

#ifndef __IPIEHTMLSpanElement_INTERFACE_DEFINED__
#define __IPIEHTMLSpanElement_INTERFACE_DEFINED__

/* interface IPIEHTMLSpanElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPIEHTMLSpanElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDD75622-07D9-11D3-9309-00C04FAE2203")
    IPIEHTMLSpanElement : public IPIEHTMLElement
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPIEHTMLSpanElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPIEHTMLSpanElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPIEHTMLSpanElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispID )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeEx )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [in] */ DISPPARAMS __RPC_FAR *pdp,
            /* [out] */ VARIANT __RPC_FAR *pvarRes,
            /* [out] */ EXCEPINFO __RPC_FAR *pei,
            /* [unique][in] */ IServiceProvider __RPC_FAR *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByName )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ BSTR bstr,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMemberByDispID )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberProperties )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD __RPC_FAR *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberName )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextDispID )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID __RPC_FAR *pid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameSpaceParent )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_id )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrID);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_innerHTML )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ BSTR bstrInnerHTML);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_innerHTML )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerHTML);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_innerText )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [in] */ BSTR bstrInnerText);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_innerText )( 
            IPIEHTMLSpanElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInnerText);
        
        END_INTERFACE
    } IPIEHTMLSpanElementVtbl;

    interface IPIEHTMLSpanElement
    {
        CONST_VTBL struct IPIEHTMLSpanElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPIEHTMLSpanElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPIEHTMLSpanElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPIEHTMLSpanElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPIEHTMLSpanElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPIEHTMLSpanElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPIEHTMLSpanElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPIEHTMLSpanElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPIEHTMLSpanElement_GetDispID(This,bstrName,grfdex,pid)	\
    (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid)

#define IPIEHTMLSpanElement_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)

#define IPIEHTMLSpanElement_DeleteMemberByName(This,bstr,grfdex)	\
    (This)->lpVtbl -> DeleteMemberByName(This,bstr,grfdex)

#define IPIEHTMLSpanElement_DeleteMemberByDispID(This,id)	\
    (This)->lpVtbl -> DeleteMemberByDispID(This,id)

#define IPIEHTMLSpanElement_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex)

#define IPIEHTMLSpanElement_GetMemberName(This,id,pbstrName)	\
    (This)->lpVtbl -> GetMemberName(This,id,pbstrName)

#define IPIEHTMLSpanElement_GetNextDispID(This,grfdex,id,pid)	\
    (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid)

#define IPIEHTMLSpanElement_GetNameSpaceParent(This,ppunk)	\
    (This)->lpVtbl -> GetNameSpaceParent(This,ppunk)


#define IPIEHTMLSpanElement_get_id(This,pbstrID)	\
    (This)->lpVtbl -> get_id(This,pbstrID)

#define IPIEHTMLSpanElement_put_innerHTML(This,bstrInnerHTML)	\
    (This)->lpVtbl -> put_innerHTML(This,bstrInnerHTML)

#define IPIEHTMLSpanElement_get_innerHTML(This,pbstrInnerHTML)	\
    (This)->lpVtbl -> get_innerHTML(This,pbstrInnerHTML)

#define IPIEHTMLSpanElement_put_innerText(This,bstrInnerText)	\
    (This)->lpVtbl -> put_innerText(This,bstrInnerText)

#define IPIEHTMLSpanElement_get_innerText(This,pbstrInnerText)	\
    (This)->lpVtbl -> get_innerText(This,pbstrInnerText)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPIEHTMLSpanElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIEHTMLSpanElement;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD75622-07D9-11D3-9309-20C04FAE2203")
PIEHTMLSpanElement;
#endif
#endif /* __WEBVIEWLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


