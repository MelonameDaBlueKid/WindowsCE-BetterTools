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
////////////////////////////////////////////////////////////
// This is "Sample Code" and is distributable subject to the
// terms of the end user license agreement.
////////////////////////////////////////////////////////////

#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

// Window class name and window name used by the hidden communication
// window (which is created by the Media Player plugin).

#define SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_CLASSNAME   _T("MPPlugin_CW_ClassName")
#define SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_WINDOWNAME  _T("MPPlugin_CW_WindowName")

// Name of the message queue used for notifications from the Windows
// Media Player plugin to the home screen plugin.

#define SZ_MSGQUEUE_NAME        _T("WMPSample_MsgQueue")

// Enum with values indicating the status of Windows Media Player.
enum WMP_STATUS
{
    WMP_STATUS_UNKNOWN,         // Status of Windows Media Player is unknown
    WMP_STATUS_STOPPED,         // WMP is stopped
    WMP_STATUS_PAUSED,          // WMP is paused
    WMP_STATUS_PLAYING,         // WMP is playing
    WMP_STATUS_OTHER            // WMP is in some other state
};

// Maximum length of a media title (e.g., song name). We limit this
// because message queues require a maximum message size, and besides,
// really really long titles aren't very useful anyway.
#define CCH_MEDIA_TITLE_MAX     256

// Struct used in message queue. The WMP plugin initializes one of these
// and writes it to the message queue; the homescreen plugin reads it
// from the message queue.
struct MQMESSAGE
{
    WMP_STATUS      status;                             // Status of Windows Media Player
    TCHAR           szMediaTitle[CCH_MEDIA_TITLE_MAX];  // Title of media
};

// Parameters to use when creating the message queue. These are
// specified here because both plugins call CreateMsgQueue (the
// homescreen plugin calls it to actually CREATE the message queue,
// while the WMP plugin calls it to FIND the existing message queue
// instance) and we need to ensure consistency between them.
#define DW_MSGQUEUE_FLAGS       (MSGQUEUE_ALLOW_BROKEN)
#define DW_MSGQUEUE_MAXMSGS     1

// Window messages. These are sent FROM the homescreen plugin TO the
// Windows Media Player plugin.
#define WM_MPHPSAMPLE_REPORT     (WM_APP + 0)    // Please send me a status message now
#define WM_MPHPSAMPLE_PLAY       (WM_APP + 1)    // Play current media
#define WM_MPHPSAMPLE_PAUSE      (WM_APP + 2)    // Pause current media
#define WM_MPHPSAMPLE_PREV       (WM_APP + 3)    // Move to previous media item
#define WM_MPHPSAMPLE_NEXT       (WM_APP + 4)    // Move to next media item

#endif // _WMPPLUGINCOMM_H_
