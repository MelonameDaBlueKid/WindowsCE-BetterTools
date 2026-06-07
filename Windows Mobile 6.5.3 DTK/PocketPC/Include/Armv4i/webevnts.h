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
/* at Tue Nov 10 18:47:29 2009
 */
/* Compiler settings for .\webevnts.idl:
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

#ifndef __webevnts_h__
#define __webevnts_h__

/* Forward Declarations */ 

#ifndef __IWebBrowserEventsService_FWD_DEFINED__
#define __IWebBrowserEventsService_FWD_DEFINED__
typedef interface IWebBrowserEventsService IWebBrowserEventsService;
#endif 	/* __IWebBrowserEventsService_FWD_DEFINED__ */


#ifndef __IWebBrowserEventsUrlService_FWD_DEFINED__
#define __IWebBrowserEventsUrlService_FWD_DEFINED__
typedef interface IWebBrowserEventsUrlService IWebBrowserEventsUrlService;
#endif 	/* __IWebBrowserEventsUrlService_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_webevnts_0000 */
/* [local] */ 

//=--------------------------------------------------------------------------=
// webevnts.h
//=--------------------------------------------------------------------------=
// (C) Copyright 2005-2008 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#pragma comment(lib,"uuid.lib")

//---------------------------------------------------------------------------=
// IWebBrowserEventsService and IWebBrowserUrlForEvents Interfaces.



#ifndef _LPWEBEVNTS_DEFINED
#define _LPWEBEVNTS_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_webevnts_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_webevnts_0000_v0_0_s_ifspec;

#ifndef __IWebBrowserEventsService_INTERFACE_DEFINED__
#define __IWebBrowserEventsService_INTERFACE_DEFINED__

/* interface IWebBrowserEventsService */
/* [object][hidden][helpcontext][helpstring][uuid] */ 


EXTERN_C const IID IID_IWebBrowserEventsService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54A8F188-9EBD-4795-AD16-9B4945119636")
    IWebBrowserEventsService : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FireBeforeNavigate2Event( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCancel) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FireNavigateComplete2Event( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FireDownloadBeginEvent( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FireDownloadCompleteEvent( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FireDocumentCompleteEvent( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebBrowserEventsServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebBrowserEventsService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebBrowserEventsService __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebBrowserEventsService __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireBeforeNavigate2Event )( 
            IWebBrowserEventsService __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCancel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireNavigateComplete2Event )( 
            IWebBrowserEventsService __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireDownloadBeginEvent )( 
            IWebBrowserEventsService __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireDownloadCompleteEvent )( 
            IWebBrowserEventsService __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireDocumentCompleteEvent )( 
            IWebBrowserEventsService __RPC_FAR * This);
        
        END_INTERFACE
    } IWebBrowserEventsServiceVtbl;

    interface IWebBrowserEventsService
    {
        CONST_VTBL struct IWebBrowserEventsServiceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebBrowserEventsService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebBrowserEventsService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebBrowserEventsService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebBrowserEventsService_FireBeforeNavigate2Event(This,pfCancel)	\
    (This)->lpVtbl -> FireBeforeNavigate2Event(This,pfCancel)

#define IWebBrowserEventsService_FireNavigateComplete2Event(This)	\
    (This)->lpVtbl -> FireNavigateComplete2Event(This)

#define IWebBrowserEventsService_FireDownloadBeginEvent(This)	\
    (This)->lpVtbl -> FireDownloadBeginEvent(This)

#define IWebBrowserEventsService_FireDownloadCompleteEvent(This)	\
    (This)->lpVtbl -> FireDownloadCompleteEvent(This)

#define IWebBrowserEventsService_FireDocumentCompleteEvent(This)	\
    (This)->lpVtbl -> FireDocumentCompleteEvent(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IWebBrowserEventsService_FireBeforeNavigate2Event_Proxy( 
    IWebBrowserEventsService __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCancel);


void __RPC_STUB IWebBrowserEventsService_FireBeforeNavigate2Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IWebBrowserEventsService_FireNavigateComplete2Event_Proxy( 
    IWebBrowserEventsService __RPC_FAR * This);


void __RPC_STUB IWebBrowserEventsService_FireNavigateComplete2Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IWebBrowserEventsService_FireDownloadBeginEvent_Proxy( 
    IWebBrowserEventsService __RPC_FAR * This);


void __RPC_STUB IWebBrowserEventsService_FireDownloadBeginEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IWebBrowserEventsService_FireDownloadCompleteEvent_Proxy( 
    IWebBrowserEventsService __RPC_FAR * This);


void __RPC_STUB IWebBrowserEventsService_FireDownloadCompleteEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IWebBrowserEventsService_FireDocumentCompleteEvent_Proxy( 
    IWebBrowserEventsService __RPC_FAR * This);


void __RPC_STUB IWebBrowserEventsService_FireDocumentCompleteEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebBrowserEventsService_INTERFACE_DEFINED__ */


#ifndef __IWebBrowserEventsUrlService_INTERFACE_DEFINED__
#define __IWebBrowserEventsUrlService_INTERFACE_DEFINED__

/* interface IWebBrowserEventsUrlService */
/* [object][hidden][helpcontext][helpstring][uuid] */ 


EXTERN_C const IID IID_IWebBrowserEventsUrlService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("87CC5D04-EAFA-4833-9820-8F986530CC00")
    IWebBrowserEventsUrlService : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetUrlForEvents( 
            /* [retval][out] */ BSTR __RPC_FAR *pUrl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebBrowserEventsUrlServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebBrowserEventsUrlService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebBrowserEventsUrlService __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebBrowserEventsUrlService __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUrlForEvents )( 
            IWebBrowserEventsUrlService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUrl);
        
        END_INTERFACE
    } IWebBrowserEventsUrlServiceVtbl;

    interface IWebBrowserEventsUrlService
    {
        CONST_VTBL struct IWebBrowserEventsUrlServiceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebBrowserEventsUrlService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebBrowserEventsUrlService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebBrowserEventsUrlService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebBrowserEventsUrlService_GetUrlForEvents(This,pUrl)	\
    (This)->lpVtbl -> GetUrlForEvents(This,pUrl)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IWebBrowserEventsUrlService_GetUrlForEvents_Proxy( 
    IWebBrowserEventsUrlService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pUrl);


void __RPC_STUB IWebBrowserEventsUrlService_GetUrlForEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebBrowserEventsUrlService_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_webevnts_0086 */
/* [local] */ 

#endif


extern RPC_IF_HANDLE __MIDL_itf_webevnts_0086_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_webevnts_0086_v0_0_s_ifspec;

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


