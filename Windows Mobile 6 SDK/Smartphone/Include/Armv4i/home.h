
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Fri Mar 09 19:15:59 2007
 */
/* Compiler settings for .\home.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __home_h__
#define __home_h__

/* Forward Declarations */ 

#ifndef __IHomePluginEnvironment_FWD_DEFINED__
#define __IHomePluginEnvironment_FWD_DEFINED__
typedef interface IHomePluginEnvironment IHomePluginEnvironment;
#endif 	/* __IHomePluginEnvironment_FWD_DEFINED__ */


#ifndef __IHomePluginEnvironment2_FWD_DEFINED__
#define __IHomePluginEnvironment2_FWD_DEFINED__
typedef interface IHomePluginEnvironment2 IHomePluginEnvironment2;
#endif 	/* __IHomePluginEnvironment2_FWD_DEFINED__ */


#ifndef __IHomePlugin_FWD_DEFINED__
#define __IHomePlugin_FWD_DEFINED__
typedef interface IHomePlugin IHomePlugin;
#endif 	/* __IHomePlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"
#include "oleidl.h"
#include "msxml2.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_home_0000 */
/* [local] */ 

typedef DWORD HPLUGIN;



extern RPC_IF_HANDLE __MIDL_itf_home_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_home_0000_v0_0_s_ifspec;

#ifndef __IHomePluginEnvironment_INTERFACE_DEFINED__
#define __IHomePluginEnvironment_INTERFACE_DEFINED__

/* interface IHomePluginEnvironment */
/* [object][uuid] */ 

#define	IPF_HEIGHT_CHANGED	( 0x1 )

#define	IPF_SELECTABILITY_CHANGED	( 0x2 )


EXTERN_C const IID IID_IHomePluginEnvironment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF328DC0-22F5-4ac1-A103-19B389C633FA")
    IHomePluginEnvironment : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InvalidatePlugin( 
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSingleShotTimer( 
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ UINT cMiliseconds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHomePluginEnvironmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHomePluginEnvironment __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHomePluginEnvironment __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHomePluginEnvironment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidatePlugin )( 
            IHomePluginEnvironment __RPC_FAR * This,
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSingleShotTimer )( 
            IHomePluginEnvironment __RPC_FAR * This,
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ UINT cMiliseconds);
        
        END_INTERFACE
    } IHomePluginEnvironmentVtbl;

    interface IHomePluginEnvironment
    {
        CONST_VTBL struct IHomePluginEnvironmentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHomePluginEnvironment_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHomePluginEnvironment_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHomePluginEnvironment_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHomePluginEnvironment_InvalidatePlugin(This,hPlugin,dwFlags)	\
    (This)->lpVtbl -> InvalidatePlugin(This,hPlugin,dwFlags)

#define IHomePluginEnvironment_SetSingleShotTimer(This,hPlugin,cMiliseconds)	\
    (This)->lpVtbl -> SetSingleShotTimer(This,hPlugin,cMiliseconds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHomePluginEnvironment_InvalidatePlugin_Proxy( 
    IHomePluginEnvironment __RPC_FAR * This,
    /* [in] */ HPLUGIN hPlugin,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IHomePluginEnvironment_InvalidatePlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHomePluginEnvironment_SetSingleShotTimer_Proxy( 
    IHomePluginEnvironment __RPC_FAR * This,
    /* [in] */ HPLUGIN hPlugin,
    /* [in] */ UINT cMiliseconds);


void __RPC_STUB IHomePluginEnvironment_SetSingleShotTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHomePluginEnvironment_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_home_0212 */
/* [local] */ 

typedef 
enum _PluginEventID
    {	PE_KEYDOWN	= 0,
	PE_ACTION	= PE_KEYDOWN + 1,
	PE_PAINT	= PE_ACTION + 1,
	PE_SYSCOLORCHANGE	= PE_PAINT + 1,
	PE_TIMER	= PE_SYSCOLORCHANGE + 1,
	PE_DATACHANGE	= PE_TIMER + 1,
	PE_SETTINGCHANGE	= PE_DATACHANGE + 1
    }	PluginEventID;

typedef struct _PEKeyDown
    {
    WORD wVKey;
    }	PEKeyDown;

typedef struct _PEPaint
    {
    HDC hdc;
    BOOL fSelected;
    RECT rcDraw;
    }	PEPaint;

typedef /* [switch_type] */ union _PluginEventParametersUnion
    {
    /* [case()] */ PEKeyDown key;
    /* [case()] */ PEPaint paint;
    /* [default] */  /* Empty union arm */ 
    }	PluginEventParametersUnion;

typedef struct _PluginEvent
    {
    PluginEventID idEvent;
    /* [switch_is] */ PluginEventParametersUnion p;
    }	PluginEvent;



extern RPC_IF_HANDLE __MIDL_itf_home_0212_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_home_0212_v0_0_s_ifspec;

#ifndef __IHomePluginEnvironment2_INTERFACE_DEFINED__
#define __IHomePluginEnvironment2_INTERFACE_DEFINED__

/* interface IHomePluginEnvironment2 */
/* [object][uuid] */ 


EXTERN_C const IID IID_IHomePluginEnvironment2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E01A8A84-DDEF-438e-9004-3FB2A908E465")
    IHomePluginEnvironment2 : public IHomePluginEnvironment
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetColor( 
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ BSTR bstrColorName,
            /* [out] */ COLORREF __RPC_FAR *pcr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHomePluginEnvironment2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHomePluginEnvironment2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHomePluginEnvironment2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHomePluginEnvironment2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidatePlugin )( 
            IHomePluginEnvironment2 __RPC_FAR * This,
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSingleShotTimer )( 
            IHomePluginEnvironment2 __RPC_FAR * This,
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ UINT cMiliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColor )( 
            IHomePluginEnvironment2 __RPC_FAR * This,
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ BSTR bstrColorName,
            /* [out] */ COLORREF __RPC_FAR *pcr);
        
        END_INTERFACE
    } IHomePluginEnvironment2Vtbl;

    interface IHomePluginEnvironment2
    {
        CONST_VTBL struct IHomePluginEnvironment2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHomePluginEnvironment2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHomePluginEnvironment2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHomePluginEnvironment2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHomePluginEnvironment2_InvalidatePlugin(This,hPlugin,dwFlags)	\
    (This)->lpVtbl -> InvalidatePlugin(This,hPlugin,dwFlags)

#define IHomePluginEnvironment2_SetSingleShotTimer(This,hPlugin,cMiliseconds)	\
    (This)->lpVtbl -> SetSingleShotTimer(This,hPlugin,cMiliseconds)


#define IHomePluginEnvironment2_GetColor(This,hPlugin,bstrColorName,pcr)	\
    (This)->lpVtbl -> GetColor(This,hPlugin,bstrColorName,pcr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHomePluginEnvironment2_GetColor_Proxy( 
    IHomePluginEnvironment2 __RPC_FAR * This,
    /* [in] */ HPLUGIN hPlugin,
    /* [in] */ BSTR bstrColorName,
    /* [out] */ COLORREF __RPC_FAR *pcr);


void __RPC_STUB IHomePluginEnvironment2_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHomePluginEnvironment2_INTERFACE_DEFINED__ */


#ifndef __IHomePlugin_INTERFACE_DEFINED__
#define __IHomePlugin_INTERFACE_DEFINED__

/* interface IHomePlugin */
/* [object][uuid] */ 


EXTERN_C const IID IID_IHomePlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7F0C58E9-4F30-47bb-9693-D778E999C433")
    IHomePlugin : public IObjectWithSite
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ IXMLDOMNode __RPC_FAR *pnodeParams,
            /* [in] */ IXMLDOMNode __RPC_FAR *pnodeDefault) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHeight( 
            /* [out] */ int __RPC_FAR *pdyPlugin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectability( 
            /* [out] */ BOOL __RPC_FAR *pfSelectable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [out][in] */ PluginEvent __RPC_FAR *ppe) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHomePluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHomePlugin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHomePlugin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHomePlugin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSite )( 
            IHomePlugin __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkSite);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSite )( 
            IHomePlugin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvSite);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IHomePlugin __RPC_FAR * This,
            /* [in] */ HPLUGIN hPlugin,
            /* [in] */ IXMLDOMNode __RPC_FAR *pnodeParams,
            /* [in] */ IXMLDOMNode __RPC_FAR *pnodeDefault);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHeight )( 
            IHomePlugin __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *pdyPlugin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSelectability )( 
            IHomePlugin __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pfSelectable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEvent )( 
            IHomePlugin __RPC_FAR * This,
            /* [out][in] */ PluginEvent __RPC_FAR *ppe);
        
        END_INTERFACE
    } IHomePluginVtbl;

    interface IHomePlugin
    {
        CONST_VTBL struct IHomePluginVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHomePlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHomePlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHomePlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHomePlugin_SetSite(This,pUnkSite)	\
    (This)->lpVtbl -> SetSite(This,pUnkSite)

#define IHomePlugin_GetSite(This,riid,ppvSite)	\
    (This)->lpVtbl -> GetSite(This,riid,ppvSite)


#define IHomePlugin_Initialize(This,hPlugin,pnodeParams,pnodeDefault)	\
    (This)->lpVtbl -> Initialize(This,hPlugin,pnodeParams,pnodeDefault)

#define IHomePlugin_GetHeight(This,pdyPlugin)	\
    (This)->lpVtbl -> GetHeight(This,pdyPlugin)

#define IHomePlugin_GetSelectability(This,pfSelectable)	\
    (This)->lpVtbl -> GetSelectability(This,pfSelectable)

#define IHomePlugin_OnEvent(This,ppe)	\
    (This)->lpVtbl -> OnEvent(This,ppe)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHomePlugin_Initialize_Proxy( 
    IHomePlugin __RPC_FAR * This,
    /* [in] */ HPLUGIN hPlugin,
    /* [in] */ IXMLDOMNode __RPC_FAR *pnodeParams,
    /* [in] */ IXMLDOMNode __RPC_FAR *pnodeDefault);


void __RPC_STUB IHomePlugin_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHomePlugin_GetHeight_Proxy( 
    IHomePlugin __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *pdyPlugin);


void __RPC_STUB IHomePlugin_GetHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHomePlugin_GetSelectability_Proxy( 
    IHomePlugin __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pfSelectable);


void __RPC_STUB IHomePlugin_GetSelectability_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHomePlugin_OnEvent_Proxy( 
    IHomePlugin __RPC_FAR * This,
    /* [out][in] */ PluginEvent __RPC_FAR *ppe);


void __RPC_STUB IHomePlugin_OnEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHomePlugin_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  HDC_UserSize(     unsigned long __RPC_FAR *, unsigned long            , HDC __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HDC_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HDC __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HDC_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HDC __RPC_FAR * ); 
void                      __RPC_USER  HDC_UserFree(     unsigned long __RPC_FAR *, HDC __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


