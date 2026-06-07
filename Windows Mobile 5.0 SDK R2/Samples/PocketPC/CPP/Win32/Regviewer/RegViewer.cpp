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

/*************************************************************************\
*
*  PROGRAM: RegViewer: the Registry Viewer Utility.
*  PURPOSE: To demonstrate Registry API.
*  COMMENTS:
*
\*************************************************************************/
// PsPCMonkey.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "regviewer.h"
#include <commctrl.h>

#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))

#if _WIN32_WCE < 212 // Non Pocket PC devices
#error 'This sample works on Pocket PC devices only'
#endif
#include <aygshell.h>

HANDLE hInst;
HWND   hDlg;


/*************************************************************************\
*
*  FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*  PURPOSE: Creates the dialogbox.
*
*  COMMENTS:
*
\*************************************************************************/

int APIENTRY WinMain (HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
                      
                      
{
  DWORD retCode;
  
  UNREFERENCED_PARAMETER( nCmdShow );
  UNREFERENCED_PARAMETER( lpCmdLine );
  UNREFERENCED_PARAMETER( hPrevInstance );
  
  hInst   = hInstance;
  
  
  retCode = DialogBox ((HINSTANCE)hInst, MAKEINTRESOURCE(IDD_VIEWERDLG),
    NULL, (DLGPROC)ViewerDlgProc);
  PostQuitMessage(0);
  return  (retCode);
  
}

/************************************************************************\
*
*  FUNCTION: ViewerDlgProc();
*
*  PURPOSE:  Handle the Viewer dialog box messages.
*
*  MESSAGES:
*
*    WM_INITDIALOG  - Posts WM_GETFIRSTKEY message.
*
*    WM_GETFIRSTKEY - Puts the first 4 pre-defined keys in the listbox.
*
*    IDL_LISTBOX    - Trapped when an item in the left hand listbox
*                     has been double clicked.  It posts a IDB_NEXT message.
*
*    IDL_LISTBOX2   - Trapped when an item in the right hand listbox has
*                     been double clicked.  It basically calls DisplayKeyData,
*                     which fills the Value edit fields with the data from
*                     the current key's specified value information.
*
*    IDB_PRINT      - Basically calls PrintTree() which does a recursive
*                     print of the Registry from the current key to the
*                     end of it's branches.
*
*    IDB_BACK       - Sets the dialog box with the information from the
*                     previously selected key (one closer to the root of
*                     the registry, the parent of the current key).
*
*    IDB_NEXT       - Sets the dialog box with the information on the
*                     selected key child.
*
*    IDR_FULL       - Sets a global variable used to determine if the
*                     user wants to print full Registry information
*                     or only information from keys that have value
*                     associated with it.  Variable is set to TRUE.
*
*    IDR_TRIMMED    - Same as above, only the variable is set to FALSE.
*
\************************************************************************/

int APIENTRY ViewerDlgProc ( HWND  hDlg,UINT uMsg, WPARAM  wParam, LPARAM  lParam )
{
  ULONG    KeyClassLength = 256;
  ULONG    KeyNameLength = 256;
  DWORD    indexLB;
  TCHAR     *putNullAt;
  
  static   TCHAR     RegPath[MAX_PATH]  = TEXT("");
  static   TCHAR     NameLBSelect[256]  = TEXT("");
  static   HKEY     hKeyRoot;
  static   DWORD    RegLevel;
  static   BOOL     FullBranches = TRUE;
  
  static   HANDLE   hBootIni;
  
  UNREFERENCED_PARAMETER( lParam );
  
  switch (uMsg)
  {
  case WM_INITDIALOG:
    // Post a message to get the first 4 pre-defined keys, and set
    // Full Branches to be the print default.
    PostMessage (hDlg, WM_GETFIRSTKEY, 0, 0);
    
    //Create the dialog full screen
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      SHInitDialog(&shidi);
    
    return (0);
    
  case WM_GETFIRSTKEY:
    // Initialize by putting the first 4 predefined keys of the
    // registry in the list box.
    
    SendMessage (GetDlgItem(hDlg, IDL_LISTBOX),
      LB_ADDSTRING, 0, (LONG)TEXT("HKEY_LOCAL_MACHINE"));
    
    SendMessage (GetDlgItem(hDlg, IDL_LISTBOX),
      LB_ADDSTRING, 0, (LONG)TEXT("HKEY_CURRENT_USER"));
    
    SendMessage (GetDlgItem(hDlg, IDL_LISTBOX),
      LB_ADDSTRING, 0, (LONG)TEXT("HKEY_USERS"));
    
    SendMessage (GetDlgItem(hDlg, IDL_LISTBOX),
      LB_ADDSTRING, 0, (LONG)TEXT("HKEY_CLASSES_ROOT"));
    
    hKeyRoot = 0;                   // Initialize hKeyRoot.
    return (0);
    
  case WM_COMMAND:
    
    switch (LOWORD(wParam))
    {
    case IDOK:
    case IDCANCEL:
      EndDialog (hDlg, TRUE);
      return (TRUE);
      
    case IDR_FULL:
      // If Full Branches pressed, set global var to TRUE.
      FullBranches = TRUE;
      return (0);
      
    case IDR_TRIMMED:
      // If Trimmed Branches pressed, set global var to FALSE.
      FullBranches = FALSE;
      return (0);
      
    case IDL_LISTBOX:
      // If click listbox, clear Value
      // edit fields, and execute Next functionality.
      if (  LBN_SELCHANGE == HIWORD (wParam))
      {
        SetDlgItemText (hDlg, IDE_VALUE1, TEXT(""));
        SetDlgItemText (hDlg, IDE_VALUE2, TEXT(""));
        PostMessage (hDlg, WM_COMMAND, IDB_NEXT, 0);
      }
      return (0);
      
    case IDL_LISTBOX2:
      // If click listbox, clear Value edit
      // fields, then display the key's data.
      if ( LBN_SELCHANGE == HIWORD (wParam) )
      {
        SetDlgItemText (hDlg, IDE_VALUE1, TEXT(""));
        SetDlgItemText (hDlg, IDE_VALUE2, TEXT(""));
        DisplayKeyData (hDlg, RegPath, hKeyRoot);
      }
      return (0);
      
      
    case IDB_NEXT:
      // Get the index of the cursor selection
      // in the list box.
      
      indexLB = SendMessage (GetDlgItem (hDlg, IDL_LISTBOX),
        LB_GETCURSEL, 0, 0);
      
      // If nothing is selected, flag user and return, otherwise
      // process the selected key.
      // LB_ERR indicates nothing selected.
      if (indexLB == LB_ERR)
      {
        MessageBox (hDlg, TEXT("Please select an item from the list box"),
          TEXT("Registry Viewer Utility"), MB_OK);
        return (0);
      }
      
      // If listbox item 0 is pressed, user wants to move
      // back up.  Execute the Back functionality.
      if (indexLB == 0 && hKeyRoot)
      {
        PostMessage (hDlg, WM_COMMAND, IDB_BACK, 0);
        return (0);
      }
      
      // clear previous contents first, if any.
      SetDlgItemText (hDlg, IDE_VALUE1, TEXT(""));
      SetDlgItemText (hDlg, IDE_VALUE2, TEXT(""));
      SetDlgItemText (hDlg, IDE_TEXTOUT, TEXT(""));
      // Get text from selection in LB.
      SendMessage (GetDlgItem (hDlg, IDL_LISTBOX),
        LB_GETTEXT, indexLB, (LPARAM)NameLBSelect);
      
      // Put name of chosen item in Name field.
      SetDlgItemText (hDlg, IDE_NAME, NameLBSelect);
      
      // Then clear ListBox entries.
      SendMessage (GetDlgItem (hDlg, IDL_LISTBOX),
        LB_RESETCONTENT, 0, 0);
      SendMessage (GetDlgItem (hDlg, IDL_LISTBOX2),
        LB_RESETCONTENT, 0, 0);
      
      EnumerateLevel (hDlg, NameLBSelect, RegPath, ARRAYSIZE(RegPath), &hKeyRoot);
      
      return (0);
      
      
      
    case IDB_BACK:
      
      // For this case (hRootKey = 0)you're at the top level already.
      // Tell the user, then return
      if (!hKeyRoot)
      {
        MessageBox (hDlg, TEXT("Top Level: You can not backup any further."),
          TEXT("Registry Viewer Utility"), MB_OK);
        return (0);
      }
      
      //For all remaining cases, clear the list and display boxes.
      SendMessage (GetDlgItem (hDlg, IDL_LISTBOX),
        LB_RESETCONTENT, 0, 0);
      SendMessage (GetDlgItem (hDlg, IDL_LISTBOX2),
        LB_RESETCONTENT, 0, 0);
      SetDlgItemText (hDlg, IDE_VALUE1, TEXT(""));
      SetDlgItemText (hDlg, IDE_VALUE2, TEXT(""));
      SetDlgItemText (hDlg, IDE_TEXTOUT, TEXT(""));
      
      
      // If hRootKey has a value, but the pathname is blank,
      // then you must be 1 level deep, reset to level 0 by
      // posting WM_GETFIRSTKEY.
      if (lstrcmp (RegPath, TEXT("")) == 0)
      {
        SetDlgItemText (hDlg, IDE_NAME, TEXT(""));
        PostMessage (hDlg, WM_GETFIRSTKEY, 0, 0);
        return (0);
      }
      
      
      // Two cases left.  One in which the path has only one
      // key name in it, and no back slash character (meaning
      // strrchr() will return NULL); and one the other case
      // where there are more than one key name in the path (
      // and at least one back slash for strrchr().  If this
      // is the first case, we want to fakeout EnumerateLevel
      // into thinking we just picked one of the pre-defined keys,
      // and then re-enumerate it's child keys.
      if ((putNullAt = _tcsrchr (RegPath, TEXT('\\'))) == NULL)
      {
        RegPath[0] = TEXT('\0');
        
        switch ((DWORD)hKeyRoot)
        {
        case (DWORD)HKEY_LOCAL_MACHINE:
          StringCchCopy (NameLBSelect, ARRAYSIZE(NameLBSelect), TEXT("HKEY_LOCAL_MACHINE"));
          break;
          
        case (DWORD)HKEY_USERS:
          StringCchCopy (NameLBSelect, ARRAYSIZE(NameLBSelect), TEXT("HKEY_USERS"));
          break;
          
        case (DWORD)HKEY_CURRENT_USER:
          StringCchCopy (NameLBSelect, ARRAYSIZE(NameLBSelect), TEXT("HKEY_CURRENT_USER"));
          break;
          
        case (DWORD)HKEY_CLASSES_ROOT:
          StringCchCopy (NameLBSelect, ARRAYSIZE(NameLBSelect), TEXT("HKEY_CLASSES_ROOT"));
          break;
        }
        SetDlgItemText (hDlg, IDE_NAME, NameLBSelect);
        hKeyRoot = 0;
        EnumerateLevel (hDlg, NameLBSelect, RegPath, ARRAYSIZE(RegPath), &hKeyRoot);
      }
      else
      {
        // In the final case, we can just trim the last key
        // name off the path, and re-enumerate the level.
        *putNullAt = TEXT('\0');
        putNullAt = _tcsrchr (RegPath, TEXT('\\'));
        
        if (putNullAt)
        {
          StringCchCopy (NameLBSelect, ARRAYSIZE(NameLBSelect), putNullAt+1);
          *putNullAt = TEXT('\0');
        }
        else
        {
          StringCchCopy (NameLBSelect, ARRAYSIZE(NameLBSelect), RegPath);
          *RegPath = TEXT('\0');
        }
        SetDlgItemText (hDlg, IDE_NAME, NameLBSelect);
        EnumerateLevel (hDlg, NameLBSelect, RegPath, ARRAYSIZE(RegPath), &hKeyRoot);
      }
      return (0);
      
    default:
      return (0);
      
}

}
return (FALSE);

}




/************************************************************************\
*
*  FUNCTION: EnumerateLevel();
*
*  PURPOSE: To get a valid key handle (either to determine if the one sent
*           to the function was one of the pre-defined, or to open a key
*           specified by the path), and to pass that key handle along
*           to QueryKey().
*
*           To enumerate the children of a key, you must have
*           an open handle to it.  The four top keys of the
*           Registry are predefined and open for use:
*           HKEY_LOCAL_MACHINE, HKEY_USERS, HKEY_CURRENT_USER,
*           and HKEY_CLASSES_ROOT.  These 4 can be used for
*           RegEnumKey as is; but to RegEnumKey on any of the
*           children of these you must first have an open key
*           handle to the child.
*
*           If hKeyRoot != 0, assume you are lower than the
*           first level of the Registry and the user is trying
*           to enumerate one of the children.  First calculate
*           the name of the child, and then use RegOpenKey to
*           get an open handle.
*
*           If hKeyRoot == 0, assume you are at the top level
*           of the Registry, and set the hKey to be enumerated
*           to be one of the 4 predefined values, the specific
*           one indicated by the ListBox selection.
*
\************************************************************************/
VOID EnumerateLevel (HWND hDlg, LPTSTR NameLBSelect,
                     LPTSTR RegPath, size_t RegPathSize, HKEY *hKeyRoot)
{
  
  HKEY hKey;
  DWORD  retCode;
  TCHAR   Buf[80];
  
  if (*hKeyRoot)
  {
    // If RegPath is not NULL, then
    // you have to add a backslash to the
    // path name before appending the next
    // level child name.
    if (lstrcmp (RegPath, TEXT("")) != 0)
      StringCchCat (RegPath, RegPathSize, TEXT("\\"));
    
    // Add the next level child name.
    StringCchCat (RegPath, RegPathSize, NameLBSelect);
    
    // Use RegOpenKeyEx() with the new
    // Registry path to get an open handle
    // to the child key you want to
    // enumerate.
    retCode = RegOpenKeyEx (*hKeyRoot,
      RegPath,
      0,
      KEY_ENUMERATE_SUB_KEYS |
      KEY_EXECUTE |
      KEY_QUERY_VALUE,
      &hKey);
    
    if (retCode != ERROR_SUCCESS)
    {
      if (retCode == ERROR_ACCESS_DENIED)
        StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Error: unable to open key.  Probably due to security reasons."));
      else
        StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Error: Unable to open key, RegOpenKey = %d, Line = %d"),
        retCode, __LINE__);
      
      MessageBox (hDlg, Buf, TEXT(""), MB_OK);
      PostMessage (hDlg, WM_COMMAND, IDB_BACK, 0);
      return;
    }
    
  }
  else
  {
    // Set the *hKeyRoot handle based
    // on the text taken from the ListBox.
    
    if (lstrcmp (NameLBSelect, TEXT("HKEY_CLASSES_ROOT")) == 0)
      *hKeyRoot = HKEY_CLASSES_ROOT;
    
    if (lstrcmp (NameLBSelect, TEXT("HKEY_USERS")) == 0)
      *hKeyRoot = HKEY_USERS;
    
    if (lstrcmp (NameLBSelect, TEXT("HKEY_LOCAL_MACHINE")) == 0)
      *hKeyRoot = HKEY_LOCAL_MACHINE;
    
    if (lstrcmp (NameLBSelect, TEXT("HKEY_CURRENT_USER")) == 0)
      *hKeyRoot = HKEY_CURRENT_USER;
    
    hKey = *hKeyRoot;     // hKey is used in RegEnumKey().
  }//end if/else *hKeyRoot
  
  QueryKey (hDlg, hKey);
  
  RegCloseKey (hKey);   // Close the key handle.
  
  //      rect.top = 0; rect.left = 5; rect.right = 1200; rect.bottom = 25;
  //      hDC = GetDC (hDlg);
  //      FillRect (hDC, &rect, GetStockObject(WHITE_BRUSH));
  //      TextOut (hDC, 5, 5, RegPath, strlen(RegPath));
  //      ReleaseDC (hDlg, hDC);
  //      SetDlgItemText (hDlg, IDE_TEXTOUT, RegPath);
  
  {
    TCHAR	rgFullPath[MAX_PATH];
    TCHAR	*pszRoot = TEXT("HKEY_CLASSES_ROOT");
    
    if ( hKey == HKEY_USERS ) pszRoot = TEXT("HKEY_USERS");
    else if ( hKey == HKEY_LOCAL_MACHINE ) pszRoot = TEXT("HKEY_LOCAL_MACHINE");
    else if ( hKey == HKEY_CURRENT_USER ) pszRoot = TEXT("HKEY_CURRENT_USER");
    if ( *RegPath )
      StringCchPrintf(rgFullPath, ARRAYSIZE(rgFullPath), TEXT("%s\\%s"), pszRoot, RegPath);
    else
      StringCchCopy(rgFullPath, ARRAYSIZE(rgFullPath), pszRoot);
    SetDlgItemText (hDlg, IDE_TEXTOUT, rgFullPath);
  }
}


/************************************************************************\
*
*  FUNCTION: QueryKey();
*
*  PURPOSE:  To display the key's children (subkeys) and the names of
*            the Values associated with it.  This function uses RegEnumKey,
*            RegEnumValue, and RegQueryInfoKey.
*
\************************************************************************/
VOID QueryKey (HWND hDlg, HKEY hKey)
{
  TCHAR     KeyName[MAX_PATH];
  TCHAR     ClassName[MAX_PATH] = TEXT(""); // Buffer for class name.
  DWORD    dwcClassLen = MAX_PATH;   // Length of class string.
  DWORD    dwcSubKeys;               // Number of sub keys.
  DWORD    dwcMaxSubKey;             // Longest sub key size.
  DWORD    dwcMaxClass;              // Longest class string.
  DWORD    dwcValues;                // Number of values for this key.
  DWORD    dwcMaxValueName;          // Longest Value name.
  DWORD    dwcMaxValueData;          // Longest Value data.
  DWORD    dwcSecDesc;               // Security descriptor.
  FILETIME ftLastWriteTime;          // Last write time.
  DWORD	   cbName;
  DWORD i;
  DWORD retCode;
  
  DWORD j;
  DWORD retValue;
  TCHAR  ValueName[MAX_VALUE_NAME];
  DWORD dwcValueName = MAX_VALUE_NAME;
  TCHAR  Buf[80];
  
  
  // Get Class name, Value count.
  
  RegQueryInfoKey (hKey,              // Key handle.
    ClassName,         // Buffer for class name.
    &dwcClassLen,      // Length of class string.
    NULL,              // Reserved.
    &dwcSubKeys,       // Number of sub keys.
    &dwcMaxSubKey,     // Longest sub key size.
    &dwcMaxClass,      // Longest class string.
    &dwcValues,        // Number of values for this key.
    &dwcMaxValueName,  // Longest Value name.
    &dwcMaxValueData,  // Longest Value data.
    &dwcSecDesc,       // Security descriptor.
    &ftLastWriteTime); // Last write time.
  
  SetDlgItemText (hDlg, IDE_CLASS, ClassName);
  SetDlgItemInt  (hDlg, IDE_CVALUES, dwcValues, FALSE);
  
  SendMessage (GetDlgItem (hDlg, IDL_LISTBOX),
    LB_ADDSTRING, 0, (LONG)TEXT(".."));
  
  // Loop until RegEnumKey fails, get
  // the name of each child and enter
  // it into the box.
  
  // Enumerate the Child Keys.
  
  //  SetCursor (LoadCursor (NULL, IDC_WAIT));
  for (i=0, retCode = ERROR_SUCCESS; retCode == ERROR_SUCCESS; i++)
  {
    cbName = MAX_PATH;
    
    retCode = RegEnumKeyEx(
      hKey,  // handle of key to enumerate
      i,      // index of subkey to enumerate
      KeyName,      // address of buffer for subkey name
      &cbName,   // address for size of subkey buffer
      NULL, // reserved
      NULL,     // address of buffer for class string
      NULL,  // address for size of class buffer
      NULL
      );
    
    if (retCode == (DWORD)ERROR_SUCCESS)
      SendMessage (GetDlgItem(hDlg, IDL_LISTBOX),
      LB_ADDSTRING, 0, (LONG)KeyName);
  }
  
  
  // Enumerate the Key Values
  
  if (dwcValues)
    for (j = 0, retValue = ERROR_SUCCESS; j < dwcValues; j++)
    {
      dwcValueName = MAX_VALUE_NAME;
      ValueName[0] = TEXT('\0');
      retValue = RegEnumValue (hKey, j, ValueName,
        &dwcValueName,
        NULL,
        NULL,
        NULL,
        NULL);
      if (retValue != (DWORD)ERROR_SUCCESS &&
        retValue != ERROR_INSUFFICIENT_BUFFER)
      {
        StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Line:%d 0 based index = %d, retValue = %d, ValueLen = %d"),
          __LINE__, j, retValue, dwcValueName);
      }
      
      Buf[0] = TEXT('\0');
	  size_t cLen;
	  HRESULT hResult = StringCchLength(ValueName, ARRAYSIZE(ValueName), &cLen);
      if (SUCCEEDED(hResult) && !cLen)
        StringCchCopy(ValueName, ARRAYSIZE(ValueName), TEXT("<NO NAME>"));
      StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("%d) %s "), j, ValueName);
      SendMessage (GetDlgItem (hDlg, IDL_LISTBOX2),
        LB_ADDSTRING, 0, (LONG)Buf);
      
    }// end for(;;)
    
    //  SetCursor (LoadCursor (NULL, IDC_ARROW));
}



/************************************************************************\
*
*  FUNCTION: DisplayKeyData();
*
*  PURPOSE:  To display the keys values and value types to the Value edit
*            field.  This function is called when the right hand listbox
*            is double clicked.  The functionality is much like that found
*            in the function PrintTree, please see it for more details.
*
\************************************************************************/


VOID DisplayKeyData (HWND hDlg, TCHAR *RegPath, HKEY hKeyRoot)
{
  HKEY		hKey;
  DWORD		dwLBIndex;
  TCHAR		Buf[LINE_LEN];
  TCHAR		ValueName[MAX_VALUE_NAME];
  DWORD		cbValueName = MAX_VALUE_NAME;
  DWORD		dwType;
  DWORD		retCode;
  TCHAR		ClassName[MAX_PATH];
  DWORD		dwcClassLen = MAX_PATH;
  DWORD		dwcSubKeys;
  DWORD		dwcMaxSubKey;
  DWORD		dwcMaxClass;
  DWORD		dwcValues;
  DWORD		dwcMaxValueName;
  DWORD		dwcMaxValueData;
  DWORD		dwcSecDesc;
  FILETIME	ftLastWriteTime;
  BYTE   	*bData;
  DWORD  	cbData;
  TCHAR  	*outBuf;
  DWORD  	i;
//  DWORD  	cStrLen;
  TCHAR  	*BinaryStrBuf;
  TCHAR  	*ptr;
  size_t    cCharacters;
  size_t	cPtrCharacters;
  size_t	cbBytes;

  // OPEN THE KEY.
  
  // LBIndex should == value index.
  dwLBIndex = SendMessage (GetDlgItem (hDlg, IDL_LISTBOX2),
    LB_GETCURSEL, 0, 0);
  
  retCode = RegOpenKeyEx (hKeyRoot,    // Key handle at root level.
    RegPath,     // Path name of child key.
    0,           // Reserved.
    KEY_EXECUTE, // Requesting read access.
    &hKey);      // Address of key to be returned.
  
  if (retCode)
  {
    StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Error: RegOpenKeyEx = %d"), retCode);
    MessageBox (hDlg, Buf, TEXT("DisplayKeyData()"), MB_OK);
    return;
  }
  
  // ADD A QUERY AND ALLOCATE A BUFFER FOR BDATA.
  //  SetCursor (LoadCursor (NULL, IDC_WAIT));
  
  retCode =
    RegQueryInfoKey (hKey,              // Key handle.
    ClassName,         // Buffer for class name.
    &dwcClassLen,      // Length of class string.
    NULL,              // Reserved.
    &dwcSubKeys,       // Number of sub keys.
    &dwcMaxSubKey,     // Longest sub key size.
    &dwcMaxClass,      // Longest class string.
    &dwcValues,        // Number of values for this key.
    &dwcMaxValueName,  // Longest Value name.
    &dwcMaxValueData,  // Longest Value data.
    &dwcSecDesc,       // Security descriptor.
    &ftLastWriteTime); // Last write time.
  
  if (retCode)
  {
    StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Error: RegQIK = %d, %d"), retCode, __LINE__);
    MessageBox (hDlg, Buf, TEXT(""), MB_OK);
  }
  
  bData = (BYTE *) LocalAlloc(LMEM_FIXED, dwcMaxValueData);
  cbData = dwcMaxValueData;
  
  
  // ENUMERATE THE KEY.
  
  retCode = RegEnumValue (hKey,        // Key handle returned from RegOpenKeyEx.
    dwLBIndex,   // Value index, taken from listbox.
    ValueName,   // Name of value.
    &cbValueName,// Size of value name.
    NULL,        // Reserved, dword = NULL.
    &dwType,     // Type of data.
    bData,       // Data buffer.
    &cbData);    // Size of data buffer.
  
  if (retCode != ERROR_SUCCESS)
  {
    
    if (dwType < REG_FULL_RESOURCE_DESCRIPTOR)
    {
      StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Error: RegEnumValue = %d, cbData = %d, line %d"),
        retCode, cbData, __LINE__);
      MessageBox (hDlg, Buf, TEXT(""), MB_OK);
    }
  }
  
  
  switch (dwType)
  {
    //    REG_NONE                    ( 0 )   // No value type
    //    REG_SZ                      ( 1 )   // Unicode nul terminated string
    //    REG_EXPAND_SZ               ( 2 )   // Unicode nul terminated string
    // (with environment variable references)
    //    REG_BINARY                  ( 3 )   // Free form binary
    //    REG_DWORD                   ( 4 )   // 32-bit number
    //    REG_DWORD_LITTLE_ENDIAN     ( 4 )   // 32-bit number (same as REG_DWORD)
    //    REG_DWORD_BIG_ENDIAN        ( 5 )   // 32-bit number
    //    REG_LINK                    ( 6 )   // Symbolic Link (unicode)
    //    REG_MULTI_SZ                ( 7 )   // Multiple Unicode strings
    //    REG_RESOURCE_LIST           ( 8 )   // Resource list in the resource map
    //    REG_FULL_RESOURCE_DESCRIPTOR ( 9 )  // Resource list in the hardware description
    
  case REG_NONE:
    SetDlgItemText (hDlg, IDE_VALUE1, (LPCTSTR) TEXT("REG_NONE: No defined value type."));
    break;
    
  case REG_SZ:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_SZ: A null-terminated Unicode string."));
    
	cbBytes = cbData + (2*sizeof(TCHAR)); // include two characters for the quotes
    cCharacters = cbBytes / sizeof(TCHAR);
    outBuf = (TCHAR *) LocalAlloc(LMEM_FIXED, cbBytes); 
    *outBuf = TEXT('\0');
    
    StringCchCat (outBuf, cCharacters, TEXT("\""));
    StringCchCat (outBuf, cCharacters,(LPTSTR) bData);
    StringCchCat (outBuf, cCharacters, TEXT("\""));
    
    SetDlgItemText (hDlg, IDE_VALUE2, outBuf);
    LocalFree ((HLOCAL)outBuf);
    break;
    
  case REG_EXPAND_SZ:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_EXPAND_SZ: A String referencing environment variables i.e. PATH."));

	cbBytes = cbData + (2*sizeof(TCHAR)); // include two characters for the quotes
    cCharacters = cbBytes / sizeof(TCHAR);
    outBuf = (TCHAR *)LocalAlloc (LMEM_FIXED, cbBytes); 
    *outBuf = TEXT('\0');
    
    StringCchCat (outBuf, cCharacters, TEXT("\""));
    StringCchCat (outBuf, cCharacters, (LPTSTR) bData);
    StringCchCat (outBuf, cCharacters, TEXT("\""));
    
    SetDlgItemText (hDlg, IDE_VALUE2, outBuf);
    LocalFree ((HLOCAL)outBuf);
    break;
    
  case REG_BINARY:
	cbBytes = (3 * cbData * sizeof(TCHAR)) + sizeof(TCHAR);	// cbData is count of Binary data, which we will then represent in TCHAR

    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_BINARY: Freeform binary data."));
    BinaryStrBuf = (TCHAR * )LocalAlloc (LMEM_FIXED, cbBytes);
    if (BinaryStrBuf)
    {
      for (i = 0; i < cbData; i++)
      {
		cCharacters = (cbBytes / sizeof(TCHAR)) - (3 * i);
        StringCchPrintf (BinaryStrBuf+(3*i), cCharacters, TEXT("%02x "), (BYTE)bData[i]);
      }
      BinaryStrBuf[i*3] = TEXT('\0');
      SetDlgItemText (hDlg, IDE_VALUE2, BinaryStrBuf);
    }
    else
    {
      MessageBox (hDlg, TEXT("Error: BinaryStrBuf = malloc failed"),
        TEXT("Debug: DisplayKeyData"), MB_OK);
    }
    SetDlgItemText (hDlg, IDL_LISTBOX2, BinaryStrBuf);
    LocalFree ((HLOCAL)BinaryStrBuf);
    
    break;
    
  case REG_DWORD:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_DWORD: A 32 bit number."));
    SetDlgItemInt (hDlg, IDE_VALUE2, *(UINT *)bData, FALSE);
    break;
    
  case REG_DWORD_BIG_ENDIAN:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_DWORD_BIG_ENDIAN: A 32 bit number in big endian format."));
    SetDlgItemInt (hDlg, IDE_VALUE2, *(UINT *)bData, TRUE);
    break;
    
  case REG_LINK:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_LINK: A Unicode symbolic link."));
    SetDlgItemText (hDlg, IDE_VALUE2, (LPTSTR) bData);
    break;
    
  case REG_MULTI_SZ:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_MULTI_SZ: An array of null-terminated strings."));
    // Count the NULLs in the buffer to
    // find out how many strings there are.
    ptr = (LPTSTR)bData;
    cCharacters = cbData / sizeof(TCHAR);
    for (i=0, cbBytes = 0; i < cCharacters; i++)
    {
      if (!ptr[i])
      {
        cbBytes +=4 * sizeof(TCHAR);     // Add room for two quotes and two spaces per string. 
      }                      
      else
      {
        cbBytes += sizeof(TCHAR);
      }
    }

    cbBytes += 4 * sizeof(TCHAR);        // Add room for the 2 braces and 2 spaces
    cbBytes += sizeof(TCHAR);            // Add room for the NULL character at the end;

    cCharacters = cbBytes / sizeof(TCHAR);
    outBuf = (TCHAR *)LocalAlloc (LMEM_FIXED, cbBytes);
      
    ptr = (LPTSTR) bData;                     // Set ptr to beginning of buffer.
    *outBuf = TEXT('\0');                  // Initialize output string.
      
      
    size_t cLen;
    StringCchCat(outBuf, cCharacters, TEXT("{  "));    // Do first bracket.
    cPtrCharacters = cbData / sizeof(TCHAR);
    while (*ptr)                     // Loop til you hit 2 NULLs in a row.
    {
      StringCchCat(outBuf, cCharacters, TEXT("\""));        // Put quotes around each string.
      StringCchCat(outBuf, cCharacters, ptr);
      StringCchCat(outBuf, cCharacters, TEXT("\"  "));
      StringCchLength(ptr, cPtrCharacters, &cLen);
      ptr += cLen + 1;
      cPtrCharacters -= cLen + 1;
    }
    StringCchCat(outBuf, cCharacters, TEXT("}"));            // Add final bracket.
    SetDlgItemText (hDlg, IDE_VALUE2, outBuf);
    LocalFree ((HLOCAL) outBuf);                 // free output string.
    break;
      
      
  case REG_RESOURCE_LIST:            // CM_RESOURCE_LIST is complex.  Print it
    // as a free formed binary data for now.
    
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_RESOURCE_LIST: A device-driver resource list."));
    
	cbBytes = (3 * cbData * sizeof(TCHAR)) + sizeof(TCHAR);	// cbData is count of Binary data, which we will then represent in TCHAR
	BinaryStrBuf = (TCHAR *) LocalAlloc (LMEM_FIXED, cbBytes);
    if (BinaryStrBuf)
    {
      for (i = 0; i < cbData; i++)
      {
		cCharacters = (cbBytes / sizeof(TCHAR)) - (3 * i);
        StringCchPrintf (BinaryStrBuf+(3*i), cCharacters, TEXT("%02x "), (BYTE)bData[i]);
      }
      BinaryStrBuf[3*i] = TEXT('\0');
      SetDlgItemText (hDlg, IDE_VALUE2, BinaryStrBuf);
    }
    else
    {
      MessageBox (hDlg, TEXT("Error: BinaryStrBuf = malloc failed"),
        TEXT("Debug: DisplayKeyData"), MB_OK);
    }
    SetDlgItemText (hDlg, IDL_LISTBOX2, BinaryStrBuf);
    LocalFree ((HLOCAL)BinaryStrBuf);
    
    break;
    
  case REG_FULL_RESOURCE_DESCRIPTOR:
    SetDlgItemText (hDlg, IDE_VALUE1, TEXT("REG_FULL_RESOURCE_DESCRIPTOR: A resource list in the hardware description."));
    break;
    
    
    
  default:
    StringCchPrintf (Buf, ARRAYSIZE(Buf), TEXT("Undefined in this verion of the Registry Viewer. %d"),
      dwType);
    SetDlgItemText (hDlg, IDE_VALUE1, Buf);
    break;
    
} // end switch


LocalFree ((HLOCAL)bData);
//  SetCursor (LoadCursor (NULL, IDC_ARROW));
}
