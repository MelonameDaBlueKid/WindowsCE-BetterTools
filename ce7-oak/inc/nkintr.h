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

nkintr.h

Abstract:  

This file contains the data structures, macros and function prototypes
used by the NK interrupt support and by firmware to register device
interrupt information with the kernel.

Notes: 


--*/
#ifndef NKINTR_INC
#define NKINTR_INC

#ifdef __cplusplus
extern "C" {
#endif


/*
    @doc    EXTERNAL KERNEL HAL
    @type   Interrupt ID's | Interrupt id's defined in the system
    @comm   The kernel defines several well known interrupt ID's, which are 
        used by the standard system software. It also defines a range of ID's 
        which OEM's can use to define any custom platform specific interrupt 
        ID's which only their installed device drivers understand. These 
        interrupt ID's are passed in as parameters to a lot of the interrupt 
        support functions  - see the cross reference section for the entire
        list. The reason for defining these ID's to is isolate the kernel from 
        knowing about platform specific hardware interrupt numbers - the mapping 
        from hardware interrupt numbers to these well known InterruptID's is 
        done by the OEM specific ISR's.

    Predefined system values are:<nl>
    @flag SYSINTR_NOP    | When returned from the ISR, this value causes the
        kernel to complete processing of the exception handler without doing
        anything else.
    @flag SYSINTR_RESCHED | When returned from an ISR, this causes the kernel
        to go into the reschedule routine. Typically used to signal that 
        a scheduler timer event just went off.
    @flag SYSINTR_BREAK | Should be returned from an ISR when the halt button
        has been depressed.
    @flag SYSINTR_KEYBOARD    | Keyboard driver interrupt
    @flag SYSINTR_TOUCH       | Touch panel interrupt
    @flag SYSINTR_ADC         | ADC
    @flag SYSINTR_POWER       | Power
    @flag SYSINTR_SERIAL      | Serial port
    @flag SYSINTR_AUDIO       | Audio
    @flag SYSINTR_RADIO       | Radio
    @flag SYSINTR_PARALLEL    | Parallel Port
    @flag SYSINTR_TOUCH_CHANGED   | Touch panel changed interrupt
    @flag SYSINTR_OEMBASE    | Beyond this OEM's can define custom ID's
    @flag SYSINTR_MAXIMUM     | End of valid ID's

    @xref  <l Overview.Kernel Interrupt Support> <f InterruptInitialize> 
    <f InterruptDone> <f InterruptDisable> <f OEMInterruptDone>
    <f OEMInterruptDisable> <f OEMInterruptEnable>
*/

#define SYSINTR_UNDEFINED  (-1) // SysIntr not defined for IRQ <-> SYSINTR mapping 

#define SYSINTR_NOP         0   /* no processing required */
#define SYSINTR_RESCHED     1   /* set "reschedule flag" */
#define SYSINTR_BREAK       2   /* break into debugger */
#define SYSINTR_CHAIN       3   /* continue to next handler */
#define SYSINTR_IPI         4   /* interprocess interrupt */


// SYSINTR_DEVICES is the base for any non-OAL system interrupts
#define SYSINTR_DEVICES     8

#define SYSINTR_PROFILE             (SYSINTR_DEVICES+1)     // System Profiling
#define SYSINTR_TIMING              (SYSINTR_DEVICES+2)     // Latency Analysis
#define SYSINTR_IST_BGT             (SYSINTR_DEVICES+3)     // Backgroud IST thread for unknown IRQ handling.
#define SYSINTR_RTC_ALARM           (SYSINTR_DEVICES+5)  // real-time clock alarm
#define SYSINTR_NETWORK_SHARED      (SYSINTR_DEVICES+6)     // Combined interrupts for network
#define SYSINTR_VMINI               (SYSINTR_DEVICES+7)     // VMini RX interrupt.

// SYSINTR_FIRMWARE is the base for any interrupts defined in the OAL
#define SYSINTR_FIRMWARE    (SYSINTR_DEVICES+8)

#define SYSINTR_MAX_DEVICES 64
#define SYSINTR_MAXIMUM     (SYSINTR_DEVICES+SYSINTR_MAX_DEVICES)

/*

    Wake source IDs are used as parameters to kernel IOCTLs, including:
        - IOCTL_HAL_ENABLE_WAKE
        - IOCTL_HAL_DISABLE_WAKE
        - IOCTL_HAL_GET_WAKE_SOURCE
    Wake source IDs may be SysIntr values, Microsoft-defined reserved values,
    or OEM-defined values.  ID ranges are:

    1 - (SYSWAKE_BASE - 1): The interrupt associated with a SysIntr is the 
    wake source. In practice these will never exceed
        SYSINTR_MAXIMUM.
        SYSWAKE_BASE - (SYSWAKE_OEMBASE - 1): Microsoft-defined wake source IDs.
        Unused values in this range are reserved for future 
        use.
        SYSWAKE_OEMBASE - (SYSWAKE_MAXIMUM - 1): OEM-defined wake source IDs.  These 
        wake sources are platform specific.

    The kernel will return SYSWAKE_UNKNOWN if it cannot determine why the system
    resumed from suspend.
*/

// wake source ranges
#define SYSWAKE_BASE            1024 
#define SYSWAKE_OEMBASE         2048
#define SYSWAKE_MAXIMUM         4096

// kernel returns this value if it doesn't know why the system resumed
#define SYSWAKE_UNKNOWN         ((DWORD) (-1))

// MS-defined wake sources
#define SYSWAKE_DEPRECATED      (SYSWAKE_BASE + 0)
#define SYSWAKE_RING_INDICATE   (SYSWAKE_BASE + 1)  // ring indicate on any uart 
#define SYSWAKE_WAKE_ON_LAN     (SYSWAKE_BASE + 2)  // wake-on-lan from any network device 
#define SYSWAKE_POWER_BUTTON    (SYSWAKE_BASE + 3)  // primary suspend/resume button pressed

#define OEM_DEBUG_READ_NODATA   (-1)
#define OEM_DEBUG_COM_ERROR     (-2)

#ifndef ASM_ONLY

/* kernel exports */
extern BOOL NKIsSysIntrValid (DWORD idInt);
extern BOOL NKSetInterruptEvent (DWORD idInt);
extern void INTERRUPTS_ON(void);
extern void INTERRUPTS_OFF(void);
extern BOOL INTERRUPTS_ENABLE(BOOL fEnable);


/** OEM supplied functions */
extern void OEMInit(void);
extern BOOL OEMInterruptEnable(DWORD idInt, LPVOID pvData, DWORD cbData);
extern void OEMInterruptDisable(DWORD idInt);
extern void OEMInterruptDone(DWORD idInt);
extern void OEMInterruptMask (DWORD idInt, BOOL fDisable);
extern BOOL OEMGetRealTime(LPSYSTEMTIME lpst);
extern BOOL OEMSetRealTime(LPSYSTEMTIME lpst);
extern BOOL OEMSetAlarmTime(LPSYSTEMTIME lpst);
extern void OEMPowerOff(void);
extern void OEMCacheRangeFlush (LPVOID pAddr, DWORD dwLength, DWORD dwFlags);
extern void OEMIdle (DWORD idleParam);
extern BOOL OEMGetExtensionDRAM (LPDWORD pMemoryStart, LPDWORD pMemoryLength);
extern BOOL OEMIoControl (DWORD code, VOID * pInBuffer, DWORD inSize, VOID * pOutBuffer, DWORD outSize, DWORD * pOutSize);


/** OEM supplied debug support functions */
extern void OEMInitDebugSerial(void);
extern void OEMWriteDebugString(unsigned short *str);
extern void OEMWriteDebugLED(WORD wIndex, DWORD dwPattern);
extern int OEMReadDebugByte(void);
extern void OEMWriteDebugByte(BYTE ch);
extern void OEMClearDebugCommError(void);
extern int OEMParallelPortGetByte(void);
extern void OEMParallelPortSendByte(BYTE ch);

/** CoreDll functions exported to OEM Drivers (not HAL) */
BOOL SetInterruptEvent(DWORD idInt);
BOOL CeSetPowerOnEvent (HANDLE hEvt);     // used to set event in power handler

#endif

#ifdef __cplusplus
}
#endif

#endif

