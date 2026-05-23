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
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  
    usb200.h

Abstract:  
    Constant definitions from Universal Serial Bus specification version 2.0.

Notes: 

--*/
#ifndef   __USB200_H__
#define   __USB200_H__
#include <usb100.h>

#include <PSHPACK1.H>
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE                    0x06
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE           0x07

typedef struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    USHORT bcdUSB;
    UCHAR bDeviceClass;
    UCHAR bDeviceSubClass;
    UCHAR bDeviceProtocol;
    UCHAR bMaxPacketSize0;

    UCHAR bNumConfigurations;
    UCHAR bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR, *PUSB_DEVICE_QUALIFIER_DESCRIPTOR;

typedef USB_CONFIGURATION_DESCRIPTOR USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR, *PUSB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR;

#define USB_ENDPOINT_MAX_PACKET_SIZE_MASK                       0x07FF

#define USB_OTG_CONFIGURATION_DESCRIPTOR_TYPE                   0x09
typedef struct _USB_OTG_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    UCHAR bmAttributes;
} USB_OTG_DESCRIPTOR, *PUSB_OTG_DESCRIPTOR ;
// For OTG Feature
#define USB_FEATURE_B_HNP_ENABLE            0x0003
#define USB_FEATURE_A_HNP_SUPPORT           0x0004
#define USB_FEATURE_A_ALT_HNP_SUPPORT       0x0005

#ifdef USB_IF_ELECTRICAL_TEST_MODE

#define USB_EHCI_TEST_MODE_DISABLED      0x00
#define USB_EHCI_TEST_MODE_J_STATE       0x01
#define USB_EHCI_TEST_MODE_K_STATE       0x02
#define USB_EHCI_TEST_MODE_SE0_NAK       0x03
#define USB_EHCI_TEST_MODE_TEST_PACKET   0x04
#define USB_EHCI_TEST_MODE_FORCE_ENABLE 0x05

#define BUS_USBD_EXTENTION_FUNCTIONCODE 0x180
#define BUS_USBD_EXTENTION_FUNCTIONCODE_SIZE 0x40
#define IOCTL_BUS_USBD_BEGIN _BUSACCESS_CTL_CODE(BUS_USBD_EXTENTION_FUNCTIONCODE)
#define IOCTL_BUS_USBD_END   _BUSACCESS_CTL_CODE(BUS_USBD_EXTENTION_FUNCTIONCODE+BUS_USBD_EXTENTION_FUNCTIONCODE_SIZE-1)


#define BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE 0x200
#define BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE_SIZE 0x10
#define IOCTL_USB_TEST_MODE_BEGIN _BUSACCESS_CTL_CODE(BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE )
#define IOCTL_USB_TEST_MODE_END \
    _BUSACCESS_CTL_CODE(BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE+BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE_SIZE-1)

#define IOCTL_USB_EHCI_GET_NUM_PORTS _BUSACCESS_CTL_CODE(BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE+0x02)
#define IOCTL_USB_EHCI_SET_TEST_MODE _BUSACCESS_CTL_CODE(BUS_USB_TEST_MODE_EXTENTION_FUNCTIONCODE+0x03)

typedef struct _IO_USB_EHCI_SET_TEST_MODE
{
    DWORD dwPortNum;
    DWORD dwTestMode;
} IO_USB_EHCI_SET_TEST_MODE, *PIO_USB_EHCI_SET_TEST_MODE;

#endif //#ifdef USB_IF_ELECTRICAL_TEST_MODE

#include <POPPACK.H>

#endif   /* __USB200_H__ */

