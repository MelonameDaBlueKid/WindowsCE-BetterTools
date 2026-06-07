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

#include "StdAfx.h"

#define INITGUID
#include <initguid.h>
#include <Imaging.h>

#include "ImageView.h"



CImageView::CImageView(void)
  : m_hFile(INVALID_HANDLE_VALUE),
    m_pbBuffer(NULL),
	m_cbBuffer(0),
	m_dwPreviousTickCount(0),
    m_dwElapsedViewTime(0),
	m_pImage(NULL),
	m_fRightsCommitted(false)
{
}


CImageView::~CImageView(void)
{
	RELEASE_OBJ(m_pImage);

	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle (m_hFile);
	}

	if (m_pbBuffer)
	{
		LocalFree (m_pbBuffer);
	}
}


HRESULT CImageView::OpenImageFile (const HWND hWnd, const LPCTSTR pszFullName)
{
	HRESULT hr;
	DWORD dwRightsStatus;

	assert (m_hFile == INVALID_HANDLE_VALUE);

	hr = FileDrmVerifyRights (hWnd, pszFullName, FDRRF_DISPLAY, 0, &dwRightsStatus);
	if (SUCCEEDED (hr))
	{
		hr = StringCchCopy (m_szFileName, ARRAYSIZE (m_szFileName), pszFullName);
		if (SUCCEEDED (hr))
		{
			hr = FileDrmCreateFile (m_szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
										OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0, &m_hFile);
			if (SUCCEEDED (hr))
			{
				hr = ReadImageFile ();
				if (SUCCEEDED (hr))
				{
					hr = CreateIImage();
				}
			}
		}
	}
	return hr;
}


HRESULT CImageView::ReadImageFile ()
{
	HRESULT	hr = E_FAIL;

	assert (m_pbBuffer == NULL);

	m_cbBuffer = GetFileSize (m_hFile, NULL);
	if (m_cbBuffer != 0xFFFFFFFF)
	{
		m_pbBuffer = static_cast<BYTE *>(LocalAlloc (LMEM_FIXED, m_cbBuffer));
		if (m_pbBuffer)
		{
			DWORD cbRead;
			if (!ReadFile (m_hFile, m_pbBuffer, m_cbBuffer, &cbRead, NULL) || (m_cbBuffer != cbRead))
			{
				LocalFree (m_pbBuffer);
				m_pbBuffer = NULL;
			}
			hr = S_OK;
		}
	}

	if (FAILED (hr))
	{
		const DWORD dwLastError = GetLastError ();
		hr = HRESULT_FROM_WIN32 (dwLastError);
	}

	return hr;
}

HRESULT CImageView::CreateIImage ()
{
	HRESULT	hr;
	IImagingFactory	*pImgFactory = NULL;

	assert (m_pImage == NULL);

	hr = CoCreateInstance (CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER,
								IID_IImagingFactory, (void **)&pImgFactory);
	if (SUCCEEDED (hr))
	{
		hr = pImgFactory->CreateImageFromBuffer (m_pbBuffer, m_cbBuffer, DISPOSAL_NONE, &m_pImage);
	    pImgFactory->Release();
	}
	return hr;
}


/*
 *  Draw the image and manage the rights associated with the image
 *
 *  We first check to see if we have already committed rights for the
 *  image. If we have then we need to check if we can still display the
 *  image -- we need to do this if there are any type of time-based rights
 *  associated with the image. 
 *
 *  FileDrmGetMetric() is called with the FDRM_METRIC_REVERIFY_TIME parameter
 *  which returns a time interval in milliseconds representing how often we
 *  need to reverify rights for the image. Note that since we compute the
 *  elapsed time interval between successive calls to CImageView::Draw we
 *  do not need to worry about clock rollover.
 *
 *  If we still have rights (or have never committed rights) we then go on
 *  to draw the image. If we have not committed rights we then call 
 *  FileDrmCommitRights once the image has been succesfully displayed.
 */
HRESULT CImageView::Draw (HWND hWnd, HDC hdc, RECT *rc)
{
	HRESULT hr = S_OK;

	if (m_fRightsCommitted)
	{
		DWORD dwRightsStatus;
		DWORD dwCurrentTickCount = GetTickCount ();
		DWORD dwReverifyTime;

		hr = FileDrmGetMetric (FDRM_METRIC_REVERIFY_TIME, &dwReverifyTime);
		if (SUCCEEDED (hr))
		{
			m_dwElapsedViewTime += (dwCurrentTickCount - m_dwPreviousTickCount);
			if (m_dwElapsedViewTime >= dwReverifyTime)
			{
				// Reverify rights
				hr = FileDrmVerifyRights (hWnd, m_szFileName, FDRRF_DISPLAY, 
											FDRVF_VERIFY_CONTINUE, &dwRightsStatus);
				m_dwElapsedViewTime = 0;
			}
			m_dwPreviousTickCount = dwCurrentTickCount;
		}
	}

	if (SUCCEEDED (hr))
	{
        // This call will shrink or stretch the image to fit in the bounding rectangle rc.
        // It would be better to check for small images and not stretch them.
        ImageInfo imageInfo;
        m_pImage->GetImageInfo (&imageInfo);

        SIZE size;
        m_pImage->GetPhysicalDimension (&size);

		hr = m_pImage->Draw (hdc, rc, NULL);
		if (SUCCEEDED (hr))
		{
			if (!m_fRightsCommitted)
			{
				hr = FileDrmCommitRights (m_hFile, FDRRF_DISPLAY, 0);
				if (SUCCEEDED (hr))
				{
					m_fRightsCommitted = true;
					m_dwPreviousTickCount = GetTickCount ();
				}
			}
		}
	}

	return hr;
}
