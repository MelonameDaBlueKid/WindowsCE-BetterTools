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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
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
// Kernel area
//
//      0x80000000 - 0x9FFFFFFF: statically mapped, cached (512M)
//      0xA0000000 - 0xBFFFFFFF: statically mapped, uncached (512M)
//      0xC0000000 - 0xC7FFFFFF: Kernel XIP DLLs (128M)
//      0xC8000000 - 0xCFFFFFFF: object store (128M)
//      0xD0000000 - 0xDFFFFFFF: Kernel VM (256M)
//      0xE0000000 - 0xEFFFFFFF: Kernel VM (256M, cpu dependent)
//      0xF0000000 - 0xFFFFFFFF: CPU specific VM (256M)
//
#define VM_KMODE_BASE           0x80000000  // kernel mode address start (1G, 512M each, cached/uncached)
#define VM_KDLL_BASE            0xC0000000  // Kernel mode XIP DLLs (128M)
#define VM_OBJSTORE_BASE        0xC8000000  // object store (128M)    // defined in pkfuncs.h
#define VM_NKVM_BASE            0xD0000000  // Kernel VM base (256M)

// max object store size = 128M - VM_BLOCK_SIZE (-64K for protection)
#define VM_MAX_OBJSTORE_SIZE    (VM_OBJSTORE_BASE - VM_KDLL_BASE - VM_BLOCK_SIZE)

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

//
// VM page/block info
//
#define VM_PAGE_SIZE            0x1000              // page-size always 4K
#define VM_BLOCK_SIZE           0x10000             // block size == 64K

#define VM_PAGE_SHIFT           12                  // shift amount to convert VA to page number
#define VM_BLOCK_SHIFT          16                  // shift amount to convert VA to block nubmer

#define VM_PAGE_OFST_MASK       (VM_PAGE_SIZE - 1)     // mask to get page offset
#define VM_BLOCK_OFST_MASK      (VM_BLOCK_SIZE - 1)    // mask to get block offset

//
// Useful macro/functions
//
#ifndef ASM_ONLY
// validate a if a pointer points to a valid range in the user space
__inline BOOL IsValidUsrPtr (LPCVOID ptr, DWORD dwSize, BOOL fWrite)
{
    return ((int) dwSize >= 0)
        && ((int) ptr >= VM_USER_BASE)
        && (((DWORD) ptr + dwSize) < (fWrite? VM_SHARED_HEAP_BASE : VM_KMODE_BASE));
}

// IsKernelVa - check if an address is between 0x80000000 and 0xC0000000 (kernel static mapping area)
__inline BOOL IsKernelVa (LPCVOID pAddr)
{
    return ((DWORD) pAddr >= VM_KMODE_BASE) && (VM_KDLL_BASE > (DWORD) pAddr);
}

// IsInKVM - check if an address is between 0xc0000000 - 0xd0000000 (KVM area)
__inline BOOL IsInKVM (DWORD dwAddr)
{
    return (dwAddr >= VM_NKVM_BASE) && (dwAddr < VM_CPU_SPECIFIC_BASE);
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
// IsInSharedHeap - check if an address is between 0x70000000 - 0x7fffffff
//
__inline BOOL IsInSharedHeap (DWORD dwAddr)
{
    return ((int) dwAddr > VM_SHARED_HEAP_BASE);
}

#endif

#ifdef __cplusplus
}
#endif

#endif  // _VM_LAYOUT_H_

