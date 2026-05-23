/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/*++

Module Name:

    stdevs.h

Abstract:

    Header file for Stock Portfolio device ActiveSync module for Windows CE Services
--*/

// 
//  === Handler to serialize/deserialize objects ====================
//
class CDataHandler : public IReplObjHandler
{
public:
    CDataHandler( void );
    ~CDataHandler();

    // ******** IUnknown methods **************
    STDMETHODIMP_(ULONG)    AddRef( void );
    STDMETHODIMP_(ULONG)    Release( void );
    STDMETHODIMP            QueryInterface( REFIID riid, void **ppvObject );
    
    // ******** IReplObjHandler methods **************
    STDMETHODIMP Setup( PREPLSETUP pSetup );
    STDMETHODIMP Reset( PREPLSETUP pSetup );

	STDMETHODIMP GetPacket( LPBYTE *lppbData,  DWORD *pcbData, DWORD cbRecommend );
    STDMETHODIMP SetPacket( LPBYTE lpbData, DWORD cbData );
    STDMETHODIMP DeleteObj( PREPLSETUP pSetup );

private:
	long	    m_cRef;
    PREPLSETUP  m_pWriteSetup, m_pReadSetup;
    STPACKET    m_packet;
};

