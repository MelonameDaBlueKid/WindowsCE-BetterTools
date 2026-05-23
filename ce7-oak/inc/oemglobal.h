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


//
// Platform flags : bit field which specifies platform capabilities
//
#define OAL_ENABLE_SOFT_RESET               0x00000001
#define OAL_HAVE_VFP_HARDWARE               0x00000002
#define OAL_HAVE_VFP_SUPPORT                0x00000004
#define OAL_SMP_QPC_SAFE_DURING_INTERRUPTS  0x00000008
#define OAL_EXTENDED_VFP_REGISTERS          0x00000010


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

#define MIPS_DEFAULT_FPU_ENABLE                  0x20000000    
#endif


#ifdef SHx
#define SH4_INTEVT_LENGTH 12 // by default interrupt code length is 12 bits; this can be a maximum of 14 bits.
#endif

#ifdef ARM

// VFP system registers bits
//
#define FPEXC_EX_BIT        0x80000000
#define FPEXC_ENABLE_BIT    0x40000000
#define FPEXC_DEX_BIT       0x20000000
#define FPEXC_FP2V_BIT      0x10000000
#define FPEXC_VV_BIT        0x08000000

#define FPEXC_CLEAR_BITS    0xb81fffff

// VFP/Neon coproc control commands
//
#define VFP_CONTROL_POWER_ON            1
#define VFP_CONTROL_POWER_OFF           2
#define VFP_CONTROL_POWER_RETENTION     3

#endif // ARM

//
// dwType field of PFN_SendIPI
//
#define IPI_TYPE_ALL_BUT_SELF           1       // send IPI to all but self
#define IPI_TYPE_ALL_INCLUDE_SELF       2       // send IPI to all, include self
#define IPI_TYPE_SPECIFIC_CPU           3       // send IPI to a specific CPU, dwTarget is the target CPU ID
//
// IPI are used to communicate between CPUs. kernel reserve the range from 0 - 0xfff. Platform specific 
// IPIs (trigger and handled in platform code) should use range above 0x1000.
//
#define OEM_FIRST_IPI_COMMAND           0x1000
#define IPI_TEST_CALL_FUNCTION_PTR      (OEM_FIRST_IPI_COMMAND -1) //For OAL IPI Test

// RAM attributes
#define     CE_RAM_CPU_LOCAL            0x00000001  // CPU Local RAM. Can be used by kernel for MP support
#define     CE_RAM_FAST                 0x00000002  // high perf RAM. Will only be allocated with special VirtualAlloc flag
#define     CE_RAM_CAN_TURN_OFF         0x00000004  // RAM that can be turn off. Kernel will avoid allocating from this RAM as much as possible

// put this in the 1st entry of OEMAddressTable to indicate new static mappng format
#define CE_NEW_MAPPING_TABLE            0x87654321

// alarm resolution
#define MIN_NKALARMRESOLUTION_MSEC      1000    // 1 second
#define MAX_NKALARMRESOLUTION_MSEC      60000   // 60 seconds
#define DEFAULT_ALARMRESOLUTION_MSEC    10000   // 10 seconds

// watchdog priority
#define DEFAULT_WATCHDOG_PRIORITY   100

// thread quantum
#define DEFAULT_THREAD_QUANTUM 100

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
typedef void (* PFN_HaltSystem) (void);

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

typedef BOOL  (*PFN_MpStartAllCPUs) (PLONG pnCpus, FARPROC pfnContinue);
typedef DWORD (*PFN_MpPerCPUInit) (void);
typedef BOOL  (*PFN_MpCpuPowerFunc) (DWORD dwProcessor, BOOL fOnOff, DWORD dwHint);
typedef void  (*PFN_OEMIdleEx) (LARGE_INTEGER *pliIdleTime);
typedef void  (*PFN_InitInterlockedFunc) (void);
typedef void  (*PFN_KdEnableTimer) (BOOL fEnable);

typedef void (*PFN_IpiHandler) (DWORD dwCommand, DWORD dwData);

typedef BOOL (*PFN_SendIPI) (DWORD dwType, DWORD dwTarget);

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
typedef BOOL (* PFN_HandleVFPException) (ULONG fpexc, EXCEPTION_RECORD* pExr, CONTEXT* pContext, DWORD* pdwReserved, BOOL fInKMode);
typedef BOOL (* PFN_IsVFPFeaturePresent) (DWORD dwProcessorFeature);
typedef BOOL (* PFN_VFPCoprocControl) (DWORD dwCommand);

DWORD OEMARMCacheMode (void);

typedef void (* PFN_PTEUpdateBarrier) (LPVOID pte, DWORD cbSize);

#endif

// RAM TABLE and Attributes
typedef struct {
    DWORD        ShiftedRamBase;     // starting physical address of RAM >> 8
    DWORD        RamSize;            // size of RAM, 32 bits, use more entries if >= 4G of RAM
    DWORD        RamAttributes;      // RAM Attributes, see below
} RAMTableEntry, *PRAMTableEntry;
typedef const RAMTableEntry *PCRAMTableEntry;

typedef struct {
    DWORD dwVersion;                // version of RAM TABLE, should set to MAKELONG (CE_MINOR_VER, CE_MAJOR_VER)
    DWORD dwNumEntries;             // Number of entries in this table
    PCRAMTableEntry pRamEntries;     // ptr to the table
} RamTable, *PRamTable;

typedef const RamTable *PCRamTable;

typedef PCRamTable (* PFN_GetOEMRamTable) (void);

struct _DeviceTableEntry {
    DWORD       VirtualAddress;         // statically mapped virtual address
    DWORD       ShiftedPhysicalAddress; // physical address >> 8
    DWORD       Size;                   // size of the mapping
    DWORD       Attributes;             // cache settings
};
typedef struct _DeviceTableEntry DeviceTableEntry, *PDeviceTableEntry;

//
// OEMGlobal: the OAL's interface to the kernel and KITL
//
// Required functions also note their default function pointer initialization.
// Optional functions note their default function pointer initialization when
// applicable.
//
typedef struct _OEMGLOBAL {
    DWORD                   dwVersion;

    // initialization
    PFN_InitDebugSerial     pfnInitDebugSerial;            // required: OEMInitDebugSerial
    PFN_InitPlatform        pfnInitPlatform;               // required: OEMInit

    // debug functions
    PFN_WriteDebugByte      pfnWriteDebugByte;             // required: OEMWriteDebugByte
    PFN_WriteDebugString    pfnWriteDebugString;           // required: OEMWriteDebugString
    PFN_ReadDebugByte       pfnReadDebugByte;              // optional: OEMReadDebugByte
    PFN_WriteDebugLED       pfnWriteDebugLED;              // optional

    // cache fuctions
    PFN_CacheRangeFlush     pfnCacheRangeFlush;            // required: OEMCacheRangeFlush

    // time related funcitons
    PFN_InitClock           pfnInitClock;                  // optional
    PFN_GetRealTime         pfnGetRealTime;                // required: OEMGetRealTime
    PFN_SetRealTime         pfnSetRealTime;                // required: OEMSetRealTime
    PFN_SetAlarmTime        pfnSetAlarmTime;               // required: OEMSetAlarmTime
    PFN_QueryPerfCounter    pfnQueryPerfCounter;           // optional
    PFN_QueryPerfFreq       pfnQueryPerfFreq;              // optional
    PFN_GetTickCount        pfnGetTickCount;               // required: OEMGetTickCount

    // scheduler related functions
    PFN_Idle                pfnIdle;                       // required: OEMIdle
    PFN_NotifyThreadExit    pfnNotifyThreadExit;           // optional
    PFN_NotifyReschedule    pfnNotifyReschedule;           // optional
    PFN_NotifyIntrOccurs    pfnNotifyIntrOccurs;           // optional
    PFN_UpdateReschedTime   pfnUpdateReschedTime;          // optional
    DWORD                   dwDefaultThreadQuantum;

    // power related functions
    PFN_PowerOff            pfnPowerOff;                   // required: OEMPowerOff

    // DRAM detection functions
    PFN_GetOEMRamTable      pfnGetOEMRamTable;             // optional
    PFN_GetExtensionDRAM    pfnGetExtensionDRAM;           // required: OEMGetExtensionDRAM
    PFN_EnumExtensionDRAM   pfnEnumExtensionDRAM;          // optional
    PFN_CalcFSPages         pfnCalcFSPages;                // optional
    DWORD                   dwMainMemoryEndAddress;

    // interrupt handling functions
    PFN_InterruptEnable     pfnInterruptEnable;            // required: OEMInterruptEnable
    PFN_InterruptDisable    pfnInterruptDisable;           // required: OEMInterruptDisable
    PFN_InterruptDone       pfnInterruptDone;              // required: OEMInterruptDone
    PFN_InterruptMask       pfnInterruptMask;              // required: OEMInterruptMask
    
    // co-proc support
    PFN_InitCoProcRegs      pfnInitCoProcRegs;             // optional
    PFN_SaveCoProcRegs      pfnSaveCoProcRegs;             // optional
    PFN_RestoreCoProcRegs   pfnRestoreCoProcRegs;          // optional
    DWORD                   cbCoProcRegSize;
    DWORD                   fSaveCoProcReg;

    // persistent registry support
    PFN_ReadRegistry        pfnReadRegistry;               // optional
    PFN_WriteRegistry       pfnWriteRegistry;              // optional

    // watchdog support
    PFN_RefreshWatchDog     pfnRefreshWatchDog;            // optional
    DWORD                   dwWatchDogPeriod;
    DWORD                   dwWatchDogThreadPriority;

    // profiler support
    PFN_ProfileTimerEnable  pfnProfileTimerEnable;         // optional
    PFN_ProfileTimerDisable pfnProfileTimerDisable;        // optional

    // Simple RAM based Error Reporting support
    DWORD                   cbErrReportSize;
    
    // others
    PFN_Ioctl               pfnOEMIoctl;                   // required: OEMIoControl
    PFN_KDIoctl             pfnKDIoctl;                    // optional
    PFN_IsRom               pfnIsRom;                      // optional
    PFN_MapW32Priority      pfnMapW32Priority;             // optional
    PFN_SetMemoryAttributes pfnSetMemoryAttributes;        // optional
    PFN_IsProcessorFeaturePresent   pfnIsProcessorFeaturePresent; // optional
    PFN_HaltSystem          pfnHaltSystem;                 // optional
    PFN_NotifyForceCleanBoot pfnNotifyForceCleanBoot;      // optional
    
    PROMChain_t             pROMChain;

    // Platform specific information passed from OAL to KITL.
    LPVOID                  pKitlInfo;
    PFNVOID                 pfnKITLGlobalInit;             // optional

    DBGPARAM                *pdpCurSettings;

    // compiler /GS security cookie
    DWORD_PTR *             p__security_cookie;
    DWORD_PTR *             p__security_cookie_complement;

    // alarm resolution
    DWORD                   dwAlarmResolution;

    // rtc rollover support
    DWORD                   dwYearsRTCRollover;

    // platform specific flags
    DWORD                   dwPlatformFlags;

    // page pool parameters
    struct _NKPagePoolParameters *pPagePoolParam; 
    DWORD                   cpPageOutLow;                  // optional, start page out below this threshold
    DWORD                   cpPageOutHigh;                 // optional, stop page out above this threshold

    // reserved
    DWORD                   _reserved_[13];

    // reserved for CPU-dependent extensions
#if defined (x86)
    DWORD                   _reserved_plat_[16];
#elif defined (ARM)
    DWORD                   _reserved_plat_[14];

    PFN_PTEUpdateBarrier    pfnPTEUpdateBarrier;           // optional
    PFN_VFPCoprocControl    pfnVFPCoprocControl;           // optional
#elif defined (MIPS)
    DWORD                   _reserved_plat_[16];
#elif defined (SHx)
    DWORD                   _reserved_plat_[16];
#endif
    
    // MP support related
    BOOL                    fMPEnable;
    PFN_MpStartAllCPUs      pfnStartAllCpus;               // optional, required for MP
    PFN_MpPerCPUInit        pfnMpPerCPUInit;               // optional, required for MP
    PFN_MpCpuPowerFunc      pfnMpCpuPowerFunc;             // optional
    PFN_IpiHandler          pfnIpiHandler;                 // optional
    PFN_SendIPI             pfnSendIpi;                    // optional, required for MP
    PFN_OEMIdleEx           pfnIdleEx;                     // optional
    PFN_InitInterlockedFunc pfnInitInterlockedFunc;        // optional, required for MP
    PFN_KdEnableTimer       pfnKdEnableTimer;              // optional, required for MP

    // CPU-dependent fields start here
#if defined (x86)
    // CPU dependent functions
    PFN_NMIHandler          pfnNMIHandler;                 // required for x86: OEMNMIHandler

    // On x86, because each CPU has its own IDT, kernel needs to know whether to setup IDT entry
    // for only master CPU (regular interrupt), or on all CPUs (IPI). This member is to indicate
    // to kernel whether the vector needs to be setup across all CPUs.
    //
    DWORD                   dwIpiVector;
#elif defined (ARM)
    PFN_InterruptHandler    pfnInterruptHandler;           // required for ARM: OEMInterruptHandler
    PFNVOID                 pfnFIQHandler;                 // required for ARM: OEMInterruptHandlerFIQ
    
    DWORD                   dwARM1stLvlBits;
    DWORD                   dwARMCacheMode;
    DWORD                   f_V6_VIVT_ICache;

    // VFP callbacks
    PFN_SaveRestoreVFPCtrlRegs  pfnSaveVFPCtrlRegs;        // optional
    PFN_SaveRestoreVFPCtrlRegs  pfnRestoreVFPCtrlRegs;     // optional
    PFN_HandleVFPException      pfnHandleVFPExcp;          // optional
    PFN_IsVFPFeaturePresent     pfnIsVFPFeaturePresent;    // optional

    DWORD                   dwPageTableCacheBits;
    DWORD                   dwTTBRCacheBits;
#elif defined (MIPS)
    DWORD                   dwCoProcBits;
    DWORD                   dwOEMTLBLastIdx;
    DWORD                   dwArchFlagOverride;
    const BYTE *            pIntrPrio;
    const BYTE *            pIntrMask;
#elif defined (SHx)
    PFN_SHxNMIHandler       pfnNMIHandler;                 // required for SHx: OEMNMI
    DWORD                   dwSHxIntEventCodeLength;
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

#ifdef __cplusplus
}
#endif

#endif  // ASM_ONLY

#endif  // _OEM_GLOBAL_H_

