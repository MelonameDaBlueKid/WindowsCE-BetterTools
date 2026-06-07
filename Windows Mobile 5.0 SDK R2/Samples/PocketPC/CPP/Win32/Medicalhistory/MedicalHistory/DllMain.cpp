#include "stdafx.h"
#include "ClassFactory.h"
#include "MenuExtHelper.h"

ULONG g_dwDLLRefCount = 0;

#define CLSIDTEXT_TESTEXT           TEXT("746BD738-E5CE-42d8-B1F1-23CD0086022C")
#define REGKEY_EXTENSIONS_CLSID     TEXT("CLSID\\{") CLSIDTEXT_TESTEXT _T("}")

// If you change the name or location of this dll this line will have to change
#define IMAGENAME                   TEXT("\\Program Files\\MedicalHistory\\MedicalHistory.dll")

// NOTE:
// If you are creating new menu extensions based on this code
// you absolutely must create your own CLSIDs!  
// Visual Studio's Guidgen.exe (accesible via "Tools->Create Guid") is an excellent tool for this
// {746BD738-E5CE-42d8-B1F1-23CD0086022C}
DEFINE_GUID(CLSID_MEDICALHISTORY_MENUEXT, 
0x746bd738, 0xe5ce, 0x42d8, 0xb1, 0xf1, 0x23, 0xcd, 0x0, 0x86, 0x2, 0x2c);

// **************************************************************************
// DllGetClassObject  
//
//  This function retrieves the class object from a DLL object handler or object 
//  application. DllGetClassObject is called from within the CoGetClassObject 
//  function when the class context is a DLL.
// 
STDAPI DllGetClassObject
(
    REFCLSID rclsid,
    REFIID riid,
    void** ppObject
)
{
    HRESULT hr = S_OK;
    MedicalHistoryClassFactory *pFactory = NULL;

    if(rclsid == CLSID_MEDICALHISTORY_MENUEXT)
    {
        pFactory = new MedicalHistoryClassFactory;
        CPR(pFactory);

        hr = pFactory->QueryInterface(riid, ppObject);
        CHR(hr);
    }
    else
    {
        CHR(CLASS_E_CLASSNOTAVAILABLE);
    }

Error:
    RELEASE_OBJ(pFactory);

    return(hr);
}

// **************************************************************************
// DllCanUnloadNow
//
//  Returns S_OK if there are no ref counts to this DLL, S_FALSE otherwise
//
STDAPI DllCanUnloadNow()
{
    if(g_dwDLLRefCount)
    {
        return S_FALSE;
    }
    else
    {
        return S_OK;
    }
}

BOOL WINAPI DllMain(HANDLE hinstDll, DWORD dwReason, LPVOID pvReserved)
{
    switch (dwReason) 
    {
        case DLL_PROCESS_ATTACH: 
            g_hInst = (HINSTANCE) hinstDll;
            break;
            
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// **************************************************************************
// DllRegisterServer
//
//  This method is called when RegSvrCE is called.
//  Calls CreateMenuExtensionCLSIDRegKey and CreateMenuExtensionRegKey 
//  to set up the menu extension reg keys
//
STDAPI DllRegisterServer(void)
{
    HRESULT hr;

    hr = CreateMenuExtensionCLSIDRegKey(REGKEY_EXTENSIONS_CLSID, IMAGENAME);
    RETAILMSG(SUCCEEDED(hr), (L"MedicalHistory: Created CLSID reg keys %s", REGKEY_EXTENSIONS_CLSID));
    CHR(hr);

    hr = CreateMenuExtensionRegKey(REGKEY_MENUEXT_CONTACTS_SUMMARYCARD_PPC);
    RETAILMSG(SUCCEEDED(hr), (L"MedicalHistory: Created menu ext reg keys %s", REGKEY_MENUEXT_CONTACTS_SUMMARYCARD_PPC));
    CHR(hr);


Error:
    RETAILMSG(FAILED(hr), (L"Failed the setup. hr = 0x%x", hr));    
    return SUCCEEDED(hr);    
}

// **************************************************************************
// DllUnregisterServer
//
//  This method is called when RegSvrCE /U is called.
//
STDAPI DllUnregisterServer()
{
    HRESULT hr = S_OK;

    // Remove the reg keys created on registration
    CHR(RegDeleteKey(HKEY_LOCAL_MACHINE, REGKEY_EXTENSIONS_CLSID));
    CHR(RegDeleteKey(HKEY_LOCAL_MACHINE, REGKEY_MENUEXT_CONTACTS_SUMMARYCARD_PPC));

Error:
    return hr;    
}