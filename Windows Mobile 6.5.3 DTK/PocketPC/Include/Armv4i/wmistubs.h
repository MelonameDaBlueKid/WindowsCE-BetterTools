#ifndef __WMISTUBS__
#define __WMISTUBS__

struct WmiInfo
{
};

#define WMI_MEASURE_START
#define WMI_MEASURE_END

#define MFWMITAG_AUDIO_RENDERER             'ARen'  // MF Audio renderer
#define MFWMITAG_AUDIO_CAPTURER             'ACap'  // MF Audio capturer
#define MFWMITAG_CORE_BASE                  'CorB'  // MF_Core_Base
#define MFWMITAG_MUXER                      'Muxr'  // MF muxer
#define MFWMITAG_SPLITTER                   'Splt'  // MF Splitter
#define MFWMITAG_ASF_MEDIA_SINK             'AfMk'  // MF asf media sink
#define MFWMITAG_ASF_STREAM_SINK            'AfSk'  // MF asf stream sink
#define MFWMITAG_ASF_MEDIA_STREAM           'AfMm'  // MF asf media stream
#define MFWMITAG_CD_MEDIA_STREAM            'CDMm'  // MF CD media stream
#define MFWMITAG_PCMAUDIO_MEDIA_SINK        'CDSK'  // MF PCM audio media sink
#define MFWMITAG_PCMAUDIO_STREAM_SINK       'CDSk'  // MF PCM audio stream sink
#define MFWMITAG_M3U_MEDIA_STREAM           'M3uS'  // MF M3u media stream
#define MFWMITAG_MP3_MEDIA_STREAM           'MP3M'  // MF M3u media stream
#define MFMWITAG_MP3_MEDIA_SOURCE_BASE      'MP3B'  // MF MP3 media source base
#define MFWMITAG_MP3_MEDIA_SINK             'MP3K'  // MF MP3 media sink
#define MFWMITAG_MP3_STREAM_SINK            'MP3k'  // MF MP3 stream sink
#define MFWMITAG_NET_SOURCE                 'NetS'  // MF NetSOurce output
#define MFWMITAG_NET_SINK                   'Nsnk'  // MF Network sink
#define MFWMITAG_HTTP_BYTESTREAM            'HTTP'  // MF HTTP Bytestream
#define MFWMITAG_MEDIACACHE                 'MCch'  // MF MediaCache
#define MFWMITAG_WIN32FILE                  'W32F'  // MF Win32File
#define MFWMITAG_CACHEREADER                'ChRd'  // MF ASF/MP3 Source CacheReader
#define MFWMITAG_MEDIA_PROCESSOR            'MpCr'  // MediaProcess Core
#define MFWMITAG_MEDIA_PROCESSOR_TOPOLOGY   'MpTp'  // MediaProcess Topology
#define MFWMITAG_MEDIA_SESSION_BITPUMP      'MsBp'  // MF Media Session and Bitpump
#define MFWMITAG_ASF_MEDIA_SOURCE           'AfMs'  // MF Asf media source
#define MFWMITAG_VIDEO_MEDIA_SINK           'VSnk'  // MF Video Renderer
#define MFWMITAG_VIDEO_STREAM_SINK          'VStr'  // MF Video Stream
#define MFWMITAG_VIDEO_PRESENTER            'VPrs'  // MF Video Presenter
#define MFWMITAG_VIDEO_MIXER                'VMix'  // MF Video Mixer
#define MFWMITAG_VIDEO_CAPTURER             'VCap'  // MF Video Capturer    
#define MFWMITAG_WMAD                       'WMAD'  // WMA decoder
#define MFWMITAG_WMAE                       'WMAE'  // WMA encoder
#define MFWMITAG_WMSP_ENCODER               'WSPE'  // WM Speech Encoder
#define MFWMITAG_WMSP_DECODER               'WSPD'  // WM Speech Decoder
#define MFWMITAG_WMVD                       'WMVD'  // WMV decoder
#define MFWMITAG_WMVE                       'WMVE'  // WMV encoder
#define MFWMITAG_WMVSD                      'WMSD'  // WMV screen decoder
#define MFWMITAG_WMVSE                      'WMSE'  // WMV screen encoder
#define MFWMITAG_WMAGEQ                     'AGEQ'  // WM audio graphic equalizer
#define MFWMITAG_WMASPKRCORR                'SPKR'  // WM audio speaker/room correction
#define MFWMITAG_WMABASSMGMT                'BASS'  // WM audio bass management
#define MFWMITAG_WMASA                      'WMSA'  // WM audio spetrum analyzer
#define MFWMITAG_WMNORM                     'NORM'  // WM audio normalization
#define MFWMITAG_WMHDCDDEC                  'HDCD'  // WM HDCD decoder
#define MFWMITAG_WMTIMECMP                  'TCMP'  // WM time compression
#define MFWMITAG_WMAUDMORPHING              'AMOR'  // WM audio morpher
#define MFWMITAG_WMAMIX                     'AMIX'  // WM audio mixer
#define MFWMITAG_WMAVRHPHONE                'AVRH'  // WM virtualization headphone
#define MFWMITAG_WMASPKRFILL                'ESPF'  // WM audio Enhanced Speaker Filling
#define MFWMITAG_WMASPDTX                   'SpdT'  // WM audio WMA-Pro S/PDIF transmitter
#define MFWMITAG_AECMA                      'AECM'  // AEC and Micarray
#define MFWMITAG_DVDECODER                  'DVde'  // DV Decoder
#define MFWMITAG_DVENCODER                  'DVen'  // DV Encoder
#define MFWMITAG_MPEG2DEC                   'MPGD'  // MPEG2 Decoder 
#define MFWMITAG_AC3DEC                     'AC3D'  // AC3 Decoder 
#define MFWMITAG_MEDIA_ENGINE               'MEng'  // Media Engine
#define MFWMITAG_TOPOLOADER                 'TpLd'  // Topology loader
#define MFWMITAG_LATENCY                    'Late'  // Component Latency
#define MFWMITAG_SOURCERESOLVER             'SoRe'  // Source Resolver
#define MFWMITAG_VIDEO_RECORDER             'VRec'  // MF Video Recorder
#define MFWMITAG_TRANSFORM                  'Tran'  // MF Transform
#define MFWMITAG_COLOR_CONTROL              'CCtr'  // MF Color Control
#define MFWMITAG_FRAMERATE_CONVERTER        'FrCv'  // MF Frame Rate Converter
#define MFWMITAG_SMPTE_TRANSFORMS           'Smpt'  // MF SMPTE Transforms
#define MFWMITAG_COLOR_LEGALIZER            'CLgl'  // MF Color Legalizer
#define MFWMITAG_VIDEO_DENOISER             'VDns'  // MF Video Denoiser
#define MFWMITAG_COLORCONV                  'CCon'  // WM Color Conversion
#define MFWMITAG_RESIZE                     'Resz'  // WM Resizer
#define MFWMITAG_FRAME_INTERPOLATION        'FInp'  // WM Frame Interpolation
#define MFWMITAG_INTERLACE_TELECINE         'Telc'  // WM DeInterlace and Telecine
#define MFWMITAG_WMRESAMP                   'ARes'  // Audio Resampler
#define MFWMITAG_SEQUENCER_SOURCE           'TSrc'  // WM Timeline Source
#define MFWMITAG_QM                         'QMan'  // MF Quality Manager
#define MFWMITAG_MEIDA_PROC_SOURCE          'MPSc'  // WM Media Proc Source
#define MFWMITAG_FRAME_GRABBER              'FRGB'  // WM Frame Grabber Source
#define MFWMITAG_WAV_MEDIA_SINK             'WAVK'  // MF WAV media sink
#define MFWMITAG_WAV_STREAM_SINK            'WAVk'  // MF WAV stream sink
#define MFWMITAG_AVI_MEDIA_SINK             'AVIK'  // MF AVI media sink
#define MFWMITAG_AVI_STREAM_SINK            'AVIk'  // MF AVI stream sink
#define MFWMITAG_MEDIACLIP                  'MClp'  // MF Media Clip
#define MFWMITAG_SCRIPT_SINK                'SCRK'  // MF Script sink
#define MFWMITAG_FIRSTPASS_SINK             '1PAK'  // MF FirstPass sink
#define MFWMITAG_RATELESSNULL_SINK          'RLNK'  // MF Rateless Null sink
#define MFWMITAG_FILETRANSFER_SINK          'FTRK'  // MF File Transfer sink
#define MFWMITAG_MPG_SOURCE                 'MPGS'  // MF MPEG Source
#define MFWMITAG_AUDIOFILE_SOURCE           'AUFS'  // MF Audio File Source
#define MFWMITAG_SCREENCAP_SOURCE           'SCPS'  // MF Screen Capture Source
#define MFWMITAG_IMAGE_SOURCE               'IMGS'  // MF Image Source
#define MFWMITAG_SCRIPT_SOURCE              'SCRS'  // MF Script Source
#define MFWMITAG_SILENCE_SOURCE             'SILS'  // MF Silence Source
#define MFWMITAG_SOLIDCOLOR_SOURCE          'SLCS'  // WM Solid Color Source
#define MFWMITAG_FILETRANSFER_SOURCE        'FTRS'  // MF File Transfer Source
#define MFWMITAG_UNMANAGED_SINK             'UNMK'  // MF Unmanaged wrapper sink
#define MFWMITAG_EVER_SOURCE                'EVRS'  // MF EVeR Source
#define MFWMITAG_SBE_SOURCE                 'SBES'  // MF SBE Media Source
#define MFWMITAG_METADATA                   'Meta'  // MF Metadata
#define MFWMITAG_METADATA_TRANSFORM         'MXFM'  // MF Metadata Transform
#define MFWMITAG_METADATA_RULES             'MXFR'  // MF Metadata Rules
#define MFWMITAG_SAMI_SOURCE                'SAMI'  // MF SAMI Media Source
#define MFWMITAG_SAMPLEGRABBER_SINK         'SGSK'  // MF Sample Grabber Sink
#define MFWMITAG_GEN_FILE_MEDIA_SINK        'GENK'  // MF Generic File media sink
#define MFWMITAG_GEN_FILE_STREAM_SINK       'GENk'  // MF Generic File stream sink
#define MFWMITAG_PRESENTATION_CLOCK         'PClk'  // MF Presentation Clock
#define MFWMITAG_DEV_PLATFORM               'Pltf'  // MF Development Platform
#define MFWMITAG_SMX_SOURCE                 'SMXS'  // MF SMX Media Source
#define MFWMITAG_SMX_TRANSFORM              'SMXT'  // MF SMX Transform
#define MFWMITAG_MFGRAPH                    'MFGR'  // MF Graph
#define MFWMITAG_WMP_PLAYBACK               'WMPP'  // WMP Playback
#define MFWMITAG_PEAUTHCOMM                 'PEAU'  // MF PEAuth's communication
#define MFWMITAG_SOURCE_PROXY               'SrPx'  // Source Proxy
#define MFWMITAG_MS_LFX_APO                 'MLFX'
#define MFWMITAG_MS_GFX_APO                 'MGFX'
#define MFWMITAG_DMO_WRAPPER                'DMOW'  // DMO wrapper filter
#define MFWMITAG_GENERIC                    'GENF'  // Generic filter/DMO


#define bWMILOG_OBJECT                  0
#define bWMILOG_AUDIORENDER_STARVATION  0
#define bWMILOG_VIDEO_FRAME_GLITCH      0
#define bWMILOG_DATA_DROP               0
#define bWMILOG_CLOCK_GETTIME           0
#define bWMILOG_CLOCK_SETTIME           0
#define bWMILOG_VIDEOSAMPLE_TIME        0
#define bWMILOG_STREAM                  0
#define bWMILOG_MEDIATYPE_CHANGE        0
#define bWMILOG_BUFFER                  0
#define bWMILOG_MF_PROCESS              0
#define bWMILOG_UNUSUAL_STREAMING_EVENT 0
#define bWMILOG_FILE_OPEN               0
#define bWMILOG_FILE_CLOSE              0
#define bWMILOG_MF_DISKIO_REQUEST       0
#define bWMILOG_MF_DISKIO_COMPLETE      0
#define bWMILOG_RENDERER_REND           0
#define bWMILOG_RENDERER_SAMPLE         0
#define bWMILOG_AUDIORENDERER_BUFFERFULLNESS 0
#define bWMILOG_STATE_CHANGE            0
#define bWMILOG_MF_MEDIATYPE_CHANGE     0
#define bWMILOG_MEDIAENGINE             0
#define bWMILOG_TOPOLOADER              0
#define bWMILOG_PACKETSINK              0
#define bWMILOG_MEDIACACHE              0
#define bWMILOG_NETSOURCE               0
#define bWMILOG_HTTP_BYTESTREAM         0
#define bWMILOG_BITPUMP                 0
#define bWMILOG_BITPUMP_DETAILS         0
#define bWMILOG_SESSION_EVENT           0
#define bWMILOG_SOURCERESOLUTION        0
#define bWMILOG_SEQUENCER               0
#define bWMILOG_QM                      0
#define bWMILOG_MEDIAPROCSOURCE         0
#define bWMILOG_FRAMEGRABBER            0
#define bWMILOG_ADJUST_SAMPLE_TIME      0
#define bWMILOG_MEDIACLIP               0
#define bWMILOG_VIDEO_RENDER            0
#define bWMILOG_AUDIO_RENDER            0
#define bWMILOG_METADATA                0
#define bWMILOG_TRANSFORM_CREATION      0
#define bWMILOG_MUXER                   0
#define bWMILOG_TIMER_LATE              0
#define bWMILOG_LOCK                    0
#define bWMILOG_STACK                   0
#define bWMILOG_MFGRAPH                 0
#define bWMILOG_WMP_PLAYBACK            0
#define bWMILOG_PEAUTHCOMM              0
#define bWMILOG_CACHEREADER             0
#define bWMILOG_CODEC_DXVA              0

#define WMILOG_OBJECT(dwReporterTag,lActionType,pObject,lObjectType)
#define WMILOG_AUDIORENDER_STARVATION(dwReporterTag,pObject,ullCount )
#define WMILOG_VIDEO_FRAME_GLITCH( dwReporterTag,pObject,pSample,llSampleTime,llTargetSystemTime,llOffset)
#define WMILOG_DATA_DROP(dwReporterTag,dwDataType,pObject,llSampleTime,cbDropped,dwReasons)
#define WMILOG_CLOCK_GETTIME(dwReporterTag,pObject,llTime )
#define WMILOG_CLOCK_SETTIME(dwReporterTag,pObject,llTime,llDelta )
#define WMILOG_PREDICTED_VIDEOSAMPLE_TIME( dwReporterTag,pObject,llTime )
#define WMILOG_STREAM( dwReporterTag,lStreamType,pObject )
#define WMILOG_MEDIATYPE_CHANGE(dwReporterTag, pObject,pStream,cbNewType,pbNewType )

#define WMILOG_TRANSFORM_CREATION( dwReporterTag,pObject,pguidTransform,pTransform,bUserTransform )
#define WMILOG_BUFFER(dwReporterTag,pObject,Type,dwObjectCategory,pStream,llTimestamp,pClock,pSample,cbBuffer,cbSample,llDuration )
#define WMILOG_MF_PROCESS( dwReporterTag,pObject,Type,dwObjectCategory,pvSamp,ulByteCount,llTime,ullProcessTime )
#define WMILOG_UNUSUAL_STREAMING_EVENT(dwReporterTag,Type,pObject,dwEvent)
#define WMILOG_FILE_OPEN( dwReporterTag,pObject,h,pwszName )
#define WMILOG_FILE_CLOSE( dwReporterTag,pObject,h,pwszName )
#define WMILOG_MF_DISKIO_REQUEST( dwReporterTag,Type,pObject,h,qwOffset,bCount )
#define WMILOG_MF_DISKIO_COMPLETE( dwReporterTag,Type,pObject,h )
#define WMILOG_RENDERER_REND( dwReporterTag,Type,pObject,pSample,llTime,llDuration,llClock )

#define WMILOG_RENDERER_MIX( dwReporterTag, Type, pObject, pSample, llTime, llDuration, llClock ) \
    WMILOG_RENDERER_REND( dwReporterTag, Type, pObject, pSample, llTime, llDuration, llClock )

#define WMILOG_AUDIORENDERER_BUFFERFULLNESS( dwReporterTag,pObject,dwFullness)
#define WMILOG_STATE_CHANGE( dwReporterTag,pObject,dwStateChange)
#define WMILOG_MF_SAMPLE(dwReporterTag,pObject,Type,dwObjectCategory,pStream,pClock,pSample )
#define WMILOG_MEDIAENGINE( dwReporterTag,pObject,dwMET,dwAPICode )
#define WMILOG_TOPOLOADER( dwReporterTag,lActionType,pObject,dwApiCode )
#define WMILOG_PACKETSINK( dwReporterTag,pObject,Type,RtpSeq,PacketNum )
#define WMILOG_MEDIACACHE( dwReporterTag,pObject,Type,SegID,nPending,llTime,pSample)
#define WMILOG_NETSOURCE( dwReporterTag,pObject,Type,Arg1,Arg2 )
#define WMILOG_HTTP_BYTESTREAM( dwReporterTag,pObject,Type )
#define WMILOG_SOURCERESOLUTION( dwReporterTag,pObject,Type,pwszURL,pObjectCreated,hr )
#define WMILOG_SESSION_BITPUMP( dwReporterTag,pObject,Type,dwState,dwContext,hr )
#define WMILOG_SESSION_BITPUMP_DETAILS( dwReporterTag,pObject,Type,dwState,dwContext,hr )
#define WMILOG_SESSION_EVENT( dwReporterTag,pObject,Type,pParam1 )
#define WMILOG_SEQUENCER( dwReporterTag,pObject,Type,dwmet,llTime,pParam1,pwszURL )
#define WMILOG_QM( dwReporterTag,pObject,Type,dwKnobId,dwPrevLevel,dwNewLevel,llDropTime )
#define WMILOG_MEDIAPROCSOURCE( dwReporterTag,pObject,Type,dwmet,llTime,pParam1,pwszURL )
#define WMILOG_FRAMEGRABBER( dwReporterTag,pObject,Type,dwmet,llTime,pParam1,pwszURL )
#define WMILOG_ADJUST_SAMPLE_TIME(dwReporterTag,pObject,ucType,llOriginalSampleTime,llAdjustment )
#define WMILOG_MEDIACLIP( dwReporterTag,pObject,Type,dwmet,llTime,pParam1,pwszURL )
#define WMILOG_VIDEO_RENDER(dwReporterTag,pObject,pSample,llSampleTime,llSampleDuration,llClockTime,hwndVideo,dwRefreshRate,dwWidth,dwHeight,dwLeft,dwTop,dwRight,dwBottom,dwLeft1,dwTop1,dwRight1,dwBottom1)


#define WMILOG_AUDIO_RENDER(dwReporterTag,pObject,pSample,llTime,llDuration,llMasterTime,llDeviceTime)
#define WMILOG_MUXER(dwReportTag,pObject,Type,wStreamNumber,llSampleTime,cbSample,llPacketNumber,llPacketSendTime,cbPacket )
#define WMILOG_TIMER_LATE(dwReporterTag,pObject,llEventTime,llLateBy,pCallback)
#define WMILOG_LOCK(dwReporterTag,pObject,Type,pLockObject)
#define WMILOG_STACK(dwReporterTag,pObject,pFrameList)
#define WMILOG_MFGRAPH( dwReporterTag,pObject,Type,hr )
#define WMILOG_MFGRAPH_EVENT( dwReporterTag,pObject,Type,lParam,bstr )
#define WMILOG_WMP_PLAYBACK( Type,pwszFileName,GraphType,LastHr )
#define WMILOG_PEAUTHCOMM_EVENT( dwReporterTag,pObject,Type )
#define WMILOG_CACHEREADER_EVENT( dwReporterTag,pObject,llInitialOffset,llFinalOffset,dwBytesInCache,dwCacheSize,cbSectorSize )
#define WMILOG_CODEC_DXVA ( dwReporterTag,pObject,Type,dwFrameIndex,llTime )

#define SetFilePointerLogged(hFile,lDistanceToMove,lpDistanceToMoveHigh,dwMoveMethod,x) \
        SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod)

#define WriteFileLogged(hFile,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped,x) \
        WriteFile (hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped)

#define ReadFileLogged(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped,x) \
        ReadFile (hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped)

#endif // __WMISTUBS__
