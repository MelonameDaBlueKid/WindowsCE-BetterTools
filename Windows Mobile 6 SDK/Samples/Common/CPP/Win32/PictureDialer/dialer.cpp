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

#include <windows.h>
#include <windowsx.h>
#include <aygshell.h>
#include <phone.h>
#include <imaging.h>

#include "macros.h"
#include "resource.h"
#include "main.h"
#include "dialer.h"
#include "utils.h"

// Registry key template for saving the contact information
const TCHAR  c_szRegSaveFormat[] = _T("\\Software\\Microsoft\\PictureDial\\%d");

// Registry value name for the contact's phone number
const TCHAR  c_szRegValuePhoneNumber[] = _T("PhoneNumber");

// Registry value name for the contact's oid
const TCHAR  c_szRegValueOID[]         = _T("oid");


CPictureDial::CPictureDial() :
    m_hWnd        (NULL),
    m_pOutlookApp (NULL),
    m_iSel        (0),
    m_hFont       (NULL)
{
    ZeroMemory(m_rgContact, sizeof(m_rgContact));
}


CPictureDial::~CPictureDial()
{
    // Clean everything out
    for (int i=0; i<NUMITEMS; i++)
    {
        ClearContactData(i);
    }

    RELEASE_OBJ(m_pOutlookApp);

    if (m_hFont)
    {
        DeleteFont(m_hFont);
    }
}


// **************************************************************************
// Function Name: CPictureDial::OnCreate
// 
// Purpose: Handles WM_CREATE message
//
// Arguments:
//    IN HWND  hWnd - window that received the request
//
// Return Values:
//    0 indicates success, -1 indicates failure
//

LRESULT CPictureDial::OnCreate(HWND hWnd)
{
    HRESULT hr;
    BOOL fSuccess;
    SHMENUBARINFO cbi = { sizeof(cbi) };
    RECT rc;

    m_hWnd = hWnd;

    cbi.hwndParent = hWnd;
    cbi.dwFlags    = SHCMBF_HMENU;
    cbi.nToolBarId = IDM_MAINMENU;
    cbi.hInstRes   = ghInst;

    fSuccess = SHCreateMenuBar(&cbi);
    CBR(fSuccess);

    // Calculate the width and height of each square
    GetClientRect(m_hWnd, &rc);

    m_uItemWidth  = (rc.right-rc.left)/NUMCOLUMNS;
    m_uItemHeight = (rc.bottom-rc.top-CYSTATUS)/NUMROWS;

    LoadAllContacts();

    hr = S_OK;

Error:
    return (SUCCEEDED(hr) ? 0 : -1);
}


// **************************************************************************
// Function Name: CPictureDial::EnsurePOOM
// 
// Purpose: Instantiate the POOM object if necessary
//
// Arguments:
//    NONE
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::EnsurePOOM()
{
    HRESULT hr;

    if (m_pOutlookApp == NULL)
    {
        hr = CoCreateInstance(__uuidof(Application), NULL, CLSCTX_INPROC_SERVER,
                              __uuidof(IPOutlookApp2), (LPVOID*) &m_pOutlookApp);
        CHR(hr);

        hr = m_pOutlookApp->Logon(NULL);
        CHR(hr);
    }

    hr = S_OK;

Error:
    if (FAILED(hr))
    {
        // If we failed to log on, don't keep the object around
        RELEASE_OBJ(m_pOutlookApp);
    }

    return hr;
}


// **************************************************************************
// Function Name: CPictureDial::AssociateContact
// 
// Purpose: Sets the picture and phone number of the selected contact
//
// Arguments:
//    IN CEOID oid - oid of the contact
//    IN LPCTSTR pszPhoneNumber - phone number of the contact
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::AssociateContact(CEOID oid, LPCTSTR pszPhoneNumber)
{
    HRESULT  hr;
    LPTSTR   pszPhone;
    HBITMAP  hBitmap = NULL;
    UINT     uWidth  = m_uItemWidth-BORDERSIZE-CXGUTTER*2;
    UINT     uHeight = m_uItemHeight-BORDERSIZE-CYGUTTER*2;
    UINT     cchPhone;

    // First make a copy of the phone number
    cchPhone = (lstrlen(pszPhoneNumber)+1);

    pszPhone = new TCHAR[cchPhone+1];
    CPR(pszPhone);

    hr = StringCchCopy(pszPhone, cchPhone, pszPhoneNumber);
    CHR(hr);

    // Ignore the failure code.  If this fails, hBitmap should remain NULL
    FindBitmap(oid, &hBitmap, &uWidth, &uHeight);

    // Clear out the slot first
    ClearContactData(m_iSel);

    // Save the contact in the currently selected slot
    m_rgContact[m_iSel].oid      = oid;
    m_rgContact[m_iSel].hBitmap  = hBitmap;
    m_rgContact[m_iSel].dxBitmap = uWidth;
    m_rgContact[m_iSel].dyBitmap = uHeight;
    m_rgContact[m_iSel].pszPhoneNumber = pszPhone;

    pszPhone = NULL;
    hBitmap = NULL;

    // Save the association
    Save(m_iSel);

    hr = S_OK;

Error:
    // Clean up
    if (hBitmap)
    {
        DeleteBitmap(hBitmap);
    }

    delete [] pszPhone;
    return hr;
}


// **************************************************************************
// Function Name: CPictureDial::FindBitmap
// 
// Purpose: Given an oid, find the bitmap and its dimensions
//
// Arguments:
//    IN  CEOID    oid      - oid of the contact
//    IN  HBITMAP* phBitmap - bitmap of the contact's picture
//    OUT UINT*    puWidth  - width of the bitmap
//    OUT UINT*    puHeight - height of the bitmap
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::FindBitmap
(
    CEOID    oid,
    HBITMAP* phBitmap,
    UINT*    puWidth,
    UINT*    puHeight
)
{
    HRESULT   hr;
    IItem*    pItem = NULL;
    IStream*  pStream = NULL;
    ULONG     ulSize;

    // Make sure we can access POOM
    hr = EnsurePOOM();
    CHR(hr);

    hr = m_pOutlookApp->GetItemFromOidEx(oid, 0, &pItem);
    CHR(hr);
    
    // Extract the picture from the contact
    hr = pItem->OpenProperty(PIMPR_PICTURE, GENERIC_READ, &pStream);
    CHR(hr);
    
    hr = GetStreamSize(pStream, &ulSize);
    CHR(hr);

    // In some cases, the property may exist even if there is no picture.
    // Make sure we can access the stream and don't have a 0 byte stream
    CBR(ulSize > 0);

    hr = GetBitmapFromStream(pStream, phBitmap, puWidth, puHeight);
    CHR(hr);

Error:
    RELEASE_OBJ(pItem);
    RELEASE_OBJ(pStream);

    return hr;
}


// **************************************************************************
// Function Name: CPictureDial::SetContact
// 
// Purpose: Prompt the user for the contact to use for the selected digit
//          and set the contact for that digit
//
// Arguments:
//    NONE
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::SetContact()
{
    HRESULT hr;
    CHOOSECONTACT  chooserData = {0};
    CEPROPID       propid;

    // Prepare to pop up the contact chooser.  Include only voice numbers
    // in the list
    propid = PIMPR_ALL_VOICE;

    chooserData.cbSize = sizeof(chooserData);
    chooserData.dwFlags = CCF_RETURNPROPERTYVALUE;
    chooserData.rgpropidRequiredProperties = &propid;
    chooserData.cRequiredProperties = 1;
    chooserData.hwndOwner = m_hWnd;

    // Pop up the contact chooser
    hr = ChooseContact(&chooserData);
    CHR(hr);

    // associate the contact with the current selected square
    hr = AssociateContact(chooserData.oidContactID, chooserData.bstrPropertyValueSelected);
    CHR(hr);

    // Refresh the screen
    InvalidateRect(m_hWnd, NULL, TRUE);

Error:
    SysFreeString(chooserData.bstrPropertyValueSelected);

    return hr;
}


// **************************************************************************
// Function Name: CPictureDial::ClearContactData
// 
// Purpose: Clear the contact for the current digit
//
// Arguments:
//    IN int nItem - index of the entry to clear contact data on.  Frees all
//                   allocated memory and disassociates contact from the number
//
// Return Values:
//    NONE
//

void CPictureDial::ClearContactData(int nItem)
{
    if (m_rgContact[nItem].hBitmap != NULL)
    {
        DeleteBitmap(m_rgContact[nItem].hBitmap);
        m_rgContact[nItem].hBitmap = NULL;
    }

    delete [] m_rgContact[nItem].pszPhoneNumber;
    m_rgContact[nItem].pszPhoneNumber = NULL;
    ZeroMemory(&m_rgContact[nItem], sizeof(m_rgContact[0]));
}


// **************************************************************************
// Function Name: CPictureDial::DeleteContact
// 
// Purpose: Delete the contact from the digit association
//
// Arguments:
//    NONE
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::DeleteContact()
{
    ClearContactData(m_iSel);
    Refresh(m_iSel, -1);
    Save(m_iSel);

    return S_OK;
}


// **************************************************************************
// Function Name: CPictureDial::Refresh
// 
// Purpose: Optimization to redraw only two items instead of the full screen
//          to reduce flicker
//
// Arguments:
//    IN int nItem1 - first item to refresh
//    IN int nItem2 - second item to refresh
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::Refresh(int nItem1, int nItem2)
{   
    HDC hdc;

    hdc = GetDC(m_hWnd);
    if (nItem1 != -1)
    {
        DrawItem(hdc, nItem1);
    }

    if (nItem2 != -1 && nItem2 != nItem1)
    {
        DrawItem(hdc, nItem2);
    }

    DrawGrid(hdc);
    DrawStatus(hdc);

    ReleaseDC(m_hWnd, hdc);

    return S_OK;
}



// **************************************************************************
// Function Name: CPictureDial::DialContact
// 
// Purpose: Call the phone number of the currently selected contact
//
// Arguments:
//    NONE
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::DialContact()
{
    HRESULT  hr;
    LRESULT  lResult;
    PHONEMAKECALLINFO  mci = {0};

    CBR(m_rgContact[m_iSel].pszPhoneNumber);

    mci.cbSize = sizeof(mci);
    mci.dwFlags = 0;
    mci.pszDestAddress = m_rgContact[m_iSel].pszPhoneNumber;

    lResult = PhoneMakeCall(&mci);
    CBR(lResult != -1);

    hr = S_OK;

Error:
    return hr;
}


// **************************************************************************
// Function Name: CPictureDial::OnCommand
// 
// Purpose: Handles WM_COMMAND
//
// Arguments:
//    IN WORD wNotifyCode - notification is from control
//    IN WORD wID - identifier of menu item, control, or accelerator
//    in HWND hwndCtrl - window of the control sending the message
//
// Return Values:
//    LRESULT - returns 0 if processed
//

LRESULT CPictureDial::OnCommand(WORD wNotifyCode, WORD wID, HWND hwndCtrl)
{
    switch (wID)
    {
        case IDM_SET:
            SetContact();
            break;

        case IDM_DELETE:
            DeleteContact();
            break;

        case IDM_EXIT:
            PostMessage(m_hWnd, WM_CLOSE, 0, NULL);
            break;

        case IDM_DIAL:
            DialContact();
            break;
    }

    return 0;
}


// **************************************************************************
// Function Name: CPictureDial::DrawBitmap
// 
// Purpose: Draws the bitmap within the entry square
//
// Arguments:
//    IN HDC hdc - DC for drawing
//    IN int x   - horizontal location of upper left hand corner of drawing area
//    IN int y   - vertical location of upper left hand corner of drawing area
//    IN CONTACTINFO pContact - contains bitmap info for the contact to draw
//    IN int nItem - index of current item
//
// Return Values:
//    NONE
//

void CPictureDial::DrawBitmap(HDC hdc, int x, int y, CONTACTINFO* pContact, int nItem)
{
    HRESULT  hr;
    HBITMAP  hOldBitmap = NULL;
    HDC      hdcSrc = NULL;
    RECT     rc = {x, y, x+m_uItemWidth, y+m_uItemHeight};
    COLORREF clrBack;
    UINT     uItemWidth  = m_uItemWidth-BORDERSIZE-CXGUTTER*2; 
    UINT     uItemHeight = m_uItemHeight-BORDERSIZE-CYGUTTER*2; 
    UINT     xOffset = (uItemWidth  >= pContact->dxBitmap ? (uItemWidth-pContact->dxBitmap)/2 : 0);
    UINT     yOffset = (uItemHeight >= pContact->dyBitmap ? (uItemHeight-pContact->dyBitmap)/2 : 0);

    hdcSrc = CreateCompatibleDC(hdc);
    CBR(hdcSrc != NULL);

    hOldBitmap = SelectBitmap(hdcSrc, pContact->hBitmap);
    CBR(hOldBitmap != NULL);

    // Select the color depending on if we're drawing the active entry
    clrBack = (m_iSel == nItem ? GetSysColor(COLOR_HIGHLIGHT) : GetSysColor(COLOR_WINDOW));

    // Color the background first
    DrawRect(hdc, &rc, clrBack);
    
    // Draw the image
    BitBlt(hdc, x+CXGUTTER+xOffset, y+CYGUTTER+yOffset, pContact->dxBitmap, pContact->dyBitmap, hdcSrc, 0, 0, SRCCOPY);

Error:    
    if (hOldBitmap)
    {
        SelectBitmap(hdcSrc, hOldBitmap);
    }

    if (hdcSrc)
    {
        DeleteDC(hdcSrc);
    }

    return;
}


// **************************************************************************
// Function Name: CPictureDial::DrawDigit
// 
// Purpose: Draws a digit within the drawing area
//
// Arguments:
//    IN HDC hdc - DC for drawing
//    IN int x   - horizontal location of upper left hand corner of drawing area
//    IN int y   - vertical location of upper left hand corner of drawing area
//    IN CONTACTINFO* pContact - contains bitmap info for the contact to draw
//    IN int nItem - index of current item
//
// Return Values:
//    NONE
//

void CPictureDial::DrawDigit(HDC hdc, int x, int y, CONTACTINFO* pContact, int nItem)
{
    TEXTMETRIC textmetric;
    HFONT      hOldFont = NULL;
    int        iHeight;
    TCHAR      szNum[3] = {0};
    COLORREF   clrOldText = CLR_INVALID;
    COLORREF   clrOldBack = CLR_INVALID;
    UINT       uiOldTextAlign = GDI_ERROR;
    RECT       rc = { x, y, x+m_uItemWidth, y+m_uItemHeight };

    hOldFont = SelectFont(hdc, m_hFont);
    GetTextMetrics(hdc, &textmetric);

    iHeight = textmetric.tmHeight + textmetric.tmExternalLeading;

    if (m_rgContact[nItem].pszPhoneNumber != NULL)
    {
        // The contact has no phone number
        StringCchCopy(szNum, ARRAYSIZE(szNum), _T("?"));
    }
    else
    {
        // No contact, so draw the index
        StringCchPrintf(szNum, ARRAYSIZE(szNum), _T("%d"), nItem+1);
        clrOldText = SetTextColor(hdc, RGB(0xDF,0xDF,0xDF));
    }

    uiOldTextAlign = SetTextAlign(hdc, TA_CENTER);
    clrOldBack = SetBkColor(hdc, (m_iSel == nItem ? GetSysColor(COLOR_HIGHLIGHT) : GetSysColor(COLOR_WINDOW)));

    // Draw the text into the square
    ExtTextOut(hdc, x+m_uItemWidth/2-BORDERSIZE/2, y+(m_uItemHeight/2)-iHeight/2-BORDERSIZE/2, ETO_OPAQUE | ETO_CLIPPED, &rc, szNum, lstrlen(szNum), NULL);

    if (clrOldText != CLR_INVALID)
    {
        SetTextColor(hdc, clrOldText);
    }

    if (clrOldBack != CLR_INVALID)
    {
        SetBkColor(hdc, clrOldBack);
    }

    if (uiOldTextAlign != GDI_ERROR)
    {
        SetTextAlign(hdc, uiOldTextAlign);
    }

    if (hOldFont)
    {
        SelectFont(hdc, hOldFont);
    }
}


// **************************************************************************
// Function Name: CPictureDial::DrawItem
// 
// Purpose: Handles WM_COMMAND
//
// Arguments:
//    IN HDC hdc - DC for drawing
//    IN int nItem - the entry to draw
//
// Return Values:
//    NONE
//

void CPictureDial::DrawItem(HDC hdc, int nItem)
{
    int x = (nItem % NUMCOLUMNS)*m_uItemWidth;
    int y = (nItem / NUMCOLUMNS)*m_uItemHeight;

    CONTACTINFO* pContact = &m_rgContact[nItem];

    if (pContact->hBitmap)
    {
        // If the contact has a picture, draw the picture in the space
        DrawBitmap(hdc, x, y, pContact, nItem);
    }
    else
    {
        // Either slot is empty or the contact has no picture
        DrawDigit(hdc, x, y, pContact, nItem);
    }
}


// **************************************************************************
// Function Name: CPictureDial::DrawStatus
// 
// Purpose: Draw the status bar with the phone number
//
// Arguments:
//    IN HDC hdc - DC for drawing
//
// Return Values:
//    NONE
//

void CPictureDial::DrawStatus(HDC hdc)
{
    RECT rc;
    LPCTSTR   pszPhoneNumber = m_rgContact[m_iSel].pszPhoneNumber;

    // Find the bottom of the visible area
    GetClientRect(m_hWnd, &rc);
    rc.top = rc.bottom - CYSTATUS;

    // Clear the space of any old phone numbers
    DrawRect(hdc, &rc, GetSysColor(COLOR_WINDOW));

    // Draw the phone number
    if (pszPhoneNumber)
    {
        ExtTextOut(hdc, rc.left+CXGUTTER, rc.top, ETO_OPAQUE | ETO_CLIPPED, &rc, pszPhoneNumber, lstrlen(pszPhoneNumber), NULL);
    }
}


// **************************************************************************
// Function Name: CPictureDial::DrawGrid
// 
// Purpose: Draw the status bar with the phone number
//
// Arguments:
//    IN HDC hdc - DC for drawing
//
// Return Values:
//    NONE
//

void CPictureDial::DrawGrid(HDC hdc)
{
    RECT rcOrig;
    RECT rc;
    GetClientRect(m_hWnd, &rcOrig);

    // Draw the vertical lines
    rc = rcOrig;

    for (UINT iCol=1; iCol<NUMCOLUMNS; iCol++)
    {
        rc.left = iCol*m_uItemWidth-1;
        rc.right = rc.left+BORDERSIZE;
        DrawRect(hdc, &rc, RGB(0xDF,0xDF,0xDF));
    }

    // Draw the horizontal lines
    rc = rcOrig;

    for (UINT iRow=1; iRow<=NUMROWS; iRow++)
    {
        rc.top = iRow*m_uItemHeight-1;
        rc.bottom = rc.top+BORDERSIZE;
        DrawRect(hdc, &rc, RGB(0xDF, 0xDF, 0xDF));
    }
}


// **************************************************************************
// Function Name: CPictureDial::CreateCustomFont
// 
// Purpose: Create a font of the given height and weight
//
// Arguments:
//    IN HWND  hwnd    - HWND to get the default font family
//    IN int   iHeight - height in points
//    IN BOOL  fBold   - bold or regular
//
// Return Values:
//    HFONT - created font
//
HFONT CPictureDial::CreateCustomFont(HWND hwnd, int iHeight, BOOL fBold)
{
    HFONT hSysFont;
    HFONT hFontNew = NULL;

    // Get the system font
    hSysFont = (HFONT) GetStockObject(SYSTEM_FONT);
    if (hSysFont)
    {
        LOGFONT lf;
        GetObject(hSysFont, sizeof(LOGFONT), &lf);

        if (iHeight)
        {
            HDC hdc = GetDC(hwnd);
            if (hdc) 
            {
                // Convert pixel height to LOGFONT height
                lf.lfHeight = - MulDiv(iHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72);
                ReleaseDC(hwnd, hdc);
            }
        }
        
        if (fBold)
        {
            lf.lfWeight = FW_BOLD;
        }
        
        hFontNew = CreateFontIndirect(&lf);
    }
    
    return hFontNew;
}


// **************************************************************************
// Function Name: CPictureDial::OnPaint
// 
// Purpose: Draw the status bar with the phone number
//
// Arguments:
//    NONE
//
// Return Values:
//    LRESULT - returns 0 if processed
//

LRESULT CPictureDial::OnPaint()
{
    BOOL fNeedUpdate;
    RECT rc;

    fNeedUpdate = GetUpdateRect(m_hWnd, &rc, TRUE);
    if (fNeedUpdate)
    {
        PAINTSTRUCT ps;
        HDC hdc;
        RECT;

        // Create the font if it's the first time we're drawing
        if (m_hFont == NULL)
        {
            m_hFont = CreateCustomFont(NULL, 40, TRUE);
        }

        hdc = BeginPaint(m_hWnd, &ps);

        // Paint each square
        for (UINT iCol=0; iCol<NUMCOLUMNS; iCol++)
        {
            for (UINT iRow=0; iRow<NUMROWS; iRow++)
            {
                UINT i = (iCol+iRow*NUMCOLUMNS);

                DrawItem(hdc, i);
            }
        }

        // Draw the lines around the square
        DrawGrid(hdc);

        // Draw the phone number in the status area
        DrawStatus(hdc);

        EndPaint(m_hWnd, &ps);
    }

    return 0;
}


// **************************************************************************
// Function Name: CPictureDial::OnKeyDown
// 
// Purpose: Advances the cursor forward or backwards based on the virtual
//          key code
//
// Arguments:
//    WORD vk - virtual key code
//
// Return Values:
//    LRESULT - returns 0 if processed
//

LRESULT CPictureDial::OnKeyDown(WORD vk)
{
    UINT iOldSel = m_iSel;
    BOOL fDial = FALSE;

    switch (vk)
    {
        case VK_LEFT:
        {
            // Move left one spot
            if (m_iSel > 0)
            {
                m_iSel--;
            }
            break;
        }
            
        case VK_RIGHT:
        {
            // Move right one spot
            if (m_iSel < NUMITEMS-1)
            {
                m_iSel++;
            }
            break;
        }

        case VK_UP:
        {
            // Move up a row
            if (m_iSel >= NUMCOLUMNS)
            {
                m_iSel -= NUMCOLUMNS;
            }
            break;
        }

        case VK_DOWN:
        {
            // Move down a row
            if (m_iSel < NUMITEMS-NUMCOLUMNS)
            {
                m_iSel += NUMCOLUMNS;
            }
            break;
        }

    }

    // For digits, dial the phone number
    if (vk >= '1' && vk <= '9')
    {
        m_iSel = vk-'1';
        fDial = TRUE;
    }

    // If we moved to a different square, redraw the old square
    // and new square to update the highlight
    if (iOldSel != m_iSel)
    {
        Refresh(iOldSel, m_iSel);
    }

    if (fDial != FALSE)
    {
        DialContact();
    }

    return 0;
}


// **************************************************************************
// Function Name: CPictureDial::LoadAllContacts
// 
// Purpose: Load the settings for all the contacts
//
// Arguments:
//    NONE
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::LoadAllContacts()
{
    for (int i=0; i<NUMITEMS; i++)
    {
        LoadContact(i);
    }

    return S_OK;
}


// **************************************************************************
// Function Name: CPictureDial::LoadContact
// 
// Purpose: Load a single contact from the registry
//
// Arguments:
//    IN int  nItem - index of the contact to load
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::LoadContact(int nItem)
{
    HRESULT hr;
    LRESULT lResult;
    HKEY    hKey;
    TCHAR   szKey[ARRAYSIZE(c_szRegSaveFormat)+10];
    TCHAR   szPhoneNumber[MAXPHONE];
    LPTSTR  pszPhoneNumber = NULL;
    UINT    cchPhoneNumber;
    CEOID   oid;
    HBITMAP hBitmap = NULL;
    UINT    dx = m_uItemWidth-BORDERSIZE-CXGUTTER*2;
    UINT    dy = m_uItemHeight-BORDERSIZE-CYGUTTER*2;
    DWORD   dwSize;

    StringCchPrintf(szKey, ARRAYSIZE(szKey), c_szRegSaveFormat, nItem);

    lResult = RegOpenKeyEx(HKEY_CURRENT_USER, szKey, 0, KEY_QUERY_VALUE, &hKey);
    CBR(lResult == ERROR_SUCCESS);

    dwSize = sizeof(szPhoneNumber);
    lResult = RegQueryValueEx(hKey, c_szRegValuePhoneNumber, NULL, NULL, (LPBYTE) szPhoneNumber, &dwSize);
    CBR(lResult == ERROR_SUCCESS);

    dwSize = sizeof(oid);
    lResult = RegQueryValueEx(hKey, c_szRegValueOID, NULL, NULL, (LPBYTE) &oid, &dwSize);
    CBR(lResult == ERROR_SUCCESS);

    cchPhoneNumber = lstrlen(szPhoneNumber)+1;
    pszPhoneNumber = new TCHAR[cchPhoneNumber];
    CPR(pszPhoneNumber);

    StringCchCopy(pszPhoneNumber, cchPhoneNumber, szPhoneNumber);

    FindBitmap(oid, &hBitmap, &dx, &dy);

    m_rgContact[nItem].oid = oid;
    m_rgContact[nItem].pszPhoneNumber = pszPhoneNumber;
    m_rgContact[nItem].hBitmap = hBitmap;
    m_rgContact[nItem].dxBitmap = dx;
    m_rgContact[nItem].dyBitmap = dy;
    hBitmap = NULL;
    pszPhoneNumber = NULL;

    hr = S_OK;

Error:
    delete [] pszPhoneNumber;

    if (hKey)
    {
        RegCloseKey(hKey);
    }

    if (hBitmap)
    {
        DeleteBitmap(hBitmap);
    }
    return hr;
}



// **************************************************************************
// Function Name: CPictureDial::Save
// 
// Purpose: Save contact information for the given index
//
// Arguments:
//    IN int  nItem - the index of the contact to save
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//

HRESULT CPictureDial::Save(int nItem)
{
    HRESULT hr;
    LRESULT lResult;
    HKEY hKey = NULL;
    DWORD dwDisposition;
    TCHAR szKey[ARRAYSIZE(c_szRegSaveFormat)+10];

    StringCchPrintf(szKey, ARRAYSIZE(szKey), c_szRegSaveFormat, nItem);

    if (m_rgContact[nItem].pszPhoneNumber != NULL)
    {
        UINT  cbPhoneNumber;

        lResult = RegCreateKeyEx(HKEY_CURRENT_USER, szKey, 0, NULL, 0, KEY_ALL_ACCESS,
                                 NULL, &hKey, &dwDisposition);
        CBR(lResult == ERROR_SUCCESS);

        // Save the NULL along with the string
        cbPhoneNumber = (lstrlen(m_rgContact[nItem].pszPhoneNumber)+1)*sizeof(m_rgContact[nItem].pszPhoneNumber[0]);

        lResult = RegSetValueEx(hKey, c_szRegValuePhoneNumber, NULL, REG_SZ,
                                (LPBYTE) m_rgContact[nItem].pszPhoneNumber,
                                cbPhoneNumber);
        CBR(lResult == ERROR_SUCCESS);

        lResult = RegSetValueEx(hKey, c_szRegValueOID, NULL, REG_DWORD,
                                (LPBYTE) &m_rgContact[nItem].oid, sizeof(m_rgContact[nItem].oid));
        CBR(lResult == ERROR_SUCCESS);
    }
    else
    {
        RegDeleteKey(HKEY_CURRENT_USER, szKey);
    }

    hr = S_OK;

Error:
    if (hKey)
    {
        RegCloseKey(hKey);
    }
    return hr;
}


// **************************************************************************
// Function Name: CPictureDial::_WndProc
// 
// Purpose: winproc
//
// Arguments:
//    IN HWND hWnd     - handle to the window
//    IN UINT uMsg     - specifies the message
//    IN WPARAM wParam - specifies additional message information
//    IN LPARAM lParam - specifies additional message information
//
// Return Values:
//    LRESULT - result of the message processing and depends on the message sent
//

LRESULT CALLBACK CPictureDial::_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = 0;
    CPictureDial* pThis = (CPictureDial*) GetWindowLong(hWnd, GWL_USERDATA);

    switch (uMsg)
    {
        case WM_CREATE:
        {
            LPCREATESTRUCT  pCreate = (LPCREATESTRUCT) lParam;

            lResult = -1;
            if (pCreate)
            {
                pThis = (CPictureDial*) pCreate->lpCreateParams;
                if (pThis)
                {
                    SetWindowLong(hWnd, GWL_USERDATA, (LONG) pThis);
                    lResult = pThis->OnCreate(hWnd);
                }
            }

            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            lResult = pThis->OnCommand(HIWORD(wParam), LOWORD(wParam), (HWND) lParam);
            break;

        case WM_PAINT:
            lResult = pThis->OnPaint();
            break;

        case WM_KEYDOWN:
            lResult = pThis->OnKeyDown(wParam);
            break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return lResult;
}



