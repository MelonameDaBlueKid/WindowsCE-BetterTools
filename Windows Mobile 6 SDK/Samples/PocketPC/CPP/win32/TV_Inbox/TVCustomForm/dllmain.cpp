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

#include "stdafx.h"
#include "RuleClient.h"
#include "tvconsts.h"
#include "resource.h"
#include <cemapi.h>

// {BEB30194-3367-4009-82F7-118CCE923125}
EXTERN_C const GUID  CLSID_TV_INBOX = 
                     { 0xbeb30194, 0x3367, 0x4009, { 0x82, 0xf7, 0x11, 0x8c, 0xce, 0x92, 0x31, 0x25 } };

int g_cServerLocks = 0;
extern "C" HINSTANCE g_hInst = NULL;

#define IMAGENAME TEXT("TV_INBOX.DLL")

void RegisterSMSClient()
{
    HKEY hKey;
    DWORD dwDisp;
    long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, L"CLSID\\{BEB30194-3367-4009-82F7-118CCE923125}\\InProcServer32", 0, NULL, 0, 0, NULL, &hKey, &dwDisp);

    if (lResult == ERROR_SUCCESS)
    {
        HMODULE hModule = GetModuleHandle(IMAGENAME);
        if (hModule)
        {
            TCHAR szName[MAX_PATH];

            if (GetModuleFileName(hModule, szName, ARRAYSIZE(szName)))
            {
                RegSetValueEx(hKey, NULL, 0, REG_SZ, (const BYTE *)szName, _tcslen(szName)*sizeof(TCHAR));

                TCHAR szModel[] = L"Free";
                RegSetValueEx(hKey, L"ThreadingModel", 0, REG_SZ, (const BYTE *)szModel, _tcslen(szModel)*sizeof(TCHAR));

                RegCloseKey(hKey);
            }
        }
    }

    lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Inbox\\Svc\\SMS\\Rules", 0, NULL, 0, 0, NULL, &hKey, &dwDisp);

    if (lResult == ERROR_SUCCESS)
    {
        DWORD dwValue = 1;
        RegSetValueEx(hKey, L"{BEB30194-3367-4009-82F7-118CCE923125}", 0, REG_DWORD, (const BYTE *)&dwValue, sizeof(DWORD));

        RegCloseKey(hKey);
    }

    lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Inbox\\Svc\\SMS\\MsgClasses", 0, NULL, 0, 0, NULL, &hKey, &dwDisp);

    if (lResult == ERROR_SUCCESS)
    {
        DWORD dwValue = 1;
        RegSetValueEx(hKey, kszTVMsgClass, 0, REG_DWORD, (const BYTE *)&dwValue, sizeof(DWORD));

        RegCloseKey(hKey);
    }
}

void RegisterReadForm()
{
    HKEY hKey;
    DWORD dwDisp;
    long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Inbox\\MsgTypes\\IPM\\SMStext\\TV", 0, NULL, 0, 0, NULL, &hKey, &dwDisp);

    if (lResult == ERROR_SUCCESS)
    {
        HMODULE hModule = GetModuleHandle(IMAGENAME);
        if (hModule)
        {
            TCHAR szName[MAX_PATH];

            if (GetModuleFileName(hModule, szName, ARRAYSIZE(szName)))
            {
                RegSetValueEx(hKey, L"DLL", 0, REG_SZ, (const BYTE *)szName, _tcslen(szName)*sizeof(TCHAR));
                RegCloseKey(hKey);
            }
        }
    }
}

void RegisterComposeForm()
{
    HKEY hKey;
    DWORD dwDisp;
    long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Inbox\\MsgTypes\\IPM\\SMStext\\TV", 0, NULL, 0, 0, NULL, &hKey, &dwDisp);

    if (lResult == ERROR_SUCCESS)
    {
        HMODULE hModule = GetModuleHandle(IMAGENAME);
        if (hModule)
        {
            TCHAR szName[MAX_PATH];

            if (GetModuleFileName(hModule, szName, ARRAYSIZE(szName)))
            {
                RegSetValueEx(hKey, L"DLL", 0, REG_SZ, (const BYTE *)szName, _tcslen(szName)*sizeof(TCHAR));
                RegCloseKey(hKey);
            }
        }
    }
}

void RegisterListIcons()
{
    HKEY hKey;
    DWORD dwDisp;
    long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Inbox\\MsgTypes\\IPM\\SMStext\\TV", 0, NULL, 0, 0, NULL, &hKey, &dwDisp);

    INBOXGLYPHINFO gInfo;

    gInfo.cbSize = sizeof(INBOXGLYPHINFO);
    gInfo.ResIdColor = IDB_BITMAP_GLYPHS;
    gInfo.ResIdMono = IDB_BITMAP_GLYPHS;
    gInfo.iRead = 0;
    gInfo.iUnRead = 1;
    gInfo.iRepliedTo = 0;
    gInfo.iForwarded = 0;
    gInfo.iAttachment = 0;

    if (lResult == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, L"GlyphInfo", 0, REG_BINARY, (const BYTE *)&gInfo, sizeof(INBOXGLYPHINFO));

        RegCloseKey(hKey);
    }
}


STDAPI DllRegisterServer()
{
    RegisterSMSClient();
    RegisterReadForm();
    RegisterComposeForm();
    RegisterListIcons();

    return 0;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        g_hInst = (HINSTANCE)hModule;
    }

    return TRUE;
}

STDAPI DllGetClassObject(const CLSID& clsid, REFIID iid, LPVOID *ppv)
{
    HRESULT hr;
    
    // We only understand my rule's class
    if (clsid != CLSID_TV_INBOX)
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    CFactory *pFactory = new CFactory;
    if (!pFactory)
    {
        return E_OUTOFMEMORY;
    }

    // Get the requested interface
    hr = pFactory->QueryInterface(iid, ppv);
    pFactory->Release();
    
    return hr;
}

STDAPI DllCanUnloadNow()
{
    if (!g_cServerLocks)
    {
        return S_OK;
    }
    else
    {
        return S_FALSE;
    }
}

//
// Class Factory -- in charge of creating a CRuleClient object
//

CFactory::CFactory()
{
    m_cRef = 1;
}

CFactory::~CFactory()
{
}

STDMETHODIMP CFactory::QueryInterface(const IID& iid, LPVOID *ppv)
{
    HRESULT hr = E_NOINTERFACE;

    if (!ppv)
    {
        return E_INVALIDARG;
    }
    
    if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
    {
        *ppv = (IClassFactory *) this;
        ((LPUNKNOWN) *ppv)->AddRef();
        hr = S_OK;
    }
    else
    {
        *ppv = NULL;
    }
    
    return hr;
}

ULONG CFactory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

ULONG CFactory::Release()
{
    int nLocal = InterlockedDecrement(&m_cRef);

    if (!nLocal) 
    {
        delete this; 
    }

    return nLocal; 
}

STDMETHODIMP CFactory::CreateInstance(LPUNKNOWN pUnknownOuter, REFIID iid, LPVOID *ppv)
{
    CRuleClient *pClient = NULL;
    HRESULT hr;

    // No aggregation
    if (pUnknownOuter)
    {
        hr = CLASS_E_NOAGGREGATION;
        goto Error;

    }

    // You heard 'em, create a component
    pClient = new CRuleClient();
    if (!pClient)
    {
        hr = E_OUTOFMEMORY;
        goto Error;
    }
    
    // Get the requested interface
    hr = pClient->QueryInterface(iid, ppv);

Error:
    // Release the unknown pointer
    if (pClient) 
    {
        pClient->Release();
    }
    
    return hr;
}

STDMETHODIMP CFactory::LockServer(BOOL bLock)
{
    if (bLock)
    {
        g_cServerLocks++;
    }
    else
    {
        g_cServerLocks--;
    }

    return S_OK;
}


