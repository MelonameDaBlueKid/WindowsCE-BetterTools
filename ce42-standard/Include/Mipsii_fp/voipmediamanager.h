
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Thu Mar 13 23:49:50 2003
 */
/* Compiler settings for .\voipmediamanager.idl:
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

#ifndef __voipmediamanager_h__
#define __voipmediamanager_h__

/* Forward Declarations */ 

#ifndef __IVoIPMediaMgr_FWD_DEFINED__
#define __IVoIPMediaMgr_FWD_DEFINED__
typedef interface IVoIPMediaMgr IVoIPMediaMgr;
#endif 	/* __IVoIPMediaMgr_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "rtccore.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_voipmediamanager_0000 */
/* [local] */ 

typedef 
enum VoIPProgressTone
    {	e_vptInvalid	= 0,
	e_vptDial	= e_vptInvalid + 1,
	e_vptStutter	= e_vptDial + 1,
	e_vptOffHookWarning	= e_vptStutter + 1,
	e_vptConfirmation	= e_vptOffHookWarning + 1,
	e_vptMessageWaiting	= e_vptConfirmation + 1,
	e_vptRingback	= e_vptMessageWaiting + 1,
	e_vptCallWaiting	= e_vptRingback + 1,
	e_vptReorder	= e_vptCallWaiting + 1,
	e_vptCongestion	= e_vptReorder + 1,
	e_vptClientBusy	= e_vptCongestion + 1,
	e_vptNetworkBusy	= e_vptClientBusy + 1
    }	VoIPProgressTone;



extern RPC_IF_HANDLE __MIDL_itf_voipmediamanager_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_voipmediamanager_0000_v0_0_s_ifspec;

#ifndef __IVoIPMediaMgr_INTERFACE_DEFINED__
#define __IVoIPMediaMgr_INTERFACE_DEFINED__

/* interface IVoIPMediaMgr */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPMediaMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF6605B3-ECE0-40a5-94D3-2EDF3983C6EA")
    IVoIPMediaMgr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeRTCClient( 
            /* [in] */ IRTCClient2 __RPC_FAR *piClient) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreatePCToPCSession( 
            /* [in] */ IRTCClient2 __RPC_FAR *piClient,
            /* [in] */ IRTCProfile __RPC_FAR *piProfile,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppiSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AnswerSession( 
            /* [in] */ IRTCSession2 __RPC_FAR *piSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HoldSession( 
            /* [in] */ IRTCSession2 __RPC_FAR *piSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnholdSession( 
            /* [in] */ IRTCSession2 __RPC_FAR *piSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendDTMF( 
            /* [in] */ RTC_DTMF dtmf) = 0;
        
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
        
        virtual HRESULT STDMETHODCALLTYPE PlaySound( 
            /* [in] */ BSTR bstrFilePath,
            /* [in] */ INT_PTR hCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopSound( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayProgressTone( 
            /* [in] */ VoIPProgressTone vpt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopProgressTone( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnReinviteEvent( 
            /* [in] */ IRTCReInviteEvent __RPC_FAR *piReinviteEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnSessionStateChangeEvent( 
            /* [in] */ IRTCSessionStateChangeEvent __RPC_FAR *piSSCEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EvaluateSessionDescription( 
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *pfApplicationSession) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPMediaMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPMediaMgr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPMediaMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVoIPMediaMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitializeRTCClient )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCClient2 __RPC_FAR *piClient);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreatePCToPCSession )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCClient2 __RPC_FAR *piClient,
            /* [in] */ IRTCProfile __RPC_FAR *piProfile,
            /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppiSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AnswerSession )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCSession2 __RPC_FAR *piSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HoldSession )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCSession2 __RPC_FAR *piSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnholdSession )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCSession2 __RPC_FAR *piSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDTMF )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ RTC_DTMF dtmf);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeakerVolume )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeakerVolume )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ float fpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MicrophoneVolume )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MicrophoneVolume )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ float fpVolume);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeakerMute )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeakerMute )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MicrophoneMute )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MicrophoneMute )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fMuted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlaySound )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ BSTR bstrFilePath,
            /* [in] */ INT_PTR hCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopSound )( 
            IVoIPMediaMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayProgressTone )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ VoIPProgressTone vpt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopProgressTone )( 
            IVoIPMediaMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnReinviteEvent )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCReInviteEvent __RPC_FAR *piReinviteEvent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnSessionStateChangeEvent )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ IRTCSessionStateChangeEvent __RPC_FAR *piSSCEvent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EvaluateSessionDescription )( 
            IVoIPMediaMgr __RPC_FAR * This,
            /* [in] */ BSTR bstrContentType,
            /* [in] */ BSTR bstrSessionDescription,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *pfApplicationSession);
        
        END_INTERFACE
    } IVoIPMediaMgrVtbl;

    interface IVoIPMediaMgr
    {
        CONST_VTBL struct IVoIPMediaMgrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPMediaMgr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPMediaMgr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPMediaMgr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPMediaMgr_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IVoIPMediaMgr_InitializeRTCClient(This,piClient)	\
    (This)->lpVtbl -> InitializeRTCClient(This,piClient)

#define IVoIPMediaMgr_CreatePCToPCSession(This,piClient,piProfile,ppiSession)	\
    (This)->lpVtbl -> CreatePCToPCSession(This,piClient,piProfile,ppiSession)

#define IVoIPMediaMgr_AnswerSession(This,piSession)	\
    (This)->lpVtbl -> AnswerSession(This,piSession)

#define IVoIPMediaMgr_HoldSession(This,piSession)	\
    (This)->lpVtbl -> HoldSession(This,piSession)

#define IVoIPMediaMgr_UnholdSession(This,piSession)	\
    (This)->lpVtbl -> UnholdSession(This,piSession)

#define IVoIPMediaMgr_SendDTMF(This,dtmf)	\
    (This)->lpVtbl -> SendDTMF(This,dtmf)

#define IVoIPMediaMgr_get_SpeakerVolume(This,pfpVolume)	\
    (This)->lpVtbl -> get_SpeakerVolume(This,pfpVolume)

#define IVoIPMediaMgr_put_SpeakerVolume(This,fpVolume)	\
    (This)->lpVtbl -> put_SpeakerVolume(This,fpVolume)

#define IVoIPMediaMgr_get_MicrophoneVolume(This,pfpVolume)	\
    (This)->lpVtbl -> get_MicrophoneVolume(This,pfpVolume)

#define IVoIPMediaMgr_put_MicrophoneVolume(This,fpVolume)	\
    (This)->lpVtbl -> put_MicrophoneVolume(This,fpVolume)

#define IVoIPMediaMgr_get_SpeakerMute(This,pfMuted)	\
    (This)->lpVtbl -> get_SpeakerMute(This,pfMuted)

#define IVoIPMediaMgr_put_SpeakerMute(This,fMuted)	\
    (This)->lpVtbl -> put_SpeakerMute(This,fMuted)

#define IVoIPMediaMgr_get_MicrophoneMute(This,pfMuted)	\
    (This)->lpVtbl -> get_MicrophoneMute(This,pfMuted)

#define IVoIPMediaMgr_put_MicrophoneMute(This,fMuted)	\
    (This)->lpVtbl -> put_MicrophoneMute(This,fMuted)

#define IVoIPMediaMgr_PlaySound(This,bstrFilePath,hCallback)	\
    (This)->lpVtbl -> PlaySound(This,bstrFilePath,hCallback)

#define IVoIPMediaMgr_StopSound(This)	\
    (This)->lpVtbl -> StopSound(This)

#define IVoIPMediaMgr_PlayProgressTone(This,vpt)	\
    (This)->lpVtbl -> PlayProgressTone(This,vpt)

#define IVoIPMediaMgr_StopProgressTone(This)	\
    (This)->lpVtbl -> StopProgressTone(This)

#define IVoIPMediaMgr_OnReinviteEvent(This,piReinviteEvent)	\
    (This)->lpVtbl -> OnReinviteEvent(This,piReinviteEvent)

#define IVoIPMediaMgr_OnSessionStateChangeEvent(This,piSSCEvent)	\
    (This)->lpVtbl -> OnSessionStateChangeEvent(This,piSSCEvent)

#define IVoIPMediaMgr_EvaluateSessionDescription(This,bstrContentType,bstrSessionDescription,pfApplicationSession)	\
    (This)->lpVtbl -> EvaluateSessionDescription(This,bstrContentType,bstrSessionDescription,pfApplicationSession)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_Initialize_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This);


void __RPC_STUB IVoIPMediaMgr_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_InitializeRTCClient_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCClient2 __RPC_FAR *piClient);


void __RPC_STUB IVoIPMediaMgr_InitializeRTCClient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_CreatePCToPCSession_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCClient2 __RPC_FAR *piClient,
    /* [in] */ IRTCProfile __RPC_FAR *piProfile,
    /* [retval][out] */ IRTCSession2 __RPC_FAR *__RPC_FAR *ppiSession);


void __RPC_STUB IVoIPMediaMgr_CreatePCToPCSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_AnswerSession_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCSession2 __RPC_FAR *piSession);


void __RPC_STUB IVoIPMediaMgr_AnswerSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_HoldSession_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCSession2 __RPC_FAR *piSession);


void __RPC_STUB IVoIPMediaMgr_HoldSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_UnholdSession_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCSession2 __RPC_FAR *piSession);


void __RPC_STUB IVoIPMediaMgr_UnholdSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_SendDTMF_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ RTC_DTMF dtmf);


void __RPC_STUB IVoIPMediaMgr_SendDTMF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_get_SpeakerVolume_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfpVolume);


void __RPC_STUB IVoIPMediaMgr_get_SpeakerVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_put_SpeakerVolume_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ float fpVolume);


void __RPC_STUB IVoIPMediaMgr_put_SpeakerVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_get_MicrophoneVolume_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfpVolume);


void __RPC_STUB IVoIPMediaMgr_get_MicrophoneVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_put_MicrophoneVolume_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ float fpVolume);


void __RPC_STUB IVoIPMediaMgr_put_MicrophoneVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_get_SpeakerMute_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);


void __RPC_STUB IVoIPMediaMgr_get_SpeakerMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_put_SpeakerMute_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fMuted);


void __RPC_STUB IVoIPMediaMgr_put_SpeakerMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_get_MicrophoneMute_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfMuted);


void __RPC_STUB IVoIPMediaMgr_get_MicrophoneMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_put_MicrophoneMute_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fMuted);


void __RPC_STUB IVoIPMediaMgr_put_MicrophoneMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_PlaySound_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ BSTR bstrFilePath,
    /* [in] */ INT_PTR hCallback);


void __RPC_STUB IVoIPMediaMgr_PlaySound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_StopSound_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This);


void __RPC_STUB IVoIPMediaMgr_StopSound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_PlayProgressTone_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ VoIPProgressTone vpt);


void __RPC_STUB IVoIPMediaMgr_PlayProgressTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_StopProgressTone_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This);


void __RPC_STUB IVoIPMediaMgr_StopProgressTone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_OnReinviteEvent_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCReInviteEvent __RPC_FAR *piReinviteEvent);


void __RPC_STUB IVoIPMediaMgr_OnReinviteEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_OnSessionStateChangeEvent_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ IRTCSessionStateChangeEvent __RPC_FAR *piSSCEvent);


void __RPC_STUB IVoIPMediaMgr_OnSessionStateChangeEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPMediaMgr_EvaluateSessionDescription_Proxy( 
    IVoIPMediaMgr __RPC_FAR * This,
    /* [in] */ BSTR bstrContentType,
    /* [in] */ BSTR bstrSessionDescription,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *pfApplicationSession);


void __RPC_STUB IVoIPMediaMgr_EvaluateSessionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPMediaMgr_INTERFACE_DEFINED__ */


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


