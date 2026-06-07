//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#pragma once
#pragma check_stack(on)

#include <windows.h>
#include <initguid.h>   // Needed for COM
#include <pimstore.h>   // Needed for POOM and ChooseContact APIs
#include <aygshell.h>   // Needed for GetOpenFileEx API
#include "Macros.h"     // SDK macros file (Has defn for CBR, CHR etc).

// Global Variables
static IPOutlookApp2    *g_pPoom   = NULL;


///////////////////////////////////////////////////////////////////////////////
// InitPOOM2
//
//  Initializes COM, creates the POOM COM object and calls Logon.
//
HRESULT InitPOOM2()
{
    HRESULT hr = S_OK;
    
    // Init COM
    hr = CoInitializeEx(NULL, 0);   
    CHR(hr);
      
    // Create the POOM COM object.
    hr = CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, 
        IID_IPOutlookApp2, (LPVOID *) &g_pPoom);
    CHR(hr);
    CBR(NULL != g_pPoom);

    // Logon to POOM. 
    hr = g_pPoom->Logon(NULL);
    CHR(hr);

Error:        
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// UnInitPOOM2
//
//  Does a logoff on POOM, and uninitializes COM.
//
HRESULT UnInitPOOM2()
{
    HRESULT hr = S_OK;
    
    CBR(NULL != g_pPoom);

    // Logoff from POOM.
    hr = g_pPoom->Logoff();
    
Error:    
    RELEASE_OBJ(g_pPoom);    
    CoUninitialize();   
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SelectContact
//
//  [OUT] ppItem - IItem ptr to the contact the user selected
//
//  Uses the ChooseContact API to bring up the Contacts Chooser.  The user can 
//   select a contact to add a picture to.
//
HRESULT SelectContact(IItem **ppItem)
{
    HRESULT         hr = S_OK;
    CHOOSECONTACT   cc = {0};
    const CEPROPID  c_propidAllEmail = PIMPR_ALL_EMAIL; 

    CBR(NULL != ppItem);

    // Setup the CHOOSECONTACT structure.
    cc.cbSize       = sizeof (cc);
    cc.dwFlags      = CCF_DEFAULT | CCF_CHOOSECONTACTONLY;
    cc.hwndOwner    = NULL;

    // Display the Contact Chooser control and prompt the user to choose a contact.
    hr = ChooseContact(&cc);    
    CHR(hr);

    // Get the IItem from the OID for the selected contact        
    hr = g_pPoom->GetItemFromOidEx(cc.oidContactID, 0, ppItem);
    CHR(hr);
    CBR(NULL != *ppItem);

Error:
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// SelectPicture
//
//  [IN/OUT]    pszPictureFile  - ptr to buffer to copy the selected picture file name to.
//  [IN]        dwBufferSize    - count of chars in the buffer. 
//
//  Uses the Picture picker to select a picture.  The filename for the picture 
//   is passed back to the calling function.
//
HRESULT SelectPicture(LPTSTR pszPictureFile, DWORD dwBufferSize)
{
    HRESULT         hr      = S_OK;
    OPENFILENAMEEX  ofnex   = {0};
    BOOL            bResult = FALSE;

    CBR(NULL != pszPictureFile);

    // Setup the Picture picker structure
    ofnex.lStructSize   = sizeof(ofnex);
    ofnex.ExFlags       = OFN_EXFLAG_THUMBNAILVIEW;    
    ofnex.lpstrFile     = new TCHAR[MAX_PATH];
    ofnex.nMaxFile      = MAX_PATH;

    CBR(NULL != ofnex.lpstrFile);

    // Call the Picture picker UI. Lets the user select a pic.
    bResult = GetOpenFileNameEx(&ofnex);
    CBR(bResult);

    // Copies the picture to the buffer passed in.
    hr = StringCchCopy(pszPictureFile, dwBufferSize, ofnex.lpstrFile);
    CHR(hr);

Error:
    delete[] ofnex.lpstrFile;
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// SaveFileToStream
//
//  [IN]        pszFileName - pic file to copy over to the ISteram.
//  [IN/OUT]    pStream     - IStream used to set the contacts picture property.
//  [IN]        bResize     - Bool val to signify if the stream should be truncated.
//                            (useful if overwriting an existing picture)
//
//  Saves picture file to an IStream that can be used to upload it to a contact.
//
HRESULT SaveFileToStream(LPTSTR pszFileName, IStream *pStream, BOOL bResize)
{
    HRESULT     hr          = S_OK;
    HANDLE      hFile       = 0;
    ULONG       cbWritten   = 0;
    DWORD       dwSizeLow   = 0, 
                dwSizeHigh  = 0, 
                dwError     = 0,
                dwBytes     = 0;
    ULARGE_INTEGER uli      = {0};
    int         i           = 0;
    BYTE    *pAllbyteData   = NULL;

    CBR(NULL != pszFileName);
    CBR(NULL != pStream);
    
    // Open the file for reading.
    hFile = CreateFile(pszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) 
    {
        hr = E_INVALIDARG;
        goto Error;
    }

    // Get the file size.
    dwSizeLow = GetFileSize (hFile, & dwSizeHigh);          
    if (dwSizeLow == 0xFFFFFFFF && 
        (dwError = GetLastError()) != NO_ERROR )
    { 
        hr = E_FAIL;
        goto Error;
    }     

    DEBUGMSG(TRUE, (TEXT("FileSize = %u bytes"), dwSizeLow));

    if(bResize)
    {
        // Reset the stream's size (ie truncate the stream size)
        uli.LowPart     = dwSizeLow;
        uli.HighPart    = dwSizeHigh;
        hr = pStream->SetSize(uli); 
        CHR(hr);
    }

    pAllbyteData = new BYTE[dwSizeLow];
    CPR(pAllbyteData);    
    
    if (ReadFile(hFile, pAllbyteData, dwSizeLow, &dwBytes, NULL)) 
    {
        // Write the bytes from the file to the stream
        hr = pStream->Write(pAllbyteData, dwSizeLow, &cbWritten);
        if (cbWritten != dwSizeLow || FAILED(hr))
        {
            DEBUGMSG(TRUE,(TEXT("Wrote %u of %u bytes to stream"), cbWritten, dwSizeLow));
            goto Error;
        }        
    }
    else
    {
        DEBUGMSG(TRUE,(TEXT("Read from file failed!")));
        hr = E_FAIL;
        goto Error;
    }        

    // Commit the steam to the contact object.
    hr = pStream->Commit(0);

Error:
    delete[] (pAllbyteData);
    
    if(hFile != INVALID_HANDLE_VALUE && hFile != 0)
    {
        CloseHandle(hFile);
    }
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// AddPictureToContact
//
//  [IN]    ppItem          - IItem interface to the contact the user selected. 
//  [IN]    pszPictureFile  - Filename of the picture to add to the contact.
//
HRESULT AddPictureToContact(IItem *pItem, LPTSTR pszPictureFile)
{
    HRESULT     hr          = S_OK;
    IStream     *pStream    = NULL;

    CBR(NULL != pItem);
    CBR(NULL != pszPictureFile);

    // Open the picture property for the contact.
    hr = pItem->OpenProperty(PIMPR_PICTURE, GENERIC_READ | GENERIC_WRITE, &pStream);
    CHR(hr);
    CBR(NULL != pStream);

    // Add the picture to the contact's picture property
    // NOTE: Ideally you would want to scale the picture file to a smaller thumbnail
    // so you don't waste storage space (in the database) when adding a huge picture. 
    // This has intentionally not been done here as it is out of the scope of this sample.
    hr = SaveFileToStream(pszPictureFile, pStream, TRUE);
    CHR(hr);

    // Save the contact (with the picture added), to the underlying store.
    hr = pItem->Save();
    CHR(hr);

Error:
    RELEASE_OBJ(pStream);
    
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
// WinMain
//
//  Application entry point.
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    HRESULT     hr      = S_OK;
    IItem       *pItem  = NULL;
    TCHAR       szPictureFile[MAX_PATH] = {0};

    // Init POOM
    hr = InitPOOM2();
    CHR(hr);

    // Select the contact which the picture will be added to.
    hr = SelectContact(&pItem);
    CHR(hr);
    CBR(NULL != pItem);

    // Select the Picture to add to the contact just selected above.
    hr = SelectPicture(szPictureFile, MAX_PATH);
    CHR(hr);
    CBR(NULL != szPictureFile);

    DEBUGMSG(TRUE, (TEXT("pItem = 0x%x, szPictureFile=%s"), 
        pItem, szPictureFile));

    // Use POOM to add the picture to the Contact
    hr = AddPictureToContact(pItem, szPictureFile);
    CHR(hr);
    
    //Display the Contacts summary card. The summary card will display the picture.
    hr = pItem->Display(NULL);
    CHR(hr);
   
Error:    
    RELEASE_OBJ(pItem);
    
    hr = UnInitPOOM2();

    if(FAILED(hr))
    {
        return -1;
    }
    return 0;
}

