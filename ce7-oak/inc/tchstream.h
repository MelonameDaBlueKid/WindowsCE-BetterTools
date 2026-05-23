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
#ifndef __TCHSTREAM_H_
#define __TCHSTREAM_H_

#include <windev.h>

// including tchddi.h for TOUCH_PANEL_SAMPLE_FLAGS and enumTouchPanelSampleFlags
// Touch driver should include only tchstream.h. At some point in future
// tchddi.h will be deprecated
#include <tchddi.h>

// reg key for IST thread priority (HKLM\Drivers\BuiltIn\Touch\"Priority256"
#define TOUCH_IST_THREAD_PRIORITY_KEY_TEXT  TEXT("Priority256")
// default Touch IST priority (ideally should be specified in touch driver registry settings)
#define DEFAULT_TOUCH_IST_PRIORITY256       109

// default calibration mode constants for use by PDD
//
// minCalCount minimum number of valid samples before the last down sample is accepted
#define TCH_CALIBMODE_DEFAULT_MINCALCOUNT          20    
// calHoldSteadyTime minimum time in ms for user to hold the pen at calibration cross-hair
#define TCH_CALIBMODE_DEFAULT_CALHOLDSTEADYTIME    1500
// calDeltaReset     maximum delta x and delta y user's pen can move from the calibration cross-hair
#define TCH_CALIBMODE_DEFAULT_CALDELTARESET        20


// TCH DRIVER CLASS GUID
//
// {25121442-08CA-48dd-91CC-BFC9F790027C}
extern const __declspec(selectany)
    GUID TCH_DRIVER_CLASS_GUID = { 0x25121442, 0x8ca, 0x48dd, { 0x91, 0xcc, 0xbf, 0xc9, 0xf7, 0x90, 0x2, 0x7c } };
#define TCH_DRIVER_CLASS _T("{25121442-08CA-48dd-91CC-BFC9F790027C}")

// TCH IOCTLS
#define IOCTL_TOUCH_GET_TOUCH_PROPS             CTL_CODE(FILE_DEVICE_TOUCH, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_GET_SAMPLE_RATE             CTL_CODE(FILE_DEVICE_TOUCH, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_SET_SAMPLE_RATE             CTL_CODE(FILE_DEVICE_TOUCH, 3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_GET_CALIBRATION_POINTS      CTL_CODE(FILE_DEVICE_TOUCH, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_SET_SAMPLE_TIMEOUT          CTL_CODE(FILE_DEVICE_TOUCH, 5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_ENABLE_TOUCHPANEL           CTL_CODE(FILE_DEVICE_TOUCH, 6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_DISABLE_TOUCHPANEL          CTL_CODE(FILE_DEVICE_TOUCH, 7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TOUCH_GET_SAMPLES                 CTL_CODE(FILE_DEVICE_TOUCH, 8, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct {
    int width;
    int height;
    int subpixelAccuracy;
} TCH_DISPLAY_INFO;

// NOTE: This will be removed soon.
typedef struct {
    int sampleX;
    int sampleY;
    TOUCH_PANEL_SAMPLE_FLAGS sampleFlags;
} TCH_SAMPLE;

typedef struct {
    DWORD cInputs;          // Count of simultaneous touch points
    PCETOUCHINPUT pInputs;  // Set of simultaneous touch points
} TCH_INPUT_SAMPLE_SET;

/* platform specific touch driver properties - retrieved from touch driver PDD */
typedef struct
{
    /* minimum sampling rate supported by the touch driver */
    DWORD minSampleRate;  
    /* maximum sampling rate supported by the touch driver */
    DWORD maxSampleRate;
    
    /* the touch driver consumer (tchproxy) uses these constants in calibration mode
       to evaluate the user input as a calibration sample*/

    /* minimum number of valid samples before the last down sample is accepted */
    DWORD minCalCount;
    /* minimum time in ms for user to hold the pen at calibration cross-hair */
    DWORD calHoldSteadyTime;
    /* maximum delta x and delta y user's pen can move from the calibration cross-hair */
    DWORD calDeltaReset;

    /* Range of X,Y values for touch sample returned by the driver */    
    /* minimum x */
    int xRangeMin;
    /* maximum x */
    int xRangeMax;
    /* minimum y */
    int yRangeMin;
    /* maximum y */
    int yRangeMax;

    /* Type of touch controller */
    TouchType touchType;
    /* Touch controller capabilities mask */
    DWORD     dwTouchInputMask;

    /* Maximum number of simultaneous multitouch samples that the hardware supports 
       ie. Maximum cInputs value passed to the MDD. */
    DWORD maxSimultaneousSamples;
    
    /* Maximum size in bytes of a property associated with a sample. 
       ie. CETOUCHINPUT::cbProperty
       Set to 0 if no extra property data will every be sent with a sample. */
    DWORD cbPropertyMax;
    
} TCH_PROPS;

// Functions implemented by touch calibration DLL
//
typedef BOOL (*PFN_TCHCAL_SETDISPLAYINFO) (TCH_DISPLAY_INFO displayInfo);
typedef BOOL (*PFN_TCHCAL_CALIBRATESAMPLE) (IN int UncalX, IN int UncalY, OUT int* pCalX, OUT int* pCalY);
typedef BOOL (*PFN_TCHCAL_SETCALIBRATIONDATA) (int cCalibrationPoints, int   *pScreenXBuffer, int   *pScreenYBuffer,
        int   *pUncalXBuffer, int   *pUncalYBuffer);


//
//    Converts touch panel sample flags and X,Y to a primary CETOUCHINPUT sample.
//
//    Returns FALSE if there is no conversion.
//
__inline BOOL ConvertTouchPanelToTouchInput(
    TOUCH_PANEL_SAMPLE_FLAGS    Flags,
    INT                         X,
    INT                         Y,
    PCETOUCHINPUT               pInput
    )
{    
    static BOOL s_fPreviousSampleDown = FALSE;
    static INT  s_xPrevious;
    static INT  s_yPrevious;
    
    BOOL fRet = FALSE;

    if ( (Flags & (TouchSampleIgnore | TouchSampleValidFlag)) == TouchSampleValidFlag )
    {
        DWORD TouchInputFlags = 0;
        
        if (Flags & TouchSampleDownFlag)
        {
            TouchInputFlags |= TOUCHEVENTF_INRANGE;
            
            if (s_fPreviousSampleDown)
            {
                TouchInputFlags |= TOUCHEVENTF_MOVE;
            }
            else
            {
                TouchInputFlags |= TOUCHEVENTF_DOWN;
                s_fPreviousSampleDown = TRUE;
            }

            s_xPrevious = X;
            s_yPrevious = Y;
        }
        else
        {
            TouchInputFlags |= TOUCHEVENTF_UP;
            s_fPreviousSampleDown = FALSE;

            // X and Y coordinates on up were allowed to invalid.
            // Replace with the previous X,Y
            X = s_xPrevious;
            Y = s_yPrevious;
        }

        if (Flags & TouchSampleIsCalibratedFlag)
        {
            TouchInputFlags |= TOUCHEVENTF_CALIBRATED;
        }

        memset(pInput, 0, sizeof(*pInput));
        pInput->x = X;
        pInput->y = Y;
        pInput->dwFlags = TouchInputFlags;

        fRet = TRUE;
    }

    return fRet;
}

#endif

