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
/* at Thu Mar 13 23:04:01 2003
 */
/* Compiler settings for .\propidl.idl:
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

#ifndef __propidl_h__
#define __propidl_h__

/* Forward Declarations */ 

/* header files for imported files */
#include "objidl.h"
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_propidl_0000 */
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
#if ( _MSC_VER >= 800 )
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201)    /* Nameless struct/union */
#pragma warning(disable:4237)    /* obsolete member named 'bool' */
#endif
#if ( _MSC_VER >= 1020 )
#pragma once
#endif
typedef struct tagVersionedStream
    {
    GUID guidVersion;
    IStream __RPC_FAR *pStream;
    }	VERSIONEDSTREAM;

typedef struct tagVersionedStream __RPC_FAR *LPVERSIONEDSTREAM;


// Flags for IPropertySetStorage::Create
//   (This flag is only supported on StgCreatePropStg & StgOpenPropStg
//   (This flag causes a version-1 property set to be created
#define	PROPSETFLAG_CASE_SENSITIVE	( 8 )


// Flags for the reservied PID_BEHAVIOR property
#define	PROPSET_BEHAVIOR_CASE_SENSITIVE	( 1 )

#ifdef MIDL_PASS
// This is the PROPVARIANT definition for marshaling.
typedef struct tag_inner_PROPVARIANT PROPVARIANT;

#else
// This is the standard C layout of the PROPVARIANT.
typedef struct tagPROPVARIANT PROPVARIANT;
#endif
#ifndef __objidl_h__
typedef struct tagCAC
    {
    ULONG cElems;
    /* [size_is] */ CHAR __RPC_FAR *pElems;
    }	CAC;

#ifdef MIDL_PASS
// This is the PROPVARIANT padding layout for marshaling.
typedef BYTE PROPVAR_PAD1;

typedef BYTE PROPVAR_PAD2;

typedef ULONG PROPVAR_PAD3;

#else
// This is the standard C layout of the structure.
typedef WORD PROPVAR_PAD1;
typedef WORD PROPVAR_PAD2;
typedef WORD PROPVAR_PAD3;
#define tag_inner_PROPVARIANT
#endif
#ifndef MIDL_PASS
struct tagPROPVARIANT {
  union {
#endif
struct tag_inner_PROPVARIANT
    {
    VARTYPE vt;
    PROPVAR_PAD1 wReserved1;
    PROPVAR_PAD2 wReserved2;
    PROPVAR_PAD3 wReserved3;
    /* [switch_is] */ /* [switch_type] */ union 
        {
        /* [case()] */  /* Empty union arm */ 
        /* [case()] */ CHAR cVal;
        /* [case()] */ UCHAR bVal;
        /* [case()] */ SHORT iVal;
        /* [case()] */ USHORT uiVal;
        /* [case()] */ LONG lVal;
        /* [case()] */ ULONG ulVal;
        /* [case()] */ INT intVal;
        /* [case()] */ UINT uintVal;
        /* [case()] */ LARGE_INTEGER hVal;
        /* [case()] */ ULARGE_INTEGER uhVal;
        /* [case()] */ FLOAT fltVal;
        /* [case()] */ DOUBLE dblVal;
        /* [case()] */ VARIANT_BOOL boolVal;
        /* [case()] */ _VARIANT_BOOL bool;
        /* [case()] */ SCODE scode;
        /* [case()] */ CY cyVal;
        /* [case()] */ DATE date;
        /* [case()] */ FILETIME filetime;
        /* [case()] */ CLSID __RPC_FAR *puuid;
        /* [case()] */ CLIPDATA __RPC_FAR *pclipdata;
        /* [case()] */ BSTR bstrVal;
        /* [case()] */ BSTRBLOB bstrblobVal;
        /* [case()] */ BLOB blob;
        /* [case()] */ LPSTR pszVal;
        /* [case()] */ LPWSTR pwszVal;
        /* [case()] */ IUnknown __RPC_FAR *punkVal;
        /* [case()] */ IDispatch __RPC_FAR *pdispVal;
        /* [case()] */ IStream __RPC_FAR *pStream;
        /* [case()] */ IStorage __RPC_FAR *pStorage;
        /* [case()] */ LPVERSIONEDSTREAM pVersionedStream;
        /* [case()] */ LPSAFEARRAY parray;
        /* [case()] */ CAC cac;
        /* [case()] */ CAUB caub;
        /* [case()] */ CAI cai;
        /* [case()] */ CAUI caui;
        /* [case()] */ CAL cal;
        /* [case()] */ CAUL caul;
        /* [case()] */ CAH cah;
        /* [case()] */ CAUH cauh;
        /* [case()] */ CAFLT caflt;
        /* [case()] */ CADBL cadbl;
        /* [case()] */ CABOOL cabool;
        /* [case()] */ CASCODE cascode;
        /* [case()] */ CACY cacy;
        /* [case()] */ CADATE cadate;
        /* [case()] */ CAFILETIME cafiletime;
        /* [case()] */ CACLSID cauuid;
        /* [case()] */ CACLIPDATA caclipdata;
        /* [case()] */ CABSTR cabstr;
        /* [case()] */ CABSTRBLOB cabstrblob;
        /* [case()] */ CALPSTR calpstr;
        /* [case()] */ CALPWSTR calpwstr;
        /* [case()] */ CAPROPVARIANT capropvar;
        /* [case()] */ CHAR __RPC_FAR *pcVal;
        /* [case()] */ UCHAR __RPC_FAR *pbVal;
        /* [case()] */ SHORT __RPC_FAR *piVal;
        /* [case()] */ USHORT __RPC_FAR *puiVal;
        /* [case()] */ LONG __RPC_FAR *plVal;
        /* [case()] */ ULONG __RPC_FAR *pulVal;
        /* [case()] */ INT __RPC_FAR *pintVal;
        /* [case()] */ UINT __RPC_FAR *puintVal;
        /* [case()] */ FLOAT __RPC_FAR *pfltVal;
        /* [case()] */ DOUBLE __RPC_FAR *pdblVal;
        /* [case()] */ VARIANT_BOOL __RPC_FAR *pboolVal;
        /* [case()] */ DECIMAL __RPC_FAR *pdecVal;
        /* [case()] */ SCODE __RPC_FAR *pscode;
        /* [case()] */ CY __RPC_FAR *pcyVal;
        /* [case()] */ DATE __RPC_FAR *pdate;
        /* [case()] */ BSTR __RPC_FAR *pbstrVal;
        /* [case()] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkVal;
        /* [case()] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispVal;
        /* [case()] */ LPSAFEARRAY __RPC_FAR *pparray;
        /* [case()] */ PROPVARIANT __RPC_FAR *pvarVal;
        }	;
    };
#ifndef MIDL_PASS
    DECIMAL decVal;
  };
};
#endif
#ifdef MIDL_PASS
// This is the LPPROPVARIANT definition for marshaling.
typedef struct tag_inner_PROPVARIANT __RPC_FAR *LPPROPVARIANT;

#else
// This is the standard C layout of the PROPVARIANT.
typedef struct tagPROPVARIANT * LPPROPVARIANT;
#endif
#endif
// Reserved global Property IDs
// Range which is read-only to downlevel implementations
#define	PID_MIN_READONLY	( 0x80000000 )

#define	PID_MAX_READONLY	( 0xbfffffff )

// Property IDs for the DiscardableInformation Property Set

#define PIDDI_THUMBNAIL          0x00000002L // VT_BLOB

// Property IDs for the SummaryInformation Property Set

#define PIDSI_TITLE               0x00000002L  // VT_LPSTR
#define PIDSI_SUBJECT             0x00000003L  // VT_LPSTR
#define PIDSI_AUTHOR              0x00000004L  // VT_LPSTR
#define PIDSI_KEYWORDS            0x00000005L  // VT_LPSTR
#define PIDSI_COMMENTS            0x00000006L  // VT_LPSTR
#define PIDSI_TEMPLATE            0x00000007L  // VT_LPSTR
#define PIDSI_LASTAUTHOR          0x00000008L  // VT_LPSTR
#define PIDSI_REVNUMBER           0x00000009L  // VT_LPSTR
#define PIDSI_EDITTIME            0x0000000aL  // VT_FILETIME (UTC)
#define PIDSI_LASTPRINTED         0x0000000bL  // VT_FILETIME (UTC)
#define PIDSI_CREATE_DTM          0x0000000cL  // VT_FILETIME (UTC)
#define PIDSI_LASTSAVE_DTM        0x0000000dL  // VT_FILETIME (UTC)
#define PIDSI_PAGECOUNT           0x0000000eL  // VT_I4
#define PIDSI_WORDCOUNT           0x0000000fL  // VT_I4
#define PIDSI_CHARCOUNT           0x00000010L  // VT_I4
#define PIDSI_THUMBNAIL           0x00000011L  // VT_CF
#define PIDSI_APPNAME             0x00000012L  // VT_LPSTR
#define PIDSI_DOC_SECURITY        0x00000013L  // VT_I4

// Property IDs for the DocSummaryInformation Property Set

#define PIDDSI_CATEGORY          0x00000002 // VT_LPSTR
#define PIDDSI_PRESFORMAT        0x00000003 // VT_LPSTR
#define PIDDSI_BYTECOUNT         0x00000004 // VT_I4
#define PIDDSI_LINECOUNT         0x00000005 // VT_I4
#define PIDDSI_PARCOUNT          0x00000006 // VT_I4
#define PIDDSI_SLIDECOUNT        0x00000007 // VT_I4
#define PIDDSI_NOTECOUNT         0x00000008 // VT_I4
#define PIDDSI_HIDDENCOUNT       0x00000009 // VT_I4
#define PIDDSI_MMCLIPCOUNT       0x0000000A // VT_I4
#define PIDDSI_SCALE             0x0000000B // VT_BOOL
#define PIDDSI_HEADINGPAIR       0x0000000C // VT_VARIANT | VT_VECTOR
#define PIDDSI_DOCPARTS          0x0000000D // VT_LPSTR | VT_VECTOR
#define PIDDSI_MANAGER           0x0000000E // VT_LPSTR
#define PIDDSI_COMPANY           0x0000000F // VT_LPSTR
#define PIDDSI_LINKSDIRTY        0x00000010 // VT_BOOL


//  FMTID_MediaFileSummaryInfo - Property IDs

#define PIDMSI_EDITOR                   0x00000002L  // VT_LPWSTR
#define PIDMSI_SUPPLIER                 0x00000003L  // VT_LPWSTR
#define PIDMSI_SOURCE                   0x00000004L  // VT_LPWSTR
#define PIDMSI_SEQUENCE_NO              0x00000005L  // VT_LPWSTR
#define PIDMSI_PROJECT                  0x00000006L  // VT_LPWSTR
#define PIDMSI_STATUS                   0x00000007L  // VT_UI4
#define PIDMSI_OWNER                    0x00000008L  // VT_LPWSTR
#define PIDMSI_RATING                   0x00000009L  // VT_LPWSTR
#define PIDMSI_PRODUCTION               0x0000000AL  // VT_FILETIME (UTC)
#define PIDMSI_COPYRIGHT                0x0000000BL  // VT_LPWSTR

//  PIDMSI_STATUS value definitions

enum PIDMSI_STATUS_VALUE
    {	PIDMSI_STATUS_NORMAL	= 0,
	PIDMSI_STATUS_NEW	= PIDMSI_STATUS_NORMAL + 1,
	PIDMSI_STATUS_PRELIM	= PIDMSI_STATUS_NEW + 1,
	PIDMSI_STATUS_DRAFT	= PIDMSI_STATUS_PRELIM + 1,
	PIDMSI_STATUS_INPROGRESS	= PIDMSI_STATUS_DRAFT + 1,
	PIDMSI_STATUS_EDIT	= PIDMSI_STATUS_INPROGRESS + 1,
	PIDMSI_STATUS_REVIEW	= PIDMSI_STATUS_EDIT + 1,
	PIDMSI_STATUS_PROOF	= PIDMSI_STATUS_REVIEW + 1,
	PIDMSI_STATUS_FINAL	= PIDMSI_STATUS_PROOF + 1,
	PIDMSI_STATUS_OTHER	= 0x7fff
    };
#ifndef __objidl_h__
// Macros for parsing the OS Version of the Property Set Header
#define PROPSETHDR_OSVER_KIND(dwOSVer)      HIWORD( (dwOSVer) )
#define PROPSETHDR_OSVER_MAJOR(dwOSVer)     LOBYTE(LOWORD( (dwOSVer) ))
#define PROPSETHDR_OSVER_MINOR(dwOSVer)     HIBYTE(LOWORD( (dwOSVer) ))
#define PROPSETHDR_OSVERSION_UNKNOWN        0xFFFFFFFF
#endif
typedef /* [unique] */ IPropertyStorage __RPC_FAR *LPPROPERTYSTORAGE;

WINOLEAPI PropVariantCopy ( PROPVARIANT * pvarDest, const PROPVARIANT * pvarSrc );
WINOLEAPI PropVariantClear ( PROPVARIANT * pvar );
WINOLEAPI FreePropVariantArray ( ULONG cVariants, PROPVARIANT * rgvars );

#ifndef _PROPVARIANTINIT_DEFINED_
#define _PROPVARIANTINIT_DEFINED_
#   ifdef __cplusplus
inline void PropVariantInit ( PROPVARIANT * pvar )
{
    memset ( pvar, 0, sizeof(PROPVARIANT) );
}
#   else
#   define PropVariantInit(pvar) memset ( (pvar), 0, sizeof(PROPVARIANT) )
#   endif
#endif


#ifndef _STGCREATEPROPSTG_DEFINED_
WINOLEAPI StgCreatePropStg( IUnknown* pUnk, REFFMTID fmtid, const CLSID *pclsid, DWORD grfFlags, DWORD dwReserved, IPropertyStorage **ppPropStg );
WINOLEAPI StgOpenPropStg( IUnknown* pUnk, REFFMTID fmtid, DWORD grfFlags, DWORD dwReserved, IPropertyStorage **ppPropStg );
WINOLEAPI StgCreatePropSetStg( IStorage *pStorage, DWORD dwReserved, IPropertySetStorage **ppPropSetStg);

#define CCH_MAX_PROPSTG_NAME    31
WINOLEAPI FmtIdToPropStgName( const FMTID *pfmtid, LPOLESTR oszName );
WINOLEAPI PropStgNameToFmtId( const LPOLESTR oszName, FMTID *pfmtid );
#endif
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4201)    /* Nameless struct/union */
#pragma warning(default:4237)    /* keywords bool, true, false, etc.. */
#endif


extern RPC_IF_HANDLE __MIDL_itf_propidl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_propidl_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


