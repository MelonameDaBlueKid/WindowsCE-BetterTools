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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// MAILSET.CPP
//
// Allows you to set properties on stores
//


#include <windows.h>
#include "cemapi.h"
#include "mapiutil.h"
#include "resource.h"
#include "macros.h"
#include "aygshell.h"
#include "msxml.h"
#include "tpcshell.h"

// Different types that we recognize from the XML:
//   0 = String
//   1 = Integer
//   2 = Boolean
typedef enum
{
    vtNone,
    vtInteger,
    vtBoolean,
    vtString
} VALUETYPE;


// Structure to hold information about a store property
//   pwszPropertyName - The name of the property (e.g. PR_CE_SIGNATURE)
//   ulPropTag - The numeric value of this property
//   pwszDisplayName - A friendly description of this property
//   pwszDefault - The default value to use if this property isn't in the store
//   vt - The type of property
//   pStore - A pointer to the store being modified or queried
typedef struct tagSTOREINFO
{
    TCHAR *pwszPropertyName;
    ULONG ulPropTag;
    TCHAR *pwszDisplayName;
    TCHAR *pwszDefault;
    VALUETYPE vt;
    IMsgStore *pStore;
} STOREINFO;

// XML Filename
const TCHAR *kszXMLFileName = TEXT("mailset.xml");

// Node names used in the XML
const TCHAR *kszMailSetNode = TEXT("mailset");
const TCHAR *kszStoreNode = TEXT("store");

// Attribute names used in the XML
const TCHAR *kszDisplay = TEXT("display");
const TCHAR *kszDefault = TEXT("default");
const TCHAR *kszType = TEXT("type");
const TCHAR *kszPropTag = TEXT("proptag");
const TCHAR *kszPropName = TEXT("propname");

// Globals
HINSTANCE g_hInst;



///////////////////////////////////////////////////////////////////////////////
//
// PathFindFileName
//
// Searches a path for a file name
//
// pszPath: IN parameter pointing to a null-terminated string that contains the path to search.
//
// Returns a pointer to the address of the string if successful, or a pointer to the beginning of the path otherwise.
//

LPTSTR PathFindFileName(LPCTSTR pszPath)
{
    UINT ichCurrent;
    const TCHAR *pch;

    ichCurrent = 0;
    pch = &pszPath[0];

    // Iterate through the entire string
    while (pszPath[ichCurrent])
    {
        // filename only if char after '\' is not end of path or another '\'
        if (pszPath[ichCurrent] == TEXT('\\') &&
            pszPath[ichCurrent + 1] &&
            pszPath[ichCurrent + 1] != TEXT('\\'))
        {
            pch = &pszPath[ichCurrent + 1];
        }
        ichCurrent++;
    }

    return (TCHAR*)pch;
}


///////////////////////////////////////////////////////////////////////////////
//
// GetXMLPathName
//
// Generate the XML PathName based on the current app directoy and a predefined XML filename
// 
// pszPath: IN parameter pointing to a buffer to hold the pathname of the xml file
// cMaxPath: IN parameter to the length of the buffer
//
// Returns BOOL
//

BOOL GetXMLPathName(LPTSTR pszPath, UINT cMaxPath)
{
    TCHAR *pszFileName;
    BOOL fSuccess;
    HRESULT hr;
    DWORD cch;

    ZeroMemory(pszPath, cMaxPath);

    // Assume failure until all steps are done
    fSuccess = FALSE;
    
    // Get the pathname of the exe
    cch = GetModuleFileName(NULL, pszPath, cMaxPath);
    CBR(cch != 0);

    // Get the directory that the exe is running from
    // pszFileName should not point to pszPath, if so it means the filename of the exe cannot be found; pszPath is invalid
    pszFileName = PathFindFileName(pszPath);
    CBR(pszFileName != pszPath);
        
    // Generate the pathname of the XML file
    *pszFileName = NULL;
    hr = StringCchCat(pszPath, cMaxPath, kszXMLFileName);
    CHR(hr);

    // All steps successful
    fSuccess = TRUE;

Error:
    return fSuccess;
}


///////////////////////////////////////////////////////////////////////////////
//
// FreeStores
//
// Frees the store pointers associated with the spinner
// 
// hwndSpinner: IN parameter containing the window handle to the spinner that has the store names
//
// Returns HRESULT
//

HRESULT FreeStores(HWND hwndSpinner)
{
    HRESULT hr = S_OK;
    IMsgStore *pStore;
    UINT cSpinner;
    UINT i;

    // Loop through each element in the spinner
    cSpinner = SendMessage(hwndSpinner, LB_GETCOUNT, 0, 0);
    for (i = 0; i < cSpinner; i++)
    {
        // The ITEMDATA is a pointer to the store (see AddStoreOptions)
        pStore = (IMsgStore *) SendMessage(hwndSpinner, LB_GETITEMDATA, i, 0);
        RELEASE_OBJ(pStore)
    }
    
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//
// FreeStoreOptions
//
// Frees the STOREINFO associated with the spinner
// 
// hwndSpinner: IN parameter containing the window handle to the spinner that has the STOREINFO
//
// Returns HRESULT
//

HRESULT FreeStoreOptions(HWND hwndSpinner)
{
    HRESULT hr = S_OK;
    UINT cSpinner;
    UINT i;
    STOREINFO *psi;

    // Loop through each element in the spinner
    cSpinner = SendMessage(hwndSpinner, LB_GETCOUNT, 0, 0);
    for (i = 0; i < cSpinner; i++)
    {
        // Get the STOREINFO and free memory in this structure (see AddStoreOptions)
        psi = (STOREINFO *) SendMessage(hwndSpinner, LB_GETITEMDATA, i, 0);
        delete [] psi->pwszPropertyName;
        delete [] psi->pwszDisplayName;
        delete [] psi->pwszDefault;
        delete psi;
    }

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//
// ReadNodeType
//
// This function will read in a type node and return the VALUETYPE corresponding to the node value
// 
// pNodeMap: IN parameter pointing to the node
// pszNodeName : IN parameter indicating the property to retrieve from the XML
//
// Returns VALUETYPE
//

VALUETYPE ReadNodeType(IXMLDOMNamedNodeMap *pNodeMap, TCHAR *pszNodeName)
{
    HRESULT hr;
    IXMLDOMNode *pAttribute = NULL;
    VARIANT vt;
    VALUETYPE vtRet = vtNone;

    // Get the appropriate attribute
    hr = pNodeMap->getNamedItem(pszNodeName, &pAttribute);
    CHR(hr);
    CBR(pAttribute != NULL);

    // Read the value from this attribute
    VariantInit(&vt);
    hr = pAttribute->get_nodeValue(&vt);
    CHR(hr);

    // The string should be 0 (string), 1 (integer), or 2 (boolean)
    // If it's not one of these, the return value will be vtNone
    if (!lstrcmp(vt.bstrVal, TEXT("0")))
    {
        vtRet = vtString;
    }
    else if (!lstrcmp(vt.bstrVal, TEXT("1")))
    {
        vtRet = vtInteger;
    }
    else if (!lstrcmp(vt.bstrVal, TEXT("2")))
    {
        vtRet = vtBoolean;
    }
    
Error:
    RELEASE_OBJ(pAttribute)

    VariantClear(&vt);

    return vtRet;
}


///////////////////////////////////////////////////////////////////////////////
//
// ReadNodeNumber
//
// This function will read in a type node and return the ULONG corresponding to the node value
// 
// pNodeMap: IN parameter pointing to the node
// pszNodeName : IN parameter indicating the property to retrieve from the XML
//
// Returns ULONG
//

ULONG ReadNodeNumber(IXMLDOMNamedNodeMap *pNodeMap, TCHAR *pszNodeName)
{
    HRESULT hr;
    IXMLDOMNode *pAttribute = NULL;
    VARIANT vt;
    ULONG ulRet = 0;

    // Get the appropriate attribute
    hr = pNodeMap->getNamedItem(pszNodeName, &pAttribute);
    CHR(hr);
    CBR(pAttribute != NULL);

    // Read the value of this attribute
    VariantInit(&vt);
    hr = pAttribute->get_nodeValue(&vt);
    CHR(hr);

    // Convert the string to a number
    ulRet = _ttoi(vt.bstrVal);

Error:
    RELEASE_OBJ(pAttribute)

    VariantClear(&vt);

    return ulRet;
}


///////////////////////////////////////////////////////////////////////////////
//
// ReadNodeString
//
// This function will read in a type node and return the string corresponding to the node value
// 
// pNodeMap: IN parameter pointing to the node
// pszNodeName : IN parameter indicating the property to retrieve from the XML
//
// Returns LPTSTR -- the caller must free this string
//

LPTSTR ReadNodeString(IXMLDOMNamedNodeMap *pNodeMap, TCHAR *pszNodeName)
{
    HRESULT hr;
    IXMLDOMNode *pAttribute = NULL;
    VARIANT vt;
    TCHAR *pszRet = NULL;
    size_t cch;
    

    // Get the appropriate attribute
    hr = pNodeMap->getNamedItem(pszNodeName, &pAttribute);
    CHR(hr);
    CBR(pAttribute != NULL);

    // Read the value of this attribute
    VariantInit(&vt);
    hr = pAttribute->get_nodeValue(&vt);
    CHR(hr);

    // Allocate memory and copy it
    hr = StringCchLength(vt.bstrVal, STRSAFE_MAX_CCH, &cch);
    CHR(hr);
    pszRet = new TCHAR[++cch];
    CPR(pszRet);
    StringCchCopy(pszRet, cch, vt.bstrVal);

Error:
    RELEASE_OBJ(pAttribute)

    VariantClear(&vt);

    return pszRet;
}


///////////////////////////////////////////////////////////////////////////////
//
// AddStoreOptions
//
// Reads in an XML document and populates a spinner with the value in that document
// The XML document has the following format:
// 
//     <store proptag="0x811A000B"
//            propname="PR_CE_USE_SIGNATURE"
//            display="Use the account signature"
//            default="0"
//            type="2"/>
//
// See the definition of the STOREINFO structure to see how these attributes map to our
// internal data structure.
// 
// hwndSpinner: IN parameter containing the window handle of the spinner to populate
//
// Returns HRESULT
//

HRESULT AddStoreOptions(HWND hwndSpinner)
{
    HRESULT hr = S_OK;
    STOREINFO *psi = NULL;
    LRESULT lr;
    IXMLDOMDocument *pDOM = NULL;
    IXMLDOMNode *pMailNode = NULL;
    IXMLDOMNode *pNode = NULL;
    IXMLDOMNode *pSibling = NULL;
    IXMLDOMNamedNodeMap *pNodeMap = NULL;
    VARIANT_BOOL fSuccess;
    VARIANT vt;
    TCHAR szPath[MAX_PATH];
    BSTR bstrName = NULL;
    CLSID clsid;
    
    // Load the XML DOM
    hr = CLSIDFromProgID(TEXT("Msxml2.DOMDocument"), &clsid);
    CHR(hr);
    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (LPVOID *) &pDOM);
    CHR(hr);

    // Get the xml pathname
    fSuccess = GetXMLPathName(szPath, MAX_PATH);
    CBR(fSuccess);

    // Load the mailset xml file
    vt.vt = VT_BSTR;
    vt.bstrVal = SysAllocString(szPath);
    hr = pDOM->load(vt, &fSuccess);
    CHR(hr);
    CBR(fSuccess);

    // Find the mailset node
    hr = pDOM->selectSingleNode((TCHAR *) kszMailSetNode, &pMailNode);
    CHR(hr);

    // Walk the children of this node -- each top-level child will be a single store property
    hr = pMailNode->get_firstChild(&pNode);
    CHR(hr);

    while (pNode)
    {
        hr = pNode->get_nodeName(&bstrName);
        CHR(hr);

        // We only care about Store nodes -- skip this node if it's not a store node
        if (!lstrcmpi(bstrName, kszStoreNode))
        {
            // Create a STOREINFO structure.  This will be used to store information
            // about this node in memory.  It will be the ITEMDATA stored with this entry in the spinner
            // and will need to be freed when the spinner is destroyed
            psi = new STOREINFO;
            CPR(psi);
            ZeroMemory(psi, sizeof(STOREINFO));

            // Load in any attributes on this node
            RELEASE_OBJ(pNodeMap)

            hr = pNode->get_attributes(&pNodeMap);
            CHR(hr);

            // Make sure the proptag and property description values are present
            psi->pwszPropertyName = ReadNodeString(pNodeMap, (TCHAR *) kszPropName);
            psi->ulPropTag = ReadNodeNumber(pNodeMap, (TCHAR *) kszPropTag);
            CBR((psi->pwszPropertyName != NULL) && (psi->ulPropTag != 0));

            // Display name and default value are mandatory
            psi->pwszDisplayName = ReadNodeString(pNodeMap, (TCHAR *) kszDisplay);
            CBR(psi->pwszDisplayName != NULL);
            psi->pwszDefault = ReadNodeString(pNodeMap, (TCHAR *) kszDefault);
            CBR(psi->pwszDefault != NULL);

            // Type is mandatory too
            psi->vt = ReadNodeType(pNodeMap, (TCHAR *) kszType);
            CBR(psi->vt != vtNone);
            
            // Now, add this to our spinner
            lr = SendMessage(hwndSpinner, LB_ADDSTRING, 0, (LPARAM) psi->pwszPropertyName);
            CBR(lr >= 0);
            SendMessage(hwndSpinner, LB_SETITEMDATA, lr, (LPARAM) psi);

            // Reset psi to NULL so it isn't freed (owned by spinner now)
            psi = NULL;
        }

        SysFreeString(bstrName);

        // Go to the next top-level node
        hr = pNode->get_nextSibling(&pSibling);
        CHR(hr);
        
        pNode->Release();
        pNode = pSibling;
    }
        
    // Set focus on the first item in the spinner
    SendMessage(hwndSpinner, LB_SETCURSEL, 0, 0);
    
Error:
    if (psi)
    {
        // Free it up
        delete [] psi->pwszPropertyName;
        delete [] psi->pwszDisplayName;
        delete [] psi->pwszDefault;
        delete psi;
    }

    RELEASE_OBJ(pDOM)
    RELEASE_OBJ(pMailNode)
    RELEASE_OBJ(pNode)
    RELEASE_OBJ(pSibling)
    RELEASE_OBJ(pNodeMap)

    VariantClear(&vt);

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//
// EnumerateStore
//
// This function enumerates all the CEMAPI stores and adds them to a spinner
// 
// pSession: IN parameter containing a pointer to the MAPI session
// hwndSpinner: IN parameter containing the window handle of the spin box to populate
//
// Returns HRESULT
//

HRESULT EnumerateStores(IMAPISession *pSession, HWND hwndSpinner)
{
    HRESULT hr;
    LONG lr;
    IMAPITable *pMsgStoresTable = NULL;
    SRowSet *psrs = NULL;
    IMsgStore *pStore = NULL;
    ULONG cValues = 0;
    SPropValue *pspv = NULL;
    SizedSPropTagArray(1, spta) = { 1, PR_DISPLAY_NAME }; 
    
    // Get the message stores table.
    hr = pSession->GetMsgStoresTable(MAPI_UNICODE, &pMsgStoresTable);
    CHR(hr);

    // Enumerate each row in the table
    while (TRUE)
    {
        hr = pMsgStoresTable->QueryRows (1, 0, &psrs);
        CHR(hr);
        
        // Did we hit the end of the table?
        if (psrs->cRows != 1)
        {
            break;
        }
        
        // Open the message store for this service
        hr = pSession->OpenMsgStore (NULL, 
                                       psrs->aRow[0].lpProps[0].Value.bin.cb, 
                                       (ENTRYID *) psrs->aRow[0].lpProps[0].Value.bin.lpb, 
                                       NULL, 
                                       0, 
                                       &pStore);
        CHR(hr);

        // Read in the name of this store
        hr = pStore->GetProps((SPropTagArray *) &spta, MAPI_UNICODE, &cValues, &pspv);
        CHR(hr);
        
        if ((cValues == 1) && (pspv[0].ulPropTag == spta.aulPropTag[0]))
        {
            // Add this string to the dropdown spinner 
            lr = SendMessage(hwndSpinner, LB_ADDSTRING, 0, (LPARAM) pspv[0].Value.lpszW);
            if (lr != -1)
            {
                // We own this store now -- set the pointer to NULL so we don't free it
                SendMessage(hwndSpinner, LB_SETITEMDATA, lr, (LPARAM) pStore);
                pStore = NULL;
            }
        }

        // Free this memory so we can move to the next item in the table
        MAPIFreeBuffer(pspv);
        FreeProws(psrs);  
        psrs = NULL;
        RELEASE_OBJ(pStore)
    }

    // Set focus on the first item in the spinner
    SendMessage(hwndSpinner, LB_SETCURSEL, 0, 0);
    
Error:
    RELEASE_OBJ(pStore)
    RELEASE_OBJ(pMsgStoresTable)
    
    FreeProws(psrs);
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//
// SetPropertyOnStore
//
// This function sets a property on a store
// 
// psi: IN parameter pointing to a STOREINFO structure
// upv: IN parameter holding the property to set
//
// Returns HRESULT
//

HRESULT SetPropertyOnStore(STOREINFO *psi, __UPV upv)
{
    HRESULT hr;
    SPropValue spv = { 0 };

    // Call SetProps on the appropriate store to set this property
    spv.ulPropTag = psi->ulPropTag;
    spv.Value = upv;
    hr = psi->pStore->SetProps(1, &spv, NULL);
    CHR(hr);

Error:
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// LayoutPropControls
//
// Stretch the controls in the edit property dialog
// 
// hDlg: IN parameter containing the window handle of the dialog
//
// No return value
//

void LayoutPropControls(HWND hDlg)
{
    RECT rc;
    RECT rcDlg;
    HWND hwndControl;

    GetWindowRect(hDlg, &rcDlg);

    // Reposition the label describing the property
    hwndControl = GetDlgItem(hDlg, IDC_DISPLAYNAME);
    GetWindowRect(hwndControl, &rc);
    SetWindowPos(hwndControl, NULL, 0, 0, rcDlg.right - (2 * (rc.left - rcDlg.left)), rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    // Reposition the edit box
    hwndControl = GetDlgItem(hDlg, IDC_EDIT);
    GetWindowRect(hwndControl, &rc);
    SetWindowPos(hwndControl, NULL, 0, 0, rcDlg.right - (2 * (rc.left - rcDlg.left)), rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////
//
// LayoutStoreControls
//
// Stretch the controls in the main dialog
// 
// hDlg: IN parameter containing the window handle of the dialog
//
// No return value
//

void LayoutStoreControls(HWND hDlg)
{
    RECT rc;
    RECT rcDlg;
    HWND hwndControl;

    GetWindowRect(hDlg, &rcDlg);

    // Reposition the spinner listing the store names
    hwndControl = GetDlgItem(hDlg, IDC_STORELIST);
    GetWindowRect(hwndControl, &rc);
    SetWindowPos(hwndControl, NULL, 0, 0, rcDlg.right - (5 * (rc.left - rcDlg.left)), rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    // Reposition the spinner listing the properties
    hwndControl = GetDlgItem(hDlg, IDC_LIST);
    GetWindowRect(hwndControl, &rc);
    SetWindowPos(hwndControl, NULL, 0, 0, rcDlg.right - (5 * (rc.left - rcDlg.left)), rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    // Reposition the label describing the properties
    hwndControl = GetDlgItem(hDlg, IDC_DISPLAYNAME);
    GetWindowRect(hwndControl, &rc);
    SetWindowPos(hwndControl, NULL, 0, 0, rcDlg.right - (2 * (rc.left - rcDlg.left)), rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPropertyDescription
//
// Sets the description of a property based on the property currently chosen in the spinner
// 
// hDlg: IN parameter containing the window handle of the dialog
//
// No return value
//

void SetPropertyDescription(HWND hDlg)
{
    UINT i;
    STOREINFO *psi;
    
    // Find the currently selected item in the spinner
    i = SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_GETCURSEL, 0, 0);
    if (i >= 0)
    {
        // Get the STOREINFO for this item and change the description being shown
        psi = (STOREINFO *) SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_GETITEMDATA, i, 0);
        if (psi)
        {
            SetDlgItemText(hDlg, IDC_DISPLAYNAME, psi->pwszDisplayName);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// EditPropProc
//
// Dialog procedure for the Edit Property dialog
// 
// hDlg: IN parameter containing the window handle of the dialog
// msg: IN parameter containing the message
// wParam: IN parameter containing message-specific value
// lParam: IN parameter containing message-specific value
//
// Returns int
//

int WINAPI EditPropProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SHINITDLGINFO shidi;
    SHMENUBARINFO cbi = { 0 };
    static STOREINFO *s_psi;
    TCHAR szValue[MAX_PATH];
    __UPV upv = { 0 };
    ULONG rgTags[] = { 1, 0 };
    ULONG cItems = 0;
    LPSPropValue pid = NULL;
    HRESULT hr = S_OK;

    // Switch based on the message
    switch (msg)
    {
        case WM_INITDIALOG:
            // Make this full-screen
            ZeroMemory(&shidi, sizeof(shidi));

            // Size the dialog correctly
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;
            SHInitDialog(&shidi);

            // Add our menu bar
            cbi.cbSize = sizeof(SHMENUBARINFO);
            cbi.hwndParent = hDlg;
            cbi.nToolBarId = IDR_ENTRY_BUTTONS;
            cbi.hInstRes = g_hInst;
            SHCreateMenuBar(&cbi);

            // Trap the Back key to act as a backspace.
            SendMessage(cbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK,
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

            // Layout the edit control
            LayoutPropControls(hDlg);
            
            // Set information based on the setting info
            s_psi = (STOREINFO *) lParam;
            CBR(s_psi != NULL);

            // What is the current setting on the store (if any)?
            rgTags[1] = s_psi->ulPropTag;
            hr = s_psi->pStore->GetProps((LPSPropTagArray) rgTags, MAPI_UNICODE, &cItems, &pid);          
            if (SUCCEEDED(hr) && (pid[0].ulPropTag == rgTags[1]))
            {
                // Looks like we have something here -- let's use it
                if (s_psi->vt == vtString)
                {
                    StringCchCopy(szValue, MAX_PATH, pid[0].Value.lpszW);
                }
                else if (s_psi->vt == vtBoolean)
                {
                    StringCchPrintf(szValue, MAX_PATH, TEXT("%d"), pid[0].Value.b);
                }
                else if (s_psi->vt == vtInteger)
                {
                    StringCchPrintf(szValue, MAX_PATH, TEXT("%d"), pid[0].Value.l);
                }
            }
            else
            {
                // No current setting -- use the default
                StringCchCopy(szValue, MAX_PATH, s_psi->pwszDefault);
            }

            MAPIFreeBuffer(pid);

            // Set UI elements
            SetWindowText(GetDlgItem(hDlg, IDC_DISPLAYNAME), s_psi->pwszDisplayName);
            SetWindowText(GetDlgItem(hDlg, IDC_EDIT), szValue);
            SendMessage(GetDlgItem(hDlg, IDC_EDIT), EM_LIMITTEXT, 0, ARRAYSIZE(szValue) - 1);
            SetFocus(GetDlgItem(hDlg, IDC_EDIT));
            break;

        case WM_SIZE:
            // Relayout the controls in this dialog in case the dialog changed (e.g. for a screen rotation)
            LayoutPropControls(hDlg);
            break;

        case WM_HOTKEY:
            if (HIWORD(lParam) == VK_TBACK)
            {
                // Sends the backspace to the edit box 
                SHSendBackToFocusWindow(msg, wParam, lParam);
            }
            break;
                
        case WM_COMMAND:
            if (LOWORD(wParam) == IDM_DONE)
            {
                // Set a property on the store based on what they chose
                GetWindowText(GetDlgItem(hDlg, IDC_EDIT), szValue, ARRAYSIZE(szValue));

                // Convert to string, boolean, or integer
                if (s_psi->vt == vtString)
                {
                    upv.lpszW = szValue;
                }
                else if (s_psi->vt == vtBoolean)
                {
                    upv.b = (unsigned short int) _ttoi(szValue);
                }
                else if (s_psi->vt == vtInteger)
                {
                    upv.l = _ttoi(szValue);
                }

                // Now set this property in the store
                SetPropertyOnStore(s_psi, upv);

                // And close the dialog
                EndDialog(hDlg, 0);
            }
            break;

        default:
            break;
    }

Error:
    if (FAILED(hr) && (msg == WM_INITDIALOG))
    {
        EndDialog(hDlg, -1);
    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// MainDlgProc
//
// Dialog procedure for the main dialog proc
// 
// hDlg: IN parameter containing the window handle of the dialog
// msg: IN parameter containing the message
// wParam: IN parameter containing message-specific value
// lParam: IN parameter containing message-specific value
//
// Returns int
//

int WINAPI MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr = S_OK;
    static IMAPISession *pSession;
    SHINITDLGINFO shidi;
    UINT i;
    STOREINFO *psi;
    SHMENUBARINFO cbi = { 0 };
    
    switch (msg)
    {
        case WM_INITDIALOG:
            // Size the dialog correctly
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;
            SHInitDialog(&shidi);

            // Add our menu bar
            cbi.cbSize = sizeof(SHMENUBARINFO);
            cbi.hwndParent = hDlg;
            cbi.nToolBarId = IDR_MAIN_BUTTONS;
            cbi.hInstRes = g_hInst;
            SHCreateMenuBar(&cbi);
            
            // Layout the controls nicely
            LayoutStoreControls(hDlg);
            
            // Logon to MAPI
            hr = MAPILogonEx(0, NULL, NULL, 0, &pSession);
            CHR(hr);
            
            // Enumerate available stores and add them to the spinner
            hr = EnumerateStores(pSession, GetDlgItem(hDlg, IDC_STORELIST));
            CHR(hr);
            
            // Now enumerate store-specific XML options that are available
            hr = AddStoreOptions(GetDlgItem(hDlg, IDC_LIST));
            CHR(hr);

            // Set the label to the currently selected item
            SetPropertyDescription(hDlg);
            break;

        case WM_SIZE:
            // Relayout the controls
            LayoutStoreControls(hDlg);
            break;
            
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                // Hit the backspace key
                case IDCANCEL:
                    // Deliberate fall through
                    
                // Hit the done Softkey
                case IDM_DONE:
                    EndDialog(hDlg, 0);
                    break;

                // If the selection in the spinner changed, update the property description underneath it
                case IDC_LIST:
                    if (HIWORD(wParam) == LBN_SELCHANGE)
                    {
                        SetPropertyDescription(hDlg);
                    }
                    break;

                // Bring up a dialog based on the type of the item which is selected in the spinner
                case IDM_CHANGE:
                    // Get the current selection
                    i = SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_GETCURSEL, 0, 0);
                    if (i >= 0)
                    {
                        psi = (STOREINFO *) SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_GETITEMDATA, i, 0);
                        if (psi)
                        {
                            // Determine which store is selected
                            i = SendMessage(GetDlgItem(hDlg, IDC_STORELIST), LB_GETCURSEL, 0, 0);
                            if (i >= 0)
                            {
                                psi->pStore = (IMsgStore *) SendMessage(GetDlgItem(hDlg, IDC_STORELIST), LB_GETITEMDATA, i, 0);
                                if (psi->pStore)
                                {
                                    // Bring up the entry dialog
                                    DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_ENTRY), hDlg, EditPropProc, (LPARAM) psi);
                                }
                            }
                        }
                    }
                    break;
            }
            break;

        case WM_DESTROY:
            // Delete stores off the spin box
            FreeStores(GetDlgItem(hDlg, IDC_STORELIST));
            FreeStoreOptions(GetDlgItem(hDlg, IDC_LIST));

            RELEASE_OBJ(pSession)
            break;
    }

Error:
    if (FAILED(hr) && (msg == WM_INITDIALOG))
    {
        EndDialog(hDlg, -1);
    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// WinMain
//
// Entry point into this executable -- just pops up a dialog that does all the work
// 
// hInstance: IN parameter, the HINSTANCE of this program
// hPrevInstance: IN parameter, the previous HINSTANCE
// lpCmdLine: IN parameter, command-line parameter
// nCmdShow: IN parameter, information on showing the window
//
// Returns int
//

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    CoInitializeEx(NULL, 0);
    
    // Start up the main dialog, please
    g_hInst = hInstance;
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);

    CoUninitialize();
    return 0;
}

