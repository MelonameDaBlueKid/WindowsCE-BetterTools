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
//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//
//--------------------------------------------------------------------------;

#ifndef __VIDEOCTL__
#define __VIDEOCTL__

// These help with property page implementations. The first can be used to
// load any string from a resource file. The buffer to load into is passed
// as an input parameter. The same buffer is the return value if the string
// was found otherwise it returns TEXT(""). The GetDialogSize is passed the
// resource ID of a dialog box and returns the size of it in screen pixels

#define STR_MAX_LENGTH 256
TCHAR * WINAPI StringFromResource(TCHAR *pBuffer, int iResourceID);

#ifdef UNICODE
#define WideStringFromResource StringFromResource
#else
WCHAR * WINAPI WideStringFromResource(WCHAR *pBuffer, int iResourceID);
#endif

#ifndef UNDER_CE
BOOL WINAPI GetDialogSize(int iResourceID,     // Dialog box resource identifier
                          DLGPROC pDlgProc,    // Pointer to dialog procedure
                          LPARAM lParam,       // Any user data wanted in pDlgProc
                          SIZE *pResult);      // Returns the size of dialog box
#endif

// Class that aggregates an IDirectDraw interface

class CAggDirectDraw : public IDirectDraw, public CUnknown
{
protected:

    LPDIRECTDRAW m_pDirectDraw;

public:

    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid,void **ppv);

    // Constructor and destructor

    CAggDirectDraw(TCHAR *pName,LPUNKNOWN pUnk) :
        CUnknown(pName,pUnk),
        m_pDirectDraw(NULL) { };

    virtual CAggDirectDraw::~CAggDirectDraw() { };

    // Set the object we should be aggregating
    void SetDirectDraw(LPDIRECTDRAW pDirectDraw) {
        m_pDirectDraw = pDirectDraw;
    }

    // IDirectDraw methods

    STDMETHODIMP CreateClipper(DWORD, LPDIRECTDRAWCLIPPER *, IUnknown *);
    STDMETHODIMP CreatePalette(DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE *, IUnknown *);
    STDMETHODIMP CreateSurface(LPDDSURFACEDESC, LPDIRECTDRAWSURFACE *, IUnknown *);
    STDMETHODIMP EnumDisplayModes(DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMMODESCALLBACK);
    STDMETHODIMP EnumSurfaces(DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMSURFACESCALLBACK);
    STDMETHODIMP FlipToGDISurface();
    STDMETHODIMP GetCaps(LPDDCAPS, LPDDCAPS);
    STDMETHODIMP GetDisplayMode(LPDDSURFACEDESC);
    STDMETHODIMP GetFourCCCodes(LPDWORD, LPDWORD);
    STDMETHODIMP GetGDISurface(LPDIRECTDRAWSURFACE *);
    STDMETHODIMP GetMonitorFrequency(LPDWORD);
    STDMETHODIMP GetScanLine(LPDWORD);
    STDMETHODIMP GetVerticalBlankStatus(LPBOOL);
    STDMETHODIMP RestoreDisplayMode();
    STDMETHODIMP SetCooperativeLevel(HWND, DWORD);
    STDMETHODIMP SetDisplayMode(DWORD, DWORD, DWORD, DWORD, DWORD);
    STDMETHODIMP WaitForVerticalBlank(DWORD, HANDLE);
    STDMETHODIMP GetAvailableVidMem(LPDDSCAPS, LPDWORD, LPDWORD);
    STDMETHODIMP GetSurfaceFromDC(HDC, LPDIRECTDRAWSURFACE *);
    STDMETHODIMP RestoreAllSurfaces();
    STDMETHODIMP TestCooperativeLevel();
    STDMETHODIMP GetDeviceIdentifier(LPDDDEVICEIDENTIFIER, DWORD);
};


// Class that aggregates an IDirectDrawSurface interface

class CAggDrawSurface : public IDirectDrawSurface, public CUnknown
{
protected:

    LPDIRECTDRAWSURFACE m_pDirectDrawSurface;

public:

    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid,void **ppv);

    // Constructor and destructor

    CAggDrawSurface(TCHAR *pName,LPUNKNOWN pUnk) :
        CUnknown(pName,pUnk),
        m_pDirectDrawSurface(NULL) { };

    virtual ~CAggDrawSurface() { };

    // Set the object we should be aggregating
    void SetDirectDrawSurface(LPDIRECTDRAWSURFACE pDirectDrawSurface) {
        m_pDirectDrawSurface = pDirectDrawSurface;
    }

    // IDirectDrawSurface methods

    STDMETHODIMP AddOverlayDirtyRect(LPRECT);
    STDMETHODIMP Blt(LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDBLTFX);
    STDMETHODIMP EnumAttachedSurfaces(LPVOID, LPDDENUMSURFACESCALLBACK);
    STDMETHODIMP EnumOverlayZOrders(DWORD, LPVOID, LPDDENUMSURFACESCALLBACK);
    STDMETHODIMP Flip(LPDIRECTDRAWSURFACE, DWORD);
    STDMETHODIMP GetBltStatus(DWORD);
    STDMETHODIMP GetCaps(LPDDSCAPS);
    STDMETHODIMP GetClipper(LPDIRECTDRAWCLIPPER *);
    STDMETHODIMP GetColorKey(DWORD, LPDDCOLORKEY);
    STDMETHODIMP GetDC(HDC *);
    STDMETHODIMP GetFlipStatus(DWORD);
    STDMETHODIMP GetOverlayPosition(LPLONG, LPLONG);
    STDMETHODIMP GetPalette(LPDIRECTDRAWPALETTE *);
    STDMETHODIMP GetPixelFormat(LPDDPIXELFORMAT);
    STDMETHODIMP GetSurfaceDesc(LPDDSURFACEDESC);
    STDMETHODIMP IsLost();
    STDMETHODIMP Lock(LPRECT, LPDDSURFACEDESC, DWORD, HANDLE);
    STDMETHODIMP ReleaseDC(HDC);
    STDMETHODIMP Restore();
    STDMETHODIMP SetClipper(LPDIRECTDRAWCLIPPER);
    STDMETHODIMP SetColorKey(DWORD, LPDDCOLORKEY);
    STDMETHODIMP SetOverlayPosition(LONG, LONG );
    STDMETHODIMP SetPalette(LPDIRECTDRAWPALETTE);
    STDMETHODIMP Unlock(LPRECT);
    STDMETHODIMP UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDOVERLAYFX);
    STDMETHODIMP UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE);
    STDMETHODIMP GetDDInterface(LPDIRECTDRAW *);
    STDMETHODIMP AlphaBlt(LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDALPHABLTFX);
};


// ActiveMovie must work on multiple platforms, in particular it also runs on
// Windows NT 3.51 which does not have DirectDraw capabilities. The filters
// cannot therefore link statically to the DirectDraw library. To make their
// lives that little bit easier we provide this class that manages loading
// and unloading the library and creating the initial IDirectDraw interface

typedef DWORD (WINAPI *PGETFILEVERSIONINFOSIZE)(LPTSTR,LPDWORD);
typedef BOOL (WINAPI *PGETFILEVERSIONINFO)(LPTSTR,DWORD,DWORD,LPVOID);
typedef BOOL (WINAPI *PVERQUERYVALUE)(LPVOID,LPTSTR,LPVOID,PUINT);

class CLoadDirectDraw
{
    LPDIRECTDRAW m_pDirectDraw;     // The DirectDraw driver instance
    HINSTANCE m_hDirectDraw;        // Handle to the loaded library

public:

    CLoadDirectDraw();
    ~CLoadDirectDraw();

    HRESULT LoadDirectDraw();
    void ReleaseDirectDraw();
    HRESULT IsDirectDrawLoaded();
    LPDIRECTDRAW GetDirectDraw();
};

#endif // __VIDEOCTL__

