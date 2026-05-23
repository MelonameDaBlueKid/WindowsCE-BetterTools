
#pragma once


extern HINSTANCE g_hInstRes;
extern HINSTANCE g_hInst;

#define PROP_TAG(ulPropType,ulPropID)  ((((ULONG)(ulPropID))<<16)|((ULONG)(ulPropType)))

#define  ARRAYSIZE(a) (sizeof(a)/ sizeof(a[0]))


HRESULT ActivatePreviousInstance(const TCHAR* pszClass, const TCHAR* pszTitle, BOOL* pfActivated);
DWORD FormatMessageHelp(TCHAR* pszOut, UINT cchOut, const TCHAR* pszFormat, ...);
int FormattedMessageBox(HWND hwnd, UINT uType, HINSTANCE hInst, UINT idsCaption, UINT idsFormat, ...);
void DisplayError(HWND hWndOwner, HINSTANCE hInst, UINT idsCaption, UINT idsFormat, HRESULT hr);
void GetSystemTimeAsFileTime(FILETIME* pSystemAsFileTime);
HRESULT GetFileTimeForDate(int iYear, int iMonth, int iDay, FILETIME* pft);


