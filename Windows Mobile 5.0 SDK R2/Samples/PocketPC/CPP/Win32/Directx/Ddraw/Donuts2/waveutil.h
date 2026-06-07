//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
/*==========================================================================
 *
 *
 *  File:       waveutil.h
 *  Content:    Routines for dealing with sounds from resources
 *
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

//#############################################################################
//
// Data types
//
//#############################################################################

typedef struct _tag_WAVEBUFFER  WAVEBUFFER, * PWAVEBUFFER;
typedef struct _tag_WAVESTREAM  WAVESTREAM, * PWAVESTREAM;

//#############################################################################
//
// Data methods
//
//#############################################################################
PWAVESTREAM CWaveStream_Create(ULONG, PWAVEBUFFER, BOOL fLooping);
BOOL CWaveStream_Close(PWAVESTREAM);
BOOL CWaveStream_Play(PWAVESTREAM pWaveStream);
BOOL CWaveStream_SetPan(PWAVESTREAM pWaveStream, LONG lPan);
BOOL CWaveStream_IsPlaying(PWAVESTREAM);
BOOL CWaveStream_Stop(PWAVESTREAM);
BOOL CWaveStream_SetRate(PWAVESTREAM pWaveStream, ULONG ulRate);

PWAVEBUFFER CWaveBuffer_CreateFromResource(HMODULE hModule, LPCTSTR lpName);
ULONG CWaveBuffer_GetDuration(PWAVEBUFFER);
void CWaveBuffer_Release(PWAVEBUFFER);





///////////////////////////////////////////////////////////////////////////////
//
// helper routines
//
///////////////////////////////////////////////////////////////////////////////

BOOL ParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pdwWaveSize);

#ifdef __cplusplus
}
#endif

