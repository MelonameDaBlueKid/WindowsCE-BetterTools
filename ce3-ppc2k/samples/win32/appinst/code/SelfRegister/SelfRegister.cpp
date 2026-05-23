
// Sample self-registering DLL

#include <windows.h>
#include <tchar.h>
#include <olectl.h>

const TCHAR szTITLE[] = TEXT("Self_Registering DLL");
const TCHAR szREG[]   = TEXT("DllRegisterServer");
const TCHAR szUNREG[] = TEXT("DllUnregisterServer");

BOOL WINAPI DllMain(HANDLE hMod, DWORD dwReason, LPVOID lpvReserved)
{
  return TRUE;
}

STDAPI DllRegisterServer()
{
  if (IDOK == MessageBox(GetForegroundWindow(), szREG, szTITLE, MB_OKCANCEL))
    return S_OK;
  else
    return SELFREG_E_TYPELIB;
}

STDAPI DllUnregisterServer()
{
  if (IDOK == MessageBox(GetForegroundWindow(), szUNREG, szTITLE, MB_OKCANCEL))
    return S_OK;
  else
    return SELFREG_E_TYPELIB;
}
