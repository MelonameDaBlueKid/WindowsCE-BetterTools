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
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.


// Must define GUIDs, not just declare them. (But only do this
// in one source code file per module; otherwise, linker complains.)
#include <objbase.h>
#include <initguid.h>

#include "PimExProvider.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_SampleProvider, CSampleProvider)
END_OBJECT_MAP()

HANDLE g_currentInstance = NULL;


///////////////////////////////////////////////////////////////////////////
// Function:
//      DllMain
//
// Purpose:
//      Dll entry point.
//
// Returns values:
//      S_OK                        Success
//      ...
//
BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    g_currentInstance = hInstance;

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, (HINSTANCE)hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        _Module.Term();
    }
    
    return TRUE;
}


///////////////////////////////////////////////////////////////////////////
// Function:
//      DllCanUnloadNow
//
// Purpose:
//      Used to determine whether the DLL can be unloaded by OLE.
//
// Returns values:
//      S_OK                        Success
//      ...
//
STDAPI DllCanUnloadNow(void)
{
    ASSERT(_Module.GetLockCount() >= 0);
    return (_Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}


///////////////////////////////////////////////////////////////////////////
// Function:
//      DllGetClassObject
//
// Purpose:
//      Returns a class factory to create an object of the requested type.
//
// Returns values:
//      S_OK                        Success
//      ...
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    int cRetry = 0;
    
    // try a few time to sync to the instance
    while (g_currentInstance == NULL)
    {
        Sleep(500);
        
        cRetry++;
        
        if (cRetry > 3)
        {
            return E_FAIL;
        }            
    }        

    return _Module.GetClassObject(rclsid, riid, ppv);
}


///////////////////////////////////////////////////////////////////////////
// Function:
//      DllRegisterServer
//
// Purpose:
//      This method is called when RegSvrCE is called.
//      It registers the source provider and set the source-id for all the 
//      contact and appointment items so they are register to this source provider.
//      
//  Notes:
//      See the notes in the ItemSetup() for side effects of doing this on install.        
//
// Returns values:
//      S_OK                        Success
//      ...
//
STDAPI DllRegisterServer(void)
{
    HRESULT         hr      = E_FAIL;
    IPOutlookApp2   *polApp = NULL;

    hr = RegisterPIMSource();
    CHR(hr);

    // Do the setup to have this demo run
    hr = InitPOOM(&polApp);
    CHR(hr);
    CBR(NULL != polApp);

    // Update the contacts so we can use them with this source provider.
    hr = ItemSetup(polApp, olContactItem, TRUE);
    
    // Update the appointment so we can use them with this source provider.
    hr = ItemSetup(polApp, olAppointmentItem, TRUE);

Error:
    UnInitPOOM(polApp);

    if (FAILED(hr))
    {
        // Lets un-register to be safe
        DllUnregisterServer();
    }
    
    return hr;
}


///////////////////////////////////////////////////////////////////////////
// Function:
//      DllUnregisterServer
//
// Purpose:
//      This method is called when RegSvrCE /U is called.
//      It unregister the source provider and reverts the contact and appointment
//      items to their original state.
//
// Returns values:
//      S_OK                        Success
//      ...
//
STDAPI DllUnregisterServer(void)
{
    HRESULT         hr          = E_FAIL;
    BOOL            bRet        = TRUE;
    IPOutlookApp2   *polApp     = NULL;


    // We don't want to quit of this fails.
    hr = UnregisterPIMSource();
    // We need to reset the source-id prop for the items, so we'll just 
    // continue but flag the error.
    if (FAILED(hr))
    {
        bRet = FALSE;
    }

    hr = InitPOOM(&polApp);
    CHR(hr);
    CBR(NULL != polApp);

    // Undo the updates to contacts we made during the install.
    hr = ItemSetup(polApp, olContactItem, FALSE);
    // We need to reset the source-id prop for the other items, so we'll just 
    // continue but flag the error.
    if (FAILED(hr))
    {
        bRet = FALSE;
    }


    // Undo the updates to appts we made during the install.
    hr = ItemSetup(polApp, olAppointmentItem, FALSE);
    // Flag the failure.
    if (FAILED(hr))
    {
        bRet = FALSE;
    }


Error:
    UnInitPOOM(polApp);

    if (FAILED(hr) || !bRet)
    {
        hr = E_FAIL;
    }
    
    return hr;
}

