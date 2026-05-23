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
#pragma once

#include <windows.h>
#include <ceperf.h>

/* When adding new items to this enum list please use the following guide for 
   naming your entry:
   TOUCHPERFITEM_<MOD>_<DESCRIPTION>_<COUNT|DURATION>

   Where:
   <MOD>            is a 3 letter abbreviation for the module where the counter is used. 
   <DESCRIPTION>    is a short set of words to encapsulate the essence of this marker.
                    use _ characters to separate words
   <COUNT|DURATION|STATS> 
                    select the appropriate option to identify the type of information
                    captured behind this value. Over time the list of counter types
                    may increase so choose the appropriate value from the available list.

   Please group module counters together, and feel free to add a group comment to expand 
   abbreviations.
*/
enum TOUCHPERFITEM
{
    // Must be in same order as items in g_TouchPerfItems - see TouchPerf.cpp
    TOUCHPERFITEM_MDD_TRANSFER_TO_PROXY_DURATION = 0,
    TOUCHPERFITEM_MDD_TRANSFER_FROM_PDD_DURATION,

    // msgque.cpp
    TOUCHPERFITEM_MQ_UI_QLENGTH_STATS,
    TOUCHPERFITEM_MQ_PAN_COLLAPSE_COUNT,
    TOUCHPREFITEM_MQ_GESTURE_MESSAGE_COUNT,

    // Userin 
    TOUCHPERFITEM_SEND_TOUCH_INPUT_DURATION,

    // TouchGesture.cpp
    TOUCHPERFITEM_RECOGNIZE_DURATION,
    TOUCHPERFITEM_TAPSTYLUSDOWN_STATS,
    TOUCHPERFITEM_TCG_GESTUREBEGIN_DURATION,

    // FlickAnimator.cpp
    TOUCHPERFITEM_DGP_SCROLL_MESSAGES_COUNT,

    TOUCHPERFITEM_GE_PROCESSING_DURATION,
    TOUCHPERFITEM_VLV_SCROLL_END_STATS,

    // Do not add anything after this item
    TOUCHPERFITEM_LASTITEM
};

/// <summary>
/// Class with static functions to simplify client code when adding/using
/// perf markers with CePerf.
/// </summary>
class TouchPerf
{
    private:
        // The CePerf session
        static          HANDLE             s_hPerfSession;
        static volatile LONG               s_cSessionRefCnt;

    public:
        // Get/release CePerf session (should be called once each at init/deinit)
        static void AcquireSession();
        static void ReleaseSession();

        // Access to handles to the perf session and any items we are tracking.
        static HANDLE GetSession();
        static HANDLE GetItemHandle(TOUCHPERFITEM ItemID);

        static void AddStatistic(TOUCHPERFITEM eIndex, DWORD dwValue);
};

inline void TouchPerf::AddStatistic(TOUCHPERFITEM eIndex, DWORD dwValue)
{
    CePerfAddStatistic( TouchPerf::GetItemHandle(eIndex), dwValue, NULL );
}
