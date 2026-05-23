
// Sample CESetup DLL

#include <windows.h>
#include <tchar.h>
#include "ce_setup.h"

const TCHAR szTITLE[]       = TEXT("CESetup Sample DLL");
const TCHAR szINST_INIT[]   = TEXT("Install_Init\n\nContinue?");
const TCHAR szINST_EXIT[]   = TEXT("Install_Exit\n\nContinue?");
const TCHAR szUNINST_INIT[] = TEXT("Uninstall_Init\n\nContinue?");
const TCHAR szUNINST_EXIT[] = TEXT("Uninstall_Exit");

BOOL WINAPI DllMain(HANDLE hMod, DWORD dwReason, LPVOID lpvReserved)
{
	return TRUE;
}

codeINSTALL_INIT Install_Init(
  HWND    hwndParent,
  BOOL    fFirstCall,
  BOOL    fPreviouslyInstalled,
  LPCTSTR pszInstallDir)
{
  if (IDOK == MessageBox(hwndParent, szINST_INIT, szTITLE, MB_OKCANCEL))
    return codeINSTALL_INIT_CONTINUE;
  else
    return codeINSTALL_INIT_CANCEL;
}

codeINSTALL_EXIT Install_Exit(
  HWND    hwndParent,
  LPCTSTR pszInstallDir,
  WORD    cFailedDirs,
  WORD    cFailedFiles,
  WORD    cFailedRegKeys,
  WORD    cFailedRegVals,
  WORD    cFailedShortcuts)
{
  if (IDOK == MessageBox(hwndParent, szINST_EXIT, szTITLE, MB_OKCANCEL))
    return codeINSTALL_EXIT_DONE;
  else
    return codeINSTALL_EXIT_UNINSTALL;
}

codeUNINSTALL_INIT Uninstall_Init(HWND hwndParent, LPCTSTR pszInstallDir)
{
  if (IDOK == MessageBox(hwndParent, szUNINST_INIT, szTITLE, MB_OKCANCEL))
    return codeUNINSTALL_INIT_CONTINUE;
  else
    return codeUNINSTALL_INIT_CANCEL;
}

codeUNINSTALL_EXIT Uninstall_Exit(HWND hwndParent)
{
  MessageBox(hwndParent, szUNINST_EXIT, szTITLE, MB_OK);
  return codeUNINSTALL_EXIT_DONE;
}
