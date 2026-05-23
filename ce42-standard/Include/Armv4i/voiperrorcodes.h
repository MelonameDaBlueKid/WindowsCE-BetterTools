//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of your Microsoft Windows CE
// Source Alliance Program license form.  If you did not accept the terms of
// such a license, you are not authorized to use this source code.
//
#ifndef _VOIP_ERROR_CODES_
#define _VOIP_ERROR_CODES_
// VoIP interface error codes
enum
{
//API validation failures:

    // The IVoIPCallLogDBEnum or IVoIPCallerInfoDBEnum pointer
    // that was used to make this call is out of date.  Before
    // further calls will succeed, the enumerator must be reset.
    VOIP_E_ENUMOUTOFDATE        = 0x80cc0000,

    // The interface was not initialized (usually though a call
    // to Init()) before being used.
    VOIP_E_NOTINITIALIZED       = 0x80cc0001,

    // The IVoIPCallRecord or IVoIPCallerInfoRecord pointer is
    // not in any database and therefore is not removable.
    VOIP_E_RECORDNOTINDB        = 0x80cc0002,

    // The interface was already initialized and cannot be initialized
    // again until it has been uninitialized.
    VOIP_E_ALREADYINITIALIZED   = 0x80cc0003,

    //There is no caller info DB or no call log DB. The manager will still
    //work, but the DB funtionality is lost.
    VOIP_E_NODB                 = 0x80cc0004,

    //The IVoIPCurrentCallProperties interface pointer is not a current call - 
    //The pointer is probably stale
    VOIP_E_NOTCURRENTCALL       = 0x80cc0005,

    //The VoIPMgr is waiting to initialize or waiting to complete shutdown - 
    //which occurs asynchronously with respect to RTC. Therefore the Mgr is currently
    //Unusable
    VOIP_E_BUSY                 = 0x80cc0006,

    //There is no active call right now
    VOIP_E_NOACTIVECALL          = 0x80cc0007,

    //The time has not been set
    VOIP_E_TIMENOTSET            = 0x80cc0008,

    //The current call does not have the appropriate status for this operation
    VOIP_E_INVALIDCALLSTATUS     = 0x80cc0009,

    //The VoIPManager was unable to get a URI and Server so initialization fails
    VOIP_E_PROVISIONING_FAILED   = 0x80cc000b,

    //There was no media manager installed on the device and the voip manager
    //cannot be used without one
    VOIP_E_NOMEDIAMGR            = 0x80cc000c,
    
//Codes that specify action
    
    //The UI does not want the manager to terminate missed calls
    VOIP_S_DONT_TERMINATE        = 0x00cc0000,

};

#endif
