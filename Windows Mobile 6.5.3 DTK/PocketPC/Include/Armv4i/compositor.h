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
/* at Tue Nov 10 18:44:48 2009
 */
/* Compiler settings for .\compositor.idl:
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

#ifndef __compositor_h__
#define __compositor_h__

/* Forward Declarations */ 

#ifndef __ICompositor_FWD_DEFINED__
#define __ICompositor_FWD_DEFINED__
typedef interface ICompositor ICompositor;
#endif 	/* __ICompositor_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_compositor_0000 */
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
// ICompositor Interface.




extern RPC_IF_HANDLE __MIDL_itf_compositor_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_compositor_0000_v0_0_s_ifspec;

#ifndef __ICompositor_INTERFACE_DEFINED__
#define __ICompositor_INTERFACE_DEFINED__

/* interface ICompositor */
/* [unique][uuid][object][local] */ 

typedef /* [unique] */ ICompositor __RPC_FAR *LPCOMPOSITOR;


EXTERN_C const IID IID_ICompositor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("da4ad2c2-87c6-4a43-9619-bf12508f6b5b")
    ICompositor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCompositionRects( 
            /* [out] */ RECT __RPC_FAR *__RPC_FAR *pprcComposite,
            /* [out] */ ULONG __RPC_FAR *pcRects) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoComposition( 
            /* [in] */ HDC hdc,
            /* [in] */ const RECT __RPC_FAR *prcUpdate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICompositorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICompositor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICompositor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICompositor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCompositionRects )( 
            ICompositor __RPC_FAR * This,
            /* [out] */ RECT __RPC_FAR *__RPC_FAR *pprcComposite,
            /* [out] */ ULONG __RPC_FAR *pcRects);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoComposition )( 
            ICompositor __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ const RECT __RPC_FAR *prcUpdate);
        
        END_INTERFACE
    } ICompositorVtbl;

    interface ICompositor
    {
        CONST_VTBL struct ICompositorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICompositor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICompositor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICompositor_GetCompositionRects(This,pprcComposite,pcRects)	\
    (This)->lpVtbl -> GetCompositionRects(This,pprcComposite,pcRects)

#define ICompositor_DoComposition(This,hdc,prcUpdate)	\
    (This)->lpVtbl -> DoComposition(This,hdc,prcUpdate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICompositor_GetCompositionRects_Proxy( 
    ICompositor __RPC_FAR * This,
    /* [out] */ RECT __RPC_FAR *__RPC_FAR *pprcComposite,
    /* [out] */ ULONG __RPC_FAR *pcRects);


void __RPC_STUB ICompositor_GetCompositionRects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICompositor_DoComposition_Proxy( 
    ICompositor __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ const RECT __RPC_FAR *prcUpdate);


void __RPC_STUB ICompositor_DoComposition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICompositor_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


