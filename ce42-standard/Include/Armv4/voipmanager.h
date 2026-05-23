
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Thu Mar 13 23:49:48 2003
 */
/* Compiler settings for .\voipmanager.idl:
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

#ifndef __voipmanager_h__
#define __voipmanager_h__

/* Forward Declarations */ 

#ifndef __IVoIPMgr_FWD_DEFINED__
#define __IVoIPMgr_FWD_DEFINED__
typedef interface IVoIPMgr IVoIPMgr;
#endif 	/* __IVoIPMgr_FWD_DEFINED__ */


#ifndef __IVoIPCurrentCall_FWD_DEFINED__
#define __IVoIPCurrentCall_FWD_DEFINED__
typedef interface IVoIPCurrentCall IVoIPCurrentCall;
#endif 	/* __IVoIPCurrentCall_FWD_DEFINED__ */


#ifndef __IVoIPCurrentCallEnumerator_FWD_DEFINED__
#define __IVoIPCurrentCallEnumerator_FWD_DEFINED__
typedef interface IVoIPCurrentCallEnumerator IVoIPCurrentCallEnumerator;
#endif 	/* __IVoIPCurrentCallEnumerator_FWD_DEFINED__ */


#ifndef __IVoIPUI_FWD_DEFINED__
#define __IVoIPUI_FWD_DEFINED__
typedef interface IVoIPUI IVoIPUI;
#endif 	/* __IVoIPUI_FWD_DEFINED__ */


#ifndef __VoIPMgr_FWD_DEFINED__
#define __VoIPMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoIPMgr VoIPMgr;
#else
typedef struct VoIPMgr VoIPMgr;
#endif /* __cplusplus */

#endif 	/* __VoIPMgr_FWD_DEFINED__ */


/* header files for imported files */
#include "voiperrorcodes.h"
#include "rtccore.h"
#include "voipstore.h"
#include "voipmediamanager.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_voipmanager_0000 */
/* [local] */ 



typedef struct DirectoryClientRegParams
    {
    DWORD dwFlags;
    DWORD dwMask;
    BSTR bstrUserName;
    BSTR bstrPassword;
    BOOL fIsPasswordSet;
    BSTR bstrExtraXML;
    BSTR bstrDomain;
    }	DirectoryClientRegParams;

#define	DCRP_VALID_USERNAME	( 0x1 )

#define	DCRP_VALID_PASSWORD	( 0x2 )

#define	DCRP_VALID_XML	( 0x4 )

#define	DCRP_VALID_DOMAIN	( 0x8 )

#define	DCRP_VALID_ALL	( DCRP_VALID_USERNAME | DCRP_VALID_PASSWORD | DCRP_VALID_XML | DCRP_VALID_DOMAIN )

typedef struct VoIPMgrParameters
    {
    DirectoryClientRegParams DCRegParams;
    BSTR bstrSipPassword;
    }	VoIPMgrParameters;

typedef 
enum VoIPCallStatus
    {	e_vcsInvalid	= 0,
	e_vcsIdle	= RTCSS_IDLE,
	e_vcsIncoming	= RTCSS_INCOMING,
	e_vcsAnswering	= RTCSS_ANSWERING,
	e_vcsInProgress	= RTCSS_INPROGRESS,
	e_vcsConnected	= RTCSS_CONNECTED,
	e_vcsDisconnected	= RTCSS_DISCONNECTED,
	e_vcsHolding	= RTCSS_HOLD,
	e_vcsReferring	= RTCSS_REFER
    }	VoIPCallStatus;

#define	VCS_FIRST	( e_vcsInvalid )

#define	VCS_LAST	( e_vcsHolding )

typedef ULONG VoIPManagerState;

#define	VMS_NOT_READY	( 0 )

#define	VMS_INITIALIZED	( 0x1 )

#define	VMS_REGISTERED	( 0x2 )

#define	VMS_SHUTTING_DOWN	( 0x4 )

#define	VMS_CALL_LOG_DB_READY	( 0x8 )

#define	VMS_CALLER_INFO_DB_READY	( 0x10 )

#define	VMS_AUTOFORWARDING	( 0x20 )

#define	VMS_DBS_READY	( VMS_CALL_LOG_DB_READY | VMS_CALLER_INFO_DB_READY )

#define	VMS_REREGISTERING	( 0x40 )




extern RPC_IF_HANDLE __MIDL_itf_voipmanager_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_voipmanager_0000_v0_0_s_ifspec;

#ifndef __IVoIPMgr_INTERFACE_DEFINED__
#define __IVoIPMgr_INTERFACE_DEFINED__

/* interface IVoIPMgr */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BEBB5090-4E76-4664-9281-D218B005D65B")
    IVoIPMgr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IVoIPUI __RPC_FAR *piUI,
            /* [in] */ VoIPMgrParameters __RPC_FAR *pvmpMgrParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Uninitialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Call( 
            /* [in] */ BSTR bstrURI,
            /* [retval][out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *ppiCurrentCall) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reregister( 
            /* [in] */ VoIPMgrParameters __RPC_FAR *pvmpMgrParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CallLogDB( 
            /* [retval][out] */ IVoIPCallLogDB __RPC_FAR *__RPC_FAR *piCallLogDB) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CallerInfoDB( 
            /* [retval][out] */ IVoIPCallerInfoDB __RPC_FAR *__RPC_FAR *ppiCallerInfoDB) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_RTCClient( 
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppiRTCClient) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendDTMF( 
            /* [in] */ RTC_DTMF rtcdtmf) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CurrentCallEnumerator( 
            /* [retval][out] */ IVoIPCurrentCallEnumerator __RPC_FAR *__RPC_FAR *ppiEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_SpeakerVolume( 
            /* [retval][out] */ float __RPC_FAR *pfpVolume) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_SpeakerVolume( 
            /* [in] */ float fpVolume) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MicrophoneVolume( 
            /* [retval][out] */ float __RPC_FAR *pfpVolume) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_MicrophoneVolume( 
            /* [in] */ float fpVolume) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_SpeakerMute( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_SpeakerMute( 
            /* [in] */ VARIANT_BOOL fMuted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MicrophoneMute( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_MicrophoneMute( 
            /* [in] */ VARIANT_BOOL fMuted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_RingTone( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRingTone) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_RingTone( 
            /* [in] */ BSTR bstrRingTone) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_ActiveCurrentCall( 
            /* [retval][out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *ppiCall) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_MissedCallTimeout( 
            /* [in] */ UINT nTimeoutMilliseconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MissedCallTimeout( 
            /* [retval][out] */ UINT __RPC_FAR *pnTimeoutMilliseconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MyURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MyServer( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrServer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Parameters( 
            /* [retval][out] */ VoIPMgrParameters __RPC_FAR *pvmpUsed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ VoIPManagerState __RPC_FAR *pulState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_AutoForwardURI( 
            /* [in] */ BSTR bstrAutoForward) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_AutoForwardURI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAutoForward) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayProgressTone( 
            /* [in] */ VoIPProgressTone vpt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopProgressTone( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPMgr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ IVoIPUI __RPC_FAR *piUI,
            /* [in] */ VoIPMgrParameters __RPC_FAR *pvmpMgrParams);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialize )( 
            IVoIPMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Call )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ BSTR bstrURI,
            /* [retval][out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *ppiCurrentCall);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reregister )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ VoIPMgrParameters __RPC_FAR *pvmpMgrParams);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallLogDB )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallLogDB __RPC_FAR *__RPC_FAR *piCallLogDB);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallerInfoDB )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ IVoIPCallerInfoDB __RPC_FAR *__RPC_FAR *ppiCallerInfoDB);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RTCClient )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppiRTCClient);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDTMF )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ RTC_DTMF rtcdtmf);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCallEnumerator )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ IVoIPCurrentCallEnumerator __RPC_FAR *__RPC_FAR *ppiEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeakerVolume )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeakerVolume )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ float fpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MicrophoneVolume )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MicrophoneVolume )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ float fpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeakerMute )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeakerMute )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MicrophoneMute )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MicrophoneMute )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RingTone )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRingTone);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RingTone )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ BSTR bstrRingTone);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActiveCurrentCall )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *ppiCall);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MissedCallTimeout )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ UINT nTimeoutMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MissedCallTimeout )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ UINT __RPC_FAR *pnTimeoutMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyURI )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyServer )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrServer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parameters )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ VoIPMgrParameters __RPC_FAR *pvmpUsed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ VoIPManagerState __RPC_FAR *pulState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoForwardURI )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ BSTR bstrAutoForward);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoForwardURI )( 
            IVoIPMgr __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAutoForward);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayProgressTone )( 
            IVoIPMgr __RPC_FAR * This,
            /* [in] */ VoIPProgressTone vpt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopProgressTone )( 
            IVoIPMgr __RPC_FAR * This);
        
        END_INTERFACE
    } IVoIPMgrVtbl;

    interface IVoIPMgr
    {
        CONST_VTBL struct IVoIPMgrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPMgr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPMgr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPMgr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPMgr_Initialize(This,piUI,pvmpMgrParams)	\
    (This)->lpVtbl -> Initialize(This,piUI,pvmpMgrParams)

#define IVoIPMgr_Uninitialize(This)	\
    (This)->lpVtbl -> Uninitialize(This)

#define IVoIPMgr_Call(This,bstrURI,ppiCurrentCall)	\
    (This)->lpVtbl -> Call(This,bstrURI,ppiCurrentCall)

#define IVoIPMgr_Reregister(This,pvmpMgrParams)	\
    (This)->lpVtbl -> Reregister(This,pvmpMgrParams)

#define IVoIPMgr_get_CallLogDB(This,piCallLogDB)	\
    (This)->lpVtbl -> get_CallLogDB(This,piCallLogDB)

#define IVoIPMgr_get_CallerInfoDB(This,ppiCallerInfoDB)	\
    (This)->lpVtbl -> get_CallerInfoDB(This,ppiCallerInfoDB)

#define IVoIPMgr_get_RTCClient(This,ppiRTCClient)	\
    (This)->lpVtbl -> get_RTCClient(This,ppiRTCClient)

#define IVoIPMgr_SendDTMF(This,rtcdtmf)	\
    (This)->lpVtbl -> SendDTMF(This,rtcdtmf)

#define IVoIPMgr_get_CurrentCallEnumerator(This,ppiEnum)	\
    (This)->lpVtbl -> get_CurrentCallEnumerator(This,ppiEnum)

#define IVoIPMgr_get_SpeakerVolume(This,pfpVolume)	\
    (This)->lpVtbl -> get_SpeakerVolume(This,pfpVolume)

#define IVoIPMgr_put_SpeakerVolume(This,fpVolume)	\
    (This)->lpVtbl -> put_SpeakerVolume(This,fpVolume)

#define IVoIPMgr_get_MicrophoneVolume(This,pfpVolume)	\
    (This)->lpVtbl -> get_MicrophoneVolume(This,pfpVolume)

#define IVoIPMgr_put_MicrophoneVolume(This,fpVolume)	\
    (This)->lpVtbl -> put_MicrophoneVolume(This,fpVolume)

#define IVoIPMgr_get_SpeakerMute(This,pfMuted)	\
    (This)->lpVtbl -> get_SpeakerMute(This,pfMuted)

#define IVoIPMgr_put_SpeakerMute(This,fMuted)	\
    (This)->lpVtbl -> put_SpeakerMute(This,fMuted)

#define IVoIPMgr_get_MicrophoneMute(This,pfMuted)	\
    (This)->lpVtbl -> get_MicrophoneMute(This,pfMuted)

#define IVoIPMgr_put_MicrophoneMute(This,fMuted)	\
    (This)->lpVtbl -> put_MicrophoneMute(This,fMuted)

#define IVoIPMgr_get_RingTone(This,pbstrRingTone)	\
    (This)->lpVtbl -> get_RingTone(This,pbstrRingTone)

#define IVoIPMgr_put_RingTone(This,bstrRingTone)	\
    (This)->lpVtbl -> put_RingTone(This,bstrRingTone)

#define IVoIPMgr_get_ActiveCurrentCall(This,ppiCall)	\
    (This)->lpVtbl -> get_ActiveCurrentCall(This,ppiCall)

#define IVoIPMgr_put_MissedCallTimeout(This,nTimeoutMilliseconds)	\
    (This)->lpVtbl -> put_MissedCallTimeout(This,nTimeoutMilliseconds)

#define IVoIPMgr_get_MissedCallTimeout(This,pnTimeoutMilliseconds)	\
    (This)->lpVtbl -> get_MissedCallTimeout(This,pnTimeoutMilliseconds)

#define IVoIPMgr_get_MyURI(This,pbstrURI)	\
    (This)->lpVtbl -> get_MyURI(This,pbstrURI)

#define IVoIPMgr_get_MyServer(This,pbstrServer)	\
    (This)->lpVtbl -> get_MyServer(This,pbstrServer)

#define IVoIPMgr_get_Parameters(This,pvmpUsed)	\
    (This)->lpVtbl -> get_Parameters(This,pvmpUsed)

#define IVoIPMgr_get_State(This,pulState)	\
    (This)->lpVtbl -> get_State(This,pulState)

#define IVoIPMgr_put_AutoForwardURI(This,bstrAutoForward)	\
    (This)->lpVtbl -> put_AutoForwardURI(This,bstrAutoForward)

#define IVoIPMgr_get_AutoForwardURI(This,pbstrAutoForward)	\
    (This)->lpVtbl -> get_AutoForwardURI(This,pbstrAutoForward)

#define IVoIPMgr_PlayProgressTone(This,vpt)	\
    (This)->lpVtbl -> PlayProgressTone(This,vpt)

#define IVoIPMgr_StopProgressTone(This)	\
    (This)->lpVtbl -> StopProgressTone(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPMgr_Initialize_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ IVoIPUI __RPC_FAR *piUI,
    /* [in] */ VoIPMgrParameters __RPC_FAR *pvmpMgrParams);


void __RPC_STUB IVoIPMgr_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_Uninitialize_Proxy( 
    IVoIPMgr __RPC_FAR * This);


void __RPC_STUB IVoIPMgr_Uninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_Call_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ BSTR bstrURI,
    /* [retval][out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *ppiCurrentCall);


void __RPC_STUB IVoIPMgr_Call_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_Reregister_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ VoIPMgrParameters __RPC_FAR *pvmpMgrParams);


void __RPC_STUB IVoIPMgr_Reregister_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_CallLogDB_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallLogDB __RPC_FAR *__RPC_FAR *piCallLogDB);


void __RPC_STUB IVoIPMgr_get_CallLogDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_CallerInfoDB_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ IVoIPCallerInfoDB __RPC_FAR *__RPC_FAR *ppiCallerInfoDB);


void __RPC_STUB IVoIPMgr_get_CallerInfoDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_RTCClient_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ IRTCClient __RPC_FAR *__RPC_FAR *ppiRTCClient);


void __RPC_STUB IVoIPMgr_get_RTCClient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_SendDTMF_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ RTC_DTMF rtcdtmf);


void __RPC_STUB IVoIPMgr_SendDTMF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_CurrentCallEnumerator_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ IVoIPCurrentCallEnumerator __RPC_FAR *__RPC_FAR *ppiEnum);


void __RPC_STUB IVoIPMgr_get_CurrentCallEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_SpeakerVolume_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfpVolume);


void __RPC_STUB IVoIPMgr_get_SpeakerVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_SpeakerVolume_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ float fpVolume);


void __RPC_STUB IVoIPMgr_put_SpeakerVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_MicrophoneVolume_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfpVolume);


void __RPC_STUB IVoIPMgr_get_MicrophoneVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_MicrophoneVolume_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ float fpVolume);


void __RPC_STUB IVoIPMgr_put_MicrophoneVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_SpeakerMute_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);


void __RPC_STUB IVoIPMgr_get_SpeakerMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_SpeakerMute_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fMuted);


void __RPC_STUB IVoIPMgr_put_SpeakerMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_MicrophoneMute_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);


void __RPC_STUB IVoIPMgr_get_MicrophoneMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_MicrophoneMute_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fMuted);


void __RPC_STUB IVoIPMgr_put_MicrophoneMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_RingTone_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRingTone);


void __RPC_STUB IVoIPMgr_get_RingTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_RingTone_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ BSTR bstrRingTone);


void __RPC_STUB IVoIPMgr_put_RingTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_ActiveCurrentCall_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *ppiCall);


void __RPC_STUB IVoIPMgr_get_ActiveCurrentCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_MissedCallTimeout_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ UINT nTimeoutMilliseconds);


void __RPC_STUB IVoIPMgr_put_MissedCallTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_MissedCallTimeout_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ UINT __RPC_FAR *pnTimeoutMilliseconds);


void __RPC_STUB IVoIPMgr_get_MissedCallTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_MyURI_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);


void __RPC_STUB IVoIPMgr_get_MyURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_MyServer_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrServer);


void __RPC_STUB IVoIPMgr_get_MyServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_Parameters_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ VoIPMgrParameters __RPC_FAR *pvmpUsed);


void __RPC_STUB IVoIPMgr_get_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_State_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ VoIPManagerState __RPC_FAR *pulState);


void __RPC_STUB IVoIPMgr_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_put_AutoForwardURI_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ BSTR bstrAutoForward);


void __RPC_STUB IVoIPMgr_put_AutoForwardURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_get_AutoForwardURI_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrAutoForward);


void __RPC_STUB IVoIPMgr_get_AutoForwardURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_PlayProgressTone_Proxy( 
    IVoIPMgr __RPC_FAR * This,
    /* [in] */ VoIPProgressTone vpt);


void __RPC_STUB IVoIPMgr_PlayProgressTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMgr_StopProgressTone_Proxy( 
    IVoIPMgr __RPC_FAR * This);


void __RPC_STUB IVoIPMgr_StopProgressTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPMgr_INTERFACE_DEFINED__ */


#ifndef __IVoIPCurrentCall_INTERFACE_DEFINED__
#define __IVoIPCurrentCall_INTERFACE_DEFINED__

/* interface IVoIPCurrentCall */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCurrentCall;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B975DFE-B516-437C-B1AB-322EFDA8DB6A")
    IVoIPCurrentCall : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_URI( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_FriendlyName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VoIPName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *pstStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *pstDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_RTCSession( 
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *piSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ VoIPCallType __RPC_FAR *pvctType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ VoIPCallStatus __RPC_FAR *pvcsStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_RTCParticipant( 
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *piparticipant) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NetworkStatus( 
            /* [retval][out] */ LONG __RPC_FAR *plReason) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Hold( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unhold( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Answer( 
            /* [in] */ BOOL fAccept) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Hangup( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Ignore( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Redirect( 
            /* [in] */ BSTR bstrRedirectURI) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCurrentCallVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCurrentCall __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCurrentCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URI )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FriendlyName )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VoIPName )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *pstStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ SYSTEMTIME __RPC_FAR *pstDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RTCSession )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *piSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ VoIPCallType __RPC_FAR *pvctType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ VoIPCallStatus __RPC_FAR *pvcsStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RTCParticipant )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *piparticipant);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkStatus )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plReason);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hold )( 
            IVoIPCurrentCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unhold )( 
            IVoIPCurrentCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Answer )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [in] */ BOOL fAccept);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hangup )( 
            IVoIPCurrentCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Ignore )( 
            IVoIPCurrentCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Redirect )( 
            IVoIPCurrentCall __RPC_FAR * This,
            /* [in] */ BSTR bstrRedirectURI);
        
        END_INTERFACE
    } IVoIPCurrentCallVtbl;

    interface IVoIPCurrentCall
    {
        CONST_VTBL struct IVoIPCurrentCallVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCurrentCall_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCurrentCall_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCurrentCall_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCurrentCall_get_URI(This,pbstrURI)	\
    (This)->lpVtbl -> get_URI(This,pbstrURI)

#define IVoIPCurrentCall_get_FriendlyName(This,pbstrFriendlyName)	\
    (This)->lpVtbl -> get_FriendlyName(This,pbstrFriendlyName)

#define IVoIPCurrentCall_get_VoIPName(This,pbstrVoIPName)	\
    (This)->lpVtbl -> get_VoIPName(This,pbstrVoIPName)

#define IVoIPCurrentCall_get_StartTime(This,pstStart)	\
    (This)->lpVtbl -> get_StartTime(This,pstStart)

#define IVoIPCurrentCall_get_Duration(This,pstDuration)	\
    (This)->lpVtbl -> get_Duration(This,pstDuration)

#define IVoIPCurrentCall_get_RTCSession(This,piSession)	\
    (This)->lpVtbl -> get_RTCSession(This,piSession)

#define IVoIPCurrentCall_get_Type(This,pvctType)	\
    (This)->lpVtbl -> get_Type(This,pvctType)

#define IVoIPCurrentCall_get_Status(This,pvcsStatus)	\
    (This)->lpVtbl -> get_Status(This,pvcsStatus)

#define IVoIPCurrentCall_get_RTCParticipant(This,piparticipant)	\
    (This)->lpVtbl -> get_RTCParticipant(This,piparticipant)

#define IVoIPCurrentCall_get_NetworkStatus(This,plReason)	\
    (This)->lpVtbl -> get_NetworkStatus(This,plReason)

#define IVoIPCurrentCall_Hold(This)	\
    (This)->lpVtbl -> Hold(This)

#define IVoIPCurrentCall_Unhold(This)	\
    (This)->lpVtbl -> Unhold(This)

#define IVoIPCurrentCall_Answer(This,fAccept)	\
    (This)->lpVtbl -> Answer(This,fAccept)

#define IVoIPCurrentCall_Hangup(This)	\
    (This)->lpVtbl -> Hangup(This)

#define IVoIPCurrentCall_Ignore(This)	\
    (This)->lpVtbl -> Ignore(This)

#define IVoIPCurrentCall_Redirect(This,bstrRedirectURI)	\
    (This)->lpVtbl -> Redirect(This,bstrRedirectURI)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_URI_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrURI);


void __RPC_STUB IVoIPCurrentCall_get_URI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_FriendlyName_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFriendlyName);


void __RPC_STUB IVoIPCurrentCall_get_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_VoIPName_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrVoIPName);


void __RPC_STUB IVoIPCurrentCall_get_VoIPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_StartTime_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ SYSTEMTIME __RPC_FAR *pstStart);


void __RPC_STUB IVoIPCurrentCall_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_Duration_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ SYSTEMTIME __RPC_FAR *pstDuration);


void __RPC_STUB IVoIPCurrentCall_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_RTCSession_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ IRTCSession __RPC_FAR *__RPC_FAR *piSession);


void __RPC_STUB IVoIPCurrentCall_get_RTCSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_Type_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ VoIPCallType __RPC_FAR *pvctType);


void __RPC_STUB IVoIPCurrentCall_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_Status_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ VoIPCallStatus __RPC_FAR *pvcsStatus);


void __RPC_STUB IVoIPCurrentCall_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_RTCParticipant_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ IRTCParticipant __RPC_FAR *__RPC_FAR *piparticipant);


void __RPC_STUB IVoIPCurrentCall_get_RTCParticipant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_get_NetworkStatus_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *plReason);


void __RPC_STUB IVoIPCurrentCall_get_NetworkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_Hold_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This);


void __RPC_STUB IVoIPCurrentCall_Hold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_Unhold_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This);


void __RPC_STUB IVoIPCurrentCall_Unhold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_Answer_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [in] */ BOOL fAccept);


void __RPC_STUB IVoIPCurrentCall_Answer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_Hangup_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This);


void __RPC_STUB IVoIPCurrentCall_Hangup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_Ignore_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This);


void __RPC_STUB IVoIPCurrentCall_Ignore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCall_Redirect_Proxy( 
    IVoIPCurrentCall __RPC_FAR * This,
    /* [in] */ BSTR bstrRedirectURI);


void __RPC_STUB IVoIPCurrentCall_Redirect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCurrentCall_INTERFACE_DEFINED__ */


#ifndef __IVoIPCurrentCallEnumerator_INTERFACE_DEFINED__
#define __IVoIPCurrentCallEnumerator_INTERFACE_DEFINED__

/* interface IVoIPCurrentCallEnumerator */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPCurrentCallEnumerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5915B8CD-DD70-4E0A-83DD-4A1099022B75")
    IVoIPCurrentCallEnumerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ unsigned long celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ unsigned long celt,
            /* [out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *rgCCP,
            /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPCurrentCallEnumeratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPCurrentCallEnumerator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPCurrentCallEnumerator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPCurrentCallEnumerator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IVoIPCurrentCallEnumerator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IVoIPCurrentCallEnumerator __RPC_FAR * This,
            /* [in] */ unsigned long celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IVoIPCurrentCallEnumerator __RPC_FAR * This,
            /* [in] */ unsigned long celt,
            /* [out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *rgCCP,
            /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched);
        
        END_INTERFACE
    } IVoIPCurrentCallEnumeratorVtbl;

    interface IVoIPCurrentCallEnumerator
    {
        CONST_VTBL struct IVoIPCurrentCallEnumeratorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPCurrentCallEnumerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPCurrentCallEnumerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPCurrentCallEnumerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPCurrentCallEnumerator_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IVoIPCurrentCallEnumerator_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IVoIPCurrentCallEnumerator_Next(This,celt,rgCCP,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgCCP,pceltFetched)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPCurrentCallEnumerator_Reset_Proxy( 
    IVoIPCurrentCallEnumerator __RPC_FAR * This);


void __RPC_STUB IVoIPCurrentCallEnumerator_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCallEnumerator_Skip_Proxy( 
    IVoIPCurrentCallEnumerator __RPC_FAR * This,
    /* [in] */ unsigned long celt);


void __RPC_STUB IVoIPCurrentCallEnumerator_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPCurrentCallEnumerator_Next_Proxy( 
    IVoIPCurrentCallEnumerator __RPC_FAR * This,
    /* [in] */ unsigned long celt,
    /* [out] */ IVoIPCurrentCall __RPC_FAR *__RPC_FAR *rgCCP,
    /* [retval][out] */ unsigned long __RPC_FAR *pceltFetched);


void __RPC_STUB IVoIPCurrentCallEnumerator_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPCurrentCallEnumerator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_voipmanager_0247 */
/* [local] */ 

typedef 
enum VoIPCallEvent
    {	e_vceInvalid	= 0,
	e_vceStatusChanged	= e_vceInvalid + 1,
	e_vceMissed	= e_vceStatusChanged + 1,
	e_vceAutoBlocked	= e_vceMissed + 1,
	e_vceAutoForwarded	= e_vceAutoBlocked + 1,
	e_vceDropped	= e_vceAutoForwarded + 1,
	e_vceRedirectSucceeded	= e_vceDropped + 1,
	e_vceRedirectFailed	= e_vceRedirectSucceeded + 1
    }	VoIPCallEvent;

typedef 
enum VoIPSystemEvent
    {	e_vseInvalid	= 0,
	e_vseTerminated	= e_vseInvalid + 1,
	e_vseRegistering	= e_vseTerminated + 1,
	e_vseRegistrationSucceeded	= e_vseRegistering + 1,
	e_vseRegistrationFailed	= e_vseRegistrationSucceeded + 1
    }	VoIPSystemEvent;



extern RPC_IF_HANDLE __MIDL_itf_voipmanager_0247_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_voipmanager_0247_v0_0_s_ifspec;

#ifndef __IVoIPUI_INTERFACE_DEFINED__
#define __IVoIPUI_INTERFACE_DEFINED__

/* interface IVoIPUI */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74D206B8-32AD-4BD8-B941-4A9E0522988E")
    IVoIPUI : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnCallEvent( 
            /* [in] */ VoIPCallEvent vceEvent,
            /* [in] */ IVoIPCurrentCall __RPC_FAR *piCurrentCall) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnSystemEvent( 
            /* [in] */ VoIPSystemEvent vseEvent,
            /* [in] */ INT_PTR iptrParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPUI __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPUI __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPUI __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCallEvent )( 
            IVoIPUI __RPC_FAR * This,
            /* [in] */ VoIPCallEvent vceEvent,
            /* [in] */ IVoIPCurrentCall __RPC_FAR *piCurrentCall);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnSystemEvent )( 
            IVoIPUI __RPC_FAR * This,
            /* [in] */ VoIPSystemEvent vseEvent,
            /* [in] */ INT_PTR iptrParam);
        
        END_INTERFACE
    } IVoIPUIVtbl;

    interface IVoIPUI
    {
        CONST_VTBL struct IVoIPUIVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPUI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPUI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPUI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPUI_OnCallEvent(This,vceEvent,piCurrentCall)	\
    (This)->lpVtbl -> OnCallEvent(This,vceEvent,piCurrentCall)

#define IVoIPUI_OnSystemEvent(This,vseEvent,iptrParam)	\
    (This)->lpVtbl -> OnSystemEvent(This,vseEvent,iptrParam)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPUI_OnCallEvent_Proxy( 
    IVoIPUI __RPC_FAR * This,
    /* [in] */ VoIPCallEvent vceEvent,
    /* [in] */ IVoIPCurrentCall __RPC_FAR *piCurrentCall);


void __RPC_STUB IVoIPUI_OnCallEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPUI_OnSystemEvent_Proxy( 
    IVoIPUI __RPC_FAR * This,
    /* [in] */ VoIPSystemEvent vseEvent,
    /* [in] */ INT_PTR iptrParam);


void __RPC_STUB IVoIPUI_OnSystemEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPUI_INTERFACE_DEFINED__ */



#ifndef __VOIPMANAGERLib_LIBRARY_DEFINED__
#define __VOIPMANAGERLib_LIBRARY_DEFINED__

/* library VOIPMANAGERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VOIPMANAGERLib;

EXTERN_C const CLSID CLSID_VoIPMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("254D6845-7CF1-4B90-A658-E4C430C3A7BE")
VoIPMgr;
#endif
#endif /* __VOIPMANAGERLib_LIBRARY_DEFINED__ */

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


