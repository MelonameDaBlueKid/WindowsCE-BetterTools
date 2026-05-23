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
//      ceperf_log.h
//  
//  Abstract:  
//
//      Windows CE Performance Measurement API log file output format.
//      
//------------------------------------------------------------------------------


#ifndef _CEPERF_LOG_H_
#define _CEPERF_LOG_H_

#ifdef __cplusplus 
extern "C" { 
#endif 


//==============================================================================
// CELOG EVENTS
//==============================================================================

// All events are logged to CeLog using CELID_CEPERF and CELZONE_ALWAYSON.
// Whether we log to CeLog or not is controlled by the session settings
// (CEPERF_STORE_CELOG).

// The event format is: the CeLog header is followed by a DWORD CePerf event ID
// (one of the values in the following list) and then by the event data defined
// for that ID.
typedef enum {
//    CEPERF_LOGID_CPU_DESCRIPTOR          =  0,  // Reserved for future use
//    CEPERF_LOGID_CPU_CONTROL             =  1,  // Reserved for future use
//    CEPERF_LOGID_SESSION_CREATE          =  2,  // Reserved for future use
    CEPERF_LOGID_SESSION_DESCRIPTOR      =  3,  // CEPERF_LOG_SESSION_DESCRIPTOR struct
//    CEPERF_LOGID_SESSION_DESTROY         =  4,  // Reserved for future use
//    CEPERF_LOGID_SESSION_CONTROL         =  5,  // Reserved for future use
//    CEPERF_LOGID_ITEM_CREATE             =  6,  // Reserved for future use
    CEPERF_LOGID_ITEM_DESCRIPTOR         =  7,  // CEPERF_LOG_ITEM_DESCRIPTOR struct
//    CEPERF_LOGID_ITEM_DESTROY            =  8,  // Reserved for future use
    CEPERF_LOGID_DURATION_DISCRETE       =  9,  // CEPERF_LOG_DURATION_DISCRETE struct
    CEPERF_LOGID_DURATION_BEGIN          = 10,  // CEPERF_LOG_DURATION_FULL struct
    CEPERF_LOGID_DURATION_INTERMEDIATE   = 11,  // CEPERF_LOG_DURATION_FULL struct
    CEPERF_LOGID_DURATION_END            = 12,  // CEPERF_LOG_DURATION_FULL struct
    CEPERF_LOGID_STATISTIC_DISCRETE      = 13,  // CEPERF_LOG_STATISTIC_DISCRETE struct
    CEPERF_LOGID_STATISTIC_FULL          = 14,  // CEPERF_LOG_STATISTIC_FULL struct
    CEPERF_LOGID_LOCALSTATISTIC_DISCRETE = 15,  // CEPERF_LOG_LOCALSTATISTIC_DISCRETE struct
} CEPERF_LOGID;

// These values correspond to the information passed to CePerfOpenSession unless
// otherwise noted
typedef struct {
    DWORD  dwSessionID;         // System-wide ID for this session
    DWORD  dwStatusFlags;
    DWORD  dwStorageFlags;
    DWORD  rgdwRecordingFlags[CEPERF_NUMBER_OF_TYPES];
    // Followed by 2 strings: the session path (name) and storage path
    // (output file).  Both should be NULL terminated and max MAX_PATH.
} CEPERF_LOG_SESSION_DESCRIPTOR;

typedef CEPERF_LOG_SESSION_DESCRIPTOR CEPERF_LOG_SESSION_CREATE;

typedef struct {
    DWORD  dwSessionID;         // System-wide ID for this session
} CEPERF_LOG_SESSION_DESTROY;

typedef struct {
    DWORD  dwSessionID;         // System-wide ID for this session
    DWORD  dwControlFlags;
    DWORD  dwStatusFlags;
    DWORD  dwStorageFlags;
    DWORD  rgdwRecordingFlags[CEPERF_NUMBER_OF_TYPES];
    // Followed by 2 strings: the session path (name) and storage path
    // (output file).  Both should be NULL terminated and max MAX_PATH.
} CEPERF_LOG_SESSION_CONTROL;

// These values correspond to the information passed to CePerfRegisterTrackedItem
// unless otherwise noted
typedef struct {
    DWORD  dwItemID;            // System-wide ID for this item
    CEPERF_ITEM_TYPE type;
    DWORD  dwRecordingFlags;    // Flags for default recording mode (may be
                                // overridden by session defaults or dynamic
                                // session control)
    CEPERF_EXT_ITEM_DESCRIPTOR ext;
    // Followed by 1 string: the name of the item.  It should be NULL
    // terminated, and max CEPERF_MAX_ITEM_NAME_LEN.
} CEPERF_LOG_ITEM_DESCRIPTOR;

// Used to track and report discrete data for a Duration, and change data for a
// Statistic item in short-record mode; useful for time plus other data like
// CPU perf counters.  Even though counters may vary in size from 1 to 8 bytes,
// we only use 8-byte values, to minimize overflow issues.
typedef struct _CEPERF_DISCRETE_COUNTER_DATA {
    ULARGE_INTEGER ulTotal;     // Divide by number of values to get average value
                                // (Number of values is not stored in this struct)
    ULARGE_INTEGER ulMinVal;
    ULARGE_INTEGER ulMaxVal;
    double         dStdDev;     // Standard deviation
} CEPERF_DISCRETE_COUNTER_DATA;

// Min-record data from a duration (min/max/avg, etc)
typedef struct {
    DWORD dwItemID;             // System-wide ID for this item
    DWORD dwNumVals;
    DWORD dwErrorCount;         // Timing errors, mismatched begin/end, etc.
    // Followed by array of CEPERF_DISCRETE_COUNTER_DATA structs
    // for perf count, tick count, plus each CPU perf counter
} CEPERF_LOG_DURATION_DISCRETE;

// Full-record data from a duration
typedef struct {
    DWORD dwItemID;             // System-wide ID for this item
    HRESULT hResult;            // Did the Begin/Intermediate/End operation succeed?
    // Followed by array of counters for each CPU perf counter.
    // PerfCount/TickCount are not logged, since the CeLog timestamp is good enough.
} CEPERF_LOG_DURATION_FULL;

typedef struct {
    DWORD dwItemID;             // System-wide ID for this item
    DWORD dwNumChanges;
    ULARGE_INTEGER ulValue;
    // Followed by one CEPERF_DISCRETE_COUNTER_DATA struct if in short-record mode
} CEPERF_LOG_STATISTIC_DISCRETE;

// Full-record data from a statistic
typedef struct {
    DWORD dwItemID;             // System-wide ID for this item
    ULARGE_INTEGER ulValue;     // New value
} CEPERF_LOG_STATISTIC_FULL;

typedef struct {
    DWORD dwItemID;             // System-wide ID for this item
    // Followed by up to 8 bytes of data
} CEPERF_LOG_LOCALSTATISTIC_DISCRETE;


#ifdef __cplusplus 
}
#endif 

#endif // _CEPERF_LOG_H_

