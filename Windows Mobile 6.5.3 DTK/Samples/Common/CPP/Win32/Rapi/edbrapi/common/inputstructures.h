//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// --------------------------------------------------------------------------
//
// Module:
//
//     InputStructures.h
//
// Purpose:
//
//    include file for Windows CE Remote API, specially for EDB applications
//    The input structures pack the input parameters of EDB functions into one object, 
//    and pass them in CeRapiInvoke
// --------------------------------------------------------------------------

#ifndef EDB
#define EDB
#endif

typedef struct tagINMOUNTDBVOLEX
{
    DWORD dwFlags;
    WCHAR wszDBVol[MAX_PATH];
    CEVOLUMEOPTIONS *pOptions;
}INMOUNTDBVOLEX, *PINMOUNTDBVOLEX;

typedef struct tagINCREATEDBPROP
{
    CEGUID guid;
    CEDBASEINFOEX Options;
    DWORD cProps;
    CEPROPSPEC *prgProps;
}INCREATEDBPROP, *PINCREATEDBPROP;

typedef struct tagINOPENDBINSESSION
{  
    HANDLE hSession;
    CEGUID guid;
    CEOID oidDbase;
    WCHAR wszName[MAX_PATH]; 
    SORTORDERSPECEX sortorderspec; 
    DWORD dwFlags;
    CENOTIFYREQUEST request;
}INOPENDBINSESSION, *PINOPENDBINSESSION;

typedef struct tagINSEEKEB
{
  HANDLE hDatabase;
  DWORD dwSeekType; //dwFlags in CeReadRecordPropsEx 
  DWORD dwValue;    //cbBuffer in CeReadRecordPropsEx 
  WORD wNumVals;    //cPropID  in CeReadRecordPropsEx 
}INSEEKEB, *PINSEEKEB;

typedef struct tagINADDDBPROPS
{
    CEGUID guid;
    CEOID oidDbase;
    DWORD cProps;
    CEPROPSPEC* prgProps;
}INADDDBPROPS, *PINADDDBPROPS;

typedef struct tagINGETDBPROPS
{
    HANDLE hDatabase;
    WORD cPropID;
    CEPROPID* prgPropID; //NULL or not, used as flag 
    CEPROPSPEC* prgProps; //NULL or not, used as flag 
}INGETDBPROPS, *PINGETDBPROPS;

