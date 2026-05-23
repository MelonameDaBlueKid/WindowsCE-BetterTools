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
//------------------------------------------------------------------------------
//
//  File:  i2c.h
//
//  Header file for I2C functions.
//
//------------------------------------------------------------------------------
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

    //------------------------------------------------------------------------------
    // Defines
    //------------------------------------------------------------------------------
#define I2C_MAX_NUM_BUSES                 10
#define I2C_MAX_LENGTH                    2048
#define I2C_MDD_BUFFER_LENGTH             I2C_MAX_LENGTH + 4
#define I2C_DEFAULT_TIMEOUT               10                    // Default time out in miliseconds
#define I2C_MAX_TIMEOUT                   2000                  // Maximum time out in milisecond
#define I2C_STANDARD_SPEED                100000                // Standard mode.
#define I2C_FAST_SPEED                    400000                // Fast mode.
#define I2C_HIGH_SPEED                    3400000               // High speed mode.

    //=============================================================================
    // String Definations
    //=============================================================================
#define REG_DXSUPPORT_VALUE TEXT("SupportedDx")
#define REG_DEVINDEX_VALUE TEXT("Index")

    //=============================================================================
    // structs
    //=============================================================================
    typedef struct {
        DWORD dwBusIndex;
        CRITICAL_SECTION csI2cBus;
        DWORD dwPddContext;
        DWORD speed;
        DWORD maxSpeed;
    } I2C_BUS_CONTEXT;

    typedef struct
    {
        BOOL bI2cRead;
        DWORD slaveAddr;
        DWORD regAddr;
        DWORD count;
        LPBYTE pBuf;
        DWORD speed;
        DWORD slaveAddrSize;
        DWORD regAddrSize;
        DWORD timeOut;
        DWORD dwBusContext;
    } I2C_DEVICE_CONTEXT;

    // IO Control Codes
    //
#define IOCTL_I2C_SET_SLAVE_ADDRESS             CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3000, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Transfer Data
#define IOCTL_I2C_SET_SLAVE_ADDR_SIZE           CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3001, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Transfer Data
#define IOCTL_I2C_SET_REG_ADDR_SIZE             CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3002, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Transfer Data
#define IOCTL_I2C_SET_SPEED                     CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3003, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Transfer Data
#define IOCTL_I2C_SET_TIMEOUT                   CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3004, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Transfer Data

    //=============================================================================
    // Debug zones (for both DEBUG and RETAIL builds)
    //=============================================================================
#ifndef SHIP_BUILD
#ifndef ZONE_ERROR
#define ZONE_ERROR        DEBUGZONE(0)
#endif // ZONE_ERROR
#ifndef ZONE_WARNING
#define ZONE_WARNING      DEBUGZONE(1)
#endif // ZONE_WARNING
#ifndef ZONE_FUNCTION
#define ZONE_FUNCTION     DEBUGZONE(2)
#endif // ZONE_FUNCTION
#ifndef ZONE_INIT
#define ZONE_INIT         DEBUGZONE(3)
#endif // ZONE_INIT
#ifndef ZONE_PDD
#define ZONE_PDD          DEBUGZONE(4)
#endif // ZONE_PDD
#endif // SHIP_BUILD

    //------------------------------------------------------------------------------
    // Description: I2cOpen - Open the i2c driver and creat an I2C_DEVICE_IFC
    //                        context for later i2c functions access.
    //
    // Arguments:  [IN] devicename - The device name of the i2c driver. 
    //                               Example devicename L"I2C1:".
    //
    // Ret Value:  The I2C_DEVICE_IFC context.
    //------------------------------------------------------------------------------
    __inline HANDLE I2cOpen(LPCWSTR devicename)
    {
        return CreateFile(devicename,
            GENERIC_WRITE | GENERIC_READ,  // desired access
            0,                             // sharing mode
            NULL,                          // security attributes (=NULL)
            CREATE_ALWAYS,                 // creation disposition
            FILE_ATTRIBUTE_NORMAL,         // flags and attributes
            NULL);                         // template file (ignored)
    }

    //------------------------------------------------------------------------------
    // Description: I2cClose - Close the i2c driver handle and free I2C_DEVICE_IFC
    //                         context.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //
    //------------------------------------------------------------------------------
    __inline VOID I2cClose(HANDLE hI2C)
    {
        CloseHandle(hI2C);
    }

    //------------------------------------------------------------------------------
    // Description: I2cSetSlaveAddress - Set the slave address of the i2c device.
    //                  The slave address must be set before the any i2c read/write.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] address - The dword value of the i2c address for both 7
    //                            and 10 bits i2c address.
    //
    // Ret Value:  True if success.
    //------------------------------------------------------------------------------
    __inline BOOL I2cSetSlaveAddress(HANDLE hI2C, DWORD address)
    {
        return DeviceIoControl(hI2C, 
            IOCTL_I2C_SET_SLAVE_ADDRESS, 
            (LPBYTE)&address, 
            sizeof(DWORD), 
            NULL, 
            0, 
            NULL, 
            NULL);
    }

    //------------------------------------------------------------------------------
    // Description: I2cWrite - I2c write transaction.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] regAddr - register offset of the write transaction.
    //             [IN] pBuf - The pointer to the write buffer.
    //             [IN] length - The length of the write transaction.
    //
    // Ret Value:  TRUE if success.
    //------------------------------------------------------------------------------
    __inline BOOL I2cWrite(HANDLE hI2C, DWORD regAddr, LPBYTE pBuf, DWORD length)
    {
        DWORD dwByteWritten;
        SetFilePointer(hI2C, regAddr, NULL, FILE_BEGIN);
        return WriteFile(hI2C, (LPVOID) pBuf, length, (LPDWORD) &dwByteWritten, NULL);
    }

    //------------------------------------------------------------------------------
    // Description: I2cRead - I2c read transaction.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] regAddr - register offset of the write transaction.
    //             [OUT] pBuf - The pointer to the read buffer. The read result
    //                          will be saved in the buffer.
    //             [IN] length - The length of the read transaction.
    //
    // Ret Value:  TRUE if success.
    //------------------------------------------------------------------------------
    __inline BOOL I2cRead(HANDLE hI2C, DWORD regAddr, LPBYTE pBuf, DWORD length)
    {
        DWORD dwByteRead;
        SetFilePointer(hI2C, regAddr, NULL, FILE_BEGIN);
        return ReadFile(hI2C, (LPVOID) pBuf, length, (LPDWORD) &dwByteRead, NULL);
    }

    //------------------------------------------------------------------------------
    // Description: I2cSetSlaveAddrSize - Set the size of the i2c slave address.
    //                  The function is optional. If not called, the default slave 
    //                  address size is 7 bits.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] size - Size of the slave address. Should be either 7 or 10.
    //
    // Ret Value:  True if success.
    //------------------------------------------------------------------------------
    __inline BOOL I2cSetSlaveAddrSize(HANDLE hI2C, DWORD size)
    {
        return DeviceIoControl(hI2C, 
            IOCTL_I2C_SET_SLAVE_ADDR_SIZE, 
            (LPBYTE)&size, 
            sizeof(DWORD), 
            NULL, 
            0, 
            NULL, 
            NULL);
    }

    //------------------------------------------------------------------------------
    // Description: I2cSetRegAddrSize - Set the size of the i2c register address.
    //                  The function is optional. If not called, the default 
    //                  register address size is 1 byte.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] size - Size of the slave address. Should be either 7 or 10.
    //
    // Ret Value:  True if success.
    //------------------------------------------------------------------------------
    __inline BOOL I2cSetRegAddrSize(HANDLE hI2C, DWORD size)
    {
        return DeviceIoControl(hI2C, 
            IOCTL_I2C_SET_REG_ADDR_SIZE, 
            (LPBYTE)&size, 
            sizeof(DWORD), 
            NULL, 
            0, 
            NULL, 
            NULL);
    }

    //------------------------------------------------------------------------------
    // Description: I2cSetSpeed - Set target transaction speed for the i2c device.
    //                  The function is optional. If not called, the default speed
    //                  is 100kbps.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] frequency - The dword value of the target i2c bus speed.
    //
    // Ret Value:  The actual speed that been set for this device. A zero return
    //             means the speed setting is wrong.
    //------------------------------------------------------------------------------
    __inline DWORD I2cSetSpeed(HANDLE hI2C, DWORD dwTargetSpeed)
    {
        DWORD dwActualSpeed;

        DeviceIoControl(hI2C, 
            IOCTL_I2C_SET_SPEED, 
            (LPBYTE)&dwTargetSpeed, 
            sizeof(DWORD), 
            (LPBYTE)&dwActualSpeed, 
            sizeof(DWORD), 
            NULL, 
            NULL);

        return dwActualSpeed;
    }

    //------------------------------------------------------------------------------
    // Description: I2cSetTimeOut - Set the timeout value for the i2c device.
    //                  The function is optional. If not called, it will use the 
    //                  default pdd timeout value.
    //
    // Arguments:  [IN] hI2C - The i2c file handle. 
    //             [IN] timeout - The timeout value in milisecond.
    //
    // Ret Value:  True if successful.
    //------------------------------------------------------------------------------
    __inline BOOL I2cSetTimeOut(HANDLE hI2C, DWORD dwTimeOut)
    {
        return DeviceIoControl(hI2C, 
            IOCTL_I2C_SET_TIMEOUT,
            (LPBYTE)&dwTimeOut, 
            sizeof(DWORD), 
            NULL, 
            0, 
            NULL, 
            NULL);
    }

    ///------------------------------------------------------------------------------
    /// I2C functions used in OAL
    ///------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // Description: Init - initializes the i2c driver
    //
    // Arguments:  [IN] pddContext - registry key text from device manager
    //             [IN] lpvBusContext - ignored
    //
    // Ret Value:  The i2c bus context
    //------------------------------------------------------------------------------
    DWORD OalI2cInit(DWORD dwBusIndex);

    //------------------------------------------------------------------------------
    // Deinit - deinitializes the i2c driver
    //------------------------------------------------------------------------------
    BOOL OalI2cDeinit(DWORD dwContext);

    //------------------------------------------------------------------------------
    // Description: Open - Open the i2c device
    //
    // Arguments:  [IN] dwBusIndex - the bus index
    //
    // Ret Value:  The i2c device context
    //------------------------------------------------------------------------------
    I2C_DEVICE_CONTEXT* OalI2cOpen(DWORD dwBusIndex);

    //------------------------------------------------------------------------------
    // Close
    //------------------------------------------------------------------------------
    BOOL OalI2cClose(I2C_DEVICE_CONTEXT *pI2cDeviceContext);
    //------------------------------------------------------------------------------
    // Description: OalI2cSetSlaveAddress - Set the slave address of the i2c device.
    //                  The slave address must be set before the any i2c read/write.
    //
    // Arguments:  [IN] pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer. 
    //             [IN] address - The dword value of the i2c address for both 7
    //                            and 10 bits i2c address.
    //
    // Ret Value:  True if success.
    //------------------------------------------------------------------------------
    BOOL OalI2cSetSlaveAddress(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD address);

    //------------------------------------------------------------------------------
    // Description: OalI2cWrite - I2c write transaction.
    //
    // Arguments:  [IN] pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer. 
    //             [IN] regAddr - register offset of the write transaction.
    //             [IN] pBuf - The pointer to the write buffer.
    //             [IN] length - The length of the write transaction.
    //
    // Ret Value:  TRUE if success.
    //------------------------------------------------------------------------------
    BOOL OalI2cWrite(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD regAddr, LPBYTE pBuf, DWORD length);

    //------------------------------------------------------------------------------
    // Description: OalI2cRead - I2c read transaction.
    //
    // Arguments:  [IN] pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer. 
    //             [IN] regAddr - register offset of the write transaction.
    //             [OUT] pBuf - The pointer to the read buffer. The read result
    //                          will be saved in the buffer.
    //             [IN] length - The length of the read transaction.
    //
    // Ret Value:  TRUE if success.
    //------------------------------------------------------------------------------
    BOOL OalI2cRead(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD regAddr, LPBYTE pBuf, DWORD length);

    //------------------------------------------------------------------------------
    // Description: OalI2cSetSlaveAddrSize - Set the size of the i2c slave address.
    //                  The function is optional. If not called, the default slave 
    //                  address size is 7 bits.
    //
    // Arguments:  pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer.
    //             [IN] size - Size of the slave address. Should be either 7 or 10.
    //
    // Ret Value:  True if success.
    //------------------------------------------------------------------------------
    BOOL OalI2cSetSlaveAddrSize(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD size);

    //------------------------------------------------------------------------------
    // Description: OalI2cSetRegAddrSize - Set the size of the i2c register address.
    //                  The function is optional. If not called, the default 
    //                  register address size is 1 byte.
    //
    // Arguments:  [IN] pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer. 
    //             [IN] size - Size of the slave address. Should be either 7 or 10.
    //
    // Ret Value:  True if success.
    //------------------------------------------------------------------------------
    BOOL OalI2cSetRegAddrSize(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD size);

    //------------------------------------------------------------------------------
    // Description: OalI2cSetSpeed - Set target transaction speed for the i2c device.
    //                  The function is optional. If not called, the default speed
    //                  is 100kbps.
    //
    // Arguments:  [IN] pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer.
    //             [IN] frequency - The dword value of the target i2c bus speed.
    //
    // Ret Value:  The actual speed that been set for this device. A zero return
    //             means the speed setting is wrong.
    //------------------------------------------------------------------------------
    DWORD OalI2cSetSpeed(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD dwTargetSpeed);

    //------------------------------------------------------------------------------
    // Description: OalI2cSetTimeOut - Set the timeout value for the i2c device.
    //                  The function is optional. If not called, it will use the 
    //                  default pdd timeout value.
    //
    // Arguments:  [IN] pI2cDeviceContext - The I2C_DEVICE_CONTEXT pointer.
    //             [IN] timeout - The timeout value in milisecond.
    //
    // Ret Value:  True if successful.
    //------------------------------------------------------------------------------
    BOOL OalI2cSetTimeOut(I2C_DEVICE_CONTEXT *pI2cDeviceContext, DWORD dwTimeOut);

#ifdef __cplusplus
}
#endif

#endif  // __I2C_H__

