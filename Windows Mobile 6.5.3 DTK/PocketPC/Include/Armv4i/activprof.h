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
/* at Tue Nov 10 18:44:43 2009
 */
/* Compiler settings for .\activprof.idl:
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

#ifndef __activprof_h__
#define __activprof_h__

/* Forward Declarations */ 

#ifndef __IActiveScriptProfilerControl_FWD_DEFINED__
#define __IActiveScriptProfilerControl_FWD_DEFINED__
typedef interface IActiveScriptProfilerControl IActiveScriptProfilerControl;
#endif 	/* __IActiveScriptProfilerControl_FWD_DEFINED__ */


#ifndef __IActiveScriptProfilerCallback_FWD_DEFINED__
#define __IActiveScriptProfilerCallback_FWD_DEFINED__
typedef interface IActiveScriptProfilerCallback IActiveScriptProfilerCallback;
#endif 	/* __IActiveScriptProfilerCallback_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_activprof_0000 */
/* [local] */ 

//=--------------------------------------------------------------------------=
// ActivProf.h
//=--------------------------------------------------------------------------=
// Copyright (c) Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
#pragma comment(lib,"uuid.lib")
//
// Declarations for ActiveX Scripting profiling.
//

const HRESULT ACTIVPROF_E_PROFILER_PRESENT = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0200);
const HRESULT ACTIVPROF_E_PROFILER_ABSENT = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0201);
const HRESULT ACTIVPROF_E_UNABLE_TO_APPLY_ACTION = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0202);

#ifndef __ActivProf_h
#define __ActivProf_h

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_activprof_0000_0001
    {	PROFILER_SCRIPT_TYPE_USER	= 0,
	PROFILER_SCRIPT_TYPE_DYNAMIC	= PROFILER_SCRIPT_TYPE_USER + 1,
	PROFILER_SCRIPT_TYPE_NATIVE	= PROFILER_SCRIPT_TYPE_DYNAMIC + 1
    }	PROFILER_SCRIPT_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_activprof_0000_0002
    {	PROFILER_EVENT_MASK_TRACE_SCRIPT_FUNCTION_CALL	= 0x1,
	PROFILER_EVENT_MASK_TRACE_NATIVE_FUNCTION_CALL	= 0x2,
	PROFILER_EVENT_MASK_TRACE_ALL	= PROFILER_EVENT_MASK_TRACE_SCRIPT_FUNCTION_CALL | PROFILER_EVENT_MASK_TRACE_NATIVE_FUNCTION_CALL
    }	PROFILER_EVENT_MASK;

typedef LONG PROFILER_TOKEN;



extern RPC_IF_HANDLE __MIDL_itf_activprof_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_activprof_0000_v0_0_s_ifspec;

#ifndef __IActiveScriptProfilerControl_INTERFACE_DEFINED__
#define __IActiveScriptProfilerControl_INTERFACE_DEFINED__

/* interface IActiveScriptProfilerControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IActiveScriptProfilerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("784b5ff0-69b0-47d1-a7dc-2518f4230e90")
    IActiveScriptProfilerControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartProfiling( 
            /* [in] */ REFCLSID clsidProfilerObject,
            /* [in] */ DWORD dwEventMask,
            /* [in] */ DWORD dwContext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProfilerEventMask( 
            /* [in] */ DWORD dwEventMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopProfiling( 
            /* [in] */ HRESULT hrShutdownReason) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IActiveScriptProfilerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IActiveScriptProfilerControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IActiveScriptProfilerControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IActiveScriptProfilerControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartProfiling )( 
            IActiveScriptProfilerControl __RPC_FAR * This,
            /* [in] */ REFCLSID clsidProfilerObject,
            /* [in] */ DWORD dwEventMask,
            /* [in] */ DWORD dwContext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProfilerEventMask )( 
            IActiveScriptProfilerControl __RPC_FAR * This,
            /* [in] */ DWORD dwEventMask);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopProfiling )( 
            IActiveScriptProfilerControl __RPC_FAR * This,
            /* [in] */ HRESULT hrShutdownReason);
        
        END_INTERFACE
    } IActiveScriptProfilerControlVtbl;

    interface IActiveScriptProfilerControl
    {
        CONST_VTBL struct IActiveScriptProfilerControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IActiveScriptProfilerControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IActiveScriptProfilerControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IActiveScriptProfilerControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IActiveScriptProfilerControl_StartProfiling(This,clsidProfilerObject,dwEventMask,dwContext)	\
    (This)->lpVtbl -> StartProfiling(This,clsidProfilerObject,dwEventMask,dwContext)

#define IActiveScriptProfilerControl_SetProfilerEventMask(This,dwEventMask)	\
    (This)->lpVtbl -> SetProfilerEventMask(This,dwEventMask)

#define IActiveScriptProfilerControl_StopProfiling(This,hrShutdownReason)	\
    (This)->lpVtbl -> StopProfiling(This,hrShutdownReason)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IActiveScriptProfilerControl_StartProfiling_Proxy( 
    IActiveScriptProfilerControl __RPC_FAR * This,
    /* [in] */ REFCLSID clsidProfilerObject,
    /* [in] */ DWORD dwEventMask,
    /* [in] */ DWORD dwContext);


void __RPC_STUB IActiveScriptProfilerControl_StartProfiling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerControl_SetProfilerEventMask_Proxy( 
    IActiveScriptProfilerControl __RPC_FAR * This,
    /* [in] */ DWORD dwEventMask);


void __RPC_STUB IActiveScriptProfilerControl_SetProfilerEventMask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerControl_StopProfiling_Proxy( 
    IActiveScriptProfilerControl __RPC_FAR * This,
    /* [in] */ HRESULT hrShutdownReason);


void __RPC_STUB IActiveScriptProfilerControl_StopProfiling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IActiveScriptProfilerControl_INTERFACE_DEFINED__ */


#ifndef __IActiveScriptProfilerCallback_INTERFACE_DEFINED__
#define __IActiveScriptProfilerCallback_INTERFACE_DEFINED__

/* interface IActiveScriptProfilerCallback */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IActiveScriptProfilerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("740eca23-7d9d-42e5-ba9d-f8b24b1c7a9b")
    IActiveScriptProfilerCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ DWORD dwContext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Shutdown( 
            /* [in] */ HRESULT hrReason) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ScriptCompiled( 
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [in] */ PROFILER_SCRIPT_TYPE type,
            /* [in] */ IUnknown __RPC_FAR *pIDebugDocumentContext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FunctionCompiled( 
            /* [in] */ PROFILER_TOKEN functionId,
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [string][in] */ const WCHAR __RPC_FAR *pwszFunctionName,
            /* [string][in] */ const WCHAR __RPC_FAR *pwszFunctionNameHint,
            /* [in] */ IUnknown __RPC_FAR *pIDebugDocumentContext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnFunctionEnter( 
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [in] */ PROFILER_TOKEN functionId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnFunctionExit( 
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [in] */ PROFILER_TOKEN functionId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IActiveScriptProfilerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IActiveScriptProfilerCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IActiveScriptProfilerCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ DWORD dwContext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ HRESULT hrReason);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScriptCompiled )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [in] */ PROFILER_SCRIPT_TYPE type,
            /* [in] */ IUnknown __RPC_FAR *pIDebugDocumentContext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FunctionCompiled )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ PROFILER_TOKEN functionId,
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [string][in] */ const WCHAR __RPC_FAR *pwszFunctionName,
            /* [string][in] */ const WCHAR __RPC_FAR *pwszFunctionNameHint,
            /* [in] */ IUnknown __RPC_FAR *pIDebugDocumentContext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFunctionEnter )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [in] */ PROFILER_TOKEN functionId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFunctionExit )( 
            IActiveScriptProfilerCallback __RPC_FAR * This,
            /* [in] */ PROFILER_TOKEN scriptId,
            /* [in] */ PROFILER_TOKEN functionId);
        
        END_INTERFACE
    } IActiveScriptProfilerCallbackVtbl;

    interface IActiveScriptProfilerCallback
    {
        CONST_VTBL struct IActiveScriptProfilerCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IActiveScriptProfilerCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IActiveScriptProfilerCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IActiveScriptProfilerCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IActiveScriptProfilerCallback_Initialize(This,dwContext)	\
    (This)->lpVtbl -> Initialize(This,dwContext)

#define IActiveScriptProfilerCallback_Shutdown(This,hrReason)	\
    (This)->lpVtbl -> Shutdown(This,hrReason)

#define IActiveScriptProfilerCallback_ScriptCompiled(This,scriptId,type,pIDebugDocumentContext)	\
    (This)->lpVtbl -> ScriptCompiled(This,scriptId,type,pIDebugDocumentContext)

#define IActiveScriptProfilerCallback_FunctionCompiled(This,functionId,scriptId,pwszFunctionName,pwszFunctionNameHint,pIDebugDocumentContext)	\
    (This)->lpVtbl -> FunctionCompiled(This,functionId,scriptId,pwszFunctionName,pwszFunctionNameHint,pIDebugDocumentContext)

#define IActiveScriptProfilerCallback_OnFunctionEnter(This,scriptId,functionId)	\
    (This)->lpVtbl -> OnFunctionEnter(This,scriptId,functionId)

#define IActiveScriptProfilerCallback_OnFunctionExit(This,scriptId,functionId)	\
    (This)->lpVtbl -> OnFunctionExit(This,scriptId,functionId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IActiveScriptProfilerCallback_Initialize_Proxy( 
    IActiveScriptProfilerCallback __RPC_FAR * This,
    /* [in] */ DWORD dwContext);


void __RPC_STUB IActiveScriptProfilerCallback_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerCallback_Shutdown_Proxy( 
    IActiveScriptProfilerCallback __RPC_FAR * This,
    /* [in] */ HRESULT hrReason);


void __RPC_STUB IActiveScriptProfilerCallback_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerCallback_ScriptCompiled_Proxy( 
    IActiveScriptProfilerCallback __RPC_FAR * This,
    /* [in] */ PROFILER_TOKEN scriptId,
    /* [in] */ PROFILER_SCRIPT_TYPE type,
    /* [in] */ IUnknown __RPC_FAR *pIDebugDocumentContext);


void __RPC_STUB IActiveScriptProfilerCallback_ScriptCompiled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerCallback_FunctionCompiled_Proxy( 
    IActiveScriptProfilerCallback __RPC_FAR * This,
    /* [in] */ PROFILER_TOKEN functionId,
    /* [in] */ PROFILER_TOKEN scriptId,
    /* [string][in] */ const WCHAR __RPC_FAR *pwszFunctionName,
    /* [string][in] */ const WCHAR __RPC_FAR *pwszFunctionNameHint,
    /* [in] */ IUnknown __RPC_FAR *pIDebugDocumentContext);


void __RPC_STUB IActiveScriptProfilerCallback_FunctionCompiled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerCallback_OnFunctionEnter_Proxy( 
    IActiveScriptProfilerCallback __RPC_FAR * This,
    /* [in] */ PROFILER_TOKEN scriptId,
    /* [in] */ PROFILER_TOKEN functionId);


void __RPC_STUB IActiveScriptProfilerCallback_OnFunctionEnter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActiveScriptProfilerCallback_OnFunctionExit_Proxy( 
    IActiveScriptProfilerCallback __RPC_FAR * This,
    /* [in] */ PROFILER_TOKEN scriptId,
    /* [in] */ PROFILER_TOKEN functionId);


void __RPC_STUB IActiveScriptProfilerCallback_OnFunctionExit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IActiveScriptProfilerCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_activprof_0008 */
/* [local] */ 


#endif  // __ActivProf_h



extern RPC_IF_HANDLE __MIDL_itf_activprof_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_activprof_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


