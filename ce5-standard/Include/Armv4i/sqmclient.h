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

#ifndef SQMCLIENT_H__
#define SQMCLIENT_H__

#include <basetsd.h> // DWORD64

typedef DWORD HSQMSESSION;
typedef HSQMSESSION *LPHSQMSESSION;

/*++

  SqmGetSession
    The SqmGetSession function initiates a SQM session or joins an existing
    session named by the given session identifier.

  Parameters
    pszSessionIdentifier
        [in] Unicode string giving the globally unique session identifier
        string.
        If this parameter is NULL, an unnamed SQM session is created. This
        unnamed session can only be accessed from within the creating process.
        To allow an external process to access the session, it must be created
        with an identifier.
    cbMaxSessionSize
        [in] Maximum size of session data in bytes.
        When creating a new session, this parameter places a maximum on the
        allowed size of the SQM session data. This parameter is required if
        creating a new session. If connecting to an existing session, this
        parameter is ignored.
    dwFlags
        [in] Specifies creation semantics.
        The following flags are allowed:
            SQM_SESSION_CREATE_NEW
                Create a new session if it doesn't already exist.

  Return Values
    If the function succeeds, the return value is an open handle to the SQM
    session.
    If the function fails, the return result is NULL. To get extended error
    information, call GetLastError.

  Remarks
    Only one unnamed session may exist in any process. If more than one
    concurrent session is needed in a particular process, unique session
    identifiers must be used for all but one session (which may be unnamed).
    Unless cross-process SQM sessions are needed, it is recommended that
    unnamed sessions be used. There are fewer security concerns with unnamed
    sessions.
    The first SQM session created in a process (whether named or unnamed),
    is the default SQM session for that process. Passing NULL for the
    HSQMSESSION parameter of other SQM API calls will use this default session.
    In this way, components which want to record SQM data but don't want to
    manage their own sessions can use the default session of the host
    application. Calling a SQM API call with a NULL HSQMSESSION parameter is
    harmless if no default session exists.

--*/
EXTERN_C
HSQMSESSION
SqmGetSession(
    LPWSTR pszSessionIdentifier,
    DWORD  cbMaxSessionSize,
    DWORD  dwFlags
    );

#define SQM_SESSION_CREATE_NEW 0x00000001

/*++

  SqmEndSession
    The SqmEndSession function ends a SQM session and writes its data to a
    file.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    pszPattern
        [in] A pattern indicating the name of the SQM session file to save and
        where to save it.
        This parameter indicates where to save the data in the current session.
        If an absolute path to a file is provided, the data will be written to
        that file. Alternatively, a printf-style format string can be provided
        with a single format specifier (%d).
            Example: To save SQM files as c:\tmp\sqmdata00.sqm,
            c:\tmp\sqmdata01.sqm, etc., pass in the pattern
            "c:\\tmp\\sqmdata%02d.sqm"
    dwMaxFilesToQueue
        [in] If a pattern with a %d specified is passed for the pszPattern
        parameter, this parameter determines the maximum number of files to
        queue before overwriting old sessions.
    dwFlags
        [in] File save semantics.
        The following flags are allowed:
            SQM_OVERWRITE_OLDEST_FILE
                Overwrite the oldest file with the given pattern (only if max
                files are exceeeded).
            SQM_OVERWRITE_ANY_FILE
                Overwrite any file with the given pattern (only if max files
                are exceeeded).

  Remarks
    SQM uses a "rolling session model." Calling SqmEndSession does not
    invalidate the HSQMSESSION handle. It just clears out all data in the
    current session, saves it, and immediately begins a new empty session.
    All subsequent calls which modify datapoints will affect this new
    session.
    It is recommended to use a small number, such as 10 to 20, for the
    dwMaxFilesToQueue parameter, though a larger queue might be appropriate
    depending on the circumstances. SQM files should be uploaded regularly.
    Typically if large numbers of files are accumulating on the local
    machine, it is an indication that something is wrong.

--*/
EXTERN_C
VOID
SqmEndSession(
    HSQMSESSION hSession,
    LPCWSTR     pszPattern,
    DWORD       dwMaxFilesToQueue,
    DWORD       dwFlags
    );

#define SQM_OVERWRITE_ANY_FILE    0x00000001
#define SQM_OVERWRITE_OLDEST_FILE 0x00000002

/*++

  SqmStartSession
    The SqmStartSession function sets the start time for the current SQM
    session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.

  Remarks
    SQM uses a "rolling session model." Just as calling SqmEndSession does not
    invalidate the HSQMSESSION handle, calling SqmStartSession does nothing
    other than reset the timer which records the length of the session.

--*/
EXTERN_C
VOID
SqmStartSession(
    HSQMSESSION hSession
    );

/*++

  SqmGetSessionStartTime
    The SqmGetSessionStartTime function returns the start time of the current
    session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.

  Return Values
    If the function succeeds, the return value is a FILETIME with the UTC time
    at which the SQM session started.
    If the function fails, the return result is a zeroed FILETIME structure.

--*/
EXTERN_C
FILETIME
SqmGetSessionStartTime(
    HSQMSESSION hSession
    );

/*++

  SqmGetEnabled
    The SqmGetEnabled function returns a flag indicating whether SQM is
    currently enabled.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.

  Remarks
    SQM is an opt-in technology. We cannot collect data from our customers
    without their permission. Therefore, there has to be some way to disable
    SQM in an application. This is done using the SqmSetEnabled API. The
    SqmGetEnabled API retrieves whether the current session is enabled or
    disabled.
    When SQM is disabled, all instrumentation calls are NO-OPs, and when
    ending a session, no file will be written to disk.

  Return Values
    TRUE or FALSE, depending on whether SQM is currently enabled.

--*/
EXTERN_C
BOOL
SqmGetEnabled(
    HSQMSESSION hSession
    );

/*++

  SqmSetEnabled
    The SqmSetEnabled function either enables or disables the operation of SQM
    for a session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    fEnabled
        [in] Should SQM be enabled in this session?

  Remarks
    SQM is an opt-in technology. We cannot collect data from our customers
    without their permission. Therefore, there has to be some way to disable
    SQM in an application. This is done using the SqmSetEnabled API. The
    SqmGetEnabled API retrieves whether the current session is enabled or
    disabled.
    When SQM is disabled, all instrumentation calls are NO-OPs, and when
    ending a session, no file will be written to disk.

--*/
EXTERN_C
VOID
SqmSetEnabled(
    HSQMSESSION hSession,
    BOOL        fEnabled
    );

/*++

  SqmGetFlags
    The SqmGetFlags function gets the current flags for a SQM session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwFlags
        [out] Returns currently set flags for the session. See SqmSetFlags for
        set of supported flags.

--*/
EXTERN_C
VOID
SqmGetFlags(
    HSQMSESSION hSession,
    LPDWORD     pdwFlags
    );

/*++

  SqmSetFlags
    The SqmSetFlags function sets flags for a SQM session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwFlags
        [in] Specifies session semantics. The below flags are supported:
            SQM_FLAG_DEBUG
                Mark this session as a DEBUG session
            SQM_FLAG_NEVER_THROTTLE
                Make this session as immune to sampling on the server
            SQM_SECURE_UPLOAD
                Mark this session as requiring secure (HTTPS) upload
            SQM_DO_NOT_UPLOAD
                Don't upload this session - just delete it.

  Remarks
    This function overwrites all existing flags. If this behavior is not
    desired, use SqmGetFlags to get current flag settings.
    Any flags which are set are persistent throughout the length of the
    process. Calling SqmEndSession does not reset any flags. To explicitly
    clear existing flags, use SqmClearFlags.

--*/
EXTERN_C
VOID
SqmSetFlags(
    HSQMSESSION hSession,
    DWORD       dwFlags
    );

enum
{
    SQM_FLAG_DEBUG          = (1 << 0),
    SQM_FLAG_NEVER_THROTTLE = (1 << 1),
    SQM_SECURE_UPLOAD       = (1 << 2),
    SQM_DO_NOT_UPLOAD       = (1 << 3)
};

/*++

  SqmClearFlags
    The SqmClearFlags function clears all flags for the current SQM session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.

--*/
EXTERN_C
VOID
SqmClearFlags(
    HSQMSESSION hSession,
    DWORD       dwFlags
    );

/*++

  SqmGetMachineId
    The SqmGetMachineId function retrieves the machine ID set for the current
    session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    pGuid
        [out] Machine ID (GUID) associated with this session.

  Remarks
    If no user ID has been set for the session, a zeroed-out GUID will be
    returned.

--*/
EXTERN_C
VOID
SqmGetMachineId(
    HSQMSESSION hSession,
    LPGUID      pguid
    );

/*++

  SqmGetUserId
    The SqmGetUserId function retrieves the user ID set for the current
    session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    pGuid
        [out] User ID (GUID) associated with this session.

  Remarks
    If no user ID has been set for the session, a zeroed-out GUID will be
    returned.

--*/
EXTERN_C
VOID
SqmGetUserId(
    HSQMSESSION hSession,
    LPGUID      pguid
    );

/*++

  SqmSetMachineId
    The SqmSetMachineId function associates a machine ID with the current
    session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
  pGuid
        [in] Machine ID (GUID) to set for the session.

  Remarks
    This function associates with the SQM session a GUID which is unique to the
    user's machine. This identifier is required, whether or not it is desired
    to correlate SQM data by machines. The machine ID is the basis for
    sampling -- the pattern of bits in the ID determines whether or not we
    collect data from that machine on the server.
    Setting the machine ID only needs to be done once, usually soon after
    calling SqmGetSession to create a new session. The ID is retained as long
    as that session handle is valid (i.e. it is not reset by calling
    SqmEndSession).

--*/
EXTERN_C
VOID
SqmSetMachineId(
    HSQMSESSION hSession,
    LPGUID      pguid
    );

/*++

  SqmSetUserId
    The SqmSetUserId function associates a user ID with the current session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    pGuid
        [in] User ID (GUID) to set for the session.

  Remarks
    This function associates with the SQM session a GUID which is unique to the
    user. The definition of what a user is may differ depending on the
    application. Typically, a user represents a single login profile on a
    machine. However, an application might also have its own notion of users,
    and decide to use that concept of a user instead.
    Setting the user ID only needs to be done once, usually soon after calling
    SqmGetSession to create a new session. The ID is retained as long as that
    session handle is valid (i.e. it is not reset by calling SqmEndSession).
    If the user changes during the course of the process, it would be necessary
    to call SqmSetUserId again with the new user ID.

--*/
EXTERN_C
VOID
SqmSetUserId(
    HSQMSESSION hSession,
    LPGUID      pguid
    );

/*++

  SqmCreateNewId
    The SqmCreateNewId function creates a new anonymous GUID suitable for use
    as a SQM machine ID or user ID.

  Parameters
    pGuid
        [in] Pointer to GUID struct which upon success contains the newly
        created GUID.

  Remarks
    This function should be used when generating a new GUID for use as a SQM
    machine/user ID. Use of this function assures that the GUID is anonymous
    and not linkable to the machine on which it was generated. Versions of
    CoCreateGUID on older platforms include the machine's network card MAC
    address in the GUID. Using SqmCreateNewId will ensure that this doesn't
    happen, even on these older platforms.

  Return Values
    This function returns TRUE on success, and FALSE on failure.

--*/
EXTERN_C
BOOL
SqmCreateNewId(
    LPGUID pguid
    );

/*++

  SqmReadSharedMachineId
    The SqmReadSharedMachineId function reads the shared SQM machine ID from
    the registry.

  Parameters
    pGuid
        [out] Pointer to GUID structure in which to return the shared machine
        ID.

  Remarks
    The shared machine ID is a GUID which is stored in the registry key
    HKLM\Software\Microsoft\SQMClient\MachineId Any application which uses SQM
    may use this ID as the Machine ID for its sessions. If this registry key
    does not exist, then any application is free to create it using
    SqmWriteSharedMachineId.
    Creating a new GUID should be done by using SqmCreateNewId, not
    CoCreateGUID or some other Win32 API which generates GUIDs. Using
    SqmCreateNewId will ensure that a machine/user ID cannot be traced back to
    any particular machine.

  Return Values
    If the shared Machine Id exists and is retrieved successfully, the function
    returns TRUE.
    If the Machine Id does not exist or cannot be retrieved, the function
    returns FALSE.

--*/
EXTERN_C
BOOL
SqmReadSharedMachineId(
    LPGUID pguid
    );

/*++

  SqmReadSharedUserId
    The SqmReadSharedUserId function reads the shared SQM machine ID from the
    registry.

  Parameters
    pGuid
        [out] Pointer to GUID structure in which to return the shared user ID.

  Remarks
    The shared user ID is a GUID which is stored in the registry key
    HKCU\Software\Microsoft\SQMClient\UserId Any application which uses SQM may
    use this ID as the User ID for its sessions. If this registry key does not
    exist, then any application is free to create it using
    SqmWriteSharedUserId.
    Creating a new GUID should be done by using SqmCreateNewId, not
    CoCreateGUID or some other Win32 API which generates GUIDs. Using
    SqmCreateNewId will ensure that a machine/user ID cannot be traced back to
    any particular machine.

  Return Values
    If the shared User Id exists and is retrieved successfully, the function
    returns TRUE.
    If the User Id does not exist or cannot be retrieved, the function returns
    FALSE.

--*/
EXTERN_C
BOOL
SqmReadSharedUserId(
    LPGUID pguid
    );

/*++

  SqmWriteSharedMachineId
    The SqmWriteSharedMachineId function writes the shared SQM machine ID to
    the registry.

  Parameters
    pGuid
        [in] Pointer to machine ID.

  Remarks
    The shared machine ID is a GUID which is stored in the registry key
    HKLM\Software\Microsoft\SQMClient\MachineId Any application which uses SQM
    may use this ID as the Machine ID for its sessions (but it is not
    required). If this registry key does not exist, then any application is
    free to create it using SqmWriteSharedMachineId.
    Creating a new GUID should be done by using SqmCreateNewId, not
    CoCreateGUID or some other Win32 API which generates GUIDs. Using
    SqmCreateNewId will ensure that a machine/user ID cannot be traced back to
    any particular machine.
    Because the shared machine ID is located in HKEY_LOCAL_MACHINE, only an
    administrator can write the registry value. For this reason, if an
    application intends to set this registry key, it should preferably be done
    during the application's setup process.

--*/
EXTERN_C
BOOL
SqmWriteSharedMachineId(
    LPGUID pguid
    );

/*++

  SqmWriteSharedUserId
    The SqmWriteSharedUserId function writes the shared SQM user ID to the
    registry.

  Parameters
    pGuid
        [in] Pointer to user ID.

  Remarks
    The shared user ID is a GUID which is stored in the registry key
    HKLM\Software\Microsoft\SQMClient\UserId Any application which uses SQM may
    use this ID as the user ID for its sessions (but it is not required). If
    this registry key does not exist, then any application is free to create it
    using SqmWriteSharedUserId.
    Creating a new GUID should be done by using SqmCreateNewId, not
    CoCreateGUID or some other Win32 API which generates GUIDs. Using
    SqmCreateNewId will ensure that a machine/user ID cannot be traced back to
    any particular machine.
    Because the shared user ID is located in HKEY_CURRENT_USER, using it as the
    user ID for a SQM session implies that there is a one-to-one correspondence
    between the application's notion of a user and a Windows login profile.

--*/
EXTERN_C
BOOL
SqmWriteSharedUserId(
    LPGUID pguid
    );

/*++

  SqmSet
    The SqmSet function sets a single datapoint to the given value.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    dwVal
        [in] Value to assign to the specified datapoint.

  Remarks
    If no value already exists for the given datapoint, the datapoint is added
    to the session. If the datapoint already exists, then its current value is
    overwritten.

--*/
EXTERN_C
VOID
SqmSet(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwVal
    );

/*++

  SqmIncrement
    The SqmIncrement increments a single datapoint by the given amount.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    dwVal
        [in] Amount by which to increment the given datapoint. If the datapoint
        has not been previously set to any value, its value is considered to be
        0.

  Remarks
    The typical use for this function is to maintain a running count of some
    event.

--*/
EXTERN_C
VOID
SqmIncrement(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwInc
    );

/*++

  SqmSetBits
    The SqmSetBits function sets individual bits of a datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint in which to set bits.
    dwVal
        [in] A DWORD which is bitwise-ORed with the existing datapoint value.
        If the datapoint has not been previously set, then its value is
        considered to be 0.

--*/
EXTERN_C
VOID
SqmSetBits(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwOrBits
    );

/*++

  SqmSetIfMax
    The SqmSetIfMax function sets a single datapoint to the given value if it
    is larger than the current value of the datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    dwVal
        [in] Value to assign to the specified datapoint.

  Remarks
    If no value already exists for the given datapoint, it is set to the value
    of the passed parameter. If the datapoint already has a value, then its
    value is changed only if the new value is greater than the existing value.

--*/
EXTERN_C
VOID
SqmSetIfMax(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwVal
    );

/*++

  SqmSetIfMin
    The SqmSetIfMin function sets a single datapoint to the given value if it
    is smaller than the current value of the datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    dwVal
        [in] Value to assign to the specified datapoint.

  Remarks
    If no value already exists for the given datapoint, it is set to the value
    of the passed parameter. If the datapoint already has a value, then its
    value is changed only if the new value is less than the existing value.

--*/
EXTERN_C
VOID
SqmSetIfMin(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwVal
    );

/*++

  SqmAddToAverage
    The SqmAddToAverage function adds a value to a running average datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    dwVal
        [in] Value to add to the running average.

  Remarks
    Using this function with a datapoint causes the datapoint to be marked as
    a running average. If a datapoint is being used as a running-average
    datapoint, no other functions other than SqmAddToAverage should be called
    on it. Setting the value of the datapoint with a function such as SqmSet
    would eliminate all record of the running average.
    A typical use of this datapoint would be to average a set of performance
    measurements of a particular event.

--*/
EXTERN_C
VOID
SqmAddToAverage(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwVal
    );

/*++

  SqmAddToStream
    The SqmAddToStream function adds an entry to a stream datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the stream.
    nArgs
        [in] This function is a C-style varargs function. This parameter
        indicates the number of args which follow.
    ...
        [in] A variable-length list of DWORD arguments which correspond to the
        positions in the stream entry.

  Remarks
    A stream datapoint consists of an ordered list of n-tuples of DWORD values.
    A stream has a fixed width but length limited only by the memory limit of
    the session. On the client, the width is set by the first call to
    SqmAddToStream on that datapont. The variable-length list of arguments to
    SqmAddToStream represent the individual elements of a single entry
    (n-tuple) in the stream. SqmAddToStream can only be used to add a single
    entry at a time.

--*/
EXTERN_C
VOID
SqmAddToStream(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD nArgs,
    ...
    );

/*++

  SqmGet
    The SqmGet function retrieves the current value of a datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to get.
    pdwVal
        [out] Pointer to DWORD to receive return value.

  Remarks
    If no value already exists for the given datapoint, the datapoint is added
    to the session. If the datapoint already exists, then its current value is
    overwritten.

  Return Values
    If the datapoint has been set (and therefore has a value), the function
    returns TRUE.
    If the datapoint has not been set, the function returns FALSE.

--*/
EXTERN_C
BOOL
SqmGet(
    HSQMSESSION hSession,
    DWORD       dwId,
    LPDWORD     pdwVal
    );

/*++

  SqmSetAppVersion
    The SqmSetAppVersion function records the application's version number in
    a SQM session.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwVersionHigh
        [in] High DWORD in 64-bit application version.
    dwVersionLow
        [in] Low DWORD in 64-bit application version.

  Remarks
    This function should be called after creating a new SQM session with
    SqmGetSession.

--*/
EXTERN_C
VOID
SqmSetAppVersion(
    HSQMSESSION hSession,
    DWORD       dwVersionHigh,
    DWORD       dwVersionLow
    );

/*++

  SqmTimerStart
    The SqmTimerStart function starts a timer associated with a datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint associated with the timer.

  Remarks
    Only one timer may be actively running for any given datapoint
    (per session). After calling this function, eventually either
    SqmTimerRecord, SqmTimerAccumulate or SqmTimerAddToAverage should be
    called to stop the timer and record the duration. Calling this function
    again for the same datapoint just resets the associated timer.

--*/
EXTERN_C
VOID
SqmTimerStart(
    HSQMSESSION hSession,
    DWORD       dwId
    );

/*++

  SqmTimerRecord
    The SqmTimerRecord function ends a timer and records its value into the
    datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint associated with the timer.

  Remarks
    This function ends the timer for a datapoint and records its value into
    the datapoint using SqmSet. All timer values are recorded in milliseconds.

--*/
EXTERN_C
VOID
SqmTimerRecord(
    HSQMSESSION hSession,
    DWORD       dwId
    );

/*++

  SqmTimerAccumulate
    The SqmTimerAccumulate function ends a timer and adds its value to a
    datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint associated with the timer.

  Remarks
    This function ends the timer for a datapoint and adds its value to the
    existing value of the datapoint. All timer values are recorded in
    milliseconds.

--*/
EXTERN_C
VOID
SqmTimerAccumulate(
    HSQMSESSION hSession,
    DWORD       dwId
    );

/*++

  SqmTimerAddToAverage
    The SqmTimerAddToAverage function ends a timer and adds its value to a
    running-average datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used. 
    dwId
        [in] ID of the datapoint associated with the timer.

  Remarks
    This function ends the timer for a datapoint and adds its value to a
    running-average datapoint. All timer values are recorded in milliseconds.
    This function is useful for recording the average duration of some event
    that happens multiple times.

--*/
EXTERN_C
VOID
SqmTimerAddToAverage(
    HSQMSESSION hSession,
    DWORD       dwId
    );

/*++

  SqmSet64
    The SqmSet64 function sets a single 64-bit datapoint to the given value.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    qwVal
        [in] 64-bit value to assign to the specified datapoint.

  Remarks
    If no value already exists for the given datapoint, the datapoint is added
    to the session. If the datapoint already exists, then its current value is
    overwritten.

--*/
EXTERN_C
VOID
SqmSet64(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD64     qwVal
    );

/*++

  SqmSetBool
    The SqmSet function sets a single datapoint to the given boolean value.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to set.
    dwVal
        [in] Value to assign to the specified datapoint.

  Remarks
    If no value already exists for the given datapoint, the datapoint is added
    to the session. If the datapoint already exists, then its current value is
    overwritten.

--*/
EXTERN_C
VOID
SqmSetBool(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       dwVal
    );

/*++

  SqmAddToStreamV
    The SqmAddToStreamV function adds an entry to a stream datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the stream.
    nArgs
        [in] This function is a C-style varargs function. This parameter
        indicates the number of args which follow.
    argList
        [in] A variable-length list of DWORD arguments which correspond to the
        positions in the stream entry.

  Remarks
    A stream datapoint consists of an ordered list of n-tuples of DWORD values.
    A stream has a fixed width but length limited only by the memory limit of
    the session. On the client, the width is set by the first call to
    SqmAddToStream on that datapont. The variable-length list of arguments to
    SqmAddToStream represent the individual elements of a single entry
    (n-tuple) in the stream. SqmAddToStream can only be used to add a single
    entry at a time.

--*/
EXTERN_C
VOID
SqmAddToStreamV(
    HSQMSESSION hSession,
    DWORD       dwId,
    DWORD       nArgs,
    va_list     argList
    );

/*++

  SqmGet64
    The SqmGet64 function retrieves the current value of a 64-bit datapoint.

  Parameters
    hSession
        [in] Handle of the SQM session. If this parameter is NULL, the
        process's default SQM session is used.
    dwId
        [in] ID of the datapoint to get.
    pqwVal
        [out] Pointer to DWORD to receive 64-bit return value.

  Remarks
    If no value already exists for the given datapoint, the datapoint is added
    to the session. If the datapoint already exists, then its current value is
    overwritten.

  Return Values
    If the datapoint has been set (and therefore has a value), the function
    returns TRUE.
    If the datapoint has not been set, the function returns FALSE.

--*/
EXTERN_C
BOOL
SqmGet64(
    HSQMSESSION hSession,
    DWORD       dwId,
    PDWORD64    pqwVal
    );

/*++

  SqmUploadCallback
    The SqmUploadCallback function is an application-defined function which is
    called by the SQM API on the completion of each SQM upload. The
    SQMUPLOADCALLBACK type defines a pointer to this callback function.
    SqmUploadCallback is a placeholder for the application-defined function
    name.

  Parameters
    hr
        [in] This HRESULT indicates success or failure of the SQM upload.
    szFilePath
        [in] The path of the file for which upload was attempted.
    dwHttpResponse
        [in] The HTTP response code, as returned by UrlMon.

  Return Values
    If this callback function returns FALSE, any other uploads in the queue
    will be cancelled. If the callback returns TRUE, then uploads will
    continue (if there are any more uploads in the queue).

  Remarks
    If the HTTP response code returned is 403.6, this indicates that the
    client machine has been sampled out. In this case, the application should
    cease sending any further SQM data in future sessions, since it will
    simply be a waste of bandwidth.

--*/
typedef
BOOL
(WINAPI * SQMUPLOADCALLBACK)(
    HRESULT hr,
    LPCWSTR szFilePath,
    DWORD   dwHttpResponse
    );

/*++

  SqmStartUpload
    The SqmStartUpload function starts the upload process for a file or set of
    files in a queue directory.

  Parameters
    szPattern
        [in] File path or pattern to upload. If a standard file path is given,
        SqmStartUpload queues the upload for that single file. If a pattern is
        given, it must follow the pattern specification used in SqmEndSession.
    szUrl
        [in] The URL to use for uploading of normal (non-sensitive) SQM
        sessions. This URL will be used unless the session has the
        SQM_SECURE_UPLOAD flag set.
    szSecureUrl
        [in] The HTTPS URL to use for uploading of sensitive SQM sessions with
        the SQM_SECURE_UPLOAD flag set.
    dwFlags
        [in] Upload semantics. The following set of flags are supported:
            SQM_UPLOAD_SINGLE_FILE
                Upload only the first SQM file matching the given pattern.
            SQM_UPLOAD_ALL_FILES
                Upload all files matching the given pattern.
    pfnCallback
        [in] Function pointer of type SQMUPLOADCALLBACK which will be called
        after each download completes, either successfully or unsuccessfully.

  Return Values
    The return result is the number of files which were queued.

  Remarks
    This function should be called from a thread which is pumping messages.
    Uploads in progress can be cancelled by returning FALSE from the callback
    function or by using SqmAbortUpload.

--*/
EXTERN_C
DWORD
SqmStartUpload(
    LPCWSTR           szPattern,
    LPCWSTR           szUrl,
    LPCWSTR           szSecureUrl,
    DWORD             dwFlags,
    SQMUPLOADCALLBACK pfnCallback
    );

#define SQM_UPLOAD_SINGLE_FILE 0x00000001
#define SQM_UPLOAD_ALL_FILES   0x00000002

/*++

  SqmAbortUpload
    The SqmAbortUpload function waits a specified timeout period for any
    current upload to complete and cancels any further uploads. If the upload
    does not complete within the timeout, it is forcibly aborted.

  Parameters
    dwTimeoutMilliseconds
        [in] The amount of time, in milliseconds, to wait for the current
        upload to complete before forcibly aborting.

  Remarks
    This is a useful function to call in the application's shutdown path, to
    ensure that SQM uploads get shutdown cleanly.

--*/
EXTERN_C
VOID
SqmAbortUpload(
    DWORD dwTimeoutMilliseconds
    );

#endif // SQMCLIENT_H__
