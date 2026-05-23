// ***********************************************************************
//
// AutoRun.cpp
//
// This sample source code is provided as is, to demonstrate how to
// install Windows CE CAB files from a Compact Flash (CF) Card to
// Pocket PC devices.
//
// Function:
//  
//  On CF Card insertion, the app:
//  - searches for the CF Card folder name
//  - looks for the current cpu folder
//  - checks if each CAB file in this folder is already installed
//  - installs the CAB files if not installed
//
// Assumptions:
//
//  1) This app assumes that the CE CAB files to install are:
//     - renamed to the following format:
//          "<Provider> <AppName>"
//       and have the ".CAB" extension. This is used to check if the app
//       is already installed.
//
//     - stored in cpu-specific folders at the root of the CF Card - eg:
//          \4000\Microsoft SampleApp.mips.cab
//          \10003\Microsoft SampleApp.sh3.cab
//
//  2) The created file must be named "autorun.exe", and stored in a
//     cpu-specific folder at the root of the CF Card. Alternatively,
//     this file can be compiled as a CEF (Common Executable Format)
//     file, and stored in the \0 folder at the root of the CF Card - eg:
//          \0\autorun.exe
//
//  3) All the CAB files are set to read-only, so they will not be
//     dynamically deleted during install-time
//
// Notes:
//
// - This app will use the long-filename of the CAB file (before the
//   first period symbol) to determine if the app is already installed
//
// - The code can be modified to install CEF-only CAB files (it currently
//   only installs cpu-specific CAB files)
//
// - The code can be modified to perform some actions during CF Card
//   removal
//
// ***********************************************************************

#include <windows.h>
#include <tchar.h>

// AutoRun will be called with:
//      "install" on CF Card insertion
//      "uninstall" on CF Card removal
const WCHAR c_szwINSTALL[]  = L"install";

// search for all root directories on the CF Card 
const WCHAR c_szwROOT[]     = L"\\*";

// search for all CAB files
const WCHAR c_szwCAB[]      = L"\\*.CAB";

// time to wait for each install before continuing on
const DWORD c_dwTIMEOUT     = 30000;    // 30 seconds

// a top-level dir with these attributes is a flash card
const DWORD c_dwATTRIB_CF = FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_TEMPORARY;

// device-side installer program
const WCHAR c_szwAPPINST[]  = L"\\Windows\\wceload.exe";

// forward declarations
void OnCardInsert();
BOOL FInstalled(LPWSTR pszFile);

//
// WinMain
//
int WINAPI
WinMain(
    HINSTANCE   hInst,
    HINSTANCE   hInstPrev,
    LPTSTR      lpszCmdLine,
    int         nCmdShow)
{
    // on CF Card insertion, install the CAB files
    if (0 == lstrcmpi(lpszCmdLine, c_szwINSTALL))
    {
        OnCardInsert();
    }
    // otherwise, do nothing on card removal

    return 0;
}

//
// OnCardInsert()
// Install some CAB files on CF Card insertion.
//
void
OnCardInsert()
{    
    HANDLE  hFind   = NULL;
    BOOL    fLoop   = FALSE;
    WCHAR   szwPath[MAX_PATH];  // the CF Card path
    WCHAR   szwFile[MAX_PATH];  // the current file

    WIN32_FIND_DATA     fd;
    SYSTEM_INFO         sys_info;

    PROCESS_INFORMATION pi;
    STARTUPINFO         si;

    //
    // Find the CF Card name first
    //

    // search all top-level dirs
    ZeroMemory(&fd, sizeof(fd));
    hFind = FindFirstFile(c_szwROOT, &fd);
    if (INVALID_HANDLE_VALUE == hFind)
        goto Exit;

    // loop until we find the CF Card
    szwPath[0] = 0;
    do
    {
        // check the dir attributes
        if (c_dwATTRIB_CF == (c_dwATTRIB_CF & fd.dwFileAttributes))
        {
            // we have found the first CF Card
            lstrcpy(szwPath, fd.cFileName);
            break;  // exit the loop
        }

        // get the next top-level dir
        fLoop = FindNextFile(hFind, &fd);
    } while (fLoop);

    FindClose(hFind);
    hFind = NULL;

    // exit if we did not find a CF Card
    if (!szwPath[0])
        goto Exit;

    //
    // Check if there is a dir with the current CPU value.
    // If so, install all the CPU-specific CAB files from this dir.
    //
    // Note: this can be modified to install CEF-compiled CAB files
    // from a different dir
    //

    // get the CPU value
    ZeroMemory(&sys_info, sizeof(sys_info));
    GetSystemInfo(&sys_info);
    
    // construct the dir name using the CPU value
    wsprintf(szwFile, L"\\%d", sys_info.dwProcessorType);
    // concatenate the dir name to the CF Card path
    lstrcat(szwPath, szwFile);

    // find all the CAB files in this dir
    wsprintf(szwFile, L"%s%s", szwPath, c_szwCAB);
    ZeroMemory(&fd, sizeof(fd));
    hFind = FindFirstFile(szwFile, &fd);
    if (INVALID_HANDLE_VALUE == hFind)
        goto Exit;

    // 
    // install all the CAB files if not already installed
    //
    do
    {
        // skip this app if already installed
        if (!FInstalled(fd.cFileName))
        {
            // create the full filename of the CAB file (enclosed in quotes)
            wsprintf(szwFile, L"\"%s\\%s\"", szwPath, fd.cFileName);

            // Install the app by running the device-side installer with
            // the CAB file as a parameter.
            //
            // Using CreateProcess() will allow us to wait for the process to complete.
            // This can be changed to ShellExecuteEx() to run the CAB file directly, but
            // we will not be able to wait for the process to complete.
            ZeroMemory(&pi, sizeof(pi));
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            if (CreateProcess(c_szwAPPINST, szwFile, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
            {
                // wait until the process is done (for up to 30 seconds)
                WaitForSingleObject(pi.hProcess, c_dwTIMEOUT);
            }
        }

        // find the next CAB when done waiting
        fLoop = FindNextFile(hFind, &fd);
    } while (fLoop);
    FindClose(hFind);

Exit:
    return;
}

//
// AppInstall registry entries
//

// reg key (in HKLM) containing the installed applications' "home" reg key
const WCHAR c_szRKEY_HOME[] = L"Software\\Apps";
const DWORD c_cchRKEY       = lstrlen(c_szRKEY_HOME);

// reg val to specify if the app is currently installed
const WCHAR c_szRVAL_INST[] = L"Instl";

//
// FInstalled()
//
// Check if the CAB file is already installed, by checking if the filename
// (which is assumed to be the full name of the app) is currently installed.
//
BOOL
FInstalled(LPWSTR pszFile)
{
    BOOL    fInstalled  = FALSE;    // assume the app is not installed
    HKEY    hkey        = NULL;
    LPWSTR  pszApp      = NULL;
    LPWSTR  pszExt      = NULL;
    DWORD   dwVal       = 0;
    DWORD   cbData      = sizeof(dwVal);
    DWORD   dwType      = 0;
    long    lErr        = 0;
    WCHAR   szBuf[MAX_PATH];

    // given the filename, create the app's "home" registry key
    wsprintf(szBuf, L"%s\\%s", c_szRKEY_HOME, pszFile);

    // Remove any text following the filename's first period character.
    // This will include any extra CPU text and the .CAB file extension
    
    pszApp = &szBuf[c_cchRKEY];     // point to the filename in our buffer
    pszExt = _tcsstr(pszApp, L"."); // find the first period character
    // remove the text
    if (pszExt)
        *pszExt = 0;

    // check if this app is in the app's home registry key
    lErr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szBuf, 0, KEY_READ, &hkey);
    if (ERROR_SUCCESS != lErr)
        goto Exit;

    // check if the app is installed
    lErr = RegQueryValueEx(hkey, c_szRVAL_INST, NULL, &dwType, (LPBYTE)&dwVal, &cbData);
    if (ERROR_SUCCESS != lErr)
        goto Exit;

    if (dwVal)
        fInstalled = TRUE;

Exit:
    if (hkey)
        RegCloseKey(hkey);

    return fInstalled;
}
