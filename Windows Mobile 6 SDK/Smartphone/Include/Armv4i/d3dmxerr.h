//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of your Microsoft Windows CE
// Source Alliance Program license form.  If you did not accept the terms of
// such a license, you are not authorized to use this source code.
//
//----------------------------------------------------------------------
//                                                                      
//   d3dxmerr.h --  0xC code definitions for the D3DMX API                
//                                                                      
//                                                                      
//----------------------------------------------------------------------
#ifndef __D3DMXERR_H__
#define __D3DMXERR_H__

// 
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_D3DMX    0x877



//
// MessageId: D3DMXERR_NOMEMORY
//
// MessageText:
//
//  Out of memory.
// 
#define D3DMXERR_NOMEMORY    ((HRESULT)0xC8770BB8L)


//
// MessageId: D3DMXERR_NULLPOINTER
//
// MessageText:
//
//  A NULL pointer was passed as a parameter.
// 
#define D3DMXERR_NULLPOINTER    ((HRESULT)0xC8770BB9L)


//
// MessageId: D3DMXERR_INVALIDD3DMXDEVICEINDEX
//
// MessageText:
//
//  The Device Index passed in is invalid.
// 
#define D3DMXERR_INVALIDD3DMXDEVICEINDEX    ((HRESULT)0xC8770BBAL)


//
// MessageId: D3DMXERR_NODIRECTDRAWAVAILABLE
//
// MessageText:
//
//  DirectDraw has not been created.
// 
#define D3DMXERR_NODIRECTDRAWAVAILABLE    ((HRESULT)0xC8770BBBL)


//
// MessageId: D3DMXERR_NODIRECT3DAVAILABLE
//
// MessageText:
//
//  Direct3D has not been created.
// 
#define D3DMXERR_NODIRECT3DAVAILABLE    ((HRESULT)0xC8770BBCL)


//
// MessageId: D3DMXERR_NODIRECT3DDEVICEAVAILABLE
//
// MessageText:
//
//  Direct3D device has not been created.
// 
#define D3DMXERR_NODIRECT3DDEVICEAVAILABLE    ((HRESULT)0xC8770BBDL)


//
// MessageId: D3DMXERR_NOPRIMARYAVAILABLE
//
// MessageText:
//
//  Primary surface has not been created.
// 
#define D3DMXERR_NOPRIMARYAVAILABLE    ((HRESULT)0xC8770BBEL)


//
// MessageId: D3DMXERR_NOZBUFFERAVAILABLE
//
// MessageText:
//
//  Z buffer has not been created.
// 
#define D3DMXERR_NOZBUFFERAVAILABLE    ((HRESULT)0xC8770BBFL)


//
// MessageId: D3DMXERR_NOBACKBUFFERAVAILABLE
//
// MessageText:
//
//  Backbuffer has not been created.
// 
#define D3DMXERR_NOBACKBUFFERAVAILABLE    ((HRESULT)0xC8770BC0L)


//
// MessageId: D3DMXERR_COULDNTUPDATECAPS
//
// MessageText:
//
//  Failed to update caps database after changing display mode.
// 
#define D3DMXERR_COULDNTUPDATECAPS    ((HRESULT)0xC8770BC1L)


//
// MessageId: D3DMXERR_NOZBUFFER
//
// MessageText:
//
//  Could not create Z buffer.
// 
#define D3DMXERR_NOZBUFFER    ((HRESULT)0xC8770BC2L)


//
// MessageId: D3DMXERR_INVALIDMODE
//
// MessageText:
//
//  Display mode is not valid.
// 
#define D3DMXERR_INVALIDMODE    ((HRESULT)0xC8770BC3L)


//
// MessageId: D3DMXERR_INVALIDPARAMETER
//
// MessageText:
//
//  One or more of the parameters passed is invalid.
// 
#define D3DMXERR_INVALIDPARAMETER    ((HRESULT)0xC8770BC4L)


//
// MessageId: D3DMXERR_INITFAILED
//
// MessageText:
//
//  D3DMX failed to initialize itself.
// 
#define D3DMXERR_INITFAILED    ((HRESULT)0xC8770BC5L)


//
// MessageId: D3DMXERR_STARTUPFAILED
//
// MessageText:
//
//  D3DMX failed to start up.
// 
#define D3DMXERR_STARTUPFAILED    ((HRESULT)0xC8770BC6L)


//
// MessageId: D3DMXERR_D3DMXNOTSTARTEDYET
//
// MessageText:
//
//  D3DMXInitialize() must be called first.
// 
#define D3DMXERR_D3DMXNOTSTARTEDYET    ((HRESULT)0xC8770BC7L)


//
// MessageId: D3DMXERR_NOTINITIALIZED
//
// MessageText:
//
//  D3DMX is not initialized yet.
// 
#define D3DMXERR_NOTINITIALIZED    ((HRESULT)0xC8770BC8L)


//
// MessageId: D3DMXERR_FAILEDDRAWTEXT
//
// MessageText:
//
//  Failed to render text to the surface.
// 
#define D3DMXERR_FAILEDDRAWTEXT    ((HRESULT)0xC8770BC9L)


//
// MessageId: D3DMXERR_BADD3DMXCONTEXT
//
// MessageText:
//
//  Bad D3DMX context.
// 
#define D3DMXERR_BADD3DMXCONTEXT    ((HRESULT)0xC8770BCAL)


//
// MessageId: D3DMXERR_CAPSNOTSUPPORTED
//
// MessageText:
//
//  The requested device capabilities are not supported.
// 
#define D3DMXERR_CAPSNOTSUPPORTED    ((HRESULT)0xC8770BCBL)


//
// MessageId: D3DMXERR_UNSUPPORTEDFILEFORMAT
//
// MessageText:
//
//  The image file format is unrecognized.
// 
#define D3DMXERR_UNSUPPORTEDFILEFORMAT    ((HRESULT)0xC8770BCCL)


//
// MessageId: D3DMXERR_IFLERROR
//
// MessageText:
//
//  The image file loading library error.
// 
#define D3DMXERR_IFLERROR    ((HRESULT)0xC8770BCDL)


//
// MessageId: D3DMXERR_FAILEDGETCAPS
//
// MessageText:
//
//  Could not obtain device caps.
// 
#define D3DMXERR_FAILEDGETCAPS    ((HRESULT)0xC8770BCEL)


//
// MessageId: D3DMXERR_CANNOTRESIZEFULLSCREEN
//
// MessageText:
//
//  Resize does not work for full-screen.
// 
#define D3DMXERR_CANNOTRESIZEFULLSCREEN    ((HRESULT)0xC8770BCFL)


//
// MessageId: D3DMXERR_CANNOTRESIZENONWINDOWED
//
// MessageText:
//
//  Resize does not work for non-windowed contexts.
// 
#define D3DMXERR_CANNOTRESIZENONWINDOWED    ((HRESULT)0xC8770BD0L)


//
// MessageId: D3DMXERR_FRONTBUFFERALREADYEXISTS
//
// MessageText:
//
//  Front buffer already exists.
// 
#define D3DMXERR_FRONTBUFFERALREADYEXISTS    ((HRESULT)0xC8770BD1L)


//
// MessageId: D3DMXERR_FULLSCREENPRIMARYEXISTS
//
// MessageText:
//
//  The app is using the primary in full-screen mode.
// 
#define D3DMXERR_FULLSCREENPRIMARYEXISTS    ((HRESULT)0xC8770BD2L)


//
// MessageId: D3DMXERR_GETDCFAILED
//
// MessageText:
//
//  Could not get device context.
// 
#define D3DMXERR_GETDCFAILED    ((HRESULT)0xC8770BD3L)


//
// MessageId: D3DMXERR_BITBLTFAILED
//
// MessageText:
//
//  Could not bitBlt.
// 
#define D3DMXERR_BITBLTFAILED    ((HRESULT)0xC8770BD4L)


//
// MessageId: D3DMXERR_NOTEXTURE
//
// MessageText:
//
//  There is no surface backing up this texture.
// 
#define D3DMXERR_NOTEXTURE    ((HRESULT)0xC8770BD5L)


//
// MessageId: D3DMXERR_MIPLEVELABSENT
//
// MessageText:
//
//  There is no such miplevel for this surface.
// 
#define D3DMXERR_MIPLEVELABSENT    ((HRESULT)0xC8770BD6L)


//
// MessageId: D3DMXERR_SURFACENOTPALETTED
//
// MessageText:
//
//  The surface is not paletted.
// 
#define D3DMXERR_SURFACENOTPALETTED    ((HRESULT)0xC8770BD7L)


//
// MessageId: D3DMXERR_ENUMFORMATSFAILED
//
// MessageText:
//
//  An error occured while enumerating surface formats.
// 
#define D3DMXERR_ENUMFORMATSFAILED    ((HRESULT)0xC8770BD8L)


//
// MessageId: D3DMXERR_COLORDEPTHTOOLOW
//
// MessageText:
//
//  D3DMX only supports color depths of 16 bit or greater.
// 
#define D3DMXERR_COLORDEPTHTOOLOW    ((HRESULT)0xC8770BD9L)


//
// MessageId: D3DMXERR_INVALIDFILEFORMAT
//
// MessageText:
//
//  The file format is invalid.
// 
#define D3DMXERR_INVALIDFILEFORMAT    ((HRESULT)0xC8770BDAL)


//
// MessageId: D3DMXERR_NOMATCHFOUND
//
// MessageText:
//
//  No suitable match found.
// 
#define D3DMXERR_NOMATCHFOUND    ((HRESULT)0xC8770BDBL)



#endif //__D3DMXERR_H__

