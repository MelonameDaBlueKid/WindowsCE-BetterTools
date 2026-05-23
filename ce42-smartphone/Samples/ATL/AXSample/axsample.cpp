// AXSample.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f AXSampleps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "AXSample.h"

#include "AXSample_i.c"
#include "AXSampleCtl.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_AXSampleCtl, CAXSampleCtl)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DllMain
/////////////////////////////////////////////////////////////////////////////
extern "C" BOOL WINAPI DllMain
(
    HANDLE  hInstance,
    DWORD   dwReason,
    VOID *  /*lpReserved*/
)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, (HINSTANCE)hInstance);
#ifndef UNDER_CE
		DisableThreadLibraryCalls((HINSTANCE)hInstance);
#endif
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();

	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// DllCanUnloadNow
/////////////////////////////////////////////////////////////////////////////
STDAPI DllCanUnloadNow
(
)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// DllGetClassObject
/////////////////////////////////////////////////////////////////////////////
STDAPI DllGetClassObject
(
    REFCLSID    rclsid,
    REFIID      riid,
    void **     ppv
)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer
/////////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterServer
(
)
{
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer
/////////////////////////////////////////////////////////////////////////////
STDAPI DllUnregisterServer
(
)
{
	_Module.UnregisterServer();
	return S_OK;
}


