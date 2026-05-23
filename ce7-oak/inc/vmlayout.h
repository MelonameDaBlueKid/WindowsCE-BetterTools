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
//    vmlayout.h - VM Layout
//


#ifndef _VM_LAYOUT_H_
#define _VM_LAYOUT_H_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------
//
// Kernel area above 0x80000000 for ARM/x86, new style mapping
//
//      0x80000000 - <static mapping End>: statically mapping specified by OEM
//      <static mapping End> - 0xEFFFFFFF: Kernel VM, object store, kernel XIP DLLs
//      0xF0000000 - 0xFFFFFFFF: CPU specific VM (256M)
//

//------------------------------------------------------------------------
//
// Kernel area above 0x80000000 for MIPS, and ARM/x86 in BC mode (old style mapping)
//
//      0x80000000 - 0x9FFFFFFF: statically mapped, cached (512M
//      0xA0000000 - 0xBFFFFFFF: statically mapped, uncached (512M)
//      0xC0000000 - 0xEFFFFFFF: Kernel VM, object store, kernel XIP dlls (768M)
//      0xF0000000 - 0xFFFFFFFF: CPU specific VM (256M)
//

//------------------------------------------------------------------------
//
// Kernel area above 0x80000000 for SHx
//
//      0x80000000 - 0x9FFFFFFF: statically mapped, cached (512M
//      0xA0000000 - 0xBFFFFFFF: statically mapped, uncached (512M)
//      0xC0000000 - 0xDFFFFFFF: Kernel VM, object store, kernel XIP dlls (512M)
//      0xE0000000 - 0xFFFFFFFF: CPU specific VM (512M)
//


#define VM_KMODE_BASE           0x80000000  // kernel mode address start

// The following three are only valid for MIPS/SHx, and ARM/x86 in BC mode.
// DO NOT USE THEM FOR PORTABLE CODE. 
#define VM_KDLL_BASE            0xC0000000
#define VM_OBJSTORE_BASE        0xC0000000
#define VM_NKVM_BASE            0xC0000000


#ifdef SHx
#define VM_CPU_SPECIFIC_BASE    0xE0000000  // cpu specific VM limit
#else
#define VM_CPU_SPECIFIC_BASE    0xF0000000  // cpu specific VM limit
#endif


//------------------------------------------------------------------------
//
// User area
//
//      0x00000000 - 0x00010000: 1st 64K, unmaped, except for UserKData area, if exist
//      0x00100000 - 0x3FFFFFFF: user allocatable VM. 
//                              (exe code/data, RAM DLL code/data, stack, heap, data for ROM dlls)
//      0x40000000 - 0x5FFFFFFF: ROM DLL Code (up to 512M, regualar VM alloc can go top-down in this region)
//      0x60000000 - 0x6FFFFFFF: RAM-backed memory-mappings (those without files below them) (256M)
//      0x70000000 - 0x7FEFFFFF: Shared heap (255M)
//      0x7FF00000 - 0x7FFFFFFF: unmapped (1M) for protection
//  

#define VM_USER_BASE            0x00010000  // user VM base, 1st 64K reserved
#define VM_DLL_BASE             0x40000000  // DLL base
#define VM_RAM_MAP_BASE         0x60000000  // Base of RAM-backed memory-mappings
#define VM_SHARED_HEAP_BASE     0x70000000  // shared heap base
#define VM_SHARED_HEAP_BOUND    0x7FF00000  // 1M less than VM_KMODE_BASE; last 1M in user space is unmapped

//
// VM page/block info
//
#define VM_PAGE_SIZE            0x1000              // page-size always 4K
#define VM_BLOCK_SIZE           0x10000             // block size == 64K

#define VM_PAGE_SHIFT           12                  // shift amount to convert VA to page number
#define VM_BLOCK_SHIFT          16                  // shift amount to convert VA to block nubmer

#define VM_PAGE_OFST_MASK       (VM_PAGE_SIZE - 1)     // mask to get page offset
#define VM_BLOCK_OFST_MASK      (VM_BLOCK_SIZE - 1)    // mask to get block offset

#define PAGEALIGN_UP(X)         (((X) + VM_PAGE_OFST_MASK) & ~VM_PAGE_OFST_MASK)
#define PAGEALIGN_DOWN(X)       ((X) & ~VM_PAGE_OFST_MASK)
#define PAGECOUNT(x)            (((x) + VM_PAGE_OFST_MASK) >> VM_PAGE_SHIFT)

#define BLOCKALIGN_UP(x)        (((x) + VM_BLOCK_OFST_MASK) & ~VM_BLOCK_OFST_MASK)
#define BLOCKALIGN_DOWN(x)      ((x) & ~VM_BLOCK_OFST_MASK)

//
// Useful macro/functions
//
#ifndef ASM_ONLY
// validate a if a pointer points to a valid range in the user space
__inline BOOL IsValidUsrPtr (LPCVOID ptr, DWORD dwSize, BOOL fWrite)
{
    return ((int) dwSize >= 0)
        && ((int) ptr >= VM_USER_BASE)
        && (((DWORD) ptr + dwSize) < (fWrite? (DWORD)VM_SHARED_HEAP_BASE : (DWORD)VM_SHARED_HEAP_BOUND));
}

// IsKModeAddr - check to see if an address is a k-mode only address
__inline BOOL IsKModeAddr (DWORD dwAddr)
{
    return (int) dwAddr < 0;
}

//
// IsInRAMMapSection - check if an address is between 0x60000000 - 0x6fffffff
//
__inline BOOL IsInRAMMapSection (DWORD dwAddr)
{
    return ((dwAddr >= VM_RAM_MAP_BASE) && (dwAddr < VM_SHARED_HEAP_BASE));
}

//
// IsInSharedHeap - check if an address is between 0x70000000 - 0x7FF00000
//
__inline BOOL IsInSharedHeap (DWORD dwAddr)
{
    return ((dwAddr - (DWORD)VM_SHARED_HEAP_BASE) < 0xFF00000);
}

//
// check if the address - address+size falls within the shared heap region
//
__inline BOOL IsInSharedHeapRange(LPCVOID lpAddr, DWORD Size)
{
    return (((DWORD)lpAddr < VM_SHARED_HEAP_BOUND) && ((DWORD)lpAddr+Size > VM_SHARED_HEAP_BASE)) ? TRUE : FALSE;
}

#endif

#ifdef __cplusplus
}
#endif

#endif  // _VM_LAYOUT_H_

