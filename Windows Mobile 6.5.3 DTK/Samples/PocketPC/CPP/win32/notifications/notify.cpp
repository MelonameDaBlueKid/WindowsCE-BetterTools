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
#include "notify.h"
#include "ptrlist.h"


// GUID for the app {569440F0-C5B4-4ac2-A9AB-C616D19C011E}
//
// NOTE: if you base your application off this sample, you need to generate
//       your own GUID and replace this one!
//
static const GUID guidNotifyApp =
{ 0x569440f0, 0xc5b4, 0x4ac2, { 0xa9, 0xab, 0xc6, 0x16, 0xd1, 0x9c, 0x1, 0x1e }
};


// Global Variables:    
HINSTANCE            g_hInst;                                    // The current instance
HWND                g_hWnd;                                        // The main window handle
UINT                g_uiNotifyIDCount = 12540;                    // id base for notify events
UINT                g_iIDCounter = 10000;
TCHAR                g_szCustomSecs[MAX_STRINGLEN];
TCHAR                g_szCustomTitle[MAX_STRINGLEN];
TCHAR                g_szCustomHTMLSampleText[MAX_MESSAGELEN];
SHNP                g_shnpNotifyType = SHNP_INFORM;
DWORD                g_dwCustomFlags;
int                    g_iConvertedTime;
HWND                g_hDlg;
CPtrList*            g_pList;

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK NotifyMain(
    HWND, 
    UINT, 
    WPARAM,
    LPARAM
    );

LRESULT CALLBACK CustomOptions(
    HWND, 
    UINT, 
    WPARAM, 
    LPARAM
    );

// Linked List Wrapper Functions
SHNOTIFICATIONDATA* CreateAndAddNotification();

BOOL RemoveNotification(
    DWORD dwID
    );

void RemoveNotificationAll();

void FillDefaultSHND(
    SHNOTIFICATIONDATA* pshn
    );

void DestroySHND(
    SHNOTIFICATIONDATA* pshnd
    );

int WINAPI WinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    LPTSTR lpCmdLine,    
    int nCmdShow
    )
{
    g_hInst = hInstance;

    SHInitExtraControls();

    // just call a dialog box, system will handle messaging, painting, etc...
    DialogBox(hInstance,(LPCTSTR)IDD_NOTIFYMAIN, NULL,(DLGPROC)NotifyMain); 
    return 0;
}

LRESULT CALLBACK NotifyMain(
    HWND hDlg, 
    UINT message,
    WPARAM wParam,
    LPARAM lParam
    )
{
    
    SHINITDLGINFO shidi = {0};
    SHMENUBARINFO shmbi = {0};
    SHNOTIFICATIONDATA shnd = {0};
    HWND hPriorityListCtrl = NULL;
    HWND hRemoveListCtrl = NULL;
    int iItemNumber = 0;
    int iRemoveID = 0;
    SHNP shnpNotifyType;
    SHNOTIFICATIONDATA* pCurrentNotification = NULL;
    int iCurrentItem = 0;
    TCHAR szID[MAX_STRINGLEN];
    
    g_hDlg = hDlg;
    
    switch (message)
    {
    case WM_INITDIALOG:
        // Create a Done button and size it.  
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        SHInitDialog(&shidi);

        shmbi.cbSize = sizeof(shmbi);
        shmbi.hwndParent = hDlg;
        shmbi.nToolBarId = IDR_MENU_DATA;
        shmbi.hInstRes = g_hInst;
        SHCreateMenuBar(&shmbi);

        // get the combo box handle and add the priority items to it
        hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
        
        iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_INFORM);
        SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_INFORM);  
        
        iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_ICONIC);
        SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_ICONIC);  
        
        iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_UPDATED);
        SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)UPDATE_NOTIFICATION);  
        
        iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_CUSTOM);
        SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)CUSTOM_NOTIFICATION);
        
        // set the inform item as the default
        SendMessage(hPriorityListCtrl, CB_SETCURSEL, 0, 0);
        
        // populate the text information box about the type of priority
        SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_INFORM_MESSAGE);

        // initilize the CPtrList object 
        g_pList = new CPtrList;
        
        break;
        
    case WM_MESSAGEBOX:
        MessageBox(NULL, TEXT("User Clicked OK."), TEXT("Notification Callback"), NULL);
        break;
        
    case WM_TIMER:
        // wParam is the pointer to the SHNOTIFICAITONDATA structure to update - using Update Notification to update the event
        SHNOTIFICATIONDATA* pUpdateNotification;
        pUpdateNotification =(SHNOTIFICATIONDATA*)wParam;
        pUpdateNotification->pszTitle = TEXT("Updated Title!");
        SHNotificationUpdate(SHNUM_TITLE, pUpdateNotification);
        break;

    case WM_DESTROY:
        if (IDYES == MessageBox(NULL, TEXT("Clear notifications?"),
                TEXT("Notifications"), MB_YESNO | MB_ICONQUESTION))
        {
            RemoveNotificationAll();
        }
        break;
        
    case WM_COMMAND:
            // when the user finishes selecting a priority from the combo box
            if (HIWORD(wParam)== CBN_SELENDOK)
            {
                // we update the text when the user finishes the selection of the priority of the message
                hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
                iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
                shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
                switch (shnpNotifyType)
                {
                case SHNP_ICONIC:
                    SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_ICONIC_MESSAGE);
                    break;
                
                case UPDATE_NOTIFICATION:
                    SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_UPDATED_MESSAGE);
                    break;
                
                case CUSTOM_NOTIFICATION:
                    SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_CUSTOM_MESSAGE);
                    break;
                
                default:
                    SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_INFORM_MESSAGE);
                    break;
                }
            }
            else
            {
                switch (LOWORD(wParam))
                {
                    // if the user clicks add
                case IDC_ADD:
                    // Get the Selected Priority for the Notification
                    hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
                    iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
                    shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
                    
                    // create a node in the linked list for the notification
                    pCurrentNotification = CreateAndAddNotification();
                    // add the node to the listbox to show up in the display to remove(we know g_iIDCounter is the number)
                    // we do not iconic notificaitons since they expire at preset times
                    if (shnpNotifyType != SHNP_ICONIC)
                    {
                        wsprintf(szID, TEXT("%i"), g_iIDCounter);
                        hRemoveListCtrl = GetDlgItem(hDlg, IDC_REMOVELIST);
                        iCurrentItem = SendMessage(hRemoveListCtrl, LB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)szID);
                        SendMessage(hRemoveListCtrl, LB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(UINT)g_iIDCounter); 
                    }
                    
                    // This code is implemented this way to easily facilitate copying to other apps
                    switch (shnpNotifyType)
                    {
                    case SHNP_ICONIC:
                        FillDefaultSHND(&shnd);
                        shnd.hicon = LoadIcon(g_hInst,
                            MAKEINTRESOURCE(IDI_NOTIFY));
                        shnd.npPriority = SHNP_ICONIC;
                        shnd.csDuration = 10;

                        SHNotificationAdd(&shnd);
                        break;
                    case UPDATE_NOTIFICATION:
                        FillDefaultSHND(pCurrentNotification);
                        pCurrentNotification->hicon = LoadIcon(g_hInst,
                            MAKEINTRESOURCE(IDI_MESSAGE));
                        pCurrentNotification->npPriority = SHNP_INFORM;
                        pCurrentNotification->csDuration = 20;
                        
                        SHNotificationAdd(pCurrentNotification);
                        
                        // start the timer for the updated notification in 20 secs
                        // this will send a WM_TIMER message to the message queue after 20 seconds
                        SetTimer(g_hDlg,(UINT)pCurrentNotification, 20000, NULL);
                        break;
                    case CUSTOM_NOTIFICATION:
                        FillDefaultSHND(pCurrentNotification);
                        pCurrentNotification->hicon = LoadIcon(g_hInst,
                            MAKEINTRESOURCE((SHNP_ICONIC ==
                            g_shnpNotifyType) ? IDI_NOTIFY : IDI_MESSAGE));
                        pCurrentNotification->npPriority = g_shnpNotifyType;
                        pCurrentNotification->csDuration = g_iConvertedTime;
                        pCurrentNotification->pszHTML = g_szCustomHTMLSampleText;
                        pCurrentNotification->pszTitle = g_szCustomTitle;
                        pCurrentNotification->grfFlags |= g_dwCustomFlags;
                        
                        SHNotificationAdd(pCurrentNotification);
                        break;
                    default:
                        FillDefaultSHND(pCurrentNotification);
                        pCurrentNotification->hicon = LoadIcon(g_hInst,
                            MAKEINTRESOURCE(IDI_MESSAGE));
                        pCurrentNotification->npPriority = SHNP_INFORM;
                        pCurrentNotification->csDuration = 20;
                        
                        SHNotificationAdd(pCurrentNotification);
                        break;
                    }
                    break;
                    
                    // if the user clicks the custom dialog
                    case IDC_CUSTOM:
                        // check and see of the user has Custom Selected
                        hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
                        iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
                        shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
                        
                        if (shnpNotifyType == CUSTOM_NOTIFICATION)
                        {
                            DialogBox(g_hInst,(LPCTSTR)IDD_CUSTOMOPTIONS, NULL,(DLGPROC)CustomOptions); 
                        }
                        else
                        {
                            // change the selection to custom and proceed to the dialog
                            iItemNumber = SendMessage(hPriorityListCtrl, CB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)(LPCSTR)IDS_CUSTOM);
                            SendMessage(hPriorityListCtrl, CB_SETCURSEL,(WPARAM)iItemNumber, 0);
                            DialogBox(g_hInst,(LPCTSTR)IDD_CUSTOMOPTIONS, NULL,(DLGPROC)CustomOptions); 
                        }
                        break;
                        
                        // if user clicks remove 
                    case IDC_REMOVE:
                        hRemoveListCtrl = GetDlgItem(hDlg, IDC_REMOVELIST);
                        iItemNumber = SendMessage(hRemoveListCtrl, LB_GETCURSEL, 0, 0);
                        iRemoveID =(int)SendMessage(hRemoveListCtrl, LB_GETITEMDATA,(WPARAM)iItemNumber, 0);    
                        SendMessage(hRemoveListCtrl, LB_DELETESTRING,(WPARAM)iItemNumber, 0);
                        RemoveNotification(iRemoveID);
                        break;
                        
                    case IDOK:
                        EndDialog(hDlg, LOWORD(wParam));
                        break;
                        
                        // this is called if the user clicks OK(the HREF is cmd:10)
                    case 10:
                        wsprintf(szID, TEXT("%i"),(int)lParam);                
                        hRemoveListCtrl = GetDlgItem(hDlg, IDC_REMOVELIST);
                        iItemNumber = SendMessage(hRemoveListCtrl, LB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)(LPCSTR)szID);
                        SendMessage(hRemoveListCtrl, LB_DELETESTRING,(WPARAM)iItemNumber, 0);
                        RemoveNotification((int)lParam);
                        // must post message since notificaiton waits for procedure to end before closing bubble
                        // and adding a messagebox would cause it to wait forever
                        PostMessage(hDlg, WM_MESSAGEBOX, 0, 0);
                        break;    
                        
                    default:
                        break;
                }
            break;
            }
        }
    return FALSE;
}

// this is a dialog procedure for the custom dialog
LRESULT CALLBACK CustomOptions(
    HWND hDlg, 
    UINT message, 
    WPARAM wParam,
    LPARAM lParam
    )
{
    SHINITDLGINFO shidi;
    
    HWND hPriorityListCtrl;
    HWND hCheckBox = NULL;
    int iCurrentItem = 0;
    
    switch (message)
    {
    case WM_INITDIALOG:
        // Create a Done button and size it.  
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        SHInitDialog(&shidi);
                
        g_dwCustomFlags = NULL;            
                
        // get the combo box handle and add the priority items to it
        hPriorityListCtrl = GetDlgItem(hDlg, IDC_PRIORITYLIST);
        
        iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_INFORM);
        SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_INFORM);  
                
        iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_ICONIC);
        SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_ICONIC);  
        
        // set the inform item as the default
        SendMessage(hPriorityListCtrl, CB_SETCURSEL, 0, 0);
        
        // fill out the defualt time of 10 seconds in the time edit box
        SetDlgItemText(hDlg, IDC_SECONDS, IDS_DEFUALT_CUSTOM_TIME);
        
        // fill out the title
        SetDlgItemText(hDlg, IDC_TITLESOURCE, IDS_CUSTOM_TITLE);
        
        // fill out the HTML body
        SetDlgItemText(hDlg, IDC_HTMLSOURCE, IDS_CUSTOM_HTML_SAMPLE);        

        break;
        
    case WM_COMMAND:
        if (LOWORD(wParam)== IDOK)
        {
            // collect all of what the user entered
            // get seconds
            GetDlgItemText(hDlg, IDC_SECONDS, g_szCustomSecs, MAX_STRINGLEN);
            g_iConvertedTime = _ttoi(g_szCustomSecs);

            // get the title
            GetDlgItemText(hDlg, IDC_TITLESOURCE, g_szCustomTitle, MAX_STRINGLEN);

            // get the HTML body
            GetDlgItemText(hDlg, IDC_HTMLSOURCE, g_szCustomHTMLSampleText, MAX_STRINGLEN);    

            // get checkbox selections
            hCheckBox = GetDlgItem(hDlg, IDC_SHNF_STRAIGHTTOTRAY);
            if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0)== BST_CHECKED)
            {
                g_dwCustomFlags = g_dwCustomFlags | SHNF_STRAIGHTTOTRAY;
            }
            hCheckBox = GetDlgItem(hDlg, IDC_SHNF_CRITICAL);
            if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0)== BST_CHECKED)
            {
                g_dwCustomFlags = g_dwCustomFlags | SHNF_CRITICAL;
            }
            hCheckBox = GetDlgItem(hDlg, IDC_SHNF_FORCEMESSAGE);
            if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0)== BST_CHECKED)
            {
                g_dwCustomFlags = g_dwCustomFlags | SHNF_FORCEMESSAGE;
            }

            EndDialog(hDlg, LOWORD(wParam));
            PostMessage(g_hDlg, WM_COMMAND, IDC_ADD, NULL);
            return TRUE;
        }
        else if (LOWORD(wParam) == IDC_PRIORITYLIST)
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int iItemNumber;

                // Get the selected priority for the notification
                iItemNumber = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                g_shnpNotifyType = (SHNP)SendMessage((HWND)lParam,
                    CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
            }
        }
        break;

    }
    
    return FALSE;
}

//Add a node to the linked list(MFC Linked List)
SHNOTIFICATIONDATA* CreateAndAddNotification()
{
    SHNOTIFICATIONDATA* pshndTemp =(SHNOTIFICATIONDATA*)LocalAlloc(LMEM_MOVEABLE, sizeof(SHNOTIFICATIONDATA));

    if (pshndTemp)
    {
        ZeroMemory(pshndTemp, sizeof(SHNOTIFICATIONDATA));
        g_pList->AddTail((void*)pshndTemp);
    }
    
    return pshndTemp;    
}

// remove a node with the speficied dwID
BOOL RemoveNotification(
    DWORD dwID
    )
{
    BOOL bFound = FALSE;
    int iIndex = 0;
    POSITION tempPosition;
    SHNOTIFICATIONDATA* pshndTemp;
    while (!bFound &&(iIndex < g_pList->GetCount()))
    {
        tempPosition = g_pList->FindIndex(iIndex);
        pshndTemp =(SHNOTIFICATIONDATA*)g_pList->GetAt(tempPosition);
        if (NULL == pshndTemp)
        {
            break;
        }
        if (pshndTemp->dwID == dwID)
        {
            bFound = TRUE;
            SHNotificationRemove(&guidNotifyApp, dwID);
            DestroySHND(pshndTemp);
            g_pList->RemoveAt(tempPosition);
        }
        else
        {
            iIndex++;
        }
    }
    return bFound;    
}

// function removed all nodes in the list
// called when the programme exits
void RemoveNotificationAll()
{
    SHNOTIFICATIONDATA* pshndToDelete;
    POSITION tempPosition;
    int iListSize = g_pList->GetCount();
    
    for (int i = 0; i < iListSize; i++)
    {
        tempPosition = g_pList->GetHeadPosition();
        pshndToDelete =(SHNOTIFICATIONDATA*)g_pList->GetAt(tempPosition);
        if (NULL == pshndToDelete)
        {
            break;
        }
        DestroySHND(pshndToDelete);
        g_pList->RemoveHead();
    }
    SHNotificationRemove(&guidNotifyApp, 0);
}

void FillDefaultSHND(
    SHNOTIFICATIONDATA* pshnd
    )
{
    pshnd->dwID = g_iIDCounter;
    pshnd->clsid = guidNotifyApp;
    pshnd->hwndSink = g_hDlg;
    pshnd->pszHTML = IDS_DEFAULTHTMLMESSAGE;
    pshnd->cbStruct = sizeof(SHNOTIFICATIONDATA);
    pshnd->pszTitle = IDS_DEFAULTTITLE;
    pshnd->grfFlags = SHNF_HASMENU;
    pshnd->skm.hMenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_SKMENU_DEFAULT));
    pshnd->skm.cskc = 2;
    pshnd->skm.prgskc = (SOFTKEYCMD *)LocalAlloc(LMEM_FIXED, pshnd->skm.cskc * sizeof(SOFTKEYCMD));
    pshnd->skm.prgskc[0].wpCmd = 10;
    pshnd->skm.prgskc[0].grfFlags = NOTIF_SOFTKEY_FLAGS_DISMISS;
    pshnd->skm.prgskc[1].wpCmd = 2;
    pshnd->skm.prgskc[1].grfFlags = NOTIF_SOFTKEY_FLAGS_HIDE;

    g_iIDCounter++;
}

void DestroySHND(
    SHNOTIFICATIONDATA* pshnd
    )
{
    if (pshnd->hicon)
    {
        DestroyIcon(pshnd->hicon);
    }
    if (pshnd->skm.cskc && pshnd->skm.prgskc)
    {
        LocalFree(pshnd->skm.prgskc);
    }
    LocalFree(pshnd);
}
