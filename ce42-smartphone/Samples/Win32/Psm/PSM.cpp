///////////////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  This is "Sample Code" and is distributable subject to the terms of the end
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////
//
// PSM.CPP
//
// PSM Smartphone Platform Application
//
///////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//     On Smartphone the contents of '\windows' is lost when the phone is
//     turned off. This sample demonstrates how to ensure that data stored
//     in the file system survives a power off by storing it within the special
//     folder identified by CSIDL_APPDATA. This folder is part of a persistent
//     storage area known as the PSM.
//
//     This sample creates a folder within CSIDL_APPDATA which could serve as
//     a container for application-specific files which must survive power off.
//

#include <windows.h>
#include <windowsx.h>
#include <aygshell.h>
#include "resource.h"

#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))
#define MSGBUFSIZE   (MAX_PATH+100)


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    TCHAR  tszPersistentFolder[MAX_PATH];
	TCHAR  tszMessage[MSGBUFSIZE];
	size_t cLen;
    HANDLE hMutex = NULL;
	BOOL   bCreated = FALSE;

    LPCTSTR lpctszAppName;
    
    lpctszAppName = (LPCTSTR)LoadString(hInstance, IDS_APPNAME, NULL, 0);

    // We want to create a folder within the PSM
    // This #ifdef/#else ensures code compatibility with platforms that
    // don't support CSIDL_APPDATA (Pocket PC 2000/2002, other CE devices)
#ifdef CSIDL_APPDATA
	if(!SHGetSpecialFolderPath(NULL, tszPersistentFolder, CSIDL_APPDATA, TRUE))
	{
        OutputDebugString(TEXT("SHGetSpecialFolderPath Failed\n"));
        return 0;
	}
#else
	// CSIDL_APPDATA is not defined. By default, create our folder at the root
	_tcscpy(tszPersistentFolder, TEXT("\\"));
#endif

	cLen = _tcslen(tszPersistentFolder);

    // Add an trailing '\' char
    if (tszPersistentFolder[cLen - 1] != TEXT('\\'))
	{	
		_tcscpy(&tszPersistentFolder[cLen], TEXT("\\"));
		cLen++;
	}

    if (cLen + _tcslen(lpctszAppName) + 1 > ARRAYSIZE(tszPersistentFolder))
	{
        OutputDebugString(TEXT("Not enough space to build folder name\n"));
        return 0;
	}


    // Build final folder path
	_tcscpy(&tszPersistentFolder[cLen], lpctszAppName);

	// Create folder, if it doesn't already exist. We want to ensure that the
	// test-and-create is atomic, so wrap it within a mutex
	hMutex = CreateMutex(NULL, FALSE, TEXT("__PSMAPP_MUTEX__")); 
	if (NULL == hMutex)
    {
        OutputDebugString(TEXT("CreateMutex Failed\n"));
	    return 0;
	}
    else if (ERROR_ALREADY_EXISTS == GetLastError())
    {
        OutputDebugString(TEXT("Mutex already exists"));
        CloseHandle(hMutex);
        return 0;
    }

	WaitForSingleObject(hMutex,INFINITE);
	if (0xFFFFFFFF == GetFileAttributes(tszPersistentFolder))
	{	// Folder does not already exist, so create it
		if(0 == CreateDirectory(tszPersistentFolder, NULL))
		{
	        OutputDebugString(TEXT("CreateDirectory Failed\n"));
			ReleaseMutex(hMutex);
			CloseHandle(hMutex);
		    return 0;
		}
		bCreated = TRUE;
	}
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

    if (TRUE == bCreated)
    {
        _stprintf(tszMessage,TEXT("%s %s"),
		     (LPCTSTR)LoadString(hInstance, IDS_NEWFOLDER, NULL, 0),
			 tszPersistentFolder);
    }
    else
    {
        _stprintf(tszMessage,TEXT("%s %s"),
		     (LPCTSTR)LoadString(hInstance, IDS_FOLDEREXISTS, NULL, 0),
			 tszPersistentFolder);
    }

	MessageBox (NULL, tszMessage, lpctszAppName, MB_OK);

	return 0;
}
