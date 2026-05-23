//  myfile.cpp
//
//  Source file for Device-Independent Bitmap (DIB) API.  Provides
//  the following functions:
//
//  ReadDIBFile()       - Loads a DIB from a file
//
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "dibapi.h"
#include "mainfrm.h"

#include "resource.h"

/*
 * Dib Header Marker - used in writing DIBs to files
 */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

/*************************************************************************

  Function:  ReadDIBFile (CFile&)

   Purpose:  Reads in the specified DIB file into a global chunk of
			 memory.

   Returns:  A handle to a dib (hDIB) if successful.
			 NULL if an error occurs.

  Comments:  BITMAPFILEHEADER is stripped off of the DIB.  Everything
			 from the end of the BITMAPFILEHEADER structure on is
			 returned in the global memory handle.

*************************************************************************/

HDIB WINAPI ReadDIBFile(CFile& file)
{
	DWORD dwBitsSize;
	HDIB hDIB;

#if defined(READ_BM_FROM_RESOURCE)
	// determine location of the bitmap in resource fork
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP), RT_BITMAP);
	HRSRC hrsrc = ::FindResource(hInst, MAKEINTRESOURCE(IDB_BITMAP), RT_BITMAP);
	if (hrsrc == NULL)
		return FALSE;
	dwBitsSize = SizeofResource(NULL, hrsrc);
	if(dwBitsSize == 0)
		return NULL;
	HGLOBAL hGlob = LoadResource(NULL, hrsrc);
	if(hGlob == NULL)
		return NULL;

	hDIB = (HDIB)::GlobalAlloc(LMEM_FIXED | LMEM_ZEROINIT, dwBitsSize);
	if (hDIB == 0)
		return NULL;

	memcpy((void*)hDIB, (const void*)hGlob, dwBitsSize);

#else // READ_BM_FROM_RESOURCE

	BITMAPFILEHEADER bmfHeader;
	LPSTR pDIB;
	/*
	 * get length of DIB in bytes for use when reading
	 */

	dwBitsSize = file.GetLength();

	/*
	 * Go read the DIB file header and check if it's valid.
	 */
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return NULL;

	if (bmfHeader.bfType != DIB_HEADER_MARKER)
		return NULL;

	/*
	 * Allocate memory for DIB
	 */
	hDIB = (HDIB) ::GlobalAlloc(LMEM_FIXED | LMEM_ZEROINIT, dwBitsSize);
	if (hDIB == 0)
	{
		return NULL;
	}
	pDIB = (LPSTR)hDIB;

	/*
	 * Go read the bits.
	 */
	if (file.ReadHuge(pDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) != dwBitsSize - sizeof(BITMAPFILEHEADER) )
	{
		::GlobalFree((HGLOBAL) hDIB);
		return NULL;
	}
#endif // READ_BM_FROM_RESOURCE

	return hDIB;
}

