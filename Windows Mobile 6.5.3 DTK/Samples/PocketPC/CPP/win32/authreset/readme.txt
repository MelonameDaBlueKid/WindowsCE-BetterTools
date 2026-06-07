//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

Code Sample Name:
    AuthReset

Feature Area:
    LAP, Authentication Reset

Description:
    This sample demonstrates how to create a custom Authentication Reset Component (ARC).
    The purpose of the ARC is to restore the authentication information in case of loss.
    Sample shows the appropriate workflow for the ARC.  There are two steps in the Authentication
    Reset process: setup and request.  On setup, the LAP passes data to the ARC that needs
    to be protected.  ARC takes care about the data protection (by encrypting the data)
    and returnes the encrypted data to the LAP.  The key used for encryption is stored in
    a secure place.  The idea is that the protected data and the protection key are stored in
    two different places.  The protected data is meaningless without the key and the key
    (which is cryptographically strong) is securely stored on the key management server
    (the sample uses a secure portion of the registry for the sake of clarity).
    On reset, the LAP passes a encrypted data to the ARC.  The ARC retrieves the key
    unprotects the data and returns back to the LAP.
    
Usage:
    1. Use Visual Studio 2005 to build the sample.
    2. Sign the sample authreset.dll with a sign utility.
       (the sample is executed in as trusted code and so it needs to be signed)
    2. Load the sample on the device in <sample_dir> directory.
       (you are free to choose <sample_dir>)
    3. Enable Authentication Reset functionality on the device by setting the following
       registry keys:
            [HKEY_LOCAL_MACHINE\Comm\Security\Policy\LASSD\AuthReset]
            "AuthenticationReset"=dword:1
            "Dll"="<sample_dir>\\authreset.dll"
       "Dll" needs to be a full path to the sample (note that LAP won't give any error message
       if it can't find ARC).
       Also note that all dialogs displayed by ARC need to have EXSTYLE WS_EX_ABOVESTARTUP
       attribute to be shown when the device is locked (see authresetppc.rc file).
    4. Go to Start menu, Settings, and choose Lock.
    5. Set the password for the device.
    6. LAP will notice that Authentication Reset is enabled, load authreset.dll and give you
       the option to setup the Authentication Reset.

Relevant API:
    ARCSetup
    ARCRequest
    ARCGetValue

Requirements:
    Visual Studio 2005 Standard
    Windows Mobile 6 Professional SDK
    ActiveSync 4.1

** For more information about this code sample, please see the Windows Mobile SDK help system. **
