#include <windows.h>
#include "misc.h"

BOOL SupportIntlPlus(void)
{
    return TRUE;
}


BOOL UseBoldFont(void)
{
    return TRUE;
}


HWND 
CreateFullScreenWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, 
                   HWND hWndParent, HMENU hMenu, HANDLE hInstance, LPVOID lpParam)
{
    RECT rc;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

    return CreateWindow(lpClassName, lpWindowName, dwStyle, 
                        rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 
                        hWndParent, hMenu, (HINSTANCE)hInstance, lpParam);
}