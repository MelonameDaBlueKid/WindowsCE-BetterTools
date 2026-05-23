
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Thu Mar 13 23:49:49 2003
 */
/* Compiler settings for .\voipprov.idl:
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

#ifndef __voipprov_h__
#define __voipprov_h__

/* Forward Declarations */ 

#ifndef __IVoIPDirectoryClient_FWD_DEFINED__
#define __IVoIPDirectoryClient_FWD_DEFINED__
typedef interface IVoIPDirectoryClient IVoIPDirectoryClient;
#endif 	/* __IVoIPDirectoryClient_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "voipmanager.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IVoIPDirectoryClient_INTERFACE_DEFINED__
#define __IVoIPDirectoryClient_INTERFACE_DEFINED__

/* interface IVoIPDirectoryClient */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPDirectoryClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21B9AAE6-4741-44BE-9374-4D56572C3CF3")
    IVoIPDirectoryClient : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_RegistrationParameters( 
            /* [in] */ DirectoryClientRegParams __RPC_FAR *pdcrp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_SipPassword( 
            /* [in] */ BSTR bstrSipPassword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_SipServerParameters( 
            /* [out] */ BSTR __RPC_FAR *pbstrMyURI,
            /* [out] */ BSTR __RPC_FAR *pbstrMyServer,
            /* [out] */ BSTR __RPC_FAR *pbstrProfileString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPDirectoryClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPDirectoryClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPDirectoryClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPDirectoryClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RegistrationParameters )( 
            IVoIPDirectoryClient __RPC_FAR * This,
            /* [in] */ DirectoryClientRegParams __RPC_FAR *pdcrp);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SipPassword )( 
            IVoIPDirectoryClient __RPC_FAR * This,
            /* [in] */ BSTR bstrSipPassword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SipServerParameters )( 
            IVoIPDirectoryClient __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrMyURI,
            /* [out] */ BSTR __RPC_FAR *pbstrMyServer,
            /* [out] */ BSTR __RPC_FAR *pbstrProfileString);
        
        END_INTERFACE
    } IVoIPDirectoryClientVtbl;

    interface IVoIPDirectoryClient
    {
        CONST_VTBL struct IVoIPDirectoryClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPDirectoryClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPDirectoryClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPDirectoryClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPDirectoryClient_put_RegistrationParameters(This,pdcrp)	\
    (This)->lpVtbl -> put_RegistrationParameters(This,pdcrp)

#define IVoIPDirectoryClient_put_SipPassword(This,bstrSipPassword)	\
    (This)->lpVtbl -> put_SipPassword(This,bstrSipPassword)

#define IVoIPDirectoryClient_get_SipServerParameters(This,pbstrMyURI,pbstrMyServer,pbstrProfileString)	\
    (This)->lpVtbl -> get_SipServerParameters(This,pbstrMyURI,pbstrMyServer,pbstrProfileString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPDirectoryClient_put_RegistrationParameters_Proxy( 
    IVoIPDirectoryClient __RPC_FAR * This,
    /* [in] */ DirectoryClientRegParams __RPC_FAR *pdcrp);


void __RPC_STUB IVoIPDirectoryClient_put_RegistrationParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPDirectoryClient_put_SipPassword_Proxy( 
    IVoIPDirectoryClient __RPC_FAR * This,
    /* [in] */ BSTR bstrSipPassword);


void __RPC_STUB IVoIPDirectoryClient_put_SipPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPDirectoryClient_get_SipServerParameters_Proxy( 
    IVoIPDirectoryClient __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrMyURI,
    /* [out] */ BSTR __RPC_FAR *pbstrMyServer,
    /* [out] */ BSTR __RPC_FAR *pbstrProfileString);


void __RPC_STUB IVoIPDirectoryClient_get_SipServerParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPDirectoryClient_INTERFACE_DEFINED__ */


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


