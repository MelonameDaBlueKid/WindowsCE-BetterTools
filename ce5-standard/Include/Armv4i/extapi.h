///////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation. All rights reserved. //
///////////////////////////////////////////////////////////////


#pragma once

#ifndef _ExTAPI_H_
#define _ExTAPI_H_


#include <windows.h>


#ifdef __cplusplus
extern "C" {
#endif


// ExTAPI LINEERR_ constants
#define LINEERR_INCORRECTPASSWORD               0x80010001

// Line barring modes
#define LINEBARRMODE_OUT                        0x00000001
#define LINEBARRMODE_OUT_INT                    0x00000002
#define LINEBARRMODE_OUT_INTEXTOHOME            0x00000004
#define LINEBARRMODE_IN                         0x00000008
#define LINEBARRMODE_IN_ROAM                    0x00000010
#define LINEBARRMODE_IN_NOTINSIM                0x00000020
#define LINEBARRMODE_ALL                        0x00000040
#define LINEBARRMODE_ALL_OUT                    0x00000080
#define LINEBARRMODE_ALL_IN                     0x00000100

// Line call-waiting states
#define LINECALLWAITING_ENABLED                 0x00000001
#define LINECALLWAITING_DISABLED                0x00000002

// Line capability classes
#define LINECAPSCLASS_VOICE                     0x00000001
#define LINECAPSCLASS_DATA                      0x00000002
#define LINECAPSCLASS_FAX                       0x00000004
#define LINECAPSCLASS_SMS                       0x00000008
#define LINECAPSCLASS_SYNCDATA                  0x00000010
#define LINECAPSCLASS_ASYNCDATA                 0x00000020
#define LINECAPSCLASS_PACKET                    0x00000040
#define LINECAPSCLASS_PAD                       0x00000080
#define LINECAPSCLASS_ALL                       0x000000ff

// Line equipment states
#define LINEEQUIPSTATE_MINIMUM                  0x00000001
#define LINEEQUIPSTATE_RXONLY                   0x00000002
#define LINEEQUIPSTATE_TXONLY                   0x00000003
#define LINEEQUIPSTATE_NOTXRX                   0x00000004
#define LINEEQUIPSTATE_FULL                     0x00000005

// Line GPRS class types
#define LINEGPRSCLASS_GSMANDGPRS                0x00000001
#define LINEGPRSCLASS_GSMORGPRS                 0x00000002
#define LINEGPRSCLASS_GSMORGPRS_EXCLUSIVE       0x00000003
#define LINEGPRSCLASS_GPRSONLY                  0x00000004
#define LINEGPRSCLASS_GSMONLY                   0x00000005

// Line GPRS class changed types
#define LINEGPRSCLASSCHANGED_NETWORK            0x00000001
#define LINEGPRSCLASSCHANGED_RADIO              0x00000002

// Line HSCSD air-rates
#define LINEHSCSDAIRRATE_9600                   0x00000001
#define LINEHSCSDAIRRATE_14400                  0x00000002
#define LINEHSCSDAIRRATE_19200                  0x00000003
#define LINEHSCSDAIRRATE_28800                  0x00000004
#define LINEHSCSDAIRRATE_38400                  0x00000005
#define LINEHSCSDAIRRATE_43200                  0x00000006
#define LINEHSCSDAIRRATE_57600                  0x00000007

// Line HSCSD codings
#define LINEHSCSDCODING_4800                    0x00000001
#define LINEHSCSDCODING_9600                    0x00000002
#define LINEHSCSDCODING_14400                   0x00000004

// Line mute states
#define LINEMUTESTATE_MUTEENABLED               0x00000001
#define LINEMUTESTATE_MUTEDISABLED              0x00000002

// Line operator formats
#define LINEOPFORMAT_NONE                       0x00000000
#define LINEOPFORMAT_ALPHASHORT                 0x00000001
#define LINEOPFORMAT_ALPHALONG                  0x00000002
#define LINEOPFORMAT_NUMERIC                    0x00000004

// Line operator statuses
#define LINEOPSTATUS_UNKNOWN                    0x00000000
#define LINEOPSTATUS_AVAILABLE                  0x00000001
#define LINEOPSTATUS_CURRENT                    0x00000002
#define LINEOPSTATUS_FORBIDDEN                  0x00000003

// Line radio presence states
#define LINERADIOPRESENCE_PRESENT               0x00000001
#define LINERADIOPRESENCE_NOTPRESENT            0x00000002

// Line radio support states
#define LINERADIOSUPPORT_OFF                    0x00000001
#define LINERADIOSUPPORT_ON                     0x00000002
#define LINERADIOSUPPORT_UNKNOWN                0x00000003

// Line register modes
#define LINEREGMODE_AUTOMATIC                   0x00000001
#define LINEREGMODE_MANUAL                      0x00000002
#define LINEREGMODE_MANAUTO                     0x00000003

// Line register status
#define LINEREGSTATUS_UNKNOWN                   0x00000001
#define LINEREGSTATUS_DENIED                    0x00000002
#define LINEREGSTATUS_UNREGISTERED              0x00000003
#define LINEREGSTATUS_ATTEMPTING                0x00000004
#define LINEREGSTATUS_HOME                      0x00000005
#define LINEREGSTATUS_ROAM                      0x00000006
#define LINEREGSTATUS_DIGITAL                   0x00000007
#define LINEREGSTATUS_ANALOG                    0x00000008

// Line send caller-ID states
#define LINESENDCALLERID_ENABLED                0x00000001
#define LINESENDCALLERID_DISABLED               0x00000002

// Line system types, CDMA
#define LINESYSTEMTYPE_NONE                     0x00000000
#define LINESYSTEMTYPE_IS95A                    0x00000001
#define LINESYSTEMTYPE_IS95B                    0x00000002
#define LINESYSTEMTYPE_1XRTTPACKET              0x00000004
// Line system types, GSM
#define LINESYSTEMTYPE_GSM                      0x00000008
#define LINESYSTEMTYPE_GPRS                     0x00000010

// Line USSD flags
#define LINEUSSDFLAG_ACTIONREQUIRED             0x00000001
#define LINEUSSDFLAG_ACTIONNOTNEEDED            0x00000002
#define LINEUSSDFLAG_TERMINATED                 0x00000004
#define LINEUSSDFLAG_OTHERCLIENTRESPONDED       0x00000008
#define LINEUSSDFLAG_UNSUPPORTED                0x00000010
#define LINEUSSDFLAG_TIMEOUT                    0x00000020
#define LINEUSSDFLAG_ENDSESSION                 0x00000040

// Special LINEOPERATOR index values
#define LINEOPERATOR_USEFIRSTAVAILABLEINDEX     (-1)

// Maximum string lengths
#define MAX_LENGTH_OPERATOR_LONG                32
#define MAX_LENGTH_OPERATOR_SHORT               16
#define MAX_LENGTH_OPERATOR_NUMERIC             16


// LINE_DEVSPECIFIC message types
#define LINE_EQUIPSTATECHANGE                   0x00000100
    // dwParam1 = LINE_EQUIPSTATECHANGE
    // dwParam2 = One of the LINEEQUIPSTATE_* constants
    // dwParam3 = One of the LINERADIOSUPPORT_* constants

#define LINE_GPRSCLASS                          0x00000101
    // dwParam1 = LINE_GPRSCLASS
    // dwParam2 = One of the LINEGPRSCLASS_* constants
    // dwParam3 = One of the LINEGPRSCLASSCHANGED_* constants

#define LINE_GPRSREGISTERSTATE                  0x00000102
    // dwParam1 = LINE_GPRSREGISTERSTATE
    // dwParam2 = One of the LINEREGSTATUS_* constants
    // dwParam3 Unused

#define LINE_RADIOPRESENCE                      0x00000103
    // dwParam1 = LINE_RADIOPRESENCE
    // dwParam2 = One of the LINERADIOPRESENCE_* constants
    // dwParam3 Unused

#define LINE_REGISTERSTATE                      0x00000104
    // dwParam1 = LINE_REGISTERSTATE
    // dwParam2 = One of the LINEREGSTATUS_* constants
    // dwParam3 Unused

#define LINE_USSD                               0x00000105
    // dwParam1 = LINE_USSD
    // dwParam2 = Message identifier
    // dwParam3 = Size in bytes of message
    
#define LINE_CURRENTLINECHANGE                  0x00000106
    // dwParam1 = LINE_CURRENTLINECHANGE
    // dwParam2 = New line identifier
    // dwParam3 = New address ID

#define LINE_CURRENTSYSTEMCHANGE                0x00000107
    // dwParam1 = LINE_CURRENTSYSTEMCHANGE
    // dwParam2 = New system coverage (LINESYSTEMTYPE_*)
    // dwParam3 = unused


// Structures
typedef struct lineoperator_tag {
    DWORD dwIndex;
    DWORD dwValidFields;
    DWORD dwStatus;
    TCHAR lpszLongName[MAX_LENGTH_OPERATOR_LONG];
    TCHAR lpszShortName[MAX_LENGTH_OPERATOR_SHORT];
    TCHAR lpszNumName[MAX_LENGTH_OPERATOR_NUMERIC];
} LINEOPERATOR, *LPLINEOPERATOR;

typedef struct lineoperatorstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwPreferredCount;
    DWORD dwPreferredSize;
    DWORD dwPreferredOffset;
    DWORD dwAvailableCount;
    DWORD dwAvailableSize;
    DWORD dwAvailableOffset;
} LINEOPERATORSTATUS, *LPLINEOPERATORSTATUS;

typedef struct linegeneralinfo_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwManufacturerSize;
    DWORD dwManufacturerOffset;
    DWORD dwModelSize;
    DWORD dwModelOffset;
    DWORD dwRevisionSize;
    DWORD dwRevisionOffset;
    DWORD dwSerialNumberSize;
    DWORD dwSerialNumberOffset;
    DWORD dwSubscriberNumberSize;
    DWORD dwSubscriberNumberOffset;
} LINEGENERALINFO, *LPLINEGENERALINFO;

// Functions
LONG WINAPI lineGetCallBarringCaps(
    HLINE hLine,
    LPDWORD lpdwModes,
    LPDWORD lpdwClasses
);

LONG WINAPI lineGetCallBarringState(
    HLINE hLine,
    DWORD dwMode,
    LPDWORD lpdwClasses,
    LPCTSTR lpszPassword
);

LONG WINAPI lineGetCallWaitingCaps(
    HLINE hLine,
    LPDWORD lpdwClasses
);

LONG WINAPI lineGetCallWaitingState(
    HLINE hLine,
    LPDWORD lpdwClasses
);

LONG WINAPI lineGetCurrentAddressID(
    HLINE hLine,
    LPDWORD lpdwAddressID
);

LONG WINAPI lineGetCurrentHSCSDStatus(
    HLINE hLine,
    LPDWORD lpdwChannelsIn,
    LPDWORD lpdwChannelsOut,
    LPDWORD lpdwChannelCoding,
    LPDWORD lpdwAirInterfaceRate
);

LONG WINAPI lineGetCurrentOperator(
    HLINE hLine,
    LPLINEOPERATOR lpCurrentOperator
);

LONG WINAPI lineGetCurrentSystemType(
    HLINE hLine,
    LPDWORD lpdwCurrentSystemType
);

LONG WINAPI lineGetEquipmentState(
    HLINE hLine,
    LPDWORD lpdwState,
    LPDWORD lpdwRadioSupport
);

LONG WINAPI lineGetGeneralInfo(
    HLINE hLine,
    LPLINEGENERALINFO lpLineGeneralInfo
);

LONG WINAPI lineGetGPRSClass(
    HLINE hLine,
    LPDWORD lpdwClass
);

LONG WINAPI lineGetHSCSDCaps(
    HLINE hLine,
    LPDWORD lpdwClass,
    LPDWORD lpdwChannelsIn,
    LPDWORD lpdwChannelsOut,
    LPDWORD lpdwChannelsSum,
    LPDWORD lpdwChannelCodings
);

LONG WINAPI lineGetHSCSDState(
    HLINE hLine,
    LPDWORD lpdwChannelsIn,
    LPDWORD lpdwMaxChannelsIn,
    LPDWORD lpdwChannelCodings,
    LPDWORD lpdwAirInterfaceRate
);

LONG WINAPI lineGetMuteState(
    HLINE hLine,
    LPDWORD lpdwState
);

LONG WINAPI lineGetNumberCalls(
    HLINE hLine,
    LPDWORD lpdwNumActiveCalls,
    LPDWORD lpdwNumOnHoldCalls,
    LPDWORD lpdwNumOnHoldPendCalls
);

LONG WINAPI lineGetOperatorStatus(
    HLINE hLine,
    LPLINEOPERATORSTATUS lpOperatorStatus
);

LONG WINAPI lineGetRadioPresence(
    HLINE hLine,
    LPDWORD lpdwRadioPresence
);

LONG WINAPI lineGetRegisterStatus(
    HLINE hLine,
    LPDWORD lpdwRegisterStatus
);

LONG WINAPI lineGetSendCallerIDState(
    HLINE hLine,
    LPDWORD lpdwState
);

LONG WINAPI lineGetUSSD(
    HLINE hLine,
    DWORD dwID,
    LPBYTE lpbUSSD,
    DWORD dwUSSDSize,
    LPDWORD lpdwFlags
);

LONG WINAPI lineRegister(
    HLINE hLine,
    DWORD dwRegisterMode,
    LPCTSTR lpszOperator,
    DWORD dwOperatorFormat
);

LONG WINAPI lineSendUSSD(
    HLINE hLine,
    const BYTE* const lpbUSSD,
    DWORD dwUSSDSize,
    DWORD dwFlags
);

LONG WINAPI lineSetCallBarringPassword(
    HLINE hLine,
    DWORD dwMode,
    LPCTSTR lpszOldPassword,
    LPCTSTR lpszNewPassword
);

LONG WINAPI lineSetCallBarringState(
    HLINE hLine,
    DWORD dwMode,
    DWORD dwClasses,
    LPCTSTR lpszPassword
);

LONG WINAPI lineSetCallWaitingState(
    HLINE hLine,
    DWORD dwClasses,
    DWORD dwState
);

LONG WINAPI lineSetCurrentAddressID(
    HLINE hLine,
    DWORD dwAddressID
);

LONG WINAPI lineSetEquipmentState(
    HLINE hLine,
    DWORD dwState
);

LONG WINAPI lineSetGPRSClass(
    HLINE hLine,
    DWORD dwClass
);

LONG WINAPI lineSetHSCSDState(
    HLINE hLine,
    DWORD dwChannelsIn,
    DWORD dwMaxChannelsIn,
    DWORD dwChannelCodings,
    DWORD dwAirInterfaceRate
);

LONG WINAPI lineSetMuteState(
    HLINE hLine,
    DWORD dwState
);

LONG WINAPI lineSetSendCallerIDState(
    HLINE hLine,
    DWORD dwState
);

LONG WINAPI lineSetPreferredOperator(
    HLINE hLine,
    LPLINEOPERATOR lpOperator
);

LONG WINAPI lineUnregister(
    HLINE hLine
);


#ifdef __cplusplus
}
#endif


#endif // _ExTAPI_H_
