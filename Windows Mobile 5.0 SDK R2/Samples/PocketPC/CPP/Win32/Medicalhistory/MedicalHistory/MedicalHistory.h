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
#include "IDs.h"

extern HINSTANCE g_hInst;

#define MAX_CCH_MEDICAL_HISTORY_FIELD  256

typedef struct _MedicalHistoryStruct
{
    WCHAR szHealthInsuranceProvider[MAX_CCH_MEDICAL_HISTORY_FIELD];
    WCHAR szBloodGroup[MAX_CCH_MEDICAL_HISTORY_FIELD];
    WCHAR szBloodPressure[MAX_CCH_MEDICAL_HISTORY_FIELD];
    WCHAR szAllergies[MAX_CCH_MEDICAL_HISTORY_FIELD];
} MedicalHistoryStruct;

LRESULT CALLBACK MedicalHistoryDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT ShowMedicalHistory(CEOID oidPatient);
