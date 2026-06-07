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
#include <windows.h>
#include <objbase.h>
#include <commctrl.h>
#include <initguid.h>        // init POOM COM obj - this way we don't need to statically link
#include <aygshell.h>
#include "resource.h"
#include <pimstore.h>
#include "macros.h"

#define MAX_LOADSTRING  255
#define PARENT          0
#define OID             1
#define SUBJECT         2
#define PROP_ARRAY_SIZE 3

// consts
const LPWSTR cszClassName      = TEXT("Dialog");
const LPWSTR cszWndName        = TEXT("TaskTree");
const LPWSTR cszParent      = TEXT("Parent");
const LPWSTR cszOID         = TEXT("OID");
const LPWSTR cszSubject     = TEXT("Subject");
const LPWSTR cszNoParent    = TEXT("No parent");

// Global Variables
static      HINSTANCE       g_hInst                       = 0;    // instance handle
static      HWND            g_hWnd                        = 0;    // handle to the app window
static      IPOutlookApp2   *g_polApp                     = NULL;   // Declare and initialize a pointer to the IPOutlookApp interface object
static      CEPROPID        g_rgPropIDs[PROP_ARRAY_SIZE]  = {0};    // an array of property IDs for a Task object
static      LPWSTR          g_rgNamedProps[]              =
                            {
                                cszParent,
                                cszOID,
                                cszSubject,
                            }; // an array of named properties for a Task object

// Forward declarations
LRESULT CALLBACK DlgMainProc(HWND, UINT, WPARAM, LPARAM);


// Establishes a POOM session
HRESULT InitPOOM2()
{
    HRESULT hr = S_OK;

    hr = CoInitializeEx(NULL, 0);
    CHR(hr);

    hr = CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, IID_IPOutlookApp2, (LPVOID *) &g_polApp);
    CHR(hr);

Error:
    return hr;
}

HRESULT DeInitPOOM2(void)
{
    HRESULT hr = S_OK;

    CBR(g_polApp != NULL);

    // This logoff is for safety.  (We may have already logged off, but it shouldn't matter do it again anyways.)
    hr = g_polApp->Logoff();

Error:
    RELEASE_OBJ(g_polApp);
    CoUninitialize();
    return hr;
}

void ShowHR(HRESULT hr)
{
    TCHAR tszMsg[MAX_LOADSTRING] = {0};

    //we are not checking if the string gets truncated
    //because hr is a 32-bit value and the array buffer size is 255 8/16-bit chars
    StringCchPrintf(tszMsg, ARRAYSIZE(tszMsg), _T("HR = 0x%x"),hr);
    MessageBox(g_hWnd, tszMsg, _T("HRESULT"), MB_OK);
}

///////////////////////////////////////////////////////////////////////////////
// InitApp
//
//  Initializes the application
//
//  Arguments:
//      [IN] HINSTANCE hInstance - instance handle
//      [IN] WNDCLASS *lpWndClass - a pointer to the window class
//
//  Return Values:
//      int - 0 on success, -1 if Failed to register class
//
HRESULT InitApp( HINSTANCE hInstance, WNDCLASS *lpWndClass)
{
    HRESULT hr   = S_OK;
    HWND    hWnd = FindWindow (cszClassName, cszWndName); // Allow only one instance

    // Check parameters
    CPR(lpWndClass);
    CBR(hInstance != NULL);

    if (hWnd)
    {
        SetForegroundWindow(hWnd);
        hr = E_FAIL;
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
    lpWndClass->lpszClassName        = cszClassName;

    if ( RegisterClass (lpWndClass) == 0 )
    {
        DWORD dwError = GetLastError();
        if(dwError != ERROR_CLASS_ALREADY_EXISTS)
        {
            RETAILMSG(TRUE, (L"%s: Failed to register class. Error = 0x%x", dwError));
            hr = E_FAIL;
            goto Error;
        }
    }
Error:
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// InitInstance
//
//  Initializes the TASKTREE dialog
//
//  Arguments:
//      [IN] HINSTANCE hInstance - instance handle
//      [IN] int nCmdShow - state in which the dialog should first appear
//
//  Return Values:
//      BOOL - TRUE on success, FALSE if Failed to initialize
//
BOOL InitInstance(HINSTANCE hInstance)
{
    g_hInst = hInstance;// Store instance handle in our global variable

    if( DialogBox(g_hInst, MAKEINTRESOURCE(IDD_TASKTREE), NULL, (DLGPROC)DlgMainProc) < 0)
    {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// WinMain
//
//  Windows program entry point
//
//  Arguments:
//      [IN] HINSTANCE hInstance - instance handle of the program
//      [IN] HINSTANCE hPrevInstance - always 0
//      [IN] LPTSTR lpCmdLine - pointer to a string containing command line parameters passed to the program
//      [IN] int nCmdShow - state in which the dialog should first appear
//
//  Return Values:
//      int - 0 on success, -1 if Failed to register class
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG                  msg;
    WNDCLASS             wc;
    int                  rc    = 0;
    BOOL                 bRet;
    HRESULT              hr    = S_OK;
    BOOL                 br    = FALSE;
    INITCOMMONCONTROLSEX icex; // structure that contains information specifying which control classes are registered.

    // Initalize application
    hr = InitApp(hInstance, &wc);
    if(FAILED(hr))
    {
        return -1;
    }

    // Ensure that the common control DLL is loaded.
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_BAR_CLASSES|ICC_LISTVIEW_CLASSES|ICC_TAB_CLASSES|ICC_TREEVIEW_CLASSES|ICC_UPDOWN_CLASS;
    // This function registers specific common controls classes from the common control DLL.
    br = InitCommonControlsEx(&icex);
    CBR(br);

    // Init POOM
    hr = InitPOOM2();
    CHR(hr);

    // Perform application initialization:
    br = InitInstance (hInstance);
    CBR(br);

    // Main message loop
    while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    {
        if (bRet == -1)
        {
            goto Error;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


Error:
    DeInitPOOM2();
    UnregisterClass( wc.lpszClassName, wc.hInstance);
    if(FAILED(hr))
    {
        return -1;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// InitSKMenu
//
//  Initializes softkey toolbar
//
//  Arguments:
//      [IN] HWND hDlg - window handle of the dialog
//      [IN] UINT nToolBarId - tooldbar ID
//
//  Return Values:
//      HRESULT - S_OK if toolbar initialization was successful, S_FAIL otherwise, or E_INVALIDARG
//
HRESULT InitSKMenu(HWND hDlg, UINT nToolBarId)
{
    HRESULT       hr    = S_OK;
    SHMENUBARINFO mbi   = {0};
    SHINITDLGINFO shidi = {0};
    BOOL          br    = FALSE;

    mbi.cbSize     = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hDlg;
    mbi.nToolBarId = nToolBarId;
    mbi.hInstRes   = g_hInst;

    br = SHCreateMenuBar(&mbi);
    CBR(br);

    shidi.dwMask  = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
    shidi.hDlg    = hDlg;

    br = SHInitDialog(&shidi);
    CBR(br);

Error:
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// InitProps
//
//  Initialize property IDs for a PIM item and create a custom property Parent
//
//  Arguments:
//      [IN] HWND hDlg - window handle of the dialog
//      [IN] UINT nToolBarId - tooldbar ID
//
//  Return Values:
//      HRESULT - S_OK if toolbar initialization was successful, S_FAIL otherwise
//
HRESULT InitProps(void)
{
    HRESULT hr          = E_FAIL;
    LPCWSTR rgTemp[1]   = {cszParent};

    CBR(g_polApp != NULL);

    //Creates a parent property
    hr = g_polApp->GetIDsFromNames(1, rgTemp,
                                    PIM_CREATE | CEVT_I4, g_rgPropIDs);

    CHR(hr);
    g_rgPropIDs[OID]     = PIMPR_OID;
    g_rgPropIDs[SUBJECT] = PIMPR_SUBJECT;

Error:
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetItemByID
//
//  Find an item in a tree by OID
//
//  Arguments:
//      [IN] HTREEITEM hItem - poinyrt to the item in the tree to start searching from
//      [IN] long nID - OID for which to search
//
//  Return Values:
//      HTREEITEM - a pointer to the item if it was found, otherwise NULL
//
HTREEITEM GetItemByID(HTREEITEM hItem,long nID)
{
    HWND hwndTV = GetDlgItem(g_hWnd,IDC_TREE_VIEW);
    HTREEITEM hItemFound, hItemChild;
    int itemFound = -1;

    // If hItem is NULL, start search from root item.
    if (hItem == NULL)
    {
        hItem = (HTREEITEM)SendMessage(hwndTV, TVM_GETNEXTITEM,
                                       TVGN_ROOT, 0);
    }
    while (hItem != NULL)
    {
        long nItemID = -1;
        TVITEM item;

        item.hItem = hItem;
        item.mask = TVIF_PARAM | TVIF_CHILDREN; // item attributes we want to retreive

        if(FALSE == SendMessage(hwndTV, TVM_GETITEM, 0, (LPARAM)&item)) // retreive item with the specified attribs
        {
            break;
        }

        nItemID = item.lParam;

        // Did we find it?
        if (nID == nItemID)
        {
            itemFound = 0;
            break;
        }

        // Check whether we have child items.
        if (item.cChildren > 0)
        {
            // Recursively traverse child items.

            // hItemChild will never turn out to be NULL
            // because we can only hit this code if we know
            // for sure that there is at least one child
            hItemChild = (HTREEITEM)SendMessage(hwndTV, TVM_GETNEXTITEM,
                                                TVGN_CHILD, (LPARAM)hItem);
            hItemFound = GetItemByID(hItemChild, nID);

            // Did we find it?
            if (hItemFound != NULL)
            {
                itemFound = 1;
                break;
            }
        }

        // Go to next sibling item.
        hItem = (HTREEITEM)SendMessage(hwndTV, TVM_GETNEXTITEM,
                                       TVGN_NEXT, (LPARAM)hItem);
    }
Exit:
    if(itemFound == 0)
    {
        return hItem;
    }
    else if(itemFound == 1)
    {
        return hItemFound;
    }
    else
    {
        // Not found.
        return NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// AddItemToTree
//
//  Insert item into a tree
//
//  Arguments:
//      [IN] LPWSTR lpszItem - subject of the item to add
//      [IN] long  nInsertID - OID of the item to add
//      [IN] long  nParentID - OID of the item's parent
//
//  Return Values:
//      HTREEITEM - a pointer to the newly inserted item or NULL
//
HRESULT AddItemToTree(LPWSTR lpszSubject, long  nInsertID, long nParentID)
{
    HWND           hwndTV    = GetDlgItem(g_hWnd, IDC_TREE_VIEW);
    TVITEM         tvi       = {0};
    TVINSERTSTRUCT tvins     = {0};
    static         HTREEITEM hPrev = (HTREEITEM)TVI_FIRST;
    static         HTREEITEM hPrevRootItem = NULL;
    HRESULT        hr        = S_OK;

    // make sure lpszItem is not null
    CBR(lpszSubject != NULL);

    tvi.mask = TVIF_TEXT | TVIF_IMAGE
               | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    // Set the text of the item.
    //It is safe to cast WSTR to TSTR because Windows CE only uses Unicode
    tvi.pszText    = (LPTSTR) lpszSubject;
    tvi.cchTextMax = ARRAYSIZE(tvi.pszText);

    // Save the item's unique ID in the item's application-defined
    // data area.
    tvi.lParam         = (LPARAM)nInsertID;
    tvins.item         = tvi;
    tvins.hInsertAfter = hPrev;

    // Set the parent item based on nParentID.
    // if GetItemByID returns NULL, then the item is inserted at the root
    hPrevRootItem = GetItemByID(NULL, nParentID);
    tvins.hParent = hPrevRootItem;

    // Add the item to the tree-view control.
    hPrev = (HTREEITEM)SendMessage(hwndTV,
                                   TVM_INSERTITEM,
                                   0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins);
    hr = S_OK;
Error:
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// CreateNewTask
//
//  Create a Task given subject and parent ID
//
//  Arguments:
//      [IN] LPWSTR subject - subject of the item to add
//      [IN] long   nParentID - OID of the item's parent
//
//  Return Values:
//      IItem* - a pointer to the newly created IITem object (Task)
//
HRESULT CreateNewTask(LPWSTR pszSubject, long nParentID, IItem **ppItem)
{
    HRESULT      hr                         = E_FAIL;
    IDispatch *  pDisp                      = NULL;
    IItem     *  pItem                      = NULL;
    CEPROPVAL    rgPropval[PROP_ARRAY_SIZE] = {0};

    // make sure subject is not null
    CPR(pszSubject);
    CPR(ppItem);

    CBR(g_polApp != NULL);

    // create a new item
    hr = g_polApp->CreateItem(olTaskItem, &pDisp);
    CHR(hr);
    CPR(pDisp);

    // get the IItem interface the newly created item
    hr = pDisp->QueryInterface(IID_IItem, (LPVOID*)&pItem);
    CHR(hr);
    CPR(pItem);

    // set the itm props
    for(int i = 0; i < PROP_ARRAY_SIZE; i++)
    {
        rgPropval[i].propid = g_rgPropIDs[i];
    }

    rgPropval[PARENT].val.lVal    = nParentID;
    rgPropval[OID].val.lVal       = 0;
    rgPropval[SUBJECT].val.lpwstr = pszSubject;

    hr = pItem->SetProps(0, PROP_ARRAY_SIZE, rgPropval);
    CHR(hr);

    hr = pItem->Save();
    CHR(hr);

    *ppItem = pItem;
Error:
    RELEASE_OBJ(pDisp);
    if(FAILED(hr))
    {
         RELEASE_OBJ(pItem);
    }

    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// AddNewTaskToTree
//
//  Update tree view with the new task
//
//  Arguments:
//      [IN] IItem *pItem - a Task to add to the tree-view
//
//  Return Values:
//      HRESULT - S_OK if created succesfully, S_FAIL - otherwise
//
HRESULT AddNewTaskToTree(IItem *pItem)
{
    HRESULT     hr        = S_OK;
    CEPROPVAL * pPropVals = NULL;
    HANDLE      hHeap     = GetProcessHeap();
    ULONG       cbBuffer  = 0;

    // make sure pItem is not null
    CPR(pItem);

    hr = pItem->GetProps(g_rgPropIDs, CEDB_ALLOWREALLOC, ARRAYSIZE(g_rgPropIDs), &pPropVals, &cbBuffer, hHeap);
    CHR(hr);
    CPR(pPropVals);
    // now that we have prop values for a specific item call AddItemToTree
    hr = AddItemToTree(pPropVals[SUBJECT].val.lpwstr,  // subject
                  pPropVals[OID].val.lVal ,   // OID
                  pPropVals[PARENT].val.lVal);   // parent

    CHR(hr);

Error:
    HEAP_FREE(hHeap, pPropVals);

    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// InitListBox
//
//  Append a list drop-down box with a subject and an OID associated with it
//
//  Arguments:
//      [IN] LPWSTR subject - a Task subject to add to the list drop-down menu
//      [IN] long OID - an ID of the Task
//  Return Values:
//      HRESULT - S_OK if created succesfully, S_FAIL - otherwise
HRESULT InitListBox(LPWSTR pszSubject, long lOID)
{
    HRESULT hr   = S_OK;
    HWND    hwnd = ::GetDlgItem(g_hWnd, IDC_PARENT);

    // adds a subject of an existing task to the list drop-down
    int idx = (int)SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)pszSubject);
    CBR(idx >= 0);
    // associates OID with the list item
    SendMessage(hwnd, CB_SETITEMDATA, idx, (LPARAM)lOID);
Error:
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetNewTaskParent
//
//  Get an OID of the parent task from the combobox
//
//  Arguments:
//      None
//
//  Return Values:
//      long oid - an oid asso
long GetNewTaskParent()
{
    HWND hwnd = ::GetDlgItem(g_hWnd, IDC_PARENT);

    // retreives an index of the currently selected item
    int idx = (int)SendMessage(hwnd, CB_GETCURSEL, 0, 0);

    // retreives data associated with this list item
    long oid = SendMessage(hwnd, CB_GETITEMDATA, idx, 0);

    return oid;
}

///////////////////////////////////////////////////////////////////////////////
// RefreshItems
//
//  Refreshes the entire TaskTree dialog
//  Loops through a collection of tasks and uppends them
//  to the tree and list controls
//
//  Arguments:
//      None
//
//  Return Values:
//      HRESULT - S_OK if refreshed succesfully, S_FAIL - otherwise
HRESULT RefreshItems(void)
{
    HRESULT hr     = S_OK;
    HWND    hwndTV = GetDlgItem(g_hWnd, IDC_TREE_VIEW);

    // declare a reference to a generic PIM item collection
    IPOutlookItemCollection *   pItems;
    IDispatch               *   pDisp   = NULL;
    IItem                   *   pItem   = NULL;

    // declare a reference to a generic PIM item folder
    IFolder   *  pFolder   = NULL;
    int          cItems    = 0;             // count of items in the Task collection
    CEPROPVAL *  pPropVals = NULL;
    HANDLE       hHeap     = GetProcessHeap();
    ULONG        cbBuffer  = 0;

    // reset content of the tree structure
    CBR(TreeView_DeleteAllItems(hwndTV));

    // reset content of the list box
    SendMessage(::GetDlgItem(g_hWnd, IDC_PARENT), CB_RESETCONTENT , 0, 0);

    CBR(g_polApp != NULL);

    // Use the generic PIM item folder to get the Tasks folder
    hr = g_polApp->GetDefaultFolder(olFolderTasks, &pFolder);
    CHR(hr);
    CPR(pFolder);

    // Use the Tasks folder to get the collection of Task items
    hr = pFolder->get_Items(&pItems);
    CHR(hr);
    CPR(pItems);

    // sort collection by OID in ascending order so that we don't
    // try to create children before their parents
    hr = pItems->Sort(_T("[OID]"), FALSE);
    CHR(hr);

    // Get the count of Items in the pItems collection
    hr = pItems->get_Count(&cItems);
    CHR(hr);

    // loop through task items and populate drop-down list and tree view
    for(int i = 1; i < (cItems + 1); i++)
    {
        hr = pItems->Item(i, (IDispatch **) &pDisp);
        CHR(hr);
        CPR(pDisp);

        hr = pDisp->QueryInterface(IID_IItem, (LPVOID*)&pItem);
        CHR(hr);
        CPR(pItem);

        cbBuffer = 0;
        hr = pItem->GetProps(g_rgPropIDs, CEDB_ALLOWREALLOC, ARRAYSIZE(g_rgPropIDs), &pPropVals, &cbBuffer, hHeap);
        CHR(hr);
        CPR(pPropVals);

        // populate the list box with tasks
        hr = InitListBox(pPropVals[SUBJECT].val.lpwstr,     // subject
                    pPropVals[OID].val.lVal);               // OID
        CHR(hr);

        // now that we have prop values for a specific item call AddItemToTree
        hr = AddItemToTree(pPropVals[SUBJECT].val.lpwstr, pPropVals[OID].val.lVal , pPropVals[PARENT].val.lVal);
        CHR(hr);

        HEAP_FREE(hHeap, pPropVals);
        RELEASE_OBJ(pItem);
        RELEASE_OBJ(pDisp);
    }

    // this is for the case when we want to create a task without a parent
    hr = InitListBox(cszNoParent, 0);
    CHR(hr);

Error:
    HEAP_FREE(hHeap, pPropVals);
    RELEASE_OBJ(pItem);
    RELEASE_OBJ(pFolder);
    RELEASE_OBJ(pDisp);
    RELEASE_OBJ(pItems);

    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ProcessMainMenu
//
//  Interprets main menu commands
//
//  Arguments:
//      [IN] HWND hDlg - handle to the wondow dialog
//      [IN] WORD wLo - command sent to the main menu
//
//  Return Values:
//      HRESULT - S_OK if success, S_FAIL - otherwise
HRESULT ProcessMainMenu(HWND hDlg, WORD wLo)
{
    HRESULT   hr                          = S_OK;
    WCHAR     pszSubject[MAX_LOADSTRING];
    IItem   * pItem                       = NULL;
    long      lOID                        = 0;

    switch(wLo)
    {
        case IDOK: // for the foo button
        case IDM_EXIT:
            DestroyWindow (hDlg);
            PostQuitMessage(0);
            break;

        case IDM_ACTION_REFRESH:
            RefreshItems();
            break;

        case IDM_ACTION_NEW_TASK:
            // retreive contents of the subject and parent controls
            GetDlgItemText(g_hWnd, IDC_NEW_SUBJECT, pszSubject, ARRAYSIZE(pszSubject));

            // call create new task
            hr = CreateNewTask(pszSubject, GetNewTaskParent(), &pItem);
            CHR(hr);
            CPR(pItem);

            // append it to the tree
            hr = AddNewTaskToTree(pItem);
            CHR(hr);

            // append it to the list drop-down
            hr = pItem->get_Oid(&lOID);
            CHR(hr);

            //populate the list
            hr = InitListBox(pszSubject, lOID);
            CHR(hr);

            break;
    }
Error:
    RELEASE_OBJ(pItem);
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// DlgMainProc
//
//  Interprets main menu commands
//
//  Arguments:
//      [IN] HWND hDlg - handle of the window that receives the message
//      [IN] UINT message - message identifier
//      [IN] WPARAM wParam - data that come with the message
//      [IN] LPARAM lParam - data that come with the message
//
//  Return Values:
//      LRESULT
LRESULT CALLBACK DlgMainProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr      =   S_OK;

    switch(message)
    {
        case WM_CLOSE:
            EndDialog(hDlg,0);
            DestroyWindow (hDlg);
            break;

        case WM_DESTROY:
            hr = g_polApp->Logoff();
            PostQuitMessage(0);
            break;

        case WM_INITDIALOG:
            g_hWnd  = hDlg;
            hr = g_polApp->Logon((long)g_hWnd);
            CHR(hr);

            InitSKMenu(hDlg, ID_BTNBARRES);

            SetDlgItemText(hDlg, IDC_NEW_SUBJECT, TEXT("Tap here to add a new task"));

            // Initialize property IDs for a PIM item and create a custom property Parent
            hr = InitProps();
            CHR(hr);
            RefreshItems();
            UpdateWindow(hDlg);
            break;

        case WM_COMMAND:
            ProcessMainMenu(hDlg, LOWORD(wParam));
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