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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

PackageInfoAPI.h

Abstract:  

Provides function prototypes and data definitions for using the
PackageInfoAPI

Notes: 


--*/
#ifndef _PKGINFOAPI_H_
#define _PKGINFOAPI_H_

#ifdef __cplusplus
extern "C" {
#endif // __CPLUSPLUS

#define MAX_PKGNAME 100

#define PKG_UPDATE                     0x00000001
#define PKG_CANONICAL                  0x00000002
#define NK_PACKAGE                     0x00000004
#define IMGFS_PACKAGE                  0x00000008
#define RESERVED_PACKAGE               0x00000010
#define ULDR_PACKAGE                   0x00000020
#define DELETE_PACKAGE                 0x00000040
#define DELETE_AUTHORITY_MASK          0x00000180
#define DELETE_AUTHORITY_OFFSET        7
#define ALLOW_DOWNGRADE                0x00000200

enum DeleteAuthority
{
    Owner,
    OwnerAndDefaultCerts,
    Anyone,
    Reserved
};
#define DELETE_AUTHORITY(dsmFlags) ((dsmFlags & DELETE_AUTHORITY_MASK) >> DELETE_AUTHORITY_OFFSET)

// Header information for pluggable update app UI
#define UA_UPDATERESULT_HEADER_VERSION_MAJOR 7
#define UA_UPDATERESULT_HEADER_VERSION_MINOR 0
#define UA_UPDATERESULT_HEADER_VERSION ((DWORD)(((WORD)(UA_UPDATERESULT_HEADER_VERSION_MINOR)) | ((DWORD)((WORD)(UA_UPDATERESULT_HEADER_VERSION_MAJOR))) << 16))

// Registry for update app
#define UA_UPDATERESULT_ROOT_KEY HKEY_LOCAL_MACHINE
#define UA_UPDATERESULT_REGKEY_PATH TEXT("System\\ImageUpdate\\UpdateApp\\UpdateResult")

// Output file registry key
#define UA_REGVALUE_OUTPUTFILENAME  TEXT("OutputFileName")

typedef struct _PkgUpdateOutputFileHdr
{
    DWORD cbSize;
    HRESULT hrOverallResult;
    DWORD dwResultTableSize;
} PkgUpdateOutputFileHdr, *PPkgUpdateOutputFileHdr;

// Structure used to store additional information when writing an update result to the registry
typedef struct _PkgUpdateResultHdr
{
    DWORD cbSize;                               // size of PkgUpdateResultHdr
    DWORD dwVersion;                            // version of struct, use UA_PKGUPDATERESULTHDR_VERSION
    SYSTEMTIME stTime;                          // SYSTEMTIME when this struct is created
    PkgUpdateOutputFileHdr UAOutputFileHeader;  // PkgUpdateOutputFileHdr for the update result, retrieved from output file, if exists, otherwise created when this struct is created
} PkgUpdateResultHdr, *PPkgUpdateResultHdr;

// Needs to match the VersionInfo class definition in Package.cs
typedef struct _VersionInfo
{
    WORD wMajor;
    WORD wMinor;
    WORD wQFELevel;
    WORD wBuildNumber;
    struct _VersionInfo & operator =( const struct _VersionInfo & pcVersion )
    {
        wMajor = pcVersion.wMajor;
        wMinor = pcVersion.wMinor;
        wQFELevel = pcVersion.wQFELevel;
        wBuildNumber = pcVersion.wBuildNumber;
        return *this;
    }
    bool operator ==( const struct _VersionInfo & pcVersion ) const
    {
        if( (wMajor == pcVersion.wMajor) &&
            (wMinor == pcVersion.wMinor) &&
            (wQFELevel == pcVersion.wQFELevel) &&
            (wBuildNumber == pcVersion.wBuildNumber) )
        {
            return true;
        }
        return false;
    }
    bool operator >( struct _VersionInfo const & pcVersion ) const
    {
        if( wMajor > pcVersion.wMajor )
        {
            return true;
        }
        if( wMajor < pcVersion.wMajor )
        {
            return false;
        }
        if( wMinor > pcVersion.wMinor )
        {
            return true;
        }
        if( wMinor < pcVersion.wMinor )
        {
            return false;
        }
        if( wQFELevel > pcVersion.wQFELevel )
        {
            return true;
        }
        if( wQFELevel < pcVersion.wQFELevel )
        {
            return false;
        }
        if( wBuildNumber > pcVersion.wBuildNumber )
        {
            return true;
        }

        return false;
    }

}VersionInfo, *PVERSIONINFO;

typedef struct _PkgUpdateResult
{
    GUID guid;
    VersionInfo version;
    HRESULT hr;
    DWORD dwFlags;
} PkgUpdateResult, *PUpdatePkgResult;

typedef void* HPKGENUM;
typedef void* HPKG;
typedef void const * HFILEENTRY;

typedef struct _PACKAGEINFO
{
    DWORD       dwSize;                        // for versioning, so we can add new members to the structure in future revs
    DWORD       dwFlags;                       // Package specific flags.
    DWORD       dwCRC;                         // CRC stored in package
    GUID        packageGuid;                   // package specific GUID
    GUID        interfaceGuid;                 // Interface GUID that this package implements/supports
    VersionInfo packageVersion;                // Full version info for this package
    VersionInfo interfaceVersion;              // Full version info for the interface of this package
    VersionInfo targetVersion;                 // Full version info for the version that this package can update.
    WCHAR       szFriendlyName[MAX_PKGNAME];   // friendly name
} PACKAGEINFO, *PPACKAGEINFO;

HRESULT Pkg_SetBaselineDirectories(
            __in_ecount(cchFileList) LPCTSTR szPathList,
            __in  size_t cchFileList
            );
    
HRESULT Pkg_ResetBaselineDirectories();

// Finds the first valid (valid==not a malicious impersonator) package and supplies the handle needed to get package info
HRESULT Pkg_FindFirstPackage(
            __deref_out HPKGENUM *phPkgEnum,
            __deref_out HPKG *phPkg
            );

// Finds the next valid package and supplies the handle needed to get package info. S_FALSE indicates the end of the enumeration
HRESULT Pkg_FindNextPackage(
            __in  HPKGENUM hPkgEnum, 
            __out HPKG* phPkg
            );

// Closes the package enumerator
HRESULT Pkg_FindClose(
            __in  HPKGENUM hPkgEnum
            );

// 'open' a package with specified GUID supplying the handle needed to get package info.
// This is an alternative to using the FindFirstPackage/FindNextPackage API
HRESULT Pkg_OpenPackageByGUID(
            __in  REFGUID guidPkg,
            __deref_out_opt HPKG *phPkg
            );

// 'open' a package with specified name supplying the handle needed to get package info.
// This is an alternative to using the FindFirstPackage/FindNextPackage API
HRESULT Pkg_OpenPackageByName(
            __in  LPCTSTR szFileName,
            __deref_out HPKG* phPkg
            );


// 'close' the package (previously opened with Pkg_FindFirstPackage, Pkg_FindNextPackage or Pkg_OpenPackageByGUID) 
HRESULT Pkg_Close(
            __in  HPKG hPkg
            );

// Enumerate shadowed packages.
HRESULT Pkg_GetNextShadowedPackage(
            __in  HPKG hPkg, 
            __out_bcount(sizeof(GUID)) GUID* pguidShadowedPkg
            );

// Enumerate dependencies. S_FALSE indicates the end of the enumeration
HRESULT Pkg_GetFirstDependentPackage(
            __out HPKG hPkg,
            __out GUID *pguidDependentPkg,
            __out struct _VersionInfo * pDependentPackageVersion
            );

// Enumerate dependencies. S_FALSE indicates the end of the enumeration
HRESULT Pkg_GetNextDependentPackage(
            __out HPKG hPkg,
            __out GUID *pguidDependentPkg,
            __out struct _VersionInfo * pDependentPackageVersion
            );

// Returns the name of the first file in the package. cbSize is the size of the buffer, in characters.
// If the buffer is not large enough, then cbSize is set to the required size.
HRESULT Pkg_FindFirstFile(
            __out HPKG hPkg,
            __out_ecount_opt(*cchSize) LPTSTR pszFileName,
            __inout DWORD* cchSize
            );

// Enumerate files in the package. S_FALSE indicates the end of the enumeration. cbSize is the size of the buffer, in characters.
// If the buffer is not large enough, then cbSize is set to the required size.
HRESULT Pkg_GetNextFile(
            __out HPKG hPkg, 
            __out_ecount_opt(*cchSize) LPTSTR pszFileName,
            __inout DWORD* cchSize
            );

// Get the single-occurrence info for the package
HRESULT Pkg_GetPkgInfo(
            __in  HPKG hPkg,
            __out PPACKAGEINFO pPackageInfo
            );

// Determine if the package contains a specific file.
HRESULT Pkg_ContainsFile(
            __in  HPKG hPkg,
            __in  LPCTSTR szFileName,
            __deref_out_opt HFILEENTRY const ** phFileEntry
            );

// Validates the header indices and offsets.
HRESULT Pkg_ValidateHeader(
            __in  HPKG hPkg,
            __in  DWORD dwFileSize
            );

// Copies the CERT data from the DSM into the buffer specified. If no buffer is specified
// or the buffer is not large enough, the size, in bytes, is returned in dwByteCount.
// Returns E_FAIL if the DSM does not contain CERT data.
HRESULT Pkg_GetCERTData(
            __in  HPKG hPkg,
            __out_bcount_opt(*pcbBufferSize) LPVOID lpBuffer,
            __inout DWORD* pcbBufferSize
            );

#ifdef UNDER_CE //WINCE_BUG_147305

// Given a blob of data and its size sets the update results from a previous package update attempt
HRESULT Pkg_SetUpdateResults(
            __in  const BYTE* lpcData,
            __in  DWORD cbDataSize,
            __in_opt SYSTEMTIME* pTime = NULL
            );

// Return a the blob of data from saved from a previous package update atttempt
HRESULT Pkg_GetUpdateResults(
            __out_bcount(*lpcbDataSize) LPBYTE lpData,
            __inout LPDWORD lpcbDataSize
            );
#endif //UNDER_CE

#ifdef __cplusplus
}
#endif // __CPLUSPLUS

#endif _PKGINFOAPI_H_
