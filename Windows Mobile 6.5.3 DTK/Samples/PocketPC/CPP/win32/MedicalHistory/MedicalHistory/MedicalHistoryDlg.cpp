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

#include "stdafx.h"


// **************************************************************************
// Function Name: MedicalHistoryDlgProc
// 
// Purpose: Window Proc for the medical history dlg
//
// Arguments:
//    IN HWND hDlg - HWND of the dialog
//    IN UINT uMsg - Message to be processed
//    IN WPARAM wParam - wparam
//    IN LPARAM lParam - lparam
//
// Return Values:
//    LRESULT
//
LRESULT CALLBACK MedicalHistoryDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) 
    {
        case WM_INITDIALOG:
        {
            SHINITDLGINFO shidi = {0};
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLG;
            shidi.hDlg = hDlg;
            if(FAILED(SHInitDialog(&shidi)))
            {
                return FALSE;
            }

            SetWindowLong(hDlg, DWL_USER, lParam);
            MedicalHistoryStruct *pmh = (MedicalHistoryStruct *) lParam;

            if(pmh)
            {
                //Fill the dialog with the data we retrieved in ShowMedicalHistory
                SetDlgItemText(hDlg, IDC_HEALTHINSURANCE_EDITBOX, pmh->szHealthInsuranceProvider);
                SetDlgItemText(hDlg, IDC_BLOODGROUP_EDITBOX, pmh->szBloodGroup);
                SetDlgItemText(hDlg, IDC_BLOODPRESSURE_EDITBOX, pmh->szBloodPressure);
                SetDlgItemText(hDlg, IDC_ALLERGIES_EDITBOX, pmh->szAllergies);
            }
            break;
        }
        
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                {
                    MedicalHistoryStruct *pmh = (MedicalHistoryStruct *) GetWindowLong(hDlg, DWL_USER);

                    if(pmh)
                    {
                        // Store the new values in the pmh structure to return to the caller
                        GetDlgItemText(hDlg, IDC_HEALTHINSURANCE_EDITBOX, pmh->szHealthInsuranceProvider, MAX_CCH_MEDICAL_HISTORY_FIELD);
                        GetDlgItemText(hDlg, IDC_BLOODGROUP_EDITBOX, pmh->szBloodGroup, MAX_CCH_MEDICAL_HISTORY_FIELD);
                        GetDlgItemText(hDlg, IDC_BLOODPRESSURE_EDITBOX, pmh->szBloodPressure, MAX_CCH_MEDICAL_HISTORY_FIELD);
                        GetDlgItemText(hDlg, IDC_ALLERGIES_EDITBOX, pmh->szAllergies, MAX_CCH_MEDICAL_HISTORY_FIELD);
                    }

                    EndDialog(hDlg, 0);
                    break;
                }
            }
            
        case WM_DESTROY:
        {
            HFONT hFont = (HFONT)SendDlgItemMessage(hDlg, IDC_HEALTHINSURANCE_EDITBOX, WM_GETFONT, 0, 0);
            
            if (hFont)
            {
                DeleteObject(hFont);
            }
            break;
        }
        default:
            return (DefWindowProc(hDlg, uMsg, wParam, lParam));
            
    }
            
    return 0;
}



