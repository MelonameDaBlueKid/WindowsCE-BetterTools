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
//  Module Name:  
//  
//      ceperf_cpu.h
//  
//  Abstract:  
//
//      Per-CPU hooks for Windows CE Performance Measurement API
//      
//------------------------------------------------------------------------------


#ifndef _CEPERF_CPU_H_
#define _CEPERF_CPU_H_

#ifdef __cplusplus 
extern "C" { 
#endif 


#ifndef CEPERF_DISABLE

// Limitations on CPU performance counters
#define CEPERF_MAX_CPUCOUNTER_COUNT (16)             // Max number of counters that can be tracked
#define CEPERF_MAX_CPUCOUNTER_SIZE  ((1 << 8) - 1)   // Max size of each counter, in bytes
#define CEPERF_MAX_CPUCOUNTER_TOTAL (64)             // Max total size of all counters, in bytes


//------------------------------------------------------------------------------
// CPUCounterDescriptor -- A description of the data structure currently being
// used to hold CPU data.  The CePerf engine needs to understand the contents
// of the structure so that it can calculate differences as well as statistics
// like min/max/avg for each data member.  The descriptor is an array of DWORDs:
// the first is the number of struct members, the rest are an array of sizes
// (in bytes) for each struct member.
//    
// For example, if the CPU counter data is currently being tracked in this struct:
//     struct {
//         LARGE_INTEGER liData1;
//         DWORD dwData2;
//         WORD wData3;
//     }
// then the corresponding data descriptor would be:
//     pCPUCounterDescriptor[0] = 3;
//     pCPUCounterDescriptor[1] = sizeof(LARGE_INTEGER);
//     pCPUCounterDescriptor[2] = sizeof(DWORD);
//     pCPUCounterDescriptor[3] = sizeof(WORD);
//
// The maximum number of counters is CEPERF_MAX_CPUCOUNTER_COUNT, so the
// descriptor cannot have more than CEPERF_MAX_CPUCOUNTER_COUNT + 1 entries.
// Each individual counter cannot exceed CEPERF_MAX_CPUCOUNTER_SIZE in size.
// The maximum total CPU counter data struct size is CEPERF_MAX_CPUCOUNTER_TOTAL.
// The sum of the sizes in the descriptor array cannot exceed that.
//
// The CePerf engine assumes that struct members are aligned on their natural
// boundaries so you should take care to maintain proper alignment.  You can
// assume that the beginning of the counter data is aligned on a LARGE_INTEGER
// (8-byte) boundary.
//
// The descriptor will be queried after each successful call to
// pCPUControlPerfCounters() and will be replicated globally.  The contents of
// the descriptor will be ignored at all other times.
//------------------------------------------------------------------------------

extern DWORD* pCPUCounterDescriptor;


//------------------------------------------------------------------------------
// CPUControlPerfCounters -- Enable and disable CPU performance counters.
// Does the real work behind the CePerfControlCPU API.  There are no guarantees
// whether or not the counter values will be reset to 0 following this call.
// This call should succeed if the new settings are the same as the old.
// On any failure case, the CPU counters are expected to keep the same settings.
//------------------------------------------------------------------------------

// Pointer to control function for this CPU
extern
HRESULT (*pCPUControlPerfCounters) (
    DWORD  dwOptions,           // CEPERF_CPU_* flags
    LPVOID lpCPUControlStruct,  // Control structure defined for the current CPU
    DWORD  dwCPUControlSize     // Size of control structure
    );


//------------------------------------------------------------------------------
// CPUQueryPerfCounters -- Query current CPU performance counters.
// Called by CePerf APIs to gather performance data.
//------------------------------------------------------------------------------

// Pointer to query function for this CPU
extern
HRESULT (*pCPUQueryPerfCounters) (
    LPVOID lpCPUDataStruct,     // Data structure defined for the current CPU
    DWORD  dwCPUDataSize        // Size of data structure
    );


#endif // CEPERF_DISABLE


#ifdef __cplusplus 
}
#endif 

#endif // _CEPERF_CPU_H_

