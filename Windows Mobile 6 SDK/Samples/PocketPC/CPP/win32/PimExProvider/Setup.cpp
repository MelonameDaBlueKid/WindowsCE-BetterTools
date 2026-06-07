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


#include "PimExProvider.h"


////////////////////////////////////////////////////////////////////////////
// Function:
//      FindAvailableId
//
// Purpose:
//      Looks for the next available PIM source id (based on a list in the
//      registry) and creates an empty key for that id.
//
// Parameters:
//      OUT     pdwId           Filled in with id to use
//      OUT     phkeySource     Filled in with the HKEY for the source
//
// Returns values:
//      S_OK                        Success
//      E_PIMSRC_NO_AVAILABLE_ID    The maximum number of PIM sources are
//                                      already registered on this device.
//      ...
//
HRESULT FindAvailableId(DWORD *pdwId, HKEY *phkeySource)
{
    DWORD   i;
    DWORD   dwErr;
    DWORD   dwDisposition;
    DWORD   dwIdCandidate       = 1;
    HRESULT hr                  = S_OK;
    HKEY    hkeySourcesRoot     = NULL;
    HKEY    hkeySource          = NULL;

    CBR(NULL != pdwId);
    CBR(NULL != phkeySource);

    // Attempt to open the main key that lists PIM sources
    dwErr = RegCreateKeyExW(PIMSRC_REGHKEY, PIMSRC_REGPATH_ROOT, 0, NULL, 0, 0, NULL, &hkeySourcesRoot, &dwDisposition);
    CBR(ERROR_SUCCESS == dwErr);

    
    // Loop through the possible ids...
    for (i = 0; i < 32; i++)
    {
        // The id is a DWORD, so the largest value is 2^32 - 1
        WCHAR wszIdCandidate[ARRAYSIZE(L"4294967295")];

        // A valid PIM source id has exactly one bit set in it, so look for 1 and
        // then try 2, 4, 8...
        dwIdCandidate = 1 << i;

        // Convert the DWORD into a string
        hr = StringCchPrintfW(wszIdCandidate, ARRAYSIZE(wszIdCandidate), L"%u", dwIdCandidate);
        CHR(hr);
        
        // Try to open or create the source key
        dwErr = RegCreateKeyExW(hkeySourcesRoot, wszIdCandidate, 0, NULL, 0, 0, NULL, &hkeySource, &dwDisposition);
        CBR(ERROR_SUCCESS == dwErr);

        // If we just created the key, we've found a usable id
        if (REG_CREATED_NEW_KEY == dwDisposition)
        {
            break;
        }

        // Otherwise, we need to close this key so we can try another one
        RegCloseKey(hkeySource);
        hkeySource = NULL;
    }

    // Did we run out of space?
    if (32 == i)
    {
        hr = E_PIMSRC_NO_AVAILABLE_ID;
        goto Error;
    }

    // Return our findings
    *pdwId = dwIdCandidate;
    *phkeySource = hkeySource;
    hkeySource = NULL;
    
Error:
    RegCloseKey(hkeySource);
    RegCloseKey(hkeySourcesRoot);

    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      RemovePIMSource
//
// Purpose:
//      Removes a PIM Source's registration information.
//
// Parameters:
//      IN      dwId            Id of the PIM source to remove
//
// Returns values:
//      S_OK                    Success
//      ...
//
HRESULT RemovePIMSource(DWORD dwId)
{
    DWORD   dwErr;
    HRESULT hr                      = S_OK;
    HKEY    hkeySourcesRoot         = NULL;
    WCHAR   szBuffer[MAX_BUFFER];
    BOOL    fRet                    = TRUE;
    
    // Attempt to open the main key that lists PIM sources
    dwErr = RegOpenKeyExW(PIMSRC_REGHKEY, PIMSRC_REGPATH_ROOT, 0, 0, &hkeySourcesRoot);
    CBR(ERROR_SUCCESS == dwErr);
    
    // Convert the DWORD into a string
    hr = StringCchPrintfW(szBuffer, ARRAYSIZE(szBuffer), L"%u", dwId);
    CHR(hr);
    
    // Delete this source provider reg key
    dwErr = RegDeleteKey(hkeySourcesRoot, szBuffer);
    if (ERROR_SUCCESS != dwErr)
    {
        fRet = FALSE;
    }

    // Prepare the path for the CLSID reg key
    hr = StringCchPrintf(szBuffer, ARRAYSIZE(szBuffer), 
        L"CLSID\\%s", g_szCLSID_SampleProvider);
    CHR(hr);

    // Delete that reg path
    hr = RegDeleteKey(HKEY_CLASSES_ROOT, szBuffer);
    CHR(hr);
    
    
Error:    
    RegCloseKey(hkeySourcesRoot);

    if (FAILED(hr) || !fRet)
    {
        hr = E_FAIL;
    }

    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      SetCustomCalendarColor
//
// Purpose:
//      Creates the reg keys and set their value for custom calendar color.
//
// Parameters:
//      IN      dwId            Id of the PIM source to remove
//      IN      dwCustomColor   RGB value for the custom calendar background color.
//
// Returns values:
//      S_OK                    Success
//      ...
//
HRESULT SetCustomCalendarColor(DWORD dwId, DWORD dwCustomColor)
{
    DWORD   dwErr;
    DWORD   dwTemp;
    BOOL    fKeyCreated     = FALSE;
    HRESULT hr              = E_FAIL;
    HKEY    hkeySource      = NULL;
    WCHAR   szColorKey[MAX_BUFFER];
    
    // Prepare the reg key for the Color customization
    hr = StringCchPrintfW(szColorKey, ARRAYSIZE(szColorKey), L"%s\\%u\\%s", 
        PIMSRC_REGPATH_ROOT, dwId, PIMSRC_REGPATH_COLORS);
    CHR(hr);

    // Create a key for the Color
    dwErr = RegCreateKeyExW(PIMSRC_REGHKEY, szColorKey, 0, NULL, 0, 0, NULL, &hkeySource, &dwTemp);
    CBR(ERROR_SUCCESS == dwErr);

    // Set the color value 
    hr = StringCchPrintfW(szColorKey, ARRAYSIZE(szColorKey), L"%u", 
        PIMSRC_COLOR_APPOINTMENTS_BACKGROUND);
    CHR(hr);
    
    // Set the COLORREF value
    hr = RegistrySetDWORD(hkeySource, NULL, szColorKey, dwCustomColor);
    CHR(hr);

    // NOTE: You could also call this function when outside the registration code
    // but would need to do a PostMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 0);
    // so the setting take effect.  Since we only call this during registration
    // and the poutlook.exe process needs to be dead when doing that, we don't need
    // to call it.


Error:
    RegCloseKey(hkeySource);    

    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      RegisterPIMSource
//
// Purpose:
//      Register ourself as a PIM source. 
//
// Returns values:
//      S_OK                        Success
//      E_PIMSRC_NO_AVAILABLE_ID    The maximum number of PIM sources are
//                                      already registered on this device.
//      ...
//
HRESULT RegisterPIMSource()
{
    bool    fKeyCreated = false;
    DWORD   dwId;
    DWORD   dwErr;
    DWORD   dwTemp;
    HRESULT hr          = S_OK;
    HKEY    hkeySource  = NULL;
    HKEY    hkeyUs      = NULL;
    WCHAR   szBuffer[MAX_BUFFER];
    HMODULE hModule     = NULL;
    
    // Look for an available PIM source id
    hr = FindAvailableId(&dwId, &hkeySource);
    CHR(hr);

    // If we've got here, we've created a key under the PIM sources root
    fKeyCreated = TRUE;

    // Record the type of PIM data that this soucr provider will manage: 
    // i.e.: Contact & Appointments
    hr = RegistrySetDWORD(hkeySource, NULL, PIMSRC_REGVALUE_TYPE, 
        PIM_CUSTOMIZED_TYPES );
    CHR(hr);    

    // Set the Customizations for the source provider dll.
    // In this sample provider, we're doing all the customizations.
    hr = RegistrySetDWORD(hkeySource, NULL, PIMSRC_REGVALUE_CUSTOMIZATIONS, 
        PIM_CUSTOMIZATIONS);
    CHR(hr);

    // Set the CLSID value for the source provider dll
    hr = RegistrySetString(hkeySource, NULL, PIMSRC_REGVALUE_CLSID, g_szCLSID_SampleProvider);
    CHR(hr);    

    // Set the custom calendar color.  
    hr = SetCustomCalendarColor(dwId, (DWORD) g_crCalendarBackground);
    CHR(hr);
    

    // Record our PIM source id so that we can retrieve it during uninstall.
    dwErr = RegCreateKeyExW(PIMSRC_REGHKEY, g_wszOurKey, 0, NULL, 0, 0, NULL, &hkeyUs, &dwTemp);
    CBR(ERROR_SUCCESS == dwErr);

    hr = RegistrySetDWORD(hkeyUs, NULL, g_wszOurValueName, dwId);
    CHR(hr);


    // Prepare the path for the CLSID reg key
    hr = StringCchPrintf(szBuffer, ARRAYSIZE(szBuffer), 
        L"CLSID\\%s\\InprocServer32", g_szCLSID_SampleProvider);
    CHR(hr);
    
    // Create the CLSID reg key
    dwErr = RegCreateKeyExW(HKEY_CLASSES_ROOT, szBuffer, 0, NULL, 0, 0, NULL, &hkeyUs, &dwTemp);
    CBR(ERROR_SUCCESS == dwErr);

    // Get the dll handle
    hModule = GetModuleHandle(g_szDllName);
    CBR(NULL != hModule);
   
    // Get the full path to this dll
    CBR(0 != GetModuleFileName(hModule, szBuffer, ARRAYSIZE(szBuffer)));

    // Null terminate the sting for safety.
    szBuffer[ARRAYSIZE(szBuffer)-1] = NULL;
    
    // Set the dll name in the registry
    hr = RegistrySetString(hkeyUs, NULL, L"", szBuffer);
    CHR(hr);    
    
Error:
    RegCloseKey(hkeyUs);
    RegCloseKey(hkeySource);

    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      LookupSourceId
//
// Purpose:
//      Returns the source id for this source provider.  Check the cusom reg key
//      we created when registering the new source provider.
//
// Parameters:
//      OUT     pdwSourceId     Filled in with source id that registered.
//
// Returns values:
//      S_OK                        Success
//      ...
//
HRESULT LookupSourceId(DWORD *pdwSourceId)
{
    HRESULT hr = E_FAIL;

    CBR(NULL != pdwSourceId);
    
    // Look up our id
    hr = RegistryGetDWORD(PIMSRC_REGHKEY, g_wszOurKey, g_wszOurValueName, pdwSourceId);
    CHR(hr);
    
Error:
    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      UnregisterPIMSource
//
// Purpose:
//      Remove our registration information from the registry.
//
// Note:
//      A complete PIM source implementation should remove PIM items 
//      belonging to it when it is uninstalled.
//
// Returns values:
//      S_OK                    Success
//      ...
//
HRESULT UnregisterPIMSource()
{
    HRESULT hr = S_OK;
    DWORD dwId;
    
    // Lookup the current source id
    hr = LookupSourceId(&dwId);
    CHR(hr);

    // Remove our PIM source entry
    hr = RemovePIMSource(dwId);
    CHR(hr);
    
    // Remove the reg key we used to track the source id (failure isn't fatal)
    hr = RegDeleteKey(PIMSRC_REGHKEY, g_wszOurKey);    
    CHR(hr);

Error:
    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      UpdateAllItemsSourceId
//
// Purpose:
//      Updates all the items in the items collection passed in with the specified 
//      source id.
//
// Parameters:
//      IN      dwSourceId      Source Id to update it with 
//      IN      pCol            Collecitons of items to update source id for.
//
// Returns values:
//      S_OK                        Success
//      ...
//
HRESULT UpdateAllItemsSourceId(DWORD dwSourceId, IPOutlookItemCollection *pCol)
{

    HRESULT         hr              = E_FAIL;
    IItem           *pItem          = NULL;
    IDispatch       *pDisp          = NULL;
    int             cItems          = 0;
    CEPROPVAL       PropVal         = {0};
    
    CBR(NULL != pCol);
    
    // Find out how many items there are in the store.
    hr = pCol->get_Count(&cItems); 
    CHR(hr);

    // If no items exits of this type, ignore doing anything.
    if(0 >= cItems)
    {
        hr = S_FALSE;
        goto Error;
    }

    // Set the value of the source ID to set for each item.
    PropVal.propid      = PIMPR_SOURCE_ID;
    PropVal.val.ulVal   = dwSourceId;
   
    // Start the index from 1 since the index is 1-base, bu the count 0-based.
    for (int i = 1; i < (cItems+1); i++)
    {
        // Get the i-th item
        hr = pCol->Item(i, (IDispatch **)&pDisp);
        CHR(hr);
        CBR(NULL != pDisp);

        // Get the IItem so we can operate on the item generically.
        hr = pDisp->QueryInterface(IID_IItem, (LPVOID*)&pItem);
        CHR(hr);
        CBR(NULL != pItem);
        
        // Set the Source Id.
        hr = pItem->SetProps(0, 1, &PropVal);
        CHR(hr);

        // Save the changes made to the item.
        hr = pItem->Save();
        CHR(hr);

        RELEASE_OBJ(pItem);
        RELEASE_OBJ(pDisp);
    }
        
Error:
    // Lets release these incase we hit an error in the for loop.
    RELEASE_OBJ(pItem);
    RELEASE_OBJ(pDisp);    
    
    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      ItemSetup
//
// Purpose:
//      Does the necessary setup for the contacts and appointments to associate 
//      them with a source-id.  Ideally this should only be done with contact 
//      that you want associated with that source id.  For this sample, however, 
//      we'll just associate all items this source id.
//
// Parameters:
//      IN      polApp      POOM app obj
//      IN      olItemType  Outlook Item type to update source-id for.
//      IN      fInstall    TRUE to install, FALSE to uninstall.
//
// Returns values:
//      S_OK                        Success
//      ...
//
HRESULT ItemSetup(IPOutlookApp2 *polApp, int olItemType, BOOL fInstall)
{
    HRESULT         hr              = E_FAIL;
    IFolder         *pFolder        = NULL;
    IPOutlookItemCollection *pCol   = NULL;
    DWORD           dwSourceId      = 0;
    int             olFolder;

        
    CBR(NULL != polApp);
    
    // In the uninstall state we want to set the source id to 0
    // (which is the current default).
    if (fInstall) 
    {
        // Lets get the current providers source id.
        hr = LookupSourceId(&dwSourceId);
        CHR(hr);
    }        

    // Select the folder type
    switch (olItemType)
    {
        case olContactItem:
            olFolder = olFolderContacts;
            break;
            
        case olAppointmentItem:
            olFolder = olFolderCalendar;
            break;

        default:
            CHR(E_INVALIDARG);
    }

    // Get the default folder for the specified item type.
    hr = polApp->GetDefaultFolder(olFolder, &pFolder);
    CHR(hr);
    CBR(NULL != pFolder);
    
    // Get the outlook item collection which contains all the items.
    hr = pFolder->get_Items((IPOutlookItemCollection **)&pCol);
    CHR(hr);
    CBR(NULL != pCol);

    // Update all the items with the specified source id.
    hr = UpdateAllItemsSourceId(dwSourceId, pCol);

Error:
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(pCol);
    
    return hr;
}


