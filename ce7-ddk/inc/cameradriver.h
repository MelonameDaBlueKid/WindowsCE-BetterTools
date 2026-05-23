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

#ifndef __NULL_DD
#define __NULL_DD

#ifdef __cplusplus
extern "C" {
#endif

#define CAM_MSGQ_IMEOUT 250

// CAPTURE and STILL are required pin types. PREVIEW is optional, so list it last.
enum
{
    ADAPTER = -1,
    CAPTURE = 0,
    STILL   = 1,
    PREVIEW = 2
};

// DEFINES for PROPSETID_VIDCAP_VIDEOPROCAMP
typedef enum {
    // VideoProcAmp
    ENUM_BRIGHTNESS = 0,
    ENUM_CONTRAST,
    ENUM_HUE,
    ENUM_SATURATION,
    ENUM_SHARPNESS,
    ENUM_GAMMA,
    ENUM_COLORENABLE,
    ENUM_WHITEBALANCE,
    ENUM_BACKLIGHT_COMPENSATION,
    ENUM_GAIN,

    ENUM_VIDPROCAMP_MAX = ENUM_GAIN,
    
    // CameraControl
    ENUM_PAN,
    ENUM_TILT,
    ENUM_ROLL,
    ENUM_ZOOM,
    ENUM_EXPOSURE,
    ENUM_IRIS,
    ENUM_FOCUS,
    ENUM_FLASH,

    ENUM_CAMCONTROL_MAX = ENUM_FLASH,

    ENUM_DEV_PROP_MAX = ENUM_CAMCONTROL_MAX
} ENUM_DEV_PROP;


const size_t StandardSizeOfBasicValues   = sizeof(CSPROPERTY_DESCRIPTION) + sizeof(CSPROPERTY_MEMBERSHEADER) + sizeof(CSPROPERTY_STEPPING_LONG) ;
const size_t StandardSizeOfDefaultValues = sizeof(CSPROPERTY_DESCRIPTION) + sizeof(CSPROPERTY_MEMBERSHEADER) + sizeof(ULONG) ;


DWORD MDD_HandleIO( LPVOID ModeContext, ULONG ulModeType );
DWORD MDD_HandleNotification( LPVOID MDDContext, LONG lModeType, ULONG NotificationId, LPVOID Context );

class CPinDevice;

typedef class CCameraDevice 
{
public:
    CCameraDevice( );

    ~CCameraDevice( );
    
    bool
    Initialize(
        PVOID context
        );

    bool
    BindApplicationProc(
        HANDLE
        );

    bool
    UnBindApplicationProc( );
    
    DWORD
    AdapterHandlePinRequests(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD
    AdapterHandleVersion(
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );        

    DWORD
    AdapterHandlePropSetAdapter(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD
    AdapterHandleVidProcAmpRequests(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred 
        );

    DWORD
    AdapterHandleCamControlRequests(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD
    AdapterHandleVideoControlRequests(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );
    
    DWORD
    AdapterHandleDroppedFramesRequests(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD
    CCameraDevice::AdapterHandleMetadataRequests(
        PUCHAR pInBuf,
        DWORD  InBufLen,
        PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD
    AdapterHandlePowerRequests(
        DWORD  dwCode,
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD
    AdapterHandleCustomRequests(
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

    DWORD HandleNotification( 
        LONG lModeType, 
        ULONG NotificationId, 
        LPVOID Context
        );

  
    LPVOID
    ValidateBuffer(
        __in_bcount(ulActualBufLen) LPVOID  lpBuff,
        ULONG   ulActualBufLen,
        ULONG   ulExpectedBuffLen,
        DWORD * dwError
        );
    
    bool
    AdapterCompareFormat(
        const ULONG                 ulPinId,
        const PCS_DATARANGE_VIDEO   pCsDataRangeVideoToCompare,
        PCS_DATARANGE_VIDEO       * ppCsDataRangeVideoMatched,
        bool                        fDetailedComparison
        );

    bool
    AdapterCompareFormat(
        const ULONG                            ulPinId,
        const PCS_DATAFORMAT_VIDEOINFOHEADER   pCsDataRangeVideoToCompare,
        PCS_DATARANGE_VIDEO                  * ppCsDataRangeVideoMatched,
        bool                                   fDetailedComparison
        );

    bool
    IsValidPin(
        ULONG ulPinId
        );

    bool
    GetPinFormat(
        ULONG                 ulPinId,
        ULONG                 ulIndex,
        PCS_DATARANGE_VIDEO * ppCsDataRangeVid
        );

    bool
    IncrCInstances(
        ULONG        ulPinId,
        CPinDevice * pPinDev
        );

    bool
    DecrCInstances(
        ULONG ulPinId
        );

    bool
    PauseCaptureAndPreview( );

    bool
    RevertCaptureAndPreviewState( );

    DWORD
    PDDClosePin( 
        ULONG ulPinId 
        );

    DWORD 
    PDDGetPinInfo( 
        ULONG ulPinId, 
        PSENSORMODEINFO pSensorModeInfo 
        );

    DWORD PDDSetPinState( 
        ULONG ulPinId, 
        CSSTATE State 
        );

    DWORD PDDFillPinBuffer( 
        ULONG ulPinId, 
        PUCHAR pImage 
        );

    DWORD PDDInitPin( 
        ULONG ulPinId, 
        CPinDevice *pPin 
        );

    DWORD PDDSetPinFormat(
        ULONG ulPinId,
        PCS_DATARANGE_VIDEO pCsDataRangeVideo
        );

    PVOID PDDAllocatePinBuffer( 
        ULONG ulPinId 
        );

    DWORD PDDDeAllocatePinBuffer( 
        ULONG ulPinId, 
        PVOID pBuffer
        );

    DWORD PDDRegisterClientBuffer(
        ULONG ulPinId,
        PVOID pBuffer 
        );

    DWORD PDDUnRegisterClientBuffer(
        ULONG ulPinId,
        PVOID pBuffer 
        );

    DWORD PDDHandlePinCustomProperties(
        ULONG ulPinId,
        __in_bcount(InBufLen) PUCHAR pInBuf,
        DWORD  InBufLen,
        __out_bcount(OutBufLen) PUCHAR pOutBuf,
        DWORD  OutBufLen,
        PDWORD pdwBytesTransferred
        );

private:

    bool
    GetPDDPinInfo();

    void
    GetBasicSupportInfo(
        __out_bcount(OutBufLen) PUCHAR        pOutBuf,
        DWORD         OutBufLen,
        PDWORD        pdwBytesTransferred,
        PSENSOR_PROPERTY pSensorProp,
        PDWORD        pdwError
        );

    void
    GetDefaultValues(
        __out_bcount(OutBufLen) PUCHAR        pOutBuf,
        DWORD         OutBufLen,
        PDWORD        pdwBytesTransferred,
        PSENSOR_PROPERTY pDevProp,
        PDWORD        pdwError
        );

    bool
    AdapterCompareGUIDsAndFormatSize(
        const PCSDATARANGE DataRange1,
        const PCSDATARANGE DataRange2
        );

    DWORD 
    WriteMessage( 
        ULONG flag, 
        LPVOID Context 
        );

    DWORD 
    PowerDown();

    DWORD
    PowerUp();

private:

    CRITICAL_SECTION m_csDevice;        

    HANDLE          m_hStream;                         // Handle to the corresponding stream sub-device
    HANDLE          m_hCallerProcess;                  // Handle of the process this driver is currently bound to.
    HANDLE          m_hAdapterMessageQueue;
    DWORD           m_dwVersion;
    CEDEVICE_POWER_STATE m_PowerState;
    STREAM_INSTANCES *m_pStrmInstances;
    ADAPTERINFO     m_AdapterInfo;
    PVOID           m_PDDContext;
    PPDDFUNCTBL     m_pPDDFuncTbl;
    PDDFUNCTBL2     m_PDDFuncTbl2;
    DWORD           m_dwRefCount;

} CAMERADEVICE, * PCAMERADEVICE;

typedef struct CCameraOpenHandle
{
    PCAMERADEVICE pCamDevice;
} CAMERAOPENHANDLE, * PCAMERAOPENHANDLE;

#ifdef __cplusplus
}
#endif


#endif // __NULL_DD
