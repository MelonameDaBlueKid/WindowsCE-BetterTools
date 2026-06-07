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

/// CTXMENU.CPP - class implementation for CContextMenuSample

#include "common.h"

#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))


extern UINT g_cRefDLL;
extern HINSTANCE g_hinstDLL;


const CHAR c_aszVerb[] = "CME Sample";  // not UNICODE!


UINT g_idCmd = 0;


//****************************************************************************
// Function Name: CContextMenuSample
// 
// Purpose: constructor for the class
// 
// Arguments:
//    NONE
//
// Return Values:
//    NONE
//
// Side Effects:
//
// Description:
//
//****************************************************************************
CContextMenuSample::CContextMenuSample()
{
    m_cRef = 0;
    m_punkSite = NULL;
    ++g_cRefDLL;
}


//****************************************************************************
// Function Name: ~CContextMenuSample
// 
// Purpose: destructor for the class
// 
// Arguments:
//    NONE
//
// Return Values:
//    NONE
// 
// Side Effects:
//
// Description:
//
//****************************************************************************
CContextMenuSample::~CContextMenuSample()
{
    ASSERT(0 == m_cRef);

    if (NULL != m_punkSite)
    {
        m_punkSite->Release();
    }
    
    --g_cRefDLL;
}


//****************************************************************************
// Function Name: AddRef
//
// Purpose:  IUnknown::AddRef
//
// Arguments:
//    NONE
//
// Return Values:
//    ULONG - new reference count
//
// Side Effects:
//
// Description:
//
//****************************************************************************
STDMETHODIMP_(ULONG) CContextMenuSample::AddRef()
{
    return ++m_cRef;
}


//****************************************************************************
// Function Name: Release
// 
// Purpose: IUnknown::Release()
// 
// Arguments:
//    NONE
// 
// Return Values:
//    ULONG - new reference count 
//  
// Side Effects: 
//  
// Description: 
//    
//****************************************************************************
STDMETHODIMP_(ULONG) CContextMenuSample::Release()
{
    if (0 == --m_cRef)
    {
        delete this;
        return 0;
    }

    return m_cRef;
}


//****************************************************************************
// Function Name: QueryInterface
// 
// Purpose: IUnknown::QueryInterface
// 
// Arguments:
//    IN REFIID riid - interface identifier
//    OUT LPVOID *ppv - interface pointer returned if supported
//  
// Return Values:
//    HRESULT - success/failure
// 
// Side Effects: 
//  
// Description: 
//    
//****************************************************************************
STDMETHODIMP CContextMenuSample::QueryInterface(
	REFIID riid, 
	LPVOID *ppv
	)
{
    if (NULL == ppv)
	{
        return E_POINTER;
	}

    *ppv = NULL;

    if (IID_IUnknown == riid)
	{
        *ppv = (LPVOID)this;
	}
    else if (IID_IContextMenu == riid)
	{
		*ppv = dynamic_cast<IContextMenu*>(this);
	}
    else if (IID_IObjectWithSite == riid)
	{
		*ppv = dynamic_cast<IObjectWithSite*>(this);
	}

    if (NULL != *ppv)
    {
        ((IUnknown *)(*ppv))->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;

}


//****************************************************************************
// Function Name: GetCommandString
//
// Purpose: get the command string for this context menu item
//
// Arguments:
//    IN UINT idCmd - the menu command identifier
//    IN UINT uFlags - flags specifying what information is being requested
//    IN/OUT UINT *pwReserved - ignored
//    OUT LPSTR pszName - output buffer
//    IN UINT cchMax - length of output buffer
//
// Return Values:
//    HRESULT - SUCCESS/FAILURE
//
// Side Effects:
//
// Description: 
//
//****************************************************************************
STDMETHODIMP CContextMenuSample::GetCommandString(
	UINT idCmd, 
	UINT uFlags,
    UINT *pwReserved, 
	LPSTR pszName, 
	UINT cchMax
	)
{
    HRESULT hr = NOERROR;

    UNREFERENCED_PARAMETER(pwReserved);

    switch (uFlags)
    {
        case GCS_HELPTEXT:
            // no help text
            if ((NULL != pszName) && (cchMax > 0))
			{
				*pszName = '\0';
			}
            break;

        case GCS_VALIDATE:
            // only one command - does it match?
            if ((0 == g_idCmd) || (idCmd != g_idCmd))
			{
                hr = S_FALSE;
			}
            break;

        case GCS_VERB:
            // only one verb
            if (idCmd != g_idCmd)
			{
                hr = E_FAIL;
			}
            else
            {
                // copy the verb
                if (NULL != pszName)
				{
                    strncpy(pszName, c_aszVerb, cchMax);
				}
            }
            break;

        default:
            hr = E_NOTIMPL;
            break;
    }

    return hr;

}


//****************************************************************************
// Function Name: InvokeCommand
//
// Purpose: invoke a command from the context menu
//
// Arguments:
//    IN/OUT LPCMINVOKECOMMANDINFO pici - ptr to command info struct
//
// Return Values:
//    HRESULT - SUCCESS/FAILURE
//
// Side Effects:
//
// Description: 
//
//****************************************************************************
STDMETHODIMP CContextMenuSample::InvokeCommand(
	LPCMINVOKECOMMANDINFO pici
	)
{
    HRESULT hr = NOERROR;

    if (NULL == pici)
    {
        hr = E_POINTER;
    }
    else
    {
        if (sizeof(CMINVOKECOMMANDINFO) != pici->cbSize)
        {
            // there's no CMINVOKECOMMANDINFOEX in WinCE
            hr = E_INVALIDARG;
        }
        else
        {
            IDataObject *pIdo;
            
            if (FAILED(GetSite(IID_IDataObject, (void **)&pIdo)))
            {
                hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_NULL,
                    ERROR_NO_SUCH_SITE);
            }
            else
            {
                FORMATETC fe;
                STGMEDIUM sm;
                
                fe.cfFormat = CF_HDROP;
                fe.ptd = NULL;
                fe.dwAspect = DVASPECT_CONTENT;
                fe.lindex = -1;
                fe.tymed = TYMED_HGLOBAL;

                if (FAILED(pIdo->GetData(&fe, &sm)))
                {
                    hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_STORAGE,
                        ERROR_INVALID_PARAMETER);
                }
                else
                {
                    DROPFILES *pdf;
                    TCHAR *pszFile;
                    
                    pdf = (DROPFILES *)sm.hGlobal;
                    // pdf->pFiles is offset to doubly NULL terminated filename
                    // File Explorer only supports Context Menu extensions when a single
                    // file is selected, so this will always point to a single filename
                    // that is double NULL terminated.
                    pszFile = (TCHAR *)((BYTE *)pdf + pdf->pFiles);
                    MessageBox(NULL, pszFile, TEXT("CME Sample"), MB_OK); 
                
                    LocalFree(sm.hGlobal);
                }

                pIdo->Release();
            }
        }
    }

    return hr;

}


//****************************************************************************
// Function Name: QueryContextMenu
//
// Purpose: add commands to the context menu
//
// Arguments:
//    IN HMENU hmenu - handle to the menu
//    IN UINT indexMenu - zero-based position at which to insert the first item
//    IN UINT idCmdFirst - first available command ID
//    IN UINT idCmdLast - last available command ID
//    IN UINT uFlags - optional flags
//
// Return Values:
//    HRESULT - SUCCESS/FAILURE
//
// Side Effects:
//
// Description: 
//
//****************************************************************************
STDMETHODIMP CContextMenuSample::QueryContextMenu(
	HMENU hmenu,
    UINT indexMenu, 
	UINT idCmdFirst,
	UINT idCmdLast,
	UINT uFlags
	)
{
    HRESULT hr = NOERROR;

    UNREFERENCED_PARAMETER(uFlags);

    if (idCmdLast < idCmdFirst)
    {
        hr = E_INVALIDARG;
    }
    else
    {
        IDataObject *pIdo;

        // get the site
        if (FAILED(GetSite(IID_IDataObject, (void **)&pIdo)))
        {
            hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_NULL,
                ERROR_NO_SUCH_SITE);
        }
        else
        {
            FORMATETC fe;
            STGMEDIUM sm;
            
            fe.cfFormat = CF_HDROP;
            fe.ptd = NULL;
            fe.dwAspect = DVASPECT_CONTENT;
            fe.lindex = -1;
            fe.tymed = TYMED_HGLOBAL;

            if (FAILED(pIdo->GetData(&fe, &sm)))
            {
                hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_STORAGE,
                    ERROR_INVALID_PARAMETER);
            }
            else
            {
                // sm.hGlobal contains pointer to a DROPFILES stucture
                
                TCHAR szCommand[MAX_PATH];
                DROPFILES *pdf;
                TCHAR *pszFile;
                
                // load the "CME Sample" string
                StringCchCopy(szCommand, ARRAYSIZE(szCommand), (LPTSTR)LoadString(g_hinstDLL, IDS_SAMPLE,
                    NULL, 0));

                pdf = (DROPFILES *)sm.hGlobal;
                // pdf->pFiles is offset to doubly NULL terminated filename
                // File Explorer only supports Context Menu extensions when a single
                // file is selected, so this will always point to a single filename
                // that is double NULL terminated.
                pszFile = (TCHAR *)((BYTE *)pdf + pdf->pFiles);
                
                // Tack on the filename
                StringCchCat(szCommand, ARRAYSIZE(szCommand), pszFile);
                
                // add one command
                g_idCmd = idCmdFirst;
                if (InsertMenu(hmenu, indexMenu, MF_BYPOSITION, g_idCmd,
                        szCommand))
                {
                    hr = MAKE_HRESULT(SEVERITY_SUCCESS, 0, 1);
                }
                LocalFree(sm.hGlobal);
            }

            pIdo->Release();

        }
    }

    return hr;

}


//****************************************************************************
// Function Name: GetSite
//
// Purpose: get the owner (site) of the object
//
// Arguments:
//    IN REFIID riid - interface ID to retrieve
//    OUT void **ppvSite - interface pointer
//
// Return Values:
//    HRESULT - SUCCESS/FAILURE
//
// Side Effects:
//
// Description: 
//
//****************************************************************************
STDMETHODIMP CContextMenuSample::GetSite(
	REFIID riid, 
	void **ppvSite
	)
{
    HRESULT hr = NOERROR;

    if (NULL == ppvSite)
    {
        hr = E_POINTER;
    }
    else
    {
        if (NULL == m_punkSite)
        {
            // no site
            *ppvSite = NULL;
            hr = E_FAIL;
        }
        else
        {
            // see if we have the requested interface
            hr = m_punkSite->QueryInterface(riid, ppvSite);
        }
    }

    return hr;

}


//****************************************************************************
// Function Name: SetSite
//
// Purpose: set the owner (site) of the object
//
// Arguments:
//    IN IUnknown *pUnkSite - object pointer
//
// Return Values:
//    HRESULT - SUCCESS/FAILURE
//
// Side Effects:
//
// Description: 
//
//****************************************************************************
STDMETHODIMP CContextMenuSample::SetSite(
	IUnknown *pUnkSite
	)
{
    if (NULL != pUnkSite)
    {
        pUnkSite->AddRef();
    }

    if (NULL != m_punkSite)
    {
        m_punkSite->Release();
    }
    
    m_punkSite = pUnkSite;

    return NOERROR;

}
