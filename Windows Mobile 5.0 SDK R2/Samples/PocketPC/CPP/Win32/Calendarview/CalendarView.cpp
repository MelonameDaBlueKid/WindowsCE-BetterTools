//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.


#include "CalendarView.h"


///////////////////////////////////////////////////////////////////////////////
// Function:
//      WinMain
//
// Purpose:
//      Application entry point.
//
// Parameters:
//      hInstance       - Handle to current app instance.
//      hPrevInstance   - Unused.
//      lpCmdLine       - Unused.
//      nCmdShow        - Unused.
//
// Returns:
//      0               - Application exited gracefully.
//      -ve int         - App init failed.
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG         msg;
    WNDCLASS    wc;
    int         rc = 0;
    HRESULT     hr = S_OK;
    INITCOMMONCONTROLSEX icex = {0};

    // Initialize application
    rc = InitApp(hInstance, &wc );
    if (rc < 0)
    {
        return rc;
    }

    // Register specific common control classes from the common control DLL. 
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_LISTVIEW_CLASSES | ICC_TOOLTIP_CLASSES; 
    CBR(InitCommonControlsEx(&icex)); 

    // Init POOM
    hr = InitPOOM2();
    CHR(hr);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) 
    {
        CHR(E_FAIL);
    }

    // Main message loop
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

Error:
    // UnInit POOM
    UnInitPOOM2();    
    
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      InitApp
//
// Purpose:
//      Checks if the app dialog class already exists. If so, it means the app 
//      is already running so we quit this instance.
//
// Parameters:
//      hInstance       - Handle to current app instance
//      lpWndClass      - pointer to WNDCLASS struct which is filled with app settings.
//
// Returns:
//      0   - Success.
//      -1  - Failure.
//
int InitApp (HINSTANCE hInstance, WNDCLASS *lpWndClass)
{
    HRESULT hr          = E_FAIL;
    HANDLE  hMutex      = NULL;
    HWND    hWndPrev    = NULL;
    BOOL    bPrevInstanceFound = FALSE;
    

    CBR(lpWndClass);

    // Allow only one instance of the app and activate it if running
    hr = FindPreviousInstance(g_szClassName, 
        NULL, 
        &hMutex, 
        &hWndPrev, 
        &bPrevInstanceFound,
        TRUE);
    CHR(hr);

    if (bPrevInstanceFound)
    {
        hr = S_FALSE;
        goto Error;
    }

    lpWndClass->style                = 0;
    lpWndClass->lpfnWndProc          = (WNDPROC) DlgMainProc;
    lpWndClass->cbClsExtra           = 0;
    lpWndClass->cbWndExtra           = 0;
    lpWndClass->hInstance            = hInstance;
    lpWndClass->hIcon                = NULL;
    lpWndClass->hCursor              = 0;
    lpWndClass->hbrBackground        = (HBRUSH) GetStockObject(WHITE_BRUSH);
    lpWndClass->lpszMenuName         = NULL;
    lpWndClass->lpszClassName        = g_szClassName;

    if (RegisterClass(lpWndClass) == 0)
    {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_CLASS_ALREADY_EXISTS)
        {
            DEBUGMSG(TRUE, (L"%s: Failed to registed class. Error = 0x%x", dwError));
            CHR(E_FAIL);
        }
    }


Error:    
    if(FAILED(hr))
    {
        return -1;
    }
    
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      InitInstance
//
// Purpose:
//      Create the main dialog box for the application and registers its WndProc.
//
// Parameters:
//      hInstance   - Handle to current app instance.
//      nCmdShow    - Unused.
//
// Returns:
//      TRUE    - Success
//      FALSE   - Failure
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{        
    BOOL bRet;
       
    // Store instance handle in our global variable     
    g_hInst = hInstance;    
    
    // Create the main app dialogbox
    bRet = (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_CALVIEW), NULL, (DLGPROC)DlgMainProc) >= 0);
    
    return bRet;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      InitLV
//
// Purpose:
//      Creates the listview and add the columns, defined in g_rgCols, to the listview.
//
// Parameters:
//      hDlg    -   Handle to app dialog
//
// Returns:
//      An HRESULT
//
HRESULT InitLV(HWND hDlg)
{
    LVCOLUMN    lvc     = {0};
    int         i       = 0;
    HWND        hwndLV  = GetDlgItem(hDlg, IDC_APPTS_LIST);    
    HRESULT     hr      = S_OK;
    int         iRet    = -1;

    CBR(hDlg);

    // Add listview columns
    for (i = 0; i < ARRAYSIZE(g_rgCols); i++)
    {
        lvc.mask    = LVCF_TEXT;
        lvc.pszText = g_rgCols[i];

        iRet = ListView_InsertColumn(hwndLV, i, &lvc);
        CBR(-1 != iRet);

        CBR(ListView_SetColumnWidth(hwndLV, i, LVSCW_AUTOSIZE_USEHEADER));
    }
    
Error:    
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Function:
//      InitSKMenu
//
// Purpose:
//      Creates the softkey menu
//
// Parameters:
//      void
//
// Returns:
//      An HRESULT
//
HRESULT InitSKMenu(HWND hDlg, UINT nToolBarId)
{
    HRESULT         hr      = S_OK;
    SHMENUBARINFO   mbi     = {0};
    SHINITDLGINFO   shidi   = {0};
        
    mbi.cbSize      = sizeof(SHMENUBARINFO);
    mbi.hwndParent  = hDlg;
    mbi.nToolBarId  = nToolBarId;
    mbi.hInstRes    = g_hInst;
    mbi.nBmpId      = 0;
    mbi.cBmpImages  = 0;

    CBR(SHCreateMenuBar(&mbi));
    
    shidi.dwMask    = SHIDIM_FLAGS;
    shidi.dwFlags   = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
    shidi.hDlg      = hDlg;

    CBR(SHInitDialog(&shidi));

Error:
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      RefreshItems
//
// Purpose:
//      Called each time we recieve a POOM notification//
//
// Parameters:
//      hwndLV - [IN] Handle the the listview to add the items item.
//
// Returns: 
//      An HRESULT
//
HRESULT RefreshItems(HWND hwndLV)
{
    HRESULT     hr          = S_OK;
    LVITEM      lvi         = {0};
    WCHAR       szBuffer[MAX_LOADSTRING];
    IItem       *pItem      = NULL;
    IFolder     *pFolder    = NULL;
    IDispatch   *pDisp      = NULL;
    int         cItems      = 0;    
    LRESULT     lresult     = 0;
    CEPROPVAL   *pPropVals  = NULL;
    ULONG       cbBuffer    = 0;
    HANDLE      hHeap       = GetProcessHeap();
    HCURSOR     hCursor     = NULL;
    IPOutlookItemCollection *pCol = NULL;
    
    
    CBR(NULL != hwndLV);    
    
    // Cache the previous Cursor    
    hCursor = GetCursor();
        
    // Display a wait cursor while the updates are processed.
    SetCursor(LoadCursor(NULL, IDC_WAIT));         

    // Clears all the items from the LV.
    CBR(ListView_DeleteAllItems(hwndLV));

    CBR(g_polApp != NULL);
        
    hr = g_polApp->GetDefaultFolder(olFolderCalendar, &pFolder);
    CHR(hr);
    hr = pFolder->get_Items((IPOutlookItemCollection **)&g_pCol);
    CHR(hr);    

    hr = g_pCol->get_Count(&cItems);
    CHR(hr);

    hr = StringCchPrintf(szBuffer, ARRAYSIZE(szBuffer), L"Number of Calendar items = %d", cItems);
    CHR(hr);
    
    CBR(SetDlgItemText(g_hWnd, IDC_HEADER_STATIC, (LPCTSTR)szBuffer));
    
    for (int i = 0; i < cItems; i++)
    {
        // Since item in the POOM collection are 1 based indexed, 
        //  and we get the 0-based count, we need to add 1 to get the correct item.
        hr = g_pCol->Item(i+1, (IDispatch **)&pDisp);
        CHR(hr);
        CBR(pDisp);

        hr = pDisp->QueryInterface(IID_IItem, (LPVOID*)&pItem);    
        CHR(hr);
        CBR(pItem);
        RELEASE_OBJ(pDisp);
        
        cbBuffer = 0;
        hr = pItem->GetProps(g_pPropIDs, CEDB_ALLOWREALLOC, ARRAYSIZE(g_pPropIDs), &pPropVals, &cbBuffer, hHeap);
        CHR(hr);
        CBR(NULL != pPropVals);


        //Add subject
        hr = PrettyPrintPropVal(&(pPropVals[0]), szBuffer, ARRAYSIZE(szBuffer));
        CHR(hr);
        
        lvi.mask        = LVIF_TEXT;
        lvi.iItem       = i;
        lvi.iSubItem    = 0;        
        lvi.pszText     = szBuffer;
        lresult         = SendMessage(hwndLV, LVM_INSERTITEM, 0, (LPARAM)&lvi);

        for (int j = 1; j <= ARRAYSIZE(g_pPropIDs); j++)
        {
            //Add other items data
            hr = PrettyPrintPropVal(&(pPropVals[j]), szBuffer, ARRAYSIZE(szBuffer));
            CHR(hr);
            
            lvi.mask        = LVIF_TEXT;
            lvi.iItem       = i;
            lvi.iSubItem    = j;        
            lvi.pszText     = szBuffer;
            lresult         = SendMessage(hwndLV, LVM_SETITEM, 0, (LPARAM)&lvi);
        }

        HEAP_FREE(hHeap, pPropVals);         
        RELEASE_OBJ(pItem);
    }
            
Error:
    HEAP_FREE(hHeap, pPropVals);             
    RELEASE_OBJ(pItem);
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(pDisp);

    // Set back to the default cursor
    SetCursor(hCursor);            

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      ProcessMainMenu
//
//  Processes the SK menu options.
//
// Purpose:
//      Checks if the app dialog class already exists. If so, it means the app 
//      is already running so we quit this instance.
//
// Parameters:
//      void
//
// Returns: 
//      An HRESULT
//
HRESULT ProcessMainMenu(HWND hDlg, WORD wLo)
{
    HRESULT     hr      = S_OK;
    IDispatch   *pDisp  = NULL;
    HWND        hwndLV  = GetDlgItem(hDlg, IDC_APPTS_LIST);                
    IItem       *pItem  = NULL, 
                *pItem2 = NULL;

    CBR(hDlg);

    switch (wLo)
    {
        case IDOK: 
        case IDM_EXIT:
            DestroyWindow(hDlg);
            PostQuitMessage(0);
            break;

        case IDM_ACTION_REFRESH:
            RefreshItems(GetDlgItem(hDlg, IDC_APPTS_LIST));
            break;

        case IDM_ACTION_EDIT:
        case IDM_ACTION_DISPLAY:
        case IDM_ACTION_DELETE:
        case IDM_ACTION_COPY:            
            {
                int iIndex = ListView_GetSelectionMark(hwndLV);

                CBR(NULL != g_pCol);

                // Since item in the POOM collection are 1 based indexed, 
                //  and we get the 0-based index from the ListView_GetSelectionMark
                //  call, we need to add 1 to get the same item.
                hr = g_pCol->Item(iIndex+1, &pDisp);
                CHR(hr);

                // Its easier to do generic operation on the IItem (as opposed to 
                //  the IContact, IAppointment or ITask).
                hr = pDisp->QueryInterface(IID_IItem, (LPVOID*)&pItem);           
                CHR(hr);
                CBR(NULL != pItem);
                
                switch(wLo)
                {                    
                    case IDM_ACTION_EDIT: 
                        // Brings up the edit card for the user to edit the item
                        // Blocking UI call. (ie the user need to close the dialog 
                        //  to continue)
                        hr = pItem->Edit(NULL);
                        CHR(hr);
                        break;

                    case IDM_ACTION_DISPLAY:
                        // Brings up the summary card for the user to view the item details.
                        // Blocking UI call. (ie the user need to close the dialog 
                        //  to continue)
                        hr = pItem->Display(NULL);
                        CHR(hr);
                        break;

                    case IDM_ACTION_DELETE: 
                        // Delete the item from the underlying db.
                        hr = pItem->Delete(); 
                        CHR(hr);                        
                        break;

                    case IDM_ACTION_COPY:                         
                        // Makes an exact copy of the item
                        hr = pItem->Copy(&pItem2); 
                        CHR(hr);
                        break;                    
                }

            }
            break;

    }

Error:
    RELEASE_OBJ(pDisp);
    RELEASE_OBJ(pItem2);
    RELEASE_OBJ(pItem);
    
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Function:
//      DlgMainProc
//
//  Process WM messages to the dialog box. 
//
// Purpose:
//      Checks if the app dialog class already exists. If so, it means the app 
//      is already running so we quit this instance.
//
// Parameters:
//      hDlg        - [IN] Handle to main dialog 
//      message     - [IN] WM message
//      wParam      - [IN] WPARAM for WM message
//      lParam      - [IN] LPARAM for WM message
//
// Returns:
//      An LRESULT
//
LRESULT CALLBACK DlgMainProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
    HRESULT     hr  = S_OK;    
    static HWND hWndStats;
    WORD        wHi = HIWORD(wParam), 
                wLo = LOWORD(wParam);

    // Keep this static so we reuse the same variable each time this function is called.
    static IPOutlookItemCollection *pCol;

    CBR(hDlg);
           
    switch (message) 
    {
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            DestroyWindow (hDlg);
            break;
            
        case WM_DESTROY:
            RELEASE_OBJ(pCol);
            if(g_polApp)
            {
                hr = g_polApp->Logoff();                
            }            
            PostQuitMessage(0);
            break;

        case WM_INITDIALOG:
            g_hWnd  = hDlg;

            CBR(NULL != g_polApp);
            hr = g_polApp->Logon((long)g_hWnd);    
            CHR(hr);
            
            //Register for notifications
            hr = SubscribeToNotifications(g_polApp, olAppointmentItem, PIMFOLDERNOTIFICATION_ALL);
            CHR(hr);

            hr = InitSKMenu(hDlg, ID_BTNBARRES);                                              
            CHR(hr);

            hr = InitLV(hDlg);
            CHR(hr);

            hr = RefreshItems(GetDlgItem(hDlg, IDC_APPTS_LIST));
            CHR(hr);

            CBR(UpdateWindow(hDlg));
            break;

        case WM_COMMAND:    
            hr = ProcessMainMenu(hDlg, wLo);
            CHR(hr);
            break;

        case PIM_ITEM_CREATED_LOCAL:
        case PIM_ITEM_DELETED_LOCAL:
        case PIM_ITEM_CHANGED_LOCAL:
        case PIM_ITEM_CREATED_REMOTE:
        case PIM_ITEM_DELETED_REMOTE:
        case PIM_ITEM_CHANGED_REMOTE:
            // Caught a POOM notification.
            hr = RefreshItems(GetDlgItem(hDlg, IDC_APPTS_LIST));
            CHR(hr);
            break;

        default:
            return DefWindowProc(hDlg, message, wParam, lParam);
    }

Error:
    if(FAILED(hr))
    {
        ShowHR(hr);
    } 
    
    return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      ItemTypeToFolder
//
// Purpose:
//      Returns the Outlook folder type given the Outlook Item type.
//
// Parameters:
//      olItemType - Outlook item type
//
// Returns:
//      An OlDefaultFolders to the specified Item Type
//
OlDefaultFolders ItemTypeToFolder(int olItemType)
{
    OlDefaultFolders olFolder = (OlDefaultFolders) 0;
    
    switch(olItemType)
    {
        case olAppointmentItem:
            olFolder = olFolderCalendar;
            break;
            
        case olContactItem:
            olFolder = olFolderContacts;
            break;

        case olTaskItem:
            olFolder = olFolderTasks;
            break;
            
        default:
            ASSERT(FALSE);
    }

    return olFolder;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      PrettyPrintPropVal
//
// Purpose:
//      Formats the different CEPROPVAL data into a string.  This is used to 
//      format the data to be added to the listview columns.
//
// Parameters:
//      pPropVal        - [IN] CEPROPVAL struct to format and print.
//      pszPrintBuffer  - [IN/OUT] buffer to write the formatted string to.
//      cBufferSize     - [IN] size of buffer (in count of chars).
//
// Returns:
//      An HRESULT
//
HRESULT PrettyPrintPropVal(CEPROPVAL *pPropVal, LPWSTR pszPrintBuffer, int cBufferSize)
{    
    SYSTEMTIME  st = {0};    
    HRESULT     hr = S_OK;

    CBR(NULL != pPropVal);
    CBR(NULL != pszPrintBuffer);
    CBR(NULL != cBufferSize);

    // Format the data based on the CEPROPID (ie data type)
    switch (TypeFromPropID(pPropVal->propid))
    {
        
        case CEVT_I2:           
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%d", pPropVal->val.iVal);            
            break;
            
        case CEVT_UI2:            
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%u", pPropVal->val.uiVal);            
            break;            

        case CEVT_I4:    
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%d", pPropVal->val.lVal);                                
            break;

        case CEVT_UI4:                        
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%u", pPropVal->val.ulVal);
            break;
            
        case CEVT_FILETIME:            
            FileTimeToSystemTime(&(pPropVal->val.filetime), &st);            
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%u/%u/%u %u:%02u.%u", 
                st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute,st.wSecond);
            break;

        case CEVT_BOOL:
            if(pPropVal->val.boolVal)                    
            {
                hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"TRUE");
            }            
            else
            {
                hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"FALSE");
            }            
            break;
            
        // Since no standard prop is defined as R8, this is can be used to handle a custom prop defined
        // with this data type.
        case CEVT_R8:
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%u",(int) pPropVal->val.dblVal);
            break;
        
        case CEVT_LPWSTR:
            if(pPropVal->wFlags == CEDB_PROPNOTFOUND || pPropVal->val.lpwstr == NULL) 
            {
                pPropVal->val.lpwstr = NULL;
            }                                  
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"%s", pPropVal->val.lpwstr);           
            break;

        case CEVT_BLOB:
        case CEVT_PIM_STREAM:   
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"Binary data");
            break;

        //Data type for the POOM OID (ie PIMPR_OID)
        case CEVT_PIM_AUTO_I4:
            hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"0x%x",pPropVal->val.lVal);                                
            break;
      
        default:
             hr = StringCbPrintfW(pszPrintBuffer, cBufferSize, L"Invalid PropType (0x%x)",pPropVal->propid);
             break; 
    }
    
Error:
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      SubscribeToNotifications
//
// Purpose:
//      This function is used to set the level of notification the current process
//      want to get from POOM.  The options include any one of the three values:
//      PIMFOLDERNOTIFICATION_REMOTE, PIMFOLDERNOTIFICATION_LOCAL,
//      or PIMFOLDERNOTIFICATION_ALL
//
// Parameters:
//      pPoom                   - [IN] ptr to POOM app.
//      olItemType              - [IN] Item type.
//      uiNotificationsType     - [IN] Type of notification, remote or local?
//
// Returns:
//      An HRESULT
//
HRESULT SubscribeToNotifications(IPOutlookApp2 *pPoom, int olItemType, uint uiNotificationsType)
{
    HRESULT     hr          = 0;
    IFolder     *pFolder    = NULL;
    IItem       *pItem      = NULL;
    CEPROPVAL   propval     = {0};

    // Parameter check
    CBR(NULL != pPoom);
    if(!uiNotificationsType)
    {
        CHR(E_INVALIDARG);
    }

    // Get the folder for the item type.
    hr = pPoom->GetDefaultFolder(ItemTypeToFolder(olItemType), &pFolder);
    CHR(hr);
    CBR(NULL != pFolder);
    
    hr = pFolder->QueryInterface(IID_IItem, (LPVOID*)&pItem);
    CHR(hr);
    CBR(NULL != pItem);

    // Set the props on the folder.
    propval.propid      = PIMPR_FOLDERNOTIFICATIONS;
    propval.val.ulVal   = uiNotificationsType;
    hr = pItem->SetProps(0, 1, &propval);
    CHR(hr);
        
Error:
    RELEASE_OBJ(pItem);
    RELEASE_OBJ(pFolder);
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      InitPOOM2
//
// Purpose:
//      Initilizes COM, creates the POOM COM object and calls Logon.
//
// Parameters:
//      void
//
// Returns:
//      An HRESULT
//
HRESULT InitPOOM2()
{
    HRESULT hr = S_OK;
    
    CHR(CoInitializeEx(NULL, 0));
      
    hr = CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, 
        IID_IPOutlookApp2, (LPVOID *) &g_polApp);
    CHR(hr);
    CBR(NULL != g_polApp);

Error:        
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      UnInitPOOM2
//
// Purpose:
//      Does a logoff on POOM, and un-initilazize COM.
//
// Parameters:
//      void
//
// Returns:
//      An HRESULT
//
HRESULT UnInitPOOM2()
{
    HRESULT hr = S_OK;

    // Lets release the global ptr
    RELEASE_OBJ(g_pCol);
    
    CBR(g_polApp != NULL);

    // This logoff is for safety. (if its already logged off, S_FALSE will get returned)
    hr = g_polApp->Logoff();
    
Error:    
    RELEASE_OBJ(g_polApp);    
    CoUninitialize();   
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      ShowHR
//
// Purpose:
//      Used to display a message box to the user with the HRESULT value in hex.
//  
// Parameters:
//      hr  - HResult value to print
//
// Returns:
//      Nothing
//
void ShowHR(HRESULT hr)
{
    TCHAR szMsg[MAX_LOADSTRING];

    hr = StringCchPrintf(szMsg, ARRAYSIZE(szMsg), _T("HR = 0x%x"), hr);
    MessageBox(g_hWnd, szMsg, L"HRESULT", MB_OK);

    return;        
}


///////////////////////////////////////////////////////////////////////////////
// Function:
//      FindPreviousInstance
//  
// Purpose:
//      Looks for prev. instance of an app. If found, prev. instance is activated.
//
// Parameters:
//      phMutex         - [OUT] will contain mutex handle, can be NULL.
//      pwszClass       - [IN]  class name.
//      pwszTitle       - [IN]  window title.
//      phWnd           - [OUT] will contain previous window handle, if any.
//      pfFound         - [OUT] will be TRUE if there is a previous instance.
//      fActivateWindow - [IN]  TRUE causes the found instance to be the forground window.
//
// Returns:
//      An HRESULT
//
HRESULT FindPreviousInstance(const TCHAR *pwszClass,
                 const TCHAR *pwszTitle,
                 HANDLE *phMutex,
                 HWND *phWnd,
                 BOOL *pfFound,
                 BOOL fActivateWindow)
{
    BOOL    fFound          = FALSE;
    BOOL    fAlreadyExists  = FALSE;
    HRESULT hr              = S_OK;
    HANDLE  hMutex          = NULL;
    HWND    hwnd            = NULL;
    int     iTries          = c_iPrevInstTries;

    if((NULL == phWnd) || (NULL == pfFound))
    {
        return E_INVALIDARG;
    }


    do
    {
        // 2nd param FALSE means don't own the object.
        hMutex = CreateMutex(NULL, FALSE, pwszClass);     
        CBR(INVALID_HANDLE_VALUE != hMutex);

        fAlreadyExists = (GetLastError() == ERROR_ALREADY_EXISTS);

        if (fAlreadyExists)
        {
            // This instance isn't going to run, so decrement the
            // count on the object.
            CloseHandle(hMutex);
            hMutex = NULL;

            hwnd = FindWindow(pwszClass, pwszTitle);
            fFound = (hwnd != NULL);

            if (fFound && fActivateWindow && hwnd)
            {
                // Setting previous instance to foreground.
                SetForegroundWindow ((HWND)(((DWORD) hwnd) | 0x01));
            }
            else
            {
                // It's possible that the other window is in the
                // process of being created.  Sleep and then try
                // again.  Yes, we will sleep unnecessarily the last
                // time through this loop if we iterate
                // c_iPrevInstTries times.  It seems an unlikely case,
                // we're going to report an error, and the penalty as
                // a percent of the delay already experienced at that
                // point doesn't seem too bad.
                Sleep(c_iWindowCreationLatency);
            }
        }
    }
    // If we didn't find a previous inst window, it's possible that
    // the app isn't COMING UP, but rather is GOING DOWN.  Let's try
    // grabbing that fiesty mutex again.
    while (fAlreadyExists && !fFound && (--iTries > 0));  // end do while ()

    // Either the mutex shouldn't have already existed (no prev inst),
    // or we need to have found the hwnd.
    CBR(!fAlreadyExists || fFound);

Error:
    if (NULL == phMutex) 
    {
        // Caller does not need the mutex => close it
        if (NULL != hMutex)
        {
            CloseHandle(hMutex);
        }
    }
    else
    {
        // Return mutex to caller
        *phMutex = hMutex;
    }
    
    *phWnd      = hwnd;
    *pfFound    = fFound;
    
    return hr;
}

