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
//------------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//  
//------------------------------------------------------------------------------
//
//  This module contains the function prototypes and constant, type and
//  structure definitions for the Windows CE profiling functionality.
//
//------------------------------------------------------------------------------
#ifndef _PROFILER_H_
#define _PROFILER_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(push)
#pragma warning(disable:4200) // nonstandard extensions warning on zero-size array
#pragma warning(disable:4201) // nonstandard extensions warning on unnamed struct/union


//------------------------------------------------------------------------------
//
// Control APIs exposed to applications
//
//------------------------------------------------------------------------------

// ProfileStartEx uses this structure
#pragma warning(push)
//Under Microsoft extensions (/Ze), you can specify a structure without 
//a declarator as members of another structure or union. These structures 
//generate W4 warning C4201. 
#pragma warning(disable:4201) 
typedef struct ProfilerControl {
    DWORD dwVersion;                // Version of this struct, set to 1
    DWORD dwOptions;                // PROFILE_* flags
    DWORD dwReserved;
    union {
        // Used to control the kernel profiler, if PROFILE_OEMDEFINED is not set
        struct {
            DWORD dwUSecInterval;   // Sampling interval
        } Kernel;
        
        // Used to control an OEM-defined profiler, if PROFILE_OEMDEFINED is set
        struct {
            DWORD dwProcessorType;  // Type of processor expected
            DWORD dwControlSize;    // Size of the OEM-defined data
            BYTE  bHardwareSpecificSettings[0]; // Followed by OEM-defined data
        } OEM;
    };
} ProfilerControl;
#pragma warning(pop)


//
// dwOptions to ProfileStart
//
#define PROFILE_OBJCALL          0x00000001  // record object calls
#define PROFILE_KCALL            0x00000002  // record kcalls
#define PROFILE_BUFFER           0x00000004  // record hits to buffer (cannot be used with PROFILE_CELOG)
#define PROFILE_PAUSE            0x00000008  // pause recording
#define PROFILE_CONTINUE         0x00000010  // resume recording
#define PROFILE_STARTPAUSED      0x00000020  // start in paused state
#define PROFILE_CELOG            0x00000040  // record hits via CeLog
#define PROFILE_OEMDEFINED       0x00000080  // control OEM-defined profiler
#define PROFILE_START            0x00000100  // start recording
#define PROFILE_STOP             0x00000200  // stop recording
#define PROFILE_OEM_QUERY        0x00000400  // query current OEM counters
// Record callstack with every hit (requires PROFILE_CELOG).
#define PROFILE_CALLSTACK        0x00000800
// When the INPROC flag is used with PROFILE_CALLSTACK, the profiler will record
// only the (bottom) part of the callstack that's within the thread's owner
// process, without crossing any PSL boundaries.  If the INPROC flag is not set,
// PROFILE_CALLSTACK will record the thread's entire callstack.
#define PROFILE_CALLSTACK_INPROC 0x00001000
#define PROFILE_TICK             0x00002000  // Using the kernel timer-tick interrupts to implement profiling


DWORD ProfileStart(DWORD dwUSecInterval, DWORD dwOptions);
DWORD ProfileStartEx(ProfilerControl *pControl);
VOID ProfileCaptureStatus();
void ProfileStop(void);


// IOCTL_HAL_OEM_PROFILER uses this struct to return hardware-specific profiling
// data on a query.  The OAL ISR uses it to pass data to ProfilerHitEx.
typedef struct OEMProfilerData {
    DWORD ra;           // Return address of profiling interrupt
    DWORD dwProcessId;  // ID of process that was running during the profiling interrupt
    DWORD dwBufSize;    // Size of the following data buffer, does not include this struct
    BYTE  buf[0];       // Followed by the buffer of data
} OEMProfilerData;


//------------------------------------------------------------------------------
//
// OEM-implemented profiler functions.
//
//------------------------------------------------------------------------------
void OEMProfileTimerDisable(void);
void OEMProfileTimerEnable(DWORD dwUSecInterval);


//------------------------------------------------------------------------------
//
// Kernel functions used by the OAL to send data to the kernel profiler
//
//------------------------------------------------------------------------------
// BUGBUG can't expose because it's declared in different places with different types!
//void ProfilerHit(unsigned int ra);
void ProfilerHitEx(OEMProfilerData *pData);  // BUGBUG NKProfilerHitEx?



//------------------------------------------------------------------------------
//
// CeLog profiler events
//
//------------------------------------------------------------------------------

// CELID_PROFILER_START
typedef ProfilerControl _CEL_PROFILER_START, CEL_PROFILER_START, *PCEL_PROFILER_START;

// CELID_PROFILER_STOP does not use a struct

// CELID_PROFILER_MARK
typedef struct {
    LARGE_INTEGER Timestamp;    // Optional timestamp: Lets the caller specify
                                // a timestamp other than the time it came to
                                // CeLog.  (Up to caller interpretation: May
                                // use a completely different clock frequency
                                // than CeLog does.)  Set to 0 if unused.
    long  Marker;               // The marker value
    WCHAR szComment[MAX_PATH];  // Optional comment string (length is inferred
                                // from entry length - between 0 and MAX_PATH)
} CEL_PROFILER_MARK, *PCEL_PROFILER_MARK;

// CELID_PROFILER_NAME is not currently used


// CELID_MONTECARLO_HIT
typedef struct _CEL_MONTECARLO_HIT {
    DWORD dwReturnAddr;
    DWORD dwProcessId;
} CEL_MONTECARLO_HIT, *PCEL_MONTECARLO_HIT;

// CELID_OEMPROFILER_HIT uses OEMProfilerData struct

// CELID_APP_PROFILER_HIT
typedef struct _CEL_APP_PROFILER_HIT {
    DWORD ThreadId;
} CEL_APP_PROFILER_HIT, *PCEL_APP_PROFILER_HIT;


// Flag bitmask used in CELID_CAP_OVERHEAD
#define CAP_OVERHEAD_END    0x00000001  // Omit for start of measurement, set for end
#define CAP_OVERHEAD_KERNEL 0x00000002  // Omit for user mode, set for kernel mode

// CELID_CAP_OVERHEAD
typedef struct {
    DWORD Flags;                // CAP_OVERHEAD_* flag
    WORD  CallType;             // Which call type is being measured: Will be set to CELID_*
    WORD  SampleCount;          // How many call-time samples are being gathered
    LARGE_INTEGER Counters[0];  // Followed by an optional set of 64-bit signed counter values, the number to be determined by event size.  Usually omitted.
} CEL_CAP_OVERHEAD, *PCEL_CAP_OVERHEAD;

// CELID_CALLCAP_ENTER
typedef struct {
    DWORD ThreadId;             // The thread that is running
    DWORD ProcessId;            // The process that the thread is running inside (that ProcAddress falls inside)
    DWORD ProcAddress;          // The function that is being entered
    DWORD StackTop;             // The thread's call stack position
    LARGE_INTEGER Counters[0];  // Followed by an optional set of 64-bit signed counter values, the number to be determined by event size.  Usually omitted.
} CEL_CALLCAP_ENTER, *PCEL_CALLCAP_ENTER;

// CELID_CALLCAP_EXIT
typedef struct {
    DWORD ThreadId;             // The thread that is running
    DWORD ProcessId;            // The process that the thread is running inside (that ProcAddress falls inside)
    DWORD ProcAddress;          // The function that is being entered
    DWORD StackTop;             // The thread's call stack position
    LARGE_INTEGER Counters[0];  // Followed by an optional set of 64-bit signed counter values, the number to be determined by event size.  Usually omitted.
} CEL_CALLCAP_EXIT, *PCEL_CALLCAP_EXIT;

// CELID_FASTCAP_ENTER
typedef struct {
    DWORD ThreadId;             // The thread that is running
    DWORD ProcessId;            // The process that the thread is running inside (that ProcAddress falls inside)
    DWORD ProcAddress;          // The function that is making the call (caller)
    DWORD TargetAddress;        // The function that is being called (callee)
    DWORD StackTop;             // The thread's call stack position
    LARGE_INTEGER Counters[0];  // Followed by an optional set of 64-bit signed counter values, the number to be determined by event size.  Usually omitted.
} CEL_FASTCAP_ENTER, *PCEL_FASTCAP_ENTER;

// CELID_FASTCAP_EXIT
typedef struct {
    DWORD ThreadId;             // The thread that is running
    DWORD ProcessId;            // The process that the thread is running inside (that ProcAddress falls inside)
    DWORD ProcAddress;          // The function that is being entered
    DWORD StackTop;             // The thread's call stack position
    LARGE_INTEGER Counters[0];  // Followed by an optional set of 64-bit signed counter values, the number to be determined by event size.  Usually omitted.
} CEL_FASTCAP_EXIT, *PCEL_FASTCAP_EXIT;


//------------------------------------------------------------------------------
//
// CeLog events for the file cache
//
//------------------------------------------------------------------------------

// CELID_CACHE_ALLOCVIEW, CELID_CACHE_FREEVIEW, CELID_CACHE_FLUSHVIEW
typedef struct {
    ULARGE_INTEGER liMapOffset;
    DWORD   MapId;
    LPBYTE  pBaseAddr;
    DWORD   cbSize;
    DWORD   dwDirty;
} CEL_CACHEVIEW;


#pragma warning(pop)  // nonstandard extensions warnings


#ifdef __cplusplus
}
#endif


#endif // _PROFILER_H_
