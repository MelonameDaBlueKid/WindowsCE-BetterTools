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

    // FlickAnimator.cpp
    TOUCHPERFITEM_DGP_SCROLL_MESSAGES_COUNT,

    TOUCHPERFITEM_GE_PROCESSING_DURATION,
    TOUCHPERFITEM_VLV_SCROLL_END_STATS,

    TOUCHPERFITEM_LB_TOUCH_FRAME_DELAY_DURATION,
    // Latency of gesture to first paint 
    TOUCHPERFITEM_LB_TOUCH_FRAME_LATENCY_DURATION,
    // time spent in paint message
    TOUCHPERFITEM_LB_TOUCH_FRAME_PAINT_DURATION,

    // time spent in paint message
    TOUCHPERFITEM_WEBVIEW_TOUCH_FRAME_PAINT_DURATION,
    // time between paint messages
    TOUCHPERFITEM_WEBVIEW_TOUCH_FRAME_DELAY_DURATION,
    // latency of first gesture processing
    TOUCHPERFITEM_WEBVIEW_TOUCH_FRAME_LATENCY_DURATION,

    // time spent in paint message
    TOUCHPERFITEM_LISTVIEW_TOUCH_FRAME_PAINT_DURATION,
    // time between paint messages
    TOUCHPERFITEM_LISTVIEW_TOUCH_FRAME_DELAY_DURATION,
    // List view touch scroll duration
    TOUCHPERFITEM_LISTVIEW_TOUCH_LVSCROLL_DURATION,
    // List view touch erase bkground duration
    TOUCHPERFITEM_LISTVIEW_ERASE_BKGND_DURATION,
    // List view touch item redraw duration
    TOUCHPERFITEM_LISTVIEW_TOUCH_ITEM_REDRAW_DURATION,
    // List view touch drawitem duration
    TOUCHPERFITEM_LISTVIEW_TOUCH_DRAWITEM_DURATION,
    // Latency of gesture to first paint 
    TOUCHPERFITEM_LISTVIEW_TOUCH_FRAME_LATENCY_DURATION,
    // owner draw time 
    TOUCHPERFITEM_LISTVIEW_TOUCH_OWNER_DRAWITEM_DURATION,
    // How long to update the scroll bars
    TOUCHPERFITEM_LISTVIEW_TOUCH_UPDATEBARS_DURATION,
    // Item cache hit metrics
    TOUCHPERFITEM_LISTVIEW_TOUCH_DRAWCACHE_STATS,
    TOUCHPERFITEM_LISTVIEW_TOUCH_CACHEHIT_STATS,

    // time spent in paint message
    TOUCHPERFITEM_TREEVIEW_TOUCH_FRAME_PAINT_DURATION,
    // time between paint messages
    TOUCHPERFITEM_TREEVIEW_TOUCH_FRAME_DELAY_DURATION,
    // latency of first gesture processing
    TOUCHPERFITEM_TREEVIEW_TOUCH_FRAME_LATENCY_DURATION,

    // TIME SPENT IN PAINT MESSAGE
    TOUCHPERFITEM_MENU_TOUCH_FRAME_PAINT_DURATION,
    // latency of first gesture processing
    TOUCHPERFITEM_MENU_TOUCH_FRAME_LATENCY_DURATION,

    // time spent in paint message : Calendar
    TOUCHPERFITEM_CALENDAR_FRAME_PAINT_DURATION,
    // time between paint messages : Calendar
    TOUCHPERFITEM_CALENDAR_FRAME_DELAY_DURATION,
    // latency from gesture message to the first paint
    TOUCHPERFITEM_CALENDAR_LATENCY_DURATION,

    // IE 6
    // TODO: remove TOUCHPERFITEM_IE6_FRAME_DURATION after
    //       the dependency on the Product side is removed
    TOUCHPERFITEM_IE6_FRAME_DURATION,
    // time elapsed from the gesture event to the actual paint
    TOUCHPERFITEM_IE6_LATENCY_DURATION,
    // time spent during paint/scroll
    TOUCHPERFITEM_IE6_PAINT_DURATION,
    // time between from the end of one frame to the beginning of the next
    TOUCHPERFITEM_IE6_FRAME_INTERVAL_DURATION,

    // latency of gesture for start menu
    TOUCHPERFITEM_STARTMENU_LATENCY_DURATION,
    TOUCHPERFITEM_STARTMENU_FRAMERATE_DURATION,
    
    // latency of gesture for confettiplus (homescreen) 
    TOUCHPERFITEM_CONFETTIPLUS_LISTVIEW_LATENCY_DURATION,
    TOUCHPERFITEM_CONFETTIPLUS_LISTVIEW_FRAMERATE_DURATION,
    
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
