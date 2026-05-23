/*****************************************************************************

    File: PeExt.h
    Purpose: Phone Event Extension mechanism

    History:
        Created - KK 6-18-2

*/

#pragma once

#define PEDISP_CALLER_ID    100 // Param0 [VT_BSTR] - caller ID informaton of current call
#define PEDISP_INCOMING     101 // Param0 [VT_INT] - number of incoming calls
#define PEDISP_TALKING      102 // Param0 [VT_INT] - number of talking calls
#define PEDISP_HELD         103 // Param0 [VT_INT] - number of held calls
#define PEDISP_CONNECTED    104 // Param0 [VT_INT] - total number of connected calls (held + talking)
#define PEDISP_NEW_SITE_HWND    105 // Param0 [VT_UINT] - Hwnd of the new site window.  Clients can also retrieve this from IOleWindow::GetWindow
#define PEDISP_CALL_OID     106 // Param0 [VT_UINT] - when there is a single call, this is the oid of the contact if the caller is in the contacts.  Getting a 0 means there is no applicable contact.



