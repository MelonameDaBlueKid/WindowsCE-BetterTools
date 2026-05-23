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
/*
Module Name:
    DrFilter.h

Abstract:
    Driver's Filter interface defintion.


*/
#pragma once
// Filter De-activation Entry.

typedef struct __DRIVER_FILTER *PDRIVER_FILTER;
typedef VOID  (*pFDriverDeinitFn) (PDRIVER_FILTER pCurrentFilter);

// prototypes for device driver entry points
typedef DWORD (* pFilterInitFn)(DWORD,LPVOID,PDRIVER_FILTER pCurrentFilter);
typedef BOOL (* pFilterPreDeinitFn)(DWORD,PDRIVER_FILTER pCurrentFilter);
typedef BOOL (* pFilterDeinitFn)(DWORD,PDRIVER_FILTER pCurrentFilter);
typedef DWORD (* pFilterOpenFn)(DWORD,DWORD,DWORD,PDRIVER_FILTER pCurrentFilter);
typedef BOOL (* pFilterPreCloseFn)(DWORD,PDRIVER_FILTER pCurrentFilter);
typedef BOOL (* pFilterCloseFn)(DWORD,PDRIVER_FILTER pCurrentFilter);
typedef DWORD (* pFilterReadFn)(DWORD,LPVOID,DWORD,HANDLE,PDRIVER_FILTER pCurrentFilter);
typedef DWORD (* pFilterWriteFn)(DWORD,LPCVOID,DWORD,HANDLE,PDRIVER_FILTER pCurrentFilter);
typedef DWORD (* pFilterSeekFn)(DWORD,long,DWORD,PDRIVER_FILTER pCurrentFilter);
typedef BOOL (* pFilterControlFn)(DWORD,DWORD,PBYTE,DWORD,PBYTE,DWORD,PDWORD,HANDLE,PDRIVER_FILTER pCurrentFilter);
typedef void (* pFilterPowerupFn)(DWORD,PDRIVER_FILTER pCurrentFilter);
typedef void (* pFilterPowerdnFn)(DWORD,PDRIVER_FILTER pCurrentFilter);
typedef BOOL (* pFilterCancelIoFn)(DWORD, HANDLE,PDRIVER_FILTER pCurrentFilter);

#define DRIVER_FILTER_INTERFACE_VERSION_MAJOR  0
#define DRIVER_FILTER_INTERFACE_VERSION_MINOR  0

#define DRIVER_FILTER_INTERFACE_VERSION MAKELONG(DRIVER_FILTER_INTERFACE_VERSION_MINOR,DRIVER_FILTER_INTERFACE_VERSION_MAJOR)
#define GET_DRIVER_FILTER_INTERFACE_MAJOR(x) (WORD)(x>>16)
#define GET_DRIVER_FILTER_INTERFACE_MINOR(x) (WORD)(x)

typedef struct __DRIVER_FILTER {
    DWORD               dwFilterInterfaceVersion;
    pFDriverDeinitFn    fnFilterDeinit;
    PDRIVER_FILTER      pNextFilter; // Setup by DM after FilterInit called.
    
    // Driver's Entry
    pFilterInitFn         fnInit;             
    pFilterPreDeinitFn    fnPreDeinit;   
    pFilterDeinitFn       fnDeinit;         
    pFilterOpenFn         fnOpen;             
    pFilterPreCloseFn     fnPreClose;     
    pFilterCloseFn        fnClose;           
    pFilterReadFn         fnRead;
    pFilterWriteFn        fnWrite;
    pFilterSeekFn         fnSeek;
    pFilterControlFn      fnControl;
    pFilterPowerupFn      fnPowerup;       
    pFilterPowerdnFn      fnPowerdn;       
    pFilterCancelIoFn     fnCancelIo;     
    
} DRIVER_FILTER, *PDRIVER_FILTER;


typedef PDRIVER_FILTER  (*pInitEntry) ( LPCTSTR lpcFilterRegistryPath, LPCTSTR lpDeviceRegistryPath, PDRIVER_FILTER pNextFilter ) ;
    


#define DEFAULT_FILTER_REGISTRY_PATH TEXT("Drivers\\Filters\\")

#define DRIVER_FILTER_INIT_ENTRY TEXT("InitEntry")

#ifdef __cplusplus

class DriverFilterBase : public __DRIVER_FILTER {
private:
public:
    DriverFilterBase( LPCTSTR lpcRegistryPath,PDRIVER_FILTER pNextFilterParam) 
    {
        UNREFERENCED_PARAMETER(lpcRegistryPath);

        dwFilterInterfaceVersion = DRIVER_FILTER_INTERFACE_VERSION;
        fnFilterDeinit = FDriverDeinitStatic;
        pNextFilter = pNextFilterParam;
    
    // Driver's Entry
        fnInit = (pNextFilterParam!=NULL && pNextFilterParam->fnInit!=NULL)? FilterInitStatic: NULL;
        fnPreDeinit = (pNextFilterParam!=NULL && pNextFilterParam->fnPreDeinit!=NULL)? FilterPreDeinitStatic: NULL;
        fnDeinit = (pNextFilterParam!=NULL && pNextFilterParam->fnDeinit!=NULL)? FilterDeinitStatic: NULL;
        fnOpen = (pNextFilterParam!=NULL && pNextFilterParam->fnOpen!=NULL)? FilterOpenStatic: NULL;
        fnPreClose = (pNextFilterParam!=NULL && pNextFilterParam->fnPreClose!=NULL)? FilterPreCloseStatic: NULL;
        fnClose = (pNextFilterParam!=NULL && pNextFilterParam->fnClose!=NULL)? FilterCloseStatic: NULL;
        fnRead = (pNextFilterParam!=NULL && pNextFilterParam->fnRead!=NULL)? FilterReadStatic: NULL;
        fnWrite =(pNextFilterParam!=NULL && pNextFilterParam->fnWrite!=NULL)? FilterWriteStatic: NULL; 
        fnSeek = (pNextFilterParam!=NULL && pNextFilterParam->fnSeek!=NULL)? FilterSeekStatic: NULL; 
        fnControl = (pNextFilterParam!=NULL && pNextFilterParam->fnControl!=NULL)? FilterControlStatic: NULL; 
        fnPowerup = (pNextFilterParam!=NULL && pNextFilterParam->fnPowerup!=NULL)? FilterPowerupStatic: NULL; 
        fnPowerdn = (pNextFilterParam!=NULL && pNextFilterParam->fnPowerdn!=NULL)? FilterPowerdnStatic: NULL; 
        fnCancelIo = (pNextFilterParam!=NULL && pNextFilterParam->fnCancelIo!=NULL)? FilterCancelIoStatic: NULL; 
    };
    virtual Init() { return TRUE; };
    virtual ~DriverFilterBase() {};
    static VOID  FDriverDeinitStatic (PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            delete (DriverFilterBase *)pCurrentFilter;
        else {
            ASSERT(FALSE);
        }
    }
    static DWORD FilterInitStatic(DWORD dwContext,LPVOID lpParam,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterInit(dwContext, lpParam);
        else {
            ASSERT(FALSE);
            return 0;
        }
    }
    static BOOL FilterPreDeinitStatic(DWORD dwContext,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterPreDeinit(dwContext);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static BOOL FilterDeinitStatic(DWORD dwContext,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterDeinit(dwContext);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static DWORD FilterOpenStatic(DWORD dwConext,DWORD dwAccessCode,DWORD SharedMode,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterOpen(dwConext,dwAccessCode,SharedMode);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static BOOL FilterPreCloseStatic(DWORD dwOpenCont,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterPreClose(dwOpenCont);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static BOOL FilterCloseStatic(DWORD dwOpenCont,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterClose(dwOpenCont);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static DWORD FilterReadStatic(DWORD dwOpenCont,LPVOID pInBuf,DWORD cbSize,HANDLE hAsyncRef,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterRead(dwOpenCont,pInBuf,cbSize,hAsyncRef);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static DWORD FilterWriteStatic(DWORD dwOpenCont,LPCVOID pOutBuf,DWORD cbSize,HANDLE hAsyncRef,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterWrite(dwOpenCont,pOutBuf,cbSize,hAsyncRef);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static DWORD FilterSeekStatic(DWORD dwOpenCont,long lDistanceToMove,DWORD dwMoveMethod,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterSeek(dwOpenCont,lDistanceToMove,dwMoveMethod);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    static BOOL FilterControlStatic(DWORD dwOpenCont,DWORD dwCode, PBYTE pBufIn, DWORD dwLenIn, PBYTE pBufOut, DWORD dwLenOut,
              PDWORD pdwActualOut,HANDLE hAsyncRef,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterControl(dwOpenCont,dwCode,pBufIn,dwLenIn,pBufOut,dwLenOut,pdwActualOut,hAsyncRef);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
        
    }

    static void FilterPowerupStatic(DWORD dwConext,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter){
            ((DriverFilterBase *)pCurrentFilter)->FilterPowerup(dwConext);
        }
        else {
            ASSERT(FALSE);
        }
    }
    static void FilterPowerdnStatic(DWORD dwConext,PDRIVER_FILTER pCurrentFilter) {
        if (pCurrentFilter){
            return ((DriverFilterBase *)pCurrentFilter)->FilterPowerup(dwConext);
        }
        else {
            ASSERT(FALSE);
        }
    }
    static BOOL FilterCancelIoStatic(DWORD dwOpenCont, HANDLE hAsyncHandle,PDRIVER_FILTER pCurrentFilter){
        if (pCurrentFilter)
            return ((DriverFilterBase *)pCurrentFilter)->FilterCancelIo(dwOpenCont, hAsyncHandle);
        else {
            ASSERT(FALSE);
            return FALSE;
        }
    }
protected:
    virtual DWORD   FilterInit(DWORD dwContext,LPVOID lpParam) {
        return pNextFilter->fnInit(dwContext,lpParam,pNextFilter);
    }
    virtual BOOL    FilterPreDeinit(DWORD dwContext) {
        return pNextFilter->fnPreDeinit(dwContext,pNextFilter);
    }
    virtual BOOL    FilterDeinit(DWORD dwContext) {
        return pNextFilter->fnDeinit(dwContext,pNextFilter);
    }
    virtual DWORD   FilterOpen(DWORD dwConext,DWORD dwAccessCode,DWORD SharedMode) {
        return pNextFilter->fnOpen(dwConext,dwAccessCode,SharedMode,pNextFilter);
    }
    virtual BOOL    FilterPreClose(DWORD dwOpenCont) {
        return pNextFilter->fnPreClose(dwOpenCont, pNextFilter);
    }
    virtual BOOL    FilterClose(DWORD dwOpenCont) {
        return pNextFilter->fnClose(dwOpenCont,pNextFilter);
    }
    virtual DWORD   FilterRead(DWORD dwOpenCont,LPVOID pInBuf,DWORD cbSize,HANDLE hAsyncRef) {
        return pNextFilter->fnRead(dwOpenCont,pInBuf,cbSize,hAsyncRef,pNextFilter);
    }
    virtual DWORD   FilterWrite(DWORD dwOpenCont,LPCVOID pOutBuf,DWORD cbSize,HANDLE hAsyncRef) {
        return pNextFilter->fnWrite(dwOpenCont, pOutBuf, cbSize, hAsyncRef,pNextFilter);
    }
    virtual DWORD   FilterSeek(DWORD dwOpenCont,long lDistanceToMove,DWORD dwMoveMethod) {
        return pNextFilter->fnSeek(dwOpenCont,lDistanceToMove,dwMoveMethod,pNextFilter);
    }
    virtual BOOL    FilterControl(DWORD dwOpenCont,DWORD dwCode, PBYTE pBufIn, DWORD dwLenIn, PBYTE pBufOut, DWORD dwLenOut,
              PDWORD pdwActualOut,HANDLE hAsyncRef)
        {
        return pNextFilter->fnControl(dwOpenCont, dwCode, pBufIn, dwLenIn, pBufOut, dwLenOut, pdwActualOut, hAsyncRef,pNextFilter);
    }
    virtual void    FilterPowerup(DWORD dwConext) {
        return pNextFilter->fnPowerup(dwConext,pNextFilter) ;
    }
    virtual void    FilterPowerdn(DWORD dwConext ) {
        return pNextFilter->fnPowerdn(dwConext,pNextFilter);
    }
    virtual BOOL    FilterCancelIo(DWORD dwOpenCont, HANDLE hAsyncHandle) {
        return pNextFilter->fnCancelIo(dwOpenCont, hAsyncHandle, pNextFilter);
    }
    
};

#endif

