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


Module Name:

    80211hdr.h

Abstract:

    802.11


--*/

#ifndef __802_11_HDR_H__
#define __802_11_HDR_H__

#pragma once

//
// Definitions for IEEE 802.11 packet headers
//
#include <packon.h>

#ifndef __WINDOWS__
#include <windows.h>
#endif

#ifndef __WINDOT11_H__
#include <windot11.h>
#endif

#define DOT11_ADDRESS_SIZE 6

#define DOT11_CURRENT_VERSION  0

#define DOT11_MAX_MSDU_SIZE     (2346U)

typedef enum {
    DOT11_FRAME_TYPE_MANAGEMENT = 0,
    DOT11_FRAME_TYPE_CONTROL = 1,
    DOT11_FRAME_TYPE_DATA = 2,
    DOT11_FRAME_TYPE_RESERVED = 3,
} DOT11_FRAME_TYPE, * PDOT11_FRAME_TYPE;

typedef enum {
    DOT11_MGMT_SUBTYPE_ASSOCIATION_REQUEST = 0,    // Association Request
    DOT11_MGMT_SUBTYPE_ASSOCIATION_RESPONSE = 1,   // Association Response
    DOT11_MGMT_SUBTYPE_REASSOCIATION_REQUEST = 2,  // Ressociation Request
    DOT11_MGMT_SUBTYPE_REASSOCIATION_RESPONSE = 3, // Reassociation Response
    DOT11_MGMT_SUBTYPE_PROBE_REQUEST = 4,          // Probe Request
    DOT11_MGMT_SUBTYPE_PROBE_RESPONSE = 5,         // Probe Response

    DOT11_MGMT_SUBTYPE_BEACON = 8,                 // Beacon
    DOT11_MGMT_SUBTYPE_ATIM = 9,                   // Announcement Traffic Indication Message (ATIM)
    DOT11_MGMT_SUBTYPE_DISASSOCIATION = 10,        // Disassociation
    DOT11_MGMT_SUBTYPE_AUTHENTICATION = 11,        // Authentication
    DOT11_MGMT_SUBTYPE_DEAUTHENTICATION = 12,      // Deauthentication
    DOT11_MGMT_SUBTYPE_MANAGEMENT_ACTION = 13,     // Management Action
} DOT11_MGMT_SUBTYPE, * PDOT11_MGMT_SUBTYPE;

typedef enum {
    DOT11_CTRL_SUBTYPE_PS_POLL = 10,   // Power Save Poll
    DOT11_CTRL_SUBTYPE_RTS = 11,       // Request To Send
    DOT11_CTRL_SUBTYPE_CTS = 12,       // Clear To Send
    DOT11_CTRL_SUBTYPE_ACK = 13,       // Acknowledgement
    DOT11_CTRL_SUBTYPE_CFE = 14,       // Contention-Free-End
    DOT11_CTRL_SUBTYPE_CFE_CFA = 15    // CF-End + CF-Ack

} DOT11_CTRL_SUBTYPE, * PDOT11_CTRL_SUBTYPE;

typedef enum {
    DOT11_DATA_SUBTYPE_CFA_FLAG = 1,        // CF-ACK flag
    DOT11_DATA_SUBTYPE_CFP_FLAG = 2,        // CF-Poll flag
    DOT11_DATA_SUBTYPE_NULL_FLAG = 4,       // NULL data flag
    DOT11_DATA_SUBTYPE_QOS_FLAG = 8,        // QoS Flag

    // DATA:                                0 (0000)
    DOT11_DATA_SUBTYPE_DATA = 0,

    // DATA + CF-Ack                        1 (0001)
    DOT11_DATA_SUBTYPE_DATA_CFA = (DOT11_DATA_SUBTYPE_CFA_FLAG),

    // DATA + CF-Poll                       2 (0010)
    DOT11_DATA_SUBTYPE_DATA_CFP = (DOT11_DATA_SUBTYPE_CFP_FLAG),

    // Data + CF-Ack + CF-Poll              3 (0011)
    DOT11_DATA_SUBTYPE_DATA_CFA_CFP = (DOT11_DATA_SUBTYPE_CFA_FLAG | DOT11_DATA_SUBTYPE_CFP_FLAG),


    // NULL                                 4 (0100)
    DOT11_DATA_SUBTYPE_NULL = (DOT11_DATA_SUBTYPE_NULL_FLAG),

    // NULL + CF-Ack                        5 (0101)
    DOT11_DATA_SUBTYPE_NULL_CFA = (DOT11_DATA_SUBTYPE_NULL_FLAG | DOT11_DATA_SUBTYPE_CFA_FLAG),

    // NULL + CF-Poll                       6 (0110)
    DOT11_DATA_SUBTYPE_NULL_CFP = (DOT11_DATA_SUBTYPE_NULL_FLAG | DOT11_DATA_SUBTYPE_CFP_FLAG),

    // NULL + CF-Ack + CF-Poll              7 (0111)
    DOT11_DATA_SUBTYPE_NULL_CFA_CFP = (DOT11_DATA_SUBTYPE_NULL_FLAG | DOT11_DATA_SUBTYPE_DATA_CFA_CFP),

    // QOS Data                             8 (1000)
    DOT11_DATA_SUBTYPE_QOS_DATA = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_DATA),

    // QOS Data + CF-Ack                    9 (1001)
    DOT11_DATA_SUBTYPE_QOS_CFA = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_DATA_CFA),

    // QOS Data + CF-Poll                   a (1010)
    DOT11_DATA_SUBTYPE_QOS_DATA_CFP = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_DATA_CFP),

    // QOS Data + CF-Ack + CF-Poll          b (1011)
    DOT11_DATA_SUBTYPE_QOS_DATA_CFA_CFP = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_DATA_CFA_CFP),

    // QOS Null                             c (1100)
    DOT11_DATA_SUBTYPE_QOS_NULL = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_NULL),

    // Reserved                             d (1101)
    DOT11_DATA_SUBTYPE_RESERVED = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_NULL_CFA),

    // QOS Null + CF-Poll                   e (1110)
    DOT11_DATA_SUBTYPE_QOS_NULL_CFP = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_NULL_CFP),

    // QOS Null + CF-Ack + CF-Poll          f (1111)
    DOT11_DATA_SUBTYPE_QOS_NULL_CFA_CFP = (DOT11_DATA_SUBTYPE_QOS_FLAG | DOT11_DATA_SUBTYPE_NULL_CFA_CFP)
} DOT11_DATA_SUBTYPE, * PDOT11_DATA_SUBTYPE;

typedef struct {
    USHORT  Version: 2;     // Protocol Version
    USHORT  Type: 2;
    USHORT  Subtype: 4;
    USHORT  ToDS: 1;
    USHORT  FromDS: 1;
    USHORT  MoreFrag: 1;
    USHORT  Retry: 1;
    USHORT  PwrMgt: 1;
    USHORT  MoreData: 1;
    USHORT  WEP: 1;
    USHORT  Order: 1;
} DOT11_FRAME_CTRL, * PDOT11_FRAME_CTRL;

typedef union {
    struct {
        USHORT  FragmentNumber: 4;
        USHORT  SequenceNumber: 12;
    };
    USHORT usValue;
} DOT11_SEQUENCE_CONTROL, * PDOT11_SEQUENCE_CONTROL;

typedef struct {
    USHORT  Eight02OneDTag: 3;
    USHORT  Reserved1: 2;
    USHORT  AckPolicy: 2;
    USHORT  Reserved2: 9;
} DOT11_QOS_CONTROL, * PDOT11_QOS_CONTROL;

typedef struct {
    UCHAR TID: 4;
    UCHAR EOSP: 1;
    UCHAR AckPolicy: 2;
    UCHAR Reserved2: 1;
    union {
        UCHAR TXOPLimit;
        UCHAR QAPPSBufferState;
        UCHAR TXOPRequestedDuration;
        UCHAR QueueSize;
    };
} DOT11_80211E_CONTROL, * PDOT11_80211E_CONTROL;

#define DOT11_QOS_CONTROL_HEADER_SIZE    sizeof(DOT11_QOS_CONTROL)

// Generic 802.11 header
typedef struct DOT11_MAC_HEADER {
    DOT11_FRAME_CTRL    FrameControl;
    USHORT              DurationID;
    DOT11_MAC_ADDRESS   Address1;
} DOT11_MAC_HEADER, * PDOT11_MAC_HEADER;

// For data frames, short header should be used
// when either FromDS=0 or ToDS=0
typedef struct DOT11_DATA_SHORT_HEADER {
    DOT11_FRAME_CTRL        FrameControl;
    USHORT                  DurationID;
    DOT11_MAC_ADDRESS       Address1;
    DOT11_MAC_ADDRESS       Address2;
    DOT11_MAC_ADDRESS       Address3;
    DOT11_SEQUENCE_CONTROL  SequenceControl;
} DOT11_DATA_SHORT_HEADER, * PDOT11_DATA_SHORT_HEADER;
#define DOT11_DATA_SHORT_HEADER_SIZE    sizeof(DOT11_DATA_SHORT_HEADER)

#ifdef UNDER_CE
#define PDOT11_FRAGMENT_MAC_HEADER  PDOT11_DATA_SHORT_HEADER
#define DOT11_FRAGMENT_MAC_HEADER   DOT11_DATA_SHORT_HEADER
#endif

// For data frames, long header should be used
// when both FromDS=1 and ToDS=1
typedef struct DOT11_DATA_LONG_HEADER {
    DOT11_FRAME_CTRL        FrameControl;
    USHORT                  DurationID;
    DOT11_MAC_ADDRESS       Address1;
    DOT11_MAC_ADDRESS       Address2;
    DOT11_MAC_ADDRESS       Address3;
    DOT11_SEQUENCE_CONTROL  SequenceControl;
    DOT11_MAC_ADDRESS       Address4;
} DOT11_DATA_LONG_HEADER, * PDOT11_DATA_LONG_HEADER;
#define DOT11_DATA_LONG_HEADER_SIZE     sizeof(DOT11_DATA_LONG_HEADER)

// For data frames, short header should be used
// when either FromDS=0 or ToDS=0
typedef struct DOT11_QOS_DATA_SHORT_HEADER {
    DOT11_FRAME_CTRL        FrameControl;
    USHORT                  DurationID;
    DOT11_MAC_ADDRESS       Address1;
    DOT11_MAC_ADDRESS       Address2;
    DOT11_MAC_ADDRESS       Address3;
    DOT11_SEQUENCE_CONTROL  SequenceControl;
    DOT11_QOS_CONTROL       QoSControl;
} DOT11_QOS_DATA_SHORT_HEADER, * PDOT11_QOS_DATA_SHORT_HEADER;
#define DOT11_QOS_DATA_SHORT_HEADER_SIZE    sizeof(DOT11_QOS_DATA_SHORT_HEADER)

// For data frames, long header should be used
// when both FromDS=1 and ToDS=1
typedef struct DOT11_QOS_QOS_DATA_LONG_HEADER {
    DOT11_FRAME_CTRL        FrameControl;
    USHORT                  DurationID;
    DOT11_MAC_ADDRESS       Address1;
    DOT11_MAC_ADDRESS       Address2;
    DOT11_MAC_ADDRESS       Address3;
    DOT11_SEQUENCE_CONTROL  SequenceControl;
    DOT11_MAC_ADDRESS       Address4;
    DOT11_QOS_CONTROL       QoSControl;
} DOT11_QOS_DATA_LONG_HEADER, * PDOT11_QOS_DATA_LONG_HEADER;
#define DOT11_QOS_DATA_LONG_HEADER_SIZE     sizeof(DOT11_QOS_DATA_LONG_HEADER)

// Mgmt frame header
typedef struct DOT11_MGMT_HEADER {
    DOT11_FRAME_CTRL        FrameControl;
    USHORT                  DurationID;
    DOT11_MAC_ADDRESS       DA;
    DOT11_MAC_ADDRESS       SA;
    DOT11_MAC_ADDRESS       BSSID;
    DOT11_SEQUENCE_CONTROL  SequenceControl;
} DOT11_MGMT_HEADER, * PDOT11_MGMT_HEADER;
#define DOT11_MGMT_HEADER_SIZE          sizeof(DOT11_MGMT_HEADER)

#ifdef UNDER_CE
#define DOT11_MGMT_FRAME_MAC_HEADER     DOT11_MGMT_HEADER
#define PDOT11_MGMT_FRAME_MAC_HEADER    PDOT11_MGMT_HEADER
#endif

// Ctrl frame header
typedef struct DOT11_CTRL_HEADER {
    DOT11_FRAME_CTRL    FrameControl;
    USHORT              DurationID;
    DOT11_MAC_ADDRESS   Address1;
} DOT11_CTRL_HEADER, * PDOT11_CTRL_HEADER;
#define DOT11_CTRL_HEADER_SIZE          sizeof(DOT11_CTRL_HEADER)

//
// Management Frame
//

typedef union {
    struct {
        USHORT          ESS: 1;
        USHORT          IBSS: 1;
        USHORT          CFPollable: 1;
        USHORT          CFPollRequest: 1;
        USHORT          Privacy: 1;
        USHORT          ShortPreamble: 1;
        USHORT          PBCC: 1;
        USHORT          ChannelAgility: 1;
        USHORT          Reserved: 2;
        USHORT          ShortSlotTime:1;
        USHORT          Reserved2: 2;
        USHORT          DSSSOFDM: 1;
        USHORT          Reserved3: 2;
    };

    USHORT usValue;

} DOT11_CAPABILITY, * PDOT11_CAPABILITY;

//
// Management Notification Frame
//
#define DOT11_MGMT_NOTIF_CATEGORY_CODE_WME   17

typedef enum _DOT11_MGMT_NOTIF_ACTION {
    dot11_mgmt_notif_action_setup_request = 0,
    dot11_mgmt_notif_action_setup_response = 1,
    dot11_mgmt_notif_action_setup_teardown = 2,
} DOT11_MGMT_NOTIF_ACTION, * PDOT11_MGMT_NOTIF_ACTION;

typedef enum _DOT11_MGMT_NOTIF_STATUS {
    dot11_mgmt_notif_status_admission_accepted = 0,
    dot11_mgmt_notif_status_invalid_parameters = 1,
    dot11_mgmt_notif_status_refused = 3,
} DOT11_MGMT_NOTIF_STATUS, * PDOT11_MGMT_NOTIF_STATUS;

typedef struct _DOT11_MGMT_NOTIFICATION {
    UCHAR ucCategoryCode;
    UCHAR ucActionCode;
    UCHAR ucDialogToken;
    UCHAR ucStatusCode;
} DOT11_MGMT_NOTIFICATION, * PDOT11_MGMT_NOTIFICATION;
#define DOT11_MGMT_NOTIFICATION_SIZE          sizeof(DOT11_MGMT_NOTIFICATION)


#define DOT11_INFO_ELEMENT_ID_SSID                  0
#define DOT11_INFO_ELEMENT_ID_SUPPORTED_RATES       1
#define DOT11_INFO_ELEMENT_ID_FH_PARAM_SET          2
#define DOT11_INFO_ELEMENT_ID_DS_PARAM_SET          3
#define DOT11_INFO_ELEMENT_ID_CF_PARAM_SET          4
#define DOT11_INFO_ELEMENT_ID_TIM                   5
#define DOT11_INFO_ELEMENT_ID_IBSS_PARAM_SET        6
#define DOT11_INFO_ELEMENT_ID_COUNTRY_INFO          7
#define DOT11_INFO_ELEMENT_ID_FH_PARAM              8
#define DOT11_INFO_ELEMENT_ID_FH_PATTERN_TABLE      9
#define DOT11_INFO_ELEMENT_ID_REQUESTED             10
#define DOT11_INFO_ELEMENT_ID_CHALLENGE             16
#define DOT11_INFO_ELEMENT_ID_ERP                   42
#define DOT11_INFO_ELEMENT_ID_HT_CAPABILITIES       45
#define DOT11_INFO_ELEMENT_ID_RSN                   48
#define DOT11_INFO_ELEMENT_ID_EXTD_SUPPORTED_RATES  50
#define DOT11_INFO_ELEMENT_ID_HT_INFO               61
#define DOT11_INFO_ELEMENT_ID_SECONDARY_CHANNEL_OFFSET  62
#define DOT11_INFO_ELEMENT_ID_VENDOR_SPECIFIC       221

typedef struct {
    UCHAR   ElementID;      // Element Id
    UCHAR   Length;         // Length of SSID
} DOT11_INFO_ELEMENT, * PDOT11_INFO_ELEMENT;
#define DOT11_IE_SSID_MAX_LENGTH    (DOT11_SSID_MAX_LENGTH + sizeof(DOT11_INFO_ELEMENT))
#define DOT11_IE_RATES_MAX_LENGTH   (8 + sizeof(DOT11_INFO_ELEMENT))

typedef union _DOT11_ERP_IE {
    struct {
        UCHAR           NonERPPresent: 1;
        UCHAR           UseProtection: 1;
        UCHAR           BarkerPreambleMode: 1;
        UCHAR           Reserved: 5;
    };
} DOT11_ERP_IE, * PDOT11_ERP_IE;

typedef union DOT11_OUI_HEADER {
    struct {
        UCHAR OUI[3];
        UCHAR Type;
    };
    UNALIGNED ULONG uValue;
} DOT11_OUI_HEADER, * PDOT11_OUI_HEADER;

typedef struct _DOT11_SSN_IE_SUITE {
    UCHAR   OUI[3];
    UCHAR   Type;
} DOT11_SSN_IE_SUITE, * PDOT11_SSN_IE_SUITE;

typedef struct _DOT11_SSN_IE_COUNT_SUITE {
    USHORT  SuiteCount;
    DOT11_SSN_IE_SUITE  dot11SSNIESuite[1];
} DOT11_SSN_IE_COUNT_SUITE, *PDOT11_SSN_IE_COUNT_SUITE;

typedef struct _DOT11_SSN_IE_HEADER {
    UCHAR   OUI[3];
    UCHAR   OUIType;
    USHORT  Version;
} DOT11_SSN_IE_HEADER, * PDOT11_SSN_IE_HEADER;

typedef struct DOT11_RSN_IE_HEADER {
    USHORT  Version;
} DOT11_RSN_IE_HEADER, * PDOT11_RSN_IE_HEADER;

typedef struct {
    USHORT          Reserved1: 1;
    USHORT          UnicastUsingGroup: 1;
    USHORT          ReplayIndexBit: 2;
    USHORT          Reserved2: 12;
} DOT11_SSN_CAPABILITY, * PDOT11_SSN_CAPABILITY;


//
// WME IE Struct Begin
//
typedef struct {
    UCHAR ParamSetCount: 4;
    UCHAR ReservedACInfoField: 4;
} DOT11_AC_INFO_FIELD, * PDOT11_AC_INFO_FIELD;

typedef struct{
        UCHAR AIFSN: 4;
        UCHAR ACM: 1;
        UCHAR ACI: 2;
        UCHAR ReservedACIAIFSN: 1;
} DOT11_ACI_AIFSN, * PDOT11_ACI_AIFSN;

typedef struct {
    UCHAR ECWmin: 4;
    UCHAR ECWmax: 4;
} DOT11_ECW, * PDOT11_ECW;

typedef struct {
#ifdef __cplusplus
    DOT11_ACI_AIFSN aifsn;
    DOT11_ECW ecw;
#else
    DOT11_ACI_AIFSN;
    DOT11_ECW;
#endif
    USHORT TXOPLimit;
} DOT11_AC_PARAMETERS, * PDOT11_AC_PARAMETERS;

typedef struct {
#ifdef __cplusplus
    DOT11_OUI_HEADER OuiHdr;
#else
    DOT11_OUI_HEADER;
#endif
    UCHAR OUISubType;
    UCHAR Version;
#ifdef __cplusplus
    DOT11_AC_INFO_FIELD ACInfo;
#else
    DOT11_AC_INFO_FIELD;
#endif
} DOT11_WME_IE, * PDOT11_WME_IE;

typedef struct {
#ifdef __cplusplus
    DOT11_WME_IE wmeie;
#else
    DOT11_WME_IE;
#endif
    UCHAR ReservedWMEParamIE;
    DOT11_AC_PARAMETERS dot11ACParams[dot11_AC_param_max];
} DOT11_WME_PARAM_IE, * PDOT11_WME_PARAM_IE;

//
// QoS TSPEC
//
typedef struct _DOT11_WME_TS_INFO {
    USHORT Reserved1: 1;
    USHORT Eight021DTag1: 3;
    USHORT UnusedZero: 1;
    USHORT Direction: 2;
    USHORT ContentionBasedAccess: 1;
    USHORT Reserved2: 3;
    USHORT Eight021DTag2: 3;
    USHORT Reserved3: 2;
} DOT11_WME_TS_INFO, * PDOT11_WME_TS_INFO;

typedef struct _DOT11_WME_NOMINAL_MSDU_SIZE {
    USHORT Size: 15;
    USHORT Fixed: 1;
} DOT11_WME_NOMINAL_MSDU_SIZE, * PDOT11_WME_NOMINAL_MSDU_SIZE;

typedef union _DOT11_WME_SURPLUS_BANDWIDTH_ALLOWANCE_FACTOR {
    struct {
        USHORT Decimal: 13;
        USHORT Integer: 3;
    };
    USHORT usValue;
} DOT11_WME_SURPLUS_BANDWIDTH_ALLOWANCE_FACTOR, * PDOT11_WME_SURPLUS_BANDWIDTH_ALLOWANCE_FACTOR;

typedef struct _DOT11_WME_TSPEC {
    DOT11_OUI_HEADER dot11OUIHeader;
    UCHAR OUISubType;
    UCHAR Version;
    DOT11_WME_TS_INFO dot11TSInfo;
    DOT11_WME_NOMINAL_MSDU_SIZE dot11NominalMSDUSize;
    USHORT usMaxMSDUSize;
    ULONG uMinServiceInterval;
    ULONG uMaxServiceInternal;
    ULONG uInactivityInterval;
    ULONG uServiceStartTime;
    ULONG uMinimumDataRate;
    ULONG uMeanDataRate;
    ULONG uMaxBurstSize;
    ULONG uMinPhyRate;
    ULONG uPeakDataRate;
    ULONG uDelayBound;
    DOT11_WME_SURPLUS_BANDWIDTH_ALLOWANCE_FACTOR dot11WMESurplusBandwidthAllowance;
    USHORT usMediumTime;
} DOT11_WME_TSPEC, * PDOT11_WME_TSPEC;

typedef union DOT11_HT_CAPABILITIES_INFO {
    struct {
        USHORT LDPCCoding: 1;               // LDPC coding capabilities
        USHORT SupportedChannelWidth: 1;    // Supported channel width set
        USHORT SMPowerSave: 2;  // SM Power Save
        USHORT ShortGI_20: 1;   // short GI for 20 MHz
        USHORT ShortGI_40: 1;   // short GI for 40 MHz
        USHORT TxSTBC: 1;
        USHORT RxSTBC: 2;
        USHORT HTDelayedBlockAck: 1;
        USHORT MaxAMSDULength: 1;
        USHORT DSSSCCK_40: 1;
        USHORT PSMP: 1;
        USHORT Intolerant_40: 1;        // 40 MHz intolerant
        USHORT LSIGTXOPProtection: 1;
    };

    USHORT Value;
} DOT11_HT_CAPABILITIES_INFO, * PDOT11_HT_CAPABILITIES_INFO;

typedef struct DOT11_MCS_SET {
    ULONGLONG RxMCSBitmask00_63;

    ULONG RxMCSBitmask64_76: 13;
    ULONG Reserved_77: 3;
    ULONG HighestSupportedRate: 10;
    ULONG Reserved_90: 6;

    ULONG TxMCSSetDefined: 1;
    ULONG TxRxMCSSetNotEqual: 1;
    ULONG TxMaxNumSpatialStreamsSupported: 2;
    ULONG TxUnequalModulationSupported: 1;
    ULONG Reserved_101: 27;
} DOT11_MCS_SET, * PDOT11_MCS_SET;

typedef union DOT11_HT_EXT_CAPABILITIES {
    struct {
        USHORT PCO: 1;
        USHORT PCOTransTime: 2;
        USHORT Rserved_3: 5;
        USHORT MCSFeedback: 2;
        USHORT HTCSupport: 1;
        USHORT RDResponder: 1;
        USHORT Reserved_12: 4;
    };

    USHORT Value;
} DOT11_HT_EXT_CAPABILITIES, * PDOT11_HT_EXT_CAPABILITIES;

typedef union DOT11_TX_BEAMFORMING_CAPABILITIES {
    struct {
        ULONG ImplicitTxBFRxCapable: 1;

        ULONG RxStaggeredSoundingCapable: 1;
        ULONG TxStaggeredSoundingCapable: 1;

        ULONG RxNDPCapable: 1;
        ULONG TxNDPCapable: 1;

        ULONG ImplicitTxBFCapable: 1;
        ULONG Calibration: 2;

        ULONG ExplicitCSITxBFCapable: 1;
        ULONG ExplicitNonCompressedBFFeedbackMatrixCapable: 1;
        ULONG ExplicitCompressedBFFeedbackMatrixCapable: 1;

        ULONG ExplicitTxBFCSIFeedbackCapable: 1;

        ULONG ExplicitNonCompressedBFFeedbackMatrix: 2;
        ULONG ExplicitCompressedBFFeedbackMatrix: 2;

        ULONG MinimalGrouping: 2;

        ULONG CSINumBFAntennas: 2;
        ULONG NonCompressedBFFeedbackNumBFAntennas: 2;
        ULONG CompressedBFFeedbackNumBFAntennas: 2;

        ULONG CSIMaxNumRowsBFSupported: 2;

        ULONG ChannelEstimationCapability: 2;
        ULONG Reserved_29: 3;
    };

    ULONG Value;
} DOT11_TX_BEAMFORMING_CAPABILITIES, * PDOT11_TX_BEAMFORMING_CAPABILITIES;

typedef union DOT11_ANTENNA_SELECTION_CAPABILITIES {
    struct {
        UCHAR ASELCapable: 1;

        UCHAR ExplicitCSIFeedbackBasedTxASELCapable: 1;
        UCHAR AntennaIndicesFeedbackBasedTxASELCapable: 1;

        UCHAR ExplicitCSIFeedbackCapable: 1;
        UCHAR AntennaIndicesFeedbackCapable: 1;

        UCHAR RxASELCapable: 1;
        UCHAR TxSoundingPPDUCapable: 1;
        UCHAR Reserved_7: 1;
    };

    UCHAR Value;
} DOT11_ANTENNA_SELECTION_CAPABILITIES, * PDOT11_ANTENNA_SELECTION_CAPABILITIES;


typedef struct DOT11_HT_CAPABILITIES {
    DOT11_HT_CAPABILITIES_INFO Info;

    UCHAR AMSDUParam;

    DOT11_MCS_SET SupportedMCSSet;
    DOT11_HT_EXT_CAPABILITIES ExtendedCapabilities;
    DOT11_TX_BEAMFORMING_CAPABILITIES TxBFCapabilities;
    DOT11_ANTENNA_SELECTION_CAPABILITIES AntennaSelectionCapabilities;
} DOT11_HT_CAPABILITIES, * PDOT11_HT_CAPABILITIES;

//
//
//

typedef struct DOT11_BEACON_FRAME {
    ULONGLONG           Timestamp;      // the value of sender's TSFTIMER
    USHORT              BeaconInterval; // the number of time units between target beacon transmission times
    DOT11_CAPABILITY    Capability;
    DOT11_INFO_ELEMENT  InfoElements;
} DOT11_BEACON_FRAME, * PDOT11_BEACON_FRAME;

typedef ULONG DOT11_CRC, * PDOT11_CRC;

//
// Reason code
//

#define DOT11_MGMT_REASON_UPSPEC_REASON                 1
#define DOT11_MGMT_REASON_AUTH_NOT_VALID                2
#define DOT11_MGMT_REASON_DEAUTH_LEAVE_SS               3
#define DOT11_MGMT_REASON_INACTIVITY                    4
#define DOT11_MGMT_REASON_AP_OVERLOAD                   5
#define DOT11_MGMT_REASON_CLASS2_ERROR                  6
#define DOT11_MGMT_REASON_CLASS3_ERROR                  7
#define DOT11_MGMT_REASON_DISASSO_LEAVE_SS              8
#define DOT11_MGMT_REASON_ASSO_NOT_AUTH                 9
#define DOT11_MGMT_REASON_INVALID_IE                    13
#define DOT11_MGMT_REASON_MIC_FAILURE                   14
#define DOT11_MGMT_REASON_4WAY_HANDSHAKE_TIMEOUT        15
#define DOT11_MGMT_REASON_2WAY_HANDSHAKE_TIMEOUT        16
#define DOT11_MGMT_REASON_INCONSISTENT_IE               17
#define DOT11_MGMT_REASON_INVALID_GROUP_CIPHER          18
#define DOT11_MGMT_REASON_INVALID_PAIRWISE_CIPHER       19
#define DOT11_MGMT_REASON_INVALID_AKMP                  20
#define DOT11_MGMT_REASON_UNSUPPORTED_RSN_IE_VERSION    21
#define DOT11_MGMT_REASON_INVALID_RSN_IE_CAPABILITIES   22
#define DOT11_MGMT_REASON_1X_FAILURE                    23
#define DOT11_MGMT_REASON_CIPHER_SUITE_REJECTED         24

//
// The constants used in the Status Code fixed field in a frame
//

// Successful
#define DOT11_FRAME_STATUS_SUCCESSFUL                               0

// Unspecified Failure
#define DOT11_FRAME_STATUS_FAILURE                                  1

// Cannot support all requested capabilities in the Capability Information field
#define DOT11_FRAME_STATUS_UNSUPPORTED_CAPABILITIES                 10

// Reassociation denied due to inability to confirm that association exists
#define DOT11_FRAME_STATUS_REASSOC_DENIED                           11

// Association denied due to reason outside the scope of this standard
#define DOT11_FRAME_STATUS_ASSOC_DENIED                             12

// Responding station does not support the specified authentication algorithm
#define DOT11_FRAME_STATUS_UNSUPPORTED_AUTH_ALGO                    13

// Received an Authentication frame with authentication transaction
// sequence number out of expected sequence
#define DOT11_FRAME_STATUS_INVALID_AUTH_XID                         14

// Authentication rejected because of challenge failure
#define DOT11_FRAME_STATUS_INVALID_AUTH_CHALLENGE                   15

// Authenticaiton rejected due to timeout waiting for next frame in sequence
#define DOT11_FRAME_STATUS_AUTH_TIME_OUT                            16

// Association denied because AP is unable to handle additional associated stations
#define DOT11_FRAME_STATUS_ASSOC_DENIED_AP_BUSY                     17

// Association denied due to requesting station not supporting all of the data
// rates in the BSSBasicRateSet parameter
#define DOT11_FRAME_STATUS_ASSOC_DENIED_DATA_RATE_SET               18

// Association denied because short preamble not supported
#define DOT11_FRAME_STATUS_UNSUPPORTED_SHORT_PREAMBLE               19

// Association denied because PBCC not supported
#define DOT11_FRAME_STATUS_UNSUPPORTED_PBCC                         20

// Association denied because channel agility not supported
#define DOT11_FRAME_STATUS_UNSUPPORTED_CHANNEL_AGILITY              21

// Association denied because short slot time option not supported
#define DOT11_FRAME_STATUS_UNSUPPORTED_SHORT_SLOT_TIME              25

// Association denied because DSSS-OFDM option not supported
#define DOT11_FRAME_STATUS_UNSUPPORTED_DSSSOFDM                     26

// Invalid Information Element
#define DOT11_FRAME_STATUS_INVALID_IE                               40
#define DOT11_FRAME_STATUS_INVALID_GROUP_CIPHER                     41
#define DOT11_FRAME_STATUS_INVALID_PAIRWISE_CIPHER                  42
#define DOT11_FRAME_STATUS_INVALID_AKMP                             43
#define DOT11_FRAME_STATUS_UNSUPPORTED_RSN_IE_VERSION               44
#define DOT11_FRAME_STATUS_INVALID_RSN_IE_CAPABILITIES              45
#define DOT11_FRAME_STATUS_CIPHER_SUITE_REJECTED                    46

// Association denied because parent address list matching error (MSIE)
#define DOT11_FRAME_STATUS_PAL_ERROR                                30001


//
// The fixed part of an authentication frame
//

#define DOT11_AUTH_OPEN_SYSTEM  0
#define DOT11_AUTH_SHARED_KEY   1

typedef struct DOT11_AUTH_FRAME {
    USHORT usAlgorithmNumber;
    USHORT usXid;
    USHORT usStatusCode;
} DOT11_AUTH_FRAME, * PDOT11_AUTH_FRAME;

typedef struct _DOT11_DEAUTH_FRAME{
  USHORT    ReasonCode;
} DOT11_DEAUTH_FRAME, *PDOT11_DEAUTH_FRAME;

typedef struct DOT11_ASSOC_REQUEST_FRAME {
    DOT11_CAPABILITY Capability;
    USHORT usListenInterval;

    // SSID
    // Supported Rates

} DOT11_ASSOC_REQUEST_FRAME, * PDOT11_ASSOC_REQUEST_FRAME;

typedef struct DOT11_REASSOC_REQUEST_FRAME {
    DOT11_CAPABILITY Capability;
    USHORT usListenInterval;

    DOT11_MAC_ADDRESS CurrentAPAddress;

} DOT11_REASSOC_REQUEST_FRAME, * PDOT11_REASSOC_REQUEST_FRAME;

typedef struct DOT11_ASSOC_RESPONSE_FRAME {
    DOT11_CAPABILITY Capability;
    USHORT usStatusCode;
    USHORT usAID;

    // Supported Rates

} DOT11_ASSOC_RESPONSE_FRAME, * PDOT11_ASSOC_RESPONSE_FRAME;

typedef struct DOT11_REASSOC_RESPONSE_FRAME {
    DOT11_CAPABILITY Capability;
    USHORT usStatusCode;
    USHORT usAID;

    // Supported Rates

} DOT11_REASSOC_RESPONSE_FRAME, * PDOT11_REASSOC_RESPONSE_FRAME;

typedef struct DOT11_DISASSOC_FRAME {
    USHORT usReasonCode;
} DOT11_DISASSOC_FRAME, * PDOT11_DISASSOC_FRAME;


#include <packoff.h>


#endif // __802_11_HDR_H__
