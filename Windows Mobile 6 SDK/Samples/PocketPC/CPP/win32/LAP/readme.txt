Copyright (c) Microsoft Corporation.  All rights reserved.

Use of this source code is subject to the terms of the Microsoft end-user
license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
If you did not accept the terms of the EULA, you are not authorized to use
this source code. For a copy of the EULA, please see the LICENSE.RTF on your
install media.


Code Sample Name: LAP

Feature Area: LASS/LAP

Description: Implements a LAP plug-in, including all optional LAP APIs. Supports English only.

Instructions:
    Open the file lap.vcproj in Visual Studio 2005. Select Debug or Release configuration,
    then build the project. This will generate lap.dll.

Deployment:
    LAP DLL module needs to be signed before deployment.  Unsigned DLL will fail to execute.
    Deploying a LAP requires copying the DLL to the Windows directory and setting several
    registry entries. lap.inf has been included to assist in generating a .CAB installation package.
    Edit the required entries in lap.inf and run "cabwiz.exe lap.inf" from the source directory.
    The .CAB file can be copied to the device and run directly on the device to install.
    A reboot may be required after installing.

Known Issues:
    Toolbar/Softkeys do not appear when a stronger security policy is set on the device and
    the LAP requires an updated password.

Relevant APIs/Associated Help Topics: 
    InitLAP
    DeinitLAP
    VerifyUser
    VerifyUserStart
    VerifyUserStop
    VerifyUserToTop
    LAPCreateEnrollmentConfigDialog
    LAPCancelVerifySequence
    LAPDisplayCodeword
    LAPDisplayPreWipe
    LAPLockoutUser
    LASSGetValue

High-level overview of the sample:
    There are several large features implemented in this sample.  This section briefly describes the 
    functionality of each feature and outlines the organization of the code that implements it.

    Passwords enrollment:
    Password enrollment provides the dialog that lets the user enter or change the password for the 
    device.  It verifies various password parameters such as complexity and length in order to ensure 
    that the password satisfies security policy requirements.
    Implementation files: enroll.h, enroll.cpp
    Customization: To replace the enrollment dialog with your own version modify the 
    DoEnrollment(HWND hwndParent, BOOL fSecure) function which is the entry point for the password 
    enrollment component.

    Password history:
    Password history allows keeping the history of previously used passwords.  It remembers several 
    passwords according to the policy setting.  With this policy in place users cannot use the same 
    password when their password expires.
    Password history component is independent of the UI and the rest of the LAP system.  Other LAP 
    implementations can use this component without modifications.
    Implementation files: password_history.h, password_history.cpp

    Password verification:
    Password verification provides the password verification and emergency call dialogs.  This is the
    dialog shown when the device is locked with a password.  It ensures that the correct password is
    entered and lets the user unlock the device.  Also it provides emergency call functionality.  If
    the user instead of the password enters a number that is considered an emergency number, the emergency
    call dialog is displayed allowing the user to call the number without unlocking the device.
    Failed password entry attempts are registered if required by a policy setting.  The system may 
    perform specific actions such as secure device wipe when the number of failed attempts exceed 
    the maximum allowed.
    Implementation files: verify.h, verify.cpp
    Customization: The DoVerify() function performs a single verification attempt for the user.  
    Modify this function to replace the verification dialog with a custom one.

    Codeword:
    The codeword dialog is displayed when a number of incorrect passwords are entered consecutively 
    in order to prevent accidental password entry (for example when the device is in your pocket).
    This is needed because the number of password entry attempts can be limited.  The codeword dialog
    requires the user to enter a predefined sequence of symbols (typically "a1b2c3") to ensure that the
    subsequent password entries are intentional.
    Implementation files: codeword.h, codeword.cpp
    Customization: The codeword dialog is shown by the DoCodeword() function.  Modify this function to 
    replace this dialog with a custom one.

    Authentication reset:
    Authentication reset is a feature that allows a user to reset the forgotten or lost password.  
    It is only enabled if an Authentication Reset Component is installed on the system.  The 
    authentication reset functionality consists of two steps: setup and request.
    The setup is invoked when the user enters a new password.  Then she is presented with a dialog 
    that informs the user of the possibility of the authentication reset setup.  On setup the user 
    password is protected and stored securely by the ARC component.
    The request is invoked from the password verification dialog if the user chooses to reset the 
    password.  The user is required to enter a new password before her old credentials can be requested 
    from the ARC.  Then the old password is reset for the new one.
    Implementation files: authreset.h, authreset.cpp, ar_support.h, ar_support.cpp

    Customize password security policy:
    The password related security policy is located in the registry.  The relevant registry keys 
    defining the individual settings are described in the following files: util.cpp, ar_support.h.  
    These registry keys can be used to modify policy settings.

Requirements: 
   Visual Studio 2005, 
   Windows Mobile 6 Professional SDK

** For more information about this code sample, please see the Windows Mobile SDK help system. 
 
