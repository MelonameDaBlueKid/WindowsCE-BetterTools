//////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation. All rights reserved.            //
//////////////////////////////////////////////////////////////////////////


#ifndef _WAP_H_
#define _WAP_H_


//
// Errors
//

#define FACILITY_WAP                            0x500

// WTLS errors
#define WAP_E_WTLS                              MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WAP, 0x0001)
#define WAP_E_WTLS_CERTIFICATE                  MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WAP, 0x0002)
#define WAP_E_WTLS_HANDSHAKE                    MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WAP, 0x0003)
#define WAP_E_WTLS_CRYPTERROR                   MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WAP, 0x0004)
#define WAP_E_WTLS_BADMAC                       MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WAP, 0x0005)


//
// Constants
//

// Maximum sizes
#define MAX_WAP_ADDRESS_LENGTH                  (64)

// WDP field identifiers
#define WDP_FIELD_NONE                          (0x00000000)
#define WDP_FIELD_SOURCEADDRESS                 (0x00000001)
#define WDP_FIELD_SOURCEPORT                    (0x00000002)
#define WDP_FIELD_DESTINATIONADDRESS            (0x00000004)
#define WDP_FIELD_DESTINATIONPORT               (0x00000008)
#define WDP_FIELD_USERDATA                      (0x00000010)
/*
#define WDP_FIELD_ERRORCODE                     (0x00000020)
*/

// WTP field identifiers
#define WTP_FIELD_NONE                          (0x00000000)
#define WTP_FIELD_SOURCEADDRESS                 (0x00000001)
#define WTP_FIELD_SOURCEPORT                    (0x00000002)
#define WTP_FIELD_DESTINATIONADDRESS            (0x00000004)
#define WTP_FIELD_DESTINATIONPORT               (0x00000008)
#define WTP_FIELD_USERACKNOWLEDGEMENT           (0x00000010)
#define WTP_FIELD_WANTSECURETRANSACTION         (0x00000020)
#define WTP_FIELD_USERDATA                      (0x00000040)
#define WTP_FIELD_CLASSTYPE                     (0x00000080)
#define WTP_FIELD_EXITINFO                      (0x00000100)
#define WTP_FIELD_HANDLE                        (0x00000200)
#define WTP_FIELD_ABORTCODE                     (0x00000400)
#define WTP_FIELD_TRANSACTIONSECURITYLEVEL      (0x00000800)

// WAP layers
enum WAP_LAYER
    {
    WAP_LAYER_WDP = 1,
    WAP_LAYER_WTLS,
    WAP_LAYER_WTP,
    WAP_LAYER_WSP,
    WAP_LAYER_WAE,
    };

// WAP primitives
enum WAP_PRIMITIVE_ID
    {
    WAP_PRIMITIVE_ID_T_DUNITDATA = 1,
/*
    WAP_PRIMITIVE_ID_T_DERROR,
*/
    WAP_PRIMITIVE_ID_TR_INVOKE,
    WAP_PRIMITIVE_ID_TR_RESULT,
    WAP_PRIMITIVE_ID_TR_ABORT,
    };

// WAP primitive type
enum WAP_PRIMITIVE_TYPE
    {
    WAP_PRIMITIVE_TYPE_REQUEST = 1,
    WAP_PRIMITIVE_TYPE_INDICATION,
    WAP_PRIMITIVE_TYPE_RESPONSE,
    WAP_PRIMITIVE_TYPE_CONFIRM,
    };

// WAP address types
enum WAP_ADDRESS_TYPE
    {
    WAP_ADDRESS_TYPE_UDP = 1,
    WAP_ADDRESS_TYPE_GSM_SMS,
    };

// WAP address structure
typedef struct WAP_ADDRESS_tag
    {
    WAP_ADDRESS_TYPE watAddressType;
    TCHAR ptsAddress[MAX_WAP_ADDRESS_LENGTH];
    } WAP_ADDRESS;

typedef DWORD WAP_HANDLE;

// WTP transaction class types
enum WTP_TRANSACTION_CLASS_TYPE
    {
    WTP_TRANSACTION_CLASS_TYPE_0 = 1,
    WTP_TRANSACTION_CLASS_TYPE_1,
    WTP_TRANSACTION_CLASS_TYPE_2,
    };

// WTP secure transaction (WTLS) security levels
enum WTP_TRANSACTION_SECURITY_LEVEL
    {
    WTP_TRANSACTION_SECURITY_LEVEL_NOTSECURE = 1,  // Not a secure connection
    WTP_TRANSACTION_SECURITY_LEVEL_SECURENOAUTH,   // Secure with no authentication
    WTP_TRANSACTION_SECURITY_LEVEL_GATEWAYAUTH,    // Secure with gateway authentication
    };

typedef LONG WTP_TRANSACTION_HANDLE;
#define INVALID_WTP_TRANSACTION_HANDLE (0)

//
// WAP primitives
//

// Base primitive type - all other primitive types derive from this one
typedef struct wap_primitive_base_tag
    {
    WAP_PRIMITIVE_ID wpiPrimitiveID;     // One of WAP_PRIMITIVE_ID_* - Always present and valid
    WAP_PRIMITIVE_TYPE wptPrimitiveType; // One of WAP_PRIMITIVE_TYPE_* -- always present and valid
    DWORD dwValidFields;                 // One of *_FIELD_*, depending on wpiPrimitiveID - Always present and valid
    } WAP_PRIMITIVE_BASE;

// T-DUnitdata primitive (WDP)
typedef struct wdp_unitdata_tag
    {
    WAP_PRIMITIVE_ID wpiPrimitiveID;     // One of WAP_PRIMITIVE_ID_* - Always present and valid
    WAP_PRIMITIVE_TYPE wptPrimitiveType; // One of WAP_PRIMITIVE_TYPE_* -- always present and valid
    DWORD dwValidFields;                 // One of *_FIELD_*, depending on wpiPrimitiveID - Always present and valid
    WAP_ADDRESS waSourceAddress;
    DWORD dwSourcePort;
    WAP_ADDRESS waDestinationAddress;
    DWORD dwDestinationPort;
    const BYTE* pbUserData;
    DWORD dwUserDataSize;
    } WDP_UNITDATA;

/*
// T-DError primitive (WDP)
typedef struct wap_primitive_t_derror_tag
    {
    WAP_PRIMITIVE_ID wpiPrimitiveID;     // One of WAP_PRIMITIVE_ID_* - Always present and valid
    WAP_PRIMITIVE_TYPE wptPrimitiveType; // One of WAP_PRIMITIVE_TYPE_* -- always present and valid
    DWORD dwValidFields;                 // One of *_FIELD_*, depending on wpiPrimitiveID - Always present and valid
    WAP_ADDRESS waSourceAddress;
    DWORD dwSourcePort;
    WAP_ADDRESS waDestinationAddress;
    DWORD dwDestinationPort;
    HRESULT hrErrorCode;
    } WAP_PRIMITIVE_T_DERROR;
*/

// TR-Invoke primitive (WTP)
typedef struct wtp_invoke_tag
    {
    WAP_PRIMITIVE_ID wpiPrimitiveID;      // One of WAP_PRIMITIVE_ID_* - Always present and valid
    WAP_PRIMITIVE_TYPE wptPrimitiveType;  // One of WAP_PRIMITIVE_TYPE_* -- always present and valid
    DWORD dwValidFields;                  // One of *_FIELD_*, depending on wpiPrimitiveID - Always present and valid
    WAP_ADDRESS waSourceAddress;
    DWORD dwSourcePort;
    WAP_ADDRESS waDestinationAddress;
    DWORD dwDestinationPort;
    BOOL bUserAcknowledgement;
    BOOL bWantSecureTransaction;
    const BYTE* pbUserData;
    DWORD dwUserDataSize;
    WTP_TRANSACTION_CLASS_TYPE wtctClassType;
    const BYTE* pbExitInfo;
    DWORD dwExitInfoSize;
    WTP_TRANSACTION_HANDLE wthTransactionHandle;
    } WTP_INVOKE;

// TR-Result primitive (WTP)
typedef struct wtp_result_tag
    {
    WAP_PRIMITIVE_ID wpiPrimitiveID;      // One of WAP_PRIMITIVE_ID_* - Always present and valid
    WAP_PRIMITIVE_TYPE wptPrimitiveType;  // One of WAP_PRIMITIVE_TYPE_* -- always present and valid
    DWORD dwValidFields;                  // One of *_FIELD_*, depending on wpiPrimitiveID - Always present and valid
    const BYTE* pbUserData;
    DWORD dwUserDataSize;
    const BYTE* pbExitInfo;
    DWORD dwExitInfoSize;
    WTP_TRANSACTION_HANDLE wthTransactionHandle;
    WTP_TRANSACTION_SECURITY_LEVEL wtslTransactionSecurityLevel;
    } WTP_RESULT;

// TR-Abort primitive (WTP)
typedef struct wtp_abort_tag
    {
    WAP_PRIMITIVE_ID wpiPrimitiveID;      // One of WAP_PRIMITIVE_ID_* - Always present and valid
    WAP_PRIMITIVE_TYPE wptPrimitiveType;  // One of WAP_PRIMITIVE_TYPE_* -- always present and valid
    DWORD dwValidFields;                  // One of *_FIELD_*, depending on wpiPrimitiveID - Always present and valid
    BYTE bAbortCode;
    WTP_TRANSACTION_HANDLE wthTransactionHandle;
    } WTP_ABORT;


// APIs

HRESULT WapOpen
    (
    const WAP_LAYER wlLayer,
    const DWORD dwLocalPort,
    WAP_HANDLE* const pwhHandle,
    HANDLE* const phMessageAvailableEvent
    );

HRESULT WapClose
    (
    const WAP_HANDLE whHandle
    );

HRESULT WapSend
    (
    const WAP_HANDLE whHandle,
    WAP_PRIMITIVE_BASE* const pwpbPrimitive
    );

HRESULT WapGetNextPrimitiveSize
    (
    const WAP_HANDLE whHandle,
    DWORD* const pdwNextPrimitiveSize
    );

HRESULT WapRead
    (
    const WAP_HANDLE whHandle,
    WAP_PRIMITIVE_BASE* const pwpbPrimitiveBuffer,
    const DWORD dwPrimitiveBufferSize
    );

HRESULT WapPing
    (
    const WAP_ADDRESS* const pwaAddress,
    const WORD wIdentifier,
    const DWORD dwSendDataSize,
    DWORD* const pdwReceiveDataSize,
    const DWORD dwTimeout
    );


#endif // _WAP_H_
