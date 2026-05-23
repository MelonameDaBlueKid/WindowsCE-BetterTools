//
// Sample self-registering DLL
//

#include <windows.h>
#include <tchar.h>
#include <olectl.h>

const TCHAR szTITLE[]   = TEXT("Self-Registering Sample DLL");
const TCHAR szREG[]     = TEXT("DllRegisterServer");
const TCHAR szUNREG[]   = TEXT("DllUnregisterServer");

const TCHAR szWNDCLASS_INSTALLER[]   = TEXT("WCELOAD");
const TCHAR szWNDCLASS_UNINSTALLER[] = TEXT("CPL_Remove Programs");

BOOL WINAPI
DllMain( HANDLE hMod, DWORD dwReason, LPVOID lpvReserved )
{
    return TRUE;
}

STDAPI
DllRegisterServer()
{
    HWND    hwnd = FindWindow(szWNDCLASS_INSTALLER, NULL);
    if ( IDOK == MessageBox( hwnd, szREG, szTITLE, MB_OKCANCEL ) )
        return S_OK;
    else
        return SELFREG_E_TYPELIB;
}

STDAPI
DllUnregisterServer()
{
    HWND    hwnd = FindWindow(szWNDCLASS_UNINSTALLER, NULL);
    if ( IDOK == MessageBox( hwnd, szUNREG, szTITLE, MB_OKCANCEL ) )
        return S_OK;
    else
        return SELFREG_E_TYPELIB;
}
