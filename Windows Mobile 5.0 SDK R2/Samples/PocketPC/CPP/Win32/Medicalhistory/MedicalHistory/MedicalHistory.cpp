//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#include "stdafx.h"
#include "pimstore.h"

// **************************************************************************
// Function Name: CopyStringProperty
// 
// Purpose: Copies a string property from a CEPROPVAL if the 
//          CEDB_PROPNONFOUND flag is not set.
//
// Arguments:
//    OUT LPWSTR    pszDest - Pointer to copy destination string
//    IN  WORD      cchDest - Size of pszDest buffer
//    IN  CEPROPVAL pValSrc - Property to get the string from
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT CopyStringProperty(LPWSTR pszDest, WORD cchDest, CEPROPVAL *pValSrc)
{
    HRESULT hr;

    CBR(pszDest != NULL);
    CBR(pValSrc != NULL);

    if (!(pValSrc->wFlags & CEDB_PROPNOTFOUND))
    {
        CHR(StringCchCopy(pszDest, cchDest, pValSrc->val.lpwstr));
    }
Error:
    return hr;
}

// **************************************************************************
// Function Name: ShowMedicalHistory
// 
// Purpose: Shows a dialog with the given patient's medical history, 
//          updates POOM with changes
//
// Arguments:
//    IN CEOID oidPatient - oid of the patient whose data should be shown
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT ShowMedicalHistory(CEOID oidPatient)
{
    HRESULT hr = S_OK;
    IPOutlookApp2 *polApp = NULL;
    IItem *pItem = NULL;
    MedicalHistoryStruct mh = {0};
    HANDLE heap = GetProcessHeap();

    static const WCHAR * rgszPropNames[] = 
    { 
        L"HealthInsuranceProvider", 
        L"BloodGroup",
        L"BloodPressure",
        L"Allergies"
    };
    CEPROPID rgPropIDs[ARRAYSIZE(rgszPropNames)] = {0};
    CEPROPVAL *pVals = NULL;

    hr = CoCreateInstance(CLSID_Application,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          IID_IPOutlookApp2,
                          (LPVOID *) &polApp);
    CHR(hr);
    
    // Logon to the Outlook App interface
    hr = polApp->Logon(NULL);
    CHR(hr);
    
    // This gets the id's for the named props in rgszPropNames.  If these are new 
    // properties, they will be assigned new ids and S_OK will be returned, if they 
    // already exist, their existing ids will be passed back the function will 
    // return S_FALSE
    hr = polApp->GetIDsFromNames(ARRAYSIZE(rgszPropNames), rgszPropNames,
            PIM_CREATE | CEVT_LPWSTR, rgPropIDs);
    CHR(hr);

    // Get the information for this patient
    hr = polApp->GetItemFromOidEx(oidPatient, 0, &pItem);
    CHR(hr);

    DWORD cbBuffer = 0;
    // Get the props by passing in the id array returned from GetIDsFromNames
    hr = pItem->GetProps(rgPropIDs, CEDB_ALLOWREALLOC, ARRAYSIZE(rgPropIDs), &pVals, &cbBuffer, heap);
    CHR(hr);

    // Copy the data from POOM into the MedicalHistory structure so we can pass it to the dialog and 
    // fill in the fields with the current data
    CHR(CopyStringProperty(mh.szHealthInsuranceProvider, ARRAYSIZE(mh.szHealthInsuranceProvider), &pVals[0]));
    CHR(CopyStringProperty(mh.szBloodGroup, ARRAYSIZE(mh.szBloodGroup), &pVals[1]));
    CHR(CopyStringProperty(mh.szBloodPressure, ARRAYSIZE(mh.szBloodPressure), &pVals[2]));
    CHR(CopyStringProperty(mh.szAllergies, ARRAYSIZE(mh.szAllergies), &pVals[3]));

    // Show medical history
    DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_MEDICALHISTORY), NULL, 
        (DLGPROC) MedicalHistoryDlgProc, (LPARAM) &mh);


    // Set the pVals array to contain the data the user entered into the dialog.
    // Clear the flags that were passed to us from GetProps
    pVals[0].wFlags = 0;
    pVals[0].val.lpwstr = mh.szHealthInsuranceProvider;

    pVals[1].wFlags = 0;
    pVals[1].val.lpwstr = mh.szBloodGroup;

    pVals[2].wFlags = 0;
    pVals[2].val.lpwstr = mh.szBloodPressure;

    pVals[3].wFlags = 0;
    pVals[3].val.lpwstr = mh.szAllergies;

    // Sets the properties in POOM
    hr = pItem->SetProps(0, ARRAYSIZE(rgPropIDs), pVals);
    CHR(hr);

    // Save out item
    hr = pItem->Save();
    CHR(hr);

Error:
    //Cleanup 
    HeapFree(heap, 0, pVals);

    RELEASE_OBJ(pItem);
    
    polApp->Logoff();

    RELEASE_OBJ(polApp);

    return hr;
}

