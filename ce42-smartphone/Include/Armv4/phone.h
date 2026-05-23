// phone.h
//
// Phone API
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>

#ifdef WINCEOEM
#include <phonep.h>
#endif


typedef enum
{
    CALLERIDTYPE_UNAVAILABLE,
    CALLERIDTYPE_BLOCKED,
    CALLERIDTYPE_AVAILABLE
} CALLERIDTYPE;

typedef enum
{
    IOM_MISSED,
    IOM_INCOMING,
    IOM_OUTGOING
} IOM;

typedef enum
{ 
    CALLLOGSEEK_BEGINNING= 2,
    CALLLOGSEEK_END = 4
} CALLLOGSEEK;    

typedef struct
{
    DWORD cbSize;  // sizeof CALLLOGENTRY
    FILETIME ftStartTime;
    FILETIME ftEndTime;
    IOM iom;
    BOOL fOutgoing:1;        // direction of call.  (Missed calls are incoming.)
    BOOL fConnected:1;     // Did the call connect? (as opposed to busy, no answer)
    BOOL fEnded:1;        // Was the call ended? (as opposed to dropped)
    BOOL fRoam:1;        // Roaming (vs. local)
    CALLERIDTYPE cidt;
    PTSTR pszNumber;
    PTSTR pszName;
    PTSTR pszNameType;    // "w" for work tel, "h" for home tel, for example
    PTSTR pszNote;    // filename of associated Notes file
} CALLLOGENTRY, *PCALLLOGENTRY;

// Open the call log and set the seek pointer to the beginning.
HRESULT PhoneOpenCallLog (HANDLE *ph);

// PhoneGetCallLogEntry returns one call log entry and advances the seek 
// pointer.  
// pentry->cbSize must be set to "sizeof CALLLOGENTRY" before this function is 
// called.
// The entries are returned in order of start time, the most recent call first.
// It is the responsibility of the caller to LocalFree any strings 
// which are returned.
// A return value of S_FALSE indicates there are no more entries.
HRESULT PhoneGetCallLogEntry (HANDLE h, PCALLLOGENTRY pentry);

// PhoneSeekCallLog seeks to a record in the call log.  
// iRecord is the zero-based index of the  record, starting at the beginning 
// if seek == CALLLOGSEEK_BEGINNING, at the end if CALLLOGSEEK_END.  
// piRecord returns the zero-based index (from the beginning) of the seek 
// pointer after the seek is performed.
// PhoneSeekCallLog(h, CALLLOGSEEK_END, 0, &count) will return the number of 
// records.
HRESULT PhoneSeekCallLog (HANDLE hdb, CALLLOGSEEK seek, DWORD iRecord, LPDWORD piRecord);

// Close the call log
HRESULT PhoneCloseCallLog (HANDLE h);


// The Call Log application supports the context menu extensibility mechanism.
// The Context name is "Phone" and the Class name is "Log".
// The IUnknown pointer passed to the context menu handler supports IPropertyBag,
// and the set of properties supported is as follows:
//
// property name:   type:   value:
// --------------   -----   ------
// PropSet          BSTR    "CallLog"
// Number           BSTR    the phone number of the other person on the call
// NumberType       BSTR    the type of phone number (e.g. "h" for home)
// Name             BSTR    person's name 
// Year             I2      the year of the beginning time of the call
// Month            I2      the month of the beginning time of the call
// Day              I2      the day of the beginning time of the call
// Hour             I2      the hour of the beginning time of the call  
// Minute           I2      the minute of the beginning time of the call
// Second           I2      the second of the beginning time of the call
// DayOfWeek        I2      the day of the week of the beginning time of the call
// Duration         UI4     the duration of the call in seconds
// CallerIDType     UI4     a CALLERIDTYPE value (see above)
// Connected        BOOL    Did the call connect? (as opposed to busy, no answer)
// Ended            BOOL    Was the call ended? (as opposed to dropped)
// Outgoing         BOOL    Was the call outgoing?  (Missed calls are incoming.)
// Roaming          BOOL    Roaming?
// IOM              UI4     an IOM value (see above)



//++++++
//
//  PhoneMakeCall
//
//       Dials a number

typedef struct tagPHONEMAKECALLINFO
{
    DWORD cbSize;
    DWORD dwFlags;
    
    //Params to tapiRequestMakeCall
    PCWSTR pszDestAddress;
    PCWSTR pszAppName;
    PCWSTR pszCalledParty;
    PCWSTR pszComment;
} PHONEMAKECALLINFO, *PPHONEMAKECALLINFO;

// PhoneMakeCall flags
#define PMCF_DEFAULT                0x00000001
#define PMCF_PROMPTBEFORECALLING    0x00000002

LONG PhoneMakeCall(PHONEMAKECALLINFO *ppmci);

//
// End PhoneMakeCall
//
//------


#ifdef __cplusplus
}
#endif

