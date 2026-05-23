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


//-------------------------------------------------------
// This header is present on every event in the log.
//-------------------------------------------------------

typedef struct  _CEPERF_LOGEVENT_HEADER {
    BYTE bID;           // Event ID
    BYTE bReserved;     // Unused -- will be 0
    WORD wSize;         // Size of data following the header, in bytes
} CEPERF_LOGEVENT_HEADER;


//-------------------------------------------------------
// EVENT LOG IDs
//-------------------------------------------------------

#define CEPERF_LOGID_STREAM_INFO                ((BYTE)0x01)

#define CEPERF_LOGID_SESSION_DESCRIPTOR         ((BYTE)0x10)
#define CEPERF_LOGID_SESSION_OPEN               ((BYTE)0x12)
#define CEPERF_LOGID_SESSION_CLOSE              ((BYTE)0x14)
#define CEPERF_LOGID_SESSION_FLUSH_BEGIN        ((BYTE)0x16)
#define CEPERF_LOGID_SESSION_FLUSH_END          ((BYTE)0x17)
#define CEPERF_LOGID_SESSION_CONTROL            ((BYTE)0x18)

#define CEPERF_LOGID_ITEM_DESCRIPTOR            ((BYTE)0x20)
#define CEPERF_LOGID_ITEM_OPEN                  ((BYTE)0x22)
#define CEPERF_LOGID_ITEM_CLOSE                 ((BYTE)0x24)

#define CEPERF_LOGID_DURATION_DISCRETE          ((BYTE)0x30)
#define CEPERF_LOGID_DURATION_BEGIN             ((BYTE)0x32)
#define CEPERF_LOGID_DURATION_BEGIN_INFO        (CEPERF_LOGID_DURATION_BEGIN+1)
#define CEPERF_LOGID_DURATION_INTERMEDIATE      ((BYTE)0x34)
#define CEPERF_LOGID_DURATION_INTERMEDIATE_INFO (CEPERF_LOGID_DURATION_INTERMEDIATE+1)
#define CEPERF_LOGID_DURATION_END               ((BYTE)0x35)
#define CEPERF_LOGID_DURATION_END_INFO          (CEPERF_LOGID_DURATION_END+1)

#define CEPERF_LOGID_STATISTIC_DISCRETE         ((BYTE)0x40)
#define CEPERF_LOGID_STATISTIC_ADD              ((BYTE)0x42)
#define CEPERF_LOGID_STATISTIC_SET              ((BYTE)0x44)

#define CEPERF_LOGID_LOCALSTATISTIC_DISCRETE    ((BYTE)0x50)

#define CEPERF_LOGID_CPU_DESCRIPTOR             ((BYTE)0x60)
#define CEPERF_LOGID_CPU_CONTROL                ((BYTE)0x61)


//-------------------------------------------------------
// LOG DATA STRUCTURES FOR SPECIAL DATA STREAM EVENTS
//-------------------------------------------------------

// Housekeeping information, for interpreting the log

#define CEPERF_LOG_VERSION 1    // Version # for the data stream

typedef struct  _CEPERF_LOGDATA_STREAM_INFO {
    CEPERF_LOGEVENT_HEADER header;
    WORD  wLogVersion;          // CEPERF_LOG_VERSION from the DLL that
                                // generated the data
    WORD  wReserved;            // Unused
    DWORD dwPerfFreqLow;        // QueryPerformanceFrequency -> LowPart
    DWORD dwPerfFreqHigh;       // QueryPerformanceFrequency -> HighPart
    DWORD dwBytesLost;          // Number of bytes of data that could were lost
                                // instead of being written to the storage 
                                // location, due to overflow.
} CEPERF_LOGDATA_STREAM_INFO;


//-------------------------------------------------------
// LOG DATA STRUCTURES FOR SESSION EVENTS
//-------------------------------------------------------

typedef struct  _CEPERF_LOGDATA_SESSION_DESCRIPTOR {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_SESSION_DESCRIPTOR;

typedef struct _CEPERF_LOGDATA_SESSION_OPEN {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_SESSION_OPEN;

typedef struct _CEPERF_LOGDATA_SESSION_CLOSE {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_SESSION_CLOSE;

typedef struct _CEPERF_LOGDATA_SESSION_FLUSH_BEGIN {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_SESSION_FLUSH_BEGIN;

typedef struct _CEPERF_LOGDATA_SESSION_FLUSH_END {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_SESSION_FLUSH_END;

typedef struct _CEPERF_LOGDATA_SESSION_CONTROL {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_SESSION_CONTROL;


//-------------------------------------------------------
// LOG DATA STRUCTURES FOR TRACKED ITEM EVENTS
//-------------------------------------------------------

typedef struct _CEPERF_LOGDATA_ITEM_DESCRIPTOR {
    CEPERF_LOGEVENT_HEADER header;
    HANDLE hTrackedItem;        // Handle of tracked item
    CEPERF_ITEM_TYPE type;      // Type of item
    DWORD  dwRecordingFlags;    // Current recording mode
    // Followed by name of item
} CEPERF_LOGDATA_ITEM_DESCRIPTOR;

typedef struct _CEPERF_LOGDATA_ITEM_OPEN {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_ITEM_OPEN;

typedef struct _CEPERF_LOGDATA_ITEM_CLOSE {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_ITEM_CLOSE;


// Discrete data from Duration item
typedef struct _CEPERF_LOGDATA_DURATION_DISCRETE {
    CEPERF_LOGEVENT_HEADER header;
    HANDLE hTrackedItem;        // Handle of Duration item
    DWORD  dwCount;             // Number of valid begin/end pairs recorded
    DWORD  dwErrorCount;        // Number of errors recorded
    // Followed by array of CEPERF_DISCRETE_COUNTER_DATA structs, based on
    // recording flags for this item.  The counter data will be in the following
    // order:
    // 1.  Performance counter delta between begin/end, if recorded
    // 2.  Tick count delta between begin/end, if recorded
    // 3.  Array of CPU performance counter deltas between begin/end, if recorded.
    //     The counters are based on the current CPU settings.  See the
    //     definitions for the specific CPU for more details.
} CEPERF_LOGDATA_DURATION_DISCRETE;

// Continuous data (CePerfBeginDuration / CePerfIntermediateDuration /
// CePerfEndDuration / CePerfEndDurationWithInformation call)
typedef struct _CEPERF_LOGDATA_DURATION_CONTINUOUS {
    CEPERF_LOGEVENT_HEADER header;
    HANDLE hTrackedItem;        // Handle of Duration item
    DWORD  dwCount;             // Number of valid begin/end pairs recorded
    CEPERF_ITEM_DATA data;      // For a Begin item, the absolute values of all
                                // counters; for an Intermediate/End item, the
                                // counter diff since the Begin
    // Followed by CPU counter deltas, see CEPERF_ITEM_DATA for more info.
} CEPERF_LOGDATA_DURATION_CONTINUOUS;

// Extra information for continuous data: error code for any Duration call or
// error/info from CePerfEndDurationWithInformation call.
typedef struct _CEPERF_LOGDATA_DURATION_CONTINUOUS_INFO {
    CEPERF_LOGEVENT_HEADER header;
    HANDLE hTrackedItem;        // Handle of Duration item
    DWORD  dwErrorCode;         // Error code for the aborted Duration call, or 0 for no error
    DWORD  dwErrorCount;        // Number of errors recorded
    // Possibly followed by additional data buffer.
} CEPERF_LOGDATA_DURATION_CONTINUOUS_INFO;


// Discrete data from Statistic item
typedef struct _CEPERF_LOGDATA_STATISTIC_DISCRETE {
    CEPERF_LOGEVENT_HEADER header;
    HANDLE hTrackedItem;        // Handle of Statistic item
    ULARGE_INTEGER ulValue;     // Current value
    // Followed by a DWORD and a CEPERF_DISCRETE_COUNTER_DATA struct, if the
    // Statistic is in short-record mode.  The DWORD is the number of times the
    // Statistic was changed, and the CEPERF_DISCRETE_COUNTER_DATA is the data
    // about those changes.
} CEPERF_LOGDATA_STATISTIC_DISCRETE;

// Continuous data (CePerfIncrementStatistic/CePerfAddStatistic call)
typedef struct _CEPERF_LOGDATA_STATISTIC_ADD {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_STATISTIC_ADD;

// Continuous data (CePerfSetStatistic call)
typedef struct _CEPERF_LOGDATA_STATISTIC_SET {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_STATISTIC_SET;


// Discrete data from LocalStatistic item
typedef struct _CEPERF_LOGDATA_LOCALSTATISTIC_DISCRETE {
    CEPERF_LOGEVENT_HEADER header;
    HANDLE hTrackedItem;        // Handle of LocalStatistic item
    // Followed by the buffer of data
} CEPERF_LOGDATA_LOCALSTATISTIC_DISCRETE;


//-------------------------------------------------------
// LOG DATA STRUCTURES FOR CPU EVENTS
//-------------------------------------------------------

typedef struct _CEPERF_LOGDATA_CPU_DESCRIPTOR {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_CPU_DESCRIPTOR;

typedef struct _CEPERF_LOGDATA_CPU_CONTROL {
    CEPERF_LOGEVENT_HEADER header;
} CEPERF_LOGDATA_CPU_CONTROL;


#ifdef __cplusplus 
}
#endif 

#endif // _CEPERF_LOG_H_

