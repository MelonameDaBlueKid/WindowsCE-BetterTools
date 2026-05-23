///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
// ShowFontMetrics.cpp
///////////////////////////////////////////////////////////////////////////////
//
//  The program allows users to browse fonts available on the device.  The use 
//  may modify the height, weight and width of each available font and view 
//  sample of the resultant font.  The user may also change the font sample 
//  text.  Additional font metrics are avaiable via "Details"
//
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <aygshell.h>
#include <tpcshell.h>
#include "resource.h"


TCHAR tszSample[] = _T("The thin red line for the brown fox and lazy dog. 0123456789");

HINSTANCE g_hInst;
HWND g_hWndListBox;
HFONT g_hf;

// function declarations
BOOL CALLBACK ShowFontInfo(
    const HWND hWnd, 
    const UINT Msg, 
    const WPARAM wParam, 
    const LPARAM lParam
    );
BOOL CALLBACK MetricsProc(
    const HWND hWnd, 
    const UINT Msg, 
    const WPARAM wParam, 
    const LPARAM lParam
    );
int  CALLBACK EnumFontProc(
    const LOGFONT *,
    const TEXTMETRIC *, 
    ULONG , 
    LPARAM
    );
void ShowTextMetrics(
    HWND hWnd
    );
void UpdateSampleText(
    HWND hWnd
    );
void ShowFontMetrics(
    HWND hWnd
    );


// Purpose: Determine at runtime if the app is running on a smartphone device
static BOOL IsSmartphone() 
{
    TCHAR tszPlatform[64];

    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE,
         sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
    {
        if (0 == _tcsicmp(TEXT("Smartphone"), tszPlatform)) 
        {
            return TRUE;
        }
    }
    return FALSE;   
}


///////////////////////////////////////////////////////////////////////////////
// Function Name: WinMain
//
// Purpose: Main entry point into the HelloTAPI program
//
// Arguments: Standard WinMain arguments
//
// Return Values: 0
//
// Description:
//	WinMain function will create a list with pre-populated elements in it for 
//	viewing and manipulation.

int WINAPI WinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nShowCmd
    )
{

    INITCOMMONCONTROLSEX ics;

	// store the hInstance
	g_hInst = hInstance;

    ics.dwSize = sizeof(INITCOMMONCONTROLSEX);
    ics.dwICC = ICC_UPDOWN_CLASS | ICC_CAPEDIT_CLASS;

    InitCommonControlsEx(&ics);

    if(TRUE == IsSmartphone())
    {
	    // create the dialog box
	    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_FONTINFO_SPH), 0, (DLGPROC)ShowFontInfo);
    }
    else 
    {
	    // create the dialog box
	    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_FONTINFO_PPC), 0, (DLGPROC)ShowFontInfo);
    }

	return 0;
}


VOID FillControls(
    HWND hWnd
    )
{
    // Set up font information
    HDC hdc;

    //Set the example's text
    SendMessage(GetDlgItem(hWnd, IDC_EDIT1), WM_SETTEXT, NULL, (LPARAM)tszSample);

    //Use hwndLBFont to set sample text
    g_hWndListBox = GetDlgItem(hWnd,IDD_FONTLIST);
    if (NULL == g_hWndListBox) 
    {
	    //couldn't find control, exit w/error
	    EndDialog(hWnd, 1);
    }

    g_hf = NULL;

    //Prepare g_hWndListBox
    SendMessage(g_hWndListBox, LB_RESETCONTENT, 0, 0);
    //Enum fonts
    hdc = GetDC(NULL);
    EnumFonts( hdc, NULL, &EnumFontProc, (LONG)g_hWndListBox );
    ReleaseDC(NULL, hdc);

    //Set selection to first in list
    SendMessage (g_hWndListBox, LB_SETCURSEL, 0, 0);
    //Update edit controls
    ShowTextMetrics(hWnd);
    //Show sample based on edit control values
    UpdateSampleText(hWnd);		
}


///////////////////////////////////////////////////////////////////////////////
// Function Name: ShowFontInfo
// 
// Purpose: Message Handler for IDD_FONTINFO Dialog Box
//
// Arguments: Standard Dialog Procedure Arguments
//
//
// Side Effects:
//     
// Return Values:
//	Only returns to exit the dialog
//	
// Description:
//	Dialog Procedure will allow for initial population of the list box with
//  test values.  Then respond to commands to manipulate font properties

BOOL CALLBACK ShowFontInfo(
    const HWND hWnd, 
    const UINT Msg, 
    const WPARAM wParam, 
    const LPARAM lParam
    )
{
    BOOL bReturn = TRUE;
    int nLastFontSel = 0;
    
    switch (Msg)
    {
    case WM_INITDIALOG:
        // Specify that the dialog box should stretch full screen
        SHINITDLGINFO shidi;
        ZeroMemory(&shidi, sizeof(shidi));
        shidi.dwMask = SHIDIM_FLAGS;
        if (TRUE == IsSmartphone()) 
        {
            shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
        }
        else
        {
            shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
        }

        shidi.hDlg = hWnd;
        
        // If we could not initialize the dialog box, return an error
        if (FALSE == SHInitDialog(&shidi))
        {
            MessageBox(hWnd, TEXT("Failed to init dialog"), TEXT("Failure"), MB_OK);
            
            //Failed to init, so quit app
            EndDialog (hWnd, FALSE);
            bReturn = TRUE;
        }
        
        // Set up the menu bar
        SHMENUBARINFO shmbi;
        ZeroMemory(&shmbi, sizeof(shmbi));
        shmbi.cbSize = sizeof(shmbi);
        shmbi.hwndParent = hWnd;
        shmbi.nToolBarId = IDR_SHOWFONT_MENUBAR;
        shmbi.hInstRes = g_hInst;
        
        // If we could not initialize the dialog box, return an error
        if (FALSE == SHCreateMenuBar(&shmbi))
        {
            MessageBox(hWnd, TEXT("Failed to create menu bar"), TEXT("Failure"), MB_OK);
            
            //Failed to init, so quit app
            EndDialog (hWnd, FALSE);
            bReturn = TRUE;
        }
        
        // set the title bar
        SetWindowText(hWnd, TEXT("Font Information"));
        
        //Now find out if we are a smartphone device
        if (IsSmartphone())
        {
            // In order to make Back work properly, it's necessary to 
            // override it and then call the appropriate SH API
            (void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                SHMBOF_NODEFAULT | SHMBOF_NOTIFY));
        }
        
        
        FillControls(hWnd);
        
        break;
        
    case WM_COMMAND:
        switch (LOWORD(wParam)) 
        {
        case IDM_SHOWFONT_EXIT:
            EndDialog (hWnd, TRUE);
            break;
        case IDM_SHOWFONT_METRICS:
            DialogBox (g_hInst, MAKEINTRESOURCE(IDD_METRICS), hWnd, (DLGPROC)MetricsProc);
            break;
            
        case IDD_FONTLIST:
            if(LBN_SELCHANGE == HIWORD(wParam)) 
            {
                ShowTextMetrics(hWnd);
                UpdateSampleText(hWnd);
            }
            break;
        case IDD_HEIGHT:  //Fall through
        case IDD_WIDTH:   //Fall through
        case IDD_WEIGHT:
            //Edit box lost focus, update sample
            if(EN_KILLFOCUS == HIWORD(wParam))
            {
                UpdateSampleText(hWnd);
            }
            break;
        case IDOK: //Fall through
        case IDCANCEL:
            EndDialog(hWnd, 0);
            break;
        }
        break;
        
    case WM_CLOSE:
        if(g_hf) 
        {
            DeleteObject(g_hf);
        }
        EndDialog (hWnd, 0);
        break;
        
    case WM_HOTKEY:
        // The following is necessary to get the appropriate Back key behavior 
        // (handle on key-up as per recommendations)
        if(VK_TBACK == HIWORD(lParam)) {
            SHSendBackToFocusWindow(Msg, wParam, lParam);				
        }
        break;
        
        
    default:
        // nothing was processed
        bReturn = FALSE;
        break;
    }
    
    return bReturn;
}

///////////////////////////////////////////////////////////////////////////////
// Function Name: MetricsProc
// 
// Purpose: Message Handler for IDD_METRICS Dialog Box
//
// Arguments: Standard Dialog Procedure Arguments
//
// Side Effects: 
//     
// Return Values:
//	Only returns to exit the dialog
//	
// Description:
//	Dialog Procedure will allow for initial population of the list box with
//  test values.  Then respond to commands to manipulate font properties

BOOL CALLBACK MetricsProc(
    const HWND hWnd, 
    const UINT Msg,
    const WPARAM wParam, 
    const LPARAM lParam
    )
{
	BOOL	bReturn = true;

	switch (Msg)
	{
		case WM_INITDIALOG:
            // Specify that the dialog box should stretch full screen
			SHINITDLGINFO shidi;
			ZeroMemory(&shidi, sizeof(shidi));
            shidi.dwMask = SHIDIM_FLAGS;
            if (TRUE == IsSmartphone()) 
            {
                shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
            }
            else
            {
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
            }
            shidi.hDlg = hWnd;
            
			// Set up the menu bar
			SHMENUBARINFO shmbi;
			ZeroMemory(&shmbi, sizeof(shmbi));
            shmbi.cbSize = sizeof(shmbi);
            shmbi.hwndParent = hWnd;
            shmbi.nToolBarId = IDR_SHOWFONT_METRICSMENU;
            shmbi.hInstRes = g_hInst;

			// If we could not initialize the dialog box, return an error
			if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
				EndDialog(hWnd, -1);
			}

			// set the title bar
			SetWindowText(hWnd, TEXT("Font Metrics"));

			ShowFontMetrics(hWnd);

			break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) 
            {
            case IDOK: //Fall through
			case IDM_SHOWFONT_OK:
				EndDialog (hWnd, 0);
				break;
			}

		case WM_CLOSE:	
			EndDialog(hWnd, 0);
			break;
			
		default:
			// nothing was processed
			bReturn = false;
			break;
	}

	return bReturn;
}

///////////////////////////////////////////////////////////////////////////////
// Function Name: ShowTextMetrics
// 
// Purpose: Update dialog controls with values from EnumFont callback.
//
// Arguments: hwnd owning IDD_FONTLIST, IDD_HEIGHT, IDD_WIDTH, IDD_WEIGHT,
//  IDD_TM_NAME
//
// Side Effects: 
//     
// Return Values:
//	
// Description:
//  Selection index of IDD_FONTLIST is used to index into global LOGFONT list
//  and related controls updated accordingly.

void ShowTextMetrics(
    HWND hWnd 
    )
{
    LOGFONT *  plfCurrent;

    //Get the log font that is stored as LB's item data
    plfCurrent = (LOGFONT *)SendMessage(g_hWndListBox, LB_GETITEMDATA, 
        SendMessage( g_hWndListBox, LB_GETCURSEL, 0, 0 ), 0);

	//Set Dlg values
	SetDlgItemInt( hWnd, IDD_HEIGHT, plfCurrent->lfHeight, FALSE );
	SetDlgItemInt( hWnd, IDD_WIDTH,  plfCurrent->lfWidth, FALSE );
	SetDlgItemInt( hWnd, IDD_WEIGHT, plfCurrent->lfWeight, FALSE );
	SetDlgItemText( hWnd, IDD_TM_NAME, plfCurrent->lfFaceName);

	return;
}

///////////////////////////////////////////////////////////////////////////////
// Function Name: UpdateSampleText
// 
// Purpose: Update the sample text
//
// Arguments: hWnd of windows owning the following controls: IDD_FONTLIST,
//  IDC_EDIT1, IDD_HEIGHT, IDD_WIDTH, IDD_WEIGHT
//
// Side Effects: 
//     
// Return Values:
//	
// Description:
//	Font name, height, width and weight are read in from controls and a new
//  font is created using those values. This font is sent to the IDC_EDIT1
//  control and the old font object is destroyed.

void UpdateSampleText(
    HWND hWnd 
    )
{
	HFONT	hf = NULL;
	LOGFONT	lf = {0};
	HWND	hWndSample;
	static BOOL fCreatedFont = FALSE;

	//Set the font name
	SendMessage( g_hWndListBox, LB_GETTEXT, 
		SendMessage(GetDlgItem(hWnd,IDD_FONTLIST), LB_GETCURSEL,0,0),
		(LPARAM)lf.lfFaceName);

	// Sets the logical font parameters
	lf.lfHeight = GetDlgItemInt(hWnd, IDD_HEIGHT, NULL, TRUE);
	lf.lfWidth = GetDlgItemInt(hWnd, IDD_WIDTH,  NULL, FALSE);
	lf.lfWeight = GetDlgItemInt(hWnd, IDD_WEIGHT, NULL, FALSE);

    hWndSample = GetDlgItem(hWnd, IDC_EDIT1);
	if (NULL != hWndSample)
    {
		//Create a new font and cache HFONT
        hf = (HFONT)CreateFontIndirect(&lf);
		if (NULL != hf)
        {
			//change sample font to new font
			SendMessage(hWndSample, WM_SETFONT, (WPARAM)hf, TRUE);
			//if the global font was set, delete it.  g_hf will only be null before this
			//code is called once.
			if(g_hf)
            {
				DeleteObject(g_hf);
			}
			//update global font
			g_hf = hf;
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
// Function Name: ShowFontMetrics
// 
// Purpose: Place current font data in dialog controls
//
// Arguments: HWND of dialog owning controls to update
//
// Side Effects: 
//     
// Return Values:
//	
// Dependencies:
//  hWnd is child dialog of a dialog containing the control IDC_EDIT1
//	
// Description:
//	Function gets a DC, loads the font from the IDC_EDIT1 control into the
//  DC, retreives TEXTMETRIC information and updates controls.

void ShowFontMetrics(
    HWND hWnd
    )
{

	TCHAR  tszFontName[LF_FACESIZE];
	HFONT  hf;
	HDC    hdc;
	int    i; 
	static TEXTMETRIC tm;
	struct FONTINFO{
		int  nDlgID;
		long *pTM;   
	};
	static struct FONTINFO FontData[] = {  
		IDD_TM_HEIGHT,   &tm.tmHeight,
		IDD_TM_ASCENT,   &tm.tmAscent,
		IDD_TM_DESCENT,  &tm.tmDescent,
		IDD_TM_LEADINT,  &tm.tmInternalLeading,
		IDD_TM_LEADEXT,  &tm.tmExternalLeading,
		IDD_TM_WIDTHAVG, &tm.tmAveCharWidth,
		IDD_TM_WIDTHMAX, &tm.tmMaxCharWidth,
		IDD_TM_WEIGHT,   &tm.tmWeight,
		IDD_TM_OVER,     &tm.tmOverhang,
		IDD_TM_DIGITX,   &tm.tmDigitizedAspectX,
		IDD_TM_DIGITY,   &tm.tmDigitizedAspectY   
	};

	
	hdc = GetDC(NULL);
	//Select the sample text font into the DC
	hf = (HFONT)SelectObject(hdc, (HFONT)SendMessage(GetDlgItem(GetParent(hWnd), IDC_EDIT1), WM_GETFONT, 0, 0));
	GetTextMetrics(hdc, &tm);
	GetTextFace(hdc, sizeof(tszFontName)/sizeof(*tszFontName), tszFontName);
	SendDlgItemMessage(hWnd, IDD_TM_NAME, WM_SETTEXT, 0, (DWORD)(LPTSTR)tszFontName);
	//Restore the original font to the DC
	SelectObject(hdc, (HFONT)hf);
	//Clean up DC
	ReleaseDC(NULL, hdc);

	//Update controls with TEXTMETRIC data
	for(i = 0; i < sizeof(FontData)/sizeof(FontData[0]); i++)
    {
		SetDlgItemInt(hWnd, FontData[i].nDlgID, *FontData[i].pTM, TRUE);
    }
	return;
}
///////////////////////////////////////////////////////////////////////////////
// Function Name: MetricsProc
// 
// Purpose: EnumFont callback
//
// Arguments: EnumFont callback Arguments, no lParam data passed
//
// Side Effects: A member of g_lfList is set and g_nFontCount is incremented
//     
// Return Values:
//	FALSE if no member of g_lfList available, otherwise TRUE
//	
// Description:
//  Handles EnumFont callback, adding LOGFONT to the global LOGFONT list

int CALLBACK EnumFontProc(
    const LOGFONT * pLF,
    const TEXTMETRIC *tm,
    ULONG nFontType,  
    LPARAM lParam 
    )
{
    int iIndex;
    LOGFONT * plfLocal = new LOGFONT;

    if (NULL == plfLocal)
    {
        //fail and stop enumeration
        return 0;
    }

    memcpy(plfLocal, pLF, sizeof(LOGFONT));
    
    iIndex = SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)pLF->lfFaceName);

    // check to see if item was added properly
    if(LB_ERR != iIndex) 
    {
        SendMessage((HWND)lParam, LB_SETITEMDATA, (WPARAM)iIndex, (LPARAM)plfLocal);
        // Return non-zero to continue enumeration
        return 1;
    }
    else
    {
        // Return zero to stop enumeration
        return 0;
    }
} 

