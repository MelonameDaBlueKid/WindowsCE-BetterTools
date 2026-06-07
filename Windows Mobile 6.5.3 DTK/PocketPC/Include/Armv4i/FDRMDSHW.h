
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Wed Nov 11 03:10:46 2009
 */
/* Compiler settings for .\FDRMDSHW.idl:
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

#ifndef __FDRMDSHW_h__
#define __FDRMDSHW_h__

/* Forward Declarations */ 

#ifndef __IFileDrmHandler_FWD_DEFINED__
#define __IFileDrmHandler_FWD_DEFINED__
typedef interface IFileDrmHandler IFileDrmHandler;
#endif 	/* __IFileDrmHandler_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"
#include "oleidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IFileDrmHandler_INTERFACE_DEFINED__
#define __IFileDrmHandler_INTERFACE_DEFINED__

/* interface IFileDrmHandler */
/* [object][uuid] */ 


EXTERN_C const IID IID_IFileDrmHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F76ACC7A-30E5-4569-8270-0CA1A14C6F0D")
    IFileDrmHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsPlayable( 
            /* [out] */ BOOL __RPC_FAR *pfRequestUI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleError( 
            /* [in] */ HWND hwndParent,
            /* [in] */ HRESULT hrError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileDrmHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFileDrmHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFileDrmHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFileDrmHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPlayable )( 
            IFileDrmHandler __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pfRequestUI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleError )( 
            IFileDrmHandler __RPC_FAR * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ HRESULT hrError);
        
        END_INTERFACE
    } IFileDrmHandlerVtbl;

    interface IFileDrmHandler
    {
        CONST_VTBL struct IFileDrmHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileDrmHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileDrmHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileDrmHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileDrmHandler_IsPlayable(This,pfRequestUI)	\
    (This)->lpVtbl -> IsPlayable(This,pfRequestUI)

#define IFileDrmHandler_HandleError(This,hwndParent,hrError)	\
    (This)->lpVtbl -> HandleError(This,hwndParent,hrError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileDrmHandler_IsPlayable_Proxy( 
    IFileDrmHandler __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pfRequestUI);


void __RPC_STUB IFileDrmHandler_IsPlayable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDrmHandler_HandleError_Proxy( 
    IFileDrmHandler __RPC_FAR * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ HRESULT hrError);


void __RPC_STUB IFileDrmHandler_HandleError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileDrmHandler_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long __RPC_FAR *, unsigned long            , HWND __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HWND_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HWND __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HWND_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HWND __RPC_FAR * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long __RPC_FAR *, HWND __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


