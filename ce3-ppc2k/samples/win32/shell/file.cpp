// file.cpp : File operations go here
//

#include "stdafx.h"


//////////////////////////////////////
// Global Variables Set in this file
//////////////////////////////////////
BOOL	g_fModified = FALSE;
TCHAR	*g_szFile	= NULL;


//////////////////////////////////////
// Foward declarations of functions included in this code module:
//////////////////////////////////////
static LONG GetFileNameOffset(const TCHAR *pPathName);
static BOOL Load();
static BOOL Save();


//////////////////////////////////////
// Local Definitions
//////////////////////////////////////
#define SZ_UNSAVEDCHANGES	TEXT("There are unsaved changes, save them now?")
#define SZ_APPNAME			TEXT("Shell")
#define SZ_FILEFILTER		TEXT("Bitmap Files (*.2bp)\0*.2bp\0All Files (*.*)\0*.*\0")
#define SZ_DEFEXT			TEXT("2bp")


//////////////////////////////////////
// Functions Segment
//////////////////////////////////////


//
//  FUNCTION: GetFileNameOffset(const TCHAR*)
//
//  PURPOSE:  return the charpos of the first character in the filename portion.
//
LONG GetFileNameOffset(const TCHAR *pPathName)
{
int i;
	
    for (i = _tcslen(pPathName); i > 0; i--)
    {
        if ((pPathName[i-1] == _T('\\')) || (pPathName[i-1] == _T(':')))
            break;
    }
    return i;
}


//
//  FUNCTION: Load()
//
//  PURPOSE:  Open a file from a filename
//
BOOL Load()
{
	wsprintf(g_szHello, TEXT("Loaded file %s"), g_szFile);
	EnablePropertyItem();
	return TRUE;
}

//
//  FUNCTION: Save()
//
//  PURPOSE:  Write a file to a filename
//
//  COMMENTS: This includes one possible workaround for a FileOpen bug.
//            This bug shows up when the original filename is blank and the 
//			  Options dialog is never brought up.  Instead of returning 
//			  \My Documents\t.2bp GetSaveFileName will return \\My Documents\t.
//
BOOL Save()
{
LPTSTR szHead = g_szFile;
LPTSTR szTail = NULL;

	if (!g_szFile)
		return FALSE;
	
	//
	// Workaround Open bugs 
	//
	// 1. Sometimes returns a network path
	if ((g_szFile[0] == g_szFile[1]) && (g_szFile[1] == _T('\\')))
		szHead = &g_szFile[1];

	// 2. doesn't always put on the defext
	int iLen = _tcslen(g_szFile) - 1;
	if (g_szFile[iLen] == _T('.')) {
		szTail = wcschr(g_szFile, _T('.'));
		*(szTail + 1) = _T('\0');
	}

	// 3. Create new filename string
	TCHAR szFileFixed[MAX_PATH + 4];
	wsprintf(szFileFixed, TEXT("%s%s"), szHead, (szTail) ? SZ_DEFEXT : _T("\0"));
	
	// 4. Change Global filename variable
	free(g_szFile);
	g_szFile = wcsdup(szFileFixed);

	//TODO: Put the code here to save the file for real
	//
	//
	wsprintf(g_szHello, TEXT("Saved file %s"), g_szFile);

	//The file was not actually saved
	//as this is only a sample shell application
	//So set the global file name to NULL to disable 
	//the file properties menu item
	g_szFile = NULL;

	EnablePropertyItem();

	return TRUE;
}


//
//  FUNCTION: FileFolder()
//
//  PURPOSE:  Brings up standard folder dialog
//
BOOL FileFolder()
{
OPENFILENAME    ofn			= {0};
TCHAR			szBuf[1024];

	szBuf[0]			= _T('\0');
  ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= g_hwndMain;
  ofn.lpstrFilter		= SZ_FILEFILTER;
  ofn.lpstrDefExt		= SZ_DEFEXT;
	ofn.lpstrFileTitle	= szBuf;
	ofn.nMaxFileTitle	= sizeof(szBuf) / sizeof(TCHAR);
	ofn.Flags			= OFN_PROJECT | OFN_SHOW_ALL;
	if (!GetOpenFileName(&ofn)) return FALSE;

	wsprintf(g_szHello, TEXT("Selected Folder: %s"), ofn.lpstrFileTitle);
	return TRUE;
}

//
//  FUNCTION: FileOpenSave(BOOL)  {FOS_OPEN, FOS_SAVE}
//
//  PURPOSE:  Brings up standard file dialogs
//
//  COMMENTS: When the document is dirty, asks the user to save first
//
BOOL FileOpenSave(DWORD fOpen)
{
OPENFILENAME    ofn			= {0};
TCHAR			szBuf[1024];
	
    //
	// Make sure the user means it (if we're modified)
    //
	if ((fOpen == FOS_OPEN) && g_fModified)
    {
		int	iSelect = MessageBox(g_hwndMain, 
								 SZ_UNSAVEDCHANGES, 
								 SZ_APPNAME, 
								 MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1);
		
		switch (iSelect)
		{
			case IDCANCEL:
				return FALSE;

			case IDYES:
				if (!(g_szFile ? Save() : FileOpenSave(FOS_SAVE)))
					return FALSE;
		}
    }
	
    //
		// See what file the user wants
    //
		szBuf[0]		 = _T('\0');
    ofn.lStructSize	 = sizeof(OPENFILENAME);
		ofn.hwndOwner	 = g_hwndMain;
    ofn.lpstrFilter	 = SZ_FILEFILTER;
    ofn.lpstrDefExt	 = SZ_DEFEXT;
    ofn.lpstrFile	 = szBuf;
    ofn.nMaxFile	 = sizeof(szBuf) / sizeof(TCHAR);

    switch (fOpen) {
		case FOS_OPEN:
			
			ofn.Flags	 = OFN_PATHMUSTEXIST;
			if (!GetOpenFileName(&ofn)) return FALSE;
			EnablePropertyItem();
			break;

		case FOS_SAVE:

    		// use current filename
			if (g_szFile)
				_tcscpy(szBuf, g_szFile);

			ofn.Flags	 = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
			if (!GetSaveFileName(&ofn)) return FALSE;
		// Remember the filename
		// NOTE: must free g_szFile
			if (g_szFile) LocalFree(g_szFile);
			g_szFile = _tcsdup(ofn.lpstrFile);
			EnablePropertyItem();
			break;

		case FOS_PROPERTIES:

    		// use current filename - fail if no file selected
			if (!g_szFile)
      {
        MessageBox (g_hwndMain, L"Please select a file (File -> Open).", L"Info", MB_OK);
				return FALSE;
      }

			if (g_szFile)
				_tcscpy(szBuf, g_szFile);

			ofn.Flags	 = OFN_PROPERTY;
			if (!GetSaveFileName(&ofn)) return FALSE;

			wsprintf(g_szHello, TEXT("Properties now: %s"), ofn.lpstrFile);
	}
    
  // Remember the filename
	// NOTE: must free g_szFile
    if (g_szFile) LocalFree(g_szFile);
    g_szFile = _tcsdup(ofn.lpstrFile);

    // failed to copy string
		if (!g_szFile) {
			SetWindowText(g_hwndMain, SZ_APPNAME);
			return FALSE;
    }

    SetWindowText(g_hwndMain, g_szFile + GetFileNameOffset(g_szFile));

	switch (fOpen) {
		case FOS_OPEN:
			return Load();
		case FOS_SAVE:
			return Save();

	}
	return TRUE;
}
