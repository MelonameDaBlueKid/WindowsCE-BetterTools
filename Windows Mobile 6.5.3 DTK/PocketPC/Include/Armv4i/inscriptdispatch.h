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
/* at Tue Nov 10 18:45:45 2009
 */
/* Compiler settings for .\inscriptdispatch.idl:
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

#ifndef __inscriptdispatch_h__
#define __inscriptdispatch_h__

/* Forward Declarations */ 

#ifndef __IInScriptDispatch_FWD_DEFINED__
#define __IInScriptDispatch_FWD_DEFINED__
typedef interface IInScriptDispatch IInScriptDispatch;
#endif 	/* __IInScriptDispatch_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_inscriptdispatch_0000 */
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

#pragma comment(lib,"uuid.lib")

//---------------------------------------------------------------------------=
// IInScriptDispatch Interface.




extern RPC_IF_HANDLE __MIDL_itf_inscriptdispatch_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_inscriptdispatch_0000_v0_0_s_ifspec;

#ifndef __IInScriptDispatch_INTERFACE_DEFINED__
#define __IInScriptDispatch_INTERFACE_DEFINED__

/* interface IInScriptDispatch */
/* [unique][uuid][object][local] */ 

typedef /* [unique] */ IInScriptDispatch __RPC_FAR *LPINSCRIPTDISPATCH;


EXTERN_C const IID IID_IInScriptDispatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ed80b4a3-9c85-43da-98ac-b87757d04990")
    IInScriptDispatch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartInScriptMessageDispatch( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DispatchInScriptMessages( 
            /* [in] */ DWORD dwTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RunInScriptTimers( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnHyperlinkClick( 
            LPCTSTR lpstrUrl,
            BOOL fLocalNavigation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndInScriptMessageDispatch( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInScriptDispatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInScriptDispatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInScriptDispatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInScriptDispatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartInScriptMessageDispatch )( 
            IInScriptDispatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DispatchInScriptMessages )( 
            IInScriptDispatch __RPC_FAR * This,
            /* [in] */ DWORD dwTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunInScriptTimers )( 
            IInScriptDispatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnHyperlinkClick )( 
            IInScriptDispatch __RPC_FAR * This,
            LPCTSTR lpstrUrl,
            BOOL fLocalNavigation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndInScriptMessageDispatch )( 
            IInScriptDispatch __RPC_FAR * This);
        
        END_INTERFACE
    } IInScriptDispatchVtbl;

    interface IInScriptDispatch
    {
        CONST_VTBL struct IInScriptDispatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInScriptDispatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInScriptDispatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInScriptDispatch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInScriptDispatch_StartInScriptMessageDispatch(This)	\
    (This)->lpVtbl -> StartInScriptMessageDispatch(This)

#define IInScriptDispatch_DispatchInScriptMessages(This,dwTimeout)	\
    (This)->lpVtbl -> DispatchInScriptMessages(This,dwTimeout)

#define IInScriptDispatch_RunInScriptTimers(This)	\
    (This)->lpVtbl -> RunInScriptTimers(This)

#define IInScriptDispatch_OnHyperlinkClick(This,lpstrUrl,fLocalNavigation)	\
    (This)->lpVtbl -> OnHyperlinkClick(This,lpstrUrl,fLocalNavigation)

#define IInScriptDispatch_EndInScriptMessageDispatch(This)	\
    (This)->lpVtbl -> EndInScriptMessageDispatch(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IInScriptDispatch_StartInScriptMessageDispatch_Proxy( 
    IInScriptDispatch __RPC_FAR * This);


void __RPC_STUB IInScriptDispatch_StartInScriptMessageDispatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IInScriptDispatch_DispatchInScriptMessages_Proxy( 
    IInScriptDispatch __RPC_FAR * This,
    /* [in] */ DWORD dwTimeout);


void __RPC_STUB IInScriptDispatch_DispatchInScriptMessages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IInScriptDispatch_RunInScriptTimers_Proxy( 
    IInScriptDispatch __RPC_FAR * This);


void __RPC_STUB IInScriptDispatch_RunInScriptTimers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IInScriptDispatch_OnHyperlinkClick_Proxy( 
    IInScriptDispatch __RPC_FAR * This,
    LPCTSTR lpstrUrl,
    BOOL fLocalNavigation);


void __RPC_STUB IInScriptDispatch_OnHyperlinkClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IInScriptDispatch_EndInScriptMessageDispatch_Proxy( 
    IInScriptDispatch __RPC_FAR * This);


void __RPC_STUB IInScriptDispatch_EndInScriptMessageDispatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInScriptDispatch_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


