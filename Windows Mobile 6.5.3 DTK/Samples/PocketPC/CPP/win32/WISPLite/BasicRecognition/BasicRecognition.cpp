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
// BasicRecognition.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BasicRecognition.h"
#include <windows.h>
#include <commctrl.h>
#include <msinkaut.h>
#include <msinkaut_i.c>

#define MAX_LOADSTRING 100
#define SAFE_RELEASE(x) if(x){ x->Release(); x = NULL; }

// Global Variables:
HINSTANCE			g_hInst;			// current instance
HWND				g_hWndMenuBar;		// menu bar handle
IInkOverlay*        g_pInkOverlay;
HWND                g_hWnd;

// Forward declarations of functions included in this code module:
ATOM			    MyRegisterClass(HINSTANCE, LPTSTR);
BOOL			    InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

LRESULT             OnFileOpen(HWND hWnd);
LRESULT             OnFileClear(HWND hWnd);
LRESULT             OnRecognize(HWND hWnd, WPARAM wParam, LPARAM lParam);

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
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BASICRECOGNITION));

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
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BASICRECOGNITION));
    wc.hCursor       = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = 0;
    wc.lpszClassName = szWindowClass;

    return RegisterClass(&wc);
}

// 
// Create an inking region where ink can be collected.
//
void CreateInkRegion(HWND hWnd, HINSTANCE hInstance)
{
    HWND labelInk = NULL;
    HWND hWndInk = NULL;
    HWND buttonRecognize = NULL;
    HWND labelRecoText = NULL;
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
    labelInk = CreateWindow(  TEXT("static"), 
                                    TEXT("Ink Here"),
                                    SS_LEFT | WS_VISIBLE, 
                                    left, 
                                    top, 
                                    70,
                                    15,
                                    hWnd, 
                                    (HMENU) IDC_STATIC, 
                                    hInstance, 
                                    NULL);

    // Create the signature window
    hWndInk = CreateWindow( TEXT("static"),
                            NULL,
                            WS_VISIBLE | WS_CHILD | WS_BORDER, 
                            left, 
                            top + 20,
                            215, 
                            150,
                            hWnd,
                            NULL, 
                            hInstance, 
                            NULL);

    //
    // Create a button for starting recognition
    //
    buttonRecognize = CreateWindow( TEXT("Button"), 
                                    TEXT("Recognize"),
                                    SS_LEFT | WS_VISIBLE, 
                                    left, 
                                    top + 180, 
                                    70,
                                    20,
                                    hWnd, 
                                    (HMENU) IDC_RECOGNIZE, 
                                    hInstance, 
                                    NULL);

    // 
    // Create the label box for the reco result
    // 
    labelRecoText = CreateWindow(   TEXT("static"),
                                    TEXT (""), 
                                    ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 
                                    left + 75, 
                                    top + 180, 
                                    140,
                                    20, 
                                    hWnd,
                                    (HMENU)IDC_RECOTEXT, 
                                    hInstance, 
                                    NULL);

    
    // Finally, attach the inkoverlay object to the window and enable it.
    hr = g_pInkOverlay->put_hWnd((long)hWndInk);
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
    LoadString(hInstance, IDC_BASICRECOGNITION, szWindowClass, MAX_LOADSTRING);

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

    CreateInkRegion(hWnd, hInstance);
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
                case IDC_RECOGNIZE:
                    OnRecognize(hWnd, wParam, lParam);
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

        // Reset the data of the reco label
        TCHAR       szText[2]={0};
        SendDlgItemMessage (g_hWnd, IDC_RECOTEXT, WM_SETTEXT, sizeof(szText), (LPARAM)szText);             
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

    // Reset the data of the reco label
    SendDlgItemMessage (g_hWnd, IDC_RECOTEXT, WM_SETTEXT, sizeof(szText), (LPARAM)szText);             

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
// OnRecognize is the handler for the events sent from the button
// This method presents us the best string corresponding to the strokes collection, in a label
//
LRESULT OnRecognize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    IInkDisp*               pInk = NULL;    
    IInkStrokes*            pStrokes = NULL; 
    IInkRecognitionResult*  result = NULL;     
    BSTR                    resultString = NULL;
    HRESULT                 hr = S_OK;

    // If the recognize button has been pressed
    if( LOWORD(wParam) == IDC_RECOGNIZE && 
        (HIWORD(wParam) == BN_SETFOCUS || HIWORD(wParam) == BN_CLICKED ))
    {
        hr = g_pInkOverlay->get_Ink( &pInk );
        if( FAILED(hr ) )
        {
            goto End;
        }

        // Get all the strokes in the ink object
        hr = pInk->get_Strokes(&pStrokes);
        if (FAILED(hr))
            goto End;
     
        // Another way to achieve the following is: pStrokes->ToString(&resultString)

        // Get the recognition result for these strokes
        hr = pStrokes->get_RecognitionResult(&result);
        if (FAILED(hr) || !result)
        {
            goto End;
        }

        // Get the top recognized string 
        hr = result->get_TopString(&resultString);                    

        if(FAILED(hr))
        {
            goto End;
        }
    
        //
        //The best result String is shown in the edit box on the application
        //
        LPCWSTR str = resultString;
        SendDlgItemMessage (g_hWnd, IDC_RECOTEXT, WM_SETTEXT, sizeof(str), (LPARAM)str);          
}

End:
    if(FAILED(hr))
    {
        MessageBox(NULL, L"Error in recognizing ink", L"Recognition", MB_OK);
    }
    SAFE_RELEASE( pInk );
    SAFE_RELEASE( pStrokes );
    SAFE_RELEASE( result );             
    ::SysFreeString(resultString);
    return 0;
}
