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


#ifndef __RTCPLUGAUDIOINTERFACE_H__
#define __RTCPLUGAUDIOINTERFACE_H__

// Functions to allocate/release RTC buffers

/* HRESULT AllocateNewRecordBuffer(DWORD*pdwContext, BYTE** ppBuffer, DWORD* pdwMaxBufferSize); */
typedef HRESULT (*PFN_ALLOCATENEWRECORDBUFFER)(DWORD*, BYTE**, DWORD*);

/* HRESULT ReleaseRecordBuffer(DWORD dwContext); */
typedef HRESULT (*PFN_RELEASERECORDBUFFER)(DWORD);

/* HRESULT ReleasePlaybackBuffer(DWORD dwContext); */
typedef HRESULT (*PFN_RELEASEPLAYBACKBUFFER)(DWORD);


typedef struct tagRTC_BUFFER_CONTROL{
    
PFN_ALLOCATENEWRECORDBUFFER pFnAllocateNewRecordBuffer ;
PFN_RELEASERECORDBUFFER  pFnReleasePlaybackBuffer;
PFN_RELEASEPLAYBACKBUFFER  pFnReleaseRecordBuffer;

}RTC_BUFFER_CONTROL;

// Pluggbale API defintions

// Functions to assist pluggable audio dll to do global setup
extern "C"
HRESULT WINAPI RTC_GlobalSetup();

// Functions to assist pluggable audio dll to do global cleanup
extern "C"
HRESULT WINAPI RTC_GlobalCleanup();

// Playback Audio functions to be implmented by the pluggable audio dll
extern "C"
HRESULT WINAPI RTC_OpenPlaybackDevice(DWORD dwWaveID, 
                                  DWORD dwBuffLen, 
                                  DWORD dwSampleRate,
                                  WORD dwNumChannels, 
                                  DWORD dwNumBits);


extern "C"
HRESULT WINAPI RTC_ClosePlaybackDevice(const RTC_BUFFER_CONTROL * pBufferCtrl);

extern "C"
HRESULT WINAPI  RTC_StartPlaybackDevice();

extern "C"
HRESULT WINAPI  RTC_StopPlaybackDevice(const RTC_BUFFER_CONTROL * pBufferCtrl);

extern "C"
HRESULT WINAPI  RTC_PlayBuffer(const RTC_BUFFER_CONTROL * pBufferCtrl, DWORD dwBufferContext, BYTE* buffer, DWORD dwSize);

extern "C"
HRESULT WINAPI  RTC_SetPlaybackVolume(DWORD dwVolume);


extern "C"
HRESULT WINAPI  RTC_GetPlaybackVolume(DWORD* pdwVolume);


extern "C"
HRESULT WINAPI  RTC_IsPlaying(BOOL* pfPlaying);


// Record Audio functions to be implmented by the pluggable audio dll
extern "C"
HRESULT WINAPI  RTC_OpenRecordDevice(DWORD dwWaveID, 
                                 DWORD dwBuffLen, 
                                 DWORD dwSampleRate,
                                 WORD dwNumChannels, 
                                 DWORD dwNumBits);


extern "C"
HRESULT WINAPI  RTC_CloseRecordDevice(const RTC_BUFFER_CONTROL * pBufferCtrl);


extern "C"
HRESULT WINAPI  RTC_StartRecordDevice(const RTC_BUFFER_CONTROL * pBufferCtrl);

extern "C"
HRESULT WINAPI  RTC_StopRecordDevice(const RTC_BUFFER_CONTROL * pBufferCtrl);


extern "C"
HRESULT WINAPI  RTC_GetRecordedBuffer(const RTC_BUFFER_CONTROL * pBufferCtrl, DWORD* pdwBufferContext, DWORD* pdwSize);


extern "C"
HRESULT WINAPI  RTC_IsRecording(BOOL* pfRecording);

//typedef global functions
typedef HRESULT (*PFN_GLOBALSETUP)();
typedef HRESULT (*PFN_GLOBALCLEANUP)();

// typedef Playback functions
typedef HRESULT (*PFN_OPENPLAYBACKDEVICE)(DWORD, DWORD, DWORD,WORD, DWORD);
typedef HRESULT (*PFN_CLOSEPLAYBACKDEVICE)(const RTC_BUFFER_CONTROL*);
typedef HRESULT (*PFN_STARTPLAYBACKDEVICE)();
typedef HRESULT (*PFN_STOPPLAYBACKDEVICE)(const RTC_BUFFER_CONTROL *);
typedef HRESULT (*PFN_PLAYBUFFER)(const RTC_BUFFER_CONTROL * , DWORD, BYTE*, DWORD);
typedef HRESULT (*PFN_SETPLAYBACVOLUME)(DWORD);
typedef HRESULT (*PFN_GETPLAYBACVOLUME)(DWORD*);
typedef HRESULT (*PFN_ISPLAYING)(BOOL*);

// typedef Record functions
typedef HRESULT (*PFN_OPENRECORDDEVICE)(DWORD, DWORD, DWORD, WORD, DWORD);
typedef HRESULT (*PFN_CLOSERECORDDEVICE)(const RTC_BUFFER_CONTROL *);
typedef HRESULT (*PFN_STARTRECORDDEVICE)(const RTC_BUFFER_CONTROL *);
typedef HRESULT (*PFN_STOPRECORDDEVICE)(const RTC_BUFFER_CONTROL *);
typedef HRESULT (*PFN_GETRECORDEDBUFFER)(const RTC_BUFFER_CONTROL * , DWORD*, DWORD*);
typedef HRESULT (*PFN_ISRECORDING)(BOOL*);
#endif // __RTCPLUGAUDIOINTERFACE_H__


