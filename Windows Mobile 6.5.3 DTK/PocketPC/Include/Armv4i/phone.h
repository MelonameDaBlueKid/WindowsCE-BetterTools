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
    DWORD dwLogFlags;     // flags to indicate the type of the call
    CEOID oidContact;     // oid of the PIM contact
    CEPROPID pidProp;     // prop-id of the contact (one of the PIMPR properties defined in pimstore.h)
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







// PhoneShowCallLog
//
// Show the Call Log, and filter it

typedef enum
{
    CALLLOGFILTER_ALL_CALLS,
    CALLLOGFILTER_MISSED,
    CALLLOGFILTER_INCOMING,
    CALLLOGFILTER_OUTGOING
} CALLLOGFILTER;

HRESULT PhoneShowCallLog(CALLLOGFILTER iCallLogFilter);









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

    // owner window for dialog box that appears when the PMCF_EDITBEFORECALLING flag is passed into PhoneMakeCall
    HWND hwndOwner;
} PHONEMAKECALLINFO, *PPHONEMAKECALLINFO;

// PhoneMakeCall flags
#define PMCF_DEFAULT                0x00000001
#define PMCF_PROMPTBEFORECALLING    0x00000002
#define PMCF_EDITBEFORECALLING      0x00000020

LONG PhoneMakeCall(PHONEMAKECALLINFO *ppmci);

//
// End PhoneMakeCall
//
//------




//++++++
//
//  PhoneAddSpeedDial
//
//       adds a speed dial entry
//
// dwFlags - currently unused, set to 0
//
// piKey - in/out: the key sequence which will invoke the speed dial. 
//           currently an entry between 2 and 99 (inclusive) is valid. 
//            the API will cause existing entries to be overwritten
//
// pszDisplayName - the non-empty display name for the speed dial
//
// pszTelNumber - the non-empty tel# to be dialed
//

HRESULT PhoneAddSpeedDial(DWORD dwFlags, DWORD* piKey, const TCHAR* pszDisplayName, const TCHAR* pszTelNumber);

//
// End PhoneAddSpeedDial
//
//------




//++++++
//
//  PhoneSendDTMFStart
//
//  Allows an application to begin sending a DTMF tone using the 
//  current phone call.
//
//  Parameters:
//    chDTMF - DTMF character to send. Must be '0'-'9', 
//             'A'-'D', '*', or '#'.
//
//  Return Value:
//    -----------------------------------------------------------
//    Value                        Description
//    ------------------------------------------------------------
//    S_OK                         The operation completed successfully.
//    E_FAIL                       An unknown error occurred.
//    E_INVALIDARG                 chDTMF is invalid.
//    E_NOTIMPL                    No phone is present on the device, the 
//                                 phone service is not running, or no 
//                                 calls are currently active.
//    
//    Other custom failure codes where the facility code is
//    FACILITY_WINDOWS_CE may be retrieved using the HRESULT_CODE
//    macro:
//    -----------------------------------------------------------
//    Error Code                   Description
//    ------------------------------------------------------------
//    ERROR_DEVICE_NOT_CONNECTED   No phone is present on the device, 
//                                 the phone service is not running, or 
//                                 no calls are currently active.
//
//  Remarks:
//    Caller must call PhoneSendDTMFStop to stop the DTMF tone.
//
//    This function will fail if no phone is present on the 
//    device, the phone service is not running, or no calls are  
//    currently active. If a subsequent call to this API is made 
//    by the caller or any other application before the DTMF tone  
//    is finished the original DTMF tone will cease and the new 
//    DTMF will be sent.
//

HRESULT PhoneSendDTMFStart(TCHAR chDTMF);

//
// End PhoneSendDTMFStart
//
//------




//++++++
//
//  PhoneSendDTMFStop
//
//  Stops an existing DTMF tone.
//
//  Remarks:
//    This function stops all DTMF tones. Applications 
//    may use PhoneSendDTMFStart to begin a DTMF tone.
//

void PhoneSendDTMFStop();

//
// End PhoneSendDTMFStop
//
//------


//++++++
//
//  PhoneIsEmergencyNumber
//
//  Determines if a string contains an emergency phone number.
//
//  Parameters:
//    fTailMatchOnly
//        [in] If this argument is set to TRUE, the function only 
//        attempts to match emergency numbers at the end of 
//        pszNumber. If this value is FALSE, the function attempts 
//        to match the emergency string with the full pszNumber 
///       argument exactly.
//    pszNumber
//        [in] String to match. If this pointer is NULL or points 
//        to an empty string, the function returns FALSE.
//    ppszEmergencyNumber
//        [out] On success, constant pointer to the emergency phone 
//        number matched in pszNumber. Caller must not free. On 
//        failure, this pointer is undefined. Optional, may be NULL.
//
//  Return Value:
//    TRUE if pszNumber contains an emergency number; otherwise FALSE.
//
//  Remarks:
//    The system merges the list of emergency phone numbers from 
//    the registry and the SIM, if available. The list of emergency 
//    numbers can vary by device.
//

BOOL PhoneIsEmergencyNumber(BOOL fTailMatchOnly, __in LPCTSTR pszNumber, __deref_opt_out LPCTSTR* ppszEmergencyNumber);

//
// End PhoneIsEmergencyNumber
//
//------


#ifdef __cplusplus
}
#endif

