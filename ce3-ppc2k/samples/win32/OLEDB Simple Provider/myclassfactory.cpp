//--------------------------------------------------------------------
// Microsoft OLE DB Sample OLEDB Simple Provider
// (C) Copyright 1997 Microsoft Corporation.  All Rights Reserved.
//
// module MyClassFactory.cpp | The module contains the DLL Entry and Exit
// points, plus the OLE ClassFactory class.
//
//


////////////////////////////////////////////////////////
// Includes
//
////////////////////////////////////////////////////////
#include "Common.h"
#include "MyClassFactory.h"


// Added GUID constant for the sample object:
// {6BB84A7B-0498-11d3-BB68-00C04F680ACC}
const GUID CLSID_FileOSP = { 0x6bb84a7b, 0x498, 0x11d3, { 0xbb, 0x68, 0x0, 0xc0, 0x4f, 0x68, 0xa, 0xcc } };

////////////////////////////////////////////////////////
// Globals
//
////////////////////////////////////////////////////////
LONG g_cObj	= 0L;						// # of outstanding objects
LONG g_cLock = 0L;						// # of explicit locks set
DWORD g_cAttachedProcesses = 0L;		// # of attached processes
HINSTANCE g_hInstance = NULL;


REGENTRY rgRegInfo[] =
{
	//SampleOSProvider
    { HKEY_CLASSES_ROOT, L"FileOSP",			NULL,	L"Microsoft Sample OLE DB Simple Provider DLL (C++)"							},

	//CLSID
    { HKEY_CLASSES_ROOT, L"FileOSP\\Clsid",		NULL,	L"{6BB84A7B-0498-11d3-BB68-00C04F680ACC}"									},
    { HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7B-0498-11d3-BB68-00C04F680ACC}",							NULL,				L"FileOSP"	},
    { HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7B-0498-11d3-BB68-00C04F680ACC}\\ProgID",					NULL,				L"FileOSP"	},
    { HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7B-0498-11d3-BB68-00C04F680ACC}\\VersionIndependentProgID", NULL,				L"FileOSP"	},
    { HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7B-0498-11d3-BB68-00C04F680ACC}\\InprocServer32",			L"ThreadingModel",	L"Both"		},
    { HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7B-0498-11d3-BB68-00C04F680ACC}\\InprocServer32",			NULL,				L"%s"		},

	// OSP Registry

	{ HKEY_CLASSES_ROOT, L"FileOSPSample", NULL, L"Microsoft Sample OLE DB Simple Provider (File)" },
	{ HKEY_CLASSES_ROOT, L"FileOSPSample\\CLSID", NULL, L"{6BB84A7C-0498-11d3-BB68-00C04F680ACC}" },
	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}", NULL, L"FileOSPSample" },
	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}\\InprocServer32", L"ThreadingModel", L"Both"},
	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}\\InprocServer32", NULL,
#if defined(UNDER_CE)
		L"\\Windows\\MSDAOSP.DLL"}, 		// depends on location of msdaosp.dll
#else
//		L"c:\\winnt\\system32\\MSDAOSP.DLL"}, // depends on location of msdaosp.dll
		L"c:\\program files\\common files\\system\\ole db\\msdaosp.dll"},
#endif

	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}\\ProgID", NULL, L"FileOSPSample"},
	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}\\VersionIndependentProgID", NULL, L"FileOSPSample"},
	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}\\OLE DB Provider", NULL, L"Microsoft Sample OLE DB Simple Provider (File)"},
	{ HKEY_CLASSES_ROOT, L"CLSID\\{6BB84A7C-0498-11d3-BB68-00C04F680ACC}\\OSP Data Object", NULL, L"FileOSP"},
};


////////////////////////////////////////////////////////
// MyClassFactory
//
////////////////////////////////////////////////////////
MyClassFactory::MyClassFactory()
{
    m_cRef = 0;
	InterlockedIncrement(&g_cObj);
}

MyClassFactory::~MyClassFactory()
{
	InterlockedDecrement(&g_cObj);
}


STDMETHODIMP MyClassFactory::QueryInterface(REFIID	riid, void** ppv)
{
    if(ppv == NULL)
        return E_INVALIDARG;

    // Do we support this interface?
    if (riid == IID_IUnknown ||
        riid == IID_IClassFactory)
    {
		*ppv = this;
	}
    else
	{
		*ppv = NULL;
        return E_NOINTERFACE;
	}

    if ((IUnknown*)*ppv)
	{
		((IUnknown*)*ppv)->AddRef();
	} 
    return S_OK;
}


STDMETHODIMP MyClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	HRESULT hr = S_OK;
	MyDataSource* pMyDataSource = NULL;

    if(ppv == NULL)
        return E_INVALIDARG;

    // In case we fail, we need to zero output arguments
    *ppv = NULL;

    // If we're given a controlling IUnknown, it must ask for IUnknown.
    // Otherwise, the caller will end up getting a pointer to their pUnkOuter
    // instead of to the new object we create and will have no way of getting
    // back to this new object, so they won't be able to free it.  Bad!
    if (pUnkOuter && riid != IID_IUnknown)
        return E_NOINTERFACE;

    //Create a MyDataSource object
   if(!(pMyDataSource = new MyDataSource()))
    {
		hr = E_OUTOFMEMORY;
		goto CLEANUP;
	}

    // Initialize it
	pMyDataSource->AddRef();
	if(FAILED(hr = pMyDataSource->Init()))
		goto CLEANUP;
		
	//Obtain correct riid
	hr = pMyDataSource->QueryInterface(riid, ppv);

CLEANUP:
	if((pMyDataSource)) { (pMyDataSource)->Release(); (pMyDataSource) = NULL; }
	return hr;
}


STDMETHODIMP MyClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement( &g_cLock );
    else
        InterlockedDecrement( &g_cLock );

    return NOERROR;
}



////////////////////////////////////////////////////////
// DllMain
//
////////////////////////////////////////////////////////
BOOL WINAPI DllMain
    (
    HANDLE   hInstDLL,   //@parm IN | Application Instance Handle
    DWORD       fdwReason,  //@parm IN | Indicated Process or Thread activity
    LPVOID      lpvReserved //@parm IN | Reserved...
    )
{
    BOOL	fRetVal = FALSE;

    switch(fdwReason)
    {
		case DLL_PROCESS_ATTACH:

			// Assume successfully initialized
			fRetVal = TRUE;

			// Do one-time initialization when first process attaches
			if (!g_cAttachedProcesses)
			{
				g_hInstance = (HINSTANCE) hInstDLL;
			}

			// Do per-process initialization here...
        
			// Remember that another process successfully attached
			g_cAttachedProcesses++;
			break;

		case DLL_PROCESS_DETACH:
			// Clean up when the last process is going away
			if (g_cAttachedProcesses == 1)
			{
			}

			// Do per-process clean up here...

			// Remember that a process has detached
			g_cAttachedProcesses--;
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
    }

    return fRetVal;
}



////////////////////////////////////////////////////////
// DllGetClassObject
//
////////////////////////////////////////////////////////
HRESULT CALLBACK DllGetClassObject
    (
    REFCLSID    rclsid, //@parm IN | CLSID of the object class to be loaded
    REFIID      riid,   //@parm IN | Interface on object to be instantiated
    LPVOID *    ppvObj  //@parm OUT | Pointer to interface that was instantiated
    )
{
    MyClassFactory * pClassFactory;
	HRESULT         hr;

    // Check for valid ppvObj pointer
    if (!ppvObj)
        return E_INVALIDARG;

    // In case we fail, we need to zero output arguments
    *ppvObj = NULL;

    // We only service CLSID_SampleOSProvider
    if (rclsid != CLSID_FileOSP)
        return CLASS_E_CLASSNOTAVAILABLE;

    // We only support the IUnknown and IClassFactory interfaces
    if (riid != IID_IUnknown &&
        riid != IID_IClassFactory)
        return E_NOINTERFACE;

    // Create our ClassFactory object
    if(!(pClassFactory = new MyClassFactory()))
        return E_OUTOFMEMORY;

    // Get the desired interface on this object
    hr = pClassFactory->QueryInterface( riid, ppvObj );
    if(FAILED(hr))
        delete pClassFactory;

	return hr;
}


////////////////////////////////////////////////////////
// DllCanUnloadNow
//
////////////////////////////////////////////////////////
STDAPI DllCanUnloadNow( void )
{
    if (!g_cObj && !g_cLock)
        return S_OK;
    else
        return S_FALSE;
}



////////////////////////////////////////////////////////
// DllUnregisterServer
//
////////////////////////////////////////////////////////
STDAPI DllUnregisterServer()
{
    int     iNumErrors = 0;

    // Delete all table entries.  Loop in reverse order, since they
    // are entered in a basic-to-complex order.
    // We cannot delete a key that has subkeys.
    // Ignore errors.
    for (int i=NUMELEM(rgRegInfo)-1; i>=0; i--)
    {
		if(FAILED(DelRegEntry(&rgRegInfo[i])))
			iNumErrors++;
	}

    return iNumErrors ? E_FAIL : S_OK;
}


////////////////////////////////////////////////////////
// DllRegisterServer
//
////////////////////////////////////////////////////////
STDAPI DllRegisterServer()
{
	HRESULT		hr;
    WCHAR		szBuffer[MAX_NAME_LEN];
	WCHAR		szFullFileName[MAX_PATH+1];

    if (0 == GetModuleFileName( g_hInstance, szFullFileName, MAX_PATH+1))
        return E_FAIL;

    // Make a clean start
    DllUnregisterServer();

    // Loop through s_rgRegInfo, and put everything in it.
    // Every entry is based on HKEY_CLASSES_ROOT.
    for (int i=0; i<NUMELEM(rgRegInfo); i++)
    {
        // Fill in any "%s" arguments with the name of this DLL.
        wsprintf(szBuffer, rgRegInfo[i].szValue, szFullFileName );
		rgRegInfo[i].szValue = szBuffer;

		//Set the Registry Entry for this Key
        if(FAILED(hr = SetRegEntry(&rgRegInfo[i])))
			goto CLEANUP;
	}

CLEANUP:
    return hr;
}




