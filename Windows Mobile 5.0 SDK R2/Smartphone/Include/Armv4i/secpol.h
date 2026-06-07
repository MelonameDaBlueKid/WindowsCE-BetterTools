// Copyright (c) Microsoft Corporation. All rights reserved.
//
// System Security Policies
// Please keep them in numerical order.
//

// This policy setting determines whether applications stored on an MMC card are allowed to
// auto-run when inserted into the device.
//      0x00000000 - Applications ARE allowed to auto-run (default)
//      0x00000001 - Applications are NOT allowed to auto-run
#define SECPOLICY_CFAUTORUN                 0x00000002

#define POLICYVAL_CFAUTORUN_ALLOWED         0x00000000
#define POLICYVAL_CFAUTORUN_DISABLED        0x00000001


// This policy setting enforces whether RAPI calls can be used on the device
#define SECPOLICY_RAPI                      0x1001

#define SECPOLICY_RAPI_DISABLED             0
#define SECPOLICY_RAPI_ALLOWED              1
#define SECPOLICY_RAPI_RESTRICTED_MODE      2

// This policy setting determines the role mask for unsigned cabs
#define SECPOLICY_UNSIGNEDCABS             0x1005

// This policy setting enforces whether unsigned applications 
// are allowed to run on the device.
#define SECPOLICY_UNSIGNEDAPPS              0x1006

// This policy setting determines the role mask for processing .xml file for .hme and .tsk files
#define SECPOLICY_UNSIGNEDTHEMES            0x1007

// This policy setting determines whether carriers are allowed 
// to be assigned Trusted Provisioning Server (TPS) role.
#define SECPOLICY_TPSCARRIERROLE            0x1008

// This policy setting defines the maximum number allowed of retry 
// times for the user to authenticate a WAP pin-signed message.
#define SECPOLICY_MAXAUTHENTICATIONRETRY    0x1009

// This policy setting determines how messages should be processed.  All messages are  
// assigned role masks based on its security level and origin.  The message's role mask 
// is then AND-ed with the policy's role mask.  If the result is non-zero, the message is  
// accepted.
#define SECPOLICY_WAPSIGNEDMSG              0x100b

// This policy setting determines how SL signed messages 
// should be processed based on origin.
#define SECPOLICY_SL_MESSAGE                0x100c

// This policy setting determines how SI signed messages 
// should be processed based on origin.
#define SECPOLICY_SI_MESSAGE                0x100d

// This policy setting determines whether to accept non WAP-signed and 
// non ESP-encrypted messages, processed by the default security provider 
// in Security Module, based on their origin.
#define SECPOLICY_UNAUTHMESSAGES            0x100e

// This policy setting determines which provisioning messages are accepted 
// by cfghost based on the message's role(s).  This policy is used to limit 
// provisioning messages that come from Push Router.
#define SECPOLICY_OTAPROVISIONING           0x100f

// This policy setting determines whether routing of WSP notifications 
// from WAP stack is allowed.
#define SECPOLICY_WSPNOTIFICATIONS          0x1011

// This policy allows granting other roles administrative privileges to the system 
// without having to explicitly acquire the manager role.  
#define SECPOLICY_GRANTMANAGER              0x1017

// This policy allows other roles to impersonate the User Auth role.
#define SECPOLICY_GRANTUSERAUTH             0x1018

// This policy specifies the level of permissions required to create, modify, 
// and delete a trusted push proxy gateway (PPG).
#define SECPOLICY_TRUSTED_WAP_PROXY         0x1019

// This policy controls whether the user will be prompted with a Yes/No
// dialog before an unsigned application is allowed to install or execute.
// If the policy is equal to 1, then the user is never prompted.
#define SECPOLICY_UNSIGNEDPROMPT            0x101a

// This policy controls whether the 1- or 2-tier security model is in use.
// If 0, then 1-tier mode is disabled, apps run either privileged/unprivileged
// depending on how they're signed.
// If 1, then 1-tier mode is enabled and all apps run privileged, if they're
// allowed to run at all. 
#define SECPOLICY_PRIVILEGEDAPPS            0x101b

// SL security policy
// Operator can override https to use http or wsps to wsp.
// Value of 0 means we need to use https or wsps
// Value of 1 means we can use http or wsp
#define SECPOLICY_SLSECUREDOWNLOAD          0x101c

// This policy determines whether the Inbox app will send all messages signed.
// If sending signed, it signifies which algorithm to use.
#define SECPOLICY_USESIGN                   0x101d

#define POLICYVAL_USESIGN_DEFAULT           0x00000000
#define POLICYVAL_USESIGN_NONE              0x00000001
#define POLICYVAL_USESIGN_SHA_1             0x00000002
#define POLICYVAL_USESIGN_MD5               0x00000003

// This policy determines whether the Inbox app will send all messages encrypted.
// If sending encrypted, it signifies which algorithm to use.
#define SECPOLICY_USEENCRYPT                0x101e

#define POLICYVAL_USEENCRYPT_DEFAULT        0x00000000
#define POLICYVAL_USEENCRYPT_NONE           0x00000001
#define POLICYVAL_USEENCRYPT_3DES           0x00000002
#define POLICYVAL_USEENCRYPT_DES            0x00000003
#define POLICYVAL_USEENCRYPT_RC2_128        0x00000004
#define POLICYVAL_USEENCRYPT_RC2_64         0x00000005
#define POLICYVAL_USEENCRYPT_RC2_40         0x00000006

// This policy determines whether software certificates can be used to
// sign outgoing messages.  A value of 0 indicates that software certificates
// CANNOT be used to sign messages, and a value of 1 indicates that they CAN.
#define SECPOLICY_SOFTCERTS                 0x101f

// This policy determines which DRM rights messages are accepted by the DRM engine
// based on the message's role(s).
#define SECPOLICY_DRM_WAPRIGHTS             0x1021

// This policy determines whether the OMA device management transport client 
// will enforce SSL usage when connecting to a server, no matter what is bootstrapped.  
// By default, the client always uses SSL.
#define SECPOLICY_OMADMSSLCONN              0x1022

#define POLICYVAL_OMADMSSLCONN_NO_ENFORCE   0x1


