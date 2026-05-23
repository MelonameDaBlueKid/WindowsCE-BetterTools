
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Thu Mar 13 23:49:47 2003
 */
/* Compiler settings for .\voipstore.idl:
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

#ifndef __voipstore_h__
#define __voipstore_h__

/* Forward Declarations */ 

#ifndef __IVoIPCallRecord_FWD_DEFINED__
#define __IVoIPCallRecord_FWD_DEFINED__
typedef interface IVoIPCallRecord IVoIPCallRecord;
#endif 	/* __IVoIPCallRecord_FWD_DEFINED__ */


#ifndef __IVoIPCallLogDB_FWD_DEFINED__
#define __IVoIPCallLogDB_FWD_DEFINED__
typedef interface IVoIPCallLogDB IVoIPCallLogDB;
#endif 	/* __IVoIPCallLogDB_FWD_DEFINED__ */


#ifndef __IVoIPCallLogDBEnum_FWD_DEFINED__
#define __IVoIPCallLogDBEnum_FWD_DEFINED__
typedef interface IVoIPCallLogDBEnum IVoIPCallLogDBEnum;
#endif 	/* __IVoIPCallLogDBEnum_FWD_DEFINED__ */


#ifndef __IVoIPCallerInfoRecord_FWD_DEFINED__
#define __IVoIPCallerInfoRecord_FWD_DEFINED__
typedef interface IVoIPCallerInfoRecord IVoIPCallerInfoRecord;
#endif 	/* __IVoIPCallerInfoRecord_FWD_DEFINED__ */


#ifndef __IVoIPCallerInfoDB_FWD_DEFINED__
#define __IVoIPCallerInfoDB_FWD_DEFINED__
typedef interface IVoIPCallerInfoDB IVoIPCallerInfoDB;
#endif 	/* __IVoIPCallerInfoDB_FWD_DEFINED__ */


#ifndef __IVoIPCallerInfoDBEnum_FWD_DEFINED__
#define __IVoIPCallerInfoDBEnum_FWD_DEFINED__
typedef interface IVoIPCallerInfoDBEnum IVoIPCallerInfoDBEnum;
#endif 	/* __IVoIPCallerInfoDBEnum_FWD_DEFINED__ */


#ifndef __VoIPCallLogRecord_FWD_DEFINED__
#define __VoIPCallLogRecord_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoIPCallLogRecord VoIPCallLogRecord;
#else
typedef struct VoIPCallLogRecord VoIPCallLogRecord;
#endif /* __cplusplus */

#endif 	/* __VoIPCallLogRecord_FWD_DEFINED__ */


#ifndef __VoIPCallLogDB_FWD_DEFINED__
#define __VoIPCallLogDB_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoIPCallLogDB VoIPCallLogDB;
#else
typedef struct VoIPCallLogDB VoIPCallLogDB;
#endif /* __cplusplus */

#endif 	/* __VoIPCallLogDB_FWD_DEFINED__ */


#ifndef __VoIPCallerInfoDB_FWD_DEFINED__
#define __VoIPCallerInfoDB_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoIPCallerInfoDB VoIPCallerInfoDB;
#else
typedef struct VoIPCallerInfoDB VoIPCallerInfoDB;
#endif /* __cplusplus */

#endif 	/* __VoIPCallerInfoDB_FWD_DEFINED__ */


/* header files for imported files */
#include "voiperrorcodes.h"
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_voipstore_0000 */
/* [local] */ 


enum __MIDL___MIDL_itf_voipstore_0000_0001
    {	VOIP_INVALID_SPEED_DIAL_ENTRY	= -1
    };
typedef 
enum VoIPCallType
    {	e_vctInvalid	= 0,
	e_vctIncoming	= e_vctInvalid + 1,
	e_vctOutgoing	= e_vctIncoming + 1,
	e_vctMissed	= e_vctOutgoing + 1
    }	VoIPCallType;

#define	VCT_FIRST	( e_vctInvalid )

#define	VCT_LAST	( e_vctMissed )





extern RPC_IF_HANDLE __MIDL_itf_voipstore_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_voipstore_0000_v0_0_s_ifspec;

#ifndef __IVoIPCallRecord_INTERFACE_DEFINED__
#define __IVoIPCallRecord_INTERFACE_DEFINED__

/* interface IVoIPCallRecord */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCallRecord;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AAC6F8C9-69AA-4C06-852E-BCBDA7FB77D5")
    IVoIPCallRecord : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_URI( 
            /* [in] */ BSTR bstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_URI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_FriendlyName( 
            /* [in] */ BSTR bstrFriendlyName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_FriendlyName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VoIPName( 
            /* [in] */ BSTR bstrVoIPName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VoIPName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_CallType( 
            /* [in] */ VoIPCallType vctType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CallType( 
            /* [retval][out] */ VoIPCallType __RPC_FAR *pvctType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_StartTime( 
            /* [in] */ SYSTEMTIME time) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *ptime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_EndTime( 
            /* [in] */ SYSTEMTIME time) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_EndTime( 
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *ptime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [in] */ SYSTEMTIME __RPC_FAR *ptime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteFromDB( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCallRecordVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCallRecord __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCallRecord __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URI )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URI )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FriendlyName )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrFriendlyName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FriendlyName )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VoIPName )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrVoIPName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VoIPName )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CallType )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ VoIPCallType vctType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallType )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [retval][out] */ VoIPCallType __RPC_FAR *pvctType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartTime )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ SYSTEMTIME time);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *ptime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EndTime )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ SYSTEMTIME time);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndTime )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *ptime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IVoIPCallRecord __RPC_FAR * This,
            /* [in] */ SYSTEMTIME __RPC_FAR *ptime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IVoIPCallRecord __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteFromDB )( 
            IVoIPCallRecord __RPC_FAR * This);
        
        END_INTERFACE
    } IVoIPCallRecordVtbl;

    interface IVoIPCallRecord
    {
        CONST_VTBL struct IVoIPCallRecordVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCallRecord_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCallRecord_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCallRecord_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCallRecord_put_URI(This,bstrURI)	\
    (This)->lpVtbl -> put_URI(This,bstrURI)

#define IVoIPCallRecord_get_URI(This,pbstrURI)	\
    (This)->lpVtbl -> get_URI(This,pbstrURI)

#define IVoIPCallRecord_put_FriendlyName(This,bstrFriendlyName)	\
    (This)->lpVtbl -> put_FriendlyName(This,bstrFriendlyName)

#define IVoIPCallRecord_get_FriendlyName(This,pbstrFriendlyName)	\
    (This)->lpVtbl -> get_FriendlyName(This,pbstrFriendlyName)

#define IVoIPCallRecord_put_VoIPName(This,bstrVoIPName)	\
    (This)->lpVtbl -> put_VoIPName(This,bstrVoIPName)

#define IVoIPCallRecord_get_VoIPName(This,pbstrVoIPName)	\
    (This)->lpVtbl -> get_VoIPName(This,pbstrVoIPName)

#define IVoIPCallRecord_put_CallType(This,vctType)	\
    (This)->lpVtbl -> put_CallType(This,vctType)

#define IVoIPCallRecord_get_CallType(This,pvctType)	\
    (This)->lpVtbl -> get_CallType(This,pvctType)

#define IVoIPCallRecord_put_StartTime(This,time)	\
    (This)->lpVtbl -> put_StartTime(This,time)

#define IVoIPCallRecord_get_StartTime(This,ptime)	\
    (This)->lpVtbl -> get_StartTime(This,ptime)

#define IVoIPCallRecord_put_EndTime(This,time)	\
    (This)->lpVtbl -> put_EndTime(This,time)

#define IVoIPCallRecord_get_EndTime(This,ptime)	\
    (This)->lpVtbl -> get_EndTime(This,ptime)

#define IVoIPCallRecord_get_Duration(This,ptime)	\
    (This)->lpVtbl -> get_Duration(This,ptime)

#define IVoIPCallRecord_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IVoIPCallRecord_DeleteFromDB(This)	\
    (This)->lpVtbl -> DeleteFromDB(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCallRecord_put_URI_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrURI);


void __RPC_STUB IVoIPCallRecord_put_URI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_URI_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);


void __RPC_STUB IVoIPCallRecord_get_URI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_put_FriendlyName_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrFriendlyName);


void __RPC_STUB IVoIPCallRecord_put_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_FriendlyName_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName);


void __RPC_STUB IVoIPCallRecord_get_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_put_VoIPName_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrVoIPName);


void __RPC_STUB IVoIPCallRecord_put_VoIPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_VoIPName_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName);


void __RPC_STUB IVoIPCallRecord_get_VoIPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_put_CallType_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ VoIPCallType vctType);


void __RPC_STUB IVoIPCallRecord_put_CallType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_CallType_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [retval][out] */ VoIPCallType __RPC_FAR *pvctType);


void __RPC_STUB IVoIPCallRecord_get_CallType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_put_StartTime_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ SYSTEMTIME time);


void __RPC_STUB IVoIPCallRecord_put_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_StartTime_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [retval][out] */ SYSTEMTIME __RPC_FAR *ptime);


void __RPC_STUB IVoIPCallRecord_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_put_EndTime_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ SYSTEMTIME time);


void __RPC_STUB IVoIPCallRecord_put_EndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_EndTime_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [retval][out] */ SYSTEMTIME __RPC_FAR *ptime);


void __RPC_STUB IVoIPCallRecord_get_EndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_get_Duration_Proxy( 
    IVoIPCallRecord __RPC_FAR * This,
    /* [in] */ SYSTEMTIME __RPC_FAR *ptime);


void __RPC_STUB IVoIPCallRecord_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_Commit_Proxy( 
    IVoIPCallRecord __RPC_FAR * This);


void __RPC_STUB IVoIPCallRecord_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallRecord_DeleteFromDB_Proxy( 
    IVoIPCallRecord __RPC_FAR * This);


void __RPC_STUB IVoIPCallRecord_DeleteFromDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCallRecord_INTERFACE_DEFINED__ */


#ifndef __IVoIPCallLogDB_INTERFACE_DEFINED__
#define __IVoIPCallLogDB_INTERFACE_DEFINED__

/* interface IVoIPCallLogDB */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCallLogDB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1098634-9F60-4E94-BF0C-844A3D6F695B")
    IVoIPCallLogDB : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BSTR bstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateRecord( 
            /* [in] */ enum VoIPCallType __MIDL_0015,
            /* [retval][out] */ IVoIPCallRecord __RPC_FAR *__RPC_FAR *ppiRecord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Capacity( 
            /* [in] */ int cRecords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Capacity( 
            /* [retval][out] */ int __RPC_FAR *cRecords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_IncomingEnumerator( 
            /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_OutgoingEnumerator( 
            /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MissedEnumerator( 
            /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCallLogDBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCallLogDB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCallLogDB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [in] */ BSTR bstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateRecord )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [in] */ enum VoIPCallType __MIDL_0015,
            /* [retval][out] */ IVoIPCallRecord __RPC_FAR *__RPC_FAR *ppiRecord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Capacity )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [in] */ int cRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Capacity )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *cRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IncomingEnumerator )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutgoingEnumerator )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MissedEnumerator )( 
            IVoIPCallLogDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);
        
        END_INTERFACE
    } IVoIPCallLogDBVtbl;

    interface IVoIPCallLogDB
    {
        CONST_VTBL struct IVoIPCallLogDBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCallLogDB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCallLogDB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCallLogDB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCallLogDB_Init(This,bstrURI)	\
    (This)->lpVtbl -> Init(This,bstrURI)

#define IVoIPCallLogDB_CreateRecord(This,__MIDL_0015,ppiRecord)	\
    (This)->lpVtbl -> CreateRecord(This,__MIDL_0015,ppiRecord)

#define IVoIPCallLogDB_put_Capacity(This,cRecords)	\
    (This)->lpVtbl -> put_Capacity(This,cRecords)

#define IVoIPCallLogDB_get_Capacity(This,cRecords)	\
    (This)->lpVtbl -> get_Capacity(This,cRecords)

#define IVoIPCallLogDB_get_IncomingEnumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_IncomingEnumerator(This,ppiEnum)

#define IVoIPCallLogDB_get_OutgoingEnumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_OutgoingEnumerator(This,ppiEnum)

#define IVoIPCallLogDB_get_MissedEnumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_MissedEnumerator(This,ppiEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_Init_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [in] */ BSTR bstrURI);


void __RPC_STUB IVoIPCallLogDB_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_CreateRecord_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [in] */ enum VoIPCallType __MIDL_0015,
    /* [retval][out] */ IVoIPCallRecord __RPC_FAR *__RPC_FAR *ppiRecord);


void __RPC_STUB IVoIPCallLogDB_CreateRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_put_Capacity_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [in] */ int cRecords);


void __RPC_STUB IVoIPCallLogDB_put_Capacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_get_Capacity_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *cRecords);


void __RPC_STUB IVoIPCallLogDB_get_Capacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_get_IncomingEnumerator_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPCallLogDB_get_IncomingEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_get_OutgoingEnumerator_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPCallLogDB_get_OutgoingEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDB_get_MissedEnumerator_Proxy( 
    IVoIPCallLogDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallLogDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPCallLogDB_get_MissedEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCallLogDB_INTERFACE_DEFINED__ */


#ifndef __IVoIPCallLogDBEnum_INTERFACE_DEFINED__
#define __IVoIPCallLogDBEnum_INTERFACE_DEFINED__

/* interface IVoIPCallLogDBEnum */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCallLogDBEnum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25904F27-5B67-4829-837A-470C11975F75")
    IVoIPCallLogDBEnum : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ unsigned long celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ unsigned long celt,
            /* [out] */ IVoIPCallRecord __RPC_FAR *__RPC_FAR *rgVoIPCallRecord,
            /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCallLogDBEnumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCallLogDBEnum __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCallLogDBEnum __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCallLogDBEnum __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IVoIPCallLogDBEnum __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IVoIPCallLogDBEnum __RPC_FAR * This,
            /* [in] */ unsigned long celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IVoIPCallLogDBEnum __RPC_FAR * This,
            /* [in] */ unsigned long celt,
            /* [out] */ IVoIPCallRecord __RPC_FAR *__RPC_FAR *rgVoIPCallRecord,
            /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched);
        
        END_INTERFACE
    } IVoIPCallLogDBEnumVtbl;

    interface IVoIPCallLogDBEnum
    {
        CONST_VTBL struct IVoIPCallLogDBEnumVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCallLogDBEnum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCallLogDBEnum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCallLogDBEnum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCallLogDBEnum_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IVoIPCallLogDBEnum_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IVoIPCallLogDBEnum_Next(This,celt,rgVoIPCallRecord,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgVoIPCallRecord,pceltFetched)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCallLogDBEnum_Reset_Proxy( 
    IVoIPCallLogDBEnum __RPC_FAR * This);


void __RPC_STUB IVoIPCallLogDBEnum_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDBEnum_Skip_Proxy( 
    IVoIPCallLogDBEnum __RPC_FAR * This,
    /* [in] */ unsigned long celt);


void __RPC_STUB IVoIPCallLogDBEnum_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallLogDBEnum_Next_Proxy( 
    IVoIPCallLogDBEnum __RPC_FAR * This,
    /* [in] */ unsigned long celt,
    /* [out] */ IVoIPCallRecord __RPC_FAR *__RPC_FAR *rgVoIPCallRecord,
    /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched);


void __RPC_STUB IVoIPCallLogDBEnum_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCallLogDBEnum_INTERFACE_DEFINED__ */


#ifndef __IVoIPCallerInfoRecord_INTERFACE_DEFINED__
#define __IVoIPCallerInfoRecord_INTERFACE_DEFINED__

/* interface IVoIPCallerInfoRecord */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCallerInfoRecord;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("231AAD56-AF6D-4DA2-B97A-78D69906B875")
    IVoIPCallerInfoRecord : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_URI( 
            /* [in] */ BSTR bstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_URI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_FriendlyName( 
            /* [in] */ BSTR bstrFriendlyName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_FriendlyName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VoIPName( 
            /* [in] */ BSTR bstrVoIPName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VoIPName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_SpeedDialEntry( 
            /* [in] */ int idxSpeedDial) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_SpeedDialEntry( 
            /* [retval][out] */ int __RPC_FAR *pidxSpeedDial) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Blocked( 
            /* [in] */ VARIANT_BOOL fBlocked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Blocked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBlocked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_ForwardingURI( 
            /* [in] */ BSTR bstrForwardingURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_ForwardingURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrForwardingURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_RingTone( 
            /* [in] */ BSTR bstrRingTonePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_RingTone( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRingTonePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteFromDB( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCallerInfoRecordVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCallerInfoRecord __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCallerInfoRecord __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URI )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URI )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FriendlyName )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrFriendlyName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FriendlyName )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VoIPName )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrVoIPName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VoIPName )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeedDialEntry )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ int idxSpeedDial);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeedDialEntry )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pidxSpeedDial);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Blocked )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fBlocked);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Blocked )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBlocked);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ForwardingURI )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrForwardingURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ForwardingURI )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrForwardingURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RingTone )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [in] */ BSTR bstrRingTonePath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RingTone )( 
            IVoIPCallerInfoRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRingTonePath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IVoIPCallerInfoRecord __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteFromDB )( 
            IVoIPCallerInfoRecord __RPC_FAR * This);
        
        END_INTERFACE
    } IVoIPCallerInfoRecordVtbl;

    interface IVoIPCallerInfoRecord
    {
        CONST_VTBL struct IVoIPCallerInfoRecordVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCallerInfoRecord_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCallerInfoRecord_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCallerInfoRecord_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCallerInfoRecord_put_URI(This,bstrURI)	\
    (This)->lpVtbl -> put_URI(This,bstrURI)

#define IVoIPCallerInfoRecord_get_URI(This,pbstrURI)	\
    (This)->lpVtbl -> get_URI(This,pbstrURI)

#define IVoIPCallerInfoRecord_put_FriendlyName(This,bstrFriendlyName)	\
    (This)->lpVtbl -> put_FriendlyName(This,bstrFriendlyName)

#define IVoIPCallerInfoRecord_get_FriendlyName(This,pbstrFriendlyName)	\
    (This)->lpVtbl -> get_FriendlyName(This,pbstrFriendlyName)

#define IVoIPCallerInfoRecord_put_VoIPName(This,bstrVoIPName)	\
    (This)->lpVtbl -> put_VoIPName(This,bstrVoIPName)

#define IVoIPCallerInfoRecord_get_VoIPName(This,pbstrVoIPName)	\
    (This)->lpVtbl -> get_VoIPName(This,pbstrVoIPName)

#define IVoIPCallerInfoRecord_put_SpeedDialEntry(This,idxSpeedDial)	\
    (This)->lpVtbl -> put_SpeedDialEntry(This,idxSpeedDial)

#define IVoIPCallerInfoRecord_get_SpeedDialEntry(This,pidxSpeedDial)	\
    (This)->lpVtbl -> get_SpeedDialEntry(This,pidxSpeedDial)

#define IVoIPCallerInfoRecord_put_Blocked(This,fBlocked)	\
    (This)->lpVtbl -> put_Blocked(This,fBlocked)

#define IVoIPCallerInfoRecord_get_Blocked(This,pfBlocked)	\
    (This)->lpVtbl -> get_Blocked(This,pfBlocked)

#define IVoIPCallerInfoRecord_put_ForwardingURI(This,bstrForwardingURI)	\
    (This)->lpVtbl -> put_ForwardingURI(This,bstrForwardingURI)

#define IVoIPCallerInfoRecord_get_ForwardingURI(This,pbstrForwardingURI)	\
    (This)->lpVtbl -> get_ForwardingURI(This,pbstrForwardingURI)

#define IVoIPCallerInfoRecord_put_RingTone(This,bstrRingTonePath)	\
    (This)->lpVtbl -> put_RingTone(This,bstrRingTonePath)

#define IVoIPCallerInfoRecord_get_RingTone(This,pbstrRingTonePath)	\
    (This)->lpVtbl -> get_RingTone(This,pbstrRingTonePath)

#define IVoIPCallerInfoRecord_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IVoIPCallerInfoRecord_DeleteFromDB(This)	\
    (This)->lpVtbl -> DeleteFromDB(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_URI_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrURI);


void __RPC_STUB IVoIPCallerInfoRecord_put_URI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_URI_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);


void __RPC_STUB IVoIPCallerInfoRecord_get_URI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_FriendlyName_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrFriendlyName);


void __RPC_STUB IVoIPCallerInfoRecord_put_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_FriendlyName_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName);


void __RPC_STUB IVoIPCallerInfoRecord_get_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_VoIPName_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrVoIPName);


void __RPC_STUB IVoIPCallerInfoRecord_put_VoIPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_VoIPName_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName);


void __RPC_STUB IVoIPCallerInfoRecord_get_VoIPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_SpeedDialEntry_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ int idxSpeedDial);


void __RPC_STUB IVoIPCallerInfoRecord_put_SpeedDialEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_SpeedDialEntry_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pidxSpeedDial);


void __RPC_STUB IVoIPCallerInfoRecord_get_SpeedDialEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_Blocked_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fBlocked);


void __RPC_STUB IVoIPCallerInfoRecord_put_Blocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_Blocked_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfBlocked);


void __RPC_STUB IVoIPCallerInfoRecord_get_Blocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_ForwardingURI_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrForwardingURI);


void __RPC_STUB IVoIPCallerInfoRecord_put_ForwardingURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_ForwardingURI_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrForwardingURI);


void __RPC_STUB IVoIPCallerInfoRecord_get_ForwardingURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_put_RingTone_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [in] */ BSTR bstrRingTonePath);


void __RPC_STUB IVoIPCallerInfoRecord_put_RingTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_get_RingTone_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRingTonePath);


void __RPC_STUB IVoIPCallerInfoRecord_get_RingTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_Commit_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This);


void __RPC_STUB IVoIPCallerInfoRecord_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoRecord_DeleteFromDB_Proxy( 
    IVoIPCallerInfoRecord __RPC_FAR * This);


void __RPC_STUB IVoIPCallerInfoRecord_DeleteFromDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCallerInfoRecord_INTERFACE_DEFINED__ */


#ifndef __IVoIPCallerInfoDB_INTERFACE_DEFINED__
#define __IVoIPCallerInfoDB_INTERFACE_DEFINED__

/* interface IVoIPCallerInfoDB */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCallerInfoDB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D954B73A-8022-410C-B78F-90E49919C4AE")
    IVoIPCallerInfoDB : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BSTR bstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateRecord( 
            /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Enumerator( 
            /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindCallerInfoByURI( 
            /* [in] */ BSTR bstrURI,
            /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindCallerInfoBySpeedDialEntry( 
            /* [in] */ INT idxSpeedDial,
            /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_SpeedDialEnumerator( 
            /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_FriendlyNameEnumerator( 
            /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCallerInfoDBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCallerInfoDB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCallerInfoDB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [in] */ BSTR bstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateRecord )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enumerator )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindCallerInfoByURI )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [in] */ BSTR bstrURI,
            /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindCallerInfoBySpeedDialEntry )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [in] */ INT idxSpeedDial,
            /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeedDialEnumerator )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FriendlyNameEnumerator )( 
            IVoIPCallerInfoDB __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);
        
        END_INTERFACE
    } IVoIPCallerInfoDBVtbl;

    interface IVoIPCallerInfoDB
    {
        CONST_VTBL struct IVoIPCallerInfoDBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCallerInfoDB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCallerInfoDB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCallerInfoDB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCallerInfoDB_Init(This,bstrURI)	\
    (This)->lpVtbl -> Init(This,bstrURI)

#define IVoIPCallerInfoDB_CreateRecord(This,ppiRecord)	\
    (This)->lpVtbl -> CreateRecord(This,ppiRecord)

#define IVoIPCallerInfoDB_get_Enumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_Enumerator(This,ppiEnum)

#define IVoIPCallerInfoDB_FindCallerInfoByURI(This,bstrURI,ppiRecord)	\
    (This)->lpVtbl -> FindCallerInfoByURI(This,bstrURI,ppiRecord)

#define IVoIPCallerInfoDB_FindCallerInfoBySpeedDialEntry(This,idxSpeedDial,ppiRecord)	\
    (This)->lpVtbl -> FindCallerInfoBySpeedDialEntry(This,idxSpeedDial,ppiRecord)

#define IVoIPCallerInfoDB_get_SpeedDialEnumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_SpeedDialEnumerator(This,ppiEnum)

#define IVoIPCallerInfoDB_get_FriendlyNameEnumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_FriendlyNameEnumerator(This,ppiEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_Init_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [in] */ BSTR bstrURI);


void __RPC_STUB IVoIPCallerInfoDB_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_CreateRecord_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord);


void __RPC_STUB IVoIPCallerInfoDB_CreateRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_get_Enumerator_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPCallerInfoDB_get_Enumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_FindCallerInfoByURI_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [in] */ BSTR bstrURI,
    /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord);


void __RPC_STUB IVoIPCallerInfoDB_FindCallerInfoByURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_FindCallerInfoBySpeedDialEntry_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [in] */ INT idxSpeedDial,
    /* [retval][out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *ppiRecord);


void __RPC_STUB IVoIPCallerInfoDB_FindCallerInfoBySpeedDialEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_get_SpeedDialEnumerator_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPCallerInfoDB_get_SpeedDialEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDB_get_FriendlyNameEnumerator_Proxy( 
    IVoIPCallerInfoDB __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallerInfoDBEnum __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPCallerInfoDB_get_FriendlyNameEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCallerInfoDB_INTERFACE_DEFINED__ */


#ifndef __IVoIPCallerInfoDBEnum_INTERFACE_DEFINED__
#define __IVoIPCallerInfoDBEnum_INTERFACE_DEFINED__

/* interface IVoIPCallerInfoDBEnum */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCallerInfoDBEnum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11928FC4-FE62-4412-8CAF-1EC68994FDCB")
    IVoIPCallerInfoDBEnum : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ unsigned long celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ unsigned long celt,
            /* [out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *rgVoIPCallerInfoRecord,
            /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCallerInfoDBEnumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCallerInfoDBEnum __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCallerInfoDBEnum __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCallerInfoDBEnum __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IVoIPCallerInfoDBEnum __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IVoIPCallerInfoDBEnum __RPC_FAR * This,
            /* [in] */ unsigned long celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IVoIPCallerInfoDBEnum __RPC_FAR * This,
            /* [in] */ unsigned long celt,
            /* [out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *rgVoIPCallerInfoRecord,
            /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched);
        
        END_INTERFACE
    } IVoIPCallerInfoDBEnumVtbl;

    interface IVoIPCallerInfoDBEnum
    {
        CONST_VTBL struct IVoIPCallerInfoDBEnumVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCallerInfoDBEnum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCallerInfoDBEnum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCallerInfoDBEnum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCallerInfoDBEnum_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IVoIPCallerInfoDBEnum_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IVoIPCallerInfoDBEnum_Next(This,celt,rgVoIPCallerInfoRecord,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgVoIPCallerInfoRecord,pceltFetched)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDBEnum_Reset_Proxy( 
    IVoIPCallerInfoDBEnum __RPC_FAR * This);


void __RPC_STUB IVoIPCallerInfoDBEnum_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDBEnum_Skip_Proxy( 
    IVoIPCallerInfoDBEnum __RPC_FAR * This,
    /* [in] */ unsigned long celt);


void __RPC_STUB IVoIPCallerInfoDBEnum_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCallerInfoDBEnum_Next_Proxy( 
    IVoIPCallerInfoDBEnum __RPC_FAR * This,
    /* [in] */ unsigned long celt,
    /* [out] */ IVoIPCallerInfoRecord __RPC_FAR *__RPC_FAR *rgVoIPCallerInfoRecord,
    /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched);


void __RPC_STUB IVoIPCallerInfoDBEnum_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCallerInfoDBEnum_INTERFACE_DEFINED__ */



#ifndef __VOIPLib_LIBRARY_DEFINED__
#define __VOIPLib_LIBRARY_DEFINED__

/* library VOIPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VOIPLib;

EXTERN_C const CLSID CLSID_VoIPCallLogRecord;

#ifdef __cplusplus

class DECLSPEC_UUID("822E2EB8-3544-491D-8355-FB4941C55DE6")
VoIPCallLogRecord;
#endif

EXTERN_C const CLSID CLSID_VoIPCallLogDB;

#ifdef __cplusplus

class DECLSPEC_UUID("6362637C-D330-4621-8A98-1BACEE1E8065")
VoIPCallLogDB;
#endif

EXTERN_C const CLSID CLSID_VoIPCallerInfoDB;

#ifdef __cplusplus

class DECLSPEC_UUID("8555B292-2CD4-41A8-AFD7-0A3D74E6E2F5")
VoIPCallerInfoDB;
#endif
#endif /* __VOIPLib_LIBRARY_DEFINED__ */

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


