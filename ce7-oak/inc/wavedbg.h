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
#ifndef __WAVEDBG_H__
#define __WAVEDBG_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// DEBUG message support
//

#ifndef SHIP_BUILD
#define ZONE_TEST       DEBUGZONE(0)
#define ZONE_PARAMS     DEBUGZONE(1)
#define ZONE_VERBOSE    DEBUGZONE(2)
#define ZONE_INTERRUPT  DEBUGZONE(3)
#define ZONE_WODM       DEBUGZONE(4)
#define ZONE_WIDM       DEBUGZONE(5)
#define ZONE_PDD        DEBUGZONE(6)
#define ZONE_MDD        DEBUGZONE(7)
#define ZONE_REGS       DEBUGZONE(8)
#define ZONE_MISC       DEBUGZONE(9)
#define ZONE_INIT       DEBUGZONE(10)
#define ZONE_IOCTL      DEBUGZONE(11)
#define ZONE_ALLOC      DEBUGZONE(12)
#define ZONE_FUNCTION   DEBUGZONE(13)
#define ZONE_WARN       DEBUGZONE(14)
#define ZONE_ERROR      DEBUGZONE(15)


#endif

// For backwards compat only
#define PRINTMSG DEBUGMSG
#define ERRMSG(str)            PRINTMSG(ZONE_ERROR, (TEXT("[ERROR] ")TEXT( #str )TEXT("\r\n")))


#ifdef FILELOGGING
#pragma message ("Using the PPLOG functions")
HANDLE pplog_open  (PTCHAR szFilename);
BOOL   pplog_close (HANDLE hLog);
BOOL   pplog_write (HANDLE hLog, DWORD dwCondition, PTCHAR szString);
BOOL   pplog_flush (HANDLE hLog);
#else
#pragma message ("Stubbing the PPLOG functions")
#define pplog_open(x)          0
#define pplog_close(x)         0
#define pplog_write(x,y,z)     0
#define pplog_flush(x)         0
#endif


extern HANDLE hLog;
extern HANDLE hLog2;

#ifdef __cplusplus
}
#endif

#endif /* __WAVEDBG_H__ */
