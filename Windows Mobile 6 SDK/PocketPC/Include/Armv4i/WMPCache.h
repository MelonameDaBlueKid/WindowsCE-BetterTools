
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Fri Mar 09 19:09:03 2007
 */
/* Compiler settings for .\WMPCache.idl:
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

#ifndef __WMPCache_h__
#define __WMPCache_h__

/* Forward Declarations */ 

#ifndef __IWMPCache_FWD_DEFINED__
#define __IWMPCache_FWD_DEFINED__
typedef interface IWMPCache IWMPCache;
#endif 	/* __IWMPCache_FWD_DEFINED__ */


#ifndef __IWMPCacheFilter_FWD_DEFINED__
#define __IWMPCacheFilter_FWD_DEFINED__
typedef interface IWMPCacheFilter IWMPCacheFilter;
#endif 	/* __IWMPCacheFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"
#include "oleidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IWMPCache_INTERFACE_DEFINED__
#define __IWMPCache_INTERFACE_DEFINED__

/* interface IWMPCache */
/* [object][uuid] */ 


EXTERN_C const IID IID_IWMPCache;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f9c9352a-a0ed-4cf7-abd5-75a758cd9492")
    IWMPCache : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CacheStream( 
            /* [in] */ IStream __RPC_FAR *pstmSrc,
            /* [retval][out] */ IStream __RPC_FAR *__RPC_FAR *ppstmCache) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CacheFile( 
            /* [in] */ LPCWSTR szFilePath,
            /* [retval][out] */ IStream __RPC_FAR *__RPC_FAR *ppstmCache) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsCacheReady( 
            /* [in] */ IStream __RPC_FAR *pstmCache,
            /* [retval][out] */ BOOL __RPC_FAR *pfValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMPCacheVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMPCache __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMPCache __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMPCache __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CacheStream )( 
            IWMPCache __RPC_FAR * This,
            /* [in] */ IStream __RPC_FAR *pstmSrc,
            /* [retval][out] */ IStream __RPC_FAR *__RPC_FAR *ppstmCache);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CacheFile )( 
            IWMPCache __RPC_FAR * This,
            /* [in] */ LPCWSTR szFilePath,
            /* [retval][out] */ IStream __RPC_FAR *__RPC_FAR *ppstmCache);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCacheReady )( 
            IWMPCache __RPC_FAR * This,
            /* [in] */ IStream __RPC_FAR *pstmCache,
            /* [retval][out] */ BOOL __RPC_FAR *pfValid);
        
        END_INTERFACE
    } IWMPCacheVtbl;

    interface IWMPCache
    {
        CONST_VTBL struct IWMPCacheVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMPCache_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMPCache_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMPCache_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMPCache_CacheStream(This,pstmSrc,ppstmCache)	\
    (This)->lpVtbl -> CacheStream(This,pstmSrc,ppstmCache)

#define IWMPCache_CacheFile(This,szFilePath,ppstmCache)	\
    (This)->lpVtbl -> CacheFile(This,szFilePath,ppstmCache)

#define IWMPCache_IsCacheReady(This,pstmCache,pfValid)	\
    (This)->lpVtbl -> IsCacheReady(This,pstmCache,pfValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWMPCache_CacheStream_Proxy( 
    IWMPCache __RPC_FAR * This,
    /* [in] */ IStream __RPC_FAR *pstmSrc,
    /* [retval][out] */ IStream __RPC_FAR *__RPC_FAR *ppstmCache);


void __RPC_STUB IWMPCache_CacheStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMPCache_CacheFile_Proxy( 
    IWMPCache __RPC_FAR * This,
    /* [in] */ LPCWSTR szFilePath,
    /* [retval][out] */ IStream __RPC_FAR *__RPC_FAR *ppstmCache);


void __RPC_STUB IWMPCache_CacheFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMPCache_IsCacheReady_Proxy( 
    IWMPCache __RPC_FAR * This,
    /* [in] */ IStream __RPC_FAR *pstmCache,
    /* [retval][out] */ BOOL __RPC_FAR *pfValid);


void __RPC_STUB IWMPCache_IsCacheReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMPCache_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_WMPCache_0106 */
/* [local] */ 

typedef 
enum WMPCacheEvent
    {	wmpceUnknown	= 0,
	wmpceFileSysDelete	= wmpceUnknown + 1,
	wmpceFileSysMount	= wmpceFileSysDelete + 1,
	wmpceFileSysUnmount	= wmpceFileSysMount + 1
    }	WMPCacheEvent;



extern RPC_IF_HANDLE __MIDL_itf_WMPCache_0106_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WMPCache_0106_v0_0_s_ifspec;

#ifndef __IWMPCacheFilter_INTERFACE_DEFINED__
#define __IWMPCacheFilter_INTERFACE_DEFINED__

/* interface IWMPCacheFilter */
/* [object][uuid] */ 


EXTERN_C const IID IID_IWMPCacheFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10827706-846a-463b-a0aa-425bbb7464ca")
    IWMPCacheFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetWMPCache( 
            /* [in] */ IWMPCache __RPC_FAR *pWMPCache) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Queue( 
            /* [retval][out] */ BOOL __RPC_FAR *pfCacheEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleEvent( 
            /* [in] */ WMPCacheEvent wmpce,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMPCacheFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMPCacheFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMPCacheFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMPCacheFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWMPCache )( 
            IWMPCacheFilter __RPC_FAR * This,
            /* [in] */ IWMPCache __RPC_FAR *pWMPCache);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Queue )( 
            IWMPCacheFilter __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfCacheEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleEvent )( 
            IWMPCacheFilter __RPC_FAR * This,
            /* [in] */ WMPCacheEvent wmpce,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        END_INTERFACE
    } IWMPCacheFilterVtbl;

    interface IWMPCacheFilter
    {
        CONST_VTBL struct IWMPCacheFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMPCacheFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMPCacheFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMPCacheFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMPCacheFilter_SetWMPCache(This,pWMPCache)	\
    (This)->lpVtbl -> SetWMPCache(This,pWMPCache)

#define IWMPCacheFilter_Queue(This,pfCacheEnabled)	\
    (This)->lpVtbl -> Queue(This,pfCacheEnabled)

#define IWMPCacheFilter_HandleEvent(This,wmpce,wParam,lParam)	\
    (This)->lpVtbl -> HandleEvent(This,wmpce,wParam,lParam)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWMPCacheFilter_SetWMPCache_Proxy( 
    IWMPCacheFilter __RPC_FAR * This,
    /* [in] */ IWMPCache __RPC_FAR *pWMPCache);


void __RPC_STUB IWMPCacheFilter_SetWMPCache_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMPCacheFilter_Queue_Proxy( 
    IWMPCacheFilter __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfCacheEnabled);


void __RPC_STUB IWMPCacheFilter_Queue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMPCacheFilter_HandleEvent_Proxy( 
    IWMPCacheFilter __RPC_FAR * This,
    /* [in] */ WMPCacheEvent wmpce,
    /* [in] */ WPARAM wParam,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IWMPCacheFilter_HandleEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMPCacheFilter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


