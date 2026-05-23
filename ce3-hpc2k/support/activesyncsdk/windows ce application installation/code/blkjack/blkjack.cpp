//
// Blackjack sample app
//

#include <windows.h>
#include <tchar.h>

const TCHAR szTITLE[] = TEXT("Blackjack Sample");

int WINAPI
WinMain(
    HINSTANCE   hInst,
    HINSTANCE   hInstPrev,
    LPTSTR      lpszCmdLine,
    int         nCmdShow )
{
	MessageBox( NULL, lpszCmdLine, szTITLE, MB_OK );
	return 0;
}
