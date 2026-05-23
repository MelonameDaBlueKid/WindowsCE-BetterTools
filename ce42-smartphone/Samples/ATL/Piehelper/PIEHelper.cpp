// IEHelper.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f IEHelperps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "PIEHelper.h"

#include "PIEHelper_i.c"
#include "PIEHlprObj.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_IEHlprObj, CIEHlprObj)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DllMain
/////////////////////////////////////////////////////////////////////////////
extern "C" BOOL WINAPI DllMain
(
    HANDLE  hInstance,
    DWORD   dwReason,
    void *  /*lpReserved*/
)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, (HINSTANCE)hInstance);
		DisableThreadLibraryCalls((HINSTANCE)hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();

	return TRUE;
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


