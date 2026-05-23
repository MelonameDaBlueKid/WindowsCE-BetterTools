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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

oemglobal.h

Abstract:

This file defines the structure that contains all the functions/variables used by OAL and NK

Notes: 


--*/

#ifndef _OEM_GLOBAL_H_
#define _OEM_GLOBAL_H_

#ifdef MIPS
//
// MIPS Architecture flags. MIPS kernel will try to auto-detect all of the flags. However, there might
// be some CPUs that we'll not be able to detect correct value. Therefore we provide the "dwArchFlagOverride"
// variable in the OEMGLOBAL structure such that OEM can set to override auto-detection.
// That is, kernel will not do any auto-detection if (MIPS_FLAG_NO_OVERRIDE != dwArchFlagOverride)
//

#define MIPS_FLAG_NO_OVERRIDE               0xffffffff          // auto detect if dwArchFlagOverride == MIPS_FLAG_NO_OVERRIDE

// mips architecture flags
#define MIPS_FLAG_FPU_PRESENT               0x00000001          // FPU exist
#define MIPS_FLAG_IGNORE_COPROC_UNUSABLE    0x00000002          // IGNORE Co-Proc unusable exception
#define MIPS_FLAG_MIPS16                    0x00000004          // MIPS16 supported
#define MIPS_FLAG_TINY_PAGE                 0x00000008          // support tiny-page (PFN_SHIFT == 4)
#define MIPS_FLAG_INSERT_NOP_FOR_HANDLER    0x00000010          // insert 2 nops at the beginning of exception handler
#endif

#ifdef SHx
#define SH4_INTEVT_LENGTH 12 // by default interrupt code length is 12 bits; this can be a maximum of 14 bits.
#endif

#ifndef ASM_ONLY

#include <kitl.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// function types declaration
//
typedef struct _MEMORY_SECTION {
    DWORD dwFlags;
    DWORD dwStart;
    DWORD dwLen;
} MEMORY_SECTION, *PMEMORY_SECTION;

// from romldr.h
typedef struct ROMChain_t *PROMChain_t;

// initialization functions
typedef void (* PFN_InitDebugSerial) (void);
typedef void (* PFN_InitPlatform) (void);

// debug related functions
typedef void (* PFN_WriteDebugByte) (BYTE ch);
typedef void (* PFN_WriteDebugString) (LPCWSTR pszStr);
typedef int  (* PFN_ReadDebugByte) (void);
typedef void (* PFN_WriteDebugLED) (WORD wIndex, DWORD dwPattern);

// cache functions
typedef void (* PFN_CacheRangeFlush) (LPVOID pAddr, DWORD dwLength, DWORD dwFlags);

// time related functions
typedef void (* PFN_InitClock) (void);
typedef BOOL (* PFN_GetRealTime) (SYSTEMTIME *pst);
typedef BOOL (* PFN_SetRealTime) (const SYSTEMTIME *pst);
typedef PFN_SetRealTime PFN_SetAlarmTime;
typedef DWORD (* PFN_GetTickCount) (void);
typedef BOOL (* PFN_QueryPerfCounter) (LARGE_INTEGER *pli);
typedef BOOL (* PFN_QueryPerfFreq) (LARGE_INTEGER *pli);

// scheduler related
typedef void (* PFN_Idle) (DWORD dwIdleParam);
typedef void (* PFN_NotifyThreadExit) (DWORD dwThrdId, DWORD dwExitCode);
typedef void (* PFN_NotifyReschedule) (DWORD dwThrdId, DWORD dwPrio, DWORD dwQuantum, DWORD dwFlags);
typedef void (* PFN_UpdateReschedTime) (DWORD dwTick);

// power related functions
typedef void (* PFN_PowerOff) (void);

// system halt notification
typedef PFN_PowerOff        PFN_HaltSystem;

// ram detection functions
typedef BOOL (* PFN_GetExtensionDRAM) (LPDWORD lpMemStart, LPDWORD lpMemLen);
typedef DWORD (*PFN_EnumExtensionDRAM) (PMEMORY_SECTION pMemSections, DWORD cMemSections);
typedef DWORD (*PFN_CalcFSPages) (DWORD dwMemPages, DWORD dwDefaultFSPages);

// interrupt handling related
typedef void (* PFN_NMIHandler) (void);
typedef DWORD (* PFN_SHxNMIHandler) (void);
typedef BOOL (* PFN_InterruptEnable) (DWORD idInt, LPVOID pvData, DWORD cbData);
typedef void (* PFN_InterruptDisable) (DWORD idInt);
typedef PFN_InterruptDisable PFN_InterruptDone;
typedef void (* PFN_InterruptMask) (DWORD idInt, BOOL fDisable);
typedef DWORD (* PFN_NotifyIntrOccurs) (DWORD dwSysIntr);


// co-proc support
typedef void (* PFN_CoProcFunc) (LPBYTE pArea);
typedef PFN_CoProcFunc PFN_InitCoProcRegs;
typedef PFN_CoProcFunc PFN_SaveCoProcRegs;
typedef PFN_CoProcFunc PFN_RestoreCoProcRegs;

// persistent registry support
typedef DWORD (* PFN_ReadRegistry) (DWORD dwFlags, LPBYTE pBuf, DWORD len);
typedef BOOL (* PFN_WriteRegistry) (DWORD dwFlags, LPBYTE pBuf, DWORD len);

// watchdog support
typedef void (* PFN_RefreshWatchDog) (void);

// profiler support
typedef void (* PFN_ProfileTimerEnable) (DWORD dwUSec);
typedef void (* PFN_ProfileTimerDisable) (void);


// others
typedef BOOL (* PFN_KDIoctl) (DWORD dwCode, LPVOID pBuf, DWORD cbSize);
typedef BOOL (* PFN_Ioctl) (DWORD dwCode, LPVOID pInBuf, DWORD nInSize, LPVOID pOutBuf, DWORD nOutSize, LPDWORD pcbRet);
typedef BOOL (* PFN_IsRom) (DWORD dwShiftedPhysAddr);
typedef void (* PFN_MapW32Priority) (int nPrios, LPBYTE pPrioMap);
typedef BOOL (* PFN_SetMemoryAttributes) (LPVOID pVirtualAddr, LPVOID pPhysAddr, DWORD cbSize, DWORD dwAttributes);
typedef BOOL (* PFN_IsProcessorFeaturePresent) (DWORD dwProcessorFeature);
typedef void (* PFN_NotifyForceCleanBoot) (DWORD, DWORD, DWORD, DWORD);

#ifdef ARM
// OEM defined VFP save/restore for implementation defined control registers
typedef DWORD (* PFN_InterruptHandler) (DWORD dwEpc);
typedef void (* PFN_SaveRestoreVFPCtrlRegs) (LPDWORD lpExtra, int nMaxRegs);
typedef BOOL (* PFN_HandleVFPException) (EXCEPTION_RECORD *er, PCONTEXT pctx);

DWORD OEMARMCacheMode (void);

#endif


//
// the structure for exchange
//
typedef struct _OEMGLOBAL {
    DWORD                   dwVersion;

    // initialization
    PFN_InitDebugSerial     pfnInitDebugSerial;
    PFN_InitPlatform        pfnInitPlatform;

    // debug functions
    PFN_WriteDebugByte      pfnWriteDebugByte;
    PFN_WriteDebugString    pfnWriteDebugString;
    PFN_ReadDebugByte       pfnReadDebugByte;
    PFN_WriteDebugLED       pfnWriteDebugLED;

    // cache fuctions
    PFN_CacheRangeFlush     pfnCacheRangeFlush;

    // time related funcitons
    PFN_InitClock           pfnInitClock;
    PFN_GetRealTime         pfnGetRealTime;
    PFN_SetRealTime         pfnSetRealTime;
    PFN_SetAlarmTime        pfnSetAlarmTime;
    PFN_QueryPerfCounter    pfnQueryPerfCounter;
    PFN_QueryPerfFreq       pfnQueryPerfFreq;
    PFN_GetTickCount        pfnGetTickCount;

    // scheduler related functions
    PFN_Idle                pfnIdle;
    PFN_NotifyThreadExit    pfnNotifyThreadExit;
    PFN_NotifyReschedule    pfnNotifyReschedule;
    PFN_NotifyIntrOccurs    pfnNotifyIntrOccurs;
    PFN_UpdateReschedTime   pfnUpdateReschedTime;
    DWORD                   dwDefaultThreadQuantum;

    // power related functions
    PFN_PowerOff            pfnPowerOff;

    // DRAM detection functions
    PFN_GetExtensionDRAM    pfnGetExtensionDRAM;
    PFN_EnumExtensionDRAM   pfnEnumExtensionDRAM;
    PFN_CalcFSPages         pfnCalcFSPages;
    DWORD                   dwMainMemoryEndAddress;

    // interrupt handling functions
    PFN_InterruptEnable     pfnInterruptEnable;
    PFN_InterruptDisable    pfnInterruptDisable;
    PFN_InterruptDone       pfnInterruptDone;
    PFN_InterruptMask       pfnInterruptMask;
    
    // co-proc support
    PFN_InitCoProcRegs      pfnInitCoProcRegs;
    PFN_SaveCoProcRegs      pfnSaveCoProcRegs;
    PFN_RestoreCoProcRegs   pfnRestoreCoProcRegs;
    DWORD                   cbCoProcRegSize;
    DWORD                   fSaveCoProcReg;

    // persistent registry support
    PFN_ReadRegistry        pfnReadRegistry;
    PFN_WriteRegistry       pfnWriteRegistry;

    // watchdog support
    PFN_RefreshWatchDog     pfnRefreshWatchDog;
    DWORD                   dwWatchDogPeriod;
    DWORD                   dwWatchDogThreadPriority;

    // profiler support
    PFN_ProfileTimerEnable  pfnProfileTimerEnable;
    PFN_ProfileTimerDisable pfnProfileTimerDisable;

    // Simple RAM based Error Reporting support
    DWORD                   cbErrReportSize;    // was cbNKDrWatsonSize
    
    // others
    PFN_Ioctl               pfnOEMIoctl;
    PFN_KDIoctl             pfnKDIoctl;
    PFN_IsRom               pfnIsRom;
    PFN_MapW32Priority      pfnMapW32Priority;
    PFN_SetMemoryAttributes pfnSetMemoryAttributes;
    PFN_IsProcessorFeaturePresent   pfnIsProcessorFeaturePresent;
    PFN_HaltSystem          pfnHaltSystem;
    PFN_NotifyForceCleanBoot pfnNotifyForceCleanBoot;   // filesys detected object store corruption and force system boot clean
    
    PROMChain_t             pROMChain;

    // Platform specific information passed from OAL to KITL.
    LPVOID                  pKitlInfo;
    PFNVOID                 pfnKITLGlobalInit;          // KITL entry point (set to Kitl dll main if KITL is part of OEM)

    DBGPARAM                *pdpCurSettings;

    // compiler /GS security cookie
    DWORD_PTR *             p__security_cookie;
    DWORD_PTR *             p__security_cookie_complement;

    // alarm resolution
    DWORD                   dwAlarmResolution;          // alarm resolution in ms

    // rtc rollover support
    DWORD                   dwYearsRTCRollover;         // # of years RTC rollover.

    // reserve some room for future extention.
    DWORD                   _rsvd_[8];                  // reserve 8 dword for future use

    // CPU-dependent fields start here
#if defined (x86)
    // CPU dependent functions
    PFN_NMIHandler          pfnNMIHandler;              // NMI Handler
#elif defined (ARM)
    PFN_InterruptHandler    pfnInterruptHandler;        // interrupt handler
    PFNVOID                 pfnFIQHandler;              // FIQ handler
    
    DWORD                   dwARM1stLvlBits;            // extra bits to be set in 1st level page table
    DWORD                   dwARMCacheMode;             // C and B bits
    DWORD                   f_V6_VIVT_ICache;           // v6 specific - if I-Cache is VIVT ASID-tagged

    // VFP funcitons
    PFN_SaveRestoreVFPCtrlRegs  pfnSaveVFPCtrlRegs;     // save VFP control registers
    PFN_SaveRestoreVFPCtrlRegs  pfnRestoreVFPCtrlRegs;  // restore VFP control registers
    PFN_HandleVFPException      pfnHandleVFPExcp;       // handle VFP exception

#elif defined (MIPS)

    DWORD                   dwCoProcBits;               // platform specific co-proc enable bits
    DWORD                   dwOEMTLBLastIdx;            // size of TLB - 1
    DWORD                   dwArchFlagOverride;         // architecture flag override
    const BYTE *            pIntrPrio;                  // interrupt prority (ptr to 64 bytes)
    const BYTE *            pIntrMask;                  // interrupt mask (ptr to 8 bytes)
    
#elif defined (SHx)
    PFN_SHxNMIHandler       pfnNMIHandler;              // NMI Handler
    DWORD                   dwSHxIntEventCodeLength;    // platform specific interrupt code length (in bits; 12 is the default)
#else
#pragma error("No CPU Defined")
#endif

} OEMGLOBAL, *POEMGLOBAL;

extern POEMGLOBAL g_pOemGlobal;

// For backword compatibility, include bcoemglobal.h that maps the pre Win CE 6.0
// variables to the new field names

#ifndef NO_BCOEMGLOBAL
#include <bcoemglobal.h>
#endif // !NO_BCOEMGLOBAL

// alarm resolution
#define MIN_NKALARMRESOLUTION_MSEC      1000    // 1 second
#define MAX_NKALARMRESOLUTION_MSEC      60000   // 60 seconds
#define DEFAULT_ALARMRESOLUTION_MSEC    10000   // 10 seconds

#ifdef __cplusplus
}
#endif

#endif  // ASM_ONLY

#endif  // _OEM_GLOBAL_H_

