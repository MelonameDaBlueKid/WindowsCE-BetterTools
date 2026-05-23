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

//
//    fslog.h - define the common structure shared between filesys and kernel
//


#ifndef _FSLOG_H_
#define _FSLOG_H_

#include <vmlayout.h>

#define LOG_MAGIC               0x4d494b45
#define CURRENT_FSLOG_VERSION   0x400
#define MAX_MEMORY_SECTIONS     16

// OID macros from filesys - keep in sync with macros in filesys.h
// OID definition:
    // high 4 bits for filesystem type
    // next 4 bits for version
    // next 24 bits for handle / index

#define SYSTEM_INHEAP            0x0
#define SYSTEM_INROM             0x1
#define SYSTEM_INROMHIVE         0x2
#define SYSTEM_EXTERNAL_VOLUME   0x3
#define SYSTEM_VOLATILE          0x4
#define SYSTEM_EXTERNAL_REPL     0x8
#ifndef SYSTEM_MNTVOLUME
#define SYSTEM_MNTVOLUME         0xe
#else
ERRFALSE(SYSTEM_MNTVOLUME == 0xe);
#endif
#define SYSTEM_INVALID           0xf

#define SYSTEM_FROM_OID(N)             ((N) >> 28)
#define IS_ROMFILE_OID(oid)   (SYSTEM_FROM_OID(oid) == SYSTEM_INROM)
#define ROMFILE_FROM_OID(oid, type, index)                                     \
    ((type = ((oid) >> 12) & 0xf), (index = ((oid) & 0x00000fff)))


// max object store size = 128M - 64K
#define VM_MAX_OBJSTORE_SIZE     (0x08000000 - VM_BLOCK_SIZE)

typedef DWORD FSHANDLE;
typedef FSHANDLE *LPFSHANDLE;

#define DYNAMIC_MAPPED_RAM       0x800      // CANNOT COLIDE WITH CE_RAM_XXX defined in oemglobal.h
                                            // and can only use bottom 12 bits

typedef struct mem_t {
    DWORD BaseAddr;                 // Base Address
                                    //      -- physical address >> 8, if DYNAMIC_MAPPED_RAM is set in ExtnAndAttrib
                                    //      -- statically mapped kernel address, otherwise
    DWORD Length;                   // length (include memory used for usemap)
    DWORD ExtnAndAttrib;            // extension + RamAttributes
} mem_t;

typedef struct fslogentry_t {
    DWORD type;
    DWORD d1, d2, d3;
} fslogentry_t;

typedef struct fshash_t {
    DWORD hashdata[4];
} fshash_t;

#define MAX_PAGES_IN_PAGELIST       ((VM_PAGE_SIZE/sizeof(DWORD)) - 2)  // -2 for pNext and cPages
typedef struct fspagelist_t {
    struct fspagelist_t *pNext;                             // ptr to next page
    DWORD  cPages;                                          // # of pages in this "page list"
    DWORD  pa256pages[MAX_PAGES_IN_PAGELIST];               // (physical address >> 8) for 1022 pages
} fspagelist_t;

// total # of "list page" needed to hold "cPages" object store page.
// Note: the "list page" is also included in the count.
#define LISTPAGE_NEEDED(cPages)     (((cPages) + MAX_PAGES_IN_PAGELIST) / (MAX_PAGES_IN_PAGELIST+1))

#pragma warning(push)
#pragma warning(disable: 4200)
#pragma warning(disable: 4201) // disabling warning regarding unnamed structs/unions.
typedef struct fslog_t {
    DWORD version;       // version of this structure, must stay as first DWORD
    DWORD magic1;        // LOG_MAGIC if memory tables valid
    DWORD magic2;        // LOG_MAGIC if heap initialized
    union {
        struct {         // SystemHeap contains this data
            mem_t        fsmemblk[MAX_MEMORY_SECTIONS];     // Memory blocks
            fspagelist_t *pFSList;
            DWORD        nMemblks;                          // # of memory blocks;
        };
        struct {         // All other heaps contain this data
            CEGUID   guid;
            DWORD    dwRestoreFlags;
            DWORD    dwRestoreStart;
            DWORD    dwRestoreSize;
            fshash_t ROMSignature;  // Hives only: signature of the hive in ROM
        };
    };
    fshash_t pwhash;     // hashed password (stored in SystemHeap or system hive)
    DWORD virtbase;      // VirtBase when last booted
    DWORD entries;       // number of entries in recovery log
    FSHANDLE hDbaseRoot; // handle to first dbase, else INVALID_HDB
    FSHANDLE hReg;       // Handle to registry header, else INVALID_HREG
    union {
        DWORD dwReplInfo;    // Persistent replication information
        DWORD dwSequence;    // Boot Sequence Number
    };
    DWORD flags;         // file system flags. High 24 bits are dbase LCID
    fslogentry_t log[];  // log entries
} fslog_t;
#pragma warning(pop)

// Used for convenience in the memory-mapped file code.  Must match with fslog_t.
typedef struct {
    DWORD dwRestoreFlags;
    DWORD dwRestoreStart;
    DWORD dwRestoreSize;
} FSLogFlushSettings;

#define FSLOG_RESTORE_FLAG_NONE      0  // No flush is currently in progress
#define FSLOG_RESTORE_FLAG_UNFLUSHED 1  // Currently writing pages to end of file (recover from flush failure by discarding the partial flush)
#define FSLOG_RESTORE_FLAG_FLUSHED   2  // Currently writing pages into the fsheap (recover from flush failure by continuing the flush)

// size required for fslog (must be multiple of pages).
#define LOG_RESERVE                 VM_PAGE_SIZE
#define MAX_FS_PAGE                 ((VM_MAX_OBJSTORE_SIZE - LOG_RESERVE)/VM_PAGE_SIZE)


#endif  // _FSLOG_H_
