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
//////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation. All rights reserved.			//
//////////////////////////////////////////////////////////////////////////


#ifndef _TSP_H_
#define _TSP_H_


#include <windows.h>


#ifdef __cplusplus
extern "C" {
#endif


/* String constants used to identify the CellTSP */
#define CELLTSP_PROVIDERINFO_STRING (L"Cellular TAPI Service Provider")
#define CELLTSP_LINENAME_STRING (L"Cellular Line")
#define CELLTSP_PHONENAME_STRING (L"Cellular Phone")


/* Maximum length constants */
#define CELLDEVCONFIG_MAXLENGTH_GPRSACCESSPOINTNAME (64)
#define CELLDEVCONFIG_MAXLENGTH_GPRSADDRESS         (64)
#define CELLDEVCONFIG_MAXLENGTH_GPRSPARAMETERS      (32)


/* LINEBEARERMODE_ constant to identify GPRS calls */
#define LINEBEARERMODE_GPRS (LINEBEARERMODE_DATA << 16)
// When using RAS, the following string MUST be used as the destination address for all GPRS calls
#define GPRS_DEST_ADDRESS (L"~GPRS!")

/* LINEDISCONNECTMODE_ constants to provide more detailed error reporting */
#define LINEDISCONNECTMODE_PHONECONNECTIONFAILURE      (LINEDISCONNECTMODE_NORMAL | (0xd0<<16))
#define LINEDISCONNECTMODE_INVALIDSIMCARD              (LINEDISCONNECTMODE_NORMAL | (0xd1<<16))
#define LINEDISCONNECTMODE_SIMCARDBUSY                 (LINEDISCONNECTMODE_NORMAL | (0xd2<<16))
#define LINEDISCONNECTMODE_NETWORKSERVICENOTAVAILABLE  (LINEDISCONNECTMODE_NORMAL | (0xd3<<16))
#define LINEDISCONNECTMODE_EMERGENCYONLY               (LINEDISCONNECTMODE_NORMAL | (0xd4<<16))


/* Caller ID options for LINECALLPARAMSDEVSPECIFIC structure */
enum CALLER_ID_OPTIONS {
    CALLER_ID_DEFAULT,  /* Accept the default behavior */
    CALLER_ID_BLOCK,    /* Block sending of caller-ID information, overriding the current default if necessary */
    CALLER_ID_PRESENT,  /* Send caller-ID information, overriding the current default if necessary */
};

/* Structure that can be passed as data for LINECALLPARAMS.dwDevSpecific[Size, Offset] */
typedef struct linecallparamsdevspecific_tag {
    CALLER_ID_OPTIONS cidoOptions;
} LINECALLPARAMSDEVSPECIFIC, *LPLINECALLPARAMSDEVSPECIFIC;


/* Bearer Service CE constants define bearer service connection elements for CELLBEARERINFO structure */
#define CELLDEVCONFIG_CONNELEM_UNKNOWN              (0x00000000)  // Bearer service unknown
#define CELLDEVCONFIG_CONNELEM_TRANSPARENT          (0x00000001)  // Link layer correction enabled
#define CELLDEVCONFIG_CONNELEM_NONTRANSPARENT       (0x00000002)  // No link layer correction present
#define CELLDEVCONFIG_CONNELEM_BOTH_TRANSPARENT     (0x00000003)  // Both available, transparent preferred
#define CELLDEVCONFIG_CONNELEM_BOTH_NONTRANSPARENT  (0x00000004)  // Both available, non-transparent preferred

/* Telephony service type constants for CELLBEARERINFO structure
   These flags only apply for data access.  When a voice call is being
   placed, this flag is ignored. */
#define CELLDEVCONFIG_SERVICE_UNKNOWN               (0x00000000)  // Unknown service
#define CELLDEVCONFIG_SERVICE_MODEM_ASYNC           (0x00000001)  // Asynchronous modem
#define CELLDEVCONFIG_SERVICE_MODEM_SYNC            (0x00000002)  // Synchronous modem
#define CELLDEVCONFIG_SERVICE_PADACCESS_ASYNC       (0x00000003)  // PAD Access (asynchronous)
#define CELLDEVCONFIG_SERVICE_PACKETACCESS_SYNC     (0x00000004)  // Packet Access (synchronous)

/* Data rate constants define protocol dependent data rates for CELLBEARERINFO structure */
#define CELLDEVCONFIG_SPEED_UNKNOWN                 (0x00000000)  // Unknown speed
#define CELLDEVCONFIG_SPEED_AUTO                    (0x00000001)  // Automatic selection of speed
#define CELLDEVCONFIG_SPEED_300_V21                 (0x00000002)  // 300 bps      (V.21)
#define CELLDEVCONFIG_SPEED_300_V110                (0x00000003)  // 300 bps      (V.100)
#define CELLDEVCONFIG_SPEED_1200_V22                (0x00000004)  // 1200 bps     (V.22)
#define CELLDEVCONFIG_SPEED_1200_75_V23             (0x00000005)  // 1200/75 bps  (V.23)
#define CELLDEVCONFIG_SPEED_1200_V110               (0x00000006)  // 1200 bps     (V.100)
#define CELLDEVCONFIG_SPEED_1200_V120               (0x00000007)  // 1200 bps     (V.120)
#define CELLDEVCONFIG_SPEED_2400_V22BIS             (0x00000008)  // 2400 bps     (V.22bis)
#define CELLDEVCONFIG_SPEED_2400_V26TER             (0x00000009)  // 2400 bps     (V.26ter)
#define CELLDEVCONFIG_SPEED_2400_V110               (0x0000000a)  // 2400 bps     (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_2400_V120               (0x0000000b)  // 2400 bps     (V.120)
#define CELLDEVCONFIG_SPEED_4800_V32                (0x0000000c)  // 4800 bps     (V.32)
#define CELLDEVCONFIG_SPEED_4800_V110               (0x0000000d)  // 4800 bps     (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_4800_V120               (0x0000000e)  // 4800 bps     (V.120)
#define CELLDEVCONFIG_SPEED_9600_V32                (0x0000000f)  // 9600 bps     (V.32)
#define CELLDEVCONFIG_SPEED_9600_V34                (0x00000010)  // 9600 bps     (V.34)
#define CELLDEVCONFIG_SPEED_9600_V110               (0x00000011)  // 9600 bps     (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_9600_V120               (0x00000012)  // 9600 bps     (V.120)
#define CELLDEVCONFIG_SPEED_14400_V34               (0x00000013)  // 14400 bps    (V.34)
#define CELLDEVCONFIG_SPEED_14400_V110              (0x00000014)  // 14400 bps    (V.100 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_14400_V120              (0x00000015)  // 14400 bps    (V.120)
#define CELLDEVCONFIG_SPEED_19200_V34               (0x00000016)  // 19200 bps    (V.34)
#define CELLDEVCONFIG_SPEED_19200_V110              (0x00000017)  // 19200 bps    (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_19200_V120              (0x00000018)  // 19200 bps    (V.120)
#define CELLDEVCONFIG_SPEED_28800_V34               (0x00000019)  // 28800 bps    (V.34)
#define CELLDEVCONFIG_SPEED_28800_V110              (0x0000001a)  // 28800 bps    (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_28800_V120              (0x0000001b)  // 28800 bps    (V.120)
#define CELLDEVCONFIG_SPEED_38400_V110              (0x0000001c)  // 38400 bps    (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_38400_V120              (0x0000001d)  // 38400 bps    (V.120)
#define CELLDEVCONFIG_SPEED_48000_V110              (0x0000001e)  // 48000 bps    (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_48000_V120              (0x0000001f)  // 48000 bps    (V.120)
#define CELLDEVCONFIG_SPEED_56000_V110              (0x00000020)  // 56000 bps    (V.110 or X.31 flag stuffing)
#define CELLDEVCONFIG_SPEED_56000_V120              (0x00000021)  // 56000 bps    (V.120)
#define CELLDEVCONFIG_SPEED_56000_TRANSP            (0x00000022)  // 56000 bps    (bit transparent)
#define CELLDEVCONFIG_SPEED_64000_TRANSP            (0x00000023)  // 64000 bps    (bit transparent)
#define CELLDEVCONFIG_SPEED_32000_PIAFS32K          (0x00000024)      // 32000 bps (PIAFS32k)
#define CELLDEVCONFIG_SPEED_64000_PIAFS64K          (0x00000025)      //  64000 bps (PIAFS64k)
#define CELLDEVCONFIG_SPEED_28800_MULTIMEDIA        (0x00000026)      //  28800 bps (MultiMedia)
#define CELLDEVCONFIG_SPEED_32000_MULTIMEDIA        (0x00000027)      //  32000 bps (MultiMedia)
#define CELLDEVCONFIG_SPEED_33600_MULTIMEDIA        (0x00000028)      //  33600 bps (MultiMedia)
#define CELLDEVCONFIG_SPEED_56000_MULTIMEDIA        (0x00000029)      //  56000 bps (MultiMedia)
#define CELLDEVCONFIG_SPEED_64000_MULTIMEDIA        (0x0000002a)      //  64000 bps (MultiMedia)

/* Data compression directions constants for CELLDATACOMPINFO structure */
#define CELLDEVCONFIG_DATACOMPDIR_UNKNOWN           (0x00000000)  // Unknown direction
#define CELLDEVCONFIG_DATACOMPDIR_NONE              (0x00000001)  // No compression
#define CELLDEVCONFIG_DATACOMPDIR_TRANSMIT          (0x00000002)  // Transmit only
#define CELLDEVCONFIG_DATACOMPDIR_RECEIVE           (0x00000003)  // Receive only
#define CELLDEVCONFIG_DATACOMPDIR_BOTH              (0x00000004)  // Both directions, accept any direction

/* GPRS data compression settings constants for CELLGPRSCONNECTIONINFO structure */
#define CELLDEVCONFIG_GPRSCOMPRESSION_UNKNOWN       (0x00000000)  // Compression unknown
#define CELLDEVCONFIG_GPRSCOMPRESSION_OFF           (0x00000001)  // Compression off
#define CELLDEVCONFIG_GPRSCOMPRESSION_ON            (0x00000002)  // Compression on

/* GPRS protocol identifier constants for CELLGPRSCONNECTIONINFO structure */
#define CELLDEVCONFIG_GPRSPROTOCOL_UNKNOWN       (0x00000000)  // Unknown
#define CELLDEVCONFIG_GPRSPROTOCOL_X25           (0x00000001)  // Unsupported
#define CELLDEVCONFIG_GPRSPROTOCOL_IP            (0x00000002)  // IP (Radio acts as PPP server)
#define CELLDEVCONFIG_GPRSPROTOCOL_IHOSP         (0x00000003)  // Unsupported
#define CELLDEVCONFIG_GPRSPROTOCOL_PPP           (0x00000004)  // Point to Point protocol (PPP frames forwarded to end server)

/* GPRS L2 protocol identifier constants for CELLGPRSCONNECTIONINFO structure */
#define CELLDEVCONFIG_GPRSL2PROTOCOL_UNKNOWN     (0x00000000)  // Unknown
#define CELLDEVCONFIG_GPRSL2PROTOCOL_NULL        (0x00000001)  // Unsupported
#define CELLDEVCONFIG_GPRSL2PROTOCOL_PPP         (0x00000002)  // WinCE uses PPP
#define CELLDEVCONFIG_GPRSL2PROTOCOL_PAD         (0x00000003)  // Unsupported
#define CELLDEVCONFIG_GPRSL2PROTOCOL_X25         (0x00000004)  // Unsupported

/* GPRS precedence classes for CELLGPRSQOSSETTINGS structure */
#define CELLDEVCONFIG_GPRSPRECEDENCECLASS_UNKNOWN             (0x00000000)  // Unknown
#define CELLDEVCONFIG_GPRSPRECEDENCECLASS_SUBSCRIBED          (0x00000001)  // Subscribed value stored in network
#define CELLDEVCONFIG_GPRSPRECEDENCECLASS_HIGH                (0x00000002)  // High priority
#define CELLDEVCONFIG_GPRSPRECEDENCECLASS_NORMAL              (0x00000003)  // Normal priority
#define CELLDEVCONFIG_GPRSPRECEDENCECLASS_LOW                 (0x00000004)  // Low priority

/* GPRS delay classes for CELLGPRSQOSSETTINGS structure */
#define CELLDEVCONFIG_GPRSDELAYCLASS_UNKNOWN                 (0x00000000)  // Unknown
#define CELLDEVCONFIG_GPRSDELAYCLASS_SUBSCRIBED              (0x00000001)
#define CELLDEVCONFIG_GPRSDELAYCLASS_PREDICTIVE1             (0x00000002)
#define CELLDEVCONFIG_GPRSDELAYCLASS_PREDICTIVE2             (0x00000003)
#define CELLDEVCONFIG_GPRSDELAYCLASS_PREDICTIVE3             (0x00000004)
#define CELLDEVCONFIG_GPRSDELAYCLASS_BESTEFFORT              (0x00000005)

/* GPRS reliability classes for CELLGPRSQOSSETTINGS structure */
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_UNKNOWN           (0x00000000)  // Unknown
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_SUBSCRIBED        (0x00000001)
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_1                 (0x00000002)
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_2                 (0x00000003)
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_3                 (0x00000004)
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_4                 (0x00000005)
#define CELLDEVCONFIG_GPRSRELIABILITYCLASS_5                 (0x00000006)

/* GPRS peak throughput classes for CELLGPRSQOSSETTINGS structure */
#define CELLDEVCONFIG_PEAKTHRUCLASS_UNKNOWN                  (0x00000000)  // Unknown
#define CELLDEVCONFIG_PEAKTHRUCLASS_SUBSCRIBED               (0x00000001)
#define CELLDEVCONFIG_PEAKTHRUCLASS_8000                     (0x00000002)  // kbit/second
#define CELLDEVCONFIG_PEAKTHRUCLASS_16000                    (0x00000003)
#define CELLDEVCONFIG_PEAKTHRUCLASS_32000                    (0x00000004)
#define CELLDEVCONFIG_PEAKTHRUCLASS_64000                    (0x00000005)
#define CELLDEVCONFIG_PEAKTHRUCLASS_128000                   (0x00000006)
#define CELLDEVCONFIG_PEAKTHRUCLASS_256000                   (0x00000007)
#define CELLDEVCONFIG_PEAKTHRUCLASS_512000                   (0x00000008)
#define CELLDEVCONFIG_PEAKTHRUCLASS_1024000                  (0x00000009)
#define CELLDEVCONFIG_PEAKTHRUCLASS_2048000                  (0x0000000a)

/* GPRS mean throughput classes for CELLGPRSQOSSETTINGS structure */
#define CELLDEVCONFIG_MEANTHRUCLASS_UNKNOWN                  (0x00000000)  // Unknown
#define CELLDEVCONFIG_MEANTHRUCLASS_SUBSCRIBED               (0x00000001)
#define CELLDEVCONFIG_MEANTHRUCLASS_100                      (0x00000002)  // octets/hour
#define CELLDEVCONFIG_MEANTHRUCLASS_200                      (0x00000003)
#define CELLDEVCONFIG_MEANTHRUCLASS_500                      (0x00000004)
#define CELLDEVCONFIG_MEANTHRUCLASS_1000                     (0x00000005)
#define CELLDEVCONFIG_MEANTHRUCLASS_2000                     (0x00000006)
#define CELLDEVCONFIG_MEANTHRUCLASS_5000                     (0x00000007)
#define CELLDEVCONFIG_MEANTHRUCLASS_10000                    (0x00000008)
#define CELLDEVCONFIG_MEANTHRUCLASS_20000                    (0x00000009)
#define CELLDEVCONFIG_MEANTHRUCLASS_50000                    (0x0000000a)
#define CELLDEVCONFIG_MEANTHRUCLASS_100000                   (0x0000000b)
#define CELLDEVCONFIG_MEANTHRUCLASS_200000                   (0x0000000c)
#define CELLDEVCONFIG_MEANTHRUCLASS_500000                   (0x0000000d)
#define CELLDEVCONFIG_MEANTHRUCLASS_1000000                  (0x0000000e)
#define CELLDEVCONFIG_MEANTHRUCLASS_2000000                  (0x0000000f)
#define CELLDEVCONFIG_MEANTHRUCLASS_5000000                  (0x00000010)
#define CELLDEVCONFIG_MEANTHRUCLASS_10000000                 (0x00000011)
#define CELLDEVCONFIG_MEANTHRUCLASS_20000000                 (0x00000012)
#define CELLDEVCONFIG_MEANTHRUCLASS_50000000                 (0x00000013)
#define CELLDEVCONFIG_MEANTHRUCLASS_DONTCARE                 (0x00000014)  // Best effort

/* Flags for the CELLDEVCONFIG structure */
#define CELLDEVCONFIG_FLAG_TERMINALAFTERDIALING              (0x00000001)  // (Only valid when used with lineSetDevConfig)


/* Structure containing bearer information
   Used to set different bearers, specifically to enable quick connect. */
typedef struct CELLBEARERINFO_tag {
    DWORD dwSpeed;              /* One of the CELLDEVCONFIG_SPEED_* constants */
    DWORD dwService;            /* One of the CELLDEVCONFIG_SERVICE_* constants */
    DWORD dwConnectionElement;  /* One of the CELLDEVCONFIG_CONNELEM_* constants */
} CELLBEARERINFO, *LPCELLBEARERINFO;

/* Structure containing data compression information
   Used for v.42bis compression settings. */
typedef struct CELLDATACOMPINFO_tag {
    DWORD dwDirection;        /* One of the CELLDEVCONFIG_DATACOMPDIR_* constants */
    BOOL  dwRequired;         /* Data compression required */
    DWORD dwMaxDictEntries;   /* Maximum number of dictionary entries */
    DWORD dwMaxStringLength;  /* Maximum string length */
} CELLDATACOMPINFO, *LPCELLDATACOMPINFO;

/* Structure containing radio link protocol settings
   Radio link protocol is a link layer correction protocol that increases
   the perceived reliability of the air link. */
typedef struct CELLRADIOLINKINFO_tag {
    DWORD dwVersion;             /* Version number */
    DWORD dwIws;                 /* IWF to MS window size  */
    DWORD dwMws;                 /* MS to IWF window size  */
    DWORD dwAckTimer;            /* Acknowledgement timer [T1] (milliseconds) */
    DWORD dwRetransmitAttempts;  /* Retransmit attempts [N2] */
    DWORD dwResequenceTimer;     /* Resequence timer [T4] (milliseconds) */
} CELLRADIOLINKINFO, *LPCELLRADIOLINKINFO;

/* Structure containing GPRS Quality Of Service (QOS) settings
   Used to specify minimum and requested QOS settings */
typedef struct CELLGPRSQOSSETTINGS_tag {
    DWORD dwPrecedenceClass;                               /* One of the CELLDEVCONFIG_GPRSPRECEDENCECLASS_* constants */
    DWORD dwDelayClass;                                    /* One of the CELLDEVCONFIG_GPRSDELAYCLASS_* constants */
    DWORD dwReliabilityClass;                              /* One of the CELLDEVCONFIG_GPRSRELIABILITYCLASS_* constants */
    DWORD dwPeakThruClass;                                 /* One of the CELLDEVCONFIG_GPRSPEAKTHRUCLASS_* constants */
    DWORD dwMeanThruClass;                                 /* One of the CELLDEVCONFIG_GPRSMEANTHRUCLASS_* constants */
} CELLGPRSQOSSETTINGS, *LPCELLGPRSQOSSETTINGS;

/* Structure containing GPRS connection information
   Used in the initiation of GPRS calls. */
typedef struct CELLGPRSCONNECTIONINFO_tag {
    DWORD                dwProtocolType;                                                    /* One of the CELLDEVCONFIG_GPRSPROTOCOL_* constants */
    DWORD                dwL2ProtocolType;                                                  /* One of the CELLDEVCONFIG_GPRSL2PROTOCOL_* constants */
    WCHAR                wszAccessPointName[CELLDEVCONFIG_MAXLENGTH_GPRSACCESSPOINTNAME];   /* Logical name to select the GPRS gateway  */
    WCHAR                wszAddress[CELLDEVCONFIG_MAXLENGTH_GPRSADDRESS];                   /* The packet address to use (if empty, then a dynamic address will be requested) */
    DWORD                dwDataCompression;                                                 /* One of the CELLDEVCONFIG_GPRSCOMPRESSION_* constants */
    DWORD                dwHeaderCompression;                                               /* One of the CELLDEVCONFIG_GPRSCOMPRESSION_* constants */
    char                 szParameters[CELLDEVCONFIG_MAXLENGTH_GPRSPARAMETERS];              /* Prococol-specific parameters (NULL terminated) */
    BOOL                 bRequestedQOSSettingsValid;                                        /* TRUE iff sgqsRequestedQOSSettings is valid */
    CELLGPRSQOSSETTINGS  cgqsRequestedQOSSettings;                                          /* GPRS QOS settings structure */
    BOOL                 bMinimumQOSSettingsValid;                                          /* TRUE iff sgqsMinimumQOSSettings is valid */
    CELLGPRSQOSSETTINGS  cgqsMinimumQOSSettings;                                            /* GPRS QOS settings structure */
} CELLGPRSCONNECTIONINFO, *LPCELLGPRSCONNECTIONINFO;

/* A service-provider-specific configuration structure
   This structure is specific to this version of this TSP.  Future versions
   may append additional data elements to the end of this structure. */
typedef struct CELLDEVCONFIG_tag {
    DWORD                   dwTotalSize;               /* Standard TAPI structure variable */
    DWORD                   dwNeededSize;              /* Standard TAPI structure variable */
    DWORD                   dwUsedSize;                /* Standard TAPI structure variable */
    BOOL                    bBearerInfoValid;          /* TRUE iff sbiBearerInfo is valid */
    CELLBEARERINFO          cbiBearerInfo;             /* Bearer structure */
    BOOL                    bDataCompInfoValid;        /* TRUE iff sdciDataCompInfo is valid */
    CELLDATACOMPINFO        cdciDataCompInfo;          /* Data compression structure */
    BOOL                    bRadioLinkInfoValid;       /* TRUE iff srliRadioLinkInfo is valid */
    CELLRADIOLINKINFO       crliRadioLinkInfo;         /* RLP structure */
    BOOL                    bGPRSConnectionInfoValid;  /* TRUE iff sgciGPRSConnectionInfo is valid */
    CELLGPRSCONNECTIONINFO  cgciGPRSConnectionInfo;    /* GPRS connection structure */
    DWORD                   dwFlags;                   /* Bit-mask of CELLDEVCONFIG_FLAG_* constants */
} CELLDEVCONFIG, *LPCELLDEVCONFIG;


#ifdef __cplusplus
}
#endif


#endif  // _TSP_H_
