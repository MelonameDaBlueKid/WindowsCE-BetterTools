//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#pragma once

#include <imaging.h>
#include <pimstore.h>




enum
{
    CXGUTTER    = 4,                   // horizontal margin for each square
    CYGUTTER    = 4,                   // vertical margin for each square
    CYSTATUS    = 20,                  // height of the status bar to display phone number
    NUMCOLUMNS  = 3,                   // number of columns for display
    NUMROWS     = 3,                   // number of rows for display
    BORDERSIZE  = 1,                   // size of the border
    MAXPHONE    = 50,                  // maximum length of a phone number
    NUMITEMS    = NUMCOLUMNS*NUMROWS,  // number of squares
};




struct CONTACTINFO
{
    CEOID   oid;             // ID of the contact
    HBITMAP hBitmap;         // handle to bitmap of the picture
    UINT    dxBitmap;        // bitmap width
    UINT    dyBitmap;        // bitmap height
    LPTSTR  pszPhoneNumber;  // phone number for contact
};



class CPictureDial
{
public:
    CPictureDial();
    ~CPictureDial();

    static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
    LRESULT OnCreate(HWND hWnd);
    LRESULT OnCommand(WORD wNotifyCode, WORD wID, HWND hwndCtrl);
    LRESULT OnPaint();
    HRESULT SetContact();
    HRESULT DeleteContact();
    LRESULT OnKeyDown(WORD vk);

    HRESULT EnsurePOOM();
    HRESULT AssociateContact(CEOID oid, LPCTSTR pszPhoneNumber);
    void    DrawItem(HDC hdc, int iItem);
    void    DrawGrid(HDC hdc);
    void    DrawStatus(HDC hdc);
    void    DrawBitmap(HDC hdc, int x, int y, CONTACTINFO* pContact, int nItem);
    void    DrawDigit(HDC hdc, int x, int y, CONTACTINFO* pContact, int nItem);
    void    ClearContactData(int iItem);
    HRESULT DialContact();
    HRESULT FindBitmap(CEOID oid, HBITMAP* phBitmap, UINT* pcxPic, UINT* pcyPic);
    HRESULT Save(int iItem);
    HRESULT LoadContact(int iItem);
    HRESULT LoadAllContacts();
    HRESULT Refresh(int iItem1, int iItem2);
    HFONT   CreateCustomFont(HWND hwnd, int iHeight, BOOL fBold);

private:
    HWND           m_hWnd;                  // handle to main window
    CONTACTINFO    m_rgContact[NUMITEMS];   // cache of contact pictures and phone numbers
    UINT           m_uItemWidth;            // width of each square
    UINT           m_uItemHeight;           // height of each square
    IPOutlookApp2* m_pOutlookApp;           // interface to POOM
    UINT           m_iSel;                  // active square
    HFONT          m_hFont;                 // font for drawing text
};

