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
// InkSerialization.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "InkSerialization.h"
#include <windows.h>
#include <commctrl.h>
#include <msinkaut.h>
#include <msinkaut_i.c>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			g_hInst;			// current instance
HWND				g_hWndMenuBar;		// menu bar handle
IInkOverlay*        g_pInkOverlay;
HWND                g_hWnd;

// GUID for firstName and lastName properties
BSTR                firstNameGUID = SysAllocString(TEXT("{1AE79181-7B9E-45ec-B525-20023752860B}"));
BSTR                lastNameGUID  = SysAllocString(TEXT("{1AE79181-7B9E-45ec-B525-20023752860C}"));

// Forward declarations of functions included in this code module:
ATOM			    MyRegisterClass(HINSTANCE, LPTSTR);
BOOL			    InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// File load/save functions
LRESULT             OnFileOpen(HWND hWnd);
LRESULT             OnFileClear(HWND hWnd);
LRESULT             OnFileSave(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    MSG msg;

    // Initialize the COM library
    if(FAILED(::CoInitializeEx(NULL, NULL)))
    {
        return FALSE;
    }

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) 
    {
        return FALSE;
    }

    HACCEL hAccelTable;
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INKSERIALIZATION));

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INKSERIALIZATION));
    wc.hCursor       = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = 0;
    wc.lpszClassName = szWindowClass;

    return RegisterClass(&wc);
}

//
// Create labels and text boxes to collect the first name and second name
//
void CreateLabelsAndText(HWND hWnd, HINSTANCE hInstance)
{
    HWND labelFirstName = NULL;
    HWND labelLastName = NULL;
    HWND labelSignature = NULL;

    HWND editFirstName = NULL;
    HWND editLastName = NULL;
    HWND hWndSignature = NULL;
    HRESULT hr = S_OK;

    int left = 10;
    int top  = 20;

    // Create the inkoverlay object

    hr = ::CoCreateInstance(CLSID_InkOverlay,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            IID_IInkOverlay,
                            (void **)&g_pInkOverlay);
    ASSERT(SUCCEEDED(hr));

    //
    // Create the labels
    //
    labelFirstName = CreateWindow(  TEXT("static"), 
                                    TEXT("First Name"),
                                    SS_LEFT | WS_VISIBLE, 
                                    left, 
                                    top, 
                                    70,
                                    15,
                                    hWnd, 
                                    (HMENU) IDC_STATIC, 
                                    hInstance, 
                                    NULL);

    labelLastName = CreateWindow(   TEXT("static"), 
                                    TEXT("Last Name"),
                                    SS_LEFT | WS_VISIBLE, 
                                    left, 
                                    top + 30, 
                                    70,
                                    15,
                                    hWnd, 
                                    (HMENU) IDC_STATIC, 
                                    hInstance, 
                                    NULL);

    labelSignature = CreateWindow(  TEXT("static"), 
                                    TEXT("Signature"),
                                    SS_LEFT | WS_VISIBLE, 
                                    left, 
                                    top + 65, 
                                    70,
                                    15,
                                    hWnd, 
                                    (HMENU) IDC_STATIC, 
                                    hInstance, 
                                    NULL);

    // 
    // Create the text boxes
    // 
    editFirstName = CreateWindow(   TEXT("edit"),
                                    TEXT (""), 
                                    ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 
                                    left + 75, 
                                    top, 
                                    140,
                                    20, 
                                    hWnd,
                                    (HMENU)IDC_FIRSTNAME, 
                                    hInstance, 
                                    NULL);

    editLastName = CreateWindow(    TEXT("edit"),
                                    TEXT (""), 
                                    ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 
                                    left + 75, 
                                    top + 30, 
                                    140,
                                    20, 
                                    hWnd,
                                    (HMENU)IDC_LASTNAME, 
                                    hInstance, 
                                    NULL);
 
    // Finally, create the signature window
    hWndSignature = CreateWindow( TEXT("static"),
                                  NULL,
                                  WS_VISIBLE | WS_CHILD | WS_BORDER, 
                                  left, 
                                  top + 90,
                                  215, 
                                  100,
                                  hWnd,
                                  NULL, 
                                  hInstance, 
                                  NULL);
    
    // Attach the inkoverlay object to the window and enable it to start collecting ink
    g_pInkOverlay->put_hWnd((long)hWndSignature);
    ASSERT(SUCCEEDED(hr));
    hr = g_pInkOverlay->put_Enabled(VARIANT_TRUE);
    ASSERT(SUCCEEDED(hr));


    return;
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    TCHAR szTitle[MAX_LOADSTRING];		// title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];	// main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the device specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_INKSERIALIZATION, szWindowClass, MAX_LOADSTRING);

    //If it is already running, then focus on the window, and exit
    hWnd = FindWindow(szWindowClass, szTitle);	
    if (hWnd) 
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    } 

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
        return FALSE;
    }

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }
    g_hWnd = hWnd;

    // When the main window is created using CW_USEDEFAULT the height of the menubar (if one
    // is created is not taken into account). So we resize the window after creating it
    // if a menubar is present
    if (g_hWndMenuBar)
    {
        RECT rc;
        RECT rcMenuBar;

        GetWindowRect(hWnd, &rc);
        GetWindowRect(g_hWndMenuBar, &rcMenuBar);
        rc.bottom -= (rcMenuBar.bottom - rcMenuBar.top);
        
        MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);
    }


    // Now create the textboxes and signature window
    CreateLabelsAndText(hWnd, hInstance);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    static SHACTIVATEINFO s_sai;
    
    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // Parse the menu selections:
            switch (wmId)
            {
                case ID_FILE_CLEAR:
                    OnFileClear(hWnd);
                    break;
                case ID_FILE_OPEN:
                    OnFileOpen(hWnd);
                    break;
                case ID_FILE_SAVE:
                    OnFileSave(hWnd);
                    break;
                case IDM_OK:
                    SendMessage (hWnd, WM_CLOSE, 0, 0);				
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_CREATE:
            SHMENUBARINFO mbi;

            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hWnd;
            mbi.nToolBarId = IDR_MENU;
            mbi.hInstRes   = g_hInst;

            if (!SHCreateMenuBar(&mbi)) 
            {
                g_hWndMenuBar = NULL;
            }
            else
            {
                g_hWndMenuBar = mbi.hwndMB;
            }

            // Initialize the shell activate info structure
            memset(&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            
            // TODO: Add any drawing code here...
            
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            CommandBar_Destroy(g_hWndMenuBar);
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
            break;
        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


//
// Loads the supplied ISF file into the ink object
//
HRESULT LoadISFFile(LPCWSTR lpszFilename, IInkDisp** ppunkOutInk)
{
    HRESULT         hr = S_OK;
    HANDLE          hFile = INVALID_HANDLE_VALUE;
    VARIANT         vt;
    SAFEARRAY*      pSA = NULL;
    unsigned char*  pbISFData = NULL;
    DWORD           dwISFDataSize = 0;
    DWORD           dwDataRead = 0;
    IInkDisp*       punkInk = NULL;

    ::VariantInit(&vt);

    hFile = ::CreateFile(lpszFilename, 
                        GENERIC_READ, 
                        FILE_SHARE_READ, 
                        NULL, 
                        OPEN_EXISTING, 
                        FILE_ATTRIBUTE_NORMAL, 
                        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        hr = E_FAIL;
        goto End;
    }
    dwISFDataSize = (DWORD) GetFileSize(hFile, NULL);

    pSA = ::SafeArrayCreateVector(VT_UI1, 0, dwISFDataSize);
    if (NULL == pSA)
    {
        hr = E_OUTOFMEMORY;
        goto End;
    }

    //
    // Load the variant
    //
    vt.vt = VT_ARRAY | VT_UI1;
    vt.parray = pSA;

    //
    // Access the safearray so that we can load the ISF data from
    // the file to the variant
    //
    hr = ::SafeArrayAccessData(pSA, (LPVOID*) &pbISFData);
    if (FAILED(hr))
    {
        goto End;
    }

    ::ReadFile(hFile, pbISFData, dwISFDataSize, &dwDataRead, NULL);

    hr = ::SafeArrayUnaccessData(pSA);
    if (FAILED(hr))
    {
        goto End;
    }

    hr = ::CoCreateInstance(CLSID_InkDisp, NULL, CLSCTX_INPROC_SERVER, IID_IInkDisp, (void **)&punkInk);
    if (FAILED(hr))
    {
        goto End;
    }

    hr = punkInk->Load(vt);
    if (FAILED(hr))
    {
        punkInk->Release();
        goto End;
    }

    *ppunkOutInk = punkInk;

End:
    if(INVALID_HANDLE_VALUE != hFile)
    {
        ::CloseHandle(hFile);
    }
    ::VariantClear(&vt);
    return hr;
}

//
// Retrieve the extended property value corresponding to the passed GUID and update the 
// control accordingly.
//
LRESULT GetNameAndDisplay(IInkDisp *pInk, BSTR nameGUID, int controlID)
{
    IInkExtendedProperties* pInkProperties = NULL;
    IInkExtendedProperty*   pInkProperty = NULL;        
    VARIANT                 data;
    VARIANT                 var;
    VARIANT_BOOL            vbExists;
    TCHAR                   szText[255] = {0};
    
    VariantInit(&data);
    VariantInit(&var);
    var.vt = VT_BSTR;
    var.bstrVal = nameGUID;
    
    HRESULT hr;
    hr = pInk->get_ExtendedProperties(&pInkProperties);
    ASSERT(SUCCEEDED(hr));      

    // Get the raw data out of this ink's extended
    // properties list, using the passed GUID as the key
    // to the extended property we want.
    // The save method earlier stored the first and last
    // name information as extended propertiee.

    hr = pInkProperties->DoesPropertyExist( nameGUID, &vbExists);
    if( vbExists ==VARIANT_TRUE)
    {
        hr = pInkProperties->Item( var, &pInkProperty);                      
        ASSERT(SUCCEEDED(hr));      
        hr = pInkProperty->get_Data(&data);
        ASSERT(SUCCEEDED(hr));      
        BSTR temp = data.bstrVal;
        LPCWSTR fName = temp;             
        SendDlgItemMessage (g_hWnd, controlID, WM_SETTEXT, sizeof(fName), (LPARAM)fName);    
    }
    else
    {
        SendDlgItemMessage (g_hWnd, controlID, WM_SETTEXT,sizeof (""), (LPARAM)"");  
    }

    ::VariantClear(&var);
    ::VariantClear(&data);

    if(pInkProperties)
        pInkProperties->Release();

    if(pInkProperty)
        pInkProperty->Release();

    return 0;
}

//
// Get the text on the supplied control and add it as an extended property with the specified GUID
//
LRESULT SetNameFromDisplay(IInkDisp* pInk, BSTR nameGUID, int controlID)
{
    HRESULT                 hr = S_OK;
    IInkExtendedProperties* pInkProperties = NULL;
    IInkExtendedProperty*   pInkProperty = NULL;
    TCHAR                   szText[MAX_PATH];
    VARIANT                 data;   

    VariantInit(&data);
    hr = pInk->get_ExtendedProperties(&pInkProperties);

    ASSERT(SUCCEEDED(hr));      

    SendDlgItemMessage(g_hWnd, controlID, WM_GETTEXT, sizeof (szText),(LPARAM)szText);          

    // Store the name property as an extended property in the ink object
    if(szText[0]!='\0')
    {
        data.vt = VT_BSTR;
        data.bstrVal = SysAllocString(szText);        
        hr = pInkProperties->Add(nameGUID, data, &pInkProperty);
        ASSERT(SUCCEEDED(hr));
    }
    
    if(pInkProperties)
        pInkProperties->Release();

    if(pInkProperty)
        pInkProperty->Release();

    return 0;
}


//
// Open an ISF file and display the signature. Also update the firstname and secondname
//
LRESULT OnFileOpen(HWND hWnd)
{
    IInkDisp*       pInk = NULL;
    OPENFILENAME    of;
    TCHAR           szFileName[MAX_PATH] = {0};
    const LPTSTR    pszOpenFilter = L"ISF Files (*.isf)\0*.isf\0\0";
    HRESULT         hr = S_OK;

    szFileName[0] = '\0';
    memset( &of, 0, sizeof( of ) );
    of.lStructSize = sizeof( of );
    of.hwndOwner = hWnd;
    of.lpstrFile = szFileName;
    of.nMaxFile = MAX_PATH;
    of.lpstrFilter = pszOpenFilter;
    of.Flags = 0;

    if( IDOK == GetOpenFileName( &of ) )
    {       
        HANDLE logfile = NULL;
        hr = LoadISFFile(szFileName, &pInk);       
        if(FAILED(hr))
        {
            MessageBox(hWnd,TEXT("File open Failed"),TEXT("LoadISF"),MB_OK);
            goto End;

        }
        //
        // Now put this ink into the InkOverlay
        //
        ASSERT( NULL != g_pInkOverlay );

        g_pInkOverlay->put_Enabled(VARIANT_FALSE);
        g_pInkOverlay->putref_Ink(pInk);
        g_pInkOverlay->put_Enabled(VARIANT_TRUE);

        //
        // Retrieve first and last name extended properties stored in the ISF file
        // and display them in the edit boxes in the application
        //

        GetNameAndDisplay(pInk, firstNameGUID, IDC_FIRSTNAME);
        GetNameAndDisplay(pInk, lastNameGUID,  IDC_LASTNAME);
        UpdateWindow( hWnd );
    }
End:    
    if(pInk)
        pInk->Release();
    return( 0 );
}

//
// Clear the ink data and the firstname/secondname edit boxes
//
LRESULT OnFileClear(HWND hWnd)
{
    HRESULT     hr = S_OK;
    IInkDisp*   pInk = NULL;
    TCHAR       szText[2]={0};

    // Reset the data of the text boxes
    SendDlgItemMessage (g_hWnd, IDC_FIRSTNAME, WM_SETTEXT, sizeof(szText), (LPARAM)szText);            
    SendDlgItemMessage (g_hWnd, IDC_LASTNAME, WM_SETTEXT, sizeof(szText), (LPARAM)szText);             

    g_pInkOverlay->put_Enabled( VARIANT_FALSE );

    //
    // Create a new ink object and associate it with the overlay object
    //
    hr = ::CoCreateInstance(CLSID_InkDisp, NULL, CLSCTX_INPROC_SERVER, IID_IInkDisp, (void **)&pInk);
    if(FAILED(hr))
    {
        MessageBox( NULL, L"Cannot clear ink object", L"Clear", MB_OK );
        return( 0 );
    }

    hr = g_pInkOverlay->putref_Ink( pInk );

    g_pInkOverlay->put_Enabled( VARIANT_TRUE );

    if(pInk)
        pInk->Release();

    return 1;
}

//
// Save the ink data to an ISF file. Also store the firstname and secondname as extended properties.
//
LRESULT OnFileSave(HWND hWnd)
{
    HRESULT         hr = S_OK;
    SAFEARRAY*      pSA = NULL;
    HANDLE          hFileTemp = INVALID_HANDLE_VALUE;
    IInkDisp*       pInk = NULL;

    OPENFILENAME    of;
    TCHAR           szFileName[MAX_PATH] = {0};
    TCHAR           szText[MAX_PATH] ={0}; 
    const LPTSTR    pszOpenFilter = L"ISF Files (*.isf)\0*.isf\0\0";


    g_pInkOverlay->get_Ink(&pInk);

    //
    // Store the first and last name as extended properties to the ink object 
    // and store it as an ISF file
    //
    SetNameFromDisplay(pInk, firstNameGUID, IDC_FIRSTNAME);
    SetNameFromDisplay(pInk, lastNameGUID, IDC_LASTNAME);
    
    szFileName[0] = '\0';
    memset( &of, 0, sizeof( of ) );
    of.lStructSize = sizeof( of );
    of.hwndOwner = hWnd;
    of.lpstrFile = szFileName;
    of.nMaxFile = MAX_PATH;
    of.lpstrFilter = pszOpenFilter;
    of.Flags = 0;
    GetSaveFileName( &of );

    if( '\0' != szFileName[0] )
    {
        hFileTemp = CreateFile( szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
        if( INVALID_HANDLE_VALUE == hFileTemp )
        {
            goto End;
        }

        //
        // Now save the ink
        //
        VARIANT Data;
        VariantInit( &Data );

        if( FAILED( hr = pInk->Save( IPF_InkSerializedFormat, IPCM_Default, &Data ) ) )
        {
            goto End;
        }

        SAFEARRAY *pSA = V_ARRAY(&Data);

        unsigned char *pBytes = NULL;
        hr = ::SafeArrayAccessData(pSA, (void HUGEP **)&pBytes);
        if(FAILED(hr))
        {
            ::SafeArrayDestroy(pSA);
            goto End;
        }

        //
        // Write to file
        //
        DWORD dwWrittenSize = 0;
        WriteFile( hFileTemp, pBytes, pSA->rgsabound->cElements, &dwWrittenSize, NULL );

        hr = ::SafeArrayUnaccessData(pSA);
        if(FAILED(hr))
        {
            ::SafeArrayDestroy(pSA);
            goto End;
        }
    }
    else
    {
        DWORD dwLastError = GetLastError();
        if( dwLastError )
        {
            hr = E_FAIL;
        }
    }
End:
    if(FAILED(hr))
    {
        MessageBox( NULL, L"Error in saving file", L"File Error", MB_OK );
    }
    if( INVALID_HANDLE_VALUE != hFileTemp )
    {
        CloseHandle( hFileTemp );
    }
    return( 0 );
}
